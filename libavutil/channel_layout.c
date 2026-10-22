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
    အကယ်၍ (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_BASE);
    မဟုတ်ပါက အကယ်၍ ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].name)
        av_bprintf(bp, "%s", channel_names[channel_id].name);
    မဟုတ်ပါက အကယ်၍ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    မဟုတ်ပါက အကယ်၍ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    မဟုတ်ပါက အကယ်၍ (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "UNSD");
    မဟုတ်ပါက
        av_bprintf(bp, "USR%d", channel_id);
}

ကိန်းပြည့် av_channel_name(var_na *buf, size_t buf_size, ga_nanaa AVChannel channel_id)
{
    AVBPrint bp;

    အကယ်၍ (!buf && buf_size)
        ပြန်ပေး AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_name_bprint(&bp, channel_id);

    အကယ်၍ (bp.len >= INT_MAX)
        ပြန်ပေး AVERROR(ERANGE);
    ပြန်ပေး bp.len + 1;
}

void av_channel_description_bprint(AVBPrint *bp, ga_nanaa AVChannel channel_id)
{
    အကယ်၍ (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_BASE);
    မဟုတ်ပါက အကယ်၍ ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].description)
        av_bprintf(bp, "%s", channel_names[channel_id].description);
    မဟုတ်ပါက အကယ်၍ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    မဟုတ်ပါက အကယ်၍ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    မဟုတ်ပါက အကယ်၍ (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "unused");
    မဟုတ်ပါက
        av_bprintf(bp, "user %d", channel_id);
}

ကိန်းပြည့် av_channel_description(var_na *buf, size_t buf_size, ga_nanaa AVChannel channel_id)
{
    AVBPrint bp;

    အကယ်၍ (!buf && buf_size)
        ပြန်ပေး AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_description_bprint(&bp, channel_id);

    အကယ်၍ (bp.len >= INT_MAX)
        ပြန်ပေး AVERROR(ERANGE);
    ပြန်ပေး bp.len + 1;
}

ga_nanaa AVChannel av_channel_from_string(const var_na *str)
{
    ကိန်းပြည့် i;
    var_na *endptr = (var_na *)str;
    ga_nanaa AVChannel id = AV_CHAN_NONE;

    အကယ်၍ (!strncmp(str, "AMBI", 4)) {
        i = strtol(str + 4, NULL, 0);
        အကယ်၍ (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            ပြန်ပေး AV_CHAN_NONE;
        ပြန်ပေး AV_CHAN_AMBISONIC_BASE + i;
    }

    အတွက် (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        အကယ်၍ (channel_names[i].name && !strcmp(str, channel_names[i].name))
            ပြန်ပေး i;
    }
    အကယ်၍ (!strcmp(str, "UNK"))
        ပြန်ပေး AV_CHAN_UNKNOWN;
    အကယ်၍ (!strcmp(str, "UNSD"))
        ပြန်ပေး AV_CHAN_UNUSED;

    အကယ်၍ (!strncmp(str, "USR", 3)) {
        const var_na *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    အကယ်၍ (id >= 0 && !*endptr)
        ပြန်ပေး id;

    ပြန်ပေး AV_CHAN_NONE;
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

ကိန်းပြည့် av_channel_layout_custom_init(AVChannelLayout *channel_layout, ကိန်းပြည့် nb_channels)
{
    AVChannelCustom *map;

    အကယ်၍ (nb_channels <= 0)
        ပြန်ပေး AVERROR(EINVAL);

    map = av_calloc(nb_channels, parimaa_na(*channel_layout->u.map));
    အကယ်၍ (!map)
        ပြန်ပေး AVERROR(ENOMEM);
    အတွက် (ကိန်းပြည့် i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->order       = AV_CHANNEL_ORDER_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    ပြန်ပေး 0;
}

ကိန်းပြည့် av_channel_layout_from_mask(AVChannelLayout *channel_layout,
                                uint64_t mask)
{
    အကယ်၍ (!mask)
        ပြန်ပေး AVERROR(EINVAL);

    channel_layout->order       = AV_CHANNEL_ORDER_NATIVE;
    channel_layout->nb_channels = av_popcount64(mask);
    channel_layout->u.mask      = mask;

    ပြန်ပေး 0;
}

static ကိန်းပြည့် parse_channel_list(AVChannelLayout *ch_layout, const var_na *str)
{
    ကိန်းပြည့် ret;
    ကိန်းပြည့် nb_channels = 0;
    AVChannelCustom *map = NULL;
    AVChannelCustom custom = {0};

    နေစဉ် (*str) {
        var_na *channel, *chname;
        ret = av_opt_get_key_value(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_KEY, &channel, &chname);
        အကယ်၍ (ret < 0) {
            av_freep(&map);
            ပြန်ပေး ret;
        }
        အကယ်၍ (*str)
            str++; // skip separator
        အကယ်၍ (!channel) {
            channel = chname;
            chname = NULL;
        }
        av_strlcpy(custom.name, chname ? chname : "", parimaa_na(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        အကယ်၍ (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            ပြန်ပေး AVERROR(EINVAL);
        }

        av_dynarray2_add((void **)&map, &nb_channels, parimaa_na(custom), (void *)&custom);
        အကယ်၍ (!map)
            ပြန်ပေး AVERROR(ENOMEM);
    }

    အကယ်၍ (!nb_channels)
        ပြန်ပေး AVERROR(EINVAL);

    ch_layout->order = AV_CHANNEL_ORDER_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    ပြန်ပေး 0;
}

ကိန်းပြည့် av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  const var_na *str)
{
    ကိန်းပြည့် i, matches, ret;
    ကိန်းပြည့် channels = 0, nb_channels = 0;
    var_na *chlist, *end;
    uint64_t mask = 0;

    /* channel layout names */
    အတွက် (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        အကယ်၍ (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            ပြန်ပေး 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, parimaa_na(*channel_layout));

    /* ambisonic */
    အကယ်၍ (!strncmp(str, "ambisonic ", 10)) {
        const var_na *p = str + 10;
        var_na *endptr;
        AVChannelLayout extra = {0};
        ကိန်းပြည့် order;

        order = strtol(p, &endptr, 0);
        အကယ်၍ (order < 0 || order + 1  > INT_MAX / (order + 1) ||
            (*endptr && *endptr != '+'))
            ပြန်ပေး AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        အကယ်၍ (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            အကယ်၍ (ret < 0)
                ပြန်ပေး ret;
            အကယ်၍ (extra.nb_channels >= INT_MAX - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                ပြန်ပေး AVERROR(EINVAL);
            }

            အကယ်၍ (extra.order == AV_CHANNEL_ORDER_NATIVE) {
                channel_layout->u.mask = extra.u.mask;
            } မဟုတ်ပါက {
                channel_layout->order = AV_CHANNEL_ORDER_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              parimaa_na(*channel_layout->u.map));
                အကယ်၍ (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    ပြန်ပေး AVERROR(ENOMEM);
                }

                အတွက် (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                အတွက် (i = 0; i < extra.nb_channels; i++) {
                    ga_nanaa AVChannel ch = av_channel_layout_channel_from_index(&extra, i);
                    အကယ်၍ (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        ပြန်ပေး AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    အကယ်၍ (extra.order == AV_CHANNEL_ORDER_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   parimaa_na(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        ပြန်ပေး 0;
    }

    chlist = av_strdup(str);
    အကယ်၍ (!chlist)
        ပြန်ပေး AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    အကယ်၍ (ret < 0 && ret != AVERROR(EINVAL))
        ပြန်ပေး ret;

    အကယ်၍ (ret >= 0) {
        const var_na *end_par = strchr(str, ')');
        အကယ်၍ (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            ပြန်ပေး AVERROR(EINVAL);
        }
        ပြန်ပေး 0;
    }

    errno = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    အကယ်၍ (!errno && !*end && !strchr(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        ပြန်ပေး 0;
    }

    errno = 0;
    channels = strtol(str, &end, 10);

    /* number of channels */
    အကယ်၍ (!errno && !strcmp(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        အကယ်၍ (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            ပြန်ပေး 0;
    }

    /* number of unordered channels */
    အကယ်၍ (!errno && (!strcmp(end, "C") || !strcmp(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        ပြန်ပေး 0;
    }

    ပြန်ပေး AVERROR(EINVAL);
}

void av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    အကယ်၍ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, parimaa_na(*channel_layout));
}

ကိန်းပြည့် av_channel_layout_copy(AVChannelLayout *dst, const AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    အကယ်၍ (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, parimaa_na(*dst->u.map));
        အကယ်၍ (!dst->u.map)
            ပြန်ပေး AVERROR(ENOMEM);
        memcpy(dst->u.map, src->u.map, src->nb_channels * parimaa_na(*src->u.map));
    }
    ပြန်ပေး 0;
}

static int64_t masked_description(const AVChannelLayout *channel_layout, ကိန်းပြည့် start_channel)
{
    uint64_t mask = 0;
    အတွက် (ကိန်းပြည့် i = start_channel; i < channel_layout->nb_channels; i++) {
        ga_nanaa AVChannel ch = channel_layout->u.map[i].id;
        အကယ်၍ (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        မဟုတ်ပါက
            ပြန်ပေး AVERROR(EINVAL);
    }
    ပြန်ပေး mask;
}

static ကိန်းပြည့် has_channel_names(const AVChannelLayout *channel_layout)
{
    အကယ်၍ (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ပြန်ပေး 0;
    အတွက် (ကိန်းပြည့် i = 0; i < channel_layout->nb_channels; i++)
        အကယ်၍ (channel_layout->u.map[i].name[0])
            ပြန်ပေး 1;
    ပြန်ပေး 0;
}

ကိန်းပြည့် av_channel_layout_ambisonic_order(const AVChannelLayout *channel_layout)
{
    ကိန်းပြည့် i, highest_ambi, order;

    အကယ်၍ (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ပြန်ပေး AVERROR(EINVAL);

    highest_ambi = -1;
    အကယ်၍ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    မဟုတ်ပါက {
        const AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        အတွက် (i = 0; i < channel_layout->nb_channels; i++) {
            ကိန်းပြည့် is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            အကယ်၍ (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                ပြန်ပေး AVERROR(EINVAL);

            /* non-default ordering */
            အကယ်၍ (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                ပြန်ပေး AVERROR(EINVAL);

            အကယ်၍ (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    အကယ်၍ (highest_ambi < 0)
        ပြန်ပေး AVERROR(EINVAL);

    order = floor(sqrt(highest_ambi));
    /* incomplete order - some harmonics are missing */
    အကယ်၍ ((order + 1) * (order + 1) != highest_ambi + 1)
        ပြန်ပေး AVERROR(EINVAL);

    ပြန်ပေး order;
}

static ga_nanaa AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    ကိန်းပြည့် has_known_channel = 0;
    ကိန်းပြည့် order;

    အကယ်၍ (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ပြန်ပေး channel_layout->order;

    အကယ်၍ (has_channel_names(channel_layout))
        ပြန်ပေး AV_CHANNEL_ORDER_CUSTOM;

    အတွက် (ကိန်းပြည့် i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        အကယ်၍ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    အကယ်၍ (!has_known_channel)
        ပြန်ပေး AV_CHANNEL_ORDER_UNSPEC;

    အကယ်၍ (masked_description(channel_layout, 0) > 0)
        ပြန်ပေး AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    အကယ်၍ (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
        ပြန်ပေး AV_CHANNEL_ORDER_AMBISONIC;

    ပြန်ပေး AV_CHANNEL_ORDER_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
static ကိန်းပြည့် try_describe_ambisonic(AVBPrint *bp, const AVChannelLayout *channel_layout)
{
    ကိန်းပြည့် nb_ambi_channels;
    ကိန်းပြည့် order = av_channel_layout_ambisonic_order(channel_layout);
    အကယ်၍ (order < 0)
        ပြန်ပေး order;

    av_bprintf(bp, "ambisonic %d", order);

    /* extra channels present */
    nb_ambi_channels = (order + 1) * (order + 1);
    အကယ်၍ (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        အကယ်၍ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC) {
            extra.order       = AV_CHANNEL_ORDER_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.mask);
            extra.u.mask      = channel_layout->u.mask;
        } မဟုတ်ပါက {
            int64_t mask;
            အကယ်၍ (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.order       = AV_CHANNEL_ORDER_NATIVE;
                extra.nb_channels = av_popcount64(mask);
                extra.u.mask      = mask;
            } မဟုတ်ပါက {
                extra.order       = AV_CHANNEL_ORDER_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    ပြန်ပေး 0;
}

ကိန်းပြည့် av_channel_layout_describe_bprint(const AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    ကိန်းပြည့် i;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        အတွက် (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            အကယ်၍ (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                ပြန်ပေး 0;
            }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        အကယ်၍ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            ကိန်းပြည့် res = try_describe_ambisonic(bp, channel_layout);
            အကယ်၍ (res >= 0)
                ပြန်ပေး 0;
            အကယ်၍ (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                ပြန်ပေး av_channel_layout_describe_bprint(&native, bp);
            }
        }
        အကယ်၍ (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        အတွက် (i = 0; i < channel_layout->nb_channels; i++) {
            ga_nanaa AVChannel ch = av_channel_layout_channel_from_index(channel_layout, i);

            အကယ်၍ (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            အကယ်၍ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        အကယ်၍ (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            ပြန်ပေး 0;
        }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        ပြန်ပေး 0;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        ပြန်ပေး try_describe_ambisonic(bp, channel_layout);
    default:
        ပြန်ပေး AVERROR(EINVAL);
    }
}

ကိန်းပြည့် av_channel_layout_describe(const AVChannelLayout *channel_layout,
                               var_na *buf, size_t buf_size)
{
    AVBPrint bp;
    ကိန်းပြည့် ret;

    အကယ်၍ (!buf && buf_size)
        ပြန်ပေး AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    အကယ်၍ (ret < 0)
        ပြန်ပေး ret;

    အကယ်၍ (bp.len >= INT_MAX)
        ပြန်ပေး AVERROR(ERANGE);
    ပြန်ပေး bp.len + 1;
}

ga_nanaa AVChannel
av_channel_layout_channel_from_index(const AVChannelLayout *channel_layout,
                                     unsigned ကိန်းပြည့် idx)
{
    ကိန်းပြည့် i;

    အကယ်၍ (idx >= channel_layout->nb_channels)
        ပြန်ပေး AV_CHAN_NONE;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        ပြန်ပေး channel_layout->u.map[idx].id;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC: {
        ကိန်းပြည့် ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        အကယ်၍ (idx < ambi_channels)
            ပြန်ပေး AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        အတွက် (i = 0; i < 64; i++) {
            အကယ်၍ ((1ULL << i) & channel_layout->u.mask && !idx--)
                ပြန်ပေး i;
        }
        av_fallthrough;
    default:
        ပြန်ပေး AV_CHAN_NONE;
    }
}

ga_nanaa AVChannel
av_channel_layout_channel_from_string(const AVChannelLayout *channel_layout,
                                      const var_na *str)
{
    ကိန်းပြည့် index = av_channel_layout_index_from_string(channel_layout, str);

    အကယ်၍ (index < 0)
        ပြန်ပေး AV_CHAN_NONE;

    ပြန်ပေး av_channel_layout_channel_from_index(channel_layout, index);
}

ကိန်းပြည့် av_channel_layout_index_from_channel(const AVChannelLayout *channel_layout,
                                         ga_nanaa AVChannel channel)
{
    ကိန်းပြည့် i;

    အကယ်၍ (channel == AV_CHAN_NONE)
        ပြန်ပေး AVERROR(EINVAL);

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        အတွက် (i = 0; i < channel_layout->nb_channels; i++)
            အကယ်၍ (channel_layout->u.map[i].id == channel)
                ပြန်ပေး i;
        ပြန်ပေး AVERROR(EINVAL);
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
    pak_sa AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        ကိန်းပြည့် ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        အကယ်၍ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            အကယ်၍ (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                ပြန်ပေး AVERROR(EINVAL);
            ပြန်ပေး channel - AV_CHAN_AMBISONIC_BASE;
        }
        အကယ်၍ ((unsigned)channel > 63 || !(mask & (1ULL << channel)))
            ပြန်ပေး AVERROR(EINVAL);
        mask &= (1ULL << channel) - 1;
        ပြန်ပေး av_popcount64(mask) + ambi_channels;
        }
    default:
        ပြန်ပေး AVERROR(EINVAL);
    }
}

ကိန်းပြည့် av_channel_layout_index_from_string(const AVChannelLayout *channel_layout,
                                        const var_na *str)
{
    const var_na *chname;
    ga_nanaa AVChannel ch = AV_CHAN_NONE;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        chname = strstr(str, "@");
        အကယ်၍ (chname) {
            var_na buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(parimaa_na(buf), chname - str));
            အကယ်၍ (!*chname)
                chname = NULL;
            ch = av_channel_from_string(buf);
            အကယ်၍ (ch == AV_CHAN_NONE && *buf)
                ပြန်ပေး AVERROR(EINVAL);
        }
        အတွက် (ကိန်းပြည့် i = 0; chname && i < channel_layout->nb_channels; i++) {
            အကယ်၍ (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                ပြန်ပေး i;
        }
        av_fallthrough;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        အကယ်၍ (ch == AV_CHAN_NONE)
            ပြန်ပေး AVERROR(EINVAL);
        ပြန်ပေး av_channel_layout_index_from_channel(channel_layout, ch);
    }

    ပြန်ပေး AVERROR(EINVAL);
}

ကိန်းပြည့် av_channel_layout_check(const AVChannelLayout *channel_layout)
{
    အကယ်၍ (channel_layout->nb_channels <= 0)
        ပြန်ပေး 0;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        ပြန်ပေး av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        အကယ်၍ (!channel_layout->u.map)
            ပြန်ပေး 0;
        အတွက် (ကိန်းပြည့် i = 0; i < channel_layout->nb_channels; i++) {
            အကယ်၍ (channel_layout->u.map[i].id == AV_CHAN_NONE)
                ပြန်ပေး 0;
        }
        ပြန်ပေး 1;
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        ပြန်ပေး av_popcount64(channel_layout->u.mask) < channel_layout->nb_channels;
    pak_sa AV_CHANNEL_ORDER_UNSPEC:
        ပြန်ပေး 1;
    default:
        ပြန်ပေး 0;
    }
}

ကိန်းပြည့် av_channel_layout_compare(const AVChannelLayout *chl, const AVChannelLayout *chl1)
{
    ကိန်းပြည့် i;

    /* different channel counts -> not equal */
    အကယ်၍ (chl->nb_channels != chl1->nb_channels)
        ပြန်ပေး 1;

    /* if only one is unspecified -> not equal */
    အကယ်၍ ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        ပြန်ပေး 1;
    /* both are unspecified -> equal */
    မဟုတ်ပါက အကယ်၍ (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        ပြန်ပေး 0;

    /* can compare masks directly */
    အကယ်၍ ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        ပြန်ပေး chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    အတွက် (i = 0; i < chl->nb_channels; i++)
        အကယ်၍ (av_channel_layout_channel_from_index(chl,  i) !=
            av_channel_layout_channel_from_index(chl1, i))
            ပြန်ပေး 1;
    ပြန်ပေး 0;
}

void av_channel_layout_default(AVChannelLayout *ch_layout, ကိန်းပြည့် nb_channels)
{
    ကိန်းပြည့် i;
    အတွက် (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        အကယ်၍ (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            ပြန်ပေး;
        }

    ch_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

const AVChannelLayout *av_channel_layout_standard(void **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    const AVChannelLayout *ch_layout = NULL;

    အကယ်၍ (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (void*)(i + 1);
    }

    ပြန်ပေး ch_layout;
}

uint64_t av_channel_layout_subset(const AVChannelLayout *channel_layout,
                                  uint64_t mask)
{
    uint64_t ret = 0;
    ကိန်းပြည့် i;

    switch (channel_layout->order) {
    pak_sa AV_CHANNEL_ORDER_NATIVE:
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        ပြန်ပေး channel_layout->u.mask & mask;
    pak_sa AV_CHANNEL_ORDER_CUSTOM:
        အတွက် (i = 0; i < 64; i++)
            အကယ်၍ (mask & (1ULL << i) && av_channel_layout_index_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        bha_nga;
    }

    ပြန်ပေး ret;
}

ကိန်းပြည့် av_channel_layout_retype(AVChannelLayout *channel_layout, ga_nanaa AVChannelOrder order, ကိန်းပြည့် flags)
{
    ကိန်းပြည့် allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    ကိန်းပြည့် lossy;

    အကယ်၍ (!av_channel_layout_check(channel_layout))
        ပြန်ပေး AVERROR(EINVAL);

    အကယ်၍ (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    အကယ်၍ (channel_layout->order == order)
        ပြန်ပေး 0;

    switch (order) {
    pak_sa AV_CHANNEL_ORDER_UNSPEC: {
        ကိန်းပြည့် nb_channels = channel_layout->nb_channels;
        အကယ်၍ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            အတွက် (ကိန်းပြည့် i = 0; i < nb_channels; i++) {
                အကယ်၍ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    bha_nga;
                }
            }
        } မဟုတ်ပါက {
            lossy = 1;
        }
        အကယ်၍ (!lossy || allow_lossy) {
            void *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            ပြန်ပေး lossy;
        }
        ပြန်ပေး AVERROR(ENOSYS);
        }
    pak_sa AV_CHANNEL_ORDER_NATIVE:
        အကယ်၍ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            အကယ်၍ (mask < 0)
                ပြန်ပေး AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            အကယ်၍ (!lossy || allow_lossy) {
                void *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_mask(channel_layout, mask);
                channel_layout->opaque = opaque;
                ပြန်ပေး lossy;
            }
        }
        ပြန်ပေး AVERROR(ENOSYS);
    pak_sa AV_CHANNEL_ORDER_CUSTOM: {
        AVChannelLayout custom = { 0 };
        ကိန်းပြည့် ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        void *opaque = channel_layout->opaque;
        အကယ်၍ (ret < 0)
            ပြန်ပေး ret;
        အကယ်၍ (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            အတွက် (ကိန်းပြည့် i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_index(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        ပြန်ပေး 0;
        }
    pak_sa AV_CHANNEL_ORDER_AMBISONIC:
        အကယ်၍ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            ကိန်းပြည့် nb_channels = channel_layout->nb_channels;
            ကိန်းပြည့် amb_order = av_channel_layout_ambisonic_order(channel_layout);
            အကယ်၍ (amb_order < 0)
                ပြန်ပေး AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            အကယ်၍ (mask < 0)
                ပြန်ပေး AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            အကယ်၍ (!lossy || allow_lossy) {
                void *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.mask      = mask;
                channel_layout->opaque      = opaque;
                ပြန်ပေး lossy;
            }
        }
        ပြန်ပေး AVERROR(ENOSYS);
    default:
        ပြန်ပေး AVERROR(EINVAL);
    }
}
