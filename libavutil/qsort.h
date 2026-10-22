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

#شامل "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#define AV_QSORT(p, رقم, type, cmp) انجامبده {\
    تهی *پشته[64][2];\
    صحیح sp= 1;\
    پشته[0][0] = p;\
    پشته[0][1] = (p)+(رقم)-1;\
    وقتی(sp){\
        type *start= پشته[--sp][0];\
        type *end  = پشته[  sp][1];\
        وقتی(start < end){\
            اگر(start < end-1) {\
                صحیح checksort=0;\
                type *راست = end-2;\
                type *چپ  = start+1;\
                type *mid = start + ((end-start)>>1);\
                اگر(cmp(start, end) > 0) {\
                    اگر(cmp(  end, mid) > 0) FFSWAP(type, *start, *mid);\
                    وگرنه                    FFSWAP(type, *start, *end);\
                }وگرنه{\
                    اگر(cmp(start, mid) > 0) FFSWAP(type, *start, *mid);\
                    وگرنه checksort= 1;\
                }\
                اگر(cmp(mid, end) > 0){ \
                    FFSWAP(type, *mid, *end);\
                    checksort=0;\
                }\
                اگر(start == end-2) بشکن;\
                FFSWAP(type, end[-1], *mid);\
                وقتی(چپ <= راست){\
                    وقتی(چپ<=راست && cmp(چپ, end-1) < 0)\
                        چپ++;\
                    وقتی(چپ<=راست && cmp(راست, end-1) > 0)\
                        راست--;\
                    اگر(چپ <= راست){\
                        FFSWAP(type, *چپ, *راست);\
                        چپ++;\
                        راست--;\
                    }\
                }\
                FFSWAP(type, end[-1], *چپ);\
                اگر(checksort && (mid == چپ-1 || mid == چپ)){\
                    mid= start;\
                    وقتی(mid<end && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    اگر(mid==end)\
                        بشکن;\
                }\
                اگر(end-چپ < چپ-start){\
                    پشته[sp  ][0]= start;\
                    پشته[sp++][1]= راست;\
                    start = چپ+1;\
                }وگرنه{\
                    پشته[sp  ][0]= چپ+1;\
                    پشته[sp++][1]= end;\
                    end = راست;\
                }\
            }وگرنه{\
                اگر(cmp(start, end) > 0)\
                    FFSWAP(type, *start, *end);\
                بشکن;\
            }\
        }\
    }\
} وقتی (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#define AV_MSORT(p, tmp, رقم, type, cmp) انجامبده {\
    unsigned i, j, step;\
    برای(step=1; step<(رقم); step+=step){\
        برای(i=0; i<(رقم); i+=2*step){\
            unsigned a[2] = {i, i+step};\
            unsigned end = FFMIN(i+2*step, (رقم));\
            برای(j=i; a[0]<i+step && a[1]<end; j++){\
                صحیح idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            اگر(a[0]>=i+step) a[0] = a[1];\
            برای(; j<end; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} وقتی (0)

#endif /* AVUTIL_QSORT_H */
