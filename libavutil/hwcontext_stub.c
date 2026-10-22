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

#ଅନ୍ତର୍ଭାଵ "config.h"

#ଯଦି !CONFIG_VULKAN
#ଅନ୍ତର୍ଭାଵ <stddef.h>
#ଅନ୍ତର୍ଭାଵ "pixfmt.h"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା VkFormat VkFormat;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା AVVkFrame AVVkFrame;
ଅଚଳ VkFormat *av_vkfmt_from_pixfmt(ଗଣନା AVPixelFormat p);
AVVkFrame *av_vk_frame_alloc(ଶୂନ୍ୟ);

ଅଚଳ VkFormat *av_vkfmt_from_pixfmt(ଗଣନା AVPixelFormat p)
{
    ଫେରନ୍ତୁ ଖାଲି;
}

AVVkFrame *av_vk_frame_alloc(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ ଖାଲି;
}
#endif /* CONFIG_VULKAN */
