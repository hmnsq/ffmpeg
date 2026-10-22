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

#অন্তর্ভাব <stddef.h>
#অন্তর্ভাব <stdint.h>

#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "tdrdi.h"

AV3DReferenceDisplaysInfo *av_tdrdi_alloc(unsigned পূর্ণসংখ্যা nb_displays, size_t *out_আকার)
{
    কাঠামো TestStruct {
        AV3DReferenceDisplaysInfo p;
        AV3DReferenceDisplay      b;
    };
    ধ্রুবক size_t entries_offset = offsetof(কাঠামো TestStruct, b);
    size_t আকার_2 = entries_offset;
    AV3DReferenceDisplaysInfo *tdrdi;

    যদি (nb_displays > (SIZE_MAX - আকার_2) / আকার(AV3DReferenceDisplay))
        ফেরত ফাঁকা;
    আকার_2 += আকার(AV3DReferenceDisplay) * nb_displays;

    tdrdi = av_mallocz(আকার_2);
    যদি (!tdrdi)
        ফেরত ফাঁকা;

    tdrdi->অঙ্ক_ref_displays = nb_displays;
    tdrdi->entry_আকার       = আকার(AV3DReferenceDisplay);
    tdrdi->entries_offset   = entries_offset;

    যদি (out_আকার)
        *out_আকার = আকার_2;

    ফেরত tdrdi;
}
