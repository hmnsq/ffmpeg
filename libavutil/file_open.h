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

#నిర్వచితం_కాకపోతే AVUTIL_FILE_OPEN_H
#నిర్వచించు AVUTIL_FILE_OPEN_H

#అన్తర్భావ <stdio.h>

#అన్తర్భావ "config.h"
#అన్తర్భావ "attributes.h"

#ఒకవేళ HAVE_LIBC_MSVCRT
#నిర్వచించు avpriv_fopen_utf8 ff_fopen_utf8
#నిర్వచించు avpriv_open ff_open
#నిర్వచించు avpriv_tempfile ff_tempfile
#అయితే_ముగింపు

 /**
 * A wrapper for open() setting O_CLOEXEC.
 */
av_warn_వాడని_ఫలితం
పూర్ణాంకం avpriv_open(స్థిరరాశి అక్షరం *filename, పూర్ణాంకం flags, ...);

/**
 * Open a file using a UTF-8 filename.
 */
FILE *avpriv_fopen_utf8(స్థిరరాశి అక్షరం *మార్గం, స్థిరరాశి అక్షరం *బహుళకం);

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
పూర్ణాంకం avpriv_tempfile(స్థిరరాశి అక్షరం *ఉపసర్గ, అక్షరం **filename, పూర్ణాంకం log_స్థానభ్రంశం, శూన్య *log_ctx);

#అయితే_ముగింపు /* AVUTIL_FILE_OPEN_H */
