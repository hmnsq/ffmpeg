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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_WCHAR_FILENAME_H
#وصف_ڪريو AVUTIL_WCHAR_FILENAME_H

#جيڪڏهن_وصف_ٿيل _WIN32

#ضمن <errno.h>
#ضمن <stddef.h>
#ضمن <windows.h>
#ضمن "mem.h"

av_warn_اڻ_استعمال_ٿيل_نتيجو
ساكن مضمن صحيح utf8towchar(ثابت حرف *filename_utf8, wchar_t **filename_w)
{
    صحيح انگ_chars;
    انگ_chars = Multi_Byte_منزل_Wide_Char(CP_UTF8, MB_ERR_INVALID_CHARS, filename_utf8, -1, عدم, 0);
    إذا (انگ_chars <= 0) {
        *filename_w = عدم;
        errno = EINVAL;
        أرجع -1;
    }
    *filename_w = (wchar_t *)av_calloc(انگ_chars, حجم(wchar_t));
    إذا (!*filename_w) {
        errno = ENOMEM;
        أرجع -1;
    }
    Multi_Byte_منزل_Wide_Char(CP_UTF8, 0, filename_utf8, -1, *filename_w, انگ_chars);
    أرجع 0;
}

av_warn_اڻ_استعمال_ٿيل_نتيجو
ساكن مضمن صحيح wchartocp(بنانشان صحيح ڪوڊ_صفحو, ثابت wchar_t *filename_w,
                            حرف **filename)
{
    DWORD flags = ڪوڊ_صفحو == CP_UTF8 ? WC_ERR_INVALID_CHARS : 0;
    صحيح انگ_chars = Wide_Char_منزل_Multi_Byte(ڪوڊ_صفحو, flags, filename_w, -1,
                                        عدم, 0, عدم, عدم);
    إذا (انگ_chars <= 0) {
        *filename = عدم;
        errno = EINVAL;
        أرجع -1;
    }
    *filename = (حرف *)av_malloc_array(انگ_chars, حجم **filename);
    إذا (!*filename) {
        errno = ENOMEM;
        أرجع -1;
    }
    Wide_Char_منزل_Multi_Byte(ڪوڊ_صفحو, flags, filename_w, -1,
                        *filename, انگ_chars, عدم, عدم);
    أرجع 0;
}

av_warn_اڻ_استعمال_ٿيل_نتيجو
ساكن مضمن صحيح wchartoutf8(ثابت wchar_t *filename_w, حرف **filename)
{
    أرجع wchartocp(CP_UTF8, filename_w, filename);
}

av_warn_اڻ_استعمال_ٿيل_نتيجو
ساكن مضمن صحيح wchartoansi(ثابت wchar_t *filename_w, حرف **filename)
{
    أرجع wchartocp(CP_ACP, filename_w, filename);
}

av_warn_اڻ_استعمال_ٿيل_نتيجو
ساكن مضمن صحيح utf8toansi(ثابت حرف *filename_utf8, حرف **filename)
{
    wchar_t *filename_w = عدم;
    صحيح ret = -1;
    إذا (utf8towchar(filename_utf8, &filename_w))
        أرجع -1;

    إذا (!filename_w) {
        *filename = عدم;
        أرجع 0;
    }

    ret = wchartoansi(filename_w, filename);
    av_free(filename_w);
    أرجع ret;
}

/**
 * Checks for extended path prefixes for which normalization needs to be skipped.
 * see .NET6: PathInternal.IsExtended()
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L165
 */
ساكن مضمن صحيح رستو_is_extended(ثابت wchar_t *رستو)
{
    إذا (رستو[0] == L'\\' && (رستو[1] == L'\\' || رستو[1] == L'?') && رستو[2] == L'?' && رستو[3] == L'\\')
        أرجع 1;

    أرجع 0;
}

/**
 * Checks for a device path prefix.
 * see .NET6: PathInternal.IsDevice()
 * we don't check forward slashes and extended paths (as already done)
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L132
 */
ساكن مضمن صحيح رستو_is_device_رستو(ثابت wchar_t *رستو)
{
    إذا (رستو[0] == L'\\' && رستو[1] == L'\\' && رستو[2] == L'.' && رستو[3] == L'\\')
        أرجع 1;

    أرجع 0;
}

/**
 * Performs path normalization by calling GetFullPathNameW().
 * see .NET6: PathHelper.GetFullPathName()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L70
 */
ساكن مضمن صحيح get_ڀريل_رستو_name(wchar_t **ppath_w)
{
    صحيح انگ_chars;
    wchar_t *عارضي_w;

    انگ_chars = Get_ڀريل_رستو_Name_W(*ppath_w, 0, عدم, عدم);
    إذا (انگ_chars <= 0) {
        errno = EINVAL;
        أرجع -1;
    }

    عارضي_w = (wchar_t *)av_calloc(انگ_chars, حجم(wchar_t));
    إذا (!عارضي_w) {
        errno = ENOMEM;
        أرجع -1;
    }

    انگ_chars = Get_ڀريل_رستو_Name_W(*ppath_w, انگ_chars, عارضي_w, عدم);
    إذا (انگ_chars <= 0) {
        av_free(عارضي_w);
        errno = EINVAL;
        أرجع -1;
    }

    av_freep(ppath_w);
    *ppath_w = عارضي_w;

    أرجع 0;
}

/**
 * Normalizes a Windows file or folder path.
 * Expansion of short paths (with 8.3 path components) is currently omitted
 * as it is not required for accessing long paths.
 * see .NET6: PathHelper.Normalize()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L25
 */
ساكن مضمن صحيح رستو_normalize(wchar_t **ppath_w)
{
    صحيح ret;

    إذا ((ret = get_ڀريل_رستو_name(ppath_w)) < 0)
        أرجع ret;

    /* What .NET does at this point is to call PathHelper.TryExpandShortFileName()
     * in case the path contains a '~' character.
     * We don't need to do this as we don't need to normalize the file name
     * for presentation, and the extended path prefix works with 8.3 path
     * components as well
     */
    أرجع 0;
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
ساكن مضمن صحيح جوڙيو_extended_اڳياڙي(wchar_t **ppath_w)
{
    ثابت wchar_t *unc_اڳياڙي           = L"\\\\?\\UNC\\";
    ثابت wchar_t *extended_رستو_اڳياڙي = L"\\\\?\\";
    ثابت wchar_t *رستو_w               = *ppath_w;
    ثابت size_t len                    = wcslen(رستو_w);
    wchar_t *عارضي_w;

    /* We're skipping the check IsPartiallyQualified() because
     * we expect to have called GetFullPathNameW() already. */
    إذا (len < 2 || رستو_is_extended(*ppath_w) || رستو_is_device_رستو(*ppath_w)) {
        أرجع 0;
    }

    إذا (رستو_w[0] == L'\\' && رستو_w[1] == L'\\') {
        /* unc_prefix length is 8 plus 1 for terminating zeros,
         * we subtract 2 for the leading '\\' of the original path */
        عارضي_w = (wchar_t *)av_calloc(len - 2 + 8 + 1, حجم(wchar_t));
        إذا (!عارضي_w) {
            errno = ENOMEM;
            أرجع -1;
        }
        wcscpy(عارضي_w, unc_اڳياڙي);
        wcscat(عارضي_w, رستو_w + 2);
    } وإلا {
        // The length of extended_path_prefix is 4 plus 1 for terminating zeros
        عارضي_w = (wchar_t *)av_calloc(len + 4 + 1, حجم(wchar_t));
        إذا (!عارضي_w) {
            errno = ENOMEM;
            أرجع -1;
        }
        wcscpy(عارضي_w, extended_رستو_اڳياڙي);
        wcscat(عارضي_w, رستو_w);
    }

    av_freep(ppath_w);
    *ppath_w = عارضي_w;

    أرجع 0;
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
ساكن مضمن صحيح get_extended_win32_رستو(ثابت حرف *رستو, wchar_t **ppath_w)
{
    صحيح ret;
    size_t len;

    إذا ((ret = utf8towchar(رستو, ppath_w)) < 0)
        أرجع ret;

    إذا (رستو_is_extended(*ppath_w)) {
        /* Paths prefixed with '\\?\' or \??\' are considered normalized by definition.
         * Windows doesn't normalize those paths and neither should we.
         */
        أرجع 0;
    }

    إذا ((ret = رستو_normalize(ppath_w)) < 0) {
        av_freep(ppath_w);
        أرجع ret;
    }

    /* see .NET6: PathInternal.EnsureExtendedPrefixIfNeeded()
     * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L92
     */
    len = wcslen(*ppath_w);
    إذا (len >= MAX_رستو) {
        إذا ((ret = جوڙيو_extended_اڳياڙي(ppath_w)) < 0) {
            av_freep(ppath_w);
            أرجع ret;
        }
    }

    أرجع 0;
}

#جيڪڏهن_پورو

#جيڪڏهن_پورو /* AVUTIL_WCHAR_FILENAME_H */
