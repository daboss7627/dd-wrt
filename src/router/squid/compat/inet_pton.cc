/*
 * Copyright (C) 1996-2022 The Squid Software Foundation and contributors
 *
 * Squid software is distributed under GPLv2+ license and includes
 * contributions from numerous individuals and organizations.
 * Please see the COPYING and CONTRIBUTORS files for details.
 */

/*
 *  Shamelessly duplicated from the bind9 public sources
 *  for use by the Squid Project under ISC written permission
 *  included "as found" below.
 *
 * Update/Maintenance History:
 *
 *    24-Sep-2007 : Copied from bind 9.3.3
 *                      - Added protection around libray headers
 *                      - Altered configure checks to import
 *
 *    06-Oct-2007 : Various fixes to allow the build on MinGW
 *
 *    28-Oct-2007: drop some dead code. now tested working without.
 *
 *    13-Jan-2015 : Various fixed for C++ and MinGW native build
 *
 *  Original License and code follows.
 */

#include "squid.h"

#if !HAVE_DECL_INET_PTON

/*
 * Copyright (c) 2004 by Internet Systems Consortium, Inc. ("ISC")
 * Copyright (c) 1996,1999 by Internet Software Consortium.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static const char rcsid[] = "inet_pton.c,v 1.2.206.2 2005/07/28 07:43:18 marka Exp";
#endif /* LIBC_SCCS and not lint */

#if HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif
#if HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#if HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#if HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#if ARPA_INET_H
#include <arpa/inet.h>
#endif
#if HAVE_ARPA_NAMESER_H
#include <arpa/nameser.h>
#endif
#if HAVE_STRING_H
#include <string.h>
#endif
#if HAVE_ERRNO_H
#include <errno.h>
#endif

#if ! defined(NS_INADDRSZ)
#define NS_INADDRSZ      4
#endif
#if ! defined(NS_IN6ADDRSZ)
#define NS_IN6ADDRSZ    16
#endif
#if ! defined(NS_INT16SZ)
#define NS_INT16SZ      2
#endif

/*
 * WARNING: Don't even consider trying to compile this on a system where
 * sizeof(int) < 4.  sizeof(int) > 4 is fine; all the world's not a VAX.
 */

static int  inet_pton4 (const char *src, u_char *dst);
static int  inet_pton6 (const char *src, u_char *dst);

/* int
 * inet_pton(af, src, dst)
 *  convert from presentation format (which usually means ASCII printable)
 *  to network format (which is usually some kind of binary format).
 * return:
 *  1 if the address was valid for the specified address family
 *  0 if the address wasn't valid (`dst' is untouched in this case)
 *  -1 if some other error occurred (`dst' is untouched in this case, too)
 * author:
 *  Paul Vixie, 1996.
 */
int
xinet_pton(int af, const char *src, void *dst)
{
    switch (af) {
    case AF_INET:
        return (inet_pton4(src, (u_char*)dst));
    case AF_INET6:
        return (inet_pton6(src, (u_char*)dst));
    default:
        errno = EAFNOSUPPORT;
        return (-1);
    }
    /* NOTREACHED */
}

/* int
 * inet_pton4(src, dst)
 *  like inet_aton() but without all the hexadecimal and shorthand.
 * return:
 *  1 if `src' is a valid dotted quad, else 0.
 * notice:
 *  does not touch `dst' unless it's returning 1.
 * author:
 *  Paul Vixie, 1996.
 */
static int
inet_pton4(const char *src, u_char *dst)
{
    static const char digits[] = "0123456789";
    int saw_digit, octets, ch;
    u_char tmp[NS_INADDRSZ], *tp;

    saw_digit = 0;
    octets = 0;
    *(tp = tmp) = 0;
    while ((ch = *src++) != '\0') {
        const char *pch;

        if ((pch = strchr(digits, ch)) != NULL) {
            u_int nw = *tp * 10 + (pch - digits);

            if (saw_digit && *tp == 0)
                return (0);
            if (nw > 255)
                return (0);
            *tp = nw;
            if (!saw_digit) {
                if (++octets > 4)
                    return (0);
                saw_digit = 1;
            }
        } else if (ch == '.' && saw_digit) {
            if (octets == 4)
                return (0);
            *++tp = 0;
            saw_digit = 0;
        } else
            return (0);
    }
    if (octets < 4)
        return (0);
    memcpy(dst, tmp, NS_INADDRSZ);
    return (1);
}

/* int
 * inet_pton6(src, dst)
 *  convert presentation level address to network order binary form.
 * return:
 *  1 if `src' is a valid [RFC1884 2.2] address, else 0.
 * notice:
 *  (1) does not touch `dst' unless it's returning 1.
 *  (2) :: in a full address is silently ignored.
 * credit:
 *  inspired by Mark Andrews.
 * author:
 *  Paul Vixie, 1996.
 */
static int
inet_pton6(const char *src, u_char *dst)
{
    static const char xdigits_l[] = "0123456789abcdef",
                                    xdigits_u[] = "0123456789ABCDEF";
    u_char tmp[NS_IN6ADDRSZ], *tp, *endp, *colonp;
    const char *xdigits, *curtok;
    int ch, seen_xdigits;
    u_int val;

    memset((tp = tmp), '\0', NS_IN6ADDRSZ);
    endp = tp + NS_IN6ADDRSZ;
    colonp = NULL;
    /* Leading :: requires some special handling. */
    if (*src == ':')
        if (*++src != ':')
            return (0);
    curtok = src;
    seen_xdigits = 0;
    val = 0;
    while ((ch = *src++) != '\0') {
        const char *pch;

        if ((pch = strchr((xdigits = xdigits_l), ch)) == NULL)
            pch = strchr((xdigits = xdigits_u), ch);
        if (pch != NULL) {
            val <<= 4;
            val |= (pch - xdigits);
            if (++seen_xdigits > 4)
                return (0);
            continue;
        }
        if (ch == ':') {
            curtok = src;
            if (!seen_xdigits) {
                if (colonp)
                    return (0);
                colonp = tp;
                continue;
            } else if (*src == '\0') {
                return (0);
            }
            if (tp + NS_INT16SZ > endp)
                return (0);
            *tp++ = (u_char) (val >> 8) & 0xff;
            *tp++ = (u_char) val & 0xff;
            seen_xdigits = 0;
            val = 0;
            continue;
        }
        if (ch == '.' && ((tp + NS_INADDRSZ) <= endp) &&
                inet_pton4(curtok, tp) > 0) {
            tp += NS_INADDRSZ;
            seen_xdigits = 0;
            break;  /* '\0' was seen by inet_pton4(). */
        }
        return (0);
    }
    if (seen_xdigits) {
        if (tp + NS_INT16SZ > endp)
            return (0);
        *tp++ = (u_char) (val >> 8) & 0xff;
        *tp++ = (u_char) val & 0xff;
    }
    if (colonp != NULL) {
        /*
         * Since some memmove()'s erroneously fail to handle
         * overlapping regions, we'll do the shift by hand.
         */
        const int n = tp - colonp;
        int i;

        if (tp == endp)
            return (0);
        for (i = 1; i <= n; i++) {
            endp[- i] = colonp[n - i];
            colonp[n - i] = 0;
        }
        tp = endp;
    }
    if (tp != endp)
        return (0);
    memcpy(dst, tmp, NS_IN6ADDRSZ);
    return (1);
}

#endif /* HAVE_DECL_INET_PTON */

