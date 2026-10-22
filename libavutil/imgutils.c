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

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "common.h"
#అన్తర్భావ "imgutils.h"
#అన్తర్భావ "imgutils_internal.h"
#అన్తర్భావ "intreadwrite.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "mathematics.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "pixdesc.h"
#అన్తర్భావ "rational.h"

శూన్య av_image_fill_max_pixsteps(పూర్ణాంకం max_pixsteps[4], పూర్ణాంకం max_pixstep_comps[4],
                                స్థిరరాశి AVPixFmtDescriptor *pixdesc)
{
    పూర్ణాంకం i;
    memset(max_pixsteps, 0, 4*పరిమాణం(max_pixsteps[0]));
    ఒకవేళ (max_pixstep_comps)
        memset(max_pixstep_comps, 0, 4*పరిమాణం(max_pixstep_comps[0]));

    కొరకు (i = 0; i < 4; i++) {
        స్థిరరాశి AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        ఒకవేళ (comp->అడుగు > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->అడుగు;
            ఒకవేళ (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

స్థిర అంతఃవరుస
పూర్ణాంకం image_get_linesize(పూర్ణాంకం వెడల్పు, పూర్ణాంకం plane,
                       పూర్ణాంకం max_అడుగు, పూర్ణాంకం max_అడుగు_comp,
                       స్థిరరాశి AVPixFmtDescriptor *desc)
{
    పూర్ణాంకం s, shifted_w, linesize;

    ఒకవేళ (!desc)
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ (వెడల్పు < 0)
        తిరిగి AVERROR(EINVAL);
    s = (max_అడుగు_comp == 1 || max_అడుగు_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(వెడల్పు, s);
    ఒకవేళ (shifted_w && max_అడుగు > గరిష్ఠ_పూర్ణాంకం / shifted_w)
        తిరిగి AVERROR(EINVAL);
    linesize = max_అడుగు * shifted_w;

    ఒకవేళ (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    తిరిగి linesize;
}

పూర్ణాంకం av_image_get_linesize(గణన AVPixelFormat pix_fmt, పూర్ణాంకం వెడల్పు, పూర్ణాంకం plane)
{
    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    పూర్ణాంకం max_అడుగు     [4];       /* max pixel step for each plane */
    పూర్ణాంకం max_అడుగు_comp[4];       /* the component for each plane which has the max pixel step */

    ఒకవేళ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        తిరిగి AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_అడుగు, max_అడుగు_comp, desc);
    తిరిగి image_get_linesize(వెడల్పు, plane, max_అడుగు[plane], max_అడుగు_comp[plane], desc);
}

పూర్ణాంకం av_image_fill_linesizes(పూర్ణాంకం linesizes[4], గణన AVPixelFormat pix_fmt, పూర్ణాంకం వెడల్పు)
{
    పూర్ణాంకం i, ret;
    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    పూర్ణాంకం max_అడుగు     [4];       /* max pixel step for each plane */
    పూర్ణాంకం max_అడుగు_comp[4];       /* the component for each plane which has the max pixel step */

    memset(linesizes, 0, 4*పరిమాణం(linesizes[0]));

    ఒకవేళ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        తిరిగి AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_అడుగు, max_అడుగు_comp, desc);
    కొరకు (i = 0; i < 4; i++) {
        ఒకవేళ ((ret = image_get_linesize(వెడల్పు, i, max_అడుగు[i], max_అడుగు_comp[i], desc)) < 0)
            తిరిగి ret;
        linesizes[i] = ret;
    }

    తిరిగి 0;
}

పూర్ణాంకం av_image_fill_plane_sizes(size_t sizes[4], గణన AVPixelFormat pix_fmt,
                              పూర్ణాంకం ఎత్తు, స్థిరరాశి ptrdiff_t linesizes[4])
{
    పూర్ణాంకం i, has_plane[4] = { 0 };

    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    memset(sizes    , 0, పరిమాణం(sizes[0])*4);

    ఒకవేళ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ (linesizes[0] > SIZE_MAX / ఎత్తు)
        తిరిగి AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (size_t)ఎత్తు;

    ఒకవేళ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        తిరిగి 0;
    }

    కొరకు (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    కొరకు (i = 1; i < 4 && has_plane[i]; i++) {
        పూర్ణాంకం h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(ఎత్తు, s);
        ఒకవేళ (linesizes[i] > SIZE_MAX / h)
            తిరిగి AVERROR(EINVAL);
        sizes[i] = (size_t)h * linesizes[i];
    }

    తిరిగి 0;
}

పూర్ణాంకం av_image_fill_సూచికలు(uint8_t *దత్తాంశం[4], గణన AVPixelFormat pix_fmt, పూర్ణాంకం ఎత్తు,
                           uint8_t *ptr, స్థిరరాశి పూర్ణాంకం linesizes[4])
{
    పూర్ణాంకం i, ret;
    ptrdiff_t linesizes1[4];
    size_t sizes[4];

    memset(దత్తాంశం     , 0, పరిమాణం(దత్తాంశం[0])*4);

    కొరకు (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, ఎత్తు, linesizes1);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    ret = 0;
    కొరకు (i = 0; i < 4; i++) {
        ఒకవేళ (sizes[i] > గరిష్ఠ_పూర్ణాంకం - ret)
            తిరిగి AVERROR(EINVAL);
        ret += sizes[i];
    }

    ఒకవేళ (!ptr)
        తిరిగి ret;

    దత్తాంశం[0] = ptr;
    కొరకు (i = 1; i < 4 && sizes[i]; i++)
        దత్తాంశం[i] = దత్తాంశం[i - 1] + sizes[i - 1];

    తిరిగి ret;
}

పూర్ణాంకం avpriv_సమితి_systematic_pal2(uint32_t pal[256], గణన AVPixelFormat pix_fmt)
{
    పూర్ణాంకం i;

    కొరకు (i = 0; i < 256; i++) {
        పూర్ణాంకం r, g, b;

        ఎంపిక (pix_fmt) {
        స్థితి AV_PIX_FMT_RGB8:
            r = (i>>5    )*36;
            g = ((i>>2)&7)*36;
            b = (i&3     )*85;
            ఆపు;
        స్థితి AV_PIX_FMT_BGR8:
            b = (i>>6    )*85;
            g = ((i>>3)&7)*36;
            r = (i&7     )*36;
            ఆపు;
        స్థితి AV_PIX_FMT_RGB4_BYTE:
            r = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            b = (i&1     )*255;
            ఆపు;
        స్థితి AV_PIX_FMT_BGR4_BYTE:
            b = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            r = (i&1     )*255;
            ఆపు;
        స్థితి AV_PIX_FMT_GRAY8:
            r = b = g = i;
            ఆపు;
        అప్రమేయ:
            తిరిగి AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    తిరిగి 0;
}

పూర్ణాంకం av_image_alloc(uint8_t *సూచికలు[4], పూర్ణాంకం linesizes[4],
                   పూర్ణాంకం w, పూర్ణాంకం h, గణన AVPixelFormat pix_fmt, పూర్ణాంకం align)
{
    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    పూర్ణాంకం i, ret;
    ptrdiff_t linesizes1[4];
    size_t మొత్తం_కొలత, sizes[4];
    uint8_t *buf;

    ఒకవేళ (!desc)
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ ((ret = av_image_check_కొలత(w, h, 0, ఖాళీ)) < 0)
        తిరిగి ret;
    ఒకవేళ ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        తిరిగి ret;

    కొరకు (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    ఒకవేళ ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        తిరిగి ret;
    మొత్తం_కొలత = align;
    కొరకు (i = 0; i < 4; i++) {
        ఒకవేళ (మొత్తం_కొలత > SIZE_MAX - sizes[i])
            తిరిగి AVERROR(EINVAL);
        మొత్తం_కొలత += sizes[i];
    }
    buf = av_malloc(మొత్తం_కొలత);
    ఒకవేళ (!buf)
        తిరిగి AVERROR(ENOMEM);
    ఒకవేళ ((ret = av_image_fill_సూచికలు(సూచికలు, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        తిరిగి ret;
    }
    ఒకవేళ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_సమితి_systematic_pal2((uint32_t*)సూచికలు[1], pix_fmt);
        ఒకవేళ (align < 4) {
            av_log(ఖాళీ, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            తిరిగి AVERROR(EINVAL);
        }
    }

    ఒకవేళ (desc->flags & AV_PIX_FMT_FLAG_PAL && సూచికలు[1] &&
        సూచికలు[1] - సూచికలు[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        memset(సూచికలు[0] + linesizes[0] * h, 0,
               సూచికలు[1] - సూచికలు[0] - linesizes[0] * h);
    }

    తిరిగి ret;
}

రకనిర్వచనం నిర్మాణం ImgUtils {
    స్థిరరాశి AVClass *class;
    పూర్ణాంకం   log_స్థానభ్రంశం;
    శూన్య *log_ctx;
} ImgUtils;

స్థిర స్థిరరాశి AVClass imgutils_class = {
    .class_name                = "IMGUTILS",
    .అంశం_name                 = av_default_అంశం_name,
    .option                    = ఖాళీ,
    .సంస్కరణ                   = LIBAVUTIL_సంస్కరణ_INT,
    .log_level_స్థానభ్రంశం_స్థానభ్రంశం   = offsetof(ImgUtils, log_స్థానభ్రంశం),
    .మాతృ_log_context_స్థానభ్రంశం = offsetof(ImgUtils, log_ctx),
};

పూర్ణాంకం av_image_check_size2(గుర్తులేని పూర్ణాంకం w, గుర్తులేని పూర్ణాంకం h, int64_t max_pixels, గణన AVPixelFormat pix_fmt, పూర్ణాంకం log_స్థానభ్రంశం, శూన్య *log_ctx)
{
    ImgUtils imgutils = {
        .class      = &imgutils_class,
        .log_స్థానభ్రంశం = log_స్థానభ్రంశం,
        .log_ctx    = log_ctx,
    };
    int64_t stride = av_image_get_linesize(pix_fmt, w, 0);
    ఒకవేళ (stride <= 0)
        stride = 8LL*w;
    stride += 128*8;

    ఒకవేళ (w==0 || h==0 || w > INT32_MAX || h > INT32_MAX || stride >= గరిష్ఠ_పూర్ణాంకం || stride*(h + 128ULL) >= గరిష్ఠ_పూర్ణాంకం) {
        av_log(&imgutils, AV_LOG_ERROR, "Picture size %ux%u is invalid\n", w, h);
        తిరిగి AVERROR(EINVAL);
    }

    ఒకవేళ (max_pixels < INT64_MAX) {
        ఒకవేళ (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            తిరిగి AVERROR(EINVAL);
        }
    }

    తిరిగి 0;
}

పూర్ణాంకం av_image_check_కొలత(గుర్తులేని పూర్ణాంకం w, గుర్తులేని పూర్ణాంకం h, పూర్ణాంకం log_స్థానభ్రంశం, శూన్య *log_ctx)
{
    తిరిగి av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_స్థానభ్రంశం, log_ctx);
}

పూర్ణాంకం av_image_check_sar(గుర్తులేని పూర్ణాంకం w, గుర్తులేని పూర్ణాంకం h, AVRational sar)
{
    int64_t scaled_dim;

    ఒకవేళ (sar.den <= 0 || sar.అంకె < 0)
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ (!sar.అంకె || sar.అంకె == sar.den)
        తిరిగి 0;

    ఒకవేళ (sar.అంకె < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.అంకె, sar.den, AV_విడత_ZERO);
    లేకపోతే
        scaled_dim = av_rescale_rnd(h, sar.den, sar.అంకె, AV_విడత_ZERO);

    ఒకవేళ (scaled_dim > 0)
        తిరిగి 0;

    తిరిగి AVERROR(EINVAL);
}

స్థిర శూన్య image_copy_plane(uint8_t       *dst, ptrdiff_t dst_linesize,
                             స్థిరరాశి uint8_t *src, ptrdiff_t src_linesize,
                             ptrdiff_t bytewidth, పూర్ణాంకం ఎత్తు)
{
    ఒకవేళ (!dst || !src)
        తిరిగి;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    కొరకు (;ఎత్తు > 0; ఎత్తు--) {
        జ్ఞాపకం_నకలు(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

శూన్య av_image_copy_plane_uc_from(uint8_t *dst, ptrdiff_t dst_linesize,
                                 స్థిరరాశి uint8_t *src, ptrdiff_t src_linesize,
                                 ptrdiff_t bytewidth, పూర్ణాంకం ఎత్తు)
{
    పూర్ణాంకం ret = -1;

#ఒకవేళ ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, ఎత్తు);
#అయితే_ముగింపు

    ఒకవేళ (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, ఎత్తు);
}

శూన్య av_image_copy_plane(uint8_t       *dst, పూర్ణాంకం dst_linesize,
                         స్థిరరాశి uint8_t *src, పూర్ణాంకం src_linesize,
                         పూర్ణాంకం bytewidth, పూర్ణాంకం ఎత్తు)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, ఎత్తు);
}

స్థిర శూన్య image_copy(uint8_t *స్థిరరాశి dst_దత్తాంశం[4], స్థిరరాశి ptrdiff_t dst_linesizes[4],
                       స్థిరరాశి uint8_t *స్థిరరాశి src_దత్తాంశం[4], స్థిరరాశి ptrdiff_t src_linesizes[4],
                       గణన AVPixelFormat pix_fmt, పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు,
                       శూన్య (*copy_plane)(uint8_t *, ptrdiff_t, స్థిరరాశి uint8_t *,
                                          ptrdiff_t, ptrdiff_t, పూర్ణాంకం))
{
    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    ఒకవేళ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        తిరిగి;

    ఒకవేళ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_దత్తాంశం[0], dst_linesizes[0],
                   src_దత్తాంశం[0], src_linesizes[0],
                   వెడల్పు, ఎత్తు);
        /* copy the palette */
        ఒకవేళ ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_దత్తాంశం[1] && src_దత్తాంశం[1]))
            జ్ఞాపకం_నకలు(dst_దత్తాంశం[1], src_దత్తాంశం[1], 4*256);
    } లేకపోతే {
        పూర్ణాంకం i, planes_nb = 0;

        కొరకు (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        కొరకు (i = 0; i < planes_nb; i++) {
            పూర్ణాంకం h = ఎత్తు;
            ptrdiff_t bwidth = av_image_get_linesize(pix_fmt, వెడల్పు, i);
            ఒకవేళ (bwidth < 0) {
                av_log(ఖాళీ, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                తిరిగి;
            }
            ఒకవేళ (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(ఎత్తు, desc->log2_chroma_h);
            }
            copy_plane(dst_దత్తాంశం[i], dst_linesizes[i],
                       src_దత్తాంశం[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

శూన్య av_image_copy(uint8_t *స్థిరరాశి dst_దత్తాంశం[4], స్థిరరాశి పూర్ణాంకం dst_linesizes[4],
                   స్థిరరాశి uint8_t * స్థిరరాశి src_దత్తాంశం[4], స్థిరరాశి పూర్ణాంకం src_linesizes[4],
                   గణన AVPixelFormat pix_fmt, పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు)
{
    ptrdiff_t dst_linesizes1[4], src_linesizes1[4];
    పూర్ణాంకం i;

    కొరకు (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_దత్తాంశం, dst_linesizes1, src_దత్తాంశం, src_linesizes1, pix_fmt,
               వెడల్పు, ఎత్తు, image_copy_plane);
}

శూన్య av_image_copy_uc_from(uint8_t * స్థిరరాశి dst_దత్తాంశం[4], స్థిరరాశి ptrdiff_t dst_linesizes[4],
                           స్థిరరాశి uint8_t * స్థిరరాశి src_దత్తాంశం[4], స్థిరరాశి ptrdiff_t src_linesizes[4],
                           గణన AVPixelFormat pix_fmt, పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు)
{
    image_copy(dst_దత్తాంశం, dst_linesizes, src_దత్తాంశం, src_linesizes, pix_fmt,
               వెడల్పు, ఎత్తు, av_image_copy_plane_uc_from);
}

పూర్ణాంకం av_image_fill_arrays(uint8_t *dst_దత్తాంశం[4], పూర్ణాంకం dst_linesize[4],
                         స్థిరరాశి uint8_t *src, గణన AVPixelFormat pix_fmt,
                         పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, పూర్ణాంకం align)
{
    పూర్ణాంకం ret, i;

    ret = av_image_check_కొలత(వెడల్పు, ఎత్తు, 0, ఖాళీ);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, వెడల్పు);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    కొరకు (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    తిరిగి av_image_fill_సూచికలు(dst_దత్తాంశం, pix_fmt, ఎత్తు, (uint8_t *)src, dst_linesize);
}

పూర్ణాంకం av_image_get_బఫరు_కొలత(గణన AVPixelFormat pix_fmt,
                             పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, పూర్ణాంకం align)
{
    పూర్ణాంకం ret, i;
    పూర్ణాంకం linesize[4];
    ptrdiff_t aligned_linesize[4];
    size_t sizes[4];
    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ఒకవేళ (!desc)
        తిరిగి AVERROR(EINVAL);

    ret = av_image_check_కొలత(వెడల్పు, ఎత్తు, 0, ఖాళీ);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, వెడల్పు);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    కొరకు (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, ఎత్తు, aligned_linesize);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    ret = 0;
    కొరకు (i = 0; i < 4; i++) {
        ఒకవేళ (sizes[i] > గరిష్ఠ_పూర్ణాంకం - ret)
            తిరిగి AVERROR(EINVAL);
        ret += sizes[i];
    }
    తిరిగి ret;
}

పూర్ణాంకం av_image_copy_గమ్యం_బఫరు(uint8_t *dst, పూర్ణాంకం dst_కొలత,
                            స్థిరరాశి uint8_t * స్థిరరాశి src_దత్తాంశం[4],
                            స్థిరరాశి పూర్ణాంకం src_linesize[4],
                            గణన AVPixelFormat pix_fmt,
                            పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, పూర్ణాంకం align)
{
    పూర్ణాంకం i, j, nb_planes = 0, linesize[4];
    పూర్ణాంకం కొలత = av_image_get_బఫరు_కొలత(pix_fmt, వెడల్పు, ఎత్తు, align);
    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    పూర్ణాంకం ret;

    ఒకవేళ (కొలత > dst_కొలత || కొలత < 0 || !desc)
        తిరిగి AVERROR(EINVAL);

    కొరకు (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, వెడల్పు);
    av_assert0(ret >= 0); // was checked previously

    కొరకు (i = 0; i < nb_planes; i++) {
        పూర్ణాంకం h, జరుపు = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        స్థిరరాశి uint8_t *src = src_దత్తాంశం[i];
        h = AV_CEIL_RSHIFT(ఎత్తు, జరుపు);

        కొరకు (j = 0; j < h; j++) {
            జ్ఞాపకం_నకలు(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    ఒకవేళ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        కొరకు (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_దత్తాంశం[1] + 4*i));
    }

    తిరిగి కొలత;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
స్థిర శూన్య memset_బైట్లు(uint8_t *dst, size_t dst_కొలత, uint8_t *clear,
                         size_t clear_కొలత)
{
    పూర్ణాంకం same = 1;
    పూర్ణాంకం i;

    ఒకవేళ (!clear_కొలత)
        తిరిగి;

    // Reduce to memset() if possible.
    కొరకు (i = 0; i < clear_కొలత; i++) {
        ఒకవేళ (clear[i] != clear[0]) {
            same = 0;
            ఆపు;
        }
    }
    ఒకవేళ (same)
        clear_కొలత = 1;

    ఒకవేళ (clear_కొలత == 1) {
        memset(dst, clear[0], dst_కొలత);
    } లేకపోతే {
        ఒకవేళ (clear_కొలత > dst_కొలత)
            clear_కొలత = dst_కొలత;
        జ్ఞాపకం_నకలు(dst, clear, clear_కొలత);
        av_memcpy_backptr(dst + clear_కొలత, clear_కొలత, dst_కొలత - clear_కొలత);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#నిర్వచించు MAX_ఖండం_కొలత 32

పూర్ణాంకం av_image_fill_color(uint8_t * స్థిరరాశి dst_దత్తాంశం[4], స్థిరరాశి ptrdiff_t dst_linesize[4],
                        గణన AVPixelFormat pix_fmt, స్థిరరాశి uint32_t color[4],
                        పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు, పూర్ణాంకం flags)
{
    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    పూర్ణాంకం nb_planes = av_pix_fmt_లెక్క_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_ఖండం[4][MAX_ఖండం_కొలత] = {{0}}; // clear padding with 0
    పూర్ణాంకం clear_ఖండం_కొలత[4] = {0};
    ptrdiff_t plane_పంక్తి_బైట్లు[4] = {0};
    పూర్ణాంకం bitstream;
    పూర్ణాంకం plane, c;

    ఒకవేళ (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        తిరిగి AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    కొరకు (c = 0; c < desc->nb_components; c++) {
        స్థిరరాశి AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_ఖండం_కొలత[comp.plane] = FFMAX(clear_ఖండం_కొలత[comp.plane], comp.అడుగు);

        ఒకవేళ (clear_ఖండం_కొలత[comp.plane] > MAX_ఖండం_కొలత)
            తిరిగి AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    కొరకు (c = 0; c < desc->nb_components; c++) {
        స్థిరరాశి AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        పూర్ణాంకం w = (bitstream ? 8 : 1) * clear_ఖండం_కొలత[comp.plane] / comp.అడుగు;
        uint8_t *c_దత్తాంశం[4];
        స్థిరరాశి పూర్ణాంకం c_linesize[4] = {0};
        uint32_t src_array[MAX_ఖండం_కొలత];
        పూర్ణాంకం x;

        ఒకవేళ (comp.లోతు > 32)
            తిరిగి AVERROR(EINVAL);
        ఒకవేళ (w < 1)
            తిరిగి AVERROR(EINVAL);

        కొరకు (x = 0; x < w; x++)
            src_array[x] = color[c];

        కొరకు (x = 0; x < 4; x++)
            c_దత్తాంశం[x] = &clear_ఖండం[x][0];

        av_write_image_line2(src_array, c_దత్తాంశం, c_linesize, desc, 0, 0, c, w, 4);
    }

    కొరకు (plane = 0; plane < nb_planes; plane++) {
        plane_పంక్తి_బైట్లు[plane] = av_image_get_linesize(pix_fmt, వెడల్పు, plane);
        ఒకవేళ (plane_పంక్తి_బైట్లు[plane] < 0)
            తిరిగి AVERROR(EINVAL);
    }

    ఒకవేళ (!dst_దత్తాంశం)
        తిరిగి 0;

    కొరకు (plane = 0; plane < nb_planes; plane++) {
        size_t bytewidth = plane_పంక్తి_బైట్లు[plane];
        uint8_t *దత్తాంశం = dst_దత్తాంశం[plane];
        పూర్ణాంకం chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        పూర్ణాంకం plane_h = AV_CEIL_RSHIFT(ఎత్తు, chroma_div);

        కొరకు (; plane_h > 0; plane_h--) {
            memset_బైట్లు(దత్తాంశం, bytewidth, &clear_ఖండం[plane][0], clear_ఖండం_కొలత[plane]);
            దత్తాంశం += dst_linesize[plane];
        }
    }

    తిరిగి 0;
}

పూర్ణాంకం av_image_fill_black(uint8_t * స్థిరరాశి dst_దత్తాంశం[4], స్థిరరాశి ptrdiff_t dst_linesize[4],
                        గణన AVPixelFormat pix_fmt, గణన AVColorRange range,
                        పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు)
{
    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    పూర్ణాంకం nb_planes = av_pix_fmt_లెక్క_planes(pix_fmt);
    పూర్ణాంకం rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    ఒకవేళ (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        తిరిగి AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    కొరకు (పూర్ణాంకం c = 0; c < desc->nb_components; c++) {
        స్థిరరాశి AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        ఒకవేళ (comp.లోతు > 32)
            తిరిగి AVERROR(EINVAL);

        ఒకవేళ (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } లేకపోతే ఒకవేళ (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            ఒకవేళ (fltp) {
                ఒకవేళ (comp.లోతు != 16 && comp.లోతు != 32)
                    తిరిగి AVERROR(EINVAL);
                color = (comp.లోతు == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } లేకపోతే {
                color = (comp.లోతు == 32 ? 0 : (1 << comp.లోతు)) - 1;
             }
        } లేకపోతే ఒకవేళ (c == 0 && limited && comp.లోతు > 1) {
            ఒకవేళ (comp.లోతు < 8 || (fltp && comp.లోతు != 16 && comp.లోతు != 32))
                తిరిగి AVERROR(EINVAL);
            ఒకవేళ (fltp)
                color = (comp.లోతు == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            లేకపోతే
                color = 16 << (comp.లోతు - 8);
        } లేకపోతే ఒకవేళ ((c == 1 || c == 2) && !rgb && !xyz) {
            ఒకవేళ (comp.లోతు < 8 || fltp && comp.లోతు != 16 && comp.లోతు != 32)
                తిరిగి AVERROR(EINVAL);
            ఒకవేళ (fltp)
                color = (comp.లోతు == 16 ? 0x3800 : 0x3F000000); // 0.5
            లేకపోతే
                color = 128 << (comp.లోతు - 8);
        }

        colors[c] = color;
    }

    తిరిగి av_image_fill_color(dst_దత్తాంశం, dst_linesize, pix_fmt, colors, వెడల్పు, ఎత్తు, 0);
}
