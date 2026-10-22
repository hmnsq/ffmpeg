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

#অন্তর্ভাব <string.h>

#অন্তর্ভাব "libavutil/random_seed.h"
#অন্তর্ভাব "libavutil/lfg.h"
#অন্তর্ভাব "libavutil/log.h"
#অন্তর্ভাব "libavutil/mem_internal.h"
#অন্তর্ভাব "libavutil/aes_ctr.h"

স্থির ধ্রুব DECLARE_ALIGNED(8, uint8_t, plain)[] = {
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f,
    0x6d, 0x6f, 0x73, 0x74, 0x20, 0x72, 0x61, 0x6e, 0x64, 0x6f
};

স্থির ধ্রুব DECLARE_ALIGNED(8, uint8_t, encrypted)[] = {
    0x95, 0xcd, 0x9a, 0x8a, 0x83, 0xa2, 0x1a, 0x84, 0x92, 0xed,
    0xd6, 0xf2, 0x57, 0x2f, 0x61, 0x98, 0xbc, 0x20, 0x98, 0xee,
    0x6c, 0xed, 0x53, 0xae, 0x2f, 0xc4, 0x18, 0x7c, 0xeb, 0x62,
    0xbb, 0x3a, 0x71, 0x24, 0x22, 0x8c, 0xd9, 0xfa, 0xee, 0x10
};

স্থির ধ্রুব DECLARE_ALIGNED(8, uint8_t, fixed_iv)[] = {
    0xde, 0xad, 0xbe, 0xef, 0xde, 0xad, 0xbe, 0xef
};

স্থির ধ্রুব DECLARE_ALIGNED(8, uint8_t, fixed_চাবি)[] = {
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66
};

স্থির DECLARE_ALIGNED(8, uint32_t, চাবি)[4];

স্থির DECLARE_ALIGNED(8, uint8_t, tmp)[40];

পূর্ণাঙ্ক main (শূন্য)
{
    পূর্ণাঙ্ক ret = 1;
    AVLFG lfg;
    সংরচনা AVAESCTR *ae, *ad;
    ধ্রুব uint8_t *iv, *k;

    av_lfg_init(&lfg, av_get_random_seed());

    প্রতি (পূর্ণাঙ্ক i = 0; i < 2; i++) {
        ae = av_aes_ctr_alloc();
        ad = av_aes_ctr_alloc();

        যদি (!ae || !ad)
            গচ্ছ ERROR;

        যদি (i)
            k = fixed_চাবি;
        অন্যথা {
            // Note: av_random_bytes() should be used in a real world scenario,
            // but since that function can fail, av_get_random_seed() is used
            // here for the purpose of this test, as its output is sufficient.
            চাবি[0] = av_get_random_seed();
            চাবি[1] = av_get_random_seed();
            চাবি[2] = av_get_random_seed();
            চাবি[3] = av_get_random_seed();
            k = (uint8_t *)চাবি;
        }

        যদি (av_aes_ctr_init(ae, k) < 0)
            গচ্ছ ERROR;

        যদি (av_aes_ctr_init(ad, k) < 0)
            গচ্ছ ERROR;

        যদি (i)
            av_aes_ctr_set_iv(ae, fixed_iv);
        অন্যথা
            av_aes_ctr_set_random_iv(ae);
        iv =   av_aes_ctr_get_iv(ae);
        av_aes_ctr_set_full_iv(ad, iv);

        uint8_t *dst = tmp;
        ধ্রুব uint8_t *src = plain;
        পূর্ণাঙ্ক বাম = পরিমাণ(plain);
        যাবত্ (বাম > 0) {
            পূর্ণাঙ্ক গুনতি = (av_lfg_get(&lfg) % বাম) + 1;
            av_aes_ctr_crypt(ae, dst, src, গুনতি);
            dst += গুনতি;
            src += গুনতি;
            বাম -= গুনতি;
        }
        যদি (i && memcmp(tmp, encrypted, পরিমাণ(tmp)) != 0) {
            av_log(রিক্ত, AV_LOG_ERROR, "test failed\n");
            গচ্ছ ERROR;
        }

        dst = tmp;
        বাম = পরিমাণ(plain);
        যাবত্ (বাম > 0) {
            পূর্ণাঙ্ক গুনতি = (av_lfg_get(&lfg) % বাম) + 1;
            av_aes_ctr_crypt(ad, dst, dst, গুনতি);
            dst += গুনতি;
            বাম -= গুনতি;
        }

        যদি (memcmp(tmp, plain, পরিমাণ(tmp)) != 0){
            av_log(রিক্ত, AV_LOG_ERROR, "test failed\n");
            গচ্ছ ERROR;
        }

        av_aes_ctr_free(ae);
        av_aes_ctr_free(ad);
        ae = ad = রিক্ত;
    }

    av_log(রিক্ত, AV_LOG_INFO, "test passed\n");
    ret = 0;

ERROR:
    av_aes_ctr_free(ae);
    av_aes_ctr_free(ad);
    প্রত্যাগম ret;
}
