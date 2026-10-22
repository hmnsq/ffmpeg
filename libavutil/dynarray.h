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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_DYNARRAY_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_DYNARRAY_H

#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "mem.h"

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
#ವ್ಯಾಖ್ಯಾನಿಸು FF_DYNARRAY_ಕೂಡಿಸು(av_ಗಾತ್ರ_max, av_elt_ಗಾತ್ರ, av_array, av_ಗಾತ್ರ, \
                        av_success, av_failure) \
    ಮಾಡು { \
        size_t av_ಗಾತ್ರ_new = (av_ಗಾತ್ರ); \
        ಆದರೆ (!((av_ಗಾತ್ರ) & ((av_ಗಾತ್ರ) - 1))) { \
            av_ಗಾತ್ರ_new = (av_ಗಾತ್ರ) ? (av_ಗಾತ್ರ) << 1 : 1; \
            ಆದರೆ (av_ಗಾತ್ರ_new > (av_ಗಾತ್ರ_max) / (av_elt_ಗಾತ್ರ)) { \
                av_ಗಾತ್ರ_new = 0; \
            } ಇಲ್ಲದಿದ್ದರೆ { \
                ಶೂನ್ಯ *av_array_new = \
                    av_realloc((av_array), av_ಗಾತ್ರ_new * (av_elt_ಗಾತ್ರ)); \
                ಆದರೆ (!av_array_new) \
                    av_ಗಾತ್ರ_new = 0; \
                ಇಲ್ಲದಿದ್ದರೆ \
                    (av_array) = av_array_new; \
            } \
        } \
        ಆದರೆ (av_ಗಾತ್ರ_new) { \
            { av_success } \
            (av_ಗಾತ್ರ)++; \
        } ಇಲ್ಲದಿದ್ದರೆ { \
            av_failure \
        } \
    } ಆಗ (0)

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_DYNARRAY_H */
