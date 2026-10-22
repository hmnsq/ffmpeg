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

#నిర్వచితం_కాకపోతే AVUTIL_MACROS_H
#నిర్వచించు AVUTIL_MACROS_H

#అన్తర్భావ "libavutil/avconfig.h"

#ఒకవేళ AV_HAVE_BIGENDIAN
#   define AV_NE(be, le) (be)
#లేకపోతే
#   define AV_NE(be, le) (le)
#అయితే_ముగింపు

/**
 * Comparator.
 * For two numerical expressions x and y, gives 1 if x > y, -1 if x < y, and 0
 * if x == y. This is useful for instance in a qsort comparator callback.
 * Furthermore, compilers are able to optimize this to branchless code, and
 * there is no risk of overflow with signed types.
 * As with many macros, this evaluates its argument multiple times, it thus
 * must not have a side-effect.
 */
#నిర్వచించు FFDIFFSIGN(x,y) (((x)>(y)) - ((x)<(y)))

#నిర్వచించు FFMAX(a,b) ((a) > (b) ? (a) : (b))
#నిర్వచించు FFMAX3(a,b,c) FFMAX(FFMAX(a,b),c)
#నిర్వచించు FFMIN(a,b) ((a) > (b) ? (b) : (a))
#నిర్వచించు FFMIN3(a,b,c) FFMIN(FFMIN(a,b),c)

#నిర్వచించు FFSWAP(type,a,b) చేయి{type మార్పిడి_tmp= b; b= a; a= మార్పిడి_tmp;}అయితే(0)
#నిర్వచించు FF_ARRAY_ELEMS(a) (పరిమాణం(a) / పరిమాణం((a)[0]))

#నిర్వచించు MKTAG(a,b,c,d)   ((a) | ((b) << 8) | ((c) << 16) | ((గుర్తులేని)(d) << 24))
#నిర్వచించు MKBETAG(a,b,c,d) ((d) | ((c) << 8) | ((b) << 16) | ((గుర్తులేని)(a) << 24))

/**
 * @addtogroup preproc_misc Preprocessor String Macros
 *
 * String manipulation macros
 *
 * @{
 */

#నిర్వచించు AV_STRINGIFY(s)         AV_TOSTRING(s)
#నిర్వచించు AV_TOSTRING(s) #s

#నిర్వచించు AV_GLUE(a, b) a ## b
#నిర్వచించు AV_JOIN(a, b) AV_GLUE(a, b)

/**
 * @}
 */

#నిర్వచించు AV_PRAGMA(s) _Pragma(#s)

#నిర్వచించు FFALIGN(x, a) (((x)+(a)-1)&~((a)-1))

#అయితే_ముగింపు /* AVUTIL_MACROS_H */
