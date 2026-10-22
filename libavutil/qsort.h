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

#अगर_अघोषित AVUTIL_QSORT_H
#घोषणा AVUTIL_QSORT_H

#समावेश "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#घोषणा AV_QSORT(p, अंक, type, cmp) करो {\
    व्योम *ढेर_2[64][2];\
    पूर्णांक sp= 1;\
    ढेर_2[0][0] = p;\
    ढेर_2[0][1] = (p)+(अंक)-1;\
    जबतक(sp){\
        type *start= ढेर_2[--sp][0];\
        type *end  = ढेर_2[  sp][1];\
        जबतक(start < end){\
            अगर(start < end-1) {\
                पूर्णांक checksort=0;\
                type *दायाँ = end-2;\
                type *बायाँ  = start+1;\
                type *mid = start + ((end-start)>>1);\
                अगर(cmp(start, end) > 0) {\
                    अगर(cmp(  end, mid) > 0) FFSWAP(type, *start, *mid);\
                    अन्यथा                    FFSWAP(type, *start, *end);\
                }अन्यथा{\
                    अगर(cmp(start, mid) > 0) FFSWAP(type, *start, *mid);\
                    अन्यथा checksort= 1;\
                }\
                अगर(cmp(mid, end) > 0){ \
                    FFSWAP(type, *mid, *end);\
                    checksort=0;\
                }\
                अगर(start == end-2) अवरोध;\
                FFSWAP(type, end[-1], *mid);\
                जबतक(बायाँ <= दायाँ){\
                    जबतक(बायाँ<=दायाँ && cmp(बायाँ, end-1) < 0)\
                        बायाँ++;\
                    जबतक(बायाँ<=दायाँ && cmp(दायाँ, end-1) > 0)\
                        दायाँ--;\
                    अगर(बायाँ <= दायाँ){\
                        FFSWAP(type, *बायाँ, *दायाँ);\
                        बायाँ++;\
                        दायाँ--;\
                    }\
                }\
                FFSWAP(type, end[-1], *बायाँ);\
                अगर(checksort && (mid == बायाँ-1 || mid == बायाँ)){\
                    mid= start;\
                    जबतक(mid<end && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    अगर(mid==end)\
                        अवरोध;\
                }\
                अगर(end-बायाँ < बायाँ-start){\
                    ढेर_2[sp  ][0]= start;\
                    ढेर_2[sp++][1]= दायाँ;\
                    start = बायाँ+1;\
                }अन्यथा{\
                    ढेर_2[sp  ][0]= बायाँ+1;\
                    ढेर_2[sp++][1]= end;\
                    end = दायाँ;\
                }\
            }अन्यथा{\
                अगर(cmp(start, end) > 0)\
                    FFSWAP(type, *start, *end);\
                अवरोध;\
            }\
        }\
    }\
} जबतक (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#घोषणा AV_MSORT(p, tmp, अंक, type, cmp) करो {\
    अचिन्हित i, j, step;\
    क्रम(step=1; step<(अंक); step+=step){\
        क्रम(i=0; i<(अंक); i+=2*step){\
            अचिन्हित a[2] = {i, i+step};\
            अचिन्हित end = FFMIN(i+2*step, (अंक));\
            क्रम(j=i; a[0]<i+step && a[1]<end; j++){\
                पूर्णांक idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            अगर(a[0]>=i+step) a[0] = a[1];\
            क्रम(; j<end; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} जबतक (0)

#पूर्ण_अगर /* AVUTIL_QSORT_H */
