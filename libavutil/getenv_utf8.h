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

#నిర్వచితం_కాకపోతే AVUTIL_GETENV_UTF8_H
#నిర్వచించు AVUTIL_GETENV_UTF8_H

#అన్తర్భావ <stdlib.h>

#అన్తర్భావ "config.h"
#అన్తర్భావ "mem.h"

#ఒకవేళ HAVE_GETENV && defined(_WIN32)

#అన్తర్భావ "libavutil/wchar_filename.h"

స్థిర అంతఃవరుస అక్షరం *getenv_utf8(స్థిరరాశి అక్షరం *varname)
{
    wchar_t *varname_w, *var_w;
    అక్షరం *var;

    ఒకవేళ (utf8towchar(varname, &varname_w))
        తిరిగి ఖాళీ;
    ఒకవేళ (!varname_w)
        తిరిగి ఖాళీ;

    var_w = _wgetenv(varname_w);
    av_free(varname_w);

    ఒకవేళ (!var_w)
        తిరిగి ఖాళీ;
    ఒకవేళ (wchartoutf8(var_w, &var))
        తిరిగి ఖాళీ;

    తిరిగి var;

    // No CP_ACP fallback compared to other *_utf8() functions:
    // non UTF-8 strings must not be returned.
}

స్థిర అంతఃవరుస శూన్య freeenv_utf8(అక్షరం *var)
{
    av_free(var);
}

స్థిర అంతఃవరుస అక్షరం *getenv_dup(స్థిరరాశి అక్షరం *varname)
{
    తిరిగి getenv_utf8(varname);
}

#లేకపోతే

స్థిర అంతఃవరుస అక్షరం *getenv_utf8(స్థిరరాశి అక్షరం *varname)
{
    తిరిగి getenv(varname);
}

స్థిర అంతఃవరుస శూన్య freeenv_utf8(అక్షరం *var)
{
}

స్థిర అంతఃవరుస అక్షరం *getenv_dup(స్థిరరాశి అక్షరం *varname)
{
    అక్షరం *var = getenv(varname);
    ఒకవేళ (!var)
        తిరిగి ఖాళీ;
    తిరిగి av_strdup(var);
}

#అయితే_ముగింపు // HAVE_GETENV && defined(_WIN32)

#అయితే_ముగింపు // AVUTIL_GETENV_UTF8_H
