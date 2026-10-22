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

#నిర్వచితం_కాకపోతే AVUTIL_QSORT_H
#నిర్వచించు AVUTIL_QSORT_H

#అన్తర్భావ "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#నిర్వచించు AV_QSORT(p, అంకె, type, cmp) చేయి {\
    శూన్య *దొంతర[64][2];\
    పూర్ణాంకం sp= 1;\
    దొంతర[0][0] = p;\
    దొంతర[0][1] = (p)+(అంకె)-1;\
    అయితే(sp){\
        type *ప్రారంభం= దొంతర[--sp][0];\
        type *చివర  = దొంతర[  sp][1];\
        అయితే(ప్రారంభం < చివర){\
            ఒకవేళ(ప్రారంభం < చివర-1) {\
                పూర్ణాంకం checksort=0;\
                type *కుడి = చివర-2;\
                type *ఎడమ  = ప్రారంభం+1;\
                type *mid = ప్రారంభం + ((చివర-ప్రారంభం)>>1);\
                ఒకవేళ(cmp(ప్రారంభం, చివర) > 0) {\
                    ఒకవేళ(cmp(  చివర, mid) > 0) FFSWAP(type, *ప్రారంభం, *mid);\
                    లేకపోతే                    FFSWAP(type, *ప్రారంభం, *చివర);\
                }లేకపోతే{\
                    ఒకవేళ(cmp(ప్రారంభం, mid) > 0) FFSWAP(type, *ప్రారంభం, *mid);\
                    లేకపోతే checksort= 1;\
                }\
                ఒకవేళ(cmp(mid, చివర) > 0){ \
                    FFSWAP(type, *mid, *చివర);\
                    checksort=0;\
                }\
                ఒకవేళ(ప్రారంభం == చివర-2) ఆపు;\
                FFSWAP(type, చివర[-1], *mid);\
                అయితే(ఎడమ <= కుడి){\
                    అయితే(ఎడమ<=కుడి && cmp(ఎడమ, చివర-1) < 0)\
                        ఎడమ++;\
                    అయితే(ఎడమ<=కుడి && cmp(కుడి, చివర-1) > 0)\
                        కుడి--;\
                    ఒకవేళ(ఎడమ <= కుడి){\
                        FFSWAP(type, *ఎడమ, *కుడి);\
                        ఎడమ++;\
                        కుడి--;\
                    }\
                }\
                FFSWAP(type, చివర[-1], *ఎడమ);\
                ఒకవేళ(checksort && (mid == ఎడమ-1 || mid == ఎడమ)){\
                    mid= ప్రారంభం;\
                    అయితే(mid<చివర && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    ఒకవేళ(mid==చివర)\
                        ఆపు;\
                }\
                ఒకవేళ(చివర-ఎడమ < ఎడమ-ప్రారంభం){\
                    దొంతర[sp  ][0]= ప్రారంభం;\
                    దొంతర[sp++][1]= కుడి;\
                    ప్రారంభం = ఎడమ+1;\
                }లేకపోతే{\
                    దొంతర[sp  ][0]= ఎడమ+1;\
                    దొంతర[sp++][1]= చివర;\
                    చివర = కుడి;\
                }\
            }లేకపోతే{\
                ఒకవేళ(cmp(ప్రారంభం, చివర) > 0)\
                    FFSWAP(type, *ప్రారంభం, *చివర);\
                ఆపు;\
            }\
        }\
    }\
} అయితే (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#నిర్వచించు AV_MSORT(p, tmp, అంకె, type, cmp) చేయి {\
    గుర్తులేని i, j, అడుగు;\
    కొరకు(అడుగు=1; అడుగు<(అంకె); అడుగు+=అడుగు){\
        కొరకు(i=0; i<(అంకె); i+=2*అడుగు){\
            గుర్తులేని a[2] = {i, i+అడుగు};\
            గుర్తులేని చివర = FFMIN(i+2*అడుగు, (అంకె));\
            కొరకు(j=i; a[0]<i+అడుగు && a[1]<చివర; j++){\
                పూర్ణాంకం idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            ఒకవేళ(a[0]>=i+అడుగు) a[0] = a[1];\
            కొరకు(; j<చివర; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} అయితే (0)

#అయితే_ముగింపు /* AVUTIL_QSORT_H */
