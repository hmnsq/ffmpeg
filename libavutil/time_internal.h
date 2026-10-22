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

#include <time.h>
#include "config.h"

#ถ้า !HAVE_GMTIME_R && !defined(gmtime_r)
static anta_hstha sa_nracanaa tm *ff_gmtime_r(const time_t* clock, sa_nracanaa tm *result)
{
    sa_nracanaa tm *ptr = gmtime(clock);
    ถ้า (!ptr)
        คืน NULL;
    *result = *ptr;
    คืน result;
}
#define gmtime_r ff_gmtime_r
#endif

#ถ้า !HAVE_LOCALTIME_R && !defined(localtime_r)
static anta_hstha sa_nracanaa tm *ff_localtime_r(const time_t* clock, sa_nracanaa tm *result)
{
    sa_nracanaa tm *ptr = localtime(clock);
    ถ้า (!ptr)
        คืน NULL;
    *result = *ptr;
    คืน result;
}
#define localtime_r ff_localtime_r
#endif

#endif /* AVUTIL_TIME_INTERNAL_H */
