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

#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ "channel_layout.h"
#അന്തര്ഭാവ "bprint.h"
#അന്തര്ഭാവ "common.h"
#അന്തര്ഭാവ "error.h"
#അന്തര്ഭാവ "attributes.h"
#അന്തര്ഭാവ "macros.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "opt.h"

#define CHAN_IS_AMBI(x) ((x) >= AV_CHAN_AMBISONIC_BASE &&\
                         (x) <= AV_CHAN_AMBISONIC_END)

ഘടന channel_name {
    സ്ഥിരം അക്ഷരം *name;
    സ്ഥിരം അക്ഷരം *description;
};

സ്ഥിതം സ്ഥിരം ഘടന channel_name channel_names[] = {
    [AV_CHAN_FRONT_ഇടത്           ] = { "FL",        "front left"            },
    [AV_CHAN_FRONT_വലത്          ] = { "FR",        "front right"           },
    [AV_CHAN_FRONT_CENTER         ] = { "FC",        "front center"          },
    [AV_CHAN_താഴെയുള്ള_FREQUENCY        ] = { "LFE",       "low frequency"         },
    [AV_CHAN_BACK_ഇടത്            ] = { "BL",        "back left"             },
    [AV_CHAN_BACK_വലത്           ] = { "BR",        "back right"            },
    [AV_CHAN_FRONT_ഇടത്_OF_CENTER ] = { "FLC",       "front left-of-center"  },
    [AV_CHAN_FRONT_വലത്_OF_CENTER] = { "FRC",       "front right-of-center" },
    [AV_CHAN_BACK_CENTER          ] = { "BC",        "back center"           },
    [AV_CHAN_SIDE_ഇടത്            ] = { "SL",        "side left"             },
    [AV_CHAN_SIDE_വലത്           ] = { "SR",        "side right"            },
    [AV_CHAN_മുകൾ_CENTER           ] = { "TC",        "top center"            },
    [AV_CHAN_മുകൾ_FRONT_ഇടത്       ] = { "TFL",       "top front left"        },
    [AV_CHAN_മുകൾ_FRONT_CENTER     ] = { "TFC",       "top front center"      },
    [AV_CHAN_മുകൾ_FRONT_വലത്      ] = { "TFR",       "top front right"       },
    [AV_CHAN_മുകൾ_BACK_ഇടത്        ] = { "TBL",       "top back left"         },
    [AV_CHAN_മുകൾ_BACK_CENTER      ] = { "TBC",       "top back center"       },
    [AV_CHAN_മുകൾ_BACK_വലത്       ] = { "TBR",       "top back right"        },
    [AV_CHAN_STEREO_ഇടത്          ] = { "DL",        "downmix left"          },
    [AV_CHAN_STEREO_വലത്         ] = { "DR",        "downmix right"         },
    [AV_CHAN_WIDE_ഇടത്            ] = { "WL",        "wide left"             },
    [AV_CHAN_WIDE_വലത്           ] = { "WR",        "wide right"            },
    [AV_CHAN_SURROUND_DIRECT_ഇടത് ] = { "SDL",       "surround direct left"  },
    [AV_CHAN_SURROUND_DIRECT_വലത്] = { "SDR",       "surround direct right" },
    [AV_CHAN_താഴെയുള്ള_FREQUENCY_2      ] = { "LFE2",      "low frequency 2"       },
    [AV_CHAN_മുകൾ_SIDE_ഇടത്        ] = { "TSL",       "top side left"         },
    [AV_CHAN_മുകൾ_SIDE_വലത്       ] = { "TSR",       "top side right"        },
    [AV_CHAN_BOTTOM_FRONT_CENTER  ] = { "BFC",       "bottom front center"   },
    [AV_CHAN_BOTTOM_FRONT_ഇടത്    ] = { "BFL",       "bottom front left"     },
    [AV_CHAN_BOTTOM_FRONT_വലത്   ] = { "BFR",       "bottom front right"    },
    [AV_CHAN_SIDE_SURROUND_ഇടത്   ] = { "SSL",       "side surround left"    },
    [AV_CHAN_SIDE_SURROUND_വലത്  ] = { "SSR",       "side surround right"   },
    [AV_CHAN_മുകൾ_SURROUND_ഇടത്    ] = { "TTL",       "top surround left"     },
    [AV_CHAN_മുകൾ_SURROUND_വലത്   ] = { "TTR",       "top surround right"    },
    [AV_CHAN_BINAURAL_ഇടത്        ] = { "BIL",       "binaural left"         },
    [AV_CHAN_BINAURAL_വലത്       ] = { "BIR",       "binaural right"        },
};

ശൂന്യം av_channel_name_bprint(AVBPrint *bp, എണ്ണൽ AVChannel channel_id)
{
    എങ്കിൽ (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_BASE);
    അല്ലെങ്കിൽ എങ്കിൽ ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].name)
        av_bprintf(bp, "%s", channel_names[channel_id].name);
    അല്ലെങ്കിൽ എങ്കിൽ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    അല്ലെങ്കിൽ എങ്കിൽ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    അല്ലെങ്കിൽ എങ്കിൽ (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "UNSD");
    അല്ലെങ്കിൽ
        av_bprintf(bp, "USR%d", channel_id);
}

പൂർണ്ണസംഖ്യ av_channel_name(അക്ഷരം *buf, size_t buf_size, എണ്ണൽ AVChannel channel_id)
{
    AVBPrint bp;

    എങ്കിൽ (!buf && buf_size)
        തിരികെ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_name_bprint(&bp, channel_id);

    എങ്കിൽ (bp.len >= INT_MAX)
        തിരികെ AVERROR(ERANGE);
    തിരികെ bp.len + 1;
}

ശൂന്യം av_channel_description_bprint(AVBPrint *bp, എണ്ണൽ AVChannel channel_id)
{
    എങ്കിൽ (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_BASE);
    അല്ലെങ്കിൽ എങ്കിൽ ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].description)
        av_bprintf(bp, "%s", channel_names[channel_id].description);
    അല്ലെങ്കിൽ എങ്കിൽ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    അല്ലെങ്കിൽ എങ്കിൽ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    അല്ലെങ്കിൽ എങ്കിൽ (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "unused");
    അല്ലെങ്കിൽ
        av_bprintf(bp, "user %d", channel_id);
}

പൂർണ്ണസംഖ്യ av_channel_description(അക്ഷരം *buf, size_t buf_size, എണ്ണൽ AVChannel channel_id)
{
    AVBPrint bp;

    എങ്കിൽ (!buf && buf_size)
        തിരികെ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_description_bprint(&bp, channel_id);

    എങ്കിൽ (bp.len >= INT_MAX)
        തിരികെ AVERROR(ERANGE);
    തിരികെ bp.len + 1;
}

എണ്ണൽ AVChannel av_channel_from_string(സ്ഥിരം അക്ഷരം *str)
{
    പൂർണ്ണസംഖ്യ i;
    അക്ഷരം *endptr = (അക്ഷരം *)str;
    എണ്ണൽ AVChannel id = AV_CHAN_NONE;

    എങ്കിൽ (!strncmp(str, "AMBI", 4)) {
        i = strtol(str + 4, ശൂന്യ, 0);
        എങ്കിൽ (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            തിരികെ AV_CHAN_NONE;
        തിരികെ AV_CHAN_AMBISONIC_BASE + i;
    }

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        എങ്കിൽ (channel_names[i].name && !strcmp(str, channel_names[i].name))
            തിരികെ i;
    }
    എങ്കിൽ (!strcmp(str, "UNK"))
        തിരികെ AV_CHAN_UNKNOWN;
    എങ്കിൽ (!strcmp(str, "UNSD"))
        തിരികെ AV_CHAN_UNUSED;

    എങ്കിൽ (!strncmp(str, "USR", 3)) {
        സ്ഥിരം അക്ഷരം *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    എങ്കിൽ (id >= 0 && !*endptr)
        തിരികെ id;

    തിരികെ AV_CHAN_NONE;
}

ഘടന channel_layout_name {
    സ്ഥിരം അക്ഷരം *name;
    AVChannelLayout layout;
};

സ്ഥിതം സ്ഥിരം ഘടന channel_layout_name channel_layout_map[] = {
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

പൂർണ്ണസംഖ്യ av_channel_layout_custom_init(AVChannelLayout *channel_layout, പൂർണ്ണസംഖ്യ nb_channels)
{
    AVChannelCustom *map;

    എങ്കിൽ (nb_channels <= 0)
        തിരികെ AVERROR(EINVAL);

    map = av_calloc(nb_channels, വലുപ്പം(*channel_layout->u.map));
    എങ്കിൽ (!map)
        തിരികെ AVERROR(ENOMEM);
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->order       = AV_CHANNEL_ORDER_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_channel_layout_from_mask(AVChannelLayout *channel_layout,
                                uint64_t mask)
{
    എങ്കിൽ (!mask)
        തിരികെ AVERROR(EINVAL);

    channel_layout->order       = AV_CHANNEL_ORDER_NATIVE;
    channel_layout->nb_channels = av_popcount64(mask);
    channel_layout->u.mask      = mask;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ parse_channel_list(AVChannelLayout *ch_layout, സ്ഥിരം അക്ഷരം *str)
{
    പൂർണ്ണസംഖ്യ ret;
    പൂർണ്ണസംഖ്യ nb_channels = 0;
    AVChannelCustom *map = ശൂന്യ;
    AVChannelCustom custom = {0};

    ആകുമ്പോൾ (*str) {
        അക്ഷരം *channel, *chname;
        ret = av_opt_get_താക്കോൽ_മൂല്യം(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_താക്കോൽ, &channel, &chname);
        എങ്കിൽ (ret < 0) {
            av_freep(&map);
            തിരികെ ret;
        }
        എങ്കിൽ (*str)
            str++; // skip separator
        എങ്കിൽ (!channel) {
            channel = chname;
            chname = ശൂന്യ;
        }
        av_strlcpy(custom.name, chname ? chname : "", വലുപ്പം(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        എങ്കിൽ (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            തിരികെ AVERROR(EINVAL);
        }

        av_dynarray2_add((ശൂന്യം **)&map, &nb_channels, വലുപ്പം(custom), (ശൂന്യം *)&custom);
        എങ്കിൽ (!map)
            തിരികെ AVERROR(ENOMEM);
    }

    എങ്കിൽ (!nb_channels)
        തിരികെ AVERROR(EINVAL);

    ch_layout->order = AV_CHANNEL_ORDER_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  സ്ഥിരം അക്ഷരം *str)
{
    പൂർണ്ണസംഖ്യ i, matches, ret;
    പൂർണ്ണസംഖ്യ channels = 0, nb_channels = 0;
    അക്ഷരം *chlist, *end;
    uint64_t mask = 0;

    /* channel layout names */
    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        എങ്കിൽ (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            തിരികെ 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, വലുപ്പം(*channel_layout));

    /* ambisonic */
    എങ്കിൽ (!strncmp(str, "ambisonic ", 10)) {
        സ്ഥിരം അക്ഷരം *p = str + 10;
        അക്ഷരം *endptr;
        AVChannelLayout extra = {0};
        പൂർണ്ണസംഖ്യ order;

        order = strtol(p, &endptr, 0);
        എങ്കിൽ (order < 0 || order + 1  > INT_MAX / (order + 1) ||
            (*endptr && *endptr != '+'))
            തിരികെ AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        എങ്കിൽ (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            എങ്കിൽ (ret < 0)
                തിരികെ ret;
            എങ്കിൽ (extra.nb_channels >= INT_MAX - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                തിരികെ AVERROR(EINVAL);
            }

            എങ്കിൽ (extra.order == AV_CHANNEL_ORDER_NATIVE) {
                channel_layout->u.mask = extra.u.mask;
            } അല്ലെങ്കിൽ {
                channel_layout->order = AV_CHANNEL_ORDER_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              വലുപ്പം(*channel_layout->u.map));
                എങ്കിൽ (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    തിരികെ AVERROR(ENOMEM);
                }

                വേണ്ടി (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                വേണ്ടി (i = 0; i < extra.nb_channels; i++) {
                    എണ്ണൽ AVChannel ch = av_channel_layout_channel_from_index(&extra, i);
                    എങ്കിൽ (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        തിരികെ AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    എങ്കിൽ (extra.order == AV_CHANNEL_ORDER_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   വലുപ്പം(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        തിരികെ 0;
    }

    chlist = av_strdup(str);
    എങ്കിൽ (!chlist)
        തിരികെ AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    എങ്കിൽ (ret < 0 && ret != AVERROR(EINVAL))
        തിരികെ ret;

    എങ്കിൽ (ret >= 0) {
        സ്ഥിരം അക്ഷരം *end_par = strchr(str, ')');
        എങ്കിൽ (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            തിരികെ AVERROR(EINVAL);
        }
        തിരികെ 0;
    }

    errno = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    എങ്കിൽ (!errno && !*end && !strchr(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        തിരികെ 0;
    }

    errno = 0;
    channels = strtol(str, &end, 10);

    /* number of channels */
    എങ്കിൽ (!errno && !strcmp(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        എങ്കിൽ (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            തിരികെ 0;
    }

    /* number of unordered channels */
    എങ്കിൽ (!errno && (!strcmp(end, "C") || !strcmp(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        തിരികെ 0;
    }

    തിരികെ AVERROR(EINVAL);
}

ശൂന്യം av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    എങ്കിൽ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, വലുപ്പം(*channel_layout));
}

പൂർണ്ണസംഖ്യ av_channel_layout_copy(AVChannelLayout *dst, സ്ഥിരം AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    എങ്കിൽ (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, വലുപ്പം(*dst->u.map));
        എങ്കിൽ (!dst->u.map)
            തിരികെ AVERROR(ENOMEM);
        memcpy(dst->u.map, src->u.map, src->nb_channels * വലുപ്പം(*src->u.map));
    }
    തിരികെ 0;
}

സ്ഥിതം int64_t masked_description(സ്ഥിരം AVChannelLayout *channel_layout, പൂർണ്ണസംഖ്യ start_channel)
{
    uint64_t mask = 0;
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = start_channel; i < channel_layout->nb_channels; i++) {
        എണ്ണൽ AVChannel ch = channel_layout->u.map[i].id;
        എങ്കിൽ (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        അല്ലെങ്കിൽ
            തിരികെ AVERROR(EINVAL);
    }
    തിരികെ mask;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ has_channel_names(സ്ഥിരം AVChannelLayout *channel_layout)
{
    എങ്കിൽ (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        തിരികെ 0;
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < channel_layout->nb_channels; i++)
        എങ്കിൽ (channel_layout->u.map[i].name[0])
            തിരികെ 1;
    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_channel_layout_ambisonic_order(സ്ഥിരം AVChannelLayout *channel_layout)
{
    പൂർണ്ണസംഖ്യ i, highest_ambi, order;

    എങ്കിൽ (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        തിരികെ AVERROR(EINVAL);

    highest_ambi = -1;
    എങ്കിൽ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    അല്ലെങ്കിൽ {
        സ്ഥിരം AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        വേണ്ടി (i = 0; i < channel_layout->nb_channels; i++) {
            പൂർണ്ണസംഖ്യ is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            എങ്കിൽ (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                തിരികെ AVERROR(EINVAL);

            /* non-default ordering */
            എങ്കിൽ (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                തിരികെ AVERROR(EINVAL);

            എങ്കിൽ (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    എങ്കിൽ (highest_ambi < 0)
        തിരികെ AVERROR(EINVAL);

    order = floor(sqrt(highest_ambi));
    /* incomplete order - some harmonics are missing */
    എങ്കിൽ ((order + 1) * (order + 1) != highest_ambi + 1)
        തിരികെ AVERROR(EINVAL);

    തിരികെ order;
}

സ്ഥിതം എണ്ണൽ AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    പൂർണ്ണസംഖ്യ has_known_channel = 0;
    പൂർണ്ണസംഖ്യ order;

    എങ്കിൽ (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        തിരികെ channel_layout->order;

    എങ്കിൽ (has_channel_names(channel_layout))
        തിരികെ AV_CHANNEL_ORDER_CUSTOM;

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        എങ്കിൽ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    എങ്കിൽ (!has_known_channel)
        തിരികെ AV_CHANNEL_ORDER_UNSPEC;

    എങ്കിൽ (masked_description(channel_layout, 0) > 0)
        തിരികെ AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    എങ്കിൽ (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
        തിരികെ AV_CHANNEL_ORDER_AMBISONIC;

    തിരികെ AV_CHANNEL_ORDER_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
സ്ഥിതം പൂർണ്ണസംഖ്യ try_describe_ambisonic(AVBPrint *bp, സ്ഥിരം AVChannelLayout *channel_layout)
{
    പൂർണ്ണസംഖ്യ nb_ambi_channels;
    പൂർണ്ണസംഖ്യ order = av_channel_layout_ambisonic_order(channel_layout);
    എങ്കിൽ (order < 0)
        തിരികെ order;

    av_bprintf(bp, "ambisonic %d", order);

    /* extra channels present */
    nb_ambi_channels = (order + 1) * (order + 1);
    എങ്കിൽ (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        എങ്കിൽ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC) {
            extra.order       = AV_CHANNEL_ORDER_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.mask);
            extra.u.mask      = channel_layout->u.mask;
        } അല്ലെങ്കിൽ {
            int64_t mask;
            എങ്കിൽ (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.order       = AV_CHANNEL_ORDER_NATIVE;
                extra.nb_channels = av_popcount64(mask);
                extra.u.mask      = mask;
            } അല്ലെങ്കിൽ {
                extra.order       = AV_CHANNEL_ORDER_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_channel_layout_describe_bprint(സ്ഥിരം AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    പൂർണ്ണസംഖ്യ i;

    തിരഞ്ഞെടുപ്പ് (channel_layout->order) {
    അവസ്ഥ AV_CHANNEL_ORDER_NATIVE:
        വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            എങ്കിൽ (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                തിരികെ 0;
            }
        av_fallthrough;
    അവസ്ഥ AV_CHANNEL_ORDER_CUSTOM:
        എങ്കിൽ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            പൂർണ്ണസംഖ്യ res = try_describe_ambisonic(bp, channel_layout);
            എങ്കിൽ (res >= 0)
                തിരികെ 0;
            എങ്കിൽ (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                തിരികെ av_channel_layout_describe_bprint(&native, bp);
            }
        }
        എങ്കിൽ (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        വേണ്ടി (i = 0; i < channel_layout->nb_channels; i++) {
            എണ്ണൽ AVChannel ch = av_channel_layout_channel_from_index(channel_layout, i);

            എങ്കിൽ (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            എങ്കിൽ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        എങ്കിൽ (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            തിരികെ 0;
        }
        av_fallthrough;
    അവസ്ഥ AV_CHANNEL_ORDER_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        തിരികെ 0;
    അവസ്ഥ AV_CHANNEL_ORDER_AMBISONIC:
        തിരികെ try_describe_ambisonic(bp, channel_layout);
    സ്ഥിരസ്ഥിതി:
        തിരികെ AVERROR(EINVAL);
    }
}

പൂർണ്ണസംഖ്യ av_channel_layout_describe(സ്ഥിരം AVChannelLayout *channel_layout,
                               അക്ഷരം *buf, size_t buf_size)
{
    AVBPrint bp;
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (!buf && buf_size)
        തിരികെ AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    എങ്കിൽ (bp.len >= INT_MAX)
        തിരികെ AVERROR(ERANGE);
    തിരികെ bp.len + 1;
}

എണ്ണൽ AVChannel
av_channel_layout_channel_from_index(സ്ഥിരം AVChannelLayout *channel_layout,
                                     unsigned പൂർണ്ണസംഖ്യ idx)
{
    പൂർണ്ണസംഖ്യ i;

    എങ്കിൽ (idx >= channel_layout->nb_channels)
        തിരികെ AV_CHAN_NONE;

    തിരഞ്ഞെടുപ്പ് (channel_layout->order) {
    അവസ്ഥ AV_CHANNEL_ORDER_CUSTOM:
        തിരികെ channel_layout->u.map[idx].id;
    അവസ്ഥ AV_CHANNEL_ORDER_AMBISONIC: {
        പൂർണ്ണസംഖ്യ ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        എങ്കിൽ (idx < ambi_channels)
            തിരികെ AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    അവസ്ഥ AV_CHANNEL_ORDER_NATIVE:
        വേണ്ടി (i = 0; i < 64; i++) {
            എങ്കിൽ ((1ULL << i) & channel_layout->u.mask && !idx--)
                തിരികെ i;
        }
        av_fallthrough;
    സ്ഥിരസ്ഥിതി:
        തിരികെ AV_CHAN_NONE;
    }
}

എണ്ണൽ AVChannel
av_channel_layout_channel_from_string(സ്ഥിരം AVChannelLayout *channel_layout,
                                      സ്ഥിരം അക്ഷരം *str)
{
    പൂർണ്ണസംഖ്യ index = av_channel_layout_index_from_string(channel_layout, str);

    എങ്കിൽ (index < 0)
        തിരികെ AV_CHAN_NONE;

    തിരികെ av_channel_layout_channel_from_index(channel_layout, index);
}

പൂർണ്ണസംഖ്യ av_channel_layout_index_from_channel(സ്ഥിരം AVChannelLayout *channel_layout,
                                         എണ്ണൽ AVChannel channel)
{
    പൂർണ്ണസംഖ്യ i;

    എങ്കിൽ (channel == AV_CHAN_NONE)
        തിരികെ AVERROR(EINVAL);

    തിരഞ്ഞെടുപ്പ് (channel_layout->order) {
    അവസ്ഥ AV_CHANNEL_ORDER_CUSTOM:
        വേണ്ടി (i = 0; i < channel_layout->nb_channels; i++)
            എങ്കിൽ (channel_layout->u.map[i].id == channel)
                തിരികെ i;
        തിരികെ AVERROR(EINVAL);
    അവസ്ഥ AV_CHANNEL_ORDER_AMBISONIC:
    അവസ്ഥ AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        പൂർണ്ണസംഖ്യ ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        എങ്കിൽ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            എങ്കിൽ (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                തിരികെ AVERROR(EINVAL);
            തിരികെ channel - AV_CHAN_AMBISONIC_BASE;
        }
        എങ്കിൽ ((unsigned)channel > 63 || !(mask & (1ULL << channel)))
            തിരികെ AVERROR(EINVAL);
        mask &= (1ULL << channel) - 1;
        തിരികെ av_popcount64(mask) + ambi_channels;
        }
    സ്ഥിരസ്ഥിതി:
        തിരികെ AVERROR(EINVAL);
    }
}

പൂർണ്ണസംഖ്യ av_channel_layout_index_from_string(സ്ഥിരം AVChannelLayout *channel_layout,
                                        സ്ഥിരം അക്ഷരം *str)
{
    സ്ഥിരം അക്ഷരം *chname;
    എണ്ണൽ AVChannel ch = AV_CHAN_NONE;

    തിരഞ്ഞെടുപ്പ് (channel_layout->order) {
    അവസ്ഥ AV_CHANNEL_ORDER_CUSTOM:
        chname = strstr(str, "@");
        എങ്കിൽ (chname) {
            അക്ഷരം buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(വലുപ്പം(buf), chname - str));
            എങ്കിൽ (!*chname)
                chname = ശൂന്യ;
            ch = av_channel_from_string(buf);
            എങ്കിൽ (ch == AV_CHAN_NONE && *buf)
                തിരികെ AVERROR(EINVAL);
        }
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; chname && i < channel_layout->nb_channels; i++) {
            എങ്കിൽ (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                തിരികെ i;
        }
        av_fallthrough;
    അവസ്ഥ AV_CHANNEL_ORDER_AMBISONIC:
    അവസ്ഥ AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        എങ്കിൽ (ch == AV_CHAN_NONE)
            തിരികെ AVERROR(EINVAL);
        തിരികെ av_channel_layout_index_from_channel(channel_layout, ch);
    }

    തിരികെ AVERROR(EINVAL);
}

പൂർണ്ണസംഖ്യ av_channel_layout_check(സ്ഥിരം AVChannelLayout *channel_layout)
{
    എങ്കിൽ (channel_layout->nb_channels <= 0)
        തിരികെ 0;

    തിരഞ്ഞെടുപ്പ് (channel_layout->order) {
    അവസ്ഥ AV_CHANNEL_ORDER_NATIVE:
        തിരികെ av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    അവസ്ഥ AV_CHANNEL_ORDER_CUSTOM:
        എങ്കിൽ (!channel_layout->u.map)
            തിരികെ 0;
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < channel_layout->nb_channels; i++) {
            എങ്കിൽ (channel_layout->u.map[i].id == AV_CHAN_NONE)
                തിരികെ 0;
        }
        തിരികെ 1;
    അവസ്ഥ AV_CHANNEL_ORDER_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        തിരികെ av_popcount64(channel_layout->u.mask) < channel_layout->nb_channels;
    അവസ്ഥ AV_CHANNEL_ORDER_UNSPEC:
        തിരികെ 1;
    സ്ഥിരസ്ഥിതി:
        തിരികെ 0;
    }
}

പൂർണ്ണസംഖ്യ av_channel_layout_compare(സ്ഥിരം AVChannelLayout *chl, സ്ഥിരം AVChannelLayout *chl1)
{
    പൂർണ്ണസംഖ്യ i;

    /* different channel counts -> not equal */
    എങ്കിൽ (chl->nb_channels != chl1->nb_channels)
        തിരികെ 1;

    /* if only one is unspecified -> not equal */
    എങ്കിൽ ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        തിരികെ 1;
    /* both are unspecified -> equal */
    അല്ലെങ്കിൽ എങ്കിൽ (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        തിരികെ 0;

    /* can compare masks directly */
    എങ്കിൽ ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        തിരികെ chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    വേണ്ടി (i = 0; i < chl->nb_channels; i++)
        എങ്കിൽ (av_channel_layout_channel_from_index(chl,  i) !=
            av_channel_layout_channel_from_index(chl1, i))
            തിരികെ 1;
    തിരികെ 0;
}

ശൂന്യം av_channel_layout_default(AVChannelLayout *ch_layout, പൂർണ്ണസംഖ്യ nb_channels)
{
    പൂർണ്ണസംഖ്യ i;
    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        എങ്കിൽ (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            തിരികെ;
        }

    ch_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

സ്ഥിരം AVChannelLayout *av_channel_layout_standard(ശൂന്യം **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    സ്ഥിരം AVChannelLayout *ch_layout = ശൂന്യ;

    എങ്കിൽ (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (ശൂന്യം*)(i + 1);
    }

    തിരികെ ch_layout;
}

uint64_t av_channel_layout_subset(സ്ഥിരം AVChannelLayout *channel_layout,
                                  uint64_t mask)
{
    uint64_t ret = 0;
    പൂർണ്ണസംഖ്യ i;

    തിരഞ്ഞെടുപ്പ് (channel_layout->order) {
    അവസ്ഥ AV_CHANNEL_ORDER_NATIVE:
    അവസ്ഥ AV_CHANNEL_ORDER_AMBISONIC:
        തിരികെ channel_layout->u.mask & mask;
    അവസ്ഥ AV_CHANNEL_ORDER_CUSTOM:
        വേണ്ടി (i = 0; i < 64; i++)
            എങ്കിൽ (mask & (1ULL << i) && av_channel_layout_index_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        നിർത്തുക;
    }

    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_channel_layout_retype(AVChannelLayout *channel_layout, എണ്ണൽ AVChannelOrder order, പൂർണ്ണസംഖ്യ flags)
{
    പൂർണ്ണസംഖ്യ allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    പൂർണ്ണസംഖ്യ lossy;

    എങ്കിൽ (!av_channel_layout_check(channel_layout))
        തിരികെ AVERROR(EINVAL);

    എങ്കിൽ (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    എങ്കിൽ (channel_layout->order == order)
        തിരികെ 0;

    തിരഞ്ഞെടുപ്പ് (order) {
    അവസ്ഥ AV_CHANNEL_ORDER_UNSPEC: {
        പൂർണ്ണസംഖ്യ nb_channels = channel_layout->nb_channels;
        എങ്കിൽ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < nb_channels; i++) {
                എങ്കിൽ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    നിർത്തുക;
                }
            }
        } അല്ലെങ്കിൽ {
            lossy = 1;
        }
        എങ്കിൽ (!lossy || allow_lossy) {
            ശൂന്യം *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            തിരികെ lossy;
        }
        തിരികെ AVERROR(ENOSYS);
        }
    അവസ്ഥ AV_CHANNEL_ORDER_NATIVE:
        എങ്കിൽ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            എങ്കിൽ (mask < 0)
                തിരികെ AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            എങ്കിൽ (!lossy || allow_lossy) {
                ശൂന്യം *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_mask(channel_layout, mask);
                channel_layout->opaque = opaque;
                തിരികെ lossy;
            }
        }
        തിരികെ AVERROR(ENOSYS);
    അവസ്ഥ AV_CHANNEL_ORDER_CUSTOM: {
        AVChannelLayout custom = { 0 };
        പൂർണ്ണസംഖ്യ ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        ശൂന്യം *opaque = channel_layout->opaque;
        എങ്കിൽ (ret < 0)
            തിരികെ ret;
        എങ്കിൽ (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_index(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        തിരികെ 0;
        }
    അവസ്ഥ AV_CHANNEL_ORDER_AMBISONIC:
        എങ്കിൽ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            പൂർണ്ണസംഖ്യ nb_channels = channel_layout->nb_channels;
            പൂർണ്ണസംഖ്യ amb_order = av_channel_layout_ambisonic_order(channel_layout);
            എങ്കിൽ (amb_order < 0)
                തിരികെ AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            എങ്കിൽ (mask < 0)
                തിരികെ AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            എങ്കിൽ (!lossy || allow_lossy) {
                ശൂന്യം *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.mask      = mask;
                channel_layout->opaque      = opaque;
                തിരികെ lossy;
            }
        }
        തിരികെ AVERROR(ENOSYS);
    സ്ഥിരസ്ഥിതി:
        തിരികെ AVERROR(EINVAL);
    }
}
