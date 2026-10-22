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

#അന്തര്ഭാവ "config.h"

#എങ്കിൽ !CONFIG_VULKAN
#അന്തര്ഭാവ <stddef.h>
#അന്തര്ഭാവ "pixfmt.h"

തരനിർവചനം എണ്ണൽ VkFormat VkFormat;
തരനിർവചനം ഘടന AVVkFrame AVVkFrame;
സ്ഥിരം VkFormat *av_vkfmt_from_pixfmt(എണ്ണൽ AVPixelFormat p);
AVVkFrame *av_vk_frame_alloc(ശൂന്യം);

സ്ഥിരം VkFormat *av_vkfmt_from_pixfmt(എണ്ണൽ AVPixelFormat p)
{
    തിരികെ ശൂന്യ;
}

AVVkFrame *av_vk_frame_alloc(ശൂന്യം)
{
    തിരികെ ശൂന്യ;
}
#endif /* CONFIG_VULKAN */
