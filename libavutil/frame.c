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

#অন্তর্ভাৱ "channel_layout.h"
#অন্তর্ভাৱ "avassert.h"
#অন্তর্ভাৱ "buffer.h"
#অন্তর্ভাৱ "dict.h"
#অন্তর্ভাৱ "frame.h"
#অন্তর্ভাৱ "frame_internal.h"
#অন্তর্ভাৱ "imgutils.h"
#অন্তর্ভাৱ "mem.h"
#অন্তর্ভাৱ "refstruct.h"
#অন্তর্ভাৱ "samplefmt.h"
#অন্তর্ভাৱ "side_data.h"
#অন্তর্ভাৱ "hwcontext.h"

স্থির শূন্য get_frame_defaults(AVFrame *frame)
{
    memset(frame, 0, পরিমাণ(*frame));

    frame->pts                   =
    frame->pkt_dts               = AV_NOPTS_মান;
    frame->best_effort_timestamp = AV_NOPTS_মান;
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

AVFrame *av_frame_alloc(শূন্য)
{
    AVFrame *frame = av_malloc(পরিমাণ(*frame));

    যদি (!frame)
        ঘূৰাই রিক্ত;

    get_frame_defaults(frame);

    ঘূৰাই frame;
}

শূন্য av_frame_free(AVFrame **frame)
{
    যদি (!frame || !*frame)
        ঘূৰাই;

    av_frame_unref(*frame);
    av_freep(frame);
}

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

পূর্ণাঙ্ক ff_frame_get_video_buffer(AVFrame *frame, পূর্ণাঙ্ক align,
                              AVBufferRef *(*alloc)(শূন্য *opaque, size_t size),
                              শূন্য *opaque)
{
    ধ্রুৱ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    পূর্ণাঙ্ক ret, padded_height;
    পূর্ণাঙ্ক plane_padding;
    ptrdiff_t linesizes[4];
    size_t total_size, sizes[4];

    যদি (!desc)
        ঘূৰাই AVERROR(EINVAL);

    যদি ((ret = av_image_check_size(frame->width, frame->height, 0, রিক্ত)) < 0)
        ঘূৰাই ret;

    যদি (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    যদি (!frame->linesize[0]) {
        বাবে (পূর্ণাঙ্ক i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(frame->linesize, frame->format,
                                          FFALIGN(frame->width, i));
            যদি (ret < 0)
                ঘূৰাই ret;
            যদি (!(frame->linesize[0] & (align-1)))
                ভঙ্গ;
        }

        বাবে (পূর্ণাঙ্ক i = 0; i < 4 && frame->linesize[i]; i++)
            frame->linesize[i] = FFALIGN(frame->linesize[i], align);
    }

    বাবে (পূর্ণাঙ্ক i = 0; i < 4; i++)
        linesizes[i] = frame->linesize[i];

    padded_height = FFALIGN(frame->height, 32);
    যদি ((ret = av_image_fill_plane_sizes(sizes, frame->format,
                                         padded_height, linesizes)) < 0)
        ঘূৰাই ret;

    total_size = 4 * plane_padding + 4 * align;
    বাবে (পূর্ণাঙ্ক i = 0; i < 4; i++) {
        যদি (sizes[i] > SIZE_MAX - total_size)
            ঘূৰাই AVERROR(EINVAL);
        total_size += sizes[i];
    }

    frame->buf[0] = alloc ? alloc(opaque, total_size) : av_buffer_alloc(total_size);
    যদি (!frame->buf[0]) {
        ret = AVERROR(ENOMEM);
        গচ্ছ fail;
    }

    যদি ((ret = av_image_fill_pointers(frame->data, frame->format, padded_height,
                                      frame->buf[0]->data, frame->linesize)) < 0)
        গচ্ছ fail;

    বাবে (পূর্ণাঙ্ক i = 1; i < 4; i++) {
        যদি (frame->data[i])
            frame->data[i] += i * plane_padding;
        frame->data[i] = (uint8_t *)FFALIGN((uintptr_t)frame->data[i], align);
    }

    frame->extended_data = frame->data;

    ঘূৰাই 0;
fail:
    av_frame_unref(frame);
    ঘূৰাই ret;
}

স্থির পূর্ণাঙ্ক get_audio_buffer(AVFrame *frame, পূর্ণাঙ্ক align)
{
    পূর্ণাঙ্ক planar   = av_sample_fmt_is_planar(frame->format);
    পূর্ণাঙ্ক channels, planes;
    size_t size;
    পূর্ণাঙ্ক ret;

    channels = frame->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    যদি (!frame->linesize[0]) {
        ret = av_samples_get_buffer_size(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        যদি (ret < 0)
            ঘূৰাই ret;
    }

    যদি (align <= 0)
        align = ALIGN;

    যদি (planes > AV_অঙ্ক_DATA_POINTERS) {
        frame->extended_data = av_calloc(planes,
                                          পরিমাণ(*frame->extended_data));
        frame->extended_buf  = av_calloc(planes - AV_অঙ্ক_DATA_POINTERS,
                                          পরিমাণ(*frame->extended_buf));
        যদি (!frame->extended_data || !frame->extended_buf) {
            av_freep(&frame->extended_data);
            av_freep(&frame->extended_buf);
            ঘূৰাই AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_অঙ্ক_DATA_POINTERS;
    } অন্যথা
        frame->extended_data = frame->data;

    যদি (frame->linesize[0] > SIZE_MAX - align)
        ঘূৰাই AVERROR(EINVAL);
    size = frame->linesize[0] + (size_t)align;

    বাবে (পূর্ণাঙ্ক i = 0; i < FFMIN(planes, AV_অঙ্ক_DATA_POINTERS); i++) {
        frame->buf[i] = av_buffer_alloc(size);
        যদি (!frame->buf[i]) {
            av_frame_unref(frame);
            ঘূৰাই AVERROR(ENOMEM);
        }
        frame->extended_data[i] = frame->data[i] =
            (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->data, align);
    }
    বাবে (পূর্ণাঙ্ক i = 0; i < planes - AV_অঙ্ক_DATA_POINTERS; i++) {
        frame->extended_buf[i] = av_buffer_alloc(size);
        যদি (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            ঘূৰাই AVERROR(ENOMEM);
        }
        frame->extended_data[i + AV_অঙ্ক_DATA_POINTERS] =
            (uint8_t *)FFALIGN((uintptr_t)frame->extended_buf[i]->data, align);
    }
    ঘূৰাই 0;

}

পূর্ণাঙ্ক av_frame_get_buffer(AVFrame *frame, পূর্ণাঙ্ক align)
{
    যদি (frame->format < 0)
        ঘূৰাই AVERROR(EINVAL);

    যদি (frame->width > 0 && frame->height > 0)
        ঘূৰাই ff_frame_get_video_buffer(frame, align, রিক্ত, রিক্ত);
    অন্যথা যদি (frame->nb_samples > 0 &&
             (av_channel_layout_check(&frame->ch_layout)))
        ঘূৰাই get_audio_buffer(frame, align);

    ঘূৰাই AVERROR(EINVAL);
}

স্থির পূর্ণাঙ্ক frame_copy_props(AVFrame *dst, ধ্রুৱ AVFrame *src, পূর্ণাঙ্ক force_copy)
{
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_ratio    = src->sample_aspect_ratio;
    dst->crop_শীৰ্ষ               = src->crop_শীৰ্ষ;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_বাম              = src->crop_বাম;
    dst->crop_ডান             = src->crop_ডান;
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

    বাবে (পূর্ণাঙ্ক i = 0; i < src->nb_side_data; i++) {
        ধ্রুৱ AVFrameSideData *sd_src = src->side_data[i];
        AVFrameSideData *sd_dst;
        যদি (   sd_src->type == AV_FRAME_DATA_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            অনুৱর্ত;
        যদি (force_copy) {
            sd_dst = av_frame_new_side_data(dst, sd_src->type,
                                            sd_src->size);
            যদি (!sd_dst) {
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                ঘূৰাই AVERROR(ENOMEM);
            }
            memcpy(sd_dst->data, sd_src->data, sd_src->size);
        } অন্যথা {
            AVBufferRef *ref = av_buffer_ref(sd_src->buf);
            sd_dst = av_frame_new_side_data_from_buf(dst, sd_src->type, ref);
            যদি (!sd_dst) {
                av_buffer_unref(&ref);
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                ঘূৰাই AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->private_ref, src->private_ref);
    ঘূৰাই av_buffer_replace(&dst->opaque_ref, src->opaque_ref);
}

পূর্ণাঙ্ক av_frame_ref(AVFrame *dst, ধ্রুৱ AVFrame *src)
{
    পূর্ণাঙ্ক ret = 0;

    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = frame_copy_props(dst, src, 0);
    যদি (ret < 0)
        গচ্ছ fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    যদি (ret < 0)
        গচ্ছ fail;

    /* duplicate the frame data if it's not refcounted */
    যদি (!src->buf[0]) {
        ret = av_frame_get_buffer(dst, 0);
        যদি (ret < 0)
            গচ্ছ fail;

        ret = av_frame_copy(dst, src);
        যদি (ret < 0)
            গচ্ছ fail;

        ঘূৰাই 0;
    }

    /* ref the buffers */
    বাবে (পূর্ণাঙ্ক i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        যদি (!src->buf[i])
            অনুৱর্ত;
        dst->buf[i] = av_buffer_ref(src->buf[i]);
        যদি (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            গচ্ছ fail;
        }
    }

    যদি (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      পরিমাণ(*dst->extended_buf));
        যদি (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            গচ্ছ fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        বাবে (পূর্ণাঙ্ক i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_buffer_ref(src->extended_buf[i]);
            যদি (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                গচ্ছ fail;
            }
        }
    }

    যদি (src->hw_frames_ctx) {
        dst->hw_frames_ctx = av_buffer_ref(src->hw_frames_ctx);
        যদি (!dst->hw_frames_ctx) {
            ret = AVERROR(ENOMEM);
            গচ্ছ fail;
        }
    }

    /* duplicate extended data */
    যদি (src->extended_data != src->data) {
        পূর্ণাঙ্ক ch = dst->ch_layout.nb_channels;

        যদি (ch <= 0 || ch > SIZE_MAX / পরিমাণ(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            গচ্ছ fail;
        }

        dst->extended_data = av_memdup(src->extended_data, পরিমাণ(*dst->extended_data) * ch);
        যদি (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            গচ্ছ fail;
        }
    } অন্যথা
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     পরিমাণ(src->data));
    memcpy(dst->linesize, src->linesize, পরিমাণ(src->linesize));

    ঘূৰাই 0;

fail:
    av_frame_unref(dst);
    ঘূৰাই ret;
}

পূর্ণাঙ্ক av_frame_replace(AVFrame *dst, ধ্রুৱ AVFrame *src)
{
    পূর্ণাঙ্ক ret = 0;

    যদি (dst == src)
        ঘূৰাই AVERROR(EINVAL);

    যদি (!src->buf[0]) {
        av_frame_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        যদি (   src->data[0] || src->data[1]
            || src->data[2] || src->data[3])
            ঘূৰাই av_frame_ref(dst, src);

        ret = frame_copy_props(dst, src, 0);
        যদি (ret < 0)
            গচ্ছ fail;
    }

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    যদি (ret < 0)
        গচ্ছ fail;

    av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
    av_dict_free(&dst->metadata);
    ret = frame_copy_props(dst, src, 0);
    যদি (ret < 0)
        গচ্ছ fail;

    /* replace the buffers */
    বাবে (পূর্ণাঙ্ক i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_buffer_replace(&dst->buf[i], src->buf[i]);
        যদি (ret < 0)
            গচ্ছ fail;
    }

    যদি (src->extended_buf) {
        যদি (dst->nb_extended_buf != src->nb_extended_buf) {
            পূর্ণাঙ্ক nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            শূন্য *tmp;

            বাবে (পূর্ণাঙ্ক i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_buffer_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   পরিমাণ(*dst->extended_buf));
            যদি (!tmp) {
                ret = AVERROR(ENOMEM);
                গচ্ছ fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * পরিমাণ(*dst->extended_buf));
        }

        বাবে (পূর্ণাঙ্ক i = 0; i < src->nb_extended_buf; i++) {
            ret = av_buffer_replace(&dst->extended_buf[i], src->extended_buf[i]);
            যদি (ret < 0)
                গচ্ছ fail;
        }
    } অন্যথা যদি (dst->extended_buf) {
        বাবে (পূর্ণাঙ্ক i = 0; i < dst->nb_extended_buf; i++)
            av_buffer_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_buffer_replace(&dst->hw_frames_ctx, src->hw_frames_ctx);
    যদি (ret < 0)
        গচ্ছ fail;

    যদি (dst->extended_data != dst->data)
        av_freep(&dst->extended_data);

    যদি (src->extended_data != src->data) {
        পূর্ণাঙ্ক ch = dst->ch_layout.nb_channels;

        যদি (ch <= 0 || ch > SIZE_MAX / পরিমাণ(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            গচ্ছ fail;
        }

        dst->extended_data = av_memdup(src->extended_data, পরিমাণ(*dst->extended_data) * ch);
        যদি (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            গচ্ছ fail;
        }
    } অন্যথা
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     পরিমাণ(src->data));
    memcpy(dst->linesize, src->linesize, পরিমাণ(src->linesize));

    ঘূৰাই 0;

fail:
    av_frame_unref(dst);
    ঘূৰাই ret;
}

AVFrame *av_frame_clone(ধ্রুৱ AVFrame *src)
{
    AVFrame *ret = av_frame_alloc();

    যদি (!ret)
        ঘূৰাই রিক্ত;

    যদি (av_frame_ref(ret, src) < 0)
        av_frame_free(&ret);

    ঘূৰাই ret;
}

শূন্য av_frame_unref(AVFrame *frame)
{
    যদি (!frame)
        ঘূৰাই;

    av_frame_side_data_free(&frame->side_data, &frame->nb_side_data);

    বাবে (পূর্ণাঙ্ক i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_buffer_unref(&frame->buf[i]);
    বাবে (পূর্ণাঙ্ক i = 0; i < frame->nb_extended_buf; i++)
        av_buffer_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);

    av_buffer_unref(&frame->hw_frames_ctx);

    av_buffer_unref(&frame->opaque_ref);
    av_refstruct_unref(&frame->private_ref);

    যদি (frame->extended_data != frame->data)
        av_freep(&frame->extended_data);

    av_channel_layout_uninit(&frame->ch_layout);

    get_frame_defaults(frame);
}

শূন্য av_frame_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    *dst = *src;
    যদি (src->extended_data == src->data)
        dst->extended_data = dst->data;
    get_frame_defaults(src);
}

পূর্ণাঙ্ক av_frame_is_writable(AVFrame *frame)
{
    পূর্ণাঙ্ক ret = 1;

    /* assume non-refcounted frames are not writable */
    যদি (!frame->buf[0])
        ঘূৰাই 0;

    বাবে (পূর্ণাঙ্ক i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        যদি (frame->buf[i])
            ret &= !!av_buffer_is_writable(frame->buf[i]);
    বাবে (পূর্ণাঙ্ক i = 0; i < frame->nb_extended_buf; i++)
        ret &= !!av_buffer_is_writable(frame->extended_buf[i]);

    ঘূৰাই ret;
}

পূর্ণাঙ্ক av_frame_make_writable(AVFrame *frame)
{
    AVFrame tmp;
    পূর্ণাঙ্ক ret;

    যদি (av_frame_is_writable(frame))
        ঘূৰাই 0;

    memset(&tmp, 0, পরিমাণ(tmp));
    tmp.format         = frame->format;
    tmp.width          = frame->width;
    tmp.height         = frame->height;
    tmp.nb_samples     = frame->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &frame->ch_layout);
    যদি (ret < 0) {
        av_frame_unref(&tmp);
        ঘূৰাই ret;
    }

    যদি (frame->hw_frames_ctx)
        ret = av_hwframe_get_buffer(frame->hw_frames_ctx, &tmp, 0);
    অন্যথা
        ret = av_frame_get_buffer(&tmp, 0);
    যদি (ret < 0)
        ঘূৰাই ret;

    ret = av_frame_copy(&tmp, frame);
    যদি (ret < 0) {
        av_frame_unref(&tmp);
        ঘূৰাই ret;
    }

    ret = av_frame_copy_props(&tmp, frame);
    যদি (ret < 0) {
        av_frame_unref(&tmp);
        ঘূৰাই ret;
    }

    av_frame_unref(frame);

    *frame = tmp;
    যদি (tmp.data == tmp.extended_data)
        frame->extended_data = frame->data;

    ঘূৰাই 0;
}

পূর্ণাঙ্ক av_frame_copy_props(AVFrame *dst, ধ্রুৱ AVFrame *src)
{
    ঘূৰাই frame_copy_props(dst, src, 1);
}

AVBufferRef *av_frame_get_plane_buffer(ধ্রুৱ AVFrame *frame, পূর্ণাঙ্ক plane)
{
    uintptr_t data;
    পূর্ণাঙ্ক planes;

    যদি (frame->nb_samples) {
        পূর্ণাঙ্ক channels = frame->ch_layout.nb_channels;
        যদি (!channels)
            ঘূৰাই রিক্ত;
        planes = av_sample_fmt_is_planar(frame->format) ? channels : 1;
    } অন্যথা
        planes = 4;

    যদি (plane < 0 || plane >= planes || !frame->extended_data[plane])
        ঘূৰাই রিক্ত;
    data = (uintptr_t)frame->extended_data[plane];

    বাবে (পূর্ণাঙ্ক i = 0; i < FF_ARRAY_ELEMS(frame->buf) && frame->buf[i]; i++) {
        AVBufferRef *buf = frame->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        যদি (data >= buf_begin && data < buf_begin + buf->size)
            ঘূৰাই buf;
    }
    বাবে (পূর্ণাঙ্ক i = 0; i < frame->nb_extended_buf; i++) {
        AVBufferRef *buf = frame->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        যদি (data >= buf_begin && data < buf_begin + buf->size)
            ঘূৰাই buf;
    }
    ঘূৰাই রিক্ত;
}

AVFrameSideData *av_frame_new_side_data_from_buf(AVFrame *frame,
                                                 গণনা AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    ঘূৰাই
        ff_frame_side_data_add_from_buf(
            &frame->side_data, &frame->nb_side_data, type, buf);
}

AVFrameSideData *av_frame_new_side_data(AVFrame *frame,
                                        গণনা AVFrameSideDataType type,
                                        size_t size)
{
    AVFrameSideData *ret;
    AVBufferRef *buf = av_buffer_alloc(size);
    ret = av_frame_new_side_data_from_buf(frame, type, buf);
    যদি (!ret)
        av_buffer_unref(&buf);
    ঘূৰাই ret;
}

AVFrameSideData *av_frame_get_side_data(ধ্রুৱ AVFrame *frame,
                                        গণনা AVFrameSideDataType type)
{
    ঘূৰাই (AVFrameSideData *)av_frame_side_data_get(
        frame->side_data, frame->nb_side_data,
        type
    );
}

স্থির পূর্ণাঙ্ক frame_copy_video(AVFrame *dst, ধ্রুৱ AVFrame *src)
{
    পূর্ণাঙ্ক planes;

    যদি (dst->width  < src->width ||
        dst->height < src->height)
        ঘূৰাই AVERROR(EINVAL);

    যদি (src->hw_frames_ctx || dst->hw_frames_ctx)
        ঘূৰাই av_hwframe_transfer_data(dst, src, 0);

    planes = av_pix_fmt_গুনতি_planes(dst->format);
    বাবে (পূর্ণাঙ্ক i = 0; i < planes; i++)
        যদি (!dst->data[i] || !src->data[i])
            ঘূৰাই AVERROR(EINVAL);

    av_image_copy2(dst->data, dst->linesize,
                   src->data, src->linesize,
                   dst->format, src->width, src->height);

    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক frame_copy_audio(AVFrame *dst, ধ্রুৱ AVFrame *src)
{
    পূর্ণাঙ্ক planar   = av_sample_fmt_is_planar(dst->format);
    পূর্ণাঙ্ক channels = dst->ch_layout.nb_channels;
    পূর্ণাঙ্ক planes   = planar ? channels : 1;

    যদি (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        ঘূৰাই AVERROR(EINVAL);

    বাবে (পূর্ণাঙ্ক i = 0; i < planes; i++)
        যদি (!dst->extended_data[i] || !src->extended_data[i])
            ঘূৰাই AVERROR(EINVAL);

    av_samples_copy(dst->extended_data, src->extended_data, 0, 0,
                    dst->nb_samples, channels, dst->format);

    ঘূৰাই 0;
}

পূর্ণাঙ্ক av_frame_copy(AVFrame *dst, ধ্রুৱ AVFrame *src)
{
    যদি (dst->format != src->format || dst->format < 0)
        ঘূৰাই AVERROR(EINVAL);

    যদি (dst->width > 0 && dst->height > 0)
        ঘূৰাই frame_copy_video(dst, src);
    অন্যথা যদি (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        ঘূৰাই frame_copy_audio(dst, src);

    ঘূৰাই AVERROR(EINVAL);
}

শূন্য av_frame_remove_side_data(AVFrame *frame, গণনা AVFrameSideDataType type)
{
    av_frame_side_data_remove(&frame->side_data, &frame->nb_side_data, type);
}

স্থির পূর্ণাঙ্ক calc_cropping_offsets(size_t offsets[4], ধ্রুৱ AVFrame *frame,
                                 ধ্রুৱ AVPixFmtDescriptor *desc)
{
    বাবে (পূর্ণাঙ্ক i = 0; frame->data[i]; i++) {
        ধ্রুৱ AVComponentDescriptor *comp = রিক্ত;
        পূর্ণাঙ্ক shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        পূর্ণাঙ্ক shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        যদি (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            ভঙ্গ;
        }

        /* find any component descriptor for this plane */
        বাবে (পূর্ণাঙ্ক j = 0; j < desc->nb_components; j++) {
            যদি (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                ভঙ্গ;
            }
        }
        যদি (!comp)
            ঘূৰাই AVERROR_BUG;

        offsets[i] = (frame->crop_শীৰ্ষ  >> shift_y) * frame->linesize[i] +
                     (frame->crop_বাম >> shift_x) * comp->step;
    }

    ঘূৰাই 0;
}

পূর্ণাঙ্ক av_frame_apply_cropping(AVFrame *frame, পূর্ণাঙ্ক flags)
{
    ধ্রুৱ AVPixFmtDescriptor *desc;
    size_t offsets[4];
    পূর্ণাঙ্ক ret;

    যদি (!(frame->width > 0 && frame->height > 0))
        ঘূৰাই AVERROR(EINVAL);

    যদি (frame->crop_বাম >= INT_MAX - frame->crop_ডান        ||
        frame->crop_শীৰ্ষ  >= INT_MAX - frame->crop_bottom       ||
        (frame->crop_বাম + frame->crop_ডান) >= frame->width ||
        (frame->crop_শীৰ্ষ + frame->crop_bottom) >= frame->height)
        ঘূৰাই AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(frame->format);
    যদি (!desc)
        ঘূৰাই AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    যদি (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        frame->width      -= frame->crop_ডান;
        frame->height     -= frame->crop_bottom;
        frame->crop_ডান  = 0;
        frame->crop_bottom = 0;
        ঘূৰাই 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, frame, desc);
    যদি (ret < 0)
        ঘূৰাই ret;

    /* adjust the offsets to avoid breaking alignment */
    যদি (!(flags & AV_FRAME_CROP_UNALIGNED)) {
        পূর্ণাঙ্ক log2_crop_align = frame->crop_বাম ? ff_ctz(frame->crop_বাম) : INT_MAX;
        পূর্ণাঙ্ক min_log2_align = INT_MAX;

        বাবে (পূর্ণাঙ্ক i = 0; frame->data[i]; i++) {
            পূর্ণাঙ্ক log2_align = offsets[i] ? ff_ctz(offsets[i]) : INT_MAX;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        যদি (min_log2_align < 5 && log2_crop_align != INT_MAX) {
            frame->crop_বাম &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, frame, desc);
            যদি (ret < 0)
                ঘূৰাই ret;
        }
    }

    বাবে (পূর্ণাঙ্ক i = 0; frame->data[i]; i++)
        frame->data[i] += offsets[i];

    frame->width      -= (frame->crop_বাম + frame->crop_ডান);
    frame->height     -= (frame->crop_শীৰ্ষ  + frame->crop_bottom);
    frame->crop_বাম   = 0;
    frame->crop_ডান  = 0;
    frame->crop_শীৰ্ষ    = 0;
    frame->crop_bottom = 0;

    ঘূৰাই 0;
}
