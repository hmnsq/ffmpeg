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

#నిర్వచితం_కాకపోతే AVUTIL_OBJC_H
#నిర్వచించు AVUTIL_OBJC_H

#అన్తర్భావ <Foundation/Foundation.h>

స్థిర అంతఃవరుస శూన్య ff_objc_release(NSObject **obj)
{
    ఒకవేళ (*obj) {
        [*obj release];
        *obj = nil;
    }
}

#అయితే_ముగింపు /* AVUTIL_OBJC_H */
