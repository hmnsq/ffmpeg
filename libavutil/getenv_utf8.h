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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_GETENV_UTF8_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_GETENV_UTF8_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"

#ਜੇ HAVE_GETENV && defined(_WIN32)

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/wchar_filename.h"

ਸਥਿਰ ਸਤਰਅੰਦਰ ਅੱਖਰ *getenv_utf8(ਅਚਲ ਅੱਖਰ *varname)
{
    wchar_t *varname_w, *var_w;
    ਅੱਖਰ *var;

    ਜੇ (utf8towchar(varname, &varname_w))
        ਵਾਪਸ ਨਿਰਾ;
    ਜੇ (!varname_w)
        ਵਾਪਸ ਨਿਰਾ;

    var_w = _wgetenv(varname_w);
    av_free(varname_w);

    ਜੇ (!var_w)
        ਵਾਪਸ ਨਿਰਾ;
    ਜੇ (wchartoutf8(var_w, &var))
        ਵਾਪਸ ਨਿਰਾ;

    ਵਾਪਸ var;

    // No CP_ACP fallback compared to other *_utf8() functions:
    // non UTF-8 strings must not be returned.
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ freeenv_utf8(ਅੱਖਰ *var)
{
    av_free(var);
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਅੱਖਰ *getenv_dup(ਅਚਲ ਅੱਖਰ *varname)
{
    ਵਾਪਸ getenv_utf8(varname);
}

#ਨਹੀਂਤਾਂ

ਸਥਿਰ ਸਤਰਅੰਦਰ ਅੱਖਰ *getenv_utf8(ਅਚਲ ਅੱਖਰ *varname)
{
    ਵਾਪਸ getenv(varname);
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ freeenv_utf8(ਅੱਖਰ *var)
{
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਅੱਖਰ *getenv_dup(ਅਚਲ ਅੱਖਰ *varname)
{
    ਅੱਖਰ *var = getenv(varname);
    ਜੇ (!var)
        ਵਾਪਸ ਨਿਰਾ;
    ਵਾਪਸ av_strdup(var);
}

#ਜੇ_ਅੰਤ // HAVE_GETENV && defined(_WIN32)

#ਜੇ_ਅੰਤ // AVUTIL_GETENV_UTF8_H
