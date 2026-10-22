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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਜੇ !CONFIG_VULKAN
#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "pixfmt.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ VkFormat VkFormat;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVVk_ਚੌਖਟਾ AVVk_ਚੌਖਟਾ;
ਅਚਲ VkFormat *av_vkfmt_from_pixfmt(ਗਿਣਤੀ AVPixelFormat p);
AVVk_ਚੌਖਟਾ *av_vk_ਚੌਖਟਾ_alloc(ਖਾਲੀ);

ਅਚਲ VkFormat *av_vkfmt_from_pixfmt(ਗਿਣਤੀ AVPixelFormat p)
{
    ਵਾਪਸ ਨਿਰਾ;
}

AVVk_ਚੌਖਟਾ *av_vk_ਚੌਖਟਾ_alloc(ਖਾਲੀ)
{
    ਵਾਪਸ ਨਿਰਾ;
}
#ਜੇ_ਅੰਤ /* CONFIG_VULKAN */
