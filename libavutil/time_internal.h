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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_ಸಮಯ_ಆಂತರಿಕ_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_ಸಮಯ_ಆಂತರಿಕ_H

#ಅನ್ತರ್ಭಾವ <time.h>
#ಅನ್ತರ್ಭಾವ "config.h"

#ಆದರೆ !HAVE_GMTIME_R && !defined(gmtime_r)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ರಚನೆ tm *ff_gmtime_r(ಸ್ಥಿರಾಂಕ time_t* clock, ರಚನೆ tm *ಫಲಿತಾಂಶ)
{
    ರಚನೆ tm *ptr = gmtime(clock);
    ಆದರೆ (!ptr)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    *ಫಲಿತಾಂಶ = *ptr;
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}
#ವ್ಯಾಖ್ಯಾನಿಸು gmtime_r ff_gmtime_r
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ !HAVE_LOCALTIME_R && !defined(localtime_r)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ರಚನೆ tm *ff_localtime_r(ಸ್ಥಿರಾಂಕ time_t* clock, ರಚನೆ tm *ಫಲಿತಾಂಶ)
{
    ರಚನೆ tm *ptr = localtime(clock);
    ಆದರೆ (!ptr)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    *ಫಲಿತಾಂಶ = *ptr;
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}
#ವ್ಯಾಖ್ಯಾನಿಸು localtime_r ff_localtime_r
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_TIME_INTERNAL_H */
