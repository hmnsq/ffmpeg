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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_FILE_OPEN_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_FILE_OPEN_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"

#ਜੇ HAVE_LIBC_MSVCRT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ avpriv_fopen_utf8 ff_fopen_utf8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ avpriv_open ff_open
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ avpriv_tempfile ff_tempfile
#ਜੇ_ਅੰਤ

 /**
 * A wrapper for open() setting O_CLOEXEC.
 */
av_warn_ਅਣਵਰਤਿਆ_ਨਤੀਜਾ
ਪੂਰਨ avpriv_open(ਅਚਲ ਅੱਖਰ *filename, ਪੂਰਨ flags, ...);

/**
 * Open a file using a UTF-8 filename.
 */
FILE *avpriv_fopen_utf8(ਅਚਲ ਅੱਖਰ *ਰਸਤਾ, ਅਚਲ ਅੱਖਰ *ਬਹੁਲਕ);

/**
 * Wrapper to work around the lack of mkstemp() on mingw.
 * Also, tries to create file in /tmp first, if possible.
 * *prefix can be a character constant; *filename will be allocated internally.
 * @return file descriptor of opened file (or negative value corresponding to an
 * AVERROR code on error)
 * and opened file name in **filename.
 * @note On very old libcs it is necessary to set a secure umask before
 *       calling this, av_tempfile() can't call umask itself as it is used in
 *       libraries and could interfere with the calling application.
 */
ਪੂਰਨ avpriv_tempfile(ਅਚਲ ਅੱਖਰ *ਅਗੇਤਰ, ਅੱਖਰ **filename, ਪੂਰਨ log_ਵਿੱਥ, ਖਾਲੀ *log_ctx);

#ਜੇ_ਅੰਤ /* AVUTIL_FILE_OPEN_H */
