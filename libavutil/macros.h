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

#यदि_अपरिभाषितम् AVUTIL_MACROS_H
#परिभाषय AVUTIL_MACROS_H

#अन्तर्भाव "libavutil/avconfig.h"

#यदि AV_HAVE_BIGENDIAN
#   define AV_NE(be, le) (be)
#अन्यथा
#   define AV_NE(be, le) (le)
#यदि_अन्तः

/**
 * Comparator.
 * For two numerical expressions x and y, gives 1 if x > y, -1 if x < y, and 0
 * if x == y. This is useful for instance in a qsort comparator callback.
 * Furthermore, compilers are able to optimize this to branchless code, and
 * there is no risk of overflow with signed types.
 * As with many macros, this evaluates its argument multiple times, it thus
 * must not have a side-effect.
 */
#परिभाषय FFDIFFSIGN(x,y) (((x)>(y)) - ((x)<(y)))

#परिभाषय FFMAX(a,b) ((a) > (b) ? (a) : (b))
#परिभाषय FFMAX3(a,b,c) FFMAX(FFMAX(a,b),c)
#परिभाषय FFMIN(a,b) ((a) > (b) ? (b) : (a))
#परिभाषय FFMIN3(a,b,c) FFMIN(FFMIN(a,b),c)

#परिभाषय FFSWAP(type,a,b) कुरु{type SWAP_tmp= b; b= a; a= SWAP_tmp;}यावत्(0)
#परिभाषय FF_ARRAY_ELEMS(a) (परिमाण(a) / परिमाण((a)[0]))

#परिभाषय MKTAG(a,b,c,d)   ((a) | ((b) << 8) | ((c) << 16) | ((अचिह्नित)(d) << 24))
#परिभाषय MKBETAG(a,b,c,d) ((d) | ((c) << 8) | ((b) << 16) | ((अचिह्नित)(a) << 24))

/**
 * @addtogroup preproc_misc Preprocessor String Macros
 *
 * String manipulation macros
 *
 * @{
 */

#परिभाषय AV_STRINGIFY(s)         AV_TOSTRING(s)
#परिभाषय AV_TOSTRING(s) #s

#परिभाषय AV_GLUE(a, b) a ## b
#परिभाषय AV_JOIN(a, b) AV_GLUE(a, b)

/**
 * @}
 */

#परिभाषय AV_PRAGMA(s) _Pragma(#s)

#परिभाषय FFALIGN(x, a) (((x)+(a)-1)&~((a)-1))

#यदि_अन्तः /* AVUTIL_MACROS_H */
