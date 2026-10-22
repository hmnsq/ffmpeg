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

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/buffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"

ਸਥਿਰ ਪੂਰਨ custom_free_called;
ਸਥਿਰ ਪੂਰਨ pool_free_called;
ਸਥਿਰ ਪੂਰਨ pool_alloc2_called;

ਸਥਿਰ ਖਾਲੀ custom_free(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ)
{
    custom_free_called = 1;
    av_free(ਅੰਕੜੇ);
}

ਸਥਿਰ AVBufferRef *pool_alloc2(ਖਾਲੀ *opaque, size_t ਮਾਪ)
{
    pool_alloc2_called = 1;
    ਵਾਪਸ av_ਬਫਰ_alloc(ਮਾਪ);
}

ਸਥਿਰ ਖਾਲੀ pool_free_cb(ਖਾਲੀ *opaque)
{
    pool_free_called = 1;
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    AVBufferRef *buf, *buf2;
    AVBufferPool *pool;

    /* av_buffer_alloc */
    ਲਿਖੋ("Testing av_buffer_alloc()\n");
    buf = av_ਬਫਰ_alloc(64);
    ਜੇ (buf) {
        ਲਿਖੋ("alloc: size=%zu data=%s\n", buf->ਮਾਪ, buf->ਅੰਕੜੇ ? "set" : "null");
        ਲਿਖੋ("writable: %d\n", av_ਬਫਰ_is_writable(buf));
        ਲਿਖੋ("refcount: %d\n", av_ਬਫਰ_get_ref_ਗਿਣਤੀ(buf));
        av_ਬਫਰ_unref(&buf);
        ਲਿਖੋ("after unref: %s\n", buf == ਨਿਰਾ ? "null" : "leaked");
    }

    /* av_buffer_allocz */
    ਲਿਖੋ("\nTesting av_buffer_allocz()\n");
    buf = av_ਬਫਰ_allocz(16);
    ਜੇ (buf) {
        ਪੂਰਨ zeroed = 1;
        ਲਈ (ਪੂਰਨ i = 0; i < 16; i++)
            ਜੇ (buf->ਅੰਕੜੇ[i] != 0) zeroed = 0;
        ਲਿਖੋ("allocz: zeroed=%s\n", zeroed ? "yes" : "no");
        av_ਬਫਰ_unref(&buf);
    }

    /* av_buffer_create with custom free */
    ਲਿਖੋ("\nTesting av_buffer_create()\n");
    {
        uint8_t *ਅੰਕੜੇ = av_malloc(32);
        ਜੇ (ਅੰਕੜੇ) {
            custom_free_called = 0;
            buf = av_ਬਫਰ_create(ਅੰਕੜੇ, 32, custom_free, ਨਿਰਾ, 0);
            ਜੇ (buf) {
                ਲਿਖੋ("create: size=%zu\n", buf->ਮਾਪ);
                ਲਿਖੋ("opaque: %s\n",
                       av_ਬਫਰ_get_opaque(buf) == ਨਿਰਾ ? "null" : "set");
                av_ਬਫਰ_unref(&buf);
                ਲਿਖੋ("custom_free called: %s\n",
                       custom_free_called ? "yes" : "no");
            } ਨਹੀਂਤਾਂ {
                av_free(ਅੰਕੜੇ);
            }
        }
    }

    /* av_buffer_create with READONLY flag */
    ਲਿਖੋ("\nTesting AV_BUFFER_FLAG_READONLY\n");
    {
        uint8_t *ਅੰਕੜੇ = av_malloc(16);
        ਜੇ (ਅੰਕੜੇ) {
            buf = av_ਬਫਰ_create(ਅੰਕੜੇ, 16, custom_free, ਨਿਰਾ,
                                   AV_ਬਫਰ_FLAG_READONLY);
            ਜੇ (buf) {
                ਲਿਖੋ("readonly writable: %d\n", av_ਬਫਰ_is_writable(buf));
                av_ਬਫਰ_unref(&buf);
            } ਨਹੀਂਤਾਂ {
                av_free(ਅੰਕੜੇ);
            }
        }
    }

    /* av_buffer_ref and refcounting */
    ਲਿਖੋ("\nTesting av_buffer_ref()\n");
    buf = av_ਬਫਰ_alloc(32);
    ਜੇ (buf) {
        buf->ਅੰਕੜੇ[0] = 0xAB;
        buf2 = av_ਬਫਰ_ref(buf);
        ਜੇ (buf2) {
            ਲਿਖੋ("ref: refcount=%d\n", av_ਬਫਰ_get_ref_ਗਿਣਤੀ(buf));
            ਲਿਖੋ("shared data: %s\n",
                   buf2->ਅੰਕੜੇ[0] == 0xAB ? "yes" : "no");
            ਲਿਖੋ("writable after ref: %d\n", av_ਬਫਰ_is_writable(buf));
            av_ਬਫਰ_unref(&buf2);
            ਲਿਖੋ("refcount after unref: %d\n", av_ਬਫਰ_get_ref_ਗਿਣਤੀ(buf));
            ਲਿਖੋ("writable after unref: %d\n", av_ਬਫਰ_is_writable(buf));
        }
        av_ਬਫਰ_unref(&buf);
    }

    /* av_buffer_make_writable */
    ਲਿਖੋ("\nTesting av_buffer_make_writable()\n");
    buf = av_ਬਫਰ_alloc(16);
    ਜੇ (buf) {
        buf->ਅੰਕੜੇ[0] = 0xCD;
        buf2 = av_ਬਫਰ_ref(buf);
        ਜੇ (buf2) {
            ਪੂਰਨ ret = av_ਬਫਰ_make_writable(&buf2);
            ਲਿਖੋ("make_writable ret: %d\n", ret >= 0);
            ਲਿਖੋ("data preserved: %s\n",
                   buf2->ਅੰਕੜੇ[0] == 0xCD ? "yes" : "no");
            ਲਿਖੋ("now writable: %d\n", av_ਬਫਰ_is_writable(buf2));
            ਲਿਖੋ("original still valid: %s\n",
                   buf->ਅੰਕੜੇ[0] == 0xCD ? "yes" : "no");
            av_ਬਫਰ_unref(&buf2);
        }
        av_ਬਫਰ_unref(&buf);
    }

    /* av_buffer_realloc */
    ਲਿਖੋ("\nTesting av_buffer_realloc()\n");
    buf = av_ਬਫਰ_alloc(16);
    ਜੇ (buf) {
        memset(buf->ਅੰਕੜੇ, 0xEF, 16);
        av_ਬਫਰ_realloc(&buf, 32);
        ਜੇ (buf) {
            ਲਿਖੋ("realloc: size=%zu\n", buf->ਮਾਪ);
            ਲਿਖੋ("data preserved: %s\n",
                   buf->ਅੰਕੜੇ[0] == 0xEF ? "yes" : "no");
        }
        av_ਬਫਰ_unref(&buf);
    }
    /* realloc from NULL */
    buf = ਨਿਰਾ;
    av_ਬਫਰ_realloc(&buf, 8);
    ਲਿਖੋ("realloc from null: %s\n", buf ? "OK" : "FAIL");
    av_ਬਫਰ_unref(&buf);

    /* av_buffer_replace */
    ਲਿਖੋ("\nTesting av_buffer_replace()\n");
    buf = av_ਬਫਰ_alloc(8);
    buf2 = av_ਬਫਰ_alloc(8);
    ਜੇ (buf && buf2) {
        buf->ਅੰਕੜੇ[0] = 0x11;
        buf2->ਅੰਕੜੇ[0] = 0x22;
        av_ਬਫਰ_replace(&buf, buf2);
        ਲਿਖੋ("replace: data=0x%02x\n", buf->ਅੰਕੜੇ[0]);
        ਲਿਖੋ("refcount: %d\n", av_ਬਫਰ_get_ref_ਗਿਣਤੀ(buf2));
    }
    av_ਬਫਰ_unref(&buf);
    av_ਬਫਰ_unref(&buf2);

    /* replace with NULL */
    buf = av_ਬਫਰ_alloc(8);
    ਜੇ (buf) {
        av_ਬਫਰ_replace(&buf, ਨਿਰਾ);
        ਲਿਖੋ("replace with null: %s\n", buf == ਨਿਰਾ ? "OK" : "FAIL");
    }

    /* av_buffer_pool */
    ਲਿਖੋ("\nTesting av_buffer_pool()\n");
    pool = av_ਬਫਰ_pool_init(64, ਨਿਰਾ);
    ਜੇ (pool) {
        buf = av_ਬਫਰ_pool_get(pool);
        ਜੇ (buf) {
            ਲਿਖੋ("pool get: size=%zu\n", buf->ਮਾਪ);
            av_ਬਫਰ_unref(&buf);
        }
        /* get again -- should reuse the released buffer */
        buf = av_ਬਫਰ_pool_get(pool);
        ਜੇ (buf) {
            ਲਿਖੋ("pool reuse: size=%zu\n", buf->ਮਾਪ);
            av_ਬਫਰ_unref(&buf);
        }
        av_ਬਫਰ_pool_uninit(&pool);
        ਲਿਖੋ("pool uninit: %s\n", pool == ਨਿਰਾ ? "OK" : "FAIL");
    }

    /* av_buffer_pool_init2 with custom alloc and pool_free callbacks */
    ਲਿਖੋ("\nTesting av_buffer_pool_init2()\n");
    pool_alloc2_called = 0;
    pool_free_called = 0;
    pool = av_ਬਫਰ_pool_init2(64, ਨਿਰਾ, pool_alloc2, pool_free_cb);
    ਜੇ (pool) {
        buf = av_ਬਫਰ_pool_get(pool);
        ਜੇ (buf) {
            ਲਿਖੋ("pool2 get: size=%zu\n", buf->ਮਾਪ);
            ਲਿਖੋ("alloc2 called: %s\n", pool_alloc2_called ? "yes" : "no");
            ਲਿਖੋ("pool_buffer_get_opaque: %s\n",
                   av_ਬਫਰ_pool_ਬਫਰ_get_opaque(buf) == ਨਿਰਾ ? "null" : "set");
            av_ਬਫਰ_unref(&buf);
        }
        av_ਬਫਰ_pool_uninit(&pool);
        ਲਿਖੋ("pool_free called: %s\n", pool_free_called ? "yes" : "no");
    }

    /* OOM paths via av_max_alloc */
    ਲਿਖੋ("\nTesting OOM paths\n");
    av_max_alloc(1);
    buf = av_ਬਫਰ_alloc(64);
    ਲਿਖੋ("alloc OOM: %s\n", buf ? "FAIL" : "OK");
    av_ਬਫਰ_unref(&buf);
    buf = av_ਬਫਰ_allocz(64);
    ਲਿਖੋ("allocz OOM: %s\n", buf ? "FAIL" : "OK");
    av_ਬਫਰ_unref(&buf);
    pool = av_ਬਫਰ_pool_init(64, ਨਿਰਾ);
    ਲਿਖੋ("pool init OOM: %s\n", pool ? "FAIL" : "OK");
    av_ਬਫਰ_pool_uninit(&pool);
    av_max_alloc(ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);

    buf = av_ਬਫਰ_alloc(16);
    ਜੇ (buf) {
        av_max_alloc(1);
        buf2 = av_ਬਫਰ_ref(buf);
        ਲਿਖੋ("ref OOM: %s\n", buf2 ? "FAIL" : "OK");
        av_ਬਫਰ_unref(&buf2);
        ਲਿਖੋ("realloc OOM: %s\n",
               av_ਬਫਰ_realloc(&buf, 1024) < 0 ? "OK" : "FAIL");
        av_max_alloc(ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);
        av_ਬਫਰ_unref(&buf);
    }

    ਵਾਪਸ 0;
}
