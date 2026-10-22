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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_WCHAR_FILENAME_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_WCHAR_FILENAME_H

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32

#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <windows.h>
#ಅನ್ತರ್ಭಾವ "mem.h"

av_warn_ಬಳಸದ_ಫಲಿತಾಂಶ
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ utf8towchar(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *filename_utf8, wchar_t **filename_w)
{
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_chars;
    ಅಂಕೆ_chars = Multi_Byte_ಗಮ್ಯ_Wide_Char(CP_UTF8, MB_ERR_INVALID_CHARS, filename_utf8, -1, ಖಾಲಿ, 0);
    ಆದರೆ (ಅಂಕೆ_chars <= 0) {
        *filename_w = ಖಾಲಿ;
        errno = EINVAL;
        ಹಿಂತಿರುಗಿ -1;
    }
    *filename_w = (wchar_t *)av_calloc(ಅಂಕೆ_chars, ಗಾತ್ರ(wchar_t));
    ಆದರೆ (!*filename_w) {
        errno = ENOMEM;
        ಹಿಂತಿರುಗಿ -1;
    }
    Multi_Byte_ಗಮ್ಯ_Wide_Char(CP_UTF8, 0, filename_utf8, -1, *filename_w, ಅಂಕೆ_chars);
    ಹಿಂತಿರುಗಿ 0;
}

av_warn_ಬಳಸದ_ಫಲಿತಾಂಶ
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ wchartocp(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಸಂಕೇತ_ಪುಟ, ಸ್ಥಿರಾಂಕ wchar_t *filename_w,
                            ಅಕ್ಷರ **filename)
{
    DWORD flags = ಸಂಕೇತ_ಪುಟ == CP_UTF8 ? WC_ERR_INVALID_CHARS : 0;
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_chars = Wide_Char_ಗಮ್ಯ_Multi_Byte(ಸಂಕೇತ_ಪುಟ, flags, filename_w, -1,
                                        ಖಾಲಿ, 0, ಖಾಲಿ, ಖಾಲಿ);
    ಆದರೆ (ಅಂಕೆ_chars <= 0) {
        *filename = ಖಾಲಿ;
        errno = EINVAL;
        ಹಿಂತಿರುಗಿ -1;
    }
    *filename = (ಅಕ್ಷರ *)av_malloc_array(ಅಂಕೆ_chars, ಗಾತ್ರ **filename);
    ಆದರೆ (!*filename) {
        errno = ENOMEM;
        ಹಿಂತಿರುಗಿ -1;
    }
    Wide_Char_ಗಮ್ಯ_Multi_Byte(ಸಂಕೇತ_ಪುಟ, flags, filename_w, -1,
                        *filename, ಅಂಕೆ_chars, ಖಾಲಿ, ಖಾಲಿ);
    ಹಿಂತಿರುಗಿ 0;
}

av_warn_ಬಳಸದ_ಫಲಿತಾಂಶ
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ wchartoutf8(ಸ್ಥಿರಾಂಕ wchar_t *filename_w, ಅಕ್ಷರ **filename)
{
    ಹಿಂತಿರುಗಿ wchartocp(CP_UTF8, filename_w, filename);
}

av_warn_ಬಳಸದ_ಫಲಿತಾಂಶ
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ wchartoansi(ಸ್ಥಿರಾಂಕ wchar_t *filename_w, ಅಕ್ಷರ **filename)
{
    ಹಿಂತಿರುಗಿ wchartocp(CP_ACP, filename_w, filename);
}

av_warn_ಬಳಸದ_ಫಲಿತಾಂಶ
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ utf8toansi(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *filename_utf8, ಅಕ್ಷರ **filename)
{
    wchar_t *filename_w = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ ret = -1;
    ಆದರೆ (utf8towchar(filename_utf8, &filename_w))
        ಹಿಂತಿರುಗಿ -1;

    ಆದರೆ (!filename_w) {
        *filename = ಖಾಲಿ;
        ಹಿಂತಿರುಗಿ 0;
    }

    ret = wchartoansi(filename_w, filename);
    av_free(filename_w);
    ಹಿಂತಿರುಗಿ ret;
}

/**
 * Checks for extended path prefixes for which normalization needs to be skipped.
 * see .NET6: PathInternal.IsExtended()
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L165
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ಮಾರ್ಗ_is_extended(ಸ್ಥಿರಾಂಕ wchar_t *ಮಾರ್ಗ)
{
    ಆದರೆ (ಮಾರ್ಗ[0] == L'\\' && (ಮಾರ್ಗ[1] == L'\\' || ಮಾರ್ಗ[1] == L'?') && ಮಾರ್ಗ[2] == L'?' && ಮಾರ್ಗ[3] == L'\\')
        ಹಿಂತಿರುಗಿ 1;

    ಹಿಂತಿರುಗಿ 0;
}

/**
 * Checks for a device path prefix.
 * see .NET6: PathInternal.IsDevice()
 * we don't check forward slashes and extended paths (as already done)
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L132
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ಮಾರ್ಗ_is_device_ಮಾರ್ಗ(ಸ್ಥಿರಾಂಕ wchar_t *ಮಾರ್ಗ)
{
    ಆದರೆ (ಮಾರ್ಗ[0] == L'\\' && ಮಾರ್ಗ[1] == L'\\' && ಮಾರ್ಗ[2] == L'.' && ಮಾರ್ಗ[3] == L'\\')
        ಹಿಂತಿರುಗಿ 1;

    ಹಿಂತಿರುಗಿ 0;
}

/**
 * Performs path normalization by calling GetFullPathNameW().
 * see .NET6: PathHelper.GetFullPathName()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L70
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ get_ತುಂಬಿದ_ಮಾರ್ಗ_name(wchar_t **ppath_w)
{
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_chars;
    wchar_t *ತಾತ್ಕಾಲಿಕ_w;

    ಅಂಕೆ_chars = Get_ತುಂಬಿದ_ಮಾರ್ಗ_Name_W(*ppath_w, 0, ಖಾಲಿ, ಖಾಲಿ);
    ಆದರೆ (ಅಂಕೆ_chars <= 0) {
        errno = EINVAL;
        ಹಿಂತಿರುಗಿ -1;
    }

    ತಾತ್ಕಾಲಿಕ_w = (wchar_t *)av_calloc(ಅಂಕೆ_chars, ಗಾತ್ರ(wchar_t));
    ಆದರೆ (!ತಾತ್ಕಾಲಿಕ_w) {
        errno = ENOMEM;
        ಹಿಂತಿರುಗಿ -1;
    }

    ಅಂಕೆ_chars = Get_ತುಂಬಿದ_ಮಾರ್ಗ_Name_W(*ppath_w, ಅಂಕೆ_chars, ತಾತ್ಕಾಲಿಕ_w, ಖಾಲಿ);
    ಆದರೆ (ಅಂಕೆ_chars <= 0) {
        av_free(ತಾತ್ಕಾಲಿಕ_w);
        errno = EINVAL;
        ಹಿಂತಿರುಗಿ -1;
    }

    av_freep(ppath_w);
    *ppath_w = ತಾತ್ಕಾಲಿಕ_w;

    ಹಿಂತಿರುಗಿ 0;
}

/**
 * Normalizes a Windows file or folder path.
 * Expansion of short paths (with 8.3 path components) is currently omitted
 * as it is not required for accessing long paths.
 * see .NET6: PathHelper.Normalize()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L25
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ಮಾರ್ಗ_normalize(wchar_t **ppath_w)
{
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ ((ret = get_ತುಂಬಿದ_ಮಾರ್ಗ_name(ppath_w)) < 0)
        ಹಿಂತಿರುಗಿ ret;

    /* What .NET does at this point is to call PathHelper.TryExpandShortFileName()
     * in case the path contains a '~' character.
     * We don't need to do this as we don't need to normalize the file name
     * for presentation, and the extended path prefix works with 8.3 path
     * components as well
     */
    ಹಿಂತಿರುಗಿ 0;
}

/**
 * Adds an extended path or UNC prefix to longs paths or paths ending
 * with a space or a dot. (' ' or '.').
 * This function expects that the path has been normalized before by
 * calling path_normalize() and it doesn't check whether the path is
 * actually long (> MAX_PATH).
 * see .NET6: PathInternal.EnsureExtendedPrefix()
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L107
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ಕೂಡಿಸು_extended_ಪೂರ್ವಪ್ರತ್ಯಯ(wchar_t **ppath_w)
{
    ಸ್ಥಿರಾಂಕ wchar_t *unc_ಪೂರ್ವಪ್ರತ್ಯಯ           = L"\\\\?\\UNC\\";
    ಸ್ಥಿರಾಂಕ wchar_t *extended_ಮಾರ್ಗ_ಪೂರ್ವಪ್ರತ್ಯಯ = L"\\\\?\\";
    ಸ್ಥಿರಾಂಕ wchar_t *ಮಾರ್ಗ_w               = *ppath_w;
    ಸ್ಥಿರಾಂಕ size_t len                    = wcslen(ಮಾರ್ಗ_w);
    wchar_t *ತಾತ್ಕಾಲಿಕ_w;

    /* We're skipping the check IsPartiallyQualified() because
     * we expect to have called GetFullPathNameW() already. */
    ಆದರೆ (len < 2 || ಮಾರ್ಗ_is_extended(*ppath_w) || ಮಾರ್ಗ_is_device_ಮಾರ್ಗ(*ppath_w)) {
        ಹಿಂತಿರುಗಿ 0;
    }

    ಆದರೆ (ಮಾರ್ಗ_w[0] == L'\\' && ಮಾರ್ಗ_w[1] == L'\\') {
        /* unc_prefix length is 8 plus 1 for terminating zeros,
         * we subtract 2 for the leading '\\' of the original path */
        ತಾತ್ಕಾಲಿಕ_w = (wchar_t *)av_calloc(len - 2 + 8 + 1, ಗಾತ್ರ(wchar_t));
        ಆದರೆ (!ತಾತ್ಕಾಲಿಕ_w) {
            errno = ENOMEM;
            ಹಿಂತಿರುಗಿ -1;
        }
        wcscpy(ತಾತ್ಕಾಲಿಕ_w, unc_ಪೂರ್ವಪ್ರತ್ಯಯ);
        wcscat(ತಾತ್ಕಾಲಿಕ_w, ಮಾರ್ಗ_w + 2);
    } ಇಲ್ಲದಿದ್ದರೆ {
        // The length of extended_path_prefix is 4 plus 1 for terminating zeros
        ತಾತ್ಕಾಲಿಕ_w = (wchar_t *)av_calloc(len + 4 + 1, ಗಾತ್ರ(wchar_t));
        ಆದರೆ (!ತಾತ್ಕಾಲಿಕ_w) {
            errno = ENOMEM;
            ಹಿಂತಿರುಗಿ -1;
        }
        wcscpy(ತಾತ್ಕಾಲಿಕ_w, extended_ಮಾರ್ಗ_ಪೂರ್ವಪ್ರತ್ಯಯ);
        wcscat(ತಾತ್ಕಾಲಿಕ_w, ಮಾರ್ಗ_w);
    }

    av_freep(ppath_w);
    *ppath_w = ತಾತ್ಕಾಲಿಕ_w;

    ಹಿಂತಿರುಗಿ 0;
}

/**
 * Converts a file or folder path to wchar_t for use with Windows file
 * APIs. Paths with extended path prefix (either '\\?\' or \??\') are
 * left unchanged.
 * All other paths are normalized and converted to absolute paths.
 * Longs paths (>= MAX_PATH) are prefixed with the extended path or extended
 * UNC path prefix.
 * see .NET6: Path.GetFullPath() and Path.GetFullPathInternal()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/Path.Windows.cs#L126
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ get_extended_win32_ಮಾರ್ಗ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ, wchar_t **ppath_w)
{
    ಪೂರ್ಣಾಂಕ ret;
    size_t len;

    ಆದರೆ ((ret = utf8towchar(ಮಾರ್ಗ, ppath_w)) < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಆದರೆ (ಮಾರ್ಗ_is_extended(*ppath_w)) {
        /* Paths prefixed with '\\?\' or \??\' are considered normalized by definition.
         * Windows doesn't normalize those paths and neither should we.
         */
        ಹಿಂತಿರುಗಿ 0;
    }

    ಆದರೆ ((ret = ಮಾರ್ಗ_normalize(ppath_w)) < 0) {
        av_freep(ppath_w);
        ಹಿಂತಿರುಗಿ ret;
    }

    /* see .NET6: PathInternal.EnsureExtendedPrefixIfNeeded()
     * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L92
     */
    len = wcslen(*ppath_w);
    ಆದರೆ (len >= MAX_ಮಾರ್ಗ) {
        ಆದರೆ ((ret = ಕೂಡಿಸು_extended_ಪೂರ್ವಪ್ರತ್ಯಯ(ppath_w)) < 0) {
            av_freep(ppath_w);
            ಹಿಂತಿರುಗಿ ret;
        }
    }

    ಹಿಂತಿರುಗಿ 0;
}

#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_WCHAR_FILENAME_H */
