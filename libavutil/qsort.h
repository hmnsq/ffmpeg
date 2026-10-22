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

#که_نه_تعریف_شوی AVUTIL_QSORT_H
#تعریف_کړه AVUTIL_QSORT_H

#ضمن "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#تعریف_کړه AV_QSORT(p, عدد, type, cmp) افعل {\
    فراغ *ډېری[64][2];\
    صحيح sp= 1;\
    ډېری[0][0] = p;\
    ډېری[0][1] = (p)+(عدد)-1;\
    طالما(sp){\
        type *پیل= ډېری[--sp][0];\
        type *پای_ټکی  = ډېری[  sp][1];\
        طالما(پیل < پای_ټکی){\
            إذا(پیل < پای_ټکی-1) {\
                صحيح checksort=0;\
                type *ښی = پای_ټکی-2;\
                type *کیڼ  = پیل+1;\
                type *mid = پیل + ((پای_ټکی-پیل)>>1);\
                إذا(cmp(پیل, پای_ټکی) > 0) {\
                    إذا(cmp(  پای_ټکی, mid) > 0) FFSWAP(type, *پیل, *mid);\
                    وإلا                    FFSWAP(type, *پیل, *پای_ټکی);\
                }وإلا{\
                    إذا(cmp(پیل, mid) > 0) FFSWAP(type, *پیل, *mid);\
                    وإلا checksort= 1;\
                }\
                إذا(cmp(mid, پای_ټکی) > 0){ \
                    FFSWAP(type, *mid, *پای_ټکی);\
                    checksort=0;\
                }\
                إذا(پیل == پای_ټکی-2) اكسر;\
                FFSWAP(type, پای_ټکی[-1], *mid);\
                طالما(کیڼ <= ښی){\
                    طالما(کیڼ<=ښی && cmp(کیڼ, پای_ټکی-1) < 0)\
                        کیڼ++;\
                    طالما(کیڼ<=ښی && cmp(ښی, پای_ټکی-1) > 0)\
                        ښی--;\
                    إذا(کیڼ <= ښی){\
                        FFSWAP(type, *کیڼ, *ښی);\
                        کیڼ++;\
                        ښی--;\
                    }\
                }\
                FFSWAP(type, پای_ټکی[-1], *کیڼ);\
                إذا(checksort && (mid == کیڼ-1 || mid == کیڼ)){\
                    mid= پیل;\
                    طالما(mid<پای_ټکی && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    إذا(mid==پای_ټکی)\
                        اكسر;\
                }\
                إذا(پای_ټکی-کیڼ < کیڼ-پیل){\
                    ډېری[sp  ][0]= پیل;\
                    ډېری[sp++][1]= ښی;\
                    پیل = کیڼ+1;\
                }وإلا{\
                    ډېری[sp  ][0]= کیڼ+1;\
                    ډېری[sp++][1]= پای_ټکی;\
                    پای_ټکی = ښی;\
                }\
            }وإلا{\
                إذا(cmp(پیل, پای_ټکی) > 0)\
                    FFSWAP(type, *پیل, *پای_ټکی);\
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
#تعریف_کړه AV_MSORT(p, tmp, عدد, type, cmp) افعل {\
    بینښه i, j, ګام;\
    لكل(ګام=1; ګام<(عدد); ګام+=ګام){\
        لكل(i=0; i<(عدد); i+=2*ګام){\
            بینښه a[2] = {i, i+ګام};\
            بینښه پای_ټکی = FFMIN(i+2*ګام, (عدد));\
            لكل(j=i; a[0]<i+ګام && a[1]<پای_ټکی; j++){\
                صحيح idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            إذا(a[0]>=i+ګام) a[0] = a[1];\
            لكل(; j<پای_ټکی; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} طالما (0)

#د_که_پای /* AVUTIL_QSORT_H */
