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

#ଅନ୍ତର୍ଭାଵ "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#define AV_QSORT(p, ଅଙ୍କ, type, cmp) କର {\
    ଶୂନ୍ୟ *ଗଦା[64][2];\
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା sp= 1;\
    ଗଦା[0][0] = p;\
    ଗଦା[0][1] = (p)+(ଅଙ୍କ)-1;\
    ଯେତେବେଳେ(sp){\
        type *start= ଗଦା[--sp][0];\
        type *end  = ଗଦା[  sp][1];\
        ଯେତେବେଳେ(start < end){\
            ଯଦି(start < end-1) {\
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା checksort=0;\
                type *ଡାହାଣ = end-2;\
                type *ବାମ  = start+1;\
                type *mid = start + ((end-start)>>1);\
                ଯଦି(cmp(start, end) > 0) {\
                    ଯଦି(cmp(  end, mid) > 0) FFSWAP(type, *start, *mid);\
                    ଅନ୍ୟଥା                    FFSWAP(type, *start, *end);\
                }ଅନ୍ୟଥା{\
                    ଯଦି(cmp(start, mid) > 0) FFSWAP(type, *start, *mid);\
                    ଅନ୍ୟଥା checksort= 1;\
                }\
                ଯଦି(cmp(mid, end) > 0){ \
                    FFSWAP(type, *mid, *end);\
                    checksort=0;\
                }\
                ଯଦି(start == end-2) ଭାଙ୍ଗ;\
                FFSWAP(type, end[-1], *mid);\
                ଯେତେବେଳେ(ବାମ <= ଡାହାଣ){\
                    ଯେତେବେଳେ(ବାମ<=ଡାହାଣ && cmp(ବାମ, end-1) < 0)\
                        ବାମ++;\
                    ଯେତେବେଳେ(ବାମ<=ଡାହାଣ && cmp(ଡାହାଣ, end-1) > 0)\
                        ଡାହାଣ--;\
                    ଯଦି(ବାମ <= ଡାହାଣ){\
                        FFSWAP(type, *ବାମ, *ଡାହାଣ);\
                        ବାମ++;\
                        ଡାହାଣ--;\
                    }\
                }\
                FFSWAP(type, end[-1], *ବାମ);\
                ଯଦି(checksort && (mid == ବାମ-1 || mid == ବାମ)){\
                    mid= start;\
                    ଯେତେବେଳେ(mid<end && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    ଯଦି(mid==end)\
                        ଭାଙ୍ଗ;\
                }\
                ଯଦି(end-ବାମ < ବାମ-start){\
                    ଗଦା[sp  ][0]= start;\
                    ଗଦା[sp++][1]= ଡାହାଣ;\
                    start = ବାମ+1;\
                }ଅନ୍ୟଥା{\
                    ଗଦା[sp  ][0]= ବାମ+1;\
                    ଗଦା[sp++][1]= end;\
                    end = ଡାହାଣ;\
                }\
            }ଅନ୍ୟଥା{\
                ଯଦି(cmp(start, end) > 0)\
                    FFSWAP(type, *start, *end);\
                ଭାଙ୍ଗ;\
            }\
        }\
    }\
} ଯେତେବେଳେ (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#define AV_MSORT(p, tmp, ଅଙ୍କ, type, cmp) କର {\
    unsigned i, j, step;\
    ପାଇଁ(step=1; step<(ଅଙ୍କ); step+=step){\
        ପାଇଁ(i=0; i<(ଅଙ୍କ); i+=2*step){\
            unsigned a[2] = {i, i+step};\
            unsigned end = FFMIN(i+2*step, (ଅଙ୍କ));\
            ପାଇଁ(j=i; a[0]<i+step && a[1]<end; j++){\
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            ଯଦି(a[0]>=i+step) a[0] = a[1];\
            ପାଇଁ(; j<end; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} ଯେତେବେଳେ (0)

#endif /* AVUTIL_QSORT_H */
