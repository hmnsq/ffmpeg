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

#அந்தர்பாவ <time.h>
#அந்தர்பாவ "config.h"

#எனில் !HAVE_GMTIME_R && !defined(gmtime_r)
நிலையான உள்வரி கட்டமைப்பு tm *ff_gmtime_r(மாறிலி time_t* clock, கட்டமைப்பு tm *result)
{
    கட்டமைப்பு tm *ptr = gmtime(clock);
    எனில் (!ptr)
        திரும்பு வெற்று;
    *result = *ptr;
    திரும்பு result;
}
#define gmtime_r ff_gmtime_r
#endif

#எனில் !HAVE_LOCALTIME_R && !defined(localtime_r)
நிலையான உள்வரி கட்டமைப்பு tm *ff_localtime_r(மாறிலி time_t* clock, கட்டமைப்பு tm *result)
{
    கட்டமைப்பு tm *ptr = localtime(clock);
    எனில் (!ptr)
        திரும்பு வெற்று;
    *result = *ptr;
    திரும்பு result;
}
#define localtime_r ff_localtime_r
#endif

#endif /* AVUTIL_TIME_INTERNAL_H */
