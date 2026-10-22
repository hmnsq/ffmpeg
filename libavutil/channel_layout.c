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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "channel_layout.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "bprint.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "opt.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHAN_IS_AMBI(x) ((x) >= AV_CHAN_AMBISONIC_ਅਧਾਰ &&\
                         (x) <= AV_CHAN_AMBISONIC_ਸਿਰਾ)

ਬਣਤਰ channel_name {
    ਅਚਲ ਅੱਖਰ *name;
    ਅਚਲ ਅੱਖਰ *description;
};

ਸਥਿਰ ਅਚਲ ਬਣਤਰ channel_name channel_ਨਾਂ[] = {
    [AV_CHAN_FRONT_ਖੱਬਾ           ] = { "FL",        "front left"            },
    [AV_CHAN_FRONT_ਸੱਜਾ          ] = { "FR",        "front right"           },
    [AV_CHAN_FRONT_CENTER         ] = { "FC",        "front center"          },
    [AV_CHAN_ਨੀਵਾਂ_FREQUENCY        ] = { "LFE",       "low frequency"         },
    [AV_CHAN_ਪਿੱਠ_ਖੱਬਾ            ] = { "BL",        "back left"             },
    [AV_CHAN_ਪਿੱਠ_ਸੱਜਾ           ] = { "BR",        "back right"            },
    [AV_CHAN_FRONT_ਖੱਬਾ_ਦਾ_CENTER ] = { "FLC",       "front left-of-center"  },
    [AV_CHAN_FRONT_ਸੱਜਾ_ਦਾ_CENTER] = { "FRC",       "front right-of-center" },
    [AV_CHAN_ਪਿੱਠ_CENTER          ] = { "BC",        "back center"           },
    [AV_CHAN_SIDE_ਖੱਬਾ            ] = { "SL",        "side left"             },
    [AV_CHAN_SIDE_ਸੱਜਾ           ] = { "SR",        "side right"            },
    [AV_CHAN_ਸਿਖਰ_CENTER           ] = { "TC",        "top center"            },
    [AV_CHAN_ਸਿਖਰ_FRONT_ਖੱਬਾ       ] = { "TFL",       "top front left"        },
    [AV_CHAN_ਸਿਖਰ_FRONT_CENTER     ] = { "TFC",       "top front center"      },
    [AV_CHAN_ਸਿਖਰ_FRONT_ਸੱਜਾ      ] = { "TFR",       "top front right"       },
    [AV_CHAN_ਸਿਖਰ_ਪਿੱਠ_ਖੱਬਾ        ] = { "TBL",       "top back left"         },
    [AV_CHAN_ਸਿਖਰ_ਪਿੱਠ_CENTER      ] = { "TBC",       "top back center"       },
    [AV_CHAN_ਸਿਖਰ_ਪਿੱਠ_ਸੱਜਾ       ] = { "TBR",       "top back right"        },
    [AV_CHAN_STEREO_ਖੱਬਾ          ] = { "DL",        "downmix left"          },
    [AV_CHAN_STEREO_ਸੱਜਾ         ] = { "DR",        "downmix right"         },
    [AV_CHAN_WIDE_ਖੱਬਾ            ] = { "WL",        "wide left"             },
    [AV_CHAN_WIDE_ਸੱਜਾ           ] = { "WR",        "wide right"            },
    [AV_CHAN_SURROUND_ਸਿੱਧਾ_ਖੱਬਾ ] = { "SDL",       "surround direct left"  },
    [AV_CHAN_SURROUND_ਸਿੱਧਾ_ਸੱਜਾ] = { "SDR",       "surround direct right" },
    [AV_CHAN_ਨੀਵਾਂ_FREQUENCY_2      ] = { "LFE2",      "low frequency 2"       },
    [AV_CHAN_ਸਿਖਰ_SIDE_ਖੱਬਾ        ] = { "TSL",       "top side left"         },
    [AV_CHAN_ਸਿਖਰ_SIDE_ਸੱਜਾ       ] = { "TSR",       "top side right"        },
    [AV_CHAN_BOTTOM_FRONT_CENTER  ] = { "BFC",       "bottom front center"   },
    [AV_CHAN_BOTTOM_FRONT_ਖੱਬਾ    ] = { "BFL",       "bottom front left"     },
    [AV_CHAN_BOTTOM_FRONT_ਸੱਜਾ   ] = { "BFR",       "bottom front right"    },
    [AV_CHAN_SIDE_SURROUND_ਖੱਬਾ   ] = { "SSL",       "side surround left"    },
    [AV_CHAN_SIDE_SURROUND_ਸੱਜਾ  ] = { "SSR",       "side surround right"   },
    [AV_CHAN_ਸਿਖਰ_SURROUND_ਖੱਬਾ    ] = { "TTL",       "top surround left"     },
    [AV_CHAN_ਸਿਖਰ_SURROUND_ਸੱਜਾ   ] = { "TTR",       "top surround right"    },
    [AV_CHAN_BINAURAL_ਖੱਬਾ        ] = { "BIL",       "binaural left"         },
    [AV_CHAN_BINAURAL_ਸੱਜਾ       ] = { "BIR",       "binaural right"        },
};

ਖਾਲੀ av_channel_name_bprint(AVBPrint *bp, ਗਿਣਤੀ AVChannel channel_id)
{
    ਜੇ (channel_id >= AV_CHAN_AMBISONIC_ਅਧਾਰ &&
        channel_id <= AV_CHAN_AMBISONIC_ਸਿਰਾ)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_ਅਧਾਰ);
    ਨਹੀਂਤਾਂ ਜੇ ((ਬਿਨਾਨਿਸ਼ਾਨੀ)channel_id < FF_ARRAY_ELEMS(channel_ਨਾਂ) &&
             channel_ਨਾਂ[channel_id].name)
        av_bprintf(bp, "%s", channel_ਨਾਂ[channel_id].name);
    ਨਹੀਂਤਾਂ ਜੇ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    ਨਹੀਂਤਾਂ ਜੇ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    ਨਹੀਂਤਾਂ ਜੇ (channel_id == AV_CHAN_ਅਣਵਰਤਿਆ)
        av_bprintf(bp, "UNSD");
    ਨਹੀਂਤਾਂ
        av_bprintf(bp, "USR%d", channel_id);
}

ਪੂਰਨ av_channel_name(ਅੱਖਰ *buf, size_t buf_ਮਾਪ, ਗਿਣਤੀ AVChannel channel_id)
{
    AVBPrint bp;

    ਜੇ (!buf && buf_ਮਾਪ)
        ਵਾਪਸ AVERROR(EINVAL);

    av_bprint_init_for_ਬਫਰ(&bp, buf, buf_ਮਾਪ);
    av_channel_name_bprint(&bp, channel_id);

    ਜੇ (bp.len >= ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ)
        ਵਾਪਸ AVERROR(ERANGE);
    ਵਾਪਸ bp.len + 1;
}

ਖਾਲੀ av_channel_description_bprint(AVBPrint *bp, ਗਿਣਤੀ AVChannel channel_id)
{
    ਜੇ (channel_id >= AV_CHAN_AMBISONIC_ਅਧਾਰ &&
        channel_id <= AV_CHAN_AMBISONIC_ਸਿਰਾ)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_ਅਧਾਰ);
    ਨਹੀਂਤਾਂ ਜੇ ((ਬਿਨਾਨਿਸ਼ਾਨੀ)channel_id < FF_ARRAY_ELEMS(channel_ਨਾਂ) &&
             channel_ਨਾਂ[channel_id].description)
        av_bprintf(bp, "%s", channel_ਨਾਂ[channel_id].description);
    ਨਹੀਂਤਾਂ ਜੇ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    ਨਹੀਂਤਾਂ ਜੇ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    ਨਹੀਂਤਾਂ ਜੇ (channel_id == AV_CHAN_ਅਣਵਰਤਿਆ)
        av_bprintf(bp, "unused");
    ਨਹੀਂਤਾਂ
        av_bprintf(bp, "user %d", channel_id);
}

ਪੂਰਨ av_channel_description(ਅੱਖਰ *buf, size_t buf_ਮਾਪ, ਗਿਣਤੀ AVChannel channel_id)
{
    AVBPrint bp;

    ਜੇ (!buf && buf_ਮਾਪ)
        ਵਾਪਸ AVERROR(EINVAL);

    av_bprint_init_for_ਬਫਰ(&bp, buf, buf_ਮਾਪ);
    av_channel_description_bprint(&bp, channel_id);

    ਜੇ (bp.len >= ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ)
        ਵਾਪਸ AVERROR(ERANGE);
    ਵਾਪਸ bp.len + 1;
}

ਗਿਣਤੀ AVChannel av_channel_from_string(ਅਚਲ ਅੱਖਰ *str)
{
    ਪੂਰਨ i;
    ਅੱਖਰ *endptr = (ਅੱਖਰ *)str;
    ਗਿਣਤੀ AVChannel id = AV_CHAN_NONE;

    ਜੇ (!ਲੜੀ_ਤੁਲਨਾ(str, "AMBI", 4)) {
        i = strtol(str + 4, ਨਿਰਾ, 0);
        ਜੇ (i < 0 || i > AV_CHAN_AMBISONIC_ਸਿਰਾ - AV_CHAN_AMBISONIC_ਅਧਾਰ)
            ਵਾਪਸ AV_CHAN_NONE;
        ਵਾਪਸ AV_CHAN_AMBISONIC_ਅਧਾਰ + i;
    }

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(channel_ਨਾਂ); i++) {
        ਜੇ (channel_ਨਾਂ[i].name && !strcmp(str, channel_ਨਾਂ[i].name))
            ਵਾਪਸ i;
    }
    ਜੇ (!strcmp(str, "UNK"))
        ਵਾਪਸ AV_CHAN_UNKNOWN;
    ਜੇ (!strcmp(str, "UNSD"))
        ਵਾਪਸ AV_CHAN_ਅਣਵਰਤਿਆ;

    ਜੇ (!ਲੜੀ_ਤੁਲਨਾ(str, "USR", 3)) {
        ਅਚਲ ਅੱਖਰ *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    ਜੇ (id >= 0 && !*endptr)
        ਵਾਪਸ id;

    ਵਾਪਸ AV_CHAN_NONE;
}

ਬਣਤਰ channel_layout_name {
    ਅਚਲ ਅੱਖਰ *name;
    AVChannelLayout layout;
};

ਸਥਿਰ ਅਚਲ ਬਣਤਰ channel_layout_name channel_layout_map[] = {
    { "mono",           AV_CHANNEL_LAYOUT_MONO                },
    { "stereo",         AV_CHANNEL_LAYOUT_STEREO              },
    { "2.1",            AV_CHANNEL_LAYOUT_2POINT1             },
    { "3.0",            AV_CHANNEL_LAYOUT_SURROUND            },
    { "3.0(back)",      AV_CHANNEL_LAYOUT_2_1                 },
    { "4.0",            AV_CHANNEL_LAYOUT_4POINT0             },
    { "quad",           AV_CHANNEL_LAYOUT_QUAD                },
    { "quad(side)",     AV_CHANNEL_LAYOUT_2_2                 },
    { "3.1",            AV_CHANNEL_LAYOUT_3POINT1             },
    { "5.0",            AV_CHANNEL_LAYOUT_5_POINT0_ਪਿੱਠ        },
    { "5.0(side)",      AV_CHANNEL_LAYOUT_5POINT0             },
    { "4.1",            AV_CHANNEL_LAYOUT_4POINT1             },
    { "5.1",            AV_CHANNEL_LAYOUT_5_POINT1_ਪਿੱਠ        },
    { "5.1(side)",      AV_CHANNEL_LAYOUT_5POINT1             },
    { "6.0",            AV_CHANNEL_LAYOUT_6POINT0             },
    { "6.0(front)",     AV_CHANNEL_LAYOUT_6POINT0_FRONT       },
    { "3.1.2",          AV_CHANNEL_LAYOUT_3POINT1POINT2       },
    { "hexagonal",      AV_CHANNEL_LAYOUT_HEXAGONAL           },
    { "6.1",            AV_CHANNEL_LAYOUT_6POINT1             },
    { "6.1(back)",      AV_CHANNEL_LAYOUT_6_POINT1_ਪਿੱਠ        },
    { "6.1(front)",     AV_CHANNEL_LAYOUT_6POINT1_FRONT       },
    { "7.0",            AV_CHANNEL_LAYOUT_7POINT0             },
    { "7.0(front)",     AV_CHANNEL_LAYOUT_7POINT0_FRONT       },
    { "7.1",            AV_CHANNEL_LAYOUT_7POINT1             },
    { "7.1(wide)",      AV_CHANNEL_LAYOUT_7_POINT1_WIDE_ਪਿੱਠ   },
    { "7.1(wide-side)", AV_CHANNEL_LAYOUT_7POINT1_WIDE        },
    { "5.1.2",          AV_CHANNEL_LAYOUT_5POINT1POINT2       },
    { "5.1.2(back)",    AV_CHANNEL_LAYOUT_5_POINT1_POINT2_ਪਿੱਠ  },
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

ਪੂਰਨ av_channel_layout_custom_init(AVChannelLayout *channel_layout, ਪੂਰਨ nb_channels)
{
    AVChannelCustom *map;

    ਜੇ (nb_channels <= 0)
        ਵਾਪਸ AVERROR(EINVAL);

    map = av_calloc(nb_channels, ਆਕਾਰ(*channel_layout->u.map));
    ਜੇ (!map)
        ਵਾਪਸ AVERROR(ENOMEM);
    ਲਈ (ਪੂਰਨ i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->ਕ੍ਰਮ       = AV_CHANNEL_ਕ੍ਰਮ_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_channel_layout_from_ਨਕਾਬ(AVChannelLayout *channel_layout,
                                uint64_t ਨਕਾਬ_2)
{
    ਜੇ (!ਨਕਾਬ_2)
        ਵਾਪਸ AVERROR(EINVAL);

    channel_layout->ਕ੍ਰਮ       = AV_CHANNEL_ਕ੍ਰਮ_NATIVE;
    channel_layout->nb_channels = av_popcount64(ਨਕਾਬ_2);
    channel_layout->u.ਨਕਾਬ_2      = ਨਕਾਬ_2;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ parse_channel_list(AVChannelLayout *ch_layout, ਅਚਲ ਅੱਖਰ *str)
{
    ਪੂਰਨ ret;
    ਪੂਰਨ nb_channels = 0;
    AVChannelCustom *map = ਨਿਰਾ;
    AVChannelCustom custom = {0};

    ਜਦੋਂ (*str) {
        ਅੱਖਰ *channel, *chname;
        ret = av_opt_get_ਕੁੰਜੀ_ਮੁੱਲ(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_ਕੁੰਜੀ, &channel, &chname);
        ਜੇ (ret < 0) {
            av_freep(&map);
            ਵਾਪਸ ret;
        }
        ਜੇ (*str)
            str++; // skip separator
        ਜੇ (!channel) {
            channel = chname;
            chname = ਨਿਰਾ;
        }
        av_strlcpy(custom.name, chname ? chname : "", ਆਕਾਰ(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        ਜੇ (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            ਵਾਪਸ AVERROR(EINVAL);
        }

        av_dynarray2_ਜੋੜੋ((ਖਾਲੀ **)&map, &nb_channels, ਆਕਾਰ(custom), (ਖਾਲੀ *)&custom);
        ਜੇ (!map)
            ਵਾਪਸ AVERROR(ENOMEM);
    }

    ਜੇ (!nb_channels)
        ਵਾਪਸ AVERROR(EINVAL);

    ch_layout->ਕ੍ਰਮ = AV_CHANNEL_ਕ੍ਰਮ_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  ਅਚਲ ਅੱਖਰ *str)
{
    ਪੂਰਨ i, matches, ret;
    ਪੂਰਨ channels = 0, nb_channels = 0;
    ਅੱਖਰ *chlist, *ਸਿਰਾ;
    uint64_t ਨਕਾਬ_2 = 0;

    /* channel layout names */
    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        ਜੇ (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            ਵਾਪਸ 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, ਆਕਾਰ(*channel_layout));

    /* ambisonic */
    ਜੇ (!ਲੜੀ_ਤੁਲਨਾ(str, "ambisonic ", 10)) {
        ਅਚਲ ਅੱਖਰ *p = str + 10;
        ਅੱਖਰ *endptr;
        AVChannelLayout extra = {0};
        ਪੂਰਨ ਕ੍ਰਮ;

        ਕ੍ਰਮ = strtol(p, &endptr, 0);
        ਜੇ (ਕ੍ਰਮ < 0 || ਕ੍ਰਮ + 1  > ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ / (ਕ੍ਰਮ + 1) ||
            (*endptr && *endptr != '+'))
            ਵਾਪਸ AVERROR(EINVAL);

        channel_layout->ਕ੍ਰਮ       = AV_CHANNEL_ਕ੍ਰਮ_AMBISONIC;
        channel_layout->nb_channels = (ਕ੍ਰਮ + 1) * (ਕ੍ਰਮ + 1);

        ਜੇ (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            ਜੇ (ret < 0)
                ਵਾਪਸ ret;
            ਜੇ (extra.nb_channels >= ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                ਵਾਪਸ AVERROR(EINVAL);
            }

            ਜੇ (extra.ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_NATIVE) {
                channel_layout->u.ਨਕਾਬ_2 = extra.u.ਨਕਾਬ_2;
            } ਨਹੀਂਤਾਂ {
                channel_layout->ਕ੍ਰਮ = AV_CHANNEL_ਕ੍ਰਮ_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              ਆਕਾਰ(*channel_layout->u.map));
                ਜੇ (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    ਵਾਪਸ AVERROR(ENOMEM);
                }

                ਲਈ (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_ਅਧਾਰ + i;
                ਲਈ (i = 0; i < extra.nb_channels; i++) {
                    ਗਿਣਤੀ AVChannel ch = av_channel_layout_channel_from_ਸੂਚਕਾਂਕ(&extra, i);
                    ਜੇ (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        ਵਾਪਸ AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    ਜੇ (extra.ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   ਆਕਾਰ(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        ਵਾਪਸ 0;
    }

    chlist = av_strdup(str);
    ਜੇ (!chlist)
        ਵਾਪਸ AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    ਜੇ (ret < 0 && ret != AVERROR(EINVAL))
        ਵਾਪਸ ret;

    ਜੇ (ret >= 0) {
        ਅਚਲ ਅੱਖਰ *ਸਿਰਾ_par = strchr(str, ')');
        ਜੇ (matches == 2 && (nb_channels != channel_layout->nb_channels || !ਸਿਰਾ_par || *++ਸਿਰਾ_par)) {
            av_channel_layout_uninit(channel_layout);
            ਵਾਪਸ AVERROR(EINVAL);
        }
        ਵਾਪਸ 0;
    }

    errno = 0;
    ਨਕਾਬ_2 = strtoull(str, &ਸਿਰਾ, 0);

    /* channel layout mask */
    ਜੇ (!errno && !*ਸਿਰਾ && !strchr(str, '-') && ਨਕਾਬ_2) {
        av_channel_layout_from_ਨਕਾਬ(channel_layout, ਨਕਾਬ_2);
        ਵਾਪਸ 0;
    }

    errno = 0;
    channels = strtol(str, &ਸਿਰਾ, 10);

    /* number of channels */
    ਜੇ (!errno && !strcmp(ਸਿਰਾ, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        ਜੇ (channel_layout->ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_NATIVE)
            ਵਾਪਸ 0;
    }

    /* number of unordered channels */
    ਜੇ (!errno && (!strcmp(ਸਿਰਾ, "C") || !strcmp(ਸਿਰਾ, " channels"))
        && channels > 0) {
        channel_layout->ਕ੍ਰਮ = AV_CHANNEL_ਕ੍ਰਮ_UNSPEC;
        channel_layout->nb_channels = channels;
        ਵਾਪਸ 0;
    }

    ਵਾਪਸ AVERROR(EINVAL);
}

ਖਾਲੀ av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    ਜੇ (channel_layout->ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, ਆਕਾਰ(*channel_layout));
}

ਪੂਰਨ av_channel_layout_copy(AVChannelLayout *dst, ਅਚਲ AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    ਜੇ (src->ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, ਆਕਾਰ(*dst->u.map));
        ਜੇ (!dst->u.map)
            ਵਾਪਸ AVERROR(ENOMEM);
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(dst->u.map, src->u.map, src->nb_channels * ਆਕਾਰ(*src->u.map));
    }
    ਵਾਪਸ 0;
}

ਸਥਿਰ int64_t masked_description(ਅਚਲ AVChannelLayout *channel_layout, ਪੂਰਨ ਸ਼ੁਰੂ_channel)
{
    uint64_t ਨਕਾਬ_2 = 0;
    ਲਈ (ਪੂਰਨ i = ਸ਼ੁਰੂ_channel; i < channel_layout->nb_channels; i++) {
        ਗਿਣਤੀ AVChannel ch = channel_layout->u.map[i].id;
        ਜੇ (ch >= 0 && ch < 63 && ਨਕਾਬ_2 < (1ULL << ch))
            ਨਕਾਬ_2 |= (1ULL << ch);
        ਨਹੀਂਤਾਂ
            ਵਾਪਸ AVERROR(EINVAL);
    }
    ਵਾਪਸ ਨਕਾਬ_2;
}

ਸਥਿਰ ਪੂਰਨ has_channel_ਨਾਂ(ਅਚਲ AVChannelLayout *channel_layout)
{
    ਜੇ (channel_layout->ਕ੍ਰਮ != AV_CHANNEL_ਕ੍ਰਮ_CUSTOM)
        ਵਾਪਸ 0;
    ਲਈ (ਪੂਰਨ i = 0; i < channel_layout->nb_channels; i++)
        ਜੇ (channel_layout->u.map[i].name[0])
            ਵਾਪਸ 1;
    ਵਾਪਸ 0;
}

ਪੂਰਨ av_channel_layout_ambisonic_ਕ੍ਰਮ(ਅਚਲ AVChannelLayout *channel_layout)
{
    ਪੂਰਨ i, highest_ambi, ਕ੍ਰਮ;

    ਜੇ (channel_layout->ਕ੍ਰਮ != AV_CHANNEL_ਕ੍ਰਮ_AMBISONIC &&
        channel_layout->ਕ੍ਰਮ != AV_CHANNEL_ਕ੍ਰਮ_CUSTOM)
        ਵਾਪਸ AVERROR(EINVAL);

    highest_ambi = -1;
    ਜੇ (channel_layout->ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.ਨਕਾਬ_2) - 1;
    ਨਹੀਂਤਾਂ {
        ਅਚਲ AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_CUSTOM);

        ਲਈ (i = 0; i < channel_layout->nb_channels; i++) {
            ਪੂਰਨ is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            ਜੇ (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                ਵਾਪਸ AVERROR(EINVAL);

            /* non-default ordering */
            ਜੇ (is_ambi && map[i].id - AV_CHAN_AMBISONIC_ਅਧਾਰ != i)
                ਵਾਪਸ AVERROR(EINVAL);

            ਜੇ (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    ਜੇ (highest_ambi < 0)
        ਵਾਪਸ AVERROR(EINVAL);

    ਕ੍ਰਮ = floor(ਵਰਗਮੂਲ(highest_ambi));
    /* incomplete order - some harmonics are missing */
    ਜੇ ((ਕ੍ਰਮ + 1) * (ਕ੍ਰਮ + 1) != highest_ambi + 1)
        ਵਾਪਸ AVERROR(EINVAL);

    ਵਾਪਸ ਕ੍ਰਮ;
}

ਸਥਿਰ ਗਿਣਤੀ AVChannel_ਕ੍ਰਮ canonical_ਕ੍ਰਮ(AVChannelLayout *channel_layout)
{
    ਪੂਰਨ has_ਗਿਆਤ_channel = 0;
    ਪੂਰਨ ਕ੍ਰਮ;

    ਜੇ (channel_layout->ਕ੍ਰਮ != AV_CHANNEL_ਕ੍ਰਮ_CUSTOM)
        ਵਾਪਸ channel_layout->ਕ੍ਰਮ;

    ਜੇ (has_channel_ਨਾਂ(channel_layout))
        ਵਾਪਸ AV_CHANNEL_ਕ੍ਰਮ_CUSTOM;

    ਲਈ (ਪੂਰਨ i = 0; i < channel_layout->nb_channels && !has_ਗਿਆਤ_channel; i++)
        ਜੇ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_ਗਿਆਤ_channel = 1;
    ਜੇ (!has_ਗਿਆਤ_channel)
        ਵਾਪਸ AV_CHANNEL_ਕ੍ਰਮ_UNSPEC;

    ਜੇ (masked_description(channel_layout, 0) > 0)
        ਵਾਪਸ AV_CHANNEL_ਕ੍ਰਮ_NATIVE;

    ਕ੍ਰਮ = av_channel_layout_ambisonic_ਕ੍ਰਮ(channel_layout);
    ਜੇ (ਕ੍ਰਮ >= 0 && masked_description(channel_layout, (ਕ੍ਰਮ + 1) * (ਕ੍ਰਮ + 1)) >= 0)
        ਵਾਪਸ AV_CHANNEL_ਕ੍ਰਮ_AMBISONIC;

    ਵਾਪਸ AV_CHANNEL_ਕ੍ਰਮ_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
ਸਥਿਰ ਪੂਰਨ try_describe_ambisonic(AVBPrint *bp, ਅਚਲ AVChannelLayout *channel_layout)
{
    ਪੂਰਨ nb_ambi_channels;
    ਪੂਰਨ ਕ੍ਰਮ = av_channel_layout_ambisonic_ਕ੍ਰਮ(channel_layout);
    ਜੇ (ਕ੍ਰਮ < 0)
        ਵਾਪਸ ਕ੍ਰਮ;

    av_bprintf(bp, "ambisonic %d", ਕ੍ਰਮ);

    /* extra channels present */
    nb_ambi_channels = (ਕ੍ਰਮ + 1) * (ਕ੍ਰਮ + 1);
    ਜੇ (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        ਜੇ (channel_layout->ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_AMBISONIC) {
            extra.ਕ੍ਰਮ       = AV_CHANNEL_ਕ੍ਰਮ_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.ਨਕਾਬ_2);
            extra.u.ਨਕਾਬ_2      = channel_layout->u.ਨਕਾਬ_2;
        } ਨਹੀਂਤਾਂ {
            int64_t ਨਕਾਬ_2;
            ਜੇ (!has_channel_ਨਾਂ(channel_layout) &&
                (ਨਕਾਬ_2 = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.ਕ੍ਰਮ       = AV_CHANNEL_ਕ੍ਰਮ_NATIVE;
                extra.nb_channels = av_popcount64(ਨਕਾਬ_2);
                extra.u.ਨਕਾਬ_2      = ਨਕਾਬ_2;
            } ਨਹੀਂਤਾਂ {
                extra.ਕ੍ਰਮ       = AV_CHANNEL_ਕ੍ਰਮ_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_channel_layout_describe_bprint(ਅਚਲ AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    ਪੂਰਨ i;

    ਚੋਣ (channel_layout->ਕ੍ਰਮ) {
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_NATIVE:
        ਲਈ (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            ਜੇ (channel_layout->u.ਨਕਾਬ_2 == channel_layout_map[i].layout.u.ਨਕਾਬ_2) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                ਵਾਪਸ 0;
            }
        av_fallthrough;
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_CUSTOM:
        ਜੇ (channel_layout->ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_CUSTOM) {
            int64_t ਨਕਾਬ_2;
            ਪੂਰਨ res = try_describe_ambisonic(bp, channel_layout);
            ਜੇ (res >= 0)
                ਵਾਪਸ 0;
            ਜੇ (!has_channel_ਨਾਂ(channel_layout) &&
                (ਨਕਾਬ_2 = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .ਕ੍ਰਮ       = AV_CHANNEL_ਕ੍ਰਮ_NATIVE,
                                           .nb_channels = av_popcount64(ਨਕਾਬ_2),
                                           .u.ਨਕਾਬ_2      = ਨਕਾਬ_2 };
                ਵਾਪਸ av_channel_layout_describe_bprint(&native, bp);
            }
        }
        ਜੇ (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        ਲਈ (i = 0; i < channel_layout->nb_channels; i++) {
            ਗਿਣਤੀ AVChannel ch = av_channel_layout_channel_from_ਸੂਚਕਾਂਕ(channel_layout, i);

            ਜੇ (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            ਜੇ (channel_layout->ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        ਜੇ (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            ਵਾਪਸ 0;
        }
        av_fallthrough;
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        ਵਾਪਸ 0;
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_AMBISONIC:
        ਵਾਪਸ try_describe_ambisonic(bp, channel_layout);
    ਮੂਲ:
        ਵਾਪਸ AVERROR(EINVAL);
    }
}

ਪੂਰਨ av_channel_layout_describe(ਅਚਲ AVChannelLayout *channel_layout,
                               ਅੱਖਰ *buf, size_t buf_ਮਾਪ)
{
    AVBPrint bp;
    ਪੂਰਨ ret;

    ਜੇ (!buf && buf_ਮਾਪ)
        ਵਾਪਸ AVERROR(EINVAL);

    av_bprint_init_for_ਬਫਰ(&bp, buf, buf_ਮਾਪ);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ਜੇ (bp.len >= ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ)
        ਵਾਪਸ AVERROR(ERANGE);
    ਵਾਪਸ bp.len + 1;
}

ਗਿਣਤੀ AVChannel
av_channel_layout_channel_from_ਸੂਚਕਾਂਕ(ਅਚਲ AVChannelLayout *channel_layout,
                                     ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ idx)
{
    ਪੂਰਨ i;

    ਜੇ (idx >= channel_layout->nb_channels)
        ਵਾਪਸ AV_CHAN_NONE;

    ਚੋਣ (channel_layout->ਕ੍ਰਮ) {
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_CUSTOM:
        ਵਾਪਸ channel_layout->u.map[idx].id;
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_AMBISONIC: {
        ਪੂਰਨ ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.ਨਕਾਬ_2);
        ਜੇ (idx < ambi_channels)
            ਵਾਪਸ AV_CHAN_AMBISONIC_ਅਧਾਰ + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_NATIVE:
        ਲਈ (i = 0; i < 64; i++) {
            ਜੇ ((1ULL << i) & channel_layout->u.ਨਕਾਬ_2 && !idx--)
                ਵਾਪਸ i;
        }
        av_fallthrough;
    ਮੂਲ:
        ਵਾਪਸ AV_CHAN_NONE;
    }
}

ਗਿਣਤੀ AVChannel
av_channel_layout_channel_from_string(ਅਚਲ AVChannelLayout *channel_layout,
                                      ਅਚਲ ਅੱਖਰ *str)
{
    ਪੂਰਨ ਸੂਚਕਾਂਕ = av_channel_layout_ਸੂਚਕਾਂਕ_from_string(channel_layout, str);

    ਜੇ (ਸੂਚਕਾਂਕ < 0)
        ਵਾਪਸ AV_CHAN_NONE;

    ਵਾਪਸ av_channel_layout_channel_from_ਸੂਚਕਾਂਕ(channel_layout, ਸੂਚਕਾਂਕ);
}

ਪੂਰਨ av_channel_layout_ਸੂਚਕਾਂਕ_from_channel(ਅਚਲ AVChannelLayout *channel_layout,
                                         ਗਿਣਤੀ AVChannel channel)
{
    ਪੂਰਨ i;

    ਜੇ (channel == AV_CHAN_NONE)
        ਵਾਪਸ AVERROR(EINVAL);

    ਚੋਣ (channel_layout->ਕ੍ਰਮ) {
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_CUSTOM:
        ਲਈ (i = 0; i < channel_layout->nb_channels; i++)
            ਜੇ (channel_layout->u.map[i].id == channel)
                ਵਾਪਸ i;
        ਵਾਪਸ AVERROR(EINVAL);
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_AMBISONIC:
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_NATIVE: {
        uint64_t ਨਕਾਬ_2 = channel_layout->u.ਨਕਾਬ_2;
        ਪੂਰਨ ambi_channels = channel_layout->nb_channels - av_popcount64(ਨਕਾਬ_2);
        ਜੇ (channel_layout->ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_ਅਧਾਰ) {
            ਜੇ (channel - AV_CHAN_AMBISONIC_ਅਧਾਰ >= ambi_channels)
                ਵਾਪਸ AVERROR(EINVAL);
            ਵਾਪਸ channel - AV_CHAN_AMBISONIC_ਅਧਾਰ;
        }
        ਜੇ ((ਬਿਨਾਨਿਸ਼ਾਨੀ)channel > 63 || !(ਨਕਾਬ_2 & (1ULL << channel)))
            ਵਾਪਸ AVERROR(EINVAL);
        ਨਕਾਬ_2 &= (1ULL << channel) - 1;
        ਵਾਪਸ av_popcount64(ਨਕਾਬ_2) + ambi_channels;
        }
    ਮੂਲ:
        ਵਾਪਸ AVERROR(EINVAL);
    }
}

ਪੂਰਨ av_channel_layout_ਸੂਚਕਾਂਕ_from_string(ਅਚਲ AVChannelLayout *channel_layout,
                                        ਅਚਲ ਅੱਖਰ *str)
{
    ਅਚਲ ਅੱਖਰ *chname;
    ਗਿਣਤੀ AVChannel ch = AV_CHAN_NONE;

    ਚੋਣ (channel_layout->ਕ੍ਰਮ) {
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_CUSTOM:
        chname = ਲੜੀ_ਖੋਜ(str, "@");
        ਜੇ (chname) {
            ਅੱਖਰ buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(ਆਕਾਰ(buf), chname - str));
            ਜੇ (!*chname)
                chname = ਨਿਰਾ;
            ch = av_channel_from_string(buf);
            ਜੇ (ch == AV_CHAN_NONE && *buf)
                ਵਾਪਸ AVERROR(EINVAL);
        }
        ਲਈ (ਪੂਰਨ i = 0; chname && i < channel_layout->nb_channels; i++) {
            ਜੇ (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                ਵਾਪਸ i;
        }
        av_fallthrough;
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_AMBISONIC:
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_NATIVE:
        ch = av_channel_from_string(str);
        ਜੇ (ch == AV_CHAN_NONE)
            ਵਾਪਸ AVERROR(EINVAL);
        ਵਾਪਸ av_channel_layout_ਸੂਚਕਾਂਕ_from_channel(channel_layout, ch);
    }

    ਵਾਪਸ AVERROR(EINVAL);
}

ਪੂਰਨ av_channel_layout_check(ਅਚਲ AVChannelLayout *channel_layout)
{
    ਜੇ (channel_layout->nb_channels <= 0)
        ਵਾਪਸ 0;

    ਚੋਣ (channel_layout->ਕ੍ਰਮ) {
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_NATIVE:
        ਵਾਪਸ av_popcount64(channel_layout->u.ਨਕਾਬ_2) == channel_layout->nb_channels;
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_CUSTOM:
        ਜੇ (!channel_layout->u.map)
            ਵਾਪਸ 0;
        ਲਈ (ਪੂਰਨ i = 0; i < channel_layout->nb_channels; i++) {
            ਜੇ (channel_layout->u.map[i].id == AV_CHAN_NONE)
                ਵਾਪਸ 0;
        }
        ਵਾਪਸ 1;
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        ਵਾਪਸ av_popcount64(channel_layout->u.ਨਕਾਬ_2) < channel_layout->nb_channels;
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_UNSPEC:
        ਵਾਪਸ 1;
    ਮੂਲ:
        ਵਾਪਸ 0;
    }
}

ਪੂਰਨ av_channel_layout_compare(ਅਚਲ AVChannelLayout *chl, ਅਚਲ AVChannelLayout *chl1)
{
    ਪੂਰਨ i;

    /* different channel counts -> not equal */
    ਜੇ (chl->nb_channels != chl1->nb_channels)
        ਵਾਪਸ 1;

    /* if only one is unspecified -> not equal */
    ਜੇ ((chl->ਕ੍ਰਮ  == AV_CHANNEL_ਕ੍ਰਮ_UNSPEC) !=
        (chl1->ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_UNSPEC))
        ਵਾਪਸ 1;
    /* both are unspecified -> equal */
    ਨਹੀਂਤਾਂ ਜੇ (chl->ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_UNSPEC)
        ਵਾਪਸ 0;

    /* can compare masks directly */
    ਜੇ ((chl->ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_NATIVE ||
         chl->ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_AMBISONIC) &&
        chl->ਕ੍ਰਮ == chl1->ਕ੍ਰਮ)
        ਵਾਪਸ chl->u.ਨਕਾਬ_2 != chl1->u.ਨਕਾਬ_2;

    /* compare channel by channel */
    ਲਈ (i = 0; i < chl->nb_channels; i++)
        ਜੇ (av_channel_layout_channel_from_ਸੂਚਕਾਂਕ(chl,  i) !=
            av_channel_layout_channel_from_ਸੂਚਕਾਂਕ(chl1, i))
            ਵਾਪਸ 1;
    ਵਾਪਸ 0;
}

ਖਾਲੀ av_channel_layout_default(AVChannelLayout *ch_layout, ਪੂਰਨ nb_channels)
{
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        ਜੇ (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            ਵਾਪਸ;
        }

    ch_layout->ਕ੍ਰਮ       = AV_CHANNEL_ਕ੍ਰਮ_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

ਅਚਲ AVChannelLayout *av_channel_layout_standard(ਖਾਲੀ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ਅਚਲ AVChannelLayout *ch_layout = ਨਿਰਾ;

    ਜੇ (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (ਖਾਲੀ*)(i + 1);
    }

    ਵਾਪਸ ch_layout;
}

uint64_t av_channel_layout_subset(ਅਚਲ AVChannelLayout *channel_layout,
                                  uint64_t ਨਕਾਬ_2)
{
    uint64_t ret = 0;
    ਪੂਰਨ i;

    ਚੋਣ (channel_layout->ਕ੍ਰਮ) {
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_NATIVE:
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_AMBISONIC:
        ਵਾਪਸ channel_layout->u.ਨਕਾਬ_2 & ਨਕਾਬ_2;
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_CUSTOM:
        ਲਈ (i = 0; i < 64; i++)
            ਜੇ (ਨਕਾਬ_2 & (1ULL << i) && av_channel_layout_ਸੂਚਕਾਂਕ_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        ਰੋਕੋ;
    }

    ਵਾਪਸ ret;
}

ਪੂਰਨ av_channel_layout_retype(AVChannelLayout *channel_layout, ਗਿਣਤੀ AVChannel_ਕ੍ਰਮ ਕ੍ਰਮ, ਪੂਰਨ flags)
{
    ਪੂਰਨ allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    ਪੂਰਨ lossy;

    ਜੇ (!av_channel_layout_check(channel_layout))
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        ਕ੍ਰਮ = canonical_ਕ੍ਰਮ(channel_layout);

    ਜੇ (channel_layout->ਕ੍ਰਮ == ਕ੍ਰਮ)
        ਵਾਪਸ 0;

    ਚੋਣ (ਕ੍ਰਮ) {
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_UNSPEC: {
        ਪੂਰਨ nb_channels = channel_layout->nb_channels;
        ਜੇ (channel_layout->ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_CUSTOM) {
            lossy = 0;
            ਲਈ (ਪੂਰਨ i = 0; i < nb_channels; i++) {
                ਜੇ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    ਰੋਕੋ;
                }
            }
        } ਨਹੀਂਤਾਂ {
            lossy = 1;
        }
        ਜੇ (!lossy || allow_lossy) {
            ਖਾਲੀ *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->ਕ੍ਰਮ       = AV_CHANNEL_ਕ੍ਰਮ_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            ਵਾਪਸ lossy;
        }
        ਵਾਪਸ AVERROR(ENOSYS);
        }
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_NATIVE:
        ਜੇ (channel_layout->ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_CUSTOM) {
            int64_t ਨਕਾਬ_2 = masked_description(channel_layout, 0);
            ਜੇ (ਨਕਾਬ_2 < 0)
                ਵਾਪਸ AVERROR(ENOSYS);
            lossy = has_channel_ਨਾਂ(channel_layout);
            ਜੇ (!lossy || allow_lossy) {
                ਖਾਲੀ *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_ਨਕਾਬ(channel_layout, ਨਕਾਬ_2);
                channel_layout->opaque = opaque;
                ਵਾਪਸ lossy;
            }
        }
        ਵਾਪਸ AVERROR(ENOSYS);
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_CUSTOM: {
        AVChannelLayout custom = { 0 };
        ਪੂਰਨ ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        ਖਾਲੀ *opaque = channel_layout->opaque;
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;
        ਜੇ (channel_layout->ਕ੍ਰਮ != AV_CHANNEL_ਕ੍ਰਮ_UNSPEC)
            ਲਈ (ਪੂਰਨ i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_ਸੂਚਕਾਂਕ(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        ਵਾਪਸ 0;
        }
    ਹਾਲਤ AV_CHANNEL_ਕ੍ਰਮ_AMBISONIC:
        ਜੇ (channel_layout->ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_CUSTOM) {
            int64_t ਨਕਾਬ_2;
            ਪੂਰਨ nb_channels = channel_layout->nb_channels;
            ਪੂਰਨ amb_ਕ੍ਰਮ = av_channel_layout_ambisonic_ਕ੍ਰਮ(channel_layout);
            ਜੇ (amb_ਕ੍ਰਮ < 0)
                ਵਾਪਸ AVERROR(ENOSYS);
            ਨਕਾਬ_2 = masked_description(channel_layout, (amb_ਕ੍ਰਮ + 1) * (amb_ਕ੍ਰਮ + 1));
            ਜੇ (ਨਕਾਬ_2 < 0)
                ਵਾਪਸ AVERROR(ENOSYS);
            lossy = has_channel_ਨਾਂ(channel_layout);
            ਜੇ (!lossy || allow_lossy) {
                ਖਾਲੀ *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->ਕ੍ਰਮ       = AV_CHANNEL_ਕ੍ਰਮ_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.ਨਕਾਬ_2      = ਨਕਾਬ_2;
                channel_layout->opaque      = opaque;
                ਵਾਪਸ lossy;
            }
        }
        ਵਾਪਸ AVERROR(ENOSYS);
    ਮੂਲ:
        ਵਾਪਸ AVERROR(EINVAL);
    }
}
