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

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/frame.h"
#అన్తర్భావ "libavutil/mem.h"
#అన్తర్భావ "libavutil/video_enc_params.h"

పూర్ణాంకం ప్రధాన(శూన్య)
{
    AVVideoEncParams *par;
    AVVideo_ఖండం_Params *ఖండం;
    AVFrame *చట్రం;
    size_t కొలత;

    స్థిర స్థిరరాశి నిర్మాణం {
        గణన AVVideoEncParamsType type;
        స్థిరరాశి అక్షరం *name;
    } types[] = {
        { AV_VIDEO_ENC_PARAMS_VP9,   "VP9"   },
        { AV_VIDEO_ENC_PARAMS_H264,  "H264"  },
        { AV_VIDEO_ENC_PARAMS_MPEG2, "MPEG2" },
    };

    /* av_video_enc_params_alloc - each type with blocks */
    రాయి("Testing av_video_enc_params_alloc()\n");
    కొరకు (పూర్ణాంకం i = 0; i < 3; i++) {
        par = av_video_enc_params_alloc(types[i].type, 4, &కొలత);
        ఒకవేళ (par) {
            రాయి("%s: OK, type=%d, nb_blocks=%u, size>0=%s\n",
                   types[i].name, par->type, par->nb_ఖండాలు,
                   కొలత > 0 ? "yes" : "no");
            av_free(par);
        } లేకపోతే {
            రాయి("%s: FAIL\n", types[i].name);
        }
    }

    /* zero blocks */
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_VP9, 0, &కొలత);
    ఒకవేళ (par) {
        రాయి("zero blocks: OK, nb_blocks=%u\n", par->nb_ఖండాలు);
        av_free(par);
    } లేకపోతే {
        రాయి("zero blocks: FAIL\n");
    }

    /* alloc without size */
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_H264, 1, ఖాళీ);
    రాయి("alloc (no size): %s\n", par ? "OK" : "FAIL");
    av_free(par);

    /* av_video_enc_params_block - write and read back */
    రాయి("\nTesting av_video_enc_params_block()\n");
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_H264, 3, ఖాళీ);
    ఒకవేళ (par) {
        par->qp = 26;
        par->delta_qp[0][0] = -2;
        par->delta_qp[0][1] = -1;
        రాయి("frame qp=%d, delta_qp[0]={%d,%d}\n",
               par->qp, par->delta_qp[0][0], par->delta_qp[0][1]);

        కొరకు (పూర్ణాంకం i = 0; i < 3; i++) {
            ఖండం = av_video_enc_params_ఖండం(par, i);
            ఒకవేళ ((uint8_t *)ఖండం != (uint8_t *)par + par->ఖండాలు_స్థానభ్రంశం +
                                    (size_t)i * par->ఖండం_కొలత)
                రాయి("block %d: pointer inconsistent with blocks_offset/block_size\n", i);
            ఖండం->src_x = i * 16;
            ఖండం->src_y = i * 16;
            ఖండం->w = 16;
            ఖండం->h = 16;
            ఖండం->delta_qp = i - 1;
        }
        కొరకు (పూర్ణాంకం i = 0; i < 3; i++) {
            ఖండం = av_video_enc_params_ఖండం(par, i);
            రాయి("block %d: src=(%d,%d) size=%dx%d delta_qp=%d\n",
                   i, ఖండం->src_x, ఖండం->src_y,
                   ఖండం->w, ఖండం->h, ఖండం->delta_qp);
        }
        av_free(par);
    }

    /* av_video_enc_params_create_side_data */
    రాయి("\nTesting av_video_enc_params_create_side_data()\n");
    చట్రం = av_చట్రం_alloc();
    ఒకవేళ (చట్రం) {
        par = av_video_enc_params_create_side_దత్తాంశం(చట్రం,
                  AV_VIDEO_ENC_PARAMS_VP9, 2);
        ఒకవేళ (par) {
            రాయి("side_data: OK, type=%d, nb_blocks=%u\n",
                   par->type, par->nb_ఖండాలు);
            ఖండం = av_video_enc_params_ఖండం(par, 0);
            ఖండం->delta_qp = 5;
            ఖండం = av_video_enc_params_ఖండం(par, 0);
            రాయి("side_data block 0: delta_qp=%d\n", ఖండం->delta_qp);
        } లేకపోతే {
            రాయి("side_data: FAIL\n");
        }
        av_చట్రం_free(&చట్రం);
    }

    /* NONE type */
    రాయి("\nTesting NONE type\n");
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_NONE, 0, &కొలత);
    ఒకవేళ (par) {
        రాయి("NONE: OK, type=%d\n", par->type);
        av_free(par);
    } లేకపోతే {
        రాయి("NONE: FAIL\n");
    }

    తిరిగి 0;
}
