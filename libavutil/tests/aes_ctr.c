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

#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/random_seed.h"
#ಅನ್ತರ್ಭಾವ "libavutil/lfg.h"
#ಅನ್ತರ್ಭಾವ "libavutil/log.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem_internal.h"
#ಅನ್ತರ್ಭಾವ "libavutil/aes_ctr.h"

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ DECLARE_ALIGNED(8, uint8_t, plain)[] = {
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ DECLARE_ALIGNED(8, uint8_t, encrypted)[] = {
    0x95, 0xcd, 0x9a, 0x8a, 0x83, 0xa2, 0x1a, 0x84, 0x92, 0xed,
    0xd6, 0xf2, 0x57, 0x2f, 0x61, 0x98, 0xbc, 0x20, 0x98, 0xee,
    0x6c, 0xed, 0x53, 0xae, 0x2f, 0xc4, 0x18, 0x7c, 0xeb, 0x62,
    0xbb, 0x3a, 0x71, 0x24, 0x22, 0x8c, 0xd9, 0xfa, 0xee, 0x10
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ DECLARE_ALIGNED(8, uint8_t, fixed_iv)[] = {
    0xde, 0xad, 0xbe, 0xef, 0xde, 0xad, 0xbe, 0xef
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ DECLARE_ALIGNED(8, uint8_t, fixed_ಕೀಲಿ)[] = {
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66
};

ಸ್ಥಿರ DECLARE_ALIGNED(8, uint32_t, ಕೀಲಿ)[4];

ಸ್ಥಿರ DECLARE_ALIGNED(8, uint8_t, tmp)[40];

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ (ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ ret = 1;
    AVLFG lfg;
    ರಚನೆ AVAESCTR *ae, *ad;
    ಸ್ಥಿರಾಂಕ uint8_t *iv, *k;

    av_lfg_init(&lfg, av_get_random_ಬೀಜ());

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 2; i++) {
        ae = av_aes_ctr_alloc();
        ad = av_aes_ctr_alloc();

        ಆದರೆ (!ae || !ad)
            ಹೋಗು ERROR;

        ಆದರೆ (i)
            k = fixed_ಕೀಲಿ;
        ಇಲ್ಲದಿದ್ದರೆ {
            // Note: av_random_bytes() should be used in a real world scenario,
            // but since that function can fail, av_get_random_seed() is used
            // here for the purpose of this test, as its output is sufficient.
            ಕೀಲಿ[0] = av_get_random_ಬೀಜ();
            ಕೀಲಿ[1] = av_get_random_ಬೀಜ();
            ಕೀಲಿ[2] = av_get_random_ಬೀಜ();
            ಕೀಲಿ[3] = av_get_random_ಬೀಜ();
            k = (uint8_t *)ಕೀಲಿ;
        }

        ಆದರೆ (av_aes_ctr_init(ae, k) < 0)
            ಹೋಗು ERROR;

        ಆದರೆ (av_aes_ctr_init(ad, k) < 0)
            ಹೋಗು ERROR;

        ಆದರೆ (i)
            av_aes_ctr_ಗಣ_iv(ae, fixed_iv);
        ಇಲ್ಲದಿದ್ದರೆ
            av_aes_ctr_ಗಣ_random_iv(ae);
        iv =   av_aes_ctr_get_iv(ae);
        av_aes_ctr_ಗಣ_ತುಂಬಿದ_iv(ad, iv);

        uint8_t *dst = tmp;
        ಸ್ಥಿರಾಂಕ uint8_t *src = plain;
        ಪೂರ್ಣಾಂಕ ಎಡ = ಗಾತ್ರ(plain);
        ಆಗ (ಎಡ > 0) {
            ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2 = (av_lfg_get(&lfg) % ಎಡ) + 1;
            av_aes_ctr_crypt(ae, dst, src, ಎಣಿಕೆ_2);
            dst += ಎಣಿಕೆ_2;
            src += ಎಣಿಕೆ_2;
            ಎಡ -= ಎಣಿಕೆ_2;
        }
        ಆದರೆ (i && memcmp(tmp, encrypted, ಗಾತ್ರ(tmp)) != 0) {
            av_log(ಖಾಲಿ, AV_LOG_ERROR, "test failed\n");
            ಹೋಗು ERROR;
        }

        dst = tmp;
        ಎಡ = ಗಾತ್ರ(plain);
        ಆಗ (ಎಡ > 0) {
            ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2 = (av_lfg_get(&lfg) % ಎಡ) + 1;
            av_aes_ctr_crypt(ad, dst, dst, ಎಣಿಕೆ_2);
            dst += ಎಣಿಕೆ_2;
            ಎಡ -= ಎಣಿಕೆ_2;
        }

        ಆದರೆ (memcmp(tmp, plain, ಗಾತ್ರ(tmp)) != 0){
            av_log(ಖಾಲಿ, AV_LOG_ERROR, "test failed\n");
            ಹೋಗು ERROR;
        }

        av_aes_ctr_free(ae);
        av_aes_ctr_free(ad);
        ae = ad = ಖಾಲಿ;
    }

    av_log(ಖಾಲಿ, AV_LOG_INFO, "test passed\n");
    ret = 0;

ERROR:
    av_aes_ctr_free(ae);
    av_aes_ctr_free(ad);
    ಹಿಂತಿರುಗಿ ret;
}
