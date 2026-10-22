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

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "libavutil/buffer.h"
#అన్తర్భావ "libavutil/mem.h"

స్థిర పూర్ణాంకం custom_free_called;
స్థిర పూర్ణాంకం pool_free_called;
స్థిర పూర్ణాంకం pool_alloc2_called;

స్థిర శూన్య custom_free(శూన్య *opaque, uint8_t *దత్తాంశం)
{
    custom_free_called = 1;
    av_free(దత్తాంశం);
}

స్థిర AVBufferRef *pool_alloc2(శూన్య *opaque, size_t కొలత)
{
    pool_alloc2_called = 1;
    తిరిగి av_బఫరు_alloc(కొలత);
}

స్థిర శూన్య pool_free_cb(శూన్య *opaque)
{
    pool_free_called = 1;
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    AVBufferRef *buf, *buf2;
    AVBufferPool *pool;

    /* av_buffer_alloc */
    రాయి("Testing av_buffer_alloc()\n");
    buf = av_బఫరు_alloc(64);
    ఒకవేళ (buf) {
        రాయి("alloc: size=%zu data=%s\n", buf->కొలత, buf->దత్తాంశం ? "set" : "null");
        రాయి("writable: %d\n", av_బఫరు_is_writable(buf));
        రాయి("refcount: %d\n", av_బఫరు_get_ref_లెక్క(buf));
        av_బఫరు_unref(&buf);
        రాయి("after unref: %s\n", buf == ఖాళీ ? "null" : "leaked");
    }

    /* av_buffer_allocz */
    రాయి("\nTesting av_buffer_allocz()\n");
    buf = av_బఫరు_allocz(16);
    ఒకవేళ (buf) {
        పూర్ణాంకం zeroed = 1;
        కొరకు (పూర్ణాంకం i = 0; i < 16; i++)
            ఒకవేళ (buf->దత్తాంశం[i] != 0) zeroed = 0;
        రాయి("allocz: zeroed=%s\n", zeroed ? "yes" : "no");
        av_బఫరు_unref(&buf);
    }

    /* av_buffer_create with custom free */
    రాయి("\nTesting av_buffer_create()\n");
    {
        uint8_t *దత్తాంశం = av_malloc(32);
        ఒకవేళ (దత్తాంశం) {
            custom_free_called = 0;
            buf = av_బఫరు_create(దత్తాంశం, 32, custom_free, ఖాళీ, 0);
            ఒకవేళ (buf) {
                రాయి("create: size=%zu\n", buf->కొలత);
                రాయి("opaque: %s\n",
                       av_బఫరు_get_opaque(buf) == ఖాళీ ? "null" : "set");
                av_బఫరు_unref(&buf);
                రాయి("custom_free called: %s\n",
                       custom_free_called ? "yes" : "no");
            } లేకపోతే {
                av_free(దత్తాంశం);
            }
        }
    }

    /* av_buffer_create with READONLY flag */
    రాయి("\nTesting AV_BUFFER_FLAG_READONLY\n");
    {
        uint8_t *దత్తాంశం = av_malloc(16);
        ఒకవేళ (దత్తాంశం) {
            buf = av_బఫరు_create(దత్తాంశం, 16, custom_free, ఖాళీ,
                                   AV_బఫరు_FLAG_READONLY);
            ఒకవేళ (buf) {
                రాయి("readonly writable: %d\n", av_బఫరు_is_writable(buf));
                av_బఫరు_unref(&buf);
            } లేకపోతే {
                av_free(దత్తాంశం);
            }
        }
    }

    /* av_buffer_ref and refcounting */
    రాయి("\nTesting av_buffer_ref()\n");
    buf = av_బఫరు_alloc(32);
    ఒకవేళ (buf) {
        buf->దత్తాంశం[0] = 0xAB;
        buf2 = av_బఫరు_ref(buf);
        ఒకవేళ (buf2) {
            రాయి("ref: refcount=%d\n", av_బఫరు_get_ref_లెక్క(buf));
            రాయి("shared data: %s\n",
                   buf2->దత్తాంశం[0] == 0xAB ? "yes" : "no");
            రాయి("writable after ref: %d\n", av_బఫరు_is_writable(buf));
            av_బఫరు_unref(&buf2);
            రాయి("refcount after unref: %d\n", av_బఫరు_get_ref_లెక్క(buf));
            రాయి("writable after unref: %d\n", av_బఫరు_is_writable(buf));
        }
        av_బఫరు_unref(&buf);
    }

    /* av_buffer_make_writable */
    రాయి("\nTesting av_buffer_make_writable()\n");
    buf = av_బఫరు_alloc(16);
    ఒకవేళ (buf) {
        buf->దత్తాంశం[0] = 0xCD;
        buf2 = av_బఫరు_ref(buf);
        ఒకవేళ (buf2) {
            పూర్ణాంకం ret = av_బఫరు_make_writable(&buf2);
            రాయి("make_writable ret: %d\n", ret >= 0);
            రాయి("data preserved: %s\n",
                   buf2->దత్తాంశం[0] == 0xCD ? "yes" : "no");
            రాయి("now writable: %d\n", av_బఫరు_is_writable(buf2));
            రాయి("original still valid: %s\n",
                   buf->దత్తాంశం[0] == 0xCD ? "yes" : "no");
            av_బఫరు_unref(&buf2);
        }
        av_బఫరు_unref(&buf);
    }

    /* av_buffer_realloc */
    రాయి("\nTesting av_buffer_realloc()\n");
    buf = av_బఫరు_alloc(16);
    ఒకవేళ (buf) {
        memset(buf->దత్తాంశం, 0xEF, 16);
        av_బఫరు_realloc(&buf, 32);
        ఒకవేళ (buf) {
            రాయి("realloc: size=%zu\n", buf->కొలత);
            రాయి("data preserved: %s\n",
                   buf->దత్తాంశం[0] == 0xEF ? "yes" : "no");
        }
        av_బఫరు_unref(&buf);
    }
    /* realloc from NULL */
    buf = ఖాళీ;
    av_బఫరు_realloc(&buf, 8);
    రాయి("realloc from null: %s\n", buf ? "OK" : "FAIL");
    av_బఫరు_unref(&buf);

    /* av_buffer_replace */
    రాయి("\nTesting av_buffer_replace()\n");
    buf = av_బఫరు_alloc(8);
    buf2 = av_బఫరు_alloc(8);
    ఒకవేళ (buf && buf2) {
        buf->దత్తాంశం[0] = 0x11;
        buf2->దత్తాంశం[0] = 0x22;
        av_బఫరు_replace(&buf, buf2);
        రాయి("replace: data=0x%02x\n", buf->దత్తాంశం[0]);
        రాయి("refcount: %d\n", av_బఫరు_get_ref_లెక్క(buf2));
    }
    av_బఫరు_unref(&buf);
    av_బఫరు_unref(&buf2);

    /* replace with NULL */
    buf = av_బఫరు_alloc(8);
    ఒకవేళ (buf) {
        av_బఫరు_replace(&buf, ఖాళీ);
        రాయి("replace with null: %s\n", buf == ఖాళీ ? "OK" : "FAIL");
    }

    /* av_buffer_pool */
    రాయి("\nTesting av_buffer_pool()\n");
    pool = av_బఫరు_pool_init(64, ఖాళీ);
    ఒకవేళ (pool) {
        buf = av_బఫరు_pool_get(pool);
        ఒకవేళ (buf) {
            రాయి("pool get: size=%zu\n", buf->కొలత);
            av_బఫరు_unref(&buf);
        }
        /* get again -- should reuse the released buffer */
        buf = av_బఫరు_pool_get(pool);
        ఒకవేళ (buf) {
            రాయి("pool reuse: size=%zu\n", buf->కొలత);
            av_బఫరు_unref(&buf);
        }
        av_బఫరు_pool_uninit(&pool);
        రాయి("pool uninit: %s\n", pool == ఖాళీ ? "OK" : "FAIL");
    }

    /* av_buffer_pool_init2 with custom alloc and pool_free callbacks */
    రాయి("\nTesting av_buffer_pool_init2()\n");
    pool_alloc2_called = 0;
    pool_free_called = 0;
    pool = av_బఫరు_pool_init2(64, ఖాళీ, pool_alloc2, pool_free_cb);
    ఒకవేళ (pool) {
        buf = av_బఫరు_pool_get(pool);
        ఒకవేళ (buf) {
            రాయి("pool2 get: size=%zu\n", buf->కొలత);
            రాయి("alloc2 called: %s\n", pool_alloc2_called ? "yes" : "no");
            రాయి("pool_buffer_get_opaque: %s\n",
                   av_బఫరు_pool_బఫరు_get_opaque(buf) == ఖాళీ ? "null" : "set");
            av_బఫరు_unref(&buf);
        }
        av_బఫరు_pool_uninit(&pool);
        రాయి("pool_free called: %s\n", pool_free_called ? "yes" : "no");
    }

    /* OOM paths via av_max_alloc */
    రాయి("\nTesting OOM paths\n");
    av_max_alloc(1);
    buf = av_బఫరు_alloc(64);
    రాయి("alloc OOM: %s\n", buf ? "FAIL" : "OK");
    av_బఫరు_unref(&buf);
    buf = av_బఫరు_allocz(64);
    రాయి("allocz OOM: %s\n", buf ? "FAIL" : "OK");
    av_బఫరు_unref(&buf);
    pool = av_బఫరు_pool_init(64, ఖాళీ);
    రాయి("pool init OOM: %s\n", pool ? "FAIL" : "OK");
    av_బఫరు_pool_uninit(&pool);
    av_max_alloc(గరిష్ఠ_పూర్ణాంకం);

    buf = av_బఫరు_alloc(16);
    ఒకవేళ (buf) {
        av_max_alloc(1);
        buf2 = av_బఫరు_ref(buf);
        రాయి("ref OOM: %s\n", buf2 ? "FAIL" : "OK");
        av_బఫరు_unref(&buf2);
        రాయి("realloc OOM: %s\n",
               av_బఫరు_realloc(&buf, 1024) < 0 ? "OK" : "FAIL");
        av_max_alloc(గరిష్ఠ_పూర్ణాంకం);
        av_బఫరు_unref(&buf);
    }

    తిరిగి 0;
}
