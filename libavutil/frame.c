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

#அந்தர்பாவ "channel_layout.h"
#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "buffer.h"
#அந்தர்பாவ "dict.h"
#அந்தர்பாவ "frame.h"
#அந்தர்பாவ "frame_internal.h"
#அந்தர்பாவ "imgutils.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "refstruct.h"
#அந்தர்பாவ "samplefmt.h"
#அந்தர்பாவ "side_data.h"
#அந்தர்பாவ "hwcontext.h"

நிலையான வெறுமை get_frame_defaults(AVFrame *frame)
{
    memset(frame, 0, அளவு(*frame));

    frame->pts                   =
    frame->pkt_dts               = AV_NOPTS_மதிப்பு;
    frame->best_effort_timestamp = AV_NOPTS_மதிப்பு;
    frame->duration            = 0;
    frame->time_base           = (AVRational){ 0, 1 };
    frame->sample_aspect_ratio = (AVRational){ 0, 1 };
    frame->format              = -1; /* unknown */
    frame->extended_data       = frame->data;
    frame->color_primaries     = AVCOL_PRI_UNSPECIFIED;
    frame->color_trc           = AVCOL_TRC_UNSPECIFIED;
    frame->colorspace          = AVCOL_SPC_UNSPECIFIED;
    frame->color_range         = AVCOL_RANGE_UNSPECIFIED;
    frame->chroma_location     = AVCHROMA_LOC_UNSPECIFIED;
    frame->alpha_mode          = AVALPHA_MODE_UNSPECIFIED;
    frame->flags               = 0;
}

AVFrame *av_frame_alloc(வெறுமை)
{
    AVFrame *frame = av_malloc(அளவு(*frame));

    எனில் (!frame)
        திரும்பு வெற்று;

    get_frame_defaults(frame);

    திரும்பு frame;
}

வெறுமை av_frame_free(AVFrame **frame)
{
    எனில் (!frame || !*frame)
        திரும்பு;

    av_frame_unref(*frame);
    av_freep(frame);
}

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

முழு ff_frame_get_video_buffer(AVFrame *frame, முழு align,
                              AVBufferRef *(*alloc)(வெறுமை *opaque, size_t size),
                              வெறுமை *opaque)
{
    மாறிலி AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    முழு ret, padded_height;
    முழு plane_padding;
    ptrdiff_t linesizes[4];
    size_t total_size, sizes[4];

    எனில் (!desc)
        திரும்பு AVERROR(EINVAL);

    எனில் ((ret = av_image_check_size(frame->width, frame->height, 0, வெற்று)) < 0)
        திரும்பு ret;

    எனில் (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    எனில் (!frame->linesize[0]) {
        க்கு (முழு i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(frame->linesize, frame->format,
                                          FFALIGN(frame->width, i));
            எனில் (ret < 0)
                திரும்பு ret;
            எனில் (!(frame->linesize[0] & (align-1)))
                நிறுத்து;
        }

        க்கு (முழு i = 0; i < 4 && frame->linesize[i]; i++)
            frame->linesize[i] = FFALIGN(frame->linesize[i], align);
    }

    க்கு (முழு i = 0; i < 4; i++)
        linesizes[i] = frame->linesize[i];

    padded_height = FFALIGN(frame->height, 32);
    எனில் ((ret = av_image_fill_plane_sizes(sizes, frame->format,
                                         padded_height, linesizes)) < 0)
        திரும்பு ret;

    total_size = 4 * plane_padding + 4 * align;
    க்கு (முழு i = 0; i < 4; i++) {
        எனில் (sizes[i] > SIZE_MAX - total_size)
            திரும்பு AVERROR(EINVAL);
        total_size += sizes[i];
    }

    frame->buf[0] = alloc ? alloc(opaque, total_size) : av_buffer_alloc(total_size);
    எனில் (!frame->buf[0]) {
        ret = AVERROR(ENOMEM);
        செல் fail;
    }

    எனில் ((ret = av_image_fill_pointers(frame->data, frame->format, padded_height,
                                      frame->buf[0]->data, frame->linesize)) < 0)
        செல் fail;

    க்கு (முழு i = 1; i < 4; i++) {
        எனில் (frame->data[i])
            frame->data[i] += i * plane_padding;
        frame->data[i] = (uint8_t *)FFALIGN((uintptr_t)frame->data[i], align);
    }

    frame->extended_data = frame->data;

    திரும்பு 0;
fail:
    av_frame_unref(frame);
    திரும்பு ret;
}

நிலையான முழு get_audio_buffer(AVFrame *frame, முழு align)
{
    முழு planar   = av_sample_fmt_is_planar(frame->format);
    முழு channels, planes;
    size_t size;
    முழு ret;

    channels = frame->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    எனில் (!frame->linesize[0]) {
        ret = av_samples_get_buffer_size(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        எனில் (ret < 0)
            திரும்பு ret;
    }

    எனில் (align <= 0)
        align = ALIGN;

    எனில் (planes > AV_இலக்கம்_DATA_POINTERS) {
        frame->extended_data = av_calloc(planes,
                                          அளவு(*frame->extended_data));
        frame->extended_buf  = av_calloc(planes - AV_இலக்கம்_DATA_POINTERS,
                                          அளவு(*frame->extended_buf));
        எனில் (!frame->extended_data || !frame->extended_buf) {
            av_freep(&frame->extended_data);
            av_freep(&frame->extended_buf);
            திரும்பு AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_இலக்கம்_DATA_POINTERS;
    } இல்லையெனில்
        frame->extended_data = frame->data;

    எனில் (frame->linesize[0] > SIZE_MAX - align)
        திரும்பு AVERROR(EINVAL);
    size = frame->linesize[0] + (size_t)align;

    க்கு (முழு i = 0; i < FFMIN(planes, AV_இலக்கம்_DATA_POINTERS); i++) {
        frame->buf[i] = av_buffer_alloc(size);
        எனில் (!frame->buf[i]) {
            av_frame_unref(frame);
            திரும்பு AVERROR(ENOMEM);
        }
        frame->extended_data[i] = frame->data[i] =
            (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->data, align);
    }
    க்கு (முழு i = 0; i < planes - AV_இலக்கம்_DATA_POINTERS; i++) {
        frame->extended_buf[i] = av_buffer_alloc(size);
        எனில் (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            திரும்பு AVERROR(ENOMEM);
        }
        frame->extended_data[i + AV_இலக்கம்_DATA_POINTERS] =
            (uint8_t *)FFALIGN((uintptr_t)frame->extended_buf[i]->data, align);
    }
    திரும்பு 0;

}

முழு av_frame_get_buffer(AVFrame *frame, முழு align)
{
    எனில் (frame->format < 0)
        திரும்பு AVERROR(EINVAL);

    எனில் (frame->width > 0 && frame->height > 0)
        திரும்பு ff_frame_get_video_buffer(frame, align, வெற்று, வெற்று);
    இல்லையெனில் எனில் (frame->nb_samples > 0 &&
             (av_channel_layout_check(&frame->ch_layout)))
        திரும்பு get_audio_buffer(frame, align);

    திரும்பு AVERROR(EINVAL);
}

நிலையான முழு frame_copy_props(AVFrame *dst, மாறிலி AVFrame *src, முழு force_copy)
{
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_ratio    = src->sample_aspect_ratio;
    dst->crop_உச்சி               = src->crop_உச்சி;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_இடது              = src->crop_இடது;
    dst->crop_வலது             = src->crop_வலது;
    dst->pts                    = src->pts;
    dst->duration               = src->duration;
    dst->repeat_pict            = src->repeat_pict;
    dst->sample_rate            = src->sample_rate;
    dst->opaque                 = src->opaque;
    dst->pkt_dts                = src->pkt_dts;
    dst->time_base              = src->time_base;
    dst->quality                = src->quality;
    dst->best_effort_timestamp  = src->best_effort_timestamp;
    dst->flags                  = src->flags;
    dst->decode_error_flags     = src->decode_error_flags;
    dst->color_primaries        = src->color_primaries;
    dst->color_trc              = src->color_trc;
    dst->colorspace             = src->colorspace;
    dst->color_range            = src->color_range;
    dst->chroma_location        = src->chroma_location;
    dst->alpha_mode             = src->alpha_mode;

    av_dict_copy(&dst->metadata, src->metadata, 0);

    க்கு (முழு i = 0; i < src->nb_side_data; i++) {
        மாறிலி AVFrameSideData *sd_src = src->side_data[i];
        AVFrameSideData *sd_dst;
        எனில் (   sd_src->type == AV_FRAME_DATA_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            தொடர்;
        எனில் (force_copy) {
            sd_dst = av_frame_new_side_data(dst, sd_src->type,
                                            sd_src->size);
            எனில் (!sd_dst) {
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                திரும்பு AVERROR(ENOMEM);
            }
            memcpy(sd_dst->data, sd_src->data, sd_src->size);
        } இல்லையெனில் {
            AVBufferRef *ref = av_buffer_ref(sd_src->buf);
            sd_dst = av_frame_new_side_data_from_buf(dst, sd_src->type, ref);
            எனில் (!sd_dst) {
                av_buffer_unref(&ref);
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                திரும்பு AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->private_ref, src->private_ref);
    திரும்பு av_buffer_replace(&dst->opaque_ref, src->opaque_ref);
}

முழு av_frame_ref(AVFrame *dst, மாறிலி AVFrame *src)
{
    முழு ret = 0;

    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = frame_copy_props(dst, src, 0);
    எனில் (ret < 0)
        செல் fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    எனில் (ret < 0)
        செல் fail;

    /* duplicate the frame data if it's not refcounted */
    எனில் (!src->buf[0]) {
        ret = av_frame_get_buffer(dst, 0);
        எனில் (ret < 0)
            செல் fail;

        ret = av_frame_copy(dst, src);
        எனில் (ret < 0)
            செல் fail;

        திரும்பு 0;
    }

    /* ref the buffers */
    க்கு (முழு i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        எனில் (!src->buf[i])
            தொடர்;
        dst->buf[i] = av_buffer_ref(src->buf[i]);
        எனில் (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            செல் fail;
        }
    }

    எனில் (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      அளவு(*dst->extended_buf));
        எனில் (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            செல் fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        க்கு (முழு i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_buffer_ref(src->extended_buf[i]);
            எனில் (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                செல் fail;
            }
        }
    }

    எனில் (src->hw_frames_ctx) {
        dst->hw_frames_ctx = av_buffer_ref(src->hw_frames_ctx);
        எனில் (!dst->hw_frames_ctx) {
            ret = AVERROR(ENOMEM);
            செல் fail;
        }
    }

    /* duplicate extended data */
    எனில் (src->extended_data != src->data) {
        முழு ch = dst->ch_layout.nb_channels;

        எனில் (ch <= 0 || ch > SIZE_MAX / அளவு(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            செல் fail;
        }

        dst->extended_data = av_memdup(src->extended_data, அளவு(*dst->extended_data) * ch);
        எனில் (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            செல் fail;
        }
    } இல்லையெனில்
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     அளவு(src->data));
    memcpy(dst->linesize, src->linesize, அளவு(src->linesize));

    திரும்பு 0;

fail:
    av_frame_unref(dst);
    திரும்பு ret;
}

முழு av_frame_replace(AVFrame *dst, மாறிலி AVFrame *src)
{
    முழு ret = 0;

    எனில் (dst == src)
        திரும்பு AVERROR(EINVAL);

    எனில் (!src->buf[0]) {
        av_frame_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        எனில் (   src->data[0] || src->data[1]
            || src->data[2] || src->data[3])
            திரும்பு av_frame_ref(dst, src);

        ret = frame_copy_props(dst, src, 0);
        எனில் (ret < 0)
            செல் fail;
    }

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    எனில் (ret < 0)
        செல் fail;

    av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
    av_dict_free(&dst->metadata);
    ret = frame_copy_props(dst, src, 0);
    எனில் (ret < 0)
        செல் fail;

    /* replace the buffers */
    க்கு (முழு i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_buffer_replace(&dst->buf[i], src->buf[i]);
        எனில் (ret < 0)
            செல் fail;
    }

    எனில் (src->extended_buf) {
        எனில் (dst->nb_extended_buf != src->nb_extended_buf) {
            முழு nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            வெறுமை *tmp;

            க்கு (முழு i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_buffer_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   அளவு(*dst->extended_buf));
            எனில் (!tmp) {
                ret = AVERROR(ENOMEM);
                செல் fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * அளவு(*dst->extended_buf));
        }

        க்கு (முழு i = 0; i < src->nb_extended_buf; i++) {
            ret = av_buffer_replace(&dst->extended_buf[i], src->extended_buf[i]);
            எனில் (ret < 0)
                செல் fail;
        }
    } இல்லையெனில் எனில் (dst->extended_buf) {
        க்கு (முழு i = 0; i < dst->nb_extended_buf; i++)
            av_buffer_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_buffer_replace(&dst->hw_frames_ctx, src->hw_frames_ctx);
    எனில் (ret < 0)
        செல் fail;

    எனில் (dst->extended_data != dst->data)
        av_freep(&dst->extended_data);

    எனில் (src->extended_data != src->data) {
        முழு ch = dst->ch_layout.nb_channels;

        எனில் (ch <= 0 || ch > SIZE_MAX / அளவு(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            செல் fail;
        }

        dst->extended_data = av_memdup(src->extended_data, அளவு(*dst->extended_data) * ch);
        எனில் (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            செல் fail;
        }
    } இல்லையெனில்
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     அளவு(src->data));
    memcpy(dst->linesize, src->linesize, அளவு(src->linesize));

    திரும்பு 0;

fail:
    av_frame_unref(dst);
    திரும்பு ret;
}

AVFrame *av_frame_clone(மாறிலி AVFrame *src)
{
    AVFrame *ret = av_frame_alloc();

    எனில் (!ret)
        திரும்பு வெற்று;

    எனில் (av_frame_ref(ret, src) < 0)
        av_frame_free(&ret);

    திரும்பு ret;
}

வெறுமை av_frame_unref(AVFrame *frame)
{
    எனில் (!frame)
        திரும்பு;

    av_frame_side_data_free(&frame->side_data, &frame->nb_side_data);

    க்கு (முழு i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_buffer_unref(&frame->buf[i]);
    க்கு (முழு i = 0; i < frame->nb_extended_buf; i++)
        av_buffer_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);

    av_buffer_unref(&frame->hw_frames_ctx);

    av_buffer_unref(&frame->opaque_ref);
    av_refstruct_unref(&frame->private_ref);

    எனில் (frame->extended_data != frame->data)
        av_freep(&frame->extended_data);

    av_channel_layout_uninit(&frame->ch_layout);

    get_frame_defaults(frame);
}

வெறுமை av_frame_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    *dst = *src;
    எனில் (src->extended_data == src->data)
        dst->extended_data = dst->data;
    get_frame_defaults(src);
}

முழு av_frame_is_writable(AVFrame *frame)
{
    முழு ret = 1;

    /* assume non-refcounted frames are not writable */
    எனில் (!frame->buf[0])
        திரும்பு 0;

    க்கு (முழு i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        எனில் (frame->buf[i])
            ret &= !!av_buffer_is_writable(frame->buf[i]);
    க்கு (முழு i = 0; i < frame->nb_extended_buf; i++)
        ret &= !!av_buffer_is_writable(frame->extended_buf[i]);

    திரும்பு ret;
}

முழு av_frame_make_writable(AVFrame *frame)
{
    AVFrame tmp;
    முழு ret;

    எனில் (av_frame_is_writable(frame))
        திரும்பு 0;

    memset(&tmp, 0, அளவு(tmp));
    tmp.format         = frame->format;
    tmp.width          = frame->width;
    tmp.height         = frame->height;
    tmp.nb_samples     = frame->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &frame->ch_layout);
    எனில் (ret < 0) {
        av_frame_unref(&tmp);
        திரும்பு ret;
    }

    எனில் (frame->hw_frames_ctx)
        ret = av_hwframe_get_buffer(frame->hw_frames_ctx, &tmp, 0);
    இல்லையெனில்
        ret = av_frame_get_buffer(&tmp, 0);
    எனில் (ret < 0)
        திரும்பு ret;

    ret = av_frame_copy(&tmp, frame);
    எனில் (ret < 0) {
        av_frame_unref(&tmp);
        திரும்பு ret;
    }

    ret = av_frame_copy_props(&tmp, frame);
    எனில் (ret < 0) {
        av_frame_unref(&tmp);
        திரும்பு ret;
    }

    av_frame_unref(frame);

    *frame = tmp;
    எனில் (tmp.data == tmp.extended_data)
        frame->extended_data = frame->data;

    திரும்பு 0;
}

முழு av_frame_copy_props(AVFrame *dst, மாறிலி AVFrame *src)
{
    திரும்பு frame_copy_props(dst, src, 1);
}

AVBufferRef *av_frame_get_plane_buffer(மாறிலி AVFrame *frame, முழு plane)
{
    uintptr_t data;
    முழு planes;

    எனில் (frame->nb_samples) {
        முழு channels = frame->ch_layout.nb_channels;
        எனில் (!channels)
            திரும்பு வெற்று;
        planes = av_sample_fmt_is_planar(frame->format) ? channels : 1;
    } இல்லையெனில்
        planes = 4;

    எனில் (plane < 0 || plane >= planes || !frame->extended_data[plane])
        திரும்பு வெற்று;
    data = (uintptr_t)frame->extended_data[plane];

    க்கு (முழு i = 0; i < FF_ARRAY_ELEMS(frame->buf) && frame->buf[i]; i++) {
        AVBufferRef *buf = frame->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        எனில் (data >= buf_begin && data < buf_begin + buf->size)
            திரும்பு buf;
    }
    க்கு (முழு i = 0; i < frame->nb_extended_buf; i++) {
        AVBufferRef *buf = frame->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        எனில் (data >= buf_begin && data < buf_begin + buf->size)
            திரும்பு buf;
    }
    திரும்பு வெற்று;
}

AVFrameSideData *av_frame_new_side_data_from_buf(AVFrame *frame,
                                                 எண்ணிக்கை AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    திரும்பு
        ff_frame_side_data_add_from_buf(
            &frame->side_data, &frame->nb_side_data, type, buf);
}

AVFrameSideData *av_frame_new_side_data(AVFrame *frame,
                                        எண்ணிக்கை AVFrameSideDataType type,
                                        size_t size)
{
    AVFrameSideData *ret;
    AVBufferRef *buf = av_buffer_alloc(size);
    ret = av_frame_new_side_data_from_buf(frame, type, buf);
    எனில் (!ret)
        av_buffer_unref(&buf);
    திரும்பு ret;
}

AVFrameSideData *av_frame_get_side_data(மாறிலி AVFrame *frame,
                                        எண்ணிக்கை AVFrameSideDataType type)
{
    திரும்பு (AVFrameSideData *)av_frame_side_data_get(
        frame->side_data, frame->nb_side_data,
        type
    );
}

நிலையான முழு frame_copy_video(AVFrame *dst, மாறிலி AVFrame *src)
{
    முழு planes;

    எனில் (dst->width  < src->width ||
        dst->height < src->height)
        திரும்பு AVERROR(EINVAL);

    எனில் (src->hw_frames_ctx || dst->hw_frames_ctx)
        திரும்பு av_hwframe_transfer_data(dst, src, 0);

    planes = av_pix_fmt_மொத்தம்_planes(dst->format);
    க்கு (முழு i = 0; i < planes; i++)
        எனில் (!dst->data[i] || !src->data[i])
            திரும்பு AVERROR(EINVAL);

    av_image_copy2(dst->data, dst->linesize,
                   src->data, src->linesize,
                   dst->format, src->width, src->height);

    திரும்பு 0;
}

நிலையான முழு frame_copy_audio(AVFrame *dst, மாறிலி AVFrame *src)
{
    முழு planar   = av_sample_fmt_is_planar(dst->format);
    முழு channels = dst->ch_layout.nb_channels;
    முழு planes   = planar ? channels : 1;

    எனில் (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        திரும்பு AVERROR(EINVAL);

    க்கு (முழு i = 0; i < planes; i++)
        எனில் (!dst->extended_data[i] || !src->extended_data[i])
            திரும்பு AVERROR(EINVAL);

    av_samples_copy(dst->extended_data, src->extended_data, 0, 0,
                    dst->nb_samples, channels, dst->format);

    திரும்பு 0;
}

முழு av_frame_copy(AVFrame *dst, மாறிலி AVFrame *src)
{
    எனில் (dst->format != src->format || dst->format < 0)
        திரும்பு AVERROR(EINVAL);

    எனில் (dst->width > 0 && dst->height > 0)
        திரும்பு frame_copy_video(dst, src);
    இல்லையெனில் எனில் (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        திரும்பு frame_copy_audio(dst, src);

    திரும்பு AVERROR(EINVAL);
}

வெறுமை av_frame_remove_side_data(AVFrame *frame, எண்ணிக்கை AVFrameSideDataType type)
{
    av_frame_side_data_remove(&frame->side_data, &frame->nb_side_data, type);
}

நிலையான முழு calc_cropping_offsets(size_t offsets[4], மாறிலி AVFrame *frame,
                                 மாறிலி AVPixFmtDescriptor *desc)
{
    க்கு (முழு i = 0; frame->data[i]; i++) {
        மாறிலி AVComponentDescriptor *comp = வெற்று;
        முழு shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        முழு shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        எனில் (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            நிறுத்து;
        }

        /* find any component descriptor for this plane */
        க்கு (முழு j = 0; j < desc->nb_components; j++) {
            எனில் (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                நிறுத்து;
            }
        }
        எனில் (!comp)
            திரும்பு AVERROR_BUG;

        offsets[i] = (frame->crop_உச்சி  >> shift_y) * frame->linesize[i] +
                     (frame->crop_இடது >> shift_x) * comp->step;
    }

    திரும்பு 0;
}

முழு av_frame_apply_cropping(AVFrame *frame, முழு flags)
{
    மாறிலி AVPixFmtDescriptor *desc;
    size_t offsets[4];
    முழு ret;

    எனில் (!(frame->width > 0 && frame->height > 0))
        திரும்பு AVERROR(EINVAL);

    எனில் (frame->crop_இடது >= INT_MAX - frame->crop_வலது        ||
        frame->crop_உச்சி  >= INT_MAX - frame->crop_bottom       ||
        (frame->crop_இடது + frame->crop_வலது) >= frame->width ||
        (frame->crop_உச்சி + frame->crop_bottom) >= frame->height)
        திரும்பு AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(frame->format);
    எனில் (!desc)
        திரும்பு AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    எனில் (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        frame->width      -= frame->crop_வலது;
        frame->height     -= frame->crop_bottom;
        frame->crop_வலது  = 0;
        frame->crop_bottom = 0;
        திரும்பு 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, frame, desc);
    எனில் (ret < 0)
        திரும்பு ret;

    /* adjust the offsets to avoid breaking alignment */
    எனில் (!(flags & AV_FRAME_CROP_UNALIGNED)) {
        முழு log2_crop_align = frame->crop_இடது ? ff_ctz(frame->crop_இடது) : INT_MAX;
        முழு min_log2_align = INT_MAX;

        க்கு (முழு i = 0; frame->data[i]; i++) {
            முழு log2_align = offsets[i] ? ff_ctz(offsets[i]) : INT_MAX;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        எனில் (min_log2_align < 5 && log2_crop_align != INT_MAX) {
            frame->crop_இடது &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, frame, desc);
            எனில் (ret < 0)
                திரும்பு ret;
        }
    }

    க்கு (முழு i = 0; frame->data[i]; i++)
        frame->data[i] += offsets[i];

    frame->width      -= (frame->crop_இடது + frame->crop_வலது);
    frame->height     -= (frame->crop_உச்சி  + frame->crop_bottom);
    frame->crop_இடது   = 0;
    frame->crop_வலது  = 0;
    frame->crop_உச்சி    = 0;
    frame->crop_bottom = 0;

    திரும்பு 0;
}
