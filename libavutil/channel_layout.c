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

#ضمن <stdint.h>
#ضمن <stdlib.h>
#ضمن <string.h>

#ضمن "avassert.h"
#ضمن "channel_layout.h"
#ضمن "bprint.h"
#ضمن "common.h"
#ضمن "error.h"
#ضمن "attributes.h"
#ضمن "macros.h"
#ضمن "mem.h"
#ضمن "opt.h"

#تعریف_کړه CHAN_IS_AMBI(x) ((x) >= AV_CHAN_AMBISONIC_بنسټ &&\
                         (x) <= AV_CHAN_AMBISONIC_پای_ټکی)

بنية channel_name {
    ثابت حرف *name;
    ثابت حرف *description;
};

ساكن ثابت بنية channel_name channel_نومونه[] = {
    [AV_CHAN_FRONT_کیڼ           ] = { "FL",        "front left"            },
    [AV_CHAN_FRONT_ښی          ] = { "FR",        "front right"           },
    [AV_CHAN_FRONT_CENTER         ] = { "FC",        "front center"          },
    [AV_CHAN_ټیټ_FREQUENCY        ] = { "LFE",       "low frequency"         },
    [AV_CHAN_شا_کیڼ            ] = { "BL",        "back left"             },
    [AV_CHAN_شا_ښی           ] = { "BR",        "back right"            },
    [AV_CHAN_FRONT_کیڼ_د_CENTER ] = { "FLC",       "front left-of-center"  },
    [AV_CHAN_FRONT_ښی_د_CENTER] = { "FRC",       "front right-of-center" },
    [AV_CHAN_شا_CENTER          ] = { "BC",        "back center"           },
    [AV_CHAN_SIDE_کیڼ            ] = { "SL",        "side left"             },
    [AV_CHAN_SIDE_ښی           ] = { "SR",        "side right"            },
    [AV_CHAN_سر_CENTER           ] = { "TC",        "top center"            },
    [AV_CHAN_سر_FRONT_کیڼ       ] = { "TFL",       "top front left"        },
    [AV_CHAN_سر_FRONT_CENTER     ] = { "TFC",       "top front center"      },
    [AV_CHAN_سر_FRONT_ښی      ] = { "TFR",       "top front right"       },
    [AV_CHAN_سر_شا_کیڼ        ] = { "TBL",       "top back left"         },
    [AV_CHAN_سر_شا_CENTER      ] = { "TBC",       "top back center"       },
    [AV_CHAN_سر_شا_ښی       ] = { "TBR",       "top back right"        },
    [AV_CHAN_STEREO_کیڼ          ] = { "DL",        "downmix left"          },
    [AV_CHAN_STEREO_ښی         ] = { "DR",        "downmix right"         },
    [AV_CHAN_WIDE_کیڼ            ] = { "WL",        "wide left"             },
    [AV_CHAN_WIDE_ښی           ] = { "WR",        "wide right"            },
    [AV_CHAN_SURROUND_مستقیم_کیڼ ] = { "SDL",       "surround direct left"  },
    [AV_CHAN_SURROUND_مستقیم_ښی] = { "SDR",       "surround direct right" },
    [AV_CHAN_ټیټ_FREQUENCY_2      ] = { "LFE2",      "low frequency 2"       },
    [AV_CHAN_سر_SIDE_کیڼ        ] = { "TSL",       "top side left"         },
    [AV_CHAN_سر_SIDE_ښی       ] = { "TSR",       "top side right"        },
    [AV_CHAN_BOTTOM_FRONT_CENTER  ] = { "BFC",       "bottom front center"   },
    [AV_CHAN_BOTTOM_FRONT_کیڼ    ] = { "BFL",       "bottom front left"     },
    [AV_CHAN_BOTTOM_FRONT_ښی   ] = { "BFR",       "bottom front right"    },
    [AV_CHAN_SIDE_SURROUND_کیڼ   ] = { "SSL",       "side surround left"    },
    [AV_CHAN_SIDE_SURROUND_ښی  ] = { "SSR",       "side surround right"   },
    [AV_CHAN_سر_SURROUND_کیڼ    ] = { "TTL",       "top surround left"     },
    [AV_CHAN_سر_SURROUND_ښی   ] = { "TTR",       "top surround right"    },
    [AV_CHAN_BINAURAL_کیڼ        ] = { "BIL",       "binaural left"         },
    [AV_CHAN_BINAURAL_ښی       ] = { "BIR",       "binaural right"        },
};

فراغ av_channel_name_bprint(AVBPrint *bp, تعداد AVChannel channel_id)
{
    إذا (channel_id >= AV_CHAN_AMBISONIC_بنسټ &&
        channel_id <= AV_CHAN_AMBISONIC_پای_ټکی)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_بنسټ);
    وإلا إذا ((بینښه)channel_id < FF_ARRAY_ELEMS(channel_نومونه) &&
             channel_نومونه[channel_id].name)
        av_bprintf(bp, "%s", channel_نومونه[channel_id].name);
    وإلا إذا (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    وإلا إذا (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    وإلا إذا (channel_id == AV_CHAN_ناکارول_شوی)
        av_bprintf(bp, "UNSD");
    وإلا
        av_bprintf(bp, "USR%d", channel_id);
}

صحيح av_channel_name(حرف *buf, size_t buf_اندازه, تعداد AVChannel channel_id)
{
    AVBPrint bp;

    إذا (!buf && buf_اندازه)
        أرجع AVERROR(EINVAL);

    av_bprint_init_for_بفر(&bp, buf, buf_اندازه);
    av_channel_name_bprint(&bp, channel_id);

    إذا (bp.len >= لوی_عدد)
        أرجع AVERROR(ERANGE);
    أرجع bp.len + 1;
}

فراغ av_channel_description_bprint(AVBPrint *bp, تعداد AVChannel channel_id)
{
    إذا (channel_id >= AV_CHAN_AMBISONIC_بنسټ &&
        channel_id <= AV_CHAN_AMBISONIC_پای_ټکی)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_بنسټ);
    وإلا إذا ((بینښه)channel_id < FF_ARRAY_ELEMS(channel_نومونه) &&
             channel_نومونه[channel_id].description)
        av_bprintf(bp, "%s", channel_نومونه[channel_id].description);
    وإلا إذا (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    وإلا إذا (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    وإلا إذا (channel_id == AV_CHAN_ناکارول_شوی)
        av_bprintf(bp, "unused");
    وإلا
        av_bprintf(bp, "user %d", channel_id);
}

صحيح av_channel_description(حرف *buf, size_t buf_اندازه, تعداد AVChannel channel_id)
{
    AVBPrint bp;

    إذا (!buf && buf_اندازه)
        أرجع AVERROR(EINVAL);

    av_bprint_init_for_بفر(&bp, buf, buf_اندازه);
    av_channel_description_bprint(&bp, channel_id);

    إذا (bp.len >= لوی_عدد)
        أرجع AVERROR(ERANGE);
    أرجع bp.len + 1;
}

تعداد AVChannel av_channel_from_string(ثابت حرف *str)
{
    صحيح i;
    حرف *endptr = (حرف *)str;
    تعداد AVChannel id = AV_CHAN_NONE;

    إذا (!مزي_پرتله(str, "AMBI", 4)) {
        i = strtol(str + 4, عدم, 0);
        إذا (i < 0 || i > AV_CHAN_AMBISONIC_پای_ټکی - AV_CHAN_AMBISONIC_بنسټ)
            أرجع AV_CHAN_NONE;
        أرجع AV_CHAN_AMBISONIC_بنسټ + i;
    }

    لكل (i = 0; i < FF_ARRAY_ELEMS(channel_نومونه); i++) {
        إذا (channel_نومونه[i].name && !strcmp(str, channel_نومونه[i].name))
            أرجع i;
    }
    إذا (!strcmp(str, "UNK"))
        أرجع AV_CHAN_UNKNOWN;
    إذا (!strcmp(str, "UNSD"))
        أرجع AV_CHAN_ناکارول_شوی;

    إذا (!مزي_پرتله(str, "USR", 3)) {
        ثابت حرف *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    إذا (id >= 0 && !*endptr)
        أرجع id;

    أرجع AV_CHAN_NONE;
}

بنية channel_layout_name {
    ثابت حرف *name;
    AVChannelLayout layout;
};

ساكن ثابت بنية channel_layout_name channel_layout_map[] = {
    { "mono",           AV_CHANNEL_LAYOUT_MONO                },
    { "stereo",         AV_CHANNEL_LAYOUT_STEREO              },
    { "2.1",            AV_CHANNEL_LAYOUT_2POINT1             },
    { "3.0",            AV_CHANNEL_LAYOUT_SURROUND            },
    { "3.0(back)",      AV_CHANNEL_LAYOUT_2_1                 },
    { "4.0",            AV_CHANNEL_LAYOUT_4POINT0             },
    { "quad",           AV_CHANNEL_LAYOUT_QUAD                },
    { "quad(side)",     AV_CHANNEL_LAYOUT_2_2                 },
    { "3.1",            AV_CHANNEL_LAYOUT_3POINT1             },
    { "5.0",            AV_CHANNEL_LAYOUT_5_POINT0_شا        },
    { "5.0(side)",      AV_CHANNEL_LAYOUT_5POINT0             },
    { "4.1",            AV_CHANNEL_LAYOUT_4POINT1             },
    { "5.1",            AV_CHANNEL_LAYOUT_5_POINT1_شا        },
    { "5.1(side)",      AV_CHANNEL_LAYOUT_5POINT1             },
    { "6.0",            AV_CHANNEL_LAYOUT_6POINT0             },
    { "6.0(front)",     AV_CHANNEL_LAYOUT_6POINT0_FRONT       },
    { "3.1.2",          AV_CHANNEL_LAYOUT_3POINT1POINT2       },
    { "hexagonal",      AV_CHANNEL_LAYOUT_HEXAGONAL           },
    { "6.1",            AV_CHANNEL_LAYOUT_6POINT1             },
    { "6.1(back)",      AV_CHANNEL_LAYOUT_6_POINT1_شا        },
    { "6.1(front)",     AV_CHANNEL_LAYOUT_6POINT1_FRONT       },
    { "7.0",            AV_CHANNEL_LAYOUT_7POINT0             },
    { "7.0(front)",     AV_CHANNEL_LAYOUT_7POINT0_FRONT       },
    { "7.1",            AV_CHANNEL_LAYOUT_7POINT1             },
    { "7.1(wide)",      AV_CHANNEL_LAYOUT_7_POINT1_WIDE_شا   },
    { "7.1(wide-side)", AV_CHANNEL_LAYOUT_7POINT1_WIDE        },
    { "5.1.2",          AV_CHANNEL_LAYOUT_5POINT1POINT2       },
    { "5.1.2(back)",    AV_CHANNEL_LAYOUT_5_POINT1_POINT2_شا  },
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

صحيح av_channel_layout_custom_init(AVChannelLayout *channel_layout, صحيح nb_channels)
{
    AVChannelCustom *map;

    إذا (nb_channels <= 0)
        أرجع AVERROR(EINVAL);

    map = av_calloc(nb_channels, حجم(*channel_layout->u.map));
    إذا (!map)
        أرجع AVERROR(ENOMEM);
    لكل (صحيح i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->ترتیب       = AV_CHANNEL_ترتیب_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    أرجع 0;
}

صحيح av_channel_layout_from_ماسک(AVChannelLayout *channel_layout,
                                uint64_t ماسک_2)
{
    إذا (!ماسک_2)
        أرجع AVERROR(EINVAL);

    channel_layout->ترتیب       = AV_CHANNEL_ترتیب_NATIVE;
    channel_layout->nb_channels = av_popcount64(ماسک_2);
    channel_layout->u.ماسک_2      = ماسک_2;

    أرجع 0;
}

ساكن صحيح parse_channel_list(AVChannelLayout *ch_layout, ثابت حرف *str)
{
    صحيح ret;
    صحيح nb_channels = 0;
    AVChannelCustom *map = عدم;
    AVChannelCustom custom = {0};

    طالما (*str) {
        حرف *channel, *chname;
        ret = av_opt_get_کلی_ارزښت(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_کلی, &channel, &chname);
        إذا (ret < 0) {
            av_freep(&map);
            أرجع ret;
        }
        إذا (*str)
            str++; // skip separator
        إذا (!channel) {
            channel = chname;
            chname = عدم;
        }
        av_strlcpy(custom.name, chname ? chname : "", حجم(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        إذا (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            أرجع AVERROR(EINVAL);
        }

        av_dynarray2_جمع_کړه((فراغ **)&map, &nb_channels, حجم(custom), (فراغ *)&custom);
        إذا (!map)
            أرجع AVERROR(ENOMEM);
    }

    إذا (!nb_channels)
        أرجع AVERROR(EINVAL);

    ch_layout->ترتیب = AV_CHANNEL_ترتیب_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    أرجع 0;
}

صحيح av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  ثابت حرف *str)
{
    صحيح i, matches, ret;
    صحيح channels = 0, nb_channels = 0;
    حرف *chlist, *پای_ټکی;
    uint64_t ماسک_2 = 0;

    /* channel layout names */
    لكل (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        إذا (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            أرجع 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, حجم(*channel_layout));

    /* ambisonic */
    إذا (!مزي_پرتله(str, "ambisonic ", 10)) {
        ثابت حرف *p = str + 10;
        حرف *endptr;
        AVChannelLayout extra = {0};
        صحيح ترتیب;

        ترتیب = strtol(p, &endptr, 0);
        إذا (ترتیب < 0 || ترتیب + 1  > لوی_عدد / (ترتیب + 1) ||
            (*endptr && *endptr != '+'))
            أرجع AVERROR(EINVAL);

        channel_layout->ترتیب       = AV_CHANNEL_ترتیب_AMBISONIC;
        channel_layout->nb_channels = (ترتیب + 1) * (ترتیب + 1);

        إذا (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            إذا (ret < 0)
                أرجع ret;
            إذا (extra.nb_channels >= لوی_عدد - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                أرجع AVERROR(EINVAL);
            }

            إذا (extra.ترتیب == AV_CHANNEL_ترتیب_NATIVE) {
                channel_layout->u.ماسک_2 = extra.u.ماسک_2;
            } وإلا {
                channel_layout->ترتیب = AV_CHANNEL_ترتیب_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              حجم(*channel_layout->u.map));
                إذا (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    أرجع AVERROR(ENOMEM);
                }

                لكل (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_بنسټ + i;
                لكل (i = 0; i < extra.nb_channels; i++) {
                    تعداد AVChannel ch = av_channel_layout_channel_from_شاخص(&extra, i);
                    إذا (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        أرجع AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    إذا (extra.ترتیب == AV_CHANNEL_ترتیب_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   حجم(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        أرجع 0;
    }

    chlist = av_strdup(str);
    إذا (!chlist)
        أرجع AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    إذا (ret < 0 && ret != AVERROR(EINVAL))
        أرجع ret;

    إذا (ret >= 0) {
        ثابت حرف *پای_ټکی_par = strchr(str, ')');
        إذا (matches == 2 && (nb_channels != channel_layout->nb_channels || !پای_ټکی_par || *++پای_ټکی_par)) {
            av_channel_layout_uninit(channel_layout);
            أرجع AVERROR(EINVAL);
        }
        أرجع 0;
    }

    errno = 0;
    ماسک_2 = strtoull(str, &پای_ټکی, 0);

    /* channel layout mask */
    إذا (!errno && !*پای_ټکی && !strchr(str, '-') && ماسک_2) {
        av_channel_layout_from_ماسک(channel_layout, ماسک_2);
        أرجع 0;
    }

    errno = 0;
    channels = strtol(str, &پای_ټکی, 10);

    /* number of channels */
    إذا (!errno && !strcmp(پای_ټکی, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        إذا (channel_layout->ترتیب == AV_CHANNEL_ترتیب_NATIVE)
            أرجع 0;
    }

    /* number of unordered channels */
    إذا (!errno && (!strcmp(پای_ټکی, "C") || !strcmp(پای_ټکی, " channels"))
        && channels > 0) {
        channel_layout->ترتیب = AV_CHANNEL_ترتیب_UNSPEC;
        channel_layout->nb_channels = channels;
        أرجع 0;
    }

    أرجع AVERROR(EINVAL);
}

فراغ av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    إذا (channel_layout->ترتیب == AV_CHANNEL_ترتیب_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, حجم(*channel_layout));
}

صحيح av_channel_layout_copy(AVChannelLayout *dst, ثابت AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    إذا (src->ترتیب == AV_CHANNEL_ترتیب_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, حجم(*dst->u.map));
        إذا (!dst->u.map)
            أرجع AVERROR(ENOMEM);
        حافظه_نقل(dst->u.map, src->u.map, src->nb_channels * حجم(*src->u.map));
    }
    أرجع 0;
}

ساكن int64_t masked_description(ثابت AVChannelLayout *channel_layout, صحيح پیل_channel)
{
    uint64_t ماسک_2 = 0;
    لكل (صحيح i = پیل_channel; i < channel_layout->nb_channels; i++) {
        تعداد AVChannel ch = channel_layout->u.map[i].id;
        إذا (ch >= 0 && ch < 63 && ماسک_2 < (1ULL << ch))
            ماسک_2 |= (1ULL << ch);
        وإلا
            أرجع AVERROR(EINVAL);
    }
    أرجع ماسک_2;
}

ساكن صحيح has_channel_نومونه(ثابت AVChannelLayout *channel_layout)
{
    إذا (channel_layout->ترتیب != AV_CHANNEL_ترتیب_CUSTOM)
        أرجع 0;
    لكل (صحيح i = 0; i < channel_layout->nb_channels; i++)
        إذا (channel_layout->u.map[i].name[0])
            أرجع 1;
    أرجع 0;
}

صحيح av_channel_layout_ambisonic_ترتیب(ثابت AVChannelLayout *channel_layout)
{
    صحيح i, highest_ambi, ترتیب;

    إذا (channel_layout->ترتیب != AV_CHANNEL_ترتیب_AMBISONIC &&
        channel_layout->ترتیب != AV_CHANNEL_ترتیب_CUSTOM)
        أرجع AVERROR(EINVAL);

    highest_ambi = -1;
    إذا (channel_layout->ترتیب == AV_CHANNEL_ترتیب_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.ماسک_2) - 1;
    وإلا {
        ثابت AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->ترتیب == AV_CHANNEL_ترتیب_CUSTOM);

        لكل (i = 0; i < channel_layout->nb_channels; i++) {
            صحيح is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            إذا (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                أرجع AVERROR(EINVAL);

            /* non-default ordering */
            إذا (is_ambi && map[i].id - AV_CHAN_AMBISONIC_بنسټ != i)
                أرجع AVERROR(EINVAL);

            إذا (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    إذا (highest_ambi < 0)
        أرجع AVERROR(EINVAL);

    ترتیب = floor(جذر(highest_ambi));
    /* incomplete order - some harmonics are missing */
    إذا ((ترتیب + 1) * (ترتیب + 1) != highest_ambi + 1)
        أرجع AVERROR(EINVAL);

    أرجع ترتیب;
}

ساكن تعداد AVChannel_ترتیب canonical_ترتیب(AVChannelLayout *channel_layout)
{
    صحيح has_معلوم_channel = 0;
    صحيح ترتیب;

    إذا (channel_layout->ترتیب != AV_CHANNEL_ترتیب_CUSTOM)
        أرجع channel_layout->ترتیب;

    إذا (has_channel_نومونه(channel_layout))
        أرجع AV_CHANNEL_ترتیب_CUSTOM;

    لكل (صحيح i = 0; i < channel_layout->nb_channels && !has_معلوم_channel; i++)
        إذا (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_معلوم_channel = 1;
    إذا (!has_معلوم_channel)
        أرجع AV_CHANNEL_ترتیب_UNSPEC;

    إذا (masked_description(channel_layout, 0) > 0)
        أرجع AV_CHANNEL_ترتیب_NATIVE;

    ترتیب = av_channel_layout_ambisonic_ترتیب(channel_layout);
    إذا (ترتیب >= 0 && masked_description(channel_layout, (ترتیب + 1) * (ترتیب + 1)) >= 0)
        أرجع AV_CHANNEL_ترتیب_AMBISONIC;

    أرجع AV_CHANNEL_ترتیب_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
ساكن صحيح try_describe_ambisonic(AVBPrint *bp, ثابت AVChannelLayout *channel_layout)
{
    صحيح nb_ambi_channels;
    صحيح ترتیب = av_channel_layout_ambisonic_ترتیب(channel_layout);
    إذا (ترتیب < 0)
        أرجع ترتیب;

    av_bprintf(bp, "ambisonic %d", ترتیب);

    /* extra channels present */
    nb_ambi_channels = (ترتیب + 1) * (ترتیب + 1);
    إذا (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        إذا (channel_layout->ترتیب == AV_CHANNEL_ترتیب_AMBISONIC) {
            extra.ترتیب       = AV_CHANNEL_ترتیب_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.ماسک_2);
            extra.u.ماسک_2      = channel_layout->u.ماسک_2;
        } وإلا {
            int64_t ماسک_2;
            إذا (!has_channel_نومونه(channel_layout) &&
                (ماسک_2 = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.ترتیب       = AV_CHANNEL_ترتیب_NATIVE;
                extra.nb_channels = av_popcount64(ماسک_2);
                extra.u.ماسک_2      = ماسک_2;
            } وإلا {
                extra.ترتیب       = AV_CHANNEL_ترتیب_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    أرجع 0;
}

صحيح av_channel_layout_describe_bprint(ثابت AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    صحيح i;

    بدل (channel_layout->ترتیب) {
    حالة AV_CHANNEL_ترتیب_NATIVE:
        لكل (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            إذا (channel_layout->u.ماسک_2 == channel_layout_map[i].layout.u.ماسک_2) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                أرجع 0;
            }
        av_fallthrough;
    حالة AV_CHANNEL_ترتیب_CUSTOM:
        إذا (channel_layout->ترتیب == AV_CHANNEL_ترتیب_CUSTOM) {
            int64_t ماسک_2;
            صحيح res = try_describe_ambisonic(bp, channel_layout);
            إذا (res >= 0)
                أرجع 0;
            إذا (!has_channel_نومونه(channel_layout) &&
                (ماسک_2 = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .ترتیب       = AV_CHANNEL_ترتیب_NATIVE,
                                           .nb_channels = av_popcount64(ماسک_2),
                                           .u.ماسک_2      = ماسک_2 };
                أرجع av_channel_layout_describe_bprint(&native, bp);
            }
        }
        إذا (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        لكل (i = 0; i < channel_layout->nb_channels; i++) {
            تعداد AVChannel ch = av_channel_layout_channel_from_شاخص(channel_layout, i);

            إذا (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            إذا (channel_layout->ترتیب == AV_CHANNEL_ترتیب_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        إذا (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            أرجع 0;
        }
        av_fallthrough;
    حالة AV_CHANNEL_ترتیب_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        أرجع 0;
    حالة AV_CHANNEL_ترتیب_AMBISONIC:
        أرجع try_describe_ambisonic(bp, channel_layout);
    افتراضي:
        أرجع AVERROR(EINVAL);
    }
}

صحيح av_channel_layout_describe(ثابت AVChannelLayout *channel_layout,
                               حرف *buf, size_t buf_اندازه)
{
    AVBPrint bp;
    صحيح ret;

    إذا (!buf && buf_اندازه)
        أرجع AVERROR(EINVAL);

    av_bprint_init_for_بفر(&bp, buf, buf_اندازه);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    إذا (ret < 0)
        أرجع ret;

    إذا (bp.len >= لوی_عدد)
        أرجع AVERROR(ERANGE);
    أرجع bp.len + 1;
}

تعداد AVChannel
av_channel_layout_channel_from_شاخص(ثابت AVChannelLayout *channel_layout,
                                     بینښه صحيح idx)
{
    صحيح i;

    إذا (idx >= channel_layout->nb_channels)
        أرجع AV_CHAN_NONE;

    بدل (channel_layout->ترتیب) {
    حالة AV_CHANNEL_ترتیب_CUSTOM:
        أرجع channel_layout->u.map[idx].id;
    حالة AV_CHANNEL_ترتیب_AMBISONIC: {
        صحيح ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.ماسک_2);
        إذا (idx < ambi_channels)
            أرجع AV_CHAN_AMBISONIC_بنسټ + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    حالة AV_CHANNEL_ترتیب_NATIVE:
        لكل (i = 0; i < 64; i++) {
            إذا ((1ULL << i) & channel_layout->u.ماسک_2 && !idx--)
                أرجع i;
        }
        av_fallthrough;
    افتراضي:
        أرجع AV_CHAN_NONE;
    }
}

تعداد AVChannel
av_channel_layout_channel_from_string(ثابت AVChannelLayout *channel_layout,
                                      ثابت حرف *str)
{
    صحيح شاخص = av_channel_layout_شاخص_from_string(channel_layout, str);

    إذا (شاخص < 0)
        أرجع AV_CHAN_NONE;

    أرجع av_channel_layout_channel_from_شاخص(channel_layout, شاخص);
}

صحيح av_channel_layout_شاخص_from_channel(ثابت AVChannelLayout *channel_layout,
                                         تعداد AVChannel channel)
{
    صحيح i;

    إذا (channel == AV_CHAN_NONE)
        أرجع AVERROR(EINVAL);

    بدل (channel_layout->ترتیب) {
    حالة AV_CHANNEL_ترتیب_CUSTOM:
        لكل (i = 0; i < channel_layout->nb_channels; i++)
            إذا (channel_layout->u.map[i].id == channel)
                أرجع i;
        أرجع AVERROR(EINVAL);
    حالة AV_CHANNEL_ترتیب_AMBISONIC:
    حالة AV_CHANNEL_ترتیب_NATIVE: {
        uint64_t ماسک_2 = channel_layout->u.ماسک_2;
        صحيح ambi_channels = channel_layout->nb_channels - av_popcount64(ماسک_2);
        إذا (channel_layout->ترتیب == AV_CHANNEL_ترتیب_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_بنسټ) {
            إذا (channel - AV_CHAN_AMBISONIC_بنسټ >= ambi_channels)
                أرجع AVERROR(EINVAL);
            أرجع channel - AV_CHAN_AMBISONIC_بنسټ;
        }
        إذا ((بینښه)channel > 63 || !(ماسک_2 & (1ULL << channel)))
            أرجع AVERROR(EINVAL);
        ماسک_2 &= (1ULL << channel) - 1;
        أرجع av_popcount64(ماسک_2) + ambi_channels;
        }
    افتراضي:
        أرجع AVERROR(EINVAL);
    }
}

صحيح av_channel_layout_شاخص_from_string(ثابت AVChannelLayout *channel_layout,
                                        ثابت حرف *str)
{
    ثابت حرف *chname;
    تعداد AVChannel ch = AV_CHAN_NONE;

    بدل (channel_layout->ترتیب) {
    حالة AV_CHANNEL_ترتیب_CUSTOM:
        chname = مزي_پلټنه(str, "@");
        إذا (chname) {
            حرف buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(حجم(buf), chname - str));
            إذا (!*chname)
                chname = عدم;
            ch = av_channel_from_string(buf);
            إذا (ch == AV_CHAN_NONE && *buf)
                أرجع AVERROR(EINVAL);
        }
        لكل (صحيح i = 0; chname && i < channel_layout->nb_channels; i++) {
            إذا (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                أرجع i;
        }
        av_fallthrough;
    حالة AV_CHANNEL_ترتیب_AMBISONIC:
    حالة AV_CHANNEL_ترتیب_NATIVE:
        ch = av_channel_from_string(str);
        إذا (ch == AV_CHAN_NONE)
            أرجع AVERROR(EINVAL);
        أرجع av_channel_layout_شاخص_from_channel(channel_layout, ch);
    }

    أرجع AVERROR(EINVAL);
}

صحيح av_channel_layout_check(ثابت AVChannelLayout *channel_layout)
{
    إذا (channel_layout->nb_channels <= 0)
        أرجع 0;

    بدل (channel_layout->ترتیب) {
    حالة AV_CHANNEL_ترتیب_NATIVE:
        أرجع av_popcount64(channel_layout->u.ماسک_2) == channel_layout->nb_channels;
    حالة AV_CHANNEL_ترتیب_CUSTOM:
        إذا (!channel_layout->u.map)
            أرجع 0;
        لكل (صحيح i = 0; i < channel_layout->nb_channels; i++) {
            إذا (channel_layout->u.map[i].id == AV_CHAN_NONE)
                أرجع 0;
        }
        أرجع 1;
    حالة AV_CHANNEL_ترتیب_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        أرجع av_popcount64(channel_layout->u.ماسک_2) < channel_layout->nb_channels;
    حالة AV_CHANNEL_ترتیب_UNSPEC:
        أرجع 1;
    افتراضي:
        أرجع 0;
    }
}

صحيح av_channel_layout_compare(ثابت AVChannelLayout *chl, ثابت AVChannelLayout *chl1)
{
    صحيح i;

    /* different channel counts -> not equal */
    إذا (chl->nb_channels != chl1->nb_channels)
        أرجع 1;

    /* if only one is unspecified -> not equal */
    إذا ((chl->ترتیب  == AV_CHANNEL_ترتیب_UNSPEC) !=
        (chl1->ترتیب == AV_CHANNEL_ترتیب_UNSPEC))
        أرجع 1;
    /* both are unspecified -> equal */
    وإلا إذا (chl->ترتیب == AV_CHANNEL_ترتیب_UNSPEC)
        أرجع 0;

    /* can compare masks directly */
    إذا ((chl->ترتیب == AV_CHANNEL_ترتیب_NATIVE ||
         chl->ترتیب == AV_CHANNEL_ترتیب_AMBISONIC) &&
        chl->ترتیب == chl1->ترتیب)
        أرجع chl->u.ماسک_2 != chl1->u.ماسک_2;

    /* compare channel by channel */
    لكل (i = 0; i < chl->nb_channels; i++)
        إذا (av_channel_layout_channel_from_شاخص(chl,  i) !=
            av_channel_layout_channel_from_شاخص(chl1, i))
            أرجع 1;
    أرجع 0;
}

فراغ av_channel_layout_default(AVChannelLayout *ch_layout, صحيح nb_channels)
{
    صحيح i;
    لكل (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        إذا (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            أرجع;
        }

    ch_layout->ترتیب       = AV_CHANNEL_ترتیب_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

ثابت AVChannelLayout *av_channel_layout_standard(فراغ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ثابت AVChannelLayout *ch_layout = عدم;

    إذا (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (فراغ*)(i + 1);
    }

    أرجع ch_layout;
}

uint64_t av_channel_layout_subset(ثابت AVChannelLayout *channel_layout,
                                  uint64_t ماسک_2)
{
    uint64_t ret = 0;
    صحيح i;

    بدل (channel_layout->ترتیب) {
    حالة AV_CHANNEL_ترتیب_NATIVE:
    حالة AV_CHANNEL_ترتیب_AMBISONIC:
        أرجع channel_layout->u.ماسک_2 & ماسک_2;
    حالة AV_CHANNEL_ترتیب_CUSTOM:
        لكل (i = 0; i < 64; i++)
            إذا (ماسک_2 & (1ULL << i) && av_channel_layout_شاخص_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        اكسر;
    }

    أرجع ret;
}

صحيح av_channel_layout_retype(AVChannelLayout *channel_layout, تعداد AVChannel_ترتیب ترتیب, صحيح flags)
{
    صحيح allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    صحيح lossy;

    إذا (!av_channel_layout_check(channel_layout))
        أرجع AVERROR(EINVAL);

    إذا (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        ترتیب = canonical_ترتیب(channel_layout);

    إذا (channel_layout->ترتیب == ترتیب)
        أرجع 0;

    بدل (ترتیب) {
    حالة AV_CHANNEL_ترتیب_UNSPEC: {
        صحيح nb_channels = channel_layout->nb_channels;
        إذا (channel_layout->ترتیب == AV_CHANNEL_ترتیب_CUSTOM) {
            lossy = 0;
            لكل (صحيح i = 0; i < nb_channels; i++) {
                إذا (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    اكسر;
                }
            }
        } وإلا {
            lossy = 1;
        }
        إذا (!lossy || allow_lossy) {
            فراغ *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->ترتیب       = AV_CHANNEL_ترتیب_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            أرجع lossy;
        }
        أرجع AVERROR(ENOSYS);
        }
    حالة AV_CHANNEL_ترتیب_NATIVE:
        إذا (channel_layout->ترتیب == AV_CHANNEL_ترتیب_CUSTOM) {
            int64_t ماسک_2 = masked_description(channel_layout, 0);
            إذا (ماسک_2 < 0)
                أرجع AVERROR(ENOSYS);
            lossy = has_channel_نومونه(channel_layout);
            إذا (!lossy || allow_lossy) {
                فراغ *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_ماسک(channel_layout, ماسک_2);
                channel_layout->opaque = opaque;
                أرجع lossy;
            }
        }
        أرجع AVERROR(ENOSYS);
    حالة AV_CHANNEL_ترتیب_CUSTOM: {
        AVChannelLayout custom = { 0 };
        صحيح ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        فراغ *opaque = channel_layout->opaque;
        إذا (ret < 0)
            أرجع ret;
        إذا (channel_layout->ترتیب != AV_CHANNEL_ترتیب_UNSPEC)
            لكل (صحيح i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_شاخص(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        أرجع 0;
        }
    حالة AV_CHANNEL_ترتیب_AMBISONIC:
        إذا (channel_layout->ترتیب == AV_CHANNEL_ترتیب_CUSTOM) {
            int64_t ماسک_2;
            صحيح nb_channels = channel_layout->nb_channels;
            صحيح amb_ترتیب = av_channel_layout_ambisonic_ترتیب(channel_layout);
            إذا (amb_ترتیب < 0)
                أرجع AVERROR(ENOSYS);
            ماسک_2 = masked_description(channel_layout, (amb_ترتیب + 1) * (amb_ترتیب + 1));
            إذا (ماسک_2 < 0)
                أرجع AVERROR(ENOSYS);
            lossy = has_channel_نومونه(channel_layout);
            إذا (!lossy || allow_lossy) {
                فراغ *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->ترتیب       = AV_CHANNEL_ترتیب_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.ماسک_2      = ماسک_2;
                channel_layout->opaque      = opaque;
                أرجع lossy;
            }
        }
        أرجع AVERROR(ENOSYS);
    افتراضي:
        أرجع AVERROR(EINVAL);
    }
}
