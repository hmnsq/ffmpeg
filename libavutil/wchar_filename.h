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

#اگر_تعریف_نشده AVUTIL_WCHAR_FILENAME_H
#تعریف_کن AVUTIL_WCHAR_FILENAME_H

#اگر_تعریف_شده _WIN32

#ضمن <errno.h>
#ضمن <stddef.h>
#ضمن <windows.h>
#ضمن "mem.h"

av_warn_استفادهنشده_نتیجه
ساكن مضمن صحيح utf8towchar(ثابت حرف *filename_utf8, wchar_t **filename_w)
{
    صحيح رقم_chars;
    رقم_chars = Multi_Byte_مقصد_Wide_Char(CP_UTF8, MB_ERR_INVALID_CHARS, filename_utf8, -1, عدم, 0);
    إذا (رقم_chars <= 0) {
        *filename_w = عدم;
        errno = EINVAL;
        أرجع -1;
    }
    *filename_w = (wchar_t *)av_calloc(رقم_chars, حجم(wchar_t));
    إذا (!*filename_w) {
        errno = ENOMEM;
        أرجع -1;
    }
    Multi_Byte_مقصد_Wide_Char(CP_UTF8, 0, filename_utf8, -1, *filename_w, رقم_chars);
    أرجع 0;
}

av_warn_استفادهنشده_نتیجه
ساكن مضمن صحيح wchartocp(بیعلامت صحيح کد_صفحه, ثابت wchar_t *filename_w,
                            حرف **filename)
{
    DWORD flags = کد_صفحه == CP_UTF8 ? WC_ERR_INVALID_CHARS : 0;
    صحيح رقم_chars = Wide_Char_مقصد_Multi_Byte(کد_صفحه, flags, filename_w, -1,
                                        عدم, 0, عدم, عدم);
    إذا (رقم_chars <= 0) {
        *filename = عدم;
        errno = EINVAL;
        أرجع -1;
    }
    *filename = (حرف *)av_malloc_array(رقم_chars, حجم **filename);
    إذا (!*filename) {
        errno = ENOMEM;
        أرجع -1;
    }
    Wide_Char_مقصد_Multi_Byte(کد_صفحه, flags, filename_w, -1,
                        *filename, رقم_chars, عدم, عدم);
    أرجع 0;
}

av_warn_استفادهنشده_نتیجه
ساكن مضمن صحيح wchartoutf8(ثابت wchar_t *filename_w, حرف **filename)
{
    أرجع wchartocp(CP_UTF8, filename_w, filename);
}

av_warn_استفادهنشده_نتیجه
ساكن مضمن صحيح wchartoansi(ثابت wchar_t *filename_w, حرف **filename)
{
    أرجع wchartocp(CP_ACP, filename_w, filename);
}

av_warn_استفادهنشده_نتیجه
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
ساكن مضمن صحيح مسیر_is_extended(ثابت wchar_t *مسیر)
{
    إذا (مسیر[0] == L'\\' && (مسیر[1] == L'\\' || مسیر[1] == L'?') && مسیر[2] == L'?' && مسیر[3] == L'\\')
        أرجع 1;

    أرجع 0;
}

/**
 * Checks for a device path prefix.
 * see .NET6: PathInternal.IsDevice()
 * we don't check forward slashes and extended paths (as already done)
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L132
 */
ساكن مضمن صحيح مسیر_is_device_مسیر(ثابت wchar_t *مسیر)
{
    إذا (مسیر[0] == L'\\' && مسیر[1] == L'\\' && مسیر[2] == L'.' && مسیر[3] == L'\\')
        أرجع 1;

    أرجع 0;
}

/**
 * Performs path normalization by calling GetFullPathNameW().
 * see .NET6: PathHelper.GetFullPathName()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L70
 */
ساكن مضمن صحيح get_پر_مسیر_name(wchar_t **ppath_w)
{
    صحيح رقم_chars;
    wchar_t *موقت_w;

    رقم_chars = Get_پر_مسیر_Name_W(*ppath_w, 0, عدم, عدم);
    إذا (رقم_chars <= 0) {
        errno = EINVAL;
        أرجع -1;
    }

    موقت_w = (wchar_t *)av_calloc(رقم_chars, حجم(wchar_t));
    إذا (!موقت_w) {
        errno = ENOMEM;
        أرجع -1;
    }

    رقم_chars = Get_پر_مسیر_Name_W(*ppath_w, رقم_chars, موقت_w, عدم);
    إذا (رقم_chars <= 0) {
        av_free(موقت_w);
        errno = EINVAL;
        أرجع -1;
    }

    av_freep(ppath_w);
    *ppath_w = موقت_w;

    أرجع 0;
}

/**
 * Normalizes a Windows file or folder path.
 * Expansion of short paths (with 8.3 path components) is currently omitted
 * as it is not required for accessing long paths.
 * see .NET6: PathHelper.Normalize()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L25
 */
ساكن مضمن صحيح مسیر_normalize(wchar_t **ppath_w)
{
    صحيح ret;

    إذا ((ret = get_پر_مسیر_name(ppath_w)) < 0)
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
ساكن مضمن صحيح جمع_کن_extended_پیشوند(wchar_t **ppath_w)
{
    ثابت wchar_t *unc_پیشوند           = L"\\\\?\\UNC\\";
    ثابت wchar_t *extended_مسیر_پیشوند = L"\\\\?\\";
    ثابت wchar_t *مسیر_w               = *ppath_w;
    ثابت size_t len                    = wcslen(مسیر_w);
    wchar_t *موقت_w;

    /* We're skipping the check IsPartiallyQualified() because
     * we expect to have called GetFullPathNameW() already. */
    إذا (len < 2 || مسیر_is_extended(*ppath_w) || مسیر_is_device_مسیر(*ppath_w)) {
        أرجع 0;
    }

    إذا (مسیر_w[0] == L'\\' && مسیر_w[1] == L'\\') {
        /* unc_prefix length is 8 plus 1 for terminating zeros,
         * we subtract 2 for the leading '\\' of the original path */
        موقت_w = (wchar_t *)av_calloc(len - 2 + 8 + 1, حجم(wchar_t));
        إذا (!موقت_w) {
            errno = ENOMEM;
            أرجع -1;
        }
        wcscpy(موقت_w, unc_پیشوند);
        wcscat(موقت_w, مسیر_w + 2);
    } وإلا {
        // The length of extended_path_prefix is 4 plus 1 for terminating zeros
        موقت_w = (wchar_t *)av_calloc(len + 4 + 1, حجم(wchar_t));
        إذا (!موقت_w) {
            errno = ENOMEM;
            أرجع -1;
        }
        wcscpy(موقت_w, extended_مسیر_پیشوند);
        wcscat(موقت_w, مسیر_w);
    }

    av_freep(ppath_w);
    *ppath_w = موقت_w;

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
ساكن مضمن صحيح get_extended_win32_مسیر(ثابت حرف *مسیر, wchar_t **ppath_w)
{
    صحيح ret;
    size_t len;

    إذا ((ret = utf8towchar(مسیر, ppath_w)) < 0)
        أرجع ret;

    إذا (مسیر_is_extended(*ppath_w)) {
        /* Paths prefixed with '\\?\' or \??\' are considered normalized by definition.
         * Windows doesn't normalize those paths and neither should we.
         */
        أرجع 0;
    }

    إذا ((ret = مسیر_normalize(ppath_w)) < 0) {
        av_freep(ppath_w);
        أرجع ret;
    }

    /* see .NET6: PathInternal.EnsureExtendedPrefixIfNeeded()
     * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L92
     */
    len = wcslen(*ppath_w);
    إذا (len >= MAX_مسیر) {
        إذا ((ret = جمع_کن_extended_پیشوند(ppath_w)) < 0) {
            av_freep(ppath_w);
            أرجع ret;
        }
    }

    أرجع 0;
}

#پایان_اگر

#پایان_اگر /* AVUTIL_WCHAR_FILENAME_H */
