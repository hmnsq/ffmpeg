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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_TABLEGEN_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_TABLEGEN_H

#ಅನ್ತರ್ಭಾವ <math.h>

// we lack some functions on all host platforms, and we don't care about
// performance and/or strict ISO C semantics as it's performed at build time
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ದ್ವಿಗುಣ ff_cbrt(ದ್ವಿಗುಣ x)
{
    ಹಿಂತಿರುಗಿ x < 0 ? -ಘಾತ(-x, 1.0 / 3.0) : ಘಾತ(x, 1.0 / 3.0);
}
#ವ್ಯಾಖ್ಯಾನಿಸು cbrt ff_cbrt

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ದ್ವಿಗುಣ ff_rint(ದ್ವಿಗುಣ x)
{
    ಹಿಂತಿರುಗಿ x >= 0 ? floor(x + 0.5) : ceil(x - 0.5);
}
#ವ್ಯಾಖ್ಯಾನಿಸು rint ff_rint

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ದೀರ್ಘ ದೀರ್ಘ ff_llrint(ದ್ವಿಗುಣ x)
{
    ಹಿಂತಿರುಗಿ rint(x);
}
#ವ್ಯಾಖ್ಯಾನಿಸು llrint ff_llrint

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ದೀರ್ಘ ff_lrint(ದ್ವಿಗುಣ x)
{
    ಹಿಂತಿರುಗಿ rint(x);
}
#ವ್ಯಾಖ್ಯಾನಿಸು lrint ff_lrint

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_TABLEGEN_H */
