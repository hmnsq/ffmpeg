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

#ضمن <stddef.h>
#ضمن <stdint.h>

#ضمن "mem.h"
#ضمن "tdrdi.h"

AV3DReferenceDisplaysInfo *av_tdrdi_alloc(بنانشان صحيح nb_displays, size_t *ٻاهريون_سائيز)
{
    بنية TestStruct {
        AV3DReferenceDisplaysInfo p;
        AV3DReferenceDisplay      b;
    };
    ثابت size_t entries_وٿي = offsetof(بنية TestStruct, b);
    size_t سائيز = entries_وٿي;
    AV3DReferenceDisplaysInfo *tdrdi;

    إذا (nb_displays > (SIZE_MAX - سائيز) / حجم(AV3DReferenceDisplay))
        أرجع عدم;
    سائيز += حجم(AV3DReferenceDisplay) * nb_displays;

    tdrdi = av_mallocz(سائيز);
    إذا (!tdrdi)
        أرجع عدم;

    tdrdi->انگ_ref_displays = nb_displays;
    tdrdi->داخلا_سائيز       = حجم(AV3DReferenceDisplay);
    tdrdi->entries_وٿي   = entries_وٿي;

    إذا (ٻاهريون_سائيز)
        *ٻاهريون_سائيز = سائيز;

    أرجع tdrdi;
}
