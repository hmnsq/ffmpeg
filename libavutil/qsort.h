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
    ཧྲིལ sp= 1;\
    stack[0][0] = p;\
    stack[0][1] = (p)+(num)-1;\
    སྐབས(sp){\
        type *start= stack[--sp][0];\
        type *end  = stack[  sp][1];\
        སྐབས(start < end){\
            གལ་སྲིད(start < end-1) {\
                ཧྲིལ checksort=0;\
                type *right = end-2;\
                type *left  = start+1;\
                type *mid = start + ((end-start)>>1);\
                གལ་སྲིད(cmp(start, end) > 0) {\
                    གལ་སྲིད(cmp(  end, mid) > 0) FFSWAP(type, *start, *mid);\
                    དེ་མིན                    FFSWAP(type, *start, *end);\
                }དེ་མིན{\
                    གལ་སྲིད(cmp(start, mid) > 0) FFSWAP(type, *start, *mid);\
                    དེ་མིན checksort= 1;\
                }\
                གལ་སྲིད(cmp(mid, end) > 0){ \
                    FFSWAP(type, *mid, *end);\
                    checksort=0;\
                }\
                གལ་སྲིད(start == end-2) bha_nga;\
                FFSWAP(type, end[-1], *mid);\
                སྐབས(left <= right){\
                    སྐབས(left<=right && cmp(left, end-1) < 0)\
                        left++;\
                    སྐབས(left<=right && cmp(right, end-1) > 0)\
                        right--;\
                    གལ་སྲིད(left <= right){\
                        FFSWAP(type, *left, *right);\
                        left++;\
                        right--;\
                    }\
                }\
                FFSWAP(type, end[-1], *left);\
                གལ་སྲིད(checksort && (mid == left-1 || mid == left)){\
                    mid= start;\
                    སྐབས(mid<end && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    གལ་སྲིད(mid==end)\
                        bha_nga;\
                }\
                གལ་སྲིད(end-left < left-start){\
                    stack[sp  ][0]= start;\
                    stack[sp++][1]= right;\
                    start = left+1;\
                }དེ་མིན{\
                    stack[sp  ][0]= left+1;\
                    stack[sp++][1]= end;\
                    end = right;\
                }\
            }དེ་མིན{\
                གལ་སྲིད(cmp(start, end) > 0)\
                    FFSWAP(type, *start, *end);\
                bha_nga;\
            }\
        }\
    }\
} སྐབས (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#define AV_MSORT(p, tmp, num, type, cmp) do {\
    unsigned i, j, step;\
    དོན་ལུ(step=1; step<(num); step+=step){\
        དོན་ལུ(i=0; i<(num); i+=2*step){\
            unsigned a[2] = {i, i+step};\
            unsigned end = FFMIN(i+2*step, (num));\
            དོན་ལུ(j=i; a[0]<i+step && a[1]<end; j++){\
                ཧྲིལ idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            གལ་སྲིད(a[0]>=i+step) a[0] = a[1];\
            དོན་ལུ(; j<end; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} སྐབས (0)

#endif /* AVUTIL_QSORT_H */
