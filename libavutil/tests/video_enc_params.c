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

पूर्णाङ्क main(शून्य)
{
    AVVideoEncParams *par;
    AVVideoBlockParams *block;
    AVFrame *frame;
    माप_प्रकार size;

    स्थिर अचर संरचना {
        गणना AVVideoEncParamsType type;
        अचर वर्ण *name;
    } types[] = {
        { AV_VIDEO_ENC_PARAMS_VP9,   "VP9"   },
        { AV_VIDEO_ENC_PARAMS_H264,  "H264"  },
        { AV_VIDEO_ENC_PARAMS_MPEG2, "MPEG2" },
    };

    /* av_video_enc_params_alloc - each type with blocks */
    म_लिखो("Testing av_video_enc_params_alloc()\n");
    लागि (पूर्णाङ्क i = 0; i < 3; i++) {
        par = av_video_enc_params_alloc(types[i].type, 4, &size);
        यदि (par) {
            म_लिखो("%s: OK, type=%d, nb_blocks=%u, size>0=%s\n",
                   types[i].name, par->type, par->nb_blocks,
                   size > 0 ? "yes" : "no");
            av_free(par);
        } अन्यथा {
            म_लिखो("%s: FAIL\n", types[i].name);
        }
    }

    /* zero blocks */
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_VP9, 0, &size);
    यदि (par) {
        म_लिखो("zero blocks: OK, nb_blocks=%u\n", par->nb_blocks);
        av_free(par);
    } अन्यथा {
        म_लिखो("zero blocks: FAIL\n");
    }

    /* alloc without size */
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_H264, 1, रिक्त);
    म_लिखो("alloc (no size): %s\n", par ? "OK" : "FAIL");
    av_free(par);

    /* av_video_enc_params_block - write and read back */
    म_लिखो("\nTesting av_video_enc_params_block()\n");
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_H264, 3, रिक्त);
    यदि (par) {
        par->qp = 26;
        par->delta_qp[0][0] = -2;
        par->delta_qp[0][1] = -1;
        म_लिखो("frame qp=%d, delta_qp[0]={%d,%d}\n",
               par->qp, par->delta_qp[0][0], par->delta_qp[0][1]);

        लागि (पूर्णाङ्क i = 0; i < 3; i++) {
            block = av_video_enc_params_block(par, i);
            यदि ((uint8_t *)block != (uint8_t *)par + par->blocks_offset +
                                    (माप_प्रकार)i * par->block_size)
                म_लिखो("block %d: pointer inconsistent with blocks_offset/block_size\n", i);
            block->src_x = i * 16;
            block->src_y = i * 16;
            block->w = 16;
            block->h = 16;
            block->delta_qp = i - 1;
        }
        लागि (पूर्णाङ्क i = 0; i < 3; i++) {
            block = av_video_enc_params_block(par, i);
            म_लिखो("block %d: src=(%d,%d) size=%dx%d delta_qp=%d\n",
                   i, block->src_x, block->src_y,
                   block->w, block->h, block->delta_qp);
        }
        av_free(par);
    }

    /* av_video_enc_params_create_side_data */
    म_लिखो("\nTesting av_video_enc_params_create_side_data()\n");
    frame = av_frame_alloc();
    यदि (frame) {
        par = av_video_enc_params_create_side_data(frame,
                  AV_VIDEO_ENC_PARAMS_VP9, 2);
        यदि (par) {
            म_लिखो("side_data: OK, type=%d, nb_blocks=%u\n",
                   par->type, par->nb_blocks);
            block = av_video_enc_params_block(par, 0);
            block->delta_qp = 5;
            block = av_video_enc_params_block(par, 0);
            म_लिखो("side_data block 0: delta_qp=%d\n", block->delta_qp);
        } अन्यथा {
            म_लिखो("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    /* NONE type */
    म_लिखो("\nTesting NONE type\n");
    par = av_video_enc_params_alloc(AV_VIDEO_ENC_PARAMS_NONE, 0, &size);
    यदि (par) {
        म_लिखो("NONE: OK, type=%d\n", par->type);
        av_free(par);
    } अन्यथा {
        म_लिखो("NONE: FAIL\n");
    }

    फर्काऊ 0;
}
