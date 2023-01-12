/*
 * ddns.c
 *
 * Copyright (C) 2006-2022 Sebastian Gottschall <s.gottschall@dd-wrt.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Id:
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <syslog.h>
#include <sys/wait.h>

#include <bcmnvram.h>
#include <netconf.h>
#include <shutils.h>
#include <utils.h>
#include <rc.h>
#include <services.h>

/*
 * inadyn scripts by lawnmowerguy1 
 */

static char _username[] = "ddns_username_XX";
#ifdef HAVE_IPV6
static char _ipv6[] = "ddns_ipv6_XX";
#endif
static char _passwd[] = "ddns_passwd_XX";
static char _hostname[] = "ddns_hostname_XX";
static char _wildcard[] = "ddns_wildcard_XX";
static char _ssl[] = "ddns_ssl_XX";
static char _cache_file[128];
static char _cache_file_ipv6[128];
static int init_ddns(FILE * fp)
{

	int flag = nvram_geti("ddns_enable");
	if (flag > 33 || flag < 1)
		return -1;
	char *providers[] = {
		NULL,
		"default@dyndns.org",
		"default@freedns.afraid.org",
		"default@zoneedit.com",
		"default@no-ip.com",
		NULL,
		"default@3322.org",
		"default@easydns.com",
		"default@dnsomatic.com",
		"default@selfhost.de",
		"default@he.net",
		"default@duiadns.net",
		"default@tunnelbroker.net",
		"default@spdyn.de",
		"ipv4@nsupdate.info",
		"default@loopia.com",
		"default@domains.google.com",
		"default@dynu.com",
		"default@changeip.com",
		"default@ovh.com",
		"default@strato.com",
		"default@cloudflare.com",
		"default@cloudxns.net",
		"default@ddnss.de",
		"default@dhis.org",
		"default@dnsexit.com",
		"default@dnspod.cn",
		"default@duckdns.org",
		"default@freemyip.com",
		"default@gira.de",
		"default@sitelutions.com",
		"default@pdd.yandex.ru",
		"default@ipv4.dynv6.com",
		"default@goip.de",
	};

#ifdef HAVE_IPV6
	char *providers_ipv6[] = {
		NULL,
		NULL,
		"ipv6@freedns.afraid.org",
		"ipv6@zoneedit.com",
		"ipv6@no-ip.com",
		NULL,
		"ipv6@3322.org",
		"ipv6@easydns.com",
		"ipv6@dnsomatic.com",
		"ipv6@selfhost.de",
		"ipv6tb@he.net",
		"ipv6@duiadns.net",
		"ipv6tb@he.net",
		"ipv6@spdyn.de",
		"ipv6@nsupdate.info",
		NULL,
		"ipv6@domains.google.com",
		"ipv6@dynu.com",
		NULL,
		"ipv6@ovh.com",
		"ipv6@strato.com",
		"ipv6@cloudflare.com",
		NULL,
		NULL,
		"ipv6@dhis.org",
		"ipv6@dnsexit.com",
		NULL,
		"ipv6@duckdns.org",
		NULL,
		"ipv6@gira.de",
		NULL,
		NULL,
		"default@dynv6.com",
		"ipv6@goip.de",
	};
#endif
	char *provider = providers[flag];
	char *provider6 = NULL;
	snprintf(_ssl, sizeof(_ssl), "%s", "ddns_ssl");
	if (flag == 1) {
		snprintf(_username, sizeof(_username), "%s", "ddns_username");
		snprintf(_passwd, sizeof(_passwd), "%s", "ddns_passwd");
		snprintf(_hostname, sizeof(_hostname), "%s", "ddns_hostname");
#ifdef HAVE_IPV6
		snprintf(_ipv6, sizeof(_ipv6), "%s", "ddns_ipv6");
		if (nvram_matchi("ipv6_enable", 1) && nvram_matchi(_ipv6, 1))
			provider6 = providers_ipv6[flag];
#endif
		snprintf(_wildcard, sizeof(_hostname), "%s", "ddns_wildcard");
		snprintf(_cache_file, sizeof(_cache_file), "/tmp/ddns/%s-%s.cache", provider, nvram_safe_get("ddns_hostname"));
		snprintf(_cache_file_ipv6, sizeof(_cache_file_ipv6), "/tmp/ddns/%s-%s.cache", provider6, nvram_safe_get("ddns_hostname"));
	} else {
		snprintf(_username, sizeof(_username), "%s_%d", "ddns_username", flag);
		snprintf(_passwd, sizeof(_passwd), "%s_%d", "ddns_passwd", flag);
		snprintf(_hostname, sizeof(_hostname), "%s_%d", "ddns_hostname", flag);
#ifdef HAVE_IPV6
		snprintf(_ipv6, sizeof(_ipv6), "%s_%d", "ddns_ipv6", flag);
		if (nvram_matchi("ipv6_enable", 1) && nvram_matchi(_ipv6, 1))
			provider6 = providers_ipv6[flag];
#endif
		snprintf(_wildcard, sizeof(_hostname), "%s_%d", "ddns_wildcard", flag);
		snprintf(_cache_file, sizeof(_cache_file), "/tmp/ddns/%s-%s.cache", provider, nvram_nget("ddns_hostname_%d", flag));
		snprintf(_cache_file_ipv6, sizeof(_cache_file_ipv6), "/tmp/ddns/%s-%s.cache",provider6, nvram_nget("ddns_hostname_%d", flag));
	}
	if (fp) {
#ifdef HAVE_IPV6
		if (provider6)
			fprintf(fp, "allow-ipv6 = true\n");
		if (!provider6 || flag != 16) {
#endif

			if (flag == 5)
				fprintf(fp, "custom namecheap {\n");
			else
				fprintf(fp, "provider %s {\n", provider);
			if (flag != 28 && flag != 11)
				fprintf(fp, "username = \"%s\"\n", nvram_safe_get(_username));
			if (flag == 27)
				fprintf(fp, "password = \"nopasswd\"\n");
			else
				fprintf(fp, "password = \"%s\"\n", nvram_safe_get(_passwd));

			char *next;
			char var[128];
			char *hn = nvram_safe_get(_hostname);
			fprintf(fp, "hostname = {");
			int idx = 0;
			foreach(var, hn, next) {
				if (idx)
					fprintf(fp, ", ");
				fprintf(fp, "\"%s\"", var);
				idx++;
			}
			fprintf(fp, "}\n");
#ifdef HAVE_USE_OPENSSL
			fprintf(fp, "ssl = %s\n", nvram_match(_ssl, "1") ? "true" : "false");
#endif
			if (nvram_match(_wildcard, "1"))
				fprintf(fp, "wildcard = true\n");
			if (flag == 5) {
				fprintf(fp, "ddns-server = \"%s\"\n", nvram_safe_get("ddns_custom_5"));
				fprintf(fp, "ddns-path = \"%s\"\n", nvram_safe_get("ddns_path_5"));
			}
			if (nvram_match("ddns_wan_ip", "1")) {
				fprintf(fp, "checkip-command = \"/sbin/service checkwanip main\"\n");
			}
			fprintf(fp, "}\n");

#ifdef HAVE_IPV6
		}
		if (provider6) {
			fprintf(fp, "provider %s {\n", provider6);

			if (flag != 28 && flag != 11)
				fprintf(fp, "username = \"%s\"\n", nvram_safe_get(_username));
			if (flag == 27)
				fprintf(fp, "password = \"nopasswd\"\n");
			else
				fprintf(fp, "password = \"%s\"\n", nvram_safe_get(_passwd));

			char *next;
			char var[128];
			char *hn = nvram_safe_get(_hostname);
			fprintf(fp, "hostname = {");
			int idx = 0;
			foreach(var, hn, next) {
				if (idx)
					fprintf(fp, ", ");
				fprintf(fp, "\"%s\"", var);
				idx++;
			}
			fprintf(fp, "}\n");
#ifdef HAVE_USE_OPENSSL
			fprintf(fp, "ssl = %s\n", nvram_match(_ssl, "1") ? "true" : "false");
#endif
			if (nvram_match(_wildcard, "1"))
				fprintf(fp, "wildcard = true\n");
			if (flag == 5) {
				fprintf(fp, "ddns-server = \"%s\"\n", nvram_safe_get("ddns_custom_5"));
				fprintf(fp, "ddns-path = \"%s\"\n", nvram_safe_get("ddns_path_5"));
			}
			if (nvram_match("ddns_wan_ip", "1")) {
				fprintf(fp, "checkip-command = \"/sbin/service checkwanip main\"\n");
			} else {
				fprintf(fp, "checkip-server = dns64.cloudflare-dns.com\n");
				fprintf(fp, "checkip-path = /cdn-cgi/trace\n");
			}
			fprintf(fp, "}\n");

		}
#endif
	}
	return 0;
}

void start_ddns(void)
{
	int ret;
	FILE *fp;

	int flag = nvram_geti("ddns_enable");
	if (flag > 33 || flag < 1)
		return -1;

	mkdir("/tmp/ddns", 0744);

	/*
	 * Generate ddns configuration file 
	 */
	if ((fp = fopen("/tmp/ddns/inadyn.conf", "w"))) {
		if (nvram_matchi("ddns_enable", 7))
			fprintf(fp, "period = %s\n", "900");
		else
			fprintf(fp, "period = %s\n", "600");
		fprintf(fp, "forced-update = %d\n", nvram_geti("ddns_force") * 24 * 60 * 60);
		if (init_ddns(fp) < 0)
			return;
		fprintf(fp, "\n");
		fclose(fp);
	} else {
		perror("/tmp/ddns/inadyn.conf");
		return;
	}

	if (strcmp(nvram_safe_get("ddns_enable_buf"), nvram_safe_get("ddns_enable")) ||
	    strcmp(nvram_safe_get("ddns_username_buf"), nvram_safe_get(_username)) || strcmp(nvram_safe_get("ddns_passwd_buf"), nvram_safe_get(_passwd)) ||
#ifdef HAVE_IPV6
	    strcmp(nvram_safe_get("ddns_ipv6_buf"), nvram_safe_get(_ipv6)) ||
#endif
	    strcmp(nvram_safe_get("ddns_hostname_buf"), nvram_safe_get(_hostname)) || strcmp(nvram_safe_get("ddns_wildcard_buf"), nvram_safe_get(_wildcard)) ||
#ifdef HAVE_USE_OPENSSL
	    strcmp(nvram_safe_get("ddns_ssl_buf"), nvram_safe_get(_ssl)) ||
#endif
	    strcmp(nvram_safe_get("ddns_path_buf"), nvram_safe_get("ddns_path_5")) || strcmp(nvram_safe_get("ddns_custom_buf"), nvram_safe_get("ddns_custom_5"))) {
		/*
		 * If the user changed anything in the GUI, delete all cache and log 
		 */
		nvram_unset("ddns_cache");
		nvram_unset("ddns_cache_ipv6");
		unlink("/tmp/ddns/ddns.log");
		unlink(_cache_file);
		unlink(_cache_file_ipv6);
	}

	/*
	 * Restore cache data to file from NV 
	 */
	if (nvram_invmatch("ddns_cache", "")) {
		nvram2file("ddns_cache", _cache_file);
	}
	if (nvram_invmatch("ddns_cache_ipv6", "")) {
		nvram2file("ddns_cache_ipv6", _cache_file_ipv6);
	}
	if (nvram_matchi("ddns_once", 0)) {
		dd_logstart("ddns", eval("inadyn", "--cache-dir=/tmp/ddns", "-e", "ddns_success", "--exec-mode=compat", "-f", "/tmp/ddns/inadyn.conf", "-P", "/var/run/inadyn.pid", "-l", "notice", "-t", "30"));
		nvram_seti("ddns_once", 1);
	} else {
		dd_logstart("ddns", eval("inadyn", "--cache-dir=/tmp/ddns", "-e", "ddns_success", "--exec-mode=compat", "-f", "/tmp/ddns/inadyn.conf", "-P", "/var/run/inadyn.pid", "-l", "notice"));
	}
	cprintf("done\n");

	return;
}

void stop_ddns(void)
{
	int ret;
	stop_process("inadyn", "dynamic dns daemon");
	if (init_ddns(NULL) == 0) {
		unlink(_cache_file);
		unlink(_cache_file_ipv6);
	}
	if (nvram_matchi("ddns_enable", 0)) {
		unlink("/tmp/ddns/inadyn.conf");
	}
	unlink("/tmp/ddns/ddns.log");

	cprintf("done\n");

	return;
}

int checkwanip_main(int argc, char *argv[])
{
	char new_ip_str[32];
	int wan_link = check_wan_link(0);
	if (!wan_link)
		return -1;
	char *wan_ipaddr = NULL;
	if (nvram_match("wan_proto", "pptp")) {
		wan_ipaddr = wan_link ? nvram_safe_get("pptp_get_ip") : nvram_safe_get("wan_ipaddr");
	} else if (!strcmp(nvram_safe_get("wan_proto"), "pppoe")) {
		wan_ipaddr = wan_link ? nvram_safe_get("wan_ipaddr") : "0.0.0.0";
	} else if (!strcmp(nvram_safe_get("wan_proto"), "3g")) {
		wan_ipaddr = wan_link ? nvram_safe_get("wan_ipaddr") : "0.0.0.0";
	} else if (nvram_match("wan_proto", "l2tp")) {
		wan_ipaddr = wan_link ? nvram_safe_get("l2tp_get_ip") : nvram_safe_get("wan_ipaddr");
	} else if (nvram_match("wan_proto", "disabled")) {
		wan_ipaddr = "0.0.0.0";
		return -1;
	} else {
		wan_ipaddr = nvram_safe_get("wan_ipaddr");
	}

#ifdef HAVE_IPV6
	char *provider = getenv("INADYN_PROVIDER");
	if (provider && strstr(provider, "v6")) {
		char wan_if_buffer[33];
		char buf[INET6_ADDRSTRLEN];
		const char *ipv6addr = NULL;
		if (nvram_match("ipv6_typ", "ipv6native"))
			ipv6addr = getifaddr(buf, safe_get_wan_face(wan_if_buffer), AF_INET6, 0);
		if (nvram_match("ipv6_typ", "ipv6in4"))
			ipv6addr = getifaddr(buf, "ip6tun", AF_INET6, 0);
		if (nvram_match("ipv6_typ", "ipv6pd"))
			ipv6addr = getifaddr(buf, safe_get_wan_face(wan_if_buffer), AF_INET6, 0);
//			ipv6addr = getifaddr(buf, nvram_safe_get("lan_ifname"), AF_INET6, 0);
		if (nvram_match("ipv6_typ", "ipv6in4") || nvram_match("ipv6_typ", "ipv6pd") || nvram_match("ipv6_typ", "ipv6native")) {
			if (!ipv6addr)
				ipv6addr = getifaddr(buf, safe_get_wan_face(wan_if_buffer), AF_INET6, 0);	// try wan if all other fails
			if (ipv6addr)
				wan_ipaddr = ipv6addr;
		}
	}
#endif

	if (!strcmp(wan_ipaddr, "0.0.0.0")) {
		return -1;
	}
	fprintf(stdout, "%s\n", wan_ipaddr);
	return 0;
}

int ddns_success_main(int argc, char *argv[])
{
	char buf[80];
	char buf2[80];
	FILE *fp;

	if (init_ddns(NULL) == 0) {
		if ((fp = fopen(_cache_file, "r"))) {
			fgets(buf, sizeof(buf), fp);
			fclose(fp);
			nvram_set("ddns_cache", buf);
		}
		if ((fp = fopen(_cache_file_ipv6, "r"))) {
			fgets(buf, sizeof(buf), fp);
			fclose(fp);
			nvram_set("ddns_cache_ipv6", buf);
		}
	}

	nvram_set("ddns_enable_buf", nvram_safe_get("ddns_enable"));
	nvram_set("ddns_username_buf", nvram_safe_get(_username));
	nvram_set("ddns_passwd_buf", nvram_safe_get(_passwd));
	nvram_set("ddns_hostname_buf", nvram_safe_get(_hostname));
#ifdef HAVE_IPV6
	nvram_set("ddns_ipv6_buf", nvram_safe_get(_ipv6));
#endif
#ifdef HAVE_USE_OPENSSL
	nvram_set("ddns_ssl_buf", nvram_safe_get(_ssl));
#endif
	nvram_set("ddns_wildcard_buf", nvram_safe_get(_wildcard));
	nvram_set("ddns_custom_buf", nvram_safe_get("ddns_custom_5"));
	nvram_set("ddns_path_buf", nvram_safe_get("ddns_path_5"));

	nvram_async_commit();

	cprintf("done\n");

	return 0;
}
