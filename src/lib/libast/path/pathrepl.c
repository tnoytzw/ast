/***********************************************************************
 *                                                                      *
 *               This software is part of the ast package               *
 *          Copyright (c) 1985-2013 AT&T Intellectual Property          *
 *                      and is licensed under the                       *
 *                 Eclipse Public License, Version 1.0                  *
 *                    by AT&T Intellectual Property                     *
 *                                                                      *
 *                A copy of the License is available at                 *
 *          http://www.eclipse.org/org/documents/epl-v10.html           *
 *         (with md5 checksum b35adb5213ca9657e911e9befb180842)         *
 *                                                                      *
 *              Information and Software Systems Research               *
 *                            AT&T Research                             *
 *                           Florham Park NJ                            *
 *                                                                      *
 *               Glenn Fowler <glenn.s.fowler@gmail.com>                *
 *                    David Korn <dgkorn@gmail.com>                     *
 *                     Phong Vo <phongvo@gmail.com>                     *
 *                                                                      *
 ***********************************************************************/
/*
 * Glenn Fowler
 * AT&T Bell Laboratories
 *
 * in place replace of first occurrence of /match/ with /replace/ in path
 * end of path returned
 */

#define _AST_API_IMPLEMENT 1

#include <ast.h>

char *pathrepl(char *path, const char *match, const char *replace) {
    return pathrepl_20100601(path, PATH_MAX, match, replace);
}

#undef _AST_API_IMPLEMENT

#include <ast_api.h>

char *pathrepl_20100601(char *path, size_t size, const char *match, const char *replace) {
    const char *m = match;
    const char *r;
    char *t;

    if (!match) match = "";
    if (!replace) replace = "";
    if (streq(match, replace)) return (path + strlen(path));
    if (!size) size = strlen(path) + 1;
    for (;;) {
        while (*path && *path++ != '/')
            ;
        if (!*path) break;
        if (*path == *m) {
            t = path;
            while (*m && *m++ == *path) path++;
            if (!*m && *path == '/') {
                char *p;

                p = t;
                r = replace;
                while (p < path && *r) *p++ = *r++;
                if (p < path)
                    while (*p++ = *path++)
                        ;
                else if (*r && p >= path) {
                    char *u;

                    t = path + strlen(path);
                    u = t + strlen(r);
                    while (t >= path) *u-- = *t--;
                    while (*r) *p++ = *r++;
                } else
                    p += strlen(p) + 1;
                return (p - 1);
            }
            path = t;
            m = match;
        }
    }
    return (path);
}
