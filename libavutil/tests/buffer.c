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

ساكن فراغ custom_free(فراغ *opaque, uint8_t *داده)
{
    custom_free_called = 1;
    av_free(داده);
}

ساكن AVBufferRef *pool_alloc2(فراغ *opaque, size_t اندازه)
{
    pool_alloc2_called = 1;
    أرجع av_میانگیر_alloc(اندازه);
}

ساكن فراغ pool_free_cb(فراغ *opaque)
{
    pool_free_called = 1;
}

صحيح اصلی(فراغ)
{
    AVBufferRef *buf, *buf2;
    AVBufferPool *pool;

    /* av_buffer_alloc */
    چاپ_کن("Testing av_buffer_alloc()\n");
    buf = av_میانگیر_alloc(64);
    إذا (buf) {
        چاپ_کن("alloc: size=%zu data=%s\n", buf->اندازه, buf->داده ? "set" : "null");
        چاپ_کن("writable: %d\n", av_میانگیر_is_writable(buf));
        چاپ_کن("refcount: %d\n", av_میانگیر_get_ref_شمار(buf));
        av_میانگیر_unref(&buf);
        چاپ_کن("after unref: %s\n", buf == عدم ? "null" : "leaked");
    }

    /* av_buffer_allocz */
    چاپ_کن("\nTesting av_buffer_allocz()\n");
    buf = av_میانگیر_allocz(16);
    إذا (buf) {
        صحيح zeroed = 1;
        لكل (صحيح i = 0; i < 16; i++)
            إذا (buf->داده[i] != 0) zeroed = 0;
        چاپ_کن("allocz: zeroed=%s\n", zeroed ? "yes" : "no");
        av_میانگیر_unref(&buf);
    }

    /* av_buffer_create with custom free */
    چاپ_کن("\nTesting av_buffer_create()\n");
    {
        uint8_t *داده = av_malloc(32);
        إذا (داده) {
            custom_free_called = 0;
            buf = av_میانگیر_create(داده, 32, custom_free, عدم, 0);
            إذا (buf) {
                چاپ_کن("create: size=%zu\n", buf->اندازه);
                چاپ_کن("opaque: %s\n",
                       av_میانگیر_get_opaque(buf) == عدم ? "null" : "set");
                av_میانگیر_unref(&buf);
                چاپ_کن("custom_free called: %s\n",
                       custom_free_called ? "yes" : "no");
            } وإلا {
                av_free(داده);
            }
        }
    }

    /* av_buffer_create with READONLY flag */
    چاپ_کن("\nTesting AV_BUFFER_FLAG_READONLY\n");
    {
        uint8_t *داده = av_malloc(16);
        إذا (داده) {
            buf = av_میانگیر_create(داده, 16, custom_free, عدم,
                                   AV_میانگیر_FLAG_READONLY);
            إذا (buf) {
                چاپ_کن("readonly writable: %d\n", av_میانگیر_is_writable(buf));
                av_میانگیر_unref(&buf);
            } وإلا {
                av_free(داده);
            }
        }
    }

    /* av_buffer_ref and refcounting */
    چاپ_کن("\nTesting av_buffer_ref()\n");
    buf = av_میانگیر_alloc(32);
    إذا (buf) {
        buf->داده[0] = 0xAB;
        buf2 = av_میانگیر_ref(buf);
        إذا (buf2) {
            چاپ_کن("ref: refcount=%d\n", av_میانگیر_get_ref_شمار(buf));
            چاپ_کن("shared data: %s\n",
                   buf2->داده[0] == 0xAB ? "yes" : "no");
            چاپ_کن("writable after ref: %d\n", av_میانگیر_is_writable(buf));
            av_میانگیر_unref(&buf2);
            چاپ_کن("refcount after unref: %d\n", av_میانگیر_get_ref_شمار(buf));
            چاپ_کن("writable after unref: %d\n", av_میانگیر_is_writable(buf));
        }
        av_میانگیر_unref(&buf);
    }

    /* av_buffer_make_writable */
    چاپ_کن("\nTesting av_buffer_make_writable()\n");
    buf = av_میانگیر_alloc(16);
    إذا (buf) {
        buf->داده[0] = 0xCD;
        buf2 = av_میانگیر_ref(buf);
        إذا (buf2) {
            صحيح ret = av_میانگیر_make_writable(&buf2);
            چاپ_کن("make_writable ret: %d\n", ret >= 0);
            چاپ_کن("data preserved: %s\n",
                   buf2->داده[0] == 0xCD ? "yes" : "no");
            چاپ_کن("now writable: %d\n", av_میانگیر_is_writable(buf2));
            چاپ_کن("original still valid: %s\n",
                   buf->داده[0] == 0xCD ? "yes" : "no");
            av_میانگیر_unref(&buf2);
        }
        av_میانگیر_unref(&buf);
    }

    /* av_buffer_realloc */
    چاپ_کن("\nTesting av_buffer_realloc()\n");
    buf = av_میانگیر_alloc(16);
    إذا (buf) {
        memset(buf->داده, 0xEF, 16);
        av_میانگیر_realloc(&buf, 32);
        إذا (buf) {
            چاپ_کن("realloc: size=%zu\n", buf->اندازه);
            چاپ_کن("data preserved: %s\n",
                   buf->داده[0] == 0xEF ? "yes" : "no");
        }
        av_میانگیر_unref(&buf);
    }
    /* realloc from NULL */
    buf = عدم;
    av_میانگیر_realloc(&buf, 8);
    چاپ_کن("realloc from null: %s\n", buf ? "OK" : "FAIL");
    av_میانگیر_unref(&buf);

    /* av_buffer_replace */
    چاپ_کن("\nTesting av_buffer_replace()\n");
    buf = av_میانگیر_alloc(8);
    buf2 = av_میانگیر_alloc(8);
    إذا (buf && buf2) {
        buf->داده[0] = 0x11;
        buf2->داده[0] = 0x22;
        av_میانگیر_replace(&buf, buf2);
        چاپ_کن("replace: data=0x%02x\n", buf->داده[0]);
        چاپ_کن("refcount: %d\n", av_میانگیر_get_ref_شمار(buf2));
    }
    av_میانگیر_unref(&buf);
    av_میانگیر_unref(&buf2);

    /* replace with NULL */
    buf = av_میانگیر_alloc(8);
    إذا (buf) {
        av_میانگیر_replace(&buf, عدم);
        چاپ_کن("replace with null: %s\n", buf == عدم ? "OK" : "FAIL");
    }

    /* av_buffer_pool */
    چاپ_کن("\nTesting av_buffer_pool()\n");
    pool = av_میانگیر_pool_init(64, عدم);
    إذا (pool) {
        buf = av_میانگیر_pool_get(pool);
        إذا (buf) {
            چاپ_کن("pool get: size=%zu\n", buf->اندازه);
            av_میانگیر_unref(&buf);
        }
        /* get again -- should reuse the released buffer */
        buf = av_میانگیر_pool_get(pool);
        إذا (buf) {
            چاپ_کن("pool reuse: size=%zu\n", buf->اندازه);
            av_میانگیر_unref(&buf);
        }
        av_میانگیر_pool_uninit(&pool);
        چاپ_کن("pool uninit: %s\n", pool == عدم ? "OK" : "FAIL");
    }

    /* av_buffer_pool_init2 with custom alloc and pool_free callbacks */
    چاپ_کن("\nTesting av_buffer_pool_init2()\n");
    pool_alloc2_called = 0;
    pool_free_called = 0;
    pool = av_میانگیر_pool_init2(64, عدم, pool_alloc2, pool_free_cb);
    إذا (pool) {
        buf = av_میانگیر_pool_get(pool);
        إذا (buf) {
            چاپ_کن("pool2 get: size=%zu\n", buf->اندازه);
            چاپ_کن("alloc2 called: %s\n", pool_alloc2_called ? "yes" : "no");
            چاپ_کن("pool_buffer_get_opaque: %s\n",
                   av_میانگیر_pool_میانگیر_get_opaque(buf) == عدم ? "null" : "set");
            av_میانگیر_unref(&buf);
        }
        av_میانگیر_pool_uninit(&pool);
        چاپ_کن("pool_free called: %s\n", pool_free_called ? "yes" : "no");
    }

    /* OOM paths via av_max_alloc */
    چاپ_کن("\nTesting OOM paths\n");
    av_max_alloc(1);
    buf = av_میانگیر_alloc(64);
    چاپ_کن("alloc OOM: %s\n", buf ? "FAIL" : "OK");
    av_میانگیر_unref(&buf);
    buf = av_میانگیر_allocz(64);
    چاپ_کن("allocz OOM: %s\n", buf ? "FAIL" : "OK");
    av_میانگیر_unref(&buf);
    pool = av_میانگیر_pool_init(64, عدم);
    چاپ_کن("pool init OOM: %s\n", pool ? "FAIL" : "OK");
    av_میانگیر_pool_uninit(&pool);
    av_max_alloc(بیشترین_صحیح);

    buf = av_میانگیر_alloc(16);
    إذا (buf) {
        av_max_alloc(1);
        buf2 = av_میانگیر_ref(buf);
        چاپ_کن("ref OOM: %s\n", buf2 ? "FAIL" : "OK");
        av_میانگیر_unref(&buf2);
        چاپ_کن("realloc OOM: %s\n",
               av_میانگیر_realloc(&buf, 1024) < 0 ? "OK" : "FAIL");
        av_max_alloc(بیشترین_صحیح);
        av_میانگیر_unref(&buf);
    }

    أرجع 0;
}
