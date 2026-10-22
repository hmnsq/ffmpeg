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

/**
 * @file
 * Compatibility libm for table generation files
 */

#నిర్వచితం_కాకపోతే AVUTIL_TABLEGEN_H
#నిర్వచించు AVUTIL_TABLEGEN_H

#అన్తర్భావ <math.h>

// we lack some functions on all host platforms, and we don't care about
// performance and/or strict ISO C semantics as it's performed at build time
స్థిర అంతఃవరుస ద్విగుణ ff_cbrt(ద్విగుణ x)
{
    తిరిగి x < 0 ? -ఘాతం(-x, 1.0 / 3.0) : ఘాతం(x, 1.0 / 3.0);
}
#నిర్వచించు cbrt ff_cbrt

స్థిర అంతఃవరుస ద్విగుణ ff_rint(ద్విగుణ x)
{
    తిరిగి x >= 0 ? floor(x + 0.5) : ceil(x - 0.5);
}
#నిర్వచించు rint ff_rint

స్థిర అంతఃవరుస దీర్ఘ దీర్ఘ ff_llrint(ద్విగుణ x)
{
    తిరిగి rint(x);
}
#నిర్వచించు llrint ff_llrint

స్థిర అంతఃవరుస దీర్ఘ ff_lrint(ద్విగుణ x)
{
    తిరిగి rint(x);
}
#నిర్వచించు lrint ff_lrint

#అయితే_ముగింపు /* AVUTIL_TABLEGEN_H */
