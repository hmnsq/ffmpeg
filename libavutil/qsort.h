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

#यदि_अपरिभाषितम् AVUTIL_QSORT_H
#परिभाषय AVUTIL_QSORT_H

#अन्तर्भाव "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#परिभाषय AV_QSORT(p, अङ्कः, type, cmp) कुरु {\
    शून्य *राशिः[64][2];\
    पूर्णाङ्क sp= 1;\
    राशिः[0][0] = p;\
    राशिः[0][1] = (p)+(अङ्कः)-1;\
    यावत्(sp){\
        type *start= राशिः[--sp][0];\
        type *अन्तः_2  = राशिः[  sp][1];\
        यावत्(start < अन्तः_2){\
            यदि(start < अन्तः_2-1) {\
                पूर्णाङ्क checksort=0;\
                type *दक्षिणः = अन्तः_2-2;\
                type *वामः  = start+1;\
                type *mid = start + ((अन्तः_2-start)>>1);\
                यदि(cmp(start, अन्तः_2) > 0) {\
                    यदि(cmp(  अन्तः_2, mid) > 0) FFSWAP(type, *start, *mid);\
                    अन्यथा                    FFSWAP(type, *start, *अन्तः_2);\
                }अन्यथा{\
                    यदि(cmp(start, mid) > 0) FFSWAP(type, *start, *mid);\
                    अन्यथा checksort= 1;\
                }\
                यदि(cmp(mid, अन्तः_2) > 0){ \
                    FFSWAP(type, *mid, *अन्तः_2);\
                    checksort=0;\
                }\
                यदि(start == अन्तः_2-2) भङ्ग;\
                FFSWAP(type, अन्तः_2[-1], *mid);\
                यावत्(वामः <= दक्षिणः){\
                    यावत्(वामः<=दक्षिणः && cmp(वामः, अन्तः_2-1) < 0)\
                        वामः++;\
                    यावत्(वामः<=दक्षिणः && cmp(दक्षिणः, अन्तः_2-1) > 0)\
                        दक्षिणः--;\
                    यदि(वामः <= दक्षिणः){\
                        FFSWAP(type, *वामः, *दक्षिणः);\
                        वामः++;\
                        दक्षिणः--;\
                    }\
                }\
                FFSWAP(type, अन्तः_2[-1], *वामः);\
                यदि(checksort && (mid == वामः-1 || mid == वामः)){\
                    mid= start;\
                    यावत्(mid<अन्तः_2 && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    यदि(mid==अन्तः_2)\
                        भङ्ग;\
                }\
                यदि(अन्तः_2-वामः < वामः-start){\
                    राशिः[sp  ][0]= start;\
                    राशिः[sp++][1]= दक्षिणः;\
                    start = वामः+1;\
                }अन्यथा{\
                    राशिः[sp  ][0]= वामः+1;\
                    राशिः[sp++][1]= अन्तः_2;\
                    अन्तः_2 = दक्षिणः;\
                }\
            }अन्यथा{\
                यदि(cmp(start, अन्तः_2) > 0)\
                    FFSWAP(type, *start, *अन्तः_2);\
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
#परिभाषय AV_MSORT(p, tmp, अङ्कः, type, cmp) कुरु {\
    अचिह्नित i, j, चरणः;\
    प्रति(चरणः=1; चरणः<(अङ्कः); चरणः+=चरणः){\
        प्रति(i=0; i<(अङ्कः); i+=2*चरणः){\
            अचिह्नित a[2] = {i, i+चरणः};\
            अचिह्नित अन्तः_2 = FFMIN(i+2*चरणः, (अङ्कः));\
            प्रति(j=i; a[0]<i+चरणः && a[1]<अन्तः_2; j++){\
                पूर्णाङ्क idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            यदि(a[0]>=i+चरणः) a[0] = a[1];\
            प्रति(; j<अन्तः_2; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} यावत् (0)

#यदि_अन्तः /* AVUTIL_QSORT_H */
