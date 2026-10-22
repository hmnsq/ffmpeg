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

AV3DReferenceDisplaysInfo *av_tdrdi_alloc(بیعلامت صحيح nb_displays, size_t *بیرون_اندازه)
{
    بنية TestStruct {
        AV3DReferenceDisplaysInfo p;
        AV3DReferenceDisplay      b;
    };
    ثابت size_t entries_جابه_جایی = offsetof(بنية TestStruct, b);
    size_t اندازه = entries_جابه_جایی;
    AV3DReferenceDisplaysInfo *tdrdi;

    إذا (nb_displays > (SIZE_MAX - اندازه) / حجم(AV3DReferenceDisplay))
        أرجع عدم;
    اندازه += حجم(AV3DReferenceDisplay) * nb_displays;

    tdrdi = av_mallocz(اندازه);
    إذا (!tdrdi)
        أرجع عدم;

    tdrdi->رقم_ref_displays = nb_displays;
    tdrdi->مدخل_اندازه       = حجم(AV3DReferenceDisplay);
    tdrdi->entries_جابه_جایی   = entries_جابه_جایی;

    إذا (بیرون_اندازه)
        *بیرون_اندازه = اندازه;

    أرجع tdrdi;
}
