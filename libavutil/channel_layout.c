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
    ᱡᱩᱫᱤ (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_BASE);
    ᱵᱟᱝ ᱡᱩᱫᱤ ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].name)
        av_bprintf(bp, "%s", channel_names[channel_id].name);
    ᱵᱟᱝ ᱡᱩᱫᱤ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    ᱵᱟᱝ ᱡᱩᱫᱤ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    ᱵᱟᱝ ᱡᱩᱫᱤ (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "UNSD");
    ᱵᱟᱝ
        av_bprintf(bp, "USR%d", channel_id);
}

puur_naa_nka av_channel_name(var_na *buf, size_t buf_size, ga_nanaa AVChannel channel_id)
{
    AVBPrint bp;

    ᱡᱩᱫᱤ (!buf && buf_size)
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_name_bprint(&bp, channel_id);

    ᱡᱩᱫᱤ (bp.len >= INT_MAX)
        ᱨᱩᱣᱟᱹᱲ AVERROR(ERANGE);
    ᱨᱩᱣᱟᱹᱲ bp.len + 1;
}

void av_channel_description_bprint(AVBPrint *bp, ga_nanaa AVChannel channel_id)
{
    ᱡᱩᱫᱤ (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_BASE);
    ᱵᱟᱝ ᱡᱩᱫᱤ ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].description)
        av_bprintf(bp, "%s", channel_names[channel_id].description);
    ᱵᱟᱝ ᱡᱩᱫᱤ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    ᱵᱟᱝ ᱡᱩᱫᱤ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    ᱵᱟᱝ ᱡᱩᱫᱤ (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "unused");
    ᱵᱟᱝ
        av_bprintf(bp, "user %d", channel_id);
}

puur_naa_nka av_channel_description(var_na *buf, size_t buf_size, ga_nanaa AVChannel channel_id)
{
    AVBPrint bp;

    ᱡᱩᱫᱤ (!buf && buf_size)
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_description_bprint(&bp, channel_id);

    ᱡᱩᱫᱤ (bp.len >= INT_MAX)
        ᱨᱩᱣᱟᱹᱲ AVERROR(ERANGE);
    ᱨᱩᱣᱟᱹᱲ bp.len + 1;
}

ga_nanaa AVChannel av_channel_from_string(const var_na *str)
{
    puur_naa_nka i;
    var_na *endptr = (var_na *)str;
    ga_nanaa AVChannel id = AV_CHAN_NONE;

    ᱡᱩᱫᱤ (!strncmp(str, "AMBI", 4)) {
        i = strtol(str + 4, NULL, 0);
        ᱡᱩᱫᱤ (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            ᱨᱩᱣᱟᱹᱲ AV_CHAN_NONE;
        ᱨᱩᱣᱟᱹᱲ AV_CHAN_AMBISONIC_BASE + i;
    }

    for (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        ᱡᱩᱫᱤ (channel_names[i].name && !strcmp(str, channel_names[i].name))
            ᱨᱩᱣᱟᱹᱲ i;
    }
    ᱡᱩᱫᱤ (!strcmp(str, "UNK"))
        ᱨᱩᱣᱟᱹᱲ AV_CHAN_UNKNOWN;
    ᱡᱩᱫᱤ (!strcmp(str, "UNSD"))
        ᱨᱩᱣᱟᱹᱲ AV_CHAN_UNUSED;

    ᱡᱩᱫᱤ (!strncmp(str, "USR", 3)) {
        const var_na *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    ᱡᱩᱫᱤ (id >= 0 && !*endptr)
        ᱨᱩᱣᱟᱹᱲ id;

    ᱨᱩᱣᱟᱹᱲ AV_CHAN_NONE;
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

    ᱡᱩᱫᱤ (nb_channels <= 0)
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);

    map = av_calloc(nb_channels, parimaa_na(*channel_layout->u.map));
    ᱡᱩᱫᱤ (!map)
        ᱨᱩᱣᱟᱹᱲ AVERROR(ENOMEM);
    for (puur_naa_nka i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->order       = AV_CHANNEL_ORDER_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    ᱨᱩᱣᱟᱹᱲ 0;
}

puur_naa_nka av_channel_layout_from_mask(AVChannelLayout *channel_layout,
                                uint64_t mask)
{
    ᱡᱩᱫᱤ (!mask)
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);

    channel_layout->order       = AV_CHANNEL_ORDER_NATIVE;
    channel_layout->nb_channels = av_popcount64(mask);
    channel_layout->u.mask      = mask;

    ᱨᱩᱣᱟᱹᱲ 0;
}

static puur_naa_nka parse_channel_list(AVChannelLayout *ch_layout, const var_na *str)
{
    puur_naa_nka ret;
    puur_naa_nka nb_channels = 0;
    AVChannelCustom *map = NULL;
    AVChannelCustom custom = {0};

    ᱡᱚᱠᱷᱚᱱ (*str) {
        var_na *channel, *chname;
        ret = av_opt_get_key_value(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_KEY, &channel, &chname);
        ᱡᱩᱫᱤ (ret < 0) {
            av_freep(&map);
            ᱨᱩᱣᱟᱹᱲ ret;
        }
        ᱡᱩᱫᱤ (*str)
            str++; // skip separator
        ᱡᱩᱫᱤ (!channel) {
            channel = chname;
            chname = NULL;
        }
        av_strlcpy(custom.name, chname ? chname : "", parimaa_na(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        ᱡᱩᱫᱤ (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
        }

        av_dynarray2_add((void **)&map, &nb_channels, parimaa_na(custom), (void *)&custom);
        ᱡᱩᱫᱤ (!map)
            ᱨᱩᱣᱟᱹᱲ AVERROR(ENOMEM);
    }

    ᱡᱩᱫᱤ (!nb_channels)
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);

    ch_layout->order = AV_CHANNEL_ORDER_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    ᱨᱩᱣᱟᱹᱲ 0;
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
        ᱡᱩᱫᱤ (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            ᱨᱩᱣᱟᱹᱲ 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, parimaa_na(*channel_layout));

    /* ambisonic */
    ᱡᱩᱫᱤ (!strncmp(str, "ambisonic ", 10)) {
        const var_na *p = str + 10;
        var_na *endptr;
        AVChannelLayout extra = {0};
        puur_naa_nka order;

        order = strtol(p, &endptr, 0);
        ᱡᱩᱫᱤ (order < 0 || order + 1  > INT_MAX / (order + 1) ||
            (*endptr && *endptr != '+'))
            ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        ᱡᱩᱫᱤ (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            ᱡᱩᱫᱤ (ret < 0)
                ᱨᱩᱣᱟᱹᱲ ret;
            ᱡᱩᱫᱤ (extra.nb_channels >= INT_MAX - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
            }

            ᱡᱩᱫᱤ (extra.order == AV_CHANNEL_ORDER_NATIVE) {
                channel_layout->u.mask = extra.u.mask;
            } ᱵᱟᱝ {
                channel_layout->order = AV_CHANNEL_ORDER_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              parimaa_na(*channel_layout->u.map));
                ᱡᱩᱫᱤ (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    ᱨᱩᱣᱟᱹᱲ AVERROR(ENOMEM);
                }

                for (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                for (i = 0; i < extra.nb_channels; i++) {
                    ga_nanaa AVChannel ch = av_channel_layout_channel_from_index(&extra, i);
                    ᱡᱩᱫᱤ (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    ᱡᱩᱫᱤ (extra.order == AV_CHANNEL_ORDER_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   parimaa_na(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        ᱨᱩᱣᱟᱹᱲ 0;
    }

    chlist = av_strdup(str);
    ᱡᱩᱫᱤ (!chlist)
        ᱨᱩᱣᱟᱹᱲ AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    ᱡᱩᱫᱤ (ret < 0 && ret != AVERROR(EINVAL))
        ᱨᱩᱣᱟᱹᱲ ret;

    ᱡᱩᱫᱤ (ret >= 0) {
        const var_na *end_par = strchr(str, ')');
        ᱡᱩᱫᱤ (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
        }
        ᱨᱩᱣᱟᱹᱲ 0;
    }

    errno = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    ᱡᱩᱫᱤ (!errno && !*end && !strchr(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        ᱨᱩᱣᱟᱹᱲ 0;
    }

    errno = 0;
    channels = strtol(str, &end, 10);

    /* number of channels */
    ᱡᱩᱫᱤ (!errno && !strcmp(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        ᱡᱩᱫᱤ (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            ᱨᱩᱣᱟᱹᱲ 0;
    }

    /* number of unordered channels */
    ᱡᱩᱫᱤ (!errno && (!strcmp(end, "C") || !strcmp(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        ᱨᱩᱣᱟᱹᱲ 0;
    }

    ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
}

void av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    ᱡᱩᱫᱤ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, parimaa_na(*channel_layout));
}

puur_naa_nka av_channel_layout_copy(AVChannelLayout *dst, const AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    ᱡᱩᱫᱤ (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, parimaa_na(*dst->u.map));
        ᱡᱩᱫᱤ (!dst->u.map)
            ᱨᱩᱣᱟᱹᱲ AVERROR(ENOMEM);
        memcpy(dst->u.map, src->u.map, src->nb_channels * parimaa_na(*src->u.map));
    }
    ᱨᱩᱣᱟᱹᱲ 0;
}

static int64_t masked_description(const AVChannelLayout *channel_layout, puur_naa_nka start_channel)
{
    uint64_t mask = 0;
    for (puur_naa_nka i = start_channel; i < channel_layout->nb_channels; i++) {
        ga_nanaa AVChannel ch = channel_layout->u.map[i].id;
        ᱡᱩᱫᱤ (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        ᱵᱟᱝ
            ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
    }
    ᱨᱩᱣᱟᱹᱲ mask;
}

static puur_naa_nka has_channel_names(const AVChannelLayout *channel_layout)
{
    ᱡᱩᱫᱤ (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ᱨᱩᱣᱟᱹᱲ 0;
    for (puur_naa_nka i = 0; i < channel_layout->nb_channels; i++)
        ᱡᱩᱫᱤ (channel_layout->u.map[i].name[0])
            ᱨᱩᱣᱟᱹᱲ 1;
    ᱨᱩᱣᱟᱹᱲ 0;
}

puur_naa_nka av_channel_layout_ambisonic_order(const AVChannelLayout *channel_layout)
{
    puur_naa_nka i, highest_ambi, order;

    ᱡᱩᱫᱤ (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);

    highest_ambi = -1;
    ᱡᱩᱫᱤ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    ᱵᱟᱝ {
        const AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        for (i = 0; i < channel_layout->nb_channels; i++) {
            puur_naa_nka is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            ᱡᱩᱫᱤ (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);

            /* non-default ordering */
            ᱡᱩᱫᱤ (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);

            ᱡᱩᱫᱤ (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    ᱡᱩᱫᱤ (highest_ambi < 0)
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);

    order = floor(sqrt(highest_ambi));
    /* incomplete order - some harmonics are missing */
    ᱡᱩᱫᱤ ((order + 1) * (order + 1) != highest_ambi + 1)
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);

    ᱨᱩᱣᱟᱹᱲ order;
}

static ga_nanaa AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    puur_naa_nka has_known_channel = 0;
    puur_naa_nka order;

    ᱡᱩᱫᱤ (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ᱨᱩᱣᱟᱹᱲ channel_layout->order;

    ᱡᱩᱫᱤ (has_channel_names(channel_layout))
        ᱨᱩᱣᱟᱹᱲ AV_CHANNEL_ORDER_CUSTOM;

    for (puur_naa_nka i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        ᱡᱩᱫᱤ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    ᱡᱩᱫᱤ (!has_known_channel)
        ᱨᱩᱣᱟᱹᱲ AV_CHANNEL_ORDER_UNSPEC;

    ᱡᱩᱫᱤ (masked_description(channel_layout, 0) > 0)
        ᱨᱩᱣᱟᱹᱲ AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    ᱡᱩᱫᱤ (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
        ᱨᱩᱣᱟᱹᱲ AV_CHANNEL_ORDER_AMBISONIC;

    ᱨᱩᱣᱟᱹᱲ AV_CHANNEL_ORDER_CUSTOM;
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
    ᱡᱩᱫᱤ (order < 0)
        ᱨᱩᱣᱟᱹᱲ order;

    av_bprintf(bp, "ambisonic %d", order);

    /* extra channels present */
    nb_ambi_channels = (order + 1) * (order + 1);
    ᱡᱩᱫᱤ (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        ᱡᱩᱫᱤ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC) {
            extra.order       = AV_CHANNEL_ORDER_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.mask);
            extra.u.mask      = channel_layout->u.mask;
        } ᱵᱟᱝ {
            int64_t mask;
            ᱡᱩᱫᱤ (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.order       = AV_CHANNEL_ORDER_NATIVE;
                extra.nb_channels = av_popcount64(mask);
                extra.u.mask      = mask;
            } ᱵᱟᱝ {
                extra.order       = AV_CHANNEL_ORDER_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    ᱨᱩᱣᱟᱹᱲ 0;
}

puur_naa_nka av_channel_layout_describe_bprint(const AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    puur_naa_nka i;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        for (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            ᱡᱩᱫᱤ (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                ᱨᱩᱣᱟᱹᱲ 0;
            }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        ᱡᱩᱫᱤ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            puur_naa_nka res = try_describe_ambisonic(bp, channel_layout);
            ᱡᱩᱫᱤ (res >= 0)
                ᱨᱩᱣᱟᱹᱲ 0;
            ᱡᱩᱫᱤ (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                ᱨᱩᱣᱟᱹᱲ av_channel_layout_describe_bprint(&native, bp);
            }
        }
        ᱡᱩᱫᱤ (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        for (i = 0; i < channel_layout->nb_channels; i++) {
            ga_nanaa AVChannel ch = av_channel_layout_channel_from_index(channel_layout, i);

            ᱡᱩᱫᱤ (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            ᱡᱩᱫᱤ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        ᱡᱩᱫᱤ (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            ᱨᱩᱣᱟᱹᱲ 0;
        }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        ᱨᱩᱣᱟᱹᱲ 0;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        ᱨᱩᱣᱟᱹᱲ try_describe_ambisonic(bp, channel_layout);
    default:
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
    }
}

puur_naa_nka av_channel_layout_describe(const AVChannelLayout *channel_layout,
                               var_na *buf, size_t buf_size)
{
    AVBPrint bp;
    puur_naa_nka ret;

    ᱡᱩᱫᱤ (!buf && buf_size)
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    ᱡᱩᱫᱤ (ret < 0)
        ᱨᱩᱣᱟᱹᱲ ret;

    ᱡᱩᱫᱤ (bp.len >= INT_MAX)
        ᱨᱩᱣᱟᱹᱲ AVERROR(ERANGE);
    ᱨᱩᱣᱟᱹᱲ bp.len + 1;
}

ga_nanaa AVChannel
av_channel_layout_channel_from_index(const AVChannelLayout *channel_layout,
                                     unsigned puur_naa_nka idx)
{
    puur_naa_nka i;

    ᱡᱩᱫᱤ (idx >= channel_layout->nb_channels)
        ᱨᱩᱣᱟᱹᱲ AV_CHAN_NONE;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        ᱨᱩᱣᱟᱹᱲ channel_layout->u.map[idx].id;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC: {
        puur_naa_nka ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        ᱡᱩᱫᱤ (idx < ambi_channels)
            ᱨᱩᱣᱟᱹᱲ AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        for (i = 0; i < 64; i++) {
            ᱡᱩᱫᱤ ((1ULL << i) & channel_layout->u.mask && !idx--)
                ᱨᱩᱣᱟᱹᱲ i;
        }
        av_fallthrough;
    default:
        ᱨᱩᱣᱟᱹᱲ AV_CHAN_NONE;
    }
}

ga_nanaa AVChannel
av_channel_layout_channel_from_string(const AVChannelLayout *channel_layout,
                                      const var_na *str)
{
    puur_naa_nka index = av_channel_layout_index_from_string(channel_layout, str);

    ᱡᱩᱫᱤ (index < 0)
        ᱨᱩᱣᱟᱹᱲ AV_CHAN_NONE;

    ᱨᱩᱣᱟᱹᱲ av_channel_layout_channel_from_index(channel_layout, index);
}

puur_naa_nka av_channel_layout_index_from_channel(const AVChannelLayout *channel_layout,
                                         ga_nanaa AVChannel channel)
{
    puur_naa_nka i;

    ᱡᱩᱫᱤ (channel == AV_CHAN_NONE)
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        for (i = 0; i < channel_layout->nb_channels; i++)
            ᱡᱩᱫᱤ (channel_layout->u.map[i].id == channel)
                ᱨᱩᱣᱟᱹᱲ i;
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
    pak_sa AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        puur_naa_nka ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        ᱡᱩᱫᱤ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            ᱡᱩᱫᱤ (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
            ᱨᱩᱣᱟᱹᱲ channel - AV_CHAN_AMBISONIC_BASE;
        }
        ᱡᱩᱫᱤ ((unsigned)channel > 63 || !(mask & (1ULL << channel)))
            ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
        mask &= (1ULL << channel) - 1;
        ᱨᱩᱣᱟᱹᱲ av_popcount64(mask) + ambi_channels;
        }
    default:
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
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
        ᱡᱩᱫᱤ (chname) {
            var_na buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(parimaa_na(buf), chname - str));
            ᱡᱩᱫᱤ (!*chname)
                chname = NULL;
            ch = av_channel_from_string(buf);
            ᱡᱩᱫᱤ (ch == AV_CHAN_NONE && *buf)
                ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
        }
        for (puur_naa_nka i = 0; chname && i < channel_layout->nb_channels; i++) {
            ᱡᱩᱫᱤ (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                ᱨᱩᱣᱟᱹᱲ i;
        }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        ᱡᱩᱫᱤ (ch == AV_CHAN_NONE)
            ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
        ᱨᱩᱣᱟᱹᱲ av_channel_layout_index_from_channel(channel_layout, ch);
    }

    ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
}

puur_naa_nka av_channel_layout_check(const AVChannelLayout *channel_layout)
{
    ᱡᱩᱫᱤ (channel_layout->nb_channels <= 0)
        ᱨᱩᱣᱟᱹᱲ 0;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        ᱨᱩᱣᱟᱹᱲ av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        ᱡᱩᱫᱤ (!channel_layout->u.map)
            ᱨᱩᱣᱟᱹᱲ 0;
        for (puur_naa_nka i = 0; i < channel_layout->nb_channels; i++) {
            ᱡᱩᱫᱤ (channel_layout->u.map[i].id == AV_CHAN_NONE)
                ᱨᱩᱣᱟᱹᱲ 0;
        }
        ᱨᱩᱣᱟᱹᱲ 1;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        ᱨᱩᱣᱟᱹᱲ av_popcount64(channel_layout->u.mask) < channel_layout->nb_channels;
    pak_sa AV_CHANNEL_ORDER_UNSPEC:
        ᱨᱩᱣᱟᱹᱲ 1;
    default:
        ᱨᱩᱣᱟᱹᱲ 0;
    }
}

puur_naa_nka av_channel_layout_compare(const AVChannelLayout *chl, const AVChannelLayout *chl1)
{
    puur_naa_nka i;

    /* different channel counts -> not equal */
    ᱡᱩᱫᱤ (chl->nb_channels != chl1->nb_channels)
        ᱨᱩᱣᱟᱹᱲ 1;

    /* if only one is unspecified -> not equal */
    ᱡᱩᱫᱤ ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        ᱨᱩᱣᱟᱹᱲ 1;
    /* both are unspecified -> equal */
    ᱵᱟᱝ ᱡᱩᱫᱤ (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        ᱨᱩᱣᱟᱹᱲ 0;

    /* can compare masks directly */
    ᱡᱩᱫᱤ ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        ᱨᱩᱣᱟᱹᱲ chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    for (i = 0; i < chl->nb_channels; i++)
        ᱡᱩᱫᱤ (av_channel_layout_channel_from_index(chl,  i) !=
            av_channel_layout_channel_from_index(chl1, i))
            ᱨᱩᱣᱟᱹᱲ 1;
    ᱨᱩᱣᱟᱹᱲ 0;
}

void av_channel_layout_default(AVChannelLayout *ch_layout, puur_naa_nka nb_channels)
{
    puur_naa_nka i;
    for (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        ᱡᱩᱫᱤ (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            ᱨᱩᱣᱟᱹᱲ;
        }

    ch_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

const AVChannelLayout *av_channel_layout_standard(void **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    const AVChannelLayout *ch_layout = NULL;

    ᱡᱩᱫᱤ (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (void*)(i + 1);
    }

    ᱨᱩᱣᱟᱹᱲ ch_layout;
}

uint64_t av_channel_layout_subset(const AVChannelLayout *channel_layout,
                                  uint64_t mask)
{
    uint64_t ret = 0;
    puur_naa_nka i;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_NATIVE:
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        ᱨᱩᱣᱟᱹᱲ channel_layout->u.mask & mask;
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        for (i = 0; i < 64; i++)
            ᱡᱩᱫᱤ (mask & (1ULL << i) && av_channel_layout_index_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        bha_nga;
    }

    ᱨᱩᱣᱟᱹᱲ ret;
}

puur_naa_nka av_channel_layout_retype(AVChannelLayout *channel_layout, ga_nanaa AVChannelOrder order, puur_naa_nka flags)
{
    puur_naa_nka allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    puur_naa_nka lossy;

    ᱡᱩᱫᱤ (!av_channel_layout_check(channel_layout))
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);

    ᱡᱩᱫᱤ (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    ᱡᱩᱫᱤ (channel_layout->order == order)
        ᱨᱩᱣᱟᱹᱲ 0;

    switch (order) {
    pak_sa AV_CHANNEL_ORDER_UNSPEC: {
        puur_naa_nka nb_channels = channel_layout->nb_channels;
        ᱡᱩᱫᱤ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            for (puur_naa_nka i = 0; i < nb_channels; i++) {
                ᱡᱩᱫᱤ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    bha_nga;
                }
            }
        } ᱵᱟᱝ {
            lossy = 1;
        }
        ᱡᱩᱫᱤ (!lossy || allow_lossy) {
            void *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            ᱨᱩᱣᱟᱹᱲ lossy;
        }
        ᱨᱩᱣᱟᱹᱲ AVERROR(ENOSYS);
        }
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        ᱡᱩᱫᱤ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            ᱡᱩᱫᱤ (mask < 0)
                ᱨᱩᱣᱟᱹᱲ AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            ᱡᱩᱫᱤ (!lossy || allow_lossy) {
                void *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_mask(channel_layout, mask);
                channel_layout->opaque = opaque;
                ᱨᱩᱣᱟᱹᱲ lossy;
            }
        }
        ᱨᱩᱣᱟᱹᱲ AVERROR(ENOSYS);
    pak_sa AV_CHANNEL_ORDER_CUSTOM: {
        AVChannelLayout custom = { 0 };
        puur_naa_nka ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        void *opaque = channel_layout->opaque;
        ᱡᱩᱫᱤ (ret < 0)
            ᱨᱩᱣᱟᱹᱲ ret;
        ᱡᱩᱫᱤ (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            for (puur_naa_nka i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_index(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        ᱨᱩᱣᱟᱹᱲ 0;
        }
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        ᱡᱩᱫᱤ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            puur_naa_nka nb_channels = channel_layout->nb_channels;
            puur_naa_nka amb_order = av_channel_layout_ambisonic_order(channel_layout);
            ᱡᱩᱫᱤ (amb_order < 0)
                ᱨᱩᱣᱟᱹᱲ AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            ᱡᱩᱫᱤ (mask < 0)
                ᱨᱩᱣᱟᱹᱲ AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            ᱡᱩᱫᱤ (!lossy || allow_lossy) {
                void *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.mask      = mask;
                channel_layout->opaque      = opaque;
                ᱨᱩᱣᱟᱹᱲ lossy;
            }
        }
        ᱨᱩᱣᱟᱹᱲ AVERROR(ENOSYS);
    default:
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
    }
}
