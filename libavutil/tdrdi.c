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

#అన్తర్భావ <stddef.h>
#అన్తర్భావ <stdint.h>

#అన్తర్భావ "mem.h"
#అన్తర్భావ "tdrdi.h"

AV3DReferenceDisplaysInfo *av_tdrdi_alloc(గుర్తులేని పూర్ణాంకం nb_displays, size_t *బహిర్గతం_కొలత)
{
    నిర్మాణం TestStruct {
        AV3DReferenceDisplaysInfo p;
        AV3DReferenceDisplay      b;
    };
    స్థిరరాశి size_t entries_స్థానభ్రంశం = offsetof(నిర్మాణం TestStruct, b);
    size_t కొలత = entries_స్థానభ్రంశం;
    AV3DReferenceDisplaysInfo *tdrdi;

    ఒకవేళ (nb_displays > (SIZE_MAX - కొలత) / పరిమాణం(AV3DReferenceDisplay))
        తిరిగి ఖాళీ;
    కొలత += పరిమాణం(AV3DReferenceDisplay) * nb_displays;

    tdrdi = av_mallocz(కొలత);
    ఒకవేళ (!tdrdi)
        తిరిగి ఖాళీ;

    tdrdi->అంకె_ref_displays = nb_displays;
    tdrdi->నమోదు_కొలత       = పరిమాణం(AV3DReferenceDisplay);
    tdrdi->entries_స్థానభ్రంశం   = entries_స్థానభ్రంశం;

    ఒకవేళ (బహిర్గతం_కొలత)
        *బహిర్గతం_కొలత = కొలత;

    తిరిగి tdrdi;
}
