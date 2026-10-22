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

#अन्तर्भाव <math.h>

// we lack some functions on all host platforms, and we don't care about
// performance and/or strict ISO C semantics as it's performed at build time
स्थिर अन्तःस्थ द्विगुण ff_cbrt(द्विगुण x)
{
    फर्काऊ x < 0 ? -घात(-x, 1.0 / 3.0) : घात(x, 1.0 / 3.0);
}
#define cbrt ff_cbrt

स्थिर अन्तःस्थ द्विगुण ff_rint(द्विगुण x)
{
    फर्काऊ x >= 0 ? न्यूनमान(x + 0.5) : उच्चमान(x - 0.5);
}
#define rint ff_rint

स्थिर अन्तःस्थ दीर्घ दीर्घ ff_llrint(द्विगुण x)
{
    फर्काऊ rint(x);
}
#define llrint ff_llrint

स्थिर अन्तःस्थ दीर्घ ff_lrint(द्विगुण x)
{
    फर्काऊ rint(x);
}
#define lrint ff_lrint

#endif /* AVUTIL_TABLEGEN_H */
