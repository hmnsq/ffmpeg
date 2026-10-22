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

#నిర్వచితం_కాకపోతే AVUTIL_లక్షణాలు_అంతర్గత_H
#నిర్వచించు AVUTIL_లక్షణాలు_అంతర్గత_H

#అన్తర్భావ "attributes.h"

#ఒకవేళ (defined(__GNUC__) || defined(__clang__)) && (defined(__ELF__) || defined(__MACH__))
#    define attribute_visibility_hidden __attribute__((visibility("hidden")))
#    define FF_VISIBILITY_నెట్టు_HIDDEN   _Pragma("GCC visibility push(hidden)")
#    define FF_VISIBILITY_తీయి_HIDDEN    _Pragma("GCC visibility pop")
#లేకపోతే
#    define attribute_visibility_hidden
#    define FF_VISIBILITY_నెట్టు_HIDDEN
#    define FF_VISIBILITY_తీయి_HIDDEN
#అయితే_ముగింపు

#నిర్వచించు EXTERN బాహ్య attribute_visibility_hidden

#ఒకవేళ (AV_HAS_ATTRIBUTE(nonstring) && (AV_GCC_సంస్కరణ_AT_కనిష్ఠ(15,1) || defined(__clang__)))
// Attribute to mark a variable initialized via a string literal as not
// containing string data to suppress warnings about unterminated strings
// in situations like char fourcc[4] = "TALB".
#నిర్వచించు attribute_nonstring __attribute__((nonstring))
#లేకపోతే
#నిర్వచించు attribute_nonstring
#అయితే_ముగింపు

#అయితే_ముగింపు /* AVUTIL_ATTRIBUTES_INTERNAL_H */
