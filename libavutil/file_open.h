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

#यदि_अपरिभाषितम् AVUTIL_FILE_OPEN_H
#परिभाषय AVUTIL_FILE_OPEN_H

#अन्तर्भाव <stdio.h>

#अन्तर्भाव "config.h"
#अन्तर्भाव "attributes.h"

#यदि HAVE_LIBC_MSVCRT
#परिभाषय avpriv_fopen_utf8 ff_fopen_utf8
#परिभाषय avpriv_open ff_open
#परिभाषय avpriv_tempfile ff_tempfile
#यदि_अन्तः

 /**
 * A wrapper for open() setting O_CLOEXEC.
 */
av_warn_अप्रयुक्तम्_परिणाम
पूर्णाङ्क avpriv_open(ध्रुव वर्ण *filename, पूर्णाङ्क flags, ...);

/**
 * Open a file using a UTF-8 filename.
 */
FILE *avpriv_fopen_utf8(ध्रुव वर्ण *मार्गः, ध्रुव वर्ण *बहुलकम्);

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
पूर्णाङ्क avpriv_tempfile(ध्रुव वर्ण *उपसर्गः, वर्ण **filename, पूर्णाङ्क log_विस्थापनम्, शून्य *log_ctx);

#यदि_अन्तः /* AVUTIL_FILE_OPEN_H */
