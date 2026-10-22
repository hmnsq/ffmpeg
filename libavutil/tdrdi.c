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

AV3DReferenceDisplaysInfo *av_tdrdi_alloc(unsigned পূর্ণাঙ্ক nb_displays, size_t *out_size)
{
    সংরচনা TestStruct {
        AV3DReferenceDisplaysInfo p;
        AV3DReferenceDisplay      b;
    };
    ধ্রুব size_t entries_offset = offsetof(সংরচনা TestStruct, b);
    size_t size = entries_offset;
    AV3DReferenceDisplaysInfo *tdrdi;

    যদি (nb_displays > (SIZE_MAX - size) / পরিমাণ(AV3DReferenceDisplay))
        প্রত্যাগম রিক্ত;
    size += পরিমাণ(AV3DReferenceDisplay) * nb_displays;

    tdrdi = av_mallocz(size);
    যদি (!tdrdi)
        প্রত্যাগম রিক্ত;

    tdrdi->অঙ্ক_ref_displays = nb_displays;
    tdrdi->entry_size       = পরিমাণ(AV3DReferenceDisplay);
    tdrdi->entries_offset   = entries_offset;

    যদি (out_size)
        *out_size = size;

    প্রত্যাগম tdrdi;
}
