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

#அந்தர்பாவ <stddef.h>
#அந்தர்பாவ <stdint.h>

#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "tdrdi.h"

AV3DReferenceDisplaysInfo *av_tdrdi_alloc(unsigned முழு nb_displays, size_t *out_size)
{
    கட்டமைப்பு TestStruct {
        AV3DReferenceDisplaysInfo p;
        AV3DReferenceDisplay      b;
    };
    மாறிலி size_t entries_offset = offsetof(கட்டமைப்பு TestStruct, b);
    size_t size = entries_offset;
    AV3DReferenceDisplaysInfo *tdrdi;

    எனில் (nb_displays > (SIZE_MAX - size) / அளவு(AV3DReferenceDisplay))
        திரும்பு வெற்று;
    size += அளவு(AV3DReferenceDisplay) * nb_displays;

    tdrdi = av_mallocz(size);
    எனில் (!tdrdi)
        திரும்பு வெற்று;

    tdrdi->இலக்கம்_ref_displays = nb_displays;
    tdrdi->entry_size       = அளவு(AV3DReferenceDisplay);
    tdrdi->entries_offset   = entries_offset;

    எனில் (out_size)
        *out_size = size;

    திரும்பு tdrdi;
}
