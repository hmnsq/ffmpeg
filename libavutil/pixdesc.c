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

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "avstring.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "pixfmt.h"
#ಅನ್ತರ್ಭಾವ "pixdesc.h"
#ಅನ್ತರ್ಭಾವ "intreadwrite.h"

ಶೂನ್ಯ av_read_image_line2(ಶೂನ್ಯ *dst,
                        ಸ್ಥಿರಾಂಕ uint8_t *ದತ್ತಾಂಶ[4], ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ linesize[4],
                        ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc,
                        ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y, ಪೂರ್ಣಾಂಕ c, ಪೂರ್ಣಾಂಕ w,
                        ಪೂರ್ಣಾಂಕ read_pal_component,
                        ಪೂರ್ಣಾಂಕ dst_element_ಗಾತ್ರ)
{
    AVComponentDescriptor comp = desc->comp[c];
    ಪೂರ್ಣಾಂಕ plane = comp.plane;
    ಪೂರ್ಣಾಂಕ ಆಳ = comp.ಆಳ;
    ಚಿಹ್ನೆರಹಿತ ಮುಖವಾಡ_2  = (1ULL << ಆಳ) - 1;
    ಪೂರ್ಣಾಂಕ ಸರಿಸು = comp.ಸರಿಸು;
    ಪೂರ್ಣಾಂಕ ಹೆಜ್ಜೆ  = comp.ಹೆಜ್ಜೆ;
    ಪೂರ್ಣಾಂಕ flags = desc->flags;
    uint16_t *dst16 = dst;
    uint32_t *dst32 = dst;

    ಆದರೆ (!ಆಳ)
        ಹಿಂತಿರುಗಿ;

    ಆದರೆ (flags & AV_PIX_FMT_FLAG_BITSTREAM) {
        ಆದರೆ (ಹೆಜ್ಜೆ > 8) {
            // Assume all channels are packed into a 32bit value
            ಸ್ಥಿರಾಂಕ uint8_t *byte_p = ದತ್ತಾಂಶ[plane] + y * linesize[plane];
            ಸ್ಥಿರಾಂಕ uint32_t *p = (uint32_t *)byte_p;

            ಆಗ (w--) {
                ಪೂರ್ಣಾಂಕ val = AV_RB32(p);
                val = (val >> comp.ಸ್ಥಾನಾಂತರ) & ಮುಖವಾಡ_2;
                ಆದರೆ (read_pal_component)
                    val = ದತ್ತಾಂಶ[1][4*val + c];
                ಆದರೆ (dst_element_ಗಾತ್ರ == 4) *dst32++ = val;
                ಇಲ್ಲದಿದ್ದರೆ                       *dst16++ = val;
                p++;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಪೂರ್ಣಾಂಕ skip = x * ಹೆಜ್ಜೆ + comp.ಸ್ಥಾನಾಂತರ;
            ಸ್ಥಿರಾಂಕ uint8_t *p = ದತ್ತಾಂಶ[plane] + y * linesize[plane] + (skip >> 3);
            ಪೂರ್ಣಾಂಕ ಸರಿಸು = 8 - ಆಳ - (skip & 7);

            ಆಗ (w--) {
                ಪೂರ್ಣಾಂಕ val = (*p >> ಸರಿಸು) & ಮುಖವಾಡ_2;
                ಆದರೆ (read_pal_component)
                    val = ದತ್ತಾಂಶ[1][4*val + c];
                ಸರಿಸು -= ಹೆಜ್ಜೆ;
                p -= ಸರಿಸು >> 3;
                ಸರಿಸು &= 7;
                ಆದರೆ (dst_element_ಗಾತ್ರ == 4) *dst32++ = val;
                ಇಲ್ಲದಿದ್ದರೆ                       *dst16++ = val;
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರಾಂಕ uint8_t *p = ದತ್ತಾಂಶ[plane] + y * linesize[plane] +
                           x * ಹೆಜ್ಜೆ + comp.ಸ್ಥಾನಾಂತರ;
        ಪೂರ್ಣಾಂಕ is_8bit = ಸರಿಸು + ಆಳ <= 8;
        ಪೂರ್ಣಾಂಕ is_16bit= ಸರಿಸು + ಆಳ <=16;

        ಆದರೆ (is_8bit)
            p += !!(flags & AV_PIX_FMT_FLAG_BE);

        ಆಗ (w--) {
            ಚಿಹ್ನೆರಹಿತ val;
            ಆದರೆ     (is_8bit)  val = *p;
            ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ(is_16bit) val = flags & AV_PIX_FMT_FLAG_BE ? AV_RB16(p) : AV_RL16(p);
            ಇಲ್ಲದಿದ್ದರೆ              val = flags & AV_PIX_FMT_FLAG_BE ? AV_RB32(p) : AV_RL32(p);
            val = (val >> ಸರಿಸು) & ಮುಖವಾಡ_2;
            ಆದರೆ (read_pal_component)
                val = ದತ್ತಾಂಶ[1][4 * val + c];
            p += ಹೆಜ್ಜೆ;
            ಆದರೆ (dst_element_ಗಾತ್ರ == 4) *dst32++ = val;
            ಇಲ್ಲದಿದ್ದರೆ                       *dst16++ = val;
        }
    }
}

ಶೂನ್ಯ av_read_image_ಸಾಲು(uint16_t *dst,
                        ಸ್ಥಿರಾಂಕ uint8_t *ದತ್ತಾಂಶ[4], ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ linesize[4],
                        ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc,
                        ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y, ಪೂರ್ಣಾಂಕ c, ಪೂರ್ಣಾಂಕ w,
                        ಪೂರ್ಣಾಂಕ read_pal_component)
{
    av_read_image_line2(dst, ದತ್ತಾಂಶ, linesize, desc,x, y, c, w,
                        read_pal_component,
                        2);
}

ಶೂನ್ಯ av_write_image_line2(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src,
                         uint8_t *ದತ್ತಾಂಶ[4], ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ linesize[4],
                         ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc,
                         ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y, ಪೂರ್ಣಾಂಕ c, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ src_element_ಗಾತ್ರ)
{
    AVComponentDescriptor comp = desc->comp[c];
    ಪೂರ್ಣಾಂಕ plane = comp.plane;
    ಪೂರ್ಣಾಂಕ ಆಳ = comp.ಆಳ;
    ಪೂರ್ಣಾಂಕ ಹೆಜ್ಜೆ  = comp.ಹೆಜ್ಜೆ;
    ಪೂರ್ಣಾಂಕ flags = desc->flags;
    ಸ್ಥಿರಾಂಕ uint32_t *src32 = src;
    ಸ್ಥಿರಾಂಕ uint16_t *src16 = src;

    ಆದರೆ (!ಆಳ)
        ಹಿಂತಿರುಗಿ;

    ಆದರೆ (flags & AV_PIX_FMT_FLAG_BITSTREAM) {
        ಆದರೆ (ಹೆಜ್ಜೆ > 8) {
            // Assume all channels are packed into a 32bit value
            ಸ್ಥಿರಾಂಕ uint8_t *byte_p = ದತ್ತಾಂಶ[plane] + y * linesize[plane];
            uint32_t *p = (uint32_t *)byte_p;
            ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ = comp.ಸ್ಥಾನಾಂತರ;
            uint32_t ಮುಖವಾಡ_2  = ((1ULL << ಆಳ) - 1) << ಸ್ಥಾನಾಂತರ;

            ಆಗ (w--) {
                ಚಿಹ್ನೆರಹಿತ val = src_element_ಗಾತ್ರ == 4 ? *src32++ : *src16++;
                AV_WB32(p, (AV_RB32(p) & ~ಮುಖವಾಡ_2) | (val << ಸ್ಥಾನಾಂತರ));
                p++;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಪೂರ್ಣಾಂಕ skip = x * ಹೆಜ್ಜೆ + comp.ಸ್ಥಾನಾಂತರ;
            uint8_t *p = ದತ್ತಾಂಶ[plane] + y * linesize[plane] + (skip >> 3);
            ಪೂರ್ಣಾಂಕ ಸರಿಸು = 8 - ಆಳ - (skip & 7);

            ಆಗ (w--) {
                *p |= (src_element_ಗಾತ್ರ == 4 ? *src32++ : *src16++) << ಸರಿಸು;
                ಸರಿಸು -= ಹೆಜ್ಜೆ;
                p -= ಸರಿಸು >> 3;
                ಸರಿಸು &= 7;
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಪೂರ್ಣಾಂಕ ಸರಿಸು = comp.ಸರಿಸು;
        uint8_t *p = ದತ್ತಾಂಶ[plane] + y * linesize[plane] +
                     x * ಹೆಜ್ಜೆ + comp.ಸ್ಥಾನಾಂತರ;

        ಆದರೆ (ಸರಿಸು + ಆಳ <= 8) {
            p += !!(flags & AV_PIX_FMT_FLAG_BE);
            ಆಗ (w--) {
                *p |= ((src_element_ಗಾತ್ರ == 4 ? *src32++ : *src16++) << ಸರಿಸು);
                p += ಹೆಜ್ಜೆ;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆಗ (w--) {
                ಚಿಹ್ನೆರಹಿತ s = (src_element_ಗಾತ್ರ == 4 ? *src32++ : *src16++);
                ಆದರೆ (ಸರಿಸು + ಆಳ <= 16) {
                    ಆದರೆ (flags & AV_PIX_FMT_FLAG_BE) {
                        uint16_t val = AV_RB16(p) | (s << ಸರಿಸು);
                        AV_WB16(p, val);
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        uint16_t val = AV_RL16(p) | (s << ಸರಿಸು);
                        AV_WL16(p, val);
                    }
                } ಇಲ್ಲದಿದ್ದರೆ {
                    ಆದರೆ (flags & AV_PIX_FMT_FLAG_BE) {
                        uint32_t val = AV_RB32(p) | (s << ಸರಿಸು);
                        AV_WB32(p, val);
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        uint32_t val = AV_RL32(p) | (s << ಸರಿಸು);
                        AV_WL32(p, val);
                    }
                }
                p += ಹೆಜ್ಜೆ;
            }
        }
    }
}

ಶೂನ್ಯ av_write_image_ಸಾಲು(ಸ್ಥಿರಾಂಕ uint16_t *src,
                         uint8_t *ದತ್ತಾಂಶ[4], ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ linesize[4],
                         ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc,
                         ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y, ಪೂರ್ಣಾಂಕ c, ಪೂರ್ಣಾಂಕ w)
{
    av_write_image_line2(src, ದತ್ತಾಂಶ, linesize, desc, x, y, c, w, 2);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor av_pix_fmt_descriptors[AV_PIX_FMT_NB] = {
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

#ವ್ಯಾಖ್ಯಾನಿಸು BAYER8_DESC_COMMON \
        .nb_components= 3, \
        .log2_chroma_w= 0, \
        .log2_chroma_h= 0, \
        .comp = {          \
            { 0, 1, 0, 0, 2 }, \
            { 0, 1, 0, 0, 4 }, \
            { 0, 1, 0, 0, 2 }, \
        },                 \

#ವ್ಯಾಖ್ಯಾನಿಸು BAYER16_DESC_COMMON \
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
    [AV_PIX_FMT_DRM_ಅವಿಭಾಜ್ಯ] = {
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

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ color_range_ಹೆಸರುಗಳು[] = {
    [AVCOL_RANGE_UNSPECIFIED] = "unknown",
    [AVCOL_RANGE_MPEG] = "tv",
    [AVCOL_RANGE_JPEG] = "pc",
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ color_primaries_ಹೆಸರುಗಳು[AVCOL_PRI_NB] = {
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

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ color_primaries_ಹೆಸರುಗಳು_ext[AVCOL_PRI_EXT_NB -
                                                    AVCOL_PRI_EXT_ತಳ] = {
    [AVCOL_PRI_V_GAMUT - AVCOL_PRI_EXT_ತಳ] = "vgamut",
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ color_transfer_ಹೆಸರುಗಳು[] = {
    [AVCOL_TRC_RESERVED0] = "reserved",
    [AVCOL_TRC_BT709] = "bt709",
    [AVCOL_TRC_UNSPECIFIED] = "unknown",
    [AVCOL_TRC_RESERVED] = "reserved",
    [AVCOL_TRC_GAMMA22] = "bt470m",
    [AVCOL_TRC_GAMMA28] = "bt470bg",
    [AVCOL_TRC_SMPTE170M] = "smpte170m",
    [AVCOL_TRC_SMPTE240M] = "smpte240m",
    [AVCOL_TRC_ರೇಖೀಯ] = "linear",
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

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ color_transfer_ಹೆಸರುಗಳು_ext[] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_ತಳ] = "vlog",
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ color_space_ಹೆಸರುಗಳು[] = {
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

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ chroma_location_ಹೆಸರುಗಳು[] = {
    [AVCHROMA_LOC_UNSPECIFIED] = "unspecified",
    [AVCHROMA_LOC_ಎಡ] = "left",
    [AVCHROMA_LOC_CENTER] = "center",
    [AVCHROMA_LOC_TOPLEFT] = "topleft",
    [AVCHROMA_LOC_ತುದಿ] = "top",
    [AVCHROMA_LOC_BOTTOMLEFT] = "bottomleft",
    [AVCHROMA_LOC_BOTTOM] = "bottom",
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ alpha_ಬಹುಲಕ_ಹೆಸರುಗಳು[] = {
    [AVALPHA_ಬಹುಲಕ_UNSPECIFIED] = "unspecified",
    [AVALPHA_ಬಹುಲಕ_PREMULTIPLIED] = "premultiplied",
    [AVALPHA_ಬಹುಲಕ_STRAIGHT] = "straight",
};

ಸ್ಥಿರ ಎಣಿಕೆ AVPixelFormat get_pix_fmt_ಆಂತರಿಕ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಎಣಿಕೆ AVPixelFormat pix_fmt;

    ಗಾಗಿ (pix_fmt = 0; pix_fmt < AV_PIX_FMT_NB; pix_fmt++)
        ಆದರೆ (av_pix_fmt_descriptors[pix_fmt].name &&
            (!strcmp(av_pix_fmt_descriptors[pix_fmt].name, name) ||
             av_ಹೊಂದಿಕೆ_name(name, av_pix_fmt_descriptors[pix_fmt].alias)))
            ಹಿಂತಿರುಗಿ pix_fmt;

    ಹಿಂತಿರುಗಿ AV_PIX_FMT_NONE;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_get_pix_fmt_name(ಎಣಿಕೆ AVPixelFormat pix_fmt)
{
    ಹಿಂತಿರುಗಿ (ಚಿಹ್ನೆರಹಿತ)pix_fmt < AV_PIX_FMT_NB ?
        av_pix_fmt_descriptors[pix_fmt].name : ಖಾಲಿ;
}

#ಆದರೆ HAVE_BIGENDIAN
#   define X_NE(be, le) be
#ಇಲ್ಲದಿದ್ದರೆ
#   define X_NE(be, le) le
#ಆದರೆ_ಅಂತ್ಯ

ಎಣಿಕೆ AVPixelFormat av_get_pix_fmt(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಎಣಿಕೆ AVPixelFormat pix_fmt;

    ಆದರೆ (!strcmp(name, "rgb32"))
        name = X_NE("argb", "bgra");
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!strcmp(name, "bgr32"))
        name = X_NE("abgr", "rgba");

    pix_fmt = get_pix_fmt_ಆಂತರಿಕ(name);
    ಆದರೆ (pix_fmt == AV_PIX_FMT_NONE) {
        ಅಕ್ಷರ name2[32];

        snprintf(name2, ಗಾತ್ರ(name2), "%s%s", name, X_NE("be", "le"));
        pix_fmt = get_pix_fmt_ಆಂತರಿಕ(name2);
    }

    ಹಿಂತಿರುಗಿ pix_fmt;
}

ಪೂರ್ಣಾಂಕ av_get_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel(ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *pixdesc)
{
    ಪೂರ್ಣಾಂಕ c, ಬಿಟ್ಟುಗಳು = 0;
    ಪೂರ್ಣಾಂಕ log2_pixels = pixdesc->log2_chroma_w + pixdesc->log2_chroma_h;

    ಗಾಗಿ (c = 0; c < pixdesc->nb_components; c++) {
        ಪೂರ್ಣಾಂಕ s = c == 1 || c == 2 ? 0 : log2_pixels;
        ಬಿಟ್ಟುಗಳು += pixdesc->comp[c].ಆಳ << s;
    }

    ಹಿಂತಿರುಗಿ ಬಿಟ್ಟುಗಳು >> log2_pixels;
}

ಪೂರ್ಣಾಂಕ av_get_padded_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel(ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *pixdesc)
{
    ಪೂರ್ಣಾಂಕ c, ಬಿಟ್ಟುಗಳು = 0;
    ಪೂರ್ಣಾಂಕ log2_pixels = pixdesc->log2_chroma_w + pixdesc->log2_chroma_h;
    ಪೂರ್ಣಾಂಕ ಹೆಜ್ಜೆಗಳು[4] = {0};

    ಗಾಗಿ (c = 0; c < pixdesc->nb_components; c++) {
        ಸ್ಥಿರಾಂಕ AVComponentDescriptor *comp = &pixdesc->comp[c];
        ಪೂರ್ಣಾಂಕ s = c == 1 || c == 2 ? 0 : log2_pixels;
        ಹೆಜ್ಜೆಗಳು[comp->plane] = comp->ಹೆಜ್ಜೆ << s;
    }
    ಗಾಗಿ (c = 0; c < 4; c++)
        ಬಿಟ್ಟುಗಳು += ಹೆಜ್ಜೆಗಳು[c];

    ಆದರೆ(!(pixdesc->flags & AV_PIX_FMT_FLAG_BITSTREAM))
        ಬಿಟ್ಟುಗಳು *= 8;

    ಹಿಂತಿರುಗಿ ಬಿಟ್ಟುಗಳು >> log2_pixels;
}

ಅಕ್ಷರ *av_get_pix_fmt_string(ಅಕ್ಷರ *buf, ಪೂರ್ಣಾಂಕ buf_ಗಾತ್ರ,
                            ಎಣಿಕೆ AVPixelFormat pix_fmt)
{
    /* print header */
    ಆದರೆ (pix_fmt < 0) {
       snprintf (buf, buf_ಗಾತ್ರ, "name" " nb_components" " nb_bits");
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *pixdesc = &av_pix_fmt_descriptors[pix_fmt];
        snprintf(buf, buf_ಗಾತ್ರ, "%-11s %7d %10d", pixdesc->name,
                 pixdesc->nb_components, av_get_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel(pixdesc));
    }

    ಹಿಂತಿರುಗಿ buf;
}

ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *av_pix_fmt_desc_get(ಎಣಿಕೆ AVPixelFormat pix_fmt)
{
    ಆದರೆ (pix_fmt < 0 || pix_fmt >= AV_PIX_FMT_NB)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ &av_pix_fmt_descriptors[pix_fmt];
}

ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *av_pix_fmt_desc_ಮುಂದಿನ(ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *prev)
{
    ಆದರೆ (!prev)
        ಹಿಂತಿರುಗಿ &av_pix_fmt_descriptors[0];
    ಆಗ (prev - av_pix_fmt_descriptors < FF_ARRAY_ELEMS(av_pix_fmt_descriptors) - 1) {
        prev++;
        ಆದರೆ (prev->name)
            ಹಿಂತಿರುಗಿ prev;
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಎಣಿಕೆ AVPixelFormat av_pix_fmt_desc_get_id(ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc)
{
    ಆದರೆ (desc < av_pix_fmt_descriptors ||
        desc >= av_pix_fmt_descriptors + FF_ARRAY_ELEMS(av_pix_fmt_descriptors))
        ಹಿಂತಿರುಗಿ AV_PIX_FMT_NONE;

    ಹಿಂತಿರುಗಿ desc - av_pix_fmt_descriptors;
}

ಪೂರ್ಣಾಂಕ av_pix_fmt_get_chroma_sub_sample(ಎಣಿಕೆ AVPixelFormat pix_fmt,
                                     ಪೂರ್ಣಾಂಕ *h_ಸರಿಸು, ಪೂರ್ಣಾಂಕ *v_ಸರಿಸು)
{
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ಆದರೆ (!desc)
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    *h_ಸರಿಸು = desc->log2_chroma_w;
    *v_ಸರಿಸು = desc->log2_chroma_h;

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_pix_fmt_ಎಣಿಕೆ_planes(ಎಣಿಕೆ AVPixelFormat pix_fmt)
{
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ಪೂರ್ಣಾಂಕ i, planes[4] = { 0 }, ret = 0;

    ಆದರೆ (!desc)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಗಾಗಿ (i = 0; i < desc->nb_components; i++)
        planes[desc->comp[i].plane] = 1;
    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(planes); i++)
        ret += planes[i];
    ಹಿಂತಿರುಗಿ ret;
}

ಎಣಿಕೆ AVPixelFormat av_pix_fmt_ಅದಲುಬದಲು_endianness(ಎಣಿಕೆ AVPixelFormat pix_fmt)
{
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ಅಕ್ಷರ name[16];
    ಪೂರ್ಣಾಂಕ i;

    ಆದರೆ (!desc || ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(desc->name) < 2)
        ಹಿಂತಿರುಗಿ AV_PIX_FMT_NONE;
    av_strlcpy(name, desc->name, ಗಾತ್ರ(name));
    i = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(name) - 2;
    ಆದರೆ (strcmp(name + i, "be") && strcmp(name + i, "le"))
        ಹಿಂತಿರುಗಿ AV_PIX_FMT_NONE;

    name[i] ^= 'b' ^ 'l';

    ಹಿಂತಿರುಗಿ get_pix_fmt_ಆಂತರಿಕ(name);
}

#ವ್ಯಾಖ್ಯಾನಿಸು FF_COLOR_NA      -1
#ವ್ಯಾಖ್ಯಾನಿಸು FF_COLOR_RGB      0 /**< RGB color space */
#ವ್ಯಾಖ್ಯಾನಿಸು FF_COLOR_ಬೂದು     1 /**< gray color space */
#ವ್ಯಾಖ್ಯಾನಿಸು FF_COLOR_YUV      2 /**< YUV color space. 16 <= Y <= 235, 16 <= U, V <= 240 */
#ವ್ಯಾಖ್ಯಾನಿಸು FF_COLOR_YUV_JPEG 3 /**< YUV color space. 0 <= Y <= 255, 0 <= U, V <= 255 */
#ವ್ಯಾಖ್ಯಾನಿಸು FF_COLOR_XYZ      4

#ವ್ಯಾಖ್ಯಾನಿಸು pixdesc_has_alpha(pixdesc) \
    ((pixdesc)->flags & AV_PIX_FMT_FLAG_ALPHA)


ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_color_type(ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc) {
    ಆದರೆ (desc->flags & AV_PIX_FMT_FLAG_PAL)
        ಹಿಂತಿರುಗಿ FF_COLOR_RGB;

    ಆದರೆ(desc->nb_components == 1 || desc->nb_components == 2)
        ಹಿಂತಿರುಗಿ FF_COLOR_ಬೂದು;

    ಆದರೆ (desc->name) {
        ಆದರೆ (av_strstart(desc->name, "yuvj", ಖಾಲಿ))
            ಹಿಂತಿರುಗಿ FF_COLOR_YUV_JPEG;
    }

    ಆದರೆ(desc->flags & AV_PIX_FMT_FLAG_RGB)
        ಹಿಂತಿರುಗಿ FF_COLOR_RGB;

    ಆದರೆ(desc->flags & AV_PIX_FMT_FLAG_XYZ)
        ಹಿಂತಿರುಗಿ FF_COLOR_XYZ;

    ಆದರೆ(desc->nb_components == 0)
        ಹಿಂತಿರುಗಿ FF_COLOR_NA;

    ಹಿಂತಿರುಗಿ FF_COLOR_YUV;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_pix_fmt_ಆಳ(ಪೂರ್ಣಾಂಕ *min, ಪೂರ್ಣಾಂಕ *max, ಎಣಿಕೆ AVPixelFormat pix_fmt)
{
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ಪೂರ್ಣಾಂಕ i;

    ಆದರೆ (!desc || !desc->nb_components) {
        *min = *max = 0;
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    *min = ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, *max = -ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ;
    ಗಾಗಿ (i = 0; i < desc->nb_components; i++) {
        *min = FFMIN(desc->comp[i].ಆಳ, *min);
        *max = FFMAX(desc->comp[i].ಆಳ, *max);
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_pix_fmt_score(ಎಣಿಕೆ AVPixelFormat dst_pix_fmt,
                              ಎಣಿಕೆ AVPixelFormat src_pix_fmt,
                              ಚಿಹ್ನೆರಹಿತ *lossp, ಚಿಹ್ನೆರಹಿತ consider)
{
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *src_desc = av_pix_fmt_desc_get(src_pix_fmt);
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *dst_desc = av_pix_fmt_desc_get(dst_pix_fmt);
    ಪೂರ್ಣಾಂಕ src_color, dst_color;
    ಪೂರ್ಣಾಂಕ src_min_ಆಳ, src_max_ಆಳ, dst_min_ಆಳ, dst_max_ಆಳ;
    ಪೂರ್ಣಾಂಕ ret, loss, i, nb_components;
    ಪೂರ್ಣಾಂಕ score = ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ - 1;

    ಆದರೆ (!src_desc || !dst_desc)
        ಹಿಂತಿರುಗಿ -4;

    ಆದರೆ ((src_desc->flags & AV_PIX_FMT_FLAG_HWACCEL) ||
        (dst_desc->flags & AV_PIX_FMT_FLAG_HWACCEL)) {
        ಆದರೆ (dst_pix_fmt == src_pix_fmt)
            ಹಿಂತಿರುಗಿ -1;
        ಇಲ್ಲದಿದ್ದರೆ
            ಹಿಂತಿರುಗಿ -2;
    }

    /* compute loss */
    *lossp = loss = 0;

    ಆದರೆ (dst_pix_fmt == src_pix_fmt)
        ಹಿಂತಿರುಗಿ ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ;

    ಆದರೆ ((ret = get_pix_fmt_ಆಳ(&src_min_ಆಳ, &src_max_ಆಳ, src_pix_fmt)) < 0)
        ಹಿಂತಿರುಗಿ -3;
    ಆದರೆ ((ret = get_pix_fmt_ಆಳ(&dst_min_ಆಳ, &dst_max_ಆಳ, dst_pix_fmt)) < 0)
        ಹಿಂತಿರುಗಿ -3;

    src_color = get_color_type(src_desc);
    dst_color = get_color_type(dst_desc);
    ಆದರೆ (dst_pix_fmt == AV_PIX_FMT_PAL8)
        nb_components = FFMIN(src_desc->nb_components, 4);
    ಇಲ್ಲದಿದ್ದರೆ
        nb_components = FFMIN(src_desc->nb_components, dst_desc->nb_components);

    ಗಾಗಿ (i = 0; i < nb_components; i++) {
        ಪೂರ್ಣಾಂಕ ಆಳ_minus1 = (dst_pix_fmt == AV_PIX_FMT_PAL8) ? 7/nb_components : (dst_desc->comp[i].ಆಳ - 1);
        ಪೂರ್ಣಾಂಕ ಆಳ_delta = src_desc->comp[i].ಆಳ - 1 - ಆಳ_minus1;
        ಆದರೆ (ಆಳ_delta > 0 && (consider & FF_LOSS_ಆಳ)) {
            loss |= FF_LOSS_ಆಳ;
            score -= 65536 >> ಆಳ_minus1;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಆಳ_delta < 0 && (consider & FF_LOSS_EXCESS_ಆಳ)) {
            // Favour formats where bit depth exactly matches. If all other
            // scoring is equal, we'd rather use the bit depth that most closely
            // matches the source.
            loss |= FF_LOSS_EXCESS_ಆಳ;
            score += ಆಳ_delta;
        }
    }

    ಆದರೆ (consider & FF_LOSS_RESOLUTION) {
        ಆದರೆ (dst_desc->log2_chroma_w > src_desc->log2_chroma_w) {
            loss |= FF_LOSS_RESOLUTION;
            score -= 256 << dst_desc->log2_chroma_w;
        }
        ಆದರೆ (dst_desc->log2_chroma_h > src_desc->log2_chroma_h) {
            loss |= FF_LOSS_RESOLUTION;
            score -= 256 << dst_desc->log2_chroma_h;
        }
        // don't favor 422 over 420 if downsampling is needed, because 420 has much better support on the decoder side
        ಆದರೆ (dst_desc->log2_chroma_w == 1 && src_desc->log2_chroma_w == 0 &&
            dst_desc->log2_chroma_h == 1 && src_desc->log2_chroma_h == 0 ) {
            score += 512;
        }
    }

    ಆದರೆ (consider & FF_LOSS_EXCESS_RESOLUTION) {
        // Favour formats where chroma subsampling exactly matches. If all other
        // scoring is equal, we'd rather use the subsampling that most closely
        // matches the source.
        ಆದರೆ (dst_desc->log2_chroma_w < src_desc->log2_chroma_w) {
            loss |= FF_LOSS_EXCESS_RESOLUTION;
            score -= 1 << (src_desc->log2_chroma_w - dst_desc->log2_chroma_w);
        }

        ಆದರೆ (dst_desc->log2_chroma_h < src_desc->log2_chroma_h) {
            loss |= FF_LOSS_EXCESS_RESOLUTION;
            score -= 1 << (src_desc->log2_chroma_h - dst_desc->log2_chroma_h);
        }

        // don't favour 411 over 420, because 420 has much better support on the
        // decoder side.
        ಆದರೆ (dst_desc->log2_chroma_w == 1 && src_desc->log2_chroma_w == 2 &&
            dst_desc->log2_chroma_h == 1 && src_desc->log2_chroma_h == 2) {
                score += 4;
            }
    }

    ಆದರೆ(consider & FF_LOSS_COLORSPACE)
    ಆಯ್ಕೆ(dst_color) {
    ಸ್ಥಿತಿ FF_COLOR_RGB:
        ಆದರೆ (src_color != FF_COLOR_RGB &&
            src_color != FF_COLOR_ಬೂದು)
            loss |= FF_LOSS_COLORSPACE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ FF_COLOR_ಬೂದು:
        ಆದರೆ (src_color != FF_COLOR_ಬೂದು)
            loss |= FF_LOSS_COLORSPACE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ FF_COLOR_YUV:
        ಆದರೆ (src_color != FF_COLOR_YUV)
            loss |= FF_LOSS_COLORSPACE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ FF_COLOR_YUV_JPEG:
        ಆದರೆ (src_color != FF_COLOR_YUV_JPEG &&
            src_color != FF_COLOR_YUV &&
            src_color != FF_COLOR_ಬೂದು)
            loss |= FF_LOSS_COLORSPACE;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        /* fail safe test */
        ಆದರೆ (src_color != dst_color)
            loss |= FF_LOSS_COLORSPACE;
        ನಿಲ್ಲಿಸು;
    }
    ಆದರೆ(loss & FF_LOSS_COLORSPACE)
        score -= (nb_components * 65536) >> FFMIN(dst_desc->comp[0].ಆಳ - 1, src_desc->comp[0].ಆಳ - 1);

    ಆದರೆ (dst_color == FF_COLOR_ಬೂದು &&
        src_color != FF_COLOR_ಬೂದು && (consider & FF_LOSS_CHROMA)) {
        loss |= FF_LOSS_CHROMA;
        score -= 2 * 65536;
    }
    ಆದರೆ (!pixdesc_has_alpha(dst_desc) && (pixdesc_has_alpha(src_desc) && (consider & FF_LOSS_ALPHA))) {
        loss |= FF_LOSS_ALPHA;
        score -= 65536;
    }
    ಆದರೆ (dst_pix_fmt == AV_PIX_FMT_PAL8 && (consider & FF_LOSS_COLORQUANT) &&
        (src_pix_fmt != AV_PIX_FMT_PAL8 && (src_color != FF_COLOR_ಬೂದು || (pixdesc_has_alpha(src_desc) && (consider & FF_LOSS_ALPHA))))) {
        loss |= FF_LOSS_COLORQUANT;
        score -= 65536;
    }

    *lossp = loss;
    ಹಿಂತಿರುಗಿ score;
}

ಪೂರ್ಣಾಂಕ av_get_pix_fmt_loss(ಎಣಿಕೆ AVPixelFormat dst_pix_fmt,
                            ಎಣಿಕೆ AVPixelFormat src_pix_fmt,
                            ಪೂರ್ಣಾಂಕ has_alpha)
{
    ಪೂರ್ಣಾಂಕ loss;
    ಪೂರ್ಣಾಂಕ ret = get_pix_fmt_score(dst_pix_fmt, src_pix_fmt, &loss, has_alpha ? ~0 : ~FF_LOSS_ALPHA);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;
    ಹಿಂತಿರುಗಿ loss;
}

ಎಣಿಕೆ AVPixelFormat av_ಕಂಡುಹಿಡಿ_ಉತ್ತಮ_pix_fmt_ದ_2(ಎಣಿಕೆ AVPixelFormat dst_pix_fmt1, ಎಣಿಕೆ AVPixelFormat dst_pix_fmt2,
                                             ಎಣಿಕೆ AVPixelFormat src_pix_fmt, ಪೂರ್ಣಾಂಕ has_alpha, ಪೂರ್ಣಾಂಕ *loss_ptr)
{
    ಎಣಿಕೆ AVPixelFormat dst_pix_fmt;
    ಪೂರ್ಣಾಂಕ loss1, loss2, loss_ಮುಖವಾಡ;
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc1 = av_pix_fmt_desc_get(dst_pix_fmt1);
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc2 = av_pix_fmt_desc_get(dst_pix_fmt2);
    ಪೂರ್ಣಾಂಕ score1, score2;

    ಆದರೆ (!desc1) {
        dst_pix_fmt = dst_pix_fmt2;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!desc2) {
        dst_pix_fmt = dst_pix_fmt1;
    } ಇಲ್ಲದಿದ್ದರೆ {
        loss_ಮುಖವಾಡ= loss_ptr?~*loss_ptr:~0; /* use loss mask if provided */
        ಆದರೆ(!has_alpha)
            loss_ಮುಖವಾಡ &= ~FF_LOSS_ALPHA;

        score1 = get_pix_fmt_score(dst_pix_fmt1, src_pix_fmt, &loss1, loss_ಮುಖವಾಡ);
        score2 = get_pix_fmt_score(dst_pix_fmt2, src_pix_fmt, &loss2, loss_ಮುಖವಾಡ);

        ಆದರೆ (score1 == score2) {
            ಆದರೆ(av_get_padded_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel(desc2) != av_get_padded_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel(desc1)) {
                dst_pix_fmt = av_get_padded_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel(desc2) < av_get_padded_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel(desc1) ? dst_pix_fmt2 : dst_pix_fmt1;
            } ಇಲ್ಲದಿದ್ದರೆ {
                dst_pix_fmt = desc2->nb_components < desc1->nb_components ? dst_pix_fmt2 : dst_pix_fmt1;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            dst_pix_fmt = score1 < score2 ? dst_pix_fmt2 : dst_pix_fmt1;
        }
    }

    ಆದರೆ (loss_ptr)
        *loss_ptr = av_get_pix_fmt_loss(dst_pix_fmt, src_pix_fmt, has_alpha);
    ಹಿಂತಿರುಗಿ dst_pix_fmt;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_color_range_name(ಎಣಿಕೆ AVColorRange range)
{
    ಹಿಂತಿರುಗಿ (ಚಿಹ್ನೆರಹಿತ) range < AVCOL_RANGE_NB ?
        color_range_ಹೆಸರುಗಳು[range] : ಖಾಲಿ;
}

ಪೂರ್ಣಾಂಕ av_color_range_from_name(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(color_range_ಹೆಸರುಗಳು); i++) {
        ಆದರೆ (!strcmp(name, color_range_ಹೆಸರುಗಳು[i]))
            ಹಿಂತಿರುಗಿ i;
    }

    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_color_primaries_name(ಎಣಿಕೆ AVColorPrimaries primaries)
{
    ಆದರೆ ((ಚಿಹ್ನೆರಹಿತ)primaries < AVCOL_PRI_NB)
        ಹಿಂತಿರುಗಿ color_primaries_ಹೆಸರುಗಳು[primaries];
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (((ಚಿಹ್ನೆರಹಿತ)primaries >= AVCOL_PRI_EXT_ತಳ) &&
             ((ಚಿಹ್ನೆರಹಿತ)primaries < AVCOL_PRI_EXT_NB))
        ಹಿಂತಿರುಗಿ color_primaries_ಹೆಸರುಗಳು_ext[primaries - AVCOL_TRC_EXT_ತಳ];
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಪೂರ್ಣಾಂಕ av_color_primaries_from_name(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(color_primaries_ಹೆಸರುಗಳು); i++) {
        ಆದರೆ (!color_primaries_ಹೆಸರುಗಳು[i])
            ಮುಂದುವರಿ;

        ಆದರೆ (!strcmp(name, color_primaries_ಹೆಸರುಗಳು[i]))
            ಹಿಂತಿರುಗಿ i;
    }

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(color_primaries_ಹೆಸರುಗಳು_ext); i++) {
        ಆದರೆ (!color_primaries_ಹೆಸರುಗಳು_ext[i])
            ಮುಂದುವರಿ;

        ಆದರೆ (!strcmp(name, color_primaries_ಹೆಸರುಗಳು_ext[i]))
            ಹಿಂತಿರುಗಿ AVCOL_PRI_EXT_ತಳ + i;
    }

    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_color_transfer_name(ಎಣಿಕೆ AVColorTransferCharacteristic transfer)
{
    ಆದರೆ ((ಚಿಹ್ನೆರಹಿತ)transfer < AVCOL_TRC_NB)
        ಹಿಂತಿರುಗಿ color_transfer_ಹೆಸರುಗಳು[transfer];
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (((ಚಿಹ್ನೆರಹಿತ)transfer >= AVCOL_TRC_EXT_ತಳ) &&
             ((ಚಿಹ್ನೆರಹಿತ)transfer < AVCOL_TRC_EXT_NB))
        ಹಿಂತಿರುಗಿ color_transfer_ಹೆಸರುಗಳು_ext[transfer - AVCOL_TRC_EXT_ತಳ];
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಪೂರ್ಣಾಂಕ av_color_transfer_from_name(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(color_transfer_ಹೆಸರುಗಳು); i++) {
        ಆದರೆ (!color_transfer_ಹೆಸರುಗಳು[i])
            ಮುಂದುವರಿ;

        ಆದರೆ (!strcmp(name, color_transfer_ಹೆಸರುಗಳು[i]))
            ಹಿಂತಿರುಗಿ i;
    }

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(color_transfer_ಹೆಸರುಗಳು_ext); i++) {
        ಆದರೆ (!color_transfer_ಹೆಸರುಗಳು_ext[i])
            ಮುಂದುವರಿ;

        ಆದರೆ (!strcmp(name, color_transfer_ಹೆಸರುಗಳು_ext[i]))
            ಹಿಂತಿರುಗಿ AVCOL_TRC_EXT_ತಳ + i;
    }

    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_color_space_name(ಎಣಿಕೆ AVColorSpace space)
{
    ಹಿಂತಿರುಗಿ (ಚಿಹ್ನೆರಹಿತ) space < AVCOL_SPC_NB ?
        color_space_ಹೆಸರುಗಳು[space] : ಖಾಲಿ;
}

ಪೂರ್ಣಾಂಕ av_color_space_from_name(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(color_space_ಹೆಸರುಗಳು); i++) {
        ಆದರೆ (!color_space_ಹೆಸರುಗಳು[i])
            ಮುಂದುವರಿ;

        ಆದರೆ (!strcmp(name, color_space_ಹೆಸರುಗಳು[i]))
            ಹಿಂತಿರುಗಿ i;
    }

    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_chroma_location_name(ಎಣಿಕೆ AVChromaLocation location)
{
    ಹಿಂತಿರುಗಿ (ಚಿಹ್ನೆರಹಿತ) location < AVCHROMA_LOC_NB ?
        chroma_location_ಹೆಸರುಗಳು[location] : ಖಾಲಿ;
}

ಪೂರ್ಣಾಂಕ av_chroma_location_from_name(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(chroma_location_ಹೆಸರುಗಳು); i++) {
        ಆದರೆ (!chroma_location_ಹೆಸರುಗಳು[i])
            ಮುಂದುವರಿ;

        ಆದರೆ (!strcmp(name, chroma_location_ಹೆಸರುಗಳು[i]))
            ಹಿಂತಿರುಗಿ i;
    }

    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}

ಪೂರ್ಣಾಂಕ av_chroma_location_enum_ಗಮ್ಯ_pos(ಪೂರ್ಣಾಂಕ *xpos, ಪೂರ್ಣಾಂಕ *ypos, ಎಣಿಕೆ AVChromaLocation pos)
{
    ಆದರೆ (pos <= AVCHROMA_LOC_UNSPECIFIED || pos >= AVCHROMA_LOC_NB)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    pos--;

    *xpos = (pos&1) * 128;
    *ypos = ((pos>>1)^(pos<4)) * 128;

    ಹಿಂತಿರುಗಿ 0;
}

ಎಣಿಕೆ AVChromaLocation av_chroma_location_pos_ಗಮ್ಯ_enum(ಪೂರ್ಣಾಂಕ xpos, ಪೂರ್ಣಾಂಕ ypos)
{
    ಪೂರ್ಣಾಂಕ pos, xout, yout;

    ಗಾಗಿ (pos = AVCHROMA_LOC_UNSPECIFIED + 1; pos < AVCHROMA_LOC_NB; pos++) {
        ಆದರೆ (av_chroma_location_enum_ಗಮ್ಯ_pos(&xout, &yout, pos) == 0 && xout == xpos && yout == ypos)
            ಹಿಂತಿರುಗಿ pos;
    }
    ಹಿಂತಿರುಗಿ AVCHROMA_LOC_UNSPECIFIED;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_alpha_ಬಹುಲಕ_name(ಎಣಿಕೆ AVAlpha_ಬಹುಲಕ ಬಹುಲಕ)
{
    ಹಿಂತಿರುಗಿ (ಚಿಹ್ನೆರಹಿತ) ಬಹುಲಕ < AVALPHA_ಬಹುಲಕ_NB ?
        alpha_ಬಹುಲಕ_ಹೆಸರುಗಳು[ಬಹುಲಕ] : ಖಾಲಿ;
}

ಎಣಿಕೆ AVAlpha_ಬಹುಲಕ av_alpha_ಬಹುಲಕ_from_name(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(alpha_ಬಹುಲಕ_ಹೆಸರುಗಳು); i++) {
        ಆದರೆ (!alpha_ಬಹುಲಕ_ಹೆಸರುಗಳು[i])
            ಮುಂದುವರಿ;

        ಆದರೆ (!strcmp(name, alpha_ಬಹುಲಕ_ಹೆಸರುಗಳು[i]))
            ಹಿಂತಿರುಗಿ i;
    }

    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}
