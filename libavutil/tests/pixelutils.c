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

#अन्तर्भाव <stdio.h>

#अन्तर्भाव "libavutil/avassert.h"
#अन्तर्भाव "libavutil/internal.h"
#अन्तर्भाव "libavutil/log.h"
#अन्तर्भाव "libavutil/mem.h"
#अन्तर्भाव "libavutil/pixdesc.h"
#अन्तर्भाव "libavutil/pixelutils.c"
#अन्तर्भाव "libavutil/pixfmt.h"

#define W1 320
#define H1 240
#define W2 640
#define H2 480

स्थिर शून्य check_pixfmt_descriptors(शून्य)
{
    स्थिरांक AVPixFmtDescriptor *d, *last = रिक्त;
    पूर्णांक i;

    साठी (i = AV_PIX_FMT_NONE, d = रिक्त; i++, d = av_pix_fmt_desc_next(d);) {
        uint8_t fill[4][8 + 6 + 3] = {{ 0 }};
        uint8_t *data[4] = { fill[0], fill[1], fill[2], fill[3] };
        पूर्णांक linesize[4] = { 0, 0, 0, 0 };
        uint16_t tmp[2];

        av_assert0(d->name && d->name[0]);
        av_log(रिक्त, AV_LOG_INFO, "Checking: %s\n", d->name);
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

        साठी (पूर्णांक j = 0; j < FF_ARRAY_ELEMS(d->comp); j++) {
            स्थिरांक AVComponentDescriptor *c = &d->comp[j];
            जर (!c->depth) {
                सुरूठेवा;
            }
            जर (d->flags & AV_PIX_FMT_FLAG_BITSTREAM) {
                av_assert0(c->step >= c->depth);
            } अन्यथा {
                av_assert0(8*c->step >= c->depth);
            }
            जर (d->flags & AV_PIX_FMT_FLAG_BAYER)
                सुरूठेवा;
            av_read_image_ओळ(tmp, (शून्य*)data, linesize, d, 0, 0, j, 2, 0);
            av_assert0(tmp[0] == 0 && tmp[1] == 0);
            tmp[0] = tmp[1] = (1ULL << c->depth) - 1;
            av_write_image_ओळ(tmp, data, linesize, d, 0, 0, j, 2);
        }
        last = d;
    }
    av_assert0(i == AV_PIX_FMT_NB);
}

स्थिर पूर्णांक run_single_test(स्थिरांक अक्षर *test,
                           स्थिरांक uint8_t *block1, सूचक_भेद_प्रकार stride1,
                           स्थिरांक uint8_t *block2, सूचक_भेद_प्रकार stride2,
                           पूर्णांक align, पूर्णांक n)
{
    पूर्णांक out, ref;
    av_pixelutils_sad_fn f_ref = sad_c[n - 1];
    av_pixelutils_sad_fn f_out = av_pixelutils_get_sad_fn(n, n, align, रिक्त);

    निवड (align) {
    स्थिती 0: block1++; block2++; थांबा;
    स्थिती 1:           block2++; थांबा;
    स्थिती 2:                     थांबा;
    }

    out = f_out(block1, stride1, block2, stride2);
    ref = f_ref(block1, stride1, block2, stride2);
    म_लिखो("[%s] [%c%c] SAD [%s] %dx%d=%d ref=%d\n",
           out == ref ? "OK" : "FAIL",
           align ? 'A' : 'U', align == 2 ? 'A' : 'U',
           test, 1<<n, 1<<n, out, ref);
    परत out != ref;
}

स्थिर पूर्णांक run_test(स्थिरांक अक्षर *test,
                    स्थिरांक uint8_t *b1, स्थिरांक uint8_t *b2)
{
    पूर्णांक i, a, ret = 0;

    साठी (a = 0; a < 3; a++) {
        साठी (i = 1; i <= FF_ARRAY_ELEMS(sad_c); i++) {
            पूर्णांक r = run_single_test(test, b1, W1, b2, W2, a, i);
            जर (r)
                ret = r;
        }
    }
    परत ret;
}

पूर्णांक main(शून्य)
{
    पूर्णांक i, align, ret;
    uint8_t *buf1 = av_malloc(W1*H1);
    uint8_t *buf2 = av_malloc(W2*H2);
    uint32_t state = 0;

    जर (!buf1 || !buf2) {
        ख_लिखो(मानक_त्रुटि, "malloc failure\n");
        ret = 1;
        जा end;
    }

    check_pixfmt_descriptors();

#define RANDOM_INIT(buf, size) करा {             \
    पूर्णांक k;                                      \
    साठी (k = 0; k < size; k++) {                \
        state = state * 1664525 + 1013904223;   \
        buf[k] = state>>24;                     \
    }                                           \
} पर्यंत (0)

    /* Normal test with different strides */
    RANDOM_INIT(buf1, W1*H1);
    RANDOM_INIT(buf2, W2*H2);
    ret = run_test("random", buf1, buf2);
    जर (ret < 0)
        जा end;

    /* Check for maximum SAD */
    स_रखो(buf1, 0xff, W1*H1);
    स_रखो(buf2, 0x00, W2*H2);
    ret = run_test("max", buf1, buf2);
    जर (ret < 0)
        जा end;

    /* Check for minimum SAD */
    स_रखो(buf1, 0x90, W1*H1);
    स_रखो(buf2, 0x90, W2*H2);
    ret = run_test("min", buf1, buf2);
    जर (ret < 0)
        जा end;

    /* Exact buffer sizes, to check for overreads */
    साठी (i = 1; i <= 5; i++) {
        साठी (align = 0; align < 3; align++) {
            पूर्णांक size1, size2;

            av_freep(&buf1);
            av_freep(&buf2);

            size1 = size2 = 1 << (i << 1);

            निवड (align) {
            स्थिती 0: size1++; size2++; थांबा;
            स्थिती 1:          size2++; थांबा;
            स्थिती 2:                   थांबा;
            }

            buf1 = av_malloc(size1);
            buf2 = av_malloc(size2);
            जर (!buf1 || !buf2) {
                ख_लिखो(मानक_त्रुटि, "malloc failure\n");
                ret = 1;
                जा end;
            }
            RANDOM_INIT(buf1, size1);
            RANDOM_INIT(buf2, size2);
            ret = run_single_test("small", buf1, 1<<i, buf2, 1<<i, align, i);
            जर (ret < 0)
                जा end;
        }
    }

end:
    av_free(buf1);
    av_free(buf2);
    परत ret;
}
