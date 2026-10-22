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

#अन्तर्भाव <limits.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "libavutil/buffer.h"
#अन्तर्भाव "libavutil/mem.h"

स्थिर पूर्णाङ्क custom_free_called;
स्थिर पूर्णाङ्क pool_free_called;
स्थिर पूर्णाङ्क pool_alloc2_called;

स्थिर शून्य custom_free(शून्य *opaque, uint8_t *data)
{
    custom_free_called = 1;
    av_free(data);
}

स्थिर AVBufferRef *pool_alloc2(शून्य *opaque, माप_प्रकार size)
{
    pool_alloc2_called = 1;
    प्रत्यागम av_buffer_alloc(size);
}

स्थिर शून्य pool_free_cb(शून्य *opaque)
{
    pool_free_called = 1;
}

पूर्णाङ्क main(शून्य)
{
    AVBufferRef *buf, *buf2;
    AVBufferPool *pool;

    /* av_buffer_alloc */
    म_लिखो("Testing av_buffer_alloc()\n");
    buf = av_buffer_alloc(64);
    यदि (buf) {
        म_लिखो("alloc: size=%zu data=%s\n", buf->size, buf->data ? "set" : "null");
        म_लिखो("writable: %d\n", av_buffer_is_writable(buf));
        म_लिखो("refcount: %d\n", av_buffer_get_ref_गिनती(buf));
        av_buffer_unref(&buf);
        म_लिखो("after unref: %s\n", buf == रिक्त ? "null" : "leaked");
    }

    /* av_buffer_allocz */
    म_लिखो("\nTesting av_buffer_allocz()\n");
    buf = av_buffer_allocz(16);
    यदि (buf) {
        पूर्णाङ्क zeroed = 1;
        प्रति (पूर्णाङ्क i = 0; i < 16; i++)
            यदि (buf->data[i] != 0) zeroed = 0;
        म_लिखो("allocz: zeroed=%s\n", zeroed ? "yes" : "no");
        av_buffer_unref(&buf);
    }

    /* av_buffer_create with custom free */
    म_लिखो("\nTesting av_buffer_create()\n");
    {
        uint8_t *data = av_malloc(32);
        यदि (data) {
            custom_free_called = 0;
            buf = av_buffer_create(data, 32, custom_free, रिक्त, 0);
            यदि (buf) {
                म_लिखो("create: size=%zu\n", buf->size);
                म_लिखो("opaque: %s\n",
                       av_buffer_get_opaque(buf) == रिक्त ? "null" : "set");
                av_buffer_unref(&buf);
                म_लिखो("custom_free called: %s\n",
                       custom_free_called ? "yes" : "no");
            } अन्यथा {
                av_free(data);
            }
        }
    }

    /* av_buffer_create with READONLY flag */
    म_लिखो("\nTesting AV_BUFFER_FLAG_READONLY\n");
    {
        uint8_t *data = av_malloc(16);
        यदि (data) {
            buf = av_buffer_create(data, 16, custom_free, रिक्त,
                                   AV_BUFFER_FLAG_READONLY);
            यदि (buf) {
                म_लिखो("readonly writable: %d\n", av_buffer_is_writable(buf));
                av_buffer_unref(&buf);
            } अन्यथा {
                av_free(data);
            }
        }
    }

    /* av_buffer_ref and refcounting */
    म_लिखो("\nTesting av_buffer_ref()\n");
    buf = av_buffer_alloc(32);
    यदि (buf) {
        buf->data[0] = 0xAB;
        buf2 = av_buffer_ref(buf);
        यदि (buf2) {
            म_लिखो("ref: refcount=%d\n", av_buffer_get_ref_गिनती(buf));
            म_लिखो("shared data: %s\n",
                   buf2->data[0] == 0xAB ? "yes" : "no");
            म_लिखो("writable after ref: %d\n", av_buffer_is_writable(buf));
            av_buffer_unref(&buf2);
            म_लिखो("refcount after unref: %d\n", av_buffer_get_ref_गिनती(buf));
            म_लिखो("writable after unref: %d\n", av_buffer_is_writable(buf));
        }
        av_buffer_unref(&buf);
    }

    /* av_buffer_make_writable */
    म_लिखो("\nTesting av_buffer_make_writable()\n");
    buf = av_buffer_alloc(16);
    यदि (buf) {
        buf->data[0] = 0xCD;
        buf2 = av_buffer_ref(buf);
        यदि (buf2) {
            पूर्णाङ्क ret = av_buffer_make_writable(&buf2);
            म_लिखो("make_writable ret: %d\n", ret >= 0);
            म_लिखो("data preserved: %s\n",
                   buf2->data[0] == 0xCD ? "yes" : "no");
            म_लिखो("now writable: %d\n", av_buffer_is_writable(buf2));
            म_लिखो("original still valid: %s\n",
                   buf->data[0] == 0xCD ? "yes" : "no");
            av_buffer_unref(&buf2);
        }
        av_buffer_unref(&buf);
    }

    /* av_buffer_realloc */
    म_लिखो("\nTesting av_buffer_realloc()\n");
    buf = av_buffer_alloc(16);
    यदि (buf) {
        स_रखो(buf->data, 0xEF, 16);
        av_buffer_realloc(&buf, 32);
        यदि (buf) {
            म_लिखो("realloc: size=%zu\n", buf->size);
            म_लिखो("data preserved: %s\n",
                   buf->data[0] == 0xEF ? "yes" : "no");
        }
        av_buffer_unref(&buf);
    }
    /* realloc from NULL */
    buf = रिक्त;
    av_buffer_realloc(&buf, 8);
    म_लिखो("realloc from null: %s\n", buf ? "OK" : "FAIL");
    av_buffer_unref(&buf);

    /* av_buffer_replace */
    म_लिखो("\nTesting av_buffer_replace()\n");
    buf = av_buffer_alloc(8);
    buf2 = av_buffer_alloc(8);
    यदि (buf && buf2) {
        buf->data[0] = 0x11;
        buf2->data[0] = 0x22;
        av_buffer_replace(&buf, buf2);
        म_लिखो("replace: data=0x%02x\n", buf->data[0]);
        म_लिखो("refcount: %d\n", av_buffer_get_ref_गिनती(buf2));
    }
    av_buffer_unref(&buf);
    av_buffer_unref(&buf2);

    /* replace with NULL */
    buf = av_buffer_alloc(8);
    यदि (buf) {
        av_buffer_replace(&buf, रिक्त);
        म_लिखो("replace with null: %s\n", buf == रिक्त ? "OK" : "FAIL");
    }

    /* av_buffer_pool */
    म_लिखो("\nTesting av_buffer_pool()\n");
    pool = av_buffer_pool_init(64, रिक्त);
    यदि (pool) {
        buf = av_buffer_pool_get(pool);
        यदि (buf) {
            म_लिखो("pool get: size=%zu\n", buf->size);
            av_buffer_unref(&buf);
        }
        /* get again -- should reuse the released buffer */
        buf = av_buffer_pool_get(pool);
        यदि (buf) {
            म_लिखो("pool reuse: size=%zu\n", buf->size);
            av_buffer_unref(&buf);
        }
        av_buffer_pool_uninit(&pool);
        म_लिखो("pool uninit: %s\n", pool == रिक्त ? "OK" : "FAIL");
    }

    /* av_buffer_pool_init2 with custom alloc and pool_free callbacks */
    म_लिखो("\nTesting av_buffer_pool_init2()\n");
    pool_alloc2_called = 0;
    pool_free_called = 0;
    pool = av_buffer_pool_init2(64, रिक्त, pool_alloc2, pool_free_cb);
    यदि (pool) {
        buf = av_buffer_pool_get(pool);
        यदि (buf) {
            म_लिखो("pool2 get: size=%zu\n", buf->size);
            म_लिखो("alloc2 called: %s\n", pool_alloc2_called ? "yes" : "no");
            म_लिखो("pool_buffer_get_opaque: %s\n",
                   av_buffer_pool_buffer_get_opaque(buf) == रिक्त ? "null" : "set");
            av_buffer_unref(&buf);
        }
        av_buffer_pool_uninit(&pool);
        म_लिखो("pool_free called: %s\n", pool_free_called ? "yes" : "no");
    }

    /* OOM paths via av_max_alloc */
    म_लिखो("\nTesting OOM paths\n");
    av_max_alloc(1);
    buf = av_buffer_alloc(64);
    म_लिखो("alloc OOM: %s\n", buf ? "FAIL" : "OK");
    av_buffer_unref(&buf);
    buf = av_buffer_allocz(64);
    म_लिखो("allocz OOM: %s\n", buf ? "FAIL" : "OK");
    av_buffer_unref(&buf);
    pool = av_buffer_pool_init(64, रिक्त);
    म_लिखो("pool init OOM: %s\n", pool ? "FAIL" : "OK");
    av_buffer_pool_uninit(&pool);
    av_max_alloc(पूर्णांक_उच्च);

    buf = av_buffer_alloc(16);
    यदि (buf) {
        av_max_alloc(1);
        buf2 = av_buffer_ref(buf);
        म_लिखो("ref OOM: %s\n", buf2 ? "FAIL" : "OK");
        av_buffer_unref(&buf2);
        म_लिखो("realloc OOM: %s\n",
               av_buffer_realloc(&buf, 1024) < 0 ? "OK" : "FAIL");
        av_max_alloc(पूर्णांक_उच्च);
        av_buffer_unref(&buf);
    }

    प्रत्यागम 0;
}
