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


#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_HWCONTEXT_AMF_ಆಂತರಿಕ_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_HWCONTEXT_AMF_ಆಂತರಿಕ_H
#ಅನ್ತರ್ಭಾವ <AMF/core/Factory.h>
#ಅನ್ತರ್ಭಾವ <AMF/core/Context.h>

/**
* Error handling helper
*/
#ವ್ಯಾಖ್ಯಾನಿಸು AMF_RETURN_IF_FALSE(avctx, ಘಾತಾಂಕ, ret_ಮೌಲ್ಯ, /*message,*/ ...) \
    ಆದರೆ (!(ಘಾತಾಂಕ)) { \
        av_log(avctx, AV_LOG_ERROR, __VA_ARGS__); \
        ಹಿಂತಿರುಗಿ ret_ಮೌಲ್ಯ; \
    }

#ವ್ಯಾಖ್ಯಾನಿಸು AMF_GOTO_FAIL_IF_FALSE(avctx, ಘಾತಾಂಕ, ret_ಮೌಲ್ಯ, /*message,*/ ...) \
    ಆದರೆ (!(ಘಾತಾಂಕ)) { \
        av_log(avctx, AV_LOG_ERROR, __VA_ARGS__); \
        ret = ret_ಮೌಲ್ಯ; \
        ಹೋಗು fail; \
    }

#ವ್ಯಾಖ್ಯಾನಿಸು AMF_ಸಮಯ_ತಳ_Q          (AVRational){1, AMF_ಎರಡನೇ}

#ವ್ಯಾಖ್ಯಾನಿಸು AMF_IFACE_CALL(this, function, ...) ((this)->pVtbl->function((this), ##__VA_ARGS__))

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_HWCONTEXT_AMF_INTERNAL_H */
