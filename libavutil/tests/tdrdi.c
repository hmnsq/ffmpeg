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

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"
#ಅನ್ತರ್ಭಾವ "libavutil/tdrdi.h"

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    AV3DReferenceDisplaysInfo *tdrdi;
    AV3DReferenceDisplay *display;
    size_t ಗಾತ್ರ_2;

    /* av_tdrdi_alloc with 1 display */
    ಬರೆ("Testing av_tdrdi_alloc()\n");
    tdrdi = av_tdrdi_alloc(1, &ಗಾತ್ರ_2);
    ಆದರೆ (tdrdi) {
        ಬರೆ("alloc 1: size>0=%s, num_ref_displays=%u\n",
               ಗಾತ್ರ_2 > 0 ? "yes" : "no", tdrdi->ಅಂಕೆ_ref_displays);

        display = av_tdrdi_get_display(tdrdi, 0);
        /* pointer consistency check */
        ಆದರೆ ((uint8_t *)display != (uint8_t *)tdrdi + tdrdi->entries_ಸ್ಥಾನಾಂತರ)
            ಬರೆ("display 0: pointer inconsistent with entries_offset\n");

        /* write and read back */
        display->exponent_ref_display_ಅಗಲ = 3;
        display->mantissa_ref_display_ಅಗಲ = 100;
        display->ಎಡ_view_id = 0;
        display->ಬಲ_view_id = 1;
        display = av_tdrdi_get_display(tdrdi, 0);
        ಬರೆ("display 0: width_exp=%u width_man=%u left=%u right=%u\n",
               display->exponent_ref_display_ಅಗಲ,
               display->mantissa_ref_display_ಅಗಲ,
               display->ಎಡ_view_id, display->ಬಲ_view_id);
        av_free(tdrdi);
    }

    /* alloc with multiple displays */
    ಬರೆ("\nTesting multiple displays\n");
    tdrdi = av_tdrdi_alloc(3, &ಗಾತ್ರ_2);
    ಆದರೆ (tdrdi) {
        ಬರೆ("alloc 3: num_ref_displays=%u\n", tdrdi->ಅಂಕೆ_ref_displays);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 3; i++) {
            display = av_tdrdi_get_display(tdrdi, i);
            /* verify stride consistency */
            ಆದರೆ ((uint8_t *)display != (uint8_t *)tdrdi + tdrdi->entries_ಸ್ಥಾನಾಂತರ +
                                      (size_t)i * tdrdi->ನಮೂದು_ಗಾತ್ರ)
                ಬರೆ("display %d: pointer inconsistent\n", i);
            display->exponent_ref_display_ಅಗಲ = i + 1;
        }
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 3; i++) {
            display = av_tdrdi_get_display(tdrdi, i);
            ಬರೆ("display %d: width_exp=%u\n", i,
                   display->exponent_ref_display_ಅಗಲ);
        }
        av_free(tdrdi);
    }

    /* alloc with NULL size */
    tdrdi = av_tdrdi_alloc(1, ಖಾಲಿ);
    ಬರೆ("\nalloc (no size): %s\n", tdrdi ? "OK" : "FAIL");
    av_free(tdrdi);

    /* OOM paths via av_max_alloc */
    ಬರೆ("\nTesting OOM paths\n");
    av_max_alloc(1);
    tdrdi = av_tdrdi_alloc(1, &ಗಾತ್ರ_2);
    ಬರೆ("alloc OOM: %s\n", tdrdi ? "FAIL" : "OK");
    av_free(tdrdi);
    av_max_alloc(ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);

    ಹಿಂತಿರುಗಿ 0;
}
