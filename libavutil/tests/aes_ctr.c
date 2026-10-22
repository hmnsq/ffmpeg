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

#అన్తర్భావ <string.h>

#అన్తర్భావ "libavutil/random_seed.h"
#అన్తర్భావ "libavutil/lfg.h"
#అన్తర్భావ "libavutil/log.h"
#అన్తర్భావ "libavutil/mem_internal.h"
#అన్తర్భావ "libavutil/aes_ctr.h"

స్థిర స్థిరరాశి DECLARE_ALIGNED(8, uint8_t, plain)[] = {
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f
};

స్థిర స్థిరరాశి DECLARE_ALIGNED(8, uint8_t, encrypted)[] = {
    0x95, 0xcd, 0x9a, 0x8a, 0x83, 0xa2, 0x1a, 0x84, 0x92, 0xed,
    0xd6, 0xf2, 0x57, 0x2f, 0x61, 0x98, 0xbc, 0x20, 0x98, 0xee,
    0x6c, 0xed, 0x53, 0xae, 0x2f, 0xc4, 0x18, 0x7c, 0xeb, 0x62,
    0xbb, 0x3a, 0x71, 0x24, 0x22, 0x8c, 0xd9, 0xfa, 0xee, 0x10
};

స్థిర స్థిరరాశి DECLARE_ALIGNED(8, uint8_t, fixed_iv)[] = {
    0xde, 0xad, 0xbe, 0xef, 0xde, 0xad, 0xbe, 0xef
};

స్థిర స్థిరరాశి DECLARE_ALIGNED(8, uint8_t, fixed_కీలకం)[] = {
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66
};

స్థిర DECLARE_ALIGNED(8, uint32_t, కీలకం)[4];

స్థిర DECLARE_ALIGNED(8, uint8_t, tmp)[40];

పూర్ణాంకం ప్రధాన (శూన్య)
{
    పూర్ణాంకం ret = 1;
    AVLFG lfg;
    నిర్మాణం AVAESCTR *ae, *ad;
    స్థిరరాశి uint8_t *iv, *k;

    av_lfg_init(&lfg, av_get_random_విత్తనం());

    కొరకు (పూర్ణాంకం i = 0; i < 2; i++) {
        ae = av_aes_ctr_alloc();
        ad = av_aes_ctr_alloc();

        ఒకవేళ (!ae || !ad)
            వెళ్ళు ERROR;

        ఒకవేళ (i)
            k = fixed_కీలకం;
        లేకపోతే {
            // Note: av_random_bytes() should be used in a real world scenario,
            // but since that function can fail, av_get_random_seed() is used
            // here for the purpose of this test, as its output is sufficient.
            కీలకం[0] = av_get_random_విత్తనం();
            కీలకం[1] = av_get_random_విత్తనం();
            కీలకం[2] = av_get_random_విత్తనం();
            కీలకం[3] = av_get_random_విత్తనం();
            k = (uint8_t *)కీలకం;
        }

        ఒకవేళ (av_aes_ctr_init(ae, k) < 0)
            వెళ్ళు ERROR;

        ఒకవేళ (av_aes_ctr_init(ad, k) < 0)
            వెళ్ళు ERROR;

        ఒకవేళ (i)
            av_aes_ctr_సమితి_iv(ae, fixed_iv);
        లేకపోతే
            av_aes_ctr_సమితి_random_iv(ae);
        iv =   av_aes_ctr_get_iv(ae);
        av_aes_ctr_సమితి_నిండిన_iv(ad, iv);

        uint8_t *dst = tmp;
        స్థిరరాశి uint8_t *src = plain;
        పూర్ణాంకం ఎడమ = పరిమాణం(plain);
        అయితే (ఎడమ > 0) {
            పూర్ణాంకం లెక్క = (av_lfg_get(&lfg) % ఎడమ) + 1;
            av_aes_ctr_crypt(ae, dst, src, లెక్క);
            dst += లెక్క;
            src += లెక్క;
            ఎడమ -= లెక్క;
        }
        ఒకవేళ (i && memcmp(tmp, encrypted, పరిమాణం(tmp)) != 0) {
            av_log(ఖాళీ, AV_LOG_ERROR, "test failed\n");
            వెళ్ళు ERROR;
        }

        dst = tmp;
        ఎడమ = పరిమాణం(plain);
        అయితే (ఎడమ > 0) {
            పూర్ణాంకం లెక్క = (av_lfg_get(&lfg) % ఎడమ) + 1;
            av_aes_ctr_crypt(ad, dst, dst, లెక్క);
            dst += లెక్క;
            ఎడమ -= లెక్క;
        }

        ఒకవేళ (memcmp(tmp, plain, పరిమాణం(tmp)) != 0){
            av_log(ఖాళీ, AV_LOG_ERROR, "test failed\n");
            వెళ్ళు ERROR;
        }

        av_aes_ctr_free(ae);
        av_aes_ctr_free(ad);
        ae = ad = ఖాళీ;
    }

    av_log(ఖాళీ, AV_LOG_INFO, "test passed\n");
    ret = 0;

ERROR:
    av_aes_ctr_free(ae);
    av_aes_ctr_free(ad);
    తిరిగి ret;
}
