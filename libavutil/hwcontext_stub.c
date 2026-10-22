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

#ಅನ್ತರ್ಭಾವ "config.h"

#ಯದಿ !CONFIG_VULKAN
#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ "pixfmt.h"

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ VkFormat VkFormat;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ AVVkFrame AVVkFrame;
ಧ್ರುವ VkFormat *av_vkfmt_from_pixfmt(ಗಣನಾ AVPixelFormat p);
AVVkFrame *av_vk_frame_alloc(ಶೂನ್ಯ);

ಧ್ರುವ VkFormat *av_vkfmt_from_pixfmt(ಗಣನಾ AVPixelFormat p)
{
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

AVVkFrame *av_vk_frame_alloc(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}
#endif /* CONFIG_VULKAN */
