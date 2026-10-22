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

صحيح مکيه(فراغ)
{
    AVVideoEncParams *par;
    AVVideo_بلاڪ_Params *بلاڪ;
    AVFrame *چوکٺو;
    size_t سائيز;

    ساكن ثابت بنية {
        تعداد AVVideoEncParamsType type;
        ثابت حرف *name;
    } types[] = {
        { AV_VIDEO_ENC_PARAMS_VP9,   "VP9"   },
        { AV_VIDEO_ENC_PARAMS_H264,  "H264"  },
        { AV_VIDEO_ENC_PARAMS_MPEG2, "MPEG2" },
    };

    /* av_video_enc_params_alloc - each type with blocks */
    لکو("Testing av_video_enc_params_alloc()\n");
    لكل (صحيح i = 0; i < 3; i++) {
        par = av_video_enc_params_alloc(types[i].type, 4, &سائيز);
        إذا (par) {
            لکو("%s: OK, type=%d, nb_blocks=%u, size>0=%s\n",
                   types[i].name, par->type, par->nb_بلاڪون,
                   سائيز > 0 ? "yes" : "no");
            av_free(par);
        } وإلا {
            لکو("%s: FAIL\n", types[i].name);
        }
    }

    /* zero blocks */
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_VP9, 0, &سائيز);
    إذا (par) {
        لکو("zero blocks: OK, nb_blocks=%u\n", par->nb_بلاڪون);
        av_free(par);
    } وإلا {
        لکو("zero blocks: FAIL\n");
    }

    /* alloc without size */
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_H264, 1, عدم);
    لکو("alloc (no size): %s\n", par ? "OK" : "FAIL");
    av_free(par);

    /* av_video_enc_params_block - write and read back */
    لکو("\nTesting av_video_enc_params_block()\n");
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_H264, 3, عدم);
    إذا (par) {
        par->qp = 26;
        par->delta_qp[0][0] = -2;
        par->delta_qp[0][1] = -1;
        لکو("frame qp=%d, delta_qp[0]={%d,%d}\n",
               par->qp, par->delta_qp[0][0], par->delta_qp[0][1]);

        لكل (صحيح i = 0; i < 3; i++) {
            بلاڪ = av_video_enc_params_بلاڪ(par, i);
            إذا ((uint8_t *)بلاڪ != (uint8_t *)par + par->بلاڪون_وٿي +
                                    (size_t)i * par->بلاڪ_سائيز)
                لکو("block %d: pointer inconsistent with blocks_offset/block_size\n", i);
            بلاڪ->src_x = i * 16;
            بلاڪ->src_y = i * 16;
            بلاڪ->w = 16;
            بلاڪ->h = 16;
            بلاڪ->delta_qp = i - 1;
        }
        لكل (صحيح i = 0; i < 3; i++) {
            بلاڪ = av_video_enc_params_بلاڪ(par, i);
            لکو("block %d: src=(%d,%d) size=%dx%d delta_qp=%d\n",
                   i, بلاڪ->src_x, بلاڪ->src_y,
                   بلاڪ->w, بلاڪ->h, بلاڪ->delta_qp);
        }
        av_free(par);
    }

    /* av_video_enc_params_create_side_data */
    لکو("\nTesting av_video_enc_params_create_side_data()\n");
    چوکٺو = av_چوکٺو_alloc();
    إذا (چوکٺو) {
        par = av_video_enc_params_create_side_معلومات(چوکٺو,
                  AV_VIDEO_ENC_PARAMS_VP9, 2);
        إذا (par) {
            لکو("side_data: OK, type=%d, nb_blocks=%u\n",
                   par->type, par->nb_بلاڪون);
            بلاڪ = av_video_enc_params_بلاڪ(par, 0);
            بلاڪ->delta_qp = 5;
            بلاڪ = av_video_enc_params_بلاڪ(par, 0);
            لکو("side_data block 0: delta_qp=%d\n", بلاڪ->delta_qp);
        } وإلا {
            لکو("side_data: FAIL\n");
        }
        av_چوکٺو_free(&چوکٺو);
    }

    /* NONE type */
    لکو("\nTesting NONE type\n");
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_NONE, 0, &سائيز);
    إذا (par) {
        لکو("NONE: OK, type=%d\n", par->type);
        av_free(par);
    } وإلا {
        لکو("NONE: FAIL\n");
    }

    أرجع 0;
}
