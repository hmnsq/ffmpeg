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


#अगर_अघोषित AVUTIL_HWCONTEXT_AMF_INTERNAL_H
#घोषणा AVUTIL_HWCONTEXT_AMF_INTERNAL_H
#समावेश <AMF/core/Factory.h>
#समावेश <AMF/core/Context.h>

/**
* Error handling helper
*/
#घोषणा AMF_RETURN_IF_FALSE(avctx, exp, ret_मूल्य, /*message,*/ ...) \
    अगर (!(exp)) { \
        av_log(avctx, AV_LOG_ERROR, __VA_ARGS__); \
        वापस ret_मूल्य; \
    }

#घोषणा AMF_GOTO_FAIL_IF_FALSE(avctx, exp, ret_मूल्य, /*message,*/ ...) \
    अगर (!(exp)) { \
        av_log(avctx, AV_LOG_ERROR, __VA_ARGS__); \
        ret = ret_मूल्य; \
        जाओ fail; \
    }

#घोषणा AMF_TIME_BASE_Q          (AVRational){1, AMF_SECOND}

#घोषणा AMF_IFACE_CALL(this, function, ...) ((this)->pVtbl->function((this), ##__VA_ARGS__))

#पूर्ण_अगर /* AVUTIL_HWCONTEXT_AMF_INTERNAL_H */
