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

#اگر_غیر_تعریف_شدہ AVUTIL_GETENV_UTF8_H
#تعریف_کرو AVUTIL_GETENV_UTF8_H

#شامل <stdlib.h>

#شامل "config.h"
#شامل "mem.h"

#اگر HAVE_GETENV && defined(_WIN32)

#شامل "libavutil/wchar_filename.h"

ساکن اندرونی حرف *getenv_utf8(ثابت حرف *varname)
{
    wchar_t *varname_w, *var_w;
    حرف *var;

    اگر (utf8towchar(varname, &varname_w))
        واپس تہی;
    اگر (!varname_w)
        واپس تہی;

    var_w = _wgetenv(varname_w);
    av_free(varname_w);

    اگر (!var_w)
        واپس تہی;
    اگر (wchartoutf8(var_w, &var))
        واپس تہی;

    واپس var;

    // No CP_ACP fallback compared to other *_utf8() functions:
    // non UTF-8 strings must not be returned.
}

ساکن اندرونی خالی freeenv_utf8(حرف *var)
{
    av_free(var);
}

ساکن اندرونی حرف *getenv_dup(ثابت حرف *varname)
{
    واپس getenv_utf8(varname);
}

#ورنہ

ساکن اندرونی حرف *getenv_utf8(ثابت حرف *varname)
{
    واپس getenv(varname);
}

ساکن اندرونی خالی freeenv_utf8(حرف *var)
{
}

ساکن اندرونی حرف *getenv_dup(ثابت حرف *varname)
{
    حرف *var = getenv(varname);
    اگر (!var)
        واپس تہی;
    واپس av_strdup(var);
}

#اگر_ختم // HAVE_GETENV && defined(_WIN32)

#اگر_ختم // AVUTIL_GETENV_UTF8_H
