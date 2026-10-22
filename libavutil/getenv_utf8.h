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

#شامل <stdlib.h>

#شامل "config.h"
#شامل "mem.h"

#اگر HAVE_GETENV && defined(_WIN32)

#شامل "libavutil/wchar_filename.h"

ایستا درونخطی نویسه *getenv_utf8(ثابت نویسه *varname)
{
    wchar_t *varname_w, *var_w;
    نویسه *var;

    اگر (utf8towchar(varname, &varname_w))
        بازگشت پوچ;
    اگر (!varname_w)
        بازگشت پوچ;

    var_w = _wgetenv(varname_w);
    av_free(varname_w);

    اگر (!var_w)
        بازگشت پوچ;
    اگر (wchartoutf8(var_w, &var))
        بازگشت پوچ;

    بازگشت var;

    // No CP_ACP fallback compared to other *_utf8() functions:
    // non UTF-8 strings must not be returned.
}

ایستا درونخطی تهی freeenv_utf8(نویسه *var)
{
    av_free(var);
}

ایستا درونخطی نویسه *getenv_dup(ثابت نویسه *varname)
{
    بازگشت getenv_utf8(varname);
}

#وگرنه

ایستا درونخطی نویسه *getenv_utf8(ثابت نویسه *varname)
{
    بازگشت getenv(varname);
}

ایستا درونخطی تهی freeenv_utf8(نویسه *var)
{
}

ایستا درونخطی نویسه *getenv_dup(ثابت نویسه *varname)
{
    نویسه *var = getenv(varname);
    اگر (!var)
        بازگشت پوچ;
    بازگشت av_strdup(var);
}

#endif // HAVE_GETENV && defined(_WIN32)

#endif // AVUTIL_GETENV_UTF8_H
