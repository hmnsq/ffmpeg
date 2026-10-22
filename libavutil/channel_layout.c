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
    ако (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_BASE);
    иначе ако ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].name)
        av_bprintf(bp, "%s", channel_names[channel_id].name);
    иначе ако (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    иначе ако (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    иначе ако (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "UNSD");
    иначе
        av_bprintf(bp, "USR%d", channel_id);
}

цяло av_channel_name(char *buf, size_t buf_size, enum AVChannel channel_id)
{
    AVBPrint bp;

    ако (!buf && buf_size)
        върни AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_name_bprint(&bp, channel_id);

    ако (bp.len >= INT_MAX)
        върни AVERROR(ERANGE);
    върни bp.len + 1;
}

void av_channel_description_bprint(AVBPrint *bp, enum AVChannel channel_id)
{
    ако (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_BASE);
    иначе ако ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].description)
        av_bprintf(bp, "%s", channel_names[channel_id].description);
    иначе ако (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    иначе ако (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    иначе ако (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "unused");
    иначе
        av_bprintf(bp, "user %d", channel_id);
}

цяло av_channel_description(char *buf, size_t buf_size, enum AVChannel channel_id)
{
    AVBPrint bp;

    ако (!buf && buf_size)
        върни AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_description_bprint(&bp, channel_id);

    ако (bp.len >= INT_MAX)
        върни AVERROR(ERANGE);
    върни bp.len + 1;
}

enum AVChannel av_channel_from_string(const char *str)
{
    цяло i;
    char *endptr = (char *)str;
    enum AVChannel id = AV_CHAN_NONE;

    ако (!strncmp(str, "AMBI", 4)) {
        i = strtol(str + 4, NULL, 0);
        ако (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            върни AV_CHAN_NONE;
        върни AV_CHAN_AMBISONIC_BASE + i;
    }

    за (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        ако (channel_names[i].name && !strcmp(str, channel_names[i].name))
            върни i;
    }
    ако (!strcmp(str, "UNK"))
        върни AV_CHAN_UNKNOWN;
    ако (!strcmp(str, "UNSD"))
        върни AV_CHAN_UNUSED;

    ако (!strncmp(str, "USR", 3)) {
        const char *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    ако (id >= 0 && !*endptr)
        върни id;

    върни AV_CHAN_NONE;
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

цяло av_channel_layout_custom_init(AVChannelLayout *channel_layout, цяло nb_channels)
{
    AVChannelCustom *map;

    ако (nb_channels <= 0)
        върни AVERROR(EINVAL);

    map = av_calloc(nb_channels, sizeof(*channel_layout->u.map));
    ако (!map)
        върни AVERROR(ENOMEM);
    за (цяло i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->order       = AV_CHANNEL_ORDER_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    върни 0;
}

цяло av_channel_layout_from_mask(AVChannelLayout *channel_layout,
                                uint64_t mask)
{
    ако (!mask)
        върни AVERROR(EINVAL);

    channel_layout->order       = AV_CHANNEL_ORDER_NATIVE;
    channel_layout->nb_channels = av_popcount64(mask);
    channel_layout->u.mask      = mask;

    върни 0;
}

static цяло parse_channel_list(AVChannelLayout *ch_layout, const char *str)
{
    цяло ret;
    цяло nb_channels = 0;
    AVChannelCustom *map = NULL;
    AVChannelCustom custom = {0};

    докато (*str) {
        char *channel, *chname;
        ret = av_opt_get_key_value(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_KEY, &channel, &chname);
        ако (ret < 0) {
            av_freep(&map);
            върни ret;
        }
        ако (*str)
            str++; // skip separator
        ако (!channel) {
            channel = chname;
            chname = NULL;
        }
        av_strlcpy(custom.name, chname ? chname : "", sizeof(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        ако (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            върни AVERROR(EINVAL);
        }

        av_dynarray2_add((void **)&map, &nb_channels, sizeof(custom), (void *)&custom);
        ако (!map)
            върни AVERROR(ENOMEM);
    }

    ако (!nb_channels)
        върни AVERROR(EINVAL);

    ch_layout->order = AV_CHANNEL_ORDER_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    върни 0;
}

цяло av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  const char *str)
{
    цяло i, matches, ret;
    цяло channels = 0, nb_channels = 0;
    char *chlist, *end;
    uint64_t mask = 0;

    /* channel layout names */
    за (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        ако (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            върни 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, sizeof(*channel_layout));

    /* ambisonic */
    ако (!strncmp(str, "ambisonic ", 10)) {
        const char *p = str + 10;
        char *endptr;
        AVChannelLayout extra = {0};
        цяло order;

        order = strtol(p, &endptr, 0);
        ако (order < 0 || order + 1  > INT_MAX / (order + 1) ||
            (*endptr && *endptr != '+'))
            върни AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        ако (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            ако (ret < 0)
                върни ret;
            ако (extra.nb_channels >= INT_MAX - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                върни AVERROR(EINVAL);
            }

            ако (extra.order == AV_CHANNEL_ORDER_NATIVE) {
                channel_layout->u.mask = extra.u.mask;
            } иначе {
                channel_layout->order = AV_CHANNEL_ORDER_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              sizeof(*channel_layout->u.map));
                ако (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    върни AVERROR(ENOMEM);
                }

                за (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                за (i = 0; i < extra.nb_channels; i++) {
                    enum AVChannel ch = av_channel_layout_channel_from_index(&extra, i);
                    ако (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        върни AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    ако (extra.order == AV_CHANNEL_ORDER_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   sizeof(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        върни 0;
    }

    chlist = av_strdup(str);
    ако (!chlist)
        върни AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    ако (ret < 0 && ret != AVERROR(EINVAL))
        върни ret;

    ако (ret >= 0) {
        const char *end_par = strchr(str, ')');
        ако (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            върни AVERROR(EINVAL);
        }
        върни 0;
    }

    errno = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    ако (!errno && !*end && !strchr(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        върни 0;
    }

    errno = 0;
    channels = strtol(str, &end, 10);

    /* number of channels */
    ако (!errno && !strcmp(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        ако (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            върни 0;
    }

    /* number of unordered channels */
    ако (!errno && (!strcmp(end, "C") || !strcmp(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        върни 0;
    }

    върни AVERROR(EINVAL);
}

void av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    ако (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, sizeof(*channel_layout));
}

цяло av_channel_layout_copy(AVChannelLayout *dst, const AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    ако (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, sizeof(*dst->u.map));
        ако (!dst->u.map)
            върни AVERROR(ENOMEM);
        memcpy(dst->u.map, src->u.map, src->nb_channels * sizeof(*src->u.map));
    }
    върни 0;
}

static int64_t masked_description(const AVChannelLayout *channel_layout, цяло start_channel)
{
    uint64_t mask = 0;
    за (цяло i = start_channel; i < channel_layout->nb_channels; i++) {
        enum AVChannel ch = channel_layout->u.map[i].id;
        ако (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        иначе
            върни AVERROR(EINVAL);
    }
    върни mask;
}

static цяло has_channel_names(const AVChannelLayout *channel_layout)
{
    ако (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        върни 0;
    за (цяло i = 0; i < channel_layout->nb_channels; i++)
        ако (channel_layout->u.map[i].name[0])
            върни 1;
    върни 0;
}

цяло av_channel_layout_ambisonic_order(const AVChannelLayout *channel_layout)
{
    цяло i, highest_ambi, order;

    ако (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        върни AVERROR(EINVAL);

    highest_ambi = -1;
    ако (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    иначе {
        const AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        за (i = 0; i < channel_layout->nb_channels; i++) {
            цяло is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            ако (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                върни AVERROR(EINVAL);

            /* non-default ordering */
            ако (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                върни AVERROR(EINVAL);

            ако (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    ако (highest_ambi < 0)
        върни AVERROR(EINVAL);

    order = floor(sqrt(highest_ambi));
    /* incomplete order - some harmonics are missing */
    ако ((order + 1) * (order + 1) != highest_ambi + 1)
        върни AVERROR(EINVAL);

    върни order;
}

static enum AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    цяло has_known_channel = 0;
    цяло order;

    ако (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        върни channel_layout->order;

    ако (has_channel_names(channel_layout))
        върни AV_CHANNEL_ORDER_CUSTOM;

    за (цяло i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        ако (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    ако (!has_known_channel)
        върни AV_CHANNEL_ORDER_UNSPEC;

    ако (masked_description(channel_layout, 0) > 0)
        върни AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    ако (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
        върни AV_CHANNEL_ORDER_AMBISONIC;

    върни AV_CHANNEL_ORDER_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
static цяло try_describe_ambisonic(AVBPrint *bp, const AVChannelLayout *channel_layout)
{
    цяло nb_ambi_channels;
    цяло order = av_channel_layout_ambisonic_order(channel_layout);
    ако (order < 0)
        върни order;

    av_bprintf(bp, "ambisonic %d", order);

    /* extra channels present */
    nb_ambi_channels = (order + 1) * (order + 1);
    ако (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        ако (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC) {
            extra.order       = AV_CHANNEL_ORDER_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.mask);
            extra.u.mask      = channel_layout->u.mask;
        } иначе {
            int64_t mask;
            ако (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.order       = AV_CHANNEL_ORDER_NATIVE;
                extra.nb_channels = av_popcount64(mask);
                extra.u.mask      = mask;
            } иначе {
                extra.order       = AV_CHANNEL_ORDER_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    върни 0;
}

цяло av_channel_layout_describe_bprint(const AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    цяло i;

    switch (channel_layout->order) {
    case AV_CHANNEL_ORDER_NATIVE:
        за (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            ако (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                върни 0;
            }
        av_fallthrough;
    case AV_CHANNEL_ORDER_CUSTOM:
        ако (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            цяло res = try_describe_ambisonic(bp, channel_layout);
            ако (res >= 0)
                върни 0;
            ако (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                върни av_channel_layout_describe_bprint(&native, bp);
            }
        }
        ако (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        за (i = 0; i < channel_layout->nb_channels; i++) {
            enum AVChannel ch = av_channel_layout_channel_from_index(channel_layout, i);

            ако (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            ако (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        ако (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            върни 0;
        }
        av_fallthrough;
    case AV_CHANNEL_ORDER_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        върни 0;
    case AV_CHANNEL_ORDER_AMBISONIC:
        върни try_describe_ambisonic(bp, channel_layout);
    default:
        върни AVERROR(EINVAL);
    }
}

цяло av_channel_layout_describe(const AVChannelLayout *channel_layout,
                               char *buf, size_t buf_size)
{
    AVBPrint bp;
    цяло ret;

    ако (!buf && buf_size)
        върни AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    ако (ret < 0)
        върни ret;

    ако (bp.len >= INT_MAX)
        върни AVERROR(ERANGE);
    върни bp.len + 1;
}

enum AVChannel
av_channel_layout_channel_from_index(const AVChannelLayout *channel_layout,
                                     unsigned цяло idx)
{
    цяло i;

    ако (idx >= channel_layout->nb_channels)
        върни AV_CHAN_NONE;

    switch (channel_layout->order) {
    case AV_CHANNEL_ORDER_CUSTOM:
        върни channel_layout->u.map[idx].id;
    case AV_CHANNEL_ORDER_AMBISONIC: {
        цяло ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        ако (idx < ambi_channels)
            върни AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    case AV_CHANNEL_ORDER_NATIVE:
        за (i = 0; i < 64; i++) {
            ако ((1ULL << i) & channel_layout->u.mask && !idx--)
                върни i;
        }
        av_fallthrough;
    default:
        върни AV_CHAN_NONE;
    }
}

enum AVChannel
av_channel_layout_channel_from_string(const AVChannelLayout *channel_layout,
                                      const char *str)
{
    цяло index = av_channel_layout_index_from_string(channel_layout, str);

    ако (index < 0)
        върни AV_CHAN_NONE;

    върни av_channel_layout_channel_from_index(channel_layout, index);
}

цяло av_channel_layout_index_from_channel(const AVChannelLayout *channel_layout,
                                         enum AVChannel channel)
{
    цяло i;

    ако (channel == AV_CHAN_NONE)
        върни AVERROR(EINVAL);

    switch (channel_layout->order) {
    case AV_CHANNEL_ORDER_CUSTOM:
        за (i = 0; i < channel_layout->nb_channels; i++)
            ако (channel_layout->u.map[i].id == channel)
                върни i;
        върни AVERROR(EINVAL);
    case AV_CHANNEL_ORDER_AMBISONIC:
    case AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        цяло ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        ако (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            ако (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                върни AVERROR(EINVAL);
            върни channel - AV_CHAN_AMBISONIC_BASE;
        }
        ако ((unsigned)channel > 63 || !(mask & (1ULL << channel)))
            върни AVERROR(EINVAL);
        mask &= (1ULL << channel) - 1;
        върни av_popcount64(mask) + ambi_channels;
        }
    default:
        върни AVERROR(EINVAL);
    }
}

цяло av_channel_layout_index_from_string(const AVChannelLayout *channel_layout,
                                        const char *str)
{
    const char *chname;
    enum AVChannel ch = AV_CHAN_NONE;

    switch (channel_layout->order) {
    case AV_CHANNEL_ORDER_CUSTOM:
        chname = strstr(str, "@");
        ако (chname) {
            char buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(sizeof(buf), chname - str));
            ако (!*chname)
                chname = NULL;
            ch = av_channel_from_string(buf);
            ако (ch == AV_CHAN_NONE && *buf)
                върни AVERROR(EINVAL);
        }
        за (цяло i = 0; chname && i < channel_layout->nb_channels; i++) {
            ако (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                върни i;
        }
        av_fallthrough;
    case AV_CHANNEL_ORDER_AMBISONIC:
    case AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        ако (ch == AV_CHAN_NONE)
            върни AVERROR(EINVAL);
        върни av_channel_layout_index_from_channel(channel_layout, ch);
    }

    върни AVERROR(EINVAL);
}

цяло av_channel_layout_check(const AVChannelLayout *channel_layout)
{
    ако (channel_layout->nb_channels <= 0)
        върни 0;

    switch (channel_layout->order) {
    case AV_CHANNEL_ORDER_NATIVE:
        върни av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    case AV_CHANNEL_ORDER_CUSTOM:
        ако (!channel_layout->u.map)
            върни 0;
        за (цяло i = 0; i < channel_layout->nb_channels; i++) {
            ако (channel_layout->u.map[i].id == AV_CHAN_NONE)
                върни 0;
        }
        върни 1;
    case AV_CHANNEL_ORDER_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        върни av_popcount64(channel_layout->u.mask) < channel_layout->nb_channels;
    case AV_CHANNEL_ORDER_UNSPEC:
        върни 1;
    default:
        върни 0;
    }
}

цяло av_channel_layout_compare(const AVChannelLayout *chl, const AVChannelLayout *chl1)
{
    цяло i;

    /* different channel counts -> not equal */
    ако (chl->nb_channels != chl1->nb_channels)
        върни 1;

    /* if only one is unspecified -> not equal */
    ако ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        върни 1;
    /* both are unspecified -> equal */
    иначе ако (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        върни 0;

    /* can compare masks directly */
    ако ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        върни chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    за (i = 0; i < chl->nb_channels; i++)
        ако (av_channel_layout_channel_from_index(chl,  i) !=
            av_channel_layout_channel_from_index(chl1, i))
            върни 1;
    върни 0;
}

void av_channel_layout_default(AVChannelLayout *ch_layout, цяло nb_channels)
{
    цяло i;
    за (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        ако (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            върни;
        }

    ch_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

const AVChannelLayout *av_channel_layout_standard(void **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    const AVChannelLayout *ch_layout = NULL;

    ако (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (void*)(i + 1);
    }

    върни ch_layout;
}

uint64_t av_channel_layout_subset(const AVChannelLayout *channel_layout,
                                  uint64_t mask)
{
    uint64_t ret = 0;
    цяло i;

    switch (channel_layout->order) {
    case AV_CHANNEL_ORDER_NATIVE:
    case AV_CHANNEL_ORDER_AMBISONIC:
        върни channel_layout->u.mask & mask;
    case AV_CHANNEL_ORDER_CUSTOM:
        за (i = 0; i < 64; i++)
            ако (mask & (1ULL << i) && av_channel_layout_index_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        break;
    }

    върни ret;
}

цяло av_channel_layout_retype(AVChannelLayout *channel_layout, enum AVChannelOrder order, цяло flags)
{
    цяло allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    цяло lossy;

    ако (!av_channel_layout_check(channel_layout))
        върни AVERROR(EINVAL);

    ако (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    ако (channel_layout->order == order)
        върни 0;

    switch (order) {
    case AV_CHANNEL_ORDER_UNSPEC: {
        цяло nb_channels = channel_layout->nb_channels;
        ако (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            за (цяло i = 0; i < nb_channels; i++) {
                ако (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    break;
                }
            }
        } иначе {
            lossy = 1;
        }
        ако (!lossy || allow_lossy) {
            void *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            върни lossy;
        }
        върни AVERROR(ENOSYS);
        }
    case AV_CHANNEL_ORDER_NATIVE:
        ако (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            ако (mask < 0)
                върни AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            ако (!lossy || allow_lossy) {
                void *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_mask(channel_layout, mask);
                channel_layout->opaque = opaque;
                върни lossy;
            }
        }
        върни AVERROR(ENOSYS);
    case AV_CHANNEL_ORDER_CUSTOM: {
        AVChannelLayout custom = { 0 };
        цяло ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        void *opaque = channel_layout->opaque;
        ако (ret < 0)
            върни ret;
        ако (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            за (цяло i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_index(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        върни 0;
        }
    case AV_CHANNEL_ORDER_AMBISONIC:
        ако (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            цяло nb_channels = channel_layout->nb_channels;
            цяло amb_order = av_channel_layout_ambisonic_order(channel_layout);
            ако (amb_order < 0)
                върни AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            ако (mask < 0)
                върни AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            ако (!lossy || allow_lossy) {
                void *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.mask      = mask;
                channel_layout->opaque      = opaque;
                върни lossy;
            }
        }
        върни AVERROR(ENOSYS);
    default:
        върни AVERROR(EINVAL);
    }
}
