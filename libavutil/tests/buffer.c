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

ساکن صحیح custom_free_called;
ساکن صحیح pool_free_called;
ساکن صحیح pool_alloc2_called;

ساکن خالی custom_free(خالی *opaque, uint8_t *ڈیٹا)
{
    custom_free_called = 1;
    av_free(ڈیٹا);
}

ساکن AVBufferRef *pool_alloc2(خالی *opaque, size_t سائز)
{
    pool_alloc2_called = 1;
    واپس av_بفر_alloc(سائز);
}

ساکن خالی pool_free_cb(خالی *opaque)
{
    pool_free_called = 1;
}

صحیح مین(خالی)
{
    AVBufferRef *buf, *buf2;
    AVBufferPool *pool;

    /* av_buffer_alloc */
    لکھو("Testing av_buffer_alloc()\n");
    buf = av_بفر_alloc(64);
    اگر (buf) {
        لکھو("alloc: size=%zu data=%s\n", buf->سائز, buf->ڈیٹا ? "set" : "null");
        لکھو("writable: %d\n", av_بفر_is_writable(buf));
        لکھو("refcount: %d\n", av_بفر_get_ref_گنتی(buf));
        av_بفر_unref(&buf);
        لکھو("after unref: %s\n", buf == تہی ? "null" : "leaked");
    }

    /* av_buffer_allocz */
    لکھو("\nTesting av_buffer_allocz()\n");
    buf = av_بفر_allocz(16);
    اگر (buf) {
        صحیح zeroed = 1;
        برائے (صحیح i = 0; i < 16; i++)
            اگر (buf->ڈیٹا[i] != 0) zeroed = 0;
        لکھو("allocz: zeroed=%s\n", zeroed ? "yes" : "no");
        av_بفر_unref(&buf);
    }

    /* av_buffer_create with custom free */
    لکھو("\nTesting av_buffer_create()\n");
    {
        uint8_t *ڈیٹا = av_malloc(32);
        اگر (ڈیٹا) {
            custom_free_called = 0;
            buf = av_بفر_create(ڈیٹا, 32, custom_free, تہی, 0);
            اگر (buf) {
                لکھو("create: size=%zu\n", buf->سائز);
                لکھو("opaque: %s\n",
                       av_بفر_get_opaque(buf) == تہی ? "null" : "set");
                av_بفر_unref(&buf);
                لکھو("custom_free called: %s\n",
                       custom_free_called ? "yes" : "no");
            } ورنہ {
                av_free(ڈیٹا);
            }
        }
    }

    /* av_buffer_create with READONLY flag */
    لکھو("\nTesting AV_BUFFER_FLAG_READONLY\n");
    {
        uint8_t *ڈیٹا = av_malloc(16);
        اگر (ڈیٹا) {
            buf = av_بفر_create(ڈیٹا, 16, custom_free, تہی,
                                   AV_بفر_FLAG_READONLY);
            اگر (buf) {
                لکھو("readonly writable: %d\n", av_بفر_is_writable(buf));
                av_بفر_unref(&buf);
            } ورنہ {
                av_free(ڈیٹا);
            }
        }
    }

    /* av_buffer_ref and refcounting */
    لکھو("\nTesting av_buffer_ref()\n");
    buf = av_بفر_alloc(32);
    اگر (buf) {
        buf->ڈیٹا[0] = 0xAB;
        buf2 = av_بفر_ref(buf);
        اگر (buf2) {
            لکھو("ref: refcount=%d\n", av_بفر_get_ref_گنتی(buf));
            لکھو("shared data: %s\n",
                   buf2->ڈیٹا[0] == 0xAB ? "yes" : "no");
            لکھو("writable after ref: %d\n", av_بفر_is_writable(buf));
            av_بفر_unref(&buf2);
            لکھو("refcount after unref: %d\n", av_بفر_get_ref_گنتی(buf));
            لکھو("writable after unref: %d\n", av_بفر_is_writable(buf));
        }
        av_بفر_unref(&buf);
    }

    /* av_buffer_make_writable */
    لکھو("\nTesting av_buffer_make_writable()\n");
    buf = av_بفر_alloc(16);
    اگر (buf) {
        buf->ڈیٹا[0] = 0xCD;
        buf2 = av_بفر_ref(buf);
        اگر (buf2) {
            صحیح ret = av_بفر_make_writable(&buf2);
            لکھو("make_writable ret: %d\n", ret >= 0);
            لکھو("data preserved: %s\n",
                   buf2->ڈیٹا[0] == 0xCD ? "yes" : "no");
            لکھو("now writable: %d\n", av_بفر_is_writable(buf2));
            لکھو("original still valid: %s\n",
                   buf->ڈیٹا[0] == 0xCD ? "yes" : "no");
            av_بفر_unref(&buf2);
        }
        av_بفر_unref(&buf);
    }

    /* av_buffer_realloc */
    لکھو("\nTesting av_buffer_realloc()\n");
    buf = av_بفر_alloc(16);
    اگر (buf) {
        memset(buf->ڈیٹا, 0xEF, 16);
        av_بفر_realloc(&buf, 32);
        اگر (buf) {
            لکھو("realloc: size=%zu\n", buf->سائز);
            لکھو("data preserved: %s\n",
                   buf->ڈیٹا[0] == 0xEF ? "yes" : "no");
        }
        av_بفر_unref(&buf);
    }
    /* realloc from NULL */
    buf = تہی;
    av_بفر_realloc(&buf, 8);
    لکھو("realloc from null: %s\n", buf ? "OK" : "FAIL");
    av_بفر_unref(&buf);

    /* av_buffer_replace */
    لکھو("\nTesting av_buffer_replace()\n");
    buf = av_بفر_alloc(8);
    buf2 = av_بفر_alloc(8);
    اگر (buf && buf2) {
        buf->ڈیٹا[0] = 0x11;
        buf2->ڈیٹا[0] = 0x22;
        av_بفر_replace(&buf, buf2);
        لکھو("replace: data=0x%02x\n", buf->ڈیٹا[0]);
        لکھو("refcount: %d\n", av_بفر_get_ref_گنتی(buf2));
    }
    av_بفر_unref(&buf);
    av_بفر_unref(&buf2);

    /* replace with NULL */
    buf = av_بفر_alloc(8);
    اگر (buf) {
        av_بفر_replace(&buf, تہی);
        لکھو("replace with null: %s\n", buf == تہی ? "OK" : "FAIL");
    }

    /* av_buffer_pool */
    لکھو("\nTesting av_buffer_pool()\n");
    pool = av_بفر_pool_init(64, تہی);
    اگر (pool) {
        buf = av_بفر_pool_get(pool);
        اگر (buf) {
            لکھو("pool get: size=%zu\n", buf->سائز);
            av_بفر_unref(&buf);
        }
        /* get again -- should reuse the released buffer */
        buf = av_بفر_pool_get(pool);
        اگر (buf) {
            لکھو("pool reuse: size=%zu\n", buf->سائز);
            av_بفر_unref(&buf);
        }
        av_بفر_pool_uninit(&pool);
        لکھو("pool uninit: %s\n", pool == تہی ? "OK" : "FAIL");
    }

    /* av_buffer_pool_init2 with custom alloc and pool_free callbacks */
    لکھو("\nTesting av_buffer_pool_init2()\n");
    pool_alloc2_called = 0;
    pool_free_called = 0;
    pool = av_بفر_pool_init2(64, تہی, pool_alloc2, pool_free_cb);
    اگر (pool) {
        buf = av_بفر_pool_get(pool);
        اگر (buf) {
            لکھو("pool2 get: size=%zu\n", buf->سائز);
            لکھو("alloc2 called: %s\n", pool_alloc2_called ? "yes" : "no");
            لکھو("pool_buffer_get_opaque: %s\n",
                   av_بفر_pool_بفر_get_opaque(buf) == تہی ? "null" : "set");
            av_بفر_unref(&buf);
        }
        av_بفر_pool_uninit(&pool);
        لکھو("pool_free called: %s\n", pool_free_called ? "yes" : "no");
    }

    /* OOM paths via av_max_alloc */
    لکھو("\nTesting OOM paths\n");
    av_max_alloc(1);
    buf = av_بفر_alloc(64);
    لکھو("alloc OOM: %s\n", buf ? "FAIL" : "OK");
    av_بفر_unref(&buf);
    buf = av_بفر_allocz(64);
    لکھو("allocz OOM: %s\n", buf ? "FAIL" : "OK");
    av_بفر_unref(&buf);
    pool = av_بفر_pool_init(64, تہی);
    لکھو("pool init OOM: %s\n", pool ? "FAIL" : "OK");
    av_بفر_pool_uninit(&pool);
    av_max_alloc(زیادہ_سے_زیادہ_عدد);

    buf = av_بفر_alloc(16);
    اگر (buf) {
        av_max_alloc(1);
        buf2 = av_بفر_ref(buf);
        لکھو("ref OOM: %s\n", buf2 ? "FAIL" : "OK");
        av_بفر_unref(&buf2);
        لکھو("realloc OOM: %s\n",
               av_بفر_realloc(&buf, 1024) < 0 ? "OK" : "FAIL");
        av_max_alloc(زیادہ_سے_زیادہ_عدد);
        av_بفر_unref(&buf);
    }

    واپس 0;
}
