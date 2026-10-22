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

#ضمن <limits.h>
#ضمن <stdio.h>

#ضمن "libavutil/frame.h"
#ضمن "libavutil/hdr_dynamic_vivid_metadata.h"
#ضمن "libavutil/mem.h"

صحيح مکيه(فراغ)
{
    AVDynamicHDRVivid *vivid;
    AVFrame *چوکٺو;
    size_t سائيز;

    /* av_dynamic_hdr_vivid_alloc */
    لکو("Testing av_dynamic_hdr_vivid_alloc()\n");
    vivid = av_dynamic_hdr_vivid_alloc(&سائيز);
    إذا (vivid) {
        لکو("alloc: OK, size>0=%s\n", سائيز > 0 ? "yes" : "no");
        لکو("defaults: system_start_code=%u, num_windows=%u\n",
               vivid->system_شروعات_ڪوڊ, vivid->انگ_windows);

        /* write and read back */
        vivid->system_شروعات_ڪوڊ = 0x01;
        vivid->انگ_windows = 1;
        vivid->params[0].minimum_maxrgb = (AVRational){ 100, 1 };
        vivid->params[0].اوسط_maxrgb = (AVRational){ 500, 1 };
        vivid->params[0].variance_maxrgb = (AVRational){ 200, 1 };
        vivid->params[0].وڌ_کان_وڌ_maxrgb = (AVRational){ 1000, 1 };
        لکو("write: system_start_code=%u, num_windows=%u\n",
               vivid->system_شروعات_ڪوڊ, vivid->انگ_windows);
        لکو("params[0]: min=%d/%d avg=%d/%d var=%d/%d max=%d/%d\n",
               vivid->params[0].minimum_maxrgb.انگ,
               vivid->params[0].minimum_maxrgb.den,
               vivid->params[0].اوسط_maxrgb.انگ,
               vivid->params[0].اوسط_maxrgb.den,
               vivid->params[0].variance_maxrgb.انگ,
               vivid->params[0].variance_maxrgb.den,
               vivid->params[0].وڌ_کان_وڌ_maxrgb.انگ,
               vivid->params[0].وڌ_کان_وڌ_maxrgb.den);
        av_free(vivid);
    }

    /* alloc with NULL size */
    vivid = av_dynamic_hdr_vivid_alloc(عدم);
    لکو("alloc (no size): %s\n", vivid ? "OK" : "FAIL");
    av_free(vivid);

    /* av_dynamic_hdr_vivid_create_side_data */
    لکو("\nTesting av_dynamic_hdr_vivid_create_side_data()\n");
    چوکٺو = av_چوکٺو_alloc();
    إذا (چوکٺو) {
        vivid = av_dynamic_hdr_vivid_create_side_معلومات(چوکٺو);
        إذا (vivid) {
            لکو("side_data: OK\n");
            vivid->system_شروعات_ڪوڊ = 0x02;
            لکو("side_data write: system_start_code=%u\n",
                   vivid->system_شروعات_ڪوڊ);
        } وإلا {
            لکو("side_data: FAIL\n");
        }
        av_چوکٺو_free(&چوکٺو);
    }

    /* OOM paths via av_max_alloc */
    لکو("\nTesting OOM paths\n");
    av_max_alloc(1);
    vivid = av_dynamic_hdr_vivid_alloc(&سائيز);
    لکو("alloc OOM: %s\n", vivid ? "FAIL" : "OK");
    av_free(vivid);
    av_max_alloc(وڌ_کان_وڌ_عدد);

    چوکٺو = av_چوکٺو_alloc();
    إذا (چوکٺو) {
        av_max_alloc(1);
        vivid = av_dynamic_hdr_vivid_create_side_معلومات(چوکٺو);
        لکو("side_data OOM: %s\n", vivid ? "FAIL" : "OK");
        av_max_alloc(وڌ_کان_وڌ_عدد);
        av_چوکٺو_free(&چوکٺو);
    }

    أرجع 0;
}
