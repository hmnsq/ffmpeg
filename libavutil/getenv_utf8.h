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

#அந்தர்பாவ <stdlib.h>

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "mem.h"

#எனில் HAVE_GETENV && defined(_WIN32)

#அந்தர்பாவ "libavutil/wchar_filename.h"

நிலையான உள்வரி எழுத்து *getenv_utf8(மாறிலி எழுத்து *varname)
{
    wchar_t *varname_w, *var_w;
    எழுத்து *var;

    எனில் (utf8towchar(varname, &varname_w))
        திரும்பு வெற்று;
    எனில் (!varname_w)
        திரும்பு வெற்று;

    var_w = _wgetenv(varname_w);
    av_free(varname_w);

    எனில் (!var_w)
        திரும்பு வெற்று;
    எனில் (wchartoutf8(var_w, &var))
        திரும்பு வெற்று;

    திரும்பு var;

    // No CP_ACP fallback compared to other *_utf8() functions:
    // non UTF-8 strings must not be returned.
}

நிலையான உள்வரி வெறுமை freeenv_utf8(எழுத்து *var)
{
    av_free(var);
}

நிலையான உள்வரி எழுத்து *getenv_dup(மாறிலி எழுத்து *varname)
{
    திரும்பு getenv_utf8(varname);
}

#இல்லையெனில்

நிலையான உள்வரி எழுத்து *getenv_utf8(மாறிலி எழுத்து *varname)
{
    திரும்பு getenv(varname);
}

நிலையான உள்வரி வெறுமை freeenv_utf8(எழுத்து *var)
{
}

நிலையான உள்வரி எழுத்து *getenv_dup(மாறிலி எழுத்து *varname)
{
    எழுத்து *var = getenv(varname);
    எனில் (!var)
        திரும்பு வெற்று;
    திரும்பு av_strdup(var);
}

#endif // HAVE_GETENV && defined(_WIN32)

#endif // AVUTIL_GETENV_UTF8_H
