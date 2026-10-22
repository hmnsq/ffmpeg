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

struct channel_name {
    const char *name;
    const char *description;
};

static const struct channel_name channel_names[] = {
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

void av_channel_name_bprint(AVBPrint *bp, enum AVChannel channel_id)
{
    якщо (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_BASE);
    інакше якщо ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].name)
        av_bprintf(bp, "%s", channel_names[channel_id].name);
    інакше якщо (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    інакше якщо (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    інакше якщо (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "UNSD");
    інакше
        av_bprintf(bp, "USR%d", channel_id);
}

ціле av_channel_name(char *buf, size_t buf_size, enum AVChannel channel_id)
{
    AVBPrint bp;

    якщо (!buf && buf_size)
        повернути AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_name_bprint(&bp, channel_id);

    якщо (bp.len >= INT_MAX)
        повернути AVERROR(ERANGE);
    повернути bp.len + 1;
}

void av_channel_description_bprint(AVBPrint *bp, enum AVChannel channel_id)
{
    якщо (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_BASE);
    інакше якщо ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].description)
        av_bprintf(bp, "%s", channel_names[channel_id].description);
    інакше якщо (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    інакше якщо (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    інакше якщо (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "unused");
    інакше
        av_bprintf(bp, "user %d", channel_id);
}

ціле av_channel_description(char *buf, size_t buf_size, enum AVChannel channel_id)
{
    AVBPrint bp;

    якщо (!buf && buf_size)
        повернути AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_description_bprint(&bp, channel_id);

    якщо (bp.len >= INT_MAX)
        повернути AVERROR(ERANGE);
    повернути bp.len + 1;
}

enum AVChannel av_channel_from_string(const char *str)
{
    ціле i;
    char *endptr = (char *)str;
    enum AVChannel id = AV_CHAN_NONE;

    якщо (!strncmp(str, "AMBI", 4)) {
        i = strtol(str + 4, NULL, 0);
        якщо (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            повернути AV_CHAN_NONE;
        повернути AV_CHAN_AMBISONIC_BASE + i;
    }

    для (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        якщо (channel_names[i].name && !strcmp(str, channel_names[i].name))
            повернути i;
    }
    якщо (!strcmp(str, "UNK"))
        повернути AV_CHAN_UNKNOWN;
    якщо (!strcmp(str, "UNSD"))
        повернути AV_CHAN_UNUSED;

    якщо (!strncmp(str, "USR", 3)) {
        const char *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    якщо (id >= 0 && !*endptr)
        повернути id;

    повернути AV_CHAN_NONE;
}

struct channel_layout_name {
    const char *name;
    AVChannelLayout layout;
};

static const struct channel_layout_name channel_layout_map[] = {
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

ціле av_channel_layout_custom_init(AVChannelLayout *channel_layout, ціле nb_channels)
{
    AVChannelCustom *map;

    якщо (nb_channels <= 0)
        повернути AVERROR(EINVAL);

    map = av_calloc(nb_channels, sizeof(*channel_layout->u.map));
    якщо (!map)
        повернути AVERROR(ENOMEM);
    для (ціле i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->order       = AV_CHANNEL_ORDER_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    повернути 0;
}

ціле av_channel_layout_from_mask(AVChannelLayout *channel_layout,
                                uint64_t mask)
{
    якщо (!mask)
        повернути AVERROR(EINVAL);

    channel_layout->order       = AV_CHANNEL_ORDER_NATIVE;
    channel_layout->nb_channels = av_popcount64(mask);
    channel_layout->u.mask      = mask;

    повернути 0;
}

static ціле parse_channel_list(AVChannelLayout *ch_layout, const char *str)
{
    ціле ret;
    ціле nb_channels = 0;
    AVChannelCustom *map = NULL;
    AVChannelCustom custom = {0};

    поки (*str) {
        char *channel, *chname;
        ret = av_opt_get_key_value(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_KEY, &channel, &chname);
        якщо (ret < 0) {
            av_freep(&map);
            повернути ret;
        }
        якщо (*str)
            str++; // skip separator
        якщо (!channel) {
            channel = chname;
            chname = NULL;
        }
        av_strlcpy(custom.name, chname ? chname : "", sizeof(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        якщо (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            повернути AVERROR(EINVAL);
        }

        av_dynarray2_add((void **)&map, &nb_channels, sizeof(custom), (void *)&custom);
        якщо (!map)
            повернути AVERROR(ENOMEM);
    }

    якщо (!nb_channels)
        повернути AVERROR(EINVAL);

    ch_layout->order = AV_CHANNEL_ORDER_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    повернути 0;
}

ціле av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  const char *str)
{
    ціле i, matches, ret;
    ціле channels = 0, nb_channels = 0;
    char *chlist, *end;
    uint64_t mask = 0;

    /* channel layout names */
    для (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        якщо (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            повернути 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, sizeof(*channel_layout));

    /* ambisonic */
    якщо (!strncmp(str, "ambisonic ", 10)) {
        const char *p = str + 10;
        char *endptr;
        AVChannelLayout extra = {0};
        ціле order;

        order = strtol(p, &endptr, 0);
        якщо (order < 0 || order + 1  > INT_MAX / (order + 1) ||
            (*endptr && *endptr != '+'))
            повернути AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        якщо (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            якщо (ret < 0)
                повернути ret;
            якщо (extra.nb_channels >= INT_MAX - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                повернути AVERROR(EINVAL);
            }

            якщо (extra.order == AV_CHANNEL_ORDER_NATIVE) {
                channel_layout->u.mask = extra.u.mask;
            } інакше {
                channel_layout->order = AV_CHANNEL_ORDER_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              sizeof(*channel_layout->u.map));
                якщо (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    повернути AVERROR(ENOMEM);
                }

                для (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                для (i = 0; i < extra.nb_channels; i++) {
                    enum AVChannel ch = av_channel_layout_channel_from_index(&extra, i);
                    якщо (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        повернути AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    якщо (extra.order == AV_CHANNEL_ORDER_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   sizeof(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        повернути 0;
    }

    chlist = av_strdup(str);
    якщо (!chlist)
        повернути AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    якщо (ret < 0 && ret != AVERROR(EINVAL))
        повернути ret;

    якщо (ret >= 0) {
        const char *end_par = strchr(str, ')');
        якщо (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            повернути AVERROR(EINVAL);
        }
        повернути 0;
    }

    errno = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    якщо (!errno && !*end && !strchr(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        повернути 0;
    }

    errno = 0;
    channels = strtol(str, &end, 10);

    /* number of channels */
    якщо (!errno && !strcmp(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        якщо (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            повернути 0;
    }

    /* number of unordered channels */
    якщо (!errno && (!strcmp(end, "C") || !strcmp(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        повернути 0;
    }

    повернути AVERROR(EINVAL);
}

void av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    якщо (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, sizeof(*channel_layout));
}

ціле av_channel_layout_copy(AVChannelLayout *dst, const AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    якщо (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, sizeof(*dst->u.map));
        якщо (!dst->u.map)
            повернути AVERROR(ENOMEM);
        memcpy(dst->u.map, src->u.map, src->nb_channels * sizeof(*src->u.map));
    }
    повернути 0;
}

static int64_t masked_description(const AVChannelLayout *channel_layout, ціле start_channel)
{
    uint64_t mask = 0;
    для (ціле i = start_channel; i < channel_layout->nb_channels; i++) {
        enum AVChannel ch = channel_layout->u.map[i].id;
        якщо (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        інакше
            повернути AVERROR(EINVAL);
    }
    повернути mask;
}

static ціле has_channel_names(const AVChannelLayout *channel_layout)
{
    якщо (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        повернути 0;
    для (ціле i = 0; i < channel_layout->nb_channels; i++)
        якщо (channel_layout->u.map[i].name[0])
            повернути 1;
    повернути 0;
}

ціле av_channel_layout_ambisonic_order(const AVChannelLayout *channel_layout)
{
    ціле i, highest_ambi, order;

    якщо (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        повернути AVERROR(EINVAL);

    highest_ambi = -1;
    якщо (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    інакше {
        const AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        для (i = 0; i < channel_layout->nb_channels; i++) {
            ціле is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            якщо (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                повернути AVERROR(EINVAL);

            /* non-default ordering */
            якщо (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                повернути AVERROR(EINVAL);

            якщо (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    якщо (highest_ambi < 0)
        повернути AVERROR(EINVAL);

    order = floor(sqrt(highest_ambi));
    /* incomplete order - some harmonics are missing */
    якщо ((order + 1) * (order + 1) != highest_ambi + 1)
        повернути AVERROR(EINVAL);

    повернути order;
}

static enum AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    ціле has_known_channel = 0;
    ціле order;

    якщо (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        повернути channel_layout->order;

    якщо (has_channel_names(channel_layout))
        повернути AV_CHANNEL_ORDER_CUSTOM;

    для (ціле i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        якщо (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    якщо (!has_known_channel)
        повернути AV_CHANNEL_ORDER_UNSPEC;

    якщо (masked_description(channel_layout, 0) > 0)
        повернути AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    якщо (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
        повернути AV_CHANNEL_ORDER_AMBISONIC;

    повернути AV_CHANNEL_ORDER_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
static ціле try_describe_ambisonic(AVBPrint *bp, const AVChannelLayout *channel_layout)
{
    ціле nb_ambi_channels;
    ціле order = av_channel_layout_ambisonic_order(channel_layout);
    якщо (order < 0)
        повернути order;

    av_bprintf(bp, "ambisonic %d", order);

    /* extra channels present */
    nb_ambi_channels = (order + 1) * (order + 1);
    якщо (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        якщо (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC) {
            extra.order       = AV_CHANNEL_ORDER_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.mask);
            extra.u.mask      = channel_layout->u.mask;
        } інакше {
            int64_t mask;
            якщо (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.order       = AV_CHANNEL_ORDER_NATIVE;
                extra.nb_channels = av_popcount64(mask);
                extra.u.mask      = mask;
            } інакше {
                extra.order       = AV_CHANNEL_ORDER_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    повернути 0;
}

ціле av_channel_layout_describe_bprint(const AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    ціле i;

    switch (channel_layout->order) {
    case AV_CHANNEL_ORDER_NATIVE:
        для (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            якщо (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                повернути 0;
            }
        av_fallthrough;
    case AV_CHANNEL_ORDER_CUSTOM:
        якщо (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            ціле res = try_describe_ambisonic(bp, channel_layout);
            якщо (res >= 0)
                повернути 0;
            якщо (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                повернути av_channel_layout_describe_bprint(&native, bp);
            }
        }
        якщо (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        для (i = 0; i < channel_layout->nb_channels; i++) {
            enum AVChannel ch = av_channel_layout_channel_from_index(channel_layout, i);

            якщо (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            якщо (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        якщо (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            повернути 0;
        }
        av_fallthrough;
    case AV_CHANNEL_ORDER_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        повернути 0;
    case AV_CHANNEL_ORDER_AMBISONIC:
        повернути try_describe_ambisonic(bp, channel_layout);
    default:
        повернути AVERROR(EINVAL);
    }
}

ціле av_channel_layout_describe(const AVChannelLayout *channel_layout,
                               char *buf, size_t buf_size)
{
    AVBPrint bp;
    ціле ret;

    якщо (!buf && buf_size)
        повернути AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    якщо (ret < 0)
        повернути ret;

    якщо (bp.len >= INT_MAX)
        повернути AVERROR(ERANGE);
    повернути bp.len + 1;
}

enum AVChannel
av_channel_layout_channel_from_index(const AVChannelLayout *channel_layout,
                                     unsigned ціле idx)
{
    ціле i;

    якщо (idx >= channel_layout->nb_channels)
        повернути AV_CHAN_NONE;

    switch (channel_layout->order) {
    case AV_CHANNEL_ORDER_CUSTOM:
        повернути channel_layout->u.map[idx].id;
    case AV_CHANNEL_ORDER_AMBISONIC: {
        ціле ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        якщо (idx < ambi_channels)
            повернути AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    case AV_CHANNEL_ORDER_NATIVE:
        для (i = 0; i < 64; i++) {
            якщо ((1ULL << i) & channel_layout->u.mask && !idx--)
                повернути i;
        }
        av_fallthrough;
    default:
        повернути AV_CHAN_NONE;
    }
}

enum AVChannel
av_channel_layout_channel_from_string(const AVChannelLayout *channel_layout,
                                      const char *str)
{
    ціле index = av_channel_layout_index_from_string(channel_layout, str);

    якщо (index < 0)
        повернути AV_CHAN_NONE;

    повернути av_channel_layout_channel_from_index(channel_layout, index);
}

ціле av_channel_layout_index_from_channel(const AVChannelLayout *channel_layout,
                                         enum AVChannel channel)
{
    ціле i;

    якщо (channel == AV_CHAN_NONE)
        повернути AVERROR(EINVAL);

    switch (channel_layout->order) {
    case AV_CHANNEL_ORDER_CUSTOM:
        для (i = 0; i < channel_layout->nb_channels; i++)
            якщо (channel_layout->u.map[i].id == channel)
                повернути i;
        повернути AVERROR(EINVAL);
    case AV_CHANNEL_ORDER_AMBISONIC:
    case AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        ціле ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        якщо (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            якщо (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                повернути AVERROR(EINVAL);
            повернути channel - AV_CHAN_AMBISONIC_BASE;
        }
        якщо ((unsigned)channel > 63 || !(mask & (1ULL << channel)))
            повернути AVERROR(EINVAL);
        mask &= (1ULL << channel) - 1;
        повернути av_popcount64(mask) + ambi_channels;
        }
    default:
        повернути AVERROR(EINVAL);
    }
}

ціле av_channel_layout_index_from_string(const AVChannelLayout *channel_layout,
                                        const char *str)
{
    const char *chname;
    enum AVChannel ch = AV_CHAN_NONE;

    switch (channel_layout->order) {
    case AV_CHANNEL_ORDER_CUSTOM:
        chname = strstr(str, "@");
        якщо (chname) {
            char buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(sizeof(buf), chname - str));
            якщо (!*chname)
                chname = NULL;
            ch = av_channel_from_string(buf);
            якщо (ch == AV_CHAN_NONE && *buf)
                повернути AVERROR(EINVAL);
        }
        для (ціле i = 0; chname && i < channel_layout->nb_channels; i++) {
            якщо (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                повернути i;
        }
        av_fallthrough;
    case AV_CHANNEL_ORDER_AMBISONIC:
    case AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        якщо (ch == AV_CHAN_NONE)
            повернути AVERROR(EINVAL);
        повернути av_channel_layout_index_from_channel(channel_layout, ch);
    }

    повернути AVERROR(EINVAL);
}

ціле av_channel_layout_check(const AVChannelLayout *channel_layout)
{
    якщо (channel_layout->nb_channels <= 0)
        повернути 0;

    switch (channel_layout->order) {
    case AV_CHANNEL_ORDER_NATIVE:
        повернути av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    case AV_CHANNEL_ORDER_CUSTOM:
        якщо (!channel_layout->u.map)
            повернути 0;
        для (ціле i = 0; i < channel_layout->nb_channels; i++) {
            якщо (channel_layout->u.map[i].id == AV_CHAN_NONE)
                повернути 0;
        }
        повернути 1;
    case AV_CHANNEL_ORDER_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        повернути av_popcount64(channel_layout->u.mask) < channel_layout->nb_channels;
    case AV_CHANNEL_ORDER_UNSPEC:
        повернути 1;
    default:
        повернути 0;
    }
}

ціле av_channel_layout_compare(const AVChannelLayout *chl, const AVChannelLayout *chl1)
{
    ціле i;

    /* different channel counts -> not equal */
    якщо (chl->nb_channels != chl1->nb_channels)
        повернути 1;

    /* if only one is unspecified -> not equal */
    якщо ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        повернути 1;
    /* both are unspecified -> equal */
    інакше якщо (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        повернути 0;

    /* can compare masks directly */
    якщо ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        повернути chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    для (i = 0; i < chl->nb_channels; i++)
        якщо (av_channel_layout_channel_from_index(chl,  i) !=
            av_channel_layout_channel_from_index(chl1, i))
            повернути 1;
    повернути 0;
}

void av_channel_layout_default(AVChannelLayout *ch_layout, ціле nb_channels)
{
    ціле i;
    для (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        якщо (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            повернути;
        }

    ch_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

const AVChannelLayout *av_channel_layout_standard(void **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    const AVChannelLayout *ch_layout = NULL;

    якщо (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (void*)(i + 1);
    }

    повернути ch_layout;
}

uint64_t av_channel_layout_subset(const AVChannelLayout *channel_layout,
                                  uint64_t mask)
{
    uint64_t ret = 0;
    ціле i;

    switch (channel_layout->order) {
    case AV_CHANNEL_ORDER_NATIVE:
    case AV_CHANNEL_ORDER_AMBISONIC:
        повернути channel_layout->u.mask & mask;
    case AV_CHANNEL_ORDER_CUSTOM:
        для (i = 0; i < 64; i++)
            якщо (mask & (1ULL << i) && av_channel_layout_index_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        break;
    }

    повернути ret;
}

ціле av_channel_layout_retype(AVChannelLayout *channel_layout, enum AVChannelOrder order, ціле flags)
{
    ціле allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    ціле lossy;

    якщо (!av_channel_layout_check(channel_layout))
        повернути AVERROR(EINVAL);

    якщо (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    якщо (channel_layout->order == order)
        повернути 0;

    switch (order) {
    case AV_CHANNEL_ORDER_UNSPEC: {
        ціле nb_channels = channel_layout->nb_channels;
        якщо (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            для (ціле i = 0; i < nb_channels; i++) {
                якщо (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    break;
                }
            }
        } інакше {
            lossy = 1;
        }
        якщо (!lossy || allow_lossy) {
            void *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            повернути lossy;
        }
        повернути AVERROR(ENOSYS);
        }
    case AV_CHANNEL_ORDER_NATIVE:
        якщо (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            якщо (mask < 0)
                повернути AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            якщо (!lossy || allow_lossy) {
                void *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_mask(channel_layout, mask);
                channel_layout->opaque = opaque;
                повернути lossy;
            }
        }
        повернути AVERROR(ENOSYS);
    case AV_CHANNEL_ORDER_CUSTOM: {
        AVChannelLayout custom = { 0 };
        ціле ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        void *opaque = channel_layout->opaque;
        якщо (ret < 0)
            повернути ret;
        якщо (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            для (ціле i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_index(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        повернути 0;
        }
    case AV_CHANNEL_ORDER_AMBISONIC:
        якщо (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            ціле nb_channels = channel_layout->nb_channels;
            ціле amb_order = av_channel_layout_ambisonic_order(channel_layout);
            якщо (amb_order < 0)
                повернути AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            якщо (mask < 0)
                повернути AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            якщо (!lossy || allow_lossy) {
                void *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.mask      = mask;
                channel_layout->opaque      = opaque;
                повернути lossy;
            }
        }
        повернути AVERROR(ENOSYS);
    default:
        повернути AVERROR(EINVAL);
    }
}
