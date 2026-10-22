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

#समावेश <string.h>

#समावेश "libavutil/random_seed.h"
#समावेश "libavutil/lfg.h"
#समावेश "libavutil/log.h"
#समावेश "libavutil/mem_internal.h"
#समावेश "libavutil/aes_ctr.h"

अटल स्थिर DECLARE_ALIGNED(8, uint8_t, plain)[] = {
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f
};

अटल स्थिर DECLARE_ALIGNED(8, uint8_t, encrypted)[] = {
    0x95, 0xcd, 0x9a, 0x8a, 0x83, 0xa2, 0x1a, 0x84, 0x92, 0xed,
    0xd6, 0xf2, 0x57, 0x2f, 0x61, 0x98, 0xbc, 0x20, 0x98, 0xee,
    0x6c, 0xed, 0x53, 0xae, 0x2f, 0xc4, 0x18, 0x7c, 0xeb, 0x62,
    0xbb, 0x3a, 0x71, 0x24, 0x22, 0x8c, 0xd9, 0xfa, 0xee, 0x10
};

अटल स्थिर DECLARE_ALIGNED(8, uint8_t, fixed_iv)[] = {
    0xde, 0xad, 0xbe, 0xef, 0xde, 0xad, 0xbe, 0xef
};

अटल स्थिर DECLARE_ALIGNED(8, uint8_t, fixed_कुंजी)[] = {
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66
};

अटल DECLARE_ALIGNED(8, uint32_t, कुंजी)[4];

अटल DECLARE_ALIGNED(8, uint8_t, tmp)[40];

पूर्णांक मुख्य (व्योम)
{
    पूर्णांक ret = 1;
    AVLFG lfg;
    काष्ठा AVAESCTR *ae, *ad;
    स्थिर uint8_t *iv, *k;

    av_lfg_init(&lfg, av_get_random_seed());

    क्रम (पूर्णांक i = 0; i < 2; i++) {
        ae = av_aes_ctr_alloc();
        ad = av_aes_ctr_alloc();

        अगर (!ae || !ad)
            जाओ ERROR;

        अगर (i)
            k = fixed_कुंजी;
        अन्यथा {
            // Note: av_random_bytes() should be used in a real world scenario,
            // but since that function can fail, av_get_random_seed() is used
            // here for the purpose of this test, as its output is sufficient.
            कुंजी[0] = av_get_random_seed();
            कुंजी[1] = av_get_random_seed();
            कुंजी[2] = av_get_random_seed();
            कुंजी[3] = av_get_random_seed();
            k = (uint8_t *)कुंजी;
        }

        अगर (av_aes_ctr_init(ae, k) < 0)
            जाओ ERROR;

        अगर (av_aes_ctr_init(ad, k) < 0)
            जाओ ERROR;

        अगर (i)
            av_aes_ctr_set_iv(ae, fixed_iv);
        अन्यथा
            av_aes_ctr_set_random_iv(ae);
        iv =   av_aes_ctr_get_iv(ae);
        av_aes_ctr_set_full_iv(ad, iv);

        uint8_t *dst = tmp;
        स्थिर uint8_t *src = plain;
        पूर्णांक बायाँ = माप(plain);
        जबतक (बायाँ > 0) {
            पूर्णांक गिनती = (av_lfg_get(&lfg) % बायाँ) + 1;
            av_aes_ctr_crypt(ae, dst, src, गिनती);
            dst += गिनती;
            src += गिनती;
            बायाँ -= गिनती;
        }
        अगर (i && स_भेद(tmp, encrypted, माप(tmp)) != 0) {
            av_log(शून्य, AV_LOG_ERROR, "test failed\n");
            जाओ ERROR;
        }

        dst = tmp;
        बायाँ = माप(plain);
        जबतक (बायाँ > 0) {
            पूर्णांक गिनती = (av_lfg_get(&lfg) % बायाँ) + 1;
            av_aes_ctr_crypt(ad, dst, dst, गिनती);
            dst += गिनती;
            बायाँ -= गिनती;
        }

        अगर (स_भेद(tmp, plain, माप(tmp)) != 0){
            av_log(शून्य, AV_LOG_ERROR, "test failed\n");
            जाओ ERROR;
        }

        av_aes_ctr_free(ae);
        av_aes_ctr_free(ad);
        ae = ad = शून्य;
    }

    av_log(शून्य, AV_LOG_INFO, "test passed\n");
    ret = 0;

ERROR:
    av_aes_ctr_free(ae);
    av_aes_ctr_free(ad);
    वापस ret;
}
