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

#ܐܢ HAVE_GETENV && defined(_WIN32)

#ضمن "libavutil/wchar_filename.h"

ساكن مضمن حرف *getenv_utf8(ثابت حرف *varname)
{
    wchar_t *varname_w, *var_w;
    حرف *var;

    ܐܢ (utf8towchar(varname, &varname_w))
        ܦܢܐ عدم;
    ܐܢ (!varname_w)
        ܦܢܐ عدم;

    var_w = _wgetenv(varname_w);
    av_free(varname_w);

    ܐܢ (!var_w)
        ܦܢܐ عدم;
    ܐܢ (wchartoutf8(var_w, &var))
        ܦܢܐ عدم;

    ܦܢܐ var;

    // No CP_ACP fallback compared to other *_utf8() functions:
    // non UTF-8 strings must not be returned.
}

ساكن مضمن فراغ freeenv_utf8(حرف *var)
{
    av_free(var);
}

ساكن مضمن حرف *getenv_dup(ثابت حرف *varname)
{
    ܦܢܐ getenv_utf8(varname);
}

#ܐܚܪܢܐ

ساكن مضمن حرف *getenv_utf8(ثابت حرف *varname)
{
    ܦܢܐ getenv(varname);
}

ساكن مضمن فراغ freeenv_utf8(حرف *var)
{
}

ساكن مضمن حرف *getenv_dup(ثابت حرف *varname)
{
    حرف *var = getenv(varname);
    ܐܢ (!var)
        ܦܢܐ عدم;
    ܦܢܐ av_strdup(var);
}

#endif // HAVE_GETENV && defined(_WIN32)

#endif // AVUTIL_GETENV_UTF8_H
