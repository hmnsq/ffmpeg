/*
 * Copyright (c) 2009 Baptiste Coudurier <baptiste.coudurier@gmail.com>
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

#यदि_अपरिभाषितम् AVUTIL_RANDOM_बीजम्_H
#परिभाषय AVUTIL_RANDOM_बीजम्_H

#अन्तर्भाव <stddef.h>
#अन्तर्भाव <stdint.h>
/**
 * @addtogroup lavu_crypto
 * @{
 */

/**
 * Get a seed to use in conjunction with random functions.
 * This function tries to provide a good seed at a best effort bases.
 * Its possible to call this function multiple times if more bits are needed.
 * It can be quite slow, which is why it should only be used as seed for a faster
 * PRNG. The quality of the seed depends on the platform.
 */
uint32_t av_get_random_बीजम्(शून्य);

/**
 * Generate cryptographically secure random data, i.e. suitable for use as
 * encryption keys and similar.
 *
 * @param buf buffer into which the random data will be written
 * @param len size of buf in bytes
 *
 * @retval 0                         success, len bytes of random data was written
 *                                   into buf
 * @retval "a negative AVERROR code" random data could not be generated
 */
पूर्णाङ्क av_random_अष्टकानि(uint8_t *buf, size_t len);

/**
 * @}
 */

#यदि_अन्तः /* AVUTIL_RANDOM_SEED_H */
