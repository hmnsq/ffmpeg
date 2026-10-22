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

#که_نه_تعریف_شوی AVUTIL_ځانګړتیاوې_دننی_H
#تعریف_کړه AVUTIL_ځانګړتیاوې_دننی_H

#ضمن "attributes.h"

#إذا (defined(__GNUC__) || defined(__clang__)) && (defined(__ELF__) || defined(__MACH__))
#    define attribute_visibility_hidden __attribute__((visibility("hidden")))
#    define FF_VISIBILITY_ټېل_HIDDEN   _Pragma("GCC visibility push(hidden)")
#    define FF_VISIBILITY_راوباسه_HIDDEN    _Pragma("GCC visibility pop")
#وإلا
#    define attribute_visibility_hidden
#    define FF_VISIBILITY_ټېل_HIDDEN
#    define FF_VISIBILITY_راوباسه_HIDDEN
#د_که_پای

#تعریف_کړه EXTERN خارجي attribute_visibility_hidden

#إذا (AV_HAS_ATTRIBUTE(nonstring) && (AV_GCC_نسخه_AT_لږترلږه(15,1) || defined(__clang__)))
// Attribute to mark a variable initialized via a string literal as not
// containing string data to suppress warnings about unterminated strings
// in situations like char fourcc[4] = "TALB".
#تعریف_کړه attribute_nonstring __attribute__((nonstring))
#وإلا
#تعریف_کړه attribute_nonstring
#د_که_پای

#د_که_پای /* AVUTIL_ATTRIBUTES_INTERNAL_H */
