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

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "imgutils.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "imgutils_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "intreadwrite.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mathematics.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixdesc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "rational.h"

ਖਾਲੀ av_image_fill_max_pixsteps(ਪੂਰਨ max_pixsteps[4], ਪੂਰਨ max_pixstep_comps[4],
                                ਅਚਲ AVPixFmtDescriptor *pixdesc)
{
    ਪੂਰਨ i;
    memset(max_pixsteps, 0, 4*ਆਕਾਰ(max_pixsteps[0]));
    ਜੇ (max_pixstep_comps)
        memset(max_pixstep_comps, 0, 4*ਆਕਾਰ(max_pixstep_comps[0]));

    ਲਈ (i = 0; i < 4; i++) {
        ਅਚਲ AVComponentDescriptor *comp = &(pixdesc->comp[i]);
        ਜੇ (comp->ਕਦਮ > max_pixsteps[comp->plane]) {
            max_pixsteps[comp->plane] = comp->ਕਦਮ;
            ਜੇ (max_pixstep_comps)
                max_pixstep_comps[comp->plane] = i;
        }
    }
}

ਸਥਿਰ ਸਤਰਅੰਦਰ
ਪੂਰਨ image_get_linesize(ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ plane,
                       ਪੂਰਨ max_ਕਦਮ, ਪੂਰਨ max_ਕਦਮ_comp,
                       ਅਚਲ AVPixFmtDescriptor *desc)
{
    ਪੂਰਨ s, shifted_w, linesize;

    ਜੇ (!desc)
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ (ਚੌੜਾਈ < 0)
        ਵਾਪਸ AVERROR(EINVAL);
    s = (max_ਕਦਮ_comp == 1 || max_ਕਦਮ_comp == 2) ? desc->log2_chroma_w : 0;
    shifted_w = AV_CEIL_RSHIFT(ਚੌੜਾਈ, s);
    ਜੇ (shifted_w && max_ਕਦਮ > ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ / shifted_w)
        ਵਾਪਸ AVERROR(EINVAL);
    linesize = max_ਕਦਮ * shifted_w;

    ਜੇ (desc->flags & AV_PIX_FMT_FLAG_BITSTREAM)
        linesize = (linesize >> 3) + !!(linesize & 7);
    ਵਾਪਸ linesize;
}

ਪੂਰਨ av_image_get_linesize(ਗਿਣਤੀ AVPixelFormat pix_fmt, ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ plane)
{
    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ਪੂਰਨ max_ਕਦਮ     [4];       /* max pixel step for each plane */
    ਪੂਰਨ max_ਕਦਮ_comp[4];       /* the component for each plane which has the max pixel step */

    ਜੇ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ਵਾਪਸ AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_ਕਦਮ, max_ਕਦਮ_comp, desc);
    ਵਾਪਸ image_get_linesize(ਚੌੜਾਈ, plane, max_ਕਦਮ[plane], max_ਕਦਮ_comp[plane], desc);
}

ਪੂਰਨ av_image_fill_linesizes(ਪੂਰਨ linesizes[4], ਗਿਣਤੀ AVPixelFormat pix_fmt, ਪੂਰਨ ਚੌੜਾਈ)
{
    ਪੂਰਨ i, ret;
    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ਪੂਰਨ max_ਕਦਮ     [4];       /* max pixel step for each plane */
    ਪੂਰਨ max_ਕਦਮ_comp[4];       /* the component for each plane which has the max pixel step */

    memset(linesizes, 0, 4*ਆਕਾਰ(linesizes[0]));

    ਜੇ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ਵਾਪਸ AVERROR(EINVAL);

    av_image_fill_max_pixsteps(max_ਕਦਮ, max_ਕਦਮ_comp, desc);
    ਲਈ (i = 0; i < 4; i++) {
        ਜੇ ((ret = image_get_linesize(ਚੌੜਾਈ, i, max_ਕਦਮ[i], max_ਕਦਮ_comp[i], desc)) < 0)
            ਵਾਪਸ ret;
        linesizes[i] = ret;
    }

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_image_fill_plane_sizes(size_t sizes[4], ਗਿਣਤੀ AVPixelFormat pix_fmt,
                              ਪੂਰਨ ਉਚਾਈ, ਅਚਲ ptrdiff_t linesizes[4])
{
    ਪੂਰਨ i, has_plane[4] = { 0 };

    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    memset(sizes    , 0, ਆਕਾਰ(sizes[0])*4);

    ਜੇ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ (linesizes[0] > SIZE_MAX / ਉਚਾਈ)
        ਵਾਪਸ AVERROR(EINVAL);
    sizes[0] = linesizes[0] * (size_t)ਉਚਾਈ;

    ਜੇ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        sizes[1] = 256 * 4; /* palette is stored here as 256 32 bits words */
        ਵਾਪਸ 0;
    }

    ਲਈ (i = 0; i < 4; i++)
        has_plane[desc->comp[i].plane] = 1;

    ਲਈ (i = 1; i < 4 && has_plane[i]; i++) {
        ਪੂਰਨ h, s = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        h = AV_CEIL_RSHIFT(ਉਚਾਈ, s);
        ਜੇ (linesizes[i] > SIZE_MAX / h)
            ਵਾਪਸ AVERROR(EINVAL);
        sizes[i] = (size_t)h * linesizes[i];
    }

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_image_fill_ਸੂਚਕ_ਸਾਰੇ(uint8_t *ਅੰਕੜੇ[4], ਗਿਣਤੀ AVPixelFormat pix_fmt, ਪੂਰਨ ਉਚਾਈ,
                           uint8_t *ptr, ਅਚਲ ਪੂਰਨ linesizes[4])
{
    ਪੂਰਨ i, ret;
    ptrdiff_t linesizes1[4];
    size_t sizes[4];

    memset(ਅੰਕੜੇ     , 0, ਆਕਾਰ(ਅੰਕੜੇ[0])*4);

    ਲਈ (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, ਉਚਾਈ, linesizes1);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ret = 0;
    ਲਈ (i = 0; i < 4; i++) {
        ਜੇ (sizes[i] > ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ - ret)
            ਵਾਪਸ AVERROR(EINVAL);
        ret += sizes[i];
    }

    ਜੇ (!ptr)
        ਵਾਪਸ ret;

    ਅੰਕੜੇ[0] = ptr;
    ਲਈ (i = 1; i < 4 && sizes[i]; i++)
        ਅੰਕੜੇ[i] = ਅੰਕੜੇ[i - 1] + sizes[i - 1];

    ਵਾਪਸ ret;
}

ਪੂਰਨ avpriv_ਸੈੱਟ_systematic_pal2(uint32_t pal[256], ਗਿਣਤੀ AVPixelFormat pix_fmt)
{
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < 256; i++) {
        ਪੂਰਨ r, g, b;

        ਚੋਣ (pix_fmt) {
        ਹਾਲਤ AV_PIX_FMT_RGB8:
            r = (i>>5    )*36;
            g = ((i>>2)&7)*36;
            b = (i&3     )*85;
            ਰੋਕੋ;
        ਹਾਲਤ AV_PIX_FMT_BGR8:
            b = (i>>6    )*85;
            g = ((i>>3)&7)*36;
            r = (i&7     )*36;
            ਰੋਕੋ;
        ਹਾਲਤ AV_PIX_FMT_RGB4_BYTE:
            r = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            b = (i&1     )*255;
            ਰੋਕੋ;
        ਹਾਲਤ AV_PIX_FMT_BGR4_BYTE:
            b = (i>>3    )*255;
            g = ((i>>1)&3)*85;
            r = (i&1     )*255;
            ਰੋਕੋ;
        ਹਾਲਤ AV_PIX_FMT_GRAY8:
            r = b = g = i;
            ਰੋਕੋ;
        ਮੂਲ:
            ਵਾਪਸ AVERROR(EINVAL);
        }
        pal[i] = b + (g << 8) + (r << 16) + (0xFFU << 24);
    }

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_image_alloc(uint8_t *ਸੂਚਕ_ਸਾਰੇ[4], ਪੂਰਨ linesizes[4],
                   ਪੂਰਨ w, ਪੂਰਨ h, ਗਿਣਤੀ AVPixelFormat pix_fmt, ਪੂਰਨ align)
{
    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ਪੂਰਨ i, ret;
    ptrdiff_t linesizes1[4];
    size_t ਕੁੱਲ_ਮਾਪ, sizes[4];
    uint8_t *buf;

    ਜੇ (!desc)
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ ((ret = av_image_check_ਮਾਪ(w, h, 0, ਨਿਰਾ)) < 0)
        ਵਾਪਸ ret;
    ਜੇ ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        ਵਾਪਸ ret;

    ਲਈ (i = 0; i < 4; i++) {
        linesizes[i] = FFALIGN(linesizes[i], align);
        linesizes1[i] = linesizes[i];
    }

    ਜੇ ((ret = av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1)) < 0)
        ਵਾਪਸ ret;
    ਕੁੱਲ_ਮਾਪ = align;
    ਲਈ (i = 0; i < 4; i++) {
        ਜੇ (ਕੁੱਲ_ਮਾਪ > SIZE_MAX - sizes[i])
            ਵਾਪਸ AVERROR(EINVAL);
        ਕੁੱਲ_ਮਾਪ += sizes[i];
    }
    buf = av_malloc(ਕੁੱਲ_ਮਾਪ);
    ਜੇ (!buf)
        ਵਾਪਸ AVERROR(ENOMEM);
    ਜੇ ((ret = av_image_fill_ਸੂਚਕ_ਸਾਰੇ(ਸੂਚਕ_ਸਾਰੇ, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        ਵਾਪਸ ret;
    }
    ਜੇ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        avpriv_ਸੈੱਟ_systematic_pal2((uint32_t*)ਸੂਚਕ_ਸਾਰੇ[1], pix_fmt);
        ਜੇ (align < 4) {
            av_log(ਨਿਰਾ, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            av_free(buf);
            ਵਾਪਸ AVERROR(EINVAL);
        }
    }

    ਜੇ (desc->flags & AV_PIX_FMT_FLAG_PAL && ਸੂਚਕ_ਸਾਰੇ[1] &&
        ਸੂਚਕ_ਸਾਰੇ[1] - ਸੂਚਕ_ਸਾਰੇ[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        memset(ਸੂਚਕ_ਸਾਰੇ[0] + linesizes[0] * h, 0,
               ਸੂਚਕ_ਸਾਰੇ[1] - ਸੂਚਕ_ਸਾਰੇ[0] - linesizes[0] * h);
    }

    ਵਾਪਸ ret;
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ImgUtils {
    ਅਚਲ AVClass *class;
    ਪੂਰਨ   log_ਵਿੱਥ;
    ਖਾਲੀ *log_ctx;
} ImgUtils;

ਸਥਿਰ ਅਚਲ AVClass imgutils_class = {
    .class_name                = "IMGUTILS",
    .ਵਸਤੂ_name                 = av_default_ਵਸਤੂ_name,
    .option                    = ਨਿਰਾ,
    .ਸੰਸਕਰਣ                   = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
    .log_level_ਵਿੱਥ_ਵਿੱਥ   = offsetof(ImgUtils, log_ਵਿੱਥ),
    .ਮਾਪਾ_log_context_ਵਿੱਥ = offsetof(ImgUtils, log_ctx),
};

ਪੂਰਨ av_image_check_size2(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ w, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ h, int64_t max_pixels, ਗਿਣਤੀ AVPixelFormat pix_fmt, ਪੂਰਨ log_ਵਿੱਥ, ਖਾਲੀ *log_ctx)
{
    ImgUtils imgutils = {
        .class      = &imgutils_class,
        .log_ਵਿੱਥ = log_ਵਿੱਥ,
        .log_ctx    = log_ctx,
    };
    int64_t stride = av_image_get_linesize(pix_fmt, w, 0);
    ਜੇ (stride <= 0)
        stride = 8LL*w;
    stride += 128*8;

    ਜੇ (w==0 || h==0 || w > INT32_MAX || h > INT32_MAX || stride >= ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ || stride*(h + 128ULL) >= ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ) {
        av_log(&imgutils, AV_LOG_ERROR, "Picture size %ux%u is invalid\n", w, h);
        ਵਾਪਸ AVERROR(EINVAL);
    }

    ਜੇ (max_pixels < INT64_MAX) {
        ਜੇ (w*(int64_t)h > max_pixels) {
            av_log(&imgutils, AV_LOG_ERROR,
                    "Picture size %ux%u exceeds specified max pixel count %"PRId64", see the documentation if you wish to increase it\n",
                    w, h, max_pixels);
            ਵਾਪਸ AVERROR(EINVAL);
        }
    }

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_image_check_ਮਾਪ(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ w, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ h, ਪੂਰਨ log_ਵਿੱਥ, ਖਾਲੀ *log_ctx)
{
    ਵਾਪਸ av_image_check_size2(w, h, INT64_MAX, AV_PIX_FMT_NONE, log_ਵਿੱਥ, log_ctx);
}

ਪੂਰਨ av_image_check_sar(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ w, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ h, AVRational sar)
{
    int64_t scaled_dim;

    ਜੇ (sar.den <= 0 || sar.ਅੰਕ < 0)
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ (!sar.ਅੰਕ || sar.ਅੰਕ == sar.den)
        ਵਾਪਸ 0;

    ਜੇ (sar.ਅੰਕ < sar.den)
        scaled_dim = av_rescale_rnd(w, sar.ਅੰਕ, sar.den, AV_ਗੇੜਾ_ZERO);
    ਨਹੀਂਤਾਂ
        scaled_dim = av_rescale_rnd(h, sar.den, sar.ਅੰਕ, AV_ਗੇੜਾ_ZERO);

    ਜੇ (scaled_dim > 0)
        ਵਾਪਸ 0;

    ਵਾਪਸ AVERROR(EINVAL);
}

ਸਥਿਰ ਖਾਲੀ image_copy_plane(uint8_t       *dst, ptrdiff_t dst_linesize,
                             ਅਚਲ uint8_t *src, ptrdiff_t src_linesize,
                             ptrdiff_t bytewidth, ਪੂਰਨ ਉਚਾਈ)
{
    ਜੇ (!dst || !src)
        ਵਾਪਸ;
    av_assert0(FFABS(src_linesize) >= bytewidth);
    av_assert0(FFABS(dst_linesize) >= bytewidth);
    ਲਈ (;ਉਚਾਈ > 0; ਉਚਾਈ--) {
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(dst, src, bytewidth);
        dst += dst_linesize;
        src += src_linesize;
    }
}

ਖਾਲੀ av_image_copy_plane_uc_from(uint8_t *dst, ptrdiff_t dst_linesize,
                                 ਅਚਲ uint8_t *src, ptrdiff_t src_linesize,
                                 ptrdiff_t bytewidth, ਪੂਰਨ ਉਚਾਈ)
{
    ਪੂਰਨ ret = -1;

#ਜੇ ARCH_X86 && HAVE_X86ASM
    ret = ff_image_copy_plane_uc_from_x86(dst, dst_linesize, src, src_linesize,
                                          bytewidth, ਉਚਾਈ);
#ਜੇ_ਅੰਤ

    ਜੇ (ret < 0)
        image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, ਉਚਾਈ);
}

ਖਾਲੀ av_image_copy_plane(uint8_t       *dst, ਪੂਰਨ dst_linesize,
                         ਅਚਲ uint8_t *src, ਪੂਰਨ src_linesize,
                         ਪੂਰਨ bytewidth, ਪੂਰਨ ਉਚਾਈ)
{
    image_copy_plane(dst, dst_linesize, src, src_linesize, bytewidth, ਉਚਾਈ);
}

ਸਥਿਰ ਖਾਲੀ image_copy(uint8_t *ਅਚਲ dst_ਅੰਕੜੇ[4], ਅਚਲ ptrdiff_t dst_linesizes[4],
                       ਅਚਲ uint8_t *ਅਚਲ src_ਅੰਕੜੇ[4], ਅਚਲ ptrdiff_t src_linesizes[4],
                       ਗਿਣਤੀ AVPixelFormat pix_fmt, ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ,
                       ਖਾਲੀ (*copy_plane)(uint8_t *, ptrdiff_t, ਅਚਲ uint8_t *,
                                          ptrdiff_t, ptrdiff_t, ਪੂਰਨ))
{
    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    ਜੇ (!desc || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ਵਾਪਸ;

    ਜੇ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        copy_plane(dst_ਅੰਕੜੇ[0], dst_linesizes[0],
                   src_ਅੰਕੜੇ[0], src_linesizes[0],
                   ਚੌੜਾਈ, ਉਚਾਈ);
        /* copy the palette */
        ਜੇ ((desc->flags & AV_PIX_FMT_FLAG_PAL) || (dst_ਅੰਕੜੇ[1] && src_ਅੰਕੜੇ[1]))
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(dst_ਅੰਕੜੇ[1], src_ਅੰਕੜੇ[1], 4*256);
    } ਨਹੀਂਤਾਂ {
        ਪੂਰਨ i, planes_nb = 0;

        ਲਈ (i = 0; i < desc->nb_components; i++)
            planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

        ਲਈ (i = 0; i < planes_nb; i++) {
            ਪੂਰਨ h = ਉਚਾਈ;
            ptrdiff_t bwidth = av_image_get_linesize(pix_fmt, ਚੌੜਾਈ, i);
            ਜੇ (bwidth < 0) {
                av_log(ਨਿਰਾ, AV_LOG_ERROR, "av_image_get_linesize failed\n");
                ਵਾਪਸ;
            }
            ਜੇ (i == 1 || i == 2) {
                h = AV_CEIL_RSHIFT(ਉਚਾਈ, desc->log2_chroma_h);
            }
            copy_plane(dst_ਅੰਕੜੇ[i], dst_linesizes[i],
                       src_ਅੰਕੜੇ[i], src_linesizes[i],
                       bwidth, h);
        }
    }
}

ਖਾਲੀ av_image_copy(uint8_t *ਅਚਲ dst_ਅੰਕੜੇ[4], ਅਚਲ ਪੂਰਨ dst_linesizes[4],
                   ਅਚਲ uint8_t * ਅਚਲ src_ਅੰਕੜੇ[4], ਅਚਲ ਪੂਰਨ src_linesizes[4],
                   ਗਿਣਤੀ AVPixelFormat pix_fmt, ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ)
{
    ptrdiff_t dst_linesizes1[4], src_linesizes1[4];
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_ਅੰਕੜੇ, dst_linesizes1, src_ਅੰਕੜੇ, src_linesizes1, pix_fmt,
               ਚੌੜਾਈ, ਉਚਾਈ, image_copy_plane);
}

ਖਾਲੀ av_image_copy_uc_from(uint8_t * ਅਚਲ dst_ਅੰਕੜੇ[4], ਅਚਲ ptrdiff_t dst_linesizes[4],
                           ਅਚਲ uint8_t * ਅਚਲ src_ਅੰਕੜੇ[4], ਅਚਲ ptrdiff_t src_linesizes[4],
                           ਗਿਣਤੀ AVPixelFormat pix_fmt, ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ)
{
    image_copy(dst_ਅੰਕੜੇ, dst_linesizes, src_ਅੰਕੜੇ, src_linesizes, pix_fmt,
               ਚੌੜਾਈ, ਉਚਾਈ, av_image_copy_plane_uc_from);
}

ਪੂਰਨ av_image_fill_arrays(uint8_t *dst_ਅੰਕੜੇ[4], ਪੂਰਨ dst_linesize[4],
                         ਅਚਲ uint8_t *src, ਗਿਣਤੀ AVPixelFormat pix_fmt,
                         ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਪੂਰਨ align)
{
    ਪੂਰਨ ret, i;

    ret = av_image_check_ਮਾਪ(ਚੌੜਾਈ, ਉਚਾਈ, 0, ਨਿਰਾ);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ret = av_image_fill_linesizes(dst_linesize, pix_fmt, ਚੌੜਾਈ);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ਲਈ (i = 0; i < 4; i++)
        dst_linesize[i] = FFALIGN(dst_linesize[i], align);

    ਵਾਪਸ av_image_fill_ਸੂਚਕ_ਸਾਰੇ(dst_ਅੰਕੜੇ, pix_fmt, ਉਚਾਈ, (uint8_t *)src, dst_linesize);
}

ਪੂਰਨ av_image_get_ਬਫਰ_ਮਾਪ(ਗਿਣਤੀ AVPixelFormat pix_fmt,
                             ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਪੂਰਨ align)
{
    ਪੂਰਨ ret, i;
    ਪੂਰਨ linesize[4];
    ptrdiff_t aligned_linesize[4];
    size_t sizes[4];
    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ਜੇ (!desc)
        ਵਾਪਸ AVERROR(EINVAL);

    ret = av_image_check_ਮਾਪ(ਚੌੜਾਈ, ਉਚਾਈ, 0, ਨਿਰਾ);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ret = av_image_fill_linesizes(linesize, pix_fmt, ਚੌੜਾਈ);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ਲਈ (i = 0; i < 4; i++)
        aligned_linesize[i] = FFALIGN(linesize[i], align);

    ret = av_image_fill_plane_sizes(sizes, pix_fmt, ਉਚਾਈ, aligned_linesize);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ret = 0;
    ਲਈ (i = 0; i < 4; i++) {
        ਜੇ (sizes[i] > ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ - ret)
            ਵਾਪਸ AVERROR(EINVAL);
        ret += sizes[i];
    }
    ਵਾਪਸ ret;
}

ਪੂਰਨ av_image_copy_ਮੰਜ਼ਿਲ_ਬਫਰ(uint8_t *dst, ਪੂਰਨ dst_ਮਾਪ,
                            ਅਚਲ uint8_t * ਅਚਲ src_ਅੰਕੜੇ[4],
                            ਅਚਲ ਪੂਰਨ src_linesize[4],
                            ਗਿਣਤੀ AVPixelFormat pix_fmt,
                            ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਪੂਰਨ align)
{
    ਪੂਰਨ i, j, nb_planes = 0, linesize[4];
    ਪੂਰਨ ਮਾਪ = av_image_get_ਬਫਰ_ਮਾਪ(pix_fmt, ਚੌੜਾਈ, ਉਚਾਈ, align);
    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ਪੂਰਨ ret;

    ਜੇ (ਮਾਪ > dst_ਮਾਪ || ਮਾਪ < 0 || !desc)
        ਵਾਪਸ AVERROR(EINVAL);

    ਲਈ (i = 0; i < desc->nb_components; i++)
        nb_planes = FFMAX(desc->comp[i].plane, nb_planes);

    nb_planes++;

    ret = av_image_fill_linesizes(linesize, pix_fmt, ਚੌੜਾਈ);
    av_assert0(ret >= 0); // was checked previously

    ਲਈ (i = 0; i < nb_planes; i++) {
        ਪੂਰਨ h, ਖਿਸਕਾਓ = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;
        ਅਚਲ uint8_t *src = src_ਅੰਕੜੇ[i];
        h = AV_CEIL_RSHIFT(ਉਚਾਈ, ਖਿਸਕਾਓ);

        ਲਈ (j = 0; j < h; j++) {
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(dst, src, linesize[i]);
            dst += FFALIGN(linesize[i], align);
            src += src_linesize[i];
        }
    }

    ਜੇ (desc->flags & AV_PIX_FMT_FLAG_PAL) {
        uint32_t *d32 = (uint32_t *)dst;

        ਲਈ (i = 0; i<256; i++)
            AV_WL32(d32 + i, AV_RN32(src_ਅੰਕੜੇ[1] + 4*i));
    }

    ਵਾਪਸ ਮਾਪ;
}

// Fill dst[0..dst_size] with the bytes in clear[0..clear_size]. The clear
// bytes are repeated until dst_size is reached. If dst_size is unaligned (i.e.
// dst_size%clear_size!=0), the remaining data will be filled with the beginning
// of the clear data only.
ਸਥਿਰ ਖਾਲੀ memset_ਬਾਈਟਾਂ(uint8_t *dst, size_t dst_ਮਾਪ, uint8_t *clear,
                         size_t clear_ਮਾਪ)
{
    ਪੂਰਨ same = 1;
    ਪੂਰਨ i;

    ਜੇ (!clear_ਮਾਪ)
        ਵਾਪਸ;

    // Reduce to memset() if possible.
    ਲਈ (i = 0; i < clear_ਮਾਪ; i++) {
        ਜੇ (clear[i] != clear[0]) {
            same = 0;
            ਰੋਕੋ;
        }
    }
    ਜੇ (same)
        clear_ਮਾਪ = 1;

    ਜੇ (clear_ਮਾਪ == 1) {
        memset(dst, clear[0], dst_ਮਾਪ);
    } ਨਹੀਂਤਾਂ {
        ਜੇ (clear_ਮਾਪ > dst_ਮਾਪ)
            clear_ਮਾਪ = dst_ਮਾਪ;
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(dst, clear, clear_ਮਾਪ);
        av_memcpy_backptr(dst + clear_ਮਾਪ, clear_ਮਾਪ, dst_ਮਾਪ - clear_ਮਾਪ);
    }
}

// Maximum size in bytes of a plane element (usually a pixel, or multiple pixels
// if it's a subsampled packed format).
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_ਖੰਡ_ਮਾਪ 32

ਪੂਰਨ av_image_fill_color(uint8_t * ਅਚਲ dst_ਅੰਕੜੇ[4], ਅਚਲ ptrdiff_t dst_linesize[4],
                        ਗਿਣਤੀ AVPixelFormat pix_fmt, ਅਚਲ uint32_t color[4],
                        ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ, ਪੂਰਨ flags)
{
    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ਪੂਰਨ nb_planes = av_pix_fmt_ਗਿਣਤੀ_planes(pix_fmt);
    // A pixel or a group of pixels on each plane, with a value that represents the color.
    // Consider e.g. AV_PIX_FMT_UYVY422 for non-trivial cases.
    uint8_t clear_ਖੰਡ[4][MAX_ਖੰਡ_ਮਾਪ] = {{0}}; // clear padding with 0
    ਪੂਰਨ clear_ਖੰਡ_ਮਾਪ[4] = {0};
    ptrdiff_t plane_ਸਤਰ_ਬਾਈਟਾਂ[4] = {0};
    ਪੂਰਨ bitstream;
    ਪੂਰਨ plane, c;

    ਜੇ (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ਵਾਪਸ AVERROR(EINVAL);

    bitstream = !!(desc->flags & AV_PIX_FMT_FLAG_BITSTREAM);

    ਲਈ (c = 0; c < desc->nb_components; c++) {
        ਅਚਲ AVComponentDescriptor comp = desc->comp[c];

        // We try to operate on entire non-subsampled pixel groups (for
        // AV_PIX_FMT_UYVY422 this would mean two consecutive pixels).
        clear_ਖੰਡ_ਮਾਪ[comp.plane] = FFMAX(clear_ਖੰਡ_ਮਾਪ[comp.plane], comp.ਕਦਮ);

        ਜੇ (clear_ਖੰਡ_ਮਾਪ[comp.plane] > MAX_ਖੰਡ_ਮਾਪ)
            ਵਾਪਸ AVERROR(EINVAL);
    }

    // Create a byte array for clearing 1 pixel (sometimes several pixels).
    ਲਈ (c = 0; c < desc->nb_components; c++) {
        ਅਚਲ AVComponentDescriptor comp = desc->comp[c];
        // (Multiple pixels happen e.g. with AV_PIX_FMT_UYVY422.)
        ਪੂਰਨ w = (bitstream ? 8 : 1) * clear_ਖੰਡ_ਮਾਪ[comp.plane] / comp.ਕਦਮ;
        uint8_t *c_ਅੰਕੜੇ[4];
        ਅਚਲ ਪੂਰਨ c_linesize[4] = {0};
        uint32_t src_array[MAX_ਖੰਡ_ਮਾਪ];
        ਪੂਰਨ x;

        ਜੇ (comp.ਡੂੰਘਾਈ > 32)
            ਵਾਪਸ AVERROR(EINVAL);
        ਜੇ (w < 1)
            ਵਾਪਸ AVERROR(EINVAL);

        ਲਈ (x = 0; x < w; x++)
            src_array[x] = color[c];

        ਲਈ (x = 0; x < 4; x++)
            c_ਅੰਕੜੇ[x] = &clear_ਖੰਡ[x][0];

        av_write_image_line2(src_array, c_ਅੰਕੜੇ, c_linesize, desc, 0, 0, c, w, 4);
    }

    ਲਈ (plane = 0; plane < nb_planes; plane++) {
        plane_ਸਤਰ_ਬਾਈਟਾਂ[plane] = av_image_get_linesize(pix_fmt, ਚੌੜਾਈ, plane);
        ਜੇ (plane_ਸਤਰ_ਬਾਈਟਾਂ[plane] < 0)
            ਵਾਪਸ AVERROR(EINVAL);
    }

    ਜੇ (!dst_ਅੰਕੜੇ)
        ਵਾਪਸ 0;

    ਲਈ (plane = 0; plane < nb_planes; plane++) {
        size_t bytewidth = plane_ਸਤਰ_ਬਾਈਟਾਂ[plane];
        uint8_t *ਅੰਕੜੇ = dst_ਅੰਕੜੇ[plane];
        ਪੂਰਨ chroma_div = plane == 1 || plane == 2 ? desc->log2_chroma_h : 0;
        ਪੂਰਨ plane_h = AV_CEIL_RSHIFT(ਉਚਾਈ, chroma_div);

        ਲਈ (; plane_h > 0; plane_h--) {
            memset_ਬਾਈਟਾਂ(ਅੰਕੜੇ, bytewidth, &clear_ਖੰਡ[plane][0], clear_ਖੰਡ_ਮਾਪ[plane]);
            ਅੰਕੜੇ += dst_linesize[plane];
        }
    }

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_image_fill_black(uint8_t * ਅਚਲ dst_ਅੰਕੜੇ[4], ਅਚਲ ptrdiff_t dst_linesize[4],
                        ਗਿਣਤੀ AVPixelFormat pix_fmt, ਗਿਣਤੀ AVColorRange range,
                        ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ)
{
    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    ਪੂਰਨ nb_planes = av_pix_fmt_ਗਿਣਤੀ_planes(pix_fmt);
    ਪੂਰਨ rgb, xyz, pal, limited, alpha, fltp;
    uint32_t colors[4] = {0};

    ਜੇ (!desc || nb_planes < 1 || nb_planes > 4 || desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        ਵਾਪਸ AVERROR(EINVAL);

    rgb = !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
    xyz = !!(desc->flags & AV_PIX_FMT_FLAG_XYZ);
    pal = !!(desc->flags & AV_PIX_FMT_FLAG_PAL);
    limited = !rgb && !xyz && !pal && range != AVCOL_RANGE_JPEG;
    alpha = !pal && !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
    fltp = !!(desc->flags & AV_PIX_FMT_FLAG_FLOAT);

    ਲਈ (ਪੂਰਨ c = 0; c < desc->nb_components; c++) {
        ਅਚਲ AVComponentDescriptor comp = desc->comp[c];
        uint32_t color = 0;

        ਜੇ (comp.ਡੂੰਘਾਈ > 32)
            ਵਾਪਸ AVERROR(EINVAL);

        ਜੇ (pix_fmt == AV_PIX_FMT_MONOWHITE) {
            color = 1;
        } ਨਹੀਂਤਾਂ ਜੇ (c + 1 == desc->nb_components && alpha) {
            // (Assume even limited YUV uses full range alpha.)
            ਜੇ (fltp) {
                ਜੇ (comp.ਡੂੰਘਾਈ != 16 && comp.ਡੂੰਘਾਈ != 32)
                    ਵਾਪਸ AVERROR(EINVAL);
                color = (comp.ਡੂੰਘਾਈ == 16 ? 0x3C00 : 0x3F800000); // 1.0
             } ਨਹੀਂਤਾਂ {
                color = (comp.ਡੂੰਘਾਈ == 32 ? 0 : (1 << comp.ਡੂੰਘਾਈ)) - 1;
             }
        } ਨਹੀਂਤਾਂ ਜੇ (c == 0 && limited && comp.ਡੂੰਘਾਈ > 1) {
            ਜੇ (comp.ਡੂੰਘਾਈ < 8 || (fltp && comp.ਡੂੰਘਾਈ != 16 && comp.ਡੂੰਘਾਈ != 32))
                ਵਾਪਸ AVERROR(EINVAL);
            ਜੇ (fltp)
                color = (comp.ਡੂੰਘਾਈ == 16 ? 0x2C00 : 0x3D800000); // 0.0625
            ਨਹੀਂਤਾਂ
                color = 16 << (comp.ਡੂੰਘਾਈ - 8);
        } ਨਹੀਂਤਾਂ ਜੇ ((c == 1 || c == 2) && !rgb && !xyz) {
            ਜੇ (comp.ਡੂੰਘਾਈ < 8 || fltp && comp.ਡੂੰਘਾਈ != 16 && comp.ਡੂੰਘਾਈ != 32)
                ਵਾਪਸ AVERROR(EINVAL);
            ਜੇ (fltp)
                color = (comp.ਡੂੰਘਾਈ == 16 ? 0x3800 : 0x3F000000); // 0.5
            ਨਹੀਂਤਾਂ
                color = 128 << (comp.ਡੂੰਘਾਈ - 8);
        }

        colors[c] = color;
    }

    ਵਾਪਸ av_image_fill_color(dst_ਅੰਕੜੇ, dst_linesize, pix_fmt, colors, ਚੌੜਾਈ, ਉਚਾਈ, 0);
}
