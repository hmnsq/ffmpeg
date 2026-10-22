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

#define CHAN_IS_AMBI(x) ((x) >= AV_CHAN_AMBISONIC_BASE &&\
                         (x) <= AV_CHAN_AMBISONIC_END)

ಸಂರಚನಾ channel_name {
    ಧ್ರುವ ವರ್ಣ *name;
    ಧ್ರುವ ವರ್ಣ *description;
};

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ channel_name channel_names[] = {
    [AV_CHAN_FRONT_ಎಡ           ] = { "FL",        "front left"            },
    [AV_CHAN_FRONT_ಬಲ          ] = { "FR",        "front right"           },
    [AV_CHAN_FRONT_CENTER         ] = { "FC",        "front center"          },
    [AV_CHAN_ಕೆಳಗಿನ_FREQUENCY        ] = { "LFE",       "low frequency"         },
    [AV_CHAN_BACK_ಎಡ            ] = { "BL",        "back left"             },
    [AV_CHAN_BACK_ಬಲ           ] = { "BR",        "back right"            },
    [AV_CHAN_FRONT_ಎಡ_OF_CENTER ] = { "FLC",       "front left-of-center"  },
    [AV_CHAN_FRONT_ಬಲ_OF_CENTER] = { "FRC",       "front right-of-center" },
    [AV_CHAN_BACK_CENTER          ] = { "BC",        "back center"           },
    [AV_CHAN_SIDE_ಎಡ            ] = { "SL",        "side left"             },
    [AV_CHAN_SIDE_ಬಲ           ] = { "SR",        "side right"            },
    [AV_CHAN_ತುದಿ_CENTER           ] = { "TC",        "top center"            },
    [AV_CHAN_ತುದಿ_FRONT_ಎಡ       ] = { "TFL",       "top front left"        },
    [AV_CHAN_ತುದಿ_FRONT_CENTER     ] = { "TFC",       "top front center"      },
    [AV_CHAN_ತುದಿ_FRONT_ಬಲ      ] = { "TFR",       "top front right"       },
    [AV_CHAN_ತುದಿ_BACK_ಎಡ        ] = { "TBL",       "top back left"         },
    [AV_CHAN_ತುದಿ_BACK_CENTER      ] = { "TBC",       "top back center"       },
    [AV_CHAN_ತುದಿ_BACK_ಬಲ       ] = { "TBR",       "top back right"        },
    [AV_CHAN_STEREO_ಎಡ          ] = { "DL",        "downmix left"          },
    [AV_CHAN_STEREO_ಬಲ         ] = { "DR",        "downmix right"         },
    [AV_CHAN_WIDE_ಎಡ            ] = { "WL",        "wide left"             },
    [AV_CHAN_WIDE_ಬಲ           ] = { "WR",        "wide right"            },
    [AV_CHAN_SURROUND_DIRECT_ಎಡ ] = { "SDL",       "surround direct left"  },
    [AV_CHAN_SURROUND_DIRECT_ಬಲ] = { "SDR",       "surround direct right" },
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

ಶೂನ್ಯ av_channel_name_bprint(AVBPrint *bp, ಗಣನಾ AVChannel channel_id)
{
    ಯದಿ (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_BASE);
    ಅನ್ಯಥಾ ಯದಿ ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].name)
        av_bprintf(bp, "%s", channel_names[channel_id].name);
    ಅನ್ಯಥಾ ಯದಿ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    ಅನ್ಯಥಾ ಯದಿ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    ಅನ್ಯಥಾ ಯದಿ (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "UNSD");
    ಅನ್ಯಥಾ
        av_bprintf(bp, "USR%d", channel_id);
}

ಪೂರ್ಣಾಙ್ಕ av_channel_name(ವರ್ಣ *buf, size_t buf_size, ಗಣನಾ AVChannel channel_id)
{
    AVBPrint bp;

    ಯದಿ (!buf && buf_size)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_name_bprint(&bp, channel_id);

    ಯದಿ (bp.len >= INT_MAX)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ERANGE);
    ಪ್ರತ್ಯಾಗಮ bp.len + 1;
}

ಶೂನ್ಯ av_channel_description_bprint(AVBPrint *bp, ಗಣನಾ AVChannel channel_id)
{
    ಯದಿ (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_BASE);
    ಅನ್ಯಥಾ ಯದಿ ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].description)
        av_bprintf(bp, "%s", channel_names[channel_id].description);
    ಅನ್ಯಥಾ ಯದಿ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    ಅನ್ಯಥಾ ಯದಿ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    ಅನ್ಯಥಾ ಯದಿ (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "unused");
    ಅನ್ಯಥಾ
        av_bprintf(bp, "user %d", channel_id);
}

ಪೂರ್ಣಾಙ್ಕ av_channel_description(ವರ್ಣ *buf, size_t buf_size, ಗಣನಾ AVChannel channel_id)
{
    AVBPrint bp;

    ಯದಿ (!buf && buf_size)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_description_bprint(&bp, channel_id);

    ಯದಿ (bp.len >= INT_MAX)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ERANGE);
    ಪ್ರತ್ಯಾಗಮ bp.len + 1;
}

ಗಣನಾ AVChannel av_channel_from_string(ಧ್ರುವ ವರ್ಣ *str)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ವರ್ಣ *endptr = (ವರ್ಣ *)str;
    ಗಣನಾ AVChannel id = AV_CHAN_NONE;

    ಯದಿ (!strncmp(str, "AMBI", 4)) {
        i = strtol(str + 4, ರಿಕ್ತ, 0);
        ಯದಿ (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            ಪ್ರತ್ಯಾಗಮ AV_CHAN_NONE;
        ಪ್ರತ್ಯಾಗಮ AV_CHAN_AMBISONIC_BASE + i;
    }

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        ಯದಿ (channel_names[i].name && !strcmp(str, channel_names[i].name))
            ಪ್ರತ್ಯಾಗಮ i;
    }
    ಯದಿ (!strcmp(str, "UNK"))
        ಪ್ರತ್ಯಾಗಮ AV_CHAN_UNKNOWN;
    ಯದಿ (!strcmp(str, "UNSD"))
        ಪ್ರತ್ಯಾಗಮ AV_CHAN_UNUSED;

    ಯದಿ (!strncmp(str, "USR", 3)) {
        ಧ್ರುವ ವರ್ಣ *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    ಯದಿ (id >= 0 && !*endptr)
        ಪ್ರತ್ಯಾಗಮ id;

    ಪ್ರತ್ಯಾಗಮ AV_CHAN_NONE;
}

ಸಂರಚನಾ channel_layout_name {
    ಧ್ರುವ ವರ್ಣ *name;
    AVChannelLayout layout;
};

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ channel_layout_name channel_layout_map[] = {
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

ಪೂರ್ಣಾಙ್ಕ av_channel_layout_custom_init(AVChannelLayout *channel_layout, ಪೂರ್ಣಾಙ್ಕ nb_channels)
{
    AVChannelCustom *map;

    ಯದಿ (nb_channels <= 0)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    map = av_calloc(nb_channels, ಪರಿಮಾಣ(*channel_layout->u.map));
    ಯದಿ (!map)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->order       = AV_CHANNEL_ORDER_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_channel_layout_from_mask(AVChannelLayout *channel_layout,
                                uint64_t mask)
{
    ಯದಿ (!mask)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    channel_layout->order       = AV_CHANNEL_ORDER_NATIVE;
    channel_layout->nb_channels = av_popcount64(mask);
    channel_layout->u.mask      = mask;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ parse_channel_list(AVChannelLayout *ch_layout, ಧ್ರುವ ವರ್ಣ *str)
{
    ಪೂರ್ಣಾಙ್ಕ ret;
    ಪೂರ್ಣಾಙ್ಕ nb_channels = 0;
    AVChannelCustom *map = ರಿಕ್ತ;
    AVChannelCustom custom = {0};

    ಯಾವತ್ (*str) {
        ವರ್ಣ *channel, *chname;
        ret = av_opt_get_ಕೀಲಿ_ಮೌಲ್ಯ(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_ಕೀಲಿ, &channel, &chname);
        ಯದಿ (ret < 0) {
            av_freep(&map);
            ಪ್ರತ್ಯಾಗಮ ret;
        }
        ಯದಿ (*str)
            str++; // skip separator
        ಯದಿ (!channel) {
            channel = chname;
            chname = ರಿಕ್ತ;
        }
        av_strlcpy(custom.name, chname ? chname : "", ಪರಿಮಾಣ(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        ಯದಿ (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }

        av_dynarray2_add((ಶೂನ್ಯ **)&map, &nb_channels, ಪರಿಮಾಣ(custom), (ಶೂನ್ಯ *)&custom);
        ಯದಿ (!map)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }

    ಯದಿ (!nb_channels)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ch_layout->order = AV_CHANNEL_ORDER_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  ಧ್ರುವ ವರ್ಣ *str)
{
    ಪೂರ್ಣಾಙ್ಕ i, matches, ret;
    ಪೂರ್ಣಾಙ್ಕ channels = 0, nb_channels = 0;
    ವರ್ಣ *chlist, *end;
    uint64_t mask = 0;

    /* channel layout names */
    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        ಯದಿ (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            ಪ್ರತ್ಯಾಗಮ 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, ಪರಿಮಾಣ(*channel_layout));

    /* ambisonic */
    ಯದಿ (!strncmp(str, "ambisonic ", 10)) {
        ಧ್ರುವ ವರ್ಣ *p = str + 10;
        ವರ್ಣ *endptr;
        AVChannelLayout extra = {0};
        ಪೂರ್ಣಾಙ್ಕ order;

        order = strtol(p, &endptr, 0);
        ಯದಿ (order < 0 || order + 1  > INT_MAX / (order + 1) ||
            (*endptr && *endptr != '+'))
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        ಯದಿ (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            ಯದಿ (ret < 0)
                ಪ್ರತ್ಯಾಗಮ ret;
            ಯದಿ (extra.nb_channels >= INT_MAX - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
            }

            ಯದಿ (extra.order == AV_CHANNEL_ORDER_NATIVE) {
                channel_layout->u.mask = extra.u.mask;
            } ಅನ್ಯಥಾ {
                channel_layout->order = AV_CHANNEL_ORDER_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              ಪರಿಮಾಣ(*channel_layout->u.map));
                ಯದಿ (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
                }

                ಪ್ರತಿ (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                ಪ್ರತಿ (i = 0; i < extra.nb_channels; i++) {
                    ಗಣನಾ AVChannel ch = av_channel_layout_channel_from_index(&extra, i);
                    ಯದಿ (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    ಯದಿ (extra.order == AV_CHANNEL_ORDER_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   ಪರಿಮಾಣ(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        ಪ್ರತ್ಯಾಗಮ 0;
    }

    chlist = av_strdup(str);
    ಯದಿ (!chlist)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    ಯದಿ (ret < 0 && ret != AVERROR(EINVAL))
        ಪ್ರತ್ಯಾಗಮ ret;

    ಯದಿ (ret >= 0) {
        ಧ್ರುವ ವರ್ಣ *end_par = strchr(str, ')');
        ಯದಿ (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    errno = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    ಯದಿ (!errno && !*end && !strchr(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    errno = 0;
    channels = strtol(str, &end, 10);

    /* number of channels */
    ಯದಿ (!errno && !strcmp(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        ಯದಿ (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            ಪ್ರತ್ಯಾಗಮ 0;
    }

    /* number of unordered channels */
    ಯದಿ (!errno && (!strcmp(end, "C") || !strcmp(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
}

ಶೂನ್ಯ av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    ಯದಿ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, ಪರಿಮಾಣ(*channel_layout));
}

ಪೂರ್ಣಾಙ್ಕ av_channel_layout_copy(AVChannelLayout *dst, ಧ್ರುವ AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    ಯದಿ (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, ಪರಿಮಾಣ(*dst->u.map));
        ಯದಿ (!dst->u.map)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        memcpy(dst->u.map, src->u.map, src->nb_channels * ಪರಿಮಾಣ(*src->u.map));
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ int64_t masked_description(ಧ್ರುವ AVChannelLayout *channel_layout, ಪೂರ್ಣಾಙ್ಕ start_channel)
{
    uint64_t mask = 0;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = start_channel; i < channel_layout->nb_channels; i++) {
        ಗಣನಾ AVChannel ch = channel_layout->u.map[i].id;
        ಯದಿ (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        ಅನ್ಯಥಾ
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }
    ಪ್ರತ್ಯಾಗಮ mask;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ has_channel_names(ಧ್ರುವ AVChannelLayout *channel_layout)
{
    ಯದಿ (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ಪ್ರತ್ಯಾಗಮ 0;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < channel_layout->nb_channels; i++)
        ಯದಿ (channel_layout->u.map[i].name[0])
            ಪ್ರತ್ಯಾಗಮ 1;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_channel_layout_ambisonic_order(ಧ್ರುವ AVChannelLayout *channel_layout)
{
    ಪೂರ್ಣಾಙ್ಕ i, highest_ambi, order;

    ಯದಿ (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    highest_ambi = -1;
    ಯದಿ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    ಅನ್ಯಥಾ {
        ಧ್ರುವ AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        ಪ್ರತಿ (i = 0; i < channel_layout->nb_channels; i++) {
            ಪೂರ್ಣಾಙ್ಕ is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            ಯದಿ (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

            /* non-default ordering */
            ಯದಿ (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

            ಯದಿ (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    ಯದಿ (highest_ambi < 0)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    order = floor(sqrt(highest_ambi));
    /* incomplete order - some harmonics are missing */
    ಯದಿ ((order + 1) * (order + 1) != highest_ambi + 1)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಪ್ರತ್ಯಾಗಮ order;
}

ಸ್ಥಿರ ಗಣನಾ AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    ಪೂರ್ಣಾಙ್ಕ has_known_channel = 0;
    ಪೂರ್ಣಾಙ್ಕ order;

    ಯದಿ (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ಪ್ರತ್ಯಾಗಮ channel_layout->order;

    ಯದಿ (has_channel_names(channel_layout))
        ಪ್ರತ್ಯಾಗಮ AV_CHANNEL_ORDER_CUSTOM;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        ಯದಿ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    ಯದಿ (!has_known_channel)
        ಪ್ರತ್ಯಾಗಮ AV_CHANNEL_ORDER_UNSPEC;

    ಯದಿ (masked_description(channel_layout, 0) > 0)
        ಪ್ರತ್ಯಾಗಮ AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    ಯದಿ (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
        ಪ್ರತ್ಯಾಗಮ AV_CHANNEL_ORDER_AMBISONIC;

    ಪ್ರತ್ಯಾಗಮ AV_CHANNEL_ORDER_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ try_describe_ambisonic(AVBPrint *bp, ಧ್ರುವ AVChannelLayout *channel_layout)
{
    ಪೂರ್ಣಾಙ್ಕ nb_ambi_channels;
    ಪೂರ್ಣಾಙ್ಕ order = av_channel_layout_ambisonic_order(channel_layout);
    ಯದಿ (order < 0)
        ಪ್ರತ್ಯಾಗಮ order;

    av_bprintf(bp, "ambisonic %d", order);

    /* extra channels present */
    nb_ambi_channels = (order + 1) * (order + 1);
    ಯದಿ (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        ಯದಿ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC) {
            extra.order       = AV_CHANNEL_ORDER_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.mask);
            extra.u.mask      = channel_layout->u.mask;
        } ಅನ್ಯಥಾ {
            int64_t mask;
            ಯದಿ (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.order       = AV_CHANNEL_ORDER_NATIVE;
                extra.nb_channels = av_popcount64(mask);
                extra.u.mask      = mask;
            } ಅನ್ಯಥಾ {
                extra.order       = AV_CHANNEL_ORDER_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_channel_layout_describe_bprint(ಧ್ರುವ AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ವಿಕಲ್ಪ (channel_layout->order) {
    ಪಕ್ಷ AV_CHANNEL_ORDER_NATIVE:
        ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            ಯದಿ (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                ಪ್ರತ್ಯಾಗಮ 0;
            }
        av_fallthrough;
    ಪಕ್ಷ AV_CHANNEL_ORDER_CUSTOM:
        ಯದಿ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            ಪೂರ್ಣಾಙ್ಕ res = try_describe_ambisonic(bp, channel_layout);
            ಯದಿ (res >= 0)
                ಪ್ರತ್ಯಾಗಮ 0;
            ಯದಿ (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                ಪ್ರತ್ಯಾಗಮ av_channel_layout_describe_bprint(&native, bp);
            }
        }
        ಯದಿ (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        ಪ್ರತಿ (i = 0; i < channel_layout->nb_channels; i++) {
            ಗಣನಾ AVChannel ch = av_channel_layout_channel_from_index(channel_layout, i);

            ಯದಿ (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            ಯದಿ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        ಯದಿ (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            ಪ್ರತ್ಯಾಗಮ 0;
        }
        av_fallthrough;
    ಪಕ್ಷ AV_CHANNEL_ORDER_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        ಪ್ರತ್ಯಾಗಮ 0;
    ಪಕ್ಷ AV_CHANNEL_ORDER_AMBISONIC:
        ಪ್ರತ್ಯಾಗಮ try_describe_ambisonic(bp, channel_layout);
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }
}

ಪೂರ್ಣಾಙ್ಕ av_channel_layout_describe(ಧ್ರುವ AVChannelLayout *channel_layout,
                               ವರ್ಣ *buf, size_t buf_size)
{
    AVBPrint bp;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (!buf && buf_size)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ಯದಿ (bp.len >= INT_MAX)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ERANGE);
    ಪ್ರತ್ಯಾಗಮ bp.len + 1;
}

ಗಣನಾ AVChannel
av_channel_layout_channel_from_index(ಧ್ರುವ AVChannelLayout *channel_layout,
                                     unsigned ಪೂರ್ಣಾಙ್ಕ idx)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಯದಿ (idx >= channel_layout->nb_channels)
        ಪ್ರತ್ಯಾಗಮ AV_CHAN_NONE;

    ವಿಕಲ್ಪ (channel_layout->order) {
    ಪಕ್ಷ AV_CHANNEL_ORDER_CUSTOM:
        ಪ್ರತ್ಯಾಗಮ channel_layout->u.map[idx].id;
    ಪಕ್ಷ AV_CHANNEL_ORDER_AMBISONIC: {
        ಪೂರ್ಣಾಙ್ಕ ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        ಯದಿ (idx < ambi_channels)
            ಪ್ರತ್ಯಾಗಮ AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    ಪಕ್ಷ AV_CHANNEL_ORDER_NATIVE:
        ಪ್ರತಿ (i = 0; i < 64; i++) {
            ಯದಿ ((1ULL << i) & channel_layout->u.mask && !idx--)
                ಪ್ರತ್ಯಾಗಮ i;
        }
        av_fallthrough;
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ AV_CHAN_NONE;
    }
}

ಗಣನಾ AVChannel
av_channel_layout_channel_from_string(ಧ್ರುವ AVChannelLayout *channel_layout,
                                      ಧ್ರುವ ವರ್ಣ *str)
{
    ಪೂರ್ಣಾಙ್ಕ index = av_channel_layout_index_from_string(channel_layout, str);

    ಯದಿ (index < 0)
        ಪ್ರತ್ಯಾಗಮ AV_CHAN_NONE;

    ಪ್ರತ್ಯಾಗಮ av_channel_layout_channel_from_index(channel_layout, index);
}

ಪೂರ್ಣಾಙ್ಕ av_channel_layout_index_from_channel(ಧ್ರುವ AVChannelLayout *channel_layout,
                                         ಗಣನಾ AVChannel channel)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಯದಿ (channel == AV_CHAN_NONE)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ವಿಕಲ್ಪ (channel_layout->order) {
    ಪಕ್ಷ AV_CHANNEL_ORDER_CUSTOM:
        ಪ್ರತಿ (i = 0; i < channel_layout->nb_channels; i++)
            ಯದಿ (channel_layout->u.map[i].id == channel)
                ಪ್ರತ್ಯಾಗಮ i;
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    ಪಕ್ಷ AV_CHANNEL_ORDER_AMBISONIC:
    ಪಕ್ಷ AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        ಪೂರ್ಣಾಙ್ಕ ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        ಯದಿ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            ಯದಿ (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
            ಪ್ರತ್ಯಾಗಮ channel - AV_CHAN_AMBISONIC_BASE;
        }
        ಯದಿ ((unsigned)channel > 63 || !(mask & (1ULL << channel)))
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        mask &= (1ULL << channel) - 1;
        ಪ್ರತ್ಯಾಗಮ av_popcount64(mask) + ambi_channels;
        }
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }
}

ಪೂರ್ಣಾಙ್ಕ av_channel_layout_index_from_string(ಧ್ರುವ AVChannelLayout *channel_layout,
                                        ಧ್ರುವ ವರ್ಣ *str)
{
    ಧ್ರುವ ವರ್ಣ *chname;
    ಗಣನಾ AVChannel ch = AV_CHAN_NONE;

    ವಿಕಲ್ಪ (channel_layout->order) {
    ಪಕ್ಷ AV_CHANNEL_ORDER_CUSTOM:
        chname = strstr(str, "@");
        ಯದಿ (chname) {
            ವರ್ಣ buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(ಪರಿಮಾಣ(buf), chname - str));
            ಯದಿ (!*chname)
                chname = ರಿಕ್ತ;
            ch = av_channel_from_string(buf);
            ಯದಿ (ch == AV_CHAN_NONE && *buf)
                ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; chname && i < channel_layout->nb_channels; i++) {
            ಯದಿ (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                ಪ್ರತ್ಯಾಗಮ i;
        }
        av_fallthrough;
    ಪಕ್ಷ AV_CHANNEL_ORDER_AMBISONIC:
    ಪಕ್ಷ AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        ಯದಿ (ch == AV_CHAN_NONE)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        ಪ್ರತ್ಯಾಗಮ av_channel_layout_index_from_channel(channel_layout, ch);
    }

    ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
}

ಪೂರ್ಣಾಙ್ಕ av_channel_layout_check(ಧ್ರುವ AVChannelLayout *channel_layout)
{
    ಯದಿ (channel_layout->nb_channels <= 0)
        ಪ್ರತ್ಯಾಗಮ 0;

    ವಿಕಲ್ಪ (channel_layout->order) {
    ಪಕ್ಷ AV_CHANNEL_ORDER_NATIVE:
        ಪ್ರತ್ಯಾಗಮ av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    ಪಕ್ಷ AV_CHANNEL_ORDER_CUSTOM:
        ಯದಿ (!channel_layout->u.map)
            ಪ್ರತ್ಯಾಗಮ 0;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < channel_layout->nb_channels; i++) {
            ಯದಿ (channel_layout->u.map[i].id == AV_CHAN_NONE)
                ಪ್ರತ್ಯಾಗಮ 0;
        }
        ಪ್ರತ್ಯಾಗಮ 1;
    ಪಕ್ಷ AV_CHANNEL_ORDER_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        ಪ್ರತ್ಯಾಗಮ av_popcount64(channel_layout->u.mask) < channel_layout->nb_channels;
    ಪಕ್ಷ AV_CHANNEL_ORDER_UNSPEC:
        ಪ್ರತ್ಯಾಗಮ 1;
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ 0;
    }
}

ಪೂರ್ಣಾಙ್ಕ av_channel_layout_compare(ಧ್ರುವ AVChannelLayout *chl, ಧ್ರುವ AVChannelLayout *chl1)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    /* different channel counts -> not equal */
    ಯದಿ (chl->nb_channels != chl1->nb_channels)
        ಪ್ರತ್ಯಾಗಮ 1;

    /* if only one is unspecified -> not equal */
    ಯದಿ ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        ಪ್ರತ್ಯಾಗಮ 1;
    /* both are unspecified -> equal */
    ಅನ್ಯಥಾ ಯದಿ (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        ಪ್ರತ್ಯಾಗಮ 0;

    /* can compare masks directly */
    ಯದಿ ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        ಪ್ರತ್ಯಾಗಮ chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    ಪ್ರತಿ (i = 0; i < chl->nb_channels; i++)
        ಯದಿ (av_channel_layout_channel_from_index(chl,  i) !=
            av_channel_layout_channel_from_index(chl1, i))
            ಪ್ರತ್ಯಾಗಮ 1;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ av_channel_layout_default(AVChannelLayout *ch_layout, ಪೂರ್ಣಾಙ್ಕ nb_channels)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        ಯದಿ (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            ಪ್ರತ್ಯಾಗಮ;
        }

    ch_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

ಧ್ರುವ AVChannelLayout *av_channel_layout_standard(ಶೂನ್ಯ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ಧ್ರುವ AVChannelLayout *ch_layout = ರಿಕ್ತ;

    ಯದಿ (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (ಶೂನ್ಯ*)(i + 1);
    }

    ಪ್ರತ್ಯಾಗಮ ch_layout;
}

uint64_t av_channel_layout_subset(ಧ್ರುವ AVChannelLayout *channel_layout,
                                  uint64_t mask)
{
    uint64_t ret = 0;
    ಪೂರ್ಣಾಙ್ಕ i;

    ವಿಕಲ್ಪ (channel_layout->order) {
    ಪಕ್ಷ AV_CHANNEL_ORDER_NATIVE:
    ಪಕ್ಷ AV_CHANNEL_ORDER_AMBISONIC:
        ಪ್ರತ್ಯಾಗಮ channel_layout->u.mask & mask;
    ಪಕ್ಷ AV_CHANNEL_ORDER_CUSTOM:
        ಪ್ರತಿ (i = 0; i < 64; i++)
            ಯದಿ (mask & (1ULL << i) && av_channel_layout_index_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        ಭಙ್ಗ;
    }

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_channel_layout_retype(AVChannelLayout *channel_layout, ಗಣನಾ AVChannelOrder order, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಪೂರ್ಣಾಙ್ಕ allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    ಪೂರ್ಣಾಙ್ಕ lossy;

    ಯದಿ (!av_channel_layout_check(channel_layout))
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಯದಿ (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    ಯದಿ (channel_layout->order == order)
        ಪ್ರತ್ಯಾಗಮ 0;

    ವಿಕಲ್ಪ (order) {
    ಪಕ್ಷ AV_CHANNEL_ORDER_UNSPEC: {
        ಪೂರ್ಣಾಙ್ಕ nb_channels = channel_layout->nb_channels;
        ಯದಿ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_channels; i++) {
                ಯದಿ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    ಭಙ್ಗ;
                }
            }
        } ಅನ್ಯಥಾ {
            lossy = 1;
        }
        ಯದಿ (!lossy || allow_lossy) {
            ಶೂನ್ಯ *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            ಪ್ರತ್ಯಾಗಮ lossy;
        }
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
        }
    ಪಕ್ಷ AV_CHANNEL_ORDER_NATIVE:
        ಯದಿ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            ಯದಿ (mask < 0)
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            ಯದಿ (!lossy || allow_lossy) {
                ಶೂನ್ಯ *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_mask(channel_layout, mask);
                channel_layout->opaque = opaque;
                ಪ್ರತ್ಯಾಗಮ lossy;
            }
        }
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    ಪಕ್ಷ AV_CHANNEL_ORDER_CUSTOM: {
        AVChannelLayout custom = { 0 };
        ಪೂರ್ಣಾಙ್ಕ ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        ಶೂನ್ಯ *opaque = channel_layout->opaque;
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
        ಯದಿ (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_index(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        ಪ್ರತ್ಯಾಗಮ 0;
        }
    ಪಕ್ಷ AV_CHANNEL_ORDER_AMBISONIC:
        ಯದಿ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            ಪೂರ್ಣಾಙ್ಕ nb_channels = channel_layout->nb_channels;
            ಪೂರ್ಣಾಙ್ಕ amb_order = av_channel_layout_ambisonic_order(channel_layout);
            ಯದಿ (amb_order < 0)
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            ಯದಿ (mask < 0)
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            ಯದಿ (!lossy || allow_lossy) {
                ಶೂನ್ಯ *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.mask      = mask;
                channel_layout->opaque      = opaque;
                ಪ್ರತ್ಯಾಗಮ lossy;
            }
        }
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }
}
