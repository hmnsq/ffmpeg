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

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "tdrdi.h"

AV3DReferenceDisplaysInfo *av_tdrdi_alloc(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ nb_displays, size_t *ಹೊರಹೋಗು_ಗಾತ್ರ)
{
    ರಚನೆ TestStruct {
        AV3DReferenceDisplaysInfo p;
        AV3DReferenceDisplay      b;
    };
    ಸ್ಥಿರಾಂಕ size_t entries_ಸ್ಥಾನಾಂತರ = offsetof(ರಚನೆ TestStruct, b);
    size_t ಗಾತ್ರ_2 = entries_ಸ್ಥಾನಾಂತರ;
    AV3DReferenceDisplaysInfo *tdrdi;

    ಆದರೆ (nb_displays > (SIZE_MAX - ಗಾತ್ರ_2) / ಗಾತ್ರ(AV3DReferenceDisplay))
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಗಾತ್ರ_2 += ಗಾತ್ರ(AV3DReferenceDisplay) * nb_displays;

    tdrdi = av_mallocz(ಗಾತ್ರ_2);
    ಆದರೆ (!tdrdi)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    tdrdi->ಅಂಕೆ_ref_displays = nb_displays;
    tdrdi->ನಮೂದು_ಗಾತ್ರ       = ಗಾತ್ರ(AV3DReferenceDisplay);
    tdrdi->entries_ಸ್ಥಾನಾಂತರ   = entries_ಸ್ಥಾನಾಂತರ;

    ಆದರೆ (ಹೊರಹೋಗು_ಗಾತ್ರ)
        *ಹೊರಹೋಗು_ಗಾತ್ರ = ಗಾತ್ರ_2;

    ಹಿಂತಿರುಗಿ tdrdi;
}
