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

#شامل "config.h"

#اگر !CONFIG_VULKAN
#شامل <stddef.h>
#شامل "pixfmt.h"

قسمتعریف شمار VkFormat VkFormat;
قسمتعریف ساخت AVVk_چوکھٹا AVVk_چوکھٹا;
ثابت VkFormat *av_vkfmt_from_pixfmt(شمار AVPixelFormat p);
AVVk_چوکھٹا *av_vk_چوکھٹا_alloc(خالی);

ثابت VkFormat *av_vkfmt_from_pixfmt(شمار AVPixelFormat p)
{
    واپس تہی;
}

AVVk_چوکھٹا *av_vk_چوکھٹا_alloc(خالی)
{
    واپس تہی;
}
#اگر_ختم /* CONFIG_VULKAN */
