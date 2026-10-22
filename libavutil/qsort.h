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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_QSORT_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_QSORT_H

#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_QSORT(p, ਅੰਕ, type, cmp) ਕਰੋ {\
    ਖਾਲੀ *ਢੇਰ_2[64][2];\
    ਪੂਰਨ sp= 1;\
    ਢੇਰ_2[0][0] = p;\
    ਢੇਰ_2[0][1] = (p)+(ਅੰਕ)-1;\
    ਜਦੋਂ(sp){\
        type *ਸ਼ੁਰੂ= ਢੇਰ_2[--sp][0];\
        type *ਸਿਰਾ  = ਢੇਰ_2[  sp][1];\
        ਜਦੋਂ(ਸ਼ੁਰੂ < ਸਿਰਾ){\
            ਜੇ(ਸ਼ੁਰੂ < ਸਿਰਾ-1) {\
                ਪੂਰਨ checksort=0;\
                type *ਸੱਜਾ = ਸਿਰਾ-2;\
                type *ਖੱਬਾ  = ਸ਼ੁਰੂ+1;\
                type *mid = ਸ਼ੁਰੂ + ((ਸਿਰਾ-ਸ਼ੁਰੂ)>>1);\
                ਜੇ(cmp(ਸ਼ੁਰੂ, ਸਿਰਾ) > 0) {\
                    ਜੇ(cmp(  ਸਿਰਾ, mid) > 0) FFSWAP(type, *ਸ਼ੁਰੂ, *mid);\
                    ਨਹੀਂਤਾਂ                    FFSWAP(type, *ਸ਼ੁਰੂ, *ਸਿਰਾ);\
                }ਨਹੀਂਤਾਂ{\
                    ਜੇ(cmp(ਸ਼ੁਰੂ, mid) > 0) FFSWAP(type, *ਸ਼ੁਰੂ, *mid);\
                    ਨਹੀਂਤਾਂ checksort= 1;\
                }\
                ਜੇ(cmp(mid, ਸਿਰਾ) > 0){ \
                    FFSWAP(type, *mid, *ਸਿਰਾ);\
                    checksort=0;\
                }\
                ਜੇ(ਸ਼ੁਰੂ == ਸਿਰਾ-2) ਰੋਕੋ;\
                FFSWAP(type, ਸਿਰਾ[-1], *mid);\
                ਜਦੋਂ(ਖੱਬਾ <= ਸੱਜਾ){\
                    ਜਦੋਂ(ਖੱਬਾ<=ਸੱਜਾ && cmp(ਖੱਬਾ, ਸਿਰਾ-1) < 0)\
                        ਖੱਬਾ++;\
                    ਜਦੋਂ(ਖੱਬਾ<=ਸੱਜਾ && cmp(ਸੱਜਾ, ਸਿਰਾ-1) > 0)\
                        ਸੱਜਾ--;\
                    ਜੇ(ਖੱਬਾ <= ਸੱਜਾ){\
                        FFSWAP(type, *ਖੱਬਾ, *ਸੱਜਾ);\
                        ਖੱਬਾ++;\
                        ਸੱਜਾ--;\
                    }\
                }\
                FFSWAP(type, ਸਿਰਾ[-1], *ਖੱਬਾ);\
                ਜੇ(checksort && (mid == ਖੱਬਾ-1 || mid == ਖੱਬਾ)){\
                    mid= ਸ਼ੁਰੂ;\
                    ਜਦੋਂ(mid<ਸਿਰਾ && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    ਜੇ(mid==ਸਿਰਾ)\
                        ਰੋਕੋ;\
                }\
                ਜੇ(ਸਿਰਾ-ਖੱਬਾ < ਖੱਬਾ-ਸ਼ੁਰੂ){\
                    ਢੇਰ_2[sp  ][0]= ਸ਼ੁਰੂ;\
                    ਢੇਰ_2[sp++][1]= ਸੱਜਾ;\
                    ਸ਼ੁਰੂ = ਖੱਬਾ+1;\
                }ਨਹੀਂਤਾਂ{\
                    ਢੇਰ_2[sp  ][0]= ਖੱਬਾ+1;\
                    ਢੇਰ_2[sp++][1]= ਸਿਰਾ;\
                    ਸਿਰਾ = ਸੱਜਾ;\
                }\
            }ਨਹੀਂਤਾਂ{\
                ਜੇ(cmp(ਸ਼ੁਰੂ, ਸਿਰਾ) > 0)\
                    FFSWAP(type, *ਸ਼ੁਰੂ, *ਸਿਰਾ);\
                ਰੋਕੋ;\
            }\
        }\
    }\
} ਜਦੋਂ (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_MSORT(p, tmp, ਅੰਕ, type, cmp) ਕਰੋ {\
    ਬਿਨਾਨਿਸ਼ਾਨੀ i, j, ਕਦਮ;\
    ਲਈ(ਕਦਮ=1; ਕਦਮ<(ਅੰਕ); ਕਦਮ+=ਕਦਮ){\
        ਲਈ(i=0; i<(ਅੰਕ); i+=2*ਕਦਮ){\
            ਬਿਨਾਨਿਸ਼ਾਨੀ a[2] = {i, i+ਕਦਮ};\
            ਬਿਨਾਨਿਸ਼ਾਨੀ ਸਿਰਾ = FFMIN(i+2*ਕਦਮ, (ਅੰਕ));\
            ਲਈ(j=i; a[0]<i+ਕਦਮ && a[1]<ਸਿਰਾ; j++){\
                ਪੂਰਨ idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            ਜੇ(a[0]>=i+ਕਦਮ) a[0] = a[1];\
            ਲਈ(; j<ਸਿਰਾ; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} ਜਦੋਂ (0)

#ਜੇ_ਅੰਤ /* AVUTIL_QSORT_H */
