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


#నిర్వచితం_కాకపోతే AVUTIL_HWCONTEXT_AMF_అంతర్గత_H
#నిర్వచించు AVUTIL_HWCONTEXT_AMF_అంతర్గత_H
#అన్తర్భావ <AMF/core/Factory.h>
#అన్తర్భావ <AMF/core/Context.h>

/**
* Error handling helper
*/
#నిర్వచించు AMF_RETURN_IF_FALSE(avctx, ఘాతాంకం, ret_విలువ, /*message,*/ ...) \
    ఒకవేళ (!(ఘాతాంకం)) { \
        av_log(avctx, AV_LOG_ERROR, __VA_ARGS__); \
        తిరిగి ret_విలువ; \
    }

#నిర్వచించు AMF_GOTO_FAIL_IF_FALSE(avctx, ఘాతాంకం, ret_విలువ, /*message,*/ ...) \
    ఒకవేళ (!(ఘాతాంకం)) { \
        av_log(avctx, AV_LOG_ERROR, __VA_ARGS__); \
        ret = ret_విలువ; \
        వెళ్ళు fail; \
    }

#నిర్వచించు AMF_సమయం_పునాది_Q          (AVRational){1, AMF_రెండవ}

#నిర్వచించు AMF_IFACE_CALL(this, function, ...) ((this)->pVtbl->function((this), ##__VA_ARGS__))

#అయితే_ముగింపు /* AVUTIL_HWCONTEXT_AMF_INTERNAL_H */
