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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_وقت_اندروني_H
#وصف_ڪريو AVUTIL_وقت_اندروني_H

#ضمن <time.h>
#ضمن "config.h"

#إذا !HAVE_GMTIME_R && !defined(gmtime_r)
ساكن مضمن بنية tm *ff_gmtime_r(ثابت time_t* clock, بنية tm *نتيجو)
{
    بنية tm *ptr = gmtime(clock);
    إذا (!ptr)
        أرجع عدم;
    *نتيجو = *ptr;
    أرجع نتيجو;
}
#وصف_ڪريو gmtime_r ff_gmtime_r
#جيڪڏهن_پورو

#إذا !HAVE_LOCALTIME_R && !defined(localtime_r)
ساكن مضمن بنية tm *ff_localtime_r(ثابت time_t* clock, بنية tm *نتيجو)
{
    بنية tm *ptr = localtime(clock);
    إذا (!ptr)
        أرجع عدم;
    *نتيجو = *ptr;
    أرجع نتيجو;
}
#وصف_ڪريو localtime_r ff_localtime_r
#جيڪڏهن_پورو

#جيڪڏهن_پورو /* AVUTIL_TIME_INTERNAL_H */
