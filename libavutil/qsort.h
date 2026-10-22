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

#அந்தர்பாவ "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#define AV_QSORT(p, இலக்கம், type, cmp) செய் {\
    வெறுமை *அடுக்கு[64][2];\
    முழு sp= 1;\
    அடுக்கு[0][0] = p;\
    அடுக்கு[0][1] = (p)+(இலக்கம்)-1;\
    போது(sp){\
        type *start= அடுக்கு[--sp][0];\
        type *end  = அடுக்கு[  sp][1];\
        போது(start < end){\
            எனில்(start < end-1) {\
                முழு checksort=0;\
                type *வலது = end-2;\
                type *இடது  = start+1;\
                type *mid = start + ((end-start)>>1);\
                எனில்(cmp(start, end) > 0) {\
                    எனில்(cmp(  end, mid) > 0) FFSWAP(type, *start, *mid);\
                    இல்லையெனில்                    FFSWAP(type, *start, *end);\
                }இல்லையெனில்{\
                    எனில்(cmp(start, mid) > 0) FFSWAP(type, *start, *mid);\
                    இல்லையெனில் checksort= 1;\
                }\
                எனில்(cmp(mid, end) > 0){ \
                    FFSWAP(type, *mid, *end);\
                    checksort=0;\
                }\
                எனில்(start == end-2) நிறுத்து;\
                FFSWAP(type, end[-1], *mid);\
                போது(இடது <= வலது){\
                    போது(இடது<=வலது && cmp(இடது, end-1) < 0)\
                        இடது++;\
                    போது(இடது<=வலது && cmp(வலது, end-1) > 0)\
                        வலது--;\
                    எனில்(இடது <= வலது){\
                        FFSWAP(type, *இடது, *வலது);\
                        இடது++;\
                        வலது--;\
                    }\
                }\
                FFSWAP(type, end[-1], *இடது);\
                எனில்(checksort && (mid == இடது-1 || mid == இடது)){\
                    mid= start;\
                    போது(mid<end && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    எனில்(mid==end)\
                        நிறுத்து;\
                }\
                எனில்(end-இடது < இடது-start){\
                    அடுக்கு[sp  ][0]= start;\
                    அடுக்கு[sp++][1]= வலது;\
                    start = இடது+1;\
                }இல்லையெனில்{\
                    அடுக்கு[sp  ][0]= இடது+1;\
                    அடுக்கு[sp++][1]= end;\
                    end = வலது;\
                }\
            }இல்லையெனில்{\
                எனில்(cmp(start, end) > 0)\
                    FFSWAP(type, *start, *end);\
                நிறுத்து;\
            }\
        }\
    }\
} போது (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#define AV_MSORT(p, tmp, இலக்கம், type, cmp) செய் {\
    unsigned i, j, step;\
    க்கு(step=1; step<(இலக்கம்); step+=step){\
        க்கு(i=0; i<(இலக்கம்); i+=2*step){\
            unsigned a[2] = {i, i+step};\
            unsigned end = FFMIN(i+2*step, (இலக்கம்));\
            க்கு(j=i; a[0]<i+step && a[1]<end; j++){\
                முழு idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            எனில்(a[0]>=i+step) a[0] = a[1];\
            க்கு(; j<end; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} போது (0)

#endif /* AVUTIL_QSORT_H */
