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

#अन्तर्भाव "config.h"

#यदि !CONFIG_VULKAN
#अन्तर्भाव <stddef.h>
#अन्तर्भाव "pixfmt.h"

प्रकारनिर्देश गणना VkFormat VkFormat;
प्रकारनिर्देश संरचना AVVkFrame AVVkFrame;
ध्रुव VkFormat *av_vkfmt_from_pixfmt(गणना AVPixelFormat p);
AVVkFrame *av_vk_frame_alloc(शून्य);

ध्रुव VkFormat *av_vkfmt_from_pixfmt(गणना AVPixelFormat p)
{
    प्रत्यागम रिक्त;
}

AVVkFrame *av_vk_frame_alloc(शून्य)
{
    प्रत्यागम रिक्त;
}
#endif /* CONFIG_VULKAN */
