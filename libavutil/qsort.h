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

#جے_بنا_تعریف AVUTIL_QSORT_H
#تعریف_کرو AVUTIL_QSORT_H

#ضمن "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#تعریف_کرو AV_QSORT(p, عدد, type, cmp) افعل {\
    فراغ *ڈھیر_2[64][2];\
    صحيح sp= 1;\
    ڈھیر_2[0][0] = p;\
    ڈھیر_2[0][1] = (p)+(عدد)-1;\
    طالما(sp){\
        type *شروع= ڈھیر_2[--sp][0];\
        type *سرا  = ڈھیر_2[  sp][1];\
        طالما(شروع < سرا){\
            إذا(شروع < سرا-1) {\
                صحيح checksort=0;\
                type *دایاں = سرا-2;\
                type *بایاں  = شروع+1;\
                type *mid = شروع + ((سرا-شروع)>>1);\
                إذا(cmp(شروع, سرا) > 0) {\
                    إذا(cmp(  سرا, mid) > 0) FFSWAP(type, *شروع, *mid);\
                    وإلا                    FFSWAP(type, *شروع, *سرا);\
                }وإلا{\
                    إذا(cmp(شروع, mid) > 0) FFSWAP(type, *شروع, *mid);\
                    وإلا checksort= 1;\
                }\
                إذا(cmp(mid, سرا) > 0){ \
                    FFSWAP(type, *mid, *سرا);\
                    checksort=0;\
                }\
                إذا(شروع == سرا-2) اكسر;\
                FFSWAP(type, سرا[-1], *mid);\
                طالما(بایاں <= دایاں){\
                    طالما(بایاں<=دایاں && cmp(بایاں, سرا-1) < 0)\
                        بایاں++;\
                    طالما(بایاں<=دایاں && cmp(دایاں, سرا-1) > 0)\
                        دایاں--;\
                    إذا(بایاں <= دایاں){\
                        FFSWAP(type, *بایاں, *دایاں);\
                        بایاں++;\
                        دایاں--;\
                    }\
                }\
                FFSWAP(type, سرا[-1], *بایاں);\
                إذا(checksort && (mid == بایاں-1 || mid == بایاں)){\
                    mid= شروع;\
                    طالما(mid<سرا && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    إذا(mid==سرا)\
                        اكسر;\
                }\
                إذا(سرا-بایاں < بایاں-شروع){\
                    ڈھیر_2[sp  ][0]= شروع;\
                    ڈھیر_2[sp++][1]= دایاں;\
                    شروع = بایاں+1;\
                }وإلا{\
                    ڈھیر_2[sp  ][0]= بایاں+1;\
                    ڈھیر_2[sp++][1]= سرا;\
                    سرا = دایاں;\
                }\
            }وإلا{\
                إذا(cmp(شروع, سرا) > 0)\
                    FFSWAP(type, *شروع, *سرا);\
                اكسر;\
            }\
        }\
    }\
} طالما (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#تعریف_کرو AV_MSORT(p, tmp, عدد, type, cmp) افعل {\
    بنانشانی i, j, قدم;\
    لكل(قدم=1; قدم<(عدد); قدم+=قدم){\
        لكل(i=0; i<(عدد); i+=2*قدم){\
            بنانشانی a[2] = {i, i+قدم};\
            بنانشانی سرا = FFMIN(i+2*قدم, (عدد));\
            لكل(j=i; a[0]<i+قدم && a[1]<سرا; j++){\
                صحيح idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            إذا(a[0]>=i+قدم) a[0] = a[1];\
            لكل(; j<سرا; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} طالما (0)

#جے_انت /* AVUTIL_QSORT_H */
