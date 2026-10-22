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

#ضمن <stddef.h>
#ضمن "libavutil/aes_internal.h"
#ضمن "libavutil/aarch64/cpu.h"

فراغ ff_aes_decrypt_10_neon(AVAES *a, uint8_t *dst, ثابت uint8_t *src,
                            صحيح تعداد_2, uint8_t *iv, صحيح rounds);
فراغ ff_aes_decrypt_12_neon(AVAES *a, uint8_t *dst, ثابت uint8_t *src,
                            صحيح تعداد_2, uint8_t *iv, صحيح rounds);
فراغ ff_aes_decrypt_14_neon(AVAES *a, uint8_t *dst, ثابت uint8_t *src,
                            صحيح تعداد_2, uint8_t *iv, صحيح rounds);
فراغ ff_aes_encrypt_10_neon(AVAES *a, uint8_t *dst, ثابت uint8_t *src,
                            صحيح تعداد_2, uint8_t *iv, صحيح rounds);
فراغ ff_aes_encrypt_12_neon(AVAES *a, uint8_t *dst, ثابت uint8_t *src,
                            صحيح تعداد_2, uint8_t *iv, صحيح rounds);
فراغ ff_aes_encrypt_14_neon(AVAES *a, uint8_t *dst, ثابت uint8_t *src,
                            صحيح تعداد_2, uint8_t *iv, صحيح rounds);

فراغ ff_init_aes_aarch64(AVAES *a, صحيح decrypt)
{
    صحيح cpu_flags = av_get_cpu_flags();

    إذا (have_arm_aes(cpu_flags)) {
        إذا (a->rounds == 10)
            a->crypt = decrypt ? ff_aes_decrypt_10_neon : ff_aes_encrypt_10_neon;
        وإلا إذا (a->rounds == 12)
            a->crypt = decrypt ? ff_aes_decrypt_12_neon : ff_aes_encrypt_12_neon;
        وإلا إذا (a->rounds == 14)
            a->crypt = decrypt ? ff_aes_decrypt_14_neon : ff_aes_encrypt_14_neon;
    }
}
