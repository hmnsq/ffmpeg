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
#define AV_QSORT(p, अङ्कः, type, cmp) करेहि {\
    शून्य *राशिः[64][2];\
    पूर्णाङ्क sp= 1;\
    राशिः[0][0] = p;\
    राशिः[0][1] = (p)+(अङ्कः)-1;\
    जाव(sp){\
        type *start= राशिः[--sp][0];\
        type *end  = राशिः[  sp][1];\
        जाव(start < end){\
            जइ(start < end-1) {\
                पूर्णाङ्क checksort=0;\
                type *दक्षिणः = end-2;\
                type *वामः  = start+1;\
                type *mid = start + ((end-start)>>1);\
                जइ(cmp(start, end) > 0) {\
                    जइ(cmp(  end, mid) > 0) FFSWAP(type, *start, *mid);\
                    अण्णहा                    FFSWAP(type, *start, *end);\
                }अण्णहा{\
                    जइ(cmp(start, mid) > 0) FFSWAP(type, *start, *mid);\
                    अण्णहा checksort= 1;\
                }\
                जइ(cmp(mid, end) > 0){ \
                    FFSWAP(type, *mid, *end);\
                    checksort=0;\
                }\
                जइ(start == end-2) भङ्ग;\
                FFSWAP(type, end[-1], *mid);\
                जाव(वामः <= दक्षिणः){\
                    जाव(वामः<=दक्षिणः && cmp(वामः, end-1) < 0)\
                        वामः++;\
                    जाव(वामः<=दक्षिणः && cmp(दक्षिणः, end-1) > 0)\
                        दक्षिणः--;\
                    जइ(वामः <= दक्षिणः){\
                        FFSWAP(type, *वामः, *दक्षिणः);\
                        वामः++;\
                        दक्षिणः--;\
                    }\
                }\
                FFSWAP(type, end[-1], *वामः);\
                जइ(checksort && (mid == वामः-1 || mid == वामः)){\
                    mid= start;\
                    जाव(mid<end && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    जइ(mid==end)\
                        भङ्ग;\
                }\
                जइ(end-वामः < वामः-start){\
                    राशिः[sp  ][0]= start;\
                    राशिः[sp++][1]= दक्षिणः;\
                    start = वामः+1;\
                }अण्णहा{\
                    राशिः[sp  ][0]= वामः+1;\
                    राशिः[sp++][1]= end;\
                    end = दक्षिणः;\
                }\
            }अण्णहा{\
                जइ(cmp(start, end) > 0)\
                    FFSWAP(type, *start, *end);\
                भङ्ग;\
            }\
        }\
    }\
} जाव (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#define AV_MSORT(p, tmp, अङ्कः, type, cmp) करेहि {\
    unsigned i, j, step;\
    प्रति(step=1; step<(अङ्कः); step+=step){\
        प्रति(i=0; i<(अङ्कः); i+=2*step){\
            unsigned a[2] = {i, i+step};\
            unsigned end = FFMIN(i+2*step, (अङ्कः));\
            प्रति(j=i; a[0]<i+step && a[1]<end; j++){\
                पूर्णाङ्क idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            जइ(a[0]>=i+step) a[0] = a[1];\
            प्रति(; j<end; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} जाव (0)

#endif /* AVUTIL_QSORT_H */
