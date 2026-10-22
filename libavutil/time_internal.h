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

#अन्तर्भाव <time.h>
#अन्तर्भाव "config.h"

#यदि !HAVE_GMTIME_R && !defined(gmtime_r)
स्थिर अन्तःस्थ संरचना tm *ff_gmtime_r(ध्रुव time_t* clock, संरचना tm *result)
{
    संरचना tm *ptr = gmtime(clock);
    यदि (!ptr)
        प्रत्यागम रिक्त;
    *result = *ptr;
    प्रत्यागम result;
}
#define gmtime_r ff_gmtime_r
#endif

#यदि !HAVE_LOCALTIME_R && !defined(localtime_r)
स्थिर अन्तःस्थ संरचना tm *ff_localtime_r(ध्रुव time_t* clock, संरचना tm *result)
{
    संरचना tm *ptr = localtime(clock);
    यदि (!ptr)
        प्रत्यागम रिक्त;
    *result = *ptr;
    प्रत्यागम result;
}
#define localtime_r ff_localtime_r
#endif

#endif /* AVUTIL_TIME_INTERNAL_H */
