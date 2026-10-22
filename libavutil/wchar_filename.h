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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_WCHAR_FILENAME_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_WCHAR_FILENAME_H

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32

#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <windows.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"

av_warn_ਅਣਵਰਤਿਆ_ਨਤੀਜਾ
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ utf8towchar(ਅਚਲ ਅੱਖਰ *filename_utf8, wchar_t **filename_w)
{
    ਪੂਰਨ ਅੰਕ_chars;
    ਅੰਕ_chars = Multi_Byte_ਮੰਜ਼ਿਲ_Wide_Char(CP_UTF8, MB_ERR_INVALID_CHARS, filename_utf8, -1, ਨਿਰਾ, 0);
    ਜੇ (ਅੰਕ_chars <= 0) {
        *filename_w = ਨਿਰਾ;
        errno = EINVAL;
        ਵਾਪਸ -1;
    }
    *filename_w = (wchar_t *)av_calloc(ਅੰਕ_chars, ਆਕਾਰ(wchar_t));
    ਜੇ (!*filename_w) {
        errno = ENOMEM;
        ਵਾਪਸ -1;
    }
    Multi_Byte_ਮੰਜ਼ਿਲ_Wide_Char(CP_UTF8, 0, filename_utf8, -1, *filename_w, ਅੰਕ_chars);
    ਵਾਪਸ 0;
}

av_warn_ਅਣਵਰਤਿਆ_ਨਤੀਜਾ
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ wchartocp(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਕੋਡ_ਪੰਨਾ, ਅਚਲ wchar_t *filename_w,
                            ਅੱਖਰ **filename)
{
    DWORD flags = ਕੋਡ_ਪੰਨਾ == CP_UTF8 ? WC_ERR_INVALID_CHARS : 0;
    ਪੂਰਨ ਅੰਕ_chars = Wide_Char_ਮੰਜ਼ਿਲ_Multi_Byte(ਕੋਡ_ਪੰਨਾ, flags, filename_w, -1,
                                        ਨਿਰਾ, 0, ਨਿਰਾ, ਨਿਰਾ);
    ਜੇ (ਅੰਕ_chars <= 0) {
        *filename = ਨਿਰਾ;
        errno = EINVAL;
        ਵਾਪਸ -1;
    }
    *filename = (ਅੱਖਰ *)av_malloc_array(ਅੰਕ_chars, ਆਕਾਰ **filename);
    ਜੇ (!*filename) {
        errno = ENOMEM;
        ਵਾਪਸ -1;
    }
    Wide_Char_ਮੰਜ਼ਿਲ_Multi_Byte(ਕੋਡ_ਪੰਨਾ, flags, filename_w, -1,
                        *filename, ਅੰਕ_chars, ਨਿਰਾ, ਨਿਰਾ);
    ਵਾਪਸ 0;
}

av_warn_ਅਣਵਰਤਿਆ_ਨਤੀਜਾ
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ wchartoutf8(ਅਚਲ wchar_t *filename_w, ਅੱਖਰ **filename)
{
    ਵਾਪਸ wchartocp(CP_UTF8, filename_w, filename);
}

av_warn_ਅਣਵਰਤਿਆ_ਨਤੀਜਾ
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ wchartoansi(ਅਚਲ wchar_t *filename_w, ਅੱਖਰ **filename)
{
    ਵਾਪਸ wchartocp(CP_ACP, filename_w, filename);
}

av_warn_ਅਣਵਰਤਿਆ_ਨਤੀਜਾ
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ utf8toansi(ਅਚਲ ਅੱਖਰ *filename_utf8, ਅੱਖਰ **filename)
{
    wchar_t *filename_w = ਨਿਰਾ;
    ਪੂਰਨ ret = -1;
    ਜੇ (utf8towchar(filename_utf8, &filename_w))
        ਵਾਪਸ -1;

    ਜੇ (!filename_w) {
        *filename = ਨਿਰਾ;
        ਵਾਪਸ 0;
    }

    ret = wchartoansi(filename_w, filename);
    av_free(filename_w);
    ਵਾਪਸ ret;
}

/**
 * Checks for extended path prefixes for which normalization needs to be skipped.
 * see .NET6: PathInternal.IsExtended()
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L165
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ਰਸਤਾ_is_extended(ਅਚਲ wchar_t *ਰਸਤਾ)
{
    ਜੇ (ਰਸਤਾ[0] == L'\\' && (ਰਸਤਾ[1] == L'\\' || ਰਸਤਾ[1] == L'?') && ਰਸਤਾ[2] == L'?' && ਰਸਤਾ[3] == L'\\')
        ਵਾਪਸ 1;

    ਵਾਪਸ 0;
}

/**
 * Checks for a device path prefix.
 * see .NET6: PathInternal.IsDevice()
 * we don't check forward slashes and extended paths (as already done)
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L132
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ਰਸਤਾ_is_device_ਰਸਤਾ(ਅਚਲ wchar_t *ਰਸਤਾ)
{
    ਜੇ (ਰਸਤਾ[0] == L'\\' && ਰਸਤਾ[1] == L'\\' && ਰਸਤਾ[2] == L'.' && ਰਸਤਾ[3] == L'\\')
        ਵਾਪਸ 1;

    ਵਾਪਸ 0;
}

/**
 * Performs path normalization by calling GetFullPathNameW().
 * see .NET6: PathHelper.GetFullPathName()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L70
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ get_ਭਰਿਆ_ਰਸਤਾ_name(wchar_t **ppath_w)
{
    ਪੂਰਨ ਅੰਕ_chars;
    wchar_t *ਆਰਜ਼ੀ_w;

    ਅੰਕ_chars = Get_ਭਰਿਆ_ਰਸਤਾ_Name_W(*ppath_w, 0, ਨਿਰਾ, ਨਿਰਾ);
    ਜੇ (ਅੰਕ_chars <= 0) {
        errno = EINVAL;
        ਵਾਪਸ -1;
    }

    ਆਰਜ਼ੀ_w = (wchar_t *)av_calloc(ਅੰਕ_chars, ਆਕਾਰ(wchar_t));
    ਜੇ (!ਆਰਜ਼ੀ_w) {
        errno = ENOMEM;
        ਵਾਪਸ -1;
    }

    ਅੰਕ_chars = Get_ਭਰਿਆ_ਰਸਤਾ_Name_W(*ppath_w, ਅੰਕ_chars, ਆਰਜ਼ੀ_w, ਨਿਰਾ);
    ਜੇ (ਅੰਕ_chars <= 0) {
        av_free(ਆਰਜ਼ੀ_w);
        errno = EINVAL;
        ਵਾਪਸ -1;
    }

    av_freep(ppath_w);
    *ppath_w = ਆਰਜ਼ੀ_w;

    ਵਾਪਸ 0;
}

/**
 * Normalizes a Windows file or folder path.
 * Expansion of short paths (with 8.3 path components) is currently omitted
 * as it is not required for accessing long paths.
 * see .NET6: PathHelper.Normalize()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L25
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ਰਸਤਾ_normalize(wchar_t **ppath_w)
{
    ਪੂਰਨ ret;

    ਜੇ ((ret = get_ਭਰਿਆ_ਰਸਤਾ_name(ppath_w)) < 0)
        ਵਾਪਸ ret;

    /* What .NET does at this point is to call PathHelper.TryExpandShortFileName()
     * in case the path contains a '~' character.
     * We don't need to do this as we don't need to normalize the file name
     * for presentation, and the extended path prefix works with 8.3 path
     * components as well
     */
    ਵਾਪਸ 0;
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
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ਜੋੜੋ_extended_ਅਗੇਤਰ(wchar_t **ppath_w)
{
    ਅਚਲ wchar_t *unc_ਅਗੇਤਰ           = L"\\\\?\\UNC\\";
    ਅਚਲ wchar_t *extended_ਰਸਤਾ_ਅਗੇਤਰ = L"\\\\?\\";
    ਅਚਲ wchar_t *ਰਸਤਾ_w               = *ppath_w;
    ਅਚਲ size_t len                    = wcslen(ਰਸਤਾ_w);
    wchar_t *ਆਰਜ਼ੀ_w;

    /* We're skipping the check IsPartiallyQualified() because
     * we expect to have called GetFullPathNameW() already. */
    ਜੇ (len < 2 || ਰਸਤਾ_is_extended(*ppath_w) || ਰਸਤਾ_is_device_ਰਸਤਾ(*ppath_w)) {
        ਵਾਪਸ 0;
    }

    ਜੇ (ਰਸਤਾ_w[0] == L'\\' && ਰਸਤਾ_w[1] == L'\\') {
        /* unc_prefix length is 8 plus 1 for terminating zeros,
         * we subtract 2 for the leading '\\' of the original path */
        ਆਰਜ਼ੀ_w = (wchar_t *)av_calloc(len - 2 + 8 + 1, ਆਕਾਰ(wchar_t));
        ਜੇ (!ਆਰਜ਼ੀ_w) {
            errno = ENOMEM;
            ਵਾਪਸ -1;
        }
        wcscpy(ਆਰਜ਼ੀ_w, unc_ਅਗੇਤਰ);
        wcscat(ਆਰਜ਼ੀ_w, ਰਸਤਾ_w + 2);
    } ਨਹੀਂਤਾਂ {
        // The length of extended_path_prefix is 4 plus 1 for terminating zeros
        ਆਰਜ਼ੀ_w = (wchar_t *)av_calloc(len + 4 + 1, ਆਕਾਰ(wchar_t));
        ਜੇ (!ਆਰਜ਼ੀ_w) {
            errno = ENOMEM;
            ਵਾਪਸ -1;
        }
        wcscpy(ਆਰਜ਼ੀ_w, extended_ਰਸਤਾ_ਅਗੇਤਰ);
        wcscat(ਆਰਜ਼ੀ_w, ਰਸਤਾ_w);
    }

    av_freep(ppath_w);
    *ppath_w = ਆਰਜ਼ੀ_w;

    ਵਾਪਸ 0;
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
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ get_extended_win32_ਰਸਤਾ(ਅਚਲ ਅੱਖਰ *ਰਸਤਾ, wchar_t **ppath_w)
{
    ਪੂਰਨ ret;
    size_t len;

    ਜੇ ((ret = utf8towchar(ਰਸਤਾ, ppath_w)) < 0)
        ਵਾਪਸ ret;

    ਜੇ (ਰਸਤਾ_is_extended(*ppath_w)) {
        /* Paths prefixed with '\\?\' or \??\' are considered normalized by definition.
         * Windows doesn't normalize those paths and neither should we.
         */
        ਵਾਪਸ 0;
    }

    ਜੇ ((ret = ਰਸਤਾ_normalize(ppath_w)) < 0) {
        av_freep(ppath_w);
        ਵਾਪਸ ret;
    }

    /* see .NET6: PathInternal.EnsureExtendedPrefixIfNeeded()
     * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L92
     */
    len = wcslen(*ppath_w);
    ਜੇ (len >= MAX_ਰਸਤਾ) {
        ਜੇ ((ret = ਜੋੜੋ_extended_ਅਗੇਤਰ(ppath_w)) < 0) {
            av_freep(ppath_w);
            ਵਾਪਸ ret;
        }
    }

    ਵਾਪਸ 0;
}

#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* AVUTIL_WCHAR_FILENAME_H */
