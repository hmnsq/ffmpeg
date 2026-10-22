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

#परिभाषय CHAN_IS_AMBI(x) ((x) >= AV_CHAN_AMBISONIC_आधारः &&\
                         (x) <= AV_CHAN_AMBISONIC_अन्तः)

संरचना channel_name {
    ध्रुव वर्ण *name;
    ध्रुव वर्ण *description;
};

स्थिर ध्रुव संरचना channel_name channel_नामानि[] = {
    [AV_CHAN_FRONT_वामः           ] = { "FL",        "front left"            },
    [AV_CHAN_FRONT_दक्षिणः          ] = { "FR",        "front right"           },
    [AV_CHAN_FRONT_CENTER         ] = { "FC",        "front center"          },
    [AV_CHAN_नीचः_FREQUENCY        ] = { "LFE",       "low frequency"         },
    [AV_CHAN_पृष्ठभागः_वामः            ] = { "BL",        "back left"             },
    [AV_CHAN_पृष्ठभागः_दक्षिणः           ] = { "BR",        "back right"            },
    [AV_CHAN_FRONT_वामः_सम्बन्धि_CENTER ] = { "FLC",       "front left-of-center"  },
    [AV_CHAN_FRONT_दक्षिणः_सम्बन्धि_CENTER] = { "FRC",       "front right-of-center" },
    [AV_CHAN_पृष्ठभागः_CENTER          ] = { "BC",        "back center"           },
    [AV_CHAN_SIDE_वामः            ] = { "SL",        "side left"             },
    [AV_CHAN_SIDE_दक्षिणः           ] = { "SR",        "side right"            },
    [AV_CHAN_शिखरम्_CENTER           ] = { "TC",        "top center"            },
    [AV_CHAN_शिखरम्_FRONT_वामः       ] = { "TFL",       "top front left"        },
    [AV_CHAN_शिखरम्_FRONT_CENTER     ] = { "TFC",       "top front center"      },
    [AV_CHAN_शिखरम्_FRONT_दक्षिणः      ] = { "TFR",       "top front right"       },
    [AV_CHAN_शिखरम्_पृष्ठभागः_वामः        ] = { "TBL",       "top back left"         },
    [AV_CHAN_शिखरम्_पृष्ठभागः_CENTER      ] = { "TBC",       "top back center"       },
    [AV_CHAN_शिखरम्_पृष्ठभागः_दक्षिणः       ] = { "TBR",       "top back right"        },
    [AV_CHAN_STEREO_वामः          ] = { "DL",        "downmix left"          },
    [AV_CHAN_STEREO_दक्षिणः         ] = { "DR",        "downmix right"         },
    [AV_CHAN_WIDE_वामः            ] = { "WL",        "wide left"             },
    [AV_CHAN_WIDE_दक्षिणः           ] = { "WR",        "wide right"            },
    [AV_CHAN_SURROUND_प्रत्यक्षम्_वामः ] = { "SDL",       "surround direct left"  },
    [AV_CHAN_SURROUND_प्रत्यक्षम्_दक्षिणः] = { "SDR",       "surround direct right" },
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
    यदि (channel_id >= AV_CHAN_AMBISONIC_आधारः &&
        channel_id <= AV_CHAN_AMBISONIC_अन्तः)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_आधारः);
    अन्यथा यदि ((अचिह्नित)channel_id < FF_ARRAY_ELEMS(channel_नामानि) &&
             channel_नामानि[channel_id].name)
        av_bprintf(bp, "%s", channel_नामानि[channel_id].name);
    अन्यथा यदि (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    अन्यथा यदि (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    अन्यथा यदि (channel_id == AV_CHAN_अप्रयुक्तम्)
        av_bprintf(bp, "UNSD");
    अन्यथा
        av_bprintf(bp, "USR%d", channel_id);
}

पूर्णाङ्क av_channel_name(वर्ण *buf, size_t buf_आकार, गणना AVChannel channel_id)
{
    AVBPrint bp;

    यदि (!buf && buf_आकार)
        प्रत्यागम AVERROR(EINVAL);

    av_bprint_init_for_बफर(&bp, buf, buf_आकार);
    av_channel_name_bprint(&bp, channel_id);

    यदि (bp.len >= अधिकतम_पूर्णाङ्कः)
        प्रत्यागम AVERROR(ERANGE);
    प्रत्यागम bp.len + 1;
}

शून्य av_channel_description_bprint(AVBPrint *bp, गणना AVChannel channel_id)
{
    यदि (channel_id >= AV_CHAN_AMBISONIC_आधारः &&
        channel_id <= AV_CHAN_AMBISONIC_अन्तः)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_आधारः);
    अन्यथा यदि ((अचिह्नित)channel_id < FF_ARRAY_ELEMS(channel_नामानि) &&
             channel_नामानि[channel_id].description)
        av_bprintf(bp, "%s", channel_नामानि[channel_id].description);
    अन्यथा यदि (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    अन्यथा यदि (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    अन्यथा यदि (channel_id == AV_CHAN_अप्रयुक्तम्)
        av_bprintf(bp, "unused");
    अन्यथा
        av_bprintf(bp, "user %d", channel_id);
}

पूर्णाङ्क av_channel_description(वर्ण *buf, size_t buf_आकार, गणना AVChannel channel_id)
{
    AVBPrint bp;

    यदि (!buf && buf_आकार)
        प्रत्यागम AVERROR(EINVAL);

    av_bprint_init_for_बफर(&bp, buf, buf_आकार);
    av_channel_description_bprint(&bp, channel_id);

    यदि (bp.len >= अधिकतम_पूर्णाङ्कः)
        प्रत्यागम AVERROR(ERANGE);
    प्रत्यागम bp.len + 1;
}

गणना AVChannel av_channel_from_string(ध्रुव वर्ण *str)
{
    पूर्णाङ्क i;
    वर्ण *endptr = (वर्ण *)str;
    गणना AVChannel id = AV_CHAN_NONE;

    यदि (!वाक्ये_तुलय(str, "AMBI", 4)) {
        i = strtol(str + 4, रिक्त, 0);
        यदि (i < 0 || i > AV_CHAN_AMBISONIC_अन्तः - AV_CHAN_AMBISONIC_आधारः)
            प्रत्यागम AV_CHAN_NONE;
        प्रत्यागम AV_CHAN_AMBISONIC_आधारः + i;
    }

    प्रति (i = 0; i < FF_ARRAY_ELEMS(channel_नामानि); i++) {
        यदि (channel_नामानि[i].name && !वाक्यं_तुलय(str, channel_नामानि[i].name))
            प्रत्यागम i;
    }
    यदि (!वाक्यं_तुलय(str, "UNK"))
        प्रत्यागम AV_CHAN_UNKNOWN;
    यदि (!वाक्यं_तुलय(str, "UNSD"))
        प्रत्यागम AV_CHAN_अप्रयुक्तम्;

    यदि (!वाक्ये_तुलय(str, "USR", 3)) {
        ध्रुव वर्ण *p = str + 3;
        id = strtol(p, &endptr, 0);
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
    { "5.0",            AV_CHANNEL_LAYOUT_5_POINT0_पृष्ठभागः        },
    { "5.0(side)",      AV_CHANNEL_LAYOUT_5POINT0             },
    { "4.1",            AV_CHANNEL_LAYOUT_4POINT1             },
    { "5.1",            AV_CHANNEL_LAYOUT_5_POINT1_पृष्ठभागः        },
    { "5.1(side)",      AV_CHANNEL_LAYOUT_5POINT1             },
    { "6.0",            AV_CHANNEL_LAYOUT_6POINT0             },
    { "6.0(front)",     AV_CHANNEL_LAYOUT_6POINT0_FRONT       },
    { "3.1.2",          AV_CHANNEL_LAYOUT_3POINT1POINT2       },
    { "hexagonal",      AV_CHANNEL_LAYOUT_HEXAGONAL           },
    { "6.1",            AV_CHANNEL_LAYOUT_6POINT1             },
    { "6.1(back)",      AV_CHANNEL_LAYOUT_6_POINT1_पृष्ठभागः        },
    { "6.1(front)",     AV_CHANNEL_LAYOUT_6POINT1_FRONT       },
    { "7.0",            AV_CHANNEL_LAYOUT_7POINT0             },
    { "7.0(front)",     AV_CHANNEL_LAYOUT_7POINT0_FRONT       },
    { "7.1",            AV_CHANNEL_LAYOUT_7POINT1             },
    { "7.1(wide)",      AV_CHANNEL_LAYOUT_7_POINT1_WIDE_पृष्ठभागः   },
    { "7.1(wide-side)", AV_CHANNEL_LAYOUT_7POINT1_WIDE        },
    { "5.1.2",          AV_CHANNEL_LAYOUT_5POINT1POINT2       },
    { "5.1.2(back)",    AV_CHANNEL_LAYOUT_5_POINT1_POINT2_पृष्ठभागः  },
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

    channel_layout->क्रमः       = AV_CHANNEL_क्रमः_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    प्रत्यागम 0;
}

पूर्णाङ्क av_channel_layout_from_आवरणम्(AVChannelLayout *channel_layout,
                                uint64_t आवरणम्_2)
{
    यदि (!आवरणम्_2)
        प्रत्यागम AVERROR(EINVAL);

    channel_layout->क्रमः       = AV_CHANNEL_क्रमः_NATIVE;
    channel_layout->nb_channels = av_popcount64(आवरणम्_2);
    channel_layout->u.आवरणम्_2      = आवरणम्_2;

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
        ret = av_opt_get_कुञ्चिका_मानम्(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_कुञ्चिका, &channel, &chname);
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

        av_dynarray2_सङ्कलय((शून्य **)&map, &nb_channels, परिमाण(custom), (शून्य *)&custom);
        यदि (!map)
            प्रत्यागम AVERROR(ENOMEM);
    }

    यदि (!nb_channels)
        प्रत्यागम AVERROR(EINVAL);

    ch_layout->क्रमः = AV_CHANNEL_क्रमः_CUSTOM;
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
    वर्ण *chlist, *अन्तः_2;
    uint64_t आवरणम्_2 = 0;

    /* channel layout names */
    प्रति (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        यदि (channel_layout_map[i].name && !वाक्यं_तुलय(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            प्रत्यागम 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    स्मृतिं_पूरय(channel_layout, 0, परिमाण(*channel_layout));

    /* ambisonic */
    यदि (!वाक्ये_तुलय(str, "ambisonic ", 10)) {
        ध्रुव वर्ण *p = str + 10;
        वर्ण *endptr;
        AVChannelLayout extra = {0};
        पूर्णाङ्क क्रमः;

        क्रमः = strtol(p, &endptr, 0);
        यदि (क्रमः < 0 || क्रमः + 1  > अधिकतम_पूर्णाङ्कः / (क्रमः + 1) ||
            (*endptr && *endptr != '+'))
            प्रत्यागम AVERROR(EINVAL);

        channel_layout->क्रमः       = AV_CHANNEL_क्रमः_AMBISONIC;
        channel_layout->nb_channels = (क्रमः + 1) * (क्रमः + 1);

        यदि (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            यदि (ret < 0)
                प्रत्यागम ret;
            यदि (extra.nb_channels >= अधिकतम_पूर्णाङ्कः - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                प्रत्यागम AVERROR(EINVAL);
            }

            यदि (extra.क्रमः == AV_CHANNEL_क्रमः_NATIVE) {
                channel_layout->u.आवरणम्_2 = extra.u.आवरणम्_2;
            } अन्यथा {
                channel_layout->क्रमः = AV_CHANNEL_क्रमः_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              परिमाण(*channel_layout->u.map));
                यदि (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    प्रत्यागम AVERROR(ENOMEM);
                }

                प्रति (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_आधारः + i;
                प्रति (i = 0; i < extra.nb_channels; i++) {
                    गणना AVChannel ch = av_channel_layout_channel_from_सूचकांक(&extra, i);
                    यदि (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        प्रत्यागम AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    यदि (extra.क्रमः == AV_CHANNEL_क्रमः_CUSTOM &&
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
        ध्रुव वर्ण *अन्तः_par = strchr(str, ')');
        यदि (matches == 2 && (nb_channels != channel_layout->nb_channels || !अन्तः_par || *++अन्तः_par)) {
            av_channel_layout_uninit(channel_layout);
            प्रत्यागम AVERROR(EINVAL);
        }
        प्रत्यागम 0;
    }

    errno = 0;
    आवरणम्_2 = strtoull(str, &अन्तः_2, 0);

    /* channel layout mask */
    यदि (!errno && !*अन्तः_2 && !strchr(str, '-') && आवरणम्_2) {
        av_channel_layout_from_आवरणम्(channel_layout, आवरणम्_2);
        प्रत्यागम 0;
    }

    errno = 0;
    channels = strtol(str, &अन्तः_2, 10);

    /* number of channels */
    यदि (!errno && !वाक्यं_तुलय(अन्तः_2, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        यदि (channel_layout->क्रमः == AV_CHANNEL_क्रमः_NATIVE)
            प्रत्यागम 0;
    }

    /* number of unordered channels */
    यदि (!errno && (!वाक्यं_तुलय(अन्तः_2, "C") || !वाक्यं_तुलय(अन्तः_2, " channels"))
        && channels > 0) {
        channel_layout->क्रमः = AV_CHANNEL_क्रमः_UNSPEC;
        channel_layout->nb_channels = channels;
        प्रत्यागम 0;
    }

    प्रत्यागम AVERROR(EINVAL);
}

शून्य av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    यदि (channel_layout->क्रमः == AV_CHANNEL_क्रमः_CUSTOM)
        av_freep(&channel_layout->u.map);
    स्मृतिं_पूरय(channel_layout, 0, परिमाण(*channel_layout));
}

पूर्णाङ्क av_channel_layout_copy(AVChannelLayout *dst, ध्रुव AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    यदि (src->क्रमः == AV_CHANNEL_क्रमः_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, परिमाण(*dst->u.map));
        यदि (!dst->u.map)
            प्रत्यागम AVERROR(ENOMEM);
        स्मृतिं_प्रतिलिख(dst->u.map, src->u.map, src->nb_channels * परिमाण(*src->u.map));
    }
    प्रत्यागम 0;
}

स्थिर int64_t masked_description(ध्रुव AVChannelLayout *channel_layout, पूर्णाङ्क start_channel)
{
    uint64_t आवरणम्_2 = 0;
    प्रति (पूर्णाङ्क i = start_channel; i < channel_layout->nb_channels; i++) {
        गणना AVChannel ch = channel_layout->u.map[i].id;
        यदि (ch >= 0 && ch < 63 && आवरणम्_2 < (1ULL << ch))
            आवरणम्_2 |= (1ULL << ch);
        अन्यथा
            प्रत्यागम AVERROR(EINVAL);
    }
    प्रत्यागम आवरणम्_2;
}

स्थिर पूर्णाङ्क has_channel_नामानि(ध्रुव AVChannelLayout *channel_layout)
{
    यदि (channel_layout->क्रमः != AV_CHANNEL_क्रमः_CUSTOM)
        प्रत्यागम 0;
    प्रति (पूर्णाङ्क i = 0; i < channel_layout->nb_channels; i++)
        यदि (channel_layout->u.map[i].name[0])
            प्रत्यागम 1;
    प्रत्यागम 0;
}

पूर्णाङ्क av_channel_layout_ambisonic_क्रमः(ध्रुव AVChannelLayout *channel_layout)
{
    पूर्णाङ्क i, highest_ambi, क्रमः;

    यदि (channel_layout->क्रमः != AV_CHANNEL_क्रमः_AMBISONIC &&
        channel_layout->क्रमः != AV_CHANNEL_क्रमः_CUSTOM)
        प्रत्यागम AVERROR(EINVAL);

    highest_ambi = -1;
    यदि (channel_layout->क्रमः == AV_CHANNEL_क्रमः_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.आवरणम्_2) - 1;
    अन्यथा {
        ध्रुव AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->क्रमः == AV_CHANNEL_क्रमः_CUSTOM);

        प्रति (i = 0; i < channel_layout->nb_channels; i++) {
            पूर्णाङ्क is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            यदि (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                प्रत्यागम AVERROR(EINVAL);

            /* non-default ordering */
            यदि (is_ambi && map[i].id - AV_CHAN_AMBISONIC_आधारः != i)
                प्रत्यागम AVERROR(EINVAL);

            यदि (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    यदि (highest_ambi < 0)
        प्रत्यागम AVERROR(EINVAL);

    क्रमः = floor(वर्गमूलम्(highest_ambi));
    /* incomplete order - some harmonics are missing */
    यदि ((क्रमः + 1) * (क्रमः + 1) != highest_ambi + 1)
        प्रत्यागम AVERROR(EINVAL);

    प्रत्यागम क्रमः;
}

स्थिर गणना AVChannel_क्रमः canonical_क्रमः(AVChannelLayout *channel_layout)
{
    पूर्णाङ्क has_ज्ञातम्_channel = 0;
    पूर्णाङ्क क्रमः;

    यदि (channel_layout->क्रमः != AV_CHANNEL_क्रमः_CUSTOM)
        प्रत्यागम channel_layout->क्रमः;

    यदि (has_channel_नामानि(channel_layout))
        प्रत्यागम AV_CHANNEL_क्रमः_CUSTOM;

    प्रति (पूर्णाङ्क i = 0; i < channel_layout->nb_channels && !has_ज्ञातम्_channel; i++)
        यदि (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_ज्ञातम्_channel = 1;
    यदि (!has_ज्ञातम्_channel)
        प्रत्यागम AV_CHANNEL_क्रमः_UNSPEC;

    यदि (masked_description(channel_layout, 0) > 0)
        प्रत्यागम AV_CHANNEL_क्रमः_NATIVE;

    क्रमः = av_channel_layout_ambisonic_क्रमः(channel_layout);
    यदि (क्रमः >= 0 && masked_description(channel_layout, (क्रमः + 1) * (क्रमः + 1)) >= 0)
        प्रत्यागम AV_CHANNEL_क्रमः_AMBISONIC;

    प्रत्यागम AV_CHANNEL_क्रमः_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
स्थिर पूर्णाङ्क try_describe_ambisonic(AVBPrint *bp, ध्रुव AVChannelLayout *channel_layout)
{
    पूर्णाङ्क nb_ambi_channels;
    पूर्णाङ्क क्रमः = av_channel_layout_ambisonic_क्रमः(channel_layout);
    यदि (क्रमः < 0)
        प्रत्यागम क्रमः;

    av_bprintf(bp, "ambisonic %d", क्रमः);

    /* extra channels present */
    nb_ambi_channels = (क्रमः + 1) * (क्रमः + 1);
    यदि (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        यदि (channel_layout->क्रमः == AV_CHANNEL_क्रमः_AMBISONIC) {
            extra.क्रमः       = AV_CHANNEL_क्रमः_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.आवरणम्_2);
            extra.u.आवरणम्_2      = channel_layout->u.आवरणम्_2;
        } अन्यथा {
            int64_t आवरणम्_2;
            यदि (!has_channel_नामानि(channel_layout) &&
                (आवरणम्_2 = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.क्रमः       = AV_CHANNEL_क्रमः_NATIVE;
                extra.nb_channels = av_popcount64(आवरणम्_2);
                extra.u.आवरणम्_2      = आवरणम्_2;
            } अन्यथा {
                extra.क्रमः       = AV_CHANNEL_क्रमः_CUSTOM;
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

    विकल्प (channel_layout->क्रमः) {
    पक्ष AV_CHANNEL_क्रमः_NATIVE:
        प्रति (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            यदि (channel_layout->u.आवरणम्_2 == channel_layout_map[i].layout.u.आवरणम्_2) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                प्रत्यागम 0;
            }
        av_fallthrough;
    पक्ष AV_CHANNEL_क्रमः_CUSTOM:
        यदि (channel_layout->क्रमः == AV_CHANNEL_क्रमः_CUSTOM) {
            int64_t आवरणम्_2;
            पूर्णाङ्क res = try_describe_ambisonic(bp, channel_layout);
            यदि (res >= 0)
                प्रत्यागम 0;
            यदि (!has_channel_नामानि(channel_layout) &&
                (आवरणम्_2 = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .क्रमः       = AV_CHANNEL_क्रमः_NATIVE,
                                           .nb_channels = av_popcount64(आवरणम्_2),
                                           .u.आवरणम्_2      = आवरणम्_2 };
                प्रत्यागम av_channel_layout_describe_bprint(&native, bp);
            }
        }
        यदि (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        प्रति (i = 0; i < channel_layout->nb_channels; i++) {
            गणना AVChannel ch = av_channel_layout_channel_from_सूचकांक(channel_layout, i);

            यदि (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            यदि (channel_layout->क्रमः == AV_CHANNEL_क्रमः_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        यदि (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            प्रत्यागम 0;
        }
        av_fallthrough;
    पक्ष AV_CHANNEL_क्रमः_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        प्रत्यागम 0;
    पक्ष AV_CHANNEL_क्रमः_AMBISONIC:
        प्रत्यागम try_describe_ambisonic(bp, channel_layout);
    स्वभाव:
        प्रत्यागम AVERROR(EINVAL);
    }
}

पूर्णाङ्क av_channel_layout_describe(ध्रुव AVChannelLayout *channel_layout,
                               वर्ण *buf, size_t buf_आकार)
{
    AVBPrint bp;
    पूर्णाङ्क ret;

    यदि (!buf && buf_आकार)
        प्रत्यागम AVERROR(EINVAL);

    av_bprint_init_for_बफर(&bp, buf, buf_आकार);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    यदि (ret < 0)
        प्रत्यागम ret;

    यदि (bp.len >= अधिकतम_पूर्णाङ्कः)
        प्रत्यागम AVERROR(ERANGE);
    प्रत्यागम bp.len + 1;
}

गणना AVChannel
av_channel_layout_channel_from_सूचकांक(ध्रुव AVChannelLayout *channel_layout,
                                     अचिह्नित पूर्णाङ्क idx)
{
    पूर्णाङ्क i;

    यदि (idx >= channel_layout->nb_channels)
        प्रत्यागम AV_CHAN_NONE;

    विकल्प (channel_layout->क्रमः) {
    पक्ष AV_CHANNEL_क्रमः_CUSTOM:
        प्रत्यागम channel_layout->u.map[idx].id;
    पक्ष AV_CHANNEL_क्रमः_AMBISONIC: {
        पूर्णाङ्क ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.आवरणम्_2);
        यदि (idx < ambi_channels)
            प्रत्यागम AV_CHAN_AMBISONIC_आधारः + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    पक्ष AV_CHANNEL_क्रमः_NATIVE:
        प्रति (i = 0; i < 64; i++) {
            यदि ((1ULL << i) & channel_layout->u.आवरणम्_2 && !idx--)
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
    पूर्णाङ्क सूचकांक = av_channel_layout_सूचकांक_from_string(channel_layout, str);

    यदि (सूचकांक < 0)
        प्रत्यागम AV_CHAN_NONE;

    प्रत्यागम av_channel_layout_channel_from_सूचकांक(channel_layout, सूचकांक);
}

पूर्णाङ्क av_channel_layout_सूचकांक_from_channel(ध्रुव AVChannelLayout *channel_layout,
                                         गणना AVChannel channel)
{
    पूर्णाङ्क i;

    यदि (channel == AV_CHAN_NONE)
        प्रत्यागम AVERROR(EINVAL);

    विकल्प (channel_layout->क्रमः) {
    पक्ष AV_CHANNEL_क्रमः_CUSTOM:
        प्रति (i = 0; i < channel_layout->nb_channels; i++)
            यदि (channel_layout->u.map[i].id == channel)
                प्रत्यागम i;
        प्रत्यागम AVERROR(EINVAL);
    पक्ष AV_CHANNEL_क्रमः_AMBISONIC:
    पक्ष AV_CHANNEL_क्रमः_NATIVE: {
        uint64_t आवरणम्_2 = channel_layout->u.आवरणम्_2;
        पूर्णाङ्क ambi_channels = channel_layout->nb_channels - av_popcount64(आवरणम्_2);
        यदि (channel_layout->क्रमः == AV_CHANNEL_क्रमः_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_आधारः) {
            यदि (channel - AV_CHAN_AMBISONIC_आधारः >= ambi_channels)
                प्रत्यागम AVERROR(EINVAL);
            प्रत्यागम channel - AV_CHAN_AMBISONIC_आधारः;
        }
        यदि ((अचिह्नित)channel > 63 || !(आवरणम्_2 & (1ULL << channel)))
            प्रत्यागम AVERROR(EINVAL);
        आवरणम्_2 &= (1ULL << channel) - 1;
        प्रत्यागम av_popcount64(आवरणम्_2) + ambi_channels;
        }
    स्वभाव:
        प्रत्यागम AVERROR(EINVAL);
    }
}

पूर्णाङ्क av_channel_layout_सूचकांक_from_string(ध्रुव AVChannelLayout *channel_layout,
                                        ध्रुव वर्ण *str)
{
    ध्रुव वर्ण *chname;
    गणना AVChannel ch = AV_CHAN_NONE;

    विकल्प (channel_layout->क्रमः) {
    पक्ष AV_CHANNEL_क्रमः_CUSTOM:
        chname = वाक्ये_अन्विष(str, "@");
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
            यदि (!वाक्यं_तुलय(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                प्रत्यागम i;
        }
        av_fallthrough;
    पक्ष AV_CHANNEL_क्रमः_AMBISONIC:
    पक्ष AV_CHANNEL_क्रमः_NATIVE:
        ch = av_channel_from_string(str);
        यदि (ch == AV_CHAN_NONE)
            प्रत्यागम AVERROR(EINVAL);
        प्रत्यागम av_channel_layout_सूचकांक_from_channel(channel_layout, ch);
    }

    प्रत्यागम AVERROR(EINVAL);
}

पूर्णाङ्क av_channel_layout_check(ध्रुव AVChannelLayout *channel_layout)
{
    यदि (channel_layout->nb_channels <= 0)
        प्रत्यागम 0;

    विकल्प (channel_layout->क्रमः) {
    पक्ष AV_CHANNEL_क्रमः_NATIVE:
        प्रत्यागम av_popcount64(channel_layout->u.आवरणम्_2) == channel_layout->nb_channels;
    पक्ष AV_CHANNEL_क्रमः_CUSTOM:
        यदि (!channel_layout->u.map)
            प्रत्यागम 0;
        प्रति (पूर्णाङ्क i = 0; i < channel_layout->nb_channels; i++) {
            यदि (channel_layout->u.map[i].id == AV_CHAN_NONE)
                प्रत्यागम 0;
        }
        प्रत्यागम 1;
    पक्ष AV_CHANNEL_क्रमः_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        प्रत्यागम av_popcount64(channel_layout->u.आवरणम्_2) < channel_layout->nb_channels;
    पक्ष AV_CHANNEL_क्रमः_UNSPEC:
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
    यदि ((chl->क्रमः  == AV_CHANNEL_क्रमः_UNSPEC) !=
        (chl1->क्रमः == AV_CHANNEL_क्रमः_UNSPEC))
        प्रत्यागम 1;
    /* both are unspecified -> equal */
    अन्यथा यदि (chl->क्रमः == AV_CHANNEL_क्रमः_UNSPEC)
        प्रत्यागम 0;

    /* can compare masks directly */
    यदि ((chl->क्रमः == AV_CHANNEL_क्रमः_NATIVE ||
         chl->क्रमः == AV_CHANNEL_क्रमः_AMBISONIC) &&
        chl->क्रमः == chl1->क्रमः)
        प्रत्यागम chl->u.आवरणम्_2 != chl1->u.आवरणम्_2;

    /* compare channel by channel */
    प्रति (i = 0; i < chl->nb_channels; i++)
        यदि (av_channel_layout_channel_from_सूचकांक(chl,  i) !=
            av_channel_layout_channel_from_सूचकांक(chl1, i))
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

    ch_layout->क्रमः       = AV_CHANNEL_क्रमः_UNSPEC;
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
                                  uint64_t आवरणम्_2)
{
    uint64_t ret = 0;
    पूर्णाङ्क i;

    विकल्प (channel_layout->क्रमः) {
    पक्ष AV_CHANNEL_क्रमः_NATIVE:
    पक्ष AV_CHANNEL_क्रमः_AMBISONIC:
        प्रत्यागम channel_layout->u.आवरणम्_2 & आवरणम्_2;
    पक्ष AV_CHANNEL_क्रमः_CUSTOM:
        प्रति (i = 0; i < 64; i++)
            यदि (आवरणम्_2 & (1ULL << i) && av_channel_layout_सूचकांक_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        भङ्ग;
    }

    प्रत्यागम ret;
}

पूर्णाङ्क av_channel_layout_retype(AVChannelLayout *channel_layout, गणना AVChannel_क्रमः क्रमः, पूर्णाङ्क flags)
{
    पूर्णाङ्क allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    पूर्णाङ्क lossy;

    यदि (!av_channel_layout_check(channel_layout))
        प्रत्यागम AVERROR(EINVAL);

    यदि (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        क्रमः = canonical_क्रमः(channel_layout);

    यदि (channel_layout->क्रमः == क्रमः)
        प्रत्यागम 0;

    विकल्प (क्रमः) {
    पक्ष AV_CHANNEL_क्रमः_UNSPEC: {
        पूर्णाङ्क nb_channels = channel_layout->nb_channels;
        यदि (channel_layout->क्रमः == AV_CHANNEL_क्रमः_CUSTOM) {
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
            channel_layout->क्रमः       = AV_CHANNEL_क्रमः_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            प्रत्यागम lossy;
        }
        प्रत्यागम AVERROR(ENOSYS);
        }
    पक्ष AV_CHANNEL_क्रमः_NATIVE:
        यदि (channel_layout->क्रमः == AV_CHANNEL_क्रमः_CUSTOM) {
            int64_t आवरणम्_2 = masked_description(channel_layout, 0);
            यदि (आवरणम्_2 < 0)
                प्रत्यागम AVERROR(ENOSYS);
            lossy = has_channel_नामानि(channel_layout);
            यदि (!lossy || allow_lossy) {
                शून्य *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_आवरणम्(channel_layout, आवरणम्_2);
                channel_layout->opaque = opaque;
                प्रत्यागम lossy;
            }
        }
        प्रत्यागम AVERROR(ENOSYS);
    पक्ष AV_CHANNEL_क्रमः_CUSTOM: {
        AVChannelLayout custom = { 0 };
        पूर्णाङ्क ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        शून्य *opaque = channel_layout->opaque;
        यदि (ret < 0)
            प्रत्यागम ret;
        यदि (channel_layout->क्रमः != AV_CHANNEL_क्रमः_UNSPEC)
            प्रति (पूर्णाङ्क i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_सूचकांक(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        प्रत्यागम 0;
        }
    पक्ष AV_CHANNEL_क्रमः_AMBISONIC:
        यदि (channel_layout->क्रमः == AV_CHANNEL_क्रमः_CUSTOM) {
            int64_t आवरणम्_2;
            पूर्णाङ्क nb_channels = channel_layout->nb_channels;
            पूर्णाङ्क amb_क्रमः = av_channel_layout_ambisonic_क्रमः(channel_layout);
            यदि (amb_क्रमः < 0)
                प्रत्यागम AVERROR(ENOSYS);
            आवरणम्_2 = masked_description(channel_layout, (amb_क्रमः + 1) * (amb_क्रमः + 1));
            यदि (आवरणम्_2 < 0)
                प्रत्यागम AVERROR(ENOSYS);
            lossy = has_channel_नामानि(channel_layout);
            यदि (!lossy || allow_lossy) {
                शून्य *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->क्रमः       = AV_CHANNEL_क्रमः_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.आवरणम्_2      = आवरणम्_2;
                channel_layout->opaque      = opaque;
                प्रत्यागम lossy;
            }
        }
        प्रत्यागम AVERROR(ENOSYS);
    स्वभाव:
        प्रत्यागम AVERROR(EINVAL);
    }
}
