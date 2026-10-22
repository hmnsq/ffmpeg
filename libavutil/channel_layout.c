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

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "channel_layout.h"
#अन्तर्भाव "bprint.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "attributes.h"
#अन्तर्भाव "macros.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "opt.h"

#define CHAN_IS_AMBI(x) ((x) >= AV_CHAN_AMBISONIC_BASE &&\
                         (x) <= AV_CHAN_AMBISONIC_END)

संरचना channel_name {
    ध्रुव वर्ण *name;
    ध्रुव वर्ण *description;
};

स्थिर ध्रुव संरचना channel_name channel_names[] = {
    [AV_CHAN_FRONT_वामः           ] = { "FL",        "front left"            },
    [AV_CHAN_FRONT_दक्षिणः          ] = { "FR",        "front right"           },
    [AV_CHAN_FRONT_CENTER         ] = { "FC",        "front center"          },
    [AV_CHAN_नीचः_FREQUENCY        ] = { "LFE",       "low frequency"         },
    [AV_CHAN_BACK_वामः            ] = { "BL",        "back left"             },
    [AV_CHAN_BACK_दक्षिणः           ] = { "BR",        "back right"            },
    [AV_CHAN_FRONT_वामः_OF_CENTER ] = { "FLC",       "front left-of-center"  },
    [AV_CHAN_FRONT_दक्षिणः_OF_CENTER] = { "FRC",       "front right-of-center" },
    [AV_CHAN_BACK_CENTER          ] = { "BC",        "back center"           },
    [AV_CHAN_SIDE_वामः            ] = { "SL",        "side left"             },
    [AV_CHAN_SIDE_दक्षिणः           ] = { "SR",        "side right"            },
    [AV_CHAN_शिखरम्_CENTER           ] = { "TC",        "top center"            },
    [AV_CHAN_शिखरम्_FRONT_वामः       ] = { "TFL",       "top front left"        },
    [AV_CHAN_शिखरम्_FRONT_CENTER     ] = { "TFC",       "top front center"      },
    [AV_CHAN_शिखरम्_FRONT_दक्षिणः      ] = { "TFR",       "top front right"       },
    [AV_CHAN_शिखरम्_BACK_वामः        ] = { "TBL",       "top back left"         },
    [AV_CHAN_शिखरम्_BACK_CENTER      ] = { "TBC",       "top back center"       },
    [AV_CHAN_शिखरम्_BACK_दक्षिणः       ] = { "TBR",       "top back right"        },
    [AV_CHAN_STEREO_वामः          ] = { "DL",        "downmix left"          },
    [AV_CHAN_STEREO_दक्षिणः         ] = { "DR",        "downmix right"         },
    [AV_CHAN_WIDE_वामः            ] = { "WL",        "wide left"             },
    [AV_CHAN_WIDE_दक्षिणः           ] = { "WR",        "wide right"            },
    [AV_CHAN_SURROUND_DIRECT_वामः ] = { "SDL",       "surround direct left"  },
    [AV_CHAN_SURROUND_DIRECT_दक्षिणः] = { "SDR",       "surround direct right" },
    [AV_CHAN_नीचः_FREQUENCY_2      ] = { "LFE2",      "low frequency 2"       },
    [AV_CHAN_शिखरम्_SIDE_वामः        ] = { "TSL",       "top side left"         },
    [AV_CHAN_शिखरम्_SIDE_दक्षिणः       ] = { "TSR",       "top side right"        },
    [AV_CHAN_BOTTOM_FRONT_CENTER  ] = { "BFC",       "bottom front center"   },
    [AV_CHAN_BOTTOM_FRONT_वामः    ] = { "BFL",       "bottom front left"     },
    [AV_CHAN_BOTTOM_FRONT_दक्षिणः   ] = { "BFR",       "bottom front right"    },
    [AV_CHAN_SIDE_SURROUND_वामः   ] = { "SSL",       "side surround left"    },
    [AV_CHAN_SIDE_SURROUND_दक्षिणः  ] = { "SSR",       "side surround right"   },
    [AV_CHAN_शिखरम्_SURROUND_वामः    ] = { "TTL",       "top surround left"     },
    [AV_CHAN_शिखरम्_SURROUND_दक्षिणः   ] = { "TTR",       "top surround right"    },
    [AV_CHAN_BINAURAL_वामः        ] = { "BIL",       "binaural left"         },
    [AV_CHAN_BINAURAL_दक्षिणः       ] = { "BIR",       "binaural right"        },
};

शून्य av_channel_name_bprint(AVBPrint *bp, गणना AVChannel channel_id)
{
    जइ (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_BASE);
    अण्णहा जइ ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].name)
        av_bprintf(bp, "%s", channel_names[channel_id].name);
    अण्णहा जइ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    अण्णहा जइ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    अण्णहा जइ (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "UNSD");
    अण्णहा
        av_bprintf(bp, "USR%d", channel_id);
}

पूर्णाङ्क av_channel_name(वर्ण *buf, size_t buf_size, गणना AVChannel channel_id)
{
    AVBPrint bp;

    जइ (!buf && buf_size)
        प्रत्यागम AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_name_bprint(&bp, channel_id);

    जइ (bp.len >= INT_MAX)
        प्रत्यागम AVERROR(ERANGE);
    प्रत्यागम bp.len + 1;
}

शून्य av_channel_description_bprint(AVBPrint *bp, गणना AVChannel channel_id)
{
    जइ (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_BASE);
    अण्णहा जइ ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].description)
        av_bprintf(bp, "%s", channel_names[channel_id].description);
    अण्णहा जइ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    अण्णहा जइ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    अण्णहा जइ (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "unused");
    अण्णहा
        av_bprintf(bp, "user %d", channel_id);
}

पूर्णाङ्क av_channel_description(वर्ण *buf, size_t buf_size, गणना AVChannel channel_id)
{
    AVBPrint bp;

    जइ (!buf && buf_size)
        प्रत्यागम AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_description_bprint(&bp, channel_id);

    जइ (bp.len >= INT_MAX)
        प्रत्यागम AVERROR(ERANGE);
    प्रत्यागम bp.len + 1;
}

गणना AVChannel av_channel_from_string(ध्रुव वर्ण *str)
{
    पूर्णाङ्क i;
    वर्ण *endptr = (वर्ण *)str;
    गणना AVChannel id = AV_CHAN_NONE;

    जइ (!strncmp(str, "AMBI", 4)) {
        i = strtol(str + 4, रिक्त, 0);
        जइ (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            प्रत्यागम AV_CHAN_NONE;
        प्रत्यागम AV_CHAN_AMBISONIC_BASE + i;
    }

    प्रति (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        जइ (channel_names[i].name && !strcmp(str, channel_names[i].name))
            प्रत्यागम i;
    }
    जइ (!strcmp(str, "UNK"))
        प्रत्यागम AV_CHAN_UNKNOWN;
    जइ (!strcmp(str, "UNSD"))
        प्रत्यागम AV_CHAN_UNUSED;

    जइ (!strncmp(str, "USR", 3)) {
        ध्रुव वर्ण *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    जइ (id >= 0 && !*endptr)
        प्रत्यागम id;

    प्रत्यागम AV_CHAN_NONE;
}

संरचना channel_layout_name {
    ध्रुव वर्ण *name;
    AVChannelLayout layout;
};

स्थिर ध्रुव संरचना channel_layout_name channel_layout_map[] = {
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

पूर्णाङ्क av_channel_layout_custom_init(AVChannelLayout *channel_layout, पूर्णाङ्क nb_channels)
{
    AVChannelCustom *map;

    जइ (nb_channels <= 0)
        प्रत्यागम AVERROR(EINVAL);

    map = av_calloc(nb_channels, परिमाण(*channel_layout->u.map));
    जइ (!map)
        प्रत्यागम AVERROR(ENOMEM);
    प्रति (पूर्णाङ्क i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->order       = AV_CHANNEL_ORDER_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    प्रत्यागम 0;
}

पूर्णाङ्क av_channel_layout_from_mask(AVChannelLayout *channel_layout,
                                uint64_t mask)
{
    जइ (!mask)
        प्रत्यागम AVERROR(EINVAL);

    channel_layout->order       = AV_CHANNEL_ORDER_NATIVE;
    channel_layout->nb_channels = av_popcount64(mask);
    channel_layout->u.mask      = mask;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क parse_channel_list(AVChannelLayout *ch_layout, ध्रुव वर्ण *str)
{
    पूर्णाङ्क ret;
    पूर्णाङ्क nb_channels = 0;
    AVChannelCustom *map = रिक्त;
    AVChannelCustom custom = {0};

    जाव (*str) {
        वर्ण *channel, *chname;
        ret = av_opt_get_कुञ्चिका_मानम्(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_कुञ्चिका, &channel, &chname);
        जइ (ret < 0) {
            av_freep(&map);
            प्रत्यागम ret;
        }
        जइ (*str)
            str++; // skip separator
        जइ (!channel) {
            channel = chname;
            chname = रिक्त;
        }
        av_strlcpy(custom.name, chname ? chname : "", परिमाण(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        जइ (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            प्रत्यागम AVERROR(EINVAL);
        }

        av_dynarray2_add((शून्य **)&map, &nb_channels, परिमाण(custom), (शून्य *)&custom);
        जइ (!map)
            प्रत्यागम AVERROR(ENOMEM);
    }

    जइ (!nb_channels)
        प्रत्यागम AVERROR(EINVAL);

    ch_layout->order = AV_CHANNEL_ORDER_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    प्रत्यागम 0;
}

पूर्णाङ्क av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  ध्रुव वर्ण *str)
{
    पूर्णाङ्क i, matches, ret;
    पूर्णाङ्क channels = 0, nb_channels = 0;
    वर्ण *chlist, *end;
    uint64_t mask = 0;

    /* channel layout names */
    प्रति (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        जइ (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            प्रत्यागम 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, परिमाण(*channel_layout));

    /* ambisonic */
    जइ (!strncmp(str, "ambisonic ", 10)) {
        ध्रुव वर्ण *p = str + 10;
        वर्ण *endptr;
        AVChannelLayout extra = {0};
        पूर्णाङ्क order;

        order = strtol(p, &endptr, 0);
        जइ (order < 0 || order + 1  > INT_MAX / (order + 1) ||
            (*endptr && *endptr != '+'))
            प्रत्यागम AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        जइ (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            जइ (ret < 0)
                प्रत्यागम ret;
            जइ (extra.nb_channels >= INT_MAX - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                प्रत्यागम AVERROR(EINVAL);
            }

            जइ (extra.order == AV_CHANNEL_ORDER_NATIVE) {
                channel_layout->u.mask = extra.u.mask;
            } अण्णहा {
                channel_layout->order = AV_CHANNEL_ORDER_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              परिमाण(*channel_layout->u.map));
                जइ (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    प्रत्यागम AVERROR(ENOMEM);
                }

                प्रति (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                प्रति (i = 0; i < extra.nb_channels; i++) {
                    गणना AVChannel ch = av_channel_layout_channel_from_index(&extra, i);
                    जइ (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        प्रत्यागम AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    जइ (extra.order == AV_CHANNEL_ORDER_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   परिमाण(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        प्रत्यागम 0;
    }

    chlist = av_strdup(str);
    जइ (!chlist)
        प्रत्यागम AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    जइ (ret < 0 && ret != AVERROR(EINVAL))
        प्रत्यागम ret;

    जइ (ret >= 0) {
        ध्रुव वर्ण *end_par = strchr(str, ')');
        जइ (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            प्रत्यागम AVERROR(EINVAL);
        }
        प्रत्यागम 0;
    }

    errno = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    जइ (!errno && !*end && !strchr(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        प्रत्यागम 0;
    }

    errno = 0;
    channels = strtol(str, &end, 10);

    /* number of channels */
    जइ (!errno && !strcmp(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        जइ (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            प्रत्यागम 0;
    }

    /* number of unordered channels */
    जइ (!errno && (!strcmp(end, "C") || !strcmp(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        प्रत्यागम 0;
    }

    प्रत्यागम AVERROR(EINVAL);
}

शून्य av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    जइ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, परिमाण(*channel_layout));
}

पूर्णाङ्क av_channel_layout_copy(AVChannelLayout *dst, ध्रुव AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    जइ (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, परिमाण(*dst->u.map));
        जइ (!dst->u.map)
            प्रत्यागम AVERROR(ENOMEM);
        memcpy(dst->u.map, src->u.map, src->nb_channels * परिमाण(*src->u.map));
    }
    प्रत्यागम 0;
}

स्थिर int64_t masked_description(ध्रुव AVChannelLayout *channel_layout, पूर्णाङ्क start_channel)
{
    uint64_t mask = 0;
    प्रति (पूर्णाङ्क i = start_channel; i < channel_layout->nb_channels; i++) {
        गणना AVChannel ch = channel_layout->u.map[i].id;
        जइ (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        अण्णहा
            प्रत्यागम AVERROR(EINVAL);
    }
    प्रत्यागम mask;
}

स्थिर पूर्णाङ्क has_channel_names(ध्रुव AVChannelLayout *channel_layout)
{
    जइ (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        प्रत्यागम 0;
    प्रति (पूर्णाङ्क i = 0; i < channel_layout->nb_channels; i++)
        जइ (channel_layout->u.map[i].name[0])
            प्रत्यागम 1;
    प्रत्यागम 0;
}

पूर्णाङ्क av_channel_layout_ambisonic_order(ध्रुव AVChannelLayout *channel_layout)
{
    पूर्णाङ्क i, highest_ambi, order;

    जइ (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        प्रत्यागम AVERROR(EINVAL);

    highest_ambi = -1;
    जइ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    अण्णहा {
        ध्रुव AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        प्रति (i = 0; i < channel_layout->nb_channels; i++) {
            पूर्णाङ्क is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            जइ (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                प्रत्यागम AVERROR(EINVAL);

            /* non-default ordering */
            जइ (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                प्रत्यागम AVERROR(EINVAL);

            जइ (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    जइ (highest_ambi < 0)
        प्रत्यागम AVERROR(EINVAL);

    order = floor(sqrt(highest_ambi));
    /* incomplete order - some harmonics are missing */
    जइ ((order + 1) * (order + 1) != highest_ambi + 1)
        प्रत्यागम AVERROR(EINVAL);

    प्रत्यागम order;
}

स्थिर गणना AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    पूर्णाङ्क has_known_channel = 0;
    पूर्णाङ्क order;

    जइ (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        प्रत्यागम channel_layout->order;

    जइ (has_channel_names(channel_layout))
        प्रत्यागम AV_CHANNEL_ORDER_CUSTOM;

    प्रति (पूर्णाङ्क i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        जइ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    जइ (!has_known_channel)
        प्रत्यागम AV_CHANNEL_ORDER_UNSPEC;

    जइ (masked_description(channel_layout, 0) > 0)
        प्रत्यागम AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    जइ (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
        प्रत्यागम AV_CHANNEL_ORDER_AMBISONIC;

    प्रत्यागम AV_CHANNEL_ORDER_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
स्थिर पूर्णाङ्क try_describe_ambisonic(AVBPrint *bp, ध्रुव AVChannelLayout *channel_layout)
{
    पूर्णाङ्क nb_ambi_channels;
    पूर्णाङ्क order = av_channel_layout_ambisonic_order(channel_layout);
    जइ (order < 0)
        प्रत्यागम order;

    av_bprintf(bp, "ambisonic %d", order);

    /* extra channels present */
    nb_ambi_channels = (order + 1) * (order + 1);
    जइ (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        जइ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC) {
            extra.order       = AV_CHANNEL_ORDER_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.mask);
            extra.u.mask      = channel_layout->u.mask;
        } अण्णहा {
            int64_t mask;
            जइ (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.order       = AV_CHANNEL_ORDER_NATIVE;
                extra.nb_channels = av_popcount64(mask);
                extra.u.mask      = mask;
            } अण्णहा {
                extra.order       = AV_CHANNEL_ORDER_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    प्रत्यागम 0;
}

पूर्णाङ्क av_channel_layout_describe_bprint(ध्रुव AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    पूर्णाङ्क i;

    विकल्प (channel_layout->order) {
    पक्ष AV_CHANNEL_ORDER_NATIVE:
        प्रति (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            जइ (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                प्रत्यागम 0;
            }
        av_fallthrough;
    पक्ष AV_CHANNEL_ORDER_CUSTOM:
        जइ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            पूर्णाङ्क res = try_describe_ambisonic(bp, channel_layout);
            जइ (res >= 0)
                प्रत्यागम 0;
            जइ (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                प्रत्यागम av_channel_layout_describe_bprint(&native, bp);
            }
        }
        जइ (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        प्रति (i = 0; i < channel_layout->nb_channels; i++) {
            गणना AVChannel ch = av_channel_layout_channel_from_index(channel_layout, i);

            जइ (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            जइ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        जइ (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            प्रत्यागम 0;
        }
        av_fallthrough;
    पक्ष AV_CHANNEL_ORDER_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        प्रत्यागम 0;
    पक्ष AV_CHANNEL_ORDER_AMBISONIC:
        प्रत्यागम try_describe_ambisonic(bp, channel_layout);
    स्वभाव:
        प्रत्यागम AVERROR(EINVAL);
    }
}

पूर्णाङ्क av_channel_layout_describe(ध्रुव AVChannelLayout *channel_layout,
                               वर्ण *buf, size_t buf_size)
{
    AVBPrint bp;
    पूर्णाङ्क ret;

    जइ (!buf && buf_size)
        प्रत्यागम AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    जइ (ret < 0)
        प्रत्यागम ret;

    जइ (bp.len >= INT_MAX)
        प्रत्यागम AVERROR(ERANGE);
    प्रत्यागम bp.len + 1;
}

गणना AVChannel
av_channel_layout_channel_from_index(ध्रुव AVChannelLayout *channel_layout,
                                     unsigned पूर्णाङ्क idx)
{
    पूर्णाङ्क i;

    जइ (idx >= channel_layout->nb_channels)
        प्रत्यागम AV_CHAN_NONE;

    विकल्प (channel_layout->order) {
    पक्ष AV_CHANNEL_ORDER_CUSTOM:
        प्रत्यागम channel_layout->u.map[idx].id;
    पक्ष AV_CHANNEL_ORDER_AMBISONIC: {
        पूर्णाङ्क ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        जइ (idx < ambi_channels)
            प्रत्यागम AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    पक्ष AV_CHANNEL_ORDER_NATIVE:
        प्रति (i = 0; i < 64; i++) {
            जइ ((1ULL << i) & channel_layout->u.mask && !idx--)
                प्रत्यागम i;
        }
        av_fallthrough;
    स्वभाव:
        प्रत्यागम AV_CHAN_NONE;
    }
}

गणना AVChannel
av_channel_layout_channel_from_string(ध्रुव AVChannelLayout *channel_layout,
                                      ध्रुव वर्ण *str)
{
    पूर्णाङ्क index = av_channel_layout_index_from_string(channel_layout, str);

    जइ (index < 0)
        प्रत्यागम AV_CHAN_NONE;

    प्रत्यागम av_channel_layout_channel_from_index(channel_layout, index);
}

पूर्णाङ्क av_channel_layout_index_from_channel(ध्रुव AVChannelLayout *channel_layout,
                                         गणना AVChannel channel)
{
    पूर्णाङ्क i;

    जइ (channel == AV_CHAN_NONE)
        प्रत्यागम AVERROR(EINVAL);

    विकल्प (channel_layout->order) {
    पक्ष AV_CHANNEL_ORDER_CUSTOM:
        प्रति (i = 0; i < channel_layout->nb_channels; i++)
            जइ (channel_layout->u.map[i].id == channel)
                प्रत्यागम i;
        प्रत्यागम AVERROR(EINVAL);
    पक्ष AV_CHANNEL_ORDER_AMBISONIC:
    पक्ष AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        पूर्णाङ्क ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        जइ (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            जइ (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                प्रत्यागम AVERROR(EINVAL);
            प्रत्यागम channel - AV_CHAN_AMBISONIC_BASE;
        }
        जइ ((unsigned)channel > 63 || !(mask & (1ULL << channel)))
            प्रत्यागम AVERROR(EINVAL);
        mask &= (1ULL << channel) - 1;
        प्रत्यागम av_popcount64(mask) + ambi_channels;
        }
    स्वभाव:
        प्रत्यागम AVERROR(EINVAL);
    }
}

पूर्णाङ्क av_channel_layout_index_from_string(ध्रुव AVChannelLayout *channel_layout,
                                        ध्रुव वर्ण *str)
{
    ध्रुव वर्ण *chname;
    गणना AVChannel ch = AV_CHAN_NONE;

    विकल्प (channel_layout->order) {
    पक्ष AV_CHANNEL_ORDER_CUSTOM:
        chname = strstr(str, "@");
        जइ (chname) {
            वर्ण buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(परिमाण(buf), chname - str));
            जइ (!*chname)
                chname = रिक्त;
            ch = av_channel_from_string(buf);
            जइ (ch == AV_CHAN_NONE && *buf)
                प्रत्यागम AVERROR(EINVAL);
        }
        प्रति (पूर्णाङ्क i = 0; chname && i < channel_layout->nb_channels; i++) {
            जइ (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                प्रत्यागम i;
        }
        av_fallthrough;
    पक्ष AV_CHANNEL_ORDER_AMBISONIC:
    पक्ष AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        जइ (ch == AV_CHAN_NONE)
            प्रत्यागम AVERROR(EINVAL);
        प्रत्यागम av_channel_layout_index_from_channel(channel_layout, ch);
    }

    प्रत्यागम AVERROR(EINVAL);
}

पूर्णाङ्क av_channel_layout_check(ध्रुव AVChannelLayout *channel_layout)
{
    जइ (channel_layout->nb_channels <= 0)
        प्रत्यागम 0;

    विकल्प (channel_layout->order) {
    पक्ष AV_CHANNEL_ORDER_NATIVE:
        प्रत्यागम av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    पक्ष AV_CHANNEL_ORDER_CUSTOM:
        जइ (!channel_layout->u.map)
            प्रत्यागम 0;
        प्रति (पूर्णाङ्क i = 0; i < channel_layout->nb_channels; i++) {
            जइ (channel_layout->u.map[i].id == AV_CHAN_NONE)
                प्रत्यागम 0;
        }
        प्रत्यागम 1;
    पक्ष AV_CHANNEL_ORDER_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        प्रत्यागम av_popcount64(channel_layout->u.mask) < channel_layout->nb_channels;
    पक्ष AV_CHANNEL_ORDER_UNSPEC:
        प्रत्यागम 1;
    स्वभाव:
        प्रत्यागम 0;
    }
}

पूर्णाङ्क av_channel_layout_compare(ध्रुव AVChannelLayout *chl, ध्रुव AVChannelLayout *chl1)
{
    पूर्णाङ्क i;

    /* different channel counts -> not equal */
    जइ (chl->nb_channels != chl1->nb_channels)
        प्रत्यागम 1;

    /* if only one is unspecified -> not equal */
    जइ ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        प्रत्यागम 1;
    /* both are unspecified -> equal */
    अण्णहा जइ (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        प्रत्यागम 0;

    /* can compare masks directly */
    जइ ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        प्रत्यागम chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    प्रति (i = 0; i < chl->nb_channels; i++)
        जइ (av_channel_layout_channel_from_index(chl,  i) !=
            av_channel_layout_channel_from_index(chl1, i))
            प्रत्यागम 1;
    प्रत्यागम 0;
}

शून्य av_channel_layout_default(AVChannelLayout *ch_layout, पूर्णाङ्क nb_channels)
{
    पूर्णाङ्क i;
    प्रति (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        जइ (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            प्रत्यागम;
        }

    ch_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

ध्रुव AVChannelLayout *av_channel_layout_standard(शून्य **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ध्रुव AVChannelLayout *ch_layout = रिक्त;

    जइ (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (शून्य*)(i + 1);
    }

    प्रत्यागम ch_layout;
}

uint64_t av_channel_layout_subset(ध्रुव AVChannelLayout *channel_layout,
                                  uint64_t mask)
{
    uint64_t ret = 0;
    पूर्णाङ्क i;

    विकल्प (channel_layout->order) {
    पक्ष AV_CHANNEL_ORDER_NATIVE:
    पक्ष AV_CHANNEL_ORDER_AMBISONIC:
        प्रत्यागम channel_layout->u.mask & mask;
    पक्ष AV_CHANNEL_ORDER_CUSTOM:
        प्रति (i = 0; i < 64; i++)
            जइ (mask & (1ULL << i) && av_channel_layout_index_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        भङ्ग;
    }

    प्रत्यागम ret;
}

पूर्णाङ्क av_channel_layout_retype(AVChannelLayout *channel_layout, गणना AVChannelOrder order, पूर्णाङ्क flags)
{
    पूर्णाङ्क allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    पूर्णाङ्क lossy;

    जइ (!av_channel_layout_check(channel_layout))
        प्रत्यागम AVERROR(EINVAL);

    जइ (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    जइ (channel_layout->order == order)
        प्रत्यागम 0;

    विकल्प (order) {
    पक्ष AV_CHANNEL_ORDER_UNSPEC: {
        पूर्णाङ्क nb_channels = channel_layout->nb_channels;
        जइ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            प्रति (पूर्णाङ्क i = 0; i < nb_channels; i++) {
                जइ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    भङ्ग;
                }
            }
        } अण्णहा {
            lossy = 1;
        }
        जइ (!lossy || allow_lossy) {
            शून्य *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            प्रत्यागम lossy;
        }
        प्रत्यागम AVERROR(ENOSYS);
        }
    पक्ष AV_CHANNEL_ORDER_NATIVE:
        जइ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            जइ (mask < 0)
                प्रत्यागम AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            जइ (!lossy || allow_lossy) {
                शून्य *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_mask(channel_layout, mask);
                channel_layout->opaque = opaque;
                प्रत्यागम lossy;
            }
        }
        प्रत्यागम AVERROR(ENOSYS);
    पक्ष AV_CHANNEL_ORDER_CUSTOM: {
        AVChannelLayout custom = { 0 };
        पूर्णाङ्क ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        शून्य *opaque = channel_layout->opaque;
        जइ (ret < 0)
            प्रत्यागम ret;
        जइ (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            प्रति (पूर्णाङ्क i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_index(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        प्रत्यागम 0;
        }
    पक्ष AV_CHANNEL_ORDER_AMBISONIC:
        जइ (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            पूर्णाङ्क nb_channels = channel_layout->nb_channels;
            पूर्णाङ्क amb_order = av_channel_layout_ambisonic_order(channel_layout);
            जइ (amb_order < 0)
                प्रत्यागम AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            जइ (mask < 0)
                प्रत्यागम AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            जइ (!lossy || allow_lossy) {
                शून्य *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.mask      = mask;
                channel_layout->opaque      = opaque;
                प्रत्यागम lossy;
            }
        }
        प्रत्यागम AVERROR(ENOSYS);
    स्वभाव:
        प्रत्यागम AVERROR(EINVAL);
    }
}
