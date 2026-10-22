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

#నిర్వచితం_కాకపోతే AVUTIL_సమయం_అంతర్గత_H
#నిర్వచించు AVUTIL_సమయం_అంతర్గత_H

#అన్తర్భావ <time.h>
#అన్తర్భావ "config.h"

#ఒకవేళ !HAVE_GMTIME_R && !defined(gmtime_r)
స్థిర అంతఃవరుస నిర్మాణం tm *ff_gmtime_r(స్థిరరాశి time_t* clock, నిర్మాణం tm *ఫలితం)
{
    నిర్మాణం tm *ptr = gmtime(clock);
    ఒకవేళ (!ptr)
        తిరిగి ఖాళీ;
    *ఫలితం = *ptr;
    తిరిగి ఫలితం;
}
#నిర్వచించు gmtime_r ff_gmtime_r
#అయితే_ముగింపు

#ఒకవేళ !HAVE_LOCALTIME_R && !defined(localtime_r)
స్థిర అంతఃవరుస నిర్మాణం tm *ff_localtime_r(స్థిరరాశి time_t* clock, నిర్మాణం tm *ఫలితం)
{
    నిర్మాణం tm *ptr = localtime(clock);
    ఒకవేళ (!ptr)
        తిరిగి ఖాళీ;
    *ఫలితం = *ptr;
    తిరిగి ఫలితం;
}
#నిర్వచించు localtime_r ff_localtime_r
#అయితే_ముగింపు

#అయితే_ముగింపు /* AVUTIL_TIME_INTERNAL_H */
