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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_BASE64_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_BASE64_H

#ಅನ್ತರ್ಭಾವ <stdint.h>

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
ಪೂರ್ಣಾಂಕ av_base64_decode(uint8_t *ಹೊರಹೋಗು, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಒಳ, ಪೂರ್ಣಾಂಕ ಹೊರಹೋಗು_ಗಾತ್ರ);

/**
 * Calculate the output size in bytes needed to decode a base64 string
 * with length x to a data buffer.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_BASE64_DECODE_ಗಾತ್ರ(x) ((x) * 3LL / 4)

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
ಅಕ್ಷರ *av_base64_encode(ಅಕ್ಷರ *ಹೊರಹೋಗು, ಪೂರ್ಣಾಂಕ ಹೊರಹೋಗು_ಗಾತ್ರ, ಸ್ಥಿರಾಂಕ uint8_t *ಒಳ, ಪೂರ್ಣಾಂಕ ಒಳ_ಗಾತ್ರ);

/**
 * Calculate the output size needed to base64-encode x bytes to a
 * null-terminated string.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_BASE64_ಗಾತ್ರ(x)  (((x)+2) / 3 * 4 + 1)

 /**
  * @}
  */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_BASE64_H */
