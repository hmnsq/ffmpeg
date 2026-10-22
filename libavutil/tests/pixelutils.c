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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/pixdesc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/pixelutils.c"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/pixfmt.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ W1 320
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ H1 240
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ W2 640
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ H2 480

ਸਥਿਰ ਖਾਲੀ check_pixfmt_descriptors(ਖਾਲੀ)
{
    ਅਚਲ AVPixFmtDescriptor *d, *ਆਖਰੀ = ਨਿਰਾ;
    ਪੂਰਨ i;

    ਲਈ (i = AV_PIX_FMT_NONE, d = ਨਿਰਾ; i++, d = av_pix_fmt_desc_ਅਗਲਾ(d);) {
        uint8_t fill[4][8 + 6 + 3] = {{ 0 }};
        uint8_t *ਅੰਕੜੇ[4] = { fill[0], fill[1], fill[2], fill[3] };
        ਪੂਰਨ linesize[4] = { 0, 0, 0, 0 };
        uint16_t tmp[2];

        av_assert0(d->name && d->name[0]);
        av_log(ਨਿਰਾ, AV_LOG_INFO, "Checking: %s\n", d->name);
        av_assert0(d->log2_chroma_w <= 3);
        av_assert0(d->log2_chroma_h <= 3);
        av_assert0(d->nb_components <= 4);
        av_assert0(d->nb_components || (d->flags & AV_PIX_FMT_FLAG_HWACCEL));
        av_assert0(av_get_pix_fmt(d->name) == av_pix_fmt_desc_get_id(d));

        /* The following two checks as well as the one after the loop
         * would need to be changed if we changed the way the descriptors
         * are stored. */
        av_assert0(i == av_pix_fmt_desc_get_id(d));
        av_assert0(!ਆਖਰੀ || ਆਖਰੀ + 1 == d);

        ਲਈ (ਪੂਰਨ j = 0; j < FF_ARRAY_ELEMS(d->comp); j++) {
            ਅਚਲ AVComponentDescriptor *c = &d->comp[j];
            ਜੇ (!c->ਡੂੰਘਾਈ) {
                ਜਾਰੀ;
            }
            ਜੇ (d->flags & AV_PIX_FMT_FLAG_BITSTREAM) {
                av_assert0(c->ਕਦਮ >= c->ਡੂੰਘਾਈ);
            } ਨਹੀਂਤਾਂ {
                av_assert0(8*c->ਕਦਮ >= c->ਡੂੰਘਾਈ);
            }
            ਜੇ (d->flags & AV_PIX_FMT_FLAG_BAYER)
                ਜਾਰੀ;
            av_read_image_ਸਤਰ(tmp, (ਖਾਲੀ*)ਅੰਕੜੇ, linesize, d, 0, 0, j, 2, 0);
            av_assert0(tmp[0] == 0 && tmp[1] == 0);
            tmp[0] = tmp[1] = (1ULL << c->ਡੂੰਘਾਈ) - 1;
            av_write_image_ਸਤਰ(tmp, ਅੰਕੜੇ, linesize, d, 0, 0, j, 2);
        }
        ਆਖਰੀ = d;
    }
    av_assert0(i == AV_PIX_FMT_NB);
}

ਸਥਿਰ ਪੂਰਨ ਲੜੀਵਾਰ_single_test(ਅਚਲ ਅੱਖਰ *test,
                           ਅਚਲ uint8_t *block1, ptrdiff_t stride1,
                           ਅਚਲ uint8_t *block2, ptrdiff_t stride2,
                           ਪੂਰਨ align, ਪੂਰਨ n)
{
    ਪੂਰਨ ਬਾਹਰਲਾ, ref;
    av_pixelutils_sad_fn f_ref = sad_c[n - 1];
    av_pixelutils_sad_fn f_ਬਾਹਰਲਾ = av_pixelutils_get_sad_fn(n, n, align, ਨਿਰਾ);

    ਚੋਣ (align) {
    ਹਾਲਤ 0: block1++; block2++; ਰੋਕੋ;
    ਹਾਲਤ 1:           block2++; ਰੋਕੋ;
    ਹਾਲਤ 2:                     ਰੋਕੋ;
    }

    ਬਾਹਰਲਾ = f_ਬਾਹਰਲਾ(block1, stride1, block2, stride2);
    ref = f_ref(block1, stride1, block2, stride2);
    ਲਿਖੋ("[%s] [%c%c] SAD [%s] %dx%d=%d ref=%d\n",
           ਬਾਹਰਲਾ == ref ? "OK" : "FAIL",
           align ? 'A' : 'U', align == 2 ? 'A' : 'U',
           test, 1<<n, 1<<n, ਬਾਹਰਲਾ, ref);
    ਵਾਪਸ ਬਾਹਰਲਾ != ref;
}

ਸਥਿਰ ਪੂਰਨ ਲੜੀਵਾਰ_test(ਅਚਲ ਅੱਖਰ *test,
                    ਅਚਲ uint8_t *b1, ਅਚਲ uint8_t *b2)
{
    ਪੂਰਨ i, a, ret = 0;

    ਲਈ (a = 0; a < 3; a++) {
        ਲਈ (i = 1; i <= FF_ARRAY_ELEMS(sad_c); i++) {
            ਪੂਰਨ r = ਲੜੀਵਾਰ_single_test(test, b1, W1, b2, W2, a, i);
            ਜੇ (r)
                ret = r;
        }
    }
    ਵਾਪਸ ret;
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    ਪੂਰਨ i, align, ret;
    uint8_t *buf1 = av_malloc(W1*H1);
    uint8_t *buf2 = av_malloc(W2*H2);
    uint32_t state = 0;

    ਜੇ (!buf1 || !buf2) {
        fprintf(stderr, "malloc failure\n");
        ret = 1;
        ਜਾਓ ਸਿਰਾ;
    }

    check_pixfmt_descriptors();

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RANDOM_INIT(buf, ਮਾਪ) ਕਰੋ {             \
    ਪੂਰਨ k;                                      \
    ਲਈ (k = 0; k < ਮਾਪ; k++) {                \
        state = state * 1664525 + 1013904223;   \
        buf[k] = state>>24;                     \
    }                                           \
} ਜਦੋਂ (0)

    /* Normal test with different strides */
    RANDOM_INIT(buf1, W1*H1);
    RANDOM_INIT(buf2, W2*H2);
    ret = ਲੜੀਵਾਰ_test("random", buf1, buf2);
    ਜੇ (ret < 0)
        ਜਾਓ ਸਿਰਾ;

    /* Check for maximum SAD */
    memset(buf1, 0xff, W1*H1);
    memset(buf2, 0x00, W2*H2);
    ret = ਲੜੀਵਾਰ_test("max", buf1, buf2);
    ਜੇ (ret < 0)
        ਜਾਓ ਸਿਰਾ;

    /* Check for minimum SAD */
    memset(buf1, 0x90, W1*H1);
    memset(buf2, 0x90, W2*H2);
    ret = ਲੜੀਵਾਰ_test("min", buf1, buf2);
    ਜੇ (ret < 0)
        ਜਾਓ ਸਿਰਾ;

    /* Exact buffer sizes, to check for overreads */
    ਲਈ (i = 1; i <= 5; i++) {
        ਲਈ (align = 0; align < 3; align++) {
            ਪੂਰਨ size1, size2;

            av_freep(&buf1);
            av_freep(&buf2);

            size1 = size2 = 1 << (i << 1);

            ਚੋਣ (align) {
            ਹਾਲਤ 0: size1++; size2++; ਰੋਕੋ;
            ਹਾਲਤ 1:          size2++; ਰੋਕੋ;
            ਹਾਲਤ 2:                   ਰੋਕੋ;
            }

            buf1 = av_malloc(size1);
            buf2 = av_malloc(size2);
            ਜੇ (!buf1 || !buf2) {
                fprintf(stderr, "malloc failure\n");
                ret = 1;
                ਜਾਓ ਸਿਰਾ;
            }
            RANDOM_INIT(buf1, size1);
            RANDOM_INIT(buf2, size2);
            ret = ਲੜੀਵਾਰ_single_test("small", buf1, 1<<i, buf2, 1<<i, align, i);
            ਜੇ (ret < 0)
                ਜਾਓ ਸਿਰਾ;
        }
    }

ਸਿਰਾ:
    av_free(buf1);
    av_free(buf2);
    ਵਾਪਸ ret;
}
