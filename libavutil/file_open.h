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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_FILE_OPEN_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_FILE_OPEN_H

#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "attributes.h"

#ಆದರೆ HAVE_LIBC_MSVCRT
#ವ್ಯಾಖ್ಯಾನಿಸು avpriv_fopen_utf8 ff_fopen_utf8
#ವ್ಯಾಖ್ಯಾನಿಸು avpriv_open ff_open
#ವ್ಯಾಖ್ಯಾನಿಸು avpriv_tempfile ff_tempfile
#ಆದರೆ_ಅಂತ್ಯ

 /**
 * A wrapper for open() setting O_CLOEXEC.
 */
av_warn_ಬಳಸದ_ಫಲಿತಾಂಶ
ಪೂರ್ಣಾಂಕ avpriv_open(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *filename, ಪೂರ್ಣಾಂಕ flags, ...);

/**
 * Open a file using a UTF-8 filename.
 */
FILE *avpriv_fopen_utf8(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಬಹುಲಕ);

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
ಪೂರ್ಣಾಂಕ avpriv_tempfile(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪೂರ್ವಪ್ರತ್ಯಯ, ಅಕ್ಷರ **filename, ಪೂರ್ಣಾಂಕ log_ಸ್ಥಾನಾಂತರ, ಶೂನ್ಯ *log_ctx);

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_FILE_OPEN_H */
