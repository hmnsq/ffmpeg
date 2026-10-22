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

#اگر_غیر_تعریف_شدہ AVUTIL_QSORT_H
#تعریف_کرو AVUTIL_QSORT_H

#شامل "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#تعریف_کرو AV_QSORT(p, عدد, type, cmp) کرو {\
    خالی *ڈھیر_2[64][2];\
    صحیح sp= 1;\
    ڈھیر_2[0][0] = p;\
    ڈھیر_2[0][1] = (p)+(عدد)-1;\
    جب(sp){\
        type *آغاز= ڈھیر_2[--sp][0];\
        type *انتہا  = ڈھیر_2[  sp][1];\
        جب(آغاز < انتہا){\
            اگر(آغاز < انتہا-1) {\
                صحیح checksort=0;\
                type *دایاں = انتہا-2;\
                type *بایاں  = آغاز+1;\
                type *mid = آغاز + ((انتہا-آغاز)>>1);\
                اگر(cmp(آغاز, انتہا) > 0) {\
                    اگر(cmp(  انتہا, mid) > 0) FFSWAP(type, *آغاز, *mid);\
                    ورنہ                    FFSWAP(type, *آغاز, *انتہا);\
                }ورنہ{\
                    اگر(cmp(آغاز, mid) > 0) FFSWAP(type, *آغاز, *mid);\
                    ورنہ checksort= 1;\
                }\
                اگر(cmp(mid, انتہا) > 0){ \
                    FFSWAP(type, *mid, *انتہا);\
                    checksort=0;\
                }\
                اگر(آغاز == انتہا-2) توڑو;\
                FFSWAP(type, انتہا[-1], *mid);\
                جب(بایاں <= دایاں){\
                    جب(بایاں<=دایاں && cmp(بایاں, انتہا-1) < 0)\
                        بایاں++;\
                    جب(بایاں<=دایاں && cmp(دایاں, انتہا-1) > 0)\
                        دایاں--;\
                    اگر(بایاں <= دایاں){\
                        FFSWAP(type, *بایاں, *دایاں);\
                        بایاں++;\
                        دایاں--;\
                    }\
                }\
                FFSWAP(type, انتہا[-1], *بایاں);\
                اگر(checksort && (mid == بایاں-1 || mid == بایاں)){\
                    mid= آغاز;\
                    جب(mid<انتہا && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    اگر(mid==انتہا)\
                        توڑو;\
                }\
                اگر(انتہا-بایاں < بایاں-آغاز){\
                    ڈھیر_2[sp  ][0]= آغاز;\
                    ڈھیر_2[sp++][1]= دایاں;\
                    آغاز = بایاں+1;\
                }ورنہ{\
                    ڈھیر_2[sp  ][0]= بایاں+1;\
                    ڈھیر_2[sp++][1]= انتہا;\
                    انتہا = دایاں;\
                }\
            }ورنہ{\
                اگر(cmp(آغاز, انتہا) > 0)\
                    FFSWAP(type, *آغاز, *انتہا);\
                توڑو;\
            }\
        }\
    }\
} جب (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#تعریف_کرو AV_MSORT(p, tmp, عدد, type, cmp) کرو {\
    غیرعلامتی i, j, قدم;\
    برائے(قدم=1; قدم<(عدد); قدم+=قدم){\
        برائے(i=0; i<(عدد); i+=2*قدم){\
            غیرعلامتی a[2] = {i, i+قدم};\
            غیرعلامتی انتہا = FFMIN(i+2*قدم, (عدد));\
            برائے(j=i; a[0]<i+قدم && a[1]<انتہا; j++){\
                صحیح idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            اگر(a[0]>=i+قدم) a[0] = a[1];\
            برائے(; j<انتہا; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} جب (0)

#اگر_ختم /* AVUTIL_QSORT_H */
