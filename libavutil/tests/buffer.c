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

#অন্তর্ভাব <limits.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "libavutil/buffer.h"
#অন্তর্ভাব "libavutil/mem.h"

স্থির পূর্ণসংখ্যা custom_free_called;
স্থির পূর্ণসংখ্যা pool_free_called;
স্থির পূর্ণসংখ্যা pool_alloc2_called;

স্থির শূন্য custom_free(শূন্য *opaque, uint8_t *তথ্য)
{
    custom_free_called = 1;
    av_free(তথ্য);
}

স্থির AVBufferRef *pool_alloc2(শূন্য *opaque, size_t আকার_2)
{
    pool_alloc2_called = 1;
    ফেরত av_বাফার_alloc(আকার_2);
}

স্থির শূন্য pool_free_cb(শূন্য *opaque)
{
    pool_free_called = 1;
}

পূর্ণসংখ্যা প্রধান(শূন্য)
{
    AVBufferRef *buf, *buf2;
    AVBufferPool *pool;

    /* av_buffer_alloc */
    printf("Testing av_buffer_alloc()\n");
    buf = av_বাফার_alloc(64);
    যদি (buf) {
        printf("alloc: size=%zu data=%s\n", buf->আকার_2, buf->তথ্য ? "set" : "null");
        printf("writable: %d\n", av_বাফার_is_writable(buf));
        printf("refcount: %d\n", av_বাফার_get_ref_গুনতি(buf));
        av_বাফার_unref(&buf);
        printf("after unref: %s\n", buf == ফাঁকা ? "null" : "leaked");
    }

    /* av_buffer_allocz */
    printf("\nTesting av_buffer_allocz()\n");
    buf = av_বাফার_allocz(16);
    যদি (buf) {
        পূর্ণসংখ্যা zeroed = 1;
        জন্য (পূর্ণসংখ্যা i = 0; i < 16; i++)
            যদি (buf->তথ্য[i] != 0) zeroed = 0;
        printf("allocz: zeroed=%s\n", zeroed ? "yes" : "no");
        av_বাফার_unref(&buf);
    }

    /* av_buffer_create with custom free */
    printf("\nTesting av_buffer_create()\n");
    {
        uint8_t *তথ্য = av_malloc(32);
        যদি (তথ্য) {
            custom_free_called = 0;
            buf = av_বাফার_create(তথ্য, 32, custom_free, ফাঁকা, 0);
            যদি (buf) {
                printf("create: size=%zu\n", buf->আকার_2);
                printf("opaque: %s\n",
                       av_বাফার_get_opaque(buf) == ফাঁকা ? "null" : "set");
                av_বাফার_unref(&buf);
                printf("custom_free called: %s\n",
                       custom_free_called ? "yes" : "no");
            } অন্যথা {
                av_free(তথ্য);
            }
        }
    }

    /* av_buffer_create with READONLY flag */
    printf("\nTesting AV_BUFFER_FLAG_READONLY\n");
    {
        uint8_t *তথ্য = av_malloc(16);
        যদি (তথ্য) {
            buf = av_বাফার_create(তথ্য, 16, custom_free, ফাঁকা,
                                   AV_বাফার_FLAG_READONLY);
            যদি (buf) {
                printf("readonly writable: %d\n", av_বাফার_is_writable(buf));
                av_বাফার_unref(&buf);
            } অন্যথা {
                av_free(তথ্য);
            }
        }
    }

    /* av_buffer_ref and refcounting */
    printf("\nTesting av_buffer_ref()\n");
    buf = av_বাফার_alloc(32);
    যদি (buf) {
        buf->তথ্য[0] = 0xAB;
        buf2 = av_বাফার_ref(buf);
        যদি (buf2) {
            printf("ref: refcount=%d\n", av_বাফার_get_ref_গুনতি(buf));
            printf("shared data: %s\n",
                   buf2->তথ্য[0] == 0xAB ? "yes" : "no");
            printf("writable after ref: %d\n", av_বাফার_is_writable(buf));
            av_বাফার_unref(&buf2);
            printf("refcount after unref: %d\n", av_বাফার_get_ref_গুনতি(buf));
            printf("writable after unref: %d\n", av_বাফার_is_writable(buf));
        }
        av_বাফার_unref(&buf);
    }

    /* av_buffer_make_writable */
    printf("\nTesting av_buffer_make_writable()\n");
    buf = av_বাফার_alloc(16);
    যদি (buf) {
        buf->তথ্য[0] = 0xCD;
        buf2 = av_বাফার_ref(buf);
        যদি (buf2) {
            পূর্ণসংখ্যা ret = av_বাফার_make_writable(&buf2);
            printf("make_writable ret: %d\n", ret >= 0);
            printf("data preserved: %s\n",
                   buf2->তথ্য[0] == 0xCD ? "yes" : "no");
            printf("now writable: %d\n", av_বাফার_is_writable(buf2));
            printf("original still valid: %s\n",
                   buf->তথ্য[0] == 0xCD ? "yes" : "no");
            av_বাফার_unref(&buf2);
        }
        av_বাফার_unref(&buf);
    }

    /* av_buffer_realloc */
    printf("\nTesting av_buffer_realloc()\n");
    buf = av_বাফার_alloc(16);
    যদি (buf) {
        memset(buf->তথ্য, 0xEF, 16);
        av_বাফার_realloc(&buf, 32);
        যদি (buf) {
            printf("realloc: size=%zu\n", buf->আকার_2);
            printf("data preserved: %s\n",
                   buf->তথ্য[0] == 0xEF ? "yes" : "no");
        }
        av_বাফার_unref(&buf);
    }
    /* realloc from NULL */
    buf = ফাঁকা;
    av_বাফার_realloc(&buf, 8);
    printf("realloc from null: %s\n", buf ? "OK" : "FAIL");
    av_বাফার_unref(&buf);

    /* av_buffer_replace */
    printf("\nTesting av_buffer_replace()\n");
    buf = av_বাফার_alloc(8);
    buf2 = av_বাফার_alloc(8);
    যদি (buf && buf2) {
        buf->তথ্য[0] = 0x11;
        buf2->তথ্য[0] = 0x22;
        av_বাফার_replace(&buf, buf2);
        printf("replace: data=0x%02x\n", buf->তথ্য[0]);
        printf("refcount: %d\n", av_বাফার_get_ref_গুনতি(buf2));
    }
    av_বাফার_unref(&buf);
    av_বাফার_unref(&buf2);

    /* replace with NULL */
    buf = av_বাফার_alloc(8);
    যদি (buf) {
        av_বাফার_replace(&buf, ফাঁকা);
        printf("replace with null: %s\n", buf == ফাঁকা ? "OK" : "FAIL");
    }

    /* av_buffer_pool */
    printf("\nTesting av_buffer_pool()\n");
    pool = av_বাফার_pool_init(64, ফাঁকা);
    যদি (pool) {
        buf = av_বাফার_pool_get(pool);
        যদি (buf) {
            printf("pool get: size=%zu\n", buf->আকার_2);
            av_বাফার_unref(&buf);
        }
        /* get again -- should reuse the released buffer */
        buf = av_বাফার_pool_get(pool);
        যদি (buf) {
            printf("pool reuse: size=%zu\n", buf->আকার_2);
            av_বাফার_unref(&buf);
        }
        av_বাফার_pool_uninit(&pool);
        printf("pool uninit: %s\n", pool == ফাঁকা ? "OK" : "FAIL");
    }

    /* av_buffer_pool_init2 with custom alloc and pool_free callbacks */
    printf("\nTesting av_buffer_pool_init2()\n");
    pool_alloc2_called = 0;
    pool_free_called = 0;
    pool = av_বাফার_pool_init2(64, ফাঁকা, pool_alloc2, pool_free_cb);
    যদি (pool) {
        buf = av_বাফার_pool_get(pool);
        যদি (buf) {
            printf("pool2 get: size=%zu\n", buf->আকার_2);
            printf("alloc2 called: %s\n", pool_alloc2_called ? "yes" : "no");
            printf("pool_buffer_get_opaque: %s\n",
                   av_বাফার_pool_বাফার_get_opaque(buf) == ফাঁকা ? "null" : "set");
            av_বাফার_unref(&buf);
        }
        av_বাফার_pool_uninit(&pool);
        printf("pool_free called: %s\n", pool_free_called ? "yes" : "no");
    }

    /* OOM paths via av_max_alloc */
    printf("\nTesting OOM paths\n");
    av_max_alloc(1);
    buf = av_বাফার_alloc(64);
    printf("alloc OOM: %s\n", buf ? "FAIL" : "OK");
    av_বাফার_unref(&buf);
    buf = av_বাফার_allocz(64);
    printf("allocz OOM: %s\n", buf ? "FAIL" : "OK");
    av_বাফার_unref(&buf);
    pool = av_বাফার_pool_init(64, ফাঁকা);
    printf("pool init OOM: %s\n", pool ? "FAIL" : "OK");
    av_বাফার_pool_uninit(&pool);
    av_max_alloc(INT_MAX);

    buf = av_বাফার_alloc(16);
    যদি (buf) {
        av_max_alloc(1);
        buf2 = av_বাফার_ref(buf);
        printf("ref OOM: %s\n", buf2 ? "FAIL" : "OK");
        av_বাফার_unref(&buf2);
        printf("realloc OOM: %s\n",
               av_বাফার_realloc(&buf, 1024) < 0 ? "OK" : "FAIL");
        av_max_alloc(INT_MAX);
        av_বাফার_unref(&buf);
    }

    ফেরত 0;
}
