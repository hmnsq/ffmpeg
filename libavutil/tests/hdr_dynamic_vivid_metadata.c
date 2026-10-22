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

#شامل <limits.h>
#شامل <stdio.h>

#شامل "libavutil/frame.h"
#شامل "libavutil/hdr_dynamic_vivid_metadata.h"
#شامل "libavutil/mem.h"

صحیح مین(خالی)
{
    AVDynamicHDRVivid *vivid;
    AVFrame *چوکھٹا;
    size_t سائز;

    /* av_dynamic_hdr_vivid_alloc */
    لکھو("Testing av_dynamic_hdr_vivid_alloc()\n");
    vivid = av_dynamic_hdr_vivid_alloc(&سائز);
    اگر (vivid) {
        لکھو("alloc: OK, size>0=%s\n", سائز > 0 ? "yes" : "no");
        لکھو("defaults: system_start_code=%u, num_windows=%u\n",
               vivid->system_آغاز_رمز, vivid->عدد_windows);

        /* write and read back */
        vivid->system_آغاز_رمز = 0x01;
        vivid->عدد_windows = 1;
        vivid->params[0].minimum_maxrgb = (AVRational){ 100, 1 };
        vivid->params[0].اوسط_قدر_maxrgb = (AVRational){ 500, 1 };
        vivid->params[0].variance_maxrgb = (AVRational){ 200, 1 };
        vivid->params[0].زیادہ_سے_زیادہ_maxrgb = (AVRational){ 1000, 1 };
        لکھو("write: system_start_code=%u, num_windows=%u\n",
               vivid->system_آغاز_رمز, vivid->عدد_windows);
        لکھو("params[0]: min=%d/%d avg=%d/%d var=%d/%d max=%d/%d\n",
               vivid->params[0].minimum_maxrgb.عدد,
               vivid->params[0].minimum_maxrgb.den,
               vivid->params[0].اوسط_قدر_maxrgb.عدد,
               vivid->params[0].اوسط_قدر_maxrgb.den,
               vivid->params[0].variance_maxrgb.عدد,
               vivid->params[0].variance_maxrgb.den,
               vivid->params[0].زیادہ_سے_زیادہ_maxrgb.عدد,
               vivid->params[0].زیادہ_سے_زیادہ_maxrgb.den);
        av_free(vivid);
    }

    /* alloc with NULL size */
    vivid = av_dynamic_hdr_vivid_alloc(تہی);
    لکھو("alloc (no size): %s\n", vivid ? "OK" : "FAIL");
    av_free(vivid);

    /* av_dynamic_hdr_vivid_create_side_data */
    لکھو("\nTesting av_dynamic_hdr_vivid_create_side_data()\n");
    چوکھٹا = av_چوکھٹا_alloc();
    اگر (چوکھٹا) {
        vivid = av_dynamic_hdr_vivid_create_side_ڈیٹا(چوکھٹا);
        اگر (vivid) {
            لکھو("side_data: OK\n");
            vivid->system_آغاز_رمز = 0x02;
            لکھو("side_data write: system_start_code=%u\n",
                   vivid->system_آغاز_رمز);
        } ورنہ {
            لکھو("side_data: FAIL\n");
        }
        av_چوکھٹا_free(&چوکھٹا);
    }

    /* OOM paths via av_max_alloc */
    لکھو("\nTesting OOM paths\n");
    av_max_alloc(1);
    vivid = av_dynamic_hdr_vivid_alloc(&سائز);
    لکھو("alloc OOM: %s\n", vivid ? "FAIL" : "OK");
    av_free(vivid);
    av_max_alloc(زیادہ_سے_زیادہ_عدد);

    چوکھٹا = av_چوکھٹا_alloc();
    اگر (چوکھٹا) {
        av_max_alloc(1);
        vivid = av_dynamic_hdr_vivid_create_side_ڈیٹا(چوکھٹا);
        لکھو("side_data OOM: %s\n", vivid ? "FAIL" : "OK");
        av_max_alloc(زیادہ_سے_زیادہ_عدد);
        av_چوکھٹا_free(&چوکھٹا);
    }

    واپس 0;
}
