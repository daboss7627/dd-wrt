/* Plugin for mydns.jp
 *
 * Copyright (C) 2023 Sebastian Gottschall <s.gottschall@dd-wrt.com>
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
 * along with this program; if not, visit the Free Software Foundation
 * website at http://www.gnu.org/licenses/gpl-2.0.html or write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

#include "plugin.h"

#define MYDNS_UPDATE_IP_REQUEST						\
	"GET %s?"							\
	"MID=%s&"							\
	"PWD=%s&"							\
	"IPV4ADDR=%s "							\
	"HTTP/1.0\r\n"							\
	"Host: %s\r\n"							\
	"User-Agent: %s\r\n\r\n"

#define MYDNS_UPDATE_IP6_REQUEST						\
	"GET %s?"							\
	"MID=%s&"							\
	"PWD=%s&"							\
	"IPV6ADDR=%s "							\
	"GET %s?"							\
	"HTTP/1.0\r\n"							\
	"Host: %s\r\n"							\
	"User-Agent: %s\r\n\r\n"

static int request  (ddns_t       *ctx,   ddns_info_t *info, ddns_alias_t *alias);
static int response (http_trans_t *trans, ddns_info_t *info, ddns_alias_t *alias);

static ddns_system_t plugin = {
	.name         = "default@mydns.jp",

	.request      = (req_fn_t)request,
	.response     = (rsp_fn_t)response,

	.checkip_name = DYNDNS_MY_IP_SERVER,
	.checkip_url  = DYNDNS_MY_CHECKIP_URL,
	.checkip_ssl  = DYNDNS_MY_IP_SSL,

	.server_name  = "www.mydns.jp",
	.server_url   =  "/directip.html"
};

static ddns_system_t plugin_v6 = {
	.name         = "ipv6@mydns.jp",

	.request      = (req_fn_t)request,
	.response     = (rsp_fn_t)response,

	.checkip_name = "dns64.cloudflare-dns.com",
	.checkip_url  = "/cdn-cgi/trace",
	.checkip_ssl  = DDNS_CHECKIP_SSL_SUPPORTED,

	.server_name  = "www.mydns.jp",
	.server_url   =  "/directip.html"
};

static int request(ddns_t *ctx, ddns_info_t *info, ddns_alias_t *alias)
{
	if (strstr(info->system->name, "ipv6")) {
		return snprintf(ctx->request_buf, ctx->request_buflen,
			MYDNS_UPDATE_IP6_REQUEST,
			info->server_url,
			info->creds.username,
			info->creds.password,
			alias->address,
			info->server_name.name,
			info->user_agent);
	} else {
		return snprintf(ctx->request_buf, ctx->request_buflen,
			MYDNS_UPDATE_IP_REQUEST,
			info->server_url,
			info->creds.username,
			info->creds.password,
			alias->address,
			info->server_name.name,
			info->user_agent);
	}
}

static int response(http_trans_t *trans, ddns_info_t *info, ddns_alias_t *alias)
{
	char *rsp = trans->rsp_body;

	(void)info;
	(void)alias;

	DO(http_status_valid(trans->status));

	return RC_DDNS_RSP_NOTOK;
}

PLUGIN_INIT(plugin_init)
{
	plugin_register(&plugin);
	plugin_register(&plugin_v6);
}

PLUGIN_EXIT(plugin_exit)
{
	plugin_unregister(&plugin);
	plugin_unregister(&plugin_v6);
}

/**
 * Local Variables:
 *  indent-tabs-mode: t
 *  c-file-style: "linux"
 * End:
 */
