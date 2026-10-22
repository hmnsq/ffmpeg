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

#অন্তর্ভাৱ <limits.h>
#অন্তর্ভাৱ <stdint.h>
#অন্তর্ভাৱ <stdio.h>

#অন্তর্ভাৱ "libavutil/mem.h"
#অন্তর্ভাৱ "libavutil/tdrdi.h"

পূর্ণাঙ্ক main(শূন্য)
{
    AV3DReferenceDisplaysInfo *tdrdi;
    AV3DReferenceDisplay *display;
    size_t size;

    /* av_tdrdi_alloc with 1 display */
    printf("Testing av_tdrdi_alloc()\n");
    tdrdi = av_tdrdi_alloc(1, &size);
    যদি (tdrdi) {
        printf("alloc 1: size>0=%s, num_ref_displays=%u\n",
               size > 0 ? "yes" : "no", tdrdi->অঙ্ক_ref_displays);

        display = av_tdrdi_get_display(tdrdi, 0);
        /* pointer consistency check */
        যদি ((uint8_t *)display != (uint8_t *)tdrdi + tdrdi->entries_offset)
            printf("display 0: pointer inconsistent with entries_offset\n");

        /* write and read back */
        display->exponent_ref_display_width = 3;
        display->mantissa_ref_display_width = 100;
        display->বাম_view_id = 0;
        display->ডান_view_id = 1;
        display = av_tdrdi_get_display(tdrdi, 0);
        printf("display 0: width_exp=%u width_man=%u left=%u right=%u\n",
               display->exponent_ref_display_width,
               display->mantissa_ref_display_width,
               display->বাম_view_id, display->ডান_view_id);
        av_free(tdrdi);
    }

    /* alloc with multiple displays */
    printf("\nTesting multiple displays\n");
    tdrdi = av_tdrdi_alloc(3, &size);
    যদি (tdrdi) {
        printf("alloc 3: num_ref_displays=%u\n", tdrdi->অঙ্ক_ref_displays);
        বাবে (পূর্ণাঙ্ক i = 0; i < 3; i++) {
            display = av_tdrdi_get_display(tdrdi, i);
            /* verify stride consistency */
            যদি ((uint8_t *)display != (uint8_t *)tdrdi + tdrdi->entries_offset +
                                      (size_t)i * tdrdi->entry_size)
                printf("display %d: pointer inconsistent\n", i);
            display->exponent_ref_display_width = i + 1;
        }
        বাবে (পূর্ণাঙ্ক i = 0; i < 3; i++) {
            display = av_tdrdi_get_display(tdrdi, i);
            printf("display %d: width_exp=%u\n", i,
                   display->exponent_ref_display_width);
        }
        av_free(tdrdi);
    }

    /* alloc with NULL size */
    tdrdi = av_tdrdi_alloc(1, রিক্ত);
    printf("\nalloc (no size): %s\n", tdrdi ? "OK" : "FAIL");
    av_free(tdrdi);

    /* OOM paths via av_max_alloc */
    printf("\nTesting OOM paths\n");
    av_max_alloc(1);
    tdrdi = av_tdrdi_alloc(1, &size);
    printf("alloc OOM: %s\n", tdrdi ? "FAIL" : "OK");
    av_free(tdrdi);
    av_max_alloc(INT_MAX);

    ঘূৰাই 0;
}
