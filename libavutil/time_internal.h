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

#অন্তর্ভাব <time.h>
#অন্তর্ভাব "config.h"

#যদি !HAVE_GMTIME_R && !defined(gmtime_r)
স্থির অন্তঃস্থ সংরচনা tm *ff_gmtime_r(ধ্রুব time_t* clock, সংরচনা tm *result)
{
    সংরচনা tm *ptr = gmtime(clock);
    যদি (!ptr)
        প্রত্যাগম রিক্ত;
    *result = *ptr;
    প্রত্যাগম result;
}
#define gmtime_r ff_gmtime_r
#endif

#যদি !HAVE_LOCALTIME_R && !defined(localtime_r)
স্থির অন্তঃস্থ সংরচনা tm *ff_localtime_r(ধ্রুব time_t* clock, সংরচনা tm *result)
{
    সংরচনা tm *ptr = localtime(clock);
    যদি (!ptr)
        প্রত্যাগম রিক্ত;
    *result = *ptr;
    প্রত্যাগম result;
}
#define localtime_r ff_localtime_r
#endif

#endif /* AVUTIL_TIME_INTERNAL_H */
