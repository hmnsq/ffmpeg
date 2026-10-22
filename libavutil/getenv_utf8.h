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

#অন্তর্ভাৱ <stdlib.h>

#অন্তর্ভাৱ "config.h"
#অন্তর্ভাৱ "mem.h"

#যদি HAVE_GETENV && defined(_WIN32)

#অন্তর্ভাৱ "libavutil/wchar_filename.h"

স্থির অন্তঃস্থ ৱর্ণ *getenv_utf8(ধ্রুৱ ৱর্ণ *varname)
{
    wchar_t *varname_w, *var_w;
    ৱর্ণ *var;

    যদি (utf8towchar(varname, &varname_w))
        ঘূৰাই রিক্ত;
    যদি (!varname_w)
        ঘূৰাই রিক্ত;

    var_w = _wgetenv(varname_w);
    av_free(varname_w);

    যদি (!var_w)
        ঘূৰাই রিক্ত;
    যদি (wchartoutf8(var_w, &var))
        ঘূৰাই রিক্ত;

    ঘূৰাই var;

    // No CP_ACP fallback compared to other *_utf8() functions:
    // non UTF-8 strings must not be returned.
}

স্থির অন্তঃস্থ শূন্য freeenv_utf8(ৱর্ণ *var)
{
    av_free(var);
}

স্থির অন্তঃস্থ ৱর্ণ *getenv_dup(ধ্রুৱ ৱর্ণ *varname)
{
    ঘূৰাই getenv_utf8(varname);
}

#অন্যথা

স্থির অন্তঃস্থ ৱর্ণ *getenv_utf8(ধ্রুৱ ৱর্ণ *varname)
{
    ঘূৰাই getenv(varname);
}

স্থির অন্তঃস্থ শূন্য freeenv_utf8(ৱর্ণ *var)
{
}

স্থির অন্তঃস্থ ৱর্ণ *getenv_dup(ধ্রুৱ ৱর্ণ *varname)
{
    ৱর্ণ *var = getenv(varname);
    যদি (!var)
        ঘূৰাই রিক্ত;
    ঘূৰাই av_strdup(var);
}

#endif // HAVE_GETENV && defined(_WIN32)

#endif // AVUTIL_GETENV_UTF8_H
