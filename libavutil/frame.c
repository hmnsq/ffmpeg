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

#അന്തര്ഭാവ "channel_layout.h"
#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ "buffer.h"
#അന്തര്ഭാവ "dict.h"
#അന്തര്ഭാവ "frame.h"
#അന്തര്ഭാവ "frame_internal.h"
#അന്തര്ഭാവ "imgutils.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "refstruct.h"
#അന്തര്ഭാവ "samplefmt.h"
#അന്തര്ഭാവ "side_data.h"
#അന്തര്ഭാവ "hwcontext.h"

സ്ഥിതം ശൂന്യം get_frame_defaults(AVFrame *frame)
{
    memset(frame, 0, വലുപ്പം(*frame));

    frame->pts                   =
    frame->pkt_dts               = AV_NOPTS_മൂല്യം;
    frame->best_effort_timestamp = AV_NOPTS_മൂല്യം;
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

AVFrame *av_frame_alloc(ശൂന്യം)
{
    AVFrame *frame = av_malloc(വലുപ്പം(*frame));

    എങ്കിൽ (!frame)
        തിരികെ ശൂന്യ;

    get_frame_defaults(frame);

    തിരികെ frame;
}

ശൂന്യം av_frame_free(AVFrame **frame)
{
    എങ്കിൽ (!frame || !*frame)
        തിരികെ;

    av_frame_unref(*frame);
    av_freep(frame);
}

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : 32)

പൂർണ്ണസംഖ്യ ff_frame_get_video_buffer(AVFrame *frame, പൂർണ്ണസംഖ്യ align,
                              AVBufferRef *(*alloc)(ശൂന്യം *opaque, size_t size),
                              ശൂന്യം *opaque)
{
    സ്ഥിരം AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    പൂർണ്ണസംഖ്യ ret, padded_height;
    പൂർണ്ണസംഖ്യ plane_padding;
    ptrdiff_t linesizes[4];
    size_t total_size, sizes[4];

    എങ്കിൽ (!desc)
        തിരികെ AVERROR(EINVAL);

    എങ്കിൽ ((ret = av_image_check_size(frame->width, frame->height, 0, ശൂന്യ)) < 0)
        തിരികെ ret;

    എങ്കിൽ (align <= 0)
        align = ALIGN;
    plane_padding = FFMAX(ALIGN, align);

    എങ്കിൽ (!frame->linesize[0]) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 1; i <= align; i += i) {
            ret = av_image_fill_linesizes(frame->linesize, frame->format,
                                          FFALIGN(frame->width, i));
            എങ്കിൽ (ret < 0)
                തിരികെ ret;
            എങ്കിൽ (!(frame->linesize[0] & (align-1)))
                നിർത്തുക;
        }

        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < 4 && frame->linesize[i]; i++)
            frame->linesize[i] = FFALIGN(frame->linesize[i], align);
    }

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < 4; i++)
        linesizes[i] = frame->linesize[i];

    padded_height = FFALIGN(frame->height, 32);
    എങ്കിൽ ((ret = av_image_fill_plane_sizes(sizes, frame->format,
                                         padded_height, linesizes)) < 0)
        തിരികെ ret;

    total_size = 4 * plane_padding + 4 * align;
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < 4; i++) {
        എങ്കിൽ (sizes[i] > SIZE_MAX - total_size)
            തിരികെ AVERROR(EINVAL);
        total_size += sizes[i];
    }

    frame->buf[0] = alloc ? alloc(opaque, total_size) : av_buffer_alloc(total_size);
    എങ്കിൽ (!frame->buf[0]) {
        ret = AVERROR(ENOMEM);
        പോകുക fail;
    }

    എങ്കിൽ ((ret = av_image_fill_pointers(frame->data, frame->format, padded_height,
                                      frame->buf[0]->data, frame->linesize)) < 0)
        പോകുക fail;

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 1; i < 4; i++) {
        എങ്കിൽ (frame->data[i])
            frame->data[i] += i * plane_padding;
        frame->data[i] = (uint8_t *)FFALIGN((uintptr_t)frame->data[i], align);
    }

    frame->extended_data = frame->data;

    തിരികെ 0;
fail:
    av_frame_unref(frame);
    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ get_audio_buffer(AVFrame *frame, പൂർണ്ണസംഖ്യ align)
{
    പൂർണ്ണസംഖ്യ planar   = av_sample_fmt_is_planar(frame->format);
    പൂർണ്ണസംഖ്യ channels, planes;
    size_t size;
    പൂർണ്ണസംഖ്യ ret;

    channels = frame->ch_layout.nb_channels;
    planes   = planar ? channels : 1;
    എങ്കിൽ (!frame->linesize[0]) {
        ret = av_samples_get_buffer_size(&frame->linesize[0], channels,
                                         frame->nb_samples, frame->format,
                                         align);
        എങ്കിൽ (ret < 0)
            തിരികെ ret;
    }

    എങ്കിൽ (align <= 0)
        align = ALIGN;

    എങ്കിൽ (planes > AV_അക്കം_DATA_POINTERS) {
        frame->extended_data = av_calloc(planes,
                                          വലുപ്പം(*frame->extended_data));
        frame->extended_buf  = av_calloc(planes - AV_അക്കം_DATA_POINTERS,
                                          വലുപ്പം(*frame->extended_buf));
        എങ്കിൽ (!frame->extended_data || !frame->extended_buf) {
            av_freep(&frame->extended_data);
            av_freep(&frame->extended_buf);
            തിരികെ AVERROR(ENOMEM);
        }
        frame->nb_extended_buf = planes - AV_അക്കം_DATA_POINTERS;
    } അല്ലെങ്കിൽ
        frame->extended_data = frame->data;

    എങ്കിൽ (frame->linesize[0] > SIZE_MAX - align)
        തിരികെ AVERROR(EINVAL);
    size = frame->linesize[0] + (size_t)align;

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < FFMIN(planes, AV_അക്കം_DATA_POINTERS); i++) {
        frame->buf[i] = av_buffer_alloc(size);
        എങ്കിൽ (!frame->buf[i]) {
            av_frame_unref(frame);
            തിരികെ AVERROR(ENOMEM);
        }
        frame->extended_data[i] = frame->data[i] =
            (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->data, align);
    }
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < planes - AV_അക്കം_DATA_POINTERS; i++) {
        frame->extended_buf[i] = av_buffer_alloc(size);
        എങ്കിൽ (!frame->extended_buf[i]) {
            av_frame_unref(frame);
            തിരികെ AVERROR(ENOMEM);
        }
        frame->extended_data[i + AV_അക്കം_DATA_POINTERS] =
            (uint8_t *)FFALIGN((uintptr_t)frame->extended_buf[i]->data, align);
    }
    തിരികെ 0;

}

പൂർണ്ണസംഖ്യ av_frame_get_buffer(AVFrame *frame, പൂർണ്ണസംഖ്യ align)
{
    എങ്കിൽ (frame->format < 0)
        തിരികെ AVERROR(EINVAL);

    എങ്കിൽ (frame->width > 0 && frame->height > 0)
        തിരികെ ff_frame_get_video_buffer(frame, align, ശൂന്യ, ശൂന്യ);
    അല്ലെങ്കിൽ എങ്കിൽ (frame->nb_samples > 0 &&
             (av_channel_layout_check(&frame->ch_layout)))
        തിരികെ get_audio_buffer(frame, align);

    തിരികെ AVERROR(EINVAL);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ frame_copy_props(AVFrame *dst, സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ force_copy)
{
    dst->pict_type              = src->pict_type;
    dst->sample_aspect_ratio    = src->sample_aspect_ratio;
    dst->crop_മുകൾ               = src->crop_മുകൾ;
    dst->crop_bottom            = src->crop_bottom;
    dst->crop_ഇടത്              = src->crop_ഇടത്;
    dst->crop_വലത്             = src->crop_വലത്;
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

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < src->nb_side_data; i++) {
        സ്ഥിരം AVFrameSideData *sd_src = src->side_data[i];
        AVFrameSideData *sd_dst;
        എങ്കിൽ (   sd_src->type == AV_FRAME_DATA_PANSCAN
            && (src->width != dst->width || src->height != dst->height))
            തുടരുക;
        എങ്കിൽ (force_copy) {
            sd_dst = av_frame_new_side_data(dst, sd_src->type,
                                            sd_src->size);
            എങ്കിൽ (!sd_dst) {
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                തിരികെ AVERROR(ENOMEM);
            }
            memcpy(sd_dst->data, sd_src->data, sd_src->size);
        } അല്ലെങ്കിൽ {
            AVBufferRef *ref = av_buffer_ref(sd_src->buf);
            sd_dst = av_frame_new_side_data_from_buf(dst, sd_src->type, ref);
            എങ്കിൽ (!sd_dst) {
                av_buffer_unref(&ref);
                av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
                തിരികെ AVERROR(ENOMEM);
            }
        }
        av_dict_copy(&sd_dst->metadata, sd_src->metadata, 0);
    }

    av_refstruct_replace(&dst->private_ref, src->private_ref);
    തിരികെ av_buffer_replace(&dst->opaque_ref, src->opaque_ref);
}

പൂർണ്ണസംഖ്യ av_frame_ref(AVFrame *dst, സ്ഥിരം AVFrame *src)
{
    പൂർണ്ണസംഖ്യ ret = 0;

    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = frame_copy_props(dst, src, 0);
    എങ്കിൽ (ret < 0)
        പോകുക fail;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    എങ്കിൽ (ret < 0)
        പോകുക fail;

    /* duplicate the frame data if it's not refcounted */
    എങ്കിൽ (!src->buf[0]) {
        ret = av_frame_get_buffer(dst, 0);
        എങ്കിൽ (ret < 0)
            പോകുക fail;

        ret = av_frame_copy(dst, src);
        എങ്കിൽ (ret < 0)
            പോകുക fail;

        തിരികെ 0;
    }

    /* ref the buffers */
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        എങ്കിൽ (!src->buf[i])
            തുടരുക;
        dst->buf[i] = av_buffer_ref(src->buf[i]);
        എങ്കിൽ (!dst->buf[i]) {
            ret = AVERROR(ENOMEM);
            പോകുക fail;
        }
    }

    എങ്കിൽ (src->extended_buf) {
        dst->extended_buf = av_calloc(src->nb_extended_buf,
                                      വലുപ്പം(*dst->extended_buf));
        എങ്കിൽ (!dst->extended_buf) {
            ret = AVERROR(ENOMEM);
            പോകുക fail;
        }
        dst->nb_extended_buf = src->nb_extended_buf;

        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < src->nb_extended_buf; i++) {
            dst->extended_buf[i] = av_buffer_ref(src->extended_buf[i]);
            എങ്കിൽ (!dst->extended_buf[i]) {
                ret = AVERROR(ENOMEM);
                പോകുക fail;
            }
        }
    }

    എങ്കിൽ (src->hw_frames_ctx) {
        dst->hw_frames_ctx = av_buffer_ref(src->hw_frames_ctx);
        എങ്കിൽ (!dst->hw_frames_ctx) {
            ret = AVERROR(ENOMEM);
            പോകുക fail;
        }
    }

    /* duplicate extended data */
    എങ്കിൽ (src->extended_data != src->data) {
        പൂർണ്ണസംഖ്യ ch = dst->ch_layout.nb_channels;

        എങ്കിൽ (ch <= 0 || ch > SIZE_MAX / വലുപ്പം(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            പോകുക fail;
        }

        dst->extended_data = av_memdup(src->extended_data, വലുപ്പം(*dst->extended_data) * ch);
        എങ്കിൽ (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            പോകുക fail;
        }
    } അല്ലെങ്കിൽ
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     വലുപ്പം(src->data));
    memcpy(dst->linesize, src->linesize, വലുപ്പം(src->linesize));

    തിരികെ 0;

fail:
    av_frame_unref(dst);
    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_frame_replace(AVFrame *dst, സ്ഥിരം AVFrame *src)
{
    പൂർണ്ണസംഖ്യ ret = 0;

    എങ്കിൽ (dst == src)
        തിരികെ AVERROR(EINVAL);

    എങ്കിൽ (!src->buf[0]) {
        av_frame_unref(dst);

        /* duplicate the frame data if it's not refcounted */
        എങ്കിൽ (   src->data[0] || src->data[1]
            || src->data[2] || src->data[3])
            തിരികെ av_frame_ref(dst, src);

        ret = frame_copy_props(dst, src, 0);
        എങ്കിൽ (ret < 0)
            പോകുക fail;
    }

    dst->format         = src->format;
    dst->width          = src->width;
    dst->height         = src->height;
    dst->nb_samples     = src->nb_samples;

    ret = av_channel_layout_copy(&dst->ch_layout, &src->ch_layout);
    എങ്കിൽ (ret < 0)
        പോകുക fail;

    av_frame_side_data_free(&dst->side_data, &dst->nb_side_data);
    av_dict_free(&dst->metadata);
    ret = frame_copy_props(dst, src, 0);
    എങ്കിൽ (ret < 0)
        പോകുക fail;

    /* replace the buffers */
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < FF_ARRAY_ELEMS(src->buf); i++) {
        ret = av_buffer_replace(&dst->buf[i], src->buf[i]);
        എങ്കിൽ (ret < 0)
            പോകുക fail;
    }

    എങ്കിൽ (src->extended_buf) {
        എങ്കിൽ (dst->nb_extended_buf != src->nb_extended_buf) {
            പൂർണ്ണസംഖ്യ nb_extended_buf = FFMIN(dst->nb_extended_buf, src->nb_extended_buf);
            ശൂന്യം *tmp;

            വേണ്ടി (പൂർണ്ണസംഖ്യ i = nb_extended_buf; i < dst->nb_extended_buf; i++)
                av_buffer_unref(&dst->extended_buf[i]);

            tmp = av_realloc_array(dst->extended_buf, src->nb_extended_buf,
                                   വലുപ്പം(*dst->extended_buf));
            എങ്കിൽ (!tmp) {
                ret = AVERROR(ENOMEM);
                പോകുക fail;
            }
            dst->extended_buf = tmp;
            dst->nb_extended_buf = src->nb_extended_buf;

            memset(&dst->extended_buf[nb_extended_buf], 0,
                   (src->nb_extended_buf - nb_extended_buf) * വലുപ്പം(*dst->extended_buf));
        }

        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < src->nb_extended_buf; i++) {
            ret = av_buffer_replace(&dst->extended_buf[i], src->extended_buf[i]);
            എങ്കിൽ (ret < 0)
                പോകുക fail;
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (dst->extended_buf) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < dst->nb_extended_buf; i++)
            av_buffer_unref(&dst->extended_buf[i]);
        av_freep(&dst->extended_buf);
    }

    ret = av_buffer_replace(&dst->hw_frames_ctx, src->hw_frames_ctx);
    എങ്കിൽ (ret < 0)
        പോകുക fail;

    എങ്കിൽ (dst->extended_data != dst->data)
        av_freep(&dst->extended_data);

    എങ്കിൽ (src->extended_data != src->data) {
        പൂർണ്ണസംഖ്യ ch = dst->ch_layout.nb_channels;

        എങ്കിൽ (ch <= 0 || ch > SIZE_MAX / വലുപ്പം(*dst->extended_data)) {
            ret = AVERROR(EINVAL);
            പോകുക fail;
        }

        dst->extended_data = av_memdup(src->extended_data, വലുപ്പം(*dst->extended_data) * ch);
        എങ്കിൽ (!dst->extended_data) {
            ret = AVERROR(ENOMEM);
            പോകുക fail;
        }
    } അല്ലെങ്കിൽ
        dst->extended_data = dst->data;

    memcpy(dst->data,     src->data,     വലുപ്പം(src->data));
    memcpy(dst->linesize, src->linesize, വലുപ്പം(src->linesize));

    തിരികെ 0;

fail:
    av_frame_unref(dst);
    തിരികെ ret;
}

AVFrame *av_frame_clone(സ്ഥിരം AVFrame *src)
{
    AVFrame *ret = av_frame_alloc();

    എങ്കിൽ (!ret)
        തിരികെ ശൂന്യ;

    എങ്കിൽ (av_frame_ref(ret, src) < 0)
        av_frame_free(&ret);

    തിരികെ ret;
}

ശൂന്യം av_frame_unref(AVFrame *frame)
{
    എങ്കിൽ (!frame)
        തിരികെ;

    av_frame_side_data_free(&frame->side_data, &frame->nb_side_data);

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        av_buffer_unref(&frame->buf[i]);
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < frame->nb_extended_buf; i++)
        av_buffer_unref(&frame->extended_buf[i]);
    av_freep(&frame->extended_buf);
    av_dict_free(&frame->metadata);

    av_buffer_unref(&frame->hw_frames_ctx);

    av_buffer_unref(&frame->opaque_ref);
    av_refstruct_unref(&frame->private_ref);

    എങ്കിൽ (frame->extended_data != frame->data)
        av_freep(&frame->extended_data);

    av_channel_layout_uninit(&frame->ch_layout);

    get_frame_defaults(frame);
}

ശൂന്യം av_frame_move_ref(AVFrame *dst, AVFrame *src)
{
    av_assert1(dst->width == 0 && dst->height == 0);
    av_assert1(dst->ch_layout.nb_channels == 0 &&
               dst->ch_layout.order == AV_CHANNEL_ORDER_UNSPEC);

    *dst = *src;
    എങ്കിൽ (src->extended_data == src->data)
        dst->extended_data = dst->data;
    get_frame_defaults(src);
}

പൂർണ്ണസംഖ്യ av_frame_is_writable(AVFrame *frame)
{
    പൂർണ്ണസംഖ്യ ret = 1;

    /* assume non-refcounted frames are not writable */
    എങ്കിൽ (!frame->buf[0])
        തിരികെ 0;

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < FF_ARRAY_ELEMS(frame->buf); i++)
        എങ്കിൽ (frame->buf[i])
            ret &= !!av_buffer_is_writable(frame->buf[i]);
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < frame->nb_extended_buf; i++)
        ret &= !!av_buffer_is_writable(frame->extended_buf[i]);

    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_frame_make_writable(AVFrame *frame)
{
    AVFrame tmp;
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (av_frame_is_writable(frame))
        തിരികെ 0;

    memset(&tmp, 0, വലുപ്പം(tmp));
    tmp.format         = frame->format;
    tmp.width          = frame->width;
    tmp.height         = frame->height;
    tmp.nb_samples     = frame->nb_samples;
    ret = av_channel_layout_copy(&tmp.ch_layout, &frame->ch_layout);
    എങ്കിൽ (ret < 0) {
        av_frame_unref(&tmp);
        തിരികെ ret;
    }

    എങ്കിൽ (frame->hw_frames_ctx)
        ret = av_hwframe_get_buffer(frame->hw_frames_ctx, &tmp, 0);
    അല്ലെങ്കിൽ
        ret = av_frame_get_buffer(&tmp, 0);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    ret = av_frame_copy(&tmp, frame);
    എങ്കിൽ (ret < 0) {
        av_frame_unref(&tmp);
        തിരികെ ret;
    }

    ret = av_frame_copy_props(&tmp, frame);
    എങ്കിൽ (ret < 0) {
        av_frame_unref(&tmp);
        തിരികെ ret;
    }

    av_frame_unref(frame);

    *frame = tmp;
    എങ്കിൽ (tmp.data == tmp.extended_data)
        frame->extended_data = frame->data;

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_frame_copy_props(AVFrame *dst, സ്ഥിരം AVFrame *src)
{
    തിരികെ frame_copy_props(dst, src, 1);
}

AVBufferRef *av_frame_get_plane_buffer(സ്ഥിരം AVFrame *frame, പൂർണ്ണസംഖ്യ plane)
{
    uintptr_t data;
    പൂർണ്ണസംഖ്യ planes;

    എങ്കിൽ (frame->nb_samples) {
        പൂർണ്ണസംഖ്യ channels = frame->ch_layout.nb_channels;
        എങ്കിൽ (!channels)
            തിരികെ ശൂന്യ;
        planes = av_sample_fmt_is_planar(frame->format) ? channels : 1;
    } അല്ലെങ്കിൽ
        planes = 4;

    എങ്കിൽ (plane < 0 || plane >= planes || !frame->extended_data[plane])
        തിരികെ ശൂന്യ;
    data = (uintptr_t)frame->extended_data[plane];

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < FF_ARRAY_ELEMS(frame->buf) && frame->buf[i]; i++) {
        AVBufferRef *buf = frame->buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        എങ്കിൽ (data >= buf_begin && data < buf_begin + buf->size)
            തിരികെ buf;
    }
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < frame->nb_extended_buf; i++) {
        AVBufferRef *buf = frame->extended_buf[i];
        uintptr_t buf_begin = (uintptr_t)buf->data;

        എങ്കിൽ (data >= buf_begin && data < buf_begin + buf->size)
            തിരികെ buf;
    }
    തിരികെ ശൂന്യ;
}

AVFrameSideData *av_frame_new_side_data_from_buf(AVFrame *frame,
                                                 എണ്ണൽ AVFrameSideDataType type,
                                                 AVBufferRef *buf)
{
    തിരികെ
        ff_frame_side_data_add_from_buf(
            &frame->side_data, &frame->nb_side_data, type, buf);
}

AVFrameSideData *av_frame_new_side_data(AVFrame *frame,
                                        എണ്ണൽ AVFrameSideDataType type,
                                        size_t size)
{
    AVFrameSideData *ret;
    AVBufferRef *buf = av_buffer_alloc(size);
    ret = av_frame_new_side_data_from_buf(frame, type, buf);
    എങ്കിൽ (!ret)
        av_buffer_unref(&buf);
    തിരികെ ret;
}

AVFrameSideData *av_frame_get_side_data(സ്ഥിരം AVFrame *frame,
                                        എണ്ണൽ AVFrameSideDataType type)
{
    തിരികെ (AVFrameSideData *)av_frame_side_data_get(
        frame->side_data, frame->nb_side_data,
        type
    );
}

സ്ഥിതം പൂർണ്ണസംഖ്യ frame_copy_video(AVFrame *dst, സ്ഥിരം AVFrame *src)
{
    പൂർണ്ണസംഖ്യ planes;

    എങ്കിൽ (dst->width  < src->width ||
        dst->height < src->height)
        തിരികെ AVERROR(EINVAL);

    എങ്കിൽ (src->hw_frames_ctx || dst->hw_frames_ctx)
        തിരികെ av_hwframe_transfer_data(dst, src, 0);

    planes = av_pix_fmt_എണ്ണം_planes(dst->format);
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < planes; i++)
        എങ്കിൽ (!dst->data[i] || !src->data[i])
            തിരികെ AVERROR(EINVAL);

    av_image_copy2(dst->data, dst->linesize,
                   src->data, src->linesize,
                   dst->format, src->width, src->height);

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ frame_copy_audio(AVFrame *dst, സ്ഥിരം AVFrame *src)
{
    പൂർണ്ണസംഖ്യ planar   = av_sample_fmt_is_planar(dst->format);
    പൂർണ്ണസംഖ്യ channels = dst->ch_layout.nb_channels;
    പൂർണ്ണസംഖ്യ planes   = planar ? channels : 1;

    എങ്കിൽ (dst->nb_samples != src->nb_samples ||
        av_channel_layout_compare(&dst->ch_layout, &src->ch_layout))
        തിരികെ AVERROR(EINVAL);

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < planes; i++)
        എങ്കിൽ (!dst->extended_data[i] || !src->extended_data[i])
            തിരികെ AVERROR(EINVAL);

    av_samples_copy(dst->extended_data, src->extended_data, 0, 0,
                    dst->nb_samples, channels, dst->format);

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_frame_copy(AVFrame *dst, സ്ഥിരം AVFrame *src)
{
    എങ്കിൽ (dst->format != src->format || dst->format < 0)
        തിരികെ AVERROR(EINVAL);

    എങ്കിൽ (dst->width > 0 && dst->height > 0)
        തിരികെ frame_copy_video(dst, src);
    അല്ലെങ്കിൽ എങ്കിൽ (dst->nb_samples > 0 &&
             (av_channel_layout_check(&dst->ch_layout)))
        തിരികെ frame_copy_audio(dst, src);

    തിരികെ AVERROR(EINVAL);
}

ശൂന്യം av_frame_remove_side_data(AVFrame *frame, എണ്ണൽ AVFrameSideDataType type)
{
    av_frame_side_data_remove(&frame->side_data, &frame->nb_side_data, type);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ calc_cropping_offsets(size_t offsets[4], സ്ഥിരം AVFrame *frame,
                                 സ്ഥിരം AVPixFmtDescriptor *desc)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; frame->data[i]; i++) {
        സ്ഥിരം AVComponentDescriptor *comp = ശൂന്യ;
        പൂർണ്ണസംഖ്യ shift_x = (i == 1 || i == 2) ? desc->log2_chroma_w : 0;
        പൂർണ്ണസംഖ്യ shift_y = (i == 1 || i == 2) ? desc->log2_chroma_h : 0;

        എങ്കിൽ (desc->flags & AV_PIX_FMT_FLAG_PAL && i == 1) {
            offsets[i] = 0;
            നിർത്തുക;
        }

        /* find any component descriptor for this plane */
        വേണ്ടി (പൂർണ്ണസംഖ്യ j = 0; j < desc->nb_components; j++) {
            എങ്കിൽ (desc->comp[j].plane == i) {
                comp = &desc->comp[j];
                നിർത്തുക;
            }
        }
        എങ്കിൽ (!comp)
            തിരികെ AVERROR_BUG;

        offsets[i] = (frame->crop_മുകൾ  >> shift_y) * frame->linesize[i] +
                     (frame->crop_ഇടത് >> shift_x) * comp->step;
    }

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_frame_apply_cropping(AVFrame *frame, പൂർണ്ണസംഖ്യ flags)
{
    സ്ഥിരം AVPixFmtDescriptor *desc;
    size_t offsets[4];
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (!(frame->width > 0 && frame->height > 0))
        തിരികെ AVERROR(EINVAL);

    എങ്കിൽ (frame->crop_ഇടത് >= INT_MAX - frame->crop_വലത്        ||
        frame->crop_മുകൾ  >= INT_MAX - frame->crop_bottom       ||
        (frame->crop_ഇടത് + frame->crop_വലത്) >= frame->width ||
        (frame->crop_മുകൾ + frame->crop_bottom) >= frame->height)
        തിരികെ AVERROR(ERANGE);

    desc = av_pix_fmt_desc_get(frame->format);
    എങ്കിൽ (!desc)
        തിരികെ AVERROR_BUG;

    /* Apply just the right/bottom cropping for hwaccel formats. Bitstream
     * formats cannot be easily handled here either (and corresponding decoders
     * should not export any cropping anyway), so do the same for those as well.
     * */
    എങ്കിൽ (desc->flags & (AV_PIX_FMT_FLAG_BITSTREAM | AV_PIX_FMT_FLAG_HWACCEL)) {
        frame->width      -= frame->crop_വലത്;
        frame->height     -= frame->crop_bottom;
        frame->crop_വലത്  = 0;
        frame->crop_bottom = 0;
        തിരികെ 0;
    }

    /* calculate the offsets for each plane */
    ret = calc_cropping_offsets(offsets, frame, desc);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    /* adjust the offsets to avoid breaking alignment */
    എങ്കിൽ (!(flags & AV_FRAME_CROP_UNALIGNED)) {
        പൂർണ്ണസംഖ്യ log2_crop_align = frame->crop_ഇടത് ? ff_ctz(frame->crop_ഇടത്) : INT_MAX;
        പൂർണ്ണസംഖ്യ min_log2_align = INT_MAX;

        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; frame->data[i]; i++) {
            പൂർണ്ണസംഖ്യ log2_align = offsets[i] ? ff_ctz(offsets[i]) : INT_MAX;
            min_log2_align = FFMIN(log2_align, min_log2_align);
        }

        /* The data alignment is the cropping alignment scaled by a power of 2,
         * up for multi-byte pixels and down for subsampled planes */
        എങ്കിൽ (min_log2_align < 5 && log2_crop_align != INT_MAX) {
            frame->crop_ഇടത് &= ~((1 << (5 + log2_crop_align - min_log2_align)) - 1);
            ret = calc_cropping_offsets(offsets, frame, desc);
            എങ്കിൽ (ret < 0)
                തിരികെ ret;
        }
    }

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; frame->data[i]; i++)
        frame->data[i] += offsets[i];

    frame->width      -= (frame->crop_ഇടത് + frame->crop_വലത്);
    frame->height     -= (frame->crop_മുകൾ  + frame->crop_bottom);
    frame->crop_ഇടത്   = 0;
    frame->crop_വലത്  = 0;
    frame->crop_മുകൾ    = 0;
    frame->crop_bottom = 0;

    തിരികെ 0;
}
