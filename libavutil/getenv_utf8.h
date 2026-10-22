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

#অন্তর্ভাব <stdlib.h>

#অন্তর্ভাব "config.h"
#অন্তর্ভাব "mem.h"

#যদি HAVE_GETENV && defined(_WIN32)

#অন্তর্ভাব "libavutil/wchar_filename.h"

স্থির অন্তঃস্থ বর্ণ *getenv_utf8(ধ্রুব বর্ণ *varname)
{
    wchar_t *varname_w, *var_w;
    বর্ণ *var;

    যদি (utf8towchar(varname, &varname_w))
        প্রত্যাগম রিক্ত;
    যদি (!varname_w)
        প্রত্যাগম রিক্ত;

    var_w = _wgetenv(varname_w);
    av_free(varname_w);

    যদি (!var_w)
        প্রত্যাগম রিক্ত;
    যদি (wchartoutf8(var_w, &var))
        প্রত্যাগম রিক্ত;

    প্রত্যাগম var;

    // No CP_ACP fallback compared to other *_utf8() functions:
    // non UTF-8 strings must not be returned.
}

স্থির অন্তঃস্থ শূন্য freeenv_utf8(বর্ণ *var)
{
    av_free(var);
}

স্থির অন্তঃস্থ বর্ণ *getenv_dup(ধ্রুব বর্ণ *varname)
{
    প্রত্যাগম getenv_utf8(varname);
}

#অন্যথা

স্থির অন্তঃস্থ বর্ণ *getenv_utf8(ধ্রুব বর্ণ *varname)
{
    প্রত্যাগম getenv(varname);
}

স্থির অন্তঃস্থ শূন্য freeenv_utf8(বর্ণ *var)
{
}

স্থির অন্তঃস্থ বর্ণ *getenv_dup(ধ্রুব বর্ণ *varname)
{
    বর্ণ *var = getenv(varname);
    যদি (!var)
        প্রত্যাগম রিক্ত;
    প্রত্যাগম av_strdup(var);
}

#endif // HAVE_GETENV && defined(_WIN32)

#endif // AVUTIL_GETENV_UTF8_H
