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

#অন্তর্ভাৱ <stdint.h>
#অন্তর্ভাৱ <stdlib.h>
#অন্তর্ভাৱ <string.h>

#অন্তর্ভাৱ "avassert.h"
#অন্তর্ভাৱ "channel_layout.h"
#অন্তর্ভাৱ "bprint.h"
#অন্তর্ভাৱ "common.h"
#অন্তর্ভাৱ "error.h"
#অন্তর্ভাৱ "attributes.h"
#অন্তর্ভাৱ "macros.h"
#অন্তর্ভাৱ "mem.h"
#অন্তর্ভাৱ "opt.h"

#define CHAN_IS_AMBI(x) ((x) >= AV_CHAN_AMBISONIC_BASE &&\
                         (x) <= AV_CHAN_AMBISONIC_END)

সংরচনা channel_name {
    ধ্রুৱ ৱর্ণ *name;
    ধ্রুৱ ৱর্ণ *description;
};

স্থির ধ্রুৱ সংরচনা channel_name channel_names[] = {
    [AV_CHAN_FRONT_বাম           ] = { "FL",        "front left"            },
    [AV_CHAN_FRONT_ডান          ] = { "FR",        "front right"           },
    [AV_CHAN_FRONT_CENTER         ] = { "FC",        "front center"          },
    [AV_CHAN_নিচেৰ_FREQUENCY        ] = { "LFE",       "low frequency"         },
    [AV_CHAN_BACK_বাম            ] = { "BL",        "back left"             },
    [AV_CHAN_BACK_ডান           ] = { "BR",        "back right"            },
    [AV_CHAN_FRONT_বাম_OF_CENTER ] = { "FLC",       "front left-of-center"  },
    [AV_CHAN_FRONT_ডান_OF_CENTER] = { "FRC",       "front right-of-center" },
    [AV_CHAN_BACK_CENTER          ] = { "BC",        "back center"           },
    [AV_CHAN_SIDE_বাম            ] = { "SL",        "side left"             },
    [AV_CHAN_SIDE_ডান           ] = { "SR",        "side right"            },
    [AV_CHAN_শীৰ্ষ_CENTER           ] = { "TC",        "top center"            },
    [AV_CHAN_শীৰ্ষ_FRONT_বাম       ] = { "TFL",       "top front left"        },
    [AV_CHAN_শীৰ্ষ_FRONT_CENTER     ] = { "TFC",       "top front center"      },
    [AV_CHAN_শীৰ্ষ_FRONT_ডান      ] = { "TFR",       "top front right"       },
    [AV_CHAN_শীৰ্ষ_BACK_বাম        ] = { "TBL",       "top back left"         },
    [AV_CHAN_শীৰ্ষ_BACK_CENTER      ] = { "TBC",       "top back center"       },
    [AV_CHAN_শীৰ্ষ_BACK_ডান       ] = { "TBR",       "top back right"        },
    [AV_CHAN_STEREO_বাম          ] = { "DL",        "downmix left"          },
    [AV_CHAN_STEREO_ডান         ] = { "DR",        "downmix right"         },
    [AV_CHAN_WIDE_বাম            ] = { "WL",        "wide left"             },
    [AV_CHAN_WIDE_ডান           ] = { "WR",        "wide right"            },
    [AV_CHAN_SURROUND_DIRECT_বাম ] = { "SDL",       "surround direct left"  },
    [AV_CHAN_SURROUND_DIRECT_ডান] = { "SDR",       "surround direct right" },
    [AV_CHAN_নিচেৰ_FREQUENCY_2      ] = { "LFE2",      "low frequency 2"       },
    [AV_CHAN_শীৰ্ষ_SIDE_বাম        ] = { "TSL",       "top side left"         },
    [AV_CHAN_শীৰ্ষ_SIDE_ডান       ] = { "TSR",       "top side right"        },
    [AV_CHAN_BOTTOM_FRONT_CENTER  ] = { "BFC",       "bottom front center"   },
    [AV_CHAN_BOTTOM_FRONT_বাম    ] = { "BFL",       "bottom front left"     },
    [AV_CHAN_BOTTOM_FRONT_ডান   ] = { "BFR",       "bottom front right"    },
    [AV_CHAN_SIDE_SURROUND_বাম   ] = { "SSL",       "side surround left"    },
    [AV_CHAN_SIDE_SURROUND_ডান  ] = { "SSR",       "side surround right"   },
    [AV_CHAN_শীৰ্ষ_SURROUND_বাম    ] = { "TTL",       "top surround left"     },
    [AV_CHAN_শীৰ্ষ_SURROUND_ডান   ] = { "TTR",       "top surround right"    },
    [AV_CHAN_BINAURAL_বাম        ] = { "BIL",       "binaural left"         },
    [AV_CHAN_BINAURAL_ডান       ] = { "BIR",       "binaural right"        },
};

শূন্য av_channel_name_bprint(AVBPrint *bp, গণনা AVChannel channel_id)
{
    যদি (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_BASE);
    অন্যথা যদি ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].name)
        av_bprintf(bp, "%s", channel_names[channel_id].name);
    অন্যথা যদি (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    অন্যথা যদি (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    অন্যথা যদি (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "UNSD");
    অন্যথা
        av_bprintf(bp, "USR%d", channel_id);
}

পূর্ণাঙ্ক av_channel_name(ৱর্ণ *buf, size_t buf_size, গণনা AVChannel channel_id)
{
    AVBPrint bp;

    যদি (!buf && buf_size)
        ঘূৰাই AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_name_bprint(&bp, channel_id);

    যদি (bp.len >= INT_MAX)
        ঘূৰাই AVERROR(ERANGE);
    ঘূৰাই bp.len + 1;
}

শূন্য av_channel_description_bprint(AVBPrint *bp, গণনা AVChannel channel_id)
{
    যদি (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_BASE);
    অন্যথা যদি ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].description)
        av_bprintf(bp, "%s", channel_names[channel_id].description);
    অন্যথা যদি (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    অন্যথা যদি (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    অন্যথা যদি (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "unused");
    অন্যথা
        av_bprintf(bp, "user %d", channel_id);
}

পূর্ণাঙ্ক av_channel_description(ৱর্ণ *buf, size_t buf_size, গণনা AVChannel channel_id)
{
    AVBPrint bp;

    যদি (!buf && buf_size)
        ঘূৰাই AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_description_bprint(&bp, channel_id);

    যদি (bp.len >= INT_MAX)
        ঘূৰাই AVERROR(ERANGE);
    ঘূৰাই bp.len + 1;
}

গণনা AVChannel av_channel_from_string(ধ্রুৱ ৱর্ণ *str)
{
    পূর্ণাঙ্ক i;
    ৱর্ণ *endptr = (ৱর্ণ *)str;
    গণনা AVChannel id = AV_CHAN_NONE;

    যদি (!strncmp(str, "AMBI", 4)) {
        i = strtol(str + 4, রিক্ত, 0);
        যদি (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            ঘূৰাই AV_CHAN_NONE;
        ঘূৰাই AV_CHAN_AMBISONIC_BASE + i;
    }

    বাবে (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        যদি (channel_names[i].name && !strcmp(str, channel_names[i].name))
            ঘূৰাই i;
    }
    যদি (!strcmp(str, "UNK"))
        ঘূৰাই AV_CHAN_UNKNOWN;
    যদি (!strcmp(str, "UNSD"))
        ঘূৰাই AV_CHAN_UNUSED;

    যদি (!strncmp(str, "USR", 3)) {
        ধ্রুৱ ৱর্ণ *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    যদি (id >= 0 && !*endptr)
        ঘূৰাই id;

    ঘূৰাই AV_CHAN_NONE;
}

সংরচনা channel_layout_name {
    ধ্রুৱ ৱর্ণ *name;
    AVChannelLayout layout;
};

স্থির ধ্রুৱ সংরচনা channel_layout_name channel_layout_map[] = {
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

পূর্ণাঙ্ক av_channel_layout_custom_init(AVChannelLayout *channel_layout, পূর্ণাঙ্ক nb_channels)
{
    AVChannelCustom *map;

    যদি (nb_channels <= 0)
        ঘূৰাই AVERROR(EINVAL);

    map = av_calloc(nb_channels, পরিমাণ(*channel_layout->u.map));
    যদি (!map)
        ঘূৰাই AVERROR(ENOMEM);
    বাবে (পূর্ণাঙ্ক i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->order       = AV_CHANNEL_ORDER_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    ঘূৰাই 0;
}

পূর্ণাঙ্ক av_channel_layout_from_mask(AVChannelLayout *channel_layout,
                                uint64_t mask)
{
    যদি (!mask)
        ঘূৰাই AVERROR(EINVAL);

    channel_layout->order       = AV_CHANNEL_ORDER_NATIVE;
    channel_layout->nb_channels = av_popcount64(mask);
    channel_layout->u.mask      = mask;

    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক parse_channel_list(AVChannelLayout *ch_layout, ধ্রুৱ ৱর্ণ *str)
{
    পূর্ণাঙ্ক ret;
    পূর্ণাঙ্ক nb_channels = 0;
    AVChannelCustom *map = রিক্ত;
    AVChannelCustom custom = {0};

    যেতিয়ালৈ (*str) {
        ৱর্ণ *channel, *chname;
        ret = av_opt_get_চাবি_মান(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_চাবি, &channel, &chname);
        যদি (ret < 0) {
            av_freep(&map);
            ঘূৰাই ret;
        }
        যদি (*str)
            str++; // skip separator
        যদি (!channel) {
            channel = chname;
            chname = রিক্ত;
        }
        av_strlcpy(custom.name, chname ? chname : "", পরিমাণ(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        যদি (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            ঘূৰাই AVERROR(EINVAL);
        }

        av_dynarray2_add((শূন্য **)&map, &nb_channels, পরিমাণ(custom), (শূন্য *)&custom);
        যদি (!map)
            ঘূৰাই AVERROR(ENOMEM);
    }

    যদি (!nb_channels)
        ঘূৰাই AVERROR(EINVAL);

    ch_layout->order = AV_CHANNEL_ORDER_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    ঘূৰাই 0;
}

পূর্ণাঙ্ক av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  ধ্রুৱ ৱর্ণ *str)
{
    পূর্ণাঙ্ক i, matches, ret;
    পূর্ণাঙ্ক channels = 0, nb_channels = 0;
    ৱর্ণ *chlist, *end;
    uint64_t mask = 0;

    /* channel layout names */
    বাবে (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        যদি (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            ঘূৰাই 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, পরিমাণ(*channel_layout));

    /* ambisonic */
    যদি (!strncmp(str, "ambisonic ", 10)) {
        ধ্রুৱ ৱর্ণ *p = str + 10;
        ৱর্ণ *endptr;
        AVChannelLayout extra = {0};
        পূর্ণাঙ্ক order;

        order = strtol(p, &endptr, 0);
        যদি (order < 0 || order + 1  > INT_MAX / (order + 1) ||
            (*endptr && *endptr != '+'))
            ঘূৰাই AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        যদি (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            যদি (ret < 0)
                ঘূৰাই ret;
            যদি (extra.nb_channels >= INT_MAX - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                ঘূৰাই AVERROR(EINVAL);
            }

            যদি (extra.order == AV_CHANNEL_ORDER_NATIVE) {
                channel_layout->u.mask = extra.u.mask;
            } অন্যথা {
                channel_layout->order = AV_CHANNEL_ORDER_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              পরিমাণ(*channel_layout->u.map));
                যদি (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    ঘূৰাই AVERROR(ENOMEM);
                }

                বাবে (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                বাবে (i = 0; i < extra.nb_channels; i++) {
                    গণনা AVChannel ch = av_channel_layout_channel_from_index(&extra, i);
                    যদি (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        ঘূৰাই AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    যদি (extra.order == AV_CHANNEL_ORDER_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   পরিমাণ(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        ঘূৰাই 0;
    }

    chlist = av_strdup(str);
    যদি (!chlist)
        ঘূৰাই AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    যদি (ret < 0 && ret != AVERROR(EINVAL))
        ঘূৰাই ret;

    যদি (ret >= 0) {
        ধ্রুৱ ৱর্ণ *end_par = strchr(str, ')');
        যদি (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            ঘূৰাই AVERROR(EINVAL);
        }
        ঘূৰাই 0;
    }

    errno = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    যদি (!errno && !*end && !strchr(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        ঘূৰাই 0;
    }

    errno = 0;
    channels = strtol(str, &end, 10);

    /* number of channels */
    যদি (!errno && !strcmp(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        যদি (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            ঘূৰাই 0;
    }

    /* number of unordered channels */
    যদি (!errno && (!strcmp(end, "C") || !strcmp(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        ঘূৰাই 0;
    }

    ঘূৰাই AVERROR(EINVAL);
}

শূন্য av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    যদি (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, পরিমাণ(*channel_layout));
}

পূর্ণাঙ্ক av_channel_layout_copy(AVChannelLayout *dst, ধ্রুৱ AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    যদি (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, পরিমাণ(*dst->u.map));
        যদি (!dst->u.map)
            ঘূৰাই AVERROR(ENOMEM);
        memcpy(dst->u.map, src->u.map, src->nb_channels * পরিমাণ(*src->u.map));
    }
    ঘূৰাই 0;
}

স্থির int64_t masked_description(ধ্রুৱ AVChannelLayout *channel_layout, পূর্ণাঙ্ক start_channel)
{
    uint64_t mask = 0;
    বাবে (পূর্ণাঙ্ক i = start_channel; i < channel_layout->nb_channels; i++) {
        গণনা AVChannel ch = channel_layout->u.map[i].id;
        যদি (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        অন্যথা
            ঘূৰাই AVERROR(EINVAL);
    }
    ঘূৰাই mask;
}

স্থির পূর্ণাঙ্ক has_channel_names(ধ্রুৱ AVChannelLayout *channel_layout)
{
    যদি (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ঘূৰাই 0;
    বাবে (পূর্ণাঙ্ক i = 0; i < channel_layout->nb_channels; i++)
        যদি (channel_layout->u.map[i].name[0])
            ঘূৰাই 1;
    ঘূৰাই 0;
}

পূর্ণাঙ্ক av_channel_layout_ambisonic_order(ধ্রুৱ AVChannelLayout *channel_layout)
{
    পূর্ণাঙ্ক i, highest_ambi, order;

    যদি (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ঘূৰাই AVERROR(EINVAL);

    highest_ambi = -1;
    যদি (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    অন্যথা {
        ধ্রুৱ AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        বাবে (i = 0; i < channel_layout->nb_channels; i++) {
            পূর্ণাঙ্ক is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            যদি (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                ঘূৰাই AVERROR(EINVAL);

            /* non-default ordering */
            যদি (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                ঘূৰাই AVERROR(EINVAL);

            যদি (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    যদি (highest_ambi < 0)
        ঘূৰাই AVERROR(EINVAL);

    order = floor(sqrt(highest_ambi));
    /* incomplete order - some harmonics are missing */
    যদি ((order + 1) * (order + 1) != highest_ambi + 1)
        ঘূৰাই AVERROR(EINVAL);

    ঘূৰাই order;
}

স্থির গণনা AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    পূর্ণাঙ্ক has_known_channel = 0;
    পূর্ণাঙ্ক order;

    যদি (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ঘূৰাই channel_layout->order;

    যদি (has_channel_names(channel_layout))
        ঘূৰাই AV_CHANNEL_ORDER_CUSTOM;

    বাবে (পূর্ণাঙ্ক i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        যদি (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    যদি (!has_known_channel)
        ঘূৰাই AV_CHANNEL_ORDER_UNSPEC;

    যদি (masked_description(channel_layout, 0) > 0)
        ঘূৰাই AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    যদি (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
        ঘূৰাই AV_CHANNEL_ORDER_AMBISONIC;

    ঘূৰাই AV_CHANNEL_ORDER_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
স্থির পূর্ণাঙ্ক try_describe_ambisonic(AVBPrint *bp, ধ্রুৱ AVChannelLayout *channel_layout)
{
    পূর্ণাঙ্ক nb_ambi_channels;
    পূর্ণাঙ্ক order = av_channel_layout_ambisonic_order(channel_layout);
    যদি (order < 0)
        ঘূৰাই order;

    av_bprintf(bp, "ambisonic %d", order);

    /* extra channels present */
    nb_ambi_channels = (order + 1) * (order + 1);
    যদি (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        যদি (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC) {
            extra.order       = AV_CHANNEL_ORDER_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.mask);
            extra.u.mask      = channel_layout->u.mask;
        } অন্যথা {
            int64_t mask;
            যদি (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.order       = AV_CHANNEL_ORDER_NATIVE;
                extra.nb_channels = av_popcount64(mask);
                extra.u.mask      = mask;
            } অন্যথা {
                extra.order       = AV_CHANNEL_ORDER_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    ঘূৰাই 0;
}

পূর্ণাঙ্ক av_channel_layout_describe_bprint(ধ্রুৱ AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    পূর্ণাঙ্ক i;

    ৱিকল্প (channel_layout->order) {
    পক্ষ AV_CHANNEL_ORDER_NATIVE:
        বাবে (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            যদি (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                ঘূৰাই 0;
            }
        av_fallthrough;
    পক্ষ AV_CHANNEL_ORDER_CUSTOM:
        যদি (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            পূর্ণাঙ্ক res = try_describe_ambisonic(bp, channel_layout);
            যদি (res >= 0)
                ঘূৰাই 0;
            যদি (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                ঘূৰাই av_channel_layout_describe_bprint(&native, bp);
            }
        }
        যদি (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        বাবে (i = 0; i < channel_layout->nb_channels; i++) {
            গণনা AVChannel ch = av_channel_layout_channel_from_index(channel_layout, i);

            যদি (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            যদি (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        যদি (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            ঘূৰাই 0;
        }
        av_fallthrough;
    পক্ষ AV_CHANNEL_ORDER_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        ঘূৰাই 0;
    পক্ষ AV_CHANNEL_ORDER_AMBISONIC:
        ঘূৰাই try_describe_ambisonic(bp, channel_layout);
    স্ৱভাৱ:
        ঘূৰাই AVERROR(EINVAL);
    }
}

পূর্ণাঙ্ক av_channel_layout_describe(ধ্রুৱ AVChannelLayout *channel_layout,
                               ৱর্ণ *buf, size_t buf_size)
{
    AVBPrint bp;
    পূর্ণাঙ্ক ret;

    যদি (!buf && buf_size)
        ঘূৰাই AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    যদি (ret < 0)
        ঘূৰাই ret;

    যদি (bp.len >= INT_MAX)
        ঘূৰাই AVERROR(ERANGE);
    ঘূৰাই bp.len + 1;
}

গণনা AVChannel
av_channel_layout_channel_from_index(ধ্রুৱ AVChannelLayout *channel_layout,
                                     unsigned পূর্ণাঙ্ক idx)
{
    পূর্ণাঙ্ক i;

    যদি (idx >= channel_layout->nb_channels)
        ঘূৰাই AV_CHAN_NONE;

    ৱিকল্প (channel_layout->order) {
    পক্ষ AV_CHANNEL_ORDER_CUSTOM:
        ঘূৰাই channel_layout->u.map[idx].id;
    পক্ষ AV_CHANNEL_ORDER_AMBISONIC: {
        পূর্ণাঙ্ক ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        যদি (idx < ambi_channels)
            ঘূৰাই AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    পক্ষ AV_CHANNEL_ORDER_NATIVE:
        বাবে (i = 0; i < 64; i++) {
            যদি ((1ULL << i) & channel_layout->u.mask && !idx--)
                ঘূৰাই i;
        }
        av_fallthrough;
    স্ৱভাৱ:
        ঘূৰাই AV_CHAN_NONE;
    }
}

গণনা AVChannel
av_channel_layout_channel_from_string(ধ্রুৱ AVChannelLayout *channel_layout,
                                      ধ্রুৱ ৱর্ণ *str)
{
    পূর্ণাঙ্ক index = av_channel_layout_index_from_string(channel_layout, str);

    যদি (index < 0)
        ঘূৰাই AV_CHAN_NONE;

    ঘূৰাই av_channel_layout_channel_from_index(channel_layout, index);
}

পূর্ণাঙ্ক av_channel_layout_index_from_channel(ধ্রুৱ AVChannelLayout *channel_layout,
                                         গণনা AVChannel channel)
{
    পূর্ণাঙ্ক i;

    যদি (channel == AV_CHAN_NONE)
        ঘূৰাই AVERROR(EINVAL);

    ৱিকল্প (channel_layout->order) {
    পক্ষ AV_CHANNEL_ORDER_CUSTOM:
        বাবে (i = 0; i < channel_layout->nb_channels; i++)
            যদি (channel_layout->u.map[i].id == channel)
                ঘূৰাই i;
        ঘূৰাই AVERROR(EINVAL);
    পক্ষ AV_CHANNEL_ORDER_AMBISONIC:
    পক্ষ AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        পূর্ণাঙ্ক ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        যদি (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            যদি (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                ঘূৰাই AVERROR(EINVAL);
            ঘূৰাই channel - AV_CHAN_AMBISONIC_BASE;
        }
        যদি ((unsigned)channel > 63 || !(mask & (1ULL << channel)))
            ঘূৰাই AVERROR(EINVAL);
        mask &= (1ULL << channel) - 1;
        ঘূৰাই av_popcount64(mask) + ambi_channels;
        }
    স্ৱভাৱ:
        ঘূৰাই AVERROR(EINVAL);
    }
}

পূর্ণাঙ্ক av_channel_layout_index_from_string(ধ্রুৱ AVChannelLayout *channel_layout,
                                        ধ্রুৱ ৱর্ণ *str)
{
    ধ্রুৱ ৱর্ণ *chname;
    গণনা AVChannel ch = AV_CHAN_NONE;

    ৱিকল্প (channel_layout->order) {
    পক্ষ AV_CHANNEL_ORDER_CUSTOM:
        chname = strstr(str, "@");
        যদি (chname) {
            ৱর্ণ buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(পরিমাণ(buf), chname - str));
            যদি (!*chname)
                chname = রিক্ত;
            ch = av_channel_from_string(buf);
            যদি (ch == AV_CHAN_NONE && *buf)
                ঘূৰাই AVERROR(EINVAL);
        }
        বাবে (পূর্ণাঙ্ক i = 0; chname && i < channel_layout->nb_channels; i++) {
            যদি (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                ঘূৰাই i;
        }
        av_fallthrough;
    পক্ষ AV_CHANNEL_ORDER_AMBISONIC:
    পক্ষ AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        যদি (ch == AV_CHAN_NONE)
            ঘূৰাই AVERROR(EINVAL);
        ঘূৰাই av_channel_layout_index_from_channel(channel_layout, ch);
    }

    ঘূৰাই AVERROR(EINVAL);
}

পূর্ণাঙ্ক av_channel_layout_check(ধ্রুৱ AVChannelLayout *channel_layout)
{
    যদি (channel_layout->nb_channels <= 0)
        ঘূৰাই 0;

    ৱিকল্প (channel_layout->order) {
    পক্ষ AV_CHANNEL_ORDER_NATIVE:
        ঘূৰাই av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    পক্ষ AV_CHANNEL_ORDER_CUSTOM:
        যদি (!channel_layout->u.map)
            ঘূৰাই 0;
        বাবে (পূর্ণাঙ্ক i = 0; i < channel_layout->nb_channels; i++) {
            যদি (channel_layout->u.map[i].id == AV_CHAN_NONE)
                ঘূৰাই 0;
        }
        ঘূৰাই 1;
    পক্ষ AV_CHANNEL_ORDER_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        ঘূৰাই av_popcount64(channel_layout->u.mask) < channel_layout->nb_channels;
    পক্ষ AV_CHANNEL_ORDER_UNSPEC:
        ঘূৰাই 1;
    স্ৱভাৱ:
        ঘূৰাই 0;
    }
}

পূর্ণাঙ্ক av_channel_layout_compare(ধ্রুৱ AVChannelLayout *chl, ধ্রুৱ AVChannelLayout *chl1)
{
    পূর্ণাঙ্ক i;

    /* different channel counts -> not equal */
    যদি (chl->nb_channels != chl1->nb_channels)
        ঘূৰাই 1;

    /* if only one is unspecified -> not equal */
    যদি ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        ঘূৰাই 1;
    /* both are unspecified -> equal */
    অন্যথা যদি (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        ঘূৰাই 0;

    /* can compare masks directly */
    যদি ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        ঘূৰাই chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    বাবে (i = 0; i < chl->nb_channels; i++)
        যদি (av_channel_layout_channel_from_index(chl,  i) !=
            av_channel_layout_channel_from_index(chl1, i))
            ঘূৰাই 1;
    ঘূৰাই 0;
}

শূন্য av_channel_layout_default(AVChannelLayout *ch_layout, পূর্ণাঙ্ক nb_channels)
{
    পূর্ণাঙ্ক i;
    বাবে (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        যদি (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            ঘূৰাই;
        }

    ch_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

ধ্রুৱ AVChannelLayout *av_channel_layout_standard(শূন্য **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ধ্রুৱ AVChannelLayout *ch_layout = রিক্ত;

    যদি (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (শূন্য*)(i + 1);
    }

    ঘূৰাই ch_layout;
}

uint64_t av_channel_layout_subset(ধ্রুৱ AVChannelLayout *channel_layout,
                                  uint64_t mask)
{
    uint64_t ret = 0;
    পূর্ণাঙ্ক i;

    ৱিকল্প (channel_layout->order) {
    পক্ষ AV_CHANNEL_ORDER_NATIVE:
    পক্ষ AV_CHANNEL_ORDER_AMBISONIC:
        ঘূৰাই channel_layout->u.mask & mask;
    পক্ষ AV_CHANNEL_ORDER_CUSTOM:
        বাবে (i = 0; i < 64; i++)
            যদি (mask & (1ULL << i) && av_channel_layout_index_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        ভঙ্গ;
    }

    ঘূৰাই ret;
}

পূর্ণাঙ্ক av_channel_layout_retype(AVChannelLayout *channel_layout, গণনা AVChannelOrder order, পূর্ণাঙ্ক flags)
{
    পূর্ণাঙ্ক allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    পূর্ণাঙ্ক lossy;

    যদি (!av_channel_layout_check(channel_layout))
        ঘূৰাই AVERROR(EINVAL);

    যদি (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    যদি (channel_layout->order == order)
        ঘূৰাই 0;

    ৱিকল্প (order) {
    পক্ষ AV_CHANNEL_ORDER_UNSPEC: {
        পূর্ণাঙ্ক nb_channels = channel_layout->nb_channels;
        যদি (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            বাবে (পূর্ণাঙ্ক i = 0; i < nb_channels; i++) {
                যদি (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    ভঙ্গ;
                }
            }
        } অন্যথা {
            lossy = 1;
        }
        যদি (!lossy || allow_lossy) {
            শূন্য *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            ঘূৰাই lossy;
        }
        ঘূৰাই AVERROR(ENOSYS);
        }
    পক্ষ AV_CHANNEL_ORDER_NATIVE:
        যদি (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            যদি (mask < 0)
                ঘূৰাই AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            যদি (!lossy || allow_lossy) {
                শূন্য *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_mask(channel_layout, mask);
                channel_layout->opaque = opaque;
                ঘূৰাই lossy;
            }
        }
        ঘূৰাই AVERROR(ENOSYS);
    পক্ষ AV_CHANNEL_ORDER_CUSTOM: {
        AVChannelLayout custom = { 0 };
        পূর্ণাঙ্ক ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        শূন্য *opaque = channel_layout->opaque;
        যদি (ret < 0)
            ঘূৰাই ret;
        যদি (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            বাবে (পূর্ণাঙ্ক i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_index(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        ঘূৰাই 0;
        }
    পক্ষ AV_CHANNEL_ORDER_AMBISONIC:
        যদি (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            পূর্ণাঙ্ক nb_channels = channel_layout->nb_channels;
            পূর্ণাঙ্ক amb_order = av_channel_layout_ambisonic_order(channel_layout);
            যদি (amb_order < 0)
                ঘূৰাই AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            যদি (mask < 0)
                ঘূৰাই AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            যদি (!lossy || allow_lossy) {
                শূন্য *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.mask      = mask;
                channel_layout->opaque      = opaque;
                ঘূৰাই lossy;
            }
        }
        ঘূৰাই AVERROR(ENOSYS);
    স্ৱভাৱ:
        ঘূৰাই AVERROR(EINVAL);
    }
}
