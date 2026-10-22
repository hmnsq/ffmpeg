/*
 * Direct3D 12 HW acceleration.
 *
 * copyright (c) 2022-2023 Wu Jianhua <toqsxw@outlook.com>
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

#که_نه_تعریف_شوی AVUTIL_HWCONTEXT_D3_D12_VA_دننی_H
#تعریف_کړه AVUTIL_HWCONTEXT_D3_D12_VA_دننی_H

/**
 * @def COBJMACROS
 *
 * @brief Enable C style interface for D3D12
 */
#که_نه_تعریف_شوی COBJMACROS
#تعریف_کړه COBJMACROS
#د_که_پای

/**
 * @def DX_CHECK
 *
 * @brief A check macro used by D3D12 functions highly frequently
 */
#تعریف_کړه DX_CHECK(hr)                              \
    افعل {                                          \
        إذا (FAILED(hr))                           \
            اذهب fail;                            \
    } طالما (0)

/**
 * @def D3D12_OBJECT_RELEASE
 *
 * @brief A release macro used by D3D12 objects highly frequently
 */
#تعریف_کړه D3D12_OBJECT_RELEASE(pInterface)              \
    افعل {                                              \
        إذا (pInterface) {                             \
            IUnknown_Release((IUnknown *)pInterface); \
            pInterface = عدم;                        \
        }                                             \
    } طالما (0)

#د_که_پای /* AVUTIL_HWCONTEXT_D3D12VA_INTERNAL_H */
