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

#شامل <stdint.h>
#شامل <stdlib.h>
#شامل <string.h>

#شامل "avassert.h"
#شامل "channel_layout.h"
#شامل "bprint.h"
#شامل "common.h"
#شامل "error.h"
#شامل "attributes.h"
#شامل "macros.h"
#شامل "mem.h"
#شامل "opt.h"

#تعریف_کرو CHAN_IS_AMBI(x) ((x) >= AV_CHAN_AMBISONIC_بنیاد &&\
                         (x) <= AV_CHAN_AMBISONIC_انتہا)

ساخت channel_name {
    ثابت حرف *name;
    ثابت حرف *description;
};

ساکن ثابت ساخت channel_name channel_نام[] = {
    [AV_CHAN_FRONT_بایاں           ] = { "FL",        "front left"            },
    [AV_CHAN_FRONT_دایاں          ] = { "FR",        "front right"           },
    [AV_CHAN_FRONT_CENTER         ] = { "FC",        "front center"          },
    [AV_CHAN_کم_FREQUENCY        ] = { "LFE",       "low frequency"         },
    [AV_CHAN_عقب_بایاں            ] = { "BL",        "back left"             },
    [AV_CHAN_عقب_دایاں           ] = { "BR",        "back right"            },
    [AV_CHAN_FRONT_بایاں_کا_CENTER ] = { "FLC",       "front left-of-center"  },
    [AV_CHAN_FRONT_دایاں_کا_CENTER] = { "FRC",       "front right-of-center" },
    [AV_CHAN_عقب_CENTER          ] = { "BC",        "back center"           },
    [AV_CHAN_SIDE_بایاں            ] = { "SL",        "side left"             },
    [AV_CHAN_SIDE_دایاں           ] = { "SR",        "side right"            },
    [AV_CHAN_چوٹی_CENTER           ] = { "TC",        "top center"            },
    [AV_CHAN_چوٹی_FRONT_بایاں       ] = { "TFL",       "top front left"        },
    [AV_CHAN_چوٹی_FRONT_CENTER     ] = { "TFC",       "top front center"      },
    [AV_CHAN_چوٹی_FRONT_دایاں      ] = { "TFR",       "top front right"       },
    [AV_CHAN_چوٹی_عقب_بایاں        ] = { "TBL",       "top back left"         },
    [AV_CHAN_چوٹی_عقب_CENTER      ] = { "TBC",       "top back center"       },
    [AV_CHAN_چوٹی_عقب_دایاں       ] = { "TBR",       "top back right"        },
    [AV_CHAN_STEREO_بایاں          ] = { "DL",        "downmix left"          },
    [AV_CHAN_STEREO_دایاں         ] = { "DR",        "downmix right"         },
    [AV_CHAN_WIDE_بایاں            ] = { "WL",        "wide left"             },
    [AV_CHAN_WIDE_دایاں           ] = { "WR",        "wide right"            },
    [AV_CHAN_SURROUND_براہ_راست_بایاں ] = { "SDL",       "surround direct left"  },
    [AV_CHAN_SURROUND_براہ_راست_دایاں] = { "SDR",       "surround direct right" },
    [AV_CHAN_کم_FREQUENCY_2      ] = { "LFE2",      "low frequency 2"       },
    [AV_CHAN_چوٹی_SIDE_بایاں        ] = { "TSL",       "top side left"         },
    [AV_CHAN_چوٹی_SIDE_دایاں       ] = { "TSR",       "top side right"        },
    [AV_CHAN_BOTTOM_FRONT_CENTER  ] = { "BFC",       "bottom front center"   },
    [AV_CHAN_BOTTOM_FRONT_بایاں    ] = { "BFL",       "bottom front left"     },
    [AV_CHAN_BOTTOM_FRONT_دایاں   ] = { "BFR",       "bottom front right"    },
    [AV_CHAN_SIDE_SURROUND_بایاں   ] = { "SSL",       "side surround left"    },
    [AV_CHAN_SIDE_SURROUND_دایاں  ] = { "SSR",       "side surround right"   },
    [AV_CHAN_چوٹی_SURROUND_بایاں    ] = { "TTL",       "top surround left"     },
    [AV_CHAN_چوٹی_SURROUND_دایاں   ] = { "TTR",       "top surround right"    },
    [AV_CHAN_BINAURAL_بایاں        ] = { "BIL",       "binaural left"         },
    [AV_CHAN_BINAURAL_دایاں       ] = { "BIR",       "binaural right"        },
};

خالی av_channel_name_bprint(AVBPrint *bp, شمار AVChannel channel_id)
{
    اگر (channel_id >= AV_CHAN_AMBISONIC_بنیاد &&
        channel_id <= AV_CHAN_AMBISONIC_انتہا)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_بنیاد);
    ورنہ اگر ((غیرعلامتی)channel_id < FF_ARRAY_ELEMS(channel_نام) &&
             channel_نام[channel_id].name)
        av_bprintf(bp, "%s", channel_نام[channel_id].name);
    ورنہ اگر (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    ورنہ اگر (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    ورنہ اگر (channel_id == AV_CHAN_غیر_مستعمل)
        av_bprintf(bp, "UNSD");
    ورنہ
        av_bprintf(bp, "USR%d", channel_id);
}

صحیح av_channel_name(حرف *buf, size_t buf_سائز, شمار AVChannel channel_id)
{
    AVBPrint bp;

    اگر (!buf && buf_سائز)
        واپس AVERROR(EINVAL);

    av_bprint_init_for_بفر(&bp, buf, buf_سائز);
    av_channel_name_bprint(&bp, channel_id);

    اگر (bp.len >= زیادہ_سے_زیادہ_عدد)
        واپس AVERROR(ERANGE);
    واپس bp.len + 1;
}

خالی av_channel_description_bprint(AVBPrint *bp, شمار AVChannel channel_id)
{
    اگر (channel_id >= AV_CHAN_AMBISONIC_بنیاد &&
        channel_id <= AV_CHAN_AMBISONIC_انتہا)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_بنیاد);
    ورنہ اگر ((غیرعلامتی)channel_id < FF_ARRAY_ELEMS(channel_نام) &&
             channel_نام[channel_id].description)
        av_bprintf(bp, "%s", channel_نام[channel_id].description);
    ورنہ اگر (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    ورنہ اگر (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    ورنہ اگر (channel_id == AV_CHAN_غیر_مستعمل)
        av_bprintf(bp, "unused");
    ورنہ
        av_bprintf(bp, "user %d", channel_id);
}

صحیح av_channel_description(حرف *buf, size_t buf_سائز, شمار AVChannel channel_id)
{
    AVBPrint bp;

    اگر (!buf && buf_سائز)
        واپس AVERROR(EINVAL);

    av_bprint_init_for_بفر(&bp, buf, buf_سائز);
    av_channel_description_bprint(&bp, channel_id);

    اگر (bp.len >= زیادہ_سے_زیادہ_عدد)
        واپس AVERROR(ERANGE);
    واپس bp.len + 1;
}

شمار AVChannel av_channel_from_string(ثابت حرف *str)
{
    صحیح i;
    حرف *endptr = (حرف *)str;
    شمار AVChannel id = AV_CHAN_NONE;

    اگر (!لڑی_موازنہ(str, "AMBI", 4)) {
        i = strtol(str + 4, تہی, 0);
        اگر (i < 0 || i > AV_CHAN_AMBISONIC_انتہا - AV_CHAN_AMBISONIC_بنیاد)
            واپس AV_CHAN_NONE;
        واپس AV_CHAN_AMBISONIC_بنیاد + i;
    }

    برائے (i = 0; i < FF_ARRAY_ELEMS(channel_نام); i++) {
        اگر (channel_نام[i].name && !strcmp(str, channel_نام[i].name))
            واپس i;
    }
    اگر (!strcmp(str, "UNK"))
        واپس AV_CHAN_UNKNOWN;
    اگر (!strcmp(str, "UNSD"))
        واپس AV_CHAN_غیر_مستعمل;

    اگر (!لڑی_موازنہ(str, "USR", 3)) {
        ثابت حرف *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    اگر (id >= 0 && !*endptr)
        واپس id;

    واپس AV_CHAN_NONE;
}

ساخت channel_layout_name {
    ثابت حرف *name;
    AVChannelLayout layout;
};

ساکن ثابت ساخت channel_layout_name channel_layout_map[] = {
    { "mono",           AV_CHANNEL_LAYOUT_MONO                },
    { "stereo",         AV_CHANNEL_LAYOUT_STEREO              },
    { "2.1",            AV_CHANNEL_LAYOUT_2POINT1             },
    { "3.0",            AV_CHANNEL_LAYOUT_SURROUND            },
    { "3.0(back)",      AV_CHANNEL_LAYOUT_2_1                 },
    { "4.0",            AV_CHANNEL_LAYOUT_4POINT0             },
    { "quad",           AV_CHANNEL_LAYOUT_QUAD                },
    { "quad(side)",     AV_CHANNEL_LAYOUT_2_2                 },
    { "3.1",            AV_CHANNEL_LAYOUT_3POINT1             },
    { "5.0",            AV_CHANNEL_LAYOUT_5_POINT0_عقب        },
    { "5.0(side)",      AV_CHANNEL_LAYOUT_5POINT0             },
    { "4.1",            AV_CHANNEL_LAYOUT_4POINT1             },
    { "5.1",            AV_CHANNEL_LAYOUT_5_POINT1_عقب        },
    { "5.1(side)",      AV_CHANNEL_LAYOUT_5POINT1             },
    { "6.0",            AV_CHANNEL_LAYOUT_6POINT0             },
    { "6.0(front)",     AV_CHANNEL_LAYOUT_6POINT0_FRONT       },
    { "3.1.2",          AV_CHANNEL_LAYOUT_3POINT1POINT2       },
    { "hexagonal",      AV_CHANNEL_LAYOUT_HEXAGONAL           },
    { "6.1",            AV_CHANNEL_LAYOUT_6POINT1             },
    { "6.1(back)",      AV_CHANNEL_LAYOUT_6_POINT1_عقب        },
    { "6.1(front)",     AV_CHANNEL_LAYOUT_6POINT1_FRONT       },
    { "7.0",            AV_CHANNEL_LAYOUT_7POINT0             },
    { "7.0(front)",     AV_CHANNEL_LAYOUT_7POINT0_FRONT       },
    { "7.1",            AV_CHANNEL_LAYOUT_7POINT1             },
    { "7.1(wide)",      AV_CHANNEL_LAYOUT_7_POINT1_WIDE_عقب   },
    { "7.1(wide-side)", AV_CHANNEL_LAYOUT_7POINT1_WIDE        },
    { "5.1.2",          AV_CHANNEL_LAYOUT_5POINT1POINT2       },
    { "5.1.2(back)",    AV_CHANNEL_LAYOUT_5_POINT1_POINT2_عقب  },
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

صحیح av_channel_layout_custom_init(AVChannelLayout *channel_layout, صحیح nb_channels)
{
    AVChannelCustom *map;

    اگر (nb_channels <= 0)
        واپس AVERROR(EINVAL);

    map = av_calloc(nb_channels, حجم(*channel_layout->u.map));
    اگر (!map)
        واپس AVERROR(ENOMEM);
    برائے (صحیح i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->ترتیب       = AV_CHANNEL_ترتیب_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    واپس 0;
}

صحیح av_channel_layout_from_نقاب(AVChannelLayout *channel_layout,
                                uint64_t نقاب_2)
{
    اگر (!نقاب_2)
        واپس AVERROR(EINVAL);

    channel_layout->ترتیب       = AV_CHANNEL_ترتیب_NATIVE;
    channel_layout->nb_channels = av_popcount64(نقاب_2);
    channel_layout->u.نقاب_2      = نقاب_2;

    واپس 0;
}

ساکن صحیح parse_channel_list(AVChannelLayout *ch_layout, ثابت حرف *str)
{
    صحیح ret;
    صحیح nb_channels = 0;
    AVChannelCustom *map = تہی;
    AVChannelCustom custom = {0};

    جب (*str) {
        حرف *channel, *chname;
        ret = av_opt_get_کلید_قدر(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_کلید, &channel, &chname);
        اگر (ret < 0) {
            av_freep(&map);
            واپس ret;
        }
        اگر (*str)
            str++; // skip separator
        اگر (!channel) {
            channel = chname;
            chname = تہی;
        }
        av_strlcpy(custom.name, chname ? chname : "", حجم(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        اگر (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            واپس AVERROR(EINVAL);
        }

        av_dynarray2_جوڑو((خالی **)&map, &nb_channels, حجم(custom), (خالی *)&custom);
        اگر (!map)
            واپس AVERROR(ENOMEM);
    }

    اگر (!nb_channels)
        واپس AVERROR(EINVAL);

    ch_layout->ترتیب = AV_CHANNEL_ترتیب_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    واپس 0;
}

صحیح av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  ثابت حرف *str)
{
    صحیح i, matches, ret;
    صحیح channels = 0, nb_channels = 0;
    حرف *chlist, *انتہا;
    uint64_t نقاب_2 = 0;

    /* channel layout names */
    برائے (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        اگر (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            واپس 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, حجم(*channel_layout));

    /* ambisonic */
    اگر (!لڑی_موازنہ(str, "ambisonic ", 10)) {
        ثابت حرف *p = str + 10;
        حرف *endptr;
        AVChannelLayout extra = {0};
        صحیح ترتیب;

        ترتیب = strtol(p, &endptr, 0);
        اگر (ترتیب < 0 || ترتیب + 1  > زیادہ_سے_زیادہ_عدد / (ترتیب + 1) ||
            (*endptr && *endptr != '+'))
            واپس AVERROR(EINVAL);

        channel_layout->ترتیب       = AV_CHANNEL_ترتیب_AMBISONIC;
        channel_layout->nb_channels = (ترتیب + 1) * (ترتیب + 1);

        اگر (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            اگر (ret < 0)
                واپس ret;
            اگر (extra.nb_channels >= زیادہ_سے_زیادہ_عدد - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                واپس AVERROR(EINVAL);
            }

            اگر (extra.ترتیب == AV_CHANNEL_ترتیب_NATIVE) {
                channel_layout->u.نقاب_2 = extra.u.نقاب_2;
            } ورنہ {
                channel_layout->ترتیب = AV_CHANNEL_ترتیب_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              حجم(*channel_layout->u.map));
                اگر (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    واپس AVERROR(ENOMEM);
                }

                برائے (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_بنیاد + i;
                برائے (i = 0; i < extra.nb_channels; i++) {
                    شمار AVChannel ch = av_channel_layout_channel_from_اشاریہ(&extra, i);
                    اگر (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        واپس AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    اگر (extra.ترتیب == AV_CHANNEL_ترتیب_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   حجم(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        واپس 0;
    }

    chlist = av_strdup(str);
    اگر (!chlist)
        واپس AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    اگر (ret < 0 && ret != AVERROR(EINVAL))
        واپس ret;

    اگر (ret >= 0) {
        ثابت حرف *انتہا_par = strchr(str, ')');
        اگر (matches == 2 && (nb_channels != channel_layout->nb_channels || !انتہا_par || *++انتہا_par)) {
            av_channel_layout_uninit(channel_layout);
            واپس AVERROR(EINVAL);
        }
        واپس 0;
    }

    errno = 0;
    نقاب_2 = strtoull(str, &انتہا, 0);

    /* channel layout mask */
    اگر (!errno && !*انتہا && !strchr(str, '-') && نقاب_2) {
        av_channel_layout_from_نقاب(channel_layout, نقاب_2);
        واپس 0;
    }

    errno = 0;
    channels = strtol(str, &انتہا, 10);

    /* number of channels */
    اگر (!errno && !strcmp(انتہا, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        اگر (channel_layout->ترتیب == AV_CHANNEL_ترتیب_NATIVE)
            واپس 0;
    }

    /* number of unordered channels */
    اگر (!errno && (!strcmp(انتہا, "C") || !strcmp(انتہا, " channels"))
        && channels > 0) {
        channel_layout->ترتیب = AV_CHANNEL_ترتیب_UNSPEC;
        channel_layout->nb_channels = channels;
        واپس 0;
    }

    واپس AVERROR(EINVAL);
}

خالی av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    اگر (channel_layout->ترتیب == AV_CHANNEL_ترتیب_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, حجم(*channel_layout));
}

صحیح av_channel_layout_copy(AVChannelLayout *dst, ثابت AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    اگر (src->ترتیب == AV_CHANNEL_ترتیب_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, حجم(*dst->u.map));
        اگر (!dst->u.map)
            واپس AVERROR(ENOMEM);
        حافظہ_نقل(dst->u.map, src->u.map, src->nb_channels * حجم(*src->u.map));
    }
    واپس 0;
}

ساکن int64_t masked_description(ثابت AVChannelLayout *channel_layout, صحیح آغاز_channel)
{
    uint64_t نقاب_2 = 0;
    برائے (صحیح i = آغاز_channel; i < channel_layout->nb_channels; i++) {
        شمار AVChannel ch = channel_layout->u.map[i].id;
        اگر (ch >= 0 && ch < 63 && نقاب_2 < (1ULL << ch))
            نقاب_2 |= (1ULL << ch);
        ورنہ
            واپس AVERROR(EINVAL);
    }
    واپس نقاب_2;
}

ساکن صحیح has_channel_نام(ثابت AVChannelLayout *channel_layout)
{
    اگر (channel_layout->ترتیب != AV_CHANNEL_ترتیب_CUSTOM)
        واپس 0;
    برائے (صحیح i = 0; i < channel_layout->nb_channels; i++)
        اگر (channel_layout->u.map[i].name[0])
            واپس 1;
    واپس 0;
}

صحیح av_channel_layout_ambisonic_ترتیب(ثابت AVChannelLayout *channel_layout)
{
    صحیح i, highest_ambi, ترتیب;

    اگر (channel_layout->ترتیب != AV_CHANNEL_ترتیب_AMBISONIC &&
        channel_layout->ترتیب != AV_CHANNEL_ترتیب_CUSTOM)
        واپس AVERROR(EINVAL);

    highest_ambi = -1;
    اگر (channel_layout->ترتیب == AV_CHANNEL_ترتیب_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.نقاب_2) - 1;
    ورنہ {
        ثابت AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->ترتیب == AV_CHANNEL_ترتیب_CUSTOM);

        برائے (i = 0; i < channel_layout->nb_channels; i++) {
            صحیح is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            اگر (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                واپس AVERROR(EINVAL);

            /* non-default ordering */
            اگر (is_ambi && map[i].id - AV_CHAN_AMBISONIC_بنیاد != i)
                واپس AVERROR(EINVAL);

            اگر (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    اگر (highest_ambi < 0)
        واپس AVERROR(EINVAL);

    ترتیب = floor(جذر(highest_ambi));
    /* incomplete order - some harmonics are missing */
    اگر ((ترتیب + 1) * (ترتیب + 1) != highest_ambi + 1)
        واپس AVERROR(EINVAL);

    واپس ترتیب;
}

ساکن شمار AVChannel_ترتیب canonical_ترتیب(AVChannelLayout *channel_layout)
{
    صحیح has_معلوم_channel = 0;
    صحیح ترتیب;

    اگر (channel_layout->ترتیب != AV_CHANNEL_ترتیب_CUSTOM)
        واپس channel_layout->ترتیب;

    اگر (has_channel_نام(channel_layout))
        واپس AV_CHANNEL_ترتیب_CUSTOM;

    برائے (صحیح i = 0; i < channel_layout->nb_channels && !has_معلوم_channel; i++)
        اگر (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_معلوم_channel = 1;
    اگر (!has_معلوم_channel)
        واپس AV_CHANNEL_ترتیب_UNSPEC;

    اگر (masked_description(channel_layout, 0) > 0)
        واپس AV_CHANNEL_ترتیب_NATIVE;

    ترتیب = av_channel_layout_ambisonic_ترتیب(channel_layout);
    اگر (ترتیب >= 0 && masked_description(channel_layout, (ترتیب + 1) * (ترتیب + 1)) >= 0)
        واپس AV_CHANNEL_ترتیب_AMBISONIC;

    واپس AV_CHANNEL_ترتیب_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
ساکن صحیح try_describe_ambisonic(AVBPrint *bp, ثابت AVChannelLayout *channel_layout)
{
    صحیح nb_ambi_channels;
    صحیح ترتیب = av_channel_layout_ambisonic_ترتیب(channel_layout);
    اگر (ترتیب < 0)
        واپس ترتیب;

    av_bprintf(bp, "ambisonic %d", ترتیب);

    /* extra channels present */
    nb_ambi_channels = (ترتیب + 1) * (ترتیب + 1);
    اگر (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        اگر (channel_layout->ترتیب == AV_CHANNEL_ترتیب_AMBISONIC) {
            extra.ترتیب       = AV_CHANNEL_ترتیب_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.نقاب_2);
            extra.u.نقاب_2      = channel_layout->u.نقاب_2;
        } ورنہ {
            int64_t نقاب_2;
            اگر (!has_channel_نام(channel_layout) &&
                (نقاب_2 = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.ترتیب       = AV_CHANNEL_ترتیب_NATIVE;
                extra.nb_channels = av_popcount64(نقاب_2);
                extra.u.نقاب_2      = نقاب_2;
            } ورنہ {
                extra.ترتیب       = AV_CHANNEL_ترتیب_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    واپس 0;
}

صحیح av_channel_layout_describe_bprint(ثابت AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    صحیح i;

    انتخاب (channel_layout->ترتیب) {
    حالت AV_CHANNEL_ترتیب_NATIVE:
        برائے (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            اگر (channel_layout->u.نقاب_2 == channel_layout_map[i].layout.u.نقاب_2) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                واپس 0;
            }
        av_fallthrough;
    حالت AV_CHANNEL_ترتیب_CUSTOM:
        اگر (channel_layout->ترتیب == AV_CHANNEL_ترتیب_CUSTOM) {
            int64_t نقاب_2;
            صحیح res = try_describe_ambisonic(bp, channel_layout);
            اگر (res >= 0)
                واپس 0;
            اگر (!has_channel_نام(channel_layout) &&
                (نقاب_2 = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .ترتیب       = AV_CHANNEL_ترتیب_NATIVE,
                                           .nb_channels = av_popcount64(نقاب_2),
                                           .u.نقاب_2      = نقاب_2 };
                واپس av_channel_layout_describe_bprint(&native, bp);
            }
        }
        اگر (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        برائے (i = 0; i < channel_layout->nb_channels; i++) {
            شمار AVChannel ch = av_channel_layout_channel_from_اشاریہ(channel_layout, i);

            اگر (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            اگر (channel_layout->ترتیب == AV_CHANNEL_ترتیب_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        اگر (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            واپس 0;
        }
        av_fallthrough;
    حالت AV_CHANNEL_ترتیب_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        واپس 0;
    حالت AV_CHANNEL_ترتیب_AMBISONIC:
        واپس try_describe_ambisonic(bp, channel_layout);
    طےشدہ:
        واپس AVERROR(EINVAL);
    }
}

صحیح av_channel_layout_describe(ثابت AVChannelLayout *channel_layout,
                               حرف *buf, size_t buf_سائز)
{
    AVBPrint bp;
    صحیح ret;

    اگر (!buf && buf_سائز)
        واپس AVERROR(EINVAL);

    av_bprint_init_for_بفر(&bp, buf, buf_سائز);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    اگر (ret < 0)
        واپس ret;

    اگر (bp.len >= زیادہ_سے_زیادہ_عدد)
        واپس AVERROR(ERANGE);
    واپس bp.len + 1;
}

شمار AVChannel
av_channel_layout_channel_from_اشاریہ(ثابت AVChannelLayout *channel_layout,
                                     غیرعلامتی صحیح idx)
{
    صحیح i;

    اگر (idx >= channel_layout->nb_channels)
        واپس AV_CHAN_NONE;

    انتخاب (channel_layout->ترتیب) {
    حالت AV_CHANNEL_ترتیب_CUSTOM:
        واپس channel_layout->u.map[idx].id;
    حالت AV_CHANNEL_ترتیب_AMBISONIC: {
        صحیح ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.نقاب_2);
        اگر (idx < ambi_channels)
            واپس AV_CHAN_AMBISONIC_بنیاد + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    حالت AV_CHANNEL_ترتیب_NATIVE:
        برائے (i = 0; i < 64; i++) {
            اگر ((1ULL << i) & channel_layout->u.نقاب_2 && !idx--)
                واپس i;
        }
        av_fallthrough;
    طےشدہ:
        واپس AV_CHAN_NONE;
    }
}

شمار AVChannel
av_channel_layout_channel_from_string(ثابت AVChannelLayout *channel_layout,
                                      ثابت حرف *str)
{
    صحیح اشاریہ = av_channel_layout_اشاریہ_from_string(channel_layout, str);

    اگر (اشاریہ < 0)
        واپس AV_CHAN_NONE;

    واپس av_channel_layout_channel_from_اشاریہ(channel_layout, اشاریہ);
}

صحیح av_channel_layout_اشاریہ_from_channel(ثابت AVChannelLayout *channel_layout,
                                         شمار AVChannel channel)
{
    صحیح i;

    اگر (channel == AV_CHAN_NONE)
        واپس AVERROR(EINVAL);

    انتخاب (channel_layout->ترتیب) {
    حالت AV_CHANNEL_ترتیب_CUSTOM:
        برائے (i = 0; i < channel_layout->nb_channels; i++)
            اگر (channel_layout->u.map[i].id == channel)
                واپس i;
        واپس AVERROR(EINVAL);
    حالت AV_CHANNEL_ترتیب_AMBISONIC:
    حالت AV_CHANNEL_ترتیب_NATIVE: {
        uint64_t نقاب_2 = channel_layout->u.نقاب_2;
        صحیح ambi_channels = channel_layout->nb_channels - av_popcount64(نقاب_2);
        اگر (channel_layout->ترتیب == AV_CHANNEL_ترتیب_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_بنیاد) {
            اگر (channel - AV_CHAN_AMBISONIC_بنیاد >= ambi_channels)
                واپس AVERROR(EINVAL);
            واپس channel - AV_CHAN_AMBISONIC_بنیاد;
        }
        اگر ((غیرعلامتی)channel > 63 || !(نقاب_2 & (1ULL << channel)))
            واپس AVERROR(EINVAL);
        نقاب_2 &= (1ULL << channel) - 1;
        واپس av_popcount64(نقاب_2) + ambi_channels;
        }
    طےشدہ:
        واپس AVERROR(EINVAL);
    }
}

صحیح av_channel_layout_اشاریہ_from_string(ثابت AVChannelLayout *channel_layout,
                                        ثابت حرف *str)
{
    ثابت حرف *chname;
    شمار AVChannel ch = AV_CHAN_NONE;

    انتخاب (channel_layout->ترتیب) {
    حالت AV_CHANNEL_ترتیب_CUSTOM:
        chname = لڑی_تلاش(str, "@");
        اگر (chname) {
            حرف buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(حجم(buf), chname - str));
            اگر (!*chname)
                chname = تہی;
            ch = av_channel_from_string(buf);
            اگر (ch == AV_CHAN_NONE && *buf)
                واپس AVERROR(EINVAL);
        }
        برائے (صحیح i = 0; chname && i < channel_layout->nb_channels; i++) {
            اگر (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                واپس i;
        }
        av_fallthrough;
    حالت AV_CHANNEL_ترتیب_AMBISONIC:
    حالت AV_CHANNEL_ترتیب_NATIVE:
        ch = av_channel_from_string(str);
        اگر (ch == AV_CHAN_NONE)
            واپس AVERROR(EINVAL);
        واپس av_channel_layout_اشاریہ_from_channel(channel_layout, ch);
    }

    واپس AVERROR(EINVAL);
}

صحیح av_channel_layout_check(ثابت AVChannelLayout *channel_layout)
{
    اگر (channel_layout->nb_channels <= 0)
        واپس 0;

    انتخاب (channel_layout->ترتیب) {
    حالت AV_CHANNEL_ترتیب_NATIVE:
        واپس av_popcount64(channel_layout->u.نقاب_2) == channel_layout->nb_channels;
    حالت AV_CHANNEL_ترتیب_CUSTOM:
        اگر (!channel_layout->u.map)
            واپس 0;
        برائے (صحیح i = 0; i < channel_layout->nb_channels; i++) {
            اگر (channel_layout->u.map[i].id == AV_CHAN_NONE)
                واپس 0;
        }
        واپس 1;
    حالت AV_CHANNEL_ترتیب_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        واپس av_popcount64(channel_layout->u.نقاب_2) < channel_layout->nb_channels;
    حالت AV_CHANNEL_ترتیب_UNSPEC:
        واپس 1;
    طےشدہ:
        واپس 0;
    }
}

صحیح av_channel_layout_compare(ثابت AVChannelLayout *chl, ثابت AVChannelLayout *chl1)
{
    صحیح i;

    /* different channel counts -> not equal */
    اگر (chl->nb_channels != chl1->nb_channels)
        واپس 1;

    /* if only one is unspecified -> not equal */
    اگر ((chl->ترتیب  == AV_CHANNEL_ترتیب_UNSPEC) !=
        (chl1->ترتیب == AV_CHANNEL_ترتیب_UNSPEC))
        واپس 1;
    /* both are unspecified -> equal */
    ورنہ اگر (chl->ترتیب == AV_CHANNEL_ترتیب_UNSPEC)
        واپس 0;

    /* can compare masks directly */
    اگر ((chl->ترتیب == AV_CHANNEL_ترتیب_NATIVE ||
         chl->ترتیب == AV_CHANNEL_ترتیب_AMBISONIC) &&
        chl->ترتیب == chl1->ترتیب)
        واپس chl->u.نقاب_2 != chl1->u.نقاب_2;

    /* compare channel by channel */
    برائے (i = 0; i < chl->nb_channels; i++)
        اگر (av_channel_layout_channel_from_اشاریہ(chl,  i) !=
            av_channel_layout_channel_from_اشاریہ(chl1, i))
            واپس 1;
    واپس 0;
}

خالی av_channel_layout_default(AVChannelLayout *ch_layout, صحیح nb_channels)
{
    صحیح i;
    برائے (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        اگر (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            واپس;
        }

    ch_layout->ترتیب       = AV_CHANNEL_ترتیب_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

ثابت AVChannelLayout *av_channel_layout_standard(خالی **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ثابت AVChannelLayout *ch_layout = تہی;

    اگر (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (خالی*)(i + 1);
    }

    واپس ch_layout;
}

uint64_t av_channel_layout_subset(ثابت AVChannelLayout *channel_layout,
                                  uint64_t نقاب_2)
{
    uint64_t ret = 0;
    صحیح i;

    انتخاب (channel_layout->ترتیب) {
    حالت AV_CHANNEL_ترتیب_NATIVE:
    حالت AV_CHANNEL_ترتیب_AMBISONIC:
        واپس channel_layout->u.نقاب_2 & نقاب_2;
    حالت AV_CHANNEL_ترتیب_CUSTOM:
        برائے (i = 0; i < 64; i++)
            اگر (نقاب_2 & (1ULL << i) && av_channel_layout_اشاریہ_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        توڑو;
    }

    واپس ret;
}

صحیح av_channel_layout_retype(AVChannelLayout *channel_layout, شمار AVChannel_ترتیب ترتیب, صحیح flags)
{
    صحیح allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    صحیح lossy;

    اگر (!av_channel_layout_check(channel_layout))
        واپس AVERROR(EINVAL);

    اگر (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        ترتیب = canonical_ترتیب(channel_layout);

    اگر (channel_layout->ترتیب == ترتیب)
        واپس 0;

    انتخاب (ترتیب) {
    حالت AV_CHANNEL_ترتیب_UNSPEC: {
        صحیح nb_channels = channel_layout->nb_channels;
        اگر (channel_layout->ترتیب == AV_CHANNEL_ترتیب_CUSTOM) {
            lossy = 0;
            برائے (صحیح i = 0; i < nb_channels; i++) {
                اگر (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    توڑو;
                }
            }
        } ورنہ {
            lossy = 1;
        }
        اگر (!lossy || allow_lossy) {
            خالی *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->ترتیب       = AV_CHANNEL_ترتیب_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            واپس lossy;
        }
        واپس AVERROR(ENOSYS);
        }
    حالت AV_CHANNEL_ترتیب_NATIVE:
        اگر (channel_layout->ترتیب == AV_CHANNEL_ترتیب_CUSTOM) {
            int64_t نقاب_2 = masked_description(channel_layout, 0);
            اگر (نقاب_2 < 0)
                واپس AVERROR(ENOSYS);
            lossy = has_channel_نام(channel_layout);
            اگر (!lossy || allow_lossy) {
                خالی *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_نقاب(channel_layout, نقاب_2);
                channel_layout->opaque = opaque;
                واپس lossy;
            }
        }
        واپس AVERROR(ENOSYS);
    حالت AV_CHANNEL_ترتیب_CUSTOM: {
        AVChannelLayout custom = { 0 };
        صحیح ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        خالی *opaque = channel_layout->opaque;
        اگر (ret < 0)
            واپس ret;
        اگر (channel_layout->ترتیب != AV_CHANNEL_ترتیب_UNSPEC)
            برائے (صحیح i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_اشاریہ(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        واپس 0;
        }
    حالت AV_CHANNEL_ترتیب_AMBISONIC:
        اگر (channel_layout->ترتیب == AV_CHANNEL_ترتیب_CUSTOM) {
            int64_t نقاب_2;
            صحیح nb_channels = channel_layout->nb_channels;
            صحیح amb_ترتیب = av_channel_layout_ambisonic_ترتیب(channel_layout);
            اگر (amb_ترتیب < 0)
                واپس AVERROR(ENOSYS);
            نقاب_2 = masked_description(channel_layout, (amb_ترتیب + 1) * (amb_ترتیب + 1));
            اگر (نقاب_2 < 0)
                واپس AVERROR(ENOSYS);
            lossy = has_channel_نام(channel_layout);
            اگر (!lossy || allow_lossy) {
                خالی *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->ترتیب       = AV_CHANNEL_ترتیب_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.نقاب_2      = نقاب_2;
                channel_layout->opaque      = opaque;
                واپس lossy;
            }
        }
        واپس AVERROR(ENOSYS);
    طےشدہ:
        واپس AVERROR(EINVAL);
    }
}
