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

#अन्तर्भाव "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#define AV_QSORT(p, अंक, type, cmp) कुरु {\
    शून्य *ढेर[64][2];\
    पूर्णाङ्क sp= 1;\
    ढेर[0][0] = p;\
    ढेर[0][1] = (p)+(अंक)-1;\
    यावत्(sp){\
        type *start= ढेर[--sp][0];\
        type *end  = ढेर[  sp][1];\
        यावत्(start < end){\
            यदि(start < end-1) {\
                पूर्णाङ्क checksort=0;\
                type *दायाँ = end-2;\
                type *बायाँ  = start+1;\
                type *mid = start + ((end-start)>>1);\
                यदि(cmp(start, end) > 0) {\
                    यदि(cmp(  end, mid) > 0) FFSWAP(type, *start, *mid);\
                    अन्यथा                    FFSWAP(type, *start, *end);\
                }अन्यथा{\
                    यदि(cmp(start, mid) > 0) FFSWAP(type, *start, *mid);\
                    अन्यथा checksort= 1;\
                }\
                यदि(cmp(mid, end) > 0){ \
                    FFSWAP(type, *mid, *end);\
                    checksort=0;\
                }\
                यदि(start == end-2) भङ्ग;\
                FFSWAP(type, end[-1], *mid);\
                यावत्(बायाँ <= दायाँ){\
                    यावत्(बायाँ<=दायाँ && cmp(बायाँ, end-1) < 0)\
                        बायाँ++;\
                    यावत्(बायाँ<=दायाँ && cmp(दायाँ, end-1) > 0)\
                        दायाँ--;\
                    यदि(बायाँ <= दायाँ){\
                        FFSWAP(type, *बायाँ, *दायाँ);\
                        बायाँ++;\
                        दायाँ--;\
                    }\
                }\
                FFSWAP(type, end[-1], *बायाँ);\
                यदि(checksort && (mid == बायाँ-1 || mid == बायाँ)){\
                    mid= start;\
                    यावत्(mid<end && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    यदि(mid==end)\
                        भङ्ग;\
                }\
                यदि(end-बायाँ < बायाँ-start){\
                    ढेर[sp  ][0]= start;\
                    ढेर[sp++][1]= दायाँ;\
                    start = बायाँ+1;\
                }अन्यथा{\
                    ढेर[sp  ][0]= बायाँ+1;\
                    ढेर[sp++][1]= end;\
                    end = दायाँ;\
                }\
            }अन्यथा{\
                यदि(cmp(start, end) > 0)\
                    FFSWAP(type, *start, *end);\
                भङ्ग;\
            }\
        }\
    }\
} यावत् (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#define AV_MSORT(p, tmp, अंक, type, cmp) कुरु {\
    unsigned i, j, step;\
    प्रति(step=1; step<(अंक); step+=step){\
        प्रति(i=0; i<(अंक); i+=2*step){\
            unsigned a[2] = {i, i+step};\
            unsigned end = FFMIN(i+2*step, (अंक));\
            प्रति(j=i; a[0]<i+step && a[1]<end; j++){\
                पूर्णाङ्क idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            यदि(a[0]>=i+step) a[0] = a[1];\
            प्रति(; j<end; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} यावत् (0)

#endif /* AVUTIL_QSORT_H */
