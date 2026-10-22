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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_TIMECODE_ಆಂತರಿಕ_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_TIMECODE_ಆಂತರಿಕ_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "rational.h"

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
ಶೂನ್ಯ ff_timecode_ಗಣ_smpte(ಚಿಹ್ನೆರಹಿತ *drop, ಚಿಹ್ನೆರಹಿತ *hh, ಚಿಹ್ನೆರಹಿತ *mm, ಚಿಹ್ನೆರಹಿತ *ss, ಚಿಹ್ನೆರಹಿತ *ff,
                           AVRational ದರ, uint32_t tcsmpte, ಪೂರ್ಣಾಂಕ prevent_df, ಪೂರ್ಣಾಂಕ skip_ಕ್ಷೇತ್ರ);

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_TIMECODE_INTERNAL_H */
