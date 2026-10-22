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

صحيح مکھ(فراغ)
{
    AVDynamicHDRVivid *vivid;
    AVFrame *چوکھٹا;
    size_t ناپ;

    /* av_dynamic_hdr_vivid_alloc */
    لکھو("Testing av_dynamic_hdr_vivid_alloc()\n");
    vivid = av_dynamic_hdr_vivid_alloc(&ناپ);
    إذا (vivid) {
        لکھو("alloc: OK, size>0=%s\n", ناپ > 0 ? "yes" : "no");
        لکھو("defaults: system_start_code=%u, num_windows=%u\n",
               vivid->system_شروع_کوڈ, vivid->عدد_windows);

        /* write and read back */
        vivid->system_شروع_کوڈ = 0x01;
        vivid->عدد_windows = 1;
        vivid->params[0].minimum_maxrgb = (AVRational){ 100, 1 };
        vivid->params[0].اوسطن_maxrgb = (AVRational){ 500, 1 };
        vivid->params[0].variance_maxrgb = (AVRational){ 200, 1 };
        vivid->params[0].ودھ_توں_ودھ_maxrgb = (AVRational){ 1000, 1 };
        لکھو("write: system_start_code=%u, num_windows=%u\n",
               vivid->system_شروع_کوڈ, vivid->عدد_windows);
        لکھو("params[0]: min=%d/%d avg=%d/%d var=%d/%d max=%d/%d\n",
               vivid->params[0].minimum_maxrgb.عدد,
               vivid->params[0].minimum_maxrgb.den,
               vivid->params[0].اوسطن_maxrgb.عدد,
               vivid->params[0].اوسطن_maxrgb.den,
               vivid->params[0].variance_maxrgb.عدد,
               vivid->params[0].variance_maxrgb.den,
               vivid->params[0].ودھ_توں_ودھ_maxrgb.عدد,
               vivid->params[0].ودھ_توں_ودھ_maxrgb.den);
        av_free(vivid);
    }

    /* alloc with NULL size */
    vivid = av_dynamic_hdr_vivid_alloc(عدم);
    لکھو("alloc (no size): %s\n", vivid ? "OK" : "FAIL");
    av_free(vivid);

    /* av_dynamic_hdr_vivid_create_side_data */
    لکھو("\nTesting av_dynamic_hdr_vivid_create_side_data()\n");
    چوکھٹا = av_چوکھٹا_alloc();
    إذا (چوکھٹا) {
        vivid = av_dynamic_hdr_vivid_create_side_انکڑے(چوکھٹا);
        إذا (vivid) {
            لکھو("side_data: OK\n");
            vivid->system_شروع_کوڈ = 0x02;
            لکھو("side_data write: system_start_code=%u\n",
                   vivid->system_شروع_کوڈ);
        } وإلا {
            لکھو("side_data: FAIL\n");
        }
        av_چوکھٹا_free(&چوکھٹا);
    }

    /* OOM paths via av_max_alloc */
    لکھو("\nTesting OOM paths\n");
    av_max_alloc(1);
    vivid = av_dynamic_hdr_vivid_alloc(&ناپ);
    لکھو("alloc OOM: %s\n", vivid ? "FAIL" : "OK");
    av_free(vivid);
    av_max_alloc(ودھ_توں_ودھ_عدد);

    چوکھٹا = av_چوکھٹا_alloc();
    إذا (چوکھٹا) {
        av_max_alloc(1);
        vivid = av_dynamic_hdr_vivid_create_side_انکڑے(چوکھٹا);
        لکھو("side_data OOM: %s\n", vivid ? "FAIL" : "OK");
        av_max_alloc(ودھ_توں_ودھ_عدد);
        av_چوکھٹا_free(&چوکھٹا);
    }

    أرجع 0;
}
