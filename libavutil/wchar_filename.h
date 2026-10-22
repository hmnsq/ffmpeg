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

#अन्तर्भाव <errno.h>
#अन्तर्भाव <stddef.h>
#अन्तर्भाव <windows.h>
#अन्तर्भाव "mem.h"

av_warn_unused_result
स्थिर अन्तःस्थ पूर्णाङ्क utf8towchar(अचर वर्ण *filename_utf8, ब_अक्षर_प्रकार **filename_w)
{
    पूर्णाङ्क अङ्क_chars;
    अङ्क_chars = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, filename_utf8, -1, रिक्त, 0);
    यदि (अङ्क_chars <= 0) {
        *filename_w = रिक्त;
        त्रुटि_सं = EINVAL;
        फर्काऊ -1;
    }
    *filename_w = (ब_अक्षर_प्रकार *)av_calloc(अङ्क_chars, परिमाण(ब_अक्षर_प्रकार));
    यदि (!*filename_w) {
        त्रुटि_सं = ENOMEM;
        फर्काऊ -1;
    }
    MultiByteToWideChar(CP_UTF8, 0, filename_utf8, -1, *filename_w, अङ्क_chars);
    फर्काऊ 0;
}

av_warn_unused_result
स्थिर अन्तःस्थ पूर्णाङ्क wchartocp(अचिन्हित पूर्णाङ्क code_page, अचर ब_अक्षर_प्रकार *filename_w,
                            वर्ण **filename)
{
    DWORD flags = code_page == CP_UTF8 ? WC_ERR_INVALID_CHARS : 0;
    पूर्णाङ्क अङ्क_chars = WideCharToMultiByte(code_page, flags, filename_w, -1,
                                        रिक्त, 0, रिक्त, रिक्त);
    यदि (अङ्क_chars <= 0) {
        *filename = रिक्त;
        त्रुटि_सं = EINVAL;
        फर्काऊ -1;
    }
    *filename = (वर्ण *)av_malloc_array(अङ्क_chars, परिमाण **filename);
    यदि (!*filename) {
        त्रुटि_सं = ENOMEM;
        फर्काऊ -1;
    }
    WideCharToMultiByte(code_page, flags, filename_w, -1,
                        *filename, अङ्क_chars, रिक्त, रिक्त);
    फर्काऊ 0;
}

av_warn_unused_result
स्थिर अन्तःस्थ पूर्णाङ्क wchartoutf8(अचर ब_अक्षर_प्रकार *filename_w, वर्ण **filename)
{
    फर्काऊ wchartocp(CP_UTF8, filename_w, filename);
}

av_warn_unused_result
स्थिर अन्तःस्थ पूर्णाङ्क wchartoansi(अचर ब_अक्षर_प्रकार *filename_w, वर्ण **filename)
{
    फर्काऊ wchartocp(CP_ACP, filename_w, filename);
}

av_warn_unused_result
स्थिर अन्तःस्थ पूर्णाङ्क utf8toansi(अचर वर्ण *filename_utf8, वर्ण **filename)
{
    ब_अक्षर_प्रकार *filename_w = रिक्त;
    पूर्णाङ्क ret = -1;
    यदि (utf8towchar(filename_utf8, &filename_w))
        फर्काऊ -1;

    यदि (!filename_w) {
        *filename = रिक्त;
        फर्काऊ 0;
    }

    ret = wchartoansi(filename_w, filename);
    av_free(filename_w);
    फर्काऊ ret;
}

/**
 * Checks for extended path prefixes for which normalization needs to be skipped.
 * see .NET6: PathInternal.IsExtended()
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L165
 */
स्थिर अन्तःस्थ पूर्णाङ्क path_is_extended(अचर ब_अक्षर_प्रकार *path)
{
    यदि (path[0] == L'\\' && (path[1] == L'\\' || path[1] == L'?') && path[2] == L'?' && path[3] == L'\\')
        फर्काऊ 1;

    फर्काऊ 0;
}

/**
 * Checks for a device path prefix.
 * see .NET6: PathInternal.IsDevice()
 * we don't check forward slashes and extended paths (as already done)
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L132
 */
स्थिर अन्तःस्थ पूर्णाङ्क path_is_device_path(अचर ब_अक्षर_प्रकार *path)
{
    यदि (path[0] == L'\\' && path[1] == L'\\' && path[2] == L'.' && path[3] == L'\\')
        फर्काऊ 1;

    फर्काऊ 0;
}

/**
 * Performs path normalization by calling GetFullPathNameW().
 * see .NET6: PathHelper.GetFullPathName()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L70
 */
स्थिर अन्तःस्थ पूर्णाङ्क get_full_path_name(ब_अक्षर_प्रकार **ppath_w)
{
    पूर्णाङ्क अङ्क_chars;
    ब_अक्षर_प्रकार *temp_w;

    अङ्क_chars = GetFullPathNameW(*ppath_w, 0, रिक्त, रिक्त);
    यदि (अङ्क_chars <= 0) {
        त्रुटि_सं = EINVAL;
        फर्काऊ -1;
    }

    temp_w = (ब_अक्षर_प्रकार *)av_calloc(अङ्क_chars, परिमाण(ब_अक्षर_प्रकार));
    यदि (!temp_w) {
        त्रुटि_सं = ENOMEM;
        फर्काऊ -1;
    }

    अङ्क_chars = GetFullPathNameW(*ppath_w, अङ्क_chars, temp_w, रिक्त);
    यदि (अङ्क_chars <= 0) {
        av_free(temp_w);
        त्रुटि_सं = EINVAL;
        फर्काऊ -1;
    }

    av_freep(ppath_w);
    *ppath_w = temp_w;

    फर्काऊ 0;
}

/**
 * Normalizes a Windows file or folder path.
 * Expansion of short paths (with 8.3 path components) is currently omitted
 * as it is not required for accessing long paths.
 * see .NET6: PathHelper.Normalize()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L25
 */
स्थिर अन्तःस्थ पूर्णाङ्क path_normalize(ब_अक्षर_प्रकार **ppath_w)
{
    पूर्णाङ्क ret;

    यदि ((ret = get_full_path_name(ppath_w)) < 0)
        फर्काऊ ret;

    /* What .NET does at this point is to call PathHelper.TryExpandShortFileName()
     * in case the path contains a '~' character.
     * We don't need to do this as we don't need to normalize the file name
     * for presentation, and the extended path prefix works with 8.3 path
     * components as well
     */
    फर्काऊ 0;
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
स्थिर अन्तःस्थ पूर्णाङ्क add_extended_prefix(ब_अक्षर_प्रकार **ppath_w)
{
    अचर ब_अक्षर_प्रकार *unc_prefix           = L"\\\\?\\UNC\\";
    अचर ब_अक्षर_प्रकार *extended_path_prefix = L"\\\\?\\";
    अचर ब_अक्षर_प्रकार *path_w               = *ppath_w;
    अचर माप_प्रकार len                    = wcslen(path_w);
    ब_अक्षर_प्रकार *temp_w;

    /* We're skipping the check IsPartiallyQualified() because
     * we expect to have called GetFullPathNameW() already. */
    यदि (len < 2 || path_is_extended(*ppath_w) || path_is_device_path(*ppath_w)) {
        फर्काऊ 0;
    }

    यदि (path_w[0] == L'\\' && path_w[1] == L'\\') {
        /* unc_prefix length is 8 plus 1 for terminating zeros,
         * we subtract 2 for the leading '\\' of the original path */
        temp_w = (ब_अक्षर_प्रकार *)av_calloc(len - 2 + 8 + 1, परिमाण(ब_अक्षर_प्रकार));
        यदि (!temp_w) {
            त्रुटि_सं = ENOMEM;
            फर्काऊ -1;
        }
        wcscpy(temp_w, unc_prefix);
        wcscat(temp_w, path_w + 2);
    } अन्यथा {
        // The length of extended_path_prefix is 4 plus 1 for terminating zeros
        temp_w = (ब_अक्षर_प्रकार *)av_calloc(len + 4 + 1, परिमाण(ब_अक्षर_प्रकार));
        यदि (!temp_w) {
            त्रुटि_सं = ENOMEM;
            फर्काऊ -1;
        }
        wcscpy(temp_w, extended_path_prefix);
        wcscat(temp_w, path_w);
    }

    av_freep(ppath_w);
    *ppath_w = temp_w;

    फर्काऊ 0;
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
स्थिर अन्तःस्थ पूर्णाङ्क get_extended_win32_path(अचर वर्ण *path, ब_अक्षर_प्रकार **ppath_w)
{
    पूर्णाङ्क ret;
    माप_प्रकार len;

    यदि ((ret = utf8towchar(path, ppath_w)) < 0)
        फर्काऊ ret;

    यदि (path_is_extended(*ppath_w)) {
        /* Paths prefixed with '\\?\' or \??\' are considered normalized by definition.
         * Windows doesn't normalize those paths and neither should we.
         */
        फर्काऊ 0;
    }

    यदि ((ret = path_normalize(ppath_w)) < 0) {
        av_freep(ppath_w);
        फर्काऊ ret;
    }

    /* see .NET6: PathInternal.EnsureExtendedPrefixIfNeeded()
     * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L92
     */
    len = wcslen(*ppath_w);
    यदि (len >= MAX_PATH) {
        यदि ((ret = add_extended_prefix(ppath_w)) < 0) {
            av_freep(ppath_w);
            फर्काऊ ret;
        }
    }

    फर्काऊ 0;
}

#endif

#endif /* AVUTIL_WCHAR_FILENAME_H */
