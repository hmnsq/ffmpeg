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

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/tdrdi.h"

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    AV3DReferenceDisplaysInfo *tdrdi;
    AV3DReferenceDisplay *display;
    size_t ਮਾਪ;

    /* av_tdrdi_alloc with 1 display */
    ਲਿਖੋ("Testing av_tdrdi_alloc()\n");
    tdrdi = av_tdrdi_alloc(1, &ਮਾਪ);
    ਜੇ (tdrdi) {
        ਲਿਖੋ("alloc 1: size>0=%s, num_ref_displays=%u\n",
               ਮਾਪ > 0 ? "yes" : "no", tdrdi->ਅੰਕ_ref_displays);

        display = av_tdrdi_get_display(tdrdi, 0);
        /* pointer consistency check */
        ਜੇ ((uint8_t *)display != (uint8_t *)tdrdi + tdrdi->entries_ਵਿੱਥ)
            ਲਿਖੋ("display 0: pointer inconsistent with entries_offset\n");

        /* write and read back */
        display->exponent_ref_display_ਚੌੜਾਈ = 3;
        display->mantissa_ref_display_ਚੌੜਾਈ = 100;
        display->ਖੱਬਾ_view_id = 0;
        display->ਸੱਜਾ_view_id = 1;
        display = av_tdrdi_get_display(tdrdi, 0);
        ਲਿਖੋ("display 0: width_exp=%u width_man=%u left=%u right=%u\n",
               display->exponent_ref_display_ਚੌੜਾਈ,
               display->mantissa_ref_display_ਚੌੜਾਈ,
               display->ਖੱਬਾ_view_id, display->ਸੱਜਾ_view_id);
        av_free(tdrdi);
    }

    /* alloc with multiple displays */
    ਲਿਖੋ("\nTesting multiple displays\n");
    tdrdi = av_tdrdi_alloc(3, &ਮਾਪ);
    ਜੇ (tdrdi) {
        ਲਿਖੋ("alloc 3: num_ref_displays=%u\n", tdrdi->ਅੰਕ_ref_displays);
        ਲਈ (ਪੂਰਨ i = 0; i < 3; i++) {
            display = av_tdrdi_get_display(tdrdi, i);
            /* verify stride consistency */
            ਜੇ ((uint8_t *)display != (uint8_t *)tdrdi + tdrdi->entries_ਵਿੱਥ +
                                      (size_t)i * tdrdi->ਇੰਦਰਾਜ_ਮਾਪ)
                ਲਿਖੋ("display %d: pointer inconsistent\n", i);
            display->exponent_ref_display_ਚੌੜਾਈ = i + 1;
        }
        ਲਈ (ਪੂਰਨ i = 0; i < 3; i++) {
            display = av_tdrdi_get_display(tdrdi, i);
            ਲਿਖੋ("display %d: width_exp=%u\n", i,
                   display->exponent_ref_display_ਚੌੜਾਈ);
        }
        av_free(tdrdi);
    }

    /* alloc with NULL size */
    tdrdi = av_tdrdi_alloc(1, ਨਿਰਾ);
    ਲਿਖੋ("\nalloc (no size): %s\n", tdrdi ? "OK" : "FAIL");
    av_free(tdrdi);

    /* OOM paths via av_max_alloc */
    ਲਿਖੋ("\nTesting OOM paths\n");
    av_max_alloc(1);
    tdrdi = av_tdrdi_alloc(1, &ਮਾਪ);
    ਲਿਖੋ("alloc OOM: %s\n", tdrdi ? "FAIL" : "OK");
    av_free(tdrdi);
    av_max_alloc(ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);

    ਵਾਪਸ 0;
}
