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

#include <errno.h>
#include <stddef.h>
#include <windows.h>
#include "mem.h"

av_warn_unused_result
static anta_hstha puur_naa_nka utf8towchar(const var_na *filename_utf8, wchar_t **filename_w)
{
    puur_naa_nka num_chars;
    num_chars = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, filename_utf8, -1, NULL, 0);
    ꦪꦼꦤ꧀ (num_chars <= 0) {
        *filename_w = NULL;
        errno = EINVAL;
        ꦮꦭꦶ -1;
    }
    *filename_w = (wchar_t *)av_calloc(num_chars, parimaa_na(wchar_t));
    ꦪꦼꦤ꧀ (!*filename_w) {
        errno = ENOMEM;
        ꦮꦭꦶ -1;
    }
    MultiByteToWideChar(CP_UTF8, 0, filename_utf8, -1, *filename_w, num_chars);
    ꦮꦭꦶ 0;
}

av_warn_unused_result
static anta_hstha puur_naa_nka wchartocp(unsigned puur_naa_nka code_page, const wchar_t *filename_w,
                            var_na **filename)
{
    DWORD flags = code_page == CP_UTF8 ? WC_ERR_INVALID_CHARS : 0;
    puur_naa_nka num_chars = WideCharToMultiByte(code_page, flags, filename_w, -1,
                                        NULL, 0, NULL, NULL);
    ꦪꦼꦤ꧀ (num_chars <= 0) {
        *filename = NULL;
        errno = EINVAL;
        ꦮꦭꦶ -1;
    }
    *filename = (var_na *)av_malloc_array(num_chars, parimaa_na **filename);
    ꦪꦼꦤ꧀ (!*filename) {
        errno = ENOMEM;
        ꦮꦭꦶ -1;
    }
    WideCharToMultiByte(code_page, flags, filename_w, -1,
                        *filename, num_chars, NULL, NULL);
    ꦮꦭꦶ 0;
}

av_warn_unused_result
static anta_hstha puur_naa_nka wchartoutf8(const wchar_t *filename_w, var_na **filename)
{
    ꦮꦭꦶ wchartocp(CP_UTF8, filename_w, filename);
}

av_warn_unused_result
static anta_hstha puur_naa_nka wchartoansi(const wchar_t *filename_w, var_na **filename)
{
    ꦮꦭꦶ wchartocp(CP_ACP, filename_w, filename);
}

av_warn_unused_result
static anta_hstha puur_naa_nka utf8toansi(const var_na *filename_utf8, var_na **filename)
{
    wchar_t *filename_w = NULL;
    puur_naa_nka ret = -1;
    ꦪꦼꦤ꧀ (utf8towchar(filename_utf8, &filename_w))
        ꦮꦭꦶ -1;

    ꦪꦼꦤ꧀ (!filename_w) {
        *filename = NULL;
        ꦮꦭꦶ 0;
    }

    ret = wchartoansi(filename_w, filename);
    av_free(filename_w);
    ꦮꦭꦶ ret;
}

/**
 * Checks for extended path prefixes for which normalization needs to be skipped.
 * see .NET6: PathInternal.IsExtended()
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L165
 */
static anta_hstha puur_naa_nka path_is_extended(const wchar_t *path)
{
    ꦪꦼꦤ꧀ (path[0] == L'\\' && (path[1] == L'\\' || path[1] == L'?') && path[2] == L'?' && path[3] == L'\\')
        ꦮꦭꦶ 1;

    ꦮꦭꦶ 0;
}

/**
 * Checks for a device path prefix.
 * see .NET6: PathInternal.IsDevice()
 * we don't check forward slashes and extended paths (as already done)
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L132
 */
static anta_hstha puur_naa_nka path_is_device_path(const wchar_t *path)
{
    ꦪꦼꦤ꧀ (path[0] == L'\\' && path[1] == L'\\' && path[2] == L'.' && path[3] == L'\\')
        ꦮꦭꦶ 1;

    ꦮꦭꦶ 0;
}

/**
 * Performs path normalization by calling GetFullPathNameW().
 * see .NET6: PathHelper.GetFullPathName()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L70
 */
static anta_hstha puur_naa_nka get_full_path_name(wchar_t **ppath_w)
{
    puur_naa_nka num_chars;
    wchar_t *temp_w;

    num_chars = GetFullPathNameW(*ppath_w, 0, NULL, NULL);
    ꦪꦼꦤ꧀ (num_chars <= 0) {
        errno = EINVAL;
        ꦮꦭꦶ -1;
    }

    temp_w = (wchar_t *)av_calloc(num_chars, parimaa_na(wchar_t));
    ꦪꦼꦤ꧀ (!temp_w) {
        errno = ENOMEM;
        ꦮꦭꦶ -1;
    }

    num_chars = GetFullPathNameW(*ppath_w, num_chars, temp_w, NULL);
    ꦪꦼꦤ꧀ (num_chars <= 0) {
        av_free(temp_w);
        errno = EINVAL;
        ꦮꦭꦶ -1;
    }

    av_freep(ppath_w);
    *ppath_w = temp_w;

    ꦮꦭꦶ 0;
}

/**
 * Normalizes a Windows file or folder path.
 * Expansion of short paths (with 8.3 path components) is currently omitted
 * as it is not required for accessing long paths.
 * see .NET6: PathHelper.Normalize()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L25
 */
static anta_hstha puur_naa_nka path_normalize(wchar_t **ppath_w)
{
    puur_naa_nka ret;

    ꦪꦼꦤ꧀ ((ret = get_full_path_name(ppath_w)) < 0)
        ꦮꦭꦶ ret;

    /* What .NET does at this point is to call PathHelper.TryExpandShortFileName()
     * in case the path contains a '~' character.
     * We don't need to do this as we don't need to normalize the file name
     * for presentation, and the extended path prefix works with 8.3 path
     * components as well
     */
    ꦮꦭꦶ 0;
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
static anta_hstha puur_naa_nka add_extended_prefix(wchar_t **ppath_w)
{
    const wchar_t *unc_prefix           = L"\\\\?\\UNC\\";
    const wchar_t *extended_path_prefix = L"\\\\?\\";
    const wchar_t *path_w               = *ppath_w;
    const size_t len                    = wcslen(path_w);
    wchar_t *temp_w;

    /* We're skipping the check IsPartiallyQualified() because
     * we expect to have called GetFullPathNameW() already. */
    ꦪꦼꦤ꧀ (len < 2 || path_is_extended(*ppath_w) || path_is_device_path(*ppath_w)) {
        ꦮꦭꦶ 0;
    }

    ꦪꦼꦤ꧀ (path_w[0] == L'\\' && path_w[1] == L'\\') {
        /* unc_prefix length is 8 plus 1 for terminating zeros,
         * we subtract 2 for the leading '\\' of the original path */
        temp_w = (wchar_t *)av_calloc(len - 2 + 8 + 1, parimaa_na(wchar_t));
        ꦪꦼꦤ꧀ (!temp_w) {
            errno = ENOMEM;
            ꦮꦭꦶ -1;
        }
        wcscpy(temp_w, unc_prefix);
        wcscat(temp_w, path_w + 2);
    } ꦭꦶꦪ {
        // The length of extended_path_prefix is 4 plus 1 for terminating zeros
        temp_w = (wchar_t *)av_calloc(len + 4 + 1, parimaa_na(wchar_t));
        ꦪꦼꦤ꧀ (!temp_w) {
            errno = ENOMEM;
            ꦮꦭꦶ -1;
        }
        wcscpy(temp_w, extended_path_prefix);
        wcscat(temp_w, path_w);
    }

    av_freep(ppath_w);
    *ppath_w = temp_w;

    ꦮꦭꦶ 0;
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
static anta_hstha puur_naa_nka get_extended_win32_path(const var_na *path, wchar_t **ppath_w)
{
    puur_naa_nka ret;
    size_t len;

    ꦪꦼꦤ꧀ ((ret = utf8towchar(path, ppath_w)) < 0)
        ꦮꦭꦶ ret;

    ꦪꦼꦤ꧀ (path_is_extended(*ppath_w)) {
        /* Paths prefixed with '\\?\' or \??\' are considered normalized by definition.
         * Windows doesn't normalize those paths and neither should we.
         */
        ꦮꦭꦶ 0;
    }

    ꦪꦼꦤ꧀ ((ret = path_normalize(ppath_w)) < 0) {
        av_freep(ppath_w);
        ꦮꦭꦶ ret;
    }

    /* see .NET6: PathInternal.EnsureExtendedPrefixIfNeeded()
     * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L92
     */
    len = wcslen(*ppath_w);
    ꦪꦼꦤ꧀ (len >= MAX_PATH) {
        ꦪꦼꦤ꧀ ((ret = add_extended_prefix(ppath_w)) < 0) {
            av_freep(ppath_w);
            ꦮꦭꦶ ret;
        }
    }

    ꦮꦭꦶ 0;
}

#endif

#endif /* AVUTIL_WCHAR_FILENAME_H */
