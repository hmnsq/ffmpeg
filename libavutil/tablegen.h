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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_TABLEGEN_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_TABLEGEN_H

#ਅਨ੍ਤਰ੍ਭਾਵ <math.h>

// we lack some functions on all host platforms, and we don't care about
// performance and/or strict ISO C semantics as it's performed at build time
ਸਥਿਰ ਸਤਰਅੰਦਰ ਦੁੱਗਣਾ ff_cbrt(ਦੁੱਗਣਾ x)
{
    ਵਾਪਸ x < 0 ? -ਘਾਤ(-x, 1.0 / 3.0) : ਘਾਤ(x, 1.0 / 3.0);
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ cbrt ff_cbrt

ਸਥਿਰ ਸਤਰਅੰਦਰ ਦੁੱਗਣਾ ff_rint(ਦੁੱਗਣਾ x)
{
    ਵਾਪਸ x >= 0 ? floor(x + 0.5) : ceil(x - 0.5);
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ rint ff_rint

ਸਥਿਰ ਸਤਰਅੰਦਰ ਲੰਮਾ ਲੰਮਾ ff_llrint(ਦੁੱਗਣਾ x)
{
    ਵਾਪਸ rint(x);
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ llrint ff_llrint

ਸਥਿਰ ਸਤਰਅੰਦਰ ਲੰਮਾ ff_lrint(ਦੁੱਗਣਾ x)
{
    ਵਾਪਸ rint(x);
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ lrint ff_lrint

#ਜੇ_ਅੰਤ /* AVUTIL_TABLEGEN_H */
