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

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/imgutils.c"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/crc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"

ਸਥਿਰ ਪੂਰਨ check_image_fill(ਗਿਣਤੀ AVPixelFormat pix_fmt, ਪੂਰਨ w, ਪੂਰਨ h) {
    uint8_t *ਅੰਕੜੇ[4];
    size_t sizes[4];
    ptrdiff_t linesizes1[4], offsets[3] = { 0 };
    ਪੂਰਨ i, ਕੁੱਲ_ਮਾਪ, linesizes[4];

    ਜੇ (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        ਵਾਪਸ -1;
    ਲਈ (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    ਜੇ (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        ਵਾਪਸ -1;
    ਕੁੱਲ_ਮਾਪ = av_image_fill_ਸੂਚਕ_ਸਾਰੇ(ਅੰਕੜੇ, pix_fmt, h, (ਖਾਲੀ *)1, linesizes);
    ਜੇ (ਕੁੱਲ_ਮਾਪ < 0)
        ਵਾਪਸ -1;
    ਲਈ (i = 0; i < 4 && ਅੰਕੜੇ[i]; i++);
    ਲਿਖੋ("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    ਲਿਖੋ(", linesizes:");
    ਲਈ (i = 0; i < 4; i++)
        ਲਿਖੋ(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    ਲਿਖੋ(", plane_sizes:");
    ਲਈ (i = 0; i < 4; i++)
        ਲਿਖੋ(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    ਲਈ (i = 0; i < 3 && ਅੰਕੜੇ[i + 1]; i++)
        offsets[i] = ਅੰਕੜੇ[i + 1] - ਅੰਕੜੇ[i];
    ਲਿਖੋ(", plane_offsets:");
    ਲਈ (i = 0; i < 3; i++)
        ਲਿਖੋ(" %5td", offsets[i]);
    ਲਿਖੋ(", total_size: %d", ਕੁੱਲ_ਮਾਪ);

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ check_image_fill_black(ਅਚਲ AVPixFmtDescriptor *desc, ਗਿਣਤੀ AVPixelFormat pix_fmt, ਪੂਰਨ w, ਪੂਰਨ h)
{
    uint8_t *ਅੰਕੜੇ[4];
    ptrdiff_t linesizes1[4];
    ਪੂਰਨ ret, ਕੁੱਲ_ਮਾਪ, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;
    ਕੁੱਲ_ਮਾਪ = av_image_alloc(ਅੰਕੜੇ, linesizes, w, h, pix_fmt, 4);
    ਜੇ (ਕੁੱਲ_ਮਾਪ < 0) {
        ਲਿਖੋ("alloc failure");
        ਵਾਪਸ ਕੁੱਲ_ਮਾਪ;
    }
    ਲਿਖੋ("total_size: %6d", ਕੁੱਲ_ਮਾਪ);
    ਜੇ (desc->flags & AV_PIX_FMT_FLAG_PAL)
        ਕੁੱਲ_ਮਾਪ -= 256 * 4;
    // Make it non-black by default...
    memset(ਅੰਕੜੇ[0], 0xA3, ਕੁੱਲ_ਮਾਪ);
    ਲਈ (ਪੂਰਨ i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    ਲਈ (ਗਿਣਤੀ AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(ਅੰਕੜੇ, linesizes1, pix_fmt, range, w, h);
        ਲਿਖੋ(",  black_%s_crc: ", av_color_range_name(range));
        ਜੇ (ret < 0) {
            ਲਿਖੋ("----------");
        } ਨਹੀਂਤਾਂ {
            ਅਚਲ AVCRC *ਚੱਕਰੀ_ਜਾਂਚ = av_ਚੱਕਰੀ_ਜਾਂਚ_get_ਸਾਰਣੀ(AV_ਚੱਕਰੀ_ਜਾਂਚ_32_IEEE_LE);
            ਲਿਖੋ("0x%08"PRIx32, av_ਚੱਕਰੀ_ਜਾਂਚ(ਚੱਕਰੀ_ਜਾਂਚ, 0, ਅੰਕੜੇ[0], ਕੁੱਲ_ਮਾਪ));
        }
    }
    av_freep(&ਅੰਕੜੇ[0]);

    ਵਾਪਸ 0;
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    int64_t x, y;

    ਲਈ (y = -1; y<UINT_MAX; y+= y/2 + 1) {
        ਲਈ (x = -1; x<UINT_MAX; x+= x/2 + 1) {
            ਪੂਰਨ ret = av_image_check_ਮਾਪ(x, y, 0, ਨਿਰਾ);
            ਲਿਖੋ("%d", ret >= 0);
        }
        ਲਿਖੋ("\n");
    }
    ਲਿਖੋ("\n");

    ਲਈ (ਪੂਰਨ i = 0; i < 2; i++) {
        ਲਿਖੋ(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        ਲਈ (ਅਚਲ AVPixFmtDescriptor *desc = ਨਿਰਾ; desc = av_pix_fmt_desc_ਅਗਲਾ(desc);) {
            ਪੂਰਨ w = 64, h = 48;
            ਗਿਣਤੀ AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            ਜੇ (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                ਜਾਰੀ;

            ਲਿਖੋ("%-16s", desc->name);
            ਜੇ (i == 0)
                check_image_fill(pix_fmt, w, h);
            ਨਹੀਂਤਾਂ
                check_image_fill_black(desc, pix_fmt, w, h);
            ਲਿਖੋ("\n");
        }
    }

    ਵਾਪਸ 0;
}
