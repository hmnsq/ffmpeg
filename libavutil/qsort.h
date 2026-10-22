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
#define AV_QSORT(p, اڠک, type, cmp) افعل {\
    فراغ *تيندنن[64][2];\
    صحيح sp= 1;\
    تيندنن[0][0] = p;\
    تيندنن[0][1] = (p)+(اڠک)-1;\
    طالما(sp){\
        type *start= تيندنن[--sp][0];\
        type *end  = تيندنن[  sp][1];\
        طالما(start < end){\
            إذا(start < end-1) {\
                صحيح checksort=0;\
                type *کانن = end-2;\
                type *کيري  = start+1;\
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
                طالما(کيري <= کانن){\
                    طالما(کيري<=کانن && cmp(کيري, end-1) < 0)\
                        کيري++;\
                    طالما(کيري<=کانن && cmp(کانن, end-1) > 0)\
                        کانن--;\
                    إذا(کيري <= کانن){\
                        FFSWAP(type, *کيري, *کانن);\
                        کيري++;\
                        کانن--;\
                    }\
                }\
                FFSWAP(type, end[-1], *کيري);\
                إذا(checksort && (mid == کيري-1 || mid == کيري)){\
                    mid= start;\
                    طالما(mid<end && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    إذا(mid==end)\
                        اكسر;\
                }\
                إذا(end-کيري < کيري-start){\
                    تيندنن[sp  ][0]= start;\
                    تيندنن[sp++][1]= کانن;\
                    start = کيري+1;\
                }وإلا{\
                    تيندنن[sp  ][0]= کيري+1;\
                    تيندنن[sp++][1]= end;\
                    end = کانن;\
                }\
            }وإلا{\
                إذا(cmp(start, end) > 0)\
                    FFSWAP(type, *start, *end);\
                اكسر;\
            }\
        }\
    }\
} طالما (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#define AV_MSORT(p, tmp, اڠک, type, cmp) افعل {\
    unsigned i, j, step;\
    لكل(step=1; step<(اڠک); step+=step){\
        لكل(i=0; i<(اڠک); i+=2*step){\
            unsigned a[2] = {i, i+step};\
            unsigned end = FFMIN(i+2*step, (اڠک));\
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
} طالما (0)

#endif /* AVUTIL_QSORT_H */
