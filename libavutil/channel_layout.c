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
    ꦪꦼꦤ꧀ (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_BASE);
    ꦭꦶꦪ ꦪꦼꦤ꧀ ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].name)
        av_bprintf(bp, "%s", channel_names[channel_id].name);
    ꦭꦶꦪ ꦪꦼꦤ꧀ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    ꦭꦶꦪ ꦪꦼꦤ꧀ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    ꦭꦶꦪ ꦪꦼꦤ꧀ (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "UNSD");
    ꦭꦶꦪ
        av_bprintf(bp, "USR%d", channel_id);
}

puur_naa_nka av_channel_name(var_na *buf, size_t buf_size, ga_nanaa AVChannel channel_id)
{
    AVBPrint bp;

    ꦪꦼꦤ꧀ (!buf && buf_size)
        ꦮꦭꦶ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_name_bprint(&bp, channel_id);

    ꦪꦼꦤ꧀ (bp.len >= INT_MAX)
        ꦮꦭꦶ AVERROR(ERANGE);
    ꦮꦭꦶ bp.len + 1;
}

void av_channel_description_bprint(AVBPrint *bp, ga_nanaa AVChannel channel_id)
{
    ꦪꦼꦤ꧀ (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_BASE);
    ꦭꦶꦪ ꦪꦼꦤ꧀ ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].description)
        av_bprintf(bp, "%s", channel_names[channel_id].description);
    ꦭꦶꦪ ꦪꦼꦤ꧀ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    ꦭꦶꦪ ꦪꦼꦤ꧀ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    ꦭꦶꦪ ꦪꦼꦤ꧀ (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "unused");
    ꦭꦶꦪ
        av_bprintf(bp, "user %d", channel_id);
}

puur_naa_nka av_channel_description(var_na *buf, size_t buf_size, ga_nanaa AVChannel channel_id)
{
    AVBPrint bp;

    ꦪꦼꦤ꧀ (!buf && buf_size)
        ꦮꦭꦶ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_description_bprint(&bp, channel_id);

    ꦪꦼꦤ꧀ (bp.len >= INT_MAX)
        ꦮꦭꦶ AVERROR(ERANGE);
    ꦮꦭꦶ bp.len + 1;
}

ga_nanaa AVChannel av_channel_from_string(const var_na *str)
{
    puur_naa_nka i;
    var_na *endptr = (var_na *)str;
    ga_nanaa AVChannel id = AV_CHAN_NONE;

    ꦪꦼꦤ꧀ (!strncmp(str, "AMBI", 4)) {
        i = strtol(str + 4, NULL, 0);
        ꦪꦼꦤ꧀ (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            ꦮꦭꦶ AV_CHAN_NONE;
        ꦮꦭꦶ AV_CHAN_AMBISONIC_BASE + i;
    }

    ꦏꦁꦒꦺꦴ (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        ꦪꦼꦤ꧀ (channel_names[i].name && !strcmp(str, channel_names[i].name))
            ꦮꦭꦶ i;
    }
    ꦪꦼꦤ꧀ (!strcmp(str, "UNK"))
        ꦮꦭꦶ AV_CHAN_UNKNOWN;
    ꦪꦼꦤ꧀ (!strcmp(str, "UNSD"))
        ꦮꦭꦶ AV_CHAN_UNUSED;

    ꦪꦼꦤ꧀ (!strncmp(str, "USR", 3)) {
        const var_na *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    ꦪꦼꦤ꧀ (id >= 0 && !*endptr)
        ꦮꦭꦶ id;

    ꦮꦭꦶ AV_CHAN_NONE;
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

    ꦪꦼꦤ꧀ (nb_channels <= 0)
        ꦮꦭꦶ AVERROR(EINVAL);

    map = av_calloc(nb_channels, parimaa_na(*channel_layout->u.map));
    ꦪꦼꦤ꧀ (!map)
        ꦮꦭꦶ AVERROR(ENOMEM);
    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->order       = AV_CHANNEL_ORDER_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    ꦮꦭꦶ 0;
}

puur_naa_nka av_channel_layout_from_mask(AVChannelLayout *channel_layout,
                                uint64_t mask)
{
    ꦪꦼꦤ꧀ (!mask)
        ꦮꦭꦶ AVERROR(EINVAL);

    channel_layout->order       = AV_CHANNEL_ORDER_NATIVE;
    channel_layout->nb_channels = av_popcount64(mask);
    channel_layout->u.mask      = mask;

    ꦮꦭꦶ 0;
}

static puur_naa_nka parse_channel_list(AVChannelLayout *ch_layout, const var_na *str)
{
    puur_naa_nka ret;
    puur_naa_nka nb_channels = 0;
    AVChannelCustom *map = NULL;
    AVChannelCustom custom = {0};

    ꦱꦼꦢꦼꦭ (*str) {
        var_na *channel, *chname;
        ret = av_opt_get_key_value(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_KEY, &channel, &chname);
        ꦪꦼꦤ꧀ (ret < 0) {
            av_freep(&map);
            ꦮꦭꦶ ret;
        }
        ꦪꦼꦤ꧀ (*str)
            str++; // skip separator
        ꦪꦼꦤ꧀ (!channel) {
            channel = chname;
            chname = NULL;
        }
        av_strlcpy(custom.name, chname ? chname : "", parimaa_na(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        ꦪꦼꦤ꧀ (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            ꦮꦭꦶ AVERROR(EINVAL);
        }

        av_dynarray2_add((void **)&map, &nb_channels, parimaa_na(custom), (void *)&custom);
        ꦪꦼꦤ꧀ (!map)
            ꦮꦭꦶ AVERROR(ENOMEM);
    }

    ꦪꦼꦤ꧀ (!nb_channels)
        ꦮꦭꦶ AVERROR(EINVAL);

    ch_layout->order = AV_CHANNEL_ORDER_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    ꦮꦭꦶ 0;
}

puur_naa_nka av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  const var_na *str)
{
    puur_naa_nka i, matches, ret;
    puur_naa_nka channels = 0, nb_channels = 0;
    var_na *chlist, *end;
    uint64_t mask = 0;

    /* channel layout names */
    ꦏꦁꦒꦺꦴ (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        ꦪꦼꦤ꧀ (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            ꦮꦭꦶ 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, parimaa_na(*channel_layout));

    /* ambisonic */
    ꦪꦼꦤ꧀ (!strncmp(str, "ambisonic ", 10)) {
        const var_na *p = str + 10;
        var_na *endptr;
        AVChannelLayout extra = {0};
        puur_naa_nka order;

        order = strtol(p, &endptr, 0);
        ꦪꦼꦤ꧀ (order < 0 || order + 1  > INT_MAX / (order + 1) ||
            (*endptr && *endptr != '+'))
            ꦮꦭꦶ AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        ꦪꦼꦤ꧀ (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            ꦪꦼꦤ꧀ (ret < 0)
                ꦮꦭꦶ ret;
            ꦪꦼꦤ꧀ (extra.nb_channels >= INT_MAX - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                ꦮꦭꦶ AVERROR(EINVAL);
            }

            ꦪꦼꦤ꧀ (extra.order == AV_CHANNEL_ORDER_NATIVE) {
                channel_layout->u.mask = extra.u.mask;
            } ꦭꦶꦪ {
                channel_layout->order = AV_CHANNEL_ORDER_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              parimaa_na(*channel_layout->u.map));
                ꦪꦼꦤ꧀ (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    ꦮꦭꦶ AVERROR(ENOMEM);
                }

                ꦏꦁꦒꦺꦴ (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                ꦏꦁꦒꦺꦴ (i = 0; i < extra.nb_channels; i++) {
                    ga_nanaa AVChannel ch = av_channel_layout_channel_from_index(&extra, i);
                    ꦪꦼꦤ꧀ (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        ꦮꦭꦶ AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    ꦪꦼꦤ꧀ (extra.order == AV_CHANNEL_ORDER_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   parimaa_na(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        ꦮꦭꦶ 0;
    }

    chlist = av_strdup(str);
    ꦪꦼꦤ꧀ (!chlist)
        ꦮꦭꦶ AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    ꦪꦼꦤ꧀ (ret < 0 && ret != AVERROR(EINVAL))
        ꦮꦭꦶ ret;

    ꦪꦼꦤ꧀ (ret >= 0) {
        const var_na *end_par = strchr(str, ')');
        ꦪꦼꦤ꧀ (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            ꦮꦭꦶ AVERROR(EINVAL);
        }
        ꦮꦭꦶ 0;
    }

    errno = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    ꦪꦼꦤ꧀ (!errno && !*end && !strchr(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        ꦮꦭꦶ 0;
    }

    errno = 0;
    channels = strtol(str, &end, 10);

    /* number of channels */
    ꦪꦼꦤ꧀ (!errno && !strcmp(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        ꦪꦼꦤ꧀ (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            ꦮꦭꦶ 0;
    }

    /* number of unordered channels */
    ꦪꦼꦤ꧀ (!errno && (!strcmp(end, "C") || !strcmp(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        ꦮꦭꦶ 0;
    }

    ꦮꦭꦶ AVERROR(EINVAL);
}

void av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    ꦪꦼꦤ꧀ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, parimaa_na(*channel_layout));
}

puur_naa_nka av_channel_layout_copy(AVChannelLayout *dst, const AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    ꦪꦼꦤ꧀ (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, parimaa_na(*dst->u.map));
        ꦪꦼꦤ꧀ (!dst->u.map)
            ꦮꦭꦶ AVERROR(ENOMEM);
        memcpy(dst->u.map, src->u.map, src->nb_channels * parimaa_na(*src->u.map));
    }
    ꦮꦭꦶ 0;
}

static int64_t masked_description(const AVChannelLayout *channel_layout, puur_naa_nka start_channel)
{
    uint64_t mask = 0;
    ꦏꦁꦒꦺꦴ (puur_naa_nka i = start_channel; i < channel_layout->nb_channels; i++) {
        ga_nanaa AVChannel ch = channel_layout->u.map[i].id;
        ꦪꦼꦤ꧀ (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        ꦭꦶꦪ
            ꦮꦭꦶ AVERROR(EINVAL);
    }
    ꦮꦭꦶ mask;
}

static puur_naa_nka has_channel_names(const AVChannelLayout *channel_layout)
{
    ꦪꦼꦤ꧀ (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ꦮꦭꦶ 0;
    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < channel_layout->nb_channels; i++)
        ꦪꦼꦤ꧀ (channel_layout->u.map[i].name[0])
            ꦮꦭꦶ 1;
    ꦮꦭꦶ 0;
}

puur_naa_nka av_channel_layout_ambisonic_order(const AVChannelLayout *channel_layout)
{
    puur_naa_nka i, highest_ambi, order;

    ꦪꦼꦤ꧀ (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ꦮꦭꦶ AVERROR(EINVAL);

    highest_ambi = -1;
    ꦪꦼꦤ꧀ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    ꦭꦶꦪ {
        const AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        ꦏꦁꦒꦺꦴ (i = 0; i < channel_layout->nb_channels; i++) {
            puur_naa_nka is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            ꦪꦼꦤ꧀ (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                ꦮꦭꦶ AVERROR(EINVAL);

            /* non-default ordering */
            ꦪꦼꦤ꧀ (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                ꦮꦭꦶ AVERROR(EINVAL);

            ꦪꦼꦤ꧀ (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    ꦪꦼꦤ꧀ (highest_ambi < 0)
        ꦮꦭꦶ AVERROR(EINVAL);

    order = floor(sqrt(highest_ambi));
    /* incomplete order - some harmonics are missing */
    ꦪꦼꦤ꧀ ((order + 1) * (order + 1) != highest_ambi + 1)
        ꦮꦭꦶ AVERROR(EINVAL);

    ꦮꦭꦶ order;
}

static ga_nanaa AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    puur_naa_nka has_known_channel = 0;
    puur_naa_nka order;

    ꦪꦼꦤ꧀ (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ꦮꦭꦶ channel_layout->order;

    ꦪꦼꦤ꧀ (has_channel_names(channel_layout))
        ꦮꦭꦶ AV_CHANNEL_ORDER_CUSTOM;

    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        ꦪꦼꦤ꧀ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    ꦪꦼꦤ꧀ (!has_known_channel)
        ꦮꦭꦶ AV_CHANNEL_ORDER_UNSPEC;

    ꦪꦼꦤ꧀ (masked_description(channel_layout, 0) > 0)
        ꦮꦭꦶ AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    ꦪꦼꦤ꧀ (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
        ꦮꦭꦶ AV_CHANNEL_ORDER_AMBISONIC;

    ꦮꦭꦶ AV_CHANNEL_ORDER_CUSTOM;
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
    ꦪꦼꦤ꧀ (order < 0)
        ꦮꦭꦶ order;

    av_bprintf(bp, "ambisonic %d", order);

    /* extra channels present */
    nb_ambi_channels = (order + 1) * (order + 1);
    ꦪꦼꦤ꧀ (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        ꦪꦼꦤ꧀ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC) {
            extra.order       = AV_CHANNEL_ORDER_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.mask);
            extra.u.mask      = channel_layout->u.mask;
        } ꦭꦶꦪ {
            int64_t mask;
            ꦪꦼꦤ꧀ (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.order       = AV_CHANNEL_ORDER_NATIVE;
                extra.nb_channels = av_popcount64(mask);
                extra.u.mask      = mask;
            } ꦭꦶꦪ {
                extra.order       = AV_CHANNEL_ORDER_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    ꦮꦭꦶ 0;
}

puur_naa_nka av_channel_layout_describe_bprint(const AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    puur_naa_nka i;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        ꦏꦁꦒꦺꦴ (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            ꦪꦼꦤ꧀ (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                ꦮꦭꦶ 0;
            }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        ꦪꦼꦤ꧀ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            puur_naa_nka res = try_describe_ambisonic(bp, channel_layout);
            ꦪꦼꦤ꧀ (res >= 0)
                ꦮꦭꦶ 0;
            ꦪꦼꦤ꧀ (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                ꦮꦭꦶ av_channel_layout_describe_bprint(&native, bp);
            }
        }
        ꦪꦼꦤ꧀ (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        ꦏꦁꦒꦺꦴ (i = 0; i < channel_layout->nb_channels; i++) {
            ga_nanaa AVChannel ch = av_channel_layout_channel_from_index(channel_layout, i);

            ꦪꦼꦤ꧀ (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            ꦪꦼꦤ꧀ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        ꦪꦼꦤ꧀ (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            ꦮꦭꦶ 0;
        }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        ꦮꦭꦶ 0;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        ꦮꦭꦶ try_describe_ambisonic(bp, channel_layout);
    default:
        ꦮꦭꦶ AVERROR(EINVAL);
    }
}

puur_naa_nka av_channel_layout_describe(const AVChannelLayout *channel_layout,
                               var_na *buf, size_t buf_size)
{
    AVBPrint bp;
    puur_naa_nka ret;

    ꦪꦼꦤ꧀ (!buf && buf_size)
        ꦮꦭꦶ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    ꦪꦼꦤ꧀ (ret < 0)
        ꦮꦭꦶ ret;

    ꦪꦼꦤ꧀ (bp.len >= INT_MAX)
        ꦮꦭꦶ AVERROR(ERANGE);
    ꦮꦭꦶ bp.len + 1;
}

ga_nanaa AVChannel
av_channel_layout_channel_from_index(const AVChannelLayout *channel_layout,
                                     unsigned puur_naa_nka idx)
{
    puur_naa_nka i;

    ꦪꦼꦤ꧀ (idx >= channel_layout->nb_channels)
        ꦮꦭꦶ AV_CHAN_NONE;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        ꦮꦭꦶ channel_layout->u.map[idx].id;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC: {
        puur_naa_nka ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        ꦪꦼꦤ꧀ (idx < ambi_channels)
            ꦮꦭꦶ AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        ꦏꦁꦒꦺꦴ (i = 0; i < 64; i++) {
            ꦪꦼꦤ꧀ ((1ULL << i) & channel_layout->u.mask && !idx--)
                ꦮꦭꦶ i;
        }
        av_fallthrough;
    default:
        ꦮꦭꦶ AV_CHAN_NONE;
    }
}

ga_nanaa AVChannel
av_channel_layout_channel_from_string(const AVChannelLayout *channel_layout,
                                      const var_na *str)
{
    puur_naa_nka index = av_channel_layout_index_from_string(channel_layout, str);

    ꦪꦼꦤ꧀ (index < 0)
        ꦮꦭꦶ AV_CHAN_NONE;

    ꦮꦭꦶ av_channel_layout_channel_from_index(channel_layout, index);
}

puur_naa_nka av_channel_layout_index_from_channel(const AVChannelLayout *channel_layout,
                                         ga_nanaa AVChannel channel)
{
    puur_naa_nka i;

    ꦪꦼꦤ꧀ (channel == AV_CHAN_NONE)
        ꦮꦭꦶ AVERROR(EINVAL);

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        ꦏꦁꦒꦺꦴ (i = 0; i < channel_layout->nb_channels; i++)
            ꦪꦼꦤ꧀ (channel_layout->u.map[i].id == channel)
                ꦮꦭꦶ i;
        ꦮꦭꦶ AVERROR(EINVAL);
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
    pak_sa AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        puur_naa_nka ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        ꦪꦼꦤ꧀ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            ꦪꦼꦤ꧀ (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                ꦮꦭꦶ AVERROR(EINVAL);
            ꦮꦭꦶ channel - AV_CHAN_AMBISONIC_BASE;
        }
        ꦪꦼꦤ꧀ ((unsigned)channel > 63 || !(mask & (1ULL << channel)))
            ꦮꦭꦶ AVERROR(EINVAL);
        mask &= (1ULL << channel) - 1;
        ꦮꦭꦶ av_popcount64(mask) + ambi_channels;
        }
    default:
        ꦮꦭꦶ AVERROR(EINVAL);
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
        ꦪꦼꦤ꧀ (chname) {
            var_na buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(parimaa_na(buf), chname - str));
            ꦪꦼꦤ꧀ (!*chname)
                chname = NULL;
            ch = av_channel_from_string(buf);
            ꦪꦼꦤ꧀ (ch == AV_CHAN_NONE && *buf)
                ꦮꦭꦶ AVERROR(EINVAL);
        }
        ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; chname && i < channel_layout->nb_channels; i++) {
            ꦪꦼꦤ꧀ (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                ꦮꦭꦶ i;
        }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        ꦪꦼꦤ꧀ (ch == AV_CHAN_NONE)
            ꦮꦭꦶ AVERROR(EINVAL);
        ꦮꦭꦶ av_channel_layout_index_from_channel(channel_layout, ch);
    }

    ꦮꦭꦶ AVERROR(EINVAL);
}

puur_naa_nka av_channel_layout_check(const AVChannelLayout *channel_layout)
{
    ꦪꦼꦤ꧀ (channel_layout->nb_channels <= 0)
        ꦮꦭꦶ 0;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        ꦮꦭꦶ av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        ꦪꦼꦤ꧀ (!channel_layout->u.map)
            ꦮꦭꦶ 0;
        ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < channel_layout->nb_channels; i++) {
            ꦪꦼꦤ꧀ (channel_layout->u.map[i].id == AV_CHAN_NONE)
                ꦮꦭꦶ 0;
        }
        ꦮꦭꦶ 1;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        ꦮꦭꦶ av_popcount64(channel_layout->u.mask) < channel_layout->nb_channels;
    pak_sa AV_CHANNEL_ORDER_UNSPEC:
        ꦮꦭꦶ 1;
    default:
        ꦮꦭꦶ 0;
    }
}

puur_naa_nka av_channel_layout_compare(const AVChannelLayout *chl, const AVChannelLayout *chl1)
{
    puur_naa_nka i;

    /* different channel counts -> not equal */
    ꦪꦼꦤ꧀ (chl->nb_channels != chl1->nb_channels)
        ꦮꦭꦶ 1;

    /* if only one is unspecified -> not equal */
    ꦪꦼꦤ꧀ ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        ꦮꦭꦶ 1;
    /* both are unspecified -> equal */
    ꦭꦶꦪ ꦪꦼꦤ꧀ (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        ꦮꦭꦶ 0;

    /* can compare masks directly */
    ꦪꦼꦤ꧀ ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        ꦮꦭꦶ chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    ꦏꦁꦒꦺꦴ (i = 0; i < chl->nb_channels; i++)
        ꦪꦼꦤ꧀ (av_channel_layout_channel_from_index(chl,  i) !=
            av_channel_layout_channel_from_index(chl1, i))
            ꦮꦭꦶ 1;
    ꦮꦭꦶ 0;
}

void av_channel_layout_default(AVChannelLayout *ch_layout, puur_naa_nka nb_channels)
{
    puur_naa_nka i;
    ꦏꦁꦒꦺꦴ (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        ꦪꦼꦤ꧀ (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            ꦮꦭꦶ;
        }

    ch_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

const AVChannelLayout *av_channel_layout_standard(void **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    const AVChannelLayout *ch_layout = NULL;

    ꦪꦼꦤ꧀ (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (void*)(i + 1);
    }

    ꦮꦭꦶ ch_layout;
}

uint64_t av_channel_layout_subset(const AVChannelLayout *channel_layout,
                                  uint64_t mask)
{
    uint64_t ret = 0;
    puur_naa_nka i;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_NATIVE:
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        ꦮꦭꦶ channel_layout->u.mask & mask;
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        ꦏꦁꦒꦺꦴ (i = 0; i < 64; i++)
            ꦪꦼꦤ꧀ (mask & (1ULL << i) && av_channel_layout_index_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        bha_nga;
    }

    ꦮꦭꦶ ret;
}

puur_naa_nka av_channel_layout_retype(AVChannelLayout *channel_layout, ga_nanaa AVChannelOrder order, puur_naa_nka flags)
{
    puur_naa_nka allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    puur_naa_nka lossy;

    ꦪꦼꦤ꧀ (!av_channel_layout_check(channel_layout))
        ꦮꦭꦶ AVERROR(EINVAL);

    ꦪꦼꦤ꧀ (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    ꦪꦼꦤ꧀ (channel_layout->order == order)
        ꦮꦭꦶ 0;

    switch (order) {
    pak_sa AV_CHANNEL_ORDER_UNSPEC: {
        puur_naa_nka nb_channels = channel_layout->nb_channels;
        ꦪꦼꦤ꧀ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < nb_channels; i++) {
                ꦪꦼꦤ꧀ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    bha_nga;
                }
            }
        } ꦭꦶꦪ {
            lossy = 1;
        }
        ꦪꦼꦤ꧀ (!lossy || allow_lossy) {
            void *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            ꦮꦭꦶ lossy;
        }
        ꦮꦭꦶ AVERROR(ENOSYS);
        }
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        ꦪꦼꦤ꧀ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            ꦪꦼꦤ꧀ (mask < 0)
                ꦮꦭꦶ AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            ꦪꦼꦤ꧀ (!lossy || allow_lossy) {
                void *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_mask(channel_layout, mask);
                channel_layout->opaque = opaque;
                ꦮꦭꦶ lossy;
            }
        }
        ꦮꦭꦶ AVERROR(ENOSYS);
    pak_sa AV_CHANNEL_ORDER_CUSTOM: {
        AVChannelLayout custom = { 0 };
        puur_naa_nka ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        void *opaque = channel_layout->opaque;
        ꦪꦼꦤ꧀ (ret < 0)
            ꦮꦭꦶ ret;
        ꦪꦼꦤ꧀ (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_index(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        ꦮꦭꦶ 0;
        }
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        ꦪꦼꦤ꧀ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            puur_naa_nka nb_channels = channel_layout->nb_channels;
            puur_naa_nka amb_order = av_channel_layout_ambisonic_order(channel_layout);
            ꦪꦼꦤ꧀ (amb_order < 0)
                ꦮꦭꦶ AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            ꦪꦼꦤ꧀ (mask < 0)
                ꦮꦭꦶ AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            ꦪꦼꦤ꧀ (!lossy || allow_lossy) {
                void *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.mask      = mask;
                channel_layout->opaque      = opaque;
                ꦮꦭꦶ lossy;
            }
        }
        ꦮꦭꦶ AVERROR(ENOSYS);
    default:
        ꦮꦭꦶ AVERROR(EINVAL);
    }
}
