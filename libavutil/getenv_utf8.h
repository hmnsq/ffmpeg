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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_GETENV_UTF8_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_GETENV_UTF8_H

#ಅನ್ತರ್ಭಾವ <stdlib.h>

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "mem.h"

#ಆದರೆ HAVE_GETENV && defined(_WIN32)

#ಅನ್ತರ್ಭಾವ "libavutil/wchar_filename.h"

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಅಕ್ಷರ *getenv_utf8(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *varname)
{
    wchar_t *varname_w, *var_w;
    ಅಕ್ಷರ *var;

    ಆದರೆ (utf8towchar(varname, &varname_w))
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಆದರೆ (!varname_w)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    var_w = _wgetenv(varname_w);
    av_free(varname_w);

    ಆದರೆ (!var_w)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಆದರೆ (wchartoutf8(var_w, &var))
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಹಿಂತಿರುಗಿ var;

    // No CP_ACP fallback compared to other *_utf8() functions:
    // non UTF-8 strings must not be returned.
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ freeenv_utf8(ಅಕ್ಷರ *var)
{
    av_free(var);
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಅಕ್ಷರ *getenv_dup(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *varname)
{
    ಹಿಂತಿರುಗಿ getenv_utf8(varname);
}

#ಇಲ್ಲದಿದ್ದರೆ

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಅಕ್ಷರ *getenv_utf8(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *varname)
{
    ಹಿಂತಿರುಗಿ getenv(varname);
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ freeenv_utf8(ಅಕ್ಷರ *var)
{
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಅಕ್ಷರ *getenv_dup(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *varname)
{
    ಅಕ್ಷರ *var = getenv(varname);
    ಆದರೆ (!var)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ av_strdup(var);
}

#ಆದರೆ_ಅಂತ್ಯ // HAVE_GETENV && defined(_WIN32)

#ಆದರೆ_ಅಂತ್ಯ // AVUTIL_GETENV_UTF8_H
