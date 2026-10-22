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

#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tdrdi.h"

AV3DReferenceDisplaysInfo *av_tdrdi_alloc(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ nb_displays, size_t *ਬਾਹਰਲਾ_ਮਾਪ)
{
    ਬਣਤਰ TestStruct {
        AV3DReferenceDisplaysInfo p;
        AV3DReferenceDisplay      b;
    };
    ਅਚਲ size_t entries_ਵਿੱਥ = offsetof(ਬਣਤਰ TestStruct, b);
    size_t ਮਾਪ = entries_ਵਿੱਥ;
    AV3DReferenceDisplaysInfo *tdrdi;

    ਜੇ (nb_displays > (SIZE_MAX - ਮਾਪ) / ਆਕਾਰ(AV3DReferenceDisplay))
        ਵਾਪਸ ਨਿਰਾ;
    ਮਾਪ += ਆਕਾਰ(AV3DReferenceDisplay) * nb_displays;

    tdrdi = av_mallocz(ਮਾਪ);
    ਜੇ (!tdrdi)
        ਵਾਪਸ ਨਿਰਾ;

    tdrdi->ਅੰਕ_ref_displays = nb_displays;
    tdrdi->ਇੰਦਰਾਜ_ਮਾਪ       = ਆਕਾਰ(AV3DReferenceDisplay);
    tdrdi->entries_ਵਿੱਥ   = entries_ਵਿੱਥ;

    ਜੇ (ਬਾਹਰਲਾ_ਮਾਪ)
        *ਬਾਹਰਲਾ_ਮਾਪ = ਮਾਪ;

    ਵਾਪਸ tdrdi;
}
