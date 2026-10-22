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

#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/avassert.h"
#అన్తర్భావ "libavutil/internal.h"
#అన్తర్భావ "libavutil/log.h"
#అన్తర్భావ "libavutil/mem.h"
#అన్తర్భావ "libavutil/pixdesc.h"
#అన్తర్భావ "libavutil/pixelutils.c"
#అన్తర్భావ "libavutil/pixfmt.h"

#నిర్వచించు W1 320
#నిర్వచించు H1 240
#నిర్వచించు W2 640
#నిర్వచించు H2 480

స్థిర శూన్య check_pixfmt_descriptors(శూన్య)
{
    స్థిరరాశి AVPixFmtDescriptor *d, *చివరి = ఖాళీ;
    పూర్ణాంకం i;

    కొరకు (i = AV_PIX_FMT_NONE, d = ఖాళీ; i++, d = av_pix_fmt_desc_తదుపరి(d);) {
        uint8_t fill[4][8 + 6 + 3] = {{ 0 }};
        uint8_t *దత్తాంశం[4] = { fill[0], fill[1], fill[2], fill[3] };
        పూర్ణాంకం linesize[4] = { 0, 0, 0, 0 };
        uint16_t tmp[2];

        av_assert0(d->name && d->name[0]);
        av_log(ఖాళీ, AV_LOG_INFO, "Checking: %s\n", d->name);
        av_assert0(d->log2_chroma_w <= 3);
        av_assert0(d->log2_chroma_h <= 3);
        av_assert0(d->nb_components <= 4);
        av_assert0(d->nb_components || (d->flags & AV_PIX_FMT_FLAG_HWACCEL));
        av_assert0(av_get_pix_fmt(d->name) == av_pix_fmt_desc_get_id(d));

        /* The following two checks as well as the one after the loop
         * would need to be changed if we changed the way the descriptors
         * are stored. */
        av_assert0(i == av_pix_fmt_desc_get_id(d));
        av_assert0(!చివరి || చివరి + 1 == d);

        కొరకు (పూర్ణాంకం j = 0; j < FF_ARRAY_ELEMS(d->comp); j++) {
            స్థిరరాశి AVComponentDescriptor *c = &d->comp[j];
            ఒకవేళ (!c->లోతు) {
                కొనసాగు;
            }
            ఒకవేళ (d->flags & AV_PIX_FMT_FLAG_BITSTREAM) {
                av_assert0(c->అడుగు >= c->లోతు);
            } లేకపోతే {
                av_assert0(8*c->అడుగు >= c->లోతు);
            }
            ఒకవేళ (d->flags & AV_PIX_FMT_FLAG_BAYER)
                కొనసాగు;
            av_read_image_పంక్తి(tmp, (శూన్య*)దత్తాంశం, linesize, d, 0, 0, j, 2, 0);
            av_assert0(tmp[0] == 0 && tmp[1] == 0);
            tmp[0] = tmp[1] = (1ULL << c->లోతు) - 1;
            av_write_image_పంక్తి(tmp, దత్తాంశం, linesize, d, 0, 0, j, 2);
        }
        చివరి = d;
    }
    av_assert0(i == AV_PIX_FMT_NB);
}

స్థిర పూర్ణాంకం నిరంతరం_single_test(స్థిరరాశి అక్షరం *test,
                           స్థిరరాశి uint8_t *block1, ptrdiff_t stride1,
                           స్థిరరాశి uint8_t *block2, ptrdiff_t stride2,
                           పూర్ణాంకం align, పూర్ణాంకం n)
{
    పూర్ణాంకం బహిర్గతం, ref;
    av_pixelutils_sad_fn f_ref = sad_c[n - 1];
    av_pixelutils_sad_fn f_బహిర్గతం = av_pixelutils_get_sad_fn(n, n, align, ఖాళీ);

    ఎంపిక (align) {
    స్థితి 0: block1++; block2++; ఆపు;
    స్థితి 1:           block2++; ఆపు;
    స్థితి 2:                     ఆపు;
    }

    బహిర్గతం = f_బహిర్గతం(block1, stride1, block2, stride2);
    ref = f_ref(block1, stride1, block2, stride2);
    రాయి("[%s] [%c%c] SAD [%s] %dx%d=%d ref=%d\n",
           బహిర్గతం == ref ? "OK" : "FAIL",
           align ? 'A' : 'U', align == 2 ? 'A' : 'U',
           test, 1<<n, 1<<n, బహిర్గతం, ref);
    తిరిగి బహిర్గతం != ref;
}

స్థిర పూర్ణాంకం నిరంతరం_test(స్థిరరాశి అక్షరం *test,
                    స్థిరరాశి uint8_t *b1, స్థిరరాశి uint8_t *b2)
{
    పూర్ణాంకం i, a, ret = 0;

    కొరకు (a = 0; a < 3; a++) {
        కొరకు (i = 1; i <= FF_ARRAY_ELEMS(sad_c); i++) {
            పూర్ణాంకం r = నిరంతరం_single_test(test, b1, W1, b2, W2, a, i);
            ఒకవేళ (r)
                ret = r;
        }
    }
    తిరిగి ret;
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    పూర్ణాంకం i, align, ret;
    uint8_t *buf1 = av_malloc(W1*H1);
    uint8_t *buf2 = av_malloc(W2*H2);
    uint32_t state = 0;

    ఒకవేళ (!buf1 || !buf2) {
        fprintf(stderr, "malloc failure\n");
        ret = 1;
        వెళ్ళు చివర;
    }

    check_pixfmt_descriptors();

#నిర్వచించు RANDOM_INIT(buf, కొలత) చేయి {             \
    పూర్ణాంకం k;                                      \
    కొరకు (k = 0; k < కొలత; k++) {                \
        state = state * 1664525 + 1013904223;   \
        buf[k] = state>>24;                     \
    }                                           \
} అయితే (0)

    /* Normal test with different strides */
    RANDOM_INIT(buf1, W1*H1);
    RANDOM_INIT(buf2, W2*H2);
    ret = నిరంతరం_test("random", buf1, buf2);
    ఒకవేళ (ret < 0)
        వెళ్ళు చివర;

    /* Check for maximum SAD */
    memset(buf1, 0xff, W1*H1);
    memset(buf2, 0x00, W2*H2);
    ret = నిరంతరం_test("max", buf1, buf2);
    ఒకవేళ (ret < 0)
        వెళ్ళు చివర;

    /* Check for minimum SAD */
    memset(buf1, 0x90, W1*H1);
    memset(buf2, 0x90, W2*H2);
    ret = నిరంతరం_test("min", buf1, buf2);
    ఒకవేళ (ret < 0)
        వెళ్ళు చివర;

    /* Exact buffer sizes, to check for overreads */
    కొరకు (i = 1; i <= 5; i++) {
        కొరకు (align = 0; align < 3; align++) {
            పూర్ణాంకం size1, size2;

            av_freep(&buf1);
            av_freep(&buf2);

            size1 = size2 = 1 << (i << 1);

            ఎంపిక (align) {
            స్థితి 0: size1++; size2++; ఆపు;
            స్థితి 1:          size2++; ఆపు;
            స్థితి 2:                   ఆపు;
            }

            buf1 = av_malloc(size1);
            buf2 = av_malloc(size2);
            ఒకవేళ (!buf1 || !buf2) {
                fprintf(stderr, "malloc failure\n");
                ret = 1;
                వెళ్ళు చివర;
            }
            RANDOM_INIT(buf1, size1);
            RANDOM_INIT(buf2, size2);
            ret = నిరంతరం_single_test("small", buf1, 1<<i, buf2, 1<<i, align, i);
            ఒకవేళ (ret < 0)
                వెళ్ళు చివర;
        }
    }

చివర:
    av_free(buf1);
    av_free(buf2);
    తిరిగి ret;
}
