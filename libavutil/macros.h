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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_MACROS_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_MACROS_H

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/avconfig.h"

#ਜੇ AV_HAVE_BIGENDIAN
#   define AV_NE(be, le) (be)
#ਨਹੀਂਤਾਂ
#   define AV_NE(be, le) (le)
#ਜੇ_ਅੰਤ

/**
 * Comparator.
 * For two numerical expressions x and y, gives 1 if x > y, -1 if x < y, and 0
 * if x == y. This is useful for instance in a qsort comparator callback.
 * Furthermore, compilers are able to optimize this to branchless code, and
 * there is no risk of overflow with signed types.
 * As with many macros, this evaluates its argument multiple times, it thus
 * must not have a side-effect.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FFDIFFSIGN(x,y) (((x)>(y)) - ((x)<(y)))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FFMAX(a,b) ((a) > (b) ? (a) : (b))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FFMAX3(a,b,c) FFMAX(FFMAX(a,b),c)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FFMIN(a,b) ((a) > (b) ? (b) : (a))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FFMIN3(a,b,c) FFMIN(FFMIN(a,b),c)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FFSWAP(type,a,b) ਕਰੋ{type ਅਦਲਾ_ਬਦਲੀ_tmp= b; b= a; a= ਅਦਲਾ_ਬਦਲੀ_tmp;}ਜਦੋਂ(0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_ARRAY_ELEMS(a) (ਆਕਾਰ(a) / ਆਕਾਰ((a)[0]))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MKTAG(a,b,c,d)   ((a) | ((b) << 8) | ((c) << 16) | ((ਬਿਨਾਨਿਸ਼ਾਨੀ)(d) << 24))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MKBETAG(a,b,c,d) ((d) | ((c) << 8) | ((b) << 16) | ((ਬਿਨਾਨਿਸ਼ਾਨੀ)(a) << 24))

/**
 * @addtogroup preproc_misc Preprocessor String Macros
 *
 * String manipulation macros
 *
 * @{
 */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_STRINGIFY(s)         AV_TOSTRING(s)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_TOSTRING(s) #s

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_GLUE(a, b) a ## b
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_JOIN(a, b) AV_GLUE(a, b)

/**
 * @}
 */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_PRAGMA(s) _Pragma(#s)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FFALIGN(x, a) (((x)+(a)-1)&~((a)-1))

#ਜੇ_ਅੰਤ /* AVUTIL_MACROS_H */
