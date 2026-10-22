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

#અન્તર્ભાવ <stddef.h>
#અન્તર્ભાવ <stdint.h>

#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "tdrdi.h"

AV3DReferenceDisplaysInfo *av_tdrdi_alloc(unsigned પૂર્ણાંક nb_displays, size_t *out_size)
{
    સંરચના TestStruct {
        AV3DReferenceDisplaysInfo p;
        AV3DReferenceDisplay      b;
    };
    અચલ size_t entries_offset = offsetof(સંરચના TestStruct, b);
    size_t size = entries_offset;
    AV3DReferenceDisplaysInfo *tdrdi;

    જો (nb_displays > (SIZE_MAX - size) / કદ(AV3DReferenceDisplay))
        પાછા ખાલી;
    size += કદ(AV3DReferenceDisplay) * nb_displays;

    tdrdi = av_mallocz(size);
    જો (!tdrdi)
        પાછા ખાલી;

    tdrdi->અંક_ref_displays = nb_displays;
    tdrdi->entry_size       = કદ(AV3DReferenceDisplay);
    tdrdi->entries_offset   = entries_offset;

    જો (out_size)
        *out_size = size;

    પાછા tdrdi;
}
