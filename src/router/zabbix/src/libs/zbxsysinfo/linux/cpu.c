/*
** Zabbix
** Copyright (C) 2001-2022 Zabbix SIA
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
**/

#include "common.h"
#include "sysinfo.h"
#include "stats.h"
#include "log.h"


/* uclibc and dietlibc do not have this junk -ReneR */
#if defined (__UCLIBC__) || defined (__dietlibc__)
static int getloadavg (double loadavg[], int nelem)
{
  int fd;

  fd = open ("/proc/loadavg", O_RDONLY);
  if (fd < 0)
    return -1;
  else
    {
      char buf[65], *p;
      ssize_t nread;
      int i;

      nread = read (fd, buf, sizeof buf - 1);
      close (fd);
      if (nread <= 0)
	return -1;
      buf[nread - 1] = '\0';

      if (nelem > 3)
	nelem = 3;
      p = buf;
      for (i = 0; i < nelem; ++i)
	{
	  char *endp;
	  loadavg[i] = strtod (p, &endp);
	  if (endp == p)
	    return -1;
	  p = endp;
	}

      return i;
    }
}
#endif

int	SYSTEM_CPU_NUM(AGENT_REQUEST *request, AGENT_RESULT *result)
{
	char	*type;
	int	name;
	long	ncpu;

	if (1 < request->nparam)
	{
		SET_MSG_RESULT(result, zbx_strdup(NULL, "Too many parameters."));
		return SYSINFO_RET_FAIL;
	}

	type = get_rparam(request, 0);

	if (NULL == type || '\0' == *type || 0 == strcmp(type, "online"))
		name = _SC_NPROCESSORS_ONLN;
	else if (0 == strcmp(type, "max"))
		name = _SC_NPROCESSORS_CONF;
	else
	{
		SET_MSG_RESULT(result, zbx_strdup(NULL, "Invalid first parameter."));
		return SYSINFO_RET_FAIL;
	}

	if (-1 == (ncpu = sysconf(name)))
	{
		SET_MSG_RESULT(result, zbx_dsprintf(NULL, "Cannot obtain number of CPUs: %s", zbx_strerror(errno)));
		return SYSINFO_RET_FAIL;
	}

	SET_UI64_RESULT(result, ncpu);

	return SYSINFO_RET_OK;
}

int	SYSTEM_CPU_UTIL(AGENT_REQUEST *request, AGENT_RESULT *result)
{
	char	*tmp;
	int	cpu_num, state, mode;

	if (3 < request->nparam)
	{
		SET_MSG_RESULT(result, zbx_strdup(NULL, "Too many parameters."));
		return SYSINFO_RET_FAIL;
	}

	tmp = get_rparam(request, 0);

	if (NULL == tmp || '\0' == *tmp || 0 == strcmp(tmp, "all"))
	{
		cpu_num = ZBX_CPUNUM_ALL;
	}
	else if (SUCCEED != is_uint31_1(tmp, &cpu_num))
	{
		SET_MSG_RESULT(result, zbx_strdup(NULL, "Invalid first parameter."));
		return SYSINFO_RET_FAIL;
	}

	tmp = get_rparam(request, 1);

	if (NULL == tmp || '\0' == *tmp || 0 == strcmp(tmp, "user"))
		state = ZBX_CPU_STATE_USER;
	else if (0 == strcmp(tmp, "nice"))
		state = ZBX_CPU_STATE_NICE;
	else if (0 == strcmp(tmp, "system"))
		state = ZBX_CPU_STATE_SYSTEM;
	else if (0 == strcmp(tmp, "idle"))
		state = ZBX_CPU_STATE_IDLE;
	else if (0 == strcmp(tmp, "iowait"))
		state = ZBX_CPU_STATE_IOWAIT;
	else if (0 == strcmp(tmp, "interrupt"))
		state = ZBX_CPU_STATE_INTERRUPT;
	else if (0 == strcmp(tmp, "softirq"))
		state = ZBX_CPU_STATE_SOFTIRQ;
	else if (0 == strcmp(tmp, "steal"))
		state = ZBX_CPU_STATE_STEAL;
	else if (0 == strcmp(tmp, "guest"))
		state = ZBX_CPU_STATE_GCPU;
	else if (0 == strcmp(tmp, "guest_nice"))
		state = ZBX_CPU_STATE_GNICE;
	else
	{
		SET_MSG_RESULT(result, zbx_strdup(NULL, "Invalid second parameter."));
		return SYSINFO_RET_FAIL;
	}

	tmp = get_rparam(request, 2);

	if (NULL == tmp || '\0' == *tmp || 0 == strcmp(tmp, "avg1"))
		mode = ZBX_AVG1;
	else if (0 == strcmp(tmp, "avg5"))
		mode = ZBX_AVG5;
	else if (0 == strcmp(tmp, "avg15"))
		mode = ZBX_AVG15;
	else
	{
		SET_MSG_RESULT(result, zbx_strdup(NULL, "Invalid third parameter."));
		return SYSINFO_RET_FAIL;
	}

	return get_cpustat(result, cpu_num, state, mode);
}

int	SYSTEM_CPU_LOAD(AGENT_REQUEST *request, AGENT_RESULT *result)
{
	char	*tmp;
	int	mode, per_cpu = 1, cpu_num;
	double	load[ZBX_AVG_COUNT], value;

	if (2 < request->nparam)
	{
		SET_MSG_RESULT(result, zbx_strdup(NULL, "Too many parameters."));
		return SYSINFO_RET_FAIL;
	}

	tmp = get_rparam(request, 0);

	if (NULL == tmp || '\0' == *tmp || 0 == strcmp(tmp, "all"))
	{
		per_cpu = 0;
	}
	else if (0 != strcmp(tmp, "percpu"))
	{
		SET_MSG_RESULT(result, zbx_strdup(NULL, "Invalid first parameter."));
		return SYSINFO_RET_FAIL;
	}

	tmp = get_rparam(request, 1);

	if (NULL == tmp || '\0' == *tmp || 0 == strcmp(tmp, "avg1"))
		mode = ZBX_AVG1;
	else if (0 == strcmp(tmp, "avg5"))
		mode = ZBX_AVG5;
	else if (0 == strcmp(tmp, "avg15"))
		mode = ZBX_AVG15;
	else
	{
		SET_MSG_RESULT(result, zbx_strdup(NULL, "Invalid second parameter."));
		return SYSINFO_RET_FAIL;
	}

	if (mode >= getloadavg(load, 3))
	{
		SET_MSG_RESULT(result, zbx_strdup(NULL, "Cannot obtain load average."));
		return SYSINFO_RET_FAIL;
	}

	value = load[mode];

	if (1 == per_cpu)
	{
		if (0 >= (cpu_num = sysconf(_SC_NPROCESSORS_ONLN)))
		{
			SET_MSG_RESULT(result, zbx_dsprintf(NULL, "Cannot obtain number of CPUs: %s",
				zbx_strerror(errno)));
			return SYSINFO_RET_FAIL;
		}
		value /= cpu_num;
	}

	SET_DBL_RESULT(result, value);

	return SYSINFO_RET_OK;
}

int     SYSTEM_CPU_SWITCHES(AGENT_REQUEST *request, AGENT_RESULT *result)
{
	int		ret = SYSINFO_RET_FAIL;
	char		line[MAX_STRING_LEN];
	zbx_uint64_t	value = 0;
	FILE		*f;

	ZBX_UNUSED(request);

	if (NULL == (f = fopen("/proc/stat", "r")))
	{
		SET_MSG_RESULT(result, zbx_dsprintf(NULL, "Cannot open /proc/stat: %s", zbx_strerror(errno)));
		return SYSINFO_RET_FAIL;
	}

	while (NULL != fgets(line, sizeof(line), f))
	{
		if (0 != strncmp(line, "ctxt", 4))
			continue;

		if (1 != sscanf(line, "%*s " ZBX_FS_UI64, &value))
			continue;

		SET_UI64_RESULT(result, value);
		ret = SYSINFO_RET_OK;
		break;
	}
	zbx_fclose(f);

	if (SYSINFO_RET_FAIL == ret)
		SET_MSG_RESULT(result, zbx_strdup(NULL, "Cannot find a line with \"ctxt\" in /proc/stat."));

	return ret;
}

int     SYSTEM_CPU_INTR(AGENT_REQUEST *request, AGENT_RESULT *result)
{
	int		ret = SYSINFO_RET_FAIL;
	char		line[MAX_STRING_LEN];
	zbx_uint64_t	value = 0;
	FILE		*f;

	ZBX_UNUSED(request);

	if (NULL == (f = fopen("/proc/stat", "r")))
	{
		SET_MSG_RESULT(result, zbx_dsprintf(NULL, "Cannot open /proc/stat: %s", zbx_strerror(errno)));
		return SYSINFO_RET_FAIL;
	}

	while (NULL != fgets(line, sizeof(line), f))
	{
		if (0 != strncmp(line, "intr", 4))
			continue;

		if (1 != sscanf(line, "%*s " ZBX_FS_UI64, &value))
			continue;

		SET_UI64_RESULT(result, value);
		ret = SYSINFO_RET_OK;
		break;
	}
	zbx_fclose(f);

	if (SYSINFO_RET_FAIL == ret)
		SET_MSG_RESULT(result, zbx_strdup(NULL, "Cannot find a line with \"intr\" in /proc/stat."));

	return ret;
}
