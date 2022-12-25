/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 *   Copyright (C) 2018 Samsung Electronics Co., Ltd.
 */

#ifndef __KSMBD_MISC_H__
#define __KSMBD_MISC_H__

struct ksmbd_share_config;
struct nls_table;
struct kstat;
struct ksmbd_file;

static int match_pattern(const char *str, size_t len, const char *pattern);

static int ksmbd_validate_filename(char *filename);

static int parse_stream_name(char *filename, char **stream_name, int *s_type);

static char *convert_to_nt_pathname(const char *filename);

static int get_nlink(struct kstat *st);

static void ksmbd_conv_path_to_unix(char *path);
static void ksmbd_strip_last_slash(char *path);
static void ksmbd_conv_path_to_windows(char *path);

static char *ksmbd_casefold_sharename(struct unicode_map *um, const char *name);
static char *ksmbd_extract_sharename(struct unicode_map *um, const char *treename);

static char *convert_to_unix_name(struct ksmbd_share_config *share, const char *name);

#define KSMBD_DIR_INFO_ALIGNMENT	8

struct ksmbd_dir_info;
static char *ksmbd_convert_dir_info_name(struct ksmbd_dir_info *d_info,
				  const struct nls_table *local_nls,
				  int *conv_len);




#define NTFS_TIME_OFFSET	((u64)(369 * 365 + 89) * 24 * 3600 * 10000000)

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 18, 0)
#define notify_change(a, b, c) notify_change(a, b)
#define vfs_unlink(a, b, c) vfs_unlink(a, b)
#define vfs_link(a, b, c, d) vfs_link(a, b, c)
#define vfs_rename(a, b, c, d, e, f) vfs_rename(a, b, c, d)
#define netdev_notifier_info_to_dev(ptr) ptr
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 4, 21)
#define inode_lock(inode) mutex_lock(&inode->i_mutex)
#define inode_unlock(inode) mutex_unlock(&inode->i_mutex)
#define inode_lock_nested(inode, b) mutex_lock_nested(&inode->i_mutex, b)
#endif

#if LINUX_VERSION_CODE <= KERNEL_VERSION(4, 18, 0)
static struct timespec ksmbd_NTtimeToUnix(__le64 ntutc);
#else
static struct timespec64 ksmbd_NTtimeToUnix(__le64 ntutc);
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 20, 0)
#define KSMBD_TIME_TO_TM	time64_to_tm
#else
#define KSMBD_TIME_TO_TM	time_to_tm
#endif
#if LINUX_VERSION_CODE <= KERNEL_VERSION(4, 18, 0)
static u64 ksmbd_UnixTimeToNT(struct timespec t);
#else
static u64 ksmbd_UnixTimeToNT(struct timespec64 t);
#endif
static long long ksmbd_systime(void);

#define sysfs_emit compat_sysfs_emit
#define sysfs_emit_at compat_sysfs_emit_at

static int sysfs_emit(char *buf, const char *fmt, ...)
{
	va_list args;
	int len;

	if (WARN(!buf || offset_in_page(buf),
		 "invalid sysfs_emit: buf:%p\n", buf))
		return 0;

	va_start(args, fmt);
	len = vscnprintf(buf, PAGE_SIZE, fmt, args);
	va_end(args);

	return len;
}

static int sysfs_emit_at(char *buf, int at, const char *fmt, ...)
{
	va_list args;
	int len;

	if (WARN(!buf || offset_in_page(buf) || at < 0 || at >= PAGE_SIZE,
		 "invalid sysfs_emit_at: buf:%p at:%d\n", buf, at))
		return 0;

	va_start(args, fmt);
	len = vscnprintf(buf + at, PAGE_SIZE - at, fmt, args);
	va_end(args);

	return len;
}


#endif /* __KSMBD_MISC_H__ */
