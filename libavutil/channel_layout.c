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

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "channel_layout.h"
#అన్తర్భావ "bprint.h"
#అన్తర్భావ "common.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "attributes.h"
#అన్తర్భావ "macros.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "opt.h"

#నిర్వచించు CHAN_IS_AMBI(x) ((x) >= AV_CHAN_AMBISONIC_పునాది &&\
                         (x) <= AV_CHAN_AMBISONIC_చివర)

నిర్మాణం channel_name {
    స్థిరరాశి అక్షరం *name;
    స్థిరరాశి అక్షరం *description;
};

స్థిర స్థిరరాశి నిర్మాణం channel_name channel_పేర్లు[] = {
    [AV_CHAN_FRONT_ఎడమ           ] = { "FL",        "front left"            },
    [AV_CHAN_FRONT_కుడి          ] = { "FR",        "front right"           },
    [AV_CHAN_FRONT_CENTER         ] = { "FC",        "front center"          },
    [AV_CHAN_దిగువ_FREQUENCY        ] = { "LFE",       "low frequency"         },
    [AV_CHAN_వెనుక_ఎడమ            ] = { "BL",        "back left"             },
    [AV_CHAN_వెనుక_కుడి           ] = { "BR",        "back right"            },
    [AV_CHAN_FRONT_ఎడమ_యొక్క_CENTER ] = { "FLC",       "front left-of-center"  },
    [AV_CHAN_FRONT_కుడి_యొక్క_CENTER] = { "FRC",       "front right-of-center" },
    [AV_CHAN_వెనుక_CENTER          ] = { "BC",        "back center"           },
    [AV_CHAN_SIDE_ఎడమ            ] = { "SL",        "side left"             },
    [AV_CHAN_SIDE_కుడి           ] = { "SR",        "side right"            },
    [AV_CHAN_శిఖరం_CENTER           ] = { "TC",        "top center"            },
    [AV_CHAN_శిఖరం_FRONT_ఎడమ       ] = { "TFL",       "top front left"        },
    [AV_CHAN_శిఖరం_FRONT_CENTER     ] = { "TFC",       "top front center"      },
    [AV_CHAN_శిఖరం_FRONT_కుడి      ] = { "TFR",       "top front right"       },
    [AV_CHAN_శిఖరం_వెనుక_ఎడమ        ] = { "TBL",       "top back left"         },
    [AV_CHAN_శిఖరం_వెనుక_CENTER      ] = { "TBC",       "top back center"       },
    [AV_CHAN_శిఖరం_వెనుక_కుడి       ] = { "TBR",       "top back right"        },
    [AV_CHAN_STEREO_ఎడమ          ] = { "DL",        "downmix left"          },
    [AV_CHAN_STEREO_కుడి         ] = { "DR",        "downmix right"         },
    [AV_CHAN_WIDE_ఎడమ            ] = { "WL",        "wide left"             },
    [AV_CHAN_WIDE_కుడి           ] = { "WR",        "wide right"            },
    [AV_CHAN_SURROUND_ప్రత్యక్ష_ఎడమ ] = { "SDL",       "surround direct left"  },
    [AV_CHAN_SURROUND_ప్రత్యక్ష_కుడి] = { "SDR",       "surround direct right" },
    [AV_CHAN_దిగువ_FREQUENCY_2      ] = { "LFE2",      "low frequency 2"       },
    [AV_CHAN_శిఖరం_SIDE_ఎడమ        ] = { "TSL",       "top side left"         },
    [AV_CHAN_శిఖరం_SIDE_కుడి       ] = { "TSR",       "top side right"        },
    [AV_CHAN_BOTTOM_FRONT_CENTER  ] = { "BFC",       "bottom front center"   },
    [AV_CHAN_BOTTOM_FRONT_ఎడమ    ] = { "BFL",       "bottom front left"     },
    [AV_CHAN_BOTTOM_FRONT_కుడి   ] = { "BFR",       "bottom front right"    },
    [AV_CHAN_SIDE_SURROUND_ఎడమ   ] = { "SSL",       "side surround left"    },
    [AV_CHAN_SIDE_SURROUND_కుడి  ] = { "SSR",       "side surround right"   },
    [AV_CHAN_శిఖరం_SURROUND_ఎడమ    ] = { "TTL",       "top surround left"     },
    [AV_CHAN_శిఖరం_SURROUND_కుడి   ] = { "TTR",       "top surround right"    },
    [AV_CHAN_BINAURAL_ఎడమ        ] = { "BIL",       "binaural left"         },
    [AV_CHAN_BINAURAL_కుడి       ] = { "BIR",       "binaural right"        },
};

శూన్య av_channel_name_bprint(AVBPrint *bp, గణన AVChannel channel_id)
{
    ఒకవేళ (channel_id >= AV_CHAN_AMBISONIC_పునాది &&
        channel_id <= AV_CHAN_AMBISONIC_చివర)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_పునాది);
    లేకపోతే ఒకవేళ ((గుర్తులేని)channel_id < FF_ARRAY_ELEMS(channel_పేర్లు) &&
             channel_పేర్లు[channel_id].name)
        av_bprintf(bp, "%s", channel_పేర్లు[channel_id].name);
    లేకపోతే ఒకవేళ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    లేకపోతే ఒకవేళ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    లేకపోతే ఒకవేళ (channel_id == AV_CHAN_వాడని)
        av_bprintf(bp, "UNSD");
    లేకపోతే
        av_bprintf(bp, "USR%d", channel_id);
}

పూర్ణాంకం av_channel_name(అక్షరం *buf, size_t buf_కొలత, గణన AVChannel channel_id)
{
    AVBPrint bp;

    ఒకవేళ (!buf && buf_కొలత)
        తిరిగి AVERROR(EINVAL);

    av_bprint_init_for_బఫరు(&bp, buf, buf_కొలత);
    av_channel_name_bprint(&bp, channel_id);

    ఒకవేళ (bp.len >= గరిష్ఠ_పూర్ణాంకం)
        తిరిగి AVERROR(ERANGE);
    తిరిగి bp.len + 1;
}

శూన్య av_channel_description_bprint(AVBPrint *bp, గణన AVChannel channel_id)
{
    ఒకవేళ (channel_id >= AV_CHAN_AMBISONIC_పునాది &&
        channel_id <= AV_CHAN_AMBISONIC_చివర)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_పునాది);
    లేకపోతే ఒకవేళ ((గుర్తులేని)channel_id < FF_ARRAY_ELEMS(channel_పేర్లు) &&
             channel_పేర్లు[channel_id].description)
        av_bprintf(bp, "%s", channel_పేర్లు[channel_id].description);
    లేకపోతే ఒకవేళ (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    లేకపోతే ఒకవేళ (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    లేకపోతే ఒకవేళ (channel_id == AV_CHAN_వాడని)
        av_bprintf(bp, "unused");
    లేకపోతే
        av_bprintf(bp, "user %d", channel_id);
}

పూర్ణాంకం av_channel_description(అక్షరం *buf, size_t buf_కొలత, గణన AVChannel channel_id)
{
    AVBPrint bp;

    ఒకవేళ (!buf && buf_కొలత)
        తిరిగి AVERROR(EINVAL);

    av_bprint_init_for_బఫరు(&bp, buf, buf_కొలత);
    av_channel_description_bprint(&bp, channel_id);

    ఒకవేళ (bp.len >= గరిష్ఠ_పూర్ణాంకం)
        తిరిగి AVERROR(ERANGE);
    తిరిగి bp.len + 1;
}

గణన AVChannel av_channel_from_string(స్థిరరాశి అక్షరం *str)
{
    పూర్ణాంకం i;
    అక్షరం *endptr = (అక్షరం *)str;
    గణన AVChannel id = AV_CHAN_NONE;

    ఒకవేళ (!అక్షరశ్రేణి_పోలిక(str, "AMBI", 4)) {
        i = strtol(str + 4, ఖాళీ, 0);
        ఒకవేళ (i < 0 || i > AV_CHAN_AMBISONIC_చివర - AV_CHAN_AMBISONIC_పునాది)
            తిరిగి AV_CHAN_NONE;
        తిరిగి AV_CHAN_AMBISONIC_పునాది + i;
    }

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(channel_పేర్లు); i++) {
        ఒకవేళ (channel_పేర్లు[i].name && !strcmp(str, channel_పేర్లు[i].name))
            తిరిగి i;
    }
    ఒకవేళ (!strcmp(str, "UNK"))
        తిరిగి AV_CHAN_UNKNOWN;
    ఒకవేళ (!strcmp(str, "UNSD"))
        తిరిగి AV_CHAN_వాడని;

    ఒకవేళ (!అక్షరశ్రేణి_పోలిక(str, "USR", 3)) {
        స్థిరరాశి అక్షరం *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    ఒకవేళ (id >= 0 && !*endptr)
        తిరిగి id;

    తిరిగి AV_CHAN_NONE;
}

నిర్మాణం channel_layout_name {
    స్థిరరాశి అక్షరం *name;
    AVChannelLayout layout;
};

స్థిర స్థిరరాశి నిర్మాణం channel_layout_name channel_layout_map[] = {
    { "mono",           AV_CHANNEL_LAYOUT_MONO                },
    { "stereo",         AV_CHANNEL_LAYOUT_STEREO              },
    { "2.1",            AV_CHANNEL_LAYOUT_2POINT1             },
    { "3.0",            AV_CHANNEL_LAYOUT_SURROUND            },
    { "3.0(back)",      AV_CHANNEL_LAYOUT_2_1                 },
    { "4.0",            AV_CHANNEL_LAYOUT_4POINT0             },
    { "quad",           AV_CHANNEL_LAYOUT_QUAD                },
    { "quad(side)",     AV_CHANNEL_LAYOUT_2_2                 },
    { "3.1",            AV_CHANNEL_LAYOUT_3POINT1             },
    { "5.0",            AV_CHANNEL_LAYOUT_5_POINT0_వెనుక        },
    { "5.0(side)",      AV_CHANNEL_LAYOUT_5POINT0             },
    { "4.1",            AV_CHANNEL_LAYOUT_4POINT1             },
    { "5.1",            AV_CHANNEL_LAYOUT_5_POINT1_వెనుక        },
    { "5.1(side)",      AV_CHANNEL_LAYOUT_5POINT1             },
    { "6.0",            AV_CHANNEL_LAYOUT_6POINT0             },
    { "6.0(front)",     AV_CHANNEL_LAYOUT_6POINT0_FRONT       },
    { "3.1.2",          AV_CHANNEL_LAYOUT_3POINT1POINT2       },
    { "hexagonal",      AV_CHANNEL_LAYOUT_HEXAGONAL           },
    { "6.1",            AV_CHANNEL_LAYOUT_6POINT1             },
    { "6.1(back)",      AV_CHANNEL_LAYOUT_6_POINT1_వెనుక        },
    { "6.1(front)",     AV_CHANNEL_LAYOUT_6POINT1_FRONT       },
    { "7.0",            AV_CHANNEL_LAYOUT_7POINT0             },
    { "7.0(front)",     AV_CHANNEL_LAYOUT_7POINT0_FRONT       },
    { "7.1",            AV_CHANNEL_LAYOUT_7POINT1             },
    { "7.1(wide)",      AV_CHANNEL_LAYOUT_7_POINT1_WIDE_వెనుక   },
    { "7.1(wide-side)", AV_CHANNEL_LAYOUT_7POINT1_WIDE        },
    { "5.1.2",          AV_CHANNEL_LAYOUT_5POINT1POINT2       },
    { "5.1.2(back)",    AV_CHANNEL_LAYOUT_5_POINT1_POINT2_వెనుక  },
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

పూర్ణాంకం av_channel_layout_custom_init(AVChannelLayout *channel_layout, పూర్ణాంకం nb_channels)
{
    AVChannelCustom *map;

    ఒకవేళ (nb_channels <= 0)
        తిరిగి AVERROR(EINVAL);

    map = av_calloc(nb_channels, పరిమాణం(*channel_layout->u.map));
    ఒకవేళ (!map)
        తిరిగి AVERROR(ENOMEM);
    కొరకు (పూర్ణాంకం i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->క్రమం       = AV_CHANNEL_క్రమం_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    తిరిగి 0;
}

పూర్ణాంకం av_channel_layout_from_ముసుగు(AVChannelLayout *channel_layout,
                                uint64_t ముసుగు_2)
{
    ఒకవేళ (!ముసుగు_2)
        తిరిగి AVERROR(EINVAL);

    channel_layout->క్రమం       = AV_CHANNEL_క్రమం_NATIVE;
    channel_layout->nb_channels = av_popcount64(ముసుగు_2);
    channel_layout->u.ముసుగు_2      = ముసుగు_2;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం parse_channel_list(AVChannelLayout *ch_layout, స్థిరరాశి అక్షరం *str)
{
    పూర్ణాంకం ret;
    పూర్ణాంకం nb_channels = 0;
    AVChannelCustom *map = ఖాళీ;
    AVChannelCustom custom = {0};

    అయితే (*str) {
        అక్షరం *channel, *chname;
        ret = av_opt_get_కీలకం_విలువ(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_కీలకం, &channel, &chname);
        ఒకవేళ (ret < 0) {
            av_freep(&map);
            తిరిగి ret;
        }
        ఒకవేళ (*str)
            str++; // skip separator
        ఒకవేళ (!channel) {
            channel = chname;
            chname = ఖాళీ;
        }
        av_strlcpy(custom.name, chname ? chname : "", పరిమాణం(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        ఒకవేళ (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            తిరిగి AVERROR(EINVAL);
        }

        av_dynarray2_కూడు((శూన్య **)&map, &nb_channels, పరిమాణం(custom), (శూన్య *)&custom);
        ఒకవేళ (!map)
            తిరిగి AVERROR(ENOMEM);
    }

    ఒకవేళ (!nb_channels)
        తిరిగి AVERROR(EINVAL);

    ch_layout->క్రమం = AV_CHANNEL_క్రమం_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    తిరిగి 0;
}

పూర్ణాంకం av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  స్థిరరాశి అక్షరం *str)
{
    పూర్ణాంకం i, matches, ret;
    పూర్ణాంకం channels = 0, nb_channels = 0;
    అక్షరం *chlist, *చివర;
    uint64_t ముసుగు_2 = 0;

    /* channel layout names */
    కొరకు (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        ఒకవేళ (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            తిరిగి 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, పరిమాణం(*channel_layout));

    /* ambisonic */
    ఒకవేళ (!అక్షరశ్రేణి_పోలిక(str, "ambisonic ", 10)) {
        స్థిరరాశి అక్షరం *p = str + 10;
        అక్షరం *endptr;
        AVChannelLayout extra = {0};
        పూర్ణాంకం క్రమం;

        క్రమం = strtol(p, &endptr, 0);
        ఒకవేళ (క్రమం < 0 || క్రమం + 1  > గరిష్ఠ_పూర్ణాంకం / (క్రమం + 1) ||
            (*endptr && *endptr != '+'))
            తిరిగి AVERROR(EINVAL);

        channel_layout->క్రమం       = AV_CHANNEL_క్రమం_AMBISONIC;
        channel_layout->nb_channels = (క్రమం + 1) * (క్రమం + 1);

        ఒకవేళ (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            ఒకవేళ (ret < 0)
                తిరిగి ret;
            ఒకవేళ (extra.nb_channels >= గరిష్ఠ_పూర్ణాంకం - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                తిరిగి AVERROR(EINVAL);
            }

            ఒకవేళ (extra.క్రమం == AV_CHANNEL_క్రమం_NATIVE) {
                channel_layout->u.ముసుగు_2 = extra.u.ముసుగు_2;
            } లేకపోతే {
                channel_layout->క్రమం = AV_CHANNEL_క్రమం_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              పరిమాణం(*channel_layout->u.map));
                ఒకవేళ (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    తిరిగి AVERROR(ENOMEM);
                }

                కొరకు (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_పునాది + i;
                కొరకు (i = 0; i < extra.nb_channels; i++) {
                    గణన AVChannel ch = av_channel_layout_channel_from_సూచీ(&extra, i);
                    ఒకవేళ (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        తిరిగి AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    ఒకవేళ (extra.క్రమం == AV_CHANNEL_క్రమం_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   పరిమాణం(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        తిరిగి 0;
    }

    chlist = av_strdup(str);
    ఒకవేళ (!chlist)
        తిరిగి AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    ఒకవేళ (ret < 0 && ret != AVERROR(EINVAL))
        తిరిగి ret;

    ఒకవేళ (ret >= 0) {
        స్థిరరాశి అక్షరం *చివర_par = strchr(str, ')');
        ఒకవేళ (matches == 2 && (nb_channels != channel_layout->nb_channels || !చివర_par || *++చివర_par)) {
            av_channel_layout_uninit(channel_layout);
            తిరిగి AVERROR(EINVAL);
        }
        తిరిగి 0;
    }

    errno = 0;
    ముసుగు_2 = strtoull(str, &చివర, 0);

    /* channel layout mask */
    ఒకవేళ (!errno && !*చివర && !strchr(str, '-') && ముసుగు_2) {
        av_channel_layout_from_ముసుగు(channel_layout, ముసుగు_2);
        తిరిగి 0;
    }

    errno = 0;
    channels = strtol(str, &చివర, 10);

    /* number of channels */
    ఒకవేళ (!errno && !strcmp(చివర, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        ఒకవేళ (channel_layout->క్రమం == AV_CHANNEL_క్రమం_NATIVE)
            తిరిగి 0;
    }

    /* number of unordered channels */
    ఒకవేళ (!errno && (!strcmp(చివర, "C") || !strcmp(చివర, " channels"))
        && channels > 0) {
        channel_layout->క్రమం = AV_CHANNEL_క్రమం_UNSPEC;
        channel_layout->nb_channels = channels;
        తిరిగి 0;
    }

    తిరిగి AVERROR(EINVAL);
}

శూన్య av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    ఒకవేళ (channel_layout->క్రమం == AV_CHANNEL_క్రమం_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, పరిమాణం(*channel_layout));
}

పూర్ణాంకం av_channel_layout_copy(AVChannelLayout *dst, స్థిరరాశి AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    ఒకవేళ (src->క్రమం == AV_CHANNEL_క్రమం_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, పరిమాణం(*dst->u.map));
        ఒకవేళ (!dst->u.map)
            తిరిగి AVERROR(ENOMEM);
        జ్ఞాపకం_నకలు(dst->u.map, src->u.map, src->nb_channels * పరిమాణం(*src->u.map));
    }
    తిరిగి 0;
}

స్థిర int64_t masked_description(స్థిరరాశి AVChannelLayout *channel_layout, పూర్ణాంకం ప్రారంభం_channel)
{
    uint64_t ముసుగు_2 = 0;
    కొరకు (పూర్ణాంకం i = ప్రారంభం_channel; i < channel_layout->nb_channels; i++) {
        గణన AVChannel ch = channel_layout->u.map[i].id;
        ఒకవేళ (ch >= 0 && ch < 63 && ముసుగు_2 < (1ULL << ch))
            ముసుగు_2 |= (1ULL << ch);
        లేకపోతే
            తిరిగి AVERROR(EINVAL);
    }
    తిరిగి ముసుగు_2;
}

స్థిర పూర్ణాంకం has_channel_పేర్లు(స్థిరరాశి AVChannelLayout *channel_layout)
{
    ఒకవేళ (channel_layout->క్రమం != AV_CHANNEL_క్రమం_CUSTOM)
        తిరిగి 0;
    కొరకు (పూర్ణాంకం i = 0; i < channel_layout->nb_channels; i++)
        ఒకవేళ (channel_layout->u.map[i].name[0])
            తిరిగి 1;
    తిరిగి 0;
}

పూర్ణాంకం av_channel_layout_ambisonic_క్రమం(స్థిరరాశి AVChannelLayout *channel_layout)
{
    పూర్ణాంకం i, highest_ambi, క్రమం;

    ఒకవేళ (channel_layout->క్రమం != AV_CHANNEL_క్రమం_AMBISONIC &&
        channel_layout->క్రమం != AV_CHANNEL_క్రమం_CUSTOM)
        తిరిగి AVERROR(EINVAL);

    highest_ambi = -1;
    ఒకవేళ (channel_layout->క్రమం == AV_CHANNEL_క్రమం_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.ముసుగు_2) - 1;
    లేకపోతే {
        స్థిరరాశి AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->క్రమం == AV_CHANNEL_క్రమం_CUSTOM);

        కొరకు (i = 0; i < channel_layout->nb_channels; i++) {
            పూర్ణాంకం is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            ఒకవేళ (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                తిరిగి AVERROR(EINVAL);

            /* non-default ordering */
            ఒకవేళ (is_ambi && map[i].id - AV_CHAN_AMBISONIC_పునాది != i)
                తిరిగి AVERROR(EINVAL);

            ఒకవేళ (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    ఒకవేళ (highest_ambi < 0)
        తిరిగి AVERROR(EINVAL);

    క్రమం = floor(వర్గమూలం(highest_ambi));
    /* incomplete order - some harmonics are missing */
    ఒకవేళ ((క్రమం + 1) * (క్రమం + 1) != highest_ambi + 1)
        తిరిగి AVERROR(EINVAL);

    తిరిగి క్రమం;
}

స్థిర గణన AVChannel_క్రమం canonical_క్రమం(AVChannelLayout *channel_layout)
{
    పూర్ణాంకం has_తెలిసిన_channel = 0;
    పూర్ణాంకం క్రమం;

    ఒకవేళ (channel_layout->క్రమం != AV_CHANNEL_క్రమం_CUSTOM)
        తిరిగి channel_layout->క్రమం;

    ఒకవేళ (has_channel_పేర్లు(channel_layout))
        తిరిగి AV_CHANNEL_క్రమం_CUSTOM;

    కొరకు (పూర్ణాంకం i = 0; i < channel_layout->nb_channels && !has_తెలిసిన_channel; i++)
        ఒకవేళ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_తెలిసిన_channel = 1;
    ఒకవేళ (!has_తెలిసిన_channel)
        తిరిగి AV_CHANNEL_క్రమం_UNSPEC;

    ఒకవేళ (masked_description(channel_layout, 0) > 0)
        తిరిగి AV_CHANNEL_క్రమం_NATIVE;

    క్రమం = av_channel_layout_ambisonic_క్రమం(channel_layout);
    ఒకవేళ (క్రమం >= 0 && masked_description(channel_layout, (క్రమం + 1) * (క్రమం + 1)) >= 0)
        తిరిగి AV_CHANNEL_క్రమం_AMBISONIC;

    తిరిగి AV_CHANNEL_క్రమం_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
స్థిర పూర్ణాంకం try_describe_ambisonic(AVBPrint *bp, స్థిరరాశి AVChannelLayout *channel_layout)
{
    పూర్ణాంకం nb_ambi_channels;
    పూర్ణాంకం క్రమం = av_channel_layout_ambisonic_క్రమం(channel_layout);
    ఒకవేళ (క్రమం < 0)
        తిరిగి క్రమం;

    av_bprintf(bp, "ambisonic %d", క్రమం);

    /* extra channels present */
    nb_ambi_channels = (క్రమం + 1) * (క్రమం + 1);
    ఒకవేళ (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        ఒకవేళ (channel_layout->క్రమం == AV_CHANNEL_క్రమం_AMBISONIC) {
            extra.క్రమం       = AV_CHANNEL_క్రమం_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.ముసుగు_2);
            extra.u.ముసుగు_2      = channel_layout->u.ముసుగు_2;
        } లేకపోతే {
            int64_t ముసుగు_2;
            ఒకవేళ (!has_channel_పేర్లు(channel_layout) &&
                (ముసుగు_2 = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.క్రమం       = AV_CHANNEL_క్రమం_NATIVE;
                extra.nb_channels = av_popcount64(ముసుగు_2);
                extra.u.ముసుగు_2      = ముసుగు_2;
            } లేకపోతే {
                extra.క్రమం       = AV_CHANNEL_క్రమం_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    తిరిగి 0;
}

పూర్ణాంకం av_channel_layout_describe_bprint(స్థిరరాశి AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    పూర్ణాంకం i;

    ఎంపిక (channel_layout->క్రమం) {
    స్థితి AV_CHANNEL_క్రమం_NATIVE:
        కొరకు (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            ఒకవేళ (channel_layout->u.ముసుగు_2 == channel_layout_map[i].layout.u.ముసుగు_2) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                తిరిగి 0;
            }
        av_fallthrough;
    స్థితి AV_CHANNEL_క్రమం_CUSTOM:
        ఒకవేళ (channel_layout->క్రమం == AV_CHANNEL_క్రమం_CUSTOM) {
            int64_t ముసుగు_2;
            పూర్ణాంకం res = try_describe_ambisonic(bp, channel_layout);
            ఒకవేళ (res >= 0)
                తిరిగి 0;
            ఒకవేళ (!has_channel_పేర్లు(channel_layout) &&
                (ముసుగు_2 = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .క్రమం       = AV_CHANNEL_క్రమం_NATIVE,
                                           .nb_channels = av_popcount64(ముసుగు_2),
                                           .u.ముసుగు_2      = ముసుగు_2 };
                తిరిగి av_channel_layout_describe_bprint(&native, bp);
            }
        }
        ఒకవేళ (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        కొరకు (i = 0; i < channel_layout->nb_channels; i++) {
            గణన AVChannel ch = av_channel_layout_channel_from_సూచీ(channel_layout, i);

            ఒకవేళ (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            ఒకవేళ (channel_layout->క్రమం == AV_CHANNEL_క్రమం_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        ఒకవేళ (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            తిరిగి 0;
        }
        av_fallthrough;
    స్థితి AV_CHANNEL_క్రమం_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        తిరిగి 0;
    స్థితి AV_CHANNEL_క్రమం_AMBISONIC:
        తిరిగి try_describe_ambisonic(bp, channel_layout);
    అప్రమేయ:
        తిరిగి AVERROR(EINVAL);
    }
}

పూర్ణాంకం av_channel_layout_describe(స్థిరరాశి AVChannelLayout *channel_layout,
                               అక్షరం *buf, size_t buf_కొలత)
{
    AVBPrint bp;
    పూర్ణాంకం ret;

    ఒకవేళ (!buf && buf_కొలత)
        తిరిగి AVERROR(EINVAL);

    av_bprint_init_for_బఫరు(&bp, buf, buf_కొలత);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    ఒకవేళ (bp.len >= గరిష్ఠ_పూర్ణాంకం)
        తిరిగి AVERROR(ERANGE);
    తిరిగి bp.len + 1;
}

గణన AVChannel
av_channel_layout_channel_from_సూచీ(స్థిరరాశి AVChannelLayout *channel_layout,
                                     గుర్తులేని పూర్ణాంకం idx)
{
    పూర్ణాంకం i;

    ఒకవేళ (idx >= channel_layout->nb_channels)
        తిరిగి AV_CHAN_NONE;

    ఎంపిక (channel_layout->క్రమం) {
    స్థితి AV_CHANNEL_క్రమం_CUSTOM:
        తిరిగి channel_layout->u.map[idx].id;
    స్థితి AV_CHANNEL_క్రమం_AMBISONIC: {
        పూర్ణాంకం ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.ముసుగు_2);
        ఒకవేళ (idx < ambi_channels)
            తిరిగి AV_CHAN_AMBISONIC_పునాది + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    స్థితి AV_CHANNEL_క్రమం_NATIVE:
        కొరకు (i = 0; i < 64; i++) {
            ఒకవేళ ((1ULL << i) & channel_layout->u.ముసుగు_2 && !idx--)
                తిరిగి i;
        }
        av_fallthrough;
    అప్రమేయ:
        తిరిగి AV_CHAN_NONE;
    }
}

గణన AVChannel
av_channel_layout_channel_from_string(స్థిరరాశి AVChannelLayout *channel_layout,
                                      స్థిరరాశి అక్షరం *str)
{
    పూర్ణాంకం సూచీ = av_channel_layout_సూచీ_from_string(channel_layout, str);

    ఒకవేళ (సూచీ < 0)
        తిరిగి AV_CHAN_NONE;

    తిరిగి av_channel_layout_channel_from_సూచీ(channel_layout, సూచీ);
}

పూర్ణాంకం av_channel_layout_సూచీ_from_channel(స్థిరరాశి AVChannelLayout *channel_layout,
                                         గణన AVChannel channel)
{
    పూర్ణాంకం i;

    ఒకవేళ (channel == AV_CHAN_NONE)
        తిరిగి AVERROR(EINVAL);

    ఎంపిక (channel_layout->క్రమం) {
    స్థితి AV_CHANNEL_క్రమం_CUSTOM:
        కొరకు (i = 0; i < channel_layout->nb_channels; i++)
            ఒకవేళ (channel_layout->u.map[i].id == channel)
                తిరిగి i;
        తిరిగి AVERROR(EINVAL);
    స్థితి AV_CHANNEL_క్రమం_AMBISONIC:
    స్థితి AV_CHANNEL_క్రమం_NATIVE: {
        uint64_t ముసుగు_2 = channel_layout->u.ముసుగు_2;
        పూర్ణాంకం ambi_channels = channel_layout->nb_channels - av_popcount64(ముసుగు_2);
        ఒకవేళ (channel_layout->క్రమం == AV_CHANNEL_క్రమం_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_పునాది) {
            ఒకవేళ (channel - AV_CHAN_AMBISONIC_పునాది >= ambi_channels)
                తిరిగి AVERROR(EINVAL);
            తిరిగి channel - AV_CHAN_AMBISONIC_పునాది;
        }
        ఒకవేళ ((గుర్తులేని)channel > 63 || !(ముసుగు_2 & (1ULL << channel)))
            తిరిగి AVERROR(EINVAL);
        ముసుగు_2 &= (1ULL << channel) - 1;
        తిరిగి av_popcount64(ముసుగు_2) + ambi_channels;
        }
    అప్రమేయ:
        తిరిగి AVERROR(EINVAL);
    }
}

పూర్ణాంకం av_channel_layout_సూచీ_from_string(స్థిరరాశి AVChannelLayout *channel_layout,
                                        స్థిరరాశి అక్షరం *str)
{
    స్థిరరాశి అక్షరం *chname;
    గణన AVChannel ch = AV_CHAN_NONE;

    ఎంపిక (channel_layout->క్రమం) {
    స్థితి AV_CHANNEL_క్రమం_CUSTOM:
        chname = అక్షరశ్రేణి_శోధన(str, "@");
        ఒకవేళ (chname) {
            అక్షరం buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(పరిమాణం(buf), chname - str));
            ఒకవేళ (!*chname)
                chname = ఖాళీ;
            ch = av_channel_from_string(buf);
            ఒకవేళ (ch == AV_CHAN_NONE && *buf)
                తిరిగి AVERROR(EINVAL);
        }
        కొరకు (పూర్ణాంకం i = 0; chname && i < channel_layout->nb_channels; i++) {
            ఒకవేళ (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                తిరిగి i;
        }
        av_fallthrough;
    స్థితి AV_CHANNEL_క్రమం_AMBISONIC:
    స్థితి AV_CHANNEL_క్రమం_NATIVE:
        ch = av_channel_from_string(str);
        ఒకవేళ (ch == AV_CHAN_NONE)
            తిరిగి AVERROR(EINVAL);
        తిరిగి av_channel_layout_సూచీ_from_channel(channel_layout, ch);
    }

    తిరిగి AVERROR(EINVAL);
}

పూర్ణాంకం av_channel_layout_check(స్థిరరాశి AVChannelLayout *channel_layout)
{
    ఒకవేళ (channel_layout->nb_channels <= 0)
        తిరిగి 0;

    ఎంపిక (channel_layout->క్రమం) {
    స్థితి AV_CHANNEL_క్రమం_NATIVE:
        తిరిగి av_popcount64(channel_layout->u.ముసుగు_2) == channel_layout->nb_channels;
    స్థితి AV_CHANNEL_క్రమం_CUSTOM:
        ఒకవేళ (!channel_layout->u.map)
            తిరిగి 0;
        కొరకు (పూర్ణాంకం i = 0; i < channel_layout->nb_channels; i++) {
            ఒకవేళ (channel_layout->u.map[i].id == AV_CHAN_NONE)
                తిరిగి 0;
        }
        తిరిగి 1;
    స్థితి AV_CHANNEL_క్రమం_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        తిరిగి av_popcount64(channel_layout->u.ముసుగు_2) < channel_layout->nb_channels;
    స్థితి AV_CHANNEL_క్రమం_UNSPEC:
        తిరిగి 1;
    అప్రమేయ:
        తిరిగి 0;
    }
}

పూర్ణాంకం av_channel_layout_compare(స్థిరరాశి AVChannelLayout *chl, స్థిరరాశి AVChannelLayout *chl1)
{
    పూర్ణాంకం i;

    /* different channel counts -> not equal */
    ఒకవేళ (chl->nb_channels != chl1->nb_channels)
        తిరిగి 1;

    /* if only one is unspecified -> not equal */
    ఒకవేళ ((chl->క్రమం  == AV_CHANNEL_క్రమం_UNSPEC) !=
        (chl1->క్రమం == AV_CHANNEL_క్రమం_UNSPEC))
        తిరిగి 1;
    /* both are unspecified -> equal */
    లేకపోతే ఒకవేళ (chl->క్రమం == AV_CHANNEL_క్రమం_UNSPEC)
        తిరిగి 0;

    /* can compare masks directly */
    ఒకవేళ ((chl->క్రమం == AV_CHANNEL_క్రమం_NATIVE ||
         chl->క్రమం == AV_CHANNEL_క్రమం_AMBISONIC) &&
        chl->క్రమం == chl1->క్రమం)
        తిరిగి chl->u.ముసుగు_2 != chl1->u.ముసుగు_2;

    /* compare channel by channel */
    కొరకు (i = 0; i < chl->nb_channels; i++)
        ఒకవేళ (av_channel_layout_channel_from_సూచీ(chl,  i) !=
            av_channel_layout_channel_from_సూచీ(chl1, i))
            తిరిగి 1;
    తిరిగి 0;
}

శూన్య av_channel_layout_default(AVChannelLayout *ch_layout, పూర్ణాంకం nb_channels)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        ఒకవేళ (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            తిరిగి;
        }

    ch_layout->క్రమం       = AV_CHANNEL_క్రమం_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

స్థిరరాశి AVChannelLayout *av_channel_layout_standard(శూన్య **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    స్థిరరాశి AVChannelLayout *ch_layout = ఖాళీ;

    ఒకవేళ (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (శూన్య*)(i + 1);
    }

    తిరిగి ch_layout;
}

uint64_t av_channel_layout_subset(స్థిరరాశి AVChannelLayout *channel_layout,
                                  uint64_t ముసుగు_2)
{
    uint64_t ret = 0;
    పూర్ణాంకం i;

    ఎంపిక (channel_layout->క్రమం) {
    స్థితి AV_CHANNEL_క్రమం_NATIVE:
    స్థితి AV_CHANNEL_క్రమం_AMBISONIC:
        తిరిగి channel_layout->u.ముసుగు_2 & ముసుగు_2;
    స్థితి AV_CHANNEL_క్రమం_CUSTOM:
        కొరకు (i = 0; i < 64; i++)
            ఒకవేళ (ముసుగు_2 & (1ULL << i) && av_channel_layout_సూచీ_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        ఆపు;
    }

    తిరిగి ret;
}

పూర్ణాంకం av_channel_layout_retype(AVChannelLayout *channel_layout, గణన AVChannel_క్రమం క్రమం, పూర్ణాంకం flags)
{
    పూర్ణాంకం allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    పూర్ణాంకం lossy;

    ఒకవేళ (!av_channel_layout_check(channel_layout))
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        క్రమం = canonical_క్రమం(channel_layout);

    ఒకవేళ (channel_layout->క్రమం == క్రమం)
        తిరిగి 0;

    ఎంపిక (క్రమం) {
    స్థితి AV_CHANNEL_క్రమం_UNSPEC: {
        పూర్ణాంకం nb_channels = channel_layout->nb_channels;
        ఒకవేళ (channel_layout->క్రమం == AV_CHANNEL_క్రమం_CUSTOM) {
            lossy = 0;
            కొరకు (పూర్ణాంకం i = 0; i < nb_channels; i++) {
                ఒకవేళ (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    ఆపు;
                }
            }
        } లేకపోతే {
            lossy = 1;
        }
        ఒకవేళ (!lossy || allow_lossy) {
            శూన్య *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->క్రమం       = AV_CHANNEL_క్రమం_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            తిరిగి lossy;
        }
        తిరిగి AVERROR(ENOSYS);
        }
    స్థితి AV_CHANNEL_క్రమం_NATIVE:
        ఒకవేళ (channel_layout->క్రమం == AV_CHANNEL_క్రమం_CUSTOM) {
            int64_t ముసుగు_2 = masked_description(channel_layout, 0);
            ఒకవేళ (ముసుగు_2 < 0)
                తిరిగి AVERROR(ENOSYS);
            lossy = has_channel_పేర్లు(channel_layout);
            ఒకవేళ (!lossy || allow_lossy) {
                శూన్య *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_ముసుగు(channel_layout, ముసుగు_2);
                channel_layout->opaque = opaque;
                తిరిగి lossy;
            }
        }
        తిరిగి AVERROR(ENOSYS);
    స్థితి AV_CHANNEL_క్రమం_CUSTOM: {
        AVChannelLayout custom = { 0 };
        పూర్ణాంకం ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        శూన్య *opaque = channel_layout->opaque;
        ఒకవేళ (ret < 0)
            తిరిగి ret;
        ఒకవేళ (channel_layout->క్రమం != AV_CHANNEL_క్రమం_UNSPEC)
            కొరకు (పూర్ణాంకం i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_సూచీ(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        తిరిగి 0;
        }
    స్థితి AV_CHANNEL_క్రమం_AMBISONIC:
        ఒకవేళ (channel_layout->క్రమం == AV_CHANNEL_క్రమం_CUSTOM) {
            int64_t ముసుగు_2;
            పూర్ణాంకం nb_channels = channel_layout->nb_channels;
            పూర్ణాంకం amb_క్రమం = av_channel_layout_ambisonic_క్రమం(channel_layout);
            ఒకవేళ (amb_క్రమం < 0)
                తిరిగి AVERROR(ENOSYS);
            ముసుగు_2 = masked_description(channel_layout, (amb_క్రమం + 1) * (amb_క్రమం + 1));
            ఒకవేళ (ముసుగు_2 < 0)
                తిరిగి AVERROR(ENOSYS);
            lossy = has_channel_పేర్లు(channel_layout);
            ఒకవేళ (!lossy || allow_lossy) {
                శూన్య *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->క్రమం       = AV_CHANNEL_క్రమం_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.ముసుగు_2      = ముసుగు_2;
                channel_layout->opaque      = opaque;
                తిరిగి lossy;
            }
        }
        తిరిగి AVERROR(ENOSYS);
    అప్రమేయ:
        తిరిగి AVERROR(EINVAL);
    }
}
