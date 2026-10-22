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

#यदि_अपरिभाषितम् AVUTIL_गुणाः_आन्तरिकम्_H
#परिभाषय AVUTIL_गुणाः_आन्तरिकम्_H

#अन्तर्भाव "attributes.h"

#यदि (defined(__GNUC__) || defined(__clang__)) && (defined(__ELF__) || defined(__MACH__))
#    define attribute_visibility_hidden __attribute__((visibility("hidden")))
#    define FF_VISIBILITY_प्रक्षिप_HIDDEN   _Pragma("GCC visibility push(hidden)")
#    define FF_VISIBILITY_निष्कासय_HIDDEN    _Pragma("GCC visibility pop")
#अन्यथा
#    define attribute_visibility_hidden
#    define FF_VISIBILITY_प्रक्षिप_HIDDEN
#    define FF_VISIBILITY_निष्कासय_HIDDEN
#यदि_अन्तः

#परिभाषय EXTERN बाह्य attribute_visibility_hidden

#यदि (AV_HAS_ATTRIBUTE(nonstring) && (AV_GCC_संस्करणम्_AT_न्यूनतमम्(15,1) || defined(__clang__)))
// Attribute to mark a variable initialized via a string literal as not
// containing string data to suppress warnings about unterminated strings
// in situations like char fourcc[4] = "TALB".
#परिभाषय attribute_nonstring __attribute__((nonstring))
#अन्यथा
#परिभाषय attribute_nonstring
#यदि_अन्तः

#यदि_अन्तः /* AVUTIL_ATTRIBUTES_INTERNAL_H */
