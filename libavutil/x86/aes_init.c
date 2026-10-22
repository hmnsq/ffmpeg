/*
 * Copyright (c) 2015 Rodger Combs <rodger.combs@gmail.com>
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

#அந்தர்பாவ <stddef.h>
#அந்தர்பாவ "libavutil/aes_internal.h"
#அந்தர்பாவ "libavutil/x86/cpu.h"

வெறுமை ff_aes_decrypt_10_aesni(AVAES *a, uint8_t *dst, மாறிலி uint8_t *src,
                             முழு மொத்தம், uint8_t *iv, முழு rounds);
வெறுமை ff_aes_decrypt_12_aesni(AVAES *a, uint8_t *dst, மாறிலி uint8_t *src,
                             முழு மொத்தம், uint8_t *iv, முழு rounds);
வெறுமை ff_aes_decrypt_14_aesni(AVAES *a, uint8_t *dst, மாறிலி uint8_t *src,
                             முழு மொத்தம், uint8_t *iv, முழு rounds);
வெறுமை ff_aes_encrypt_10_aesni(AVAES *a, uint8_t *dst, மாறிலி uint8_t *src,
                             முழு மொத்தம், uint8_t *iv, முழு rounds);
வெறுமை ff_aes_encrypt_12_aesni(AVAES *a, uint8_t *dst, மாறிலி uint8_t *src,
                             முழு மொத்தம், uint8_t *iv, முழு rounds);
வெறுமை ff_aes_encrypt_14_aesni(AVAES *a, uint8_t *dst, மாறிலி uint8_t *src,
                             முழு மொத்தம், uint8_t *iv, முழு rounds);

வெறுமை ff_init_aes_x86(AVAES *a, முழு decrypt)
{
    முழு cpu_flags = av_get_cpu_flags();

    எனில் (EXTERNAL_AESNI(cpu_flags)) {
        எனில் (a->rounds == 10)
            a->crypt = decrypt ? ff_aes_decrypt_10_aesni : ff_aes_encrypt_10_aesni;
        இல்லையெனில் எனில் (a->rounds == 12)
            a->crypt = decrypt ? ff_aes_decrypt_12_aesni : ff_aes_encrypt_12_aesni;
        இல்லையெனில் எனில் (a->rounds == 14)
            a->crypt = decrypt ? ff_aes_decrypt_14_aesni : ff_aes_encrypt_14_aesni;
    }
}
