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

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ custom_free_called;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ pool_free_called;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ pool_alloc2_called;

ಸ್ಥಿರ ಶೂನ್ಯ custom_free(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{
    custom_free_called = 1;
    av_free(ದತ್ತಾಂಶ);
}

ಸ್ಥಿರ AVBufferRef *pool_alloc2(ಶೂನ್ಯ *opaque, size_t ಗಾತ್ರ_2)
{
    pool_alloc2_called = 1;
    ಹಿಂತಿರುಗಿ av_ಬಫರ್_alloc(ಗಾತ್ರ_2);
}

ಸ್ಥಿರ ಶೂನ್ಯ pool_free_cb(ಶೂನ್ಯ *opaque)
{
    pool_free_called = 1;
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    AVBufferRef *buf, *buf2;
    AVBufferPool *pool;

    /* av_buffer_alloc */
    ಬರೆ("Testing av_buffer_alloc()\n");
    buf = av_ಬಫರ್_alloc(64);
    ಆದರೆ (buf) {
        ಬರೆ("alloc: size=%zu data=%s\n", buf->ಗಾತ್ರ_2, buf->ದತ್ತಾಂಶ ? "set" : "null");
        ಬರೆ("writable: %d\n", av_ಬಫರ್_is_writable(buf));
        ಬರೆ("refcount: %d\n", av_ಬಫರ್_get_ref_ಎಣಿಕೆ(buf));
        av_ಬಫರ್_unref(&buf);
        ಬರೆ("after unref: %s\n", buf == ಖಾಲಿ ? "null" : "leaked");
    }

    /* av_buffer_allocz */
    ಬರೆ("\nTesting av_buffer_allocz()\n");
    buf = av_ಬಫರ್_allocz(16);
    ಆದರೆ (buf) {
        ಪೂರ್ಣಾಂಕ zeroed = 1;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 16; i++)
            ಆದರೆ (buf->ದತ್ತಾಂಶ[i] != 0) zeroed = 0;
        ಬರೆ("allocz: zeroed=%s\n", zeroed ? "yes" : "no");
        av_ಬಫರ್_unref(&buf);
    }

    /* av_buffer_create with custom free */
    ಬರೆ("\nTesting av_buffer_create()\n");
    {
        uint8_t *ದತ್ತಾಂಶ = av_malloc(32);
        ಆದರೆ (ದತ್ತಾಂಶ) {
            custom_free_called = 0;
            buf = av_ಬಫರ್_create(ದತ್ತಾಂಶ, 32, custom_free, ಖಾಲಿ, 0);
            ಆದರೆ (buf) {
                ಬರೆ("create: size=%zu\n", buf->ಗಾತ್ರ_2);
                ಬರೆ("opaque: %s\n",
                       av_ಬಫರ್_get_opaque(buf) == ಖಾಲಿ ? "null" : "set");
                av_ಬಫರ್_unref(&buf);
                ಬರೆ("custom_free called: %s\n",
                       custom_free_called ? "yes" : "no");
            } ಇಲ್ಲದಿದ್ದರೆ {
                av_free(ದತ್ತಾಂಶ);
            }
        }
    }

    /* av_buffer_create with READONLY flag */
    ಬರೆ("\nTesting AV_BUFFER_FLAG_READONLY\n");
    {
        uint8_t *ದತ್ತಾಂಶ = av_malloc(16);
        ಆದರೆ (ದತ್ತಾಂಶ) {
            buf = av_ಬಫರ್_create(ದತ್ತಾಂಶ, 16, custom_free, ಖಾಲಿ,
                                   AV_ಬಫರ್_FLAG_READONLY);
            ಆದರೆ (buf) {
                ಬರೆ("readonly writable: %d\n", av_ಬಫರ್_is_writable(buf));
                av_ಬಫರ್_unref(&buf);
            } ಇಲ್ಲದಿದ್ದರೆ {
                av_free(ದತ್ತಾಂಶ);
            }
        }
    }

    /* av_buffer_ref and refcounting */
    ಬರೆ("\nTesting av_buffer_ref()\n");
    buf = av_ಬಫರ್_alloc(32);
    ಆದರೆ (buf) {
        buf->ದತ್ತಾಂಶ[0] = 0xAB;
        buf2 = av_ಬಫರ್_ref(buf);
        ಆದರೆ (buf2) {
            ಬರೆ("ref: refcount=%d\n", av_ಬಫರ್_get_ref_ಎಣಿಕೆ(buf));
            ಬರೆ("shared data: %s\n",
                   buf2->ದತ್ತಾಂಶ[0] == 0xAB ? "yes" : "no");
            ಬರೆ("writable after ref: %d\n", av_ಬಫರ್_is_writable(buf));
            av_ಬಫರ್_unref(&buf2);
            ಬರೆ("refcount after unref: %d\n", av_ಬಫರ್_get_ref_ಎಣಿಕೆ(buf));
            ಬರೆ("writable after unref: %d\n", av_ಬಫರ್_is_writable(buf));
        }
        av_ಬಫರ್_unref(&buf);
    }

    /* av_buffer_make_writable */
    ಬರೆ("\nTesting av_buffer_make_writable()\n");
    buf = av_ಬಫರ್_alloc(16);
    ಆದರೆ (buf) {
        buf->ದತ್ತಾಂಶ[0] = 0xCD;
        buf2 = av_ಬಫರ್_ref(buf);
        ಆದರೆ (buf2) {
            ಪೂರ್ಣಾಂಕ ret = av_ಬಫರ್_make_writable(&buf2);
            ಬರೆ("make_writable ret: %d\n", ret >= 0);
            ಬರೆ("data preserved: %s\n",
                   buf2->ದತ್ತಾಂಶ[0] == 0xCD ? "yes" : "no");
            ಬರೆ("now writable: %d\n", av_ಬಫರ್_is_writable(buf2));
            ಬರೆ("original still valid: %s\n",
                   buf->ದತ್ತಾಂಶ[0] == 0xCD ? "yes" : "no");
            av_ಬಫರ್_unref(&buf2);
        }
        av_ಬಫರ್_unref(&buf);
    }

    /* av_buffer_realloc */
    ಬರೆ("\nTesting av_buffer_realloc()\n");
    buf = av_ಬಫರ್_alloc(16);
    ಆದರೆ (buf) {
        memset(buf->ದತ್ತಾಂಶ, 0xEF, 16);
        av_ಬಫರ್_realloc(&buf, 32);
        ಆದರೆ (buf) {
            ಬರೆ("realloc: size=%zu\n", buf->ಗಾತ್ರ_2);
            ಬರೆ("data preserved: %s\n",
                   buf->ದತ್ತಾಂಶ[0] == 0xEF ? "yes" : "no");
        }
        av_ಬಫರ್_unref(&buf);
    }
    /* realloc from NULL */
    buf = ಖಾಲಿ;
    av_ಬಫರ್_realloc(&buf, 8);
    ಬರೆ("realloc from null: %s\n", buf ? "OK" : "FAIL");
    av_ಬಫರ್_unref(&buf);

    /* av_buffer_replace */
    ಬರೆ("\nTesting av_buffer_replace()\n");
    buf = av_ಬಫರ್_alloc(8);
    buf2 = av_ಬಫರ್_alloc(8);
    ಆದರೆ (buf && buf2) {
        buf->ದತ್ತಾಂಶ[0] = 0x11;
        buf2->ದತ್ತಾಂಶ[0] = 0x22;
        av_ಬಫರ್_replace(&buf, buf2);
        ಬರೆ("replace: data=0x%02x\n", buf->ದತ್ತಾಂಶ[0]);
        ಬರೆ("refcount: %d\n", av_ಬಫರ್_get_ref_ಎಣಿಕೆ(buf2));
    }
    av_ಬಫರ್_unref(&buf);
    av_ಬಫರ್_unref(&buf2);

    /* replace with NULL */
    buf = av_ಬಫರ್_alloc(8);
    ಆದರೆ (buf) {
        av_ಬಫರ್_replace(&buf, ಖಾಲಿ);
        ಬರೆ("replace with null: %s\n", buf == ಖಾಲಿ ? "OK" : "FAIL");
    }

    /* av_buffer_pool */
    ಬರೆ("\nTesting av_buffer_pool()\n");
    pool = av_ಬಫರ್_pool_init(64, ಖಾಲಿ);
    ಆದರೆ (pool) {
        buf = av_ಬಫರ್_pool_get(pool);
        ಆದರೆ (buf) {
            ಬರೆ("pool get: size=%zu\n", buf->ಗಾತ್ರ_2);
            av_ಬಫರ್_unref(&buf);
        }
        /* get again -- should reuse the released buffer */
        buf = av_ಬಫರ್_pool_get(pool);
        ಆದರೆ (buf) {
            ಬರೆ("pool reuse: size=%zu\n", buf->ಗಾತ್ರ_2);
            av_ಬಫರ್_unref(&buf);
        }
        av_ಬಫರ್_pool_uninit(&pool);
        ಬರೆ("pool uninit: %s\n", pool == ಖಾಲಿ ? "OK" : "FAIL");
    }

    /* av_buffer_pool_init2 with custom alloc and pool_free callbacks */
    ಬರೆ("\nTesting av_buffer_pool_init2()\n");
    pool_alloc2_called = 0;
    pool_free_called = 0;
    pool = av_ಬಫರ್_pool_init2(64, ಖಾಲಿ, pool_alloc2, pool_free_cb);
    ಆದರೆ (pool) {
        buf = av_ಬಫರ್_pool_get(pool);
        ಆದರೆ (buf) {
            ಬರೆ("pool2 get: size=%zu\n", buf->ಗಾತ್ರ_2);
            ಬರೆ("alloc2 called: %s\n", pool_alloc2_called ? "yes" : "no");
            ಬರೆ("pool_buffer_get_opaque: %s\n",
                   av_ಬಫರ್_pool_ಬಫರ್_get_opaque(buf) == ಖಾಲಿ ? "null" : "set");
            av_ಬಫರ್_unref(&buf);
        }
        av_ಬಫರ್_pool_uninit(&pool);
        ಬರೆ("pool_free called: %s\n", pool_free_called ? "yes" : "no");
    }

    /* OOM paths via av_max_alloc */
    ಬರೆ("\nTesting OOM paths\n");
    av_max_alloc(1);
    buf = av_ಬಫರ್_alloc(64);
    ಬರೆ("alloc OOM: %s\n", buf ? "FAIL" : "OK");
    av_ಬಫರ್_unref(&buf);
    buf = av_ಬಫರ್_allocz(64);
    ಬರೆ("allocz OOM: %s\n", buf ? "FAIL" : "OK");
    av_ಬಫರ್_unref(&buf);
    pool = av_ಬಫರ್_pool_init(64, ಖಾಲಿ);
    ಬರೆ("pool init OOM: %s\n", pool ? "FAIL" : "OK");
    av_ಬಫರ್_pool_uninit(&pool);
    av_max_alloc(ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);

    buf = av_ಬಫರ್_alloc(16);
    ಆದರೆ (buf) {
        av_max_alloc(1);
        buf2 = av_ಬಫರ್_ref(buf);
        ಬರೆ("ref OOM: %s\n", buf2 ? "FAIL" : "OK");
        av_ಬಫರ್_unref(&buf2);
        ಬರೆ("realloc OOM: %s\n",
               av_ಬಫರ್_realloc(&buf, 1024) < 0 ? "OK" : "FAIL");
        av_max_alloc(ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);
        av_ಬಫರ್_unref(&buf);
    }

    ಹಿಂತಿರುಗಿ 0;
}
