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

AV3DReferenceDisplaysInfo *av_tdrdi_alloc(بنانشانی صحيح nb_displays, size_t *باہرلا_ناپ)
{
    بنية TestStruct {
        AV3DReferenceDisplaysInfo p;
        AV3DReferenceDisplay      b;
    };
    ثابت size_t entries_وتھ = offsetof(بنية TestStruct, b);
    size_t ناپ = entries_وتھ;
    AV3DReferenceDisplaysInfo *tdrdi;

    إذا (nb_displays > (SIZE_MAX - ناپ) / حجم(AV3DReferenceDisplay))
        أرجع عدم;
    ناپ += حجم(AV3DReferenceDisplay) * nb_displays;

    tdrdi = av_mallocz(ناپ);
    إذا (!tdrdi)
        أرجع عدم;

    tdrdi->عدد_ref_displays = nb_displays;
    tdrdi->اندراج_ناپ       = حجم(AV3DReferenceDisplay);
    tdrdi->entries_وتھ   = entries_وتھ;

    إذا (باہرلا_ناپ)
        *باہرلا_ناپ = ناپ;

    أرجع tdrdi;
}
