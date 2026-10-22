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

#অন্তর্ভাব <stdio.h>

#অন্তর্ভাব "libavutil/avassert.h"
#অন্তর্ভাব "libavutil/internal.h"
#অন্তর্ভাব "libavutil/log.h"
#অন্তর্ভাব "libavutil/mem.h"
#অন্তর্ভাব "libavutil/pixdesc.h"
#অন্তর্ভাব "libavutil/pixelutils.c"
#অন্তর্ভাব "libavutil/pixfmt.h"

#define W1 320
#define H1 240
#define W2 640
#define H2 480

স্থির শূন্য check_pixfmt_descriptors(শূন্য)
{
    ধ্রুবক AVPixFmtDescriptor *d, *last = ফাঁকা;
    পূর্ণসংখ্যা i;

    জন্য (i = AV_PIX_FMT_NONE, d = ফাঁকা; i++, d = av_pix_fmt_desc_পরবর্তী(d);) {
        uint8_t fill[4][8 + 6 + 3] = {{ 0 }};
        uint8_t *তথ্য[4] = { fill[0], fill[1], fill[2], fill[3] };
        পূর্ণসংখ্যা linesize[4] = { 0, 0, 0, 0 };
        uint16_t tmp[2];

        av_assert0(d->name && d->name[0]);
        av_log(ফাঁকা, AV_LOG_INFO, "Checking: %s\n", d->name);
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

        জন্য (পূর্ণসংখ্যা j = 0; j < FF_ARRAY_ELEMS(d->comp); j++) {
            ধ্রুবক AVComponentDescriptor *c = &d->comp[j];
            যদি (!c->depth) {
                চালু;
            }
            যদি (d->flags & AV_PIX_FMT_FLAG_BITSTREAM) {
                av_assert0(c->step >= c->depth);
            } অন্যথা {
                av_assert0(8*c->step >= c->depth);
            }
            যদি (d->flags & AV_PIX_FMT_FLAG_BAYER)
                চালু;
            av_read_image_সারি(tmp, (শূন্য*)তথ্য, linesize, d, 0, 0, j, 2, 0);
            av_assert0(tmp[0] == 0 && tmp[1] == 0);
            tmp[0] = tmp[1] = (1ULL << c->depth) - 1;
            av_write_image_সারি(tmp, তথ্য, linesize, d, 0, 0, j, 2);
        }
        last = d;
    }
    av_assert0(i == AV_PIX_FMT_NB);
}

স্থির পূর্ণসংখ্যা run_single_test(ধ্রুবক অক্ষর *test,
                           ধ্রুবক uint8_t *block1, ptrdiff_t stride1,
                           ধ্রুবক uint8_t *block2, ptrdiff_t stride2,
                           পূর্ণসংখ্যা align, পূর্ণসংখ্যা n)
{
    পূর্ণসংখ্যা out, ref;
    av_pixelutils_sad_fn f_ref = sad_c[n - 1];
    av_pixelutils_sad_fn f_out = av_pixelutils_get_sad_fn(n, n, align, ফাঁকা);

    নির্বাচন (align) {
    ক্ষেত্র 0: block1++; block2++; বিরতি;
    ক্ষেত্র 1:           block2++; বিরতি;
    ক্ষেত্র 2:                     বিরতি;
    }

    out = f_out(block1, stride1, block2, stride2);
    ref = f_ref(block1, stride1, block2, stride2);
    printf("[%s] [%c%c] SAD [%s] %dx%d=%d ref=%d\n",
           out == ref ? "OK" : "FAIL",
           align ? 'A' : 'U', align == 2 ? 'A' : 'U',
           test, 1<<n, 1<<n, out, ref);
    ফেরত out != ref;
}

স্থির পূর্ণসংখ্যা run_test(ধ্রুবক অক্ষর *test,
                    ধ্রুবক uint8_t *b1, ধ্রুবক uint8_t *b2)
{
    পূর্ণসংখ্যা i, a, ret = 0;

    জন্য (a = 0; a < 3; a++) {
        জন্য (i = 1; i <= FF_ARRAY_ELEMS(sad_c); i++) {
            পূর্ণসংখ্যা r = run_single_test(test, b1, W1, b2, W2, a, i);
            যদি (r)
                ret = r;
        }
    }
    ফেরত ret;
}

পূর্ণসংখ্যা প্রধান(শূন্য)
{
    পূর্ণসংখ্যা i, align, ret;
    uint8_t *buf1 = av_malloc(W1*H1);
    uint8_t *buf2 = av_malloc(W2*H2);
    uint32_t state = 0;

    যদি (!buf1 || !buf2) {
        fprintf(stderr, "malloc failure\n");
        ret = 1;
        যাও end;
    }

    check_pixfmt_descriptors();

#define RANDOM_INIT(buf, আকার_2) করো {             \
    পূর্ণসংখ্যা k;                                      \
    জন্য (k = 0; k < আকার_2; k++) {                \
        state = state * 1664525 + 1013904223;   \
        buf[k] = state>>24;                     \
    }                                           \
} যখন (0)

    /* Normal test with different strides */
    RANDOM_INIT(buf1, W1*H1);
    RANDOM_INIT(buf2, W2*H2);
    ret = run_test("random", buf1, buf2);
    যদি (ret < 0)
        যাও end;

    /* Check for maximum SAD */
    memset(buf1, 0xff, W1*H1);
    memset(buf2, 0x00, W2*H2);
    ret = run_test("max", buf1, buf2);
    যদি (ret < 0)
        যাও end;

    /* Check for minimum SAD */
    memset(buf1, 0x90, W1*H1);
    memset(buf2, 0x90, W2*H2);
    ret = run_test("min", buf1, buf2);
    যদি (ret < 0)
        যাও end;

    /* Exact buffer sizes, to check for overreads */
    জন্য (i = 1; i <= 5; i++) {
        জন্য (align = 0; align < 3; align++) {
            পূর্ণসংখ্যা size1, size2;

            av_freep(&buf1);
            av_freep(&buf2);

            size1 = size2 = 1 << (i << 1);

            নির্বাচন (align) {
            ক্ষেত্র 0: size1++; size2++; বিরতি;
            ক্ষেত্র 1:          size2++; বিরতি;
            ক্ষেত্র 2:                   বিরতি;
            }

            buf1 = av_malloc(size1);
            buf2 = av_malloc(size2);
            যদি (!buf1 || !buf2) {
                fprintf(stderr, "malloc failure\n");
                ret = 1;
                যাও end;
            }
            RANDOM_INIT(buf1, size1);
            RANDOM_INIT(buf2, size2);
            ret = run_single_test("small", buf1, 1<<i, buf2, 1<<i, align, i);
            যদি (ret < 0)
                যাও end;
        }
    }

end:
    av_free(buf1);
    av_free(buf2);
    ফেরত ret;
}
