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

#ضمن <stdint.h>
#ضمن <stdlib.h>
#ضمن <string.h>

#ضمن "avassert.h"
#ضمن "channel_layout.h"
#ضمن "bprint.h"
#ضمن "common.h"
#ضمن "error.h"
#ضمن "attributes.h"
#ضمن "macros.h"
#ضمن "mem.h"
#ضمن "opt.h"

#define CHAN_IS_AMBI(x) ((x) >= AV_CHAN_AMBISONIC_BASE &&\
                         (x) <= AV_CHAN_AMBISONIC_END)

بنية channel_name {
    ثابت حرف *name;
    ثابت حرف *description;
};

ساكن ثابت بنية channel_name channel_names[] = {
    [AV_CHAN_FRONT_يسار           ] = { "FL",        "front left"            },
    [AV_CHAN_FRONT_يمين          ] = { "FR",        "front right"           },
    [AV_CHAN_FRONT_CENTER         ] = { "FC",        "front center"          },
    [AV_CHAN_أدنى_FREQUENCY        ] = { "LFE",       "low frequency"         },
    [AV_CHAN_BACK_يسار            ] = { "BL",        "back left"             },
    [AV_CHAN_BACK_يمين           ] = { "BR",        "back right"            },
    [AV_CHAN_FRONT_يسار_OF_CENTER ] = { "FLC",       "front left-of-center"  },
    [AV_CHAN_FRONT_يمين_OF_CENTER] = { "FRC",       "front right-of-center" },
    [AV_CHAN_BACK_CENTER          ] = { "BC",        "back center"           },
    [AV_CHAN_SIDE_يسار            ] = { "SL",        "side left"             },
    [AV_CHAN_SIDE_يمين           ] = { "SR",        "side right"            },
    [AV_CHAN_قمة_CENTER           ] = { "TC",        "top center"            },
    [AV_CHAN_قمة_FRONT_يسار       ] = { "TFL",       "top front left"        },
    [AV_CHAN_قمة_FRONT_CENTER     ] = { "TFC",       "top front center"      },
    [AV_CHAN_قمة_FRONT_يمين      ] = { "TFR",       "top front right"       },
    [AV_CHAN_قمة_BACK_يسار        ] = { "TBL",       "top back left"         },
    [AV_CHAN_قمة_BACK_CENTER      ] = { "TBC",       "top back center"       },
    [AV_CHAN_قمة_BACK_يمين       ] = { "TBR",       "top back right"        },
    [AV_CHAN_STEREO_يسار          ] = { "DL",        "downmix left"          },
    [AV_CHAN_STEREO_يمين         ] = { "DR",        "downmix right"         },
    [AV_CHAN_WIDE_يسار            ] = { "WL",        "wide left"             },
    [AV_CHAN_WIDE_يمين           ] = { "WR",        "wide right"            },
    [AV_CHAN_SURROUND_DIRECT_يسار ] = { "SDL",       "surround direct left"  },
    [AV_CHAN_SURROUND_DIRECT_يمين] = { "SDR",       "surround direct right" },
    [AV_CHAN_أدنى_FREQUENCY_2      ] = { "LFE2",      "low frequency 2"       },
    [AV_CHAN_قمة_SIDE_يسار        ] = { "TSL",       "top side left"         },
    [AV_CHAN_قمة_SIDE_يمين       ] = { "TSR",       "top side right"        },
    [AV_CHAN_BOTTOM_FRONT_CENTER  ] = { "BFC",       "bottom front center"   },
    [AV_CHAN_BOTTOM_FRONT_يسار    ] = { "BFL",       "bottom front left"     },
    [AV_CHAN_BOTTOM_FRONT_يمين   ] = { "BFR",       "bottom front right"    },
    [AV_CHAN_SIDE_SURROUND_يسار   ] = { "SSL",       "side surround left"    },
    [AV_CHAN_SIDE_SURROUND_يمين  ] = { "SSR",       "side surround right"   },
    [AV_CHAN_قمة_SURROUND_يسار    ] = { "TTL",       "top surround left"     },
    [AV_CHAN_قمة_SURROUND_يمين   ] = { "TTR",       "top surround right"    },
    [AV_CHAN_BINAURAL_يسار        ] = { "BIL",       "binaural left"         },
    [AV_CHAN_BINAURAL_يمين       ] = { "BIR",       "binaural right"        },
};

فراغ av_channel_name_bprint(AVBPrint *bp, تعداد AVChannel channel_id)
{
    إذا (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_BASE);
    وإلا إذا ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].name)
        av_bprintf(bp, "%s", channel_names[channel_id].name);
    وإلا إذا (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    وإلا إذا (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    وإلا إذا (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "UNSD");
    وإلا
        av_bprintf(bp, "USR%d", channel_id);
}

صحيح av_channel_name(حرف *buf, size_t buf_size, تعداد AVChannel channel_id)
{
    AVBPrint bp;

    إذا (!buf && buf_size)
        إرجاع AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_name_bprint(&bp, channel_id);

    إذا (bp.len >= INT_MAX)
        إرجاع AVERROR(ERANGE);
    إرجاع bp.len + 1;
}

فراغ av_channel_description_bprint(AVBPrint *bp, تعداد AVChannel channel_id)
{
    إذا (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_BASE);
    وإلا إذا ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].description)
        av_bprintf(bp, "%s", channel_names[channel_id].description);
    وإلا إذا (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    وإلا إذا (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    وإلا إذا (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "unused");
    وإلا
        av_bprintf(bp, "user %d", channel_id);
}

صحيح av_channel_description(حرف *buf, size_t buf_size, تعداد AVChannel channel_id)
{
    AVBPrint bp;

    إذا (!buf && buf_size)
        إرجاع AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_description_bprint(&bp, channel_id);

    إذا (bp.len >= INT_MAX)
        إرجاع AVERROR(ERANGE);
    إرجاع bp.len + 1;
}

تعداد AVChannel av_channel_from_string(ثابت حرف *str)
{
    صحيح i;
    حرف *endptr = (حرف *)str;
    تعداد AVChannel id = AV_CHAN_NONE;

    إذا (!strncmp(str, "AMBI", 4)) {
        i = strtol(str + 4, عدم, 0);
        إذا (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            إرجاع AV_CHAN_NONE;
        إرجاع AV_CHAN_AMBISONIC_BASE + i;
    }

    لكل (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        إذا (channel_names[i].name && !strcmp(str, channel_names[i].name))
            إرجاع i;
    }
    إذا (!strcmp(str, "UNK"))
        إرجاع AV_CHAN_UNKNOWN;
    إذا (!strcmp(str, "UNSD"))
        إرجاع AV_CHAN_UNUSED;

    إذا (!strncmp(str, "USR", 3)) {
        ثابت حرف *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    إذا (id >= 0 && !*endptr)
        إرجاع id;

    إرجاع AV_CHAN_NONE;
}

بنية channel_layout_name {
    ثابت حرف *name;
    AVChannelLayout layout;
};

ساكن ثابت بنية channel_layout_name channel_layout_map[] = {
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

صحيح av_channel_layout_custom_init(AVChannelLayout *channel_layout, صحيح nb_channels)
{
    AVChannelCustom *map;

    إذا (nb_channels <= 0)
        إرجاع AVERROR(EINVAL);

    map = av_calloc(nb_channels, حجم(*channel_layout->u.map));
    إذا (!map)
        إرجاع AVERROR(ENOMEM);
    لكل (صحيح i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->order       = AV_CHANNEL_ORDER_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    إرجاع 0;
}

صحيح av_channel_layout_from_mask(AVChannelLayout *channel_layout,
                                uint64_t mask)
{
    إذا (!mask)
        إرجاع AVERROR(EINVAL);

    channel_layout->order       = AV_CHANNEL_ORDER_NATIVE;
    channel_layout->nb_channels = av_popcount64(mask);
    channel_layout->u.mask      = mask;

    إرجاع 0;
}

ساكن صحيح parse_channel_list(AVChannelLayout *ch_layout, ثابت حرف *str)
{
    صحيح ret;
    صحيح nb_channels = 0;
    AVChannelCustom *map = عدم;
    AVChannelCustom custom = {0};

    بينما (*str) {
        حرف *channel, *chname;
        ret = av_opt_get_مفتاح_قيمة(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_مفتاح, &channel, &chname);
        إذا (ret < 0) {
            av_freep(&map);
            إرجاع ret;
        }
        إذا (*str)
            str++; // skip separator
        إذا (!channel) {
            channel = chname;
            chname = عدم;
        }
        av_strlcpy(custom.name, chname ? chname : "", حجم(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        إذا (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            إرجاع AVERROR(EINVAL);
        }

        av_dynarray2_add((فراغ **)&map, &nb_channels, حجم(custom), (فراغ *)&custom);
        إذا (!map)
            إرجاع AVERROR(ENOMEM);
    }

    إذا (!nb_channels)
        إرجاع AVERROR(EINVAL);

    ch_layout->order = AV_CHANNEL_ORDER_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    إرجاع 0;
}

صحيح av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  ثابت حرف *str)
{
    صحيح i, matches, ret;
    صحيح channels = 0, nb_channels = 0;
    حرف *chlist, *end;
    uint64_t mask = 0;

    /* channel layout names */
    لكل (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        إذا (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            إرجاع 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, حجم(*channel_layout));

    /* ambisonic */
    إذا (!strncmp(str, "ambisonic ", 10)) {
        ثابت حرف *p = str + 10;
        حرف *endptr;
        AVChannelLayout extra = {0};
        صحيح order;

        order = strtol(p, &endptr, 0);
        إذا (order < 0 || order + 1  > INT_MAX / (order + 1) ||
            (*endptr && *endptr != '+'))
            إرجاع AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        إذا (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            إذا (ret < 0)
                إرجاع ret;
            إذا (extra.nb_channels >= INT_MAX - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                إرجاع AVERROR(EINVAL);
            }

            إذا (extra.order == AV_CHANNEL_ORDER_NATIVE) {
                channel_layout->u.mask = extra.u.mask;
            } وإلا {
                channel_layout->order = AV_CHANNEL_ORDER_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              حجم(*channel_layout->u.map));
                إذا (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    إرجاع AVERROR(ENOMEM);
                }

                لكل (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                لكل (i = 0; i < extra.nb_channels; i++) {
                    تعداد AVChannel ch = av_channel_layout_channel_from_index(&extra, i);
                    إذا (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        إرجاع AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    إذا (extra.order == AV_CHANNEL_ORDER_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   حجم(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        إرجاع 0;
    }

    chlist = av_strdup(str);
    إذا (!chlist)
        إرجاع AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    إذا (ret < 0 && ret != AVERROR(EINVAL))
        إرجاع ret;

    إذا (ret >= 0) {
        ثابت حرف *end_par = strchr(str, ')');
        إذا (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            إرجاع AVERROR(EINVAL);
        }
        إرجاع 0;
    }

    errno = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    إذا (!errno && !*end && !strchr(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        إرجاع 0;
    }

    errno = 0;
    channels = strtol(str, &end, 10);

    /* number of channels */
    إذا (!errno && !strcmp(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        إذا (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            إرجاع 0;
    }

    /* number of unordered channels */
    إذا (!errno && (!strcmp(end, "C") || !strcmp(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        إرجاع 0;
    }

    إرجاع AVERROR(EINVAL);
}

فراغ av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    إذا (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, حجم(*channel_layout));
}

صحيح av_channel_layout_copy(AVChannelLayout *dst, ثابت AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    إذا (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, حجم(*dst->u.map));
        إذا (!dst->u.map)
            إرجاع AVERROR(ENOMEM);
        memcpy(dst->u.map, src->u.map, src->nb_channels * حجم(*src->u.map));
    }
    إرجاع 0;
}

ساكن int64_t masked_description(ثابت AVChannelLayout *channel_layout, صحيح start_channel)
{
    uint64_t mask = 0;
    لكل (صحيح i = start_channel; i < channel_layout->nb_channels; i++) {
        تعداد AVChannel ch = channel_layout->u.map[i].id;
        إذا (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        وإلا
            إرجاع AVERROR(EINVAL);
    }
    إرجاع mask;
}

ساكن صحيح has_channel_names(ثابت AVChannelLayout *channel_layout)
{
    إذا (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        إرجاع 0;
    لكل (صحيح i = 0; i < channel_layout->nb_channels; i++)
        إذا (channel_layout->u.map[i].name[0])
            إرجاع 1;
    إرجاع 0;
}

صحيح av_channel_layout_ambisonic_order(ثابت AVChannelLayout *channel_layout)
{
    صحيح i, highest_ambi, order;

    إذا (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        إرجاع AVERROR(EINVAL);

    highest_ambi = -1;
    إذا (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    وإلا {
        ثابت AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        لكل (i = 0; i < channel_layout->nb_channels; i++) {
            صحيح is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            إذا (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                إرجاع AVERROR(EINVAL);

            /* non-default ordering */
            إذا (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                إرجاع AVERROR(EINVAL);

            إذا (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    إذا (highest_ambi < 0)
        إرجاع AVERROR(EINVAL);

    order = floor(sqrt(highest_ambi));
    /* incomplete order - some harmonics are missing */
    إذا ((order + 1) * (order + 1) != highest_ambi + 1)
        إرجاع AVERROR(EINVAL);

    إرجاع order;
}

ساكن تعداد AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    صحيح has_known_channel = 0;
    صحيح order;

    إذا (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        إرجاع channel_layout->order;

    إذا (has_channel_names(channel_layout))
        إرجاع AV_CHANNEL_ORDER_CUSTOM;

    لكل (صحيح i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        إذا (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    إذا (!has_known_channel)
        إرجاع AV_CHANNEL_ORDER_UNSPEC;

    إذا (masked_description(channel_layout, 0) > 0)
        إرجاع AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    إذا (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
        إرجاع AV_CHANNEL_ORDER_AMBISONIC;

    إرجاع AV_CHANNEL_ORDER_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
ساكن صحيح try_describe_ambisonic(AVBPrint *bp, ثابت AVChannelLayout *channel_layout)
{
    صحيح nb_ambi_channels;
    صحيح order = av_channel_layout_ambisonic_order(channel_layout);
    إذا (order < 0)
        إرجاع order;

    av_bprintf(bp, "ambisonic %d", order);

    /* extra channels present */
    nb_ambi_channels = (order + 1) * (order + 1);
    إذا (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        إذا (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC) {
            extra.order       = AV_CHANNEL_ORDER_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.mask);
            extra.u.mask      = channel_layout->u.mask;
        } وإلا {
            int64_t mask;
            إذا (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.order       = AV_CHANNEL_ORDER_NATIVE;
                extra.nb_channels = av_popcount64(mask);
                extra.u.mask      = mask;
            } وإلا {
                extra.order       = AV_CHANNEL_ORDER_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    إرجاع 0;
}

صحيح av_channel_layout_describe_bprint(ثابت AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    صحيح i;

    بدل (channel_layout->order) {
    حالة AV_CHANNEL_ORDER_NATIVE:
        لكل (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            إذا (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                إرجاع 0;
            }
        av_fallthrough;
    حالة AV_CHANNEL_ORDER_CUSTOM:
        إذا (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            صحيح res = try_describe_ambisonic(bp, channel_layout);
            إذا (res >= 0)
                إرجاع 0;
            إذا (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                إرجاع av_channel_layout_describe_bprint(&native, bp);
            }
        }
        إذا (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        لكل (i = 0; i < channel_layout->nb_channels; i++) {
            تعداد AVChannel ch = av_channel_layout_channel_from_index(channel_layout, i);

            إذا (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            إذا (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        إذا (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            إرجاع 0;
        }
        av_fallthrough;
    حالة AV_CHANNEL_ORDER_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        إرجاع 0;
    حالة AV_CHANNEL_ORDER_AMBISONIC:
        إرجاع try_describe_ambisonic(bp, channel_layout);
    افتراضي:
        إرجاع AVERROR(EINVAL);
    }
}

صحيح av_channel_layout_describe(ثابت AVChannelLayout *channel_layout,
                               حرف *buf, size_t buf_size)
{
    AVBPrint bp;
    صحيح ret;

    إذا (!buf && buf_size)
        إرجاع AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    إذا (ret < 0)
        إرجاع ret;

    إذا (bp.len >= INT_MAX)
        إرجاع AVERROR(ERANGE);
    إرجاع bp.len + 1;
}

تعداد AVChannel
av_channel_layout_channel_from_index(ثابت AVChannelLayout *channel_layout,
                                     unsigned صحيح idx)
{
    صحيح i;

    إذا (idx >= channel_layout->nb_channels)
        إرجاع AV_CHAN_NONE;

    بدل (channel_layout->order) {
    حالة AV_CHANNEL_ORDER_CUSTOM:
        إرجاع channel_layout->u.map[idx].id;
    حالة AV_CHANNEL_ORDER_AMBISONIC: {
        صحيح ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        إذا (idx < ambi_channels)
            إرجاع AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    حالة AV_CHANNEL_ORDER_NATIVE:
        لكل (i = 0; i < 64; i++) {
            إذا ((1ULL << i) & channel_layout->u.mask && !idx--)
                إرجاع i;
        }
        av_fallthrough;
    افتراضي:
        إرجاع AV_CHAN_NONE;
    }
}

تعداد AVChannel
av_channel_layout_channel_from_string(ثابت AVChannelLayout *channel_layout,
                                      ثابت حرف *str)
{
    صحيح index = av_channel_layout_index_from_string(channel_layout, str);

    إذا (index < 0)
        إرجاع AV_CHAN_NONE;

    إرجاع av_channel_layout_channel_from_index(channel_layout, index);
}

صحيح av_channel_layout_index_from_channel(ثابت AVChannelLayout *channel_layout,
                                         تعداد AVChannel channel)
{
    صحيح i;

    إذا (channel == AV_CHAN_NONE)
        إرجاع AVERROR(EINVAL);

    بدل (channel_layout->order) {
    حالة AV_CHANNEL_ORDER_CUSTOM:
        لكل (i = 0; i < channel_layout->nb_channels; i++)
            إذا (channel_layout->u.map[i].id == channel)
                إرجاع i;
        إرجاع AVERROR(EINVAL);
    حالة AV_CHANNEL_ORDER_AMBISONIC:
    حالة AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        صحيح ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        إذا (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            إذا (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                إرجاع AVERROR(EINVAL);
            إرجاع channel - AV_CHAN_AMBISONIC_BASE;
        }
        إذا ((unsigned)channel > 63 || !(mask & (1ULL << channel)))
            إرجاع AVERROR(EINVAL);
        mask &= (1ULL << channel) - 1;
        إرجاع av_popcount64(mask) + ambi_channels;
        }
    افتراضي:
        إرجاع AVERROR(EINVAL);
    }
}

صحيح av_channel_layout_index_from_string(ثابت AVChannelLayout *channel_layout,
                                        ثابت حرف *str)
{
    ثابت حرف *chname;
    تعداد AVChannel ch = AV_CHAN_NONE;

    بدل (channel_layout->order) {
    حالة AV_CHANNEL_ORDER_CUSTOM:
        chname = strstr(str, "@");
        إذا (chname) {
            حرف buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(حجم(buf), chname - str));
            إذا (!*chname)
                chname = عدم;
            ch = av_channel_from_string(buf);
            إذا (ch == AV_CHAN_NONE && *buf)
                إرجاع AVERROR(EINVAL);
        }
        لكل (صحيح i = 0; chname && i < channel_layout->nb_channels; i++) {
            إذا (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                إرجاع i;
        }
        av_fallthrough;
    حالة AV_CHANNEL_ORDER_AMBISONIC:
    حالة AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        إذا (ch == AV_CHAN_NONE)
            إرجاع AVERROR(EINVAL);
        إرجاع av_channel_layout_index_from_channel(channel_layout, ch);
    }

    إرجاع AVERROR(EINVAL);
}

صحيح av_channel_layout_check(ثابت AVChannelLayout *channel_layout)
{
    إذا (channel_layout->nb_channels <= 0)
        إرجاع 0;

    بدل (channel_layout->order) {
    حالة AV_CHANNEL_ORDER_NATIVE:
        إرجاع av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    حالة AV_CHANNEL_ORDER_CUSTOM:
        إذا (!channel_layout->u.map)
            إرجاع 0;
        لكل (صحيح i = 0; i < channel_layout->nb_channels; i++) {
            إذا (channel_layout->u.map[i].id == AV_CHAN_NONE)
                إرجاع 0;
        }
        إرجاع 1;
    حالة AV_CHANNEL_ORDER_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        إرجاع av_popcount64(channel_layout->u.mask) < channel_layout->nb_channels;
    حالة AV_CHANNEL_ORDER_UNSPEC:
        إرجاع 1;
    افتراضي:
        إرجاع 0;
    }
}

صحيح av_channel_layout_compare(ثابت AVChannelLayout *chl, ثابت AVChannelLayout *chl1)
{
    صحيح i;

    /* different channel counts -> not equal */
    إذا (chl->nb_channels != chl1->nb_channels)
        إرجاع 1;

    /* if only one is unspecified -> not equal */
    إذا ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        إرجاع 1;
    /* both are unspecified -> equal */
    وإلا إذا (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        إرجاع 0;

    /* can compare masks directly */
    إذا ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        إرجاع chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    لكل (i = 0; i < chl->nb_channels; i++)
        إذا (av_channel_layout_channel_from_index(chl,  i) !=
            av_channel_layout_channel_from_index(chl1, i))
            إرجاع 1;
    إرجاع 0;
}

فراغ av_channel_layout_default(AVChannelLayout *ch_layout, صحيح nb_channels)
{
    صحيح i;
    لكل (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        إذا (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            إرجاع;
        }

    ch_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

ثابت AVChannelLayout *av_channel_layout_standard(فراغ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ثابت AVChannelLayout *ch_layout = عدم;

    إذا (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (فراغ*)(i + 1);
    }

    إرجاع ch_layout;
}

uint64_t av_channel_layout_subset(ثابت AVChannelLayout *channel_layout,
                                  uint64_t mask)
{
    uint64_t ret = 0;
    صحيح i;

    بدل (channel_layout->order) {
    حالة AV_CHANNEL_ORDER_NATIVE:
    حالة AV_CHANNEL_ORDER_AMBISONIC:
        إرجاع channel_layout->u.mask & mask;
    حالة AV_CHANNEL_ORDER_CUSTOM:
        لكل (i = 0; i < 64; i++)
            إذا (mask & (1ULL << i) && av_channel_layout_index_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        اكسر;
    }

    إرجاع ret;
}

صحيح av_channel_layout_retype(AVChannelLayout *channel_layout, تعداد AVChannelOrder order, صحيح flags)
{
    صحيح allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    صحيح lossy;

    إذا (!av_channel_layout_check(channel_layout))
        إرجاع AVERROR(EINVAL);

    إذا (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    إذا (channel_layout->order == order)
        إرجاع 0;

    بدل (order) {
    حالة AV_CHANNEL_ORDER_UNSPEC: {
        صحيح nb_channels = channel_layout->nb_channels;
        إذا (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            لكل (صحيح i = 0; i < nb_channels; i++) {
                إذا (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    اكسر;
                }
            }
        } وإلا {
            lossy = 1;
        }
        إذا (!lossy || allow_lossy) {
            فراغ *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            إرجاع lossy;
        }
        إرجاع AVERROR(ENOSYS);
        }
    حالة AV_CHANNEL_ORDER_NATIVE:
        إذا (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            إذا (mask < 0)
                إرجاع AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            إذا (!lossy || allow_lossy) {
                فراغ *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_mask(channel_layout, mask);
                channel_layout->opaque = opaque;
                إرجاع lossy;
            }
        }
        إرجاع AVERROR(ENOSYS);
    حالة AV_CHANNEL_ORDER_CUSTOM: {
        AVChannelLayout custom = { 0 };
        صحيح ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        فراغ *opaque = channel_layout->opaque;
        إذا (ret < 0)
            إرجاع ret;
        إذا (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            لكل (صحيح i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_index(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        إرجاع 0;
        }
    حالة AV_CHANNEL_ORDER_AMBISONIC:
        إذا (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            صحيح nb_channels = channel_layout->nb_channels;
            صحيح amb_order = av_channel_layout_ambisonic_order(channel_layout);
            إذا (amb_order < 0)
                إرجاع AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            إذا (mask < 0)
                إرجاع AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            إذا (!lossy || allow_lossy) {
                فراغ *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.mask      = mask;
                channel_layout->opaque      = opaque;
                إرجاع lossy;
            }
        }
        إرجاع AVERROR(ENOSYS);
    افتراضي:
        إرجاع AVERROR(EINVAL);
    }
}
