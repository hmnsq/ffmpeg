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

صحيح مکھ(فراغ)
{
    AVVideoEncParams *par;
    AVVideo_بلاک_Params *بلاک;
    AVFrame *چوکھٹا;
    size_t ناپ;

    ساكن ثابت بنية {
        تعداد AVVideoEncParamsType type;
        ثابت حرف *name;
    } types[] = {
        { AV_VIDEO_ENC_PARAMS_VP9,   "VP9"   },
        { AV_VIDEO_ENC_PARAMS_H264,  "H264"  },
        { AV_VIDEO_ENC_PARAMS_MPEG2, "MPEG2" },
    };

    /* av_video_enc_params_alloc - each type with blocks */
    لکھو("Testing av_video_enc_params_alloc()\n");
    لكل (صحيح i = 0; i < 3; i++) {
        par = av_video_enc_params_alloc(types[i].type, 4, &ناپ);
        إذا (par) {
            لکھو("%s: OK, type=%d, nb_blocks=%u, size>0=%s\n",
                   types[i].name, par->type, par->nb_بلاکاں,
                   ناپ > 0 ? "yes" : "no");
            av_free(par);
        } وإلا {
            لکھو("%s: FAIL\n", types[i].name);
        }
    }

    /* zero blocks */
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_VP9, 0, &ناپ);
    إذا (par) {
        لکھو("zero blocks: OK, nb_blocks=%u\n", par->nb_بلاکاں);
        av_free(par);
    } وإلا {
        لکھو("zero blocks: FAIL\n");
    }

    /* alloc without size */
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_H264, 1, عدم);
    لکھو("alloc (no size): %s\n", par ? "OK" : "FAIL");
    av_free(par);

    /* av_video_enc_params_block - write and read back */
    لکھو("\nTesting av_video_enc_params_block()\n");
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_H264, 3, عدم);
    إذا (par) {
        par->qp = 26;
        par->delta_qp[0][0] = -2;
        par->delta_qp[0][1] = -1;
        لکھو("frame qp=%d, delta_qp[0]={%d,%d}\n",
               par->qp, par->delta_qp[0][0], par->delta_qp[0][1]);

        لكل (صحيح i = 0; i < 3; i++) {
            بلاک = av_video_enc_params_بلاک(par, i);
            إذا ((uint8_t *)بلاک != (uint8_t *)par + par->بلاکاں_وتھ +
                                    (size_t)i * par->بلاک_ناپ)
                لکھو("block %d: pointer inconsistent with blocks_offset/block_size\n", i);
            بلاک->src_x = i * 16;
            بلاک->src_y = i * 16;
            بلاک->w = 16;
            بلاک->h = 16;
            بلاک->delta_qp = i - 1;
        }
        لكل (صحيح i = 0; i < 3; i++) {
            بلاک = av_video_enc_params_بلاک(par, i);
            لکھو("block %d: src=(%d,%d) size=%dx%d delta_qp=%d\n",
                   i, بلاک->src_x, بلاک->src_y,
                   بلاک->w, بلاک->h, بلاک->delta_qp);
        }
        av_free(par);
    }

    /* av_video_enc_params_create_side_data */
    لکھو("\nTesting av_video_enc_params_create_side_data()\n");
    چوکھٹا = av_چوکھٹا_alloc();
    إذا (چوکھٹا) {
        par = av_video_enc_params_create_side_انکڑے(چوکھٹا,
                  AV_VIDEO_ENC_PARAMS_VP9, 2);
        إذا (par) {
            لکھو("side_data: OK, type=%d, nb_blocks=%u\n",
                   par->type, par->nb_بلاکاں);
            بلاک = av_video_enc_params_بلاک(par, 0);
            بلاک->delta_qp = 5;
            بلاک = av_video_enc_params_بلاک(par, 0);
            لکھو("side_data block 0: delta_qp=%d\n", بلاک->delta_qp);
        } وإلا {
            لکھو("side_data: FAIL\n");
        }
        av_چوکھٹا_free(&چوکھٹا);
    }

    /* NONE type */
    لکھو("\nTesting NONE type\n");
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_NONE, 0, &ناپ);
    إذا (par) {
        لکھو("NONE: OK, type=%d\n", par->type);
        av_free(par);
    } وإلا {
        لکھو("NONE: FAIL\n");
    }

    أرجع 0;
}
