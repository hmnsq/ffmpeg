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

#अन्तर्भाव "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#define AV_QSORT(p, अंक, type, cmp) करा {\
    शून्य *चळत[64][2];\
    पूर्णांक sp= 1;\
    चळत[0][0] = p;\
    चळत[0][1] = (p)+(अंक)-1;\
    पर्यंत(sp){\
        type *start= चळत[--sp][0];\
        type *end  = चळत[  sp][1];\
        पर्यंत(start < end){\
            जर(start < end-1) {\
                पूर्णांक checksort=0;\
                type *उजवा = end-2;\
                type *डावा  = start+1;\
                type *mid = start + ((end-start)>>1);\
                जर(cmp(start, end) > 0) {\
                    जर(cmp(  end, mid) > 0) FFSWAP(type, *start, *mid);\
                    अन्यथा                    FFSWAP(type, *start, *end);\
                }अन्यथा{\
                    जर(cmp(start, mid) > 0) FFSWAP(type, *start, *mid);\
                    अन्यथा checksort= 1;\
                }\
                जर(cmp(mid, end) > 0){ \
                    FFSWAP(type, *mid, *end);\
                    checksort=0;\
                }\
                जर(start == end-2) थांबा;\
                FFSWAP(type, end[-1], *mid);\
                पर्यंत(डावा <= उजवा){\
                    पर्यंत(डावा<=उजवा && cmp(डावा, end-1) < 0)\
                        डावा++;\
                    पर्यंत(डावा<=उजवा && cmp(उजवा, end-1) > 0)\
                        उजवा--;\
                    जर(डावा <= उजवा){\
                        FFSWAP(type, *डावा, *उजवा);\
                        डावा++;\
                        उजवा--;\
                    }\
                }\
                FFSWAP(type, end[-1], *डावा);\
                जर(checksort && (mid == डावा-1 || mid == डावा)){\
                    mid= start;\
                    पर्यंत(mid<end && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    जर(mid==end)\
                        थांबा;\
                }\
                जर(end-डावा < डावा-start){\
                    चळत[sp  ][0]= start;\
                    चळत[sp++][1]= उजवा;\
                    start = डावा+1;\
                }अन्यथा{\
                    चळत[sp  ][0]= डावा+1;\
                    चळत[sp++][1]= end;\
                    end = उजवा;\
                }\
            }अन्यथा{\
                जर(cmp(start, end) > 0)\
                    FFSWAP(type, *start, *end);\
                थांबा;\
            }\
        }\
    }\
} पर्यंत (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#define AV_MSORT(p, tmp, अंक, type, cmp) करा {\
    अचिन्हित i, j, step;\
    साठी(step=1; step<(अंक); step+=step){\
        साठी(i=0; i<(अंक); i+=2*step){\
            अचिन्हित a[2] = {i, i+step};\
            अचिन्हित end = FFMIN(i+2*step, (अंक));\
            साठी(j=i; a[0]<i+step && a[1]<end; j++){\
                पूर्णांक idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            जर(a[0]>=i+step) a[0] = a[1];\
            साठी(; j<end; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} पर्यंत (0)

#endif /* AVUTIL_QSORT_H */
