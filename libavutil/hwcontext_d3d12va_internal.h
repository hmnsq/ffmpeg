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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_HWCONTEXT_D3_D12_VA_ಆಂತರಿಕ_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_HWCONTEXT_D3_D12_VA_ಆಂತರಿಕ_H

/**
 * @def COBJMACROS
 *
 * @brief Enable C style interface for D3D12
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ COBJMACROS
#ವ್ಯಾಖ್ಯಾನಿಸು COBJMACROS
#ಆದರೆ_ಅಂತ್ಯ

/**
 * @def DX_CHECK
 *
 * @brief A check macro used by D3D12 functions highly frequently
 */
#ವ್ಯಾಖ್ಯಾನಿಸು DX_CHECK(hr)                              \
    ಮಾಡು {                                          \
        ಆದರೆ (FAILED(hr))                           \
            ಹೋಗು fail;                            \
    } ಆಗ (0)

/**
 * @def D3D12_OBJECT_RELEASE
 *
 * @brief A release macro used by D3D12 objects highly frequently
 */
#ವ್ಯಾಖ್ಯಾನಿಸು D3D12_OBJECT_RELEASE(pInterface)              \
    ಮಾಡು {                                              \
        ಆದರೆ (pInterface) {                             \
            IUnknown_Release((IUnknown *)pInterface); \
            pInterface = ಖಾಲಿ;                        \
        }                                             \
    } ಆಗ (0)

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_HWCONTEXT_D3D12VA_INTERNAL_H */
