/*
 * pixel format descriptor
 * Copyright (c) 2009 Michael Niedermayer <michaelni@gmx.at>
 *
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

#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "avstring.h"
#ଅନ୍ତର୍ଭାଵ "common.h"
#ଅନ୍ତର୍ଭାଵ "pixfmt.h"
#ଅନ୍ତର୍ଭାଵ "pixdesc.h"
#ଅନ୍ତର୍ଭାଵ "intreadwrite.h"

ଶୂନ୍ୟ av_read_image_line2(ଶୂନ୍ୟ *dst,
                        ଅଚଳ uint8_t *data[4], ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା linesize[4],
                        ଅଚଳ AVPixFmtDescriptor *desc,
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w,
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା read_pal_component,
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା dst_element_size)
{
    AVComponentDescriptor comp = desc->comp[c];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା plane = comp.plane;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା depth = comp.depth;
    unsigned mask  = (1ULL << depth) - 1;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା shift = comp.shift;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା step  = comp.step;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = desc->flags;
    uint16_t *dst16 = dst;
    uint32_t *dst32 = dst;

    ଯଦି (!depth)
        ଫେରନ୍ତୁ;

    ଯଦି (flags & AV_PIX_FMT_FLAG_BITSTREAM) {
        ଯଦି (step > 8) {
            // Assume all channels are packed into a 32bit value
            ଅଚଳ uint8_t *byte_p = data[plane] + y * linesize[plane];
            ଅଚଳ uint32_t *p = (uint32_t *)byte_p;

            ଯେତେବେଳେ (w--) {
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା val = AV_RB32(p);
                val = (val >> comp.offset) & mask;
                ଯଦି (read_pal_component)
                    val = data[1][4*val + c];
                ଯଦି (dst_element_size == 4) *dst32++ = val;
                ଅନ୍ୟଥା                       *dst16++ = val;
                p++;
            }
        } ଅନ୍ୟଥା {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା skip = x * step + comp.offset;
            ଅଚଳ uint8_t *p = data[plane] + y * linesize[plane] + (skip >> 3);
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା shift = 8 - depth - (skip & 7);

            ଯେତେବେଳେ (w--) {
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା val = (*p >> shift) & mask;
                ଯଦି (read_pal_component)
                    val = data[1][4*val + c];
                shift -= step;
                p -= shift >> 3;
                shift &= 7;
                ଯଦି (dst_element_size == 4) *dst32++ = val;
                ଅନ୍ୟଥା                       *dst16++ = val;
            }
        }
    } ଅନ୍ୟଥା {
        ଅଚଳ uint8_t *p = data[plane] + y * linesize[plane] +
                           x * step + comp.offset;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା is_8bit = shift + depth <= 8;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା is_16bit= shift + depth <=16;

        ଯଦି (is_8bit)
            p += !!(flags & AV_PIX_FMT_FLAG_BE);

        ଯେତେବେଳେ (w--) {
            unsigned val;
            ଯଦି     (is_8bit)  val = *p;
            ଅନ୍ୟଥା ଯଦି(is_16bit) val = flags & AV_PIX_FMT_FLAG_BE ? AV_RB16(p) : AV_RL16(p);
            ଅନ୍ୟଥା              val = flags & AV_PIX_FMT_FLAG_BE ? AV_RB32(p) : AV_RL32(p);
            val = (val >> shift) & mask;
            ଯଦି (read_pal_component)
                val = data[1][4 * val + c];
            p += step;
            ଯଦି (dst_element_size == 4) *dst32++ = val;
            ଅନ୍ୟଥା                       *dst16++ = val;
        }
    }
}

ଶୂନ୍ୟ av_read_image_ଧାଡ଼ି(uint16_t *dst,
                        ଅଚଳ uint8_t *data[4], ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା linesize[4],
                        ଅଚଳ AVPixFmtDescriptor *desc,
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w,
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା read_pal_component)
{
    av_read_image_line2(dst, data, linesize, desc,x, y, c, w,
                        read_pal_component,
                        2);
}

ଶୂନ୍ୟ av_write_image_line2(ଅଚଳ ଶୂନ୍ୟ *src,
                         uint8_t *data[4], ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା linesize[4],
                         ଅଚଳ AVPixFmtDescriptor *desc,
                         ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_element_size)
{
    AVComponentDescriptor comp = desc->comp[c];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା plane = comp.plane;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା depth = comp.depth;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା step  = comp.step;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = desc->flags;
    ଅଚଳ uint32_t *src32 = src;
    ଅଚଳ uint16_t *src16 = src;

    ଯଦି (!depth)
        ଫେରନ୍ତୁ;

    ଯଦି (flags & AV_PIX_FMT_FLAG_BITSTREAM) {
        ଯଦି (step > 8) {
            // Assume all channels are packed into a 32bit value
            ଅଚଳ uint8_t *byte_p = data[plane] + y * linesize[plane];
            uint32_t *p = (uint32_t *)byte_p;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା offset = comp.offset;
            uint32_t mask  = ((1ULL << depth) - 1) << offset;

            ଯେତେବେଳେ (w--) {
                unsigned val = src_element_size == 4 ? *src32++ : *src16++;
                AV_WB32(p, (AV_RB32(p) & ~mask) | (val << offset));
                p++;
            }
        } ଅନ୍ୟଥା {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା skip = x * step + comp.offset;
            uint8_t *p = data[plane] + y * linesize[plane] + (skip >> 3);
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା shift = 8 - depth - (skip & 7);

            ଯେତେବେଳେ (w--) {
                *p |= (src_element_size == 4 ? *src32++ : *src16++) << shift;
                shift -= step;
                p -= shift >> 3;
                shift &= 7;
            }
        }
    } ଅନ୍ୟଥା {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା shift = comp.shift;
        uint8_t *p = data[plane] + y * linesize[plane] +
                     x * step + comp.offset;

        ଯଦି (shift + depth <= 8) {
            p += !!(flags & AV_PIX_FMT_FLAG_BE);
            ଯେତେବେଳେ (w--) {
                *p |= ((src_element_size == 4 ? *src32++ : *src16++) << shift);
                p += step;
            }
        } ଅନ୍ୟଥା {
            ଯେତେବେଳେ (w--) {
                unsigned s = (src_element_size == 4 ? *src32++ : *src16++);
                ଯଦି (shift + depth <= 16) {
                    ଯଦି (flags & AV_PIX_FMT_FLAG_BE) {
                        uint16_t val = AV_RB16(p) | (s << shift);
                        AV_WB16(p, val);
                    } ଅନ୍ୟଥା {
                        uint16_t val = AV_RL16(p) | (s << shift);
                        AV_WL16(p, val);
                    }
                } ଅନ୍ୟଥା {
                    ଯଦି (flags & AV_PIX_FMT_FLAG_BE) {
                        uint32_t val = AV_RB32(p) | (s << shift);
                        AV_WB32(p, val);
                    } ଅନ୍ୟଥା {
                        uint32_t val = AV_RL32(p) | (s << shift);
                        AV_WL32(p, val);
                    }
                }
                p += step;
            }
        }
    }
}

ଶୂନ୍ୟ av_write_image_ଧାଡ଼ି(ଅଚଳ uint16_t *src,
                         uint8_t *data[4], ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା linesize[4],
                         ଅଚଳ AVPixFmtDescriptor *desc,
                         ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w)
{
    av_write_image_line2(src, data, linesize, desc, x, y, c, w, 2);
}

ସ୍ଥିର ଅଚଳ AVPixFmtDescriptor av_pix_fmt_descriptors[AV_PIX_FMT_NB] = {
    [AV_PIX_FMT_YUV420P] = {
        .name = "yuv420p",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
            { 1, 1, 0, 0, 8 },        /* U */
            { 2, 1, 0, 0, 8 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUYV422] = {
        .name = "yuyv422",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 8 },        /* Y */
            { 0, 4, 1, 0, 8 },        /* U */
            { 0, 4, 3, 0, 8 },        /* V */
        },
    },
    [AV_PIX_FMT_YVYU422] = {
        .name = "yvyu422",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 8 },        /* Y */
            { 0, 4, 3, 0, 8 },        /* U */
            { 0, 4, 1, 0, 8 },        /* V */
        },
    },
    [AV_PIX_FMT_Y210LE] = {
        .name = "y210le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 0, 6, 10 },        /* Y */
            { 0, 8, 2, 6, 10 },        /* U */
            { 0, 8, 6, 6, 10 },        /* V */
        },
    },
    [AV_PIX_FMT_Y210BE] = {
        .name = "y210be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 0, 6, 10 },        /* Y */
            { 0, 8, 2, 6, 10 },        /* U */
            { 0, 8, 6, 6, 10 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE,
    },
    [AV_PIX_FMT_RGB24] = {
        .name = "rgb24",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 3, 0, 0, 8 },        /* R */
            { 0, 3, 1, 0, 8 },        /* G */
            { 0, 3, 2, 0, 8 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_BGR24] = {
        .name = "bgr24",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 3, 2, 0, 8 },        /* R */
            { 0, 3, 1, 0, 8 },        /* G */
            { 0, 3, 0, 0, 8 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_X2RGB10LE] = {
        .name = "x2rgb10le",
        .nb_components= 3,
        .log2_chroma_w= 0,
        .log2_chroma_h= 0,
        .comp = {
            { 0, 4, 2, 4, 10 },       /* R */
            { 0, 4, 1, 2, 10 },       /* G */
            { 0, 4, 0, 0, 10 },       /* B */
            { 0, 4, 3, 6,  2 },       /* X */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_X2RGB10BE] = {
        .name = "x2rgb10be",
        .nb_components= 3,
        .log2_chroma_w= 0,
        .log2_chroma_h= 0,
        .comp = {
            { 0, 4, 0, 4, 10 },       /* R */
            { 0, 4, 1, 2, 10 },       /* G */
            { 0, 4, 2, 0, 10 },       /* B */
            { 0, 4, 3, 6,  2 },       /* X */
        },
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_BE,
    },
    [AV_PIX_FMT_X2BGR10LE] = {
        .name = "x2bgr10le",
        .nb_components= 3,
        .log2_chroma_w= 0,
        .log2_chroma_h= 0,
        .comp = {
            { 0, 4, 0, 0, 10 },       /* R */
            { 0, 4, 1, 2, 10 },       /* G */
            { 0, 4, 2, 4, 10 },       /* B */
            { 0, 4, 3, 6,  2 },       /* X */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_X2BGR10BE] = {
        .name = "x2bgr10be",
        .nb_components= 3,
        .log2_chroma_w= 0,
        .log2_chroma_h= 0,
        .comp = {
            { 0, 4, 2, 0, 10 },       /* R */
            { 0, 4, 1, 2, 10 },       /* G */
            { 0, 4, 0, 4, 10 },       /* B */
            { 0, 4, 3, 6,  2 },       /* X */
        },
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_BE,
    },
    [AV_PIX_FMT_YUV422P] = {
        .name = "yuv422p",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
            { 1, 1, 0, 0, 8 },        /* U */
            { 2, 1, 0, 0, 8 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV444P] = {
        .name = "yuv444p",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
            { 1, 1, 0, 0, 8 },        /* U */
            { 2, 1, 0, 0, 8 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV410P] = {
        .name = "yuv410p",
        .nb_components = 3,
        .log2_chroma_w = 2,
        .log2_chroma_h = 2,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
            { 1, 1, 0, 0, 8 },        /* U */
            { 2, 1, 0, 0, 8 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV411P] = {
        .name = "yuv411p",
        .nb_components = 3,
        .log2_chroma_w = 2,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
            { 1, 1, 0, 0, 8 },        /* U */
            { 2, 1, 0, 0, 8 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUVJ411P] = {
        .name = "yuvj411p",
        .nb_components = 3,
        .log2_chroma_w = 2,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
            { 1, 1, 0, 0, 8 },        /* U */
            { 2, 1, 0, 0, 8 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_GRAY8] = {
        .name = "gray",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
        },
        .alias = "gray8,y8",
    },
    [AV_PIX_FMT_MONOWHITE] = {
        .name = "monow",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 1, 0, 0, 1 },        /* Y */
        },
        .flags = AV_PIX_FMT_FLAG_BITSTREAM,
    },
    [AV_PIX_FMT_MONOBLACK] = {
        .name = "monob",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 1, 0, 7, 1 },        /* Y */
        },
        .flags = AV_PIX_FMT_FLAG_BITSTREAM,
    },
    [AV_PIX_FMT_PAL8] = {
        .name = "pal8",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 1, 0, 0, 8 },
        },
        .flags = AV_PIX_FMT_FLAG_PAL | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVJ420P] = {
        .name = "yuvj420p",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
            { 1, 1, 0, 0, 8 },        /* U */
            { 2, 1, 0, 0, 8 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUVJ422P] = {
        .name = "yuvj422p",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
            { 1, 1, 0, 0, 8 },        /* U */
            { 2, 1, 0, 0, 8 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUVJ444P] = {
        .name = "yuvj444p",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
            { 1, 1, 0, 0, 8 },        /* U */
            { 2, 1, 0, 0, 8 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_UYVY422] = {
        .name = "uyvy422",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 1, 0, 8 },        /* Y */
            { 0, 4, 0, 0, 8 },        /* U */
            { 0, 4, 2, 0, 8 },        /* V */
        },
    },
    [AV_PIX_FMT_UYYVYY411] = {
        .name = "uyyvyy411",
        .nb_components = 3,
        .log2_chroma_w = 2,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 1, 0, 8 },        /* Y */
            { 0, 6, 0, 0, 8 },        /* U */
            { 0, 6, 3, 0, 8 },        /* V */
        },
    },
    [AV_PIX_FMT_BGR8] = {
        .name = "bgr8",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 1, 0, 0, 3 },        /* R */
            { 0, 1, 0, 3, 3 },        /* G */
            { 0, 1, 0, 6, 2 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_BGR4] = {
        .name = "bgr4",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 3, 0, 1 },        /* R */
            { 0, 4, 1, 0, 2 },        /* G */
            { 0, 4, 0, 0, 1 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_BGR4_BYTE] = {
        .name = "bgr4_byte",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 1, 0, 0, 1 },        /* R */
            { 0, 1, 0, 1, 2 },        /* G */
            { 0, 1, 0, 3, 1 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_RGB8] = {
        .name = "rgb8",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 1, 0, 5, 3 },        /* R */
            { 0, 1, 0, 2, 3 },        /* G */
            { 0, 1, 0, 0, 2 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_RGB4] = {
        .name = "rgb4",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 0, 0, 1 },        /* R */
            { 0, 4, 1, 0, 2 },        /* G */
            { 0, 4, 3, 0, 1 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_RGB4_BYTE] = {
        .name = "rgb4_byte",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 1, 0, 3, 1 },        /* R */
            { 0, 1, 0, 1, 2 },        /* G */
            { 0, 1, 0, 0, 1 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_NV12] = {
        .name = "nv12",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
            { 1, 2, 0, 0, 8 },        /* U */
            { 1, 2, 1, 0, 8 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_NV21] = {
        .name = "nv21",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
            { 1, 2, 1, 0, 8 },        /* U */
            { 1, 2, 0, 0, 8 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_ARGB] = {
        .name = "argb",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 1, 0, 8 },        /* R */
            { 0, 4, 2, 0, 8 },        /* G */
            { 0, 4, 3, 0, 8 },        /* B */
            { 0, 4, 0, 0, 8 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_RGBA] = {
        .name = "rgba",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 0, 0, 8 },        /* R */
            { 0, 4, 1, 0, 8 },        /* G */
            { 0, 4, 2, 0, 8 },        /* B */
            { 0, 4, 3, 0, 8 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_ABGR] = {
        .name = "abgr",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 3, 0, 8 },        /* R */
            { 0, 4, 2, 0, 8 },        /* G */
            { 0, 4, 1, 0, 8 },        /* B */
            { 0, 4, 0, 0, 8 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_BGRA] = {
        .name = "bgra",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 2, 0, 8 },        /* R */
            { 0, 4, 1, 0, 8 },        /* G */
            { 0, 4, 0, 0, 8 },        /* B */
            { 0, 4, 3, 0, 8 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_0RGB] = {
        .name = "0rgb",
        .nb_components= 3,
        .log2_chroma_w= 0,
        .log2_chroma_h= 0,
        .comp = {
            { 0, 4, 1, 0, 8 },        /* R */
            { 0, 4, 2, 0, 8 },        /* G */
            { 0, 4, 3, 0, 8 },        /* B */
            { 0, 4, 0, 0, 8 },        /* X */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_RGB0] = {
        .name = "rgb0",
        .nb_components= 3,
        .log2_chroma_w= 0,
        .log2_chroma_h= 0,
        .comp = {
            { 0, 4, 0, 0, 8 },        /* R */
            { 0, 4, 1, 0, 8 },        /* G */
            { 0, 4, 2, 0, 8 },        /* B */
            { 0, 4, 3, 0, 8 },        /* X */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_0BGR] = {
        .name = "0bgr",
        .nb_components= 3,
        .log2_chroma_w= 0,
        .log2_chroma_h= 0,
        .comp = {
            { 0, 4, 3, 0, 8 },        /* R */
            { 0, 4, 2, 0, 8 },        /* G */
            { 0, 4, 1, 0, 8 },        /* B */
            { 0, 4, 0, 0, 8 },        /* X */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_BGR0] = {
        .name = "bgr0",
        .nb_components= 3,
        .log2_chroma_w= 0,
        .log2_chroma_h= 0,
        .comp = {
            { 0, 4, 2, 0, 8 },        /* R */
            { 0, 4, 1, 0, 8 },        /* G */
            { 0, 4, 0, 0, 8 },        /* B */
            { 0, 4, 3, 0, 8 },        /* X */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_GRAY9BE] = {
        .name = "gray9be",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 9 },       /* Y */
        },
        .flags = AV_PIX_FMT_FLAG_BE,
        .alias = "y9be",
    },
    [AV_PIX_FMT_GRAY9LE] = {
        .name = "gray9le",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 9 },       /* Y */
        },
        .alias = "y9le",
    },
    [AV_PIX_FMT_GRAY10BE] = {
        .name = "gray10be",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 10 },       /* Y */
        },
        .flags = AV_PIX_FMT_FLAG_BE,
        .alias = "y10be",
    },
    [AV_PIX_FMT_GRAY10LE] = {
        .name = "gray10le",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 10 },       /* Y */
        },
        .alias = "y10le",
    },
    [AV_PIX_FMT_GRAY12BE] = {
        .name = "gray12be",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 12 },       /* Y */
        },
        .flags = AV_PIX_FMT_FLAG_BE,
        .alias = "y12be",
    },
    [AV_PIX_FMT_GRAY12LE] = {
        .name = "gray12le",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 12 },       /* Y */
        },
        .alias = "y12le",
    },
    [AV_PIX_FMT_GRAY14BE] = {
        .name = "gray14be",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 14 },       /* Y */
        },
        .flags = AV_PIX_FMT_FLAG_BE,
        .alias = "y14be",
    },
    [AV_PIX_FMT_GRAY14LE] = {
        .name = "gray14le",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 14 },       /* Y */
        },
        .alias = "y14le",
    },
    [AV_PIX_FMT_GRAY16BE] = {
        .name = "gray16be",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 16 },       /* Y */
        },
        .flags = AV_PIX_FMT_FLAG_BE,
        .alias = "y16be",
    },
    [AV_PIX_FMT_GRAY16LE] = {
        .name = "gray16le",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 16 },       /* Y */
        },
        .alias = "y16le",
    },
    [AV_PIX_FMT_GRAY32BE] = {
        .name = "gray32be",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 0, 0, 32 },       /* Y */
        },
        .flags = AV_PIX_FMT_FLAG_BE,
        .alias = "y32be",
    },
    [AV_PIX_FMT_GRAY32LE] = {
        .name = "gray32le",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 0, 0, 32 },       /* Y */
        },
        .alias = "y32le",
    },
    [AV_PIX_FMT_YUV440P] = {
        .name = "yuv440p",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
            { 1, 1, 0, 0, 8 },        /* U */
            { 2, 1, 0, 0, 8 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUVJ440P] = {
        .name = "yuvj440p",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
            { 1, 1, 0, 0, 8 },        /* U */
            { 2, 1, 0, 0, 8 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV440P10LE] = {
        .name = "yuv440p10le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 10 },        /* Y */
            { 1, 2, 0, 0, 10 },        /* U */
            { 2, 2, 0, 0, 10 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV440P10BE] = {
        .name = "yuv440p10be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 10 },        /* Y */
            { 1, 2, 0, 0, 10 },        /* U */
            { 2, 2, 0, 0, 10 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV440P12LE] = {
        .name = "yuv440p12le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 12 },        /* Y */
            { 1, 2, 0, 0, 12 },        /* U */
            { 2, 2, 0, 0, 12 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV440P12BE] = {
        .name = "yuv440p12be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 12 },        /* Y */
            { 1, 2, 0, 0, 12 },        /* U */
            { 2, 2, 0, 0, 12 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUVA420P] = {
        .name = "yuva420p",
        .nb_components = 4,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
            { 1, 1, 0, 0, 8 },        /* U */
            { 2, 1, 0, 0, 8 },        /* V */
            { 3, 1, 0, 0, 8 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA422P] = {
        .name = "yuva422p",
        .nb_components = 4,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
            { 1, 1, 0, 0, 8 },        /* U */
            { 2, 1, 0, 0, 8 },        /* V */
            { 3, 1, 0, 0, 8 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA444P] = {
        .name = "yuva444p",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
            { 1, 1, 0, 0, 8 },        /* U */
            { 2, 1, 0, 0, 8 },        /* V */
            { 3, 1, 0, 0, 8 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA420P9BE] = {
        .name = "yuva420p9be",
        .nb_components = 4,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 9 },        /* Y */
            { 1, 2, 0, 0, 9 },        /* U */
            { 2, 2, 0, 0, 9 },        /* V */
            { 3, 2, 0, 0, 9 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA420P9LE] = {
        .name = "yuva420p9le",
        .nb_components = 4,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 9 },        /* Y */
            { 1, 2, 0, 0, 9 },        /* U */
            { 2, 2, 0, 0, 9 },        /* V */
            { 3, 2, 0, 0, 9 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA422P9BE] = {
        .name = "yuva422p9be",
        .nb_components = 4,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 9 },        /* Y */
            { 1, 2, 0, 0, 9 },        /* U */
            { 2, 2, 0, 0, 9 },        /* V */
            { 3, 2, 0, 0, 9 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA422P9LE] = {
        .name = "yuva422p9le",
        .nb_components = 4,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 9 },        /* Y */
            { 1, 2, 0, 0, 9 },        /* U */
            { 2, 2, 0, 0, 9 },        /* V */
            { 3, 2, 0, 0, 9 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA444P9BE] = {
        .name = "yuva444p9be",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 9 },        /* Y */
            { 1, 2, 0, 0, 9 },        /* U */
            { 2, 2, 0, 0, 9 },        /* V */
            { 3, 2, 0, 0, 9 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA444P9LE] = {
        .name = "yuva444p9le",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 9 },        /* Y */
            { 1, 2, 0, 0, 9 },        /* U */
            { 2, 2, 0, 0, 9 },        /* V */
            { 3, 2, 0, 0, 9 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA420P10BE] = {
        .name = "yuva420p10be",
        .nb_components = 4,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 10 },        /* Y */
            { 1, 2, 0, 0, 10 },        /* U */
            { 2, 2, 0, 0, 10 },        /* V */
            { 3, 2, 0, 0, 10 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA420P10LE] = {
        .name = "yuva420p10le",
        .nb_components = 4,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 10 },        /* Y */
            { 1, 2, 0, 0, 10 },        /* U */
            { 2, 2, 0, 0, 10 },        /* V */
            { 3, 2, 0, 0, 10 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA422P10BE] = {
        .name = "yuva422p10be",
        .nb_components = 4,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 10 },        /* Y */
            { 1, 2, 0, 0, 10 },        /* U */
            { 2, 2, 0, 0, 10 },        /* V */
            { 3, 2, 0, 0, 10 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA422P10LE] = {
        .name = "yuva422p10le",
        .nb_components = 4,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 10 },        /* Y */
            { 1, 2, 0, 0, 10 },        /* U */
            { 2, 2, 0, 0, 10 },        /* V */
            { 3, 2, 0, 0, 10 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA444P10BE] = {
        .name = "yuva444p10be",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 10 },        /* Y */
            { 1, 2, 0, 0, 10 },        /* U */
            { 2, 2, 0, 0, 10 },        /* V */
            { 3, 2, 0, 0, 10 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA444P10LE] = {
        .name = "yuva444p10le",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 10 },        /* Y */
            { 1, 2, 0, 0, 10 },        /* U */
            { 2, 2, 0, 0, 10 },        /* V */
            { 3, 2, 0, 0, 10 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA420P16BE] = {
        .name = "yuva420p16be",
        .nb_components = 4,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 16 },        /* Y */
            { 1, 2, 0, 0, 16 },        /* U */
            { 2, 2, 0, 0, 16 },        /* V */
            { 3, 2, 0, 0, 16 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA420P16LE] = {
        .name = "yuva420p16le",
        .nb_components = 4,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 16 },        /* Y */
            { 1, 2, 0, 0, 16 },        /* U */
            { 2, 2, 0, 0, 16 },        /* V */
            { 3, 2, 0, 0, 16 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA422P16BE] = {
        .name = "yuva422p16be",
        .nb_components = 4,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 16 },        /* Y */
            { 1, 2, 0, 0, 16 },        /* U */
            { 2, 2, 0, 0, 16 },        /* V */
            { 3, 2, 0, 0, 16 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA422P16LE] = {
        .name = "yuva422p16le",
        .nb_components = 4,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 16 },        /* Y */
            { 1, 2, 0, 0, 16 },        /* U */
            { 2, 2, 0, 0, 16 },        /* V */
            { 3, 2, 0, 0, 16 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA444P16BE] = {
        .name = "yuva444p16be",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 16 },        /* Y */
            { 1, 2, 0, 0, 16 },        /* U */
            { 2, 2, 0, 0, 16 },        /* V */
            { 3, 2, 0, 0, 16 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA444P16LE] = {
        .name = "yuva444p16le",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 16 },        /* Y */
            { 1, 2, 0, 0, 16 },        /* U */
            { 2, 2, 0, 0, 16 },        /* V */
            { 3, 2, 0, 0, 16 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_RGB48BE] = {
        .name = "rgb48be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 6, 0, 0, 16 },       /* R */
            { 0, 6, 2, 0, 16 },       /* G */
            { 0, 6, 4, 0, 16 },       /* B */
        },
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_BE,
    },
    [AV_PIX_FMT_RGB48LE] = {
        .name = "rgb48le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 6, 0, 0, 16 },       /* R */
            { 0, 6, 2, 0, 16 },       /* G */
            { 0, 6, 4, 0, 16 },       /* B */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_RGBA64BE] = {
        .name = "rgba64be",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 8, 0, 0, 16 },       /* R */
            { 0, 8, 2, 0, 16 },       /* G */
            { 0, 8, 4, 0, 16 },       /* B */
            { 0, 8, 6, 0, 16 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_RGBA64LE] = {
        .name = "rgba64le",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 8, 0, 0, 16 },       /* R */
            { 0, 8, 2, 0, 16 },       /* G */
            { 0, 8, 4, 0, 16 },       /* B */
            { 0, 8, 6, 0, 16 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_RGB565BE] = {
        .name = "rgb565be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, -1, 3, 5 },        /* R */
            { 0, 2,  0, 5, 6 },        /* G */
            { 0, 2,  0, 0, 5 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_RGB565LE] = {
        .name = "rgb565le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 1, 3, 5 },        /* R */
            { 0, 2, 0, 5, 6 },        /* G */
            { 0, 2, 0, 0, 5 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_RGB555BE] = {
        .name = "rgb555be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, -1, 2, 5 },        /* R */
            { 0, 2,  0, 5, 5 },        /* G */
            { 0, 2,  0, 0, 5 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_RGB555LE] = {
        .name = "rgb555le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 1, 2, 5 },        /* R */
            { 0, 2, 0, 5, 5 },        /* G */
            { 0, 2, 0, 0, 5 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_RGB444BE] = {
        .name = "rgb444be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, -1, 0, 4 },        /* R */
            { 0, 2,  0, 4, 4 },        /* G */
            { 0, 2,  0, 0, 4 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_RGB444LE] = {
        .name = "rgb444le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 1, 0, 4 },        /* R */
            { 0, 2, 0, 4, 4 },        /* G */
            { 0, 2, 0, 0, 4 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_BGR48BE] = {
        .name = "bgr48be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 6, 4, 0, 16 },       /* R */
            { 0, 6, 2, 0, 16 },       /* G */
            { 0, 6, 0, 0, 16 },       /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_BGR48LE] = {
        .name = "bgr48le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 6, 4, 0, 16 },       /* R */
            { 0, 6, 2, 0, 16 },       /* G */
            { 0, 6, 0, 0, 16 },       /* B */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_BGRA64BE] = {
        .name = "bgra64be",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 8, 4, 0, 16 },       /* R */
            { 0, 8, 2, 0, 16 },       /* G */
            { 0, 8, 0, 0, 16 },       /* B */
            { 0, 8, 6, 0, 16 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_BGRA64LE] = {
        .name = "bgra64le",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 8, 4, 0, 16 },       /* R */
            { 0, 8, 2, 0, 16 },       /* G */
            { 0, 8, 0, 0, 16 },       /* B */
            { 0, 8, 6, 0, 16 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_BGR565BE] = {
        .name = "bgr565be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2,  0, 0, 5 },        /* R */
            { 0, 2,  0, 5, 6 },        /* G */
            { 0, 2, -1, 3, 5 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_BGR565LE] = {
        .name = "bgr565le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 5 },        /* R */
            { 0, 2, 0, 5, 6 },        /* G */
            { 0, 2, 1, 3, 5 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_BGR555BE] = {
        .name = "bgr555be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2,  0, 0, 5 },       /* R */
            { 0, 2,  0, 5, 5 },       /* G */
            { 0, 2, -1, 2, 5 },       /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_RGB,
     },
    [AV_PIX_FMT_BGR555LE] = {
        .name = "bgr555le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 5 },        /* R */
            { 0, 2, 0, 5, 5 },        /* G */
            { 0, 2, 1, 2, 5 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_BGR444BE] = {
        .name = "bgr444be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2,  0, 0, 4 },       /* R */
            { 0, 2,  0, 4, 4 },       /* G */
            { 0, 2, -1, 0, 4 },       /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_RGB,
     },
    [AV_PIX_FMT_BGR444LE] = {
        .name = "bgr444le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 4 },        /* R */
            { 0, 2, 0, 4, 4 },        /* G */
            { 0, 2, 1, 0, 4 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_VAAPI] = {
        .name = "vaapi",
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .flags = AV_PIX_FMT_FLAG_HWACCEL,
    },
    [AV_PIX_FMT_YUV420P9LE] = {
        .name = "yuv420p9le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 9 },        /* Y */
            { 1, 2, 0, 0, 9 },        /* U */
            { 2, 2, 0, 0, 9 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV420P9BE] = {
        .name = "yuv420p9be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 9 },        /* Y */
            { 1, 2, 0, 0, 9 },        /* U */
            { 2, 2, 0, 0, 9 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV420P10LE] = {
        .name = "yuv420p10le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 10 },        /* Y */
            { 1, 2, 0, 0, 10 },        /* U */
            { 2, 2, 0, 0, 10 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV420P10BE] = {
        .name = "yuv420p10be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 10 },        /* Y */
            { 1, 2, 0, 0, 10 },        /* U */
            { 2, 2, 0, 0, 10 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV420P12LE] = {
        .name = "yuv420p12le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 12 },        /* Y */
            { 1, 2, 0, 0, 12 },        /* U */
            { 2, 2, 0, 0, 12 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV420P12BE] = {
        .name = "yuv420p12be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 12 },        /* Y */
            { 1, 2, 0, 0, 12 },        /* U */
            { 2, 2, 0, 0, 12 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV420P14LE] = {
        .name = "yuv420p14le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 14 },        /* Y */
            { 1, 2, 0, 0, 14 },        /* U */
            { 2, 2, 0, 0, 14 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV420P14BE] = {
        .name = "yuv420p14be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 14 },        /* Y */
            { 1, 2, 0, 0, 14 },        /* U */
            { 2, 2, 0, 0, 14 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV420P16LE] = {
        .name = "yuv420p16le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 16 },        /* Y */
            { 1, 2, 0, 0, 16 },        /* U */
            { 2, 2, 0, 0, 16 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV420P16BE] = {
        .name = "yuv420p16be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 16 },        /* Y */
            { 1, 2, 0, 0, 16 },        /* U */
            { 2, 2, 0, 0, 16 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV422P9LE] = {
        .name = "yuv422p9le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 9 },        /* Y */
            { 1, 2, 0, 0, 9 },        /* U */
            { 2, 2, 0, 0, 9 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV422P9BE] = {
        .name = "yuv422p9be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 9 },        /* Y */
            { 1, 2, 0, 0, 9 },        /* U */
            { 2, 2, 0, 0, 9 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV422P10LE] = {
        .name = "yuv422p10le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 10 },        /* Y */
            { 1, 2, 0, 0, 10 },        /* U */
            { 2, 2, 0, 0, 10 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV422P10BE] = {
        .name = "yuv422p10be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 10 },        /* Y */
            { 1, 2, 0, 0, 10 },        /* U */
            { 2, 2, 0, 0, 10 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV422P12LE] = {
        .name = "yuv422p12le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 12 },        /* Y */
            { 1, 2, 0, 0, 12 },        /* U */
            { 2, 2, 0, 0, 12 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV422P12BE] = {
        .name = "yuv422p12be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 12 },        /* Y */
            { 1, 2, 0, 0, 12 },        /* U */
            { 2, 2, 0, 0, 12 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV422P14LE] = {
        .name = "yuv422p14le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 14 },        /* Y */
            { 1, 2, 0, 0, 14 },        /* U */
            { 2, 2, 0, 0, 14 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV422P14BE] = {
        .name = "yuv422p14be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 14 },        /* Y */
            { 1, 2, 0, 0, 14 },        /* U */
            { 2, 2, 0, 0, 14 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV422P16LE] = {
        .name = "yuv422p16le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 16 },        /* Y */
            { 1, 2, 0, 0, 16 },        /* U */
            { 2, 2, 0, 0, 16 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV422P16BE] = {
        .name = "yuv422p16be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 16 },        /* Y */
            { 1, 2, 0, 0, 16 },        /* U */
            { 2, 2, 0, 0, 16 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV444P16LE] = {
        .name = "yuv444p16le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 16 },        /* Y */
            { 1, 2, 0, 0, 16 },        /* U */
            { 2, 2, 0, 0, 16 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV444P16BE] = {
        .name = "yuv444p16be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 16 },        /* Y */
            { 1, 2, 0, 0, 16 },        /* U */
            { 2, 2, 0, 0, 16 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV444P10LE] = {
        .name = "yuv444p10le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 10 },        /* Y */
            { 1, 2, 0, 0, 10 },        /* U */
            { 2, 2, 0, 0, 10 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV444P10BE] = {
        .name = "yuv444p10be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 10 },        /* Y */
            { 1, 2, 0, 0, 10 },        /* U */
            { 2, 2, 0, 0, 10 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV444P10MSBLE] = {
        .name = "yuv444p10msble",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 6, 10 },        /* Y */
            { 1, 2, 0, 6, 10 },        /* U */
            { 2, 2, 0, 6, 10 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV444P10MSBBE] = {
        .name = "yuv444p10msbbe",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 6, 10 },        /* Y */
            { 1, 2, 0, 6, 10 },        /* U */
            { 2, 2, 0, 6, 10 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV444P9LE] = {
        .name = "yuv444p9le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 9 },        /* Y */
            { 1, 2, 0, 0, 9 },        /* U */
            { 2, 2, 0, 0, 9 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV444P9BE] = {
        .name = "yuv444p9be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 9 },        /* Y */
            { 1, 2, 0, 0, 9 },        /* U */
            { 2, 2, 0, 0, 9 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV444P12LE] = {
        .name = "yuv444p12le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 12 },        /* Y */
            { 1, 2, 0, 0, 12 },        /* U */
            { 2, 2, 0, 0, 12 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV444P12BE] = {
        .name = "yuv444p12be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 12 },        /* Y */
            { 1, 2, 0, 0, 12 },        /* U */
            { 2, 2, 0, 0, 12 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV444P12MSBLE] = {
        .name = "yuv444p12msble",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 4, 12 },        /* Y */
            { 1, 2, 0, 4, 12 },        /* U */
            { 2, 2, 0, 4, 12 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV444P12MSBBE] = {
        .name = "yuv444p12msbbe",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 4, 12 },        /* Y */
            { 1, 2, 0, 4, 12 },        /* U */
            { 2, 2, 0, 4, 12 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV444P14LE] = {
        .name = "yuv444p14le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 14 },        /* Y */
            { 1, 2, 0, 0, 14 },        /* U */
            { 2, 2, 0, 0, 14 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_YUV444P14BE] = {
        .name = "yuv444p14be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 14 },        /* Y */
            { 1, 2, 0, 0, 14 },        /* U */
            { 2, 2, 0, 0, 14 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_D3D11VA_VLD] = {
        .name = "d3d11va_vld",
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .flags = AV_PIX_FMT_FLAG_HWACCEL,
    },
    [AV_PIX_FMT_DXVA2_VLD] = {
        .name = "dxva2_vld",
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .flags = AV_PIX_FMT_FLAG_HWACCEL,
    },
    [AV_PIX_FMT_YA8] = {
        .name = "ya8",
        .nb_components = 2,
        .comp = {
            { 0, 2, 0, 0, 8 },        /* Y */
            { 0, 2, 1, 0, 8 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_ALPHA,
        .alias = "gray8a",
    },
    [AV_PIX_FMT_YA16LE] = {
        .name = "ya16le",
        .nb_components = 2,
        .comp = {
            { 0, 4, 0, 0, 16 },        /* Y */
            { 0, 4, 2, 0, 16 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YA16BE] = {
        .name = "ya16be",
        .nb_components = 2,
        .comp = {
            { 0, 4, 0, 0, 16 },        /* Y */
            { 0, 4, 2, 0, 16 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_VIDEOTOOLBOX] = {
        .name = "videotoolbox_vld",
        .flags = AV_PIX_FMT_FLAG_HWACCEL,
    },
    [AV_PIX_FMT_GBRP] = {
        .name = "gbrp",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 1, 0, 0, 8 },        /* R */
            { 0, 1, 0, 0, 8 },        /* G */
            { 1, 1, 0, 0, 8 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_GBRP9LE] = {
        .name = "gbrp9le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 9 },        /* R */
            { 0, 2, 0, 0, 9 },        /* G */
            { 1, 2, 0, 0, 9 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_GBRP9BE] = {
        .name = "gbrp9be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 9 },        /* R */
            { 0, 2, 0, 0, 9 },        /* G */
            { 1, 2, 0, 0, 9 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_GBRP10LE] = {
        .name = "gbrp10le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 10 },        /* R */
            { 0, 2, 0, 0, 10 },        /* G */
            { 1, 2, 0, 0, 10 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_GBRP10BE] = {
        .name = "gbrp10be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 10 },        /* R */
            { 0, 2, 0, 0, 10 },        /* G */
            { 1, 2, 0, 0, 10 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_GBRP10MSBLE] = {
        .name = "gbrp10msble",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 6, 10 },        /* R */
            { 0, 2, 0, 6, 10 },        /* G */
            { 1, 2, 0, 6, 10 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_GBRP10MSBBE] = {
        .name = "gbrp10msbbe",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 6, 10 },        /* R */
            { 0, 2, 0, 6, 10 },        /* G */
            { 1, 2, 0, 6, 10 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_GBRP12LE] = {
        .name = "gbrp12le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 12 },        /* R */
            { 0, 2, 0, 0, 12 },        /* G */
            { 1, 2, 0, 0, 12 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_GBRP12BE] = {
        .name = "gbrp12be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 12 },        /* R */
            { 0, 2, 0, 0, 12 },        /* G */
            { 1, 2, 0, 0, 12 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_GBRP12MSBLE] = {
        .name = "gbrp12msble",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 4, 12 },        /* R */
            { 0, 2, 0, 4, 12 },        /* G */
            { 1, 2, 0, 4, 12 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_GBRP12MSBBE] = {
        .name = "gbrp12msbbe",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 4, 12 },        /* R */
            { 0, 2, 0, 4, 12 },        /* G */
            { 1, 2, 0, 4, 12 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_GBRP14LE] = {
        .name = "gbrp14le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 14 },        /* R */
            { 0, 2, 0, 0, 14 },        /* G */
            { 1, 2, 0, 0, 14 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_GBRP14BE] = {
        .name = "gbrp14be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 14 },        /* R */
            { 0, 2, 0, 0, 14 },        /* G */
            { 1, 2, 0, 0, 14 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_GBRP16LE] = {
        .name = "gbrp16le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 16 },       /* R */
            { 0, 2, 0, 0, 16 },       /* G */
            { 1, 2, 0, 0, 16 },       /* B */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_GBRP16BE] = {
        .name = "gbrp16be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 16 },       /* R */
            { 0, 2, 0, 0, 16 },       /* G */
            { 1, 2, 0, 0, 16 },       /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_GBRAP] = {
        .name = "gbrap",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 1, 0, 0, 8 },        /* R */
            { 0, 1, 0, 0, 8 },        /* G */
            { 1, 1, 0, 0, 8 },        /* B */
            { 3, 1, 0, 0, 8 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB |
                 AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_GBRAP16LE] = {
        .name = "gbrap16le",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 16 },       /* R */
            { 0, 2, 0, 0, 16 },       /* G */
            { 1, 2, 0, 0, 16 },       /* B */
            { 3, 2, 0, 0, 16 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB |
                 AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_GBRAP16BE] = {
        .name = "gbrap16be",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 16 },       /* R */
            { 0, 2, 0, 0, 16 },       /* G */
            { 1, 2, 0, 0, 16 },       /* B */
            { 3, 2, 0, 0, 16 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR |
                 AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_GBRAP32LE] = {
        .name = "gbrap32le",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 4, 0, 0, 32 },       /* R */
            { 0, 4, 0, 0, 32 },       /* G */
            { 1, 4, 0, 0, 32 },       /* B */
            { 3, 4, 0, 0, 32 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB |
                 AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_GBRAP32BE] = {
        .name = "gbrap32be",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 4, 0, 0, 32 },       /* R */
            { 0, 4, 0, 0, 32 },       /* G */
            { 1, 4, 0, 0, 32 },       /* B */
            { 3, 4, 0, 0, 32 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR |
                 AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_VDPAU] = {
        .name = "vdpau",
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .flags = AV_PIX_FMT_FLAG_HWACCEL,
    },
    [AV_PIX_FMT_XYZ12LE] = {
        .name = "xyz12le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 6, 0, 4, 12 },       /* X */
            { 0, 6, 2, 4, 12 },       /* Y */
            { 0, 6, 4, 4, 12 },       /* Z */
        },
        .flags = AV_PIX_FMT_FLAG_XYZ,
    },
    [AV_PIX_FMT_XYZ12BE] = {
        .name = "xyz12be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 6, 0, 4, 12 },       /* X */
            { 0, 6, 2, 4, 12 },       /* Y */
            { 0, 6, 4, 4, 12 },       /* Z */
       },
        .flags = AV_PIX_FMT_FLAG_XYZ | AV_PIX_FMT_FLAG_BE,
    },
    [AV_PIX_FMT_XYZP12LE] = {
        .name = "xyzp12le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 4, 12 },       /* X */
            { 1, 2, 0, 4, 12 },       /* Y */
            { 2, 2, 0, 4, 12 },       /* Z */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_XYZ,
    },
    [AV_PIX_FMT_XYZP12BE] = {
        .name = "xyzp12be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 4, 12 },       /* X */
            { 1, 2, 0, 4, 12 },       /* Y */
            { 2, 2, 0, 4, 12 },       /* Z */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_XYZ | AV_PIX_FMT_FLAG_BE,
    },

#define BAYER8_DESC_COMMON \
        .nb_components= 3, \
        .log2_chroma_w= 0, \
        .log2_chroma_h= 0, \
        .comp = {          \
            { 0, 1, 0, 0, 2 }, \
            { 0, 1, 0, 0, 4 }, \
            { 0, 1, 0, 0, 2 }, \
        },                 \

#define BAYER16_DESC_COMMON \
        .nb_components= 3, \
        .log2_chroma_w= 0, \
        .log2_chroma_h= 0, \
        .comp = {          \
            { 0, 2, 0, 0, 4 }, \
            { 0, 2, 0, 0, 8 }, \
            { 0, 2, 0, 0, 4 }, \
        },                 \

    [AV_PIX_FMT_BAYER_BGGR8] = {
        .name = "bayer_bggr8",
        BAYER8_DESC_COMMON
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_BAYER,
    },
    [AV_PIX_FMT_BAYER_BGGR16LE] = {
        .name = "bayer_bggr16le",
        BAYER16_DESC_COMMON
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_BAYER,
    },
    [AV_PIX_FMT_BAYER_BGGR16BE] = {
        .name = "bayer_bggr16be",
        BAYER16_DESC_COMMON
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_BAYER,
    },
    [AV_PIX_FMT_BAYER_RGGB8] = {
        .name = "bayer_rggb8",
        BAYER8_DESC_COMMON
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_BAYER,
    },
    [AV_PIX_FMT_BAYER_RGGB16LE] = {
        .name = "bayer_rggb16le",
        BAYER16_DESC_COMMON
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_BAYER,
    },
    [AV_PIX_FMT_BAYER_RGGB16BE] = {
        .name = "bayer_rggb16be",
        BAYER16_DESC_COMMON
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_BAYER,
    },
    [AV_PIX_FMT_BAYER_GBRG8] = {
        .name = "bayer_gbrg8",
        BAYER8_DESC_COMMON
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_BAYER,
    },
    [AV_PIX_FMT_BAYER_GBRG16LE] = {
        .name = "bayer_gbrg16le",
        BAYER16_DESC_COMMON
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_BAYER,
    },
    [AV_PIX_FMT_BAYER_GBRG16BE] = {
        .name = "bayer_gbrg16be",
        BAYER16_DESC_COMMON
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_BAYER,
    },
    [AV_PIX_FMT_BAYER_GRBG8] = {
        .name = "bayer_grbg8",
        BAYER8_DESC_COMMON
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_BAYER,
    },
    [AV_PIX_FMT_BAYER_GRBG16LE] = {
        .name = "bayer_grbg16le",
        BAYER16_DESC_COMMON
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_BAYER,
    },
    [AV_PIX_FMT_BAYER_GRBG16BE] = {
        .name = "bayer_grbg16be",
        BAYER16_DESC_COMMON
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_BAYER,
    },
    [AV_PIX_FMT_NV16] = {
        .name = "nv16",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
            { 1, 2, 0, 0, 8 },        /* U */
            { 1, 2, 1, 0, 8 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_NV20LE] = {
        .name = "nv20le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 10 },        /* Y */
            { 1, 4, 0, 0, 10 },        /* U */
            { 1, 4, 2, 0, 10 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_NV20BE] = {
        .name = "nv20be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 10 },        /* Y */
            { 1, 4, 0, 0, 10 },        /* U */
            { 1, 4, 2, 0, 10 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_BE,
    },
    [AV_PIX_FMT_QSV] = {
        .name = "qsv",
        .flags = AV_PIX_FMT_FLAG_HWACCEL,
    },
    [AV_PIX_FMT_MEDIACODEC] = {
        .name = "mediacodec",
        .flags = AV_PIX_FMT_FLAG_HWACCEL,
    },
    [AV_PIX_FMT_MMAL] = {
        .name = "mmal",
        .flags = AV_PIX_FMT_FLAG_HWACCEL,
    },
    [AV_PIX_FMT_CUDA] = {
        .name = "cuda",
        .flags = AV_PIX_FMT_FLAG_HWACCEL,
    },
    [AV_PIX_FMT_CUARRAY] = {
        .name = "cuarray",
        .flags = AV_PIX_FMT_FLAG_HWACCEL,
    },
    [AV_PIX_FMT_AMF_SURFACE] = {
        .name = "amf",
        .flags = AV_PIX_FMT_FLAG_HWACCEL,
    },
    [AV_PIX_FMT_VYU444] = {
        .name = "vyu444",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 3, 1, 0, 8 },        /* Y */
            { 0, 3, 2, 0, 8 },        /* U */
            { 0, 3, 0, 0, 8 },        /* V */
        },
    },
    [AV_PIX_FMT_UYVA] = {
        .name = "uyva",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 1, 0, 8 },        /* Y */
            { 0, 4, 0, 0, 8 },        /* U */
            { 0, 4, 2, 0, 8 },        /* V */
            { 0, 4, 3, 0, 8 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_AYUV] = {
        .name = "ayuv",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 1, 0, 8 },        /* Y */
            { 0, 4, 2, 0, 8 },        /* U */
            { 0, 4, 3, 0, 8 },        /* V */
            { 0, 4, 0, 0, 8 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_AYUV64LE] = {
        .name = "ayuv64le",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 8, 2, 0, 16 },        /* Y */
            { 0, 8, 4, 0, 16 },        /* U */
            { 0, 8, 6, 0, 16 },        /* V */
            { 0, 8, 0, 0, 16 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_AYUV64BE] = {
        .name = "ayuv64be",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 8, 2, 0, 16 },        /* Y */
            { 0, 8, 4, 0, 16 },        /* U */
            { 0, 8, 6, 0, 16 },        /* V */
            { 0, 8, 0, 0, 16 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_P010LE] = {
        .name = "p010le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 6, 10 },        /* Y */
            { 1, 4, 0, 6, 10 },        /* U */
            { 1, 4, 2, 6, 10 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_P010BE] = {
        .name = "p010be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 6, 10 },        /* Y */
            { 1, 4, 0, 6, 10 },        /* U */
            { 1, 4, 2, 6, 10 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_BE,
    },
    [AV_PIX_FMT_P012LE] = {
        .name = "p012le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 4, 12 },        /* Y */
            { 1, 4, 0, 4, 12 },        /* U */
            { 1, 4, 2, 4, 12 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_P012BE] = {
        .name = "p012be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 4, 12 },        /* Y */
            { 1, 4, 0, 4, 12 },        /* U */
            { 1, 4, 2, 4, 12 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_BE,
    },
    [AV_PIX_FMT_P016LE] = {
        .name = "p016le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 16 },       /* Y */
            { 1, 4, 0, 0, 16 },       /* U */
            { 1, 4, 2, 0, 16 },       /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_P016BE] = {
        .name = "p016be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 1,
        .comp = {
            { 0, 2, 0, 0, 16 },       /* Y */
            { 1, 4, 0, 0, 16 },       /* U */
            { 1, 4, 2, 0, 16 },       /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_BE,
    },
    [AV_PIX_FMT_GBRAP14LE] = {
        .name = "gbrap14le",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 14 },       /* R */
            { 0, 2, 0, 0, 14 },       /* G */
            { 1, 2, 0, 0, 14 },       /* B */
            { 3, 2, 0, 0, 14 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB |
                 AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_GBRAP14BE] = {
        .name = "gbrap14be",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 14 },       /* R */
            { 0, 2, 0, 0, 14 },       /* G */
            { 1, 2, 0, 0, 14 },       /* B */
            { 3, 2, 0, 0, 14 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR |
                 AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_GBRAP12LE] = {
        .name = "gbrap12le",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 12 },       /* R */
            { 0, 2, 0, 0, 12 },       /* G */
            { 1, 2, 0, 0, 12 },       /* B */
            { 3, 2, 0, 0, 12 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB |
                 AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_GBRAP12BE] = {
        .name = "gbrap12be",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 12 },       /* R */
            { 0, 2, 0, 0, 12 },       /* G */
            { 1, 2, 0, 0, 12 },       /* B */
            { 3, 2, 0, 0, 12 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR |
                 AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_GBRAP10LE] = {
        .name = "gbrap10le",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 10 },       /* R */
            { 0, 2, 0, 0, 10 },       /* G */
            { 1, 2, 0, 0, 10 },       /* B */
            { 3, 2, 0, 0, 10 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_RGB |
                 AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_GBRAP10BE] = {
        .name = "gbrap10be",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 10 },       /* R */
            { 0, 2, 0, 0, 10 },       /* G */
            { 1, 2, 0, 0, 10 },       /* B */
            { 3, 2, 0, 0, 10 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR |
                 AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_D3D11] = {
        .name = "d3d11",
        .flags = AV_PIX_FMT_FLAG_HWACCEL,
    },
    [AV_PIX_FMT_D3D12] = {
        .name = "d3d12",
        .flags = AV_PIX_FMT_FLAG_HWACCEL,
    },
    [AV_PIX_FMT_GBRPF32BE] = {
        .name = "gbrpf32be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 4, 0, 0, 32 },        /* R */
            { 0, 4, 0, 0, 32 },        /* G */
            { 1, 4, 0, 0, 32 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR |
                 AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_FLOAT,
    },
    [AV_PIX_FMT_GBRPF32LE] = {
        .name = "gbrpf32le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 4, 0, 0, 32 },        /* R */
            { 0, 4, 0, 0, 32 },        /* G */
            { 1, 4, 0, 0, 32 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_FLOAT | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_GBRAPF32BE] = {
        .name = "gbrapf32be",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 4, 0, 0, 32 },        /* R */
            { 0, 4, 0, 0, 32 },        /* G */
            { 1, 4, 0, 0, 32 },        /* B */
            { 3, 4, 0, 0, 32 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR |
                 AV_PIX_FMT_FLAG_ALPHA | AV_PIX_FMT_FLAG_RGB |
                 AV_PIX_FMT_FLAG_FLOAT,
    },
    [AV_PIX_FMT_GBRAPF32LE] = {
        .name = "gbrapf32le",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 4, 0, 0, 32 },        /* R */
            { 0, 4, 0, 0, 32 },        /* G */
            { 1, 4, 0, 0, 32 },        /* B */
            { 3, 4, 0, 0, 32 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA |
                 AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_FLOAT,
    },
    [AV_PIX_FMT_GBRPF16BE] = {
        .name = "gbrpf16be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 16 },        /* R */
            { 0, 2, 0, 0, 16 },        /* G */
            { 1, 2, 0, 0, 16 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR |
                 AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_FLOAT,
    },
    [AV_PIX_FMT_GBRPF16LE] = {
        .name = "gbrpf16le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 16 },        /* R */
            { 0, 2, 0, 0, 16 },        /* G */
            { 1, 2, 0, 0, 16 },        /* B */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_FLOAT | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_GBRAPF16BE] = {
        .name = "gbrapf16be",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 16 },        /* R */
            { 0, 2, 0, 0, 16 },        /* G */
            { 1, 2, 0, 0, 16 },        /* B */
            { 3, 2, 0, 0, 16 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR |
                 AV_PIX_FMT_FLAG_ALPHA | AV_PIX_FMT_FLAG_RGB |
                 AV_PIX_FMT_FLAG_FLOAT,
    },
    [AV_PIX_FMT_GBRAPF16LE] = {
        .name = "gbrapf16le",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 2, 2, 0, 0, 16 },        /* R */
            { 0, 2, 0, 0, 16 },        /* G */
            { 1, 2, 0, 0, 16 },        /* B */
            { 3, 2, 0, 0, 16 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA |
                 AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_FLOAT,
    },
    [AV_PIX_FMT_DRM_ମୌଳିକ] = {
        .name = "drm_prime",
        .flags = AV_PIX_FMT_FLAG_HWACCEL,
    },
    [AV_PIX_FMT_OPENCL] = {
        .name  = "opencl",
        .flags = AV_PIX_FMT_FLAG_HWACCEL,
    },
    [AV_PIX_FMT_GRAYF32BE] = {
        .name = "grayf32be",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 0, 0, 32 },       /* Y */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_FLOAT,
        .alias = "yf32be",
    },
    [AV_PIX_FMT_GRAYF32LE] = {
        .name = "grayf32le",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 0, 0, 32 },       /* Y */
        },
        .flags = AV_PIX_FMT_FLAG_FLOAT,
        .alias = "yf32le",
    },
    [AV_PIX_FMT_GRAYF16BE] = {
        .name = "grayf16be",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 16 },       /* Y */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_FLOAT,
    },
    [AV_PIX_FMT_GRAYF16LE] = {
        .name = "grayf16le",
        .nb_components = 1,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 16 },       /* Y */
        },
        .flags = AV_PIX_FMT_FLAG_FLOAT,
    },
    [AV_PIX_FMT_YAF32BE] = {
        .name = "yaf32be",
        .nb_components = 2,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 8, 0, 0, 32 },       /* Y */
            { 0, 8, 4, 0, 32 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_FLOAT | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YAF32LE] = {
        .name = "yaf32le",
        .nb_components = 2,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 8, 0, 0, 32 },       /* Y */
            { 0, 8, 4, 0, 32 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_FLOAT | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YAF16BE] = {
        .name = "yaf16be",
        .nb_components = 2,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 0, 0, 16 },       /* Y */
            { 0, 4, 2, 0, 16 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_FLOAT | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YAF16LE] = {
        .name = "yaf16le",
        .nb_components = 2,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 0, 0, 16 },       /* Y */
            { 0, 4, 2, 0, 16 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_FLOAT | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA422P12BE] = {
        .name = "yuva422p12be",
        .nb_components = 4,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 12 },        /* Y */
            { 1, 2, 0, 0, 12 },        /* U */
            { 2, 2, 0, 0, 12 },        /* V */
            { 3, 2, 0, 0, 12 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA422P12LE] = {
        .name = "yuva422p12le",
        .nb_components = 4,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 12 },        /* Y */
            { 1, 2, 0, 0, 12 },        /* U */
            { 2, 2, 0, 0, 12 },        /* V */
            { 3, 2, 0, 0, 12 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA444P12BE] = {
        .name = "yuva444p12be",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 12 },        /* Y */
            { 1, 2, 0, 0, 12 },        /* U */
            { 2, 2, 0, 0, 12 },        /* V */
            { 3, 2, 0, 0, 12 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_YUVA444P12LE] = {
        .name = "yuva444p12le",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 12 },        /* Y */
            { 1, 2, 0, 0, 12 },        /* U */
            { 2, 2, 0, 0, 12 },        /* V */
            { 3, 2, 0, 0, 12 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_NV24] = {
        .name = "nv24",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
            { 1, 2, 0, 0, 8 },        /* U */
            { 1, 2, 1, 0, 8 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_NV42] = {
        .name = "nv42",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 1, 0, 0, 8 },        /* Y */
            { 1, 2, 1, 0, 8 },        /* U */
            { 1, 2, 0, 0, 8 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_VULKAN] = {
        .name = "vulkan",
        .flags = AV_PIX_FMT_FLAG_HWACCEL,
    },
    [AV_PIX_FMT_P210BE] = {
        .name = "p210be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 6, 10 },        /* Y */
            { 1, 4, 0, 6, 10 },        /* U */
            { 1, 4, 2, 6, 10 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_BE,
    },
    [AV_PIX_FMT_P210LE] = {
        .name = "p210le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 6, 10 },        /* Y */
            { 1, 4, 0, 6, 10 },        /* U */
            { 1, 4, 2, 6, 10 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_P410BE] = {
        .name = "p410be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 6, 10 },        /* Y */
            { 1, 4, 0, 6, 10 },        /* U */
            { 1, 4, 2, 6, 10 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_BE,
    },
    [AV_PIX_FMT_P410LE] = {
        .name = "p410le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 6, 10 },        /* Y */
            { 1, 4, 0, 6, 10 },        /* U */
            { 1, 4, 2, 6, 10 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_P216BE] = {
        .name = "p216be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 16 },        /* Y */
            { 1, 4, 0, 0, 16 },        /* U */
            { 1, 4, 2, 0, 16 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_BE,
    },
    [AV_PIX_FMT_P216LE] = {
        .name = "p216le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 16 },        /* Y */
            { 1, 4, 0, 0, 16 },        /* U */
            { 1, 4, 2, 0, 16 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_P416BE] = {
        .name = "p416be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 16 },        /* Y */
            { 1, 4, 0, 0, 16 },        /* U */
            { 1, 4, 2, 0, 16 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_BE,
    },
    [AV_PIX_FMT_P416LE] = {
        .name = "p416le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 0, 16 },        /* Y */
            { 1, 4, 0, 0, 16 },        /* U */
            { 1, 4, 2, 0, 16 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_VUYA] = {
        .name = "vuya",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 2, 0, 8 },        /* Y */
            { 0, 4, 1, 0, 8 },        /* U */
            { 0, 4, 0, 0, 8 },        /* V */
            { 0, 4, 3, 0, 8 },        /* A */
        },
        .flags = AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_VUYX] = {
        .name = "vuyx",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 2, 0, 8 },        /* Y */
            { 0, 4, 1, 0, 8 },        /* U */
            { 0, 4, 0, 0, 8 },        /* V */
            { 0, 4, 3, 0, 8 },        /* X */
        },
    },
    [AV_PIX_FMT_RGBF16BE] = {
        .name = "rgbf16be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 6, 0, 0, 16 },       /* R */
            { 0, 6, 2, 0, 16 },       /* G */
            { 0, 6, 4, 0, 16 },       /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_RGB |
                 AV_PIX_FMT_FLAG_FLOAT,
    },
    [AV_PIX_FMT_RGBF16LE] = {
        .name = "rgbf16le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 6, 0, 0, 16 },       /* R */
            { 0, 6, 2, 0, 16 },       /* G */
            { 0, 6, 4, 0, 16 },       /* B */
        },
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_FLOAT
    },
    [AV_PIX_FMT_RGBAF16BE] = {
        .name = "rgbaf16be",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 8, 0, 0, 16 },       /* R */
            { 0, 8, 2, 0, 16 },       /* G */
            { 0, 8, 4, 0, 16 },       /* B */
            { 0, 8, 6, 0, 16 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_RGB |
                 AV_PIX_FMT_FLAG_ALPHA | AV_PIX_FMT_FLAG_FLOAT,
    },
    [AV_PIX_FMT_RGBAF16LE] = {
        .name = "rgbaf16le",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 8, 0, 0, 16 },       /* R */
            { 0, 8, 2, 0, 16 },       /* G */
            { 0, 8, 4, 0, 16 },       /* B */
            { 0, 8, 6, 0, 16 },       /* A */
        },
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_ALPHA |
                 AV_PIX_FMT_FLAG_FLOAT,
    },
    [AV_PIX_FMT_Y212LE] = {
        .name = "y212le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 0, 4, 12 },        /* Y */
            { 0, 8, 2, 4, 12 },        /* U */
            { 0, 8, 6, 4, 12 },        /* V */
        },
    },
    [AV_PIX_FMT_Y212BE] = {
        .name = "y212be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 0, 4, 12 },        /* Y */
            { 0, 8, 2, 4, 12 },        /* U */
            { 0, 8, 6, 4, 12 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE,
    },
    [AV_PIX_FMT_XV30LE] = {
        .name = "xv30le",
        .nb_components= 3,
        .log2_chroma_w= 0,
        .log2_chroma_h= 0,
        .comp = {
            { 0, 4, 1, 2, 10 },       /* Y */
            { 0, 4, 0, 0, 10 },       /* U */
            { 0, 4, 2, 4, 10 },       /* V */
            { 0, 4, 3, 6,  2 },       /* X */
        },
    },
    [AV_PIX_FMT_XV30BE] = {
        .name = "xv30be",
        .nb_components= 3,
        .log2_chroma_w= 0,
        .log2_chroma_h= 0,
        .comp = {
            { 0, 32, 10, 0, 10 },       /* Y */
            { 0, 32,  0, 0, 10 },       /* U */
            { 0, 32, 20, 0, 10 },       /* V */
            { 0, 32, 30, 0,  2 },       /* X */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_BITSTREAM,
    },
    [AV_PIX_FMT_XV36LE] = {
        .name = "xv36le",
        .nb_components= 3,
        .log2_chroma_w= 0,
        .log2_chroma_h= 0,
        .comp = {
            { 0, 8, 2, 4, 12 },       /* Y */
            { 0, 8, 0, 4, 12 },       /* U */
            { 0, 8, 4, 4, 12 },       /* V */
            { 0, 8, 6, 4, 12 },       /* X */
        },
    },
    [AV_PIX_FMT_XV36BE] = {
        .name = "xv36be",
        .nb_components= 3,
        .log2_chroma_w= 0,
        .log2_chroma_h= 0,
        .comp = {
            { 0, 8, 2, 4, 12 },       /* Y */
            { 0, 8, 0, 4, 12 },       /* U */
            { 0, 8, 4, 4, 12 },       /* V */
            { 0, 8, 6, 4, 12 },       /* X */
        },
        .flags = AV_PIX_FMT_FLAG_BE,
    },
    [AV_PIX_FMT_XV48LE] = {
        .name = "xv48le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 8, 2, 0, 16 },        /* Y */
            { 0, 8, 0, 0, 16 },        /* U */
            { 0, 8, 4, 0, 16 },        /* V */
            { 0, 8, 6, 0, 16 },        /* X */
        },
    },
    [AV_PIX_FMT_XV48BE] = {
        .name = "xv48be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 8, 2, 0, 16 },        /* Y */
            { 0, 8, 0, 0, 16 },        /* U */
            { 0, 8, 4, 0, 16 },        /* V */
            { 0, 8, 6, 0, 16 },        /* X */
        },
        .flags = AV_PIX_FMT_FLAG_BE,
    },
    [AV_PIX_FMT_V30XLE] = {
        .name = "v30xle",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 1, 4, 10 },       /* Y */
            { 0, 4, 0, 2, 10 },       /* U */
            { 0, 4, 2, 6, 10 },       /* V */
            { 0, 4, 0, 0,  2 },       /* X */
        },
    },
    [AV_PIX_FMT_V30XBE] = {
        .name = "v30xbe",
        .nb_components= 3,
        .log2_chroma_w= 0,
        .log2_chroma_h= 0,
        .comp = {
            { 0, 32, 12, 0, 10 },     /* Y */
            { 0, 32,  2, 0, 10 },     /* U */
            { 0, 32, 22, 0, 10 },     /* V */
            { 0, 32,  0, 0,  2 },     /* X */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_BITSTREAM,
    },
    [AV_PIX_FMT_RGBF32BE] = {
        .name = "rgbf32be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 12, 0, 0, 32 },       /* R */
            { 0, 12, 4, 0, 32 },       /* G */
            { 0, 12, 8, 0, 32 },       /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_RGB |
                 AV_PIX_FMT_FLAG_FLOAT,
    },
    [AV_PIX_FMT_RGBF32LE] = {
        .name = "rgbf32le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 12, 0, 0, 32 },       /* R */
            { 0, 12, 4, 0, 32 },       /* G */
            { 0, 12, 8, 0, 32 },       /* B */
        },
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_FLOAT,
    },
    [AV_PIX_FMT_RGB96BE] = {
        .name = "rgb96be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 12, 0, 0, 32 },       /* R */
            { 0, 12, 4, 0, 32 },       /* G */
            { 0, 12, 8, 0, 32 },       /* B */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_RGB96LE] = {
        .name = "rgb96le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 12, 0, 0, 32 },       /* R */
            { 0, 12, 4, 0, 32 },       /* G */
            { 0, 12, 8, 0, 32 },       /* B */
        },
        .flags = AV_PIX_FMT_FLAG_RGB,
    },
    [AV_PIX_FMT_RGBAF32BE] = {
        .name = "rgbaf32be",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 16,  0, 0, 32 },      /* R */
            { 0, 16,  4, 0, 32 },      /* G */
            { 0, 16,  8, 0, 32 },      /* B */
            { 0, 16, 12, 0, 32 },      /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_RGB |
                 AV_PIX_FMT_FLAG_FLOAT | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_RGBAF32LE] = {
        .name = "rgbaf32le",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 16,  0, 0, 32 },      /* R */
            { 0, 16,  4, 0, 32 },      /* G */
            { 0, 16,  8, 0, 32 },      /* B */
            { 0, 16, 12, 0, 32 },      /* A */
        },
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_FLOAT |
                 AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_RGBA128BE] = {
        .name = "rgba128be",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 16,  0, 0, 32 },      /* R */
            { 0, 16,  4, 0, 32 },      /* G */
            { 0, 16,  8, 0, 32 },      /* B */
            { 0, 16, 12, 0, 32 },      /* A */
        },
        .flags = AV_PIX_FMT_FLAG_BE | AV_PIX_FMT_FLAG_RGB |
                 AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_RGBA128LE] = {
        .name = "rgba128le",
        .nb_components = 4,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 16,  0, 0, 32 },      /* R */
            { 0, 16,  4, 0, 32 },      /* G */
            { 0, 16,  8, 0, 32 },      /* B */
            { 0, 16, 12, 0, 32 },      /* A */
        },
        .flags = AV_PIX_FMT_FLAG_RGB | AV_PIX_FMT_FLAG_ALPHA,
    },
    [AV_PIX_FMT_P212BE] = {
        .name = "p212be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 4, 12 },        /* Y */
            { 1, 4, 0, 4, 12 },        /* U */
            { 1, 4, 2, 4, 12 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_BE,
    },
    [AV_PIX_FMT_P212LE] = {
        .name = "p212le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 4, 12 },        /* Y */
            { 1, 4, 0, 4, 12 },        /* U */
            { 1, 4, 2, 4, 12 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_P412BE] = {
        .name = "p412be",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 4, 12 },        /* Y */
            { 1, 4, 0, 4, 12 },        /* U */
            { 1, 4, 2, 4, 12 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR | AV_PIX_FMT_FLAG_BE,
    },
    [AV_PIX_FMT_P412LE] = {
        .name = "p412le",
        .nb_components = 3,
        .log2_chroma_w = 0,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 2, 0, 4, 12 },        /* Y */
            { 1, 4, 0, 4, 12 },        /* U */
            { 1, 4, 2, 4, 12 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_PLANAR,
    },
    [AV_PIX_FMT_Y216LE] = {
        .name = "y216le",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 0, 0, 16 },        /* Y */
            { 0, 8, 2, 0, 16 },        /* U */
            { 0, 8, 6, 0, 16 },        /* V */
        },
    },
    [AV_PIX_FMT_Y216BE] = {
        .name = "y216be",
        .nb_components = 3,
        .log2_chroma_w = 1,
        .log2_chroma_h = 0,
        .comp = {
            { 0, 4, 0, 0, 16 },        /* Y */
            { 0, 8, 2, 0, 16 },        /* U */
            { 0, 8, 6, 0, 16 },        /* V */
        },
        .flags = AV_PIX_FMT_FLAG_BE,
    },
    [AV_PIX_FMT_OHCODEC] = {
        .name = "ohcodec",
        .flags = AV_PIX_FMT_FLAG_HWACCEL,
    },
};

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର * ଅଚଳ color_range_names[] = {
    [AVCOL_RANGE_UNSPECIFIED] = "unknown",
    [AVCOL_RANGE_MPEG] = "tv",
    [AVCOL_RANGE_JPEG] = "pc",
};

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର * ଅଚଳ color_primaries_names[AVCOL_PRI_NB] = {
    [AVCOL_PRI_RESERVED0] = "reserved",
    [AVCOL_PRI_BT709] = "bt709",
    [AVCOL_PRI_UNSPECIFIED] = "unknown",
    [AVCOL_PRI_RESERVED] = "reserved",
    [AVCOL_PRI_BT470M] = "bt470m",
    [AVCOL_PRI_BT470BG] = "bt470bg",
    [AVCOL_PRI_SMPTE170M] = "smpte170m",
    [AVCOL_PRI_SMPTE240M] = "smpte240m",
    [AVCOL_PRI_FILM] = "film",
    [AVCOL_PRI_BT2020] = "bt2020",
    [AVCOL_PRI_SMPTE428] = "smpte428",
    [AVCOL_PRI_SMPTE431] = "smpte431",
    [AVCOL_PRI_SMPTE432] = "smpte432",
    [AVCOL_PRI_EBU3213] = "ebu3213",
};

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର * ଅଚଳ color_primaries_names_ext[AVCOL_PRI_EXT_NB -
                                                    AVCOL_PRI_EXT_BASE] = {
    [AVCOL_PRI_V_GAMUT - AVCOL_PRI_EXT_BASE] = "vgamut",
};

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର * ଅଚଳ color_transfer_names[] = {
    [AVCOL_TRC_RESERVED0] = "reserved",
    [AVCOL_TRC_BT709] = "bt709",
    [AVCOL_TRC_UNSPECIFIED] = "unknown",
    [AVCOL_TRC_RESERVED] = "reserved",
    [AVCOL_TRC_GAMMA22] = "bt470m",
    [AVCOL_TRC_GAMMA28] = "bt470bg",
    [AVCOL_TRC_SMPTE170M] = "smpte170m",
    [AVCOL_TRC_SMPTE240M] = "smpte240m",
    [AVCOL_TRC_LINEAR] = "linear",
    [AVCOL_TRC_LOG] = "log100",
    [AVCOL_TRC_LOG_SQRT] = "log316",
    [AVCOL_TRC_IEC61966_2_4] = "iec61966-2-4",
    [AVCOL_TRC_BT1361_ECG] = "bt1361e",
    [AVCOL_TRC_IEC61966_2_1] = "iec61966-2-1",
    [AVCOL_TRC_BT2020_10] = "bt2020-10",
    [AVCOL_TRC_BT2020_12] = "bt2020-12",
    [AVCOL_TRC_SMPTE2084] = "smpte2084",
    [AVCOL_TRC_SMPTE428] = "smpte428",
    [AVCOL_TRC_ARIB_STD_B67] = "arib-std-b67",
};

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର * ଅଚଳ color_transfer_names_ext[] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_BASE] = "vlog",
};

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର * ଅଚଳ color_space_names[] = {
    [AVCOL_SPC_RGB] = "gbr",
    [AVCOL_SPC_BT709] = "bt709",
    [AVCOL_SPC_UNSPECIFIED] = "unknown",
    [AVCOL_SPC_RESERVED] = "reserved",
    [AVCOL_SPC_FCC] = "fcc",
    [AVCOL_SPC_BT470BG] = "bt470bg",
    [AVCOL_SPC_SMPTE170M] = "smpte170m",
    [AVCOL_SPC_SMPTE240M] = "smpte240m",
    [AVCOL_SPC_YCGCO] = "ycgco",
    [AVCOL_SPC_BT2020_NCL] = "bt2020nc",
    [AVCOL_SPC_BT2020_CL] = "bt2020c",
    [AVCOL_SPC_SMPTE2085] = "smpte2085",
    [AVCOL_SPC_CHROMA_DERIVED_NCL] = "chroma-derived-nc",
    [AVCOL_SPC_CHROMA_DERIVED_CL] = "chroma-derived-c",
    [AVCOL_SPC_ICTCP] = "ictcp",
    [AVCOL_SPC_IPT_C2] = "ipt-c2",
    [AVCOL_SPC_YCGCO_RE] = "ycgco-re",
    [AVCOL_SPC_YCGCO_RO] = "ycgco-ro",
};

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର * ଅଚଳ chroma_location_names[] = {
    [AVCHROMA_LOC_UNSPECIFIED] = "unspecified",
    [AVCHROMA_LOC_ବାମ] = "left",
    [AVCHROMA_LOC_CENTER] = "center",
    [AVCHROMA_LOC_TOPLEFT] = "topleft",
    [AVCHROMA_LOC_ଶୀର୍ଷ] = "top",
    [AVCHROMA_LOC_BOTTOMLEFT] = "bottomleft",
    [AVCHROMA_LOC_BOTTOM] = "bottom",
};

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର * ଅଚଳ alpha_mode_names[] = {
    [AVALPHA_MODE_UNSPECIFIED] = "unspecified",
    [AVALPHA_MODE_PREMULTIPLIED] = "premultiplied",
    [AVALPHA_MODE_STRAIGHT] = "straight",
};

ସ୍ଥିର ଗଣନା AVPixelFormat get_pix_fmt_internal(ଅଚଳ ଅକ୍ଷର *name)
{
    ଗଣନା AVPixelFormat pix_fmt;

    ପାଇଁ (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++)
        ଯଦି (av_pix_fmt_descriptors[pix_fmt].name &&
            (!strcmp(av_pix_fmt_descriptors[pix_fmt].name, name) ||
             av_match_name(name, av_pix_fmt_descriptors[pix_fmt].alias)))
            ଫେରନ୍ତୁ pix_fmt;

    ଫେରନ୍ତୁ AV_PIX_FMT_NONE;
}

ଅଚଳ ଅକ୍ଷର *av_get_pix_fmt_name(ଗଣନା AVPixelFormat pix_fmt)
{
    ଫେରନ୍ତୁ (unsigned)pix_fmt < AV_PIX_FMT_NB ?
        av_pix_fmt_descriptors[pix_fmt].name : ଖାଲି;
}

#ଯଦି HAVE_BIGENDIAN
#   define X_NE(be, le) be
#ଅନ୍ୟଥା
#   define X_NE(be, le) le
#endif

ଗଣନା AVPixelFormat av_get_pix_fmt(ଅଚଳ ଅକ୍ଷର *name)
{
    ଗଣନା AVPixelFormat pix_fmt;

    ଯଦି (!strcmp(name, "rgb32"))
        name = X_NE("argb", "bgra");
    ଅନ୍ୟଥା ଯଦି (!strcmp(name, "bgr32"))
        name = X_NE("abgr", "rgba");

    pix_fmt = get_pix_fmt_internal(name);
    ଯଦି (pix_fmt == AV_PIX_FMT_NONE) {
        ଅକ୍ଷର name2[32];

        snprintf(name2, ଆକାର(name2), "%s%s", name, X_NE("be", "le"));
        pix_fmt = get_pix_fmt_internal(name2);
    }

    ଫେରନ୍ତୁ pix_fmt;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_get_bits_per_pixel(ଅଚଳ AVPixFmtDescriptor *pixdesc)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, bits = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା log2_pixels = pixdesc->log2_chroma_w + pixdesc->log2_chroma_h;

    ପାଇଁ (c = 0; c < pixdesc->nb_components; c++) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା s = c == 1 || c == 2 ? 0 : log2_pixels;
        bits += pixdesc->comp[c].depth << s;
    }

    ଫେରନ୍ତୁ bits >> log2_pixels;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_get_padded_bits_per_pixel(ଅଚଳ AVPixFmtDescriptor *pixdesc)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, bits = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା log2_pixels = pixdesc->log2_chroma_w + pixdesc->log2_chroma_h;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା steps[4] = {0};

    ପାଇଁ (c = 0; c < pixdesc->nb_components; c++) {
        ଅଚଳ AVComponentDescriptor *comp = &pixdesc->comp[c];
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା s = c == 1 || c == 2 ? 0 : log2_pixels;
        steps[comp->plane] = comp->step << s;
    }
    ପାଇଁ (c = 0; c < 4; c++)
        bits += steps[c];

    ଯଦି(!(pixdesc->flags & AV_PIX_FMT_FLAG_BITSTREAM))
        bits *= 8;

    ଫେରନ୍ତୁ bits >> log2_pixels;
}

ଅକ୍ଷର *av_get_pix_fmt_string(ଅକ୍ଷର *buf, ପୂର୍ଣ୍ଣସଂଖ୍ୟା buf_size,
                            ଗଣନା AVPixelFormat pix_fmt)
{
    /* print header */
    ଯଦି (pix_fmt < 0) {
       snprintf (buf, buf_size, "name" " nb_components" " nb_bits");
    } ଅନ୍ୟଥା {
        ଅଚଳ AVPixFmtDescriptor *pixdesc = &av_pix_fmt_descriptors[pix_fmt];
        snprintf(buf, buf_size, "%-11s %7d %10d", pixdesc->name,
                 pixdesc->nb_components, av_get_bits_per_pixel(pixdesc));
    }

    ଫେରନ୍ତୁ buf;
}

ଅଚଳ AVPixFmtDescriptor *av_pix_fmt_desc_get(ଗଣନା AVPixelFormat pix_fmt)
{
    ଯଦି (pix_fmt < 0 || pix_fmt >= AV_PIX_FMT_NB)
        ଫେରନ୍ତୁ ଖାଲି;
    ଫେରନ୍ତୁ &av_pix_fmt_descriptors[pix_fmt];
}

ଅଚଳ AVPixFmtDescriptor *av_pix_fmt_desc_next(ଅଚଳ AVPixFmtDescriptor *prev)
{
    ଯଦି (!prev)
        ଫେରନ୍ତୁ &av_pix_fmt_descriptors[0];
    ଯେତେବେଳେ (prev - av_pix_fmt_descriptors < FF_ARRAY_ELEMS(av_pix_fmt_descriptors) - 1) {
        prev++;
        ଯଦି (prev->name)
            ଫେରନ୍ତୁ prev;
    }
    ଫେରନ୍ତୁ ଖାଲି;
}

ଗଣନା AVPixelFormat av_pix_fmt_desc_get_id(ଅଚଳ AVPixFmtDescriptor *desc)
{
    ଯଦି (desc < av_pix_fmt_descriptors ||
        desc >= av_pix_fmt_descriptors + FF_ARRAY_ELEMS(av_pix_fmt_descriptors))
        ଫେରନ୍ତୁ AV_PIX_FMT_NONE;

    ଫେରନ୍ତୁ desc - av_pix_fmt_descriptors;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_pix_fmt_get_chroma_sub_sample(ଗଣନା AVPixelFormat pix_fmt,
                                     ପୂର୍ଣ୍ଣସଂଖ୍ୟା *h_shift, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *v_shift)
{
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ଯଦି (!desc)
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    *h_shift = desc->log2_chroma_w;
    *v_shift = desc->log2_chroma_h;

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_pix_fmt_ଗଣନା_planes(ଗଣନା AVPixelFormat pix_fmt)
{
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, planes[4] = { 0 }, ret = 0;

    ଯଦି (!desc)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ପାଇଁ (i = 0; i < desc->nb_components; i++)
        planes[desc->comp[i].plane] = 1;
    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(planes); i++)
        ret += planes[i];
    ଫେରନ୍ତୁ ret;
}

ଗଣନା AVPixelFormat av_pix_fmt_swap_endianness(ଗଣନା AVPixelFormat pix_fmt)
{
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ଅକ୍ଷର name[16];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ଯଦି (!desc || strlen(desc->name) < 2)
        ଫେରନ୍ତୁ AV_PIX_FMT_NONE;
    av_strlcpy(name, desc->name, ଆକାର(name));
    i = strlen(name) - 2;
    ଯଦି (strcmp(name + i, "be") && strcmp(name + i, "le"))
        ଫେରନ୍ତୁ AV_PIX_FMT_NONE;

    name[i] ^= 'b' ^ 'l';

    ଫେରନ୍ତୁ get_pix_fmt_internal(name);
}

#define FF_COLOR_NA      -1
#define FF_COLOR_RGB      0 /**< RGB color space */
#define FF_COLOR_GRAY     1 /**< gray color space */
#define FF_COLOR_YUV      2 /**< YUV color space. 16 <= Y <= 235, 16 <= U, V <= 240 */
#define FF_COLOR_YUV_JPEG 3 /**< YUV color space. 0 <= Y <= 255, 0 <= U, V <= 255 */
#define FF_COLOR_XYZ      4

#define pixdesc_has_alpha(pixdesc) \
    ((pixdesc)->flags & AV_PIX_FMT_FLAG_ALPHA)


ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_color_type(ଅଚଳ AVPixFmtDescriptor *desc) {
    ଯଦି (desc->flags & AV_PIX_FMT_FLAG_PAL)
        ଫେରନ୍ତୁ FF_COLOR_RGB;

    ଯଦି(desc->nb_components == 1 || desc->nb_components == 2)
        ଫେରନ୍ତୁ FF_COLOR_GRAY;

    ଯଦି (desc->name) {
        ଯଦି (av_strstart(desc->name, "yuvj", ଖାଲି))
            ଫେରନ୍ତୁ FF_COLOR_YUV_JPEG;
    }

    ଯଦି(desc->flags & AV_PIX_FMT_FLAG_RGB)
        ଫେରନ୍ତୁ FF_COLOR_RGB;

    ଯଦି(desc->flags & AV_PIX_FMT_FLAG_XYZ)
        ଫେରନ୍ତୁ FF_COLOR_XYZ;

    ଯଦି(desc->nb_components == 0)
        ଫେରନ୍ତୁ FF_COLOR_NA;

    ଫେରନ୍ତୁ FF_COLOR_YUV;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_pix_fmt_depth(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *min, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *max, ଗଣନା AVPixelFormat pix_fmt)
{
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ଯଦି (!desc || !desc->nb_components) {
        *min = *max = 0;
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    *min = INT_MAX, *max = -INT_MAX;
    ପାଇଁ (i = 0; i < desc->nb_components; i++) {
        *min = FFMIN(desc->comp[i].depth, *min);
        *max = FFMAX(desc->comp[i].depth, *max);
    }
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_pix_fmt_score(ଗଣନା AVPixelFormat dst_pix_fmt,
                              ଗଣନା AVPixelFormat src_pix_fmt,
                              unsigned *lossp, unsigned consider)
{
    ଅଚଳ AVPixFmtDescriptor *src_desc = av_pix_fmt_desc_get(src_pix_fmt);
    ଅଚଳ AVPixFmtDescriptor *dst_desc = av_pix_fmt_desc_get(dst_pix_fmt);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_color, dst_color;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_min_depth, src_max_depth, dst_min_depth, dst_max_depth;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, loss, i, nb_components;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା score = INT_MAX - 1;

    ଯଦି (!src_desc || !dst_desc)
        ଫେରନ୍ତୁ -4;

    ଯଦି ((src_desc->flags & AV_PIX_FMT_FLAG_HWACCEL) ||
        (dst_desc->flags & AV_PIX_FMT_FLAG_HWACCEL)) {
        ଯଦି (dst_pix_fmt == src_pix_fmt)
            ଫେରନ୍ତୁ -1;
        ଅନ୍ୟଥା
            ଫେରନ୍ତୁ -2;
    }

    /* compute loss */
    *lossp = loss = 0;

    ଯଦି (dst_pix_fmt == src_pix_fmt)
        ଫେରନ୍ତୁ INT_MAX;

    ଯଦି ((ret = get_pix_fmt_depth(&src_min_depth, &src_max_depth, src_pix_fmt)) < 0)
        ଫେରନ୍ତୁ -3;
    ଯଦି ((ret = get_pix_fmt_depth(&dst_min_depth, &dst_max_depth, dst_pix_fmt)) < 0)
        ଫେରନ୍ତୁ -3;

    src_color = get_color_type(src_desc);
    dst_color = get_color_type(dst_desc);
    ଯଦି (dst_pix_fmt == AV_PIX_FMT_PAL8)
        nb_components = FFMIN(src_desc->nb_components, 4);
    ଅନ୍ୟଥା
        nb_components = FFMIN(src_desc->nb_components, dst_desc->nb_components);

    ପାଇଁ (i = 0; i < nb_components; i++) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା depth_minus1 = (dst_pix_fmt == AV_PIX_FMT_PAL8) ? 7/nb_components : (dst_desc->comp[i].depth - 1);
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା depth_delta = src_desc->comp[i].depth - 1 - depth_minus1;
        ଯଦି (depth_delta > 0 && (consider & FF_LOSS_DEPTH)) {
            loss |= FF_LOSS_DEPTH;
            score -= 65536 >> depth_minus1;
        } ଅନ୍ୟଥା ଯଦି (depth_delta < 0 && (consider & FF_LOSS_EXCESS_DEPTH)) {
            // Favour formats where bit depth exactly matches. If all other
            // scoring is equal, we'd rather use the bit depth that most closely
            // matches the source.
            loss |= FF_LOSS_EXCESS_DEPTH;
            score += depth_delta;
        }
    }

    ଯଦି (consider & FF_LOSS_RESOLUTION) {
        ଯଦି (dst_desc->log2_chroma_w > src_desc->log2_chroma_w) {
            loss |= FF_LOSS_RESOLUTION;
            score -= 256 << dst_desc->log2_chroma_w;
        }
        ଯଦି (dst_desc->log2_chroma_h > src_desc->log2_chroma_h) {
            loss |= FF_LOSS_RESOLUTION;
            score -= 256 << dst_desc->log2_chroma_h;
        }
        // don't favor 422 over 420 if downsampling is needed, because 420 has much better support on the decoder side
        ଯଦି (dst_desc->log2_chroma_w == 1 && src_desc->log2_chroma_w == 0 &&
            dst_desc->log2_chroma_h == 1 && src_desc->log2_chroma_h == 0 ) {
            score += 512;
        }
    }

    ଯଦି (consider & FF_LOSS_EXCESS_RESOLUTION) {
        // Favour formats where chroma subsampling exactly matches. If all other
        // scoring is equal, we'd rather use the subsampling that most closely
        // matches the source.
        ଯଦି (dst_desc->log2_chroma_w < src_desc->log2_chroma_w) {
            loss |= FF_LOSS_EXCESS_RESOLUTION;
            score -= 1 << (src_desc->log2_chroma_w - dst_desc->log2_chroma_w);
        }

        ଯଦି (dst_desc->log2_chroma_h < src_desc->log2_chroma_h) {
            loss |= FF_LOSS_EXCESS_RESOLUTION;
            score -= 1 << (src_desc->log2_chroma_h - dst_desc->log2_chroma_h);
        }

        // don't favour 411 over 420, because 420 has much better support on the
        // decoder side.
        ଯଦି (dst_desc->log2_chroma_w == 1 && src_desc->log2_chroma_w == 2 &&
            dst_desc->log2_chroma_h == 1 && src_desc->log2_chroma_h == 2) {
                score += 4;
            }
    }

    ଯଦି(consider & FF_LOSS_COLORSPACE)
    ବାଛ(dst_color) {
    ସ୍ଥିତି FF_COLOR_RGB:
        ଯଦି (src_color != FF_COLOR_RGB &&
            src_color != FF_COLOR_GRAY)
            loss |= FF_LOSS_COLORSPACE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି FF_COLOR_GRAY:
        ଯଦି (src_color != FF_COLOR_GRAY)
            loss |= FF_LOSS_COLORSPACE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି FF_COLOR_YUV:
        ଯଦି (src_color != FF_COLOR_YUV)
            loss |= FF_LOSS_COLORSPACE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି FF_COLOR_YUV_JPEG:
        ଯଦି (src_color != FF_COLOR_YUV_JPEG &&
            src_color != FF_COLOR_YUV &&
            src_color != FF_COLOR_GRAY)
            loss |= FF_LOSS_COLORSPACE;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        /* fail safe test */
        ଯଦି (src_color != dst_color)
            loss |= FF_LOSS_COLORSPACE;
        ଭାଙ୍ଗ;
    }
    ଯଦି(loss & FF_LOSS_COLORSPACE)
        score -= (nb_components * 65536) >> FFMIN(dst_desc->comp[0].depth - 1, src_desc->comp[0].depth - 1);

    ଯଦି (dst_color == FF_COLOR_GRAY &&
        src_color != FF_COLOR_GRAY && (consider & FF_LOSS_CHROMA)) {
        loss |= FF_LOSS_CHROMA;
        score -= 2 * 65536;
    }
    ଯଦି (!pixdesc_has_alpha(dst_desc) && (pixdesc_has_alpha(src_desc) && (consider & FF_LOSS_ALPHA))) {
        loss |= FF_LOSS_ALPHA;
        score -= 65536;
    }
    ଯଦି (dst_pix_fmt == AV_PIX_FMT_PAL8 && (consider & FF_LOSS_COLORQUANT) &&
        (src_pix_fmt != AV_PIX_FMT_PAL8 && (src_color != FF_COLOR_GRAY || (pixdesc_has_alpha(src_desc) && (consider & FF_LOSS_ALPHA))))) {
        loss |= FF_LOSS_COLORQUANT;
        score -= 65536;
    }

    *lossp = loss;
    ଫେରନ୍ତୁ score;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_get_pix_fmt_loss(ଗଣନା AVPixelFormat dst_pix_fmt,
                            ଗଣନା AVPixelFormat src_pix_fmt,
                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା has_alpha)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା loss;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = get_pix_fmt_score(dst_pix_fmt, src_pix_fmt, &loss, has_alpha ? ~0 : ~FF_LOSS_ALPHA);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;
    ଫେରନ୍ତୁ loss;
}

ଗଣନା AVPixelFormat av_find_best_pix_fmt_of_2(ଗଣନା AVPixelFormat dst_pix_fmt1, ଗଣନା AVPixelFormat dst_pix_fmt2,
                                             ଗଣନା AVPixelFormat src_pix_fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା has_alpha, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *loss_ptr)
{
    ଗଣନା AVPixelFormat dst_pix_fmt;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା loss1, loss2, loss_mask;
    ଅଚଳ AVPixFmtDescriptor *desc1 = av_pix_fmt_desc_get(dst_pix_fmt1);
    ଅଚଳ AVPixFmtDescriptor *desc2 = av_pix_fmt_desc_get(dst_pix_fmt2);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା score1, score2;

    ଯଦି (!desc1) {
        dst_pix_fmt = dst_pix_fmt2;
    } ଅନ୍ୟଥା ଯଦି (!desc2) {
        dst_pix_fmt = dst_pix_fmt1;
    } ଅନ୍ୟଥା {
        loss_mask= loss_ptr?~*loss_ptr:~0; /* use loss mask if provided */
        ଯଦି(!has_alpha)
            loss_mask &= ~FF_LOSS_ALPHA;

        score1 = get_pix_fmt_score(dst_pix_fmt1, src_pix_fmt, &loss1, loss_mask);
        score2 = get_pix_fmt_score(dst_pix_fmt2, src_pix_fmt, &loss2, loss_mask);

        ଯଦି (score1 == score2) {
            ଯଦି(av_get_padded_bits_per_pixel(desc2) != av_get_padded_bits_per_pixel(desc1)) {
                dst_pix_fmt = av_get_padded_bits_per_pixel(desc2) < av_get_padded_bits_per_pixel(desc1) ? dst_pix_fmt2 : dst_pix_fmt1;
            } ଅନ୍ୟଥା {
                dst_pix_fmt = desc2->nb_components < desc1->nb_components ? dst_pix_fmt2 : dst_pix_fmt1;
            }
        } ଅନ୍ୟଥା {
            dst_pix_fmt = score1 < score2 ? dst_pix_fmt2 : dst_pix_fmt1;
        }
    }

    ଯଦି (loss_ptr)
        *loss_ptr = av_get_pix_fmt_loss(dst_pix_fmt, src_pix_fmt, has_alpha);
    ଫେରନ୍ତୁ dst_pix_fmt;
}

ଅଚଳ ଅକ୍ଷର *av_color_range_name(ଗଣନା AVColorRange range)
{
    ଫେରନ୍ତୁ (unsigned) range < AVCOL_RANGE_NB ?
        color_range_names[range] : ଖାଲି;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_color_range_from_name(ଅଚଳ ଅକ୍ଷର *name)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(color_range_names); i++) {
        ଯଦି (!strcmp(name, color_range_names[i]))
            ଫେରନ୍ତୁ i;
    }

    ଫେରନ୍ତୁ AVERROR(EINVAL);
}

ଅଚଳ ଅକ୍ଷର *av_color_primaries_name(ଗଣନା AVColorPrimaries primaries)
{
    ଯଦି ((unsigned)primaries < AVCOL_PRI_NB)
        ଫେରନ୍ତୁ color_primaries_names[primaries];
    ଅନ୍ୟଥା ଯଦି (((unsigned)primaries >= AVCOL_PRI_EXT_BASE) &&
             ((unsigned)primaries < AVCOL_PRI_EXT_NB))
        ଫେରନ୍ତୁ color_primaries_names_ext[primaries - AVCOL_TRC_EXT_BASE];
    ଫେରନ୍ତୁ ଖାଲି;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_color_primaries_from_name(ଅଚଳ ଅକ୍ଷର *name)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(color_primaries_names); i++) {
        ଯଦି (!color_primaries_names[i])
            ଜାରି;

        ଯଦି (!strcmp(name, color_primaries_names[i]))
            ଫେରନ୍ତୁ i;
    }

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(color_primaries_names_ext); i++) {
        ଯଦି (!color_primaries_names_ext[i])
            ଜାରି;

        ଯଦି (!strcmp(name, color_primaries_names_ext[i]))
            ଫେରନ୍ତୁ AVCOL_PRI_EXT_BASE + i;
    }

    ଫେରନ୍ତୁ AVERROR(EINVAL);
}

ଅଚଳ ଅକ୍ଷର *av_color_transfer_name(ଗଣନା AVColorTransferCharacteristic transfer)
{
    ଯଦି ((unsigned)transfer < AVCOL_TRC_NB)
        ଫେରନ୍ତୁ color_transfer_names[transfer];
    ଅନ୍ୟଥା ଯଦି (((unsigned)transfer >= AVCOL_TRC_EXT_BASE) &&
             ((unsigned)transfer < AVCOL_TRC_EXT_NB))
        ଫେରନ୍ତୁ color_transfer_names_ext[transfer - AVCOL_TRC_EXT_BASE];
    ଫେରନ୍ତୁ ଖାଲି;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_color_transfer_from_name(ଅଚଳ ଅକ୍ଷର *name)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(color_transfer_names); i++) {
        ଯଦି (!color_transfer_names[i])
            ଜାରି;

        ଯଦି (!strcmp(name, color_transfer_names[i]))
            ଫେରନ୍ତୁ i;
    }

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(color_transfer_names_ext); i++) {
        ଯଦି (!color_transfer_names_ext[i])
            ଜାରି;

        ଯଦି (!strcmp(name, color_transfer_names_ext[i]))
            ଫେରନ୍ତୁ AVCOL_TRC_EXT_BASE + i;
    }

    ଫେରନ୍ତୁ AVERROR(EINVAL);
}

ଅଚଳ ଅକ୍ଷର *av_color_space_name(ଗଣନା AVColorSpace space)
{
    ଫେରନ୍ତୁ (unsigned) space < AVCOL_SPC_NB ?
        color_space_names[space] : ଖାଲି;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_color_space_from_name(ଅଚଳ ଅକ୍ଷର *name)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(color_space_names); i++) {
        ଯଦି (!color_space_names[i])
            ଜାରି;

        ଯଦି (!strcmp(name, color_space_names[i]))
            ଫେରନ୍ତୁ i;
    }

    ଫେରନ୍ତୁ AVERROR(EINVAL);
}

ଅଚଳ ଅକ୍ଷର *av_chroma_location_name(ଗଣନା AVChromaLocation location)
{
    ଫେରନ୍ତୁ (unsigned) location < AVCHROMA_LOC_NB ?
        chroma_location_names[location] : ଖାଲି;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_chroma_location_from_name(ଅଚଳ ଅକ୍ଷର *name)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(chroma_location_names); i++) {
        ଯଦି (!chroma_location_names[i])
            ଜାରି;

        ଯଦି (!strcmp(name, chroma_location_names[i]))
            ଫେରନ୍ତୁ i;
    }

    ଫେରନ୍ତୁ AVERROR(EINVAL);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_chroma_location_enum_to_pos(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *xpos, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *ypos, ଗଣନା AVChromaLocation pos)
{
    ଯଦି (pos <= AVCHROMA_LOC_UNSPECIFIED || pos >= AVCHROMA_LOC_NB)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    pos--;

    *xpos = (pos&1) * 128;
    *ypos = ((pos>>1)^(pos<4)) * 128;

    ଫେରନ୍ତୁ 0;
}

ଗଣନା AVChromaLocation av_chroma_location_pos_to_enum(ପୂର୍ଣ୍ଣସଂଖ୍ୟା xpos, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ypos)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା pos, xout, yout;

    ପାଇଁ (pos = AVCHROMA_LOC_UNSPECIFIED + 1; pos < AVCHROMA_LOC_NB; pos++) {
        ଯଦି (av_chroma_location_enum_to_pos(&xout, &yout, pos) == 0 && xout == xpos && yout == ypos)
            ଫେରନ୍ତୁ pos;
    }
    ଫେରନ୍ତୁ AVCHROMA_LOC_UNSPECIFIED;
}

ଅଚଳ ଅକ୍ଷର *av_alpha_mode_name(ଗଣନା AVAlphaMode mode)
{
    ଫେରନ୍ତୁ (unsigned) mode < AVALPHA_MODE_NB ?
        alpha_mode_names[mode] : ଖାଲି;
}

ଗଣନା AVAlphaMode av_alpha_mode_from_name(ଅଚଳ ଅକ୍ଷର *name)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_ARRAY_ELEMS(alpha_mode_names); i++) {
        ଯଦି (!alpha_mode_names[i])
            ଜାରି;

        ଯଦି (!strcmp(name, alpha_mode_names[i]))
            ଫେରନ୍ତୁ i;
    }

    ଫେରନ୍ତୁ AVERROR(EINVAL);
}
