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

#شامل <stdio.h>

#شامل "libavutil/avassert.h"
#شامل "libavutil/internal.h"
#شامل "libavutil/log.h"
#شامل "libavutil/mem.h"
#شامل "libavutil/pixdesc.h"
#شامل "libavutil/pixelutils.c"
#شامل "libavutil/pixfmt.h"

#تعریف_کرو W1 320
#تعریف_کرو H1 240
#تعریف_کرو W2 640
#تعریف_کرو H2 480

ساکن خالی check_pixfmt_descriptors(خالی)
{
    ثابت AVPixFmtDescriptor *d, *آخری = تہی;
    صحیح i;

    برائے (i = AV_PIX_FMT_NONE, d = تہی; i++, d = av_pix_fmt_desc_اگلا(d);) {
        uint8_t fill[4][8 + 6 + 3] = {{ 0 }};
        uint8_t *ڈیٹا[4] = { fill[0], fill[1], fill[2], fill[3] };
        صحیح linesize[4] = { 0, 0, 0, 0 };
        uint16_t tmp[2];

        av_assert0(d->name && d->name[0]);
        av_log(تہی, AV_LOG_INFO, "Checking: %s\n", d->name);
        av_assert0(d->log2_chroma_w <= 3);
        av_assert0(d->log2_chroma_h <= 3);
        av_assert0(d->nb_components <= 4);
        av_assert0(d->nb_components || (d->flags & AV_PIX_FMT_FLAG_HWACCEL));
        av_assert0(av_get_pix_fmt(d->name) == av_pix_fmt_desc_get_id(d));

        /* The following two checks as well as the one after the loop
         * would need to be changed if we changed the way the descriptors
         * are stored. */
        av_assert0(i == av_pix_fmt_desc_get_id(d));
        av_assert0(!آخری || آخری + 1 == d);

        برائے (صحیح j = 0; j < FF_ARRAY_ELEMS(d->comp); j++) {
            ثابت AVComponentDescriptor *c = &d->comp[j];
            اگر (!c->گہرائی) {
                جاری;
            }
            اگر (d->flags & AV_PIX_FMT_FLAG_BITSTREAM) {
                av_assert0(c->قدم >= c->گہرائی);
            } ورنہ {
                av_assert0(8*c->قدم >= c->گہرائی);
            }
            اگر (d->flags & AV_PIX_FMT_FLAG_BAYER)
                جاری;
            av_read_image_سطر(tmp, (خالی*)ڈیٹا, linesize, d, 0, 0, j, 2, 0);
            av_assert0(tmp[0] == 0 && tmp[1] == 0);
            tmp[0] = tmp[1] = (1ULL << c->گہرائی) - 1;
            av_write_image_سطر(tmp, ڈیٹا, linesize, d, 0, 0, j, 2);
        }
        آخری = d;
    }
    av_assert0(i == AV_PIX_FMT_NB);
}

ساکن صحیح تسلسل_single_test(ثابت حرف *test,
                           ثابت uint8_t *block1, ptrdiff_t stride1,
                           ثابت uint8_t *block2, ptrdiff_t stride2,
                           صحیح align, صحیح n)
{
    صحیح برآمد, ref;
    av_pixelutils_sad_fn f_ref = sad_c[n - 1];
    av_pixelutils_sad_fn f_برآمد = av_pixelutils_get_sad_fn(n, n, align, تہی);

    انتخاب (align) {
    حالت 0: block1++; block2++; توڑو;
    حالت 1:           block2++; توڑو;
    حالت 2:                     توڑو;
    }

    برآمد = f_برآمد(block1, stride1, block2, stride2);
    ref = f_ref(block1, stride1, block2, stride2);
    لکھو("[%s] [%c%c] SAD [%s] %dx%d=%d ref=%d\n",
           برآمد == ref ? "OK" : "FAIL",
           align ? 'A' : 'U', align == 2 ? 'A' : 'U',
           test, 1<<n, 1<<n, برآمد, ref);
    واپس برآمد != ref;
}

ساکن صحیح تسلسل_test(ثابت حرف *test,
                    ثابت uint8_t *b1, ثابت uint8_t *b2)
{
    صحیح i, a, ret = 0;

    برائے (a = 0; a < 3; a++) {
        برائے (i = 1; i <= FF_ARRAY_ELEMS(sad_c); i++) {
            صحیح r = تسلسل_single_test(test, b1, W1, b2, W2, a, i);
            اگر (r)
                ret = r;
        }
    }
    واپس ret;
}

صحیح مین(خالی)
{
    صحیح i, align, ret;
    uint8_t *buf1 = av_malloc(W1*H1);
    uint8_t *buf2 = av_malloc(W2*H2);
    uint32_t state = 0;

    اگر (!buf1 || !buf2) {
        fprintf(stderr, "malloc failure\n");
        ret = 1;
        جاؤ انتہا;
    }

    check_pixfmt_descriptors();

#تعریف_کرو RANDOM_INIT(buf, سائز) کرو {             \
    صحیح k;                                      \
    برائے (k = 0; k < سائز; k++) {                \
        state = state * 1664525 + 1013904223;   \
        buf[k] = state>>24;                     \
    }                                           \
} جب (0)

    /* Normal test with different strides */
    RANDOM_INIT(buf1, W1*H1);
    RANDOM_INIT(buf2, W2*H2);
    ret = تسلسل_test("random", buf1, buf2);
    اگر (ret < 0)
        جاؤ انتہا;

    /* Check for maximum SAD */
    memset(buf1, 0xff, W1*H1);
    memset(buf2, 0x00, W2*H2);
    ret = تسلسل_test("max", buf1, buf2);
    اگر (ret < 0)
        جاؤ انتہا;

    /* Check for minimum SAD */
    memset(buf1, 0x90, W1*H1);
    memset(buf2, 0x90, W2*H2);
    ret = تسلسل_test("min", buf1, buf2);
    اگر (ret < 0)
        جاؤ انتہا;

    /* Exact buffer sizes, to check for overreads */
    برائے (i = 1; i <= 5; i++) {
        برائے (align = 0; align < 3; align++) {
            صحیح size1, size2;

            av_freep(&buf1);
            av_freep(&buf2);

            size1 = size2 = 1 << (i << 1);

            انتخاب (align) {
            حالت 0: size1++; size2++; توڑو;
            حالت 1:          size2++; توڑو;
            حالت 2:                   توڑو;
            }

            buf1 = av_malloc(size1);
            buf2 = av_malloc(size2);
            اگر (!buf1 || !buf2) {
                fprintf(stderr, "malloc failure\n");
                ret = 1;
                جاؤ انتہا;
            }
            RANDOM_INIT(buf1, size1);
            RANDOM_INIT(buf2, size2);
            ret = تسلسل_single_test("small", buf1, 1<<i, buf2, 1<<i, align, i);
            اگر (ret < 0)
                جاؤ انتہا;
        }
    }

انتہا:
    av_free(buf1);
    av_free(buf2);
    واپس ret;
}
