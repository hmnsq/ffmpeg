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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_ਸਮਾਂ_ਅੰਦਰੂਨੀ_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_ਸਮਾਂ_ਅੰਦਰੂਨੀ_H

#ਅਨ੍ਤਰ੍ਭਾਵ <time.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਜੇ !HAVE_GMTIME_R && !defined(gmtime_r)
ਸਥਿਰ ਸਤਰਅੰਦਰ ਬਣਤਰ tm *ff_gmtime_r(ਅਚਲ time_t* clock, ਬਣਤਰ tm *ਨਤੀਜਾ)
{
    ਬਣਤਰ tm *ptr = gmtime(clock);
    ਜੇ (!ptr)
        ਵਾਪਸ ਨਿਰਾ;
    *ਨਤੀਜਾ = *ptr;
    ਵਾਪਸ ਨਤੀਜਾ;
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ gmtime_r ff_gmtime_r
#ਜੇ_ਅੰਤ

#ਜੇ !HAVE_LOCALTIME_R && !defined(localtime_r)
ਸਥਿਰ ਸਤਰਅੰਦਰ ਬਣਤਰ tm *ff_localtime_r(ਅਚਲ time_t* clock, ਬਣਤਰ tm *ਨਤੀਜਾ)
{
    ਬਣਤਰ tm *ptr = localtime(clock);
    ਜੇ (!ptr)
        ਵਾਪਸ ਨਿਰਾ;
    *ਨਤੀਜਾ = *ptr;
    ਵਾਪਸ ਨਤੀਜਾ;
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ localtime_r ff_localtime_r
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* AVUTIL_TIME_INTERNAL_H */
