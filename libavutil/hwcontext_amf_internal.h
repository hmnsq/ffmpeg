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


#اگر_غیر_تعریف_شدہ AVUTIL_HWCONTEXT_AMF_اندرونی_H
#تعریف_کرو AVUTIL_HWCONTEXT_AMF_اندرونی_H
#شامل <AMF/core/Factory.h>
#شامل <AMF/core/Context.h>

/**
* Error handling helper
*/
#تعریف_کرو AMF_RETURN_IF_FALSE(avctx, قوت_نما, ret_قدر, /*message,*/ ...) \
    اگر (!(قوت_نما)) { \
        av_log(avctx, AV_LOG_ERROR, __VA_ARGS__); \
        واپس ret_قدر; \
    }

#تعریف_کرو AMF_GOTO_FAIL_IF_FALSE(avctx, قوت_نما, ret_قدر, /*message,*/ ...) \
    اگر (!(قوت_نما)) { \
        av_log(avctx, AV_LOG_ERROR, __VA_ARGS__); \
        ret = ret_قدر; \
        جاؤ fail; \
    }

#تعریف_کرو AMF_وقت_بنیاد_Q          (AVRational){1, AMF_دوسرا}

#تعریف_کرو AMF_IFACE_CALL(this, function, ...) ((this)->pVtbl->function((this), ##__VA_ARGS__))

#اگر_ختم /* AVUTIL_HWCONTEXT_AMF_INTERNAL_H */
