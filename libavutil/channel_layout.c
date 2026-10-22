/*
 * Copyright (c) 2006 Michael Niedermayer <michaelni@gmx.at>
 *
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

/**
 * @file
 * audio channel layout utility functions
 */

#شامل <stdint.h>
#شامل <stdlib.h>
#شامل <string.h>

#شامل "avassert.h"
#شامل "channel_layout.h"
#شامل "bprint.h"
#شامل "common.h"
#شامل "error.h"
#شامل "attributes.h"
#شامل "macros.h"
#شامل "mem.h"
#شامل "opt.h"

#define CHAN_IS_AMBI(x) ((x) >= AV_CHAN_AMBISONIC_BASE &&\
                         (x) <= AV_CHAN_AMBISONIC_END)

ساختار channel_name {
    ثابت نویسه *name;
    ثابت نویسه *description;
};

ایستا ثابت ساختار channel_name channel_names[] = {
    [AV_CHAN_FRONT_چپ           ] = { "FL",        "front left"            },
    [AV_CHAN_FRONT_راست          ] = { "FR",        "front right"           },
    [AV_CHAN_FRONT_CENTER         ] = { "FC",        "front center"          },
    [AV_CHAN_کم_FREQUENCY        ] = { "LFE",       "low frequency"         },
    [AV_CHAN_BACK_چپ            ] = { "BL",        "back left"             },
    [AV_CHAN_BACK_راست           ] = { "BR",        "back right"            },
    [AV_CHAN_FRONT_چپ_OF_CENTER ] = { "FLC",       "front left-of-center"  },
    [AV_CHAN_FRONT_راست_OF_CENTER] = { "FRC",       "front right-of-center" },
    [AV_CHAN_BACK_CENTER          ] = { "BC",        "back center"           },
    [AV_CHAN_SIDE_چپ            ] = { "SL",        "side left"             },
    [AV_CHAN_SIDE_راست           ] = { "SR",        "side right"            },
    [AV_CHAN_بالاترین_CENTER           ] = { "TC",        "top center"            },
    [AV_CHAN_بالاترین_FRONT_چپ       ] = { "TFL",       "top front left"        },
    [AV_CHAN_بالاترین_FRONT_CENTER     ] = { "TFC",       "top front center"      },
    [AV_CHAN_بالاترین_FRONT_راست      ] = { "TFR",       "top front right"       },
    [AV_CHAN_بالاترین_BACK_چپ        ] = { "TBL",       "top back left"         },
    [AV_CHAN_بالاترین_BACK_CENTER      ] = { "TBC",       "top back center"       },
    [AV_CHAN_بالاترین_BACK_راست       ] = { "TBR",       "top back right"        },
    [AV_CHAN_STEREO_چپ          ] = { "DL",        "downmix left"          },
    [AV_CHAN_STEREO_راست         ] = { "DR",        "downmix right"         },
    [AV_CHAN_WIDE_چپ            ] = { "WL",        "wide left"             },
    [AV_CHAN_WIDE_راست           ] = { "WR",        "wide right"            },
    [AV_CHAN_SURROUND_DIRECT_چپ ] = { "SDL",       "surround direct left"  },
    [AV_CHAN_SURROUND_DIRECT_راست] = { "SDR",       "surround direct right" },
    [AV_CHAN_کم_FREQUENCY_2      ] = { "LFE2",      "low frequency 2"       },
    [AV_CHAN_بالاترین_SIDE_چپ        ] = { "TSL",       "top side left"         },
    [AV_CHAN_بالاترین_SIDE_راست       ] = { "TSR",       "top side right"        },
    [AV_CHAN_BOTTOM_FRONT_CENTER  ] = { "BFC",       "bottom front center"   },
    [AV_CHAN_BOTTOM_FRONT_چپ    ] = { "BFL",       "bottom front left"     },
    [AV_CHAN_BOTTOM_FRONT_راست   ] = { "BFR",       "bottom front right"    },
    [AV_CHAN_SIDE_SURROUND_چپ   ] = { "SSL",       "side surround left"    },
    [AV_CHAN_SIDE_SURROUND_راست  ] = { "SSR",       "side surround right"   },
    [AV_CHAN_بالاترین_SURROUND_چپ    ] = { "TTL",       "top surround left"     },
    [AV_CHAN_بالاترین_SURROUND_راست   ] = { "TTR",       "top surround right"    },
    [AV_CHAN_BINAURAL_چپ        ] = { "BIL",       "binaural left"         },
    [AV_CHAN_BINAURAL_راست       ] = { "BIR",       "binaural right"        },
};

تهی av_channel_name_bprint(AVBPrint *bp, شمارش AVChannel channel_id)
{
    اگر (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_BASE);
    وگرنه اگر ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].name)
        av_bprintf(bp, "%s", channel_names[channel_id].name);
    وگرنه اگر (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    وگرنه اگر (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    وگرنه اگر (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "UNSD");
    وگرنه
        av_bprintf(bp, "USR%d", channel_id);
}

صحیح av_channel_name(نویسه *buf, size_t buf_size, شمارش AVChannel channel_id)
{
    AVBPrint bp;

    اگر (!buf && buf_size)
        بازگشت AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_name_bprint(&bp, channel_id);

    اگر (bp.len >= INT_MAX)
        بازگشت AVERROR(ERANGE);
    بازگشت bp.len + 1;
}

تهی av_channel_description_bprint(AVBPrint *bp, شمارش AVChannel channel_id)
{
    اگر (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_BASE);
    وگرنه اگر ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].description)
        av_bprintf(bp, "%s", channel_names[channel_id].description);
    وگرنه اگر (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    وگرنه اگر (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    وگرنه اگر (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "unused");
    وگرنه
        av_bprintf(bp, "user %d", channel_id);
}

صحیح av_channel_description(نویسه *buf, size_t buf_size, شمارش AVChannel channel_id)
{
    AVBPrint bp;

    اگر (!buf && buf_size)
        بازگشت AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_description_bprint(&bp, channel_id);

    اگر (bp.len >= INT_MAX)
        بازگشت AVERROR(ERANGE);
    بازگشت bp.len + 1;
}

شمارش AVChannel av_channel_from_string(ثابت نویسه *str)
{
    صحیح i;
    نویسه *endptr = (نویسه *)str;
    شمارش AVChannel id = AV_CHAN_NONE;

    اگر (!strncmp(str, "AMBI", 4)) {
        i = strtol(str + 4, پوچ, 0);
        اگر (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            بازگشت AV_CHAN_NONE;
        بازگشت AV_CHAN_AMBISONIC_BASE + i;
    }

    برای (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        اگر (channel_names[i].name && !strcmp(str, channel_names[i].name))
            بازگشت i;
    }
    اگر (!strcmp(str, "UNK"))
        بازگشت AV_CHAN_UNKNOWN;
    اگر (!strcmp(str, "UNSD"))
        بازگشت AV_CHAN_UNUSED;

    اگر (!strncmp(str, "USR", 3)) {
        ثابت نویسه *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    اگر (id >= 0 && !*endptr)
        بازگشت id;

    بازگشت AV_CHAN_NONE;
}

ساختار channel_layout_name {
    ثابت نویسه *name;
    AVChannelLayout layout;
};

ایستا ثابت ساختار channel_layout_name channel_layout_map[] = {
    { "mono",           AV_CHANNEL_LAYOUT_MONO                },
    { "stereo",         AV_CHANNEL_LAYOUT_STEREO              },
    { "2.1",            AV_CHANNEL_LAYOUT_2POINT1             },
    { "3.0",            AV_CHANNEL_LAYOUT_SURROUND            },
    { "3.0(back)",      AV_CHANNEL_LAYOUT_2_1                 },
    { "4.0",            AV_CHANNEL_LAYOUT_4POINT0             },
    { "quad",           AV_CHANNEL_LAYOUT_QUAD                },
    { "quad(side)",     AV_CHANNEL_LAYOUT_2_2                 },
    { "3.1",            AV_CHANNEL_LAYOUT_3POINT1             },
    { "5.0",            AV_CHANNEL_LAYOUT_5POINT0_BACK        },
    { "5.0(side)",      AV_CHANNEL_LAYOUT_5POINT0             },
    { "4.1",            AV_CHANNEL_LAYOUT_4POINT1             },
    { "5.1",            AV_CHANNEL_LAYOUT_5POINT1_BACK        },
    { "5.1(side)",      AV_CHANNEL_LAYOUT_5POINT1             },
    { "6.0",            AV_CHANNEL_LAYOUT_6POINT0             },
    { "6.0(front)",     AV_CHANNEL_LAYOUT_6POINT0_FRONT       },
    { "3.1.2",          AV_CHANNEL_LAYOUT_3POINT1POINT2       },
    { "hexagonal",      AV_CHANNEL_LAYOUT_HEXAGONAL           },
    { "6.1",            AV_CHANNEL_LAYOUT_6POINT1             },
    { "6.1(back)",      AV_CHANNEL_LAYOUT_6POINT1_BACK        },
    { "6.1(front)",     AV_CHANNEL_LAYOUT_6POINT1_FRONT       },
    { "7.0",            AV_CHANNEL_LAYOUT_7POINT0             },
    { "7.0(front)",     AV_CHANNEL_LAYOUT_7POINT0_FRONT       },
    { "7.1",            AV_CHANNEL_LAYOUT_7POINT1             },
    { "7.1(wide)",      AV_CHANNEL_LAYOUT_7POINT1_WIDE_BACK   },
    { "7.1(wide-side)", AV_CHANNEL_LAYOUT_7POINT1_WIDE        },
    { "5.1.2",          AV_CHANNEL_LAYOUT_5POINT1POINT2       },
    { "5.1.2(back)",    AV_CHANNEL_LAYOUT_5POINT1POINT2_BACK  },
    { "octagonal",      AV_CHANNEL_LAYOUT_OCTAGONAL           },
    { "cube",           AV_CHANNEL_LAYOUT_CUBE                },
    { "5.1.4",          AV_CHANNEL_LAYOUT_5POINT1POINT4       },
    { "5.1.6",          AV_CHANNEL_LAYOUT_5POINT1POINT6       },
    { "7.1.2",          AV_CHANNEL_LAYOUT_7POINT1POINT2       },
    { "7.1.4",          AV_CHANNEL_LAYOUT_7POINT1POINT4       },
    { "7.1.6",          AV_CHANNEL_LAYOUT_7POINT1POINT6       },
    { "7.2.3",          AV_CHANNEL_LAYOUT_7POINT2POINT3       },
    { "9.1.4",          AV_CHANNEL_LAYOUT_9POINT1POINT4       },
    { "9.1.6",          AV_CHANNEL_LAYOUT_9POINT1POINT6       },
    { "hexadecagonal",  AV_CHANNEL_LAYOUT_HEXADECAGONAL       },
    { "binaural",       AV_CHANNEL_LAYOUT_BINAURAL            },
    { "downmix",        AV_CHANNEL_LAYOUT_STEREO_DOWNMIX,     },
    { "22.2",           AV_CHANNEL_LAYOUT_22POINT2,           },
};

صحیح av_channel_layout_custom_init(AVChannelLayout *channel_layout, صحیح nb_channels)
{
    AVChannelCustom *map;

    اگر (nb_channels <= 0)
        بازگشت AVERROR(EINVAL);

    map = av_calloc(nb_channels, اندازه(*channel_layout->u.map));
    اگر (!map)
        بازگشت AVERROR(ENOMEM);
    برای (صحیح i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->order       = AV_CHANNEL_ORDER_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    بازگشت 0;
}

صحیح av_channel_layout_from_mask(AVChannelLayout *channel_layout,
                                uint64_t mask)
{
    اگر (!mask)
        بازگشت AVERROR(EINVAL);

    channel_layout->order       = AV_CHANNEL_ORDER_NATIVE;
    channel_layout->nb_channels = av_popcount64(mask);
    channel_layout->u.mask      = mask;

    بازگشت 0;
}

ایستا صحیح parse_channel_list(AVChannelLayout *ch_layout, ثابت نویسه *str)
{
    صحیح ret;
    صحیح nb_channels = 0;
    AVChannelCustom *map = پوچ;
    AVChannelCustom custom = {0};

    وقتی (*str) {
        نویسه *channel, *chname;
        ret = av_opt_get_کلید_مقدار(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_کلید, &channel, &chname);
        اگر (ret < 0) {
            av_freep(&map);
            بازگشت ret;
        }
        اگر (*str)
            str++; // skip separator
        اگر (!channel) {
            channel = chname;
            chname = پوچ;
        }
        av_strlcpy(custom.name, chname ? chname : "", اندازه(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        اگر (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            بازگشت AVERROR(EINVAL);
        }

        av_dynarray2_add((تهی **)&map, &nb_channels, اندازه(custom), (تهی *)&custom);
        اگر (!map)
            بازگشت AVERROR(ENOMEM);
    }

    اگر (!nb_channels)
        بازگشت AVERROR(EINVAL);

    ch_layout->order = AV_CHANNEL_ORDER_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    بازگشت 0;
}

صحیح av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  ثابت نویسه *str)
{
    صحیح i, matches, ret;
    صحیح channels = 0, nb_channels = 0;
    نویسه *chlist, *end;
    uint64_t mask = 0;

    /* channel layout names */
    برای (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        اگر (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            بازگشت 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, اندازه(*channel_layout));

    /* ambisonic */
    اگر (!strncmp(str, "ambisonic ", 10)) {
        ثابت نویسه *p = str + 10;
        نویسه *endptr;
        AVChannelLayout extra = {0};
        صحیح order;

        order = strtol(p, &endptr, 0);
        اگر (order < 0 || order + 1  > INT_MAX / (order + 1) ||
            (*endptr && *endptr != '+'))
            بازگشت AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        اگر (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            اگر (ret < 0)
                بازگشت ret;
            اگر (extra.nb_channels >= INT_MAX - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                بازگشت AVERROR(EINVAL);
            }

            اگر (extra.order == AV_CHANNEL_ORDER_NATIVE) {
                channel_layout->u.mask = extra.u.mask;
            } وگرنه {
                channel_layout->order = AV_CHANNEL_ORDER_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              اندازه(*channel_layout->u.map));
                اگر (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    بازگشت AVERROR(ENOMEM);
                }

                برای (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                برای (i = 0; i < extra.nb_channels; i++) {
                    شمارش AVChannel ch = av_channel_layout_channel_from_index(&extra, i);
                    اگر (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        بازگشت AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    اگر (extra.order == AV_CHANNEL_ORDER_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   اندازه(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        بازگشت 0;
    }

    chlist = av_strdup(str);
    اگر (!chlist)
        بازگشت AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    اگر (ret < 0 && ret != AVERROR(EINVAL))
        بازگشت ret;

    اگر (ret >= 0) {
        ثابت نویسه *end_par = strchr(str, ')');
        اگر (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            بازگشت AVERROR(EINVAL);
        }
        بازگشت 0;
    }

    errno = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    اگر (!errno && !*end && !strchr(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        بازگشت 0;
    }

    errno = 0;
    channels = strtol(str, &end, 10);

    /* number of channels */
    اگر (!errno && !strcmp(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        اگر (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            بازگشت 0;
    }

    /* number of unordered channels */
    اگر (!errno && (!strcmp(end, "C") || !strcmp(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        بازگشت 0;
    }

    بازگشت AVERROR(EINVAL);
}

تهی av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    اگر (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, اندازه(*channel_layout));
}

صحیح av_channel_layout_copy(AVChannelLayout *dst, ثابت AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    اگر (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, اندازه(*dst->u.map));
        اگر (!dst->u.map)
            بازگشت AVERROR(ENOMEM);
        memcpy(dst->u.map, src->u.map, src->nb_channels * اندازه(*src->u.map));
    }
    بازگشت 0;
}

ایستا int64_t masked_description(ثابت AVChannelLayout *channel_layout, صحیح start_channel)
{
    uint64_t mask = 0;
    برای (صحیح i = start_channel; i < channel_layout->nb_channels; i++) {
        شمارش AVChannel ch = channel_layout->u.map[i].id;
        اگر (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        وگرنه
            بازگشت AVERROR(EINVAL);
    }
    بازگشت mask;
}

ایستا صحیح has_channel_names(ثابت AVChannelLayout *channel_layout)
{
    اگر (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        بازگشت 0;
    برای (صحیح i = 0; i < channel_layout->nb_channels; i++)
        اگر (channel_layout->u.map[i].name[0])
            بازگشت 1;
    بازگشت 0;
}

صحیح av_channel_layout_ambisonic_order(ثابت AVChannelLayout *channel_layout)
{
    صحیح i, highest_ambi, order;

    اگر (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        بازگشت AVERROR(EINVAL);

    highest_ambi = -1;
    اگر (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    وگرنه {
        ثابت AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        برای (i = 0; i < channel_layout->nb_channels; i++) {
            صحیح is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            اگر (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                بازگشت AVERROR(EINVAL);

            /* non-default ordering */
            اگر (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                بازگشت AVERROR(EINVAL);

            اگر (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    اگر (highest_ambi < 0)
        بازگشت AVERROR(EINVAL);

    order = floor(sqrt(highest_ambi));
    /* incomplete order - some harmonics are missing */
    اگر ((order + 1) * (order + 1) != highest_ambi + 1)
        بازگشت AVERROR(EINVAL);

    بازگشت order;
}

ایستا شمارش AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    صحیح has_known_channel = 0;
    صحیح order;

    اگر (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        بازگشت channel_layout->order;

    اگر (has_channel_names(channel_layout))
        بازگشت AV_CHANNEL_ORDER_CUSTOM;

    برای (صحیح i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        اگر (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    اگر (!has_known_channel)
        بازگشت AV_CHANNEL_ORDER_UNSPEC;

    اگر (masked_description(channel_layout, 0) > 0)
        بازگشت AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    اگر (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
        بازگشت AV_CHANNEL_ORDER_AMBISONIC;

    بازگشت AV_CHANNEL_ORDER_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
ایستا صحیح try_describe_ambisonic(AVBPrint *bp, ثابت AVChannelLayout *channel_layout)
{
    صحیح nb_ambi_channels;
    صحیح order = av_channel_layout_ambisonic_order(channel_layout);
    اگر (order < 0)
        بازگشت order;

    av_bprintf(bp, "ambisonic %d", order);

    /* extra channels present */
    nb_ambi_channels = (order + 1) * (order + 1);
    اگر (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        اگر (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC) {
            extra.order       = AV_CHANNEL_ORDER_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.mask);
            extra.u.mask      = channel_layout->u.mask;
        } وگرنه {
            int64_t mask;
            اگر (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.order       = AV_CHANNEL_ORDER_NATIVE;
                extra.nb_channels = av_popcount64(mask);
                extra.u.mask      = mask;
            } وگرنه {
                extra.order       = AV_CHANNEL_ORDER_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    بازگشت 0;
}

صحیح av_channel_layout_describe_bprint(ثابت AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    صحیح i;

    انتخاب (channel_layout->order) {
    حالت AV_CHANNEL_ORDER_NATIVE:
        برای (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            اگر (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                بازگشت 0;
            }
        av_fallthrough;
    حالت AV_CHANNEL_ORDER_CUSTOM:
        اگر (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            صحیح res = try_describe_ambisonic(bp, channel_layout);
            اگر (res >= 0)
                بازگشت 0;
            اگر (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                بازگشت av_channel_layout_describe_bprint(&native, bp);
            }
        }
        اگر (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        برای (i = 0; i < channel_layout->nb_channels; i++) {
            شمارش AVChannel ch = av_channel_layout_channel_from_index(channel_layout, i);

            اگر (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            اگر (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        اگر (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            بازگشت 0;
        }
        av_fallthrough;
    حالت AV_CHANNEL_ORDER_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        بازگشت 0;
    حالت AV_CHANNEL_ORDER_AMBISONIC:
        بازگشت try_describe_ambisonic(bp, channel_layout);
    پیشفرض:
        بازگشت AVERROR(EINVAL);
    }
}

صحیح av_channel_layout_describe(ثابت AVChannelLayout *channel_layout,
                               نویسه *buf, size_t buf_size)
{
    AVBPrint bp;
    صحیح ret;

    اگر (!buf && buf_size)
        بازگشت AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    اگر (ret < 0)
        بازگشت ret;

    اگر (bp.len >= INT_MAX)
        بازگشت AVERROR(ERANGE);
    بازگشت bp.len + 1;
}

شمارش AVChannel
av_channel_layout_channel_from_index(ثابت AVChannelLayout *channel_layout,
                                     unsigned صحیح idx)
{
    صحیح i;

    اگر (idx >= channel_layout->nb_channels)
        بازگشت AV_CHAN_NONE;

    انتخاب (channel_layout->order) {
    حالت AV_CHANNEL_ORDER_CUSTOM:
        بازگشت channel_layout->u.map[idx].id;
    حالت AV_CHANNEL_ORDER_AMBISONIC: {
        صحیح ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        اگر (idx < ambi_channels)
            بازگشت AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    حالت AV_CHANNEL_ORDER_NATIVE:
        برای (i = 0; i < 64; i++) {
            اگر ((1ULL << i) & channel_layout->u.mask && !idx--)
                بازگشت i;
        }
        av_fallthrough;
    پیشفرض:
        بازگشت AV_CHAN_NONE;
    }
}

شمارش AVChannel
av_channel_layout_channel_from_string(ثابت AVChannelLayout *channel_layout,
                                      ثابت نویسه *str)
{
    صحیح index = av_channel_layout_index_from_string(channel_layout, str);

    اگر (index < 0)
        بازگشت AV_CHAN_NONE;

    بازگشت av_channel_layout_channel_from_index(channel_layout, index);
}

صحیح av_channel_layout_index_from_channel(ثابت AVChannelLayout *channel_layout,
                                         شمارش AVChannel channel)
{
    صحیح i;

    اگر (channel == AV_CHAN_NONE)
        بازگشت AVERROR(EINVAL);

    انتخاب (channel_layout->order) {
    حالت AV_CHANNEL_ORDER_CUSTOM:
        برای (i = 0; i < channel_layout->nb_channels; i++)
            اگر (channel_layout->u.map[i].id == channel)
                بازگشت i;
        بازگشت AVERROR(EINVAL);
    حالت AV_CHANNEL_ORDER_AMBISONIC:
    حالت AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        صحیح ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        اگر (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            اگر (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                بازگشت AVERROR(EINVAL);
            بازگشت channel - AV_CHAN_AMBISONIC_BASE;
        }
        اگر ((unsigned)channel > 63 || !(mask & (1ULL << channel)))
            بازگشت AVERROR(EINVAL);
        mask &= (1ULL << channel) - 1;
        بازگشت av_popcount64(mask) + ambi_channels;
        }
    پیشفرض:
        بازگشت AVERROR(EINVAL);
    }
}

صحیح av_channel_layout_index_from_string(ثابت AVChannelLayout *channel_layout,
                                        ثابت نویسه *str)
{
    ثابت نویسه *chname;
    شمارش AVChannel ch = AV_CHAN_NONE;

    انتخاب (channel_layout->order) {
    حالت AV_CHANNEL_ORDER_CUSTOM:
        chname = strstr(str, "@");
        اگر (chname) {
            نویسه buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(اندازه(buf), chname - str));
            اگر (!*chname)
                chname = پوچ;
            ch = av_channel_from_string(buf);
            اگر (ch == AV_CHAN_NONE && *buf)
                بازگشت AVERROR(EINVAL);
        }
        برای (صحیح i = 0; chname && i < channel_layout->nb_channels; i++) {
            اگر (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                بازگشت i;
        }
        av_fallthrough;
    حالت AV_CHANNEL_ORDER_AMBISONIC:
    حالت AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        اگر (ch == AV_CHAN_NONE)
            بازگشت AVERROR(EINVAL);
        بازگشت av_channel_layout_index_from_channel(channel_layout, ch);
    }

    بازگشت AVERROR(EINVAL);
}

صحیح av_channel_layout_check(ثابت AVChannelLayout *channel_layout)
{
    اگر (channel_layout->nb_channels <= 0)
        بازگشت 0;

    انتخاب (channel_layout->order) {
    حالت AV_CHANNEL_ORDER_NATIVE:
        بازگشت av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    حالت AV_CHANNEL_ORDER_CUSTOM:
        اگر (!channel_layout->u.map)
            بازگشت 0;
        برای (صحیح i = 0; i < channel_layout->nb_channels; i++) {
            اگر (channel_layout->u.map[i].id == AV_CHAN_NONE)
                بازگشت 0;
        }
        بازگشت 1;
    حالت AV_CHANNEL_ORDER_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        بازگشت av_popcount64(channel_layout->u.mask) < channel_layout->nb_channels;
    حالت AV_CHANNEL_ORDER_UNSPEC:
        بازگشت 1;
    پیشفرض:
        بازگشت 0;
    }
}

صحیح av_channel_layout_compare(ثابت AVChannelLayout *chl, ثابت AVChannelLayout *chl1)
{
    صحیح i;

    /* different channel counts -> not equal */
    اگر (chl->nb_channels != chl1->nb_channels)
        بازگشت 1;

    /* if only one is unspecified -> not equal */
    اگر ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        بازگشت 1;
    /* both are unspecified -> equal */
    وگرنه اگر (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        بازگشت 0;

    /* can compare masks directly */
    اگر ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        بازگشت chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    برای (i = 0; i < chl->nb_channels; i++)
        اگر (av_channel_layout_channel_from_index(chl,  i) !=
            av_channel_layout_channel_from_index(chl1, i))
            بازگشت 1;
    بازگشت 0;
}

تهی av_channel_layout_default(AVChannelLayout *ch_layout, صحیح nb_channels)
{
    صحیح i;
    برای (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        اگر (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            بازگشت;
        }

    ch_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

ثابت AVChannelLayout *av_channel_layout_standard(تهی **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ثابت AVChannelLayout *ch_layout = پوچ;

    اگر (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (تهی*)(i + 1);
    }

    بازگشت ch_layout;
}

uint64_t av_channel_layout_subset(ثابت AVChannelLayout *channel_layout,
                                  uint64_t mask)
{
    uint64_t ret = 0;
    صحیح i;

    انتخاب (channel_layout->order) {
    حالت AV_CHANNEL_ORDER_NATIVE:
    حالت AV_CHANNEL_ORDER_AMBISONIC:
        بازگشت channel_layout->u.mask & mask;
    حالت AV_CHANNEL_ORDER_CUSTOM:
        برای (i = 0; i < 64; i++)
            اگر (mask & (1ULL << i) && av_channel_layout_index_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        بشکن;
    }

    بازگشت ret;
}

صحیح av_channel_layout_retype(AVChannelLayout *channel_layout, شمارش AVChannelOrder order, صحیح flags)
{
    صحیح allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    صحیح lossy;

    اگر (!av_channel_layout_check(channel_layout))
        بازگشت AVERROR(EINVAL);

    اگر (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    اگر (channel_layout->order == order)
        بازگشت 0;

    انتخاب (order) {
    حالت AV_CHANNEL_ORDER_UNSPEC: {
        صحیح nb_channels = channel_layout->nb_channels;
        اگر (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            برای (صحیح i = 0; i < nb_channels; i++) {
                اگر (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    بشکن;
                }
            }
        } وگرنه {
            lossy = 1;
        }
        اگر (!lossy || allow_lossy) {
            تهی *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            بازگشت lossy;
        }
        بازگشت AVERROR(ENOSYS);
        }
    حالت AV_CHANNEL_ORDER_NATIVE:
        اگر (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            اگر (mask < 0)
                بازگشت AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            اگر (!lossy || allow_lossy) {
                تهی *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_mask(channel_layout, mask);
                channel_layout->opaque = opaque;
                بازگشت lossy;
            }
        }
        بازگشت AVERROR(ENOSYS);
    حالت AV_CHANNEL_ORDER_CUSTOM: {
        AVChannelLayout custom = { 0 };
        صحیح ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        تهی *opaque = channel_layout->opaque;
        اگر (ret < 0)
            بازگشت ret;
        اگر (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            برای (صحیح i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_index(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        بازگشت 0;
        }
    حالت AV_CHANNEL_ORDER_AMBISONIC:
        اگر (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            صحیح nb_channels = channel_layout->nb_channels;
            صحیح amb_order = av_channel_layout_ambisonic_order(channel_layout);
            اگر (amb_order < 0)
                بازگشت AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            اگر (mask < 0)
                بازگشت AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            اگر (!lossy || allow_lossy) {
                تهی *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.mask      = mask;
                channel_layout->opaque      = opaque;
                بازگشت lossy;
            }
        }
        بازگشت AVERROR(ENOSYS);
    پیشفرض:
        بازگشت AVERROR(EINVAL);
    }
}
