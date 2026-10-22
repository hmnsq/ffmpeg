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

AV3DReferenceDisplaysInfo *av_tdrdi_alloc(अचिह्नित पूर्णाङ्क nb_displays, size_t *बहिर्गमनम्_आकार)
{
    संरचना TestStruct {
        AV3DReferenceDisplaysInfo p;
        AV3DReferenceDisplay      b;
    };
    ध्रुव size_t entries_विस्थापनम् = offsetof(संरचना TestStruct, b);
    size_t आकार = entries_विस्थापनम्;
    AV3DReferenceDisplaysInfo *tdrdi;

    यदि (nb_displays > (SIZE_MAX - आकार) / परिमाण(AV3DReferenceDisplay))
        प्रत्यागम रिक्त;
    आकार += परिमाण(AV3DReferenceDisplay) * nb_displays;

    tdrdi = av_mallocz(आकार);
    यदि (!tdrdi)
        प्रत्यागम रिक्त;

    tdrdi->अङ्कः_ref_displays = nb_displays;
    tdrdi->प्रविष्टिः_आकार       = परिमाण(AV3DReferenceDisplay);
    tdrdi->entries_विस्थापनम्   = entries_विस्थापनम्;

    यदि (बहिर्गमनम्_आकार)
        *बहिर्गमनम्_आकार = आकार;

    प्रत्यागम tdrdi;
}
