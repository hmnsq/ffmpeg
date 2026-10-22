/*
 * Copyright (c) 2006 Ryan Martell. (rdm4@martellventures.com)
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

#यदि_अपरिभाषितम् AVUTIL_BASE64_H
#परिभाषय AVUTIL_BASE64_H

#अन्तर्भाव <stdint.h>

/**
 * @defgroup lavu_base64 Base64
 * @ingroup lavu_crypto
 * @{
 */

/**
 * Decode a base64-encoded string.
 *
 * @param out      buffer for decoded data
 * @param in       null-terminated input string
 * @param out_size size in bytes of the out buffer, must be at
 *                 least 3/4 of the length of in, that is AV_BASE64_DECODE_SIZE(strlen(in))
 * @return         number of bytes written, or a negative value in case of
 *                 invalid input
 */
पूर्णाङ्क av_base64_decode(uint8_t *बहिर्गमनम्, ध्रुव वर्ण *अन्तर्, पूर्णाङ्क बहिर्गमनम्_आकार);

/**
 * Calculate the output size in bytes needed to decode a base64 string
 * with length x to a data buffer.
 */
#परिभाषय AV_BASE64_DECODE_आकार(x) ((x) * 3LL / 4)

/**
 * Encode data to base64 and null-terminate.
 *
 * @param out      buffer for encoded data
 * @param out_size size in bytes of the out buffer (including the
 *                 null terminator), must be at least AV_BASE64_SIZE(in_size)
 * @param in       input buffer containing the data to encode
 * @param in_size  size in bytes of the in buffer
 * @return         out or NULL in case of error
 */
वर्ण *av_base64_encode(वर्ण *बहिर्गमनम्, पूर्णाङ्क बहिर्गमनम्_आकार, ध्रुव uint8_t *अन्तर्, पूर्णाङ्क अन्तर्_आकार);

/**
 * Calculate the output size needed to base64-encode x bytes to a
 * null-terminated string.
 */
#परिभाषय AV_BASE64_आकार(x)  (((x)+2) / 3 * 4 + 1)

 /**
  * @}
  */

#यदि_अन्तः /* AVUTIL_BASE64_H */
