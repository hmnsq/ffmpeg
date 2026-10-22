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

#अन्तर्भाव <string.h>

#अन्तर्भाव "libavutil/random_seed.h"
#अन्तर्भाव "libavutil/lfg.h"
#अन्तर्भाव "libavutil/log.h"
#अन्तर्भाव "libavutil/mem_internal.h"
#अन्तर्भाव "libavutil/aes_ctr.h"

स्थिर ध्रुव DECLARE_ALIGNED(8, uint8_t, plain)[] = {
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f
};

स्थिर ध्रुव DECLARE_ALIGNED(8, uint8_t, encrypted)[] = {
    0x95, 0xcd, 0x9a, 0x8a, 0x83, 0xa2, 0x1a, 0x84, 0x92, 0xed,
    0xd6, 0xf2, 0x57, 0x2f, 0x61, 0x98, 0xbc, 0x20, 0x98, 0xee,
    0x6c, 0xed, 0x53, 0xae, 0x2f, 0xc4, 0x18, 0x7c, 0xeb, 0x62,
    0xbb, 0x3a, 0x71, 0x24, 0x22, 0x8c, 0xd9, 0xfa, 0xee, 0x10
};

स्थिर ध्रुव DECLARE_ALIGNED(8, uint8_t, fixed_iv)[] = {
    0xde, 0xad, 0xbe, 0xef, 0xde, 0xad, 0xbe, 0xef
};

स्थिर ध्रुव DECLARE_ALIGNED(8, uint8_t, fixed_कुञ्चिका)[] = {
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66
};

स्थिर DECLARE_ALIGNED(8, uint32_t, कुञ्चिका)[4];

स्थिर DECLARE_ALIGNED(8, uint8_t, tmp)[40];

पूर्णाङ्क मुख्यम् (शून्य)
{
    पूर्णाङ्क ret = 1;
    AVLFG lfg;
    संरचना AVAESCTR *ae, *ad;
    ध्रुव uint8_t *iv, *k;

    av_lfg_init(&lfg, av_get_random_बीजम्());

    प्रति (पूर्णाङ्क i = 0; i < 2; i++) {
        ae = av_aes_ctr_alloc();
        ad = av_aes_ctr_alloc();

        यदि (!ae || !ad)
            गच्छ ERROR;

        यदि (i)
            k = fixed_कुञ्चिका;
        अन्यथा {
            // Note: av_random_bytes() should be used in a real world scenario,
            // but since that function can fail, av_get_random_seed() is used
            // here for the purpose of this test, as its output is sufficient.
            कुञ्चिका[0] = av_get_random_बीजम्();
            कुञ्चिका[1] = av_get_random_बीजम्();
            कुञ्चिका[2] = av_get_random_बीजम्();
            कुञ्चिका[3] = av_get_random_बीजम्();
            k = (uint8_t *)कुञ्चिका;
        }

        यदि (av_aes_ctr_init(ae, k) < 0)
            गच्छ ERROR;

        यदि (av_aes_ctr_init(ad, k) < 0)
            गच्छ ERROR;

        यदि (i)
            av_aes_ctr_समुच्चयः_iv(ae, fixed_iv);
        अन्यथा
            av_aes_ctr_समुच्चयः_random_iv(ae);
        iv =   av_aes_ctr_get_iv(ae);
        av_aes_ctr_समुच्चयः_पूर्णम्_iv(ad, iv);

        uint8_t *dst = tmp;
        ध्रुव uint8_t *src = plain;
        पूर्णाङ्क वामः = परिमाण(plain);
        यावत् (वामः > 0) {
            पूर्णाङ्क गणनम् = (av_lfg_get(&lfg) % वामः) + 1;
            av_aes_ctr_crypt(ae, dst, src, गणनम्);
            dst += गणनम्;
            src += गणनम्;
            वामः -= गणनम्;
        }
        यदि (i && memcmp(tmp, encrypted, परिमाण(tmp)) != 0) {
            av_log(रिक्त, AV_LOG_ERROR, "test failed\n");
            गच्छ ERROR;
        }

        dst = tmp;
        वामः = परिमाण(plain);
        यावत् (वामः > 0) {
            पूर्णाङ्क गणनम् = (av_lfg_get(&lfg) % वामः) + 1;
            av_aes_ctr_crypt(ad, dst, dst, गणनम्);
            dst += गणनम्;
            वामः -= गणनम्;
        }

        यदि (memcmp(tmp, plain, परिमाण(tmp)) != 0){
            av_log(रिक्त, AV_LOG_ERROR, "test failed\n");
            गच्छ ERROR;
        }

        av_aes_ctr_free(ae);
        av_aes_ctr_free(ad);
        ae = ad = रिक्त;
    }

    av_log(रिक्त, AV_LOG_INFO, "test passed\n");
    ret = 0;

ERROR:
    av_aes_ctr_free(ae);
    av_aes_ctr_free(ad);
    प्रत्यागम ret;
}
