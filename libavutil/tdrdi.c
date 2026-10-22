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

#अन्तर्भाव <stddef.h>
#अन्तर्भाव <stdint.h>

#अन्तर्भाव "mem.h"
#अन्तर्भाव "tdrdi.h"

AV3DReferenceDisplaysInfo *av_tdrdi_alloc(अचिन्हित पूर्णांक nb_displays, माप_प्रकार *out_size)
{
    संरचना TestStruct {
        AV3DReferenceDisplaysInfo p;
        AV3DReferenceDisplay      b;
    };
    स्थिरांक माप_प्रकार entries_offset = दुरत्व(संरचना TestStruct, b);
    माप_प्रकार size = entries_offset;
    AV3DReferenceDisplaysInfo *tdrdi;

    जर (nb_displays > (SIZE_MAX - size) / आकार(AV3DReferenceDisplay))
        परत रिक्त;
    size += आकार(AV3DReferenceDisplay) * nb_displays;

    tdrdi = av_mallocz(size);
    जर (!tdrdi)
        परत रिक्त;

    tdrdi->अंक_ref_displays = nb_displays;
    tdrdi->entry_size       = आकार(AV3DReferenceDisplay);
    tdrdi->entries_offset   = entries_offset;

    जर (out_size)
        *out_size = size;

    परत tdrdi;
}
