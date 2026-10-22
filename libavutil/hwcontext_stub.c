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

#ضمن "config.h"

#إذا !CONFIG_VULKAN
#ضمن <stddef.h>
#ضمن "pixfmt.h"

تعريفنوع تعداد VkFormat VkFormat;
تعريفنوع بنية AVVk_چوکھٹا AVVk_چوکھٹا;
ثابت VkFormat *av_vkfmt_from_pixfmt(تعداد AVPixelFormat p);
AVVk_چوکھٹا *av_vk_چوکھٹا_alloc(فراغ);

ثابت VkFormat *av_vkfmt_from_pixfmt(تعداد AVPixelFormat p)
{
    أرجع عدم;
}

AVVk_چوکھٹا *av_vk_چوکھٹا_alloc(فراغ)
{
    أرجع عدم;
}
#جے_انت /* CONFIG_VULKAN */
