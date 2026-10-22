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

#اگر_تعریف_نشده AVUTIL_TIMECODE_داخلی_H
#تعریف_کن AVUTIL_TIMECODE_داخلی_H

#ضمن <stdint.h>
#ضمن "rational.h"

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
فراغ ff_timecode_مجموعه_smpte(بیعلامت *drop, بیعلامت *hh, بیعلامت *mm, بیعلامت *ss, بیعلامت *ff,
                           AVRational نرخ, uint32_t tcsmpte, صحيح prevent_df, صحيح skip_فیلد);

#پایان_اگر /* AVUTIL_TIMECODE_INTERNAL_H */
