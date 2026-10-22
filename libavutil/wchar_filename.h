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

#অন্তর্ভাব <errno.h>
#অন্তর্ভাব <stddef.h>
#অন্তর্ভাব <windows.h>
#অন্তর্ভাব "mem.h"

av_warn_unused_ফলাফল
স্থির অন্তঃরেখ পূর্ণসংখ্যা utf8towchar(ধ্রুবক অক্ষর *filename_utf8, wchar_t **filename_w)
{
    পূর্ণসংখ্যা অঙ্ক_chars;
    অঙ্ক_chars = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, filename_utf8, -1, ফাঁকা, 0);
    যদি (অঙ্ক_chars <= 0) {
        *filename_w = ফাঁকা;
        errno = EINVAL;
        ফেরত -1;
    }
    *filename_w = (wchar_t *)av_calloc(অঙ্ক_chars, আকার(wchar_t));
    যদি (!*filename_w) {
        errno = ENOMEM;
        ফেরত -1;
    }
    MultiByteToWideChar(CP_UTF8, 0, filename_utf8, -1, *filename_w, অঙ্ক_chars);
    ফেরত 0;
}

av_warn_unused_ফলাফল
স্থির অন্তঃরেখ পূর্ণসংখ্যা wchartocp(unsigned পূর্ণসংখ্যা code_page, ধ্রুবক wchar_t *filename_w,
                            অক্ষর **filename)
{
    DWORD flags = code_page == CP_UTF8 ? WC_ERR_INVALID_CHARS : 0;
    পূর্ণসংখ্যা অঙ্ক_chars = WideCharToMultiByte(code_page, flags, filename_w, -1,
                                        ফাঁকা, 0, ফাঁকা, ফাঁকা);
    যদি (অঙ্ক_chars <= 0) {
        *filename = ফাঁকা;
        errno = EINVAL;
        ফেরত -1;
    }
    *filename = (অক্ষর *)av_malloc_array(অঙ্ক_chars, আকার **filename);
    যদি (!*filename) {
        errno = ENOMEM;
        ফেরত -1;
    }
    WideCharToMultiByte(code_page, flags, filename_w, -1,
                        *filename, অঙ্ক_chars, ফাঁকা, ফাঁকা);
    ফেরত 0;
}

av_warn_unused_ফলাফল
স্থির অন্তঃরেখ পূর্ণসংখ্যা wchartoutf8(ধ্রুবক wchar_t *filename_w, অক্ষর **filename)
{
    ফেরত wchartocp(CP_UTF8, filename_w, filename);
}

av_warn_unused_ফলাফল
স্থির অন্তঃরেখ পূর্ণসংখ্যা wchartoansi(ধ্রুবক wchar_t *filename_w, অক্ষর **filename)
{
    ফেরত wchartocp(CP_ACP, filename_w, filename);
}

av_warn_unused_ফলাফল
স্থির অন্তঃরেখ পূর্ণসংখ্যা utf8toansi(ধ্রুবক অক্ষর *filename_utf8, অক্ষর **filename)
{
    wchar_t *filename_w = ফাঁকা;
    পূর্ণসংখ্যা ret = -1;
    যদি (utf8towchar(filename_utf8, &filename_w))
        ফেরত -1;

    যদি (!filename_w) {
        *filename = ফাঁকা;
        ফেরত 0;
    }

    ret = wchartoansi(filename_w, filename);
    av_free(filename_w);
    ফেরত ret;
}

/**
 * Checks for extended path prefixes for which normalization needs to be skipped.
 * see .NET6: PathInternal.IsExtended()
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L165
 */
স্থির অন্তঃরেখ পূর্ণসংখ্যা path_is_extended(ধ্রুবক wchar_t *path)
{
    যদি (path[0] == L'\\' && (path[1] == L'\\' || path[1] == L'?') && path[2] == L'?' && path[3] == L'\\')
        ফেরত 1;

    ফেরত 0;
}

/**
 * Checks for a device path prefix.
 * see .NET6: PathInternal.IsDevice()
 * we don't check forward slashes and extended paths (as already done)
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L132
 */
স্থির অন্তঃরেখ পূর্ণসংখ্যা path_is_device_path(ধ্রুবক wchar_t *path)
{
    যদি (path[0] == L'\\' && path[1] == L'\\' && path[2] == L'.' && path[3] == L'\\')
        ফেরত 1;

    ফেরত 0;
}

/**
 * Performs path normalization by calling GetFullPathNameW().
 * see .NET6: PathHelper.GetFullPathName()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L70
 */
স্থির অন্তঃরেখ পূর্ণসংখ্যা get_full_path_name(wchar_t **ppath_w)
{
    পূর্ণসংখ্যা অঙ্ক_chars;
    wchar_t *অস্থায়ী_w;

    অঙ্ক_chars = GetFullPathNameW(*ppath_w, 0, ফাঁকা, ফাঁকা);
    যদি (অঙ্ক_chars <= 0) {
        errno = EINVAL;
        ফেরত -1;
    }

    অস্থায়ী_w = (wchar_t *)av_calloc(অঙ্ক_chars, আকার(wchar_t));
    যদি (!অস্থায়ী_w) {
        errno = ENOMEM;
        ফেরত -1;
    }

    অঙ্ক_chars = GetFullPathNameW(*ppath_w, অঙ্ক_chars, অস্থায়ী_w, ফাঁকা);
    যদি (অঙ্ক_chars <= 0) {
        av_free(অস্থায়ী_w);
        errno = EINVAL;
        ফেরত -1;
    }

    av_freep(ppath_w);
    *ppath_w = অস্থায়ী_w;

    ফেরত 0;
}

/**
 * Normalizes a Windows file or folder path.
 * Expansion of short paths (with 8.3 path components) is currently omitted
 * as it is not required for accessing long paths.
 * see .NET6: PathHelper.Normalize()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L25
 */
স্থির অন্তঃরেখ পূর্ণসংখ্যা path_normalize(wchar_t **ppath_w)
{
    পূর্ণসংখ্যা ret;

    যদি ((ret = get_full_path_name(ppath_w)) < 0)
        ফেরত ret;

    /* What .NET does at this point is to call PathHelper.TryExpandShortFileName()
     * in case the path contains a '~' character.
     * We don't need to do this as we don't need to normalize the file name
     * for presentation, and the extended path prefix works with 8.3 path
     * components as well
     */
    ফেরত 0;
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
স্থির অন্তঃরেখ পূর্ণসংখ্যা add_extended_prefix(wchar_t **ppath_w)
{
    ধ্রুবক wchar_t *unc_prefix           = L"\\\\?\\UNC\\";
    ধ্রুবক wchar_t *extended_path_prefix = L"\\\\?\\";
    ধ্রুবক wchar_t *path_w               = *ppath_w;
    ধ্রুবক size_t len                    = wcslen(path_w);
    wchar_t *অস্থায়ী_w;

    /* We're skipping the check IsPartiallyQualified() because
     * we expect to have called GetFullPathNameW() already. */
    যদি (len < 2 || path_is_extended(*ppath_w) || path_is_device_path(*ppath_w)) {
        ফেরত 0;
    }

    যদি (path_w[0] == L'\\' && path_w[1] == L'\\') {
        /* unc_prefix length is 8 plus 1 for terminating zeros,
         * we subtract 2 for the leading '\\' of the original path */
        অস্থায়ী_w = (wchar_t *)av_calloc(len - 2 + 8 + 1, আকার(wchar_t));
        যদি (!অস্থায়ী_w) {
            errno = ENOMEM;
            ফেরত -1;
        }
        wcscpy(অস্থায়ী_w, unc_prefix);
        wcscat(অস্থায়ী_w, path_w + 2);
    } অন্যথা {
        // The length of extended_path_prefix is 4 plus 1 for terminating zeros
        অস্থায়ী_w = (wchar_t *)av_calloc(len + 4 + 1, আকার(wchar_t));
        যদি (!অস্থায়ী_w) {
            errno = ENOMEM;
            ফেরত -1;
        }
        wcscpy(অস্থায়ী_w, extended_path_prefix);
        wcscat(অস্থায়ী_w, path_w);
    }

    av_freep(ppath_w);
    *ppath_w = অস্থায়ী_w;

    ফেরত 0;
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
স্থির অন্তঃরেখ পূর্ণসংখ্যা get_extended_win32_path(ধ্রুবক অক্ষর *path, wchar_t **ppath_w)
{
    পূর্ণসংখ্যা ret;
    size_t len;

    যদি ((ret = utf8towchar(path, ppath_w)) < 0)
        ফেরত ret;

    যদি (path_is_extended(*ppath_w)) {
        /* Paths prefixed with '\\?\' or \??\' are considered normalized by definition.
         * Windows doesn't normalize those paths and neither should we.
         */
        ফেরত 0;
    }

    যদি ((ret = path_normalize(ppath_w)) < 0) {
        av_freep(ppath_w);
        ফেরত ret;
    }

    /* see .NET6: PathInternal.EnsureExtendedPrefixIfNeeded()
     * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L92
     */
    len = wcslen(*ppath_w);
    যদি (len >= MAX_PATH) {
        যদি ((ret = add_extended_prefix(ppath_w)) < 0) {
            av_freep(ppath_w);
            ফেরত ret;
        }
    }

    ফেরত 0;
}

#endif

#endif /* AVUTIL_WCHAR_FILENAME_H */
