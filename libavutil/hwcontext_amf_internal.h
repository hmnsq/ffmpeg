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


#که_نه_تعریف_شوی AVUTIL_HWCONTEXT_AMF_دننی_H
#تعریف_کړه AVUTIL_HWCONTEXT_AMF_دننی_H
#ضمن <AMF/core/Factory.h>
#ضمن <AMF/core/Context.h>

/**
* Error handling helper
*/
#تعریف_کړه AMF_RETURN_IF_FALSE(avctx, توانیز_تابع, ret_ارزښت, /*message,*/ ...) \
    إذا (!(توانیز_تابع)) { \
        av_log(avctx, AV_LOG_ERROR, __VA_ARGS__); \
        أرجع ret_ارزښت; \
    }

#تعریف_کړه AMF_GOTO_FAIL_IF_FALSE(avctx, توانیز_تابع, ret_ارزښت, /*message,*/ ...) \
    إذا (!(توانیز_تابع)) { \
        av_log(avctx, AV_LOG_ERROR, __VA_ARGS__); \
        ret = ret_ارزښت; \
        اذهب fail; \
    }

#تعریف_کړه AMF_وخت_بنسټ_Q          (AVRational){1, AMF_دوهم}

#تعریف_کړه AMF_IFACE_CALL(this, function, ...) ((this)->pVtbl->function((this), ##__VA_ARGS__))

#د_که_پای /* AVUTIL_HWCONTEXT_AMF_INTERNAL_H */
