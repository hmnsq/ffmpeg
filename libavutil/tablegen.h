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

/**
 * @file
 * Compatibility libm for table generation files
 */

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_TABLEGEN_H
#وصف_ڪريو AVUTIL_TABLEGEN_H

#ضمن <math.h>

// we lack some functions on all host platforms, and we don't care about
// performance and/or strict ISO C semantics as it's performed at build time
ساكن مضمن مزدوج ff_cbrt(مزدوج x)
{
    أرجع x < 0 ? -قوت(-x, 1.0 / 3.0) : قوت(x, 1.0 / 3.0);
}
#وصف_ڪريو cbrt ff_cbrt

ساكن مضمن مزدوج ff_rint(مزدوج x)
{
    أرجع x >= 0 ? floor(x + 0.5) : ceil(x - 0.5);
}
#وصف_ڪريو rint ff_rint

ساكن مضمن ڊگهو ڊگهو ff_llrint(مزدوج x)
{
    أرجع rint(x);
}
#وصف_ڪريو llrint ff_llrint

ساكن مضمن ڊگهو ff_lrint(مزدوج x)
{
    أرجع rint(x);
}
#وصف_ڪريو lrint ff_lrint

#جيڪڏهن_پورو /* AVUTIL_TABLEGEN_H */
