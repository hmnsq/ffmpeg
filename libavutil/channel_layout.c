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

#समावेश <stdint.h>
#समावेश <stdlib.h>
#समावेश <string.h>

#समावेश "avassert.h"
#समावेश "channel_layout.h"
#समावेश "bprint.h"
#समावेश "common.h"
#समावेश "error.h"
#समावेश "attributes.h"
#समावेश "macros.h"
#समावेश "mem.h"
#समावेश "opt.h"

#घोषणा CHAN_IS_AMBI(x) ((x) >= AV_CHAN_AMBISONIC_BASE &&\
                         (x) <= AV_CHAN_AMBISONIC_END)

काष्ठा channel_name {
    स्थिर अक्षर *name;
    स्थिर अक्षर *description;
};

अटल स्थिर काष्ठा channel_name channel_names[] = {
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

व्योम av_channel_name_bprint(AVBPrint *bp, क्रमागत AVChannel channel_id)
{
    अगर (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_BASE);
    अन्यथा अगर ((अचिन्हित)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].name)
        av_bprintf(bp, "%s", channel_names[channel_id].name);
    अन्यथा अगर (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    अन्यथा अगर (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    अन्यथा अगर (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "UNSD");
    अन्यथा
        av_bprintf(bp, "USR%d", channel_id);
}

पूर्णांक av_channel_name(अक्षर *buf, माप_प्रकार buf_आकार, क्रमागत AVChannel channel_id)
{
    AVBPrint bp;

    अगर (!buf && buf_आकार)
        वापस AVERROR(EINVAL);

    av_bprint_init_for_बफर(&bp, buf, buf_आकार);
    av_channel_name_bprint(&bp, channel_id);

    अगर (bp.len >= पूर्णांक_उच्च)
        वापस AVERROR(दुस्फल);
    वापस bp.len + 1;
}

व्योम av_channel_description_bprint(AVBPrint *bp, क्रमागत AVChannel channel_id)
{
    अगर (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_BASE);
    अन्यथा अगर ((अचिन्हित)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].description)
        av_bprintf(bp, "%s", channel_names[channel_id].description);
    अन्यथा अगर (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    अन्यथा अगर (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    अन्यथा अगर (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "unused");
    अन्यथा
        av_bprintf(bp, "user %d", channel_id);
}

पूर्णांक av_channel_description(अक्षर *buf, माप_प्रकार buf_आकार, क्रमागत AVChannel channel_id)
{
    AVBPrint bp;

    अगर (!buf && buf_आकार)
        वापस AVERROR(EINVAL);

    av_bprint_init_for_बफर(&bp, buf, buf_आकार);
    av_channel_description_bprint(&bp, channel_id);

    अगर (bp.len >= पूर्णांक_उच्च)
        वापस AVERROR(दुस्फल);
    वापस bp.len + 1;
}

क्रमागत AVChannel av_channel_from_string(स्थिर अक्षर *str)
{
    पूर्णांक i;
    अक्षर *endptr = (अक्षर *)str;
    क्रमागत AVChannel id = AV_CHAN_NONE;

    अगर (!म_भेदन(str, "AMBI", 4)) {
        i = म_से_दीर्घ(str + 4, शून्य, 0);
        अगर (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            वापस AV_CHAN_NONE;
        वापस AV_CHAN_AMBISONIC_BASE + i;
    }

    क्रम (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        अगर (channel_names[i].name && !म_भेद(str, channel_names[i].name))
            वापस i;
    }
    अगर (!म_भेद(str, "UNK"))
        वापस AV_CHAN_UNKNOWN;
    अगर (!म_भेद(str, "UNSD"))
        वापस AV_CHAN_UNUSED;

    अगर (!म_भेदन(str, "USR", 3)) {
        स्थिर अक्षर *p = str + 3;
        id = म_से_दीर्घ(p, &endptr, 0);
    }
    अगर (id >= 0 && !*endptr)
        वापस id;

    वापस AV_CHAN_NONE;
}

काष्ठा channel_layout_name {
    स्थिर अक्षर *name;
    AVChannelLayout layout;
};

अटल स्थिर काष्ठा channel_layout_name channel_layout_map[] = {
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

    अगर (nb_channels <= 0)
        वापस AVERROR(EINVAL);

    map = av_calloc(nb_channels, माप(*channel_layout->u.map));
    अगर (!map)
        वापस AVERROR(ENOMEM);
    क्रम (पूर्णांक i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->order       = AV_CHANNEL_ORDER_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    वापस 0;
}

पूर्णांक av_channel_layout_from_mask(AVChannelLayout *channel_layout,
                                uint64_t mask)
{
    अगर (!mask)
        वापस AVERROR(EINVAL);

    channel_layout->order       = AV_CHANNEL_ORDER_NATIVE;
    channel_layout->nb_channels = av_popcount64(mask);
    channel_layout->u.mask      = mask;

    वापस 0;
}

अटल पूर्णांक parse_channel_list(AVChannelLayout *ch_layout, स्थिर अक्षर *str)
{
    पूर्णांक ret;
    पूर्णांक nb_channels = 0;
    AVChannelCustom *map = शून्य;
    AVChannelCustom custom = {0};

    जबतक (*str) {
        अक्षर *channel, *chname;
        ret = av_opt_get_कुंजी_मूल्य(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_कुंजी, &channel, &chname);
        अगर (ret < 0) {
            av_freep(&map);
            वापस ret;
        }
        अगर (*str)
            str++; // skip separator
        अगर (!channel) {
            channel = chname;
            chname = शून्य;
        }
        av_strlcpy(custom.name, chname ? chname : "", माप(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        अगर (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            वापस AVERROR(EINVAL);
        }

        av_dynarray2_add((व्योम **)&map, &nb_channels, माप(custom), (व्योम *)&custom);
        अगर (!map)
            वापस AVERROR(ENOMEM);
    }

    अगर (!nb_channels)
        वापस AVERROR(EINVAL);

    ch_layout->order = AV_CHANNEL_ORDER_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    वापस 0;
}

पूर्णांक av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  स्थिर अक्षर *str)
{
    पूर्णांक i, matches, ret;
    पूर्णांक channels = 0, nb_channels = 0;
    अक्षर *chlist, *end;
    uint64_t mask = 0;

    /* channel layout names */
    क्रम (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        अगर (channel_layout_map[i].name && !म_भेद(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            वापस 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    स_रखो(channel_layout, 0, माप(*channel_layout));

    /* ambisonic */
    अगर (!म_भेदन(str, "ambisonic ", 10)) {
        स्थिर अक्षर *p = str + 10;
        अक्षर *endptr;
        AVChannelLayout extra = {0};
        पूर्णांक order;

        order = म_से_दीर्घ(p, &endptr, 0);
        अगर (order < 0 || order + 1  > पूर्णांक_उच्च / (order + 1) ||
            (*endptr && *endptr != '+'))
            वापस AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        अगर (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            अगर (ret < 0)
                वापस ret;
            अगर (extra.nb_channels >= पूर्णांक_उच्च - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                वापस AVERROR(EINVAL);
            }

            अगर (extra.order == AV_CHANNEL_ORDER_NATIVE) {
                channel_layout->u.mask = extra.u.mask;
            } अन्यथा {
                channel_layout->order = AV_CHANNEL_ORDER_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              माप(*channel_layout->u.map));
                अगर (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    वापस AVERROR(ENOMEM);
                }

                क्रम (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                क्रम (i = 0; i < extra.nb_channels; i++) {
                    क्रमागत AVChannel ch = av_channel_layout_channel_from_सूचकांक(&extra, i);
                    अगर (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        वापस AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    अगर (extra.order == AV_CHANNEL_ORDER_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   माप(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        वापस 0;
    }

    chlist = av_strdup(str);
    अगर (!chlist)
        वापस AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    अगर (ret < 0 && ret != AVERROR(EINVAL))
        वापस ret;

    अगर (ret >= 0) {
        स्थिर अक्षर *end_par = म_अक्षर(str, ')');
        अगर (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            वापस AVERROR(EINVAL);
        }
        वापस 0;
    }

    त्रुटि_सं = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    अगर (!त्रुटि_सं && !*end && !म_अक्षर(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        वापस 0;
    }

    त्रुटि_सं = 0;
    channels = म_से_दीर्घ(str, &end, 10);

    /* number of channels */
    अगर (!त्रुटि_सं && !म_भेद(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        अगर (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            वापस 0;
    }

    /* number of unordered channels */
    अगर (!त्रुटि_सं && (!म_भेद(end, "C") || !म_भेद(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        वापस 0;
    }

    वापस AVERROR(EINVAL);
}

व्योम av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    अगर (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    स_रखो(channel_layout, 0, माप(*channel_layout));
}

पूर्णांक av_channel_layout_copy(AVChannelLayout *dst, स्थिर AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    अगर (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, माप(*dst->u.map));
        अगर (!dst->u.map)
            वापस AVERROR(ENOMEM);
        स_नकल(dst->u.map, src->u.map, src->nb_channels * माप(*src->u.map));
    }
    वापस 0;
}

अटल int64_t masked_description(स्थिर AVChannelLayout *channel_layout, पूर्णांक start_channel)
{
    uint64_t mask = 0;
    क्रम (पूर्णांक i = start_channel; i < channel_layout->nb_channels; i++) {
        क्रमागत AVChannel ch = channel_layout->u.map[i].id;
        अगर (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        अन्यथा
            वापस AVERROR(EINVAL);
    }
    वापस mask;
}

अटल पूर्णांक has_channel_names(स्थिर AVChannelLayout *channel_layout)
{
    अगर (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        वापस 0;
    क्रम (पूर्णांक i = 0; i < channel_layout->nb_channels; i++)
        अगर (channel_layout->u.map[i].name[0])
            वापस 1;
    वापस 0;
}

पूर्णांक av_channel_layout_ambisonic_order(स्थिर AVChannelLayout *channel_layout)
{
    पूर्णांक i, highest_ambi, order;

    अगर (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        वापस AVERROR(EINVAL);

    highest_ambi = -1;
    अगर (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    अन्यथा {
        स्थिर AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        क्रम (i = 0; i < channel_layout->nb_channels; i++) {
            पूर्णांक is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            अगर (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                वापस AVERROR(EINVAL);

            /* non-default ordering */
            अगर (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                वापस AVERROR(EINVAL);

            अगर (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    अगर (highest_ambi < 0)
        वापस AVERROR(EINVAL);

    order = न्यूनमान(वर्ग_मूल(highest_ambi));
    /* incomplete order - some harmonics are missing */
    अगर ((order + 1) * (order + 1) != highest_ambi + 1)
        वापस AVERROR(EINVAL);

    वापस order;
}

अटल क्रमागत AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    पूर्णांक has_known_channel = 0;
    पूर्णांक order;

    अगर (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        वापस channel_layout->order;

    अगर (has_channel_names(channel_layout))
        वापस AV_CHANNEL_ORDER_CUSTOM;

    क्रम (पूर्णांक i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        अगर (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    अगर (!has_known_channel)
        वापस AV_CHANNEL_ORDER_UNSPEC;

    अगर (masked_description(channel_layout, 0) > 0)
        वापस AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    अगर (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
        वापस AV_CHANNEL_ORDER_AMBISONIC;

    वापस AV_CHANNEL_ORDER_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
अटल पूर्णांक try_describe_ambisonic(AVBPrint *bp, स्थिर AVChannelLayout *channel_layout)
{
    पूर्णांक nb_ambi_channels;
    पूर्णांक order = av_channel_layout_ambisonic_order(channel_layout);
    अगर (order < 0)
        वापस order;

    av_bprintf(bp, "ambisonic %d", order);

    /* extra channels present */
    nb_ambi_channels = (order + 1) * (order + 1);
    अगर (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        अगर (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC) {
            extra.order       = AV_CHANNEL_ORDER_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.mask);
            extra.u.mask      = channel_layout->u.mask;
        } अन्यथा {
            int64_t mask;
            अगर (!has_channel_names(channel_layout) &&
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

    वापस 0;
}

पूर्णांक av_channel_layout_describe_bprint(स्थिर AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    पूर्णांक i;

    चयन (channel_layout->order) {
    हाल AV_CHANNEL_ORDER_NATIVE:
        क्रम (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            अगर (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                वापस 0;
            }
        av_fallthrough;
    हाल AV_CHANNEL_ORDER_CUSTOM:
        अगर (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            पूर्णांक res = try_describe_ambisonic(bp, channel_layout);
            अगर (res >= 0)
                वापस 0;
            अगर (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                वापस av_channel_layout_describe_bprint(&native, bp);
            }
        }
        अगर (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        क्रम (i = 0; i < channel_layout->nb_channels; i++) {
            क्रमागत AVChannel ch = av_channel_layout_channel_from_सूचकांक(channel_layout, i);

            अगर (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            अगर (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        अगर (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            वापस 0;
        }
        av_fallthrough;
    हाल AV_CHANNEL_ORDER_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        वापस 0;
    हाल AV_CHANNEL_ORDER_AMBISONIC:
        वापस try_describe_ambisonic(bp, channel_layout);
    शेष:
        वापस AVERROR(EINVAL);
    }
}

पूर्णांक av_channel_layout_describe(स्थिर AVChannelLayout *channel_layout,
                               अक्षर *buf, माप_प्रकार buf_आकार)
{
    AVBPrint bp;
    पूर्णांक ret;

    अगर (!buf && buf_आकार)
        वापस AVERROR(EINVAL);

    av_bprint_init_for_बफर(&bp, buf, buf_आकार);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    अगर (ret < 0)
        वापस ret;

    अगर (bp.len >= पूर्णांक_उच्च)
        वापस AVERROR(दुस्फल);
    वापस bp.len + 1;
}

क्रमागत AVChannel
av_channel_layout_channel_from_सूचकांक(स्थिर AVChannelLayout *channel_layout,
                                     अचिन्हित पूर्णांक idx)
{
    पूर्णांक i;

    अगर (idx >= channel_layout->nb_channels)
        वापस AV_CHAN_NONE;

    चयन (channel_layout->order) {
    हाल AV_CHANNEL_ORDER_CUSTOM:
        वापस channel_layout->u.map[idx].id;
    हाल AV_CHANNEL_ORDER_AMBISONIC: {
        पूर्णांक ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        अगर (idx < ambi_channels)
            वापस AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    हाल AV_CHANNEL_ORDER_NATIVE:
        क्रम (i = 0; i < 64; i++) {
            अगर ((1ULL << i) & channel_layout->u.mask && !idx--)
                वापस i;
        }
        av_fallthrough;
    शेष:
        वापस AV_CHAN_NONE;
    }
}

क्रमागत AVChannel
av_channel_layout_channel_from_string(स्थिर AVChannelLayout *channel_layout,
                                      स्थिर अक्षर *str)
{
    पूर्णांक सूचकांक = av_channel_layout_सूचकांक_from_string(channel_layout, str);

    अगर (सूचकांक < 0)
        वापस AV_CHAN_NONE;

    वापस av_channel_layout_channel_from_सूचकांक(channel_layout, सूचकांक);
}

पूर्णांक av_channel_layout_सूचकांक_from_channel(स्थिर AVChannelLayout *channel_layout,
                                         क्रमागत AVChannel channel)
{
    पूर्णांक i;

    अगर (channel == AV_CHAN_NONE)
        वापस AVERROR(EINVAL);

    चयन (channel_layout->order) {
    हाल AV_CHANNEL_ORDER_CUSTOM:
        क्रम (i = 0; i < channel_layout->nb_channels; i++)
            अगर (channel_layout->u.map[i].id == channel)
                वापस i;
        वापस AVERROR(EINVAL);
    हाल AV_CHANNEL_ORDER_AMBISONIC:
    हाल AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        पूर्णांक ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        अगर (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            अगर (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                वापस AVERROR(EINVAL);
            वापस channel - AV_CHAN_AMBISONIC_BASE;
        }
        अगर ((अचिन्हित)channel > 63 || !(mask & (1ULL << channel)))
            वापस AVERROR(EINVAL);
        mask &= (1ULL << channel) - 1;
        वापस av_popcount64(mask) + ambi_channels;
        }
    शेष:
        वापस AVERROR(EINVAL);
    }
}

पूर्णांक av_channel_layout_सूचकांक_from_string(स्थिर AVChannelLayout *channel_layout,
                                        स्थिर अक्षर *str)
{
    स्थिर अक्षर *chname;
    क्रमागत AVChannel ch = AV_CHAN_NONE;

    चयन (channel_layout->order) {
    हाल AV_CHANNEL_ORDER_CUSTOM:
        chname = म_माला(str, "@");
        अगर (chname) {
            अक्षर buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(माप(buf), chname - str));
            अगर (!*chname)
                chname = शून्य;
            ch = av_channel_from_string(buf);
            अगर (ch == AV_CHAN_NONE && *buf)
                वापस AVERROR(EINVAL);
        }
        क्रम (पूर्णांक i = 0; chname && i < channel_layout->nb_channels; i++) {
            अगर (!म_भेद(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                वापस i;
        }
        av_fallthrough;
    हाल AV_CHANNEL_ORDER_AMBISONIC:
    हाल AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        अगर (ch == AV_CHAN_NONE)
            वापस AVERROR(EINVAL);
        वापस av_channel_layout_सूचकांक_from_channel(channel_layout, ch);
    }

    वापस AVERROR(EINVAL);
}

पूर्णांक av_channel_layout_check(स्थिर AVChannelLayout *channel_layout)
{
    अगर (channel_layout->nb_channels <= 0)
        वापस 0;

    चयन (channel_layout->order) {
    हाल AV_CHANNEL_ORDER_NATIVE:
        वापस av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    हाल AV_CHANNEL_ORDER_CUSTOM:
        अगर (!channel_layout->u.map)
            वापस 0;
        क्रम (पूर्णांक i = 0; i < channel_layout->nb_channels; i++) {
            अगर (channel_layout->u.map[i].id == AV_CHAN_NONE)
                वापस 0;
        }
        वापस 1;
    हाल AV_CHANNEL_ORDER_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        वापस av_popcount64(channel_layout->u.mask) < channel_layout->nb_channels;
    हाल AV_CHANNEL_ORDER_UNSPEC:
        वापस 1;
    शेष:
        वापस 0;
    }
}

पूर्णांक av_channel_layout_compare(स्थिर AVChannelLayout *chl, स्थिर AVChannelLayout *chl1)
{
    पूर्णांक i;

    /* different channel counts -> not equal */
    अगर (chl->nb_channels != chl1->nb_channels)
        वापस 1;

    /* if only one is unspecified -> not equal */
    अगर ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        वापस 1;
    /* both are unspecified -> equal */
    अन्यथा अगर (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        वापस 0;

    /* can compare masks directly */
    अगर ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        वापस chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    क्रम (i = 0; i < chl->nb_channels; i++)
        अगर (av_channel_layout_channel_from_सूचकांक(chl,  i) !=
            av_channel_layout_channel_from_सूचकांक(chl1, i))
            वापस 1;
    वापस 0;
}

व्योम av_channel_layout_default(AVChannelLayout *ch_layout, पूर्णांक nb_channels)
{
    पूर्णांक i;
    क्रम (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        अगर (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            वापस;
        }

    ch_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

स्थिर AVChannelLayout *av_channel_layout_standard(व्योम **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    स्थिर AVChannelLayout *ch_layout = शून्य;

    अगर (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (व्योम*)(i + 1);
    }

    वापस ch_layout;
}

uint64_t av_channel_layout_subset(स्थिर AVChannelLayout *channel_layout,
                                  uint64_t mask)
{
    uint64_t ret = 0;
    पूर्णांक i;

    चयन (channel_layout->order) {
    हाल AV_CHANNEL_ORDER_NATIVE:
    हाल AV_CHANNEL_ORDER_AMBISONIC:
        वापस channel_layout->u.mask & mask;
    हाल AV_CHANNEL_ORDER_CUSTOM:
        क्रम (i = 0; i < 64; i++)
            अगर (mask & (1ULL << i) && av_channel_layout_सूचकांक_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        अवरोध;
    }

    वापस ret;
}

पूर्णांक av_channel_layout_retype(AVChannelLayout *channel_layout, क्रमागत AVChannelOrder order, पूर्णांक flags)
{
    पूर्णांक allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    पूर्णांक lossy;

    अगर (!av_channel_layout_check(channel_layout))
        वापस AVERROR(EINVAL);

    अगर (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    अगर (channel_layout->order == order)
        वापस 0;

    चयन (order) {
    हाल AV_CHANNEL_ORDER_UNSPEC: {
        पूर्णांक nb_channels = channel_layout->nb_channels;
        अगर (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            क्रम (पूर्णांक i = 0; i < nb_channels; i++) {
                अगर (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    अवरोध;
                }
            }
        } अन्यथा {
            lossy = 1;
        }
        अगर (!lossy || allow_lossy) {
            व्योम *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            वापस lossy;
        }
        वापस AVERROR(ENOSYS);
        }
    हाल AV_CHANNEL_ORDER_NATIVE:
        अगर (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            अगर (mask < 0)
                वापस AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            अगर (!lossy || allow_lossy) {
                व्योम *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_mask(channel_layout, mask);
                channel_layout->opaque = opaque;
                वापस lossy;
            }
        }
        वापस AVERROR(ENOSYS);
    हाल AV_CHANNEL_ORDER_CUSTOM: {
        AVChannelLayout custom = { 0 };
        पूर्णांक ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        व्योम *opaque = channel_layout->opaque;
        अगर (ret < 0)
            वापस ret;
        अगर (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            क्रम (पूर्णांक i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_सूचकांक(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        वापस 0;
        }
    हाल AV_CHANNEL_ORDER_AMBISONIC:
        अगर (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            पूर्णांक nb_channels = channel_layout->nb_channels;
            पूर्णांक amb_order = av_channel_layout_ambisonic_order(channel_layout);
            अगर (amb_order < 0)
                वापस AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            अगर (mask < 0)
                वापस AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            अगर (!lossy || allow_lossy) {
                व्योम *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.mask      = mask;
                channel_layout->opaque      = opaque;
                वापस lossy;
            }
        }
        वापस AVERROR(ENOSYS);
    शेष:
        वापस AVERROR(EINVAL);
    }
}
