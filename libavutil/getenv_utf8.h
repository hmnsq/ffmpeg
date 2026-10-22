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

#ಅನ್ತರ್ಭಾವ <stdlib.h>

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "mem.h"

#ಯದಿ HAVE_GETENV && defined(_WIN32)

#ಅನ್ತರ್ಭಾವ "libavutil/wchar_filename.h"

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ವರ್ಣ *getenv_utf8(ಧ್ರುವ ವರ್ಣ *varname)
{
    wchar_t *varname_w, *var_w;
    ವರ್ಣ *var;

    ಯದಿ (utf8towchar(varname, &varname_w))
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    ಯದಿ (!varname_w)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    var_w = _wgetenv(varname_w);
    av_free(varname_w);

    ಯದಿ (!var_w)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    ಯದಿ (wchartoutf8(var_w, &var))
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ಪ್ರತ್ಯಾಗಮ var;

    // No CP_ACP fallback compared to other *_utf8() functions:
    // non UTF-8 strings must not be returned.
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ freeenv_utf8(ವರ್ಣ *var)
{
    av_free(var);
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ವರ್ಣ *getenv_dup(ಧ್ರುವ ವರ್ಣ *varname)
{
    ಪ್ರತ್ಯಾಗಮ getenv_utf8(varname);
}

#ಅನ್ಯಥಾ

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ವರ್ಣ *getenv_utf8(ಧ್ರುವ ವರ್ಣ *varname)
{
    ಪ್ರತ್ಯಾಗಮ getenv(varname);
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ freeenv_utf8(ವರ್ಣ *var)
{
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ವರ್ಣ *getenv_dup(ಧ್ರುವ ವರ್ಣ *varname)
{
    ವರ್ಣ *var = getenv(varname);
    ಯದಿ (!var)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ av_strdup(var);
}

#endif // HAVE_GETENV && defined(_WIN32)

#endif // AVUTIL_GETENV_UTF8_H
