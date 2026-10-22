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

#ضمن <limits.h>
#ضمن <stdint.h>
#ضمن <stdio.h>

#ضمن "libavutil/mem.h"
#ضمن "libavutil/tdrdi.h"

صحيح اصلی(فراغ)
{
    AV3DReferenceDisplaysInfo *tdrdi;
    AV3DReferenceDisplay *display;
    size_t اندازه;

    /* av_tdrdi_alloc with 1 display */
    چاپ_کن("Testing av_tdrdi_alloc()\n");
    tdrdi = av_tdrdi_alloc(1, &اندازه);
    إذا (tdrdi) {
        چاپ_کن("alloc 1: size>0=%s, num_ref_displays=%u\n",
               اندازه > 0 ? "yes" : "no", tdrdi->رقم_ref_displays);

        display = av_tdrdi_get_display(tdrdi, 0);
        /* pointer consistency check */
        إذا ((uint8_t *)display != (uint8_t *)tdrdi + tdrdi->entries_جابه_جایی)
            چاپ_کن("display 0: pointer inconsistent with entries_offset\n");

        /* write and read back */
        display->exponent_ref_display_عرض = 3;
        display->mantissa_ref_display_عرض = 100;
        display->چپ_view_id = 0;
        display->راست_view_id = 1;
        display = av_tdrdi_get_display(tdrdi, 0);
        چاپ_کن("display 0: width_exp=%u width_man=%u left=%u right=%u\n",
               display->exponent_ref_display_عرض,
               display->mantissa_ref_display_عرض,
               display->چپ_view_id, display->راست_view_id);
        av_free(tdrdi);
    }

    /* alloc with multiple displays */
    چاپ_کن("\nTesting multiple displays\n");
    tdrdi = av_tdrdi_alloc(3, &اندازه);
    إذا (tdrdi) {
        چاپ_کن("alloc 3: num_ref_displays=%u\n", tdrdi->رقم_ref_displays);
        لكل (صحيح i = 0; i < 3; i++) {
            display = av_tdrdi_get_display(tdrdi, i);
            /* verify stride consistency */
            إذا ((uint8_t *)display != (uint8_t *)tdrdi + tdrdi->entries_جابه_جایی +
                                      (size_t)i * tdrdi->مدخل_اندازه)
                چاپ_کن("display %d: pointer inconsistent\n", i);
            display->exponent_ref_display_عرض = i + 1;
        }
        لكل (صحيح i = 0; i < 3; i++) {
            display = av_tdrdi_get_display(tdrdi, i);
            چاپ_کن("display %d: width_exp=%u\n", i,
                   display->exponent_ref_display_عرض);
        }
        av_free(tdrdi);
    }

    /* alloc with NULL size */
    tdrdi = av_tdrdi_alloc(1, عدم);
    چاپ_کن("\nalloc (no size): %s\n", tdrdi ? "OK" : "FAIL");
    av_free(tdrdi);

    /* OOM paths via av_max_alloc */
    چاپ_کن("\nTesting OOM paths\n");
    av_max_alloc(1);
    tdrdi = av_tdrdi_alloc(1, &اندازه);
    چاپ_کن("alloc OOM: %s\n", tdrdi ? "FAIL" : "OK");
    av_free(tdrdi);
    av_max_alloc(بیشترین_صحیح);

    أرجع 0;
}
