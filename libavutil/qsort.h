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

#অন্তর্ভাব "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#define AV_QSORT(p, অঙ্ক, type, cmp) করো {\
    শূন্য *স্তূপ[64][2];\
    পূর্ণসংখ্যা sp= 1;\
    স্তূপ[0][0] = p;\
    স্তূপ[0][1] = (p)+(অঙ্ক)-1;\
    যখন(sp){\
        type *start= স্তূপ[--sp][0];\
        type *end  = স্তূপ[  sp][1];\
        যখন(start < end){\
            যদি(start < end-1) {\
                পূর্ণসংখ্যা checksort=0;\
                type *ডান = end-2;\
                type *বাম  = start+1;\
                type *mid = start + ((end-start)>>1);\
                যদি(cmp(start, end) > 0) {\
                    যদি(cmp(  end, mid) > 0) FFSWAP(type, *start, *mid);\
                    অন্যথা                    FFSWAP(type, *start, *end);\
                }অন্যথা{\
                    যদি(cmp(start, mid) > 0) FFSWAP(type, *start, *mid);\
                    অন্যথা checksort= 1;\
                }\
                যদি(cmp(mid, end) > 0){ \
                    FFSWAP(type, *mid, *end);\
                    checksort=0;\
                }\
                যদি(start == end-2) বিরতি;\
                FFSWAP(type, end[-1], *mid);\
                যখন(বাম <= ডান){\
                    যখন(বাম<=ডান && cmp(বাম, end-1) < 0)\
                        বাম++;\
                    যখন(বাম<=ডান && cmp(ডান, end-1) > 0)\
                        ডান--;\
                    যদি(বাম <= ডান){\
                        FFSWAP(type, *বাম, *ডান);\
                        বাম++;\
                        ডান--;\
                    }\
                }\
                FFSWAP(type, end[-1], *বাম);\
                যদি(checksort && (mid == বাম-1 || mid == বাম)){\
                    mid= start;\
                    যখন(mid<end && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    যদি(mid==end)\
                        বিরতি;\
                }\
                যদি(end-বাম < বাম-start){\
                    স্তূপ[sp  ][0]= start;\
                    স্তূপ[sp++][1]= ডান;\
                    start = বাম+1;\
                }অন্যথা{\
                    স্তূপ[sp  ][0]= বাম+1;\
                    স্তূপ[sp++][1]= end;\
                    end = ডান;\
                }\
            }অন্যথা{\
                যদি(cmp(start, end) > 0)\
                    FFSWAP(type, *start, *end);\
                বিরতি;\
            }\
        }\
    }\
} যখন (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#define AV_MSORT(p, tmp, অঙ্ক, type, cmp) করো {\
    unsigned i, j, step;\
    জন্য(step=1; step<(অঙ্ক); step+=step){\
        জন্য(i=0; i<(অঙ্ক); i+=2*step){\
            unsigned a[2] = {i, i+step};\
            unsigned end = FFMIN(i+2*step, (অঙ্ক));\
            জন্য(j=i; a[0]<i+step && a[1]<end; j++){\
                পূর্ণসংখ্যা idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            যদি(a[0]>=i+step) a[0] = a[1];\
            জন্য(; j<end; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} যখন (0)

#endif /* AVUTIL_QSORT_H */
