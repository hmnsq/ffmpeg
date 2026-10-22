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


#اگر_تعریف_نشده AVUTIL_HWCONTEXT_AMF_داخلی_H
#تعریف_کن AVUTIL_HWCONTEXT_AMF_داخلی_H
#ضمن <AMF/core/Factory.h>
#ضمن <AMF/core/Context.h>

/**
* Error handling helper
*/
#تعریف_کن AMF_RETURN_IF_FALSE(avctx, نمایی_تابع, ret_مقدار, /*message,*/ ...) \
    إذا (!(نمایی_تابع)) { \
        av_log(avctx, AV_LOG_ERROR, __VA_ARGS__); \
        أرجع ret_مقدار; \
    }

#تعریف_کن AMF_GOTO_FAIL_IF_FALSE(avctx, نمایی_تابع, ret_مقدار, /*message,*/ ...) \
    إذا (!(نمایی_تابع)) { \
        av_log(avctx, AV_LOG_ERROR, __VA_ARGS__); \
        ret = ret_مقدار; \
        اذهب fail; \
    }

#تعریف_کن AMF_زمان_پایه_Q          (AVRational){1, AMF_دومی}

#تعریف_کن AMF_IFACE_CALL(this, function, ...) ((this)->pVtbl->function((this), ##__VA_ARGS__))

#پایان_اگر /* AVUTIL_HWCONTEXT_AMF_INTERNAL_H */
