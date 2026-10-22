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

#അന്തര്ഭാവ <stdlib.h>

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "mem.h"

#എങ്കിൽ HAVE_GETENV && defined(_WIN32)

#അന്തര്ഭാവ "libavutil/wchar_filename.h"

സ്ഥിതം വരിയിൽ അക്ഷരം *getenv_utf8(സ്ഥിരം അക്ഷരം *varname)
{
    wchar_t *varname_w, *var_w;
    അക്ഷരം *var;

    എങ്കിൽ (utf8towchar(varname, &varname_w))
        തിരികെ ശൂന്യ;
    എങ്കിൽ (!varname_w)
        തിരികെ ശൂന്യ;

    var_w = _wgetenv(varname_w);
    av_free(varname_w);

    എങ്കിൽ (!var_w)
        തിരികെ ശൂന്യ;
    എങ്കിൽ (wchartoutf8(var_w, &var))
        തിരികെ ശൂന്യ;

    തിരികെ var;

    // No CP_ACP fallback compared to other *_utf8() functions:
    // non UTF-8 strings must not be returned.
}

സ്ഥിതം വരിയിൽ ശൂന്യം freeenv_utf8(അക്ഷരം *var)
{
    av_free(var);
}

സ്ഥിതം വരിയിൽ അക്ഷരം *getenv_dup(സ്ഥിരം അക്ഷരം *varname)
{
    തിരികെ getenv_utf8(varname);
}

#അല്ലെങ്കിൽ

സ്ഥിതം വരിയിൽ അക്ഷരം *getenv_utf8(സ്ഥിരം അക്ഷരം *varname)
{
    തിരികെ getenv(varname);
}

സ്ഥിതം വരിയിൽ ശൂന്യം freeenv_utf8(അക്ഷരം *var)
{
}

സ്ഥിതം വരിയിൽ അക്ഷരം *getenv_dup(സ്ഥിരം അക്ഷരം *varname)
{
    അക്ഷരം *var = getenv(varname);
    എങ്കിൽ (!var)
        തിരികെ ശൂന്യ;
    തിരികെ av_strdup(var);
}

#endif // HAVE_GETENV && defined(_WIN32)

#endif // AVUTIL_GETENV_UTF8_H
