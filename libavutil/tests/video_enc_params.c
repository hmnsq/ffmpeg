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

صحيح اصلی(فراغ)
{
    AVVideoEncParams *par;
    AVVideo_بلوک_Params *بلوک;
    AVFrame *قاب;
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
    چاپ_کن("Testing av_video_enc_params_alloc()\n");
    لكل (صحيح i = 0; i < 3; i++) {
        par = av_video_enc_params_alloc(types[i].type, 4, &اندازه);
        إذا (par) {
            چاپ_کن("%s: OK, type=%d, nb_blocks=%u, size>0=%s\n",
                   types[i].name, par->type, par->nb_بلوکها,
                   اندازه > 0 ? "yes" : "no");
            av_free(par);
        } وإلا {
            چاپ_کن("%s: FAIL\n", types[i].name);
        }
    }

    /* zero blocks */
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_VP9, 0, &اندازه);
    إذا (par) {
        چاپ_کن("zero blocks: OK, nb_blocks=%u\n", par->nb_بلوکها);
        av_free(par);
    } وإلا {
        چاپ_کن("zero blocks: FAIL\n");
    }

    /* alloc without size */
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_H264, 1, عدم);
    چاپ_کن("alloc (no size): %s\n", par ? "OK" : "FAIL");
    av_free(par);

    /* av_video_enc_params_block - write and read back */
    چاپ_کن("\nTesting av_video_enc_params_block()\n");
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_H264, 3, عدم);
    إذا (par) {
        par->qp = 26;
        par->delta_qp[0][0] = -2;
        par->delta_qp[0][1] = -1;
        چاپ_کن("frame qp=%d, delta_qp[0]={%d,%d}\n",
               par->qp, par->delta_qp[0][0], par->delta_qp[0][1]);

        لكل (صحيح i = 0; i < 3; i++) {
            بلوک = av_video_enc_params_بلوک(par, i);
            إذا ((uint8_t *)بلوک != (uint8_t *)par + par->بلوکها_جابه_جایی +
                                    (size_t)i * par->بلوک_اندازه)
                چاپ_کن("block %d: pointer inconsistent with blocks_offset/block_size\n", i);
            بلوک->src_x = i * 16;
            بلوک->src_y = i * 16;
            بلوک->w = 16;
            بلوک->h = 16;
            بلوک->delta_qp = i - 1;
        }
        لكل (صحيح i = 0; i < 3; i++) {
            بلوک = av_video_enc_params_بلوک(par, i);
            چاپ_کن("block %d: src=(%d,%d) size=%dx%d delta_qp=%d\n",
                   i, بلوک->src_x, بلوک->src_y,
                   بلوک->w, بلوک->h, بلوک->delta_qp);
        }
        av_free(par);
    }

    /* av_video_enc_params_create_side_data */
    چاپ_کن("\nTesting av_video_enc_params_create_side_data()\n");
    قاب = av_قاب_alloc();
    إذا (قاب) {
        par = av_video_enc_params_create_side_داده(قاب,
                  AV_VIDEO_ENC_PARAMS_VP9, 2);
        إذا (par) {
            چاپ_کن("side_data: OK, type=%d, nb_blocks=%u\n",
                   par->type, par->nb_بلوکها);
            بلوک = av_video_enc_params_بلوک(par, 0);
            بلوک->delta_qp = 5;
            بلوک = av_video_enc_params_بلوک(par, 0);
            چاپ_کن("side_data block 0: delta_qp=%d\n", بلوک->delta_qp);
        } وإلا {
            چاپ_کن("side_data: FAIL\n");
        }
        av_قاب_free(&قاب);
    }

    /* NONE type */
    چاپ_کن("\nTesting NONE type\n");
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_NONE, 0, &اندازه);
    إذا (par) {
        چاپ_کن("NONE: OK, type=%d\n", par->type);
        av_free(par);
    } وإلا {
        چاپ_کن("NONE: FAIL\n");
    }

    أرجع 0;
}
