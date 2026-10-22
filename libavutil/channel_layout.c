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

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "channel_layout.h"
#অন্তর্ভাব "bprint.h"
#অন্তর্ভাব "common.h"
#অন্তর্ভাব "error.h"
#অন্তর্ভাব "attributes.h"
#অন্তর্ভাব "macros.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "opt.h"

#define CHAN_IS_AMBI(x) ((x) >= AV_CHAN_AMBISONIC_BASE &&\
                         (x) <= AV_CHAN_AMBISONIC_END)

সংরচনা channel_name {
    ধ্রুব বর্ণ *name;
    ধ্রুব বর্ণ *description;
};

স্থির ধ্রুব সংরচনা channel_name channel_names[] = {
    [AV_CHAN_FRONT_বাম           ] = { "FL",        "front left"            },
    [AV_CHAN_FRONT_ডান          ] = { "FR",        "front right"           },
    [AV_CHAN_FRONT_CENTER         ] = { "FC",        "front center"          },
    [AV_CHAN_নিচের_FREQUENCY        ] = { "LFE",       "low frequency"         },
    [AV_CHAN_BACK_বাম            ] = { "BL",        "back left"             },
    [AV_CHAN_BACK_ডান           ] = { "BR",        "back right"            },
    [AV_CHAN_FRONT_বাম_OF_CENTER ] = { "FLC",       "front left-of-center"  },
    [AV_CHAN_FRONT_ডান_OF_CENTER] = { "FRC",       "front right-of-center" },
    [AV_CHAN_BACK_CENTER          ] = { "BC",        "back center"           },
    [AV_CHAN_SIDE_বাম            ] = { "SL",        "side left"             },
    [AV_CHAN_SIDE_ডান           ] = { "SR",        "side right"            },
    [AV_CHAN_শীর্ষ_CENTER           ] = { "TC",        "top center"            },
    [AV_CHAN_শীর্ষ_FRONT_বাম       ] = { "TFL",       "top front left"        },
    [AV_CHAN_শীর্ষ_FRONT_CENTER     ] = { "TFC",       "top front center"      },
    [AV_CHAN_শীর্ষ_FRONT_ডান      ] = { "TFR",       "top front right"       },
    [AV_CHAN_শীর্ষ_BACK_বাম        ] = { "TBL",       "top back left"         },
    [AV_CHAN_শীর্ষ_BACK_CENTER      ] = { "TBC",       "top back center"       },
    [AV_CHAN_শীর্ষ_BACK_ডান       ] = { "TBR",       "top back right"        },
    [AV_CHAN_STEREO_বাম          ] = { "DL",        "downmix left"          },
    [AV_CHAN_STEREO_ডান         ] = { "DR",        "downmix right"         },
    [AV_CHAN_WIDE_বাম            ] = { "WL",        "wide left"             },
    [AV_CHAN_WIDE_ডান           ] = { "WR",        "wide right"            },
    [AV_CHAN_SURROUND_DIRECT_বাম ] = { "SDL",       "surround direct left"  },
    [AV_CHAN_SURROUND_DIRECT_ডান] = { "SDR",       "surround direct right" },
    [AV_CHAN_নিচের_FREQUENCY_2      ] = { "LFE2",      "low frequency 2"       },
    [AV_CHAN_শীর্ষ_SIDE_বাম        ] = { "TSL",       "top side left"         },
    [AV_CHAN_শীর্ষ_SIDE_ডান       ] = { "TSR",       "top side right"        },
    [AV_CHAN_BOTTOM_FRONT_CENTER  ] = { "BFC",       "bottom front center"   },
    [AV_CHAN_BOTTOM_FRONT_বাম    ] = { "BFL",       "bottom front left"     },
    [AV_CHAN_BOTTOM_FRONT_ডান   ] = { "BFR",       "bottom front right"    },
    [AV_CHAN_SIDE_SURROUND_বাম   ] = { "SSL",       "side surround left"    },
    [AV_CHAN_SIDE_SURROUND_ডান  ] = { "SSR",       "side surround right"   },
    [AV_CHAN_শীর্ষ_SURROUND_বাম    ] = { "TTL",       "top surround left"     },
    [AV_CHAN_শীর্ষ_SURROUND_ডান   ] = { "TTR",       "top surround right"    },
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

পূর্ণাঙ্ক av_channel_name(বর্ণ *buf, size_t buf_size, গণনা AVChannel channel_id)
{
    AVBPrint bp;

    যদি (!buf && buf_size)
        প্রত্যাগম AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_name_bprint(&bp, channel_id);

    যদি (bp.len >= INT_MAX)
        প্রত্যাগম AVERROR(ERANGE);
    প্রত্যাগম bp.len + 1;
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

পূর্ণাঙ্ক av_channel_description(বর্ণ *buf, size_t buf_size, গণনা AVChannel channel_id)
{
    AVBPrint bp;

    যদি (!buf && buf_size)
        প্রত্যাগম AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_description_bprint(&bp, channel_id);

    যদি (bp.len >= INT_MAX)
        প্রত্যাগম AVERROR(ERANGE);
    প্রত্যাগম bp.len + 1;
}

গণনা AVChannel av_channel_from_string(ধ্রুব বর্ণ *str)
{
    পূর্ণাঙ্ক i;
    বর্ণ *endptr = (বর্ণ *)str;
    গণনা AVChannel id = AV_CHAN_NONE;

    যদি (!strncmp(str, "AMBI", 4)) {
        i = strtol(str + 4, রিক্ত, 0);
        যদি (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            প্রত্যাগম AV_CHAN_NONE;
        প্রত্যাগম AV_CHAN_AMBISONIC_BASE + i;
    }

    প্রতি (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        যদি (channel_names[i].name && !strcmp(str, channel_names[i].name))
            প্রত্যাগম i;
    }
    যদি (!strcmp(str, "UNK"))
        প্রত্যাগম AV_CHAN_UNKNOWN;
    যদি (!strcmp(str, "UNSD"))
        প্রত্যাগম AV_CHAN_UNUSED;

    যদি (!strncmp(str, "USR", 3)) {
        ধ্রুব বর্ণ *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    যদি (id >= 0 && !*endptr)
        প্রত্যাগম id;

    প্রত্যাগম AV_CHAN_NONE;
}

সংরচনা channel_layout_name {
    ধ্রুব বর্ণ *name;
    AVChannelLayout layout;
};

স্থির ধ্রুব সংরচনা channel_layout_name channel_layout_map[] = {
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
        প্রত্যাগম AVERROR(EINVAL);

    map = av_calloc(nb_channels, পরিমাণ(*channel_layout->u.map));
    যদি (!map)
        প্রত্যাগম AVERROR(ENOMEM);
    প্রতি (পূর্ণাঙ্ক i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->order       = AV_CHANNEL_ORDER_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_channel_layout_from_mask(AVChannelLayout *channel_layout,
                                uint64_t mask)
{
    যদি (!mask)
        প্রত্যাগম AVERROR(EINVAL);

    channel_layout->order       = AV_CHANNEL_ORDER_NATIVE;
    channel_layout->nb_channels = av_popcount64(mask);
    channel_layout->u.mask      = mask;

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক parse_channel_list(AVChannelLayout *ch_layout, ধ্রুব বর্ণ *str)
{
    পূর্ণাঙ্ক ret;
    পূর্ণাঙ্ক nb_channels = 0;
    AVChannelCustom *map = রিক্ত;
    AVChannelCustom custom = {0};

    যাবত্ (*str) {
        বর্ণ *channel, *chname;
        ret = av_opt_get_চাবি_মান(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_চাবি, &channel, &chname);
        যদি (ret < 0) {
            av_freep(&map);
            প্রত্যাগম ret;
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
            প্রত্যাগম AVERROR(EINVAL);
        }

        av_dynarray2_add((শূন্য **)&map, &nb_channels, পরিমাণ(custom), (শূন্য *)&custom);
        যদি (!map)
            প্রত্যাগম AVERROR(ENOMEM);
    }

    যদি (!nb_channels)
        প্রত্যাগম AVERROR(EINVAL);

    ch_layout->order = AV_CHANNEL_ORDER_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  ধ্রুব বর্ণ *str)
{
    পূর্ণাঙ্ক i, matches, ret;
    পূর্ণাঙ্ক channels = 0, nb_channels = 0;
    বর্ণ *chlist, *end;
    uint64_t mask = 0;

    /* channel layout names */
    প্রতি (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        যদি (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            প্রত্যাগম 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, পরিমাণ(*channel_layout));

    /* ambisonic */
    যদি (!strncmp(str, "ambisonic ", 10)) {
        ধ্রুব বর্ণ *p = str + 10;
        বর্ণ *endptr;
        AVChannelLayout extra = {0};
        পূর্ণাঙ্ক order;

        order = strtol(p, &endptr, 0);
        যদি (order < 0 || order + 1  > INT_MAX / (order + 1) ||
            (*endptr && *endptr != '+'))
            প্রত্যাগম AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        যদি (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            যদি (ret < 0)
                প্রত্যাগম ret;
            যদি (extra.nb_channels >= INT_MAX - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                প্রত্যাগম AVERROR(EINVAL);
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
                    প্রত্যাগম AVERROR(ENOMEM);
                }

                প্রতি (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                প্রতি (i = 0; i < extra.nb_channels; i++) {
                    গণনা AVChannel ch = av_channel_layout_channel_from_index(&extra, i);
                    যদি (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        প্রত্যাগম AVERROR(EINVAL);
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

        প্রত্যাগম 0;
    }

    chlist = av_strdup(str);
    যদি (!chlist)
        প্রত্যাগম AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    যদি (ret < 0 && ret != AVERROR(EINVAL))
        প্রত্যাগম ret;

    যদি (ret >= 0) {
        ধ্রুব বর্ণ *end_par = strchr(str, ')');
        যদি (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            প্রত্যাগম AVERROR(EINVAL);
        }
        প্রত্যাগম 0;
    }

    errno = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    যদি (!errno && !*end && !strchr(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        প্রত্যাগম 0;
    }

    errno = 0;
    channels = strtol(str, &end, 10);

    /* number of channels */
    যদি (!errno && !strcmp(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        যদি (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            প্রত্যাগম 0;
    }

    /* number of unordered channels */
    যদি (!errno && (!strcmp(end, "C") || !strcmp(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        প্রত্যাগম 0;
    }

    প্রত্যাগম AVERROR(EINVAL);
}

শূন্য av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    যদি (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, পরিমাণ(*channel_layout));
}

পূর্ণাঙ্ক av_channel_layout_copy(AVChannelLayout *dst, ধ্রুব AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    যদি (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, পরিমাণ(*dst->u.map));
        যদি (!dst->u.map)
            প্রত্যাগম AVERROR(ENOMEM);
        memcpy(dst->u.map, src->u.map, src->nb_channels * পরিমাণ(*src->u.map));
    }
    প্রত্যাগম 0;
}

স্থির int64_t masked_description(ধ্রুব AVChannelLayout *channel_layout, পূর্ণাঙ্ক start_channel)
{
    uint64_t mask = 0;
    প্রতি (পূর্ণাঙ্ক i = start_channel; i < channel_layout->nb_channels; i++) {
        গণনা AVChannel ch = channel_layout->u.map[i].id;
        যদি (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        অন্যথা
            প্রত্যাগম AVERROR(EINVAL);
    }
    প্রত্যাগম mask;
}

স্থির পূর্ণাঙ্ক has_channel_names(ধ্রুব AVChannelLayout *channel_layout)
{
    যদি (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        প্রত্যাগম 0;
    প্রতি (পূর্ণাঙ্ক i = 0; i < channel_layout->nb_channels; i++)
        যদি (channel_layout->u.map[i].name[0])
            প্রত্যাগম 1;
    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_channel_layout_ambisonic_order(ধ্রুব AVChannelLayout *channel_layout)
{
    পূর্ণাঙ্ক i, highest_ambi, order;

    যদি (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        প্রত্যাগম AVERROR(EINVAL);

    highest_ambi = -1;
    যদি (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    অন্যথা {
        ধ্রুব AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        প্রতি (i = 0; i < channel_layout->nb_channels; i++) {
            পূর্ণাঙ্ক is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            যদি (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                প্রত্যাগম AVERROR(EINVAL);

            /* non-default ordering */
            যদি (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                প্রত্যাগম AVERROR(EINVAL);

            যদি (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    যদি (highest_ambi < 0)
        প্রত্যাগম AVERROR(EINVAL);

    order = floor(sqrt(highest_ambi));
    /* incomplete order - some harmonics are missing */
    যদি ((order + 1) * (order + 1) != highest_ambi + 1)
        প্রত্যাগম AVERROR(EINVAL);

    প্রত্যাগম order;
}

স্থির গণনা AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    পূর্ণাঙ্ক has_known_channel = 0;
    পূর্ণাঙ্ক order;

    যদি (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        প্রত্যাগম channel_layout->order;

    যদি (has_channel_names(channel_layout))
        প্রত্যাগম AV_CHANNEL_ORDER_CUSTOM;

    প্রতি (পূর্ণাঙ্ক i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        যদি (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    যদি (!has_known_channel)
        প্রত্যাগম AV_CHANNEL_ORDER_UNSPEC;

    যদি (masked_description(channel_layout, 0) > 0)
        প্রত্যাগম AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    যদি (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
        প্রত্যাগম AV_CHANNEL_ORDER_AMBISONIC;

    প্রত্যাগম AV_CHANNEL_ORDER_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
স্থির পূর্ণাঙ্ক try_describe_ambisonic(AVBPrint *bp, ধ্রুব AVChannelLayout *channel_layout)
{
    পূর্ণাঙ্ক nb_ambi_channels;
    পূর্ণাঙ্ক order = av_channel_layout_ambisonic_order(channel_layout);
    যদি (order < 0)
        প্রত্যাগম order;

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

    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_channel_layout_describe_bprint(ধ্রুব AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    পূর্ণাঙ্ক i;

    বিকল্প (channel_layout->order) {
    পক্ষ AV_CHANNEL_ORDER_NATIVE:
        প্রতি (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            যদি (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                প্রত্যাগম 0;
            }
        av_fallthrough;
    পক্ষ AV_CHANNEL_ORDER_CUSTOM:
        যদি (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            পূর্ণাঙ্ক res = try_describe_ambisonic(bp, channel_layout);
            যদি (res >= 0)
                প্রত্যাগম 0;
            যদি (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                প্রত্যাগম av_channel_layout_describe_bprint(&native, bp);
            }
        }
        যদি (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        প্রতি (i = 0; i < channel_layout->nb_channels; i++) {
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
            প্রত্যাগম 0;
        }
        av_fallthrough;
    পক্ষ AV_CHANNEL_ORDER_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        প্রত্যাগম 0;
    পক্ষ AV_CHANNEL_ORDER_AMBISONIC:
        প্রত্যাগম try_describe_ambisonic(bp, channel_layout);
    স্বভাব:
        প্রত্যাগম AVERROR(EINVAL);
    }
}

পূর্ণাঙ্ক av_channel_layout_describe(ধ্রুব AVChannelLayout *channel_layout,
                               বর্ণ *buf, size_t buf_size)
{
    AVBPrint bp;
    পূর্ণাঙ্ক ret;

    যদি (!buf && buf_size)
        প্রত্যাগম AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    যদি (ret < 0)
        প্রত্যাগম ret;

    যদি (bp.len >= INT_MAX)
        প্রত্যাগম AVERROR(ERANGE);
    প্রত্যাগম bp.len + 1;
}

গণনা AVChannel
av_channel_layout_channel_from_index(ধ্রুব AVChannelLayout *channel_layout,
                                     unsigned পূর্ণাঙ্ক idx)
{
    পূর্ণাঙ্ক i;

    যদি (idx >= channel_layout->nb_channels)
        প্রত্যাগম AV_CHAN_NONE;

    বিকল্প (channel_layout->order) {
    পক্ষ AV_CHANNEL_ORDER_CUSTOM:
        প্রত্যাগম channel_layout->u.map[idx].id;
    পক্ষ AV_CHANNEL_ORDER_AMBISONIC: {
        পূর্ণাঙ্ক ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        যদি (idx < ambi_channels)
            প্রত্যাগম AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    পক্ষ AV_CHANNEL_ORDER_NATIVE:
        প্রতি (i = 0; i < 64; i++) {
            যদি ((1ULL << i) & channel_layout->u.mask && !idx--)
                প্রত্যাগম i;
        }
        av_fallthrough;
    স্বভাব:
        প্রত্যাগম AV_CHAN_NONE;
    }
}

গণনা AVChannel
av_channel_layout_channel_from_string(ধ্রুব AVChannelLayout *channel_layout,
                                      ধ্রুব বর্ণ *str)
{
    পূর্ণাঙ্ক index = av_channel_layout_index_from_string(channel_layout, str);

    যদি (index < 0)
        প্রত্যাগম AV_CHAN_NONE;

    প্রত্যাগম av_channel_layout_channel_from_index(channel_layout, index);
}

পূর্ণাঙ্ক av_channel_layout_index_from_channel(ধ্রুব AVChannelLayout *channel_layout,
                                         গণনা AVChannel channel)
{
    পূর্ণাঙ্ক i;

    যদি (channel == AV_CHAN_NONE)
        প্রত্যাগম AVERROR(EINVAL);

    বিকল্প (channel_layout->order) {
    পক্ষ AV_CHANNEL_ORDER_CUSTOM:
        প্রতি (i = 0; i < channel_layout->nb_channels; i++)
            যদি (channel_layout->u.map[i].id == channel)
                প্রত্যাগম i;
        প্রত্যাগম AVERROR(EINVAL);
    পক্ষ AV_CHANNEL_ORDER_AMBISONIC:
    পক্ষ AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        পূর্ণাঙ্ক ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        যদি (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            যদি (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                প্রত্যাগম AVERROR(EINVAL);
            প্রত্যাগম channel - AV_CHAN_AMBISONIC_BASE;
        }
        যদি ((unsigned)channel > 63 || !(mask & (1ULL << channel)))
            প্রত্যাগম AVERROR(EINVAL);
        mask &= (1ULL << channel) - 1;
        প্রত্যাগম av_popcount64(mask) + ambi_channels;
        }
    স্বভাব:
        প্রত্যাগম AVERROR(EINVAL);
    }
}

পূর্ণাঙ্ক av_channel_layout_index_from_string(ধ্রুব AVChannelLayout *channel_layout,
                                        ধ্রুব বর্ণ *str)
{
    ধ্রুব বর্ণ *chname;
    গণনা AVChannel ch = AV_CHAN_NONE;

    বিকল্প (channel_layout->order) {
    পক্ষ AV_CHANNEL_ORDER_CUSTOM:
        chname = strstr(str, "@");
        যদি (chname) {
            বর্ণ buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(পরিমাণ(buf), chname - str));
            যদি (!*chname)
                chname = রিক্ত;
            ch = av_channel_from_string(buf);
            যদি (ch == AV_CHAN_NONE && *buf)
                প্রত্যাগম AVERROR(EINVAL);
        }
        প্রতি (পূর্ণাঙ্ক i = 0; chname && i < channel_layout->nb_channels; i++) {
            যদি (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                প্রত্যাগম i;
        }
        av_fallthrough;
    পক্ষ AV_CHANNEL_ORDER_AMBISONIC:
    পক্ষ AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        যদি (ch == AV_CHAN_NONE)
            প্রত্যাগম AVERROR(EINVAL);
        প্রত্যাগম av_channel_layout_index_from_channel(channel_layout, ch);
    }

    প্রত্যাগম AVERROR(EINVAL);
}

পূর্ণাঙ্ক av_channel_layout_check(ধ্রুব AVChannelLayout *channel_layout)
{
    যদি (channel_layout->nb_channels <= 0)
        প্রত্যাগম 0;

    বিকল্প (channel_layout->order) {
    পক্ষ AV_CHANNEL_ORDER_NATIVE:
        প্রত্যাগম av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    পক্ষ AV_CHANNEL_ORDER_CUSTOM:
        যদি (!channel_layout->u.map)
            প্রত্যাগম 0;
        প্রতি (পূর্ণাঙ্ক i = 0; i < channel_layout->nb_channels; i++) {
            যদি (channel_layout->u.map[i].id == AV_CHAN_NONE)
                প্রত্যাগম 0;
        }
        প্রত্যাগম 1;
    পক্ষ AV_CHANNEL_ORDER_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        প্রত্যাগম av_popcount64(channel_layout->u.mask) < channel_layout->nb_channels;
    পক্ষ AV_CHANNEL_ORDER_UNSPEC:
        প্রত্যাগম 1;
    স্বভাব:
        প্রত্যাগম 0;
    }
}

পূর্ণাঙ্ক av_channel_layout_compare(ধ্রুব AVChannelLayout *chl, ধ্রুব AVChannelLayout *chl1)
{
    পূর্ণাঙ্ক i;

    /* different channel counts -> not equal */
    যদি (chl->nb_channels != chl1->nb_channels)
        প্রত্যাগম 1;

    /* if only one is unspecified -> not equal */
    যদি ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        প্রত্যাগম 1;
    /* both are unspecified -> equal */
    অন্যথা যদি (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        প্রত্যাগম 0;

    /* can compare masks directly */
    যদি ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        প্রত্যাগম chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    প্রতি (i = 0; i < chl->nb_channels; i++)
        যদি (av_channel_layout_channel_from_index(chl,  i) !=
            av_channel_layout_channel_from_index(chl1, i))
            প্রত্যাগম 1;
    প্রত্যাগম 0;
}

শূন্য av_channel_layout_default(AVChannelLayout *ch_layout, পূর্ণাঙ্ক nb_channels)
{
    পূর্ণাঙ্ক i;
    প্রতি (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        যদি (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            প্রত্যাগম;
        }

    ch_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

ধ্রুব AVChannelLayout *av_channel_layout_standard(শূন্য **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ধ্রুব AVChannelLayout *ch_layout = রিক্ত;

    যদি (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (শূন্য*)(i + 1);
    }

    প্রত্যাগম ch_layout;
}

uint64_t av_channel_layout_subset(ধ্রুব AVChannelLayout *channel_layout,
                                  uint64_t mask)
{
    uint64_t ret = 0;
    পূর্ণাঙ্ক i;

    বিকল্প (channel_layout->order) {
    পক্ষ AV_CHANNEL_ORDER_NATIVE:
    পক্ষ AV_CHANNEL_ORDER_AMBISONIC:
        প্রত্যাগম channel_layout->u.mask & mask;
    পক্ষ AV_CHANNEL_ORDER_CUSTOM:
        প্রতি (i = 0; i < 64; i++)
            যদি (mask & (1ULL << i) && av_channel_layout_index_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        ভঙ্গ;
    }

    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_channel_layout_retype(AVChannelLayout *channel_layout, গণনা AVChannelOrder order, পূর্ণাঙ্ক flags)
{
    পূর্ণাঙ্ক allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    পূর্ণাঙ্ক lossy;

    যদি (!av_channel_layout_check(channel_layout))
        প্রত্যাগম AVERROR(EINVAL);

    যদি (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    যদি (channel_layout->order == order)
        প্রত্যাগম 0;

    বিকল্প (order) {
    পক্ষ AV_CHANNEL_ORDER_UNSPEC: {
        পূর্ণাঙ্ক nb_channels = channel_layout->nb_channels;
        যদি (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            প্রতি (পূর্ণাঙ্ক i = 0; i < nb_channels; i++) {
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
            প্রত্যাগম lossy;
        }
        প্রত্যাগম AVERROR(ENOSYS);
        }
    পক্ষ AV_CHANNEL_ORDER_NATIVE:
        যদি (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            যদি (mask < 0)
                প্রত্যাগম AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            যদি (!lossy || allow_lossy) {
                শূন্য *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_mask(channel_layout, mask);
                channel_layout->opaque = opaque;
                প্রত্যাগম lossy;
            }
        }
        প্রত্যাগম AVERROR(ENOSYS);
    পক্ষ AV_CHANNEL_ORDER_CUSTOM: {
        AVChannelLayout custom = { 0 };
        পূর্ণাঙ্ক ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        শূন্য *opaque = channel_layout->opaque;
        যদি (ret < 0)
            প্রত্যাগম ret;
        যদি (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            প্রতি (পূর্ণাঙ্ক i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_index(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        প্রত্যাগম 0;
        }
    পক্ষ AV_CHANNEL_ORDER_AMBISONIC:
        যদি (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            পূর্ণাঙ্ক nb_channels = channel_layout->nb_channels;
            পূর্ণাঙ্ক amb_order = av_channel_layout_ambisonic_order(channel_layout);
            যদি (amb_order < 0)
                প্রত্যাগম AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            যদি (mask < 0)
                প্রত্যাগম AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            যদি (!lossy || allow_lossy) {
                শূন্য *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.mask      = mask;
                channel_layout->opaque      = opaque;
                প্রত্যাগম lossy;
            }
        }
        প্রত্যাগম AVERROR(ENOSYS);
    স্বভাব:
        প্রত্যাগম AVERROR(EINVAL);
    }
}
