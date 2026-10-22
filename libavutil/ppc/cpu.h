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

#جے_بنا_تعریف AVUTIL_PPC_CPU_H
#تعریف_کرو AVUTIL_PPC_CPU_H

#ضمن "libavutil/cpu.h"
#ضمن "libavutil/cpu_internal.h"

#تعریف_کرو PPC_ALTIVEC(flags) CPUEXT(flags, ALTIVEC)
#تعریف_کرو PPC_VSX(flags) CPUEXT(flags, VSX)
#تعریف_کرو PPC_POWER8(flags) CPUEXT(flags, POWER8)

#جے_انت /* AVUTIL_PPC_CPU_H */
