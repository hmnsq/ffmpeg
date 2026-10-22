/*
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVUTIL_GETENV_UTF8_H
#define AVUTIL_GETENV_UTF8_H

#include <stdlib.h>

#include "config.h"
#include "mem.h"

#如果 HAVE_GETENV && defined(_WIN32)

#include "libavutil/wchar_filename.h"

static inline char *getenv_utf8(const char *varname)
{
    wchar_t *varname_w, *var_w;
    char *var;

    如果 (utf8towchar(varname, &varname_w))
        返回 NULL;
    如果 (!varname_w)
        返回 NULL;

    var_w = _wgetenv(varname_w);
    av_free(varname_w);

    如果 (!var_w)
        返回 NULL;
    如果 (wchartoutf8(var_w, &var))
        返回 NULL;

    返回 var;

    // No CP_ACP fallback compared to other *_utf8() functions:
    // non UTF-8 strings must not be returned.
}

static inline void freeenv_utf8(char *var)
{
    av_free(var);
}

static inline char *getenv_dup(const char *varname)
{
    返回 getenv_utf8(varname);
}

#否则

static inline char *getenv_utf8(const char *varname)
{
    返回 getenv(varname);
}

static inline void freeenv_utf8(char *var)
{
}

static inline char *getenv_dup(const char *varname)
{
    char *var = getenv(varname);
    如果 (!var)
        返回 NULL;
    返回 av_strdup(var);
}

#endif // HAVE_GETENV && defined(_WIN32)

#endif // AVUTIL_GETENV_UTF8_H
