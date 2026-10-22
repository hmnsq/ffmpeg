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

#అన్తర్భావ "libavutil/imgutils.c"
#అన్తర్భావ "libavutil/crc.h"
#అన్తర్భావ "libavutil/mem.h"

స్థిర పూర్ణాంకం check_image_fill(గణన AVPixelFormat pix_fmt, పూర్ణాంకం w, పూర్ణాంకం h) {
    uint8_t *దత్తాంశం[4];
    size_t sizes[4];
    ptrdiff_t linesizes1[4], offsets[3] = { 0 };
    పూర్ణాంకం i, మొత్తం_కొలత, linesizes[4];

    ఒకవేళ (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        తిరిగి -1;
    కొరకు (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    ఒకవేళ (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        తిరిగి -1;
    మొత్తం_కొలత = av_image_fill_సూచికలు(దత్తాంశం, pix_fmt, h, (శూన్య *)1, linesizes);
    ఒకవేళ (మొత్తం_కొలత < 0)
        తిరిగి -1;
    కొరకు (i = 0; i < 4 && దత్తాంశం[i]; i++);
    రాయి("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    రాయి(", linesizes:");
    కొరకు (i = 0; i < 4; i++)
        రాయి(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    రాయి(", plane_sizes:");
    కొరకు (i = 0; i < 4; i++)
        రాయి(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    కొరకు (i = 0; i < 3 && దత్తాంశం[i + 1]; i++)
        offsets[i] = దత్తాంశం[i + 1] - దత్తాంశం[i];
    రాయి(", plane_offsets:");
    కొరకు (i = 0; i < 3; i++)
        రాయి(" %5td", offsets[i]);
    రాయి(", total_size: %d", మొత్తం_కొలత);

    తిరిగి 0;
}

స్థిర పూర్ణాంకం check_image_fill_black(స్థిరరాశి AVPixFmtDescriptor *desc, గణన AVPixelFormat pix_fmt, పూర్ణాంకం w, పూర్ణాంకం h)
{
    uint8_t *దత్తాంశం[4];
    ptrdiff_t linesizes1[4];
    పూర్ణాంకం ret, మొత్తం_కొలత, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    ఒకవేళ (ret < 0)
        తిరిగి ret;
    మొత్తం_కొలత = av_image_alloc(దత్తాంశం, linesizes, w, h, pix_fmt, 4);
    ఒకవేళ (మొత్తం_కొలత < 0) {
        రాయి("alloc failure");
        తిరిగి మొత్తం_కొలత;
    }
    రాయి("total_size: %6d", మొత్తం_కొలత);
    ఒకవేళ (desc->flags & AV_PIX_FMT_FLAG_PAL)
        మొత్తం_కొలత -= 256 * 4;
    // Make it non-black by default...
    memset(దత్తాంశం[0], 0xA3, మొత్తం_కొలత);
    కొరకు (పూర్ణాంకం i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    కొరకు (గణన AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(దత్తాంశం, linesizes1, pix_fmt, range, w, h);
        రాయి(",  black_%s_crc: ", av_color_range_name(range));
        ఒకవేళ (ret < 0) {
            రాయి("----------");
        } లేకపోతే {
            స్థిరరాశి AVCRC *చక్రీయ_తనిఖీ = av_చక్రీయ_తనిఖీ_get_పట్టిక(AV_చక్రీయ_తనిఖీ_32_IEEE_LE);
            రాయి("0x%08"PRIx32, av_చక్రీయ_తనిఖీ(చక్రీయ_తనిఖీ, 0, దత్తాంశం[0], మొత్తం_కొలత));
        }
    }
    av_freep(&దత్తాంశం[0]);

    తిరిగి 0;
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    int64_t x, y;

    కొరకు (y = -1; y<UINT_MAX; y+= y/2 + 1) {
        కొరకు (x = -1; x<UINT_MAX; x+= x/2 + 1) {
            పూర్ణాంకం ret = av_image_check_కొలత(x, y, 0, ఖాళీ);
            రాయి("%d", ret >= 0);
        }
        రాయి("\n");
    }
    రాయి("\n");

    కొరకు (పూర్ణాంకం i = 0; i < 2; i++) {
        రాయి(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        కొరకు (స్థిరరాశి AVPixFmtDescriptor *desc = ఖాళీ; desc = av_pix_fmt_desc_తదుపరి(desc);) {
            పూర్ణాంకం w = 64, h = 48;
            గణన AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            ఒకవేళ (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                కొనసాగు;

            రాయి("%-16s", desc->name);
            ఒకవేళ (i == 0)
                check_image_fill(pix_fmt, w, h);
            లేకపోతే
                check_image_fill_black(desc, pix_fmt, w, h);
            రాయి("\n");
        }
    }

    తిరిగి 0;
}
