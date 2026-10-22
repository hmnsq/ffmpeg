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

ساكن فراغ custom_free(فراغ *opaque, uint8_t *معلومات)
{
    custom_free_called = 1;
    av_free(معلومات);
}

ساكن AVBufferRef *pool_alloc2(فراغ *opaque, size_t اندازه)
{
    pool_alloc2_called = 1;
    أرجع av_بفر_alloc(اندازه);
}

ساكن فراغ pool_free_cb(فراغ *opaque)
{
    pool_free_called = 1;
}

صحيح اصلي(فراغ)
{
    AVBufferRef *buf, *buf2;
    AVBufferPool *pool;

    /* av_buffer_alloc */
    چاپ_کړه("Testing av_buffer_alloc()\n");
    buf = av_بفر_alloc(64);
    إذا (buf) {
        چاپ_کړه("alloc: size=%zu data=%s\n", buf->اندازه, buf->معلومات ? "set" : "null");
        چاپ_کړه("writable: %d\n", av_بفر_is_writable(buf));
        چاپ_کړه("refcount: %d\n", av_بفر_get_ref_شمېر(buf));
        av_بفر_unref(&buf);
        چاپ_کړه("after unref: %s\n", buf == عدم ? "null" : "leaked");
    }

    /* av_buffer_allocz */
    چاپ_کړه("\nTesting av_buffer_allocz()\n");
    buf = av_بفر_allocz(16);
    إذا (buf) {
        صحيح zeroed = 1;
        لكل (صحيح i = 0; i < 16; i++)
            إذا (buf->معلومات[i] != 0) zeroed = 0;
        چاپ_کړه("allocz: zeroed=%s\n", zeroed ? "yes" : "no");
        av_بفر_unref(&buf);
    }

    /* av_buffer_create with custom free */
    چاپ_کړه("\nTesting av_buffer_create()\n");
    {
        uint8_t *معلومات = av_malloc(32);
        إذا (معلومات) {
            custom_free_called = 0;
            buf = av_بفر_create(معلومات, 32, custom_free, عدم, 0);
            إذا (buf) {
                چاپ_کړه("create: size=%zu\n", buf->اندازه);
                چاپ_کړه("opaque: %s\n",
                       av_بفر_get_opaque(buf) == عدم ? "null" : "set");
                av_بفر_unref(&buf);
                چاپ_کړه("custom_free called: %s\n",
                       custom_free_called ? "yes" : "no");
            } وإلا {
                av_free(معلومات);
            }
        }
    }

    /* av_buffer_create with READONLY flag */
    چاپ_کړه("\nTesting AV_BUFFER_FLAG_READONLY\n");
    {
        uint8_t *معلومات = av_malloc(16);
        إذا (معلومات) {
            buf = av_بفر_create(معلومات, 16, custom_free, عدم,
                                   AV_بفر_FLAG_READONLY);
            إذا (buf) {
                چاپ_کړه("readonly writable: %d\n", av_بفر_is_writable(buf));
                av_بفر_unref(&buf);
            } وإلا {
                av_free(معلومات);
            }
        }
    }

    /* av_buffer_ref and refcounting */
    چاپ_کړه("\nTesting av_buffer_ref()\n");
    buf = av_بفر_alloc(32);
    إذا (buf) {
        buf->معلومات[0] = 0xAB;
        buf2 = av_بفر_ref(buf);
        إذا (buf2) {
            چاپ_کړه("ref: refcount=%d\n", av_بفر_get_ref_شمېر(buf));
            چاپ_کړه("shared data: %s\n",
                   buf2->معلومات[0] == 0xAB ? "yes" : "no");
            چاپ_کړه("writable after ref: %d\n", av_بفر_is_writable(buf));
            av_بفر_unref(&buf2);
            چاپ_کړه("refcount after unref: %d\n", av_بفر_get_ref_شمېر(buf));
            چاپ_کړه("writable after unref: %d\n", av_بفر_is_writable(buf));
        }
        av_بفر_unref(&buf);
    }

    /* av_buffer_make_writable */
    چاپ_کړه("\nTesting av_buffer_make_writable()\n");
    buf = av_بفر_alloc(16);
    إذا (buf) {
        buf->معلومات[0] = 0xCD;
        buf2 = av_بفر_ref(buf);
        إذا (buf2) {
            صحيح ret = av_بفر_make_writable(&buf2);
            چاپ_کړه("make_writable ret: %d\n", ret >= 0);
            چاپ_کړه("data preserved: %s\n",
                   buf2->معلومات[0] == 0xCD ? "yes" : "no");
            چاپ_کړه("now writable: %d\n", av_بفر_is_writable(buf2));
            چاپ_کړه("original still valid: %s\n",
                   buf->معلومات[0] == 0xCD ? "yes" : "no");
            av_بفر_unref(&buf2);
        }
        av_بفر_unref(&buf);
    }

    /* av_buffer_realloc */
    چاپ_کړه("\nTesting av_buffer_realloc()\n");
    buf = av_بفر_alloc(16);
    إذا (buf) {
        memset(buf->معلومات, 0xEF, 16);
        av_بفر_realloc(&buf, 32);
        إذا (buf) {
            چاپ_کړه("realloc: size=%zu\n", buf->اندازه);
            چاپ_کړه("data preserved: %s\n",
                   buf->معلومات[0] == 0xEF ? "yes" : "no");
        }
        av_بفر_unref(&buf);
    }
    /* realloc from NULL */
    buf = عدم;
    av_بفر_realloc(&buf, 8);
    چاپ_کړه("realloc from null: %s\n", buf ? "OK" : "FAIL");
    av_بفر_unref(&buf);

    /* av_buffer_replace */
    چاپ_کړه("\nTesting av_buffer_replace()\n");
    buf = av_بفر_alloc(8);
    buf2 = av_بفر_alloc(8);
    إذا (buf && buf2) {
        buf->معلومات[0] = 0x11;
        buf2->معلومات[0] = 0x22;
        av_بفر_replace(&buf, buf2);
        چاپ_کړه("replace: data=0x%02x\n", buf->معلومات[0]);
        چاپ_کړه("refcount: %d\n", av_بفر_get_ref_شمېر(buf2));
    }
    av_بفر_unref(&buf);
    av_بفر_unref(&buf2);

    /* replace with NULL */
    buf = av_بفر_alloc(8);
    إذا (buf) {
        av_بفر_replace(&buf, عدم);
        چاپ_کړه("replace with null: %s\n", buf == عدم ? "OK" : "FAIL");
    }

    /* av_buffer_pool */
    چاپ_کړه("\nTesting av_buffer_pool()\n");
    pool = av_بفر_pool_init(64, عدم);
    إذا (pool) {
        buf = av_بفر_pool_get(pool);
        إذا (buf) {
            چاپ_کړه("pool get: size=%zu\n", buf->اندازه);
            av_بفر_unref(&buf);
        }
        /* get again -- should reuse the released buffer */
        buf = av_بفر_pool_get(pool);
        إذا (buf) {
            چاپ_کړه("pool reuse: size=%zu\n", buf->اندازه);
            av_بفر_unref(&buf);
        }
        av_بفر_pool_uninit(&pool);
        چاپ_کړه("pool uninit: %s\n", pool == عدم ? "OK" : "FAIL");
    }

    /* av_buffer_pool_init2 with custom alloc and pool_free callbacks */
    چاپ_کړه("\nTesting av_buffer_pool_init2()\n");
    pool_alloc2_called = 0;
    pool_free_called = 0;
    pool = av_بفر_pool_init2(64, عدم, pool_alloc2, pool_free_cb);
    إذا (pool) {
        buf = av_بفر_pool_get(pool);
        إذا (buf) {
            چاپ_کړه("pool2 get: size=%zu\n", buf->اندازه);
            چاپ_کړه("alloc2 called: %s\n", pool_alloc2_called ? "yes" : "no");
            چاپ_کړه("pool_buffer_get_opaque: %s\n",
                   av_بفر_pool_بفر_get_opaque(buf) == عدم ? "null" : "set");
            av_بفر_unref(&buf);
        }
        av_بفر_pool_uninit(&pool);
        چاپ_کړه("pool_free called: %s\n", pool_free_called ? "yes" : "no");
    }

    /* OOM paths via av_max_alloc */
    چاپ_کړه("\nTesting OOM paths\n");
    av_max_alloc(1);
    buf = av_بفر_alloc(64);
    چاپ_کړه("alloc OOM: %s\n", buf ? "FAIL" : "OK");
    av_بفر_unref(&buf);
    buf = av_بفر_allocz(64);
    چاپ_کړه("allocz OOM: %s\n", buf ? "FAIL" : "OK");
    av_بفر_unref(&buf);
    pool = av_بفر_pool_init(64, عدم);
    چاپ_کړه("pool init OOM: %s\n", pool ? "FAIL" : "OK");
    av_بفر_pool_uninit(&pool);
    av_max_alloc(لوی_عدد);

    buf = av_بفر_alloc(16);
    إذا (buf) {
        av_max_alloc(1);
        buf2 = av_بفر_ref(buf);
        چاپ_کړه("ref OOM: %s\n", buf2 ? "FAIL" : "OK");
        av_بفر_unref(&buf2);
        چاپ_کړه("realloc OOM: %s\n",
               av_بفر_realloc(&buf, 1024) < 0 ? "OK" : "FAIL");
        av_max_alloc(لوی_عدد);
        av_بفر_unref(&buf);
    }

    أرجع 0;
}
