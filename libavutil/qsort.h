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
#define AV_QSORT(p, num, type, cmp) 𐤐𐤏𐤋 {\
    فراغ *stack[64][2];\
    صحيح sp= 1;\
    stack[0][0] = p;\
    stack[0][1] = (p)+(num)-1;\
    طالما(sp){\
        type *start= stack[--sp][0];\
        type *end  = stack[  sp][1];\
        طالما(start < end){\
            𐤀𐤌(start < end-1) {\
                صحيح checksort=0;\
                type *right = end-2;\
                type *left  = start+1;\
                type *mid = start + ((end-start)>>1);\
                𐤀𐤌(cmp(start, end) > 0) {\
                    𐤀𐤌(cmp(  end, mid) > 0) FFSWAP(type, *start, *mid);\
                    وإلا                    FFSWAP(type, *start, *end);\
                }وإلا{\
                    𐤀𐤌(cmp(start, mid) > 0) FFSWAP(type, *start, *mid);\
                    وإلا checksort= 1;\
                }\
                𐤀𐤌(cmp(mid, end) > 0){ \
                    FFSWAP(type, *mid, *end);\
                    checksort=0;\
                }\
                𐤀𐤌(start == end-2) اكسر;\
                FFSWAP(type, end[-1], *mid);\
                طالما(left <= right){\
                    طالما(left<=right && cmp(left, end-1) < 0)\
                        left++;\
                    طالما(left<=right && cmp(right, end-1) > 0)\
                        right--;\
                    𐤀𐤌(left <= right){\
                        FFSWAP(type, *left, *right);\
                        left++;\
                        right--;\
                    }\
                }\
                FFSWAP(type, end[-1], *left);\
                𐤀𐤌(checksort && (mid == left-1 || mid == left)){\
                    mid= start;\
                    طالما(mid<end && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    𐤀𐤌(mid==end)\
                        اكسر;\
                }\
                𐤀𐤌(end-left < left-start){\
                    stack[sp  ][0]= start;\
                    stack[sp++][1]= right;\
                    start = left+1;\
                }وإلا{\
                    stack[sp  ][0]= left+1;\
                    stack[sp++][1]= end;\
                    end = right;\
                }\
            }وإلا{\
                𐤀𐤌(cmp(start, end) > 0)\
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
#define AV_MSORT(p, tmp, num, type, cmp) 𐤐𐤏𐤋 {\
    unsigned i, j, step;\
    لكل(step=1; step<(num); step+=step){\
        لكل(i=0; i<(num); i+=2*step){\
            unsigned a[2] = {i, i+step};\
            unsigned end = FFMIN(i+2*step, (num));\
            لكل(j=i; a[0]<i+step && a[1]<end; j++){\
                صحيح idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            𐤀𐤌(a[0]>=i+step) a[0] = a[1];\
            لكل(; j<end; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} طالما (0)

#endif /* AVUTIL_QSORT_H */
