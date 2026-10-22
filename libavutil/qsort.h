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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_QSORT_H
#وصف_ڪريو AVUTIL_QSORT_H

#ضمن "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#وصف_ڪريو AV_QSORT(p, انگ, type, cmp) افعل {\
    فراغ *ڍير_2[64][2];\
    صحيح sp= 1;\
    ڍير_2[0][0] = p;\
    ڍير_2[0][1] = (p)+(انگ)-1;\
    طالما(sp){\
        type *شروعات= ڍير_2[--sp][0];\
        type *پڇاڙي  = ڍير_2[  sp][1];\
        طالما(شروعات < پڇاڙي){\
            إذا(شروعات < پڇاڙي-1) {\
                صحيح checksort=0;\
                type *ساڄو = پڇاڙي-2;\
                type *کاٻو  = شروعات+1;\
                type *mid = شروعات + ((پڇاڙي-شروعات)>>1);\
                إذا(cmp(شروعات, پڇاڙي) > 0) {\
                    إذا(cmp(  پڇاڙي, mid) > 0) FFSWAP(type, *شروعات, *mid);\
                    وإلا                    FFSWAP(type, *شروعات, *پڇاڙي);\
                }وإلا{\
                    إذا(cmp(شروعات, mid) > 0) FFSWAP(type, *شروعات, *mid);\
                    وإلا checksort= 1;\
                }\
                إذا(cmp(mid, پڇاڙي) > 0){ \
                    FFSWAP(type, *mid, *پڇاڙي);\
                    checksort=0;\
                }\
                إذا(شروعات == پڇاڙي-2) اكسر;\
                FFSWAP(type, پڇاڙي[-1], *mid);\
                طالما(کاٻو <= ساڄو){\
                    طالما(کاٻو<=ساڄو && cmp(کاٻو, پڇاڙي-1) < 0)\
                        کاٻو++;\
                    طالما(کاٻو<=ساڄو && cmp(ساڄو, پڇاڙي-1) > 0)\
                        ساڄو--;\
                    إذا(کاٻو <= ساڄو){\
                        FFSWAP(type, *کاٻو, *ساڄو);\
                        کاٻو++;\
                        ساڄو--;\
                    }\
                }\
                FFSWAP(type, پڇاڙي[-1], *کاٻو);\
                إذا(checksort && (mid == کاٻو-1 || mid == کاٻو)){\
                    mid= شروعات;\
                    طالما(mid<پڇاڙي && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    إذا(mid==پڇاڙي)\
                        اكسر;\
                }\
                إذا(پڇاڙي-کاٻو < کاٻو-شروعات){\
                    ڍير_2[sp  ][0]= شروعات;\
                    ڍير_2[sp++][1]= ساڄو;\
                    شروعات = کاٻو+1;\
                }وإلا{\
                    ڍير_2[sp  ][0]= کاٻو+1;\
                    ڍير_2[sp++][1]= پڇاڙي;\
                    پڇاڙي = ساڄو;\
                }\
            }وإلا{\
                إذا(cmp(شروعات, پڇاڙي) > 0)\
                    FFSWAP(type, *شروعات, *پڇاڙي);\
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
#وصف_ڪريو AV_MSORT(p, tmp, انگ, type, cmp) افعل {\
    بنانشان i, j, قدم;\
    لكل(قدم=1; قدم<(انگ); قدم+=قدم){\
        لكل(i=0; i<(انگ); i+=2*قدم){\
            بنانشان a[2] = {i, i+قدم};\
            بنانشان پڇاڙي = FFMIN(i+2*قدم, (انگ));\
            لكل(j=i; a[0]<i+قدم && a[1]<پڇاڙي; j++){\
                صحيح idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            إذا(a[0]>=i+قدم) a[0] = a[1];\
            لكل(; j<پڇاڙي; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} طالما (0)

#جيڪڏهن_پورو /* AVUTIL_QSORT_H */
