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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/frame.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/video_enc_params.h"

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    AVVideoEncParams *par;
    AVVideo_ਖੰਡ_Params *ਖੰਡ;
    AVFrame *ਚੌਖਟਾ;
    size_t ਮਾਪ;

    ਸਥਿਰ ਅਚਲ ਬਣਤਰ {
        ਗਿਣਤੀ AVVideoEncParamsType type;
        ਅਚਲ ਅੱਖਰ *name;
    } types[] = {
        { AV_VIDEO_ENC_PARAMS_VP9,   "VP9"   },
        { AV_VIDEO_ENC_PARAMS_H264,  "H264"  },
        { AV_VIDEO_ENC_PARAMS_MPEG2, "MPEG2" },
    };

    /* av_video_enc_params_alloc - each type with blocks */
    ਲਿਖੋ("Testing av_video_enc_params_alloc()\n");
    ਲਈ (ਪੂਰਨ i = 0; i < 3; i++) {
        par = av_video_enc_params_alloc(types[i].type, 4, &ਮਾਪ);
        ਜੇ (par) {
            ਲਿਖੋ("%s: OK, type=%d, nb_blocks=%u, size>0=%s\n",
                   types[i].name, par->type, par->nb_ਖੰਡਾਂ,
                   ਮਾਪ > 0 ? "yes" : "no");
            av_free(par);
        } ਨਹੀਂਤਾਂ {
            ਲਿਖੋ("%s: FAIL\n", types[i].name);
        }
    }

    /* zero blocks */
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_VP9, 0, &ਮਾਪ);
    ਜੇ (par) {
        ਲਿਖੋ("zero blocks: OK, nb_blocks=%u\n", par->nb_ਖੰਡਾਂ);
        av_free(par);
    } ਨਹੀਂਤਾਂ {
        ਲਿਖੋ("zero blocks: FAIL\n");
    }

    /* alloc without size */
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_H264, 1, ਨਿਰਾ);
    ਲਿਖੋ("alloc (no size): %s\n", par ? "OK" : "FAIL");
    av_free(par);

    /* av_video_enc_params_block - write and read back */
    ਲਿਖੋ("\nTesting av_video_enc_params_block()\n");
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_H264, 3, ਨਿਰਾ);
    ਜੇ (par) {
        par->qp = 26;
        par->delta_qp[0][0] = -2;
        par->delta_qp[0][1] = -1;
        ਲਿਖੋ("frame qp=%d, delta_qp[0]={%d,%d}\n",
               par->qp, par->delta_qp[0][0], par->delta_qp[0][1]);

        ਲਈ (ਪੂਰਨ i = 0; i < 3; i++) {
            ਖੰਡ = av_video_enc_params_ਖੰਡ(par, i);
            ਜੇ ((uint8_t *)ਖੰਡ != (uint8_t *)par + par->ਖੰਡਾਂ_ਵਿੱਥ +
                                    (size_t)i * par->ਖੰਡ_ਮਾਪ)
                ਲਿਖੋ("block %d: pointer inconsistent with blocks_offset/block_size\n", i);
            ਖੰਡ->src_x = i * 16;
            ਖੰਡ->src_y = i * 16;
            ਖੰਡ->w = 16;
            ਖੰਡ->h = 16;
            ਖੰਡ->delta_qp = i - 1;
        }
        ਲਈ (ਪੂਰਨ i = 0; i < 3; i++) {
            ਖੰਡ = av_video_enc_params_ਖੰਡ(par, i);
            ਲਿਖੋ("block %d: src=(%d,%d) size=%dx%d delta_qp=%d\n",
                   i, ਖੰਡ->src_x, ਖੰਡ->src_y,
                   ਖੰਡ->w, ਖੰਡ->h, ਖੰਡ->delta_qp);
        }
        av_free(par);
    }

    /* av_video_enc_params_create_side_data */
    ਲਿਖੋ("\nTesting av_video_enc_params_create_side_data()\n");
    ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    ਜੇ (ਚੌਖਟਾ) {
        par = av_video_enc_params_create_side_ਅੰਕੜੇ(ਚੌਖਟਾ,
                  AV_VIDEO_ENC_PARAMS_VP9, 2);
        ਜੇ (par) {
            ਲਿਖੋ("side_data: OK, type=%d, nb_blocks=%u\n",
                   par->type, par->nb_ਖੰਡਾਂ);
            ਖੰਡ = av_video_enc_params_ਖੰਡ(par, 0);
            ਖੰਡ->delta_qp = 5;
            ਖੰਡ = av_video_enc_params_ਖੰਡ(par, 0);
            ਲਿਖੋ("side_data block 0: delta_qp=%d\n", ਖੰਡ->delta_qp);
        } ਨਹੀਂਤਾਂ {
            ਲਿਖੋ("side_data: FAIL\n");
        }
        av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);
    }

    /* NONE type */
    ਲਿਖੋ("\nTesting NONE type\n");
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_NONE, 0, &ਮਾਪ);
    ਜੇ (par) {
        ਲਿਖੋ("NONE: OK, type=%d\n", par->type);
        av_free(par);
    } ਨਹੀਂਤਾਂ {
        ਲਿਖੋ("NONE: FAIL\n");
    }

    ਵਾਪਸ 0;
}
