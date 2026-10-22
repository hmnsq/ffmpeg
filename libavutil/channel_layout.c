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

#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "channel_layout.h"
#ଅନ୍ତର୍ଭାଵ "bprint.h"
#ଅନ୍ତର୍ଭାଵ "common.h"
#ଅନ୍ତର୍ଭାଵ "error.h"
#ଅନ୍ତର୍ଭାଵ "attributes.h"
#ଅନ୍ତର୍ଭାଵ "macros.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "opt.h"

#define CHAN_IS_AMBI(x) ((x) >= AV_CHAN_AMBISONIC_BASE &&\
                         (x) <= AV_CHAN_AMBISONIC_END)

ସଂରଚନା channel_name {
    ଅଚଳ ଅକ୍ଷର *name;
    ଅଚଳ ଅକ୍ଷର *description;
};

ସ୍ଥିର ଅଚଳ ସଂରଚନା channel_name channel_names[] = {
    [AV_CHAN_FRONT_ବାମ           ] = { "FL",        "front left"            },
    [AV_CHAN_FRONT_ଡାହାଣ          ] = { "FR",        "front right"           },
    [AV_CHAN_FRONT_CENTER         ] = { "FC",        "front center"          },
    [AV_CHAN_ତଳ_FREQUENCY        ] = { "LFE",       "low frequency"         },
    [AV_CHAN_BACK_ବାମ            ] = { "BL",        "back left"             },
    [AV_CHAN_BACK_ଡାହାଣ           ] = { "BR",        "back right"            },
    [AV_CHAN_FRONT_ବାମ_OF_CENTER ] = { "FLC",       "front left-of-center"  },
    [AV_CHAN_FRONT_ଡାହାଣ_OF_CENTER] = { "FRC",       "front right-of-center" },
    [AV_CHAN_BACK_CENTER          ] = { "BC",        "back center"           },
    [AV_CHAN_SIDE_ବାମ            ] = { "SL",        "side left"             },
    [AV_CHAN_SIDE_ଡାହାଣ           ] = { "SR",        "side right"            },
    [AV_CHAN_ଶୀର୍ଷ_CENTER           ] = { "TC",        "top center"            },
    [AV_CHAN_ଶୀର୍ଷ_FRONT_ବାମ       ] = { "TFL",       "top front left"        },
    [AV_CHAN_ଶୀର୍ଷ_FRONT_CENTER     ] = { "TFC",       "top front center"      },
    [AV_CHAN_ଶୀର୍ଷ_FRONT_ଡାହାଣ      ] = { "TFR",       "top front right"       },
    [AV_CHAN_ଶୀର୍ଷ_BACK_ବାମ        ] = { "TBL",       "top back left"         },
    [AV_CHAN_ଶୀର୍ଷ_BACK_CENTER      ] = { "TBC",       "top back center"       },
    [AV_CHAN_ଶୀର୍ଷ_BACK_ଡାହାଣ       ] = { "TBR",       "top back right"        },
    [AV_CHAN_STEREO_ବାମ          ] = { "DL",        "downmix left"          },
    [AV_CHAN_STEREO_ଡାହାଣ         ] = { "DR",        "downmix right"         },
    [AV_CHAN_WIDE_ବାମ            ] = { "WL",        "wide left"             },
    [AV_CHAN_WIDE_ଡାହାଣ           ] = { "WR",        "wide right"            },
    [AV_CHAN_SURROUND_DIRECT_ବାମ ] = { "SDL",       "surround direct left"  },
    [AV_CHAN_SURROUND_DIRECT_ଡାହାଣ] = { "SDR",       "surround direct right" },
    [AV_CHAN_ତଳ_FREQUENCY_2      ] = { "LFE2",      "low frequency 2"       },
    [AV_CHAN_ଶୀର୍ଷ_SIDE_ବାମ        ] = { "TSL",       "top side left"         },
    [AV_CHAN_ଶୀର୍ଷ_SIDE_ଡାହାଣ       ] = { "TSR",       "top side right"        },
    [AV_CHAN_BOTTOM_FRONT_CENTER  ] = { "BFC",       "bottom front center"   },
    [AV_CHAN_BOTTOM_FRONT_ବାମ    ] = { "BFL",       "bottom front left"     },
    [AV_CHAN_BOTTOM_FRONT_ଡାହାଣ   ] = { "BFR",       "bottom front right"    },
    [AV_CHAN_SIDE_SURROUND_ବାମ   ] = { "SSL",       "side surround left"    },
    [AV_CHAN_SIDE_SURROUND_ଡାହାଣ  ] = { "SSR",       "side surround right"   },
    [AV_CHAN_ଶୀର୍ଷ_SURROUND_ବାମ    ] = { "TTL",       "top surround left"     },
    [AV_CHAN_ଶୀର୍ଷ_SURROUND_ଡାହାଣ   ] = { "TTR",       "top surround right"    },
    [AV_CHAN_BINAURAL_ବାମ        ] = { "BIL",       "binaural left"         },
    [AV_CHAN_BINAURAL_ଡାହାଣ       ] = { "BIR",       "binaural right"        },
};

ଶୂନ୍ୟ av_channel_name_bprint(AVBPrint *bp, ଗଣନା AVChannel channel_id)
{
    ଯଦି (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_BASE);
    ଅନ୍ୟଥା ଯଦି ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].name)
        av_bprintf(bp, "%s", channel_names[channel_id].name);
    ଅନ୍ୟଥା ଯଦି (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    ଅନ୍ୟଥା ଯଦି (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    ଅନ୍ୟଥା ଯଦି (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "UNSD");
    ଅନ୍ୟଥା
        av_bprintf(bp, "USR%d", channel_id);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_channel_name(ଅକ୍ଷର *buf, size_t buf_size, ଗଣନା AVChannel channel_id)
{
    AVBPrint bp;

    ଯଦି (!buf && buf_size)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_name_bprint(&bp, channel_id);

    ଯଦି (bp.len >= INT_MAX)
        ଫେରନ୍ତୁ AVERROR(ERANGE);
    ଫେରନ୍ତୁ bp.len + 1;
}

ଶୂନ୍ୟ av_channel_description_bprint(AVBPrint *bp, ଗଣନା AVChannel channel_id)
{
    ଯଦି (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_BASE);
    ଅନ୍ୟଥା ଯଦି ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].description)
        av_bprintf(bp, "%s", channel_names[channel_id].description);
    ଅନ୍ୟଥା ଯଦି (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    ଅନ୍ୟଥା ଯଦି (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    ଅନ୍ୟଥା ଯଦି (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "unused");
    ଅନ୍ୟଥା
        av_bprintf(bp, "user %d", channel_id);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_channel_description(ଅକ୍ଷର *buf, size_t buf_size, ଗଣନା AVChannel channel_id)
{
    AVBPrint bp;

    ଯଦି (!buf && buf_size)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_description_bprint(&bp, channel_id);

    ଯଦି (bp.len >= INT_MAX)
        ଫେରନ୍ତୁ AVERROR(ERANGE);
    ଫେରନ୍ତୁ bp.len + 1;
}

ଗଣନା AVChannel av_channel_from_string(ଅଚଳ ଅକ୍ଷର *str)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ଅକ୍ଷର *endptr = (ଅକ୍ଷର *)str;
    ଗଣନା AVChannel id = AV_CHAN_NONE;

    ଯଦି (!strncmp(str, "AMBI", 4)) {
        i = strtol(str + 4, ଖାଲି, 0);
        ଯଦି (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            ଫେରନ୍ତୁ AV_CHAN_NONE;
        ଫେରନ୍ତୁ AV_CHAN_AMBISONIC_BASE + i;
    }

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        ଯଦି (channel_names[i].name && !strcmp(str, channel_names[i].name))
            ଫେରନ୍ତୁ i;
    }
    ଯଦି (!strcmp(str, "UNK"))
        ଫେରନ୍ତୁ AV_CHAN_UNKNOWN;
    ଯଦି (!strcmp(str, "UNSD"))
        ଫେରନ୍ତୁ AV_CHAN_UNUSED;

    ଯଦି (!strncmp(str, "USR", 3)) {
        ଅଚଳ ଅକ୍ଷର *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    ଯଦି (id >= 0 && !*endptr)
        ଫେରନ୍ତୁ id;

    ଫେରନ୍ତୁ AV_CHAN_NONE;
}

ସଂରଚନା channel_layout_name {
    ଅଚଳ ଅକ୍ଷର *name;
    AVChannelLayout layout;
};

ସ୍ଥିର ଅଚଳ ସଂରଚନା channel_layout_name channel_layout_map[] = {
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

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_channel_layout_custom_init(AVChannelLayout *channel_layout, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_channels)
{
    AVChannelCustom *map;

    ଯଦି (nb_channels <= 0)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    map = av_calloc(nb_channels, ଆକାର(*channel_layout->u.map));
    ଯଦି (!map)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->order       = AV_CHANNEL_ORDER_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_channel_layout_from_mask(AVChannelLayout *channel_layout,
                                uint64_t mask)
{
    ଯଦି (!mask)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    channel_layout->order       = AV_CHANNEL_ORDER_NATIVE;
    channel_layout->nb_channels = av_popcount64(mask);
    channel_layout->u.mask      = mask;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା parse_channel_list(AVChannelLayout *ch_layout, ଅଚଳ ଅକ୍ଷର *str)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_channels = 0;
    AVChannelCustom *map = ଖାଲି;
    AVChannelCustom custom = {0};

    ଯେତେବେଳେ (*str) {
        ଅକ୍ଷର *channel, *chname;
        ret = av_opt_get_ଚାବି_ମୂଲ୍ୟ(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_ଚାବି, &channel, &chname);
        ଯଦି (ret < 0) {
            av_freep(&map);
            ଫେରନ୍ତୁ ret;
        }
        ଯଦି (*str)
            str++; // skip separator
        ଯଦି (!channel) {
            channel = chname;
            chname = ଖାଲି;
        }
        av_strlcpy(custom.name, chname ? chname : "", ଆକାର(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        ଯଦି (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }

        av_dynarray2_add((ଶୂନ୍ୟ **)&map, &nb_channels, ଆକାର(custom), (ଶୂନ୍ୟ *)&custom);
        ଯଦି (!map)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

    ଯଦି (!nb_channels)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ch_layout->order = AV_CHANNEL_ORDER_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  ଅଚଳ ଅକ୍ଷର *str)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, matches, ret;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା channels = 0, nb_channels = 0;
    ଅକ୍ଷର *chlist, *end;
    uint64_t mask = 0;

    /* channel layout names */
    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        ଯଦି (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            ଫେରନ୍ତୁ 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, ଆକାର(*channel_layout));

    /* ambisonic */
    ଯଦି (!strncmp(str, "ambisonic ", 10)) {
        ଅଚଳ ଅକ୍ଷର *p = str + 10;
        ଅକ୍ଷର *endptr;
        AVChannelLayout extra = {0};
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା order;

        order = strtol(p, &endptr, 0);
        ଯଦି (order < 0 || order + 1  > INT_MAX / (order + 1) ||
            (*endptr && *endptr != '+'))
            ଫେରନ୍ତୁ AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        ଯଦି (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            ଯଦି (ret < 0)
                ଫେରନ୍ତୁ ret;
            ଯଦି (extra.nb_channels >= INT_MAX - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                ଫେରନ୍ତୁ AVERROR(EINVAL);
            }

            ଯଦି (extra.order == AV_CHANNEL_ORDER_NATIVE) {
                channel_layout->u.mask = extra.u.mask;
            } ଅନ୍ୟଥା {
                channel_layout->order = AV_CHANNEL_ORDER_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              ଆକାର(*channel_layout->u.map));
                ଯଦି (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    ଫେରନ୍ତୁ AVERROR(ENOMEM);
                }

                ପାଇଁ (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                ପାଇଁ (i = 0; i < extra.nb_channels; i++) {
                    ଗଣନା AVChannel ch = av_channel_layout_channel_from_index(&extra, i);
                    ଯଦି (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        ଫେରନ୍ତୁ AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    ଯଦି (extra.order == AV_CHANNEL_ORDER_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   ଆକାର(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        ଫେରନ୍ତୁ 0;
    }

    chlist = av_strdup(str);
    ଯଦି (!chlist)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    ଯଦି (ret < 0 && ret != AVERROR(EINVAL))
        ଫେରନ୍ତୁ ret;

    ଯଦି (ret >= 0) {
        ଅଚଳ ଅକ୍ଷର *end_par = strchr(str, ')');
        ଯଦି (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }
        ଫେରନ୍ତୁ 0;
    }

    errno = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    ଯଦି (!errno && !*end && !strchr(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        ଫେରନ୍ତୁ 0;
    }

    errno = 0;
    channels = strtol(str, &end, 10);

    /* number of channels */
    ଯଦି (!errno && !strcmp(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        ଯଦି (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            ଫେରନ୍ତୁ 0;
    }

    /* number of unordered channels */
    ଯଦି (!errno && (!strcmp(end, "C") || !strcmp(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        ଫେରନ୍ତୁ 0;
    }

    ଫେରନ୍ତୁ AVERROR(EINVAL);
}

ଶୂନ୍ୟ av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    ଯଦି (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, ଆକାର(*channel_layout));
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_channel_layout_copy(AVChannelLayout *dst, ଅଚଳ AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    ଯଦି (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, ଆକାର(*dst->u.map));
        ଯଦି (!dst->u.map)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        memcpy(dst->u.map, src->u.map, src->nb_channels * ଆକାର(*src->u.map));
    }
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର int64_t masked_description(ଅଚଳ AVChannelLayout *channel_layout, ପୂର୍ଣ୍ଣସଂଖ୍ୟା start_channel)
{
    uint64_t mask = 0;
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = start_channel; i < channel_layout->nb_channels; i++) {
        ଗଣନା AVChannel ch = channel_layout->u.map[i].id;
        ଯଦି (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        ଅନ୍ୟଥା
            ଫେରନ୍ତୁ AVERROR(EINVAL);
    }
    ଫେରନ୍ତୁ mask;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା has_channel_names(ଅଚଳ AVChannelLayout *channel_layout)
{
    ଯଦି (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ଫେରନ୍ତୁ 0;
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < channel_layout->nb_channels; i++)
        ଯଦି (channel_layout->u.map[i].name[0])
            ଫେରନ୍ତୁ 1;
    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_channel_layout_ambisonic_order(ଅଚଳ AVChannelLayout *channel_layout)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, highest_ambi, order;

    ଯଦି (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    highest_ambi = -1;
    ଯଦି (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    ଅନ୍ୟଥା {
        ଅଚଳ AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        ପାଇଁ (i = 0; i < channel_layout->nb_channels; i++) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            ଯଦି (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                ଫେରନ୍ତୁ AVERROR(EINVAL);

            /* non-default ordering */
            ଯଦି (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                ଫେରନ୍ତୁ AVERROR(EINVAL);

            ଯଦି (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    ଯଦି (highest_ambi < 0)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    order = floor(sqrt(highest_ambi));
    /* incomplete order - some harmonics are missing */
    ଯଦି ((order + 1) * (order + 1) != highest_ambi + 1)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଫେରନ୍ତୁ order;
}

ସ୍ଥିର ଗଣନା AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା has_known_channel = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା order;

    ଯଦି (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        ଫେରନ୍ତୁ channel_layout->order;

    ଯଦି (has_channel_names(channel_layout))
        ଫେରନ୍ତୁ AV_CHANNEL_ORDER_CUSTOM;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        ଯଦି (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    ଯଦି (!has_known_channel)
        ଫେରନ୍ତୁ AV_CHANNEL_ORDER_UNSPEC;

    ଯଦି (masked_description(channel_layout, 0) > 0)
        ଫେରନ୍ତୁ AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    ଯଦି (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
        ଫେରନ୍ତୁ AV_CHANNEL_ORDER_AMBISONIC;

    ଫେରନ୍ତୁ AV_CHANNEL_ORDER_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା try_describe_ambisonic(AVBPrint *bp, ଅଚଳ AVChannelLayout *channel_layout)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_ambi_channels;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା order = av_channel_layout_ambisonic_order(channel_layout);
    ଯଦି (order < 0)
        ଫେରନ୍ତୁ order;

    av_bprintf(bp, "ambisonic %d", order);

    /* extra channels present */
    nb_ambi_channels = (order + 1) * (order + 1);
    ଯଦି (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        ଯଦି (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC) {
            extra.order       = AV_CHANNEL_ORDER_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.mask);
            extra.u.mask      = channel_layout->u.mask;
        } ଅନ୍ୟଥା {
            int64_t mask;
            ଯଦି (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.order       = AV_CHANNEL_ORDER_NATIVE;
                extra.nb_channels = av_popcount64(mask);
                extra.u.mask      = mask;
            } ଅନ୍ୟଥା {
                extra.order       = AV_CHANNEL_ORDER_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_channel_layout_describe_bprint(ଅଚଳ AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ବାଛ (channel_layout->order) {
    ସ୍ଥିତି AV_CHANNEL_ORDER_NATIVE:
        ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            ଯଦି (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                ଫେରନ୍ତୁ 0;
            }
        av_fallthrough;
    ସ୍ଥିତି AV_CHANNEL_ORDER_CUSTOM:
        ଯଦି (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା res = try_describe_ambisonic(bp, channel_layout);
            ଯଦି (res >= 0)
                ଫେରନ୍ତୁ 0;
            ଯଦି (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                ଫେରନ୍ତୁ av_channel_layout_describe_bprint(&native, bp);
            }
        }
        ଯଦି (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        ପାଇଁ (i = 0; i < channel_layout->nb_channels; i++) {
            ଗଣନା AVChannel ch = av_channel_layout_channel_from_index(channel_layout, i);

            ଯଦି (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            ଯଦି (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        ଯଦି (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            ଫେରନ୍ତୁ 0;
        }
        av_fallthrough;
    ସ୍ଥିତି AV_CHANNEL_ORDER_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        ଫେରନ୍ତୁ 0;
    ସ୍ଥିତି AV_CHANNEL_ORDER_AMBISONIC:
        ଫେରନ୍ତୁ try_describe_ambisonic(bp, channel_layout);
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_channel_layout_describe(ଅଚଳ AVChannelLayout *channel_layout,
                               ଅକ୍ଷର *buf, size_t buf_size)
{
    AVBPrint bp;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (!buf && buf_size)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    ଯଦି (bp.len >= INT_MAX)
        ଫେରନ୍ତୁ AVERROR(ERANGE);
    ଫେରନ୍ତୁ bp.len + 1;
}

ଗଣନା AVChannel
av_channel_layout_channel_from_index(ଅଚଳ AVChannelLayout *channel_layout,
                                     unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା idx)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ଯଦି (idx >= channel_layout->nb_channels)
        ଫେରନ୍ତୁ AV_CHAN_NONE;

    ବାଛ (channel_layout->order) {
    ସ୍ଥିତି AV_CHANNEL_ORDER_CUSTOM:
        ଫେରନ୍ତୁ channel_layout->u.map[idx].id;
    ସ୍ଥିତି AV_CHANNEL_ORDER_AMBISONIC: {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        ଯଦି (idx < ambi_channels)
            ଫେରନ୍ତୁ AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    ସ୍ଥିତି AV_CHANNEL_ORDER_NATIVE:
        ପାଇଁ (i = 0; i < 64; i++) {
            ଯଦି ((1ULL << i) & channel_layout->u.mask && !idx--)
                ଫେରନ୍ତୁ i;
        }
        av_fallthrough;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ AV_CHAN_NONE;
    }
}

ଗଣନା AVChannel
av_channel_layout_channel_from_string(ଅଚଳ AVChannelLayout *channel_layout,
                                      ଅଚଳ ଅକ୍ଷର *str)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା index = av_channel_layout_index_from_string(channel_layout, str);

    ଯଦି (index < 0)
        ଫେରନ୍ତୁ AV_CHAN_NONE;

    ଫେରନ୍ତୁ av_channel_layout_channel_from_index(channel_layout, index);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_channel_layout_index_from_channel(ଅଚଳ AVChannelLayout *channel_layout,
                                         ଗଣନା AVChannel channel)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ଯଦି (channel == AV_CHAN_NONE)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ବାଛ (channel_layout->order) {
    ସ୍ଥିତି AV_CHANNEL_ORDER_CUSTOM:
        ପାଇଁ (i = 0; i < channel_layout->nb_channels; i++)
            ଯଦି (channel_layout->u.map[i].id == channel)
                ଫେରନ୍ତୁ i;
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    ସ୍ଥିତି AV_CHANNEL_ORDER_AMBISONIC:
    ସ୍ଥିତି AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        ଯଦି (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            ଯଦି (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                ଫେରନ୍ତୁ AVERROR(EINVAL);
            ଫେରନ୍ତୁ channel - AV_CHAN_AMBISONIC_BASE;
        }
        ଯଦି ((unsigned)channel > 63 || !(mask & (1ULL << channel)))
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        mask &= (1ULL << channel) - 1;
        ଫେରନ୍ତୁ av_popcount64(mask) + ambi_channels;
        }
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_channel_layout_index_from_string(ଅଚଳ AVChannelLayout *channel_layout,
                                        ଅଚଳ ଅକ୍ଷର *str)
{
    ଅଚଳ ଅକ୍ଷର *chname;
    ଗଣନା AVChannel ch = AV_CHAN_NONE;

    ବାଛ (channel_layout->order) {
    ସ୍ଥିତି AV_CHANNEL_ORDER_CUSTOM:
        chname = strstr(str, "@");
        ଯଦି (chname) {
            ଅକ୍ଷର buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(ଆକାର(buf), chname - str));
            ଯଦି (!*chname)
                chname = ଖାଲି;
            ch = av_channel_from_string(buf);
            ଯଦି (ch == AV_CHAN_NONE && *buf)
                ଫେରନ୍ତୁ AVERROR(EINVAL);
        }
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; chname && i < channel_layout->nb_channels; i++) {
            ଯଦି (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                ଫେରନ୍ତୁ i;
        }
        av_fallthrough;
    ସ୍ଥିତି AV_CHANNEL_ORDER_AMBISONIC:
    ସ୍ଥିତି AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        ଯଦି (ch == AV_CHAN_NONE)
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        ଫେରନ୍ତୁ av_channel_layout_index_from_channel(channel_layout, ch);
    }

    ଫେରନ୍ତୁ AVERROR(EINVAL);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_channel_layout_check(ଅଚଳ AVChannelLayout *channel_layout)
{
    ଯଦି (channel_layout->nb_channels <= 0)
        ଫେରନ୍ତୁ 0;

    ବାଛ (channel_layout->order) {
    ସ୍ଥିତି AV_CHANNEL_ORDER_NATIVE:
        ଫେରନ୍ତୁ av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    ସ୍ଥିତି AV_CHANNEL_ORDER_CUSTOM:
        ଯଦି (!channel_layout->u.map)
            ଫେରନ୍ତୁ 0;
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < channel_layout->nb_channels; i++) {
            ଯଦି (channel_layout->u.map[i].id == AV_CHAN_NONE)
                ଫେରନ୍ତୁ 0;
        }
        ଫେରନ୍ତୁ 1;
    ସ୍ଥିତି AV_CHANNEL_ORDER_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        ଫେରନ୍ତୁ av_popcount64(channel_layout->u.mask) < channel_layout->nb_channels;
    ସ୍ଥିତି AV_CHANNEL_ORDER_UNSPEC:
        ଫେରନ୍ତୁ 1;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ 0;
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_channel_layout_compare(ଅଚଳ AVChannelLayout *chl, ଅଚଳ AVChannelLayout *chl1)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    /* different channel counts -> not equal */
    ଯଦି (chl->nb_channels != chl1->nb_channels)
        ଫେରନ୍ତୁ 1;

    /* if only one is unspecified -> not equal */
    ଯଦି ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        ଫେରନ୍ତୁ 1;
    /* both are unspecified -> equal */
    ଅନ୍ୟଥା ଯଦି (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        ଫେରନ୍ତୁ 0;

    /* can compare masks directly */
    ଯଦି ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        ଫେରନ୍ତୁ chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    ପାଇଁ (i = 0; i < chl->nb_channels; i++)
        ଯଦି (av_channel_layout_channel_from_index(chl,  i) !=
            av_channel_layout_channel_from_index(chl1, i))
            ଫେରନ୍ତୁ 1;
    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ av_channel_layout_default(AVChannelLayout *ch_layout, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_channels)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        ଯଦି (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            ଫେରନ୍ତୁ;
        }

    ch_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

ଅଚଳ AVChannelLayout *av_channel_layout_standard(ଶୂନ୍ୟ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ଅଚଳ AVChannelLayout *ch_layout = ଖାଲି;

    ଯଦି (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (ଶୂନ୍ୟ*)(i + 1);
    }

    ଫେରନ୍ତୁ ch_layout;
}

uint64_t av_channel_layout_subset(ଅଚଳ AVChannelLayout *channel_layout,
                                  uint64_t mask)
{
    uint64_t ret = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ବାଛ (channel_layout->order) {
    ସ୍ଥିତି AV_CHANNEL_ORDER_NATIVE:
    ସ୍ଥିତି AV_CHANNEL_ORDER_AMBISONIC:
        ଫେରନ୍ତୁ channel_layout->u.mask & mask;
    ସ୍ଥିତି AV_CHANNEL_ORDER_CUSTOM:
        ପାଇଁ (i = 0; i < 64; i++)
            ଯଦି (mask & (1ULL << i) && av_channel_layout_index_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        ଭାଙ୍ଗ;
    }

    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_channel_layout_retype(AVChannelLayout *channel_layout, ଗଣନା AVChannelOrder order, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା lossy;

    ଯଦି (!av_channel_layout_check(channel_layout))
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଯଦି (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    ଯଦି (channel_layout->order == order)
        ଫେରନ୍ତୁ 0;

    ବାଛ (order) {
    ସ୍ଥିତି AV_CHANNEL_ORDER_UNSPEC: {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_channels = channel_layout->nb_channels;
        ଯଦି (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_channels; i++) {
                ଯଦି (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    ଭାଙ୍ଗ;
                }
            }
        } ଅନ୍ୟଥା {
            lossy = 1;
        }
        ଯଦି (!lossy || allow_lossy) {
            ଶୂନ୍ୟ *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            ଫେରନ୍ତୁ lossy;
        }
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
        }
    ସ୍ଥିତି AV_CHANNEL_ORDER_NATIVE:
        ଯଦି (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            ଯଦି (mask < 0)
                ଫେରନ୍ତୁ AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            ଯଦି (!lossy || allow_lossy) {
                ଶୂନ୍ୟ *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_mask(channel_layout, mask);
                channel_layout->opaque = opaque;
                ଫେରନ୍ତୁ lossy;
            }
        }
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    ସ୍ଥିତି AV_CHANNEL_ORDER_CUSTOM: {
        AVChannelLayout custom = { 0 };
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        ଶୂନ୍ୟ *opaque = channel_layout->opaque;
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;
        ଯଦି (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_index(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        ଫେରନ୍ତୁ 0;
        }
    ସ୍ଥିତି AV_CHANNEL_ORDER_AMBISONIC:
        ଯଦି (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_channels = channel_layout->nb_channels;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା amb_order = av_channel_layout_ambisonic_order(channel_layout);
            ଯଦି (amb_order < 0)
                ଫେରନ୍ତୁ AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            ଯଦି (mask < 0)
                ଫେରନ୍ତୁ AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            ଯଦି (!lossy || allow_lossy) {
                ଶୂନ୍ୟ *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.mask      = mask;
                channel_layout->opaque      = opaque;
                ଫେରନ୍ତୁ lossy;
            }
        }
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }
}
