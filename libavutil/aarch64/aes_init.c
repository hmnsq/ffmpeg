/*
 * Copyright (c) 2026 Shreesh Adiga <16567adigashreesh@gmail.com>
 *
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

#ଅନ୍ତର୍ଭାଵ <stddef.h>
#ଅନ୍ତର୍ଭାଵ "libavutil/aes_internal.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/aarch64/cpu.h"

ଶୂନ୍ୟ ff_aes_decrypt_10_neon(AVAES *a, uint8_t *dst, ଅଚଳ uint8_t *src,
                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2, uint8_t *iv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା rounds);
ଶୂନ୍ୟ ff_aes_decrypt_12_neon(AVAES *a, uint8_t *dst, ଅଚଳ uint8_t *src,
                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2, uint8_t *iv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା rounds);
ଶୂନ୍ୟ ff_aes_decrypt_14_neon(AVAES *a, uint8_t *dst, ଅଚଳ uint8_t *src,
                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2, uint8_t *iv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା rounds);
ଶୂନ୍ୟ ff_aes_encrypt_10_neon(AVAES *a, uint8_t *dst, ଅଚଳ uint8_t *src,
                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2, uint8_t *iv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା rounds);
ଶୂନ୍ୟ ff_aes_encrypt_12_neon(AVAES *a, uint8_t *dst, ଅଚଳ uint8_t *src,
                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2, uint8_t *iv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା rounds);
ଶୂନ୍ୟ ff_aes_encrypt_14_neon(AVAES *a, uint8_t *dst, ଅଚଳ uint8_t *src,
                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2, uint8_t *iv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା rounds);

ଶୂନ୍ୟ ff_init_aes_aarch64(AVAES *a, ପୂର୍ଣ୍ଣସଂଖ୍ୟା decrypt)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpu_flags = av_get_cpu_flags();

    ଯଦି (have_arm_aes(cpu_flags)) {
        ଯଦି (a->rounds == 10)
            a->crypt = decrypt ? ff_aes_decrypt_10_neon : ff_aes_encrypt_10_neon;
        ଅନ୍ୟଥା ଯଦି (a->rounds == 12)
            a->crypt = decrypt ? ff_aes_decrypt_12_neon : ff_aes_encrypt_12_neon;
        ଅନ୍ୟଥା ଯଦି (a->rounds == 14)
            a->crypt = decrypt ? ff_aes_decrypt_14_neon : ff_aes_encrypt_14_neon;
    }
}
