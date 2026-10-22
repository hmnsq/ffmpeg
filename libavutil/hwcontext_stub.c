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

#అన్తర్భావ "config.h"

#ఒకవేళ !CONFIG_VULKAN
#అన్తర్భావ <stddef.h>
#అన్తర్భావ "pixfmt.h"

రకనిర్వచనం గణన VkFormat VkFormat;
రకనిర్వచనం నిర్మాణం AVVk_చట్రం AVVk_చట్రం;
స్థిరరాశి VkFormat *av_vkfmt_from_pixfmt(గణన AVPixelFormat p);
AVVk_చట్రం *av_vk_చట్రం_alloc(శూన్య);

స్థిరరాశి VkFormat *av_vkfmt_from_pixfmt(గణన AVPixelFormat p)
{
    తిరిగి ఖాళీ;
}

AVVk_చట్రం *av_vk_చట్రం_alloc(శూన్య)
{
    తిరిగి ఖాళీ;
}
#అయితే_ముగింపు /* CONFIG_VULKAN */
