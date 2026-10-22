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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_MACROS_H
#وصف_ڪريو AVUTIL_MACROS_H

#ضمن "libavutil/avconfig.h"

#إذا AV_HAVE_BIGENDIAN
#   define AV_NE(be, le) (be)
#وإلا
#   define AV_NE(be, le) (le)
#جيڪڏهن_پورو

/**
 * Comparator.
 * For two numerical expressions x and y, gives 1 if x > y, -1 if x < y, and 0
 * if x == y. This is useful for instance in a qsort comparator callback.
 * Furthermore, compilers are able to optimize this to branchless code, and
 * there is no risk of overflow with signed types.
 * As with many macros, this evaluates its argument multiple times, it thus
 * must not have a side-effect.
 */
#وصف_ڪريو FFDIFFSIGN(x,y) (((x)>(y)) - ((x)<(y)))

#وصف_ڪريو FFMAX(a,b) ((a) > (b) ? (a) : (b))
#وصف_ڪريو FFMAX3(a,b,c) FFMAX(FFMAX(a,b),c)
#وصف_ڪريو FFMIN(a,b) ((a) > (b) ? (b) : (a))
#وصف_ڪريو FFMIN3(a,b,c) FFMIN(FFMIN(a,b),c)

#وصف_ڪريو FFSWAP(type,a,b) افعل{type مٽا_سٽا_tmp= b; b= a; a= مٽا_سٽا_tmp;}طالما(0)
#وصف_ڪريو FF_ARRAY_ELEMS(a) (حجم(a) / حجم((a)[0]))

#وصف_ڪريو MKTAG(a,b,c,d)   ((a) | ((b) << 8) | ((c) << 16) | ((بنانشان)(d) << 24))
#وصف_ڪريو MKBETAG(a,b,c,d) ((d) | ((c) << 8) | ((b) << 16) | ((بنانشان)(a) << 24))

/**
 * @addtogroup preproc_misc Preprocessor String Macros
 *
 * String manipulation macros
 *
 * @{
 */

#وصف_ڪريو AV_STRINGIFY(s)         AV_TOSTRING(s)
#وصف_ڪريو AV_TOSTRING(s) #s

#وصف_ڪريو AV_GLUE(a, b) a ## b
#وصف_ڪريو AV_JOIN(a, b) AV_GLUE(a, b)

/**
 * @}
 */

#وصف_ڪريو AV_PRAGMA(s) _Pragma(#s)

#وصف_ڪريو FFALIGN(x, a) (((x)+(a)-1)&~((a)-1))

#جيڪڏهن_پورو /* AVUTIL_MACROS_H */
