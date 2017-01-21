/*	$OpenBSD: parse.h,v 1.4 2017/01/21 08:47:21 benno Exp $ */
/*
 * Copyright (c) 2016 Sebastian Benoit <benno@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef PARSE_H
#define PARSE_H

#include <sys/queue.h>

#define AUTH_MAXLEN	120	/* max lenght of an authority_c name */
#define DOMAIN_MAXLEN	255	/* max len of a domain name (rfc2181) */

/*
 * XXX other size limits needed?
 * limit all paths to PATH_MAX
 */

struct authority_c {
	LIST_ENTRY(authority_c)	 entry;
	char		       	*name;
	char		       	*agreement;
	char		       	*api;
	char		       	*account;
};

struct domain_c {
	LIST_ENTRY(domain_c)	 entry;
	LIST_HEAD(, altname_c)	altname_list;
	int			altname_count;
	char		       	*domain;
	char		       	*key;
	char		       	*cert;
	char		       	*auth;
	char		       	*challengedir;
};

struct altname_c {
	LIST_ENTRY(altname_c)	 entry;
	char		       	*domain;
};

struct keyfile {
	LIST_ENTRY(keyfile)	 entry;
	char			*name;
};

#define ACME_OPT_VERBOSE	0x00000001
#define ACME_OPT_NEWACCT	0x00000002
#define ACME_OPT_NEWDKEY	0x00000004
#define ACME_OPT_CHECK		0x00000008

struct acme_conf {
	int			 opts;
	LIST_HEAD(, authority_c) authority_list;
	LIST_HEAD(, domain_c)	 domain_list;
	LIST_HEAD(, keyfile)	 used_key_list;
};

struct acme_conf	*parse_config(const char *, int);
int			 cmdline_symset(char *);

/* use these to find a authority or domain by name */
struct authority_c	*authority_find(struct acme_conf *, char *);
struct authority_c	*authority_find0(struct acme_conf *);
struct domain_c		*domain_find(struct acme_conf *, char *);

int			 domain_valid(const char *);

#endif /* PARSE_H */
