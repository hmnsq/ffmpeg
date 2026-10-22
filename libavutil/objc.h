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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_OBJC_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_OBJC_H

#ಅನ್ತರ್ಭಾವ <Foundation/Foundation.h>

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ ff_objc_release(NSObject **obj)
{
    ಆದರೆ (*obj) {
        [*obj release];
        *obj = nil;
    }
}

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_OBJC_H */
