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

#अगर_अघोषित AVUTIL_MACROS_H
#घोषणा AVUTIL_MACROS_H

#समावेश "libavutil/avconfig.h"

#अगर AV_HAVE_BIGENDIAN
#   define AV_NE(be, le) (be)
#अन्यथा
#   define AV_NE(be, le) (le)
#पूर्ण_अगर

/**
 * Comparator.
 * For two numerical expressions x and y, gives 1 if x > y, -1 if x < y, and 0
 * if x == y. This is useful for instance in a qsort comparator callback.
 * Furthermore, compilers are able to optimize this to branchless code, and
 * there is no risk of overflow with signed types.
 * As with many macros, this evaluates its argument multiple times, it thus
 * must not have a side-effect.
 */
#घोषणा FFDIFFSIGN(x,y) (((x)>(y)) - ((x)<(y)))

#घोषणा FFMAX(a,b) ((a) > (b) ? (a) : (b))
#घोषणा FFMAX3(a,b,c) FFMAX(FFMAX(a,b),c)
#घोषणा FFMIN(a,b) ((a) > (b) ? (b) : (a))
#घोषणा FFMIN3(a,b,c) FFMIN(FFMIN(a,b),c)

#घोषणा FFSWAP(type,a,b) करो{type SWAP_tmp= b; b= a; a= SWAP_tmp;}जबतक(0)
#घोषणा FF_ARRAY_ELEMS(a) (माप(a) / माप((a)[0]))

#घोषणा MKTAG(a,b,c,d)   ((a) | ((b) << 8) | ((c) << 16) | ((अचिन्हित)(d) << 24))
#घोषणा MKBETAG(a,b,c,d) ((d) | ((c) << 8) | ((b) << 16) | ((अचिन्हित)(a) << 24))

/**
 * @addtogroup preproc_misc Preprocessor String Macros
 *
 * String manipulation macros
 *
 * @{
 */

#घोषणा AV_STRINGIFY(s)         AV_TOSTRING(s)
#घोषणा AV_TOSTRING(s) #s

#घोषणा AV_GLUE(a, b) a ## b
#घोषणा AV_JOIN(a, b) AV_GLUE(a, b)

/**
 * @}
 */

#घोषणा AV_PRAGMA(s) _Pragma(#s)

#घोषणा FFALIGN(x, a) (((x)+(a)-1)&~((a)-1))

#पूर्ण_अगर /* AVUTIL_MACROS_H */
