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

#ຖ້າ HAVE_GETENV && defined(_WIN32)

#include "libavutil/wchar_filename.h"

static anta_hstha var_na *getenv_utf8(const var_na *varname)
{
    wchar_t *varname_w, *var_w;
    var_na *var;

    ຖ້າ (utf8towchar(varname, &varname_w))
        ສົ່ງຄືນ NULL;
    ຖ້າ (!varname_w)
        ສົ່ງຄືນ NULL;

    var_w = _wgetenv(varname_w);
    av_free(varname_w);

    ຖ້າ (!var_w)
        ສົ່ງຄືນ NULL;
    ຖ້າ (wchartoutf8(var_w, &var))
        ສົ່ງຄືນ NULL;

    ສົ່ງຄືນ var;

    // No CP_ACP fallback compared to other *_utf8() functions:
    // non UTF-8 strings must not be returned.
}

static anta_hstha void freeenv_utf8(var_na *var)
{
    av_free(var);
}

static anta_hstha var_na *getenv_dup(const var_na *varname)
{
    ສົ່ງຄືນ getenv_utf8(varname);
}

#ບໍ່ດັ່ງນັ້ນ

static anta_hstha var_na *getenv_utf8(const var_na *varname)
{
    ສົ່ງຄືນ getenv(varname);
}

static anta_hstha void freeenv_utf8(var_na *var)
{
}

static anta_hstha var_na *getenv_dup(const var_na *varname)
{
    var_na *var = getenv(varname);
    ຖ້າ (!var)
        ສົ່ງຄືນ NULL;
    ສົ່ງຄືນ av_strdup(var);
}

#endif // HAVE_GETENV && defined(_WIN32)

#endif // AVUTIL_GETENV_UTF8_H
