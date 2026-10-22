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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_HWCONTEXT_D3_D12_VA_ਅੰਦਰੂਨੀ_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_HWCONTEXT_D3_D12_VA_ਅੰਦਰੂਨੀ_H

/**
 * @def COBJMACROS
 *
 * @brief Enable C style interface for D3D12
 */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ COBJMACROS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ COBJMACROS
#ਜੇ_ਅੰਤ

/**
 * @def DX_CHECK
 *
 * @brief A check macro used by D3D12 functions highly frequently
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DX_CHECK(hr)                              \
    ਕਰੋ {                                          \
        ਜੇ (FAILED(hr))                           \
            ਜਾਓ fail;                            \
    } ਜਦੋਂ (0)

/**
 * @def D3D12_OBJECT_RELEASE
 *
 * @brief A release macro used by D3D12 objects highly frequently
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ D3D12_OBJECT_RELEASE(pInterface)              \
    ਕਰੋ {                                              \
        ਜੇ (pInterface) {                             \
            IUnknown_Release((IUnknown *)pInterface); \
            pInterface = ਨਿਰਾ;                        \
        }                                             \
    } ਜਦੋਂ (0)

#ਜੇ_ਅੰਤ /* AVUTIL_HWCONTEXT_D3D12VA_INTERNAL_H */
