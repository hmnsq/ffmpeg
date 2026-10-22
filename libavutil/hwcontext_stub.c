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

#समावेश "config.h"

#अगर !CONFIG_VULKAN
#समावेश <stddef.h>
#समावेश "pixfmt.h"

प्रकार क्रमागत VkFormat VkFormat;
प्रकार काष्ठा AVVkFrame AVVkFrame;
स्थिर VkFormat *av_vkfmt_from_pixfmt(क्रमागत AVPixelFormat p);
AVVkFrame *av_vk_frame_alloc(व्योम);

स्थिर VkFormat *av_vkfmt_from_pixfmt(क्रमागत AVPixelFormat p)
{
    वापस शून्य;
}

AVVkFrame *av_vk_frame_alloc(व्योम)
{
    वापस शून्य;
}
#पूर्ण_अगर /* CONFIG_VULKAN */
