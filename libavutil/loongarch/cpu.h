/*
 * Copyright (c) 2020 Loongson Technology Corporation Limited
 * Contributed by Shiyou Yin <yinshiyou-hf@loongson.cn>
 *
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

#اگر_تعریف_نشده AVUTIL_LOONGARCH_CPU_H
#تعریف_کن AVUTIL_LOONGARCH_CPU_H

#ضمن "libavutil/cpu.h"
#ضمن "libavutil/cpu_internal.h"

#تعریف_کن have_lsx(flags) CPUEXT(flags, LSX)
#تعریف_کن have_lasx(flags) CPUEXT(flags, LASX)

#پایان_اگر /* AVUTIL_LOONGARCH_CPU_H */
