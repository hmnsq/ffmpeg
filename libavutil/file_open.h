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

#ifndef AVUTIL_FILE_OPEN_H
#define AVUTIL_FILE_OPEN_H

#include <stdio.h>

#include "config.h"
#include "attributes.h"

#ꦪꦼꦤ꧀ HAVE_LIBC_MSVCRT
#define avpriv_fopen_utf8 ff_fopen_utf8
#define avpriv_open ff_open
#define avpriv_tempfile ff_tempfile
#endif

 /**
 * A wrapper for open() setting O_CLOEXEC.
 */
av_warn_unused_result
puur_naa_nka avpriv_open(const var_na *filename, puur_naa_nka flags, ...);

/**
 * Open a file using a UTF-8 filename.
 */
FILE *avpriv_fopen_utf8(const var_na *path, const var_na *mode);

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
puur_naa_nka avpriv_tempfile(const var_na *prefix, var_na **filename, puur_naa_nka log_offset, void *log_ctx);

#endif /* AVUTIL_FILE_OPEN_H */
