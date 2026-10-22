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

#اگر_غیر_تعریف_شدہ AVUTIL_اوصاف_اندرونی_H
#تعریف_کرو AVUTIL_اوصاف_اندرونی_H

#شامل "attributes.h"

#اگر (defined(__GNUC__) || defined(__clang__)) && (defined(__ELF__) || defined(__MACH__))
#    define attribute_visibility_hidden __attribute__((visibility("hidden")))
#    define FF_VISIBILITY_ڈالو_HIDDEN   _Pragma("GCC visibility push(hidden)")
#    define FF_VISIBILITY_نکالو_HIDDEN    _Pragma("GCC visibility pop")
#ورنہ
#    define attribute_visibility_hidden
#    define FF_VISIBILITY_ڈالو_HIDDEN
#    define FF_VISIBILITY_نکالو_HIDDEN
#اگر_ختم

#تعریف_کرو EXTERN خارجی attribute_visibility_hidden

#اگر (AV_HAS_ATTRIBUTE(nonstring) && (AV_GCC_نسخہ_AT_کم_سے_کم(15,1) || defined(__clang__)))
// Attribute to mark a variable initialized via a string literal as not
// containing string data to suppress warnings about unterminated strings
// in situations like char fourcc[4] = "TALB".
#تعریف_کرو attribute_nonstring __attribute__((nonstring))
#ورنہ
#تعریف_کرو attribute_nonstring
#اگر_ختم

#اگر_ختم /* AVUTIL_ATTRIBUTES_INTERNAL_H */
