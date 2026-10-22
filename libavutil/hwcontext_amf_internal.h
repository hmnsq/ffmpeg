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


#यदि_अपरिभाषितम् AVUTIL_HWCONTEXT_AMF_आन्तरिकम्_H
#परिभाषय AVUTIL_HWCONTEXT_AMF_आन्तरिकम्_H
#अन्तर्भाव <AMF/core/Factory.h>
#अन्तर्भाव <AMF/core/Context.h>

/**
* Error handling helper
*/
#परिभाषय AMF_RETURN_IF_FALSE(avctx, घातांकः, ret_मानम्, /*message,*/ ...) \
    यदि (!(घातांकः)) { \
        av_log(avctx, AV_LOG_ERROR, __VA_ARGS__); \
        प्रत्यागम ret_मानम्; \
    }

#परिभाषय AMF_GOTO_FAIL_IF_FALSE(avctx, घातांकः, ret_मानम्, /*message,*/ ...) \
    यदि (!(घातांकः)) { \
        av_log(avctx, AV_LOG_ERROR, __VA_ARGS__); \
        ret = ret_मानम्; \
        गच्छ fail; \
    }

#परिभाषय AMF_TIME_आधारः_Q          (AVRational){1, AMF_SECOND}

#परिभाषय AMF_IFACE_CALL(this, function, ...) ((this)->pVtbl->function((this), ##__VA_ARGS__))

#यदि_अन्तः /* AVUTIL_HWCONTEXT_AMF_INTERNAL_H */
