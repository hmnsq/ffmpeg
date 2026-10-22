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

#अन्तर्भाव <stdlib.h>

#अन्तर्भाव "config.h"
#अन्तर्भाव "mem.h"

#जइ HAVE_GETENV && defined(_WIN32)

#अन्तर्भाव "libavutil/wchar_filename.h"

स्थिर अन्तःस्थ वर्ण *getenv_utf8(ध्रुव वर्ण *varname)
{
    wchar_t *varname_w, *var_w;
    वर्ण *var;

    जइ (utf8towchar(varname, &varname_w))
        प्रत्यागम रिक्त;
    जइ (!varname_w)
        प्रत्यागम रिक्त;

    var_w = _wgetenv(varname_w);
    av_free(varname_w);

    जइ (!var_w)
        प्रत्यागम रिक्त;
    जइ (wchartoutf8(var_w, &var))
        प्रत्यागम रिक्त;

    प्रत्यागम var;

    // No CP_ACP fallback compared to other *_utf8() functions:
    // non UTF-8 strings must not be returned.
}

स्थिर अन्तःस्थ शून्य freeenv_utf8(वर्ण *var)
{
    av_free(var);
}

स्थिर अन्तःस्थ वर्ण *getenv_dup(ध्रुव वर्ण *varname)
{
    प्रत्यागम getenv_utf8(varname);
}

#अण्णहा

स्थिर अन्तःस्थ वर्ण *getenv_utf8(ध्रुव वर्ण *varname)
{
    प्रत्यागम getenv(varname);
}

स्थिर अन्तःस्थ शून्य freeenv_utf8(वर्ण *var)
{
}

स्थिर अन्तःस्थ वर्ण *getenv_dup(ध्रुव वर्ण *varname)
{
    वर्ण *var = getenv(varname);
    जइ (!var)
        प्रत्यागम रिक्त;
    प्रत्यागम av_strdup(var);
}

#endif // HAVE_GETENV && defined(_WIN32)

#endif // AVUTIL_GETENV_UTF8_H
