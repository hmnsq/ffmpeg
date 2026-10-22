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

#અન્તર્ભાવ <stdlib.h>

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "mem.h"

#જો HAVE_GETENV && defined(_WIN32)

#અન્તર્ભાવ "libavutil/wchar_filename.h"

સ્થિર અંતઃરેખ અક્ષર *getenv_utf8(અચલ અક્ષર *varname)
{
    wchar_t *varname_w, *var_w;
    અક્ષર *var;

    જો (utf8towchar(varname, &varname_w))
        પાછા ખાલી;
    જો (!varname_w)
        પાછા ખાલી;

    var_w = _wgetenv(varname_w);
    av_free(varname_w);

    જો (!var_w)
        પાછા ખાલી;
    જો (wchartoutf8(var_w, &var))
        પાછા ખાલી;

    પાછા var;

    // No CP_ACP fallback compared to other *_utf8() functions:
    // non UTF-8 strings must not be returned.
}

સ્થિર અંતઃરેખ શૂન્ય freeenv_utf8(અક્ષર *var)
{
    av_free(var);
}

સ્થિર અંતઃરેખ અક્ષર *getenv_dup(અચલ અક્ષર *varname)
{
    પાછા getenv_utf8(varname);
}

#નહીંતર

સ્થિર અંતઃરેખ અક્ષર *getenv_utf8(અચલ અક્ષર *varname)
{
    પાછા getenv(varname);
}

સ્થિર અંતઃરેખ શૂન્ય freeenv_utf8(અક્ષર *var)
{
}

સ્થિર અંતઃરેખ અક્ષર *getenv_dup(અચલ અક્ષર *varname)
{
    અક્ષર *var = getenv(varname);
    જો (!var)
        પાછા ખાલી;
    પાછા av_strdup(var);
}

#endif // HAVE_GETENV && defined(_WIN32)

#endif // AVUTIL_GETENV_UTF8_H
