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

#ଅନ୍ତର୍ଭାଵ <stdlib.h>

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"

#ଯଦି HAVE_GETENV && defined(_WIN32)

#ଅନ୍ତର୍ଭାଵ "libavutil/wchar_filename.h"

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଅକ୍ଷର *getenv_utf8(ଅଚଳ ଅକ୍ଷର *varname)
{
    wchar_t *varname_w, *var_w;
    ଅକ୍ଷର *var;

    ଯଦି (utf8towchar(varname, &varname_w))
        ଫେରନ୍ତୁ ଖାଲି;
    ଯଦି (!varname_w)
        ଫେରନ୍ତୁ ଖାଲି;

    var_w = _wgetenv(varname_w);
    av_free(varname_w);

    ଯଦି (!var_w)
        ଫେରନ୍ତୁ ଖାଲି;
    ଯଦି (wchartoutf8(var_w, &var))
        ଫେରନ୍ତୁ ଖାଲି;

    ଫେରନ୍ତୁ var;

    // No CP_ACP fallback compared to other *_utf8() functions:
    // non UTF-8 strings must not be returned.
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ freeenv_utf8(ଅକ୍ଷର *var)
{
    av_free(var);
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଅକ୍ଷର *getenv_dup(ଅଚଳ ଅକ୍ଷର *varname)
{
    ଫେରନ୍ତୁ getenv_utf8(varname);
}

#ଅନ୍ୟଥା

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଅକ୍ଷର *getenv_utf8(ଅଚଳ ଅକ୍ଷର *varname)
{
    ଫେରନ୍ତୁ getenv(varname);
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ freeenv_utf8(ଅକ୍ଷର *var)
{
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଅକ୍ଷର *getenv_dup(ଅଚଳ ଅକ୍ଷର *varname)
{
    ଅକ୍ଷର *var = getenv(varname);
    ଯଦି (!var)
        ଫେରନ୍ତୁ ଖାଲି;
    ଫେରନ୍ତୁ av_strdup(var);
}

#endif // HAVE_GETENV && defined(_WIN32)

#endif // AVUTIL_GETENV_UTF8_H
