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

#ifndef AVUTIL_TABLEGEN_H
#define AVUTIL_TABLEGEN_H

#অন্তর্ভাৱ <math.h>

// we lack some functions on all host platforms, and we don't care about
// performance and/or strict ISO C semantics as it's performed at build time
স্থির অন্তঃস্থ দ্ৱিগুণ ff_cbrt(দ্ৱিগুণ x)
{
    ঘূৰাই x < 0 ? -pow(-x, 1.0 / 3.0) : pow(x, 1.0 / 3.0);
}
#define cbrt ff_cbrt

স্থির অন্তঃস্থ দ্ৱিগুণ ff_rint(দ্ৱিগুণ x)
{
    ঘূৰাই x >= 0 ? floor(x + 0.5) : ceil(x - 0.5);
}
#define rint ff_rint

স্থির অন্তঃস্থ long long ff_llrint(দ্ৱিগুণ x)
{
    ঘূৰাই rint(x);
}
#define llrint ff_llrint

স্থির অন্তঃস্থ long ff_lrint(দ্ৱিগুণ x)
{
    ঘূৰাই rint(x);
}
#define lrint ff_lrint

#endif /* AVUTIL_TABLEGEN_H */
