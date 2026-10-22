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

#ضمن <stdint.h>
#ضمن <stdio.h>

#ضمن "libavutil/frame.h"
#ضمن "libavutil/mem.h"
#ضمن "libavutil/video_enc_params.h"

صحيح اصلي(فراغ)
{
    AVVideoEncParams *par;
    AVVideo_بلاک_Params *بلاک;
    AVFrame *چوکاټ;
    size_t اندازه;

    ساكن ثابت بنية {
        تعداد AVVideoEncParamsType type;
        ثابت حرف *name;
    } types[] = {
        { AV_VIDEO_ENC_PARAMS_VP9,   "VP9"   },
        { AV_VIDEO_ENC_PARAMS_H264,  "H264"  },
        { AV_VIDEO_ENC_PARAMS_MPEG2, "MPEG2" },
    };

    /* av_video_enc_params_alloc - each type with blocks */
    چاپ_کړه("Testing av_video_enc_params_alloc()\n");
    لكل (صحيح i = 0; i < 3; i++) {
        par = av_video_enc_params_alloc(types[i].type, 4, &اندازه);
        إذا (par) {
            چاپ_کړه("%s: OK, type=%d, nb_blocks=%u, size>0=%s\n",
                   types[i].name, par->type, par->nb_بلاکونه,
                   اندازه > 0 ? "yes" : "no");
            av_free(par);
        } وإلا {
            چاپ_کړه("%s: FAIL\n", types[i].name);
        }
    }

    /* zero blocks */
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_VP9, 0, &اندازه);
    إذا (par) {
        چاپ_کړه("zero blocks: OK, nb_blocks=%u\n", par->nb_بلاکونه);
        av_free(par);
    } وإلا {
        چاپ_کړه("zero blocks: FAIL\n");
    }

    /* alloc without size */
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_H264, 1, عدم);
    چاپ_کړه("alloc (no size): %s\n", par ? "OK" : "FAIL");
    av_free(par);

    /* av_video_enc_params_block - write and read back */
    چاپ_کړه("\nTesting av_video_enc_params_block()\n");
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_H264, 3, عدم);
    إذا (par) {
        par->qp = 26;
        par->delta_qp[0][0] = -2;
        par->delta_qp[0][1] = -1;
        چاپ_کړه("frame qp=%d, delta_qp[0]={%d,%d}\n",
               par->qp, par->delta_qp[0][0], par->delta_qp[0][1]);

        لكل (صحيح i = 0; i < 3; i++) {
            بلاک = av_video_enc_params_بلاک(par, i);
            إذا ((uint8_t *)بلاک != (uint8_t *)par + par->بلاکونه_دننه_واټن +
                                    (size_t)i * par->بلاک_اندازه)
                چاپ_کړه("block %d: pointer inconsistent with blocks_offset/block_size\n", i);
            بلاک->src_x = i * 16;
            بلاک->src_y = i * 16;
            بلاک->w = 16;
            بلاک->h = 16;
            بلاک->delta_qp = i - 1;
        }
        لكل (صحيح i = 0; i < 3; i++) {
            بلاک = av_video_enc_params_بلاک(par, i);
            چاپ_کړه("block %d: src=(%d,%d) size=%dx%d delta_qp=%d\n",
                   i, بلاک->src_x, بلاک->src_y,
                   بلاک->w, بلاک->h, بلاک->delta_qp);
        }
        av_free(par);
    }

    /* av_video_enc_params_create_side_data */
    چاپ_کړه("\nTesting av_video_enc_params_create_side_data()\n");
    چوکاټ = av_چوکاټ_alloc();
    إذا (چوکاټ) {
        par = av_video_enc_params_create_side_معلومات(چوکاټ,
                  AV_VIDEO_ENC_PARAMS_VP9, 2);
        إذا (par) {
            چاپ_کړه("side_data: OK, type=%d, nb_blocks=%u\n",
                   par->type, par->nb_بلاکونه);
            بلاک = av_video_enc_params_بلاک(par, 0);
            بلاک->delta_qp = 5;
            بلاک = av_video_enc_params_بلاک(par, 0);
            چاپ_کړه("side_data block 0: delta_qp=%d\n", بلاک->delta_qp);
        } وإلا {
            چاپ_کړه("side_data: FAIL\n");
        }
        av_چوکاټ_free(&چوکاټ);
    }

    /* NONE type */
    چاپ_کړه("\nTesting NONE type\n");
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_NONE, 0, &اندازه);
    إذا (par) {
        چاپ_کړه("NONE: OK, type=%d\n", par->type);
        av_free(par);
    } وإلا {
        چاپ_کړه("NONE: FAIL\n");
    }

    أرجع 0;
}
