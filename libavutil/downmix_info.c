/*
 * Copyright (c) 2014 Tim Walker <tdskywalker@gmail.com>
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

#समावेश "downmix_info.h"
#समावेश "frame.h"
#समावेश "mem.h"

AVDownmixInfo *av_downmix_info_update_side_तथ्य(AVFrame *frame)
{
    AVFrame_Side_तथ्य *side_तथ्य;

    side_तथ्य = av_frame_get_side_तथ्य(frame, AV_FRAME_तथ्य_DOWNMIX_INFO);

    अगर (!side_तथ्य) {
        side_तथ्य = av_frame_new_side_तथ्य(frame, AV_FRAME_तथ्य_DOWNMIX_INFO,
                                           माप(AVDownmixInfo));
        अगर (side_तथ्य)
            स_रखो(side_तथ्य->तथ्य, 0, माप(AVDownmixInfo));
    }

    अगर (!side_तथ्य)
        वापस शून्य;

    वापस (AVDownmixInfo*)side_तथ्य->तथ्य;
}

#घोषणा MAX_CHANNELS 64

अटल स्थिर पूर्णांक type_map[] = {
    [AV_DOWNMIX_TYPE_UNKNOWN] = 0,
    [AV_DOWNMIX_TYPE_LORO]    = 2,
    [AV_DOWNMIX_TYPE_LTRT]    = 2,
    [AV_DOWNMIX_TYPE_DPLII]   = 2,
};

AVDownmixMatrix *av_downmix_matrix_alloc(क्रमागत AVDownmixType type,
                                         पूर्णांक in_ch_गिनती, माप_प्रकार *out_आकार)
{
    काष्ठा TestStruct {
        AVDownmixMatrix p;
        AVDownmixCoeff  b;
    };
    स्थिर माप_प्रकार coeffs_offset = दुरत्व(काष्ठा TestStruct, b);
    माप_प्रकार आकार = coeffs_offset;
    अचिन्हित पूर्णांक nb_coeffs;
    AVDownmixMatrix *dc;

    अगर ((अचिन्हित)type >= FF_ARRAY_ELEMS(type_map) ||
        (अचिन्हित)in_ch_गिनती > MAX_CHANNELS)
        वापस शून्य;

    nb_coeffs = type_map[type] * in_ch_गिनती;
    आकार += माप(AVDownmixCoeff) * nb_coeffs;

    dc = av_mallocz(आकार);
    अगर (!dc)
        वापस शून्य;

    dc->downmix_type  = type;
    dc->nb_coeffs     = nb_coeffs;
    dc->in_ch_गिनती   = in_ch_गिनती;
    dc->coeffs_offset = coeffs_offset;

    अगर (out_आकार)
        *out_आकार = आकार;

    वापस dc;
}
