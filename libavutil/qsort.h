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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_QSORT_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_QSORT_H

#ಅನ್ತರ್ಭಾವ "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_QSORT(p, ಅಂಕೆ, type, cmp) ಮಾಡು {\
    ಶೂನ್ಯ *ರಾಶಿ_2[64][2];\
    ಪೂರ್ಣಾಂಕ sp= 1;\
    ರಾಶಿ_2[0][0] = p;\
    ರಾಶಿ_2[0][1] = (p)+(ಅಂಕೆ)-1;\
    ಆಗ(sp){\
        type *ಆರಂಭ= ರಾಶಿ_2[--sp][0];\
        type *ಕೊನೆ  = ರಾಶಿ_2[  sp][1];\
        ಆಗ(ಆರಂಭ < ಕೊನೆ){\
            ಆದರೆ(ಆರಂಭ < ಕೊನೆ-1) {\
                ಪೂರ್ಣಾಂಕ checksort=0;\
                type *ಬಲ = ಕೊನೆ-2;\
                type *ಎಡ  = ಆರಂಭ+1;\
                type *mid = ಆರಂಭ + ((ಕೊನೆ-ಆರಂಭ)>>1);\
                ಆದರೆ(cmp(ಆರಂಭ, ಕೊನೆ) > 0) {\
                    ಆದರೆ(cmp(  ಕೊನೆ, mid) > 0) FFSWAP(type, *ಆರಂಭ, *mid);\
                    ಇಲ್ಲದಿದ್ದರೆ                    FFSWAP(type, *ಆರಂಭ, *ಕೊನೆ);\
                }ಇಲ್ಲದಿದ್ದರೆ{\
                    ಆದರೆ(cmp(ಆರಂಭ, mid) > 0) FFSWAP(type, *ಆರಂಭ, *mid);\
                    ಇಲ್ಲದಿದ್ದರೆ checksort= 1;\
                }\
                ಆದರೆ(cmp(mid, ಕೊನೆ) > 0){ \
                    FFSWAP(type, *mid, *ಕೊನೆ);\
                    checksort=0;\
                }\
                ಆದರೆ(ಆರಂಭ == ಕೊನೆ-2) ನಿಲ್ಲಿಸು;\
                FFSWAP(type, ಕೊನೆ[-1], *mid);\
                ಆಗ(ಎಡ <= ಬಲ){\
                    ಆಗ(ಎಡ<=ಬಲ && cmp(ಎಡ, ಕೊನೆ-1) < 0)\
                        ಎಡ++;\
                    ಆಗ(ಎಡ<=ಬಲ && cmp(ಬಲ, ಕೊನೆ-1) > 0)\
                        ಬಲ--;\
                    ಆದರೆ(ಎಡ <= ಬಲ){\
                        FFSWAP(type, *ಎಡ, *ಬಲ);\
                        ಎಡ++;\
                        ಬಲ--;\
                    }\
                }\
                FFSWAP(type, ಕೊನೆ[-1], *ಎಡ);\
                ಆದರೆ(checksort && (mid == ಎಡ-1 || mid == ಎಡ)){\
                    mid= ಆರಂಭ;\
                    ಆಗ(mid<ಕೊನೆ && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    ಆದರೆ(mid==ಕೊನೆ)\
                        ನಿಲ್ಲಿಸು;\
                }\
                ಆದರೆ(ಕೊನೆ-ಎಡ < ಎಡ-ಆರಂಭ){\
                    ರಾಶಿ_2[sp  ][0]= ಆರಂಭ;\
                    ರಾಶಿ_2[sp++][1]= ಬಲ;\
                    ಆರಂಭ = ಎಡ+1;\
                }ಇಲ್ಲದಿದ್ದರೆ{\
                    ರಾಶಿ_2[sp  ][0]= ಎಡ+1;\
                    ರಾಶಿ_2[sp++][1]= ಕೊನೆ;\
                    ಕೊನೆ = ಬಲ;\
                }\
            }ಇಲ್ಲದಿದ್ದರೆ{\
                ಆದರೆ(cmp(ಆರಂಭ, ಕೊನೆ) > 0)\
                    FFSWAP(type, *ಆರಂಭ, *ಕೊನೆ);\
                ನಿಲ್ಲಿಸು;\
            }\
        }\
    }\
} ಆಗ (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_MSORT(p, tmp, ಅಂಕೆ, type, cmp) ಮಾಡು {\
    ಚಿಹ್ನೆರಹಿತ i, j, ಹೆಜ್ಜೆ;\
    ಗಾಗಿ(ಹೆಜ್ಜೆ=1; ಹೆಜ್ಜೆ<(ಅಂಕೆ); ಹೆಜ್ಜೆ+=ಹೆಜ್ಜೆ){\
        ಗಾಗಿ(i=0; i<(ಅಂಕೆ); i+=2*ಹೆಜ್ಜೆ){\
            ಚಿಹ್ನೆರಹಿತ a[2] = {i, i+ಹೆಜ್ಜೆ};\
            ಚಿಹ್ನೆರಹಿತ ಕೊನೆ = FFMIN(i+2*ಹೆಜ್ಜೆ, (ಅಂಕೆ));\
            ಗಾಗಿ(j=i; a[0]<i+ಹೆಜ್ಜೆ && a[1]<ಕೊನೆ; j++){\
                ಪೂರ್ಣಾಂಕ idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            ಆದರೆ(a[0]>=i+ಹೆಜ್ಜೆ) a[0] = a[1];\
            ಗಾಗಿ(; j<ಕೊನೆ; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} ಆಗ (0)

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_QSORT_H */
