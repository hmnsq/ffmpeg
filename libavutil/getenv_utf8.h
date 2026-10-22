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

#अगर_अघोषित AVUTIL_GETENV_UTF8_H
#घोषणा AVUTIL_GETENV_UTF8_H

#समावेश <stdlib.h>

#समावेश "config.h"
#समावेश "mem.h"

#अगर HAVE_GETENV && defined(_WIN32)

#समावेश "libavutil/wchar_filename.h"

अटल अंतरभूत अक्षर *getenv_utf8(स्थिर अक्षर *varname)
{
    ब_अक्षर_प्रकार *varname_w, *var_w;
    अक्षर *var;

    अगर (utf8towchar(varname, &varname_w))
        वापस शून्य;
    अगर (!varname_w)
        वापस शून्य;

    var_w = _wgetenv(varname_w);
    av_free(varname_w);

    अगर (!var_w)
        वापस शून्य;
    अगर (wchartoutf8(var_w, &var))
        वापस शून्य;

    वापस var;

    // No CP_ACP fallback compared to other *_utf8() functions:
    // non UTF-8 strings must not be returned.
}

अटल अंतरभूत व्योम freeenv_utf8(अक्षर *var)
{
    av_free(var);
}

अटल अंतरभूत अक्षर *getenv_dup(स्थिर अक्षर *varname)
{
    वापस getenv_utf8(varname);
}

#अन्यथा

अटल अंतरभूत अक्षर *getenv_utf8(स्थिर अक्षर *varname)
{
    वापस दो_पर्या(varname);
}

अटल अंतरभूत व्योम freeenv_utf8(अक्षर *var)
{
}

अटल अंतरभूत अक्षर *getenv_dup(स्थिर अक्षर *varname)
{
    अक्षर *var = दो_पर्या(varname);
    अगर (!var)
        वापस शून्य;
    वापस av_strdup(var);
}

#पूर्ण_अगर // HAVE_GETENV && defined(_WIN32)

#पूर्ण_अगर // AVUTIL_GETENV_UTF8_H
