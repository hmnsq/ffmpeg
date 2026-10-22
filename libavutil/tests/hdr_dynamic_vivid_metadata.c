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

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "libavutil/frame.h"
#ಅನ್ತರ್ಭಾವ "libavutil/hdr_dynamic_vivid_metadata.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    AVDynamicHDRVivid *vivid;
    AVFrame *ಚೌಕಟ್ಟು;
    size_t ಗಾತ್ರ_2;

    /* av_dynamic_hdr_vivid_alloc */
    ಬರೆ("Testing av_dynamic_hdr_vivid_alloc()\n");
    vivid = av_dynamic_hdr_vivid_alloc(&ಗಾತ್ರ_2);
    ಆದರೆ (vivid) {
        ಬರೆ("alloc: OK, size>0=%s\n", ಗಾತ್ರ_2 > 0 ? "yes" : "no");
        ಬರೆ("defaults: system_start_code=%u, num_windows=%u\n",
               vivid->system_ಆರಂಭ_ಸಂಕೇತ, vivid->ಅಂಕೆ_windows);

        /* write and read back */
        vivid->system_ಆರಂಭ_ಸಂಕೇತ = 0x01;
        vivid->ಅಂಕೆ_windows = 1;
        vivid->params[0].minimum_maxrgb = (AVRational){ 100, 1 };
        vivid->params[0].ಸರಾಸರಿ_ಮೌಲ್ಯ_maxrgb = (AVRational){ 500, 1 };
        vivid->params[0].variance_maxrgb = (AVRational){ 200, 1 };
        vivid->params[0].ಗರಿಷ್ಠ_maxrgb = (AVRational){ 1000, 1 };
        ಬರೆ("write: system_start_code=%u, num_windows=%u\n",
               vivid->system_ಆರಂಭ_ಸಂಕೇತ, vivid->ಅಂಕೆ_windows);
        ಬರೆ("params[0]: min=%d/%d avg=%d/%d var=%d/%d max=%d/%d\n",
               vivid->params[0].minimum_maxrgb.ಅಂಕೆ,
               vivid->params[0].minimum_maxrgb.den,
               vivid->params[0].ಸರಾಸರಿ_ಮೌಲ್ಯ_maxrgb.ಅಂಕೆ,
               vivid->params[0].ಸರಾಸರಿ_ಮೌಲ್ಯ_maxrgb.den,
               vivid->params[0].variance_maxrgb.ಅಂಕೆ,
               vivid->params[0].variance_maxrgb.den,
               vivid->params[0].ಗರಿಷ್ಠ_maxrgb.ಅಂಕೆ,
               vivid->params[0].ಗರಿಷ್ಠ_maxrgb.den);
        av_free(vivid);
    }

    /* alloc with NULL size */
    vivid = av_dynamic_hdr_vivid_alloc(ಖಾಲಿ);
    ಬರೆ("alloc (no size): %s\n", vivid ? "OK" : "FAIL");
    av_free(vivid);

    /* av_dynamic_hdr_vivid_create_side_data */
    ಬರೆ("\nTesting av_dynamic_hdr_vivid_create_side_data()\n");
    ಚೌಕಟ್ಟು = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (ಚೌಕಟ್ಟು) {
        vivid = av_dynamic_hdr_vivid_create_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು);
        ಆದರೆ (vivid) {
            ಬರೆ("side_data: OK\n");
            vivid->system_ಆರಂಭ_ಸಂಕೇತ = 0x02;
            ಬರೆ("side_data write: system_start_code=%u\n",
                   vivid->system_ಆರಂಭ_ಸಂಕೇತ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಬರೆ("side_data: FAIL\n");
        }
        av_ಚೌಕಟ್ಟು_free(&ಚೌಕಟ್ಟು);
    }

    /* OOM paths via av_max_alloc */
    ಬರೆ("\nTesting OOM paths\n");
    av_max_alloc(1);
    vivid = av_dynamic_hdr_vivid_alloc(&ಗಾತ್ರ_2);
    ಬರೆ("alloc OOM: %s\n", vivid ? "FAIL" : "OK");
    av_free(vivid);
    av_max_alloc(ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);

    ಚೌಕಟ್ಟು = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (ಚೌಕಟ್ಟು) {
        av_max_alloc(1);
        vivid = av_dynamic_hdr_vivid_create_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು);
        ಬರೆ("side_data OOM: %s\n", vivid ? "FAIL" : "OK");
        av_max_alloc(ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);
        av_ಚೌಕಟ್ಟು_free(&ಚೌಕಟ್ಟು);
    }

    ಹಿಂತಿರುಗಿ 0;
}
