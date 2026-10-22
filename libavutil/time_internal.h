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

#ضمن <time.h>
#ضمن "config.h"

#𐡄𐡍 !HAVE_GMTIME_R && !defined(gmtime_r)
ساكن مضمن بنية tm *ff_gmtime_r(ثابت time_t* clock, بنية tm *result)
{
    بنية tm *ptr = gmtime(clock);
    𐡄𐡍 (!ptr)
        أرجع عدم;
    *result = *ptr;
    أرجع result;
}
#define gmtime_r ff_gmtime_r
#endif

#𐡄𐡍 !HAVE_LOCALTIME_R && !defined(localtime_r)
ساكن مضمن بنية tm *ff_localtime_r(ثابت time_t* clock, بنية tm *result)
{
    بنية tm *ptr = localtime(clock);
    𐡄𐡍 (!ptr)
        أرجع عدم;
    *result = *ptr;
    أرجع result;
}
#define localtime_r ff_localtime_r
#endif

#endif /* AVUTIL_TIME_INTERNAL_H */
