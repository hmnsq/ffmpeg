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

#অন্তর্ভাৱ "config.h"

#যদি !CONFIG_VULKAN
#অন্তর্ভাৱ <stddef.h>
#অন্তর্ভাৱ "pixfmt.h"

প্রকারনির্দেশ গণনা VkFormat VkFormat;
প্রকারনির্দেশ সংরচনা AVVkFrame AVVkFrame;
ধ্রুৱ VkFormat *av_vkfmt_from_pixfmt(গণনা AVPixelFormat p);
AVVkFrame *av_vk_frame_alloc(শূন্য);

ধ্রুৱ VkFormat *av_vkfmt_from_pixfmt(গণনা AVPixelFormat p)
{
    ঘূৰাই রিক্ত;
}

AVVkFrame *av_vk_frame_alloc(শূন্য)
{
    ঘূৰাই রিক্ত;
}
#endif /* CONFIG_VULKAN */
