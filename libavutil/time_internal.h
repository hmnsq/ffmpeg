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

#अगर_अघोषित AVUTIL_TIME_INTERNAL_H
#घोषणा AVUTIL_TIME_INTERNAL_H

#समावेश <time.h>
#समावेश "config.h"

#अगर !HAVE_GMTIME_R && !defined(gmtime_r)
अटल अंतरभूत काष्ठा पंचांग *ff_gmtime_r(स्थिर समय_प्रकार* घड़ी, काष्ठा पंचांग *परिणाम)
{
    काष्ठा पंचांग *ptr = स_जमट(घड़ी);
    अगर (!ptr)
        वापस शून्य;
    *परिणाम = *ptr;
    वापस परिणाम;
}
#घोषणा gmtime_r ff_gmtime_r
#पूर्ण_अगर

#अगर !HAVE_LOCALTIME_R && !defined(localtime_r)
अटल अंतरभूत काष्ठा पंचांग *ff_localtime_r(स्थिर समय_प्रकार* घड़ी, काष्ठा पंचांग *परिणाम)
{
    काष्ठा पंचांग *ptr = स_स्थानीय(घड़ी);
    अगर (!ptr)
        वापस शून्य;
    *परिणाम = *ptr;
    वापस परिणाम;
}
#घोषणा localtime_r ff_localtime_r
#पूर्ण_अगर

#पूर्ण_अगर /* AVUTIL_TIME_INTERNAL_H */
