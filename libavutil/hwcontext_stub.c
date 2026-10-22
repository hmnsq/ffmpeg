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

#ಆದರೆ !CONFIG_VULKAN
#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ "pixfmt.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ VkFormat VkFormat;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVVk_ಚೌಕಟ್ಟು AVVk_ಚೌಕಟ್ಟು;
ಸ್ಥಿರಾಂಕ VkFormat *av_vkfmt_from_pixfmt(ಎಣಿಕೆ AVPixelFormat p);
AVVk_ಚೌಕಟ್ಟು *av_vk_ಚೌಕಟ್ಟು_alloc(ಶೂನ್ಯ);

ಸ್ಥಿರಾಂಕ VkFormat *av_vkfmt_from_pixfmt(ಎಣಿಕೆ AVPixelFormat p)
{
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

AVVk_ಚೌಕಟ್ಟು *av_vk_ಚೌಕಟ್ಟು_alloc(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}
#ಆದರೆ_ಅಂತ್ಯ /* CONFIG_VULKAN */
