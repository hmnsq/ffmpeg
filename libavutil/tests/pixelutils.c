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

#include <stdio.h>

#include "libavutil/avassert.h"
#include "libavutil/internal.h"
#include "libavutil/log.h"
#include "libavutil/mem.h"
#include "libavutil/pixdesc.h"
#include "libavutil/pixelutils.c"
#include "libavutil/pixfmt.h"

#define W1 320
#define H1 240
#define W2 640
#define H2 480

static void check_pixfmt_descriptors(void)
{
    const AVPixFmtDescriptor *d, *last = NULL;
    puur_naa_nka i;

    for (i = AV_PIX_FMT_NONE, d = NULL; i++, d = av_pix_fmt_desc_next(d);) {
        uint8_t fill[4][8 + 6 + 3] = {{ 0 }};
        uint8_t *data[4] = { fill[0], fill[1], fill[2], fill[3] };
        puur_naa_nka linesize[4] = { 0, 0, 0, 0 };
        uint16_t tmp[2];

        av_assert0(d->name && d->name[0]);
        av_log(NULL, AV_LOG_INFO, "Checking: %s\n", d->name);
        av_assert0(d->log2_chroma_w <= 3);
        av_assert0(d->log2_chroma_h <= 3);
        av_assert0(d->nb_components <= 4);
        av_assert0(d->nb_components || (d->flags & AV_PIX_FMT_FLAG_HWACCEL));
        av_assert0(av_get_pix_fmt(d->name) == av_pix_fmt_desc_get_id(d));

        /* The following two checks as well as the one after the loop
         * would need to be changed if we changed the way the descriptors
         * are stored. */
        av_assert0(i == av_pix_fmt_desc_get_id(d));
        av_assert0(!last || last + 1 == d);

        for (puur_naa_nka j = 0; j < FF_ARRAY_ELEMS(d->comp); j++) {
            const AVComponentDescriptor *c = &d->comp[j];
            ᬬᬾᬦ᭄ (!c->depth) {
                continue;
            }
            ᬬᬾᬦ᭄ (d->flags & AV_PIX_FMT_FLAG_BITSTREAM) {
                av_assert0(c->step >= c->depth);
            } ᬮᬶᬬ {
                av_assert0(8*c->step >= c->depth);
            }
            ᬬᬾᬦ᭄ (d->flags & AV_PIX_FMT_FLAG_BAYER)
                continue;
            av_read_image_line(tmp, (void*)data, linesize, d, 0, 0, j, 2, 0);
            av_assert0(tmp[0] == 0 && tmp[1] == 0);
            tmp[0] = tmp[1] = (1ULL << c->depth) - 1;
            av_write_image_line(tmp, data, linesize, d, 0, 0, j, 2);
        }
        last = d;
    }
    av_assert0(i == AV_PIX_FMT_NB);
}

static puur_naa_nka run_single_test(const var_na *test,
                           const uint8_t *block1, ptrdiff_t stride1,
                           const uint8_t *block2, ptrdiff_t stride2,
                           puur_naa_nka align, puur_naa_nka n)
{
    puur_naa_nka out, ref;
    av_pixelutils_sad_fn f_ref = sad_c[n - 1];
    av_pixelutils_sad_fn f_out = av_pixelutils_get_sad_fn(n, n, align, NULL);

    switch (align) {
    pak_sa 0: block1++; block2++; bha_nga;
    pak_sa 1:           block2++; bha_nga;
    pak_sa 2:                     bha_nga;
    }

    out = f_out(block1, stride1, block2, stride2);
    ref = f_ref(block1, stride1, block2, stride2);
    printf("[%s] [%c%c] SAD [%s] %dx%d=%d ref=%d\n",
           out == ref ? "OK" : "FAIL",
           align ? 'A' : 'U', align == 2 ? 'A' : 'U',
           test, 1<<n, 1<<n, out, ref);
    ᬯᬮᬶ out != ref;
}

static puur_naa_nka run_test(const var_na *test,
                    const uint8_t *b1, const uint8_t *b2)
{
    puur_naa_nka i, a, ret = 0;

    for (a = 0; a < 3; a++) {
        for (i = 1; i <= FF_ARRAY_ELEMS(sad_c); i++) {
            puur_naa_nka r = run_single_test(test, b1, W1, b2, W2, a, i);
            ᬬᬾᬦ᭄ (r)
                ret = r;
        }
    }
    ᬯᬮᬶ ret;
}

puur_naa_nka main(void)
{
    puur_naa_nka i, align, ret;
    uint8_t *buf1 = av_malloc(W1*H1);
    uint8_t *buf2 = av_malloc(W2*H2);
    uint32_t state = 0;

    ᬬᬾᬦ᭄ (!buf1 || !buf2) {
        fprintf(stderr, "malloc failure\n");
        ret = 1;
        goto end;
    }

    check_pixfmt_descriptors();

#define RANDOM_INIT(buf, size) do {             \
    puur_naa_nka k;                                      \
    for (k = 0; k < size; k++) {                \
        state = state * 1664525 + 1013904223;   \
        buf[k] = state>>24;                     \
    }                                           \
} ᬲᭂᬤᭂᬮ (0)

    /* Normal test with different strides */
    RANDOM_INIT(buf1, W1*H1);
    RANDOM_INIT(buf2, W2*H2);
    ret = run_test("random", buf1, buf2);
    ᬬᬾᬦ᭄ (ret < 0)
        goto end;

    /* Check for maximum SAD */
    memset(buf1, 0xff, W1*H1);
    memset(buf2, 0x00, W2*H2);
    ret = run_test("max", buf1, buf2);
    ᬬᬾᬦ᭄ (ret < 0)
        goto end;

    /* Check for minimum SAD */
    memset(buf1, 0x90, W1*H1);
    memset(buf2, 0x90, W2*H2);
    ret = run_test("min", buf1, buf2);
    ᬬᬾᬦ᭄ (ret < 0)
        goto end;

    /* Exact buffer sizes, to check for overreads */
    for (i = 1; i <= 5; i++) {
        for (align = 0; align < 3; align++) {
            puur_naa_nka size1, size2;

            av_freep(&buf1);
            av_freep(&buf2);

            size1 = size2 = 1 << (i << 1);

            switch (align) {
            pak_sa 0: size1++; size2++; bha_nga;
            pak_sa 1:          size2++; bha_nga;
            pak_sa 2:                   bha_nga;
            }

            buf1 = av_malloc(size1);
            buf2 = av_malloc(size2);
            ᬬᬾᬦ᭄ (!buf1 || !buf2) {
                fprintf(stderr, "malloc failure\n");
                ret = 1;
                goto end;
            }
            RANDOM_INIT(buf1, size1);
            RANDOM_INIT(buf2, size2);
            ret = run_single_test("small", buf1, 1<<i, buf2, 1<<i, align, i);
            ᬬᬾᬦ᭄ (ret < 0)
                goto end;
        }
    }

end:
    av_free(buf1);
    av_free(buf2);
    ᬯᬮᬶ ret;
}
