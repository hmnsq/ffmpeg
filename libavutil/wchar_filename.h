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

#અન્તર્ભાવ <errno.h>
#અન્તર્ભાવ <stddef.h>
#અન્તર્ભાવ <windows.h>
#અન્તર્ભાવ "mem.h"

av_warn_unused_result
સ્થિર અંતઃરેખ પૂર્ણાંક utf8towchar(અચલ અક્ષર *filename_utf8, wchar_t **filename_w)
{
    પૂર્ણાંક અંક_chars;
    અંક_chars = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, filename_utf8, -1, ખાલી, 0);
    જો (અંક_chars <= 0) {
        *filename_w = ખાલી;
        errno = EINVAL;
        પાછા -1;
    }
    *filename_w = (wchar_t *)av_calloc(અંક_chars, કદ(wchar_t));
    જો (!*filename_w) {
        errno = ENOMEM;
        પાછા -1;
    }
    MultiByteToWideChar(CP_UTF8, 0, filename_utf8, -1, *filename_w, અંક_chars);
    પાછા 0;
}

av_warn_unused_result
સ્થિર અંતઃરેખ પૂર્ણાંક wchartocp(unsigned પૂર્ણાંક code_page, અચલ wchar_t *filename_w,
                            અક્ષર **filename)
{
    DWORD flags = code_page == CP_UTF8 ? WC_ERR_INVALID_CHARS : 0;
    પૂર્ણાંક અંક_chars = WideCharToMultiByte(code_page, flags, filename_w, -1,
                                        ખાલી, 0, ખાલી, ખાલી);
    જો (અંક_chars <= 0) {
        *filename = ખાલી;
        errno = EINVAL;
        પાછા -1;
    }
    *filename = (અક્ષર *)av_malloc_array(અંક_chars, કદ **filename);
    જો (!*filename) {
        errno = ENOMEM;
        પાછા -1;
    }
    WideCharToMultiByte(code_page, flags, filename_w, -1,
                        *filename, અંક_chars, ખાલી, ખાલી);
    પાછા 0;
}

av_warn_unused_result
સ્થિર અંતઃરેખ પૂર્ણાંક wchartoutf8(અચલ wchar_t *filename_w, અક્ષર **filename)
{
    પાછા wchartocp(CP_UTF8, filename_w, filename);
}

av_warn_unused_result
સ્થિર અંતઃરેખ પૂર્ણાંક wchartoansi(અચલ wchar_t *filename_w, અક્ષર **filename)
{
    પાછા wchartocp(CP_ACP, filename_w, filename);
}

av_warn_unused_result
સ્થિર અંતઃરેખ પૂર્ણાંક utf8toansi(અચલ અક્ષર *filename_utf8, અક્ષર **filename)
{
    wchar_t *filename_w = ખાલી;
    પૂર્ણાંક ret = -1;
    જો (utf8towchar(filename_utf8, &filename_w))
        પાછા -1;

    જો (!filename_w) {
        *filename = ખાલી;
        પાછા 0;
    }

    ret = wchartoansi(filename_w, filename);
    av_free(filename_w);
    પાછા ret;
}

/**
 * Checks for extended path prefixes for which normalization needs to be skipped.
 * see .NET6: PathInternal.IsExtended()
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L165
 */
સ્થિર અંતઃરેખ પૂર્ણાંક path_is_extended(અચલ wchar_t *path)
{
    જો (path[0] == L'\\' && (path[1] == L'\\' || path[1] == L'?') && path[2] == L'?' && path[3] == L'\\')
        પાછા 1;

    પાછા 0;
}

/**
 * Checks for a device path prefix.
 * see .NET6: PathInternal.IsDevice()
 * we don't check forward slashes and extended paths (as already done)
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L132
 */
સ્થિર અંતઃરેખ પૂર્ણાંક path_is_device_path(અચલ wchar_t *path)
{
    જો (path[0] == L'\\' && path[1] == L'\\' && path[2] == L'.' && path[3] == L'\\')
        પાછા 1;

    પાછા 0;
}

/**
 * Performs path normalization by calling GetFullPathNameW().
 * see .NET6: PathHelper.GetFullPathName()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L70
 */
સ્થિર અંતઃરેખ પૂર્ણાંક get_full_path_name(wchar_t **ppath_w)
{
    પૂર્ણાંક અંક_chars;
    wchar_t *temp_w;

    અંક_chars = GetFullPathNameW(*ppath_w, 0, ખાલી, ખાલી);
    જો (અંક_chars <= 0) {
        errno = EINVAL;
        પાછા -1;
    }

    temp_w = (wchar_t *)av_calloc(અંક_chars, કદ(wchar_t));
    જો (!temp_w) {
        errno = ENOMEM;
        પાછા -1;
    }

    અંક_chars = GetFullPathNameW(*ppath_w, અંક_chars, temp_w, ખાલી);
    જો (અંક_chars <= 0) {
        av_free(temp_w);
        errno = EINVAL;
        પાછા -1;
    }

    av_freep(ppath_w);
    *ppath_w = temp_w;

    પાછા 0;
}

/**
 * Normalizes a Windows file or folder path.
 * Expansion of short paths (with 8.3 path components) is currently omitted
 * as it is not required for accessing long paths.
 * see .NET6: PathHelper.Normalize()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L25
 */
સ્થિર અંતઃરેખ પૂર્ણાંક path_normalize(wchar_t **ppath_w)
{
    પૂર્ણાંક ret;

    જો ((ret = get_full_path_name(ppath_w)) < 0)
        પાછા ret;

    /* What .NET does at this point is to call PathHelper.TryExpandShortFileName()
     * in case the path contains a '~' character.
     * We don't need to do this as we don't need to normalize the file name
     * for presentation, and the extended path prefix works with 8.3 path
     * components as well
     */
    પાછા 0;
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
સ્થિર અંતઃરેખ પૂર્ણાંક add_extended_prefix(wchar_t **ppath_w)
{
    અચલ wchar_t *unc_prefix           = L"\\\\?\\UNC\\";
    અચલ wchar_t *extended_path_prefix = L"\\\\?\\";
    અચલ wchar_t *path_w               = *ppath_w;
    અચલ size_t len                    = wcslen(path_w);
    wchar_t *temp_w;

    /* We're skipping the check IsPartiallyQualified() because
     * we expect to have called GetFullPathNameW() already. */
    જો (len < 2 || path_is_extended(*ppath_w) || path_is_device_path(*ppath_w)) {
        પાછા 0;
    }

    જો (path_w[0] == L'\\' && path_w[1] == L'\\') {
        /* unc_prefix length is 8 plus 1 for terminating zeros,
         * we subtract 2 for the leading '\\' of the original path */
        temp_w = (wchar_t *)av_calloc(len - 2 + 8 + 1, કદ(wchar_t));
        જો (!temp_w) {
            errno = ENOMEM;
            પાછા -1;
        }
        wcscpy(temp_w, unc_prefix);
        wcscat(temp_w, path_w + 2);
    } નહીંતર {
        // The length of extended_path_prefix is 4 plus 1 for terminating zeros
        temp_w = (wchar_t *)av_calloc(len + 4 + 1, કદ(wchar_t));
        જો (!temp_w) {
            errno = ENOMEM;
            પાછા -1;
        }
        wcscpy(temp_w, extended_path_prefix);
        wcscat(temp_w, path_w);
    }

    av_freep(ppath_w);
    *ppath_w = temp_w;

    પાછા 0;
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
સ્થિર અંતઃરેખ પૂર્ણાંક get_extended_win32_path(અચલ અક્ષર *path, wchar_t **ppath_w)
{
    પૂર્ણાંક ret;
    size_t len;

    જો ((ret = utf8towchar(path, ppath_w)) < 0)
        પાછા ret;

    જો (path_is_extended(*ppath_w)) {
        /* Paths prefixed with '\\?\' or \??\' are considered normalized by definition.
         * Windows doesn't normalize those paths and neither should we.
         */
        પાછા 0;
    }

    જો ((ret = path_normalize(ppath_w)) < 0) {
        av_freep(ppath_w);
        પાછા ret;
    }

    /* see .NET6: PathInternal.EnsureExtendedPrefixIfNeeded()
     * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L92
     */
    len = wcslen(*ppath_w);
    જો (len >= MAX_PATH) {
        જો ((ret = add_extended_prefix(ppath_w)) < 0) {
            av_freep(ppath_w);
            પાછા ret;
        }
    }

    પાછા 0;
}

#endif

#endif /* AVUTIL_WCHAR_FILENAME_H */
