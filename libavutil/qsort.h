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
#define AV_QSORT(p, नुमेरो, type, cmp) do {\
    void *सालानसान[64][2];\
    int sp= 1;\
    सालानसान[0][0] = p;\
    सालानसान[0][1] = (p)+(नुमेरो)-1;\
    while(sp){\
        type *start= सालानसान[--sp][0];\
        type *end  = सालानसान[  sp][1];\
        while(start < end){\
            if(start < end-1) {\
                int checksort=0;\
                type *कानान = end-2;\
                type *कालिवा  = start+1;\
                type *mid = start + ((end-start)>>1);\
                if(cmp(start, end) > 0) {\
                    if(cmp(  end, mid) > 0) FFSWAP(type, *start, *mid);\
                    else                    FFSWAP(type, *start, *end);\
                }else{\
                    if(cmp(start, mid) > 0) FFSWAP(type, *start, *mid);\
                    else checksort= 1;\
                }\
                if(cmp(mid, end) > 0){ \
                    FFSWAP(type, *mid, *end);\
                    checksort=0;\
                }\
                if(start == end-2) break;\
                FFSWAP(type, end[-1], *mid);\
                while(कालिवा <= कानान){\
                    while(कालिवा<=कानान && cmp(कालिवा, end-1) < 0)\
                        कालिवा++;\
                    while(कालिवा<=कानान && cmp(कानान, end-1) > 0)\
                        कानान--;\
                    if(कालिवा <= कानान){\
                        FFSWAP(type, *कालिवा, *कानान);\
                        कालिवा++;\
                        कानान--;\
                    }\
                }\
                FFSWAP(type, end[-1], *कालिवा);\
                if(checksort && (mid == कालिवा-1 || mid == कालिवा)){\
                    mid= start;\
                    while(mid<end && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    if(mid==end)\
                        break;\
                }\
                if(end-कालिवा < कालिवा-start){\
                    सालानसान[sp  ][0]= start;\
                    सालानसान[sp++][1]= कानान;\
                    start = कालिवा+1;\
                }else{\
                    सालानसान[sp  ][0]= कालिवा+1;\
                    सालानसान[sp++][1]= end;\
                    end = कानान;\
                }\
            }else{\
                if(cmp(start, end) > 0)\
                    FFSWAP(type, *start, *end);\
                break;\
            }\
        }\
    }\
} while (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#define AV_MSORT(p, tmp, नुमेरो, type, cmp) do {\
    unsigned i, j, step;\
    for(step=1; step<(नुमेरो); step+=step){\
        for(i=0; i<(नुमेरो); i+=2*step){\
            unsigned a[2] = {i, i+step};\
            unsigned end = FFMIN(i+2*step, (नुमेरो));\
            for(j=i; a[0]<i+step && a[1]<end; j++){\
                int idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            if(a[0]>=i+step) a[0] = a[1];\
            for(; j<end; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} while (0)

#endif /* AVUTIL_QSORT_H */
