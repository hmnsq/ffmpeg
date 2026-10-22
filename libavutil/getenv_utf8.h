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

#ضمن <stdlib.h>

#ضمن "config.h"
#ضمن "mem.h"

#𐡄𐡍 HAVE_GETENV && defined(_WIN32)

#ضمن "libavutil/wchar_filename.h"

ساكن مضمن حرف *getenv_utf8(ثابت حرف *varname)
{
    wchar_t *varname_w, *var_w;
    حرف *var;

    𐡄𐡍 (utf8towchar(varname, &varname_w))
        أرجع عدم;
    𐡄𐡍 (!varname_w)
        أرجع عدم;

    var_w = _wgetenv(varname_w);
    av_free(varname_w);

    𐡄𐡍 (!var_w)
        أرجع عدم;
    𐡄𐡍 (wchartoutf8(var_w, &var))
        أرجع عدم;

    أرجع var;

    // No CP_ACP fallback compared to other *_utf8() functions:
    // non UTF-8 strings must not be returned.
}

ساكن مضمن فراغ freeenv_utf8(حرف *var)
{
    av_free(var);
}

ساكن مضمن حرف *getenv_dup(ثابت حرف *varname)
{
    أرجع getenv_utf8(varname);
}

#وإلا

ساكن مضمن حرف *getenv_utf8(ثابت حرف *varname)
{
    أرجع getenv(varname);
}

ساكن مضمن فراغ freeenv_utf8(حرف *var)
{
}

ساكن مضمن حرف *getenv_dup(ثابت حرف *varname)
{
    حرف *var = getenv(varname);
    𐡄𐡍 (!var)
        أرجع عدم;
    أرجع av_strdup(var);
}

#endif // HAVE_GETENV && defined(_WIN32)

#endif // AVUTIL_GETENV_UTF8_H
