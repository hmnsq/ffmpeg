/*
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with FFmpeg; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_DYNARRAY_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_DYNARRAY_H

#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"

/**
 * Add an element to a dynamic array.
 *
 * The array is reallocated when its number of elements reaches powers of 2.
 * Therefore, the amortized cost of adding an element is constant.
 *
 * In case of success, the pointer to the array is updated in order to
 * point to the new grown array, and the size is incremented.
 *
 * @param av_size_max  maximum size of the array, usually the MAX macro of
 *                     the type of the size
 * @param av_elt_size  size of the elements in the array, in bytes
 * @param av_array     pointer to the array, must be a lvalue
 * @param av_size      size of the array, must be an integer lvalue
 * @param av_success   statement to execute on success; at this point, the
 *                     size variable is not yet incremented
 * @param av_failure   statement to execute on failure; if this happens, the
 *                     array and size are not changed; the statement can end
 *                     with a return or a goto
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_DYNARRAY_ਜੋੜੋ(av_ਮਾਪ_max, av_elt_ਮਾਪ, av_array, av_ਮਾਪ, \
                        av_success, av_failure) \
    ਕਰੋ { \
        size_t av_ਮਾਪ_new = (av_ਮਾਪ); \
        ਜੇ (!((av_ਮਾਪ) & ((av_ਮਾਪ) - 1))) { \
            av_ਮਾਪ_new = (av_ਮਾਪ) ? (av_ਮਾਪ) << 1 : 1; \
            ਜੇ (av_ਮਾਪ_new > (av_ਮਾਪ_max) / (av_elt_ਮਾਪ)) { \
                av_ਮਾਪ_new = 0; \
            } ਨਹੀਂਤਾਂ { \
                ਖਾਲੀ *av_array_new = \
                    av_realloc((av_array), av_ਮਾਪ_new * (av_elt_ਮਾਪ)); \
                ਜੇ (!av_array_new) \
                    av_ਮਾਪ_new = 0; \
                ਨਹੀਂਤਾਂ \
                    (av_array) = av_array_new; \
            } \
        } \
        ਜੇ (av_ਮਾਪ_new) { \
            { av_success } \
            (av_ਮਾਪ)++; \
        } ਨਹੀਂਤਾਂ { \
            av_failure \
        } \
    } ਜਦੋਂ (0)

#ਜੇ_ਅੰਤ /* AVUTIL_DYNARRAY_H */
