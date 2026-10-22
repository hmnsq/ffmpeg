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

#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "libavutil/random_seed.h"
#അന്തര്ഭാവ "libavutil/lfg.h"
#അന്തര്ഭാവ "libavutil/log.h"
#അന്തര്ഭാവ "libavutil/mem_internal.h"
#അന്തര്ഭാവ "libavutil/aes_ctr.h"

സ്ഥിതം സ്ഥിരം DECLARE_ALIGNED(8, uint8_t, plain)[] = {
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f
};

സ്ഥിതം സ്ഥിരം DECLARE_ALIGNED(8, uint8_t, encrypted)[] = {
    0x95, 0xcd, 0x9a, 0x8a, 0x83, 0xa2, 0x1a, 0x84, 0x92, 0xed,
    0xd6, 0xf2, 0x57, 0x2f, 0x61, 0x98, 0xbc, 0x20, 0x98, 0xee,
    0x6c, 0xed, 0x53, 0xae, 0x2f, 0xc4, 0x18, 0x7c, 0xeb, 0x62,
    0xbb, 0x3a, 0x71, 0x24, 0x22, 0x8c, 0xd9, 0xfa, 0xee, 0x10
};

സ്ഥിതം സ്ഥിരം DECLARE_ALIGNED(8, uint8_t, fixed_iv)[] = {
    0xde, 0xad, 0xbe, 0xef, 0xde, 0xad, 0xbe, 0xef
};

സ്ഥിതം സ്ഥിരം DECLARE_ALIGNED(8, uint8_t, fixed_താക്കോൽ)[] = {
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66
};

സ്ഥിതം DECLARE_ALIGNED(8, uint32_t, താക്കോൽ)[4];

സ്ഥിതം DECLARE_ALIGNED(8, uint8_t, tmp)[40];

പൂർണ്ണസംഖ്യ പ്രധാന (ശൂന്യം)
{
    പൂർണ്ണസംഖ്യ ret = 1;
    AVLFG lfg;
    ഘടന AVAESCTR *ae, *ad;
    സ്ഥിരം uint8_t *iv, *k;

    av_lfg_init(&lfg, av_get_random_seed());

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < 2; i++) {
        ae = av_aes_ctr_alloc();
        ad = av_aes_ctr_alloc();

        എങ്കിൽ (!ae || !ad)
            പോകുക ERROR;

        എങ്കിൽ (i)
            k = fixed_താക്കോൽ;
        അല്ലെങ്കിൽ {
            // Note: av_random_bytes() should be used in a real world scenario,
            // but since that function can fail, av_get_random_seed() is used
            // here for the purpose of this test, as its output is sufficient.
            താക്കോൽ[0] = av_get_random_seed();
            താക്കോൽ[1] = av_get_random_seed();
            താക്കോൽ[2] = av_get_random_seed();
            താക്കോൽ[3] = av_get_random_seed();
            k = (uint8_t *)താക്കോൽ;
        }

        എങ്കിൽ (av_aes_ctr_init(ae, k) < 0)
            പോകുക ERROR;

        എങ്കിൽ (av_aes_ctr_init(ad, k) < 0)
            പോകുക ERROR;

        എങ്കിൽ (i)
            av_aes_ctr_set_iv(ae, fixed_iv);
        അല്ലെങ്കിൽ
            av_aes_ctr_set_random_iv(ae);
        iv =   av_aes_ctr_get_iv(ae);
        av_aes_ctr_set_full_iv(ad, iv);

        uint8_t *dst = tmp;
        സ്ഥിരം uint8_t *src = plain;
        പൂർണ്ണസംഖ്യ ഇടത് = വലുപ്പം(plain);
        ആകുമ്പോൾ (ഇടത് > 0) {
            പൂർണ്ണസംഖ്യ എണ്ണം = (av_lfg_get(&lfg) % ഇടത്) + 1;
            av_aes_ctr_crypt(ae, dst, src, എണ്ണം);
            dst += എണ്ണം;
            src += എണ്ണം;
            ഇടത് -= എണ്ണം;
        }
        എങ്കിൽ (i && memcmp(tmp, encrypted, വലുപ്പം(tmp)) != 0) {
            av_log(ശൂന്യ, AV_LOG_ERROR, "test failed\n");
            പോകുക ERROR;
        }

        dst = tmp;
        ഇടത് = വലുപ്പം(plain);
        ആകുമ്പോൾ (ഇടത് > 0) {
            പൂർണ്ണസംഖ്യ എണ്ണം = (av_lfg_get(&lfg) % ഇടത്) + 1;
            av_aes_ctr_crypt(ad, dst, dst, എണ്ണം);
            dst += എണ്ണം;
            ഇടത് -= എണ്ണം;
        }

        എങ്കിൽ (memcmp(tmp, plain, വലുപ്പം(tmp)) != 0){
            av_log(ശൂന്യ, AV_LOG_ERROR, "test failed\n");
            പോകുക ERROR;
        }

        av_aes_ctr_free(ae);
        av_aes_ctr_free(ad);
        ae = ad = ശൂന്യ;
    }

    av_log(ശൂന്യ, AV_LOG_INFO, "test passed\n");
    ret = 0;

ERROR:
    av_aes_ctr_free(ae);
    av_aes_ctr_free(ad);
    തിരികെ ret;
}
