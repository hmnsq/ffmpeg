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

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdio.h>

#अन्तर्भाव "libavutil/frame.h"
#अन्तर्भाव "libavutil/mem.h"
#अन्तर्भाव "libavutil/video_enc_params.h"

पूर्णाङ्क मुख्यम्(शून्य)
{
    AVVideoEncParams *par;
    AVVideo_खण्डम्_Params *खण्डम्;
    AVFrame *frame;
    size_t आकार;

    स्थिर ध्रुव संरचना {
        गणना AVVideoEncParamsType type;
        ध्रुव वर्ण *name;
    } types[] = {
        { AV_VIDEO_ENC_PARAMS_VP9,   "VP9"   },
        { AV_VIDEO_ENC_PARAMS_H264,  "H264"  },
        { AV_VIDEO_ENC_PARAMS_MPEG2, "MPEG2" },
    };

    /* av_video_enc_params_alloc - each type with blocks */
    प्रारूप_लिख("Testing av_video_enc_params_alloc()\n");
    प्रति (पूर्णाङ्क i = 0; i < 3; i++) {
        par = av_video_enc_params_alloc(types[i].type, 4, &आकार);
        यदि (par) {
            प्रारूप_लिख("%s: OK, type=%d, nb_blocks=%u, size>0=%s\n",
                   types[i].name, par->type, par->nb_खण्डानि,
                   आकार > 0 ? "yes" : "no");
            av_free(par);
        } अन्यथा {
            प्रारूप_लिख("%s: FAIL\n", types[i].name);
        }
    }

    /* zero blocks */
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_VP9, 0, &आकार);
    यदि (par) {
        प्रारूप_लिख("zero blocks: OK, nb_blocks=%u\n", par->nb_खण्डानि);
        av_free(par);
    } अन्यथा {
        प्रारूप_लिख("zero blocks: FAIL\n");
    }

    /* alloc without size */
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_H264, 1, रिक्त);
    प्रारूप_लिख("alloc (no size): %s\n", par ? "OK" : "FAIL");
    av_free(par);

    /* av_video_enc_params_block - write and read back */
    प्रारूप_लिख("\nTesting av_video_enc_params_block()\n");
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_H264, 3, रिक्त);
    यदि (par) {
        par->qp = 26;
        par->delta_qp[0][0] = -2;
        par->delta_qp[0][1] = -1;
        प्रारूप_लिख("frame qp=%d, delta_qp[0]={%d,%d}\n",
               par->qp, par->delta_qp[0][0], par->delta_qp[0][1]);

        प्रति (पूर्णाङ्क i = 0; i < 3; i++) {
            खण्डम् = av_video_enc_params_खण्डम्(par, i);
            यदि ((uint8_t *)खण्डम् != (uint8_t *)par + par->खण्डानि_विस्थापनम् +
                                    (size_t)i * par->खण्डम्_आकार)
                प्रारूप_लिख("block %d: pointer inconsistent with blocks_offset/block_size\n", i);
            खण्डम्->src_x = i * 16;
            खण्डम्->src_y = i * 16;
            खण्डम्->w = 16;
            खण्डम्->h = 16;
            खण्डम्->delta_qp = i - 1;
        }
        प्रति (पूर्णाङ्क i = 0; i < 3; i++) {
            खण्डम् = av_video_enc_params_खण्डम्(par, i);
            प्रारूप_लिख("block %d: src=(%d,%d) size=%dx%d delta_qp=%d\n",
                   i, खण्डम्->src_x, खण्डम्->src_y,
                   खण्डम्->w, खण्डम्->h, खण्डम्->delta_qp);
        }
        av_free(par);
    }

    /* av_video_enc_params_create_side_data */
    प्रारूप_लिख("\nTesting av_video_enc_params_create_side_data()\n");
    frame = av_frame_alloc();
    यदि (frame) {
        par = av_video_enc_params_create_side_दत्त(frame,
                  AV_VIDEO_ENC_PARAMS_VP9, 2);
        यदि (par) {
            प्रारूप_लिख("side_data: OK, type=%d, nb_blocks=%u\n",
                   par->type, par->nb_खण्डानि);
            खण्डम् = av_video_enc_params_खण्डम्(par, 0);
            खण्डम्->delta_qp = 5;
            खण्डम् = av_video_enc_params_खण्डम्(par, 0);
            प्रारूप_लिख("side_data block 0: delta_qp=%d\n", खण्डम्->delta_qp);
        } अन्यथा {
            प्रारूप_लिख("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    /* NONE type */
    प्रारूप_लिख("\nTesting NONE type\n");
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_NONE, 0, &आकार);
    यदि (par) {
        प्रारूप_लिख("NONE: OK, type=%d\n", par->type);
        av_free(par);
    } अन्यथा {
        प्रारूप_लिख("NONE: FAIL\n");
    }

    प्रत्यागम 0;
}
