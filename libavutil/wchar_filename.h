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

#அந்தர்பாவ <errno.h>
#அந்தர்பாவ <stddef.h>
#அந்தர்பாவ <windows.h>
#அந்தர்பாவ "mem.h"

av_warn_unused_result
நிலையான உள்வரி முழு utf8towchar(மாறிலி எழுத்து *filename_utf8, wchar_t **filename_w)
{
    முழு இலக்கம்_chars;
    இலக்கம்_chars = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, filename_utf8, -1, வெற்று, 0);
    எனில் (இலக்கம்_chars <= 0) {
        *filename_w = வெற்று;
        errno = EINVAL;
        திரும்பு -1;
    }
    *filename_w = (wchar_t *)av_calloc(இலக்கம்_chars, அளவு(wchar_t));
    எனில் (!*filename_w) {
        errno = ENOMEM;
        திரும்பு -1;
    }
    MultiByteToWideChar(CP_UTF8, 0, filename_utf8, -1, *filename_w, இலக்கம்_chars);
    திரும்பு 0;
}

av_warn_unused_result
நிலையான உள்வரி முழு wchartocp(unsigned முழு code_page, மாறிலி wchar_t *filename_w,
                            எழுத்து **filename)
{
    DWORD flags = code_page == CP_UTF8 ? WC_ERR_INVALID_CHARS : 0;
    முழு இலக்கம்_chars = WideCharToMultiByte(code_page, flags, filename_w, -1,
                                        வெற்று, 0, வெற்று, வெற்று);
    எனில் (இலக்கம்_chars <= 0) {
        *filename = வெற்று;
        errno = EINVAL;
        திரும்பு -1;
    }
    *filename = (எழுத்து *)av_malloc_array(இலக்கம்_chars, அளவு **filename);
    எனில் (!*filename) {
        errno = ENOMEM;
        திரும்பு -1;
    }
    WideCharToMultiByte(code_page, flags, filename_w, -1,
                        *filename, இலக்கம்_chars, வெற்று, வெற்று);
    திரும்பு 0;
}

av_warn_unused_result
நிலையான உள்வரி முழு wchartoutf8(மாறிலி wchar_t *filename_w, எழுத்து **filename)
{
    திரும்பு wchartocp(CP_UTF8, filename_w, filename);
}

av_warn_unused_result
நிலையான உள்வரி முழு wchartoansi(மாறிலி wchar_t *filename_w, எழுத்து **filename)
{
    திரும்பு wchartocp(CP_ACP, filename_w, filename);
}

av_warn_unused_result
நிலையான உள்வரி முழு utf8toansi(மாறிலி எழுத்து *filename_utf8, எழுத்து **filename)
{
    wchar_t *filename_w = வெற்று;
    முழு ret = -1;
    எனில் (utf8towchar(filename_utf8, &filename_w))
        திரும்பு -1;

    எனில் (!filename_w) {
        *filename = வெற்று;
        திரும்பு 0;
    }

    ret = wchartoansi(filename_w, filename);
    av_free(filename_w);
    திரும்பு ret;
}

/**
 * Checks for extended path prefixes for which normalization needs to be skipped.
 * see .NET6: PathInternal.IsExtended()
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L165
 */
நிலையான உள்வரி முழு path_is_extended(மாறிலி wchar_t *path)
{
    எனில் (path[0] == L'\\' && (path[1] == L'\\' || path[1] == L'?') && path[2] == L'?' && path[3] == L'\\')
        திரும்பு 1;

    திரும்பு 0;
}

/**
 * Checks for a device path prefix.
 * see .NET6: PathInternal.IsDevice()
 * we don't check forward slashes and extended paths (as already done)
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L132
 */
நிலையான உள்வரி முழு path_is_device_path(மாறிலி wchar_t *path)
{
    எனில் (path[0] == L'\\' && path[1] == L'\\' && path[2] == L'.' && path[3] == L'\\')
        திரும்பு 1;

    திரும்பு 0;
}

/**
 * Performs path normalization by calling GetFullPathNameW().
 * see .NET6: PathHelper.GetFullPathName()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L70
 */
நிலையான உள்வரி முழு get_full_path_name(wchar_t **ppath_w)
{
    முழு இலக்கம்_chars;
    wchar_t *temp_w;

    இலக்கம்_chars = GetFullPathNameW(*ppath_w, 0, வெற்று, வெற்று);
    எனில் (இலக்கம்_chars <= 0) {
        errno = EINVAL;
        திரும்பு -1;
    }

    temp_w = (wchar_t *)av_calloc(இலக்கம்_chars, அளவு(wchar_t));
    எனில் (!temp_w) {
        errno = ENOMEM;
        திரும்பு -1;
    }

    இலக்கம்_chars = GetFullPathNameW(*ppath_w, இலக்கம்_chars, temp_w, வெற்று);
    எனில் (இலக்கம்_chars <= 0) {
        av_free(temp_w);
        errno = EINVAL;
        திரும்பு -1;
    }

    av_freep(ppath_w);
    *ppath_w = temp_w;

    திரும்பு 0;
}

/**
 * Normalizes a Windows file or folder path.
 * Expansion of short paths (with 8.3 path components) is currently omitted
 * as it is not required for accessing long paths.
 * see .NET6: PathHelper.Normalize()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L25
 */
நிலையான உள்வரி முழு path_normalize(wchar_t **ppath_w)
{
    முழு ret;

    எனில் ((ret = get_full_path_name(ppath_w)) < 0)
        திரும்பு ret;

    /* What .NET does at this point is to call PathHelper.TryExpandShortFileName()
     * in case the path contains a '~' character.
     * We don't need to do this as we don't need to normalize the file name
     * for presentation, and the extended path prefix works with 8.3 path
     * components as well
     */
    திரும்பு 0;
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
நிலையான உள்வரி முழு add_extended_prefix(wchar_t **ppath_w)
{
    மாறிலி wchar_t *unc_prefix           = L"\\\\?\\UNC\\";
    மாறிலி wchar_t *extended_path_prefix = L"\\\\?\\";
    மாறிலி wchar_t *path_w               = *ppath_w;
    மாறிலி size_t len                    = wcslen(path_w);
    wchar_t *temp_w;

    /* We're skipping the check IsPartiallyQualified() because
     * we expect to have called GetFullPathNameW() already. */
    எனில் (len < 2 || path_is_extended(*ppath_w) || path_is_device_path(*ppath_w)) {
        திரும்பு 0;
    }

    எனில் (path_w[0] == L'\\' && path_w[1] == L'\\') {
        /* unc_prefix length is 8 plus 1 for terminating zeros,
         * we subtract 2 for the leading '\\' of the original path */
        temp_w = (wchar_t *)av_calloc(len - 2 + 8 + 1, அளவு(wchar_t));
        எனில் (!temp_w) {
            errno = ENOMEM;
            திரும்பு -1;
        }
        wcscpy(temp_w, unc_prefix);
        wcscat(temp_w, path_w + 2);
    } இல்லையெனில் {
        // The length of extended_path_prefix is 4 plus 1 for terminating zeros
        temp_w = (wchar_t *)av_calloc(len + 4 + 1, அளவு(wchar_t));
        எனில் (!temp_w) {
            errno = ENOMEM;
            திரும்பு -1;
        }
        wcscpy(temp_w, extended_path_prefix);
        wcscat(temp_w, path_w);
    }

    av_freep(ppath_w);
    *ppath_w = temp_w;

    திரும்பு 0;
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
நிலையான உள்வரி முழு get_extended_win32_path(மாறிலி எழுத்து *path, wchar_t **ppath_w)
{
    முழு ret;
    size_t len;

    எனில் ((ret = utf8towchar(path, ppath_w)) < 0)
        திரும்பு ret;

    எனில் (path_is_extended(*ppath_w)) {
        /* Paths prefixed with '\\?\' or \??\' are considered normalized by definition.
         * Windows doesn't normalize those paths and neither should we.
         */
        திரும்பு 0;
    }

    எனில் ((ret = path_normalize(ppath_w)) < 0) {
        av_freep(ppath_w);
        திரும்பு ret;
    }

    /* see .NET6: PathInternal.EnsureExtendedPrefixIfNeeded()
     * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L92
     */
    len = wcslen(*ppath_w);
    எனில் (len >= MAX_PATH) {
        எனில் ((ret = add_extended_prefix(ppath_w)) < 0) {
            av_freep(ppath_w);
            திரும்பு ret;
        }
    }

    திரும்பு 0;
}

#endif

#endif /* AVUTIL_WCHAR_FILENAME_H */
