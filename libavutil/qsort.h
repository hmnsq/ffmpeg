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

#include "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#define AV_QSORT(p, num, type, cmp) do {\
    void *stack[64][2];\
    จำนวนเต็ม sp= 1;\
    stack[0][0] = p;\
    stack[0][1] = (p)+(num)-1;\
    ขณะ(sp){\
        type *start= stack[--sp][0];\
        type *end  = stack[  sp][1];\
        ขณะ(start < end){\
            ถ้า(start < end-1) {\
                จำนวนเต็ม checksort=0;\
                type *right = end-2;\
                type *left  = start+1;\
                type *mid = start + ((end-start)>>1);\
                ถ้า(cmp(start, end) > 0) {\
                    ถ้า(cmp(  end, mid) > 0) FFSWAP(type, *start, *mid);\
                    มิฉะนั้น                    FFSWAP(type, *start, *end);\
                }มิฉะนั้น{\
                    ถ้า(cmp(start, mid) > 0) FFSWAP(type, *start, *mid);\
                    มิฉะนั้น checksort= 1;\
                }\
                ถ้า(cmp(mid, end) > 0){ \
                    FFSWAP(type, *mid, *end);\
                    checksort=0;\
                }\
                ถ้า(start == end-2) bha_nga;\
                FFSWAP(type, end[-1], *mid);\
                ขณะ(left <= right){\
                    ขณะ(left<=right && cmp(left, end-1) < 0)\
                        left++;\
                    ขณะ(left<=right && cmp(right, end-1) > 0)\
                        right--;\
                    ถ้า(left <= right){\
                        FFSWAP(type, *left, *right);\
                        left++;\
                        right--;\
                    }\
                }\
                FFSWAP(type, end[-1], *left);\
                ถ้า(checksort && (mid == left-1 || mid == left)){\
                    mid= start;\
                    ขณะ(mid<end && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    ถ้า(mid==end)\
                        bha_nga;\
                }\
                ถ้า(end-left < left-start){\
                    stack[sp  ][0]= start;\
                    stack[sp++][1]= right;\
                    start = left+1;\
                }มิฉะนั้น{\
                    stack[sp  ][0]= left+1;\
                    stack[sp++][1]= end;\
                    end = right;\
                }\
            }มิฉะนั้น{\
                ถ้า(cmp(start, end) > 0)\
                    FFSWAP(type, *start, *end);\
                bha_nga;\
            }\
        }\
    }\
} ขณะ (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#define AV_MSORT(p, tmp, num, type, cmp) do {\
    unsigned i, j, step;\
    สำหรับ(step=1; step<(num); step+=step){\
        สำหรับ(i=0; i<(num); i+=2*step){\
            unsigned a[2] = {i, i+step};\
            unsigned end = FFMIN(i+2*step, (num));\
            สำหรับ(j=i; a[0]<i+step && a[1]<end; j++){\
                จำนวนเต็ม idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            ถ้า(a[0]>=i+step) a[0] = a[1];\
            สำหรับ(; j<end; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} ขณะ (0)

#endif /* AVUTIL_QSORT_H */
