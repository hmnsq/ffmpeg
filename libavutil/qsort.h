/*
 * copyright (c) 2012 Michael Niedermayer <michaelni@gmx.at>
 *
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

#ifndef AVUTIL_QSORT_H
#define AVUTIL_QSORT_H

#ضمن "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#define AV_QSORT(p, رقم, type, cmp) افعل {\
    فراغ *مكدس[64][2];\
    صحيح sp= 1;\
    مكدس[0][0] = p;\
    مكدس[0][1] = (p)+(رقم)-1;\
    بينما(sp){\
        type *start= مكدس[--sp][0];\
        type *end  = مكدس[  sp][1];\
        بينما(start < end){\
            إذا(start < end-1) {\
                صحيح checksort=0;\
                type *يمين = end-2;\
                type *يسار  = start+1;\
                type *mid = start + ((end-start)>>1);\
                إذا(cmp(start, end) > 0) {\
                    إذا(cmp(  end, mid) > 0) FFSWAP(type, *start, *mid);\
                    وإلا                    FFSWAP(type, *start, *end);\
                }وإلا{\
                    إذا(cmp(start, mid) > 0) FFSWAP(type, *start, *mid);\
                    وإلا checksort= 1;\
                }\
                إذا(cmp(mid, end) > 0){ \
                    FFSWAP(type, *mid, *end);\
                    checksort=0;\
                }\
                إذا(start == end-2) اكسر;\
                FFSWAP(type, end[-1], *mid);\
                بينما(يسار <= يمين){\
                    بينما(يسار<=يمين && cmp(يسار, end-1) < 0)\
                        يسار++;\
                    بينما(يسار<=يمين && cmp(يمين, end-1) > 0)\
                        يمين--;\
                    إذا(يسار <= يمين){\
                        FFSWAP(type, *يسار, *يمين);\
                        يسار++;\
                        يمين--;\
                    }\
                }\
                FFSWAP(type, end[-1], *يسار);\
                إذا(checksort && (mid == يسار-1 || mid == يسار)){\
                    mid= start;\
                    بينما(mid<end && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    إذا(mid==end)\
                        اكسر;\
                }\
                إذا(end-يسار < يسار-start){\
                    مكدس[sp  ][0]= start;\
                    مكدس[sp++][1]= يمين;\
                    start = يسار+1;\
                }وإلا{\
                    مكدس[sp  ][0]= يسار+1;\
                    مكدس[sp++][1]= end;\
                    end = يمين;\
                }\
            }وإلا{\
                إذا(cmp(start, end) > 0)\
                    FFSWAP(type, *start, *end);\
                اكسر;\
            }\
        }\
    }\
} بينما (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#define AV_MSORT(p, tmp, رقم, type, cmp) افعل {\
    unsigned i, j, step;\
    لكل(step=1; step<(رقم); step+=step){\
        لكل(i=0; i<(رقم); i+=2*step){\
            unsigned a[2] = {i, i+step};\
            unsigned end = FFMIN(i+2*step, (رقم));\
            لكل(j=i; a[0]<i+step && a[1]<end; j++){\
                صحيح idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            إذا(a[0]>=i+step) a[0] = a[1];\
            لكل(; j<end; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} بينما (0)

#endif /* AVUTIL_QSORT_H */
