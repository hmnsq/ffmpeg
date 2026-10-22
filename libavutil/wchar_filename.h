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

#اگر_غیر_تعریف_شدہ AVUTIL_WCHAR_FILENAME_H
#تعریف_کرو AVUTIL_WCHAR_FILENAME_H

#اگر_تعریف_شدہ _WIN32

#شامل <errno.h>
#شامل <stddef.h>
#شامل <windows.h>
#شامل "mem.h"

av_warn_غیر_مستعمل_نتیجہ
ساکن اندرونی صحیح utf8towchar(ثابت حرف *filename_utf8, wchar_t **filename_w)
{
    صحیح عدد_chars;
    عدد_chars = Multi_Byte_مقصد_Wide_Char(CP_UTF8, MB_ERR_INVALID_CHARS, filename_utf8, -1, تہی, 0);
    اگر (عدد_chars <= 0) {
        *filename_w = تہی;
        errno = EINVAL;
        واپس -1;
    }
    *filename_w = (wchar_t *)av_calloc(عدد_chars, حجم(wchar_t));
    اگر (!*filename_w) {
        errno = ENOMEM;
        واپس -1;
    }
    Multi_Byte_مقصد_Wide_Char(CP_UTF8, 0, filename_utf8, -1, *filename_w, عدد_chars);
    واپس 0;
}

av_warn_غیر_مستعمل_نتیجہ
ساکن اندرونی صحیح wchartocp(غیرعلامتی صحیح رمز_صفحہ, ثابت wchar_t *filename_w,
                            حرف **filename)
{
    DWORD flags = رمز_صفحہ == CP_UTF8 ? WC_ERR_INVALID_CHARS : 0;
    صحیح عدد_chars = Wide_Char_مقصد_Multi_Byte(رمز_صفحہ, flags, filename_w, -1,
                                        تہی, 0, تہی, تہی);
    اگر (عدد_chars <= 0) {
        *filename = تہی;
        errno = EINVAL;
        واپس -1;
    }
    *filename = (حرف *)av_malloc_array(عدد_chars, حجم **filename);
    اگر (!*filename) {
        errno = ENOMEM;
        واپس -1;
    }
    Wide_Char_مقصد_Multi_Byte(رمز_صفحہ, flags, filename_w, -1,
                        *filename, عدد_chars, تہی, تہی);
    واپس 0;
}

av_warn_غیر_مستعمل_نتیجہ
ساکن اندرونی صحیح wchartoutf8(ثابت wchar_t *filename_w, حرف **filename)
{
    واپس wchartocp(CP_UTF8, filename_w, filename);
}

av_warn_غیر_مستعمل_نتیجہ
ساکن اندرونی صحیح wchartoansi(ثابت wchar_t *filename_w, حرف **filename)
{
    واپس wchartocp(CP_ACP, filename_w, filename);
}

av_warn_غیر_مستعمل_نتیجہ
ساکن اندرونی صحیح utf8toansi(ثابت حرف *filename_utf8, حرف **filename)
{
    wchar_t *filename_w = تہی;
    صحیح ret = -1;
    اگر (utf8towchar(filename_utf8, &filename_w))
        واپس -1;

    اگر (!filename_w) {
        *filename = تہی;
        واپس 0;
    }

    ret = wchartoansi(filename_w, filename);
    av_free(filename_w);
    واپس ret;
}

/**
 * Checks for extended path prefixes for which normalization needs to be skipped.
 * see .NET6: PathInternal.IsExtended()
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L165
 */
ساکن اندرونی صحیح راستہ_is_extended(ثابت wchar_t *راستہ)
{
    اگر (راستہ[0] == L'\\' && (راستہ[1] == L'\\' || راستہ[1] == L'?') && راستہ[2] == L'?' && راستہ[3] == L'\\')
        واپس 1;

    واپس 0;
}

/**
 * Checks for a device path prefix.
 * see .NET6: PathInternal.IsDevice()
 * we don't check forward slashes and extended paths (as already done)
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L132
 */
ساکن اندرونی صحیح راستہ_is_device_راستہ(ثابت wchar_t *راستہ)
{
    اگر (راستہ[0] == L'\\' && راستہ[1] == L'\\' && راستہ[2] == L'.' && راستہ[3] == L'\\')
        واپس 1;

    واپس 0;
}

/**
 * Performs path normalization by calling GetFullPathNameW().
 * see .NET6: PathHelper.GetFullPathName()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L70
 */
ساکن اندرونی صحیح get_بھرا_راستہ_name(wchar_t **ppath_w)
{
    صحیح عدد_chars;
    wchar_t *عارضی_w;

    عدد_chars = Get_بھرا_راستہ_Name_W(*ppath_w, 0, تہی, تہی);
    اگر (عدد_chars <= 0) {
        errno = EINVAL;
        واپس -1;
    }

    عارضی_w = (wchar_t *)av_calloc(عدد_chars, حجم(wchar_t));
    اگر (!عارضی_w) {
        errno = ENOMEM;
        واپس -1;
    }

    عدد_chars = Get_بھرا_راستہ_Name_W(*ppath_w, عدد_chars, عارضی_w, تہی);
    اگر (عدد_chars <= 0) {
        av_free(عارضی_w);
        errno = EINVAL;
        واپس -1;
    }

    av_freep(ppath_w);
    *ppath_w = عارضی_w;

    واپس 0;
}

/**
 * Normalizes a Windows file or folder path.
 * Expansion of short paths (with 8.3 path components) is currently omitted
 * as it is not required for accessing long paths.
 * see .NET6: PathHelper.Normalize()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L25
 */
ساکن اندرونی صحیح راستہ_normalize(wchar_t **ppath_w)
{
    صحیح ret;

    اگر ((ret = get_بھرا_راستہ_name(ppath_w)) < 0)
        واپس ret;

    /* What .NET does at this point is to call PathHelper.TryExpandShortFileName()
     * in case the path contains a '~' character.
     * We don't need to do this as we don't need to normalize the file name
     * for presentation, and the extended path prefix works with 8.3 path
     * components as well
     */
    واپس 0;
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
ساکن اندرونی صحیح جوڑو_extended_سابقہ(wchar_t **ppath_w)
{
    ثابت wchar_t *unc_سابقہ           = L"\\\\?\\UNC\\";
    ثابت wchar_t *extended_راستہ_سابقہ = L"\\\\?\\";
    ثابت wchar_t *راستہ_w               = *ppath_w;
    ثابت size_t len                    = wcslen(راستہ_w);
    wchar_t *عارضی_w;

    /* We're skipping the check IsPartiallyQualified() because
     * we expect to have called GetFullPathNameW() already. */
    اگر (len < 2 || راستہ_is_extended(*ppath_w) || راستہ_is_device_راستہ(*ppath_w)) {
        واپس 0;
    }

    اگر (راستہ_w[0] == L'\\' && راستہ_w[1] == L'\\') {
        /* unc_prefix length is 8 plus 1 for terminating zeros,
         * we subtract 2 for the leading '\\' of the original path */
        عارضی_w = (wchar_t *)av_calloc(len - 2 + 8 + 1, حجم(wchar_t));
        اگر (!عارضی_w) {
            errno = ENOMEM;
            واپس -1;
        }
        wcscpy(عارضی_w, unc_سابقہ);
        wcscat(عارضی_w, راستہ_w + 2);
    } ورنہ {
        // The length of extended_path_prefix is 4 plus 1 for terminating zeros
        عارضی_w = (wchar_t *)av_calloc(len + 4 + 1, حجم(wchar_t));
        اگر (!عارضی_w) {
            errno = ENOMEM;
            واپس -1;
        }
        wcscpy(عارضی_w, extended_راستہ_سابقہ);
        wcscat(عارضی_w, راستہ_w);
    }

    av_freep(ppath_w);
    *ppath_w = عارضی_w;

    واپس 0;
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
ساکن اندرونی صحیح get_extended_win32_راستہ(ثابت حرف *راستہ, wchar_t **ppath_w)
{
    صحیح ret;
    size_t len;

    اگر ((ret = utf8towchar(راستہ, ppath_w)) < 0)
        واپس ret;

    اگر (راستہ_is_extended(*ppath_w)) {
        /* Paths prefixed with '\\?\' or \??\' are considered normalized by definition.
         * Windows doesn't normalize those paths and neither should we.
         */
        واپس 0;
    }

    اگر ((ret = راستہ_normalize(ppath_w)) < 0) {
        av_freep(ppath_w);
        واپس ret;
    }

    /* see .NET6: PathInternal.EnsureExtendedPrefixIfNeeded()
     * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L92
     */
    len = wcslen(*ppath_w);
    اگر (len >= MAX_راستہ) {
        اگر ((ret = جوڑو_extended_سابقہ(ppath_w)) < 0) {
            av_freep(ppath_w);
            واپس ret;
        }
    }

    واپس 0;
}

#اگر_ختم

#اگر_ختم /* AVUTIL_WCHAR_FILENAME_H */
