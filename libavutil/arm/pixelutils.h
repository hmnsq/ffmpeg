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

#ifndef AVUTIL_ARM_PIXELUTILS_H
#define AVUTIL_ARM_PIXELUTILS_H

#അന്തര്ഭാവ <stddef.h>
#അന്തര്ഭാവ <stdint.h>

#അന്തര്ഭാവ "cpu.h"
#അന്തര്ഭാവ "libavutil/attributes.h"
#അന്തര്ഭാവ "libavutil/cpu.h"
#അന്തര്ഭാവ "libavutil/pixelutils.h"

പൂർണ്ണസംഖ്യ ff_pixelutils_sad16_armv6(സ്ഥിരം uint8_t *src1, ptrdiff_t stride1,
                              സ്ഥിരം uint8_t *src2, ptrdiff_t stride2);
പൂർണ്ണസംഖ്യ ff_pixelutils_sad8_armv6 (സ്ഥിരം uint8_t *src1, ptrdiff_t stride1,
                              സ്ഥിരം uint8_t *src2, ptrdiff_t stride2);

സ്ഥിതം വരിയിൽ av_cold ശൂന്യം ff_pixelutils_sad_init_arm(av_pixelutils_sad_fn *sad, പൂർണ്ണസംഖ്യ aligned)
{
    പൂർണ്ണസംഖ്യ cpu_flags = av_get_cpu_flags();

    എങ്കിൽ (have_armv6(cpu_flags)) {
        എങ്കിൽ (aligned != 0) {
            sad[2] = ff_pixelutils_sad8_armv6;
            sad[3] = ff_pixelutils_sad16_armv6;
        }
    }
}
#endif
