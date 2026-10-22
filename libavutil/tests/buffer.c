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

#شامل <limits.h>
#شامل <stdio.h>
#شامل <string.h>

#شامل "libavutil/buffer.h"
#شامل "libavutil/mem.h"

ایستا صحیح custom_free_called;
ایستا صحیح pool_free_called;
ایستا صحیح pool_alloc2_called;

ایستا تهی custom_free(تهی *opaque, uint8_t *data)
{
    custom_free_called = 1;
    av_free(data);
}

ایستا AVBufferRef *pool_alloc2(تهی *opaque, size_t size)
{
    pool_alloc2_called = 1;
    بازگشت av_buffer_alloc(size);
}

ایستا تهی pool_free_cb(تهی *opaque)
{
    pool_free_called = 1;
}

صحیح اصلی(تهی)
{
    AVBufferRef *buf, *buf2;
    AVBufferPool *pool;

    /* av_buffer_alloc */
    printf("Testing av_buffer_alloc()\n");
    buf = av_buffer_alloc(64);
    اگر (buf) {
        printf("alloc: size=%zu data=%s\n", buf->size, buf->data ? "set" : "null");
        printf("writable: %d\n", av_buffer_is_writable(buf));
        printf("refcount: %d\n", av_buffer_get_ref_شمار(buf));
        av_buffer_unref(&buf);
        printf("after unref: %s\n", buf == پوچ ? "null" : "leaked");
    }

    /* av_buffer_allocz */
    printf("\nTesting av_buffer_allocz()\n");
    buf = av_buffer_allocz(16);
    اگر (buf) {
        صحیح zeroed = 1;
        برای (صحیح i = 0; i < 16; i++)
            اگر (buf->data[i] != 0) zeroed = 0;
        printf("allocz: zeroed=%s\n", zeroed ? "yes" : "no");
        av_buffer_unref(&buf);
    }

    /* av_buffer_create with custom free */
    printf("\nTesting av_buffer_create()\n");
    {
        uint8_t *data = av_malloc(32);
        اگر (data) {
            custom_free_called = 0;
            buf = av_buffer_create(data, 32, custom_free, پوچ, 0);
            اگر (buf) {
                printf("create: size=%zu\n", buf->size);
                printf("opaque: %s\n",
                       av_buffer_get_opaque(buf) == پوچ ? "null" : "set");
                av_buffer_unref(&buf);
                printf("custom_free called: %s\n",
                       custom_free_called ? "yes" : "no");
            } وگرنه {
                av_free(data);
            }
        }
    }

    /* av_buffer_create with READONLY flag */
    printf("\nTesting AV_BUFFER_FLAG_READONLY\n");
    {
        uint8_t *data = av_malloc(16);
        اگر (data) {
            buf = av_buffer_create(data, 16, custom_free, پوچ,
                                   AV_BUFFER_FLAG_READONLY);
            اگر (buf) {
                printf("readonly writable: %d\n", av_buffer_is_writable(buf));
                av_buffer_unref(&buf);
            } وگرنه {
                av_free(data);
            }
        }
    }

    /* av_buffer_ref and refcounting */
    printf("\nTesting av_buffer_ref()\n");
    buf = av_buffer_alloc(32);
    اگر (buf) {
        buf->data[0] = 0xAB;
        buf2 = av_buffer_ref(buf);
        اگر (buf2) {
            printf("ref: refcount=%d\n", av_buffer_get_ref_شمار(buf));
            printf("shared data: %s\n",
                   buf2->data[0] == 0xAB ? "yes" : "no");
            printf("writable after ref: %d\n", av_buffer_is_writable(buf));
            av_buffer_unref(&buf2);
            printf("refcount after unref: %d\n", av_buffer_get_ref_شمار(buf));
            printf("writable after unref: %d\n", av_buffer_is_writable(buf));
        }
        av_buffer_unref(&buf);
    }

    /* av_buffer_make_writable */
    printf("\nTesting av_buffer_make_writable()\n");
    buf = av_buffer_alloc(16);
    اگر (buf) {
        buf->data[0] = 0xCD;
        buf2 = av_buffer_ref(buf);
        اگر (buf2) {
            صحیح ret = av_buffer_make_writable(&buf2);
            printf("make_writable ret: %d\n", ret >= 0);
            printf("data preserved: %s\n",
                   buf2->data[0] == 0xCD ? "yes" : "no");
            printf("now writable: %d\n", av_buffer_is_writable(buf2));
            printf("original still valid: %s\n",
                   buf->data[0] == 0xCD ? "yes" : "no");
            av_buffer_unref(&buf2);
        }
        av_buffer_unref(&buf);
    }

    /* av_buffer_realloc */
    printf("\nTesting av_buffer_realloc()\n");
    buf = av_buffer_alloc(16);
    اگر (buf) {
        memset(buf->data, 0xEF, 16);
        av_buffer_realloc(&buf, 32);
        اگر (buf) {
            printf("realloc: size=%zu\n", buf->size);
            printf("data preserved: %s\n",
                   buf->data[0] == 0xEF ? "yes" : "no");
        }
        av_buffer_unref(&buf);
    }
    /* realloc from NULL */
    buf = پوچ;
    av_buffer_realloc(&buf, 8);
    printf("realloc from null: %s\n", buf ? "OK" : "FAIL");
    av_buffer_unref(&buf);

    /* av_buffer_replace */
    printf("\nTesting av_buffer_replace()\n");
    buf = av_buffer_alloc(8);
    buf2 = av_buffer_alloc(8);
    اگر (buf && buf2) {
        buf->data[0] = 0x11;
        buf2->data[0] = 0x22;
        av_buffer_replace(&buf, buf2);
        printf("replace: data=0x%02x\n", buf->data[0]);
        printf("refcount: %d\n", av_buffer_get_ref_شمار(buf2));
    }
    av_buffer_unref(&buf);
    av_buffer_unref(&buf2);

    /* replace with NULL */
    buf = av_buffer_alloc(8);
    اگر (buf) {
        av_buffer_replace(&buf, پوچ);
        printf("replace with null: %s\n", buf == پوچ ? "OK" : "FAIL");
    }

    /* av_buffer_pool */
    printf("\nTesting av_buffer_pool()\n");
    pool = av_buffer_pool_init(64, پوچ);
    اگر (pool) {
        buf = av_buffer_pool_get(pool);
        اگر (buf) {
            printf("pool get: size=%zu\n", buf->size);
            av_buffer_unref(&buf);
        }
        /* get again -- should reuse the released buffer */
        buf = av_buffer_pool_get(pool);
        اگر (buf) {
            printf("pool reuse: size=%zu\n", buf->size);
            av_buffer_unref(&buf);
        }
        av_buffer_pool_uninit(&pool);
        printf("pool uninit: %s\n", pool == پوچ ? "OK" : "FAIL");
    }

    /* av_buffer_pool_init2 with custom alloc and pool_free callbacks */
    printf("\nTesting av_buffer_pool_init2()\n");
    pool_alloc2_called = 0;
    pool_free_called = 0;
    pool = av_buffer_pool_init2(64, پوچ, pool_alloc2, pool_free_cb);
    اگر (pool) {
        buf = av_buffer_pool_get(pool);
        اگر (buf) {
            printf("pool2 get: size=%zu\n", buf->size);
            printf("alloc2 called: %s\n", pool_alloc2_called ? "yes" : "no");
            printf("pool_buffer_get_opaque: %s\n",
                   av_buffer_pool_buffer_get_opaque(buf) == پوچ ? "null" : "set");
            av_buffer_unref(&buf);
        }
        av_buffer_pool_uninit(&pool);
        printf("pool_free called: %s\n", pool_free_called ? "yes" : "no");
    }

    /* OOM paths via av_max_alloc */
    printf("\nTesting OOM paths\n");
    av_max_alloc(1);
    buf = av_buffer_alloc(64);
    printf("alloc OOM: %s\n", buf ? "FAIL" : "OK");
    av_buffer_unref(&buf);
    buf = av_buffer_allocz(64);
    printf("allocz OOM: %s\n", buf ? "FAIL" : "OK");
    av_buffer_unref(&buf);
    pool = av_buffer_pool_init(64, پوچ);
    printf("pool init OOM: %s\n", pool ? "FAIL" : "OK");
    av_buffer_pool_uninit(&pool);
    av_max_alloc(INT_MAX);

    buf = av_buffer_alloc(16);
    اگر (buf) {
        av_max_alloc(1);
        buf2 = av_buffer_ref(buf);
        printf("ref OOM: %s\n", buf2 ? "FAIL" : "OK");
        av_buffer_unref(&buf2);
        printf("realloc OOM: %s\n",
               av_buffer_realloc(&buf, 1024) < 0 ? "OK" : "FAIL");
        av_max_alloc(INT_MAX);
        av_buffer_unref(&buf);
    }

    بازگشت 0;
}
