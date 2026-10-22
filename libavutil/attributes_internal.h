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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_ਗੁਣ_ਅੰਦਰੂਨੀ_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_ਗੁਣ_ਅੰਦਰੂਨੀ_H

#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"

#ਜੇ (defined(__GNUC__) || defined(__clang__)) && (defined(__ELF__) || defined(__MACH__))
#    define attribute_visibility_hidden __attribute__((visibility("hidden")))
#    define FF_VISIBILITY_ਧੱਕੋ_HIDDEN   _Pragma("GCC visibility push(hidden)")
#    define FF_VISIBILITY_ਕੱਢੋ_HIDDEN    _Pragma("GCC visibility pop")
#ਨਹੀਂਤਾਂ
#    define attribute_visibility_hidden
#    define FF_VISIBILITY_ਧੱਕੋ_HIDDEN
#    define FF_VISIBILITY_ਕੱਢੋ_HIDDEN
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERN ਬਾਹਰੀ attribute_visibility_hidden

#ਜੇ (AV_HAS_ATTRIBUTE(nonstring) && (AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(15,1) || defined(__clang__)))
// Attribute to mark a variable initialized via a string literal as not
// containing string data to suppress warnings about unterminated strings
// in situations like char fourcc[4] = "TALB".
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ attribute_nonstring __attribute__((nonstring))
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ attribute_nonstring
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* AVUTIL_ATTRIBUTES_INTERNAL_H */
