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

#నిర్వచితం_కాకపోతే AVUTIL_WCHAR_FILENAME_H
#నిర్వచించు AVUTIL_WCHAR_FILENAME_H

#నిర్వచితమైతే _WIN32

#అన్తర్భావ <errno.h>
#అన్తర్భావ <stddef.h>
#అన్తర్భావ <windows.h>
#అన్తర్భావ "mem.h"

av_warn_వాడని_ఫలితం
స్థిర అంతఃవరుస పూర్ణాంకం utf8towchar(స్థిరరాశి అక్షరం *filename_utf8, wchar_t **filename_w)
{
    పూర్ణాంకం అంకె_chars;
    అంకె_chars = Multi_Byte_గమ్యం_Wide_Char(CP_UTF8, MB_ERR_INVALID_CHARS, filename_utf8, -1, ఖాళీ, 0);
    ఒకవేళ (అంకె_chars <= 0) {
        *filename_w = ఖాళీ;
        errno = EINVAL;
        తిరిగి -1;
    }
    *filename_w = (wchar_t *)av_calloc(అంకె_chars, పరిమాణం(wchar_t));
    ఒకవేళ (!*filename_w) {
        errno = ENOMEM;
        తిరిగి -1;
    }
    Multi_Byte_గమ్యం_Wide_Char(CP_UTF8, 0, filename_utf8, -1, *filename_w, అంకె_chars);
    తిరిగి 0;
}

av_warn_వాడని_ఫలితం
స్థిర అంతఃవరుస పూర్ణాంకం wchartocp(గుర్తులేని పూర్ణాంకం సంకేతం_పుట, స్థిరరాశి wchar_t *filename_w,
                            అక్షరం **filename)
{
    DWORD flags = సంకేతం_పుట == CP_UTF8 ? WC_ERR_INVALID_CHARS : 0;
    పూర్ణాంకం అంకె_chars = Wide_Char_గమ్యం_Multi_Byte(సంకేతం_పుట, flags, filename_w, -1,
                                        ఖాళీ, 0, ఖాళీ, ఖాళీ);
    ఒకవేళ (అంకె_chars <= 0) {
        *filename = ఖాళీ;
        errno = EINVAL;
        తిరిగి -1;
    }
    *filename = (అక్షరం *)av_malloc_array(అంకె_chars, పరిమాణం **filename);
    ఒకవేళ (!*filename) {
        errno = ENOMEM;
        తిరిగి -1;
    }
    Wide_Char_గమ్యం_Multi_Byte(సంకేతం_పుట, flags, filename_w, -1,
                        *filename, అంకె_chars, ఖాళీ, ఖాళీ);
    తిరిగి 0;
}

av_warn_వాడని_ఫలితం
స్థిర అంతఃవరుస పూర్ణాంకం wchartoutf8(స్థిరరాశి wchar_t *filename_w, అక్షరం **filename)
{
    తిరిగి wchartocp(CP_UTF8, filename_w, filename);
}

av_warn_వాడని_ఫలితం
స్థిర అంతఃవరుస పూర్ణాంకం wchartoansi(స్థిరరాశి wchar_t *filename_w, అక్షరం **filename)
{
    తిరిగి wchartocp(CP_ACP, filename_w, filename);
}

av_warn_వాడని_ఫలితం
స్థిర అంతఃవరుస పూర్ణాంకం utf8toansi(స్థిరరాశి అక్షరం *filename_utf8, అక్షరం **filename)
{
    wchar_t *filename_w = ఖాళీ;
    పూర్ణాంకం ret = -1;
    ఒకవేళ (utf8towchar(filename_utf8, &filename_w))
        తిరిగి -1;

    ఒకవేళ (!filename_w) {
        *filename = ఖాళీ;
        తిరిగి 0;
    }

    ret = wchartoansi(filename_w, filename);
    av_free(filename_w);
    తిరిగి ret;
}

/**
 * Checks for extended path prefixes for which normalization needs to be skipped.
 * see .NET6: PathInternal.IsExtended()
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L165
 */
స్థిర అంతఃవరుస పూర్ణాంకం మార్గం_is_extended(స్థిరరాశి wchar_t *మార్గం)
{
    ఒకవేళ (మార్గం[0] == L'\\' && (మార్గం[1] == L'\\' || మార్గం[1] == L'?') && మార్గం[2] == L'?' && మార్గం[3] == L'\\')
        తిరిగి 1;

    తిరిగి 0;
}

/**
 * Checks for a device path prefix.
 * see .NET6: PathInternal.IsDevice()
 * we don't check forward slashes and extended paths (as already done)
 * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L132
 */
స్థిర అంతఃవరుస పూర్ణాంకం మార్గం_is_device_మార్గం(స్థిరరాశి wchar_t *మార్గం)
{
    ఒకవేళ (మార్గం[0] == L'\\' && మార్గం[1] == L'\\' && మార్గం[2] == L'.' && మార్గం[3] == L'\\')
        తిరిగి 1;

    తిరిగి 0;
}

/**
 * Performs path normalization by calling GetFullPathNameW().
 * see .NET6: PathHelper.GetFullPathName()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L70
 */
స్థిర అంతఃవరుస పూర్ణాంకం get_నిండిన_మార్గం_name(wchar_t **ppath_w)
{
    పూర్ణాంకం అంకె_chars;
    wchar_t *తాత్కాలిక_w;

    అంకె_chars = Get_నిండిన_మార్గం_Name_W(*ppath_w, 0, ఖాళీ, ఖాళీ);
    ఒకవేళ (అంకె_chars <= 0) {
        errno = EINVAL;
        తిరిగి -1;
    }

    తాత్కాలిక_w = (wchar_t *)av_calloc(అంకె_chars, పరిమాణం(wchar_t));
    ఒకవేళ (!తాత్కాలిక_w) {
        errno = ENOMEM;
        తిరిగి -1;
    }

    అంకె_chars = Get_నిండిన_మార్గం_Name_W(*ppath_w, అంకె_chars, తాత్కాలిక_w, ఖాళీ);
    ఒకవేళ (అంకె_chars <= 0) {
        av_free(తాత్కాలిక_w);
        errno = EINVAL;
        తిరిగి -1;
    }

    av_freep(ppath_w);
    *ppath_w = తాత్కాలిక_w;

    తిరిగి 0;
}

/**
 * Normalizes a Windows file or folder path.
 * Expansion of short paths (with 8.3 path components) is currently omitted
 * as it is not required for accessing long paths.
 * see .NET6: PathHelper.Normalize()
 * https://github.com/dotnet/runtime/blob/2a99e18eedabcf1add064c099da59d9301ce45e0/src/libraries/System.Private.CoreLib/src/System/IO/PathHelper.Windows.cs#L25
 */
స్థిర అంతఃవరుస పూర్ణాంకం మార్గం_normalize(wchar_t **ppath_w)
{
    పూర్ణాంకం ret;

    ఒకవేళ ((ret = get_నిండిన_మార్గం_name(ppath_w)) < 0)
        తిరిగి ret;

    /* What .NET does at this point is to call PathHelper.TryExpandShortFileName()
     * in case the path contains a '~' character.
     * We don't need to do this as we don't need to normalize the file name
     * for presentation, and the extended path prefix works with 8.3 path
     * components as well
     */
    తిరిగి 0;
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
స్థిర అంతఃవరుస పూర్ణాంకం కూడు_extended_ఉపసర్గ(wchar_t **ppath_w)
{
    స్థిరరాశి wchar_t *unc_ఉపసర్గ           = L"\\\\?\\UNC\\";
    స్థిరరాశి wchar_t *extended_మార్గం_ఉపసర్గ = L"\\\\?\\";
    స్థిరరాశి wchar_t *మార్గం_w               = *ppath_w;
    స్థిరరాశి size_t len                    = wcslen(మార్గం_w);
    wchar_t *తాత్కాలిక_w;

    /* We're skipping the check IsPartiallyQualified() because
     * we expect to have called GetFullPathNameW() already. */
    ఒకవేళ (len < 2 || మార్గం_is_extended(*ppath_w) || మార్గం_is_device_మార్గం(*ppath_w)) {
        తిరిగి 0;
    }

    ఒకవేళ (మార్గం_w[0] == L'\\' && మార్గం_w[1] == L'\\') {
        /* unc_prefix length is 8 plus 1 for terminating zeros,
         * we subtract 2 for the leading '\\' of the original path */
        తాత్కాలిక_w = (wchar_t *)av_calloc(len - 2 + 8 + 1, పరిమాణం(wchar_t));
        ఒకవేళ (!తాత్కాలిక_w) {
            errno = ENOMEM;
            తిరిగి -1;
        }
        wcscpy(తాత్కాలిక_w, unc_ఉపసర్గ);
        wcscat(తాత్కాలిక_w, మార్గం_w + 2);
    } లేకపోతే {
        // The length of extended_path_prefix is 4 plus 1 for terminating zeros
        తాత్కాలిక_w = (wchar_t *)av_calloc(len + 4 + 1, పరిమాణం(wchar_t));
        ఒకవేళ (!తాత్కాలిక_w) {
            errno = ENOMEM;
            తిరిగి -1;
        }
        wcscpy(తాత్కాలిక_w, extended_మార్గం_ఉపసర్గ);
        wcscat(తాత్కాలిక_w, మార్గం_w);
    }

    av_freep(ppath_w);
    *ppath_w = తాత్కాలిక_w;

    తిరిగి 0;
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
స్థిర అంతఃవరుస పూర్ణాంకం get_extended_win32_మార్గం(స్థిరరాశి అక్షరం *మార్గం, wchar_t **ppath_w)
{
    పూర్ణాంకం ret;
    size_t len;

    ఒకవేళ ((ret = utf8towchar(మార్గం, ppath_w)) < 0)
        తిరిగి ret;

    ఒకవేళ (మార్గం_is_extended(*ppath_w)) {
        /* Paths prefixed with '\\?\' or \??\' are considered normalized by definition.
         * Windows doesn't normalize those paths and neither should we.
         */
        తిరిగి 0;
    }

    ఒకవేళ ((ret = మార్గం_normalize(ppath_w)) < 0) {
        av_freep(ppath_w);
        తిరిగి ret;
    }

    /* see .NET6: PathInternal.EnsureExtendedPrefixIfNeeded()
     * https://github.com/dotnet/runtime/blob/9260c249140ef90b4299d0fe1aa3037e25228518/src/libraries/Common/src/System/IO/PathInternal.Windows.cs#L92
     */
    len = wcslen(*ppath_w);
    ఒకవేళ (len >= MAX_మార్గం) {
        ఒకవేళ ((ret = కూడు_extended_ఉపసర్గ(ppath_w)) < 0) {
            av_freep(ppath_w);
            తిరిగి ret;
        }
    }

    తిరిగి 0;
}

#అయితే_ముగింపు

#అయితే_ముగింపు /* AVUTIL_WCHAR_FILENAME_H */
