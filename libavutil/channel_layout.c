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
    [AV_CHAN_FRONT_बायाँ           ] = { "FL",        "front left"            },
    [AV_CHAN_FRONT_दायाँ          ] = { "FR",        "front right"           },
    [AV_CHAN_FRONT_CENTER         ] = { "FC",        "front center"          },
    [AV_CHAN_निचला_FREQUENCY        ] = { "LFE",       "low frequency"         },
    [AV_CHAN_BACK_बायाँ            ] = { "BL",        "back left"             },
    [AV_CHAN_BACK_दायाँ           ] = { "BR",        "back right"            },
    [AV_CHAN_FRONT_बायाँ_OF_CENTER ] = { "FLC",       "front left-of-center"  },
    [AV_CHAN_FRONT_दायाँ_OF_CENTER] = { "FRC",       "front right-of-center" },
    [AV_CHAN_BACK_CENTER          ] = { "BC",        "back center"           },
    [AV_CHAN_SIDE_बायाँ            ] = { "SL",        "side left"             },
    [AV_CHAN_SIDE_दायाँ           ] = { "SR",        "side right"            },
    [AV_CHAN_शीर्ष_CENTER           ] = { "TC",        "top center"            },
    [AV_CHAN_शीर्ष_FRONT_बायाँ       ] = { "TFL",       "top front left"        },
    [AV_CHAN_शीर्ष_FRONT_CENTER     ] = { "TFC",       "top front center"      },
    [AV_CHAN_शीर्ष_FRONT_दायाँ      ] = { "TFR",       "top front right"       },
    [AV_CHAN_शीर्ष_BACK_बायाँ        ] = { "TBL",       "top back left"         },
    [AV_CHAN_शीर्ष_BACK_CENTER      ] = { "TBC",       "top back center"       },
    [AV_CHAN_शीर्ष_BACK_दायाँ       ] = { "TBR",       "top back right"        },
    [AV_CHAN_STEREO_बायाँ          ] = { "DL",        "downmix left"          },
    [AV_CHAN_STEREO_दायाँ         ] = { "DR",        "downmix right"         },
    [AV_CHAN_WIDE_बायाँ            ] = { "WL",        "wide left"             },
    [AV_CHAN_WIDE_दायाँ           ] = { "WR",        "wide right"            },
    [AV_CHAN_SURROUND_DIRECT_बायाँ ] = { "SDL",       "surround direct left"  },
    [AV_CHAN_SURROUND_DIRECT_दायाँ] = { "SDR",       "surround direct right" },
    [AV_CHAN_निचला_FREQUENCY_2      ] = { "LFE2",      "low frequency 2"       },
    [AV_CHAN_शीर्ष_SIDE_बायाँ        ] = { "TSL",       "top side left"         },
    [AV_CHAN_शीर्ष_SIDE_दायाँ       ] = { "TSR",       "top side right"        },
    [AV_CHAN_BOTTOM_FRONT_CENTER  ] = { "BFC",       "bottom front center"   },
    [AV_CHAN_BOTTOM_FRONT_बायाँ    ] = { "BFL",       "bottom front left"     },
    [AV_CHAN_BOTTOM_FRONT_दायाँ   ] = { "BFR",       "bottom front right"    },
    [AV_CHAN_SIDE_SURROUND_बायाँ   ] = { "SSL",       "side surround left"    },
    [AV_CHAN_SIDE_SURROUND_दायाँ  ] = { "SSR",       "side surround right"   },
    [AV_CHAN_शीर्ष_SURROUND_बायाँ    ] = { "TTL",       "top surround left"     },
    [AV_CHAN_शीर्ष_SURROUND_दायाँ   ] = { "TTR",       "top surround right"    },
    [AV_CHAN_BINAURAL_बायाँ        ] = { "BIL",       "binaural left"         },
    [AV_CHAN_BINAURAL_दायाँ       ] = { "BIR",       "binaural right"        },
};

शून्य av_channel_name_bprint(AVBPrint *bp, गणना AVChannel channel_id)
{
    यदि (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_BASE);
    अन्यथा यदि ((अचिन्हित)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].name)
        av_bprintf(bp, "%s", channel_names[channel_id].name);
    अन्यथा यदि (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    अन्यथा यदि (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    अन्यथा यदि (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "UNSD");
    अन्यथा
        av_bprintf(bp, "USR%d", channel_id);
}

पूर्णाङ्क av_channel_name(वर्ण *buf, माप_प्रकार buf_size, गणना AVChannel channel_id)
{
    AVBPrint bp;

    यदि (!buf && buf_size)
        प्रत्यागम AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_name_bprint(&bp, channel_id);

    यदि (bp.len >= पूर्णांक_उच्च)
        प्रत्यागम AVERROR(दुस्फल);
    प्रत्यागम bp.len + 1;
}

शून्य av_channel_description_bprint(AVBPrint *bp, गणना AVChannel channel_id)
{
    यदि (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_BASE);
    अन्यथा यदि ((अचिन्हित)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].description)
        av_bprintf(bp, "%s", channel_names[channel_id].description);
    अन्यथा यदि (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    अन्यथा यदि (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    अन्यथा यदि (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "unused");
    अन्यथा
        av_bprintf(bp, "user %d", channel_id);
}

पूर्णाङ्क av_channel_description(वर्ण *buf, माप_प्रकार buf_size, गणना AVChannel channel_id)
{
    AVBPrint bp;

    यदि (!buf && buf_size)
        प्रत्यागम AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_description_bprint(&bp, channel_id);

    यदि (bp.len >= पूर्णांक_उच्च)
        प्रत्यागम AVERROR(दुस्फल);
    प्रत्यागम bp.len + 1;
}

गणना AVChannel av_channel_from_string(ध्रुव वर्ण *str)
{
    पूर्णाङ्क i;
    वर्ण *endptr = (वर्ण *)str;
    गणना AVChannel id = AV_CHAN_NONE;

    यदि (!म_भेदन(str, "AMBI", 4)) {
        i = म_से_दीर्घ(str + 4, रिक्त, 0);
        यदि (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            प्रत्यागम AV_CHAN_NONE;
        प्रत्यागम AV_CHAN_AMBISONIC_BASE + i;
    }

    प्रति (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        यदि (channel_names[i].name && !म_भेद(str, channel_names[i].name))
            प्रत्यागम i;
    }
    यदि (!म_भेद(str, "UNK"))
        प्रत्यागम AV_CHAN_UNKNOWN;
    यदि (!म_भेद(str, "UNSD"))
        प्रत्यागम AV_CHAN_UNUSED;

    यदि (!म_भेदन(str, "USR", 3)) {
        ध्रुव वर्ण *p = str + 3;
        id = म_से_दीर्घ(p, &endptr, 0);
    }
    यदि (id >= 0 && !*endptr)
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

    यदि (nb_channels <= 0)
        प्रत्यागम AVERROR(EINVAL);

    map = av_calloc(nb_channels, परिमाण(*channel_layout->u.map));
    यदि (!map)
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
    यदि (!mask)
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

    यावत् (*str) {
        वर्ण *channel, *chname;
        ret = av_opt_get_कुंजी_मूल्य(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_कुंजी, &channel, &chname);
        यदि (ret < 0) {
            av_freep(&map);
            प्रत्यागम ret;
        }
        यदि (*str)
            str++; // skip separator
        यदि (!channel) {
            channel = chname;
            chname = रिक्त;
        }
        av_strlcpy(custom.name, chname ? chname : "", परिमाण(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        यदि (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            प्रत्यागम AVERROR(EINVAL);
        }

        av_dynarray2_add((शून्य **)&map, &nb_channels, परिमाण(custom), (शून्य *)&custom);
        यदि (!map)
            प्रत्यागम AVERROR(ENOMEM);
    }

    यदि (!nb_channels)
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
        यदि (channel_layout_map[i].name && !म_भेद(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            प्रत्यागम 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    स_रखो(channel_layout, 0, परिमाण(*channel_layout));

    /* ambisonic */
    यदि (!म_भेदन(str, "ambisonic ", 10)) {
        ध्रुव वर्ण *p = str + 10;
        वर्ण *endptr;
        AVChannelLayout extra = {0};
        पूर्णाङ्क order;

        order = म_से_दीर्घ(p, &endptr, 0);
        यदि (order < 0 || order + 1  > पूर्णांक_उच्च / (order + 1) ||
            (*endptr && *endptr != '+'))
            प्रत्यागम AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        यदि (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            यदि (ret < 0)
                प्रत्यागम ret;
            यदि (extra.nb_channels >= पूर्णांक_उच्च - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                प्रत्यागम AVERROR(EINVAL);
            }

            यदि (extra.order == AV_CHANNEL_ORDER_NATIVE) {
                channel_layout->u.mask = extra.u.mask;
            } अन्यथा {
                channel_layout->order = AV_CHANNEL_ORDER_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              परिमाण(*channel_layout->u.map));
                यदि (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    प्रत्यागम AVERROR(ENOMEM);
                }

                प्रति (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                प्रति (i = 0; i < extra.nb_channels; i++) {
                    गणना AVChannel ch = av_channel_layout_channel_from_index(&extra, i);
                    यदि (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        प्रत्यागम AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    यदि (extra.order == AV_CHANNEL_ORDER_CUSTOM &&
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
    यदि (!chlist)
        प्रत्यागम AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    यदि (ret < 0 && ret != AVERROR(EINVAL))
        प्रत्यागम ret;

    यदि (ret >= 0) {
        ध्रुव वर्ण *end_par = म_अक्षर(str, ')');
        यदि (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            प्रत्यागम AVERROR(EINVAL);
        }
        प्रत्यागम 0;
    }

    त्रुटि_सं = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    यदि (!त्रुटि_सं && !*end && !म_अक्षर(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        प्रत्यागम 0;
    }

    त्रुटि_सं = 0;
    channels = म_से_दीर्घ(str, &end, 10);

    /* number of channels */
    यदि (!त्रुटि_सं && !म_भेद(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        यदि (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            प्रत्यागम 0;
    }

    /* number of unordered channels */
    यदि (!त्रुटि_सं && (!म_भेद(end, "C") || !म_भेद(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        प्रत्यागम 0;
    }

    प्रत्यागम AVERROR(EINVAL);
}

शून्य av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    यदि (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    स_रखो(channel_layout, 0, परिमाण(*channel_layout));
}

पूर्णाङ्क av_channel_layout_copy(AVChannelLayout *dst, ध्रुव AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    यदि (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, परिमाण(*dst->u.map));
        यदि (!dst->u.map)
            प्रत्यागम AVERROR(ENOMEM);
        स_नकल(dst->u.map, src->u.map, src->nb_channels * परिमाण(*src->u.map));
    }
    प्रत्यागम 0;
}

स्थिर int64_t masked_description(ध्रुव AVChannelLayout *channel_layout, पूर्णाङ्क start_channel)
{
    uint64_t mask = 0;
    प्रति (पूर्णाङ्क i = start_channel; i < channel_layout->nb_channels; i++) {
        गणना AVChannel ch = channel_layout->u.map[i].id;
        यदि (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        अन्यथा
            प्रत्यागम AVERROR(EINVAL);
    }
    प्रत्यागम mask;
}

स्थिर पूर्णाङ्क has_channel_names(ध्रुव AVChannelLayout *channel_layout)
{
    यदि (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        प्रत्यागम 0;
    प्रति (पूर्णाङ्क i = 0; i < channel_layout->nb_channels; i++)
        यदि (channel_layout->u.map[i].name[0])
            प्रत्यागम 1;
    प्रत्यागम 0;
}

पूर्णाङ्क av_channel_layout_ambisonic_order(ध्रुव AVChannelLayout *channel_layout)
{
    पूर्णाङ्क i, highest_ambi, order;

    यदि (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        प्रत्यागम AVERROR(EINVAL);

    highest_ambi = -1;
    यदि (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    अन्यथा {
        ध्रुव AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        प्रति (i = 0; i < channel_layout->nb_channels; i++) {
            पूर्णाङ्क is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            यदि (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                प्रत्यागम AVERROR(EINVAL);

            /* non-default ordering */
            यदि (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                प्रत्यागम AVERROR(EINVAL);

            यदि (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    यदि (highest_ambi < 0)
        प्रत्यागम AVERROR(EINVAL);

    order = न्यूनमान(वर्ग_मूल(highest_ambi));
    /* incomplete order - some harmonics are missing */
    यदि ((order + 1) * (order + 1) != highest_ambi + 1)
        प्रत्यागम AVERROR(EINVAL);

    प्रत्यागम order;
}

स्थिर गणना AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    पूर्णाङ्क has_known_channel = 0;
    पूर्णाङ्क order;

    यदि (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        प्रत्यागम channel_layout->order;

    यदि (has_channel_names(channel_layout))
        प्रत्यागम AV_CHANNEL_ORDER_CUSTOM;

    प्रति (पूर्णाङ्क i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        यदि (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    यदि (!has_known_channel)
        प्रत्यागम AV_CHANNEL_ORDER_UNSPEC;

    यदि (masked_description(channel_layout, 0) > 0)
        प्रत्यागम AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    यदि (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
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
    यदि (order < 0)
        प्रत्यागम order;

    av_bprintf(bp, "ambisonic %d", order);

    /* extra channels present */
    nb_ambi_channels = (order + 1) * (order + 1);
    यदि (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        यदि (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC) {
            extra.order       = AV_CHANNEL_ORDER_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.mask);
            extra.u.mask      = channel_layout->u.mask;
        } अन्यथा {
            int64_t mask;
            यदि (!has_channel_names(channel_layout) &&
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

    प्रत्यागम 0;
}

पूर्णाङ्क av_channel_layout_describe_bprint(ध्रुव AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    पूर्णाङ्क i;

    विकल्प (channel_layout->order) {
    पक्ष AV_CHANNEL_ORDER_NATIVE:
        प्रति (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            यदि (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                प्रत्यागम 0;
            }
        av_fallthrough;
    पक्ष AV_CHANNEL_ORDER_CUSTOM:
        यदि (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            पूर्णाङ्क res = try_describe_ambisonic(bp, channel_layout);
            यदि (res >= 0)
                प्रत्यागम 0;
            यदि (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                प्रत्यागम av_channel_layout_describe_bprint(&native, bp);
            }
        }
        यदि (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        प्रति (i = 0; i < channel_layout->nb_channels; i++) {
            गणना AVChannel ch = av_channel_layout_channel_from_index(channel_layout, i);

            यदि (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            यदि (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        यदि (channel_layout->nb_channels) {
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
                               वर्ण *buf, माप_प्रकार buf_size)
{
    AVBPrint bp;
    पूर्णाङ्क ret;

    यदि (!buf && buf_size)
        प्रत्यागम AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    यदि (ret < 0)
        प्रत्यागम ret;

    यदि (bp.len >= पूर्णांक_उच्च)
        प्रत्यागम AVERROR(दुस्फल);
    प्रत्यागम bp.len + 1;
}

गणना AVChannel
av_channel_layout_channel_from_index(ध्रुव AVChannelLayout *channel_layout,
                                     अचिन्हित पूर्णाङ्क idx)
{
    पूर्णाङ्क i;

    यदि (idx >= channel_layout->nb_channels)
        प्रत्यागम AV_CHAN_NONE;

    विकल्प (channel_layout->order) {
    पक्ष AV_CHANNEL_ORDER_CUSTOM:
        प्रत्यागम channel_layout->u.map[idx].id;
    पक्ष AV_CHANNEL_ORDER_AMBISONIC: {
        पूर्णाङ्क ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        यदि (idx < ambi_channels)
            प्रत्यागम AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    पक्ष AV_CHANNEL_ORDER_NATIVE:
        प्रति (i = 0; i < 64; i++) {
            यदि ((1ULL << i) & channel_layout->u.mask && !idx--)
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

    यदि (index < 0)
        प्रत्यागम AV_CHAN_NONE;

    प्रत्यागम av_channel_layout_channel_from_index(channel_layout, index);
}

पूर्णाङ्क av_channel_layout_index_from_channel(ध्रुव AVChannelLayout *channel_layout,
                                         गणना AVChannel channel)
{
    पूर्णाङ्क i;

    यदि (channel == AV_CHAN_NONE)
        प्रत्यागम AVERROR(EINVAL);

    विकल्प (channel_layout->order) {
    पक्ष AV_CHANNEL_ORDER_CUSTOM:
        प्रति (i = 0; i < channel_layout->nb_channels; i++)
            यदि (channel_layout->u.map[i].id == channel)
                प्रत्यागम i;
        प्रत्यागम AVERROR(EINVAL);
    पक्ष AV_CHANNEL_ORDER_AMBISONIC:
    पक्ष AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        पूर्णाङ्क ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        यदि (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            यदि (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                प्रत्यागम AVERROR(EINVAL);
            प्रत्यागम channel - AV_CHAN_AMBISONIC_BASE;
        }
        यदि ((अचिन्हित)channel > 63 || !(mask & (1ULL << channel)))
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
        chname = म_माला(str, "@");
        यदि (chname) {
            वर्ण buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(परिमाण(buf), chname - str));
            यदि (!*chname)
                chname = रिक्त;
            ch = av_channel_from_string(buf);
            यदि (ch == AV_CHAN_NONE && *buf)
                प्रत्यागम AVERROR(EINVAL);
        }
        प्रति (पूर्णाङ्क i = 0; chname && i < channel_layout->nb_channels; i++) {
            यदि (!म_भेद(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                प्रत्यागम i;
        }
        av_fallthrough;
    पक्ष AV_CHANNEL_ORDER_AMBISONIC:
    पक्ष AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        यदि (ch == AV_CHAN_NONE)
            प्रत्यागम AVERROR(EINVAL);
        प्रत्यागम av_channel_layout_index_from_channel(channel_layout, ch);
    }

    प्रत्यागम AVERROR(EINVAL);
}

पूर्णाङ्क av_channel_layout_check(ध्रुव AVChannelLayout *channel_layout)
{
    यदि (channel_layout->nb_channels <= 0)
        प्रत्यागम 0;

    विकल्प (channel_layout->order) {
    पक्ष AV_CHANNEL_ORDER_NATIVE:
        प्रत्यागम av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    पक्ष AV_CHANNEL_ORDER_CUSTOM:
        यदि (!channel_layout->u.map)
            प्रत्यागम 0;
        प्रति (पूर्णाङ्क i = 0; i < channel_layout->nb_channels; i++) {
            यदि (channel_layout->u.map[i].id == AV_CHAN_NONE)
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
    यदि (chl->nb_channels != chl1->nb_channels)
        प्रत्यागम 1;

    /* if only one is unspecified -> not equal */
    यदि ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        प्रत्यागम 1;
    /* both are unspecified -> equal */
    अन्यथा यदि (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        प्रत्यागम 0;

    /* can compare masks directly */
    यदि ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        प्रत्यागम chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    प्रति (i = 0; i < chl->nb_channels; i++)
        यदि (av_channel_layout_channel_from_index(chl,  i) !=
            av_channel_layout_channel_from_index(chl1, i))
            प्रत्यागम 1;
    प्रत्यागम 0;
}

शून्य av_channel_layout_default(AVChannelLayout *ch_layout, पूर्णाङ्क nb_channels)
{
    पूर्णाङ्क i;
    प्रति (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        यदि (nb_channels == channel_layout_map[i].layout.nb_channels) {
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

    यदि (i < FF_ARRAY_ELEMS(channel_layout_map)) {
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
            यदि (mask & (1ULL << i) && av_channel_layout_index_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        भङ्ग;
    }

    प्रत्यागम ret;
}

पूर्णाङ्क av_channel_layout_retype(AVChannelLayout *channel_layout, गणना AVChannelOrder order, पूर्णाङ्क flags)
{
    पूर्णाङ्क allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    पूर्णाङ्क lossy;

    यदि (!av_channel_layout_check(channel_layout))
        प्रत्यागम AVERROR(EINVAL);

    यदि (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    यदि (channel_layout->order == order)
        प्रत्यागम 0;

    विकल्प (order) {
    पक्ष AV_CHANNEL_ORDER_UNSPEC: {
        पूर्णाङ्क nb_channels = channel_layout->nb_channels;
        यदि (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            प्रति (पूर्णाङ्क i = 0; i < nb_channels; i++) {
                यदि (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    भङ्ग;
                }
            }
        } अन्यथा {
            lossy = 1;
        }
        यदि (!lossy || allow_lossy) {
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
        यदि (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            यदि (mask < 0)
                प्रत्यागम AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            यदि (!lossy || allow_lossy) {
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
        यदि (ret < 0)
            प्रत्यागम ret;
        यदि (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            प्रति (पूर्णाङ्क i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_index(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        प्रत्यागम 0;
        }
    पक्ष AV_CHANNEL_ORDER_AMBISONIC:
        यदि (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            पूर्णाङ्क nb_channels = channel_layout->nb_channels;
            पूर्णाङ्क amb_order = av_channel_layout_ambisonic_order(channel_layout);
            यदि (amb_order < 0)
                प्रत्यागम AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            यदि (mask < 0)
                प्रत्यागम AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            यदि (!lossy || allow_lossy) {
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
