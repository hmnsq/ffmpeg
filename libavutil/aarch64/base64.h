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

#ifndef AVUTIL_AARCH64_BASE64_H
#define AVUTIL_AARCH64_BASE64_H

#অন্তর্ভাব <stdint.h>

বর্ণ *ff_base64_encode_neon(বর্ণ *out, ধ্রুব uint8_t *in, পূর্ণাঙ্ক in_size, ধ্রুব বর্ণ *tbl);

#endif /* AVUTIL_AARCH64_BASE64_H */
