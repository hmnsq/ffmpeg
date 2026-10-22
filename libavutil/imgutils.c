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

/**
 * @file
 * misc image utilities
 */

#समावेश "avassert.h"
#समावेश "common.h"
#समावेश "imgutils.h"
#समावेश "imgutils_internal.h"
#समावेश "intreadwrite.h"
#समावेश "log.h"
#समावेश "mathematics.h"
#समावेश "mem.h"
#समावेश "pixdesc.h"
#समावेश "rational.h"

व्योम av_image_fill_max_pixsteps(पूर्णांक max_pixsteps[4], पूर्णांक max_pixstep_comps[4],
                                स्थिर AVPixFmtDescriptor *pixdesc)
{
    पूर्णांक i;
    स_रखो(max_pixsteps, 0, 4*माप(max_pixsteps[0]));
    अगर (max_pixstep_comps)
        स_रखो(max_pixstep_comps, 0, 4*माप(max_pixstep_comps[0]));

    क्रम (i = 0; i < 4; i++) {
        स्थिर AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        अगर (comp->step > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->step;
            अगर (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

अटल अंतरभूत
पूर्णांक image_get_linesize(पूर्णांक width, पूर्णांक plane,
                       पूर्णांक max_step, पूर्णांक max_step_comp,
                       स्थिर AVPixFmtDescriptor *desc)
{
    पूर्णांक s, shifted_w, linesize;

    अगर (!desc)
        वापस AVERROR(EINVAL);

    अगर (width < 0)
        वापस AVERROR(EINVAL);
    s = (max_step_comp == 1 || max_step_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(width, s);
    अगर (shifted_w && max_step > पूर्णांक_उच्च / shifted_w)
        वापस AVERROR(EINVAL);
    linesize = max_step * shifted_w;

    अगर (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    वापस linesize;
}

पूर्णांक av_image_get_linesize(क्रमागत AVPixelFormat pix_fmt, पूर्णांक width, पूर्णांक plane)
{
    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    पूर्णांक max_step     [4];       /* max pixel step for each plane */
    पूर्णांक max_step_comp[4];       /* the component for each plane which has the max pixel step */

    अगर (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        वापस AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    वापस image_get_linesize(width, plane, max_step[plane], max_step_comp[plane], desc);
}

पूर्णांक av_image_fill_linesizes(पूर्णांक linesizes[4], क्रमागत AVPixelFormat pix_fmt, पूर्णांक width)
{
    पूर्णांक i, ret;
    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    पूर्णांक max_step     [4];       /* max pixel step for each plane */
    पूर्णांक max_step_comp[4];       /* the component for each plane which has the max pixel step */

    स_रखो(linesizes, 0, 4*माप(linesizes[0]));

    अगर (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        वापस AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_step, max_step_comp, desc);
    क्रम (i = 0; i < 4; i++) {
        अगर ((ret = image_get_linesize(width, i, max_step[i], max_step_comp[i], desc)) < 0)
            वापस ret;
        linesizes[i] = ret;
    }

    वापस 0;
}

पूर्णांक av_image_fill_plane_sizes(माप_प्रकार sizes[4], क्रमागत AVPixelFormat pix_fmt,
                              पूर्णांक height, स्थिर सूचक_भेद_प्रकार linesizes[4])
{
    पूर्णांक i, has_plane[4] = { 0 };

    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    स_रखो(sizes    , 0, माप(sizes[0])*4);

    अगर (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        वापस AVERROR(EINVAL);

    अगर (linesizes[0] > SIZE_MAX / height)
        वापस AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (माप_प्रकार)height;

    अगर (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        वापस 0;
    }

    क्रम (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    क्रम (i = 1; i < 4 && has_plane[i]; i++) {
        पूर्णांक h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(height, s);
        अगर (linesizes[i] > SIZE_MAX / h)
            वापस AVERROR(EINVAL);
        sizes[i] = (माप_प्रकार)h * linesizes[i];
    }

    वापस 0;
}

पूर्णांक av_image_fill_pointers(uint8_t *तथ्य[4], क्रमागत AVPixelFormat pix_fmt, पूर्णांक height,
                           uint8_t *ptr, स्थिर पूर्णांक linesizes[4])
{
    पूर्णांक i, ret;
    सूचक_भेद_प्रकार linesizes1[4];
    माप_प्रकार sizes[4];

    स_रखो(तथ्य     , 0, माप(तथ्य[0])*4);

    क्रम (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, linesizes1);
    अगर (ret < 0)
        वापस ret;

    ret = 0;
    क्रम (i = 0; i < 4; i++) {
        अगर (sizes[i] > पूर्णांक_उच्च - ret)
            वापस AVERROR(EINVAL);
        ret += sizes[i];
    }

    अगर (!ptr)
        वापस ret;

    तथ्य[0] = ptr;
    क्रम (i = 1; i < 4 && sizes[i]; i++)
        तथ्य[i] = तथ्य[i - 1] + sizes[i - 1];

    वापस ret;
}

पूर्णांक avpriv_set_systematic_pal2(uint32_t pal[256], क्रमागत AVPixelFormat pix_fmt)
{
    पूर्णांक i;

    क्रम (i = 0; i < 256; i++) {
        पूर्णांक r, g, b;

        चयन (pix_fmt) {
        हाल AV_PIX_FMT_RGB8:
            r = (i>>5    )*36;
            g = ((i>>2)&7)*36;
            b = (i&3     )*85;
            अवरोध;
        हाल AV_PIX_FMT_BGR8:
            b = (i>>6    )*85;
            g = ((i>>3)&7)*36;
            r = (i&7     )*36;
            अवरोध;
        हाल AV_PIX_FMT_RGB4_BYTE:
            r = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            b = (i&1     )*255;
            अवरोध;
        हाल AV_PIX_FMT_BGR4_BYTE:
            b = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            r = (i&1     )*255;
            अवरोध;
        हाल AV_PIX_FMT_GRAY8:
            r = b = g = i;
            अवरोध;
        शेष:
            वापस AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    वापस 0;
}

पूर्णांक av_image_alloc(uint8_t *pointers[4], पूर्णांक linesizes[4],
                   पूर्णांक w, पूर्णांक h, क्रमागत AVPixelFormat pix_fmt, पूर्णांक align)
{
    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    पूर्णांक i, ret;
    सूचक_भेद_प्रकार linesizes1[4];
    माप_प्रकार योग_आकार, sizes[4];
    uint8_t *buf;

    अगर (!desc)
        वापस AVERROR(EINVAL);

    अगर ((ret = av_image_check_आकार(w, h, 0, शून्य)) < 0)
        वापस ret;
    अगर ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        वापस ret;

    क्रम (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    अगर ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        वापस ret;
    योग_आकार = align;
    क्रम (i = 0; i < 4; i++) {
        अगर (योग_आकार > SIZE_MAX - sizes[i])
            वापस AVERROR(EINVAL);
        योग_आकार += sizes[i];
    }
    buf = av_malloc(योग_आकार);
    अगर (!buf)
        वापस AVERROR(ENOMEM);
    अगर ((ret = av_image_fill_pointers(pointers, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        वापस ret;
    }
    अगर (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_set_systematic_pal2((uint32_t*)pointers[1], pix_fmt);
        अगर (align < 4) {
            av_log(शून्य, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            वापस AVERROR(EINVAL);
        }
    }

    अगर (desc->flags & AV_PIX_FMT_FLAG_PAL && pointers[1] &&
        pointers[1] - pointers[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        स_रखो(pointers[0] + linesizes[0] * h, 0,
               pointers[1] - pointers[0] - linesizes[0] * h);
    }

    वापस ret;
}

प्रकार काष्ठा ImgUtils {
    स्थिर AVClass *class;
    पूर्णांक   log_offset;
    व्योम *log_ctx;
} ImgUtils;

अटल स्थिर AVClass imgutils_class = {
    .class_name                = "IMGUTILS",
    .item_name                 = av_default_item_name,
    .option                    = शून्य,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = दुरत्व(ImgUtils, log_offset),
    .parent_log_context_offset = दुरत्व(ImgUtils, log_ctx),
};

पूर्णांक av_image_check_size2(अचिन्हित पूर्णांक w, अचिन्हित पूर्णांक h, int64_t max_pixels, क्रमागत AVPixelFormat pix_fmt, पूर्णांक log_offset, व्योम *log_ctx)
{
    ImgUtils imgutils = {
        .class      = &imgutils_class,
        .log_offset = log_offset,
        .log_ctx    = log_ctx,
    };
    int64_t stride = av_image_get_linesize(pix_fmt, w, 0);
    अगर (stride <= 0)
        stride = 8LL*w;
    stride += 128*8;

    अगर (w==0 || h==0 || w > INT32_MAX || h > INT32_MAX || stride >= पूर्णांक_उच्च || stride*(h + 128ULL) >= पूर्णांक_उच्च) {
        av_log(&imgutils, AV_LOG_ERROR, "Picture size %ux%u is invalid\n", w, h);
        वापस AVERROR(EINVAL);
    }

    अगर (max_pixels < INT64_MAX) {
        अगर (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            वापस AVERROR(EINVAL);
        }
    }

    वापस 0;
}

पूर्णांक av_image_check_आकार(अचिन्हित पूर्णांक w, अचिन्हित पूर्णांक h, पूर्णांक log_offset, व्योम *log_ctx)
{
    वापस av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_offset, log_ctx);
}

पूर्णांक av_image_check_sar(अचिन्हित पूर्णांक w, अचिन्हित पूर्णांक h, AVRational sar)
{
    int64_t scaled_dim;

    अगर (sar.den <= 0 || sar.अंक < 0)
        वापस AVERROR(EINVAL);

    अगर (!sar.अंक || sar.अंक == sar.den)
        वापस 0;

    अगर (sar.अंक < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.अंक, sar.den, AV_ROUND_ZERO);
    अन्यथा
        scaled_dim = av_rescale_rnd(h, sar.den, sar.अंक, AV_ROUND_ZERO);

    अगर (scaled_dim > 0)
        वापस 0;

    वापस AVERROR(EINVAL);
}

अटल व्योम image_copy_plane(uint8_t       *dst, सूचक_भेद_प्रकार dst_linesize,
                             स्थिर uint8_t *src, सूचक_भेद_प्रकार src_linesize,
                             सूचक_भेद_प्रकार bytewidth, पूर्णांक height)
{
    अगर (!dst || !src)
        वापस;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    क्रम (;height > 0; height--) {
        स_नकल(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

व्योम av_image_copy_plane_uc_from(uint8_t *dst, सूचक_भेद_प्रकार dst_linesize,
                                 स्थिर uint8_t *src, सूचक_भेद_प्रकार src_linesize,
                                 सूचक_भेद_प्रकार bytewidth, पूर्णांक height)
{
    पूर्णांक ret = -1;

#अगर ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, height);
#पूर्ण_अगर

    अगर (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

व्योम av_image_copy_plane(uint8_t       *dst, पूर्णांक dst_linesize,
                         स्थिर uint8_t *src, पूर्णांक src_linesize,
                         पूर्णांक bytewidth, पूर्णांक height)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, height);
}

अटल व्योम image_copy(uint8_t *स्थिर dst_तथ्य[4], स्थिर सूचक_भेद_प्रकार dst_linesizes[4],
                       स्थिर uint8_t *स्थिर src_तथ्य[4], स्थिर सूचक_भेद_प्रकार src_linesizes[4],
                       क्रमागत AVPixelFormat pix_fmt, पूर्णांक width, पूर्णांक height,
                       व्योम (*copy_plane)(uint8_t *, सूचक_भेद_प्रकार, स्थिर uint8_t *,
                                          सूचक_भेद_प्रकार, सूचक_भेद_प्रकार, पूर्णांक))
{
    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    अगर (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        वापस;

    अगर (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_तथ्य[0], dst_linesizes[0],
                   src_तथ्य[0], src_linesizes[0],
                   width, height);
        /* copy the palette */
        अगर ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_तथ्य[1] && src_तथ्य[1]))
            स_नकल(dst_तथ्य[1], src_तथ्य[1], 4*256);
    } अन्यथा {
        पूर्णांक i, planes_nb = 0;

        क्रम (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        क्रम (i = 0; i < planes_nb; i++) {
            पूर्णांक h = height;
            सूचक_भेद_प्रकार bwidth = av_image_get_linesize(pix_fmt, width, i);
            अगर (bwidth < 0) {
                av_log(शून्य, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                वापस;
            }
            अगर (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(height, desc->log2_chroma_h);
            }
            copy_plane(dst_तथ्य[i], dst_linesizes[i],
                       src_तथ्य[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

व्योम av_image_copy(uint8_t *स्थिर dst_तथ्य[4], स्थिर पूर्णांक dst_linesizes[4],
                   स्थिर uint8_t * स्थिर src_तथ्य[4], स्थिर पूर्णांक src_linesizes[4],
                   क्रमागत AVPixelFormat pix_fmt, पूर्णांक width, पूर्णांक height)
{
    सूचक_भेद_प्रकार dst_linesizes1[4], src_linesizes1[4];
    पूर्णांक i;

    क्रम (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_तथ्य, dst_linesizes1, src_तथ्य, src_linesizes1, pix_fmt,
               width, height, image_copy_plane);
}

व्योम av_image_copy_uc_from(uint8_t * स्थिर dst_तथ्य[4], स्थिर सूचक_भेद_प्रकार dst_linesizes[4],
                           स्थिर uint8_t * स्थिर src_तथ्य[4], स्थिर सूचक_भेद_प्रकार src_linesizes[4],
                           क्रमागत AVPixelFormat pix_fmt, पूर्णांक width, पूर्णांक height)
{
    image_copy(dst_तथ्य, dst_linesizes, src_तथ्य, src_linesizes, pix_fmt,
               width, height, av_image_copy_plane_uc_from);
}

पूर्णांक av_image_fill_arrays(uint8_t *dst_तथ्य[4], पूर्णांक dst_linesize[4],
                         स्थिर uint8_t *src, क्रमागत AVPixelFormat pix_fmt,
                         पूर्णांक width, पूर्णांक height, पूर्णांक align)
{
    पूर्णांक ret, i;

    ret = av_image_check_आकार(width, height, 0, शून्य);
    अगर (ret < 0)
        वापस ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, width);
    अगर (ret < 0)
        वापस ret;

    क्रम (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    वापस av_image_fill_pointers(dst_तथ्य, pix_fmt, height, (uint8_t *)src, dst_linesize);
}

पूर्णांक av_image_get_बफर_आकार(क्रमागत AVPixelFormat pix_fmt,
                             पूर्णांक width, पूर्णांक height, पूर्णांक align)
{
    पूर्णांक ret, i;
    पूर्णांक linesize[4];
    सूचक_भेद_प्रकार aligned_linesize[4];
    माप_प्रकार sizes[4];
    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    अगर (!desc)
        वापस AVERROR(EINVAL);

    ret = av_image_check_आकार(width, height, 0, शून्य);
    अगर (ret < 0)
        वापस ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    अगर (ret < 0)
        वापस ret;

    क्रम (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, height, aligned_linesize);
    अगर (ret < 0)
        वापस ret;

    ret = 0;
    क्रम (i = 0; i < 4; i++) {
        अगर (sizes[i] > पूर्णांक_उच्च - ret)
            वापस AVERROR(EINVAL);
        ret += sizes[i];
    }
    वापस ret;
}

पूर्णांक av_image_copy_to_बफर(uint8_t *dst, पूर्णांक dst_आकार,
                            स्थिर uint8_t * स्थिर src_तथ्य[4],
                            स्थिर पूर्णांक src_linesize[4],
                            क्रमागत AVPixelFormat pix_fmt,
                            पूर्णांक width, पूर्णांक height, पूर्णांक align)
{
    पूर्णांक i, j, nb_planes = 0, linesize[4];
    पूर्णांक आकार = av_image_get_बफर_आकार(pix_fmt, width, height, align);
    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    पूर्णांक ret;

    अगर (आकार > dst_आकार || आकार < 0 || !desc)
        वापस AVERROR(EINVAL);

    क्रम (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, width);
    av_assert0(ret >= 0); // was checked previously

    क्रम (i = 0; i < nb_planes; i++) {
        पूर्णांक h, shift = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        स्थिर uint8_t *src = src_तथ्य[i];
        h = AV_CEIL_RSHIFT(height, shift);

        क्रम (j = 0; j < h; j++) {
            स_नकल(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    अगर (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        क्रम (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_तथ्य[1] + 4*i));
    }

    वापस आकार;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
अटल व्योम memset_bytes(uint8_t *dst, माप_प्रकार dst_आकार, uint8_t *clear,
                         माप_प्रकार clear_आकार)
{
    पूर्णांक same = 1;
    पूर्णांक i;

    अगर (!clear_आकार)
        वापस;

    // Reduce to memset() if possible.
    क्रम (i = 0; i < clear_आकार; i++) {
        अगर (clear[i] != clear[0]) {
            same = 0;
            अवरोध;
        }
    }
    अगर (same)
        clear_आकार = 1;

    अगर (clear_आकार == 1) {
        स_रखो(dst, clear[0], dst_आकार);
    } अन्यथा {
        अगर (clear_आकार > dst_आकार)
            clear_आकार = dst_आकार;
        स_नकल(dst, clear, clear_आकार);
        av_memcpy_backptr(dst + clear_आकार, clear_आकार, dst_आकार - clear_आकार);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#घोषणा MAX_BLOCK_आकार 32

पूर्णांक av_image_fill_color(uint8_t * स्थिर dst_तथ्य[4], स्थिर सूचक_भेद_प्रकार dst_linesize[4],
                        क्रमागत AVPixelFormat pix_fmt, स्थिर uint32_t color[4],
                        पूर्णांक width, पूर्णांक height, पूर्णांक flags)
{
    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    पूर्णांक nb_planes = av_pix_fmt_गिनती_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_block[4][MAX_BLOCK_आकार] = {{0}}; // clear padding with 0
    पूर्णांक clear_block_आकार[4] = {0};
    सूचक_भेद_प्रकार plane_पंक्ति_bytes[4] = {0};
    पूर्णांक bitstream;
    पूर्णांक plane, c;

    अगर (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        वापस AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    क्रम (c = 0; c < desc->nb_components; c++) {
        स्थिर AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_block_आकार[comp.plane] = FFMAX(clear_block_आकार[comp.plane], comp.step);

        अगर (clear_block_आकार[comp.plane] > MAX_BLOCK_आकार)
            वापस AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    क्रम (c = 0; c < desc->nb_components; c++) {
        स्थिर AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        पूर्णांक w = (bitstream ? 8 : 1) * clear_block_आकार[comp.plane] / comp.step;
        uint8_t *c_तथ्य[4];
        स्थिर पूर्णांक c_linesize[4] = {0};
        uint32_t src_array[MAX_BLOCK_आकार];
        पूर्णांक x;

        अगर (comp.depth > 32)
            वापस AVERROR(EINVAL);
        अगर (w < 1)
            वापस AVERROR(EINVAL);

        क्रम (x = 0; x < w; x++)
            src_array[x] = color[c];

        क्रम (x = 0; x < 4; x++)
            c_तथ्य[x] = &clear_block[x][0];

        av_write_image_line2(src_array, c_तथ्य, c_linesize, desc, 0, 0, c, w, 4);
    }

    क्रम (plane = 0; plane < nb_planes; plane++) {
        plane_पंक्ति_bytes[plane] = av_image_get_linesize(pix_fmt, width, plane);
        अगर (plane_पंक्ति_bytes[plane] < 0)
            वापस AVERROR(EINVAL);
    }

    अगर (!dst_तथ्य)
        वापस 0;

    क्रम (plane = 0; plane < nb_planes; plane++) {
        माप_प्रकार bytewidth = plane_पंक्ति_bytes[plane];
        uint8_t *तथ्य = dst_तथ्य[plane];
        पूर्णांक chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        पूर्णांक plane_h = AV_CEIL_RSHIFT(height, chroma_div);

        क्रम (; plane_h > 0; plane_h--) {
            memset_bytes(तथ्य, bytewidth, &clear_block[plane][0], clear_block_आकार[plane]);
            तथ्य += dst_linesize[plane];
        }
    }

    वापस 0;
}

पूर्णांक av_image_fill_black(uint8_t * स्थिर dst_तथ्य[4], स्थिर सूचक_भेद_प्रकार dst_linesize[4],
                        क्रमागत AVPixelFormat pix_fmt, क्रमागत AVColorRange range,
                        पूर्णांक width, पूर्णांक height)
{
    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    पूर्णांक nb_planes = av_pix_fmt_गिनती_planes(pix_fmt);
    पूर्णांक rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    अगर (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        वापस AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    क्रम (पूर्णांक c = 0; c < desc->nb_components; c++) {
        स्थिर AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        अगर (comp.depth > 32)
            वापस AVERROR(EINVAL);

        अगर (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } अन्यथा अगर (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            अगर (fltp) {
                अगर (comp.depth != 16 && comp.depth != 32)
                    वापस AVERROR(EINVAL);
                color = (comp.depth == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } अन्यथा {
                color = (comp.depth == 32 ? 0 : (1 << comp.depth)) - 1;
             }
        } अन्यथा अगर (c == 0 && limited && comp.depth > 1) {
            अगर (comp.depth < 8 || (fltp && comp.depth != 16 && comp.depth != 32))
                वापस AVERROR(EINVAL);
            अगर (fltp)
                color = (comp.depth == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            अन्यथा
                color = 16 << (comp.depth - 8);
        } अन्यथा अगर ((c == 1 || c == 2) && !rgb && !xyz) {
            अगर (comp.depth < 8 || fltp && comp.depth != 16 && comp.depth != 32)
                वापस AVERROR(EINVAL);
            अगर (fltp)
                color = (comp.depth == 16 ? 0x3800 : 0x3F000000); // 0.5
            अन्यथा
                color = 128 << (comp.depth - 8);
        }

        colors[c] = color;
    }

    वापस av_image_fill_color(dst_तथ्य, dst_linesize, pix_fmt, colors, width, height, 0);
}
