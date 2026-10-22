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

#अगर_अघोषित AVUTIL_TABLEGEN_H
#घोषणा AVUTIL_TABLEGEN_H

#समावेश <math.h>

// we lack some functions on all host platforms, and we don't care about
// performance and/or strict ISO C semantics as it's performed at build time
अटल अंतरभूत द्विगुन ff_cbrt(द्विगुन x)
{
    वापस x < 0 ? -घात(-x, 1.0 / 3.0) : घात(x, 1.0 / 3.0);
}
#घोषणा cbrt ff_cbrt

अटल अंतरभूत द्विगुन ff_rint(द्विगुन x)
{
    वापस x >= 0 ? न्यूनमान(x + 0.5) : उच्चमान(x - 0.5);
}
#घोषणा rint ff_rint

अटल अंतरभूत दीर्घ दीर्घ ff_llrint(द्विगुन x)
{
    वापस rint(x);
}
#घोषणा llrint ff_llrint

अटल अंतरभूत दीर्घ ff_lrint(द्विगुन x)
{
    वापस rint(x);
}
#घोषणा lrint ff_lrint

#पूर्ण_अगर /* AVUTIL_TABLEGEN_H */
