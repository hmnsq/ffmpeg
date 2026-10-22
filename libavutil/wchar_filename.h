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

#ضمن <errno.h>
#ضمن <stddef.h>
#ضمن <windows.h>
#ضمن "mem.h"

av_warn_unused_result
ساكن مضمن صحيح utf8towchar(ثابت حرف *filename_utf8, wchar_t **filename_w)
{
    صحيح num_chars;
    num_chars = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, filename_utf8, -1, عدم, 0);
    ܐܢ (num_chars <= 0) {
        *filename_w = عدم;
        errno = EINVAL;
        ܦܢܐ -1;
    }
    *filename_w = (wchar_t *)av_calloc(num_chars, حجم(wchar_t));
    ܐܢ (!*filename_w) {
        errno = ENOMEM;
        ܦܢܐ -1;
    }
    MultiByteToWideChar(CP_UTF8, 0, filename_utf8, -1, *filename_w, num_chars);
    ܦܢܐ 0;
}

av_warn_unused_result
ساكن مضمن صحيح wchartocp(unsigned صحيح code_page, ثابت wchar_t *filename_w,
                            حرف **filename)
{
    DWORD flags = code_page == CP_UTF8 ? WC_ERR_INVALID_CHARS : 0;
    صحيح num_chars = WideCharToMultiByte(code_page, flags, filename_w, -1,
                                        عدم, 0, عدم, عدم);
    ܐܢ (num_chars <= 0) {
        *filename = عدم;
        errno = EINVAL;
        ܦܢܐ -1;
    }
    *filename = (حرف *)av_malloc_array(num_chars, حجم **filename);
    ܐܢ (!*filename) {
        errno = ENOMEM;
        ܦܢܐ -1;
    }
    WideCharToMultiByte(code_page, flags, filename_w, -1,
                        *filename, num_chars, عدم, عدم);
    ܦܢܐ 0;
}

av_warn_unused_result
ساكن مضمن صحيح wchartoutf8(ثابت wchar_t *filename_w, حرف **filename)
{
    ܦܢܐ wchartocp(CP_UTF8, filename_w, filename);
}

av_warn_unused_result
ساكن مضمن صحيح wchartoansi(ثابت wchar_t *filename_w, حرف **filename)
{
    ܦܢܐ wchartocp(CP_ACP, filename_w, filename);
}

av_warn_unused_result
ساكن مضمن صحيح utf8toansi(ثابت حرف *filename_utf8, حرف **filename)
{
    wchar_t *filename_w = عدم;
    صحيح ret = -1;
    ܐܢ (utf8towchar(filename_utf8, &filename_w))
        ܦܢܐ -1;

    ܐܢ (!filename_w) {
        *filename = عدم;
        ܦܢܐ 0;
    }

    ret = wchartoansi(filename_w, filename);
    av_free(filename_w);
    ܦܢܐ ret;
}

/**
 * Checks for extended path prefixes for which normalization needs to be skipped.
 * see .NET6: PathInternal.IsExtended()
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L165
 */
ساكن مضمن صحيح path_is_extended(ثابت wchar_t *path)
{
    ܐܢ (path[0] == L'\\' && (path[1] == L'\\' || path[1] == L'?') && path[2] == L'?' && path[3] == L'\\')
        ܦܢܐ 1;

    ܦܢܐ 0;
}

/**
 * Checks for a device path prefix.
 * see .NET6: PathInternal.IsDevice()
 * we don't check forward slashes and extended paths (as already done)
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L132
 */
ساكن مضمن صحيح path_is_device_path(ثابت wchar_t *path)
{
    ܐܢ (path[0] == L'\\' && path[1] == L'\\' && path[2] == L'.' && path[3] == L'\\')
        ܦܢܐ 1;

    ܦܢܐ 0;
}

/**
 * Performs path normalization by calling GetFullPathNameW().
 * see .NET6: PathHelper.GetFullPathName()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L70
 */
ساكن مضمن صحيح get_full_path_name(wchar_t **ppath_w)
{
    صحيح num_chars;
    wchar_t *temp_w;

    num_chars = GetFullPathNameW(*ppath_w, 0, عدم, عدم);
    ܐܢ (num_chars <= 0) {
        errno = EINVAL;
        ܦܢܐ -1;
    }

    temp_w = (wchar_t *)av_calloc(num_chars, حجم(wchar_t));
    ܐܢ (!temp_w) {
        errno = ENOMEM;
        ܦܢܐ -1;
    }

    num_chars = GetFullPathNameW(*ppath_w, num_chars, temp_w, عدم);
    ܐܢ (num_chars <= 0) {
        av_free(temp_w);
        errno = EINVAL;
        ܦܢܐ -1;
    }

    av_freep(ppath_w);
    *ppath_w = temp_w;

    ܦܢܐ 0;
}

/**
 * Normalizes a Windows file or folder path.
 * Expansion of short paths (with 8.3 path components) is currently omitted
 * as it is not required for accessing long paths.
 * see .NET6: PathHelper.Normalize()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L25
 */
ساكن مضمن صحيح path_normalize(wchar_t **ppath_w)
{
    صحيح ret;

    ܐܢ ((ret = get_full_path_name(ppath_w)) < 0)
        ܦܢܐ ret;

    /* What .NET does at this point is to call PathHelper.TryExpandShortFileName()
     * in case the path contains a '~' character.
     * We don't need to do this as we don't need to normalize the file name
     * for presentation, and the extended path prefix works with 8.3 path
     * components as well
     */
    ܦܢܐ 0;
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
ساكن مضمن صحيح add_extended_prefix(wchar_t **ppath_w)
{
    ثابت wchar_t *unc_prefix           = L"\\\\?\\UNC\\";
    ثابت wchar_t *extended_path_prefix = L"\\\\?\\";
    ثابت wchar_t *path_w               = *ppath_w;
    ثابت size_t len                    = wcslen(path_w);
    wchar_t *temp_w;

    /* We're skipping the check IsPartiallyQualified() because
     * we expect to have called GetFullPathNameW() already. */
    ܐܢ (len < 2 || path_is_extended(*ppath_w) || path_is_device_path(*ppath_w)) {
        ܦܢܐ 0;
    }

    ܐܢ (path_w[0] == L'\\' && path_w[1] == L'\\') {
        /* unc_prefix length is 8 plus 1 for terminating zeros,
         * we subtract 2 for the leading '\\' of the original path */
        temp_w = (wchar_t *)av_calloc(len - 2 + 8 + 1, حجم(wchar_t));
        ܐܢ (!temp_w) {
            errno = ENOMEM;
            ܦܢܐ -1;
        }
        wcscpy(temp_w, unc_prefix);
        wcscat(temp_w, path_w + 2);
    } ܐܚܪܢܐ {
        // The length of extended_path_prefix is 4 plus 1 for terminating zeros
        temp_w = (wchar_t *)av_calloc(len + 4 + 1, حجم(wchar_t));
        ܐܢ (!temp_w) {
            errno = ENOMEM;
            ܦܢܐ -1;
        }
        wcscpy(temp_w, extended_path_prefix);
        wcscat(temp_w, path_w);
    }

    av_freep(ppath_w);
    *ppath_w = temp_w;

    ܦܢܐ 0;
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
ساكن مضمن صحيح get_extended_win32_path(ثابت حرف *path, wchar_t **ppath_w)
{
    صحيح ret;
    size_t len;

    ܐܢ ((ret = utf8towchar(path, ppath_w)) < 0)
        ܦܢܐ ret;

    ܐܢ (path_is_extended(*ppath_w)) {
        /* Paths prefixed with '\\?\' or \??\' are considered normalized by definition.
         * Windows doesn't normalize those paths and neither should we.
         */
        ܦܢܐ 0;
    }

    ܐܢ ((ret = path_normalize(ppath_w)) < 0) {
        av_freep(ppath_w);
        ܦܢܐ ret;
    }

    /* see .NET6: PathInternal.EnsureExtendedPrefixIfNeeded()
     * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L92
     */
    len = wcslen(*ppath_w);
    ܐܢ (len >= MAX_PATH) {
        ܐܢ ((ret = add_extended_prefix(ppath_w)) < 0) {
            av_freep(ppath_w);
            ܦܢܐ ret;
        }
    }

    ܦܢܐ 0;
}

#endif

#endif /* AVUTIL_WCHAR_FILENAME_H */
