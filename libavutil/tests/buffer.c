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

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/buffer.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ custom_free_called;
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ pool_free_called;
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ pool_alloc2_called;

ಸ್ಥಿರ ಶೂನ್ಯ custom_free(ಶೂನ್ಯ *opaque, uint8_t *data)
{
    custom_free_called = 1;
    av_free(data);
}

ಸ್ಥಿರ AVBufferRef *pool_alloc2(ಶೂನ್ಯ *opaque, size_t size)
{
    pool_alloc2_called = 1;
    ಪ್ರತ್ಯಾಗಮ av_buffer_alloc(size);
}

ಸ್ಥಿರ ಶೂನ್ಯ pool_free_cb(ಶೂನ್ಯ *opaque)
{
    pool_free_called = 1;
}

ಪೂರ್ಣಾಙ್ಕ main(ಶೂನ್ಯ)
{
    AVBufferRef *buf, *buf2;
    AVBufferPool *pool;

    /* av_buffer_alloc */
    printf("Testing av_buffer_alloc()\n");
    buf = av_buffer_alloc(64);
    ಯದಿ (buf) {
        printf("alloc: size=%zu data=%s\n", buf->size, buf->data ? "set" : "null");
        printf("writable: %d\n", av_buffer_is_writable(buf));
        printf("refcount: %d\n", av_buffer_get_ref_ಎಣಿಕೆ(buf));
        av_buffer_unref(&buf);
        printf("after unref: %s\n", buf == ರಿಕ್ತ ? "null" : "leaked");
    }

    /* av_buffer_allocz */
    printf("\nTesting av_buffer_allocz()\n");
    buf = av_buffer_allocz(16);
    ಯದಿ (buf) {
        ಪೂರ್ಣಾಙ್ಕ zeroed = 1;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < 16; i++)
            ಯದಿ (buf->data[i] != 0) zeroed = 0;
        printf("allocz: zeroed=%s\n", zeroed ? "yes" : "no");
        av_buffer_unref(&buf);
    }

    /* av_buffer_create with custom free */
    printf("\nTesting av_buffer_create()\n");
    {
        uint8_t *data = av_malloc(32);
        ಯದಿ (data) {
            custom_free_called = 0;
            buf = av_buffer_create(data, 32, custom_free, ರಿಕ್ತ, 0);
            ಯದಿ (buf) {
                printf("create: size=%zu\n", buf->size);
                printf("opaque: %s\n",
                       av_buffer_get_opaque(buf) == ರಿಕ್ತ ? "null" : "set");
                av_buffer_unref(&buf);
                printf("custom_free called: %s\n",
                       custom_free_called ? "yes" : "no");
            } ಅನ್ಯಥಾ {
                av_free(data);
            }
        }
    }

    /* av_buffer_create with READONLY flag */
    printf("\nTesting AV_BUFFER_FLAG_READONLY\n");
    {
        uint8_t *data = av_malloc(16);
        ಯದಿ (data) {
            buf = av_buffer_create(data, 16, custom_free, ರಿಕ್ತ,
                                   AV_BUFFER_FLAG_READONLY);
            ಯದಿ (buf) {
                printf("readonly writable: %d\n", av_buffer_is_writable(buf));
                av_buffer_unref(&buf);
            } ಅನ್ಯಥಾ {
                av_free(data);
            }
        }
    }

    /* av_buffer_ref and refcounting */
    printf("\nTesting av_buffer_ref()\n");
    buf = av_buffer_alloc(32);
    ಯದಿ (buf) {
        buf->data[0] = 0xAB;
        buf2 = av_buffer_ref(buf);
        ಯದಿ (buf2) {
            printf("ref: refcount=%d\n", av_buffer_get_ref_ಎಣಿಕೆ(buf));
            printf("shared data: %s\n",
                   buf2->data[0] == 0xAB ? "yes" : "no");
            printf("writable after ref: %d\n", av_buffer_is_writable(buf));
            av_buffer_unref(&buf2);
            printf("refcount after unref: %d\n", av_buffer_get_ref_ಎಣಿಕೆ(buf));
            printf("writable after unref: %d\n", av_buffer_is_writable(buf));
        }
        av_buffer_unref(&buf);
    }

    /* av_buffer_make_writable */
    printf("\nTesting av_buffer_make_writable()\n");
    buf = av_buffer_alloc(16);
    ಯದಿ (buf) {
        buf->data[0] = 0xCD;
        buf2 = av_buffer_ref(buf);
        ಯದಿ (buf2) {
            ಪೂರ್ಣಾಙ್ಕ ret = av_buffer_make_writable(&buf2);
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
    ಯದಿ (buf) {
        memset(buf->data, 0xEF, 16);
        av_buffer_realloc(&buf, 32);
        ಯದಿ (buf) {
            printf("realloc: size=%zu\n", buf->size);
            printf("data preserved: %s\n",
                   buf->data[0] == 0xEF ? "yes" : "no");
        }
        av_buffer_unref(&buf);
    }
    /* realloc from NULL */
    buf = ರಿಕ್ತ;
    av_buffer_realloc(&buf, 8);
    printf("realloc from null: %s\n", buf ? "OK" : "FAIL");
    av_buffer_unref(&buf);

    /* av_buffer_replace */
    printf("\nTesting av_buffer_replace()\n");
    buf = av_buffer_alloc(8);
    buf2 = av_buffer_alloc(8);
    ಯದಿ (buf && buf2) {
        buf->data[0] = 0x11;
        buf2->data[0] = 0x22;
        av_buffer_replace(&buf, buf2);
        printf("replace: data=0x%02x\n", buf->data[0]);
        printf("refcount: %d\n", av_buffer_get_ref_ಎಣಿಕೆ(buf2));
    }
    av_buffer_unref(&buf);
    av_buffer_unref(&buf2);

    /* replace with NULL */
    buf = av_buffer_alloc(8);
    ಯದಿ (buf) {
        av_buffer_replace(&buf, ರಿಕ್ತ);
        printf("replace with null: %s\n", buf == ರಿಕ್ತ ? "OK" : "FAIL");
    }

    /* av_buffer_pool */
    printf("\nTesting av_buffer_pool()\n");
    pool = av_buffer_pool_init(64, ರಿಕ್ತ);
    ಯದಿ (pool) {
        buf = av_buffer_pool_get(pool);
        ಯದಿ (buf) {
            printf("pool get: size=%zu\n", buf->size);
            av_buffer_unref(&buf);
        }
        /* get again -- should reuse the released buffer */
        buf = av_buffer_pool_get(pool);
        ಯದಿ (buf) {
            printf("pool reuse: size=%zu\n", buf->size);
            av_buffer_unref(&buf);
        }
        av_buffer_pool_uninit(&pool);
        printf("pool uninit: %s\n", pool == ರಿಕ್ತ ? "OK" : "FAIL");
    }

    /* av_buffer_pool_init2 with custom alloc and pool_free callbacks */
    printf("\nTesting av_buffer_pool_init2()\n");
    pool_alloc2_called = 0;
    pool_free_called = 0;
    pool = av_buffer_pool_init2(64, ರಿಕ್ತ, pool_alloc2, pool_free_cb);
    ಯದಿ (pool) {
        buf = av_buffer_pool_get(pool);
        ಯದಿ (buf) {
            printf("pool2 get: size=%zu\n", buf->size);
            printf("alloc2 called: %s\n", pool_alloc2_called ? "yes" : "no");
            printf("pool_buffer_get_opaque: %s\n",
                   av_buffer_pool_buffer_get_opaque(buf) == ರಿಕ್ತ ? "null" : "set");
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
    pool = av_buffer_pool_init(64, ರಿಕ್ತ);
    printf("pool init OOM: %s\n", pool ? "FAIL" : "OK");
    av_buffer_pool_uninit(&pool);
    av_max_alloc(INT_MAX);

    buf = av_buffer_alloc(16);
    ಯದಿ (buf) {
        av_max_alloc(1);
        buf2 = av_buffer_ref(buf);
        printf("ref OOM: %s\n", buf2 ? "FAIL" : "OK");
        av_buffer_unref(&buf2);
        printf("realloc OOM: %s\n",
               av_buffer_realloc(&buf, 1024) < 0 ? "OK" : "FAIL");
        av_max_alloc(INT_MAX);
        av_buffer_unref(&buf);
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}
