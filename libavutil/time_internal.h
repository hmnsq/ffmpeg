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

#ಅನ್ತರ್ಭಾವ <time.h>
#ಅನ್ತರ್ಭಾವ "config.h"

#ಯದಿ !HAVE_GMTIME_R && !defined(gmtime_r)
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಸಂರಚನಾ tm *ff_gmtime_r(ಧ್ರುವ time_t* clock, ಸಂರಚನಾ tm *result)
{
    ಸಂರಚನಾ tm *ptr = gmtime(clock);
    ಯದಿ (!ptr)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    *result = *ptr;
    ಪ್ರತ್ಯಾಗಮ result;
}
#define gmtime_r ff_gmtime_r
#endif

#ಯದಿ !HAVE_LOCALTIME_R && !defined(localtime_r)
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಸಂರಚನಾ tm *ff_localtime_r(ಧ್ರುವ time_t* clock, ಸಂರಚನಾ tm *result)
{
    ಸಂರಚನಾ tm *ptr = localtime(clock);
    ಯದಿ (!ptr)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    *result = *ptr;
    ಪ್ರತ್ಯಾಗಮ result;
}
#define localtime_r ff_localtime_r
#endif

#endif /* AVUTIL_TIME_INTERNAL_H */
