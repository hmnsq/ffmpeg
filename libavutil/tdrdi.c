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

#समावेश <stddef.h>
#समावेश <stdint.h>

#समावेश "mem.h"
#समावेश "tdrdi.h"

AV3DReferenceDisplaysInfo *av_tdrdi_alloc(अचिन्हित पूर्णांक nb_displays, माप_प्रकार *out_आकार)
{
    काष्ठा TestStruct {
        AV3DReferenceDisplaysInfo p;
        AV3DReferenceDisplay      b;
    };
    स्थिर माप_प्रकार entries_offset = दुरत्व(काष्ठा TestStruct, b);
    माप_प्रकार आकार = entries_offset;
    AV3DReferenceDisplaysInfo *tdrdi;

    अगर (nb_displays > (SIZE_MAX - आकार) / माप(AV3DReferenceDisplay))
        वापस शून्य;
    आकार += माप(AV3DReferenceDisplay) * nb_displays;

    tdrdi = av_mallocz(आकार);
    अगर (!tdrdi)
        वापस शून्य;

    tdrdi->अंक_ref_displays = nb_displays;
    tdrdi->entry_आकार       = माप(AV3DReferenceDisplay);
    tdrdi->entries_offset   = entries_offset;

    अगर (out_आकार)
        *out_आकार = आकार;

    वापस tdrdi;
}
