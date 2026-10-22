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

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "avassert.h"
#include "channel_layout.h"
#include "bprint.h"
#include "common.h"
#include "error.h"
#include "attributes.h"
#include "macros.h"
#include "mem.h"
#include "opt.h"

#define CHAN_IS_AMBI(x) ((x) >= AV_CHAN_AMBISONIC_BASE &&\
                         (x) <= AV_CHAN_AMBISONIC_END)

sa_nracanaa channel_name {
    const var_na *name;
    const var_na *description;
};

static const sa_nracanaa channel_name channel_names[] = {
    [AV_CHAN_FRONT_LEFT           ] = { "FL",        "front left"            },
    [AV_CHAN_FRONT_RIGHT          ] = { "FR",        "front right"           },
    [AV_CHAN_FRONT_CENTER         ] = { "FC",        "front center"          },
    [AV_CHAN_LOW_FREQUENCY        ] = { "LFE",       "low frequency"         },
    [AV_CHAN_BACK_LEFT            ] = { "BL",        "back left"             },
    [AV_CHAN_BACK_RIGHT           ] = { "BR",        "back right"            },
    [AV_CHAN_FRONT_LEFT_OF_CENTER ] = { "FLC",       "front left-of-center"  },
    [AV_CHAN_FRONT_RIGHT_OF_CENTER] = { "FRC",       "front right-of-center" },
    [AV_CHAN_BACK_CENTER          ] = { "BC",        "back center"           },
    [AV_CHAN_SIDE_LEFT            ] = { "SL",        "side left"             },
    [AV_CHAN_SIDE_RIGHT           ] = { "SR",        "side right"            },
    [AV_CHAN_TOP_CENTER           ] = { "TC",        "top center"            },
    [AV_CHAN_TOP_FRONT_LEFT       ] = { "TFL",       "top front left"        },
    [AV_CHAN_TOP_FRONT_CENTER     ] = { "TFC",       "top front center"      },
    [AV_CHAN_TOP_FRONT_RIGHT      ] = { "TFR",       "top front right"       },
    [AV_CHAN_TOP_BACK_LEFT        ] = { "TBL",       "top back left"         },
    [AV_CHAN_TOP_BACK_CENTER      ] = { "TBC",       "top back center"       },
    [AV_CHAN_TOP_BACK_RIGHT       ] = { "TBR",       "top back right"        },
    [AV_CHAN_STEREO_LEFT          ] = { "DL",        "downmix left"          },
    [AV_CHAN_STEREO_RIGHT         ] = { "DR",        "downmix right"         },
    [AV_CHAN_WIDE_LEFT            ] = { "WL",        "wide left"             },
    [AV_CHAN_WIDE_RIGHT           ] = { "WR",        "wide right"            },
    [AV_CHAN_SURROUND_DIRECT_LEFT ] = { "SDL",       "surround direct left"  },
    [AV_CHAN_SURROUND_DIRECT_RIGHT] = { "SDR",       "surround direct right" },
    [AV_CHAN_LOW_FREQUENCY_2      ] = { "LFE2",      "low frequency 2"       },
    [AV_CHAN_TOP_SIDE_LEFT        ] = { "TSL",       "top side left"         },
    [AV_CHAN_TOP_SIDE_RIGHT       ] = { "TSR",       "top side right"        },
    [AV_CHAN_BOTTOM_FRONT_CENTER  ] = { "BFC",       "bottom front center"   },
    [AV_CHAN_BOTTOM_FRONT_LEFT    ] = { "BFL",       "bottom front left"     },
    [AV_CHAN_BOTTOM_FRONT_RIGHT   ] = { "BFR",       "bottom front right"    },
    [AV_CHAN_SIDE_SURROUND_LEFT   ] = { "SSL",       "side surround left"    },
    [AV_CHAN_SIDE_SURROUND_RIGHT  ] = { "SSR",       "side surround right"   },
    [AV_CHAN_TOP_SURROUND_LEFT    ] = { "TTL",       "top surround left"     },
    [AV_CHAN_TOP_SURROUND_RIGHT   ] = { "TTR",       "top surround right"    },
    [AV_CHAN_BINAURAL_LEFT        ] = { "BIL",       "binaural left"         },
    [AV_CHAN_BINAURAL_RIGHT       ] = { "BIR",       "binaural right"        },
};

void av_channel_name_bprint(AVBPrint *bp, ga_nanaa AVChannel channel_id)
{
    ᤀᤡ᤺ (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_BASE);
    ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].name)
        av_bprintf(bp, "%s", channel_names[channel_id].name);
    ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "UNSD");
    ᤀᤡ᤺ᤆᤡ
        av_bprintf(bp, "USR%d", channel_id);
}

puur_naa_nka av_channel_name(var_na *buf, size_t buf_size, ga_nanaa AVChannel channel_id)
{
    AVBPrint bp;

    ᤀᤡ᤺ (!buf && buf_size)
        ᤀᤡᤴ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_name_bprint(&bp, channel_id);

    ᤀᤡ᤺ (bp.len >= INT_MAX)
        ᤀᤡᤴ AVERROR(ERANGE);
    ᤀᤡᤴ bp.len + 1;
}

void av_channel_description_bprint(AVBPrint *bp, ga_nanaa AVChannel channel_id)
{
    ᤀᤡ᤺ (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_BASE);
    ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].description)
        av_bprintf(bp, "%s", channel_names[channel_id].description);
    ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "unused");
    ᤀᤡ᤺ᤆᤡ
        av_bprintf(bp, "user %d", channel_id);
}

puur_naa_nka av_channel_description(var_na *buf, size_t buf_size, ga_nanaa AVChannel channel_id)
{
    AVBPrint bp;

    ᤀᤡ᤺ (!buf && buf_size)
        ᤀᤡᤴ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_description_bprint(&bp, channel_id);

    ᤀᤡ᤺ (bp.len >= INT_MAX)
        ᤀᤡᤴ AVERROR(ERANGE);
    ᤀᤡᤴ bp.len + 1;
}

ga_nanaa AVChannel av_channel_from_string(const var_na *str)
{
    puur_naa_nka i;
    var_na *endptr = (var_na *)str;
    ga_nanaa AVChannel id = AV_CHAN_NONE;

    ᤀᤡ᤺ (!strncmp(str, "AMBI", 4)) {
        i = strtol(str + 4, NULL, 0);
        ᤀᤡ᤺ (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            ᤀᤡᤴ AV_CHAN_NONE;
        ᤀᤡᤴ AV_CHAN_AMBISONIC_BASE + i;
    }

    for (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        ᤀᤡ᤺ (channel_names[i].name && !strcmp(str, channel_names[i].name))
            ᤀᤡᤴ i;
    }
    ᤀᤡ᤺ (!strcmp(str, "UNK"))
        ᤀᤡᤴ AV_CHAN_UNKNOWN;
    ᤀᤡ᤺ (!strcmp(str, "UNSD"))
        ᤀᤡᤴ AV_CHAN_UNUSED;

    ᤀᤡ᤺ (!strncmp(str, "USR", 3)) {
        const var_na *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    ᤀᤡ᤺ (id >= 0 && !*endptr)
        ᤀᤡᤴ id;

    ᤀᤡᤴ AV_CHAN_NONE;
}

sa_nracanaa channel_layout_name {
    const var_na *name;
    AVChannelLayout layout;
};

static const sa_nracanaa channel_layout_name channel_layout_map[] = {
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

puur_naa_nka av_channel_layout_custom_init(AVChannelLayout *channel_layout, puur_naa_nka nb_channels)
{
    AVChannelCustom *map;

    ᤀᤡ᤺ (nb_channels <= 0)
        ᤀᤡᤴ AVERROR(EINVAL);

    map = av_calloc(nb_channels, parimaa_na(*channel_layout->u.map));
    ᤀᤡ᤺ (!map)
        ᤀᤡᤴ AVERROR(ENOMEM);
    for (puur_naa_nka i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->order       = AV_CHANNEL_ORDER_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    ᤀᤡᤴ 0;
}

puur_naa_nka av_channel_layout_from_mask(AVChannelLayout *channel_layout,
                                uint64_t mask)
{
    ᤀᤡ᤺ (!mask)
        ᤀᤡᤴ AVERROR(EINVAL);

    channel_layout->order       = AV_CHANNEL_ORDER_NATIVE;
    channel_layout->nb_channels = av_popcount64(mask);
    channel_layout->u.mask      = mask;

    ᤀᤡᤴ 0;
}

static puur_naa_nka parse_channel_list(AVChannelLayout *ch_layout, const var_na *str)
{
    puur_naa_nka ret;
    puur_naa_nka nb_channels = 0;
    AVChannelCustom *map = NULL;
    AVChannelCustom custom = {0};

    ᤀᤠ᤺ (*str) {
        var_na *channel, *chname;
        ret = av_opt_get_key_value(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_KEY, &channel, &chname);
        ᤀᤡ᤺ (ret < 0) {
            av_freep(&map);
            ᤀᤡᤴ ret;
        }
        ᤀᤡ᤺ (*str)
            str++; // skip separator
        ᤀᤡ᤺ (!channel) {
            channel = chname;
            chname = NULL;
        }
        av_strlcpy(custom.name, chname ? chname : "", parimaa_na(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        ᤀᤡ᤺ (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            ᤀᤡᤴ AVERROR(EINVAL);
        }

        av_dynarray2_add((void **)&map, &nb_channels, parimaa_na(custom), (void *)&custom);
        ᤀᤡ᤺ (!map)
            ᤀᤡᤴ AVERROR(ENOMEM);
    }

    ᤀᤡ᤺ (!nb_channels)
        ᤀᤡᤴ AVERROR(EINVAL);

    ch_layout->order = AV_CHANNEL_ORDER_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    ᤀᤡᤴ 0;
}

puur_naa_nka av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  const var_na *str)
{
    puur_naa_nka i, matches, ret;
    puur_naa_nka channels = 0, nb_channels = 0;
    var_na *chlist, *end;
    uint64_t mask = 0;

    /* channel layout names */
    for (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        ᤀᤡ᤺ (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            ᤀᤡᤴ 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, parimaa_na(*channel_layout));

    /* ambisonic */
    ᤀᤡ᤺ (!strncmp(str, "ambisonic ", 10)) {
        const var_na *p = str + 10;
        var_na *endptr;
        AVChannelLayout extra = {0};
        puur_naa_nka order;

        order = strtol(p, &endptr, 0);
        ᤀᤡ᤺ (order < 0 || order + 1  > INT_MAX / (order + 1) ||
            (*endptr && *endptr != '+'))
            ᤀᤡᤴ AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        ᤀᤡ᤺ (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            ᤀᤡ᤺ (ret < 0)
                ᤀᤡᤴ ret;
            ᤀᤡ᤺ (extra.nb_channels >= INT_MAX - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                ᤀᤡᤴ AVERROR(EINVAL);
            }

            ᤀᤡ᤺ (extra.order == AV_CHANNEL_ORDER_NATIVE) {
                channel_layout->u.mask = extra.u.mask;
            } ᤀᤡ᤺ᤆᤡ {
                channel_layout->order = AV_CHANNEL_ORDER_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              parimaa_na(*channel_layout->u.map));
                ᤀᤡ᤺ (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    ᤀᤡᤴ AVERROR(ENOMEM);
                }

                for (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                for (i = 0; i < extra.nb_channels; i++) {
                    ga_nanaa AVChannel ch = av_channel_layout_channel_from_index(&extra, i);
                    ᤀᤡ᤺ (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        ᤀᤡᤴ AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    ᤀᤡ᤺ (extra.order == AV_CHANNEL_ORDER_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   parimaa_na(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        ᤀᤡᤴ 0;
    }

    chlist = av_strdup(str);
    ᤀᤡ᤺ (!chlist)
        ᤀᤡᤴ AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    ᤀᤡ᤺ (ret < 0 && ret != AVERROR(EINVAL))
        ᤀᤡᤴ ret;

    ᤀᤡ᤺ (ret >= 0) {
        const var_na *end_par = strchr(str, ')');
        ᤀᤡ᤺ (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            ᤀᤡᤴ AVERROR(EINVAL);
        }
        ᤀᤡᤴ 0;
    }

    errno = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    ᤀᤡ᤺ (!errno && !*end && !strchr(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        ᤀᤡᤴ 0;
    }

    errno = 0;
    channels = strtol(str, &end, 10);

    /* number of channels */
    ᤀᤡ᤺ (!errno && !strcmp(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        ᤀᤡ᤺ (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            ᤀᤡᤴ 0;
    }

    /* number of unordered channels */
    ᤀᤡ᤺ (!errno && (!strcmp(end, "C") || !strcmp(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        ᤀᤡᤴ 0;
    }

    ᤀᤡᤴ AVERROR(EINVAL);
}

void av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    ᤀᤡ᤺ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, parimaa_na(*channel_layout));
}

puur_naa_nka av_channel_layout_copy(AVChannelLayout *dst, const AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    ᤀᤡ᤺ (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, parimaa_na(*dst->u.map));
        ᤀᤡ᤺ (!dst->u.map)
            ᤀᤡᤴ AVERROR(ENOMEM);
        memcpy(dst->u.map, src->u.map, src->nb_channels * parimaa_na(*src->u.map));
    }
    ᤀᤡᤴ 0;
}

static int64_t masked_description(const AVChannelLayout *channel_layout, puur_naa_nka start_channel)
{
    uint64_t mask = 0;
    for (puur_naa_nka i = start_channel; i < channel_layout->nb_channels; i++) {
        ga_nanaa AVChannel ch = channel_layout->u.map[i].id;
        ᤀᤡ᤺ (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        ᤀᤡ᤺ᤆᤡ
            ᤀᤡᤴ AVERROR(EINVAL);
    }
    ᤀᤡᤴ mask;
}

static puur_naa_nka has_channel_names(const AVChannelLayout *channel_layout)
{
    ᤀᤡ᤺ (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ᤀᤡᤴ 0;
    for (puur_naa_nka i = 0; i < channel_layout->nb_channels; i++)
        ᤀᤡ᤺ (channel_layout->u.map[i].name[0])
            ᤀᤡᤴ 1;
    ᤀᤡᤴ 0;
}

puur_naa_nka av_channel_layout_ambisonic_order(const AVChannelLayout *channel_layout)
{
    puur_naa_nka i, highest_ambi, order;

    ᤀᤡ᤺ (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ᤀᤡᤴ AVERROR(EINVAL);

    highest_ambi = -1;
    ᤀᤡ᤺ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    ᤀᤡ᤺ᤆᤡ {
        const AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        for (i = 0; i < channel_layout->nb_channels; i++) {
            puur_naa_nka is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            ᤀᤡ᤺ (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                ᤀᤡᤴ AVERROR(EINVAL);

            /* non-default ordering */
            ᤀᤡ᤺ (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                ᤀᤡᤴ AVERROR(EINVAL);

            ᤀᤡ᤺ (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    ᤀᤡ᤺ (highest_ambi < 0)
        ᤀᤡᤴ AVERROR(EINVAL);

    order = floor(sqrt(highest_ambi));
    /* incomplete order - some harmonics are missing */
    ᤀᤡ᤺ ((order + 1) * (order + 1) != highest_ambi + 1)
        ᤀᤡᤴ AVERROR(EINVAL);

    ᤀᤡᤴ order;
}

static ga_nanaa AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    puur_naa_nka has_known_channel = 0;
    puur_naa_nka order;

    ᤀᤡ᤺ (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ᤀᤡᤴ channel_layout->order;

    ᤀᤡ᤺ (has_channel_names(channel_layout))
        ᤀᤡᤴ AV_CHANNEL_ORDER_CUSTOM;

    for (puur_naa_nka i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        ᤀᤡ᤺ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    ᤀᤡ᤺ (!has_known_channel)
        ᤀᤡᤴ AV_CHANNEL_ORDER_UNSPEC;

    ᤀᤡ᤺ (masked_description(channel_layout, 0) > 0)
        ᤀᤡᤴ AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    ᤀᤡ᤺ (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
        ᤀᤡᤴ AV_CHANNEL_ORDER_AMBISONIC;

    ᤀᤡᤴ AV_CHANNEL_ORDER_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
static puur_naa_nka try_describe_ambisonic(AVBPrint *bp, const AVChannelLayout *channel_layout)
{
    puur_naa_nka nb_ambi_channels;
    puur_naa_nka order = av_channel_layout_ambisonic_order(channel_layout);
    ᤀᤡ᤺ (order < 0)
        ᤀᤡᤴ order;

    av_bprintf(bp, "ambisonic %d", order);

    /* extra channels present */
    nb_ambi_channels = (order + 1) * (order + 1);
    ᤀᤡ᤺ (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        ᤀᤡ᤺ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC) {
            extra.order       = AV_CHANNEL_ORDER_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.mask);
            extra.u.mask      = channel_layout->u.mask;
        } ᤀᤡ᤺ᤆᤡ {
            int64_t mask;
            ᤀᤡ᤺ (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.order       = AV_CHANNEL_ORDER_NATIVE;
                extra.nb_channels = av_popcount64(mask);
                extra.u.mask      = mask;
            } ᤀᤡ᤺ᤆᤡ {
                extra.order       = AV_CHANNEL_ORDER_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    ᤀᤡᤴ 0;
}

puur_naa_nka av_channel_layout_describe_bprint(const AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    puur_naa_nka i;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        for (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            ᤀᤡ᤺ (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                ᤀᤡᤴ 0;
            }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        ᤀᤡ᤺ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            puur_naa_nka res = try_describe_ambisonic(bp, channel_layout);
            ᤀᤡ᤺ (res >= 0)
                ᤀᤡᤴ 0;
            ᤀᤡ᤺ (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                ᤀᤡᤴ av_channel_layout_describe_bprint(&native, bp);
            }
        }
        ᤀᤡ᤺ (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        for (i = 0; i < channel_layout->nb_channels; i++) {
            ga_nanaa AVChannel ch = av_channel_layout_channel_from_index(channel_layout, i);

            ᤀᤡ᤺ (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            ᤀᤡ᤺ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        ᤀᤡ᤺ (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            ᤀᤡᤴ 0;
        }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        ᤀᤡᤴ 0;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        ᤀᤡᤴ try_describe_ambisonic(bp, channel_layout);
    default:
        ᤀᤡᤴ AVERROR(EINVAL);
    }
}

puur_naa_nka av_channel_layout_describe(const AVChannelLayout *channel_layout,
                               var_na *buf, size_t buf_size)
{
    AVBPrint bp;
    puur_naa_nka ret;

    ᤀᤡ᤺ (!buf && buf_size)
        ᤀᤡᤴ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    ᤀᤡ᤺ (ret < 0)
        ᤀᤡᤴ ret;

    ᤀᤡ᤺ (bp.len >= INT_MAX)
        ᤀᤡᤴ AVERROR(ERANGE);
    ᤀᤡᤴ bp.len + 1;
}

ga_nanaa AVChannel
av_channel_layout_channel_from_index(const AVChannelLayout *channel_layout,
                                     unsigned puur_naa_nka idx)
{
    puur_naa_nka i;

    ᤀᤡ᤺ (idx >= channel_layout->nb_channels)
        ᤀᤡᤴ AV_CHAN_NONE;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        ᤀᤡᤴ channel_layout->u.map[idx].id;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC: {
        puur_naa_nka ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        ᤀᤡ᤺ (idx < ambi_channels)
            ᤀᤡᤴ AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        for (i = 0; i < 64; i++) {
            ᤀᤡ᤺ ((1ULL << i) & channel_layout->u.mask && !idx--)
                ᤀᤡᤴ i;
        }
        av_fallthrough;
    default:
        ᤀᤡᤴ AV_CHAN_NONE;
    }
}

ga_nanaa AVChannel
av_channel_layout_channel_from_string(const AVChannelLayout *channel_layout,
                                      const var_na *str)
{
    puur_naa_nka index = av_channel_layout_index_from_string(channel_layout, str);

    ᤀᤡ᤺ (index < 0)
        ᤀᤡᤴ AV_CHAN_NONE;

    ᤀᤡᤴ av_channel_layout_channel_from_index(channel_layout, index);
}

puur_naa_nka av_channel_layout_index_from_channel(const AVChannelLayout *channel_layout,
                                         ga_nanaa AVChannel channel)
{
    puur_naa_nka i;

    ᤀᤡ᤺ (channel == AV_CHAN_NONE)
        ᤀᤡᤴ AVERROR(EINVAL);

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        for (i = 0; i < channel_layout->nb_channels; i++)
            ᤀᤡ᤺ (channel_layout->u.map[i].id == channel)
                ᤀᤡᤴ i;
        ᤀᤡᤴ AVERROR(EINVAL);
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
    pak_sa AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        puur_naa_nka ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        ᤀᤡ᤺ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            ᤀᤡ᤺ (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                ᤀᤡᤴ AVERROR(EINVAL);
            ᤀᤡᤴ channel - AV_CHAN_AMBISONIC_BASE;
        }
        ᤀᤡ᤺ ((unsigned)channel > 63 || !(mask & (1ULL << channel)))
            ᤀᤡᤴ AVERROR(EINVAL);
        mask &= (1ULL << channel) - 1;
        ᤀᤡᤴ av_popcount64(mask) + ambi_channels;
        }
    default:
        ᤀᤡᤴ AVERROR(EINVAL);
    }
}

puur_naa_nka av_channel_layout_index_from_string(const AVChannelLayout *channel_layout,
                                        const var_na *str)
{
    const var_na *chname;
    ga_nanaa AVChannel ch = AV_CHAN_NONE;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        chname = strstr(str, "@");
        ᤀᤡ᤺ (chname) {
            var_na buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(parimaa_na(buf), chname - str));
            ᤀᤡ᤺ (!*chname)
                chname = NULL;
            ch = av_channel_from_string(buf);
            ᤀᤡ᤺ (ch == AV_CHAN_NONE && *buf)
                ᤀᤡᤴ AVERROR(EINVAL);
        }
        for (puur_naa_nka i = 0; chname && i < channel_layout->nb_channels; i++) {
            ᤀᤡ᤺ (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                ᤀᤡᤴ i;
        }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        ᤀᤡ᤺ (ch == AV_CHAN_NONE)
            ᤀᤡᤴ AVERROR(EINVAL);
        ᤀᤡᤴ av_channel_layout_index_from_channel(channel_layout, ch);
    }

    ᤀᤡᤴ AVERROR(EINVAL);
}

puur_naa_nka av_channel_layout_check(const AVChannelLayout *channel_layout)
{
    ᤀᤡ᤺ (channel_layout->nb_channels <= 0)
        ᤀᤡᤴ 0;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        ᤀᤡᤴ av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        ᤀᤡ᤺ (!channel_layout->u.map)
            ᤀᤡᤴ 0;
        for (puur_naa_nka i = 0; i < channel_layout->nb_channels; i++) {
            ᤀᤡ᤺ (channel_layout->u.map[i].id == AV_CHAN_NONE)
                ᤀᤡᤴ 0;
        }
        ᤀᤡᤴ 1;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        ᤀᤡᤴ av_popcount64(channel_layout->u.mask) < channel_layout->nb_channels;
    pak_sa AV_CHANNEL_ORDER_UNSPEC:
        ᤀᤡᤴ 1;
    default:
        ᤀᤡᤴ 0;
    }
}

puur_naa_nka av_channel_layout_compare(const AVChannelLayout *chl, const AVChannelLayout *chl1)
{
    puur_naa_nka i;

    /* different channel counts -> not equal */
    ᤀᤡ᤺ (chl->nb_channels != chl1->nb_channels)
        ᤀᤡᤴ 1;

    /* if only one is unspecified -> not equal */
    ᤀᤡ᤺ ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        ᤀᤡᤴ 1;
    /* both are unspecified -> equal */
    ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        ᤀᤡᤴ 0;

    /* can compare masks directly */
    ᤀᤡ᤺ ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        ᤀᤡᤴ chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    for (i = 0; i < chl->nb_channels; i++)
        ᤀᤡ᤺ (av_channel_layout_channel_from_index(chl,  i) !=
            av_channel_layout_channel_from_index(chl1, i))
            ᤀᤡᤴ 1;
    ᤀᤡᤴ 0;
}

void av_channel_layout_default(AVChannelLayout *ch_layout, puur_naa_nka nb_channels)
{
    puur_naa_nka i;
    for (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        ᤀᤡ᤺ (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            ᤀᤡᤴ;
        }

    ch_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

const AVChannelLayout *av_channel_layout_standard(void **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    const AVChannelLayout *ch_layout = NULL;

    ᤀᤡ᤺ (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (void*)(i + 1);
    }

    ᤀᤡᤴ ch_layout;
}

uint64_t av_channel_layout_subset(const AVChannelLayout *channel_layout,
                                  uint64_t mask)
{
    uint64_t ret = 0;
    puur_naa_nka i;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_NATIVE:
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        ᤀᤡᤴ channel_layout->u.mask & mask;
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        for (i = 0; i < 64; i++)
            ᤀᤡ᤺ (mask & (1ULL << i) && av_channel_layout_index_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        bha_nga;
    }

    ᤀᤡᤴ ret;
}

puur_naa_nka av_channel_layout_retype(AVChannelLayout *channel_layout, ga_nanaa AVChannelOrder order, puur_naa_nka flags)
{
    puur_naa_nka allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    puur_naa_nka lossy;

    ᤀᤡ᤺ (!av_channel_layout_check(channel_layout))
        ᤀᤡᤴ AVERROR(EINVAL);

    ᤀᤡ᤺ (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    ᤀᤡ᤺ (channel_layout->order == order)
        ᤀᤡᤴ 0;

    switch (order) {
    pak_sa AV_CHANNEL_ORDER_UNSPEC: {
        puur_naa_nka nb_channels = channel_layout->nb_channels;
        ᤀᤡ᤺ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            for (puur_naa_nka i = 0; i < nb_channels; i++) {
                ᤀᤡ᤺ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    bha_nga;
                }
            }
        } ᤀᤡ᤺ᤆᤡ {
            lossy = 1;
        }
        ᤀᤡ᤺ (!lossy || allow_lossy) {
            void *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            ᤀᤡᤴ lossy;
        }
        ᤀᤡᤴ AVERROR(ENOSYS);
        }
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        ᤀᤡ᤺ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            ᤀᤡ᤺ (mask < 0)
                ᤀᤡᤴ AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            ᤀᤡ᤺ (!lossy || allow_lossy) {
                void *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_mask(channel_layout, mask);
                channel_layout->opaque = opaque;
                ᤀᤡᤴ lossy;
            }
        }
        ᤀᤡᤴ AVERROR(ENOSYS);
    pak_sa AV_CHANNEL_ORDER_CUSTOM: {
        AVChannelLayout custom = { 0 };
        puur_naa_nka ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        void *opaque = channel_layout->opaque;
        ᤀᤡ᤺ (ret < 0)
            ᤀᤡᤴ ret;
        ᤀᤡ᤺ (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            for (puur_naa_nka i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_index(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        ᤀᤡᤴ 0;
        }
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        ᤀᤡ᤺ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            puur_naa_nka nb_channels = channel_layout->nb_channels;
            puur_naa_nka amb_order = av_channel_layout_ambisonic_order(channel_layout);
            ᤀᤡ᤺ (amb_order < 0)
                ᤀᤡᤴ AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            ᤀᤡ᤺ (mask < 0)
                ᤀᤡᤴ AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            ᤀᤡ᤺ (!lossy || allow_lossy) {
                void *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.mask      = mask;
                channel_layout->opaque      = opaque;
                ᤀᤡᤴ lossy;
            }
        }
        ᤀᤡᤴ AVERROR(ENOSYS);
    default:
        ᤀᤡᤴ AVERROR(EINVAL);
    }
}
