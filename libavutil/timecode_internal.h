/*
 * Copyright (c) 2006 Smartjog S.A.S, Baptiste Coudurier <baptiste.coudurier@gmail.com>
 * Copyright (c) 2011-2012 Smartjog S.A.S, Clément Bœsch <clement.boesch@smartjog.com>
 *
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

/**
 * @file
 * Timecode helpers header
 */

#अगर_अघोषित AVUTIL_TIMECODE_INTERNAL_H
#घोषणा AVUTIL_TIMECODE_INTERNAL_H

#समावेश <stdint.h>
#समावेश "rational.h"

/**
 * Convert SMPTE 12M binary representation to sei info.
 *
 * @param drop       drop flag output
 * @param hh         hour output
 * @param mm         minute output
 * @param ss         second output
 * @param ff         frame number output
 * @param rate       frame rate of the timecode
 * @param tcsmpte    the 32-bit SMPTE timecode
 * @param prevent_df prevent the use of a drop flag when it is known the DF bit
 *                   is arbitrary
 * @param skip_field prevent the use of a field flag when it is known the field
 *                   bit is arbitrary (e.g. because it is used as PC flag)
 */
व्योम ff_timecode_set_smpte(अचिन्हित *drop, अचिन्हित *hh, अचिन्हित *mm, अचिन्हित *ss, अचिन्हित *ff,
                           AVRational rate, uint32_t tcsmpte, पूर्णांक prevent_df, पूर्णांक skip_field);

#पूर्ण_अगर /* AVUTIL_TIMECODE_INTERNAL_H */
