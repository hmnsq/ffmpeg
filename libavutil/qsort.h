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
    puur_naa_nka sp= 1;\
    stack[0][0] = p;\
    stack[0][1] = (p)+(num)-1;\
    ᬲᭂᬤᭂᬮ(sp){\
        type *start= stack[--sp][0];\
        type *end  = stack[  sp][1];\
        ᬲᭂᬤᭂᬮ(start < end){\
            ᬬᬾᬦ᭄(start < end-1) {\
                puur_naa_nka checksort=0;\
                type *right = end-2;\
                type *left  = start+1;\
                type *mid = start + ((end-start)>>1);\
                ᬬᬾᬦ᭄(cmp(start, end) > 0) {\
                    ᬬᬾᬦ᭄(cmp(  end, mid) > 0) FFSWAP(type, *start, *mid);\
                    ᬮᬶᬬ                    FFSWAP(type, *start, *end);\
                }ᬮᬶᬬ{\
                    ᬬᬾᬦ᭄(cmp(start, mid) > 0) FFSWAP(type, *start, *mid);\
                    ᬮᬶᬬ checksort= 1;\
                }\
                ᬬᬾᬦ᭄(cmp(mid, end) > 0){ \
                    FFSWAP(type, *mid, *end);\
                    checksort=0;\
                }\
                ᬬᬾᬦ᭄(start == end-2) bha_nga;\
                FFSWAP(type, end[-1], *mid);\
                ᬲᭂᬤᭂᬮ(left <= right){\
                    ᬲᭂᬤᭂᬮ(left<=right && cmp(left, end-1) < 0)\
                        left++;\
                    ᬲᭂᬤᭂᬮ(left<=right && cmp(right, end-1) > 0)\
                        right--;\
                    ᬬᬾᬦ᭄(left <= right){\
                        FFSWAP(type, *left, *right);\
                        left++;\
                        right--;\
                    }\
                }\
                FFSWAP(type, end[-1], *left);\
                ᬬᬾᬦ᭄(checksort && (mid == left-1 || mid == left)){\
                    mid= start;\
                    ᬲᭂᬤᭂᬮ(mid<end && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    ᬬᬾᬦ᭄(mid==end)\
                        bha_nga;\
                }\
                ᬬᬾᬦ᭄(end-left < left-start){\
                    stack[sp  ][0]= start;\
                    stack[sp++][1]= right;\
                    start = left+1;\
                }ᬮᬶᬬ{\
                    stack[sp  ][0]= left+1;\
                    stack[sp++][1]= end;\
                    end = right;\
                }\
            }ᬮᬶᬬ{\
                ᬬᬾᬦ᭄(cmp(start, end) > 0)\
                    FFSWAP(type, *start, *end);\
                bha_nga;\
            }\
        }\
    }\
} ᬲᭂᬤᭂᬮ (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#define AV_MSORT(p, tmp, num, type, cmp) do {\
    unsigned i, j, step;\
    for(step=1; step<(num); step+=step){\
        for(i=0; i<(num); i+=2*step){\
            unsigned a[2] = {i, i+step};\
            unsigned end = FFMIN(i+2*step, (num));\
            for(j=i; a[0]<i+step && a[1]<end; j++){\
                puur_naa_nka idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            ᬬᬾᬦ᭄(a[0]>=i+step) a[0] = a[1];\
            for(; j<end; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} ᬲᭂᬤᭂᬮ (0)

#endif /* AVUTIL_QSORT_H */
