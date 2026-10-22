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

#اگر_تعریف_نشده AVUTIL_QSORT_H
#تعریف_کن AVUTIL_QSORT_H

#ضمن "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#تعریف_کن AV_QSORT(p, رقم, type, cmp) افعل {\
    فراغ *پشته[64][2];\
    صحيح sp= 1;\
    پشته[0][0] = p;\
    پشته[0][1] = (p)+(رقم)-1;\
    طالما(sp){\
        type *شروع= پشته[--sp][0];\
        type *انتها  = پشته[  sp][1];\
        طالما(شروع < انتها){\
            إذا(شروع < انتها-1) {\
                صحيح checksort=0;\
                type *راست = انتها-2;\
                type *چپ  = شروع+1;\
                type *mid = شروع + ((انتها-شروع)>>1);\
                إذا(cmp(شروع, انتها) > 0) {\
                    إذا(cmp(  انتها, mid) > 0) FFSWAP(type, *شروع, *mid);\
                    وإلا                    FFSWAP(type, *شروع, *انتها);\
                }وإلا{\
                    إذا(cmp(شروع, mid) > 0) FFSWAP(type, *شروع, *mid);\
                    وإلا checksort= 1;\
                }\
                إذا(cmp(mid, انتها) > 0){ \
                    FFSWAP(type, *mid, *انتها);\
                    checksort=0;\
                }\
                إذا(شروع == انتها-2) اكسر;\
                FFSWAP(type, انتها[-1], *mid);\
                طالما(چپ <= راست){\
                    طالما(چپ<=راست && cmp(چپ, انتها-1) < 0)\
                        چپ++;\
                    طالما(چپ<=راست && cmp(راست, انتها-1) > 0)\
                        راست--;\
                    إذا(چپ <= راست){\
                        FFSWAP(type, *چپ, *راست);\
                        چپ++;\
                        راست--;\
                    }\
                }\
                FFSWAP(type, انتها[-1], *چپ);\
                إذا(checksort && (mid == چپ-1 || mid == چپ)){\
                    mid= شروع;\
                    طالما(mid<انتها && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    إذا(mid==انتها)\
                        اكسر;\
                }\
                إذا(انتها-چپ < چپ-شروع){\
                    پشته[sp  ][0]= شروع;\
                    پشته[sp++][1]= راست;\
                    شروع = چپ+1;\
                }وإلا{\
                    پشته[sp  ][0]= چپ+1;\
                    پشته[sp++][1]= انتها;\
                    انتها = راست;\
                }\
            }وإلا{\
                إذا(cmp(شروع, انتها) > 0)\
                    FFSWAP(type, *شروع, *انتها);\
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
#تعریف_کن AV_MSORT(p, tmp, رقم, type, cmp) افعل {\
    بیعلامت i, j, گام;\
    لكل(گام=1; گام<(رقم); گام+=گام){\
        لكل(i=0; i<(رقم); i+=2*گام){\
            بیعلامت a[2] = {i, i+گام};\
            بیعلامت انتها = FFMIN(i+2*گام, (رقم));\
            لكل(j=i; a[0]<i+گام && a[1]<انتها; j++){\
                صحيح idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            إذا(a[0]>=i+گام) a[0] = a[1];\
            لكل(; j<انتها; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} طالما (0)

#پایان_اگر /* AVUTIL_QSORT_H */
