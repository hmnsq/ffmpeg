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

पूर्णाङ्क मुख्यम्(शून्य)
{
    AV3DReferenceDisplaysInfo *tdrdi;
    AV3DReferenceDisplay *display;
    size_t आकार;

    /* av_tdrdi_alloc with 1 display */
    प्रारूप_लिख("Testing av_tdrdi_alloc()\n");
    tdrdi = av_tdrdi_alloc(1, &आकार);
    यदि (tdrdi) {
        प्रारूप_लिख("alloc 1: size>0=%s, num_ref_displays=%u\n",
               आकार > 0 ? "yes" : "no", tdrdi->अङ्कः_ref_displays);

        display = av_tdrdi_get_display(tdrdi, 0);
        /* pointer consistency check */
        यदि ((uint8_t *)display != (uint8_t *)tdrdi + tdrdi->entries_विस्थापनम्)
            प्रारूप_लिख("display 0: pointer inconsistent with entries_offset\n");

        /* write and read back */
        display->exponent_ref_display_विस्तारः = 3;
        display->mantissa_ref_display_विस्तारः = 100;
        display->वामः_view_id = 0;
        display->दक्षिणः_view_id = 1;
        display = av_tdrdi_get_display(tdrdi, 0);
        प्रारूप_लिख("display 0: width_exp=%u width_man=%u left=%u right=%u\n",
               display->exponent_ref_display_विस्तारः,
               display->mantissa_ref_display_विस्तारः,
               display->वामः_view_id, display->दक्षिणः_view_id);
        av_free(tdrdi);
    }

    /* alloc with multiple displays */
    प्रारूप_लिख("\nTesting multiple displays\n");
    tdrdi = av_tdrdi_alloc(3, &आकार);
    यदि (tdrdi) {
        प्रारूप_लिख("alloc 3: num_ref_displays=%u\n", tdrdi->अङ्कः_ref_displays);
        प्रति (पूर्णाङ्क i = 0; i < 3; i++) {
            display = av_tdrdi_get_display(tdrdi, i);
            /* verify stride consistency */
            यदि ((uint8_t *)display != (uint8_t *)tdrdi + tdrdi->entries_विस्थापनम् +
                                      (size_t)i * tdrdi->प्रविष्टिः_आकार)
                प्रारूप_लिख("display %d: pointer inconsistent\n", i);
            display->exponent_ref_display_विस्तारः = i + 1;
        }
        प्रति (पूर्णाङ्क i = 0; i < 3; i++) {
            display = av_tdrdi_get_display(tdrdi, i);
            प्रारूप_लिख("display %d: width_exp=%u\n", i,
                   display->exponent_ref_display_विस्तारः);
        }
        av_free(tdrdi);
    }

    /* alloc with NULL size */
    tdrdi = av_tdrdi_alloc(1, रिक्त);
    प्रारूप_लिख("\nalloc (no size): %s\n", tdrdi ? "OK" : "FAIL");
    av_free(tdrdi);

    /* OOM paths via av_max_alloc */
    प्रारूप_लिख("\nTesting OOM paths\n");
    av_max_alloc(1);
    tdrdi = av_tdrdi_alloc(1, &आकार);
    प्रारूप_लिख("alloc OOM: %s\n", tdrdi ? "FAIL" : "OK");
    av_free(tdrdi);
    av_max_alloc(अधिकतम_पूर्णाङ्कः);

    प्रत्यागम 0;
}
