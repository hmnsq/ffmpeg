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

#ಅನ್ತರ್ಭಾವ "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#define AV_QSORT(p, ಅಂಕೆ, type, cmp) ಕುರು {\
    ಶೂನ್ಯ *ರಾಶಿ[64][2];\
    ಪೂರ್ಣಾಙ್ಕ sp= 1;\
    ರಾಶಿ[0][0] = p;\
    ರಾಶಿ[0][1] = (p)+(ಅಂಕೆ)-1;\
    ಯಾವತ್(sp){\
        type *start= ರಾಶಿ[--sp][0];\
        type *end  = ರಾಶಿ[  sp][1];\
        ಯಾವತ್(start < end){\
            ಯದಿ(start < end-1) {\
                ಪೂರ್ಣಾಙ್ಕ checksort=0;\
                type *ಬಲ = end-2;\
                type *ಎಡ  = start+1;\
                type *mid = start + ((end-start)>>1);\
                ಯದಿ(cmp(start, end) > 0) {\
                    ಯದಿ(cmp(  end, mid) > 0) FFSWAP(type, *start, *mid);\
                    ಅನ್ಯಥಾ                    FFSWAP(type, *start, *end);\
                }ಅನ್ಯಥಾ{\
                    ಯದಿ(cmp(start, mid) > 0) FFSWAP(type, *start, *mid);\
                    ಅನ್ಯಥಾ checksort= 1;\
                }\
                ಯದಿ(cmp(mid, end) > 0){ \
                    FFSWAP(type, *mid, *end);\
                    checksort=0;\
                }\
                ಯದಿ(start == end-2) ಭಙ್ಗ;\
                FFSWAP(type, end[-1], *mid);\
                ಯಾವತ್(ಎಡ <= ಬಲ){\
                    ಯಾವತ್(ಎಡ<=ಬಲ && cmp(ಎಡ, end-1) < 0)\
                        ಎಡ++;\
                    ಯಾವತ್(ಎಡ<=ಬಲ && cmp(ಬಲ, end-1) > 0)\
                        ಬಲ--;\
                    ಯದಿ(ಎಡ <= ಬಲ){\
                        FFSWAP(type, *ಎಡ, *ಬಲ);\
                        ಎಡ++;\
                        ಬಲ--;\
                    }\
                }\
                FFSWAP(type, end[-1], *ಎಡ);\
                ಯದಿ(checksort && (mid == ಎಡ-1 || mid == ಎಡ)){\
                    mid= start;\
                    ಯಾವತ್(mid<end && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    ಯದಿ(mid==end)\
                        ಭಙ್ಗ;\
                }\
                ಯದಿ(end-ಎಡ < ಎಡ-start){\
                    ರಾಶಿ[sp  ][0]= start;\
                    ರಾಶಿ[sp++][1]= ಬಲ;\
                    start = ಎಡ+1;\
                }ಅನ್ಯಥಾ{\
                    ರಾಶಿ[sp  ][0]= ಎಡ+1;\
                    ರಾಶಿ[sp++][1]= end;\
                    end = ಬಲ;\
                }\
            }ಅನ್ಯಥಾ{\
                ಯದಿ(cmp(start, end) > 0)\
                    FFSWAP(type, *start, *end);\
                ಭಙ್ಗ;\
            }\
        }\
    }\
} ಯಾವತ್ (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#define AV_MSORT(p, tmp, ಅಂಕೆ, type, cmp) ಕುರು {\
    unsigned i, j, step;\
    ಪ್ರತಿ(step=1; step<(ಅಂಕೆ); step+=step){\
        ಪ್ರತಿ(i=0; i<(ಅಂಕೆ); i+=2*step){\
            unsigned a[2] = {i, i+step};\
            unsigned end = FFMIN(i+2*step, (ಅಂಕೆ));\
            ಪ್ರತಿ(j=i; a[0]<i+step && a[1]<end; j++){\
                ಪೂರ್ಣಾಙ್ಕ idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            ಯದಿ(a[0]>=i+step) a[0] = a[1];\
            ಪ್ರತಿ(; j<end; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} ಯಾವತ್ (0)

#endif /* AVUTIL_QSORT_H */
