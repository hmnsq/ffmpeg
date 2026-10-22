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

#अन्तर्भाव <limits.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdio.h>

#अन्तर्भाव "libavutil/mem.h"
#अन्तर्भाव "libavutil/tdrdi.h"

पूर्णाङ्क main(शून्य)
{
    AV3DReferenceDisplaysInfo *tdrdi;
    AV3DReferenceDisplay *display;
    माप_प्रकार size;

    /* av_tdrdi_alloc with 1 display */
    म_लिखो("Testing av_tdrdi_alloc()\n");
    tdrdi = av_tdrdi_alloc(1, &size);
    यदि (tdrdi) {
        म_लिखो("alloc 1: size>0=%s, num_ref_displays=%u\n",
               size > 0 ? "yes" : "no", tdrdi->अङ्क_ref_displays);

        display = av_tdrdi_get_display(tdrdi, 0);
        /* pointer consistency check */
        यदि ((uint8_t *)display != (uint8_t *)tdrdi + tdrdi->entries_offset)
            म_लिखो("display 0: pointer inconsistent with entries_offset\n");

        /* write and read back */
        display->exponent_ref_display_width = 3;
        display->mantissa_ref_display_width = 100;
        display->बायाँ_view_id = 0;
        display->दायाँ_view_id = 1;
        display = av_tdrdi_get_display(tdrdi, 0);
        म_लिखो("display 0: width_exp=%u width_man=%u left=%u right=%u\n",
               display->exponent_ref_display_width,
               display->mantissa_ref_display_width,
               display->बायाँ_view_id, display->दायाँ_view_id);
        av_free(tdrdi);
    }

    /* alloc with multiple displays */
    म_लिखो("\nTesting multiple displays\n");
    tdrdi = av_tdrdi_alloc(3, &size);
    यदि (tdrdi) {
        म_लिखो("alloc 3: num_ref_displays=%u\n", tdrdi->अङ्क_ref_displays);
        लागि (पूर्णाङ्क i = 0; i < 3; i++) {
            display = av_tdrdi_get_display(tdrdi, i);
            /* verify stride consistency */
            यदि ((uint8_t *)display != (uint8_t *)tdrdi + tdrdi->entries_offset +
                                      (माप_प्रकार)i * tdrdi->entry_size)
                म_लिखो("display %d: pointer inconsistent\n", i);
            display->exponent_ref_display_width = i + 1;
        }
        लागि (पूर्णाङ्क i = 0; i < 3; i++) {
            display = av_tdrdi_get_display(tdrdi, i);
            म_लिखो("display %d: width_exp=%u\n", i,
                   display->exponent_ref_display_width);
        }
        av_free(tdrdi);
    }

    /* alloc with NULL size */
    tdrdi = av_tdrdi_alloc(1, रिक्त);
    म_लिखो("\nalloc (no size): %s\n", tdrdi ? "OK" : "FAIL");
    av_free(tdrdi);

    /* OOM paths via av_max_alloc */
    म_लिखो("\nTesting OOM paths\n");
    av_max_alloc(1);
    tdrdi = av_tdrdi_alloc(1, &size);
    म_लिखो("alloc OOM: %s\n", tdrdi ? "FAIL" : "OK");
    av_free(tdrdi);
    av_max_alloc(पूर्णांक_उच्च);

    फर्काऊ 0;
}
