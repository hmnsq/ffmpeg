/*
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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_ಗುಣಲಕ್ಷಣಗಳು_ಆಂತರಿಕ_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_ಗುಣಲಕ್ಷಣಗಳು_ಆಂತರಿಕ_H

#ಅನ್ತರ್ಭಾವ "attributes.h"

#ಆದರೆ (defined(__GNUC__) || defined(__clang__)) && (defined(__ELF__) || defined(__MACH__))
#    define attribute_visibility_hidden __attribute__((visibility("hidden")))
#    define FF_VISIBILITY_ತಳ್ಳು_HIDDEN   _Pragma("GCC visibility push(hidden)")
#    define FF_VISIBILITY_ತೆಗೆ_HIDDEN    _Pragma("GCC visibility pop")
#ಇಲ್ಲದಿದ್ದರೆ
#    define attribute_visibility_hidden
#    define FF_VISIBILITY_ತಳ್ಳು_HIDDEN
#    define FF_VISIBILITY_ತೆಗೆ_HIDDEN
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು EXTERN ಬಾಹ್ಯ attribute_visibility_hidden

#ಆದರೆ (AV_HAS_ATTRIBUTE(nonstring) && (AV_GCC_ಆವೃತ್ತಿ_AT_ಕನಿಷ್ಠ(15,1) || defined(__clang__)))
// Attribute to mark a variable initialized via a string literal as not
// containing string data to suppress warnings about unterminated strings
// in situations like char fourcc[4] = "TALB".
#ವ್ಯಾಖ್ಯಾನಿಸು attribute_nonstring __attribute__((nonstring))
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು attribute_nonstring
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_ATTRIBUTES_INTERNAL_H */
