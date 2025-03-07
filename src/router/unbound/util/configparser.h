/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_UTIL_CONFIGPARSER_H_INCLUDED
# define YY_YY_UTIL_CONFIGPARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SPACE = 258,                   /* SPACE  */
    LETTER = 259,                  /* LETTER  */
    NEWLINE = 260,                 /* NEWLINE  */
    COMMENT = 261,                 /* COMMENT  */
    COLON = 262,                   /* COLON  */
    ANY = 263,                     /* ANY  */
    ZONESTR = 264,                 /* ZONESTR  */
    STRING_ARG = 265,              /* STRING_ARG  */
    VAR_FORCE_TOPLEVEL = 266,      /* VAR_FORCE_TOPLEVEL  */
    VAR_SERVER = 267,              /* VAR_SERVER  */
    VAR_VERBOSITY = 268,           /* VAR_VERBOSITY  */
    VAR_NUM_THREADS = 269,         /* VAR_NUM_THREADS  */
    VAR_PORT = 270,                /* VAR_PORT  */
    VAR_OUTGOING_RANGE = 271,      /* VAR_OUTGOING_RANGE  */
    VAR_INTERFACE = 272,           /* VAR_INTERFACE  */
    VAR_PREFER_IP4 = 273,          /* VAR_PREFER_IP4  */
    VAR_DO_IP4 = 274,              /* VAR_DO_IP4  */
    VAR_DO_IP6 = 275,              /* VAR_DO_IP6  */
    VAR_PREFER_IP6 = 276,          /* VAR_PREFER_IP6  */
    VAR_DO_UDP = 277,              /* VAR_DO_UDP  */
    VAR_DO_TCP = 278,              /* VAR_DO_TCP  */
    VAR_TCP_MSS = 279,             /* VAR_TCP_MSS  */
    VAR_OUTGOING_TCP_MSS = 280,    /* VAR_OUTGOING_TCP_MSS  */
    VAR_TCP_IDLE_TIMEOUT = 281,    /* VAR_TCP_IDLE_TIMEOUT  */
    VAR_EDNS_TCP_KEEPALIVE = 282,  /* VAR_EDNS_TCP_KEEPALIVE  */
    VAR_EDNS_TCP_KEEPALIVE_TIMEOUT = 283, /* VAR_EDNS_TCP_KEEPALIVE_TIMEOUT  */
    VAR_CHROOT = 284,              /* VAR_CHROOT  */
    VAR_USERNAME = 285,            /* VAR_USERNAME  */
    VAR_DIRECTORY = 286,           /* VAR_DIRECTORY  */
    VAR_LOGFILE = 287,             /* VAR_LOGFILE  */
    VAR_PIDFILE = 288,             /* VAR_PIDFILE  */
    VAR_MSG_CACHE_SIZE = 289,      /* VAR_MSG_CACHE_SIZE  */
    VAR_MSG_CACHE_SLABS = 290,     /* VAR_MSG_CACHE_SLABS  */
    VAR_NUM_QUERIES_PER_THREAD = 291, /* VAR_NUM_QUERIES_PER_THREAD  */
    VAR_RRSET_CACHE_SIZE = 292,    /* VAR_RRSET_CACHE_SIZE  */
    VAR_RRSET_CACHE_SLABS = 293,   /* VAR_RRSET_CACHE_SLABS  */
    VAR_OUTGOING_NUM_TCP = 294,    /* VAR_OUTGOING_NUM_TCP  */
    VAR_INFRA_HOST_TTL = 295,      /* VAR_INFRA_HOST_TTL  */
    VAR_INFRA_LAME_TTL = 296,      /* VAR_INFRA_LAME_TTL  */
    VAR_INFRA_CACHE_SLABS = 297,   /* VAR_INFRA_CACHE_SLABS  */
    VAR_INFRA_CACHE_NUMHOSTS = 298, /* VAR_INFRA_CACHE_NUMHOSTS  */
    VAR_INFRA_CACHE_LAME_SIZE = 299, /* VAR_INFRA_CACHE_LAME_SIZE  */
    VAR_NAME = 300,                /* VAR_NAME  */
    VAR_STUB_ZONE = 301,           /* VAR_STUB_ZONE  */
    VAR_STUB_HOST = 302,           /* VAR_STUB_HOST  */
    VAR_STUB_ADDR = 303,           /* VAR_STUB_ADDR  */
    VAR_TARGET_FETCH_POLICY = 304, /* VAR_TARGET_FETCH_POLICY  */
    VAR_HARDEN_SHORT_BUFSIZE = 305, /* VAR_HARDEN_SHORT_BUFSIZE  */
    VAR_HARDEN_LARGE_QUERIES = 306, /* VAR_HARDEN_LARGE_QUERIES  */
    VAR_FORWARD_ZONE = 307,        /* VAR_FORWARD_ZONE  */
    VAR_FORWARD_HOST = 308,        /* VAR_FORWARD_HOST  */
    VAR_FORWARD_ADDR = 309,        /* VAR_FORWARD_ADDR  */
    VAR_DO_NOT_QUERY_ADDRESS = 310, /* VAR_DO_NOT_QUERY_ADDRESS  */
    VAR_HIDE_IDENTITY = 311,       /* VAR_HIDE_IDENTITY  */
    VAR_HIDE_VERSION = 312,        /* VAR_HIDE_VERSION  */
    VAR_IDENTITY = 313,            /* VAR_IDENTITY  */
    VAR_VERSION = 314,             /* VAR_VERSION  */
    VAR_HARDEN_GLUE = 315,         /* VAR_HARDEN_GLUE  */
    VAR_MODULE_CONF = 316,         /* VAR_MODULE_CONF  */
    VAR_TRUST_ANCHOR_FILE = 317,   /* VAR_TRUST_ANCHOR_FILE  */
    VAR_TRUST_ANCHOR = 318,        /* VAR_TRUST_ANCHOR  */
    VAR_VAL_OVERRIDE_DATE = 319,   /* VAR_VAL_OVERRIDE_DATE  */
    VAR_BOGUS_TTL = 320,           /* VAR_BOGUS_TTL  */
    VAR_VAL_CLEAN_ADDITIONAL = 321, /* VAR_VAL_CLEAN_ADDITIONAL  */
    VAR_VAL_PERMISSIVE_MODE = 322, /* VAR_VAL_PERMISSIVE_MODE  */
    VAR_INCOMING_NUM_TCP = 323,    /* VAR_INCOMING_NUM_TCP  */
    VAR_MSG_BUFFER_SIZE = 324,     /* VAR_MSG_BUFFER_SIZE  */
    VAR_KEY_CACHE_SIZE = 325,      /* VAR_KEY_CACHE_SIZE  */
    VAR_KEY_CACHE_SLABS = 326,     /* VAR_KEY_CACHE_SLABS  */
    VAR_TRUSTED_KEYS_FILE = 327,   /* VAR_TRUSTED_KEYS_FILE  */
    VAR_VAL_NSEC3_KEYSIZE_ITERATIONS = 328, /* VAR_VAL_NSEC3_KEYSIZE_ITERATIONS  */
    VAR_USE_SYSLOG = 329,          /* VAR_USE_SYSLOG  */
    VAR_OUTGOING_INTERFACE = 330,  /* VAR_OUTGOING_INTERFACE  */
    VAR_ROOT_HINTS = 331,          /* VAR_ROOT_HINTS  */
    VAR_DO_NOT_QUERY_LOCALHOST = 332, /* VAR_DO_NOT_QUERY_LOCALHOST  */
    VAR_CACHE_MAX_TTL = 333,       /* VAR_CACHE_MAX_TTL  */
    VAR_HARDEN_DNSSEC_STRIPPED = 334, /* VAR_HARDEN_DNSSEC_STRIPPED  */
    VAR_ACCESS_CONTROL = 335,      /* VAR_ACCESS_CONTROL  */
    VAR_LOCAL_ZONE = 336,          /* VAR_LOCAL_ZONE  */
    VAR_LOCAL_DATA = 337,          /* VAR_LOCAL_DATA  */
    VAR_INTERFACE_AUTOMATIC = 338, /* VAR_INTERFACE_AUTOMATIC  */
    VAR_STATISTICS_INTERVAL = 339, /* VAR_STATISTICS_INTERVAL  */
    VAR_DO_DAEMONIZE = 340,        /* VAR_DO_DAEMONIZE  */
    VAR_USE_CAPS_FOR_ID = 341,     /* VAR_USE_CAPS_FOR_ID  */
    VAR_STATISTICS_CUMULATIVE = 342, /* VAR_STATISTICS_CUMULATIVE  */
    VAR_OUTGOING_PORT_PERMIT = 343, /* VAR_OUTGOING_PORT_PERMIT  */
    VAR_OUTGOING_PORT_AVOID = 344, /* VAR_OUTGOING_PORT_AVOID  */
    VAR_DLV_ANCHOR_FILE = 345,     /* VAR_DLV_ANCHOR_FILE  */
    VAR_DLV_ANCHOR = 346,          /* VAR_DLV_ANCHOR  */
    VAR_NEG_CACHE_SIZE = 347,      /* VAR_NEG_CACHE_SIZE  */
    VAR_HARDEN_REFERRAL_PATH = 348, /* VAR_HARDEN_REFERRAL_PATH  */
    VAR_PRIVATE_ADDRESS = 349,     /* VAR_PRIVATE_ADDRESS  */
    VAR_PRIVATE_DOMAIN = 350,      /* VAR_PRIVATE_DOMAIN  */
    VAR_REMOTE_CONTROL = 351,      /* VAR_REMOTE_CONTROL  */
    VAR_CONTROL_ENABLE = 352,      /* VAR_CONTROL_ENABLE  */
    VAR_CONTROL_INTERFACE = 353,   /* VAR_CONTROL_INTERFACE  */
    VAR_CONTROL_PORT = 354,        /* VAR_CONTROL_PORT  */
    VAR_SERVER_KEY_FILE = 355,     /* VAR_SERVER_KEY_FILE  */
    VAR_SERVER_CERT_FILE = 356,    /* VAR_SERVER_CERT_FILE  */
    VAR_CONTROL_KEY_FILE = 357,    /* VAR_CONTROL_KEY_FILE  */
    VAR_CONTROL_CERT_FILE = 358,   /* VAR_CONTROL_CERT_FILE  */
    VAR_CONTROL_USE_CERT = 359,    /* VAR_CONTROL_USE_CERT  */
    VAR_TCP_REUSE_TIMEOUT = 360,   /* VAR_TCP_REUSE_TIMEOUT  */
    VAR_MAX_REUSE_TCP_QUERIES = 361, /* VAR_MAX_REUSE_TCP_QUERIES  */
    VAR_EXTENDED_STATISTICS = 362, /* VAR_EXTENDED_STATISTICS  */
    VAR_LOCAL_DATA_PTR = 363,      /* VAR_LOCAL_DATA_PTR  */
    VAR_JOSTLE_TIMEOUT = 364,      /* VAR_JOSTLE_TIMEOUT  */
    VAR_STUB_PRIME = 365,          /* VAR_STUB_PRIME  */
    VAR_UNWANTED_REPLY_THRESHOLD = 366, /* VAR_UNWANTED_REPLY_THRESHOLD  */
    VAR_LOG_TIME_ASCII = 367,      /* VAR_LOG_TIME_ASCII  */
    VAR_DOMAIN_INSECURE = 368,     /* VAR_DOMAIN_INSECURE  */
    VAR_PYTHON = 369,              /* VAR_PYTHON  */
    VAR_PYTHON_SCRIPT = 370,       /* VAR_PYTHON_SCRIPT  */
    VAR_VAL_SIG_SKEW_MIN = 371,    /* VAR_VAL_SIG_SKEW_MIN  */
    VAR_VAL_SIG_SKEW_MAX = 372,    /* VAR_VAL_SIG_SKEW_MAX  */
    VAR_VAL_MAX_RESTART = 373,     /* VAR_VAL_MAX_RESTART  */
    VAR_CACHE_MIN_TTL = 374,       /* VAR_CACHE_MIN_TTL  */
    VAR_VAL_LOG_LEVEL = 375,       /* VAR_VAL_LOG_LEVEL  */
    VAR_AUTO_TRUST_ANCHOR_FILE = 376, /* VAR_AUTO_TRUST_ANCHOR_FILE  */
    VAR_KEEP_MISSING = 377,        /* VAR_KEEP_MISSING  */
    VAR_ADD_HOLDDOWN = 378,        /* VAR_ADD_HOLDDOWN  */
    VAR_DEL_HOLDDOWN = 379,        /* VAR_DEL_HOLDDOWN  */
    VAR_SO_RCVBUF = 380,           /* VAR_SO_RCVBUF  */
    VAR_EDNS_BUFFER_SIZE = 381,    /* VAR_EDNS_BUFFER_SIZE  */
    VAR_PREFETCH = 382,            /* VAR_PREFETCH  */
    VAR_PREFETCH_KEY = 383,        /* VAR_PREFETCH_KEY  */
    VAR_SO_SNDBUF = 384,           /* VAR_SO_SNDBUF  */
    VAR_SO_REUSEPORT = 385,        /* VAR_SO_REUSEPORT  */
    VAR_HARDEN_BELOW_NXDOMAIN = 386, /* VAR_HARDEN_BELOW_NXDOMAIN  */
    VAR_IGNORE_CD_FLAG = 387,      /* VAR_IGNORE_CD_FLAG  */
    VAR_LOG_QUERIES = 388,         /* VAR_LOG_QUERIES  */
    VAR_LOG_REPLIES = 389,         /* VAR_LOG_REPLIES  */
    VAR_LOG_LOCAL_ACTIONS = 390,   /* VAR_LOG_LOCAL_ACTIONS  */
    VAR_TCP_UPSTREAM = 391,        /* VAR_TCP_UPSTREAM  */
    VAR_SSL_UPSTREAM = 392,        /* VAR_SSL_UPSTREAM  */
    VAR_TCP_AUTH_QUERY_TIMEOUT = 393, /* VAR_TCP_AUTH_QUERY_TIMEOUT  */
    VAR_SSL_SERVICE_KEY = 394,     /* VAR_SSL_SERVICE_KEY  */
    VAR_SSL_SERVICE_PEM = 395,     /* VAR_SSL_SERVICE_PEM  */
    VAR_SSL_PORT = 396,            /* VAR_SSL_PORT  */
    VAR_FORWARD_FIRST = 397,       /* VAR_FORWARD_FIRST  */
    VAR_STUB_SSL_UPSTREAM = 398,   /* VAR_STUB_SSL_UPSTREAM  */
    VAR_FORWARD_SSL_UPSTREAM = 399, /* VAR_FORWARD_SSL_UPSTREAM  */
    VAR_TLS_CERT_BUNDLE = 400,     /* VAR_TLS_CERT_BUNDLE  */
    VAR_STUB_TCP_UPSTREAM = 401,   /* VAR_STUB_TCP_UPSTREAM  */
    VAR_FORWARD_TCP_UPSTREAM = 402, /* VAR_FORWARD_TCP_UPSTREAM  */
    VAR_HTTPS_PORT = 403,          /* VAR_HTTPS_PORT  */
    VAR_HTTP_ENDPOINT = 404,       /* VAR_HTTP_ENDPOINT  */
    VAR_HTTP_MAX_STREAMS = 405,    /* VAR_HTTP_MAX_STREAMS  */
    VAR_HTTP_QUERY_BUFFER_SIZE = 406, /* VAR_HTTP_QUERY_BUFFER_SIZE  */
    VAR_HTTP_RESPONSE_BUFFER_SIZE = 407, /* VAR_HTTP_RESPONSE_BUFFER_SIZE  */
    VAR_HTTP_NODELAY = 408,        /* VAR_HTTP_NODELAY  */
    VAR_HTTP_NOTLS_DOWNSTREAM = 409, /* VAR_HTTP_NOTLS_DOWNSTREAM  */
    VAR_STUB_FIRST = 410,          /* VAR_STUB_FIRST  */
    VAR_MINIMAL_RESPONSES = 411,   /* VAR_MINIMAL_RESPONSES  */
    VAR_RRSET_ROUNDROBIN = 412,    /* VAR_RRSET_ROUNDROBIN  */
    VAR_MAX_UDP_SIZE = 413,        /* VAR_MAX_UDP_SIZE  */
    VAR_DELAY_CLOSE = 414,         /* VAR_DELAY_CLOSE  */
    VAR_UDP_CONNECT = 415,         /* VAR_UDP_CONNECT  */
    VAR_UNBLOCK_LAN_ZONES = 416,   /* VAR_UNBLOCK_LAN_ZONES  */
    VAR_INSECURE_LAN_ZONES = 417,  /* VAR_INSECURE_LAN_ZONES  */
    VAR_INFRA_CACHE_MIN_RTT = 418, /* VAR_INFRA_CACHE_MIN_RTT  */
    VAR_INFRA_CACHE_MAX_RTT = 419, /* VAR_INFRA_CACHE_MAX_RTT  */
    VAR_INFRA_KEEP_PROBING = 420,  /* VAR_INFRA_KEEP_PROBING  */
    VAR_DNS64_PREFIX = 421,        /* VAR_DNS64_PREFIX  */
    VAR_DNS64_SYNTHALL = 422,      /* VAR_DNS64_SYNTHALL  */
    VAR_DNS64_IGNORE_AAAA = 423,   /* VAR_DNS64_IGNORE_AAAA  */
    VAR_DNSTAP = 424,              /* VAR_DNSTAP  */
    VAR_DNSTAP_ENABLE = 425,       /* VAR_DNSTAP_ENABLE  */
    VAR_DNSTAP_SOCKET_PATH = 426,  /* VAR_DNSTAP_SOCKET_PATH  */
    VAR_DNSTAP_IP = 427,           /* VAR_DNSTAP_IP  */
    VAR_DNSTAP_TLS = 428,          /* VAR_DNSTAP_TLS  */
    VAR_DNSTAP_TLS_SERVER_NAME = 429, /* VAR_DNSTAP_TLS_SERVER_NAME  */
    VAR_DNSTAP_TLS_CERT_BUNDLE = 430, /* VAR_DNSTAP_TLS_CERT_BUNDLE  */
    VAR_DNSTAP_TLS_CLIENT_KEY_FILE = 431, /* VAR_DNSTAP_TLS_CLIENT_KEY_FILE  */
    VAR_DNSTAP_TLS_CLIENT_CERT_FILE = 432, /* VAR_DNSTAP_TLS_CLIENT_CERT_FILE  */
    VAR_DNSTAP_SEND_IDENTITY = 433, /* VAR_DNSTAP_SEND_IDENTITY  */
    VAR_DNSTAP_SEND_VERSION = 434, /* VAR_DNSTAP_SEND_VERSION  */
    VAR_DNSTAP_BIDIRECTIONAL = 435, /* VAR_DNSTAP_BIDIRECTIONAL  */
    VAR_DNSTAP_IDENTITY = 436,     /* VAR_DNSTAP_IDENTITY  */
    VAR_DNSTAP_VERSION = 437,      /* VAR_DNSTAP_VERSION  */
    VAR_DNSTAP_LOG_RESOLVER_QUERY_MESSAGES = 438, /* VAR_DNSTAP_LOG_RESOLVER_QUERY_MESSAGES  */
    VAR_DNSTAP_LOG_RESOLVER_RESPONSE_MESSAGES = 439, /* VAR_DNSTAP_LOG_RESOLVER_RESPONSE_MESSAGES  */
    VAR_DNSTAP_LOG_CLIENT_QUERY_MESSAGES = 440, /* VAR_DNSTAP_LOG_CLIENT_QUERY_MESSAGES  */
    VAR_DNSTAP_LOG_CLIENT_RESPONSE_MESSAGES = 441, /* VAR_DNSTAP_LOG_CLIENT_RESPONSE_MESSAGES  */
    VAR_DNSTAP_LOG_FORWARDER_QUERY_MESSAGES = 442, /* VAR_DNSTAP_LOG_FORWARDER_QUERY_MESSAGES  */
    VAR_DNSTAP_LOG_FORWARDER_RESPONSE_MESSAGES = 443, /* VAR_DNSTAP_LOG_FORWARDER_RESPONSE_MESSAGES  */
    VAR_RESPONSE_IP_TAG = 444,     /* VAR_RESPONSE_IP_TAG  */
    VAR_RESPONSE_IP = 445,         /* VAR_RESPONSE_IP  */
    VAR_RESPONSE_IP_DATA = 446,    /* VAR_RESPONSE_IP_DATA  */
    VAR_HARDEN_ALGO_DOWNGRADE = 447, /* VAR_HARDEN_ALGO_DOWNGRADE  */
    VAR_IP_TRANSPARENT = 448,      /* VAR_IP_TRANSPARENT  */
    VAR_IP_DSCP = 449,             /* VAR_IP_DSCP  */
    VAR_DISABLE_DNSSEC_LAME_CHECK = 450, /* VAR_DISABLE_DNSSEC_LAME_CHECK  */
    VAR_IP_RATELIMIT = 451,        /* VAR_IP_RATELIMIT  */
    VAR_IP_RATELIMIT_SLABS = 452,  /* VAR_IP_RATELIMIT_SLABS  */
    VAR_IP_RATELIMIT_SIZE = 453,   /* VAR_IP_RATELIMIT_SIZE  */
    VAR_RATELIMIT = 454,           /* VAR_RATELIMIT  */
    VAR_RATELIMIT_SLABS = 455,     /* VAR_RATELIMIT_SLABS  */
    VAR_RATELIMIT_SIZE = 456,      /* VAR_RATELIMIT_SIZE  */
    VAR_OUTBOUND_MSG_RETRY = 457,  /* VAR_OUTBOUND_MSG_RETRY  */
    VAR_RATELIMIT_FOR_DOMAIN = 458, /* VAR_RATELIMIT_FOR_DOMAIN  */
    VAR_RATELIMIT_BELOW_DOMAIN = 459, /* VAR_RATELIMIT_BELOW_DOMAIN  */
    VAR_IP_RATELIMIT_FACTOR = 460, /* VAR_IP_RATELIMIT_FACTOR  */
    VAR_RATELIMIT_FACTOR = 461,    /* VAR_RATELIMIT_FACTOR  */
    VAR_IP_RATELIMIT_BACKOFF = 462, /* VAR_IP_RATELIMIT_BACKOFF  */
    VAR_RATELIMIT_BACKOFF = 463,   /* VAR_RATELIMIT_BACKOFF  */
    VAR_SEND_CLIENT_SUBNET = 464,  /* VAR_SEND_CLIENT_SUBNET  */
    VAR_CLIENT_SUBNET_ZONE = 465,  /* VAR_CLIENT_SUBNET_ZONE  */
    VAR_CLIENT_SUBNET_ALWAYS_FORWARD = 466, /* VAR_CLIENT_SUBNET_ALWAYS_FORWARD  */
    VAR_CLIENT_SUBNET_OPCODE = 467, /* VAR_CLIENT_SUBNET_OPCODE  */
    VAR_MAX_CLIENT_SUBNET_IPV4 = 468, /* VAR_MAX_CLIENT_SUBNET_IPV4  */
    VAR_MAX_CLIENT_SUBNET_IPV6 = 469, /* VAR_MAX_CLIENT_SUBNET_IPV6  */
    VAR_MIN_CLIENT_SUBNET_IPV4 = 470, /* VAR_MIN_CLIENT_SUBNET_IPV4  */
    VAR_MIN_CLIENT_SUBNET_IPV6 = 471, /* VAR_MIN_CLIENT_SUBNET_IPV6  */
    VAR_MAX_ECS_TREE_SIZE_IPV4 = 472, /* VAR_MAX_ECS_TREE_SIZE_IPV4  */
    VAR_MAX_ECS_TREE_SIZE_IPV6 = 473, /* VAR_MAX_ECS_TREE_SIZE_IPV6  */
    VAR_CAPS_WHITELIST = 474,      /* VAR_CAPS_WHITELIST  */
    VAR_CACHE_MAX_NEGATIVE_TTL = 475, /* VAR_CACHE_MAX_NEGATIVE_TTL  */
    VAR_PERMIT_SMALL_HOLDDOWN = 476, /* VAR_PERMIT_SMALL_HOLDDOWN  */
    VAR_QNAME_MINIMISATION = 477,  /* VAR_QNAME_MINIMISATION  */
    VAR_QNAME_MINIMISATION_STRICT = 478, /* VAR_QNAME_MINIMISATION_STRICT  */
    VAR_IP_FREEBIND = 479,         /* VAR_IP_FREEBIND  */
    VAR_DEFINE_TAG = 480,          /* VAR_DEFINE_TAG  */
    VAR_LOCAL_ZONE_TAG = 481,      /* VAR_LOCAL_ZONE_TAG  */
    VAR_ACCESS_CONTROL_TAG = 482,  /* VAR_ACCESS_CONTROL_TAG  */
    VAR_LOCAL_ZONE_OVERRIDE = 483, /* VAR_LOCAL_ZONE_OVERRIDE  */
    VAR_ACCESS_CONTROL_TAG_ACTION = 484, /* VAR_ACCESS_CONTROL_TAG_ACTION  */
    VAR_ACCESS_CONTROL_TAG_DATA = 485, /* VAR_ACCESS_CONTROL_TAG_DATA  */
    VAR_VIEW = 486,                /* VAR_VIEW  */
    VAR_ACCESS_CONTROL_VIEW = 487, /* VAR_ACCESS_CONTROL_VIEW  */
    VAR_VIEW_FIRST = 488,          /* VAR_VIEW_FIRST  */
    VAR_SERVE_EXPIRED = 489,       /* VAR_SERVE_EXPIRED  */
    VAR_SERVE_EXPIRED_TTL = 490,   /* VAR_SERVE_EXPIRED_TTL  */
    VAR_SERVE_EXPIRED_TTL_RESET = 491, /* VAR_SERVE_EXPIRED_TTL_RESET  */
    VAR_SERVE_EXPIRED_REPLY_TTL = 492, /* VAR_SERVE_EXPIRED_REPLY_TTL  */
    VAR_SERVE_EXPIRED_CLIENT_TIMEOUT = 493, /* VAR_SERVE_EXPIRED_CLIENT_TIMEOUT  */
    VAR_EDE_SERVE_EXPIRED = 494,   /* VAR_EDE_SERVE_EXPIRED  */
    VAR_SERVE_ORIGINAL_TTL = 495,  /* VAR_SERVE_ORIGINAL_TTL  */
    VAR_FAKE_DSA = 496,            /* VAR_FAKE_DSA  */
    VAR_FAKE_SHA1 = 497,           /* VAR_FAKE_SHA1  */
    VAR_LOG_IDENTITY = 498,        /* VAR_LOG_IDENTITY  */
    VAR_HIDE_TRUSTANCHOR = 499,    /* VAR_HIDE_TRUSTANCHOR  */
    VAR_HIDE_HTTP_USER_AGENT = 500, /* VAR_HIDE_HTTP_USER_AGENT  */
    VAR_HTTP_USER_AGENT = 501,     /* VAR_HTTP_USER_AGENT  */
    VAR_TRUST_ANCHOR_SIGNALING = 502, /* VAR_TRUST_ANCHOR_SIGNALING  */
    VAR_AGGRESSIVE_NSEC = 503,     /* VAR_AGGRESSIVE_NSEC  */
    VAR_USE_SYSTEMD = 504,         /* VAR_USE_SYSTEMD  */
    VAR_SHM_ENABLE = 505,          /* VAR_SHM_ENABLE  */
    VAR_SHM_KEY = 506,             /* VAR_SHM_KEY  */
    VAR_ROOT_KEY_SENTINEL = 507,   /* VAR_ROOT_KEY_SENTINEL  */
    VAR_DNSCRYPT = 508,            /* VAR_DNSCRYPT  */
    VAR_DNSCRYPT_ENABLE = 509,     /* VAR_DNSCRYPT_ENABLE  */
    VAR_DNSCRYPT_PORT = 510,       /* VAR_DNSCRYPT_PORT  */
    VAR_DNSCRYPT_PROVIDER = 511,   /* VAR_DNSCRYPT_PROVIDER  */
    VAR_DNSCRYPT_SECRET_KEY = 512, /* VAR_DNSCRYPT_SECRET_KEY  */
    VAR_DNSCRYPT_PROVIDER_CERT = 513, /* VAR_DNSCRYPT_PROVIDER_CERT  */
    VAR_DNSCRYPT_PROVIDER_CERT_ROTATED = 514, /* VAR_DNSCRYPT_PROVIDER_CERT_ROTATED  */
    VAR_DNSCRYPT_SHARED_SECRET_CACHE_SIZE = 515, /* VAR_DNSCRYPT_SHARED_SECRET_CACHE_SIZE  */
    VAR_DNSCRYPT_SHARED_SECRET_CACHE_SLABS = 516, /* VAR_DNSCRYPT_SHARED_SECRET_CACHE_SLABS  */
    VAR_DNSCRYPT_NONCE_CACHE_SIZE = 517, /* VAR_DNSCRYPT_NONCE_CACHE_SIZE  */
    VAR_DNSCRYPT_NONCE_CACHE_SLABS = 518, /* VAR_DNSCRYPT_NONCE_CACHE_SLABS  */
    VAR_PAD_RESPONSES = 519,       /* VAR_PAD_RESPONSES  */
    VAR_PAD_RESPONSES_BLOCK_SIZE = 520, /* VAR_PAD_RESPONSES_BLOCK_SIZE  */
    VAR_PAD_QUERIES = 521,         /* VAR_PAD_QUERIES  */
    VAR_PAD_QUERIES_BLOCK_SIZE = 522, /* VAR_PAD_QUERIES_BLOCK_SIZE  */
    VAR_IPSECMOD_ENABLED = 523,    /* VAR_IPSECMOD_ENABLED  */
    VAR_IPSECMOD_HOOK = 524,       /* VAR_IPSECMOD_HOOK  */
    VAR_IPSECMOD_IGNORE_BOGUS = 525, /* VAR_IPSECMOD_IGNORE_BOGUS  */
    VAR_IPSECMOD_MAX_TTL = 526,    /* VAR_IPSECMOD_MAX_TTL  */
    VAR_IPSECMOD_WHITELIST = 527,  /* VAR_IPSECMOD_WHITELIST  */
    VAR_IPSECMOD_STRICT = 528,     /* VAR_IPSECMOD_STRICT  */
    VAR_CACHEDB = 529,             /* VAR_CACHEDB  */
    VAR_CACHEDB_BACKEND = 530,     /* VAR_CACHEDB_BACKEND  */
    VAR_CACHEDB_SECRETSEED = 531,  /* VAR_CACHEDB_SECRETSEED  */
    VAR_CACHEDB_REDISHOST = 532,   /* VAR_CACHEDB_REDISHOST  */
    VAR_CACHEDB_REDISPORT = 533,   /* VAR_CACHEDB_REDISPORT  */
    VAR_CACHEDB_REDISTIMEOUT = 534, /* VAR_CACHEDB_REDISTIMEOUT  */
    VAR_CACHEDB_REDISEXPIRERECORDS = 535, /* VAR_CACHEDB_REDISEXPIRERECORDS  */
    VAR_UDP_UPSTREAM_WITHOUT_DOWNSTREAM = 536, /* VAR_UDP_UPSTREAM_WITHOUT_DOWNSTREAM  */
    VAR_FOR_UPSTREAM = 537,        /* VAR_FOR_UPSTREAM  */
    VAR_AUTH_ZONE = 538,           /* VAR_AUTH_ZONE  */
    VAR_ZONEFILE = 539,            /* VAR_ZONEFILE  */
    VAR_MASTER = 540,              /* VAR_MASTER  */
    VAR_URL = 541,                 /* VAR_URL  */
    VAR_FOR_DOWNSTREAM = 542,      /* VAR_FOR_DOWNSTREAM  */
    VAR_FALLBACK_ENABLED = 543,    /* VAR_FALLBACK_ENABLED  */
    VAR_TLS_ADDITIONAL_PORT = 544, /* VAR_TLS_ADDITIONAL_PORT  */
    VAR_LOW_RTT = 545,             /* VAR_LOW_RTT  */
    VAR_LOW_RTT_PERMIL = 546,      /* VAR_LOW_RTT_PERMIL  */
    VAR_FAST_SERVER_PERMIL = 547,  /* VAR_FAST_SERVER_PERMIL  */
    VAR_FAST_SERVER_NUM = 548,     /* VAR_FAST_SERVER_NUM  */
    VAR_ALLOW_NOTIFY = 549,        /* VAR_ALLOW_NOTIFY  */
    VAR_TLS_WIN_CERT = 550,        /* VAR_TLS_WIN_CERT  */
    VAR_TCP_CONNECTION_LIMIT = 551, /* VAR_TCP_CONNECTION_LIMIT  */
    VAR_FORWARD_NO_CACHE = 552,    /* VAR_FORWARD_NO_CACHE  */
    VAR_STUB_NO_CACHE = 553,       /* VAR_STUB_NO_CACHE  */
    VAR_LOG_SERVFAIL = 554,        /* VAR_LOG_SERVFAIL  */
    VAR_DENY_ANY = 555,            /* VAR_DENY_ANY  */
    VAR_UNKNOWN_SERVER_TIME_LIMIT = 556, /* VAR_UNKNOWN_SERVER_TIME_LIMIT  */
    VAR_LOG_TAG_QUERYREPLY = 557,  /* VAR_LOG_TAG_QUERYREPLY  */
    VAR_STREAM_WAIT_SIZE = 558,    /* VAR_STREAM_WAIT_SIZE  */
    VAR_TLS_CIPHERS = 559,         /* VAR_TLS_CIPHERS  */
    VAR_TLS_CIPHERSUITES = 560,    /* VAR_TLS_CIPHERSUITES  */
    VAR_TLS_USE_SNI = 561,         /* VAR_TLS_USE_SNI  */
    VAR_IPSET = 562,               /* VAR_IPSET  */
    VAR_IPSET_NAME_V4 = 563,       /* VAR_IPSET_NAME_V4  */
    VAR_IPSET_NAME_V6 = 564,       /* VAR_IPSET_NAME_V6  */
    VAR_TLS_SESSION_TICKET_KEYS = 565, /* VAR_TLS_SESSION_TICKET_KEYS  */
    VAR_RPZ = 566,                 /* VAR_RPZ  */
    VAR_TAGS = 567,                /* VAR_TAGS  */
    VAR_RPZ_ACTION_OVERRIDE = 568, /* VAR_RPZ_ACTION_OVERRIDE  */
    VAR_RPZ_CNAME_OVERRIDE = 569,  /* VAR_RPZ_CNAME_OVERRIDE  */
    VAR_RPZ_LOG = 570,             /* VAR_RPZ_LOG  */
    VAR_RPZ_LOG_NAME = 571,        /* VAR_RPZ_LOG_NAME  */
    VAR_DYNLIB = 572,              /* VAR_DYNLIB  */
    VAR_DYNLIB_FILE = 573,         /* VAR_DYNLIB_FILE  */
    VAR_EDNS_CLIENT_STRING = 574,  /* VAR_EDNS_CLIENT_STRING  */
    VAR_EDNS_CLIENT_STRING_OPCODE = 575, /* VAR_EDNS_CLIENT_STRING_OPCODE  */
    VAR_NSID = 576,                /* VAR_NSID  */
    VAR_ZONEMD_PERMISSIVE_MODE = 577, /* VAR_ZONEMD_PERMISSIVE_MODE  */
    VAR_ZONEMD_CHECK = 578,        /* VAR_ZONEMD_CHECK  */
    VAR_ZONEMD_REJECT_ABSENCE = 579, /* VAR_ZONEMD_REJECT_ABSENCE  */
    VAR_RPZ_SIGNAL_NXDOMAIN_RA = 580, /* VAR_RPZ_SIGNAL_NXDOMAIN_RA  */
    VAR_INTERFACE_AUTOMATIC_PORTS = 581, /* VAR_INTERFACE_AUTOMATIC_PORTS  */
    VAR_EDE = 582,                 /* VAR_EDE  */
    VAR_INTERFACE_ACTION = 583,    /* VAR_INTERFACE_ACTION  */
    VAR_INTERFACE_VIEW = 584,      /* VAR_INTERFACE_VIEW  */
    VAR_INTERFACE_TAG = 585,       /* VAR_INTERFACE_TAG  */
    VAR_INTERFACE_TAG_ACTION = 586, /* VAR_INTERFACE_TAG_ACTION  */
    VAR_INTERFACE_TAG_DATA = 587,  /* VAR_INTERFACE_TAG_DATA  */
    VAR_PROXY_PROTOCOL_PORT = 588  /* VAR_PROXY_PROTOCOL_PORT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define SPACE 258
#define LETTER 259
#define NEWLINE 260
#define COMMENT 261
#define COLON 262
#define ANY 263
#define ZONESTR 264
#define STRING_ARG 265
#define VAR_FORCE_TOPLEVEL 266
#define VAR_SERVER 267
#define VAR_VERBOSITY 268
#define VAR_NUM_THREADS 269
#define VAR_PORT 270
#define VAR_OUTGOING_RANGE 271
#define VAR_INTERFACE 272
#define VAR_PREFER_IP4 273
#define VAR_DO_IP4 274
#define VAR_DO_IP6 275
#define VAR_PREFER_IP6 276
#define VAR_DO_UDP 277
#define VAR_DO_TCP 278
#define VAR_TCP_MSS 279
#define VAR_OUTGOING_TCP_MSS 280
#define VAR_TCP_IDLE_TIMEOUT 281
#define VAR_EDNS_TCP_KEEPALIVE 282
#define VAR_EDNS_TCP_KEEPALIVE_TIMEOUT 283
#define VAR_CHROOT 284
#define VAR_USERNAME 285
#define VAR_DIRECTORY 286
#define VAR_LOGFILE 287
#define VAR_PIDFILE 288
#define VAR_MSG_CACHE_SIZE 289
#define VAR_MSG_CACHE_SLABS 290
#define VAR_NUM_QUERIES_PER_THREAD 291
#define VAR_RRSET_CACHE_SIZE 292
#define VAR_RRSET_CACHE_SLABS 293
#define VAR_OUTGOING_NUM_TCP 294
#define VAR_INFRA_HOST_TTL 295
#define VAR_INFRA_LAME_TTL 296
#define VAR_INFRA_CACHE_SLABS 297
#define VAR_INFRA_CACHE_NUMHOSTS 298
#define VAR_INFRA_CACHE_LAME_SIZE 299
#define VAR_NAME 300
#define VAR_STUB_ZONE 301
#define VAR_STUB_HOST 302
#define VAR_STUB_ADDR 303
#define VAR_TARGET_FETCH_POLICY 304
#define VAR_HARDEN_SHORT_BUFSIZE 305
#define VAR_HARDEN_LARGE_QUERIES 306
#define VAR_FORWARD_ZONE 307
#define VAR_FORWARD_HOST 308
#define VAR_FORWARD_ADDR 309
#define VAR_DO_NOT_QUERY_ADDRESS 310
#define VAR_HIDE_IDENTITY 311
#define VAR_HIDE_VERSION 312
#define VAR_IDENTITY 313
#define VAR_VERSION 314
#define VAR_HARDEN_GLUE 315
#define VAR_MODULE_CONF 316
#define VAR_TRUST_ANCHOR_FILE 317
#define VAR_TRUST_ANCHOR 318
#define VAR_VAL_OVERRIDE_DATE 319
#define VAR_BOGUS_TTL 320
#define VAR_VAL_CLEAN_ADDITIONAL 321
#define VAR_VAL_PERMISSIVE_MODE 322
#define VAR_INCOMING_NUM_TCP 323
#define VAR_MSG_BUFFER_SIZE 324
#define VAR_KEY_CACHE_SIZE 325
#define VAR_KEY_CACHE_SLABS 326
#define VAR_TRUSTED_KEYS_FILE 327
#define VAR_VAL_NSEC3_KEYSIZE_ITERATIONS 328
#define VAR_USE_SYSLOG 329
#define VAR_OUTGOING_INTERFACE 330
#define VAR_ROOT_HINTS 331
#define VAR_DO_NOT_QUERY_LOCALHOST 332
#define VAR_CACHE_MAX_TTL 333
#define VAR_HARDEN_DNSSEC_STRIPPED 334
#define VAR_ACCESS_CONTROL 335
#define VAR_LOCAL_ZONE 336
#define VAR_LOCAL_DATA 337
#define VAR_INTERFACE_AUTOMATIC 338
#define VAR_STATISTICS_INTERVAL 339
#define VAR_DO_DAEMONIZE 340
#define VAR_USE_CAPS_FOR_ID 341
#define VAR_STATISTICS_CUMULATIVE 342
#define VAR_OUTGOING_PORT_PERMIT 343
#define VAR_OUTGOING_PORT_AVOID 344
#define VAR_DLV_ANCHOR_FILE 345
#define VAR_DLV_ANCHOR 346
#define VAR_NEG_CACHE_SIZE 347
#define VAR_HARDEN_REFERRAL_PATH 348
#define VAR_PRIVATE_ADDRESS 349
#define VAR_PRIVATE_DOMAIN 350
#define VAR_REMOTE_CONTROL 351
#define VAR_CONTROL_ENABLE 352
#define VAR_CONTROL_INTERFACE 353
#define VAR_CONTROL_PORT 354
#define VAR_SERVER_KEY_FILE 355
#define VAR_SERVER_CERT_FILE 356
#define VAR_CONTROL_KEY_FILE 357
#define VAR_CONTROL_CERT_FILE 358
#define VAR_CONTROL_USE_CERT 359
#define VAR_TCP_REUSE_TIMEOUT 360
#define VAR_MAX_REUSE_TCP_QUERIES 361
#define VAR_EXTENDED_STATISTICS 362
#define VAR_LOCAL_DATA_PTR 363
#define VAR_JOSTLE_TIMEOUT 364
#define VAR_STUB_PRIME 365
#define VAR_UNWANTED_REPLY_THRESHOLD 366
#define VAR_LOG_TIME_ASCII 367
#define VAR_DOMAIN_INSECURE 368
#define VAR_PYTHON 369
#define VAR_PYTHON_SCRIPT 370
#define VAR_VAL_SIG_SKEW_MIN 371
#define VAR_VAL_SIG_SKEW_MAX 372
#define VAR_VAL_MAX_RESTART 373
#define VAR_CACHE_MIN_TTL 374
#define VAR_VAL_LOG_LEVEL 375
#define VAR_AUTO_TRUST_ANCHOR_FILE 376
#define VAR_KEEP_MISSING 377
#define VAR_ADD_HOLDDOWN 378
#define VAR_DEL_HOLDDOWN 379
#define VAR_SO_RCVBUF 380
#define VAR_EDNS_BUFFER_SIZE 381
#define VAR_PREFETCH 382
#define VAR_PREFETCH_KEY 383
#define VAR_SO_SNDBUF 384
#define VAR_SO_REUSEPORT 385
#define VAR_HARDEN_BELOW_NXDOMAIN 386
#define VAR_IGNORE_CD_FLAG 387
#define VAR_LOG_QUERIES 388
#define VAR_LOG_REPLIES 389
#define VAR_LOG_LOCAL_ACTIONS 390
#define VAR_TCP_UPSTREAM 391
#define VAR_SSL_UPSTREAM 392
#define VAR_TCP_AUTH_QUERY_TIMEOUT 393
#define VAR_SSL_SERVICE_KEY 394
#define VAR_SSL_SERVICE_PEM 395
#define VAR_SSL_PORT 396
#define VAR_FORWARD_FIRST 397
#define VAR_STUB_SSL_UPSTREAM 398
#define VAR_FORWARD_SSL_UPSTREAM 399
#define VAR_TLS_CERT_BUNDLE 400
#define VAR_STUB_TCP_UPSTREAM 401
#define VAR_FORWARD_TCP_UPSTREAM 402
#define VAR_HTTPS_PORT 403
#define VAR_HTTP_ENDPOINT 404
#define VAR_HTTP_MAX_STREAMS 405
#define VAR_HTTP_QUERY_BUFFER_SIZE 406
#define VAR_HTTP_RESPONSE_BUFFER_SIZE 407
#define VAR_HTTP_NODELAY 408
#define VAR_HTTP_NOTLS_DOWNSTREAM 409
#define VAR_STUB_FIRST 410
#define VAR_MINIMAL_RESPONSES 411
#define VAR_RRSET_ROUNDROBIN 412
#define VAR_MAX_UDP_SIZE 413
#define VAR_DELAY_CLOSE 414
#define VAR_UDP_CONNECT 415
#define VAR_UNBLOCK_LAN_ZONES 416
#define VAR_INSECURE_LAN_ZONES 417
#define VAR_INFRA_CACHE_MIN_RTT 418
#define VAR_INFRA_CACHE_MAX_RTT 419
#define VAR_INFRA_KEEP_PROBING 420
#define VAR_DNS64_PREFIX 421
#define VAR_DNS64_SYNTHALL 422
#define VAR_DNS64_IGNORE_AAAA 423
#define VAR_DNSTAP 424
#define VAR_DNSTAP_ENABLE 425
#define VAR_DNSTAP_SOCKET_PATH 426
#define VAR_DNSTAP_IP 427
#define VAR_DNSTAP_TLS 428
#define VAR_DNSTAP_TLS_SERVER_NAME 429
#define VAR_DNSTAP_TLS_CERT_BUNDLE 430
#define VAR_DNSTAP_TLS_CLIENT_KEY_FILE 431
#define VAR_DNSTAP_TLS_CLIENT_CERT_FILE 432
#define VAR_DNSTAP_SEND_IDENTITY 433
#define VAR_DNSTAP_SEND_VERSION 434
#define VAR_DNSTAP_BIDIRECTIONAL 435
#define VAR_DNSTAP_IDENTITY 436
#define VAR_DNSTAP_VERSION 437
#define VAR_DNSTAP_LOG_RESOLVER_QUERY_MESSAGES 438
#define VAR_DNSTAP_LOG_RESOLVER_RESPONSE_MESSAGES 439
#define VAR_DNSTAP_LOG_CLIENT_QUERY_MESSAGES 440
#define VAR_DNSTAP_LOG_CLIENT_RESPONSE_MESSAGES 441
#define VAR_DNSTAP_LOG_FORWARDER_QUERY_MESSAGES 442
#define VAR_DNSTAP_LOG_FORWARDER_RESPONSE_MESSAGES 443
#define VAR_RESPONSE_IP_TAG 444
#define VAR_RESPONSE_IP 445
#define VAR_RESPONSE_IP_DATA 446
#define VAR_HARDEN_ALGO_DOWNGRADE 447
#define VAR_IP_TRANSPARENT 448
#define VAR_IP_DSCP 449
#define VAR_DISABLE_DNSSEC_LAME_CHECK 450
#define VAR_IP_RATELIMIT 451
#define VAR_IP_RATELIMIT_SLABS 452
#define VAR_IP_RATELIMIT_SIZE 453
#define VAR_RATELIMIT 454
#define VAR_RATELIMIT_SLABS 455
#define VAR_RATELIMIT_SIZE 456
#define VAR_OUTBOUND_MSG_RETRY 457
#define VAR_RATELIMIT_FOR_DOMAIN 458
#define VAR_RATELIMIT_BELOW_DOMAIN 459
#define VAR_IP_RATELIMIT_FACTOR 460
#define VAR_RATELIMIT_FACTOR 461
#define VAR_IP_RATELIMIT_BACKOFF 462
#define VAR_RATELIMIT_BACKOFF 463
#define VAR_SEND_CLIENT_SUBNET 464
#define VAR_CLIENT_SUBNET_ZONE 465
#define VAR_CLIENT_SUBNET_ALWAYS_FORWARD 466
#define VAR_CLIENT_SUBNET_OPCODE 467
#define VAR_MAX_CLIENT_SUBNET_IPV4 468
#define VAR_MAX_CLIENT_SUBNET_IPV6 469
#define VAR_MIN_CLIENT_SUBNET_IPV4 470
#define VAR_MIN_CLIENT_SUBNET_IPV6 471
#define VAR_MAX_ECS_TREE_SIZE_IPV4 472
#define VAR_MAX_ECS_TREE_SIZE_IPV6 473
#define VAR_CAPS_WHITELIST 474
#define VAR_CACHE_MAX_NEGATIVE_TTL 475
#define VAR_PERMIT_SMALL_HOLDDOWN 476
#define VAR_QNAME_MINIMISATION 477
#define VAR_QNAME_MINIMISATION_STRICT 478
#define VAR_IP_FREEBIND 479
#define VAR_DEFINE_TAG 480
#define VAR_LOCAL_ZONE_TAG 481
#define VAR_ACCESS_CONTROL_TAG 482
#define VAR_LOCAL_ZONE_OVERRIDE 483
#define VAR_ACCESS_CONTROL_TAG_ACTION 484
#define VAR_ACCESS_CONTROL_TAG_DATA 485
#define VAR_VIEW 486
#define VAR_ACCESS_CONTROL_VIEW 487
#define VAR_VIEW_FIRST 488
#define VAR_SERVE_EXPIRED 489
#define VAR_SERVE_EXPIRED_TTL 490
#define VAR_SERVE_EXPIRED_TTL_RESET 491
#define VAR_SERVE_EXPIRED_REPLY_TTL 492
#define VAR_SERVE_EXPIRED_CLIENT_TIMEOUT 493
#define VAR_EDE_SERVE_EXPIRED 494
#define VAR_SERVE_ORIGINAL_TTL 495
#define VAR_FAKE_DSA 496
#define VAR_FAKE_SHA1 497
#define VAR_LOG_IDENTITY 498
#define VAR_HIDE_TRUSTANCHOR 499
#define VAR_HIDE_HTTP_USER_AGENT 500
#define VAR_HTTP_USER_AGENT 501
#define VAR_TRUST_ANCHOR_SIGNALING 502
#define VAR_AGGRESSIVE_NSEC 503
#define VAR_USE_SYSTEMD 504
#define VAR_SHM_ENABLE 505
#define VAR_SHM_KEY 506
#define VAR_ROOT_KEY_SENTINEL 507
#define VAR_DNSCRYPT 508
#define VAR_DNSCRYPT_ENABLE 509
#define VAR_DNSCRYPT_PORT 510
#define VAR_DNSCRYPT_PROVIDER 511
#define VAR_DNSCRYPT_SECRET_KEY 512
#define VAR_DNSCRYPT_PROVIDER_CERT 513
#define VAR_DNSCRYPT_PROVIDER_CERT_ROTATED 514
#define VAR_DNSCRYPT_SHARED_SECRET_CACHE_SIZE 515
#define VAR_DNSCRYPT_SHARED_SECRET_CACHE_SLABS 516
#define VAR_DNSCRYPT_NONCE_CACHE_SIZE 517
#define VAR_DNSCRYPT_NONCE_CACHE_SLABS 518
#define VAR_PAD_RESPONSES 519
#define VAR_PAD_RESPONSES_BLOCK_SIZE 520
#define VAR_PAD_QUERIES 521
#define VAR_PAD_QUERIES_BLOCK_SIZE 522
#define VAR_IPSECMOD_ENABLED 523
#define VAR_IPSECMOD_HOOK 524
#define VAR_IPSECMOD_IGNORE_BOGUS 525
#define VAR_IPSECMOD_MAX_TTL 526
#define VAR_IPSECMOD_WHITELIST 527
#define VAR_IPSECMOD_STRICT 528
#define VAR_CACHEDB 529
#define VAR_CACHEDB_BACKEND 530
#define VAR_CACHEDB_SECRETSEED 531
#define VAR_CACHEDB_REDISHOST 532
#define VAR_CACHEDB_REDISPORT 533
#define VAR_CACHEDB_REDISTIMEOUT 534
#define VAR_CACHEDB_REDISEXPIRERECORDS 535
#define VAR_UDP_UPSTREAM_WITHOUT_DOWNSTREAM 536
#define VAR_FOR_UPSTREAM 537
#define VAR_AUTH_ZONE 538
#define VAR_ZONEFILE 539
#define VAR_MASTER 540
#define VAR_URL 541
#define VAR_FOR_DOWNSTREAM 542
#define VAR_FALLBACK_ENABLED 543
#define VAR_TLS_ADDITIONAL_PORT 544
#define VAR_LOW_RTT 545
#define VAR_LOW_RTT_PERMIL 546
#define VAR_FAST_SERVER_PERMIL 547
#define VAR_FAST_SERVER_NUM 548
#define VAR_ALLOW_NOTIFY 549
#define VAR_TLS_WIN_CERT 550
#define VAR_TCP_CONNECTION_LIMIT 551
#define VAR_FORWARD_NO_CACHE 552
#define VAR_STUB_NO_CACHE 553
#define VAR_LOG_SERVFAIL 554
#define VAR_DENY_ANY 555
#define VAR_UNKNOWN_SERVER_TIME_LIMIT 556
#define VAR_LOG_TAG_QUERYREPLY 557
#define VAR_STREAM_WAIT_SIZE 558
#define VAR_TLS_CIPHERS 559
#define VAR_TLS_CIPHERSUITES 560
#define VAR_TLS_USE_SNI 561
#define VAR_IPSET 562
#define VAR_IPSET_NAME_V4 563
#define VAR_IPSET_NAME_V6 564
#define VAR_TLS_SESSION_TICKET_KEYS 565
#define VAR_RPZ 566
#define VAR_TAGS 567
#define VAR_RPZ_ACTION_OVERRIDE 568
#define VAR_RPZ_CNAME_OVERRIDE 569
#define VAR_RPZ_LOG 570
#define VAR_RPZ_LOG_NAME 571
#define VAR_DYNLIB 572
#define VAR_DYNLIB_FILE 573
#define VAR_EDNS_CLIENT_STRING 574
#define VAR_EDNS_CLIENT_STRING_OPCODE 575
#define VAR_NSID 576
#define VAR_ZONEMD_PERMISSIVE_MODE 577
#define VAR_ZONEMD_CHECK 578
#define VAR_ZONEMD_REJECT_ABSENCE 579
#define VAR_RPZ_SIGNAL_NXDOMAIN_RA 580
#define VAR_INTERFACE_AUTOMATIC_PORTS 581
#define VAR_EDE 582
#define VAR_INTERFACE_ACTION 583
#define VAR_INTERFACE_VIEW 584
#define VAR_INTERFACE_TAG 585
#define VAR_INTERFACE_TAG_ACTION 586
#define VAR_INTERFACE_TAG_DATA 587
#define VAR_PROXY_PROTOCOL_PORT 588

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 67 "util/configparser.y"

	char*	str;

#line 737 "util/configparser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_UTIL_CONFIGPARSER_H_INCLUDED  */
