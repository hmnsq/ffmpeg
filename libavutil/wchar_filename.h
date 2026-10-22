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

#ifndef AVUTIL_WCHAR_FILENAME_H
#define AVUTIL_WCHAR_FILENAME_H

#ifdef _WIN32

#അന്തര്ഭാവ <errno.h>
#അന്തര്ഭാവ <stddef.h>
#അന്തര്ഭാവ <windows.h>
#അന്തര്ഭാവ "mem.h"

av_warn_unused_result
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ utf8towchar(സ്ഥിരം അക്ഷരം *filename_utf8, wchar_t **filename_w)
{
    പൂർണ്ണസംഖ്യ അക്കം_chars;
    അക്കം_chars = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, filename_utf8, -1, ശൂന്യ, 0);
    എങ്കിൽ (അക്കം_chars <= 0) {
        *filename_w = ശൂന്യ;
        errno = EINVAL;
        തിരികെ -1;
    }
    *filename_w = (wchar_t *)av_calloc(അക്കം_chars, വലുപ്പം(wchar_t));
    എങ്കിൽ (!*filename_w) {
        errno = ENOMEM;
        തിരികെ -1;
    }
    MultiByteToWideChar(CP_UTF8, 0, filename_utf8, -1, *filename_w, അക്കം_chars);
    തിരികെ 0;
}

av_warn_unused_result
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ wchartocp(unsigned പൂർണ്ണസംഖ്യ code_page, സ്ഥിരം wchar_t *filename_w,
                            അക്ഷരം **filename)
{
    DWORD flags = code_page == CP_UTF8 ? WC_ERR_INVALID_CHARS : 0;
    പൂർണ്ണസംഖ്യ അക്കം_chars = WideCharToMultiByte(code_page, flags, filename_w, -1,
                                        ശൂന്യ, 0, ശൂന്യ, ശൂന്യ);
    എങ്കിൽ (അക്കം_chars <= 0) {
        *filename = ശൂന്യ;
        errno = EINVAL;
        തിരികെ -1;
    }
    *filename = (അക്ഷരം *)av_malloc_array(അക്കം_chars, വലുപ്പം **filename);
    എങ്കിൽ (!*filename) {
        errno = ENOMEM;
        തിരികെ -1;
    }
    WideCharToMultiByte(code_page, flags, filename_w, -1,
                        *filename, അക്കം_chars, ശൂന്യ, ശൂന്യ);
    തിരികെ 0;
}

av_warn_unused_result
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ wchartoutf8(സ്ഥിരം wchar_t *filename_w, അക്ഷരം **filename)
{
    തിരികെ wchartocp(CP_UTF8, filename_w, filename);
}

av_warn_unused_result
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ wchartoansi(സ്ഥിരം wchar_t *filename_w, അക്ഷരം **filename)
{
    തിരികെ wchartocp(CP_ACP, filename_w, filename);
}

av_warn_unused_result
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ utf8toansi(സ്ഥിരം അക്ഷരം *filename_utf8, അക്ഷരം **filename)
{
    wchar_t *filename_w = ശൂന്യ;
    പൂർണ്ണസംഖ്യ ret = -1;
    എങ്കിൽ (utf8towchar(filename_utf8, &filename_w))
        തിരികെ -1;

    എങ്കിൽ (!filename_w) {
        *filename = ശൂന്യ;
        തിരികെ 0;
    }

    ret = wchartoansi(filename_w, filename);
    av_free(filename_w);
    തിരികെ ret;
}

/**
 * Checks for extended path prefixes for which normalization needs to be skipped.
 * see .NET6: PathInternal.IsExtended()
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L165
 */
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ path_is_extended(സ്ഥിരം wchar_t *path)
{
    എങ്കിൽ (path[0] == L'\\' && (path[1] == L'\\' || path[1] == L'?') && path[2] == L'?' && path[3] == L'\\')
        തിരികെ 1;

    തിരികെ 0;
}

/**
 * Checks for a device path prefix.
 * see .NET6: PathInternal.IsDevice()
 * we don't check forward slashes and extended paths (as already done)
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L132
 */
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ path_is_device_path(സ്ഥിരം wchar_t *path)
{
    എങ്കിൽ (path[0] == L'\\' && path[1] == L'\\' && path[2] == L'.' && path[3] == L'\\')
        തിരികെ 1;

    തിരികെ 0;
}

/**
 * Performs path normalization by calling GetFullPathNameW().
 * see .NET6: PathHelper.GetFullPathName()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L70
 */
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ get_full_path_name(wchar_t **ppath_w)
{
    പൂർണ്ണസംഖ്യ അക്കം_chars;
    wchar_t *temp_w;

    അക്കം_chars = GetFullPathNameW(*ppath_w, 0, ശൂന്യ, ശൂന്യ);
    എങ്കിൽ (അക്കം_chars <= 0) {
        errno = EINVAL;
        തിരികെ -1;
    }

    temp_w = (wchar_t *)av_calloc(അക്കം_chars, വലുപ്പം(wchar_t));
    എങ്കിൽ (!temp_w) {
        errno = ENOMEM;
        തിരികെ -1;
    }

    അക്കം_chars = GetFullPathNameW(*ppath_w, അക്കം_chars, temp_w, ശൂന്യ);
    എങ്കിൽ (അക്കം_chars <= 0) {
        av_free(temp_w);
        errno = EINVAL;
        തിരികെ -1;
    }

    av_freep(ppath_w);
    *ppath_w = temp_w;

    തിരികെ 0;
}

/**
 * Normalizes a Windows file or folder path.
 * Expansion of short paths (with 8.3 path components) is currently omitted
 * as it is not required for accessing long paths.
 * see .NET6: PathHelper.Normalize()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L25
 */
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ path_normalize(wchar_t **ppath_w)
{
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ ((ret = get_full_path_name(ppath_w)) < 0)
        തിരികെ ret;

    /* What .NET does at this point is to call PathHelper.TryExpandShortFileName()
     * in case the path contains a '~' character.
     * We don't need to do this as we don't need to normalize the file name
     * for presentation, and the extended path prefix works with 8.3 path
     * components as well
     */
    തിരികെ 0;
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
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ add_extended_prefix(wchar_t **ppath_w)
{
    സ്ഥിരം wchar_t *unc_prefix           = L"\\\\?\\UNC\\";
    സ്ഥിരം wchar_t *extended_path_prefix = L"\\\\?\\";
    സ്ഥിരം wchar_t *path_w               = *ppath_w;
    സ്ഥിരം size_t len                    = wcslen(path_w);
    wchar_t *temp_w;

    /* We're skipping the check IsPartiallyQualified() because
     * we expect to have called GetFullPathNameW() already. */
    എങ്കിൽ (len < 2 || path_is_extended(*ppath_w) || path_is_device_path(*ppath_w)) {
        തിരികെ 0;
    }

    എങ്കിൽ (path_w[0] == L'\\' && path_w[1] == L'\\') {
        /* unc_prefix length is 8 plus 1 for terminating zeros,
         * we subtract 2 for the leading '\\' of the original path */
        temp_w = (wchar_t *)av_calloc(len - 2 + 8 + 1, വലുപ്പം(wchar_t));
        എങ്കിൽ (!temp_w) {
            errno = ENOMEM;
            തിരികെ -1;
        }
        wcscpy(temp_w, unc_prefix);
        wcscat(temp_w, path_w + 2);
    } അല്ലെങ്കിൽ {
        // The length of extended_path_prefix is 4 plus 1 for terminating zeros
        temp_w = (wchar_t *)av_calloc(len + 4 + 1, വലുപ്പം(wchar_t));
        എങ്കിൽ (!temp_w) {
            errno = ENOMEM;
            തിരികെ -1;
        }
        wcscpy(temp_w, extended_path_prefix);
        wcscat(temp_w, path_w);
    }

    av_freep(ppath_w);
    *ppath_w = temp_w;

    തിരികെ 0;
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
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ get_extended_win32_path(സ്ഥിരം അക്ഷരം *path, wchar_t **ppath_w)
{
    പൂർണ്ണസംഖ്യ ret;
    size_t len;

    എങ്കിൽ ((ret = utf8towchar(path, ppath_w)) < 0)
        തിരികെ ret;

    എങ്കിൽ (path_is_extended(*ppath_w)) {
        /* Paths prefixed with '\\?\' or \??\' are considered normalized by definition.
         * Windows doesn't normalize those paths and neither should we.
         */
        തിരികെ 0;
    }

    എങ്കിൽ ((ret = path_normalize(ppath_w)) < 0) {
        av_freep(ppath_w);
        തിരികെ ret;
    }

    /* see .NET6: PathInternal.EnsureExtendedPrefixIfNeeded()
     * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L92
     */
    len = wcslen(*ppath_w);
    എങ്കിൽ (len >= MAX_PATH) {
        എങ്കിൽ ((ret = add_extended_prefix(ppath_w)) < 0) {
            av_freep(ppath_w);
            തിരികെ ret;
        }
    }

    തിരികെ 0;
}

#endif

#endif /* AVUTIL_WCHAR_FILENAME_H */
