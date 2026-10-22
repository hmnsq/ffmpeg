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

स्थिर शून्य custom_free(शून्य *opaque, uint8_t *दत्त)
{
    custom_free_called = 1;
    av_free(दत्त);
}

स्थिर AVBufferRef *pool_alloc2(शून्य *opaque, size_t आकार)
{
    pool_alloc2_called = 1;
    प्रत्यागम av_बफर_alloc(आकार);
}

स्थिर शून्य pool_free_cb(शून्य *opaque)
{
    pool_free_called = 1;
}

पूर्णाङ्क मुख्यम्(शून्य)
{
    AVBufferRef *buf, *buf2;
    AVBufferPool *pool;

    /* av_buffer_alloc */
    प्रारूप_लिख("Testing av_buffer_alloc()\n");
    buf = av_बफर_alloc(64);
    यदि (buf) {
        प्रारूप_लिख("alloc: size=%zu data=%s\n", buf->आकार, buf->दत्त ? "set" : "null");
        प्रारूप_लिख("writable: %d\n", av_बफर_is_writable(buf));
        प्रारूप_लिख("refcount: %d\n", av_बफर_get_ref_गणनम्(buf));
        av_बफर_unref(&buf);
        प्रारूप_लिख("after unref: %s\n", buf == रिक्त ? "null" : "leaked");
    }

    /* av_buffer_allocz */
    प्रारूप_लिख("\nTesting av_buffer_allocz()\n");
    buf = av_बफर_allocz(16);
    यदि (buf) {
        पूर्णाङ्क zeroed = 1;
        प्रति (पूर्णाङ्क i = 0; i < 16; i++)
            यदि (buf->दत्त[i] != 0) zeroed = 0;
        प्रारूप_लिख("allocz: zeroed=%s\n", zeroed ? "yes" : "no");
        av_बफर_unref(&buf);
    }

    /* av_buffer_create with custom free */
    प्रारूप_लिख("\nTesting av_buffer_create()\n");
    {
        uint8_t *दत्त = av_malloc(32);
        यदि (दत्त) {
            custom_free_called = 0;
            buf = av_बफर_create(दत्त, 32, custom_free, रिक्त, 0);
            यदि (buf) {
                प्रारूप_लिख("create: size=%zu\n", buf->आकार);
                प्रारूप_लिख("opaque: %s\n",
                       av_बफर_get_opaque(buf) == रिक्त ? "null" : "set");
                av_बफर_unref(&buf);
                प्रारूप_लिख("custom_free called: %s\n",
                       custom_free_called ? "yes" : "no");
            } अन्यथा {
                av_free(दत्त);
            }
        }
    }

    /* av_buffer_create with READONLY flag */
    प्रारूप_लिख("\nTesting AV_BUFFER_FLAG_READONLY\n");
    {
        uint8_t *दत्त = av_malloc(16);
        यदि (दत्त) {
            buf = av_बफर_create(दत्त, 16, custom_free, रिक्त,
                                   AV_बफर_FLAG_READONLY);
            यदि (buf) {
                प्रारूप_लिख("readonly writable: %d\n", av_बफर_is_writable(buf));
                av_बफर_unref(&buf);
            } अन्यथा {
                av_free(दत्त);
            }
        }
    }

    /* av_buffer_ref and refcounting */
    प्रारूप_लिख("\nTesting av_buffer_ref()\n");
    buf = av_बफर_alloc(32);
    यदि (buf) {
        buf->दत्त[0] = 0xAB;
        buf2 = av_बफर_ref(buf);
        यदि (buf2) {
            प्रारूप_लिख("ref: refcount=%d\n", av_बफर_get_ref_गणनम्(buf));
            प्रारूप_लिख("shared data: %s\n",
                   buf2->दत्त[0] == 0xAB ? "yes" : "no");
            प्रारूप_लिख("writable after ref: %d\n", av_बफर_is_writable(buf));
            av_बफर_unref(&buf2);
            प्रारूप_लिख("refcount after unref: %d\n", av_बफर_get_ref_गणनम्(buf));
            प्रारूप_लिख("writable after unref: %d\n", av_बफर_is_writable(buf));
        }
        av_बफर_unref(&buf);
    }

    /* av_buffer_make_writable */
    प्रारूप_लिख("\nTesting av_buffer_make_writable()\n");
    buf = av_बफर_alloc(16);
    यदि (buf) {
        buf->दत्त[0] = 0xCD;
        buf2 = av_बफर_ref(buf);
        यदि (buf2) {
            पूर्णाङ्क ret = av_बफर_make_writable(&buf2);
            प्रारूप_लिख("make_writable ret: %d\n", ret >= 0);
            प्रारूप_लिख("data preserved: %s\n",
                   buf2->दत्त[0] == 0xCD ? "yes" : "no");
            प्रारूप_लिख("now writable: %d\n", av_बफर_is_writable(buf2));
            प्रारूप_लिख("original still valid: %s\n",
                   buf->दत्त[0] == 0xCD ? "yes" : "no");
            av_बफर_unref(&buf2);
        }
        av_बफर_unref(&buf);
    }

    /* av_buffer_realloc */
    प्रारूप_लिख("\nTesting av_buffer_realloc()\n");
    buf = av_बफर_alloc(16);
    यदि (buf) {
        स्मृतिं_पूरय(buf->दत्त, 0xEF, 16);
        av_बफर_realloc(&buf, 32);
        यदि (buf) {
            प्रारूप_लिख("realloc: size=%zu\n", buf->आकार);
            प्रारूप_लिख("data preserved: %s\n",
                   buf->दत्त[0] == 0xEF ? "yes" : "no");
        }
        av_बफर_unref(&buf);
    }
    /* realloc from NULL */
    buf = रिक्त;
    av_बफर_realloc(&buf, 8);
    प्रारूप_लिख("realloc from null: %s\n", buf ? "OK" : "FAIL");
    av_बफर_unref(&buf);

    /* av_buffer_replace */
    प्रारूप_लिख("\nTesting av_buffer_replace()\n");
    buf = av_बफर_alloc(8);
    buf2 = av_बफर_alloc(8);
    यदि (buf && buf2) {
        buf->दत्त[0] = 0x11;
        buf2->दत्त[0] = 0x22;
        av_बफर_replace(&buf, buf2);
        प्रारूप_लिख("replace: data=0x%02x\n", buf->दत्त[0]);
        प्रारूप_लिख("refcount: %d\n", av_बफर_get_ref_गणनम्(buf2));
    }
    av_बफर_unref(&buf);
    av_बफर_unref(&buf2);

    /* replace with NULL */
    buf = av_बफर_alloc(8);
    यदि (buf) {
        av_बफर_replace(&buf, रिक्त);
        प्रारूप_लिख("replace with null: %s\n", buf == रिक्त ? "OK" : "FAIL");
    }

    /* av_buffer_pool */
    प्रारूप_लिख("\nTesting av_buffer_pool()\n");
    pool = av_बफर_pool_init(64, रिक्त);
    यदि (pool) {
        buf = av_बफर_pool_get(pool);
        यदि (buf) {
            प्रारूप_लिख("pool get: size=%zu\n", buf->आकार);
            av_बफर_unref(&buf);
        }
        /* get again -- should reuse the released buffer */
        buf = av_बफर_pool_get(pool);
        यदि (buf) {
            प्रारूप_लिख("pool reuse: size=%zu\n", buf->आकार);
            av_बफर_unref(&buf);
        }
        av_बफर_pool_uninit(&pool);
        प्रारूप_लिख("pool uninit: %s\n", pool == रिक्त ? "OK" : "FAIL");
    }

    /* av_buffer_pool_init2 with custom alloc and pool_free callbacks */
    प्रारूप_लिख("\nTesting av_buffer_pool_init2()\n");
    pool_alloc2_called = 0;
    pool_free_called = 0;
    pool = av_बफर_pool_init2(64, रिक्त, pool_alloc2, pool_free_cb);
    यदि (pool) {
        buf = av_बफर_pool_get(pool);
        यदि (buf) {
            प्रारूप_लिख("pool2 get: size=%zu\n", buf->आकार);
            प्रारूप_लिख("alloc2 called: %s\n", pool_alloc2_called ? "yes" : "no");
            प्रारूप_लिख("pool_buffer_get_opaque: %s\n",
                   av_बफर_pool_बफर_get_opaque(buf) == रिक्त ? "null" : "set");
            av_बफर_unref(&buf);
        }
        av_बफर_pool_uninit(&pool);
        प्रारूप_लिख("pool_free called: %s\n", pool_free_called ? "yes" : "no");
    }

    /* OOM paths via av_max_alloc */
    प्रारूप_लिख("\nTesting OOM paths\n");
    av_max_alloc(1);
    buf = av_बफर_alloc(64);
    प्रारूप_लिख("alloc OOM: %s\n", buf ? "FAIL" : "OK");
    av_बफर_unref(&buf);
    buf = av_बफर_allocz(64);
    प्रारूप_लिख("allocz OOM: %s\n", buf ? "FAIL" : "OK");
    av_बफर_unref(&buf);
    pool = av_बफर_pool_init(64, रिक्त);
    प्रारूप_लिख("pool init OOM: %s\n", pool ? "FAIL" : "OK");
    av_बफर_pool_uninit(&pool);
    av_max_alloc(अधिकतम_पूर्णाङ्कः);

    buf = av_बफर_alloc(16);
    यदि (buf) {
        av_max_alloc(1);
        buf2 = av_बफर_ref(buf);
        प्रारूप_लिख("ref OOM: %s\n", buf2 ? "FAIL" : "OK");
        av_बफर_unref(&buf2);
        प्रारूप_लिख("realloc OOM: %s\n",
               av_बफर_realloc(&buf, 1024) < 0 ? "OK" : "FAIL");
        av_max_alloc(अधिकतम_पूर्णाङ्कः);
        av_बफर_unref(&buf);
    }

    प्रत्यागम 0;
}
