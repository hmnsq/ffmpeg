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

#ifndef AVUTIL_TIME_INTERNAL_H
#define AVUTIL_TIME_INTERNAL_H

#അന്തര്ഭാവ <time.h>
#അന്തര്ഭാവ "config.h"

#എങ്കിൽ !HAVE_GMTIME_R && !defined(gmtime_r)
സ്ഥിതം വരിയിൽ ഘടന tm *ff_gmtime_r(സ്ഥിരം time_t* clock, ഘടന tm *result)
{
    ഘടന tm *ptr = gmtime(clock);
    എങ്കിൽ (!ptr)
        തിരികെ ശൂന്യ;
    *result = *ptr;
    തിരികെ result;
}
#define gmtime_r ff_gmtime_r
#endif

#എങ്കിൽ !HAVE_LOCALTIME_R && !defined(localtime_r)
സ്ഥിതം വരിയിൽ ഘടന tm *ff_localtime_r(സ്ഥിരം time_t* clock, ഘടന tm *result)
{
    ഘടന tm *ptr = localtime(clock);
    എങ്കിൽ (!ptr)
        തിരികെ ശൂന്യ;
    *result = *ptr;
    തിരികെ result;
}
#define localtime_r ff_localtime_r
#endif

#endif /* AVUTIL_TIME_INTERNAL_H */
