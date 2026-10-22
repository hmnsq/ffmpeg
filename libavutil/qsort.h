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

#અન્તર્ભાવ "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#define AV_QSORT(p, અંક, type, cmp) કરો {\
    શૂન્ય *ઢગલો[64][2];\
    પૂર્ણાંક sp= 1;\
    ઢગલો[0][0] = p;\
    ઢગલો[0][1] = (p)+(અંક)-1;\
    જ્યારે(sp){\
        type *start= ઢગલો[--sp][0];\
        type *end  = ઢગલો[  sp][1];\
        જ્યારે(start < end){\
            જો(start < end-1) {\
                પૂર્ણાંક checksort=0;\
                type *જમણું = end-2;\
                type *ડાબું  = start+1;\
                type *mid = start + ((end-start)>>1);\
                જો(cmp(start, end) > 0) {\
                    જો(cmp(  end, mid) > 0) FFSWAP(type, *start, *mid);\
                    નહીંતર                    FFSWAP(type, *start, *end);\
                }નહીંતર{\
                    જો(cmp(start, mid) > 0) FFSWAP(type, *start, *mid);\
                    નહીંતર checksort= 1;\
                }\
                જો(cmp(mid, end) > 0){ \
                    FFSWAP(type, *mid, *end);\
                    checksort=0;\
                }\
                જો(start == end-2) તોડો;\
                FFSWAP(type, end[-1], *mid);\
                જ્યારે(ડાબું <= જમણું){\
                    જ્યારે(ડાબું<=જમણું && cmp(ડાબું, end-1) < 0)\
                        ડાબું++;\
                    જ્યારે(ડાબું<=જમણું && cmp(જમણું, end-1) > 0)\
                        જમણું--;\
                    જો(ડાબું <= જમણું){\
                        FFSWAP(type, *ડાબું, *જમણું);\
                        ડાબું++;\
                        જમણું--;\
                    }\
                }\
                FFSWAP(type, end[-1], *ડાબું);\
                જો(checksort && (mid == ડાબું-1 || mid == ડાબું)){\
                    mid= start;\
                    જ્યારે(mid<end && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    જો(mid==end)\
                        તોડો;\
                }\
                જો(end-ડાબું < ડાબું-start){\
                    ઢગલો[sp  ][0]= start;\
                    ઢગલો[sp++][1]= જમણું;\
                    start = ડાબું+1;\
                }નહીંતર{\
                    ઢગલો[sp  ][0]= ડાબું+1;\
                    ઢગલો[sp++][1]= end;\
                    end = જમણું;\
                }\
            }નહીંતર{\
                જો(cmp(start, end) > 0)\
                    FFSWAP(type, *start, *end);\
                તોડો;\
            }\
        }\
    }\
} જ્યારે (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#define AV_MSORT(p, tmp, અંક, type, cmp) કરો {\
    unsigned i, j, step;\
    માટે(step=1; step<(અંક); step+=step){\
        માટે(i=0; i<(અંક); i+=2*step){\
            unsigned a[2] = {i, i+step};\
            unsigned end = FFMIN(i+2*step, (અંક));\
            માટે(j=i; a[0]<i+step && a[1]<end; j++){\
                પૂર્ણાંક idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            જો(a[0]>=i+step) a[0] = a[1];\
            માટે(; j<end; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} જ્યારે (0)

#endif /* AVUTIL_QSORT_H */
