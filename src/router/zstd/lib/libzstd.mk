# ################################################################
# Copyright (c) Yann Collet, Facebook, Inc.
# All rights reserved.
#
# This source code is licensed under both the BSD-style license (found in the
# LICENSE file in the root directory of this source tree) and the GPLv2 (found
# in the COPYING file in the root directory of this source tree).
# You may select, at your option, one of the above-listed licenses.
# ################################################################

##################################################################
# Input Variables
##################################################################

# Zstd lib directory
LIBZSTD ?= ./

# Legacy support
ZSTD_LEGACY_SUPPORT ?= 5
ZSTD_LEGACY_MULTITHREADED_API ?= 0

# Build size optimizations
HUF_FORCE_DECOMPRESS_X1 ?= 0
HUF_FORCE_DECOMPRESS_X2 ?= 0
ZSTD_FORCE_DECOMPRESS_SEQUENCES_SHORT ?= 0
ZSTD_FORCE_DECOMPRESS_SEQUENCES_LONG ?= 0
ZSTD_NO_INLINE ?= 0
ZSTD_STRIP_ERROR_STRINGS ?= 0

# Assembly support
ZSTD_NO_ASM ?= 0

##################################################################
# libzstd helpers
##################################################################

VOID ?= /dev/null

# Make 4.3 doesn't support '\#' anymore (https://lwn.net/Articles/810071/)
NUM_SYMBOL := \#

# define silent mode as default (verbose mode with V=1 or VERBOSE=1)
$(V)$(VERBOSE).SILENT:

# When cross-compiling from linux to windows,
# one might need to specify TARGET_SYSTEM as "Windows."
# Building from Fedora fails without it.
# (but Ubuntu and Debian don't need to set anything)
TARGET_SYSTEM ?= $(OS)

# Version numbers
LIBVER_SRC := $(LIBZSTD)/zstd.h
LIBVER_MAJOR_SCRIPT:=`sed -n '/define ZSTD_VERSION_MAJOR/s/.*[[:blank:]]\([0-9][0-9]*\).*/\1/p' < $(LIBVER_SRC)`
LIBVER_MINOR_SCRIPT:=`sed -n '/define ZSTD_VERSION_MINOR/s/.*[[:blank:]]\([0-9][0-9]*\).*/\1/p' < $(LIBVER_SRC)`
LIBVER_PATCH_SCRIPT:=`sed -n '/define ZSTD_VERSION_RELEASE/s/.*[[:blank:]]\([0-9][0-9]*\).*/\1/p' < $(LIBVER_SRC)`
LIBVER_SCRIPT:= $(LIBVER_MAJOR_SCRIPT).$(LIBVER_MINOR_SCRIPT).$(LIBVER_PATCH_SCRIPT)
LIBVER_MAJOR := $(shell echo $(LIBVER_MAJOR_SCRIPT))
LIBVER_MINOR := $(shell echo $(LIBVER_MINOR_SCRIPT))
LIBVER_PATCH := $(shell echo $(LIBVER_PATCH_SCRIPT))
LIBVER := $(shell echo $(LIBVER_SCRIPT))
CCVER := $(shell $(CC) --version)
ZSTD_VERSION?= $(LIBVER)

# ZSTD_LIB_MINIFY is a helper variable that
# configures a bunch of other variables to space-optimized defaults.
ZSTD_LIB_MINIFY ?= 0
ifneq ($(ZSTD_LIB_MINIFY), 0)
  HAVE_CC_OZ ?= $(shell echo "" | $(CC) -Oz -x c -c - -o /dev/null 2> /dev/null && echo 1 || echo 0)
  ZSTD_LEGACY_SUPPORT ?= 0
  ZSTD_LIB_DEPRECATED ?= 0
  HUF_FORCE_DECOMPRESS_X1 ?= 1
  ZSTD_FORCE_DECOMPRESS_SEQUENCES_SHORT ?= 1
  ZSTD_NO_INLINE ?= 1
  ZSTD_STRIP_ERROR_STRINGS ?= 1
ifneq ($(HAVE_CC_OZ), 0)
    # Some compilers (clang) support an even more space-optimized setting.
    CFLAGS += -Oz
else
    CFLAGS += -Os
endif
  CFLAGS += -fno-stack-protector -fomit-frame-pointer -fno-ident \
            -DDYNAMIC_BMI2=0 -DNDEBUG
else
  CFLAGS ?= -O3
endif

DEBUGLEVEL ?= 0
CPPFLAGS += -DXXH_NAMESPACE=ZSTD_ -DDEBUGLEVEL=$(DEBUGLEVEL)
ifeq ($(TARGET_SYSTEM),Windows_NT)   # MinGW assumed
  CPPFLAGS += -D__USE_MINGW_ANSI_STDIO   # compatibility with %zu formatting
endif
DEBUGFLAGS= -Wall -Wextra -Wcast-qual -Wcast-align -Wshadow \
            -Wstrict-aliasing=1 -Wswitch-enum -Wdeclaration-after-statement \
            -Wstrict-prototypes -Wundef -Wpointer-arith \
            -Wvla -Wformat=2 -Winit-self -Wfloat-equal -Wwrite-strings \
            -Wredundant-decls -Wmissing-prototypes -Wc++-compat
CFLAGS   += $(DEBUGFLAGS) $(MOREFLAGS)
ASFLAGS  += $(DEBUGFLAGS) $(MOREFLAGS) $(CFLAGS)
LDFLAGS  += $(MOREFLAGS)
FLAGS     = $(CPPFLAGS) $(CFLAGS) $(ASFLAGS) $(LDFLAGS)

ifndef ALREADY_APPENDED_NOEXECSTACK
export ALREADY_APPENDED_NOEXECSTACK := 1
ifeq ($(shell echo "int main(int argc, char* argv[]) { (void)argc; (void)argv; return 0; }" | $(CC) $(FLAGS) -z noexecstack -x c -Werror - -o $(VOID) 2>$(VOID) && echo 1 || echo 0),1)
LDFLAGS += -z noexecstack
endif
ifeq ($(shell echo | $(CC) $(FLAGS) -Wa,--noexecstack -x assembler -Werror -c - -o $(VOID) 2>$(VOID) && echo 1 || echo 0),1)
CFLAGS  += -Wa,--noexecstack
# CFLAGS are also added to ASFLAGS
else ifeq ($(shell echo | $(CC) $(FLAGS) -Qunused-arguments -Wa,--noexecstack -x assembler -Werror -c - -o $(VOID) 2>$(VOID) && echo 1 || echo 0),1)
# See e.g.: https://github.com/android/ndk/issues/171
CFLAGS  += -Qunused-arguments -Wa,--noexecstack
# CFLAGS are also added to ASFLAGS
endif
endif

HAVE_COLORNEVER = $(shell echo a | grep --color=never a > /dev/null 2> /dev/null && echo 1 || echo 0)
GREP_OPTIONS ?=
ifeq ($HAVE_COLORNEVER, 1)
  GREP_OPTIONS += --color=never
endif
GREP = grep $(GREP_OPTIONS)
SED_ERE_OPT ?= -E

ZSTD_COMMON_FILES := $(sort $(wildcard $(LIBZSTD)/common/*.c))
ZSTD_COMPRESS_FILES := $(sort $(wildcard $(LIBZSTD)/compress/*.c))
ZSTD_DECOMPRESS_FILES := $(sort $(wildcard $(LIBZSTD)/decompress/*.c))
ZSTD_DICTBUILDER_FILES := $(sort $(wildcard $(LIBZSTD)/dictBuilder/*.c))
ZSTD_DEPRECATED_FILES := $(sort $(wildcard $(LIBZSTD)/deprecated/*.c))
ZSTD_LEGACY_FILES :=

ZSTD_DECOMPRESS_AMD64_ASM_FILES := $(sort $(wildcard $(LIBZSTD)/decompress/*_amd64.S))

ifneq ($(ZSTD_NO_ASM), 0)
  CPPFLAGS += -DZSTD_DISABLE_ASM
else
  # Unconditionally add the ASM files they are disabled by
  # macros in the .S file.
  ZSTD_DECOMPRESS_FILES += $(ZSTD_DECOMPRESS_AMD64_ASM_FILES)
endif
  CFLAGS += -DZSTD_NO_TRACE

ifneq ($(HUF_FORCE_DECOMPRESS_X1), 0)
  CFLAGS += -DHUF_FORCE_DECOMPRESS_X1
endif

ifneq ($(HUF_FORCE_DECOMPRESS_X2), 0)
  CFLAGS += -DHUF_FORCE_DECOMPRESS_X2
endif

ifneq ($(ZSTD_FORCE_DECOMPRESS_SEQUENCES_SHORT), 0)
  CFLAGS += -DZSTD_FORCE_DECOMPRESS_SEQUENCES_SHORT
endif

ifneq ($(ZSTD_FORCE_DECOMPRESS_SEQUENCES_LONG), 0)
  CFLAGS += -DZSTD_FORCE_DECOMPRESS_SEQUENCES_LONG
endif

ifneq ($(ZSTD_NO_INLINE), 0)
  CFLAGS += -DZSTD_NO_INLINE
endif

ifneq ($(ZSTD_STRIP_ERROR_STRINGS), 0)
  CFLAGS += -DZSTD_STRIP_ERROR_STRINGS
endif

ifneq ($(ZSTD_LEGACY_MULTITHREADED_API), 0)
  CFLAGS += -DZSTD_LEGACY_MULTITHREADED_API
endif

ifneq ($(ZSTD_LEGACY_SUPPORT), 0)
ifeq ($(shell test $(ZSTD_LEGACY_SUPPORT) -lt 8; echo $$?), 0)
  ZSTD_LEGACY_FILES += $(shell ls $(LIBZSTD)/legacy/*.c | $(GREP) 'v0[$(ZSTD_LEGACY_SUPPORT)-7]')
endif
endif
CPPFLAGS  += -DZSTD_LEGACY_SUPPORT=$(ZSTD_LEGACY_SUPPORT)

UNAME := $(shell uname)

ifndef BUILD_DIR
ifeq ($(UNAME), Darwin)
  ifeq ($(shell md5 < /dev/null > /dev/null; echo $$?), 0)
    HASH ?= md5
  endif
else ifeq ($(UNAME), FreeBSD)
  HASH ?= gmd5sum
else ifeq ($(UNAME), NetBSD)
  HASH ?= md5 -n
else ifeq ($(UNAME), OpenBSD)
  HASH ?= md5
endif
HASH ?= md5sum

HASH_DIR = conf_$(shell echo $(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $(ZSTD_FILES) | $(HASH) | cut -f 1 -d " " )
HAVE_HASH :=$(shell echo 1 | $(HASH) > /dev/null && echo 1 || echo 0)
ifeq ($(HAVE_HASH),0)
  $(info warning : could not find HASH ($(HASH)), needed to differentiate builds using different flags)
  BUILD_DIR := obj/generic_noconf
endif
endif # BUILD_DIR

ZSTD_SUBDIR := $(LIBZSTD)/common $(LIBZSTD)/compress $(LIBZSTD)/decompress $(LIBZSTD)/dictBuilder $(LIBZSTD)/legacy $(LIBZSTD)/deprecated
vpath %.c $(ZSTD_SUBDIR)
vpath %.S $(ZSTD_SUBDIR)
