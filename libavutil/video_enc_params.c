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

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಅನ್ತರ್ಭಾವ "buffer.h"
#ಅನ್ತರ್ಭಾವ "frame.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "video_enc_params.h"

AVVideoEncParams *av_video_enc_params_alloc(ಎಣಿಕೆ AVVideoEncParamsType type,
                                            ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ nb_ಖಂಡಗಳು, size_t *ಹೊರಹೋಗು_ಗಾತ್ರ)
{
    ರಚನೆ TestStruct {
        AVVideoEncParams   p;
        AVVideo_ಖಂಡ_Params b;
    };
    ಸ್ಥಿರಾಂಕ size_t ಖಂಡಗಳು_ಸ್ಥಾನಾಂತರ = offsetof(ರಚನೆ TestStruct, b);
    size_t ಗಾತ್ರ_2 = ಖಂಡಗಳು_ಸ್ಥಾನಾಂತರ;
    AVVideoEncParams *par;

    ಆದರೆ (nb_ಖಂಡಗಳು > (SIZE_MAX - ಗಾತ್ರ_2) / ಗಾತ್ರ(AVVideo_ಖಂಡ_Params))
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಗಾತ್ರ_2 += ಗಾತ್ರ(AVVideo_ಖಂಡ_Params) * nb_ಖಂಡಗಳು;

    par = av_mallocz(ಗಾತ್ರ_2);
    ಆದರೆ (!par)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    par->type          = type;
    par->nb_ಖಂಡಗಳು     = nb_ಖಂಡಗಳು;
    par->ಖಂಡ_ಗಾತ್ರ    = ಗಾತ್ರ(AVVideo_ಖಂಡ_Params);
    par->ಖಂಡಗಳು_ಸ್ಥಾನಾಂತರ = ಖಂಡಗಳು_ಸ್ಥಾನಾಂತರ;

    ಆದರೆ (ಹೊರಹೋಗು_ಗಾತ್ರ)
        *ಹೊರಹೋಗು_ಗಾತ್ರ = ಗಾತ್ರ_2;

    ಹಿಂತಿರುಗಿ par;
}

AVVideoEncParams*
av_video_enc_params_create_side_ದತ್ತಾಂಶ(AVFrame *ಚೌಕಟ್ಟು, ಎಣಿಕೆ AVVideoEncParamsType type,
                                     ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ nb_ಖಂಡಗಳು)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    size_t ಗಾತ್ರ_2;

    par = av_video_enc_params_alloc(type, nb_ಖಂಡಗಳು, &ಗಾತ್ರ_2);
    ಆದರೆ (!par)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    buf = av_ಬಫರ್_create((uint8_t *)par, ಗಾತ್ರ_2, ಖಾಲಿ, ಖಾಲಿ, 0);
    ಆದರೆ (!buf) {
        av_freep(&par);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (!av_ಚೌಕಟ್ಟು_new_side_ದತ್ತಾಂಶ_from_buf(ಚೌಕಟ್ಟು, AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_VIDEO_ENC_PARAMS, buf)) {
        av_ಬಫರ್_unref(&buf);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ par;
}
