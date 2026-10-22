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

#ಅನ್ತರ್ಭಾವ "libavutil/imgutils.c"
#ಅನ್ತರ್ಭಾವ "libavutil/crc.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ check_image_fill(ಎಣಿಕೆ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h) {
    uint8_t *ದತ್ತಾಂಶ[4];
    size_t sizes[4];
    ptrdiff_t linesizes1[4], offsets[3] = { 0 };
    ಪೂರ್ಣಾಂಕ i, ಒಟ್ಟು_ಗಾತ್ರ, linesizes[4];

    ಆದರೆ (av_image_fill_linesizes(linesizes, pix_fmt, w) < 0)
        ಹಿಂತಿರುಗಿ -1;
    ಗಾಗಿ (i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    ಆದರೆ (av_image_fill_plane_sizes(sizes, pix_fmt, h, linesizes1) < 0)
        ಹಿಂತಿರುಗಿ -1;
    ಒಟ್ಟು_ಗಾತ್ರ = av_image_fill_ಸೂಚಕಗಳು(ದತ್ತಾಂಶ, pix_fmt, h, (ಶೂನ್ಯ *)1, linesizes);
    ಆದರೆ (ಒಟ್ಟು_ಗಾತ್ರ < 0)
        ಹಿಂತಿರುಗಿ -1;
    ಗಾಗಿ (i = 0; i < 4 && ದತ್ತಾಂಶ[i]; i++);
    ಬರೆ("planes: %d", i);
    // Test the output of av_image_fill_linesizes()
    ಬರೆ(", linesizes:");
    ಗಾಗಿ (i = 0; i < 4; i++)
        ಬರೆ(" %3d", linesizes[i]);
    // Test the output of av_image_fill_plane_sizes()
    ಬರೆ(", plane_sizes:");
    ಗಾಗಿ (i = 0; i < 4; i++)
        ಬರೆ(" %5zu", sizes[i]);
    // Test the output of av_image_fill_pointers()
    ಗಾಗಿ (i = 0; i < 3 && ದತ್ತಾಂಶ[i + 1]; i++)
        offsets[i] = ದತ್ತಾಂಶ[i + 1] - ದತ್ತಾಂಶ[i];
    ಬರೆ(", plane_offsets:");
    ಗಾಗಿ (i = 0; i < 3; i++)
        ಬರೆ(" %5td", offsets[i]);
    ಬರೆ(", total_size: %d", ಒಟ್ಟು_ಗಾತ್ರ);

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ check_image_fill_black(ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc, ಎಣಿಕೆ AVPixelFormat pix_fmt, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h)
{
    uint8_t *ದತ್ತಾಂಶ[4];
    ptrdiff_t linesizes1[4];
    ಪೂರ್ಣಾಂಕ ret, ಒಟ್ಟು_ಗಾತ್ರ, linesizes[4];

    ret = av_image_fill_linesizes(linesizes, pix_fmt, w);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;
    ಒಟ್ಟು_ಗಾತ್ರ = av_image_alloc(ದತ್ತಾಂಶ, linesizes, w, h, pix_fmt, 4);
    ಆದರೆ (ಒಟ್ಟು_ಗಾತ್ರ < 0) {
        ಬರೆ("alloc failure");
        ಹಿಂತಿರುಗಿ ಒಟ್ಟು_ಗಾತ್ರ;
    }
    ಬರೆ("total_size: %6d", ಒಟ್ಟು_ಗಾತ್ರ);
    ಆದರೆ (desc->flags & AV_PIX_FMT_FLAG_PAL)
        ಒಟ್ಟು_ಗಾತ್ರ -= 256 * 4;
    // Make it non-black by default...
    memset(ದತ್ತಾಂಶ[0], 0xA3, ಒಟ್ಟು_ಗಾತ್ರ);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 4; i++)
        linesizes1[i] = linesizes[i];
    ಗಾಗಿ (ಎಣಿಕೆ AVColorRange range = 0; range < AVCOL_RANGE_NB; range++) {
        ret = av_image_fill_black(ದತ್ತಾಂಶ, linesizes1, pix_fmt, range, w, h);
        ಬರೆ(",  black_%s_crc: ", av_color_range_name(range));
        ಆದರೆ (ret < 0) {
            ಬರೆ("----------");
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಸ್ಥಿರಾಂಕ AVCRC *ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ = av_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_get_ಕೋಷ್ಟಕ(AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_IEEE_LE);
            ಬರೆ("0x%08"PRIx32, av_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ(ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ, 0, ದತ್ತಾಂಶ[0], ಒಟ್ಟು_ಗಾತ್ರ));
        }
    }
    av_freep(&ದತ್ತಾಂಶ[0]);

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    int64_t x, y;

    ಗಾಗಿ (y = -1; y<UINT_MAX; y+= y/2 + 1) {
        ಗಾಗಿ (x = -1; x<UINT_MAX; x+= x/2 + 1) {
            ಪೂರ್ಣಾಂಕ ret = av_image_check_ಗಾತ್ರ(x, y, 0, ಖಾಲಿ);
            ಬರೆ("%d", ret >= 0);
        }
        ಬರೆ("\n");
    }
    ಬರೆ("\n");

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 2; i++) {
        ಬರೆ(i ? "\nimage_fill_black tests\n" : "image_fill tests\n");
        ಗಾಗಿ (ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = ಖಾಲಿ; desc = av_pix_fmt_desc_ಮುಂದಿನ(desc);) {
            ಪೂರ್ಣಾಂಕ w = 64, h = 48;
            ಎಣಿಕೆ AVPixelFormat pix_fmt = av_pix_fmt_desc_get_id(desc);

            ಆದರೆ (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
                ಮುಂದುವರಿ;

            ಬರೆ("%-16s", desc->name);
            ಆದರೆ (i == 0)
                check_image_fill(pix_fmt, w, h);
            ಇಲ್ಲದಿದ್ದರೆ
                check_image_fill_black(desc, pix_fmt, w, h);
            ಬರೆ("\n");
        }
    }

    ಹಿಂತಿರುಗಿ 0;
}
