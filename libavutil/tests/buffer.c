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

#समावेश <limits.h>
#समावेश <stdio.h>
#समावेश <string.h>

#समावेश "libavutil/buffer.h"
#समावेश "libavutil/mem.h"

अटल पूर्णांक custom_free_called;
अटल पूर्णांक pool_free_called;
अटल पूर्णांक pool_alloc2_called;

अटल व्योम custom_free(व्योम *opaque, uint8_t *तथ्य)
{
    custom_free_called = 1;
    av_free(तथ्य);
}

अटल AVBufferRef *pool_alloc2(व्योम *opaque, माप_प्रकार आकार)
{
    pool_alloc2_called = 1;
    वापस av_बफर_alloc(आकार);
}

अटल व्योम pool_free_cb(व्योम *opaque)
{
    pool_free_called = 1;
}

पूर्णांक मुख्य(व्योम)
{
    AVBufferRef *buf, *buf2;
    AVBufferPool *pool;

    /* av_buffer_alloc */
    म_लिखो("Testing av_buffer_alloc()\n");
    buf = av_बफर_alloc(64);
    अगर (buf) {
        म_लिखो("alloc: size=%zu data=%s\n", buf->आकार, buf->तथ्य ? "set" : "null");
        म_लिखो("writable: %d\n", av_बफर_is_writable(buf));
        म_लिखो("refcount: %d\n", av_बफर_get_ref_गिनती(buf));
        av_बफर_unref(&buf);
        म_लिखो("after unref: %s\n", buf == शून्य ? "null" : "leaked");
    }

    /* av_buffer_allocz */
    म_लिखो("\nTesting av_buffer_allocz()\n");
    buf = av_बफर_allocz(16);
    अगर (buf) {
        पूर्णांक zeroed = 1;
        क्रम (पूर्णांक i = 0; i < 16; i++)
            अगर (buf->तथ्य[i] != 0) zeroed = 0;
        म_लिखो("allocz: zeroed=%s\n", zeroed ? "yes" : "no");
        av_बफर_unref(&buf);
    }

    /* av_buffer_create with custom free */
    म_लिखो("\nTesting av_buffer_create()\n");
    {
        uint8_t *तथ्य = av_malloc(32);
        अगर (तथ्य) {
            custom_free_called = 0;
            buf = av_बफर_create(तथ्य, 32, custom_free, शून्य, 0);
            अगर (buf) {
                म_लिखो("create: size=%zu\n", buf->आकार);
                म_लिखो("opaque: %s\n",
                       av_बफर_get_opaque(buf) == शून्य ? "null" : "set");
                av_बफर_unref(&buf);
                म_लिखो("custom_free called: %s\n",
                       custom_free_called ? "yes" : "no");
            } अन्यथा {
                av_free(तथ्य);
            }
        }
    }

    /* av_buffer_create with READONLY flag */
    म_लिखो("\nTesting AV_BUFFER_FLAG_READONLY\n");
    {
        uint8_t *तथ्य = av_malloc(16);
        अगर (तथ्य) {
            buf = av_बफर_create(तथ्य, 16, custom_free, शून्य,
                                   AV_बफर_FLAG_READONLY);
            अगर (buf) {
                म_लिखो("readonly writable: %d\n", av_बफर_is_writable(buf));
                av_बफर_unref(&buf);
            } अन्यथा {
                av_free(तथ्य);
            }
        }
    }

    /* av_buffer_ref and refcounting */
    म_लिखो("\nTesting av_buffer_ref()\n");
    buf = av_बफर_alloc(32);
    अगर (buf) {
        buf->तथ्य[0] = 0xAB;
        buf2 = av_बफर_ref(buf);
        अगर (buf2) {
            म_लिखो("ref: refcount=%d\n", av_बफर_get_ref_गिनती(buf));
            म_लिखो("shared data: %s\n",
                   buf2->तथ्य[0] == 0xAB ? "yes" : "no");
            म_लिखो("writable after ref: %d\n", av_बफर_is_writable(buf));
            av_बफर_unref(&buf2);
            म_लिखो("refcount after unref: %d\n", av_बफर_get_ref_गिनती(buf));
            म_लिखो("writable after unref: %d\n", av_बफर_is_writable(buf));
        }
        av_बफर_unref(&buf);
    }

    /* av_buffer_make_writable */
    म_लिखो("\nTesting av_buffer_make_writable()\n");
    buf = av_बफर_alloc(16);
    अगर (buf) {
        buf->तथ्य[0] = 0xCD;
        buf2 = av_बफर_ref(buf);
        अगर (buf2) {
            पूर्णांक ret = av_बफर_make_writable(&buf2);
            म_लिखो("make_writable ret: %d\n", ret >= 0);
            म_लिखो("data preserved: %s\n",
                   buf2->तथ्य[0] == 0xCD ? "yes" : "no");
            म_लिखो("now writable: %d\n", av_बफर_is_writable(buf2));
            म_लिखो("original still valid: %s\n",
                   buf->तथ्य[0] == 0xCD ? "yes" : "no");
            av_बफर_unref(&buf2);
        }
        av_बफर_unref(&buf);
    }

    /* av_buffer_realloc */
    म_लिखो("\nTesting av_buffer_realloc()\n");
    buf = av_बफर_alloc(16);
    अगर (buf) {
        स_रखो(buf->तथ्य, 0xEF, 16);
        av_बफर_realloc(&buf, 32);
        अगर (buf) {
            म_लिखो("realloc: size=%zu\n", buf->आकार);
            म_लिखो("data preserved: %s\n",
                   buf->तथ्य[0] == 0xEF ? "yes" : "no");
        }
        av_बफर_unref(&buf);
    }
    /* realloc from NULL */
    buf = शून्य;
    av_बफर_realloc(&buf, 8);
    म_लिखो("realloc from null: %s\n", buf ? "OK" : "FAIL");
    av_बफर_unref(&buf);

    /* av_buffer_replace */
    म_लिखो("\nTesting av_buffer_replace()\n");
    buf = av_बफर_alloc(8);
    buf2 = av_बफर_alloc(8);
    अगर (buf && buf2) {
        buf->तथ्य[0] = 0x11;
        buf2->तथ्य[0] = 0x22;
        av_बफर_replace(&buf, buf2);
        म_लिखो("replace: data=0x%02x\n", buf->तथ्य[0]);
        म_लिखो("refcount: %d\n", av_बफर_get_ref_गिनती(buf2));
    }
    av_बफर_unref(&buf);
    av_बफर_unref(&buf2);

    /* replace with NULL */
    buf = av_बफर_alloc(8);
    अगर (buf) {
        av_बफर_replace(&buf, शून्य);
        म_लिखो("replace with null: %s\n", buf == शून्य ? "OK" : "FAIL");
    }

    /* av_buffer_pool */
    म_लिखो("\nTesting av_buffer_pool()\n");
    pool = av_बफर_pool_init(64, शून्य);
    अगर (pool) {
        buf = av_बफर_pool_get(pool);
        अगर (buf) {
            म_लिखो("pool get: size=%zu\n", buf->आकार);
            av_बफर_unref(&buf);
        }
        /* get again -- should reuse the released buffer */
        buf = av_बफर_pool_get(pool);
        अगर (buf) {
            म_लिखो("pool reuse: size=%zu\n", buf->आकार);
            av_बफर_unref(&buf);
        }
        av_बफर_pool_uninit(&pool);
        म_लिखो("pool uninit: %s\n", pool == शून्य ? "OK" : "FAIL");
    }

    /* av_buffer_pool_init2 with custom alloc and pool_free callbacks */
    म_लिखो("\nTesting av_buffer_pool_init2()\n");
    pool_alloc2_called = 0;
    pool_free_called = 0;
    pool = av_बफर_pool_init2(64, शून्य, pool_alloc2, pool_free_cb);
    अगर (pool) {
        buf = av_बफर_pool_get(pool);
        अगर (buf) {
            म_लिखो("pool2 get: size=%zu\n", buf->आकार);
            म_लिखो("alloc2 called: %s\n", pool_alloc2_called ? "yes" : "no");
            म_लिखो("pool_buffer_get_opaque: %s\n",
                   av_बफर_pool_बफर_get_opaque(buf) == शून्य ? "null" : "set");
            av_बफर_unref(&buf);
        }
        av_बफर_pool_uninit(&pool);
        म_लिखो("pool_free called: %s\n", pool_free_called ? "yes" : "no");
    }

    /* OOM paths via av_max_alloc */
    म_लिखो("\nTesting OOM paths\n");
    av_max_alloc(1);
    buf = av_बफर_alloc(64);
    म_लिखो("alloc OOM: %s\n", buf ? "FAIL" : "OK");
    av_बफर_unref(&buf);
    buf = av_बफर_allocz(64);
    म_लिखो("allocz OOM: %s\n", buf ? "FAIL" : "OK");
    av_बफर_unref(&buf);
    pool = av_बफर_pool_init(64, शून्य);
    म_लिखो("pool init OOM: %s\n", pool ? "FAIL" : "OK");
    av_बफर_pool_uninit(&pool);
    av_max_alloc(पूर्णांक_उच्च);

    buf = av_बफर_alloc(16);
    अगर (buf) {
        av_max_alloc(1);
        buf2 = av_बफर_ref(buf);
        म_लिखो("ref OOM: %s\n", buf2 ? "FAIL" : "OK");
        av_बफर_unref(&buf2);
        म_लिखो("realloc OOM: %s\n",
               av_बफर_realloc(&buf, 1024) < 0 ? "OK" : "FAIL");
        av_max_alloc(पूर्णांक_उच्च);
        av_बफर_unref(&buf);
    }

    वापस 0;
}
