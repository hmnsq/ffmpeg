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

#اگر_غیر_تعریف_شدہ AVUTIL_TABLEGEN_H
#تعریف_کرو AVUTIL_TABLEGEN_H

#شامل <math.h>

// we lack some functions on all host platforms, and we don't care about
// performance and/or strict ISO C semantics as it's performed at build time
ساکن اندرونی دوہرا ff_cbrt(دوہرا x)
{
    واپس x < 0 ? -قوت(-x, 1.0 / 3.0) : قوت(x, 1.0 / 3.0);
}
#تعریف_کرو cbrt ff_cbrt

ساکن اندرونی دوہرا ff_rint(دوہرا x)
{
    واپس x >= 0 ? floor(x + 0.5) : ceil(x - 0.5);
}
#تعریف_کرو rint ff_rint

ساکن اندرونی طویل طویل ff_llrint(دوہرا x)
{
    واپس rint(x);
}
#تعریف_کرو llrint ff_llrint

ساکن اندرونی طویل ff_lrint(دوہرا x)
{
    واپس rint(x);
}
#تعریف_کرو lrint ff_lrint

#اگر_ختم /* AVUTIL_TABLEGEN_H */
