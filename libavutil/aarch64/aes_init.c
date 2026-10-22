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

#অন্তর্ভাৱ <stddef.h>
#অন্তর্ভাৱ "libavutil/aes_internal.h"
#অন্তর্ভাৱ "libavutil/aarch64/cpu.h"

শূন্য ff_aes_decrypt_10_neon(AVAES *a, uint8_t *dst, ধ্রুৱ uint8_t *src,
                            পূর্ণাঙ্ক গুনতি, uint8_t *iv, পূর্ণাঙ্ক rounds);
শূন্য ff_aes_decrypt_12_neon(AVAES *a, uint8_t *dst, ধ্রুৱ uint8_t *src,
                            পূর্ণাঙ্ক গুনতি, uint8_t *iv, পূর্ণাঙ্ক rounds);
শূন্য ff_aes_decrypt_14_neon(AVAES *a, uint8_t *dst, ধ্রুৱ uint8_t *src,
                            পূর্ণাঙ্ক গুনতি, uint8_t *iv, পূর্ণাঙ্ক rounds);
শূন্য ff_aes_encrypt_10_neon(AVAES *a, uint8_t *dst, ধ্রুৱ uint8_t *src,
                            পূর্ণাঙ্ক গুনতি, uint8_t *iv, পূর্ণাঙ্ক rounds);
শূন্য ff_aes_encrypt_12_neon(AVAES *a, uint8_t *dst, ধ্রুৱ uint8_t *src,
                            পূর্ণাঙ্ক গুনতি, uint8_t *iv, পূর্ণাঙ্ক rounds);
শূন্য ff_aes_encrypt_14_neon(AVAES *a, uint8_t *dst, ধ্রুৱ uint8_t *src,
                            পূর্ণাঙ্ক গুনতি, uint8_t *iv, পূর্ণাঙ্ক rounds);

শূন্য ff_init_aes_aarch64(AVAES *a, পূর্ণাঙ্ক decrypt)
{
    পূর্ণাঙ্ক cpu_flags = av_get_cpu_flags();

    যদি (have_arm_aes(cpu_flags)) {
        যদি (a->rounds == 10)
            a->crypt = decrypt ? ff_aes_decrypt_10_neon : ff_aes_encrypt_10_neon;
        অন্যথা যদি (a->rounds == 12)
            a->crypt = decrypt ? ff_aes_decrypt_12_neon : ff_aes_encrypt_12_neon;
        অন্যথা যদি (a->rounds == 14)
            a->crypt = decrypt ? ff_aes_decrypt_14_neon : ff_aes_encrypt_14_neon;
    }
}
