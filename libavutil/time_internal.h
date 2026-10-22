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

#که_نه_تعریف_شوی AVUTIL_وخت_دننی_H
#تعریف_کړه AVUTIL_وخت_دننی_H

#ضمن <time.h>
#ضمن "config.h"

#إذا !HAVE_GMTIME_R && !defined(gmtime_r)
ساكن مضمن بنية tm *ff_gmtime_r(ثابت time_t* clock, بنية tm *پایله)
{
    بنية tm *ptr = gmtime(clock);
    إذا (!ptr)
        أرجع عدم;
    *پایله = *ptr;
    أرجع پایله;
}
#تعریف_کړه gmtime_r ff_gmtime_r
#د_که_پای

#إذا !HAVE_LOCALTIME_R && !defined(localtime_r)
ساكن مضمن بنية tm *ff_localtime_r(ثابت time_t* clock, بنية tm *پایله)
{
    بنية tm *ptr = localtime(clock);
    إذا (!ptr)
        أرجع عدم;
    *پایله = *ptr;
    أرجع پایله;
}
#تعریف_کړه localtime_r ff_localtime_r
#د_که_پای

#د_که_پای /* AVUTIL_TIME_INTERNAL_H */
