/*
 * sundries.h: Support function prototypes.  Functions are in sundries.c.
 *
 * Copyright (C) 2007  Red Hat, Inc.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sys/types.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stdarg.h>
#include <stdlib.h>
#if !defined(bool_t) && !defined(__GLIBC__)
#include <rpc/types.h>
#endif

extern int mount_quiet;
extern int verbose;
extern int sloppy;

#define streq(s, t)	(strcmp ((s), (t)) == 0)


/* String list data structure.  */
typedef struct string_list
{
  char *hd;
  struct string_list *tl;
} *string_list;

#define car(p) ((p) -> hd)
#define cdr(p) ((p) -> tl)

string_list cons (char *a, const string_list);

/* Functions in sundries.c that are used in mount.c and umount.c  */
void block_signals (int how);
char *canonicalize (const char *path);
char *realpath (const char *path, char *resolved_path);
void error (const char *fmt, ...);
int matching_type (const char *type, string_list types);
string_list parse_list (char *strings);
void *xmalloc (size_t size);
char *xstrdup (const char *s);
char *xstrndup (const char *s, int n);
char *xstrconcat2 (const char *, const char *);
char *xstrconcat3 (const char *, const char *, const char *);
char *xstrconcat4 (const char *, const char *, const char *, const char *);

/* Here is some serious cruft.  */
#ifdef __GNUC__
#if __GNUC__ > 2 || (defined(__GNUC_MINOR__) && __GNUC__ == 2 && __GNUC_MINOR__ >= 5)
void die (int errcode, const char *fmt, ...) __attribute__ ((noreturn));
#else /* GNUC < 2.5 */
void volatile die (int errcode, const char *fmt, ...);
#endif /* GNUC < 2.5 */
#else /* !__GNUC__ */
void die (int errcode, const char *fmt, ...);
#endif /* !__GNUC__ */

#ifdef HAVE_NFS
int nfsmount (const char *spec, const char *node, int *flags,
	      char **orig_opts, char **opt_args, int running_bg);
#endif

/* exit status - bits below are ORed */
#define EX_USAGE	1	/* incorrect invocation or permission */
#define EX_SYSERR	2	/* out of memory, cannot fork, ... */
#define EX_SOFTWARE	4	/* internal mount bug or wrong version */
#define EX_USER		8	/* user interrupt */
#define EX_FILEIO      16	/* problems writing, locking, ... mtab/fstab */
#define EX_FAIL	       32	/* mount failure */
#define EX_SOMEOK      64	/* some mount succeeded */

#define EX_BG         256       /* retry in background (internal only) */
