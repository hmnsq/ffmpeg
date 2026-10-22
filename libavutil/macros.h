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
 * @ingroup lavu
 * Utility Preprocessor macros
 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_MACROS_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_MACROS_H

#ಅನ್ತರ್ಭಾವ "libavutil/avconfig.h"

#ಆದರೆ AV_HAVE_BIGENDIAN
#   define AV_NE(be, le) (be)
#ಇಲ್ಲದಿದ್ದರೆ
#   define AV_NE(be, le) (le)
#ಆದರೆ_ಅಂತ್ಯ

/**
 * Comparator.
 * For two numerical expressions x and y, gives 1 if x > y, -1 if x < y, and 0
 * if x == y. This is useful for instance in a qsort comparator callback.
 * Furthermore, compilers are able to optimize this to branchless code, and
 * there is no risk of overflow with signed types.
 * As with many macros, this evaluates its argument multiple times, it thus
 * must not have a side-effect.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು FFDIFFSIGN(x,y) (((x)>(y)) - ((x)<(y)))

#ವ್ಯಾಖ್ಯಾನಿಸು FFMAX(a,b) ((a) > (b) ? (a) : (b))
#ವ್ಯಾಖ್ಯಾನಿಸು FFMAX3(a,b,c) FFMAX(FFMAX(a,b),c)
#ವ್ಯಾಖ್ಯಾನಿಸು FFMIN(a,b) ((a) > (b) ? (b) : (a))
#ವ್ಯಾಖ್ಯಾನಿಸು FFMIN3(a,b,c) FFMIN(FFMIN(a,b),c)

#ವ್ಯಾಖ್ಯಾನಿಸು FFSWAP(type,a,b) ಮಾಡು{type ಅದಲುಬದಲು_tmp= b; b= a; a= ಅದಲುಬದಲು_tmp;}ಆಗ(0)
#ವ್ಯಾಖ್ಯಾನಿಸು FF_ARRAY_ELEMS(a) (ಗಾತ್ರ(a) / ಗಾತ್ರ((a)[0]))

#ವ್ಯಾಖ್ಯಾನಿಸು MKTAG(a,b,c,d)   ((a) | ((b) << 8) | ((c) << 16) | ((ಚಿಹ್ನೆರಹಿತ)(d) << 24))
#ವ್ಯಾಖ್ಯಾನಿಸು MKBETAG(a,b,c,d) ((d) | ((c) << 8) | ((b) << 16) | ((ಚಿಹ್ನೆರಹಿತ)(a) << 24))

/**
 * @addtogroup preproc_misc Preprocessor String Macros
 *
 * String manipulation macros
 *
 * @{
 */

#ವ್ಯಾಖ್ಯಾನಿಸು AV_STRINGIFY(s)         AV_TOSTRING(s)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_TOSTRING(s) #s

#ವ್ಯಾಖ್ಯಾನಿಸು AV_GLUE(a, b) a ## b
#ವ್ಯಾಖ್ಯಾನಿಸು AV_JOIN(a, b) AV_GLUE(a, b)

/**
 * @}
 */

#ವ್ಯಾಖ್ಯಾನಿಸು AV_PRAGMA(s) _Pragma(#s)

#ವ್ಯಾಖ್ಯಾನಿಸು FFALIGN(x, a) (((x)+(a)-1)&~((a)-1))

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_MACROS_H */
