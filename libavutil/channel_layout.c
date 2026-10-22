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

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "channel_layout.h"
#ಅನ್ತರ್ಭಾವ "bprint.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "attributes.h"
#ಅನ್ತರ್ಭಾವ "macros.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "opt.h"

#ವ್ಯಾಖ್ಯಾನಿಸು CHAN_IS_AMBI(x) ((x) >= AV_CHAN_AMBISONIC_ತಳ &&\
                         (x) <= AV_CHAN_AMBISONIC_ಕೊನೆ)

ರಚನೆ channel_name {
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *description;
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ channel_name channel_ಹೆಸರುಗಳು[] = {
    [AV_CHAN_FRONT_ಎಡ           ] = { "FL",        "front left"            },
    [AV_CHAN_FRONT_ಬಲ          ] = { "FR",        "front right"           },
    [AV_CHAN_FRONT_CENTER         ] = { "FC",        "front center"          },
    [AV_CHAN_ಕೆಳಗಿನ_FREQUENCY        ] = { "LFE",       "low frequency"         },
    [AV_CHAN_ಹಿಂಭಾಗ_ಎಡ            ] = { "BL",        "back left"             },
    [AV_CHAN_ಹಿಂಭಾಗ_ಬಲ           ] = { "BR",        "back right"            },
    [AV_CHAN_FRONT_ಎಡ_ದ_CENTER ] = { "FLC",       "front left-of-center"  },
    [AV_CHAN_FRONT_ಬಲ_ದ_CENTER] = { "FRC",       "front right-of-center" },
    [AV_CHAN_ಹಿಂಭಾಗ_CENTER          ] = { "BC",        "back center"           },
    [AV_CHAN_SIDE_ಎಡ            ] = { "SL",        "side left"             },
    [AV_CHAN_SIDE_ಬಲ           ] = { "SR",        "side right"            },
    [AV_CHAN_ತುದಿ_CENTER           ] = { "TC",        "top center"            },
    [AV_CHAN_ತುದಿ_FRONT_ಎಡ       ] = { "TFL",       "top front left"        },
    [AV_CHAN_ತುದಿ_FRONT_CENTER     ] = { "TFC",       "top front center"      },
    [AV_CHAN_ತುದಿ_FRONT_ಬಲ      ] = { "TFR",       "top front right"       },
    [AV_CHAN_ತುದಿ_ಹಿಂಭಾಗ_ಎಡ        ] = { "TBL",       "top back left"         },
    [AV_CHAN_ತುದಿ_ಹಿಂಭಾಗ_CENTER      ] = { "TBC",       "top back center"       },
    [AV_CHAN_ತುದಿ_ಹಿಂಭಾಗ_ಬಲ       ] = { "TBR",       "top back right"        },
    [AV_CHAN_STEREO_ಎಡ          ] = { "DL",        "downmix left"          },
    [AV_CHAN_STEREO_ಬಲ         ] = { "DR",        "downmix right"         },
    [AV_CHAN_WIDE_ಎಡ            ] = { "WL",        "wide left"             },
    [AV_CHAN_WIDE_ಬಲ           ] = { "WR",        "wide right"            },
    [AV_CHAN_SURROUND_ನೇರ_ಎಡ ] = { "SDL",       "surround direct left"  },
    [AV_CHAN_SURROUND_ನೇರ_ಬಲ] = { "SDR",       "surround direct right" },
    [AV_CHAN_ಕೆಳಗಿನ_FREQUENCY_2      ] = { "LFE2",      "low frequency 2"       },
    [AV_CHAN_ತುದಿ_SIDE_ಎಡ        ] = { "TSL",       "top side left"         },
    [AV_CHAN_ತುದಿ_SIDE_ಬಲ       ] = { "TSR",       "top side right"        },
    [AV_CHAN_BOTTOM_FRONT_CENTER  ] = { "BFC",       "bottom front center"   },
    [AV_CHAN_BOTTOM_FRONT_ಎಡ    ] = { "BFL",       "bottom front left"     },
    [AV_CHAN_BOTTOM_FRONT_ಬಲ   ] = { "BFR",       "bottom front right"    },
    [AV_CHAN_SIDE_SURROUND_ಎಡ   ] = { "SSL",       "side surround left"    },
    [AV_CHAN_SIDE_SURROUND_ಬಲ  ] = { "SSR",       "side surround right"   },
    [AV_CHAN_ತುದಿ_SURROUND_ಎಡ    ] = { "TTL",       "top surround left"     },
    [AV_CHAN_ತುದಿ_SURROUND_ಬಲ   ] = { "TTR",       "top surround right"    },
    [AV_CHAN_BINAURAL_ಎಡ        ] = { "BIL",       "binaural left"         },
    [AV_CHAN_BINAURAL_ಬಲ       ] = { "BIR",       "binaural right"        },
};

ಶೂನ್ಯ av_channel_name_bprint(AVBPrint *bp, ಎಣಿಕೆ AVChannel channel_id)
{
    ಆದರೆ (channel_id >= AV_CHAN_AMBISONIC_ತಳ &&
        channel_id <= AV_CHAN_AMBISONIC_ಕೊನೆ)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_ತಳ);
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ಚಿಹ್ನೆರಹಿತ)channel_id < FF_ARRAY_ELEMS(channel_ಹೆಸರುಗಳು) &&
             channel_ಹೆಸರುಗಳು[channel_id].name)
        av_bprintf(bp, "%s", channel_ಹೆಸರುಗಳು[channel_id].name);
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (channel_id == AV_CHAN_ಬಳಸದ)
        av_bprintf(bp, "UNSD");
    ಇಲ್ಲದಿದ್ದರೆ
        av_bprintf(bp, "USR%d", channel_id);
}

ಪೂರ್ಣಾಂಕ av_channel_name(ಅಕ್ಷರ *buf, size_t buf_ಗಾತ್ರ, ಎಣಿಕೆ AVChannel channel_id)
{
    AVBPrint bp;

    ಆದರೆ (!buf && buf_ಗಾತ್ರ)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    av_bprint_init_for_ಬಫರ್(&bp, buf, buf_ಗಾತ್ರ);
    av_channel_name_bprint(&bp, channel_id);

    ಆದರೆ (bp.len >= ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ)
        ಹಿಂತಿರುಗಿ AVERROR(ERANGE);
    ಹಿಂತಿರುಗಿ bp.len + 1;
}

ಶೂನ್ಯ av_channel_description_bprint(AVBPrint *bp, ಎಣಿಕೆ AVChannel channel_id)
{
    ಆದರೆ (channel_id >= AV_CHAN_AMBISONIC_ತಳ &&
        channel_id <= AV_CHAN_AMBISONIC_ಕೊನೆ)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_ತಳ);
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ಚಿಹ್ನೆರಹಿತ)channel_id < FF_ARRAY_ELEMS(channel_ಹೆಸರುಗಳು) &&
             channel_ಹೆಸರುಗಳು[channel_id].description)
        av_bprintf(bp, "%s", channel_ಹೆಸರುಗಳು[channel_id].description);
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (channel_id == AV_CHAN_ಬಳಸದ)
        av_bprintf(bp, "unused");
    ಇಲ್ಲದಿದ್ದರೆ
        av_bprintf(bp, "user %d", channel_id);
}

ಪೂರ್ಣಾಂಕ av_channel_description(ಅಕ್ಷರ *buf, size_t buf_ಗಾತ್ರ, ಎಣಿಕೆ AVChannel channel_id)
{
    AVBPrint bp;

    ಆದರೆ (!buf && buf_ಗಾತ್ರ)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    av_bprint_init_for_ಬಫರ್(&bp, buf, buf_ಗಾತ್ರ);
    av_channel_description_bprint(&bp, channel_id);

    ಆದರೆ (bp.len >= ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ)
        ಹಿಂತಿರುಗಿ AVERROR(ERANGE);
    ಹಿಂತಿರುಗಿ bp.len + 1;
}

ಎಣಿಕೆ AVChannel av_channel_from_string(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str)
{
    ಪೂರ್ಣಾಂಕ i;
    ಅಕ್ಷರ *endptr = (ಅಕ್ಷರ *)str;
    ಎಣಿಕೆ AVChannel id = AV_CHAN_NONE;

    ಆದರೆ (!ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ(str, "AMBI", 4)) {
        i = strtol(str + 4, ಖಾಲಿ, 0);
        ಆದರೆ (i < 0 || i > AV_CHAN_AMBISONIC_ಕೊನೆ - AV_CHAN_AMBISONIC_ತಳ)
            ಹಿಂತಿರುಗಿ AV_CHAN_NONE;
        ಹಿಂತಿರುಗಿ AV_CHAN_AMBISONIC_ತಳ + i;
    }

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(channel_ಹೆಸರುಗಳು); i++) {
        ಆದರೆ (channel_ಹೆಸರುಗಳು[i].name && !strcmp(str, channel_ಹೆಸರುಗಳು[i].name))
            ಹಿಂತಿರುಗಿ i;
    }
    ಆದರೆ (!strcmp(str, "UNK"))
        ಹಿಂತಿರುಗಿ AV_CHAN_UNKNOWN;
    ಆದರೆ (!strcmp(str, "UNSD"))
        ಹಿಂತಿರುಗಿ AV_CHAN_ಬಳಸದ;

    ಆದರೆ (!ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ(str, "USR", 3)) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    ಆದರೆ (id >= 0 && !*endptr)
        ಹಿಂತಿರುಗಿ id;

    ಹಿಂತಿರುಗಿ AV_CHAN_NONE;
}

ರಚನೆ channel_layout_name {
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name;
    AVChannelLayout layout;
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ channel_layout_name channel_layout_map[] = {
    { "mono",           AV_CHANNEL_LAYOUT_MONO                },
    { "stereo",         AV_CHANNEL_LAYOUT_STEREO              },
    { "2.1",            AV_CHANNEL_LAYOUT_2POINT1             },
    { "3.0",            AV_CHANNEL_LAYOUT_SURROUND            },
    { "3.0(back)",      AV_CHANNEL_LAYOUT_2_1                 },
    { "4.0",            AV_CHANNEL_LAYOUT_4POINT0             },
    { "quad",           AV_CHANNEL_LAYOUT_QUAD                },
    { "quad(side)",     AV_CHANNEL_LAYOUT_2_2                 },
    { "3.1",            AV_CHANNEL_LAYOUT_3POINT1             },
    { "5.0",            AV_CHANNEL_LAYOUT_5_POINT0_ಹಿಂಭಾಗ        },
    { "5.0(side)",      AV_CHANNEL_LAYOUT_5POINT0             },
    { "4.1",            AV_CHANNEL_LAYOUT_4POINT1             },
    { "5.1",            AV_CHANNEL_LAYOUT_5_POINT1_ಹಿಂಭಾಗ        },
    { "5.1(side)",      AV_CHANNEL_LAYOUT_5POINT1             },
    { "6.0",            AV_CHANNEL_LAYOUT_6POINT0             },
    { "6.0(front)",     AV_CHANNEL_LAYOUT_6POINT0_FRONT       },
    { "3.1.2",          AV_CHANNEL_LAYOUT_3POINT1POINT2       },
    { "hexagonal",      AV_CHANNEL_LAYOUT_HEXAGONAL           },
    { "6.1",            AV_CHANNEL_LAYOUT_6POINT1             },
    { "6.1(back)",      AV_CHANNEL_LAYOUT_6_POINT1_ಹಿಂಭಾಗ        },
    { "6.1(front)",     AV_CHANNEL_LAYOUT_6POINT1_FRONT       },
    { "7.0",            AV_CHANNEL_LAYOUT_7POINT0             },
    { "7.0(front)",     AV_CHANNEL_LAYOUT_7POINT0_FRONT       },
    { "7.1",            AV_CHANNEL_LAYOUT_7POINT1             },
    { "7.1(wide)",      AV_CHANNEL_LAYOUT_7_POINT1_WIDE_ಹಿಂಭಾಗ   },
    { "7.1(wide-side)", AV_CHANNEL_LAYOUT_7POINT1_WIDE        },
    { "5.1.2",          AV_CHANNEL_LAYOUT_5POINT1POINT2       },
    { "5.1.2(back)",    AV_CHANNEL_LAYOUT_5_POINT1_POINT2_ಹಿಂಭಾಗ  },
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

ಪೂರ್ಣಾಂಕ av_channel_layout_custom_init(AVChannelLayout *channel_layout, ಪೂರ್ಣಾಂಕ nb_channels)
{
    AVChannelCustom *map;

    ಆದರೆ (nb_channels <= 0)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    map = av_calloc(nb_channels, ಗಾತ್ರ(*channel_layout->u.map));
    ಆದರೆ (!map)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->ಕ್ರಮ       = AV_CHANNEL_ಕ್ರಮ_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_channel_layout_from_ಮುಖವಾಡ(AVChannelLayout *channel_layout,
                                uint64_t ಮುಖವಾಡ_2)
{
    ಆದರೆ (!ಮುಖವಾಡ_2)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    channel_layout->ಕ್ರಮ       = AV_CHANNEL_ಕ್ರಮ_NATIVE;
    channel_layout->nb_channels = av_popcount64(ಮುಖವಾಡ_2);
    channel_layout->u.ಮುಖವಾಡ_2      = ಮುಖವಾಡ_2;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ parse_channel_list(AVChannelLayout *ch_layout, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str)
{
    ಪೂರ್ಣಾಂಕ ret;
    ಪೂರ್ಣಾಂಕ nb_channels = 0;
    AVChannelCustom *map = ಖಾಲಿ;
    AVChannelCustom custom = {0};

    ಆಗ (*str) {
        ಅಕ್ಷರ *channel, *chname;
        ret = av_opt_get_ಕೀಲಿ_ಮೌಲ್ಯ(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_ಕೀಲಿ, &channel, &chname);
        ಆದರೆ (ret < 0) {
            av_freep(&map);
            ಹಿಂತಿರುಗಿ ret;
        }
        ಆದರೆ (*str)
            str++; // skip separator
        ಆದರೆ (!channel) {
            channel = chname;
            chname = ಖಾಲಿ;
        }
        av_strlcpy(custom.name, chname ? chname : "", ಗಾತ್ರ(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        ಆದರೆ (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }

        av_dynarray2_ಕೂಡಿಸು((ಶೂನ್ಯ **)&map, &nb_channels, ಗಾತ್ರ(custom), (ಶೂನ್ಯ *)&custom);
        ಆದರೆ (!map)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    ಆದರೆ (!nb_channels)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ch_layout->ಕ್ರಮ = AV_CHANNEL_ಕ್ರಮ_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str)
{
    ಪೂರ್ಣಾಂಕ i, matches, ret;
    ಪೂರ್ಣಾಂಕ channels = 0, nb_channels = 0;
    ಅಕ್ಷರ *chlist, *ಕೊನೆ;
    uint64_t ಮುಖವಾಡ_2 = 0;

    /* channel layout names */
    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        ಆದರೆ (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            ಹಿಂತಿರುಗಿ 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, ಗಾತ್ರ(*channel_layout));

    /* ambisonic */
    ಆದರೆ (!ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ(str, "ambisonic ", 10)) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p = str + 10;
        ಅಕ್ಷರ *endptr;
        AVChannelLayout extra = {0};
        ಪೂರ್ಣಾಂಕ ಕ್ರಮ;

        ಕ್ರಮ = strtol(p, &endptr, 0);
        ಆದರೆ (ಕ್ರಮ < 0 || ಕ್ರಮ + 1  > ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ / (ಕ್ರಮ + 1) ||
            (*endptr && *endptr != '+'))
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

        channel_layout->ಕ್ರಮ       = AV_CHANNEL_ಕ್ರಮ_AMBISONIC;
        channel_layout->nb_channels = (ಕ್ರಮ + 1) * (ಕ್ರಮ + 1);

        ಆದರೆ (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            ಆದರೆ (ret < 0)
                ಹಿಂತಿರುಗಿ ret;
            ಆದರೆ (extra.nb_channels >= ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
            }

            ಆದರೆ (extra.ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_NATIVE) {
                channel_layout->u.ಮುಖವಾಡ_2 = extra.u.ಮುಖವಾಡ_2;
            } ಇಲ್ಲದಿದ್ದರೆ {
                channel_layout->ಕ್ರಮ = AV_CHANNEL_ಕ್ರಮ_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              ಗಾತ್ರ(*channel_layout->u.map));
                ಆದರೆ (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
                }

                ಗಾಗಿ (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_ತಳ + i;
                ಗಾಗಿ (i = 0; i < extra.nb_channels; i++) {
                    ಎಣಿಕೆ AVChannel ch = av_channel_layout_channel_from_ಸೂಚ್ಯಂಕ(&extra, i);
                    ಆದರೆ (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    ಆದರೆ (extra.ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   ಗಾತ್ರ(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        ಹಿಂತಿರುಗಿ 0;
    }

    chlist = av_strdup(str);
    ಆದರೆ (!chlist)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    ಆದರೆ (ret < 0 && ret != AVERROR(EINVAL))
        ಹಿಂತಿರುಗಿ ret;

    ಆದರೆ (ret >= 0) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೊನೆ_par = strchr(str, ')');
        ಆದರೆ (matches == 2 && (nb_channels != channel_layout->nb_channels || !ಕೊನೆ_par || *++ಕೊನೆ_par)) {
            av_channel_layout_uninit(channel_layout);
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
        ಹಿಂತಿರುಗಿ 0;
    }

    errno = 0;
    ಮುಖವಾಡ_2 = strtoull(str, &ಕೊನೆ, 0);

    /* channel layout mask */
    ಆದರೆ (!errno && !*ಕೊನೆ && !strchr(str, '-') && ಮುಖವಾಡ_2) {
        av_channel_layout_from_ಮುಖವಾಡ(channel_layout, ಮುಖವಾಡ_2);
        ಹಿಂತಿರುಗಿ 0;
    }

    errno = 0;
    channels = strtol(str, &ಕೊನೆ, 10);

    /* number of channels */
    ಆದರೆ (!errno && !strcmp(ಕೊನೆ, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        ಆದರೆ (channel_layout->ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_NATIVE)
            ಹಿಂತಿರುಗಿ 0;
    }

    /* number of unordered channels */
    ಆದರೆ (!errno && (!strcmp(ಕೊನೆ, "C") || !strcmp(ಕೊನೆ, " channels"))
        && channels > 0) {
        channel_layout->ಕ್ರಮ = AV_CHANNEL_ಕ್ರಮ_UNSPEC;
        channel_layout->nb_channels = channels;
        ಹಿಂತಿರುಗಿ 0;
    }

    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}

ಶೂನ್ಯ av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    ಆದರೆ (channel_layout->ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, ಗಾತ್ರ(*channel_layout));
}

ಪೂರ್ಣಾಂಕ av_channel_layout_copy(AVChannelLayout *dst, ಸ್ಥಿರಾಂಕ AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    ಆದರೆ (src->ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, ಗಾತ್ರ(*dst->u.map));
        ಆದರೆ (!dst->u.map)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        ಸ್ಮರಣೆ_ನಕಲು(dst->u.map, src->u.map, src->nb_channels * ಗಾತ್ರ(*src->u.map));
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ int64_t masked_description(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout, ಪೂರ್ಣಾಂಕ ಆರಂಭ_channel)
{
    uint64_t ಮುಖವಾಡ_2 = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = ಆರಂಭ_channel; i < channel_layout->nb_channels; i++) {
        ಎಣಿಕೆ AVChannel ch = channel_layout->u.map[i].id;
        ಆದರೆ (ch >= 0 && ch < 63 && ಮುಖವಾಡ_2 < (1ULL << ch))
            ಮುಖವಾಡ_2 |= (1ULL << ch);
        ಇಲ್ಲದಿದ್ದರೆ
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }
    ಹಿಂತಿರುಗಿ ಮುಖವಾಡ_2;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ has_channel_ಹೆಸರುಗಳು(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout)
{
    ಆದರೆ (channel_layout->ಕ್ರಮ != AV_CHANNEL_ಕ್ರಮ_CUSTOM)
        ಹಿಂತಿರುಗಿ 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < channel_layout->nb_channels; i++)
        ಆದರೆ (channel_layout->u.map[i].name[0])
            ಹಿಂತಿರುಗಿ 1;
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_channel_layout_ambisonic_ಕ್ರಮ(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout)
{
    ಪೂರ್ಣಾಂಕ i, highest_ambi, ಕ್ರಮ;

    ಆದರೆ (channel_layout->ಕ್ರಮ != AV_CHANNEL_ಕ್ರಮ_AMBISONIC &&
        channel_layout->ಕ್ರಮ != AV_CHANNEL_ಕ್ರಮ_CUSTOM)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    highest_ambi = -1;
    ಆದರೆ (channel_layout->ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.ಮುಖವಾಡ_2) - 1;
    ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಥಿರಾಂಕ AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_CUSTOM);

        ಗಾಗಿ (i = 0; i < channel_layout->nb_channels; i++) {
            ಪೂರ್ಣಾಂಕ is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            ಆದರೆ (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

            /* non-default ordering */
            ಆದರೆ (is_ambi && map[i].id - AV_CHAN_AMBISONIC_ತಳ != i)
                ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

            ಆದರೆ (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    ಆದರೆ (highest_ambi < 0)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಕ್ರಮ = floor(ವರ್ಗಮೂಲ(highest_ambi));
    /* incomplete order - some harmonics are missing */
    ಆದರೆ ((ಕ್ರಮ + 1) * (ಕ್ರಮ + 1) != highest_ambi + 1)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಹಿಂತಿರುಗಿ ಕ್ರಮ;
}

ಸ್ಥಿರ ಎಣಿಕೆ AVChannel_ಕ್ರಮ canonical_ಕ್ರಮ(AVChannelLayout *channel_layout)
{
    ಪೂರ್ಣಾಂಕ has_ತಿಳಿದ_channel = 0;
    ಪೂರ್ಣಾಂಕ ಕ್ರಮ;

    ಆದರೆ (channel_layout->ಕ್ರಮ != AV_CHANNEL_ಕ್ರಮ_CUSTOM)
        ಹಿಂತಿರುಗಿ channel_layout->ಕ್ರಮ;

    ಆದರೆ (has_channel_ಹೆಸರುಗಳು(channel_layout))
        ಹಿಂತಿರುಗಿ AV_CHANNEL_ಕ್ರಮ_CUSTOM;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < channel_layout->nb_channels && !has_ತಿಳಿದ_channel; i++)
        ಆದರೆ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_ತಿಳಿದ_channel = 1;
    ಆದರೆ (!has_ತಿಳಿದ_channel)
        ಹಿಂತಿರುಗಿ AV_CHANNEL_ಕ್ರಮ_UNSPEC;

    ಆದರೆ (masked_description(channel_layout, 0) > 0)
        ಹಿಂತಿರುಗಿ AV_CHANNEL_ಕ್ರಮ_NATIVE;

    ಕ್ರಮ = av_channel_layout_ambisonic_ಕ್ರಮ(channel_layout);
    ಆದರೆ (ಕ್ರಮ >= 0 && masked_description(channel_layout, (ಕ್ರಮ + 1) * (ಕ್ರಮ + 1)) >= 0)
        ಹಿಂತಿರುಗಿ AV_CHANNEL_ಕ್ರಮ_AMBISONIC;

    ಹಿಂತಿರುಗಿ AV_CHANNEL_ಕ್ರಮ_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ try_describe_ambisonic(AVBPrint *bp, ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout)
{
    ಪೂರ್ಣಾಂಕ nb_ambi_channels;
    ಪೂರ್ಣಾಂಕ ಕ್ರಮ = av_channel_layout_ambisonic_ಕ್ರಮ(channel_layout);
    ಆದರೆ (ಕ್ರಮ < 0)
        ಹಿಂತಿರುಗಿ ಕ್ರಮ;

    av_bprintf(bp, "ambisonic %d", ಕ್ರಮ);

    /* extra channels present */
    nb_ambi_channels = (ಕ್ರಮ + 1) * (ಕ್ರಮ + 1);
    ಆದರೆ (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        ಆದರೆ (channel_layout->ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_AMBISONIC) {
            extra.ಕ್ರಮ       = AV_CHANNEL_ಕ್ರಮ_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.ಮುಖವಾಡ_2);
            extra.u.ಮುಖವಾಡ_2      = channel_layout->u.ಮುಖವಾಡ_2;
        } ಇಲ್ಲದಿದ್ದರೆ {
            int64_t ಮುಖವಾಡ_2;
            ಆದರೆ (!has_channel_ಹೆಸರುಗಳು(channel_layout) &&
                (ಮುಖವಾಡ_2 = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.ಕ್ರಮ       = AV_CHANNEL_ಕ್ರಮ_NATIVE;
                extra.nb_channels = av_popcount64(ಮುಖವಾಡ_2);
                extra.u.ಮುಖವಾಡ_2      = ಮುಖವಾಡ_2;
            } ಇಲ್ಲದಿದ್ದರೆ {
                extra.ಕ್ರಮ       = AV_CHANNEL_ಕ್ರಮ_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_channel_layout_describe_bprint(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    ಪೂರ್ಣಾಂಕ i;

    ಆಯ್ಕೆ (channel_layout->ಕ್ರಮ) {
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_NATIVE:
        ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            ಆದರೆ (channel_layout->u.ಮುಖವಾಡ_2 == channel_layout_map[i].layout.u.ಮುಖವಾಡ_2) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                ಹಿಂತಿರುಗಿ 0;
            }
        av_fallthrough;
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_CUSTOM:
        ಆದರೆ (channel_layout->ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_CUSTOM) {
            int64_t ಮುಖವಾಡ_2;
            ಪೂರ್ಣಾಂಕ res = try_describe_ambisonic(bp, channel_layout);
            ಆದರೆ (res >= 0)
                ಹಿಂತಿರುಗಿ 0;
            ಆದರೆ (!has_channel_ಹೆಸರುಗಳು(channel_layout) &&
                (ಮುಖವಾಡ_2 = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .ಕ್ರಮ       = AV_CHANNEL_ಕ್ರಮ_NATIVE,
                                           .nb_channels = av_popcount64(ಮುಖವಾಡ_2),
                                           .u.ಮುಖವಾಡ_2      = ಮುಖವಾಡ_2 };
                ಹಿಂತಿರುಗಿ av_channel_layout_describe_bprint(&native, bp);
            }
        }
        ಆದರೆ (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        ಗಾಗಿ (i = 0; i < channel_layout->nb_channels; i++) {
            ಎಣಿಕೆ AVChannel ch = av_channel_layout_channel_from_ಸೂಚ್ಯಂಕ(channel_layout, i);

            ಆದರೆ (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            ಆದರೆ (channel_layout->ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        ಆದರೆ (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            ಹಿಂತಿರುಗಿ 0;
        }
        av_fallthrough;
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        ಹಿಂತಿರುಗಿ 0;
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_AMBISONIC:
        ಹಿಂತಿರುಗಿ try_describe_ambisonic(bp, channel_layout);
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }
}

ಪೂರ್ಣಾಂಕ av_channel_layout_describe(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout,
                               ಅಕ್ಷರ *buf, size_t buf_ಗಾತ್ರ)
{
    AVBPrint bp;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (!buf && buf_ಗಾತ್ರ)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    av_bprint_init_for_ಬಫರ್(&bp, buf, buf_ಗಾತ್ರ);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಆದರೆ (bp.len >= ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ)
        ಹಿಂತಿರುಗಿ AVERROR(ERANGE);
    ಹಿಂತಿರುಗಿ bp.len + 1;
}

ಎಣಿಕೆ AVChannel
av_channel_layout_channel_from_ಸೂಚ್ಯಂಕ(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout,
                                     ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ idx)
{
    ಪೂರ್ಣಾಂಕ i;

    ಆದರೆ (idx >= channel_layout->nb_channels)
        ಹಿಂತಿರುಗಿ AV_CHAN_NONE;

    ಆಯ್ಕೆ (channel_layout->ಕ್ರಮ) {
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_CUSTOM:
        ಹಿಂತಿರುಗಿ channel_layout->u.map[idx].id;
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_AMBISONIC: {
        ಪೂರ್ಣಾಂಕ ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.ಮುಖವಾಡ_2);
        ಆದರೆ (idx < ambi_channels)
            ಹಿಂತಿರುಗಿ AV_CHAN_AMBISONIC_ತಳ + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_NATIVE:
        ಗಾಗಿ (i = 0; i < 64; i++) {
            ಆದರೆ ((1ULL << i) & channel_layout->u.ಮುಖವಾಡ_2 && !idx--)
                ಹಿಂತಿರುಗಿ i;
        }
        av_fallthrough;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ AV_CHAN_NONE;
    }
}

ಎಣಿಕೆ AVChannel
av_channel_layout_channel_from_string(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout,
                                      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str)
{
    ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ = av_channel_layout_ಸೂಚ್ಯಂಕ_from_string(channel_layout, str);

    ಆದರೆ (ಸೂಚ್ಯಂಕ < 0)
        ಹಿಂತಿರುಗಿ AV_CHAN_NONE;

    ಹಿಂತಿರುಗಿ av_channel_layout_channel_from_ಸೂಚ್ಯಂಕ(channel_layout, ಸೂಚ್ಯಂಕ);
}

ಪೂರ್ಣಾಂಕ av_channel_layout_ಸೂಚ್ಯಂಕ_from_channel(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout,
                                         ಎಣಿಕೆ AVChannel channel)
{
    ಪೂರ್ಣಾಂಕ i;

    ಆದರೆ (channel == AV_CHAN_NONE)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆಯ್ಕೆ (channel_layout->ಕ್ರಮ) {
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_CUSTOM:
        ಗಾಗಿ (i = 0; i < channel_layout->nb_channels; i++)
            ಆದರೆ (channel_layout->u.map[i].id == channel)
                ಹಿಂತಿರುಗಿ i;
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_AMBISONIC:
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_NATIVE: {
        uint64_t ಮುಖವಾಡ_2 = channel_layout->u.ಮುಖವಾಡ_2;
        ಪೂರ್ಣಾಂಕ ambi_channels = channel_layout->nb_channels - av_popcount64(ಮುಖವಾಡ_2);
        ಆದರೆ (channel_layout->ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_ತಳ) {
            ಆದರೆ (channel - AV_CHAN_AMBISONIC_ತಳ >= ambi_channels)
                ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
            ಹಿಂತಿರುಗಿ channel - AV_CHAN_AMBISONIC_ತಳ;
        }
        ಆದರೆ ((ಚಿಹ್ನೆರಹಿತ)channel > 63 || !(ಮುಖವಾಡ_2 & (1ULL << channel)))
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        ಮುಖವಾಡ_2 &= (1ULL << channel) - 1;
        ಹಿಂತಿರುಗಿ av_popcount64(ಮುಖವಾಡ_2) + ambi_channels;
        }
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }
}

ಪೂರ್ಣಾಂಕ av_channel_layout_ಸೂಚ್ಯಂಕ_from_string(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout,
                                        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *chname;
    ಎಣಿಕೆ AVChannel ch = AV_CHAN_NONE;

    ಆಯ್ಕೆ (channel_layout->ಕ್ರಮ) {
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_CUSTOM:
        chname = ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(str, "@");
        ಆದರೆ (chname) {
            ಅಕ್ಷರ buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(ಗಾತ್ರ(buf), chname - str));
            ಆದರೆ (!*chname)
                chname = ಖಾಲಿ;
            ch = av_channel_from_string(buf);
            ಆದರೆ (ch == AV_CHAN_NONE && *buf)
                ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; chname && i < channel_layout->nb_channels; i++) {
            ಆದರೆ (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                ಹಿಂತಿರುಗಿ i;
        }
        av_fallthrough;
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_AMBISONIC:
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_NATIVE:
        ch = av_channel_from_string(str);
        ಆದರೆ (ch == AV_CHAN_NONE)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        ಹಿಂತಿರುಗಿ av_channel_layout_ಸೂಚ್ಯಂಕ_from_channel(channel_layout, ch);
    }

    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}

ಪೂರ್ಣಾಂಕ av_channel_layout_check(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout)
{
    ಆದರೆ (channel_layout->nb_channels <= 0)
        ಹಿಂತಿರುಗಿ 0;

    ಆಯ್ಕೆ (channel_layout->ಕ್ರಮ) {
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_NATIVE:
        ಹಿಂತಿರುಗಿ av_popcount64(channel_layout->u.ಮುಖವಾಡ_2) == channel_layout->nb_channels;
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_CUSTOM:
        ಆದರೆ (!channel_layout->u.map)
            ಹಿಂತಿರುಗಿ 0;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < channel_layout->nb_channels; i++) {
            ಆದರೆ (channel_layout->u.map[i].id == AV_CHAN_NONE)
                ಹಿಂತಿರುಗಿ 0;
        }
        ಹಿಂತಿರುಗಿ 1;
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        ಹಿಂತಿರುಗಿ av_popcount64(channel_layout->u.ಮುಖವಾಡ_2) < channel_layout->nb_channels;
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_UNSPEC:
        ಹಿಂತಿರುಗಿ 1;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ 0;
    }
}

ಪೂರ್ಣಾಂಕ av_channel_layout_compare(ಸ್ಥಿರಾಂಕ AVChannelLayout *chl, ಸ್ಥಿರಾಂಕ AVChannelLayout *chl1)
{
    ಪೂರ್ಣಾಂಕ i;

    /* different channel counts -> not equal */
    ಆದರೆ (chl->nb_channels != chl1->nb_channels)
        ಹಿಂತಿರುಗಿ 1;

    /* if only one is unspecified -> not equal */
    ಆದರೆ ((chl->ಕ್ರಮ  == AV_CHANNEL_ಕ್ರಮ_UNSPEC) !=
        (chl1->ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_UNSPEC))
        ಹಿಂತಿರುಗಿ 1;
    /* both are unspecified -> equal */
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (chl->ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_UNSPEC)
        ಹಿಂತಿರುಗಿ 0;

    /* can compare masks directly */
    ಆದರೆ ((chl->ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_NATIVE ||
         chl->ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_AMBISONIC) &&
        chl->ಕ್ರಮ == chl1->ಕ್ರಮ)
        ಹಿಂತಿರುಗಿ chl->u.ಮುಖವಾಡ_2 != chl1->u.ಮುಖವಾಡ_2;

    /* compare channel by channel */
    ಗಾಗಿ (i = 0; i < chl->nb_channels; i++)
        ಆದರೆ (av_channel_layout_channel_from_ಸೂಚ್ಯಂಕ(chl,  i) !=
            av_channel_layout_channel_from_ಸೂಚ್ಯಂಕ(chl1, i))
            ಹಿಂತಿರುಗಿ 1;
    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ av_channel_layout_default(AVChannelLayout *ch_layout, ಪೂರ್ಣಾಂಕ nb_channels)
{
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        ಆದರೆ (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            ಹಿಂತಿರುಗಿ;
        }

    ch_layout->ಕ್ರಮ       = AV_CHANNEL_ಕ್ರಮ_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

ಸ್ಥಿರಾಂಕ AVChannelLayout *av_channel_layout_standard(ಶೂನ್ಯ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ಸ್ಥಿರಾಂಕ AVChannelLayout *ch_layout = ಖಾಲಿ;

    ಆದರೆ (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (ಶೂನ್ಯ*)(i + 1);
    }

    ಹಿಂತಿರುಗಿ ch_layout;
}

uint64_t av_channel_layout_subset(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout,
                                  uint64_t ಮುಖವಾಡ_2)
{
    uint64_t ret = 0;
    ಪೂರ್ಣಾಂಕ i;

    ಆಯ್ಕೆ (channel_layout->ಕ್ರಮ) {
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_NATIVE:
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_AMBISONIC:
        ಹಿಂತಿರುಗಿ channel_layout->u.ಮುಖವಾಡ_2 & ಮುಖವಾಡ_2;
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_CUSTOM:
        ಗಾಗಿ (i = 0; i < 64; i++)
            ಆದರೆ (ಮುಖವಾಡ_2 & (1ULL << i) && av_channel_layout_ಸೂಚ್ಯಂಕ_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        ನಿಲ್ಲಿಸು;
    }

    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_channel_layout_retype(AVChannelLayout *channel_layout, ಎಣಿಕೆ AVChannel_ಕ್ರಮ ಕ್ರಮ, ಪೂರ್ಣಾಂಕ flags)
{
    ಪೂರ್ಣಾಂಕ allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    ಪೂರ್ಣಾಂಕ lossy;

    ಆದರೆ (!av_channel_layout_check(channel_layout))
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        ಕ್ರಮ = canonical_ಕ್ರಮ(channel_layout);

    ಆದರೆ (channel_layout->ಕ್ರಮ == ಕ್ರಮ)
        ಹಿಂತಿರುಗಿ 0;

    ಆಯ್ಕೆ (ಕ್ರಮ) {
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_UNSPEC: {
        ಪೂರ್ಣಾಂಕ nb_channels = channel_layout->nb_channels;
        ಆದರೆ (channel_layout->ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_CUSTOM) {
            lossy = 0;
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_channels; i++) {
                ಆದರೆ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    ನಿಲ್ಲಿಸು;
                }
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            lossy = 1;
        }
        ಆದರೆ (!lossy || allow_lossy) {
            ಶೂನ್ಯ *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->ಕ್ರಮ       = AV_CHANNEL_ಕ್ರಮ_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            ಹಿಂತಿರುಗಿ lossy;
        }
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
        }
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_NATIVE:
        ಆದರೆ (channel_layout->ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_CUSTOM) {
            int64_t ಮುಖವಾಡ_2 = masked_description(channel_layout, 0);
            ಆದರೆ (ಮುಖವಾಡ_2 < 0)
                ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
            lossy = has_channel_ಹೆಸರುಗಳು(channel_layout);
            ಆದರೆ (!lossy || allow_lossy) {
                ಶೂನ್ಯ *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_ಮುಖವಾಡ(channel_layout, ಮುಖವಾಡ_2);
                channel_layout->opaque = opaque;
                ಹಿಂತಿರುಗಿ lossy;
            }
        }
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_CUSTOM: {
        AVChannelLayout custom = { 0 };
        ಪೂರ್ಣಾಂಕ ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        ಶೂನ್ಯ *opaque = channel_layout->opaque;
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;
        ಆದರೆ (channel_layout->ಕ್ರಮ != AV_CHANNEL_ಕ್ರಮ_UNSPEC)
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_ಸೂಚ್ಯಂಕ(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        ಹಿಂತಿರುಗಿ 0;
        }
    ಸ್ಥಿತಿ AV_CHANNEL_ಕ್ರಮ_AMBISONIC:
        ಆದರೆ (channel_layout->ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_CUSTOM) {
            int64_t ಮುಖವಾಡ_2;
            ಪೂರ್ಣಾಂಕ nb_channels = channel_layout->nb_channels;
            ಪೂರ್ಣಾಂಕ amb_ಕ್ರಮ = av_channel_layout_ambisonic_ಕ್ರಮ(channel_layout);
            ಆದರೆ (amb_ಕ್ರಮ < 0)
                ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
            ಮುಖವಾಡ_2 = masked_description(channel_layout, (amb_ಕ್ರಮ + 1) * (amb_ಕ್ರಮ + 1));
            ಆದರೆ (ಮುಖವಾಡ_2 < 0)
                ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
            lossy = has_channel_ಹೆಸರುಗಳು(channel_layout);
            ಆದರೆ (!lossy || allow_lossy) {
                ಶೂನ್ಯ *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->ಕ್ರಮ       = AV_CHANNEL_ಕ್ರಮ_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.ಮುಖವಾಡ_2      = ಮುಖವಾಡ_2;
                channel_layout->opaque      = opaque;
                ಹಿಂತಿರುಗಿ lossy;
            }
        }
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }
}
