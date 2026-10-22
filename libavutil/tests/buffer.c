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

#ضمن <limits.h>
#ضمن <stdio.h>
#ضمن <string.h>

#ضمن "libavutil/buffer.h"
#ضمن "libavutil/mem.h"

ساكن صحيح custom_free_called;
ساكن صحيح pool_free_called;
ساكن صحيح pool_alloc2_called;

ساكن فراغ custom_free(فراغ *opaque, uint8_t *انکڑے)
{
    custom_free_called = 1;
    av_free(انکڑے);
}

ساكن AVBufferRef *pool_alloc2(فراغ *opaque, size_t ناپ)
{
    pool_alloc2_called = 1;
    أرجع av_بفر_alloc(ناپ);
}

ساكن فراغ pool_free_cb(فراغ *opaque)
{
    pool_free_called = 1;
}

صحيح مکھ(فراغ)
{
    AVBufferRef *buf, *buf2;
    AVBufferPool *pool;

    /* av_buffer_alloc */
    لکھو("Testing av_buffer_alloc()\n");
    buf = av_بفر_alloc(64);
    إذا (buf) {
        لکھو("alloc: size=%zu data=%s\n", buf->ناپ, buf->انکڑے ? "set" : "null");
        لکھو("writable: %d\n", av_بفر_is_writable(buf));
        لکھو("refcount: %d\n", av_بفر_get_ref_گنتی(buf));
        av_بفر_unref(&buf);
        لکھو("after unref: %s\n", buf == عدم ? "null" : "leaked");
    }

    /* av_buffer_allocz */
    لکھو("\nTesting av_buffer_allocz()\n");
    buf = av_بفر_allocz(16);
    إذا (buf) {
        صحيح zeroed = 1;
        لكل (صحيح i = 0; i < 16; i++)
            إذا (buf->انکڑے[i] != 0) zeroed = 0;
        لکھو("allocz: zeroed=%s\n", zeroed ? "yes" : "no");
        av_بفر_unref(&buf);
    }

    /* av_buffer_create with custom free */
    لکھو("\nTesting av_buffer_create()\n");
    {
        uint8_t *انکڑے = av_malloc(32);
        إذا (انکڑے) {
            custom_free_called = 0;
            buf = av_بفر_create(انکڑے, 32, custom_free, عدم, 0);
            إذا (buf) {
                لکھو("create: size=%zu\n", buf->ناپ);
                لکھو("opaque: %s\n",
                       av_بفر_get_opaque(buf) == عدم ? "null" : "set");
                av_بفر_unref(&buf);
                لکھو("custom_free called: %s\n",
                       custom_free_called ? "yes" : "no");
            } وإلا {
                av_free(انکڑے);
            }
        }
    }

    /* av_buffer_create with READONLY flag */
    لکھو("\nTesting AV_BUFFER_FLAG_READONLY\n");
    {
        uint8_t *انکڑے = av_malloc(16);
        إذا (انکڑے) {
            buf = av_بفر_create(انکڑے, 16, custom_free, عدم,
                                   AV_بفر_FLAG_READONLY);
            إذا (buf) {
                لکھو("readonly writable: %d\n", av_بفر_is_writable(buf));
                av_بفر_unref(&buf);
            } وإلا {
                av_free(انکڑے);
            }
        }
    }

    /* av_buffer_ref and refcounting */
    لکھو("\nTesting av_buffer_ref()\n");
    buf = av_بفر_alloc(32);
    إذا (buf) {
        buf->انکڑے[0] = 0xAB;
        buf2 = av_بفر_ref(buf);
        إذا (buf2) {
            لکھو("ref: refcount=%d\n", av_بفر_get_ref_گنتی(buf));
            لکھو("shared data: %s\n",
                   buf2->انکڑے[0] == 0xAB ? "yes" : "no");
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
    إذا (buf) {
        buf->انکڑے[0] = 0xCD;
        buf2 = av_بفر_ref(buf);
        إذا (buf2) {
            صحيح ret = av_بفر_make_writable(&buf2);
            لکھو("make_writable ret: %d\n", ret >= 0);
            لکھو("data preserved: %s\n",
                   buf2->انکڑے[0] == 0xCD ? "yes" : "no");
            لکھو("now writable: %d\n", av_بفر_is_writable(buf2));
            لکھو("original still valid: %s\n",
                   buf->انکڑے[0] == 0xCD ? "yes" : "no");
            av_بفر_unref(&buf2);
        }
        av_بفر_unref(&buf);
    }

    /* av_buffer_realloc */
    لکھو("\nTesting av_buffer_realloc()\n");
    buf = av_بفر_alloc(16);
    إذا (buf) {
        memset(buf->انکڑے, 0xEF, 16);
        av_بفر_realloc(&buf, 32);
        إذا (buf) {
            لکھو("realloc: size=%zu\n", buf->ناپ);
            لکھو("data preserved: %s\n",
                   buf->انکڑے[0] == 0xEF ? "yes" : "no");
        }
        av_بفر_unref(&buf);
    }
    /* realloc from NULL */
    buf = عدم;
    av_بفر_realloc(&buf, 8);
    لکھو("realloc from null: %s\n", buf ? "OK" : "FAIL");
    av_بفر_unref(&buf);

    /* av_buffer_replace */
    لکھو("\nTesting av_buffer_replace()\n");
    buf = av_بفر_alloc(8);
    buf2 = av_بفر_alloc(8);
    إذا (buf && buf2) {
        buf->انکڑے[0] = 0x11;
        buf2->انکڑے[0] = 0x22;
        av_بفر_replace(&buf, buf2);
        لکھو("replace: data=0x%02x\n", buf->انکڑے[0]);
        لکھو("refcount: %d\n", av_بفر_get_ref_گنتی(buf2));
    }
    av_بفر_unref(&buf);
    av_بفر_unref(&buf2);

    /* replace with NULL */
    buf = av_بفر_alloc(8);
    إذا (buf) {
        av_بفر_replace(&buf, عدم);
        لکھو("replace with null: %s\n", buf == عدم ? "OK" : "FAIL");
    }

    /* av_buffer_pool */
    لکھو("\nTesting av_buffer_pool()\n");
    pool = av_بفر_pool_init(64, عدم);
    إذا (pool) {
        buf = av_بفر_pool_get(pool);
        إذا (buf) {
            لکھو("pool get: size=%zu\n", buf->ناپ);
            av_بفر_unref(&buf);
        }
        /* get again -- should reuse the released buffer */
        buf = av_بفر_pool_get(pool);
        إذا (buf) {
            لکھو("pool reuse: size=%zu\n", buf->ناپ);
            av_بفر_unref(&buf);
        }
        av_بفر_pool_uninit(&pool);
        لکھو("pool uninit: %s\n", pool == عدم ? "OK" : "FAIL");
    }

    /* av_buffer_pool_init2 with custom alloc and pool_free callbacks */
    لکھو("\nTesting av_buffer_pool_init2()\n");
    pool_alloc2_called = 0;
    pool_free_called = 0;
    pool = av_بفر_pool_init2(64, عدم, pool_alloc2, pool_free_cb);
    إذا (pool) {
        buf = av_بفر_pool_get(pool);
        إذا (buf) {
            لکھو("pool2 get: size=%zu\n", buf->ناپ);
            لکھو("alloc2 called: %s\n", pool_alloc2_called ? "yes" : "no");
            لکھو("pool_buffer_get_opaque: %s\n",
                   av_بفر_pool_بفر_get_opaque(buf) == عدم ? "null" : "set");
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
    pool = av_بفر_pool_init(64, عدم);
    لکھو("pool init OOM: %s\n", pool ? "FAIL" : "OK");
    av_بفر_pool_uninit(&pool);
    av_max_alloc(ودھ_توں_ودھ_عدد);

    buf = av_بفر_alloc(16);
    إذا (buf) {
        av_max_alloc(1);
        buf2 = av_بفر_ref(buf);
        لکھو("ref OOM: %s\n", buf2 ? "FAIL" : "OK");
        av_بفر_unref(&buf2);
        لکھو("realloc OOM: %s\n",
               av_بفر_realloc(&buf, 1024) < 0 ? "OK" : "FAIL");
        av_max_alloc(ودھ_توں_ودھ_عدد);
        av_بفر_unref(&buf);
    }

    أرجع 0;
}
