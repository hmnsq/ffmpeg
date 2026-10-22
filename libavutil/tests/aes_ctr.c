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

ಸ್ಥಿರ ಧ್ರುವ DECLARE_ALIGNED(8, uint8_t, plain)[] = {
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f
};

ಸ್ಥಿರ ಧ್ರುವ DECLARE_ALIGNED(8, uint8_t, encrypted)[] = {
    0x95, 0xcd, 0x9a, 0x8a, 0x83, 0xa2, 0x1a, 0x84, 0x92, 0xed,
    0xd6, 0xf2, 0x57, 0x2f, 0x61, 0x98, 0xbc, 0x20, 0x98, 0xee,
    0x6c, 0xed, 0x53, 0xae, 0x2f, 0xc4, 0x18, 0x7c, 0xeb, 0x62,
    0xbb, 0x3a, 0x71, 0x24, 0x22, 0x8c, 0xd9, 0xfa, 0xee, 0x10
};

ಸ್ಥಿರ ಧ್ರುವ DECLARE_ALIGNED(8, uint8_t, fixed_iv)[] = {
    0xde, 0xad, 0xbe, 0xef, 0xde, 0xad, 0xbe, 0xef
};

ಸ್ಥಿರ ಧ್ರುವ DECLARE_ALIGNED(8, uint8_t, fixed_ಕೀಲಿ)[] = {
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66
};

ಸ್ಥಿರ DECLARE_ALIGNED(8, uint32_t, ಕೀಲಿ)[4];

ಸ್ಥಿರ DECLARE_ALIGNED(8, uint8_t, tmp)[40];

ಪೂರ್ಣಾಙ್ಕ main (ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ ret = 1;
    AVLFG lfg;
    ಸಂರಚನಾ AVAESCTR *ae, *ad;
    ಧ್ರುವ uint8_t *iv, *k;

    av_lfg_init(&lfg, av_get_random_seed());

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < 2; i++) {
        ae = av_aes_ctr_alloc();
        ad = av_aes_ctr_alloc();

        ಯದಿ (!ae || !ad)
            ಗಚ್ಛ ERROR;

        ಯದಿ (i)
            k = fixed_ಕೀಲಿ;
        ಅನ್ಯಥಾ {
            // Note: av_random_bytes() should be used in a real world scenario,
            // but since that function can fail, av_get_random_seed() is used
            // here for the purpose of this test, as its output is sufficient.
            ಕೀಲಿ[0] = av_get_random_seed();
            ಕೀಲಿ[1] = av_get_random_seed();
            ಕೀಲಿ[2] = av_get_random_seed();
            ಕೀಲಿ[3] = av_get_random_seed();
            k = (uint8_t *)ಕೀಲಿ;
        }

        ಯದಿ (av_aes_ctr_init(ae, k) < 0)
            ಗಚ್ಛ ERROR;

        ಯದಿ (av_aes_ctr_init(ad, k) < 0)
            ಗಚ್ಛ ERROR;

        ಯದಿ (i)
            av_aes_ctr_set_iv(ae, fixed_iv);
        ಅನ್ಯಥಾ
            av_aes_ctr_set_random_iv(ae);
        iv =   av_aes_ctr_get_iv(ae);
        av_aes_ctr_set_full_iv(ad, iv);

        uint8_t *dst = tmp;
        ಧ್ರುವ uint8_t *src = plain;
        ಪೂರ್ಣಾಙ್ಕ ಎಡ = ಪರಿಮಾಣ(plain);
        ಯಾವತ್ (ಎಡ > 0) {
            ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ = (av_lfg_get(&lfg) % ಎಡ) + 1;
            av_aes_ctr_crypt(ae, dst, src, ಎಣಿಕೆ);
            dst += ಎಣಿಕೆ;
            src += ಎಣಿಕೆ;
            ಎಡ -= ಎಣಿಕೆ;
        }
        ಯದಿ (i && memcmp(tmp, encrypted, ಪರಿಮಾಣ(tmp)) != 0) {
            av_log(ರಿಕ್ತ, AV_LOG_ERROR, "test failed\n");
            ಗಚ್ಛ ERROR;
        }

        dst = tmp;
        ಎಡ = ಪರಿಮಾಣ(plain);
        ಯಾವತ್ (ಎಡ > 0) {
            ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ = (av_lfg_get(&lfg) % ಎಡ) + 1;
            av_aes_ctr_crypt(ad, dst, dst, ಎಣಿಕೆ);
            dst += ಎಣಿಕೆ;
            ಎಡ -= ಎಣಿಕೆ;
        }

        ಯದಿ (memcmp(tmp, plain, ಪರಿಮಾಣ(tmp)) != 0){
            av_log(ರಿಕ್ತ, AV_LOG_ERROR, "test failed\n");
            ಗಚ್ಛ ERROR;
        }

        av_aes_ctr_free(ae);
        av_aes_ctr_free(ad);
        ae = ad = ರಿಕ್ತ;
    }

    av_log(ರಿಕ್ತ, AV_LOG_INFO, "test passed\n");
    ret = 0;

ERROR:
    av_aes_ctr_free(ae);
    av_aes_ctr_free(ad);
    ಪ್ರತ್ಯಾಗಮ ret;
}
