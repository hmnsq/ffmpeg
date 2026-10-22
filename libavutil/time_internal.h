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

#जर !HAVE_GMTIME_R && !defined(gmtime_r)
स्थिर ओळीत संरचना पंचांग *ff_gmtime_r(स्थिरांक समय_प्रकार* घड़ी, संरचना पंचांग *result)
{
    संरचना पंचांग *ptr = स_जमट(घड़ी);
    जर (!ptr)
        परत रिक्त;
    *result = *ptr;
    परत result;
}
#define gmtime_r ff_gmtime_r
#endif

#जर !HAVE_LOCALTIME_R && !defined(localtime_r)
स्थिर ओळीत संरचना पंचांग *ff_localtime_r(स्थिरांक समय_प्रकार* घड़ी, संरचना पंचांग *result)
{
    संरचना पंचांग *ptr = स_स्थानीय(घड़ी);
    जर (!ptr)
        परत रिक्त;
    *result = *ptr;
    परत result;
}
#define localtime_r ff_localtime_r
#endif

#endif /* AVUTIL_TIME_INTERNAL_H */
