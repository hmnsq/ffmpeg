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


#جيڪڏهن_وصف_نه_ٿيل AVUTIL_HWCONTEXT_AMF_اندروني_H
#وصف_ڪريو AVUTIL_HWCONTEXT_AMF_اندروني_H
#ضمن <AMF/core/Factory.h>
#ضمن <AMF/core/Context.h>

/**
* Error handling helper
*/
#وصف_ڪريو AMF_RETURN_IF_FALSE(avctx, قوت_نما, ret_قدر, /*message,*/ ...) \
    إذا (!(قوت_نما)) { \
        av_log(avctx, AV_LOG_ERROR, __VA_ARGS__); \
        أرجع ret_قدر; \
    }

#وصف_ڪريو AMF_GOTO_FAIL_IF_FALSE(avctx, قوت_نما, ret_قدر, /*message,*/ ...) \
    إذا (!(قوت_نما)) { \
        av_log(avctx, AV_LOG_ERROR, __VA_ARGS__); \
        ret = ret_قدر; \
        اذهب fail; \
    }

#وصف_ڪريو AMF_وقت_بنياد_Q          (AVRational){1, AMF_ٻيو}

#وصف_ڪريو AMF_IFACE_CALL(this, function, ...) ((this)->pVtbl->function((this), ##__VA_ARGS__))

#جيڪڏهن_پورو /* AVUTIL_HWCONTEXT_AMF_INTERNAL_H */
