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

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/frame.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/hdr_dynamic_vivid_metadata.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    AVDynamicHDRVivid *vivid;
    AVFrame *ਚੌਖਟਾ;
    size_t ਮਾਪ;

    /* av_dynamic_hdr_vivid_alloc */
    ਲਿਖੋ("Testing av_dynamic_hdr_vivid_alloc()\n");
    vivid = av_dynamic_hdr_vivid_alloc(&ਮਾਪ);
    ਜੇ (vivid) {
        ਲਿਖੋ("alloc: OK, size>0=%s\n", ਮਾਪ > 0 ? "yes" : "no");
        ਲਿਖੋ("defaults: system_start_code=%u, num_windows=%u\n",
               vivid->system_ਸ਼ੁਰੂ_ਕੋਡ, vivid->ਅੰਕ_windows);

        /* write and read back */
        vivid->system_ਸ਼ੁਰੂ_ਕੋਡ = 0x01;
        vivid->ਅੰਕ_windows = 1;
        vivid->params[0].minimum_maxrgb = (AVRational){ 100, 1 };
        vivid->params[0].ਔਸਤਨ_maxrgb = (AVRational){ 500, 1 };
        vivid->params[0].variance_maxrgb = (AVRational){ 200, 1 };
        vivid->params[0].ਵੱਧ_ਤੋਂ_ਵੱਧ_maxrgb = (AVRational){ 1000, 1 };
        ਲਿਖੋ("write: system_start_code=%u, num_windows=%u\n",
               vivid->system_ਸ਼ੁਰੂ_ਕੋਡ, vivid->ਅੰਕ_windows);
        ਲਿਖੋ("params[0]: min=%d/%d avg=%d/%d var=%d/%d max=%d/%d\n",
               vivid->params[0].minimum_maxrgb.ਅੰਕ,
               vivid->params[0].minimum_maxrgb.den,
               vivid->params[0].ਔਸਤਨ_maxrgb.ਅੰਕ,
               vivid->params[0].ਔਸਤਨ_maxrgb.den,
               vivid->params[0].variance_maxrgb.ਅੰਕ,
               vivid->params[0].variance_maxrgb.den,
               vivid->params[0].ਵੱਧ_ਤੋਂ_ਵੱਧ_maxrgb.ਅੰਕ,
               vivid->params[0].ਵੱਧ_ਤੋਂ_ਵੱਧ_maxrgb.den);
        av_free(vivid);
    }

    /* alloc with NULL size */
    vivid = av_dynamic_hdr_vivid_alloc(ਨਿਰਾ);
    ਲਿਖੋ("alloc (no size): %s\n", vivid ? "OK" : "FAIL");
    av_free(vivid);

    /* av_dynamic_hdr_vivid_create_side_data */
    ਲਿਖੋ("\nTesting av_dynamic_hdr_vivid_create_side_data()\n");
    ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    ਜੇ (ਚੌਖਟਾ) {
        vivid = av_dynamic_hdr_vivid_create_side_ਅੰਕੜੇ(ਚੌਖਟਾ);
        ਜੇ (vivid) {
            ਲਿਖੋ("side_data: OK\n");
            vivid->system_ਸ਼ੁਰੂ_ਕੋਡ = 0x02;
            ਲਿਖੋ("side_data write: system_start_code=%u\n",
                   vivid->system_ਸ਼ੁਰੂ_ਕੋਡ);
        } ਨਹੀਂਤਾਂ {
            ਲਿਖੋ("side_data: FAIL\n");
        }
        av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);
    }

    /* OOM paths via av_max_alloc */
    ਲਿਖੋ("\nTesting OOM paths\n");
    av_max_alloc(1);
    vivid = av_dynamic_hdr_vivid_alloc(&ਮਾਪ);
    ਲਿਖੋ("alloc OOM: %s\n", vivid ? "FAIL" : "OK");
    av_free(vivid);
    av_max_alloc(ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);

    ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    ਜੇ (ਚੌਖਟਾ) {
        av_max_alloc(1);
        vivid = av_dynamic_hdr_vivid_create_side_ਅੰਕੜੇ(ਚੌਖਟਾ);
        ਲਿਖੋ("side_data OOM: %s\n", vivid ? "FAIL" : "OK");
        av_max_alloc(ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);
        av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);
    }

    ਵਾਪਸ 0;
}
