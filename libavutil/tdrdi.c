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

#شامل <stddef.h>
#شامل <stdint.h>

#شامل "mem.h"
#شامل "tdrdi.h"

AV3DReferenceDisplaysInfo *av_tdrdi_alloc(غیرعلامتی صحیح nb_displays, size_t *برآمد_سائز)
{
    ساخت TestStruct {
        AV3DReferenceDisplaysInfo p;
        AV3DReferenceDisplay      b;
    };
    ثابت size_t entries_انحراف = offsetof(ساخت TestStruct, b);
    size_t سائز = entries_انحراف;
    AV3DReferenceDisplaysInfo *tdrdi;

    اگر (nb_displays > (SIZE_MAX - سائز) / حجم(AV3DReferenceDisplay))
        واپس تہی;
    سائز += حجم(AV3DReferenceDisplay) * nb_displays;

    tdrdi = av_mallocz(سائز);
    اگر (!tdrdi)
        واپس تہی;

    tdrdi->عدد_ref_displays = nb_displays;
    tdrdi->اندراج_سائز       = حجم(AV3DReferenceDisplay);
    tdrdi->entries_انحراف   = entries_انحراف;

    اگر (برآمد_سائز)
        *برآمد_سائز = سائز;

    واپس tdrdi;
}
