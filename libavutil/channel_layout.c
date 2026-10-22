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
    स्थिरांक अक्षर *name;
    स्थिरांक अक्षर *description;
};

स्थिर स्थिरांक संरचना channel_name channel_names[] = {
    [AV_CHAN_FRONT_डावा           ] = { "FL",        "front left"            },
    [AV_CHAN_FRONT_उजवा          ] = { "FR",        "front right"           },
    [AV_CHAN_FRONT_CENTER         ] = { "FC",        "front center"          },
    [AV_CHAN_खालचा_FREQUENCY        ] = { "LFE",       "low frequency"         },
    [AV_CHAN_BACK_डावा            ] = { "BL",        "back left"             },
    [AV_CHAN_BACK_उजवा           ] = { "BR",        "back right"            },
    [AV_CHAN_FRONT_डावा_OF_CENTER ] = { "FLC",       "front left-of-center"  },
    [AV_CHAN_FRONT_उजवा_OF_CENTER] = { "FRC",       "front right-of-center" },
    [AV_CHAN_BACK_CENTER          ] = { "BC",        "back center"           },
    [AV_CHAN_SIDE_डावा            ] = { "SL",        "side left"             },
    [AV_CHAN_SIDE_उजवा           ] = { "SR",        "side right"            },
    [AV_CHAN_शीर्ष_CENTER           ] = { "TC",        "top center"            },
    [AV_CHAN_शीर्ष_FRONT_डावा       ] = { "TFL",       "top front left"        },
    [AV_CHAN_शीर्ष_FRONT_CENTER     ] = { "TFC",       "top front center"      },
    [AV_CHAN_शीर्ष_FRONT_उजवा      ] = { "TFR",       "top front right"       },
    [AV_CHAN_शीर्ष_BACK_डावा        ] = { "TBL",       "top back left"         },
    [AV_CHAN_शीर्ष_BACK_CENTER      ] = { "TBC",       "top back center"       },
    [AV_CHAN_शीर्ष_BACK_उजवा       ] = { "TBR",       "top back right"        },
    [AV_CHAN_STEREO_डावा          ] = { "DL",        "downmix left"          },
    [AV_CHAN_STEREO_उजवा         ] = { "DR",        "downmix right"         },
    [AV_CHAN_WIDE_डावा            ] = { "WL",        "wide left"             },
    [AV_CHAN_WIDE_उजवा           ] = { "WR",        "wide right"            },
    [AV_CHAN_SURROUND_DIRECT_डावा ] = { "SDL",       "surround direct left"  },
    [AV_CHAN_SURROUND_DIRECT_उजवा] = { "SDR",       "surround direct right" },
    [AV_CHAN_खालचा_FREQUENCY_2      ] = { "LFE2",      "low frequency 2"       },
    [AV_CHAN_शीर्ष_SIDE_डावा        ] = { "TSL",       "top side left"         },
    [AV_CHAN_शीर्ष_SIDE_उजवा       ] = { "TSR",       "top side right"        },
    [AV_CHAN_BOTTOM_FRONT_CENTER  ] = { "BFC",       "bottom front center"   },
    [AV_CHAN_BOTTOM_FRONT_डावा    ] = { "BFL",       "bottom front left"     },
    [AV_CHAN_BOTTOM_FRONT_उजवा   ] = { "BFR",       "bottom front right"    },
    [AV_CHAN_SIDE_SURROUND_डावा   ] = { "SSL",       "side surround left"    },
    [AV_CHAN_SIDE_SURROUND_उजवा  ] = { "SSR",       "side surround right"   },
    [AV_CHAN_शीर्ष_SURROUND_डावा    ] = { "TTL",       "top surround left"     },
    [AV_CHAN_शीर्ष_SURROUND_उजवा   ] = { "TTR",       "top surround right"    },
    [AV_CHAN_BINAURAL_डावा        ] = { "BIL",       "binaural left"         },
    [AV_CHAN_BINAURAL_उजवा       ] = { "BIR",       "binaural right"        },
};

शून्य av_channel_name_bprint(AVBPrint *bp, गणना AVChannel channel_id)
{
    जर (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_BASE);
    अन्यथा जर ((अचिन्हित)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].name)
        av_bprintf(bp, "%s", channel_names[channel_id].name);
    अन्यथा जर (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    अन्यथा जर (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    अन्यथा जर (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "UNSD");
    अन्यथा
        av_bprintf(bp, "USR%d", channel_id);
}

पूर्णांक av_channel_name(अक्षर *buf, माप_प्रकार buf_size, गणना AVChannel channel_id)
{
    AVBPrint bp;

    जर (!buf && buf_size)
        परत AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_name_bprint(&bp, channel_id);

    जर (bp.len >= पूर्णांक_उच्च)
        परत AVERROR(दुस्फल);
    परत bp.len + 1;
}

शून्य av_channel_description_bprint(AVBPrint *bp, गणना AVChannel channel_id)
{
    जर (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_BASE);
    अन्यथा जर ((अचिन्हित)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].description)
        av_bprintf(bp, "%s", channel_names[channel_id].description);
    अन्यथा जर (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    अन्यथा जर (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    अन्यथा जर (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "unused");
    अन्यथा
        av_bprintf(bp, "user %d", channel_id);
}

पूर्णांक av_channel_description(अक्षर *buf, माप_प्रकार buf_size, गणना AVChannel channel_id)
{
    AVBPrint bp;

    जर (!buf && buf_size)
        परत AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_description_bprint(&bp, channel_id);

    जर (bp.len >= पूर्णांक_उच्च)
        परत AVERROR(दुस्फल);
    परत bp.len + 1;
}

गणना AVChannel av_channel_from_string(स्थिरांक अक्षर *str)
{
    पूर्णांक i;
    अक्षर *endptr = (अक्षर *)str;
    गणना AVChannel id = AV_CHAN_NONE;

    जर (!म_भेदन(str, "AMBI", 4)) {
        i = म_से_दीर्घ(str + 4, रिक्त, 0);
        जर (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            परत AV_CHAN_NONE;
        परत AV_CHAN_AMBISONIC_BASE + i;
    }

    साठी (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        जर (channel_names[i].name && !म_भेद(str, channel_names[i].name))
            परत i;
    }
    जर (!म_भेद(str, "UNK"))
        परत AV_CHAN_UNKNOWN;
    जर (!म_भेद(str, "UNSD"))
        परत AV_CHAN_UNUSED;

    जर (!म_भेदन(str, "USR", 3)) {
        स्थिरांक अक्षर *p = str + 3;
        id = म_से_दीर्घ(p, &endptr, 0);
    }
    जर (id >= 0 && !*endptr)
        परत id;

    परत AV_CHAN_NONE;
}

संरचना channel_layout_name {
    स्थिरांक अक्षर *name;
    AVChannelLayout layout;
};

स्थिर स्थिरांक संरचना channel_layout_name channel_layout_map[] = {
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

पूर्णांक av_channel_layout_custom_init(AVChannelLayout *channel_layout, पूर्णांक nb_channels)
{
    AVChannelCustom *map;

    जर (nb_channels <= 0)
        परत AVERROR(EINVAL);

    map = av_calloc(nb_channels, आकार(*channel_layout->u.map));
    जर (!map)
        परत AVERROR(ENOMEM);
    साठी (पूर्णांक i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->order       = AV_CHANNEL_ORDER_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    परत 0;
}

पूर्णांक av_channel_layout_from_mask(AVChannelLayout *channel_layout,
                                uint64_t mask)
{
    जर (!mask)
        परत AVERROR(EINVAL);

    channel_layout->order       = AV_CHANNEL_ORDER_NATIVE;
    channel_layout->nb_channels = av_popcount64(mask);
    channel_layout->u.mask      = mask;

    परत 0;
}

स्थिर पूर्णांक parse_channel_list(AVChannelLayout *ch_layout, स्थिरांक अक्षर *str)
{
    पूर्णांक ret;
    पूर्णांक nb_channels = 0;
    AVChannelCustom *map = रिक्त;
    AVChannelCustom custom = {0};

    पर्यंत (*str) {
        अक्षर *channel, *chname;
        ret = av_opt_get_किल्ली_मूल्य(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_किल्ली, &channel, &chname);
        जर (ret < 0) {
            av_freep(&map);
            परत ret;
        }
        जर (*str)
            str++; // skip separator
        जर (!channel) {
            channel = chname;
            chname = रिक्त;
        }
        av_strlcpy(custom.name, chname ? chname : "", आकार(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        जर (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            परत AVERROR(EINVAL);
        }

        av_dynarray2_add((शून्य **)&map, &nb_channels, आकार(custom), (शून्य *)&custom);
        जर (!map)
            परत AVERROR(ENOMEM);
    }

    जर (!nb_channels)
        परत AVERROR(EINVAL);

    ch_layout->order = AV_CHANNEL_ORDER_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    परत 0;
}

पूर्णांक av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  स्थिरांक अक्षर *str)
{
    पूर्णांक i, matches, ret;
    पूर्णांक channels = 0, nb_channels = 0;
    अक्षर *chlist, *end;
    uint64_t mask = 0;

    /* channel layout names */
    साठी (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        जर (channel_layout_map[i].name && !म_भेद(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            परत 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    स_रखो(channel_layout, 0, आकार(*channel_layout));

    /* ambisonic */
    जर (!म_भेदन(str, "ambisonic ", 10)) {
        स्थिरांक अक्षर *p = str + 10;
        अक्षर *endptr;
        AVChannelLayout extra = {0};
        पूर्णांक order;

        order = म_से_दीर्घ(p, &endptr, 0);
        जर (order < 0 || order + 1  > पूर्णांक_उच्च / (order + 1) ||
            (*endptr && *endptr != '+'))
            परत AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        जर (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            जर (ret < 0)
                परत ret;
            जर (extra.nb_channels >= पूर्णांक_उच्च - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                परत AVERROR(EINVAL);
            }

            जर (extra.order == AV_CHANNEL_ORDER_NATIVE) {
                channel_layout->u.mask = extra.u.mask;
            } अन्यथा {
                channel_layout->order = AV_CHANNEL_ORDER_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              आकार(*channel_layout->u.map));
                जर (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    परत AVERROR(ENOMEM);
                }

                साठी (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                साठी (i = 0; i < extra.nb_channels; i++) {
                    गणना AVChannel ch = av_channel_layout_channel_from_index(&extra, i);
                    जर (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        परत AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    जर (extra.order == AV_CHANNEL_ORDER_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   आकार(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        परत 0;
    }

    chlist = av_strdup(str);
    जर (!chlist)
        परत AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    जर (ret < 0 && ret != AVERROR(EINVAL))
        परत ret;

    जर (ret >= 0) {
        स्थिरांक अक्षर *end_par = म_अक्षर(str, ')');
        जर (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            परत AVERROR(EINVAL);
        }
        परत 0;
    }

    त्रुटि_सं = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    जर (!त्रुटि_सं && !*end && !म_अक्षर(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        परत 0;
    }

    त्रुटि_सं = 0;
    channels = म_से_दीर्घ(str, &end, 10);

    /* number of channels */
    जर (!त्रुटि_सं && !म_भेद(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        जर (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            परत 0;
    }

    /* number of unordered channels */
    जर (!त्रुटि_सं && (!म_भेद(end, "C") || !म_भेद(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        परत 0;
    }

    परत AVERROR(EINVAL);
}

शून्य av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    जर (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    स_रखो(channel_layout, 0, आकार(*channel_layout));
}

पूर्णांक av_channel_layout_copy(AVChannelLayout *dst, स्थिरांक AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    जर (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, आकार(*dst->u.map));
        जर (!dst->u.map)
            परत AVERROR(ENOMEM);
        स_नकल(dst->u.map, src->u.map, src->nb_channels * आकार(*src->u.map));
    }
    परत 0;
}

स्थिर int64_t masked_description(स्थिरांक AVChannelLayout *channel_layout, पूर्णांक start_channel)
{
    uint64_t mask = 0;
    साठी (पूर्णांक i = start_channel; i < channel_layout->nb_channels; i++) {
        गणना AVChannel ch = channel_layout->u.map[i].id;
        जर (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        अन्यथा
            परत AVERROR(EINVAL);
    }
    परत mask;
}

स्थिर पूर्णांक has_channel_names(स्थिरांक AVChannelLayout *channel_layout)
{
    जर (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        परत 0;
    साठी (पूर्णांक i = 0; i < channel_layout->nb_channels; i++)
        जर (channel_layout->u.map[i].name[0])
            परत 1;
    परत 0;
}

पूर्णांक av_channel_layout_ambisonic_order(स्थिरांक AVChannelLayout *channel_layout)
{
    पूर्णांक i, highest_ambi, order;

    जर (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        परत AVERROR(EINVAL);

    highest_ambi = -1;
    जर (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    अन्यथा {
        स्थिरांक AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        साठी (i = 0; i < channel_layout->nb_channels; i++) {
            पूर्णांक is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            जर (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                परत AVERROR(EINVAL);

            /* non-default ordering */
            जर (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                परत AVERROR(EINVAL);

            जर (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    जर (highest_ambi < 0)
        परत AVERROR(EINVAL);

    order = न्यूनमान(वर्ग_मूल(highest_ambi));
    /* incomplete order - some harmonics are missing */
    जर ((order + 1) * (order + 1) != highest_ambi + 1)
        परत AVERROR(EINVAL);

    परत order;
}

स्थिर गणना AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    पूर्णांक has_known_channel = 0;
    पूर्णांक order;

    जर (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        परत channel_layout->order;

    जर (has_channel_names(channel_layout))
        परत AV_CHANNEL_ORDER_CUSTOM;

    साठी (पूर्णांक i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        जर (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    जर (!has_known_channel)
        परत AV_CHANNEL_ORDER_UNSPEC;

    जर (masked_description(channel_layout, 0) > 0)
        परत AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    जर (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
        परत AV_CHANNEL_ORDER_AMBISONIC;

    परत AV_CHANNEL_ORDER_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
स्थिर पूर्णांक try_describe_ambisonic(AVBPrint *bp, स्थिरांक AVChannelLayout *channel_layout)
{
    पूर्णांक nb_ambi_channels;
    पूर्णांक order = av_channel_layout_ambisonic_order(channel_layout);
    जर (order < 0)
        परत order;

    av_bprintf(bp, "ambisonic %d", order);

    /* extra channels present */
    nb_ambi_channels = (order + 1) * (order + 1);
    जर (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        जर (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC) {
            extra.order       = AV_CHANNEL_ORDER_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.mask);
            extra.u.mask      = channel_layout->u.mask;
        } अन्यथा {
            int64_t mask;
            जर (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.order       = AV_CHANNEL_ORDER_NATIVE;
                extra.nb_channels = av_popcount64(mask);
                extra.u.mask      = mask;
            } अन्यथा {
                extra.order       = AV_CHANNEL_ORDER_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    परत 0;
}

पूर्णांक av_channel_layout_describe_bprint(स्थिरांक AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    पूर्णांक i;

    निवड (channel_layout->order) {
    स्थिती AV_CHANNEL_ORDER_NATIVE:
        साठी (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            जर (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                परत 0;
            }
        av_fallthrough;
    स्थिती AV_CHANNEL_ORDER_CUSTOM:
        जर (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            पूर्णांक res = try_describe_ambisonic(bp, channel_layout);
            जर (res >= 0)
                परत 0;
            जर (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                परत av_channel_layout_describe_bprint(&native, bp);
            }
        }
        जर (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        साठी (i = 0; i < channel_layout->nb_channels; i++) {
            गणना AVChannel ch = av_channel_layout_channel_from_index(channel_layout, i);

            जर (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            जर (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        जर (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            परत 0;
        }
        av_fallthrough;
    स्थिती AV_CHANNEL_ORDER_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        परत 0;
    स्थिती AV_CHANNEL_ORDER_AMBISONIC:
        परत try_describe_ambisonic(bp, channel_layout);
    पूर्वनिर्धारित:
        परत AVERROR(EINVAL);
    }
}

पूर्णांक av_channel_layout_describe(स्थिरांक AVChannelLayout *channel_layout,
                               अक्षर *buf, माप_प्रकार buf_size)
{
    AVBPrint bp;
    पूर्णांक ret;

    जर (!buf && buf_size)
        परत AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    जर (ret < 0)
        परत ret;

    जर (bp.len >= पूर्णांक_उच्च)
        परत AVERROR(दुस्फल);
    परत bp.len + 1;
}

गणना AVChannel
av_channel_layout_channel_from_index(स्थिरांक AVChannelLayout *channel_layout,
                                     अचिन्हित पूर्णांक idx)
{
    पूर्णांक i;

    जर (idx >= channel_layout->nb_channels)
        परत AV_CHAN_NONE;

    निवड (channel_layout->order) {
    स्थिती AV_CHANNEL_ORDER_CUSTOM:
        परत channel_layout->u.map[idx].id;
    स्थिती AV_CHANNEL_ORDER_AMBISONIC: {
        पूर्णांक ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        जर (idx < ambi_channels)
            परत AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    स्थिती AV_CHANNEL_ORDER_NATIVE:
        साठी (i = 0; i < 64; i++) {
            जर ((1ULL << i) & channel_layout->u.mask && !idx--)
                परत i;
        }
        av_fallthrough;
    पूर्वनिर्धारित:
        परत AV_CHAN_NONE;
    }
}

गणना AVChannel
av_channel_layout_channel_from_string(स्थिरांक AVChannelLayout *channel_layout,
                                      स्थिरांक अक्षर *str)
{
    पूर्णांक index = av_channel_layout_index_from_string(channel_layout, str);

    जर (index < 0)
        परत AV_CHAN_NONE;

    परत av_channel_layout_channel_from_index(channel_layout, index);
}

पूर्णांक av_channel_layout_index_from_channel(स्थिरांक AVChannelLayout *channel_layout,
                                         गणना AVChannel channel)
{
    पूर्णांक i;

    जर (channel == AV_CHAN_NONE)
        परत AVERROR(EINVAL);

    निवड (channel_layout->order) {
    स्थिती AV_CHANNEL_ORDER_CUSTOM:
        साठी (i = 0; i < channel_layout->nb_channels; i++)
            जर (channel_layout->u.map[i].id == channel)
                परत i;
        परत AVERROR(EINVAL);
    स्थिती AV_CHANNEL_ORDER_AMBISONIC:
    स्थिती AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        पूर्णांक ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        जर (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            जर (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                परत AVERROR(EINVAL);
            परत channel - AV_CHAN_AMBISONIC_BASE;
        }
        जर ((अचिन्हित)channel > 63 || !(mask & (1ULL << channel)))
            परत AVERROR(EINVAL);
        mask &= (1ULL << channel) - 1;
        परत av_popcount64(mask) + ambi_channels;
        }
    पूर्वनिर्धारित:
        परत AVERROR(EINVAL);
    }
}

पूर्णांक av_channel_layout_index_from_string(स्थिरांक AVChannelLayout *channel_layout,
                                        स्थिरांक अक्षर *str)
{
    स्थिरांक अक्षर *chname;
    गणना AVChannel ch = AV_CHAN_NONE;

    निवड (channel_layout->order) {
    स्थिती AV_CHANNEL_ORDER_CUSTOM:
        chname = म_माला(str, "@");
        जर (chname) {
            अक्षर buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(आकार(buf), chname - str));
            जर (!*chname)
                chname = रिक्त;
            ch = av_channel_from_string(buf);
            जर (ch == AV_CHAN_NONE && *buf)
                परत AVERROR(EINVAL);
        }
        साठी (पूर्णांक i = 0; chname && i < channel_layout->nb_channels; i++) {
            जर (!म_भेद(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                परत i;
        }
        av_fallthrough;
    स्थिती AV_CHANNEL_ORDER_AMBISONIC:
    स्थिती AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        जर (ch == AV_CHAN_NONE)
            परत AVERROR(EINVAL);
        परत av_channel_layout_index_from_channel(channel_layout, ch);
    }

    परत AVERROR(EINVAL);
}

पूर्णांक av_channel_layout_check(स्थिरांक AVChannelLayout *channel_layout)
{
    जर (channel_layout->nb_channels <= 0)
        परत 0;

    निवड (channel_layout->order) {
    स्थिती AV_CHANNEL_ORDER_NATIVE:
        परत av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    स्थिती AV_CHANNEL_ORDER_CUSTOM:
        जर (!channel_layout->u.map)
            परत 0;
        साठी (पूर्णांक i = 0; i < channel_layout->nb_channels; i++) {
            जर (channel_layout->u.map[i].id == AV_CHAN_NONE)
                परत 0;
        }
        परत 1;
    स्थिती AV_CHANNEL_ORDER_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        परत av_popcount64(channel_layout->u.mask) < channel_layout->nb_channels;
    स्थिती AV_CHANNEL_ORDER_UNSPEC:
        परत 1;
    पूर्वनिर्धारित:
        परत 0;
    }
}

पूर्णांक av_channel_layout_compare(स्थिरांक AVChannelLayout *chl, स्थिरांक AVChannelLayout *chl1)
{
    पूर्णांक i;

    /* different channel counts -> not equal */
    जर (chl->nb_channels != chl1->nb_channels)
        परत 1;

    /* if only one is unspecified -> not equal */
    जर ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        परत 1;
    /* both are unspecified -> equal */
    अन्यथा जर (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        परत 0;

    /* can compare masks directly */
    जर ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        परत chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    साठी (i = 0; i < chl->nb_channels; i++)
        जर (av_channel_layout_channel_from_index(chl,  i) !=
            av_channel_layout_channel_from_index(chl1, i))
            परत 1;
    परत 0;
}

शून्य av_channel_layout_default(AVChannelLayout *ch_layout, पूर्णांक nb_channels)
{
    पूर्णांक i;
    साठी (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        जर (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            परत;
        }

    ch_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

स्थिरांक AVChannelLayout *av_channel_layout_standard(शून्य **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    स्थिरांक AVChannelLayout *ch_layout = रिक्त;

    जर (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (शून्य*)(i + 1);
    }

    परत ch_layout;
}

uint64_t av_channel_layout_subset(स्थिरांक AVChannelLayout *channel_layout,
                                  uint64_t mask)
{
    uint64_t ret = 0;
    पूर्णांक i;

    निवड (channel_layout->order) {
    स्थिती AV_CHANNEL_ORDER_NATIVE:
    स्थिती AV_CHANNEL_ORDER_AMBISONIC:
        परत channel_layout->u.mask & mask;
    स्थिती AV_CHANNEL_ORDER_CUSTOM:
        साठी (i = 0; i < 64; i++)
            जर (mask & (1ULL << i) && av_channel_layout_index_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        थांबा;
    }

    परत ret;
}

पूर्णांक av_channel_layout_retype(AVChannelLayout *channel_layout, गणना AVChannelOrder order, पूर्णांक flags)
{
    पूर्णांक allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    पूर्णांक lossy;

    जर (!av_channel_layout_check(channel_layout))
        परत AVERROR(EINVAL);

    जर (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    जर (channel_layout->order == order)
        परत 0;

    निवड (order) {
    स्थिती AV_CHANNEL_ORDER_UNSPEC: {
        पूर्णांक nb_channels = channel_layout->nb_channels;
        जर (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            साठी (पूर्णांक i = 0; i < nb_channels; i++) {
                जर (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    थांबा;
                }
            }
        } अन्यथा {
            lossy = 1;
        }
        जर (!lossy || allow_lossy) {
            शून्य *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            परत lossy;
        }
        परत AVERROR(ENOSYS);
        }
    स्थिती AV_CHANNEL_ORDER_NATIVE:
        जर (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            जर (mask < 0)
                परत AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            जर (!lossy || allow_lossy) {
                शून्य *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_mask(channel_layout, mask);
                channel_layout->opaque = opaque;
                परत lossy;
            }
        }
        परत AVERROR(ENOSYS);
    स्थिती AV_CHANNEL_ORDER_CUSTOM: {
        AVChannelLayout custom = { 0 };
        पूर्णांक ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        शून्य *opaque = channel_layout->opaque;
        जर (ret < 0)
            परत ret;
        जर (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            साठी (पूर्णांक i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_index(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        परत 0;
        }
    स्थिती AV_CHANNEL_ORDER_AMBISONIC:
        जर (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            पूर्णांक nb_channels = channel_layout->nb_channels;
            पूर्णांक amb_order = av_channel_layout_ambisonic_order(channel_layout);
            जर (amb_order < 0)
                परत AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            जर (mask < 0)
                परत AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            जर (!lossy || allow_lossy) {
                शून्य *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.mask      = mask;
                channel_layout->opaque      = opaque;
                परत lossy;
            }
        }
        परत AVERROR(ENOSYS);
    पूर्वनिर्धारित:
        परत AVERROR(EINVAL);
    }
}
