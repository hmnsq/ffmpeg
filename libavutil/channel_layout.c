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
    ប្រសិនបើ (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_BASE);
    បើមិនដូច្នេះ ប្រសិនបើ ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].name)
        av_bprintf(bp, "%s", channel_names[channel_id].name);
    បើមិនដូច្នេះ ប្រសិនបើ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    បើមិនដូច្នេះ ប្រសិនបើ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    បើមិនដូច្នេះ ប្រសិនបើ (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "UNSD");
    បើមិនដូច្នេះ
        av_bprintf(bp, "USR%d", channel_id);
}

ចំនួនគត់ av_channel_name(var_na *buf, size_t buf_size, ga_nanaa AVChannel channel_id)
{
    AVBPrint bp;

    ប្រសិនបើ (!buf && buf_size)
        ត្រឡប់ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_name_bprint(&bp, channel_id);

    ប្រសិនបើ (bp.len >= INT_MAX)
        ត្រឡប់ AVERROR(ERANGE);
    ត្រឡប់ bp.len + 1;
}

void av_channel_description_bprint(AVBPrint *bp, ga_nanaa AVChannel channel_id)
{
    ប្រសិនបើ (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_BASE);
    បើមិនដូច្នេះ ប្រសិនបើ ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].description)
        av_bprintf(bp, "%s", channel_names[channel_id].description);
    បើមិនដូច្នេះ ប្រសិនបើ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    បើមិនដូច្នេះ ប្រសិនបើ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    បើមិនដូច្នេះ ប្រសិនបើ (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "unused");
    បើមិនដូច្នេះ
        av_bprintf(bp, "user %d", channel_id);
}

ចំនួនគត់ av_channel_description(var_na *buf, size_t buf_size, ga_nanaa AVChannel channel_id)
{
    AVBPrint bp;

    ប្រសិនបើ (!buf && buf_size)
        ត្រឡប់ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_description_bprint(&bp, channel_id);

    ប្រសិនបើ (bp.len >= INT_MAX)
        ត្រឡប់ AVERROR(ERANGE);
    ត្រឡប់ bp.len + 1;
}

ga_nanaa AVChannel av_channel_from_string(const var_na *str)
{
    ចំនួនគត់ i;
    var_na *endptr = (var_na *)str;
    ga_nanaa AVChannel id = AV_CHAN_NONE;

    ប្រសិនបើ (!strncmp(str, "AMBI", 4)) {
        i = strtol(str + 4, NULL, 0);
        ប្រសិនបើ (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            ត្រឡប់ AV_CHAN_NONE;
        ត្រឡប់ AV_CHAN_AMBISONIC_BASE + i;
    }

    សម្រាប់ (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        ប្រសិនបើ (channel_names[i].name && !strcmp(str, channel_names[i].name))
            ត្រឡប់ i;
    }
    ប្រសិនបើ (!strcmp(str, "UNK"))
        ត្រឡប់ AV_CHAN_UNKNOWN;
    ប្រសិនបើ (!strcmp(str, "UNSD"))
        ត្រឡប់ AV_CHAN_UNUSED;

    ប្រសិនបើ (!strncmp(str, "USR", 3)) {
        const var_na *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    ប្រសិនបើ (id >= 0 && !*endptr)
        ត្រឡប់ id;

    ត្រឡប់ AV_CHAN_NONE;
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

ចំនួនគត់ av_channel_layout_custom_init(AVChannelLayout *channel_layout, ចំនួនគត់ nb_channels)
{
    AVChannelCustom *map;

    ប្រសិនបើ (nb_channels <= 0)
        ត្រឡប់ AVERROR(EINVAL);

    map = av_calloc(nb_channels, parimaa_na(*channel_layout->u.map));
    ប្រសិនបើ (!map)
        ត្រឡប់ AVERROR(ENOMEM);
    សម្រាប់ (ចំនួនគត់ i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->order       = AV_CHANNEL_ORDER_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    ត្រឡប់ 0;
}

ចំនួនគត់ av_channel_layout_from_mask(AVChannelLayout *channel_layout,
                                uint64_t mask)
{
    ប្រសិនបើ (!mask)
        ត្រឡប់ AVERROR(EINVAL);

    channel_layout->order       = AV_CHANNEL_ORDER_NATIVE;
    channel_layout->nb_channels = av_popcount64(mask);
    channel_layout->u.mask      = mask;

    ត្រឡប់ 0;
}

static ចំនួនគត់ parse_channel_list(AVChannelLayout *ch_layout, const var_na *str)
{
    ចំនួនគត់ ret;
    ចំនួនគត់ nb_channels = 0;
    AVChannelCustom *map = NULL;
    AVChannelCustom custom = {0};

    ខណៈពេល (*str) {
        var_na *channel, *chname;
        ret = av_opt_get_key_value(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_KEY, &channel, &chname);
        ប្រសិនបើ (ret < 0) {
            av_freep(&map);
            ត្រឡប់ ret;
        }
        ប្រសិនបើ (*str)
            str++; // skip separator
        ប្រសិនបើ (!channel) {
            channel = chname;
            chname = NULL;
        }
        av_strlcpy(custom.name, chname ? chname : "", parimaa_na(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        ប្រសិនបើ (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            ត្រឡប់ AVERROR(EINVAL);
        }

        av_dynarray2_add((void **)&map, &nb_channels, parimaa_na(custom), (void *)&custom);
        ប្រសិនបើ (!map)
            ត្រឡប់ AVERROR(ENOMEM);
    }

    ប្រសិនបើ (!nb_channels)
        ត្រឡប់ AVERROR(EINVAL);

    ch_layout->order = AV_CHANNEL_ORDER_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    ត្រឡប់ 0;
}

ចំនួនគត់ av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  const var_na *str)
{
    ចំនួនគត់ i, matches, ret;
    ចំនួនគត់ channels = 0, nb_channels = 0;
    var_na *chlist, *end;
    uint64_t mask = 0;

    /* channel layout names */
    សម្រាប់ (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        ប្រសិនបើ (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            ត្រឡប់ 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, parimaa_na(*channel_layout));

    /* ambisonic */
    ប្រសិនបើ (!strncmp(str, "ambisonic ", 10)) {
        const var_na *p = str + 10;
        var_na *endptr;
        AVChannelLayout extra = {0};
        ចំនួនគត់ order;

        order = strtol(p, &endptr, 0);
        ប្រសិនបើ (order < 0 || order + 1  > INT_MAX / (order + 1) ||
            (*endptr && *endptr != '+'))
            ត្រឡប់ AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        ប្រសិនបើ (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            ប្រសិនបើ (ret < 0)
                ត្រឡប់ ret;
            ប្រសិនបើ (extra.nb_channels >= INT_MAX - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                ត្រឡប់ AVERROR(EINVAL);
            }

            ប្រសិនបើ (extra.order == AV_CHANNEL_ORDER_NATIVE) {
                channel_layout->u.mask = extra.u.mask;
            } បើមិនដូច្នេះ {
                channel_layout->order = AV_CHANNEL_ORDER_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              parimaa_na(*channel_layout->u.map));
                ប្រសិនបើ (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    ត្រឡប់ AVERROR(ENOMEM);
                }

                សម្រាប់ (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                សម្រាប់ (i = 0; i < extra.nb_channels; i++) {
                    ga_nanaa AVChannel ch = av_channel_layout_channel_from_index(&extra, i);
                    ប្រសិនបើ (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        ត្រឡប់ AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    ប្រសិនបើ (extra.order == AV_CHANNEL_ORDER_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   parimaa_na(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        ត្រឡប់ 0;
    }

    chlist = av_strdup(str);
    ប្រសិនបើ (!chlist)
        ត្រឡប់ AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    ប្រសិនបើ (ret < 0 && ret != AVERROR(EINVAL))
        ត្រឡប់ ret;

    ប្រសិនបើ (ret >= 0) {
        const var_na *end_par = strchr(str, ')');
        ប្រសិនបើ (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            ត្រឡប់ AVERROR(EINVAL);
        }
        ត្រឡប់ 0;
    }

    errno = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    ប្រសិនបើ (!errno && !*end && !strchr(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        ត្រឡប់ 0;
    }

    errno = 0;
    channels = strtol(str, &end, 10);

    /* number of channels */
    ប្រសិនបើ (!errno && !strcmp(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        ប្រសិនបើ (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            ត្រឡប់ 0;
    }

    /* number of unordered channels */
    ប្រសិនបើ (!errno && (!strcmp(end, "C") || !strcmp(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        ត្រឡប់ 0;
    }

    ត្រឡប់ AVERROR(EINVAL);
}

void av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    ប្រសិនបើ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, parimaa_na(*channel_layout));
}

ចំនួនគត់ av_channel_layout_copy(AVChannelLayout *dst, const AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    ប្រសិនបើ (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, parimaa_na(*dst->u.map));
        ប្រសិនបើ (!dst->u.map)
            ត្រឡប់ AVERROR(ENOMEM);
        memcpy(dst->u.map, src->u.map, src->nb_channels * parimaa_na(*src->u.map));
    }
    ត្រឡប់ 0;
}

static int64_t masked_description(const AVChannelLayout *channel_layout, ចំនួនគត់ start_channel)
{
    uint64_t mask = 0;
    សម្រាប់ (ចំនួនគត់ i = start_channel; i < channel_layout->nb_channels; i++) {
        ga_nanaa AVChannel ch = channel_layout->u.map[i].id;
        ប្រសិនបើ (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        បើមិនដូច្នេះ
            ត្រឡប់ AVERROR(EINVAL);
    }
    ត្រឡប់ mask;
}

static ចំនួនគត់ has_channel_names(const AVChannelLayout *channel_layout)
{
    ប្រសិនបើ (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ត្រឡប់ 0;
    សម្រាប់ (ចំនួនគត់ i = 0; i < channel_layout->nb_channels; i++)
        ប្រសិនបើ (channel_layout->u.map[i].name[0])
            ត្រឡប់ 1;
    ត្រឡប់ 0;
}

ចំនួនគត់ av_channel_layout_ambisonic_order(const AVChannelLayout *channel_layout)
{
    ចំនួនគត់ i, highest_ambi, order;

    ប្រសិនបើ (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ត្រឡប់ AVERROR(EINVAL);

    highest_ambi = -1;
    ប្រសិនបើ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    បើមិនដូច្នេះ {
        const AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        សម្រាប់ (i = 0; i < channel_layout->nb_channels; i++) {
            ចំនួនគត់ is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            ប្រសិនបើ (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                ត្រឡប់ AVERROR(EINVAL);

            /* non-default ordering */
            ប្រសិនបើ (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                ត្រឡប់ AVERROR(EINVAL);

            ប្រសិនបើ (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    ប្រសិនបើ (highest_ambi < 0)
        ត្រឡប់ AVERROR(EINVAL);

    order = floor(sqrt(highest_ambi));
    /* incomplete order - some harmonics are missing */
    ប្រសិនបើ ((order + 1) * (order + 1) != highest_ambi + 1)
        ត្រឡប់ AVERROR(EINVAL);

    ត្រឡប់ order;
}

static ga_nanaa AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    ចំនួនគត់ has_known_channel = 0;
    ចំនួនគត់ order;

    ប្រសិនបើ (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ត្រឡប់ channel_layout->order;

    ប្រសិនបើ (has_channel_names(channel_layout))
        ត្រឡប់ AV_CHANNEL_ORDER_CUSTOM;

    សម្រាប់ (ចំនួនគត់ i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        ប្រសិនបើ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    ប្រសិនបើ (!has_known_channel)
        ត្រឡប់ AV_CHANNEL_ORDER_UNSPEC;

    ប្រសិនបើ (masked_description(channel_layout, 0) > 0)
        ត្រឡប់ AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    ប្រសិនបើ (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
        ត្រឡប់ AV_CHANNEL_ORDER_AMBISONIC;

    ត្រឡប់ AV_CHANNEL_ORDER_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
static ចំនួនគត់ try_describe_ambisonic(AVBPrint *bp, const AVChannelLayout *channel_layout)
{
    ចំនួនគត់ nb_ambi_channels;
    ចំនួនគត់ order = av_channel_layout_ambisonic_order(channel_layout);
    ប្រសិនបើ (order < 0)
        ត្រឡប់ order;

    av_bprintf(bp, "ambisonic %d", order);

    /* extra channels present */
    nb_ambi_channels = (order + 1) * (order + 1);
    ប្រសិនបើ (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        ប្រសិនបើ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC) {
            extra.order       = AV_CHANNEL_ORDER_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.mask);
            extra.u.mask      = channel_layout->u.mask;
        } បើមិនដូច្នេះ {
            int64_t mask;
            ប្រសិនបើ (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.order       = AV_CHANNEL_ORDER_NATIVE;
                extra.nb_channels = av_popcount64(mask);
                extra.u.mask      = mask;
            } បើមិនដូច្នេះ {
                extra.order       = AV_CHANNEL_ORDER_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    ត្រឡប់ 0;
}

ចំនួនគត់ av_channel_layout_describe_bprint(const AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    ចំនួនគត់ i;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        សម្រាប់ (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            ប្រសិនបើ (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                ត្រឡប់ 0;
            }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        ប្រសិនបើ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            ចំនួនគត់ res = try_describe_ambisonic(bp, channel_layout);
            ប្រសិនបើ (res >= 0)
                ត្រឡប់ 0;
            ប្រសិនបើ (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                ត្រឡប់ av_channel_layout_describe_bprint(&native, bp);
            }
        }
        ប្រសិនបើ (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        សម្រាប់ (i = 0; i < channel_layout->nb_channels; i++) {
            ga_nanaa AVChannel ch = av_channel_layout_channel_from_index(channel_layout, i);

            ប្រសិនបើ (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            ប្រសិនបើ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        ប្រសិនបើ (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            ត្រឡប់ 0;
        }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        ត្រឡប់ 0;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        ត្រឡប់ try_describe_ambisonic(bp, channel_layout);
    default:
        ត្រឡប់ AVERROR(EINVAL);
    }
}

ចំនួនគត់ av_channel_layout_describe(const AVChannelLayout *channel_layout,
                               var_na *buf, size_t buf_size)
{
    AVBPrint bp;
    ចំនួនគត់ ret;

    ប្រសិនបើ (!buf && buf_size)
        ត្រឡប់ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;

    ប្រសិនបើ (bp.len >= INT_MAX)
        ត្រឡប់ AVERROR(ERANGE);
    ត្រឡប់ bp.len + 1;
}

ga_nanaa AVChannel
av_channel_layout_channel_from_index(const AVChannelLayout *channel_layout,
                                     unsigned ចំនួនគត់ idx)
{
    ចំនួនគត់ i;

    ប្រសិនបើ (idx >= channel_layout->nb_channels)
        ត្រឡប់ AV_CHAN_NONE;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        ត្រឡប់ channel_layout->u.map[idx].id;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC: {
        ចំនួនគត់ ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        ប្រសិនបើ (idx < ambi_channels)
            ត្រឡប់ AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        សម្រាប់ (i = 0; i < 64; i++) {
            ប្រសិនបើ ((1ULL << i) & channel_layout->u.mask && !idx--)
                ត្រឡប់ i;
        }
        av_fallthrough;
    default:
        ត្រឡប់ AV_CHAN_NONE;
    }
}

ga_nanaa AVChannel
av_channel_layout_channel_from_string(const AVChannelLayout *channel_layout,
                                      const var_na *str)
{
    ចំនួនគត់ index = av_channel_layout_index_from_string(channel_layout, str);

    ប្រសិនបើ (index < 0)
        ត្រឡប់ AV_CHAN_NONE;

    ត្រឡប់ av_channel_layout_channel_from_index(channel_layout, index);
}

ចំនួនគត់ av_channel_layout_index_from_channel(const AVChannelLayout *channel_layout,
                                         ga_nanaa AVChannel channel)
{
    ចំនួនគត់ i;

    ប្រសិនបើ (channel == AV_CHAN_NONE)
        ត្រឡប់ AVERROR(EINVAL);

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        សម្រាប់ (i = 0; i < channel_layout->nb_channels; i++)
            ប្រសិនបើ (channel_layout->u.map[i].id == channel)
                ត្រឡប់ i;
        ត្រឡប់ AVERROR(EINVAL);
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
    pak_sa AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        ចំនួនគត់ ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        ប្រសិនបើ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            ប្រសិនបើ (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                ត្រឡប់ AVERROR(EINVAL);
            ត្រឡប់ channel - AV_CHAN_AMBISONIC_BASE;
        }
        ប្រសិនបើ ((unsigned)channel > 63 || !(mask & (1ULL << channel)))
            ត្រឡប់ AVERROR(EINVAL);
        mask &= (1ULL << channel) - 1;
        ត្រឡប់ av_popcount64(mask) + ambi_channels;
        }
    default:
        ត្រឡប់ AVERROR(EINVAL);
    }
}

ចំនួនគត់ av_channel_layout_index_from_string(const AVChannelLayout *channel_layout,
                                        const var_na *str)
{
    const var_na *chname;
    ga_nanaa AVChannel ch = AV_CHAN_NONE;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        chname = strstr(str, "@");
        ប្រសិនបើ (chname) {
            var_na buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(parimaa_na(buf), chname - str));
            ប្រសិនបើ (!*chname)
                chname = NULL;
            ch = av_channel_from_string(buf);
            ប្រសិនបើ (ch == AV_CHAN_NONE && *buf)
                ត្រឡប់ AVERROR(EINVAL);
        }
        សម្រាប់ (ចំនួនគត់ i = 0; chname && i < channel_layout->nb_channels; i++) {
            ប្រសិនបើ (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                ត្រឡប់ i;
        }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        ប្រសិនបើ (ch == AV_CHAN_NONE)
            ត្រឡប់ AVERROR(EINVAL);
        ត្រឡប់ av_channel_layout_index_from_channel(channel_layout, ch);
    }

    ត្រឡប់ AVERROR(EINVAL);
}

ចំនួនគត់ av_channel_layout_check(const AVChannelLayout *channel_layout)
{
    ប្រសិនបើ (channel_layout->nb_channels <= 0)
        ត្រឡប់ 0;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        ត្រឡប់ av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        ប្រសិនបើ (!channel_layout->u.map)
            ត្រឡប់ 0;
        សម្រាប់ (ចំនួនគត់ i = 0; i < channel_layout->nb_channels; i++) {
            ប្រសិនបើ (channel_layout->u.map[i].id == AV_CHAN_NONE)
                ត្រឡប់ 0;
        }
        ត្រឡប់ 1;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        ត្រឡប់ av_popcount64(channel_layout->u.mask) < channel_layout->nb_channels;
    pak_sa AV_CHANNEL_ORDER_UNSPEC:
        ត្រឡប់ 1;
    default:
        ត្រឡប់ 0;
    }
}

ចំនួនគត់ av_channel_layout_compare(const AVChannelLayout *chl, const AVChannelLayout *chl1)
{
    ចំនួនគត់ i;

    /* different channel counts -> not equal */
    ប្រសិនបើ (chl->nb_channels != chl1->nb_channels)
        ត្រឡប់ 1;

    /* if only one is unspecified -> not equal */
    ប្រសិនបើ ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        ត្រឡប់ 1;
    /* both are unspecified -> equal */
    បើមិនដូច្នេះ ប្រសិនបើ (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        ត្រឡប់ 0;

    /* can compare masks directly */
    ប្រសិនបើ ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        ត្រឡប់ chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    សម្រាប់ (i = 0; i < chl->nb_channels; i++)
        ប្រសិនបើ (av_channel_layout_channel_from_index(chl,  i) !=
            av_channel_layout_channel_from_index(chl1, i))
            ត្រឡប់ 1;
    ត្រឡប់ 0;
}

void av_channel_layout_default(AVChannelLayout *ch_layout, ចំនួនគត់ nb_channels)
{
    ចំនួនគត់ i;
    សម្រាប់ (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        ប្រសិនបើ (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            ត្រឡប់;
        }

    ch_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

const AVChannelLayout *av_channel_layout_standard(void **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    const AVChannelLayout *ch_layout = NULL;

    ប្រសិនបើ (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (void*)(i + 1);
    }

    ត្រឡប់ ch_layout;
}

uint64_t av_channel_layout_subset(const AVChannelLayout *channel_layout,
                                  uint64_t mask)
{
    uint64_t ret = 0;
    ចំនួនគត់ i;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_NATIVE:
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        ត្រឡប់ channel_layout->u.mask & mask;
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        សម្រាប់ (i = 0; i < 64; i++)
            ប្រសិនបើ (mask & (1ULL << i) && av_channel_layout_index_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        bha_nga;
    }

    ត្រឡប់ ret;
}

ចំនួនគត់ av_channel_layout_retype(AVChannelLayout *channel_layout, ga_nanaa AVChannelOrder order, ចំនួនគត់ flags)
{
    ចំនួនគត់ allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    ចំនួនគត់ lossy;

    ប្រសិនបើ (!av_channel_layout_check(channel_layout))
        ត្រឡប់ AVERROR(EINVAL);

    ប្រសិនបើ (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    ប្រសិនបើ (channel_layout->order == order)
        ត្រឡប់ 0;

    switch (order) {
    pak_sa AV_CHANNEL_ORDER_UNSPEC: {
        ចំនួនគត់ nb_channels = channel_layout->nb_channels;
        ប្រសិនបើ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            សម្រាប់ (ចំនួនគត់ i = 0; i < nb_channels; i++) {
                ប្រសិនបើ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    bha_nga;
                }
            }
        } បើមិនដូច្នេះ {
            lossy = 1;
        }
        ប្រសិនបើ (!lossy || allow_lossy) {
            void *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            ត្រឡប់ lossy;
        }
        ត្រឡប់ AVERROR(ENOSYS);
        }
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        ប្រសិនបើ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            ប្រសិនបើ (mask < 0)
                ត្រឡប់ AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            ប្រសិនបើ (!lossy || allow_lossy) {
                void *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_mask(channel_layout, mask);
                channel_layout->opaque = opaque;
                ត្រឡប់ lossy;
            }
        }
        ត្រឡប់ AVERROR(ENOSYS);
    pak_sa AV_CHANNEL_ORDER_CUSTOM: {
        AVChannelLayout custom = { 0 };
        ចំនួនគត់ ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        void *opaque = channel_layout->opaque;
        ប្រសិនបើ (ret < 0)
            ត្រឡប់ ret;
        ប្រសិនបើ (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            សម្រាប់ (ចំនួនគត់ i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_index(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        ត្រឡប់ 0;
        }
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        ប្រសិនបើ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            ចំនួនគត់ nb_channels = channel_layout->nb_channels;
            ចំនួនគត់ amb_order = av_channel_layout_ambisonic_order(channel_layout);
            ប្រសិនបើ (amb_order < 0)
                ត្រឡប់ AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            ប្រសិនបើ (mask < 0)
                ត្រឡប់ AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            ប្រសិនបើ (!lossy || allow_lossy) {
                void *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.mask      = mask;
                channel_layout->opaque      = opaque;
                ត្រឡប់ lossy;
            }
        }
        ត្រឡប់ AVERROR(ENOSYS);
    default:
        ត្រឡប់ AVERROR(EINVAL);
    }
}
