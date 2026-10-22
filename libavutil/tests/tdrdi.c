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

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/mem.h"
#అన్తర్భావ "libavutil/tdrdi.h"

పూర్ణాంకం ప్రధాన(శూన్య)
{
    AV3DReferenceDisplaysInfo *tdrdi;
    AV3DReferenceDisplay *display;
    size_t కొలత;

    /* av_tdrdi_alloc with 1 display */
    రాయి("Testing av_tdrdi_alloc()\n");
    tdrdi = av_tdrdi_alloc(1, &కొలత);
    ఒకవేళ (tdrdi) {
        రాయి("alloc 1: size>0=%s, num_ref_displays=%u\n",
               కొలత > 0 ? "yes" : "no", tdrdi->అంకె_ref_displays);

        display = av_tdrdi_get_display(tdrdi, 0);
        /* pointer consistency check */
        ఒకవేళ ((uint8_t *)display != (uint8_t *)tdrdi + tdrdi->entries_స్థానభ్రంశం)
            రాయి("display 0: pointer inconsistent with entries_offset\n");

        /* write and read back */
        display->exponent_ref_display_వెడల్పు = 3;
        display->mantissa_ref_display_వెడల్పు = 100;
        display->ఎడమ_view_id = 0;
        display->కుడి_view_id = 1;
        display = av_tdrdi_get_display(tdrdi, 0);
        రాయి("display 0: width_exp=%u width_man=%u left=%u right=%u\n",
               display->exponent_ref_display_వెడల్పు,
               display->mantissa_ref_display_వెడల్పు,
               display->ఎడమ_view_id, display->కుడి_view_id);
        av_free(tdrdi);
    }

    /* alloc with multiple displays */
    రాయి("\nTesting multiple displays\n");
    tdrdi = av_tdrdi_alloc(3, &కొలత);
    ఒకవేళ (tdrdi) {
        రాయి("alloc 3: num_ref_displays=%u\n", tdrdi->అంకె_ref_displays);
        కొరకు (పూర్ణాంకం i = 0; i < 3; i++) {
            display = av_tdrdi_get_display(tdrdi, i);
            /* verify stride consistency */
            ఒకవేళ ((uint8_t *)display != (uint8_t *)tdrdi + tdrdi->entries_స్థానభ్రంశం +
                                      (size_t)i * tdrdi->నమోదు_కొలత)
                రాయి("display %d: pointer inconsistent\n", i);
            display->exponent_ref_display_వెడల్పు = i + 1;
        }
        కొరకు (పూర్ణాంకం i = 0; i < 3; i++) {
            display = av_tdrdi_get_display(tdrdi, i);
            రాయి("display %d: width_exp=%u\n", i,
                   display->exponent_ref_display_వెడల్పు);
        }
        av_free(tdrdi);
    }

    /* alloc with NULL size */
    tdrdi = av_tdrdi_alloc(1, ఖాళీ);
    రాయి("\nalloc (no size): %s\n", tdrdi ? "OK" : "FAIL");
    av_free(tdrdi);

    /* OOM paths via av_max_alloc */
    రాయి("\nTesting OOM paths\n");
    av_max_alloc(1);
    tdrdi = av_tdrdi_alloc(1, &కొలత);
    రాయి("alloc OOM: %s\n", tdrdi ? "FAIL" : "OK");
    av_free(tdrdi);
    av_max_alloc(గరిష్ఠ_పూర్ణాంకం);

    తిరిగి 0;
}
