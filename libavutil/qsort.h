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

#അന്തര്ഭാവ "macros.h"


/**
 * Quicksort
 * This sort is fast, and fully inplace but not stable and it is possible
 * to construct input that requires O(n^2) time but this is very unlikely to
 * happen with non constructed input.
 */
#define AV_QSORT(p, അക്കം, type, cmp) ചെയ്യുക {\
    ശൂന്യം *അട്ടി[64][2];\
    പൂർണ്ണസംഖ്യ sp= 1;\
    അട്ടി[0][0] = p;\
    അട്ടി[0][1] = (p)+(അക്കം)-1;\
    ആകുമ്പോൾ(sp){\
        type *start= അട്ടി[--sp][0];\
        type *end  = അട്ടി[  sp][1];\
        ആകുമ്പോൾ(start < end){\
            എങ്കിൽ(start < end-1) {\
                പൂർണ്ണസംഖ്യ checksort=0;\
                type *വലത് = end-2;\
                type *ഇടത്  = start+1;\
                type *mid = start + ((end-start)>>1);\
                എങ്കിൽ(cmp(start, end) > 0) {\
                    എങ്കിൽ(cmp(  end, mid) > 0) FFSWAP(type, *start, *mid);\
                    അല്ലെങ്കിൽ                    FFSWAP(type, *start, *end);\
                }അല്ലെങ്കിൽ{\
                    എങ്കിൽ(cmp(start, mid) > 0) FFSWAP(type, *start, *mid);\
                    അല്ലെങ്കിൽ checksort= 1;\
                }\
                എങ്കിൽ(cmp(mid, end) > 0){ \
                    FFSWAP(type, *mid, *end);\
                    checksort=0;\
                }\
                എങ്കിൽ(start == end-2) നിർത്തുക;\
                FFSWAP(type, end[-1], *mid);\
                ആകുമ്പോൾ(ഇടത് <= വലത്){\
                    ആകുമ്പോൾ(ഇടത്<=വലത് && cmp(ഇടത്, end-1) < 0)\
                        ഇടത്++;\
                    ആകുമ്പോൾ(ഇടത്<=വലത് && cmp(വലത്, end-1) > 0)\
                        വലത്--;\
                    എങ്കിൽ(ഇടത് <= വലത്){\
                        FFSWAP(type, *ഇടത്, *വലത്);\
                        ഇടത്++;\
                        വലത്--;\
                    }\
                }\
                FFSWAP(type, end[-1], *ഇടത്);\
                എങ്കിൽ(checksort && (mid == ഇടത്-1 || mid == ഇടത്)){\
                    mid= start;\
                    ആകുമ്പോൾ(mid<end && cmp(mid, mid+1) <= 0)\
                        mid++;\
                    എങ്കിൽ(mid==end)\
                        നിർത്തുക;\
                }\
                എങ്കിൽ(end-ഇടത് < ഇടത്-start){\
                    അട്ടി[sp  ][0]= start;\
                    അട്ടി[sp++][1]= വലത്;\
                    start = ഇടത്+1;\
                }അല്ലെങ്കിൽ{\
                    അട്ടി[sp  ][0]= ഇടത്+1;\
                    അട്ടി[sp++][1]= end;\
                    end = വലത്;\
                }\
            }അല്ലെങ്കിൽ{\
                എങ്കിൽ(cmp(start, end) > 0)\
                    FFSWAP(type, *start, *end);\
                നിർത്തുക;\
            }\
        }\
    }\
} ആകുമ്പോൾ (0)

/**
 * Merge sort, this sort requires a temporary buffer and is stable, its worst
 * case time is O(n log n)
 * @param p     must be a lvalue pointer, this function may exchange it with tmp
 * @param tmp   must be a lvalue pointer, this function may exchange it with p
 */
#define AV_MSORT(p, tmp, അക്കം, type, cmp) ചെയ്യുക {\
    unsigned i, j, step;\
    വേണ്ടി(step=1; step<(അക്കം); step+=step){\
        വേണ്ടി(i=0; i<(അക്കം); i+=2*step){\
            unsigned a[2] = {i, i+step};\
            unsigned end = FFMIN(i+2*step, (അക്കം));\
            വേണ്ടി(j=i; a[0]<i+step && a[1]<end; j++){\
                പൂർണ്ണസംഖ്യ idx= cmp(p+a[0], p+a[1]) > 0;\
                tmp[j] = p[ a[idx]++ ];\
            }\
            എങ്കിൽ(a[0]>=i+step) a[0] = a[1];\
            വേണ്ടി(; j<end; j++){\
                tmp[j] = p[ a[0]++ ];\
            }\
        }\
        FFSWAP(type*, p, tmp);\
    }\
} ആകുമ്പോൾ (0)

#endif /* AVUTIL_QSORT_H */
