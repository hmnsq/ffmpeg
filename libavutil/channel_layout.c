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

#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "channel_layout.h"
#અન્તર્ભાવ "bprint.h"
#અન્તર્ભાવ "common.h"
#અન્તર્ભાવ "error.h"
#અન્તર્ભાવ "attributes.h"
#અન્તર્ભાવ "macros.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "opt.h"

#define CHAN_IS_AMBI(x) ((x) >= AV_CHAN_AMBISONIC_BASE &&\
                         (x) <= AV_CHAN_AMBISONIC_END)

સંરચના channel_name {
    અચલ અક્ષર *name;
    અચલ અક્ષર *description;
};

સ્થિર અચલ સંરચના channel_name channel_names[] = {
    [AV_CHAN_FRONT_ડાબું           ] = { "FL",        "front left"            },
    [AV_CHAN_FRONT_જમણું          ] = { "FR",        "front right"           },
    [AV_CHAN_FRONT_CENTER         ] = { "FC",        "front center"          },
    [AV_CHAN_નીચલું_FREQUENCY        ] = { "LFE",       "low frequency"         },
    [AV_CHAN_BACK_ડાબું            ] = { "BL",        "back left"             },
    [AV_CHAN_BACK_જમણું           ] = { "BR",        "back right"            },
    [AV_CHAN_FRONT_ડાબું_OF_CENTER ] = { "FLC",       "front left-of-center"  },
    [AV_CHAN_FRONT_જમણું_OF_CENTER] = { "FRC",       "front right-of-center" },
    [AV_CHAN_BACK_CENTER          ] = { "BC",        "back center"           },
    [AV_CHAN_SIDE_ડાબું            ] = { "SL",        "side left"             },
    [AV_CHAN_SIDE_જમણું           ] = { "SR",        "side right"            },
    [AV_CHAN_ટોચ_CENTER           ] = { "TC",        "top center"            },
    [AV_CHAN_ટોચ_FRONT_ડાબું       ] = { "TFL",       "top front left"        },
    [AV_CHAN_ટોચ_FRONT_CENTER     ] = { "TFC",       "top front center"      },
    [AV_CHAN_ટોચ_FRONT_જમણું      ] = { "TFR",       "top front right"       },
    [AV_CHAN_ટોચ_BACK_ડાબું        ] = { "TBL",       "top back left"         },
    [AV_CHAN_ટોચ_BACK_CENTER      ] = { "TBC",       "top back center"       },
    [AV_CHAN_ટોચ_BACK_જમણું       ] = { "TBR",       "top back right"        },
    [AV_CHAN_STEREO_ડાબું          ] = { "DL",        "downmix left"          },
    [AV_CHAN_STEREO_જમણું         ] = { "DR",        "downmix right"         },
    [AV_CHAN_WIDE_ડાબું            ] = { "WL",        "wide left"             },
    [AV_CHAN_WIDE_જમણું           ] = { "WR",        "wide right"            },
    [AV_CHAN_SURROUND_DIRECT_ડાબું ] = { "SDL",       "surround direct left"  },
    [AV_CHAN_SURROUND_DIRECT_જમણું] = { "SDR",       "surround direct right" },
    [AV_CHAN_નીચલું_FREQUENCY_2      ] = { "LFE2",      "low frequency 2"       },
    [AV_CHAN_ટોચ_SIDE_ડાબું        ] = { "TSL",       "top side left"         },
    [AV_CHAN_ટોચ_SIDE_જમણું       ] = { "TSR",       "top side right"        },
    [AV_CHAN_BOTTOM_FRONT_CENTER  ] = { "BFC",       "bottom front center"   },
    [AV_CHAN_BOTTOM_FRONT_ડાબું    ] = { "BFL",       "bottom front left"     },
    [AV_CHAN_BOTTOM_FRONT_જમણું   ] = { "BFR",       "bottom front right"    },
    [AV_CHAN_SIDE_SURROUND_ડાબું   ] = { "SSL",       "side surround left"    },
    [AV_CHAN_SIDE_SURROUND_જમણું  ] = { "SSR",       "side surround right"   },
    [AV_CHAN_ટોચ_SURROUND_ડાબું    ] = { "TTL",       "top surround left"     },
    [AV_CHAN_ટોચ_SURROUND_જમણું   ] = { "TTR",       "top surround right"    },
    [AV_CHAN_BINAURAL_ડાબું        ] = { "BIL",       "binaural left"         },
    [AV_CHAN_BINAURAL_જમણું       ] = { "BIR",       "binaural right"        },
};

શૂન્ય av_channel_name_bprint(AVBPrint *bp, ગણના AVChannel channel_id)
{
    જો (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_BASE);
    નહીંતર જો ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].name)
        av_bprintf(bp, "%s", channel_names[channel_id].name);
    નહીંતર જો (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    નહીંતર જો (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    નહીંતર જો (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "UNSD");
    નહીંતર
        av_bprintf(bp, "USR%d", channel_id);
}

પૂર્ણાંક av_channel_name(અક્ષર *buf, size_t buf_size, ગણના AVChannel channel_id)
{
    AVBPrint bp;

    જો (!buf && buf_size)
        પાછા AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_name_bprint(&bp, channel_id);

    જો (bp.len >= INT_MAX)
        પાછા AVERROR(ERANGE);
    પાછા bp.len + 1;
}

શૂન્ય av_channel_description_bprint(AVBPrint *bp, ગણના AVChannel channel_id)
{
    જો (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_BASE);
    નહીંતર જો ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].description)
        av_bprintf(bp, "%s", channel_names[channel_id].description);
    નહીંતર જો (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    નહીંતર જો (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    નહીંતર જો (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "unused");
    નહીંતર
        av_bprintf(bp, "user %d", channel_id);
}

પૂર્ણાંક av_channel_description(અક્ષર *buf, size_t buf_size, ગણના AVChannel channel_id)
{
    AVBPrint bp;

    જો (!buf && buf_size)
        પાછા AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_description_bprint(&bp, channel_id);

    જો (bp.len >= INT_MAX)
        પાછા AVERROR(ERANGE);
    પાછા bp.len + 1;
}

ગણના AVChannel av_channel_from_string(અચલ અક્ષર *str)
{
    પૂર્ણાંક i;
    અક્ષર *endptr = (અક્ષર *)str;
    ગણના AVChannel id = AV_CHAN_NONE;

    જો (!strncmp(str, "AMBI", 4)) {
        i = strtol(str + 4, ખાલી, 0);
        જો (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            પાછા AV_CHAN_NONE;
        પાછા AV_CHAN_AMBISONIC_BASE + i;
    }

    માટે (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        જો (channel_names[i].name && !strcmp(str, channel_names[i].name))
            પાછા i;
    }
    જો (!strcmp(str, "UNK"))
        પાછા AV_CHAN_UNKNOWN;
    જો (!strcmp(str, "UNSD"))
        પાછા AV_CHAN_UNUSED;

    જો (!strncmp(str, "USR", 3)) {
        અચલ અક્ષર *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    જો (id >= 0 && !*endptr)
        પાછા id;

    પાછા AV_CHAN_NONE;
}

સંરચના channel_layout_name {
    અચલ અક્ષર *name;
    AVChannelLayout layout;
};

સ્થિર અચલ સંરચના channel_layout_name channel_layout_map[] = {
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

પૂર્ણાંક av_channel_layout_custom_init(AVChannelLayout *channel_layout, પૂર્ણાંક nb_channels)
{
    AVChannelCustom *map;

    જો (nb_channels <= 0)
        પાછા AVERROR(EINVAL);

    map = av_calloc(nb_channels, કદ(*channel_layout->u.map));
    જો (!map)
        પાછા AVERROR(ENOMEM);
    માટે (પૂર્ણાંક i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->order       = AV_CHANNEL_ORDER_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    પાછા 0;
}

પૂર્ણાંક av_channel_layout_from_mask(AVChannelLayout *channel_layout,
                                uint64_t mask)
{
    જો (!mask)
        પાછા AVERROR(EINVAL);

    channel_layout->order       = AV_CHANNEL_ORDER_NATIVE;
    channel_layout->nb_channels = av_popcount64(mask);
    channel_layout->u.mask      = mask;

    પાછા 0;
}

સ્થિર પૂર્ણાંક parse_channel_list(AVChannelLayout *ch_layout, અચલ અક્ષર *str)
{
    પૂર્ણાંક ret;
    પૂર્ણાંક nb_channels = 0;
    AVChannelCustom *map = ખાલી;
    AVChannelCustom custom = {0};

    જ્યારે (*str) {
        અક્ષર *channel, *chname;
        ret = av_opt_get_ચાવી_કિંમત(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_ચાવી, &channel, &chname);
        જો (ret < 0) {
            av_freep(&map);
            પાછા ret;
        }
        જો (*str)
            str++; // skip separator
        જો (!channel) {
            channel = chname;
            chname = ખાલી;
        }
        av_strlcpy(custom.name, chname ? chname : "", કદ(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        જો (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            પાછા AVERROR(EINVAL);
        }

        av_dynarray2_add((શૂન્ય **)&map, &nb_channels, કદ(custom), (શૂન્ય *)&custom);
        જો (!map)
            પાછા AVERROR(ENOMEM);
    }

    જો (!nb_channels)
        પાછા AVERROR(EINVAL);

    ch_layout->order = AV_CHANNEL_ORDER_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    પાછા 0;
}

પૂર્ણાંક av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  અચલ અક્ષર *str)
{
    પૂર્ણાંક i, matches, ret;
    પૂર્ણાંક channels = 0, nb_channels = 0;
    અક્ષર *chlist, *end;
    uint64_t mask = 0;

    /* channel layout names */
    માટે (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        જો (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            પાછા 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, કદ(*channel_layout));

    /* ambisonic */
    જો (!strncmp(str, "ambisonic ", 10)) {
        અચલ અક્ષર *p = str + 10;
        અક્ષર *endptr;
        AVChannelLayout extra = {0};
        પૂર્ણાંક order;

        order = strtol(p, &endptr, 0);
        જો (order < 0 || order + 1  > INT_MAX / (order + 1) ||
            (*endptr && *endptr != '+'))
            પાછા AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        જો (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            જો (ret < 0)
                પાછા ret;
            જો (extra.nb_channels >= INT_MAX - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                પાછા AVERROR(EINVAL);
            }

            જો (extra.order == AV_CHANNEL_ORDER_NATIVE) {
                channel_layout->u.mask = extra.u.mask;
            } નહીંતર {
                channel_layout->order = AV_CHANNEL_ORDER_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              કદ(*channel_layout->u.map));
                જો (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    પાછા AVERROR(ENOMEM);
                }

                માટે (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                માટે (i = 0; i < extra.nb_channels; i++) {
                    ગણના AVChannel ch = av_channel_layout_channel_from_index(&extra, i);
                    જો (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        પાછા AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    જો (extra.order == AV_CHANNEL_ORDER_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   કદ(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        પાછા 0;
    }

    chlist = av_strdup(str);
    જો (!chlist)
        પાછા AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    જો (ret < 0 && ret != AVERROR(EINVAL))
        પાછા ret;

    જો (ret >= 0) {
        અચલ અક્ષર *end_par = strchr(str, ')');
        જો (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            પાછા AVERROR(EINVAL);
        }
        પાછા 0;
    }

    errno = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    જો (!errno && !*end && !strchr(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        પાછા 0;
    }

    errno = 0;
    channels = strtol(str, &end, 10);

    /* number of channels */
    જો (!errno && !strcmp(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        જો (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            પાછા 0;
    }

    /* number of unordered channels */
    જો (!errno && (!strcmp(end, "C") || !strcmp(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        પાછા 0;
    }

    પાછા AVERROR(EINVAL);
}

શૂન્ય av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    જો (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, કદ(*channel_layout));
}

પૂર્ણાંક av_channel_layout_copy(AVChannelLayout *dst, અચલ AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    જો (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, કદ(*dst->u.map));
        જો (!dst->u.map)
            પાછા AVERROR(ENOMEM);
        memcpy(dst->u.map, src->u.map, src->nb_channels * કદ(*src->u.map));
    }
    પાછા 0;
}

સ્થિર int64_t masked_description(અચલ AVChannelLayout *channel_layout, પૂર્ણાંક start_channel)
{
    uint64_t mask = 0;
    માટે (પૂર્ણાંક i = start_channel; i < channel_layout->nb_channels; i++) {
        ગણના AVChannel ch = channel_layout->u.map[i].id;
        જો (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        નહીંતર
            પાછા AVERROR(EINVAL);
    }
    પાછા mask;
}

સ્થિર પૂર્ણાંક has_channel_names(અચલ AVChannelLayout *channel_layout)
{
    જો (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        પાછા 0;
    માટે (પૂર્ણાંક i = 0; i < channel_layout->nb_channels; i++)
        જો (channel_layout->u.map[i].name[0])
            પાછા 1;
    પાછા 0;
}

પૂર્ણાંક av_channel_layout_ambisonic_order(અચલ AVChannelLayout *channel_layout)
{
    પૂર્ણાંક i, highest_ambi, order;

    જો (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        પાછા AVERROR(EINVAL);

    highest_ambi = -1;
    જો (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    નહીંતર {
        અચલ AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        માટે (i = 0; i < channel_layout->nb_channels; i++) {
            પૂર્ણાંક is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            જો (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                પાછા AVERROR(EINVAL);

            /* non-default ordering */
            જો (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                પાછા AVERROR(EINVAL);

            જો (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    જો (highest_ambi < 0)
        પાછા AVERROR(EINVAL);

    order = floor(sqrt(highest_ambi));
    /* incomplete order - some harmonics are missing */
    જો ((order + 1) * (order + 1) != highest_ambi + 1)
        પાછા AVERROR(EINVAL);

    પાછા order;
}

સ્થિર ગણના AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    પૂર્ણાંક has_known_channel = 0;
    પૂર્ણાંક order;

    જો (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        પાછા channel_layout->order;

    જો (has_channel_names(channel_layout))
        પાછા AV_CHANNEL_ORDER_CUSTOM;

    માટે (પૂર્ણાંક i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        જો (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    જો (!has_known_channel)
        પાછા AV_CHANNEL_ORDER_UNSPEC;

    જો (masked_description(channel_layout, 0) > 0)
        પાછા AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    જો (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
        પાછા AV_CHANNEL_ORDER_AMBISONIC;

    પાછા AV_CHANNEL_ORDER_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
સ્થિર પૂર્ણાંક try_describe_ambisonic(AVBPrint *bp, અચલ AVChannelLayout *channel_layout)
{
    પૂર્ણાંક nb_ambi_channels;
    પૂર્ણાંક order = av_channel_layout_ambisonic_order(channel_layout);
    જો (order < 0)
        પાછા order;

    av_bprintf(bp, "ambisonic %d", order);

    /* extra channels present */
    nb_ambi_channels = (order + 1) * (order + 1);
    જો (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        જો (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC) {
            extra.order       = AV_CHANNEL_ORDER_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.mask);
            extra.u.mask      = channel_layout->u.mask;
        } નહીંતર {
            int64_t mask;
            જો (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.order       = AV_CHANNEL_ORDER_NATIVE;
                extra.nb_channels = av_popcount64(mask);
                extra.u.mask      = mask;
            } નહીંતર {
                extra.order       = AV_CHANNEL_ORDER_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    પાછા 0;
}

પૂર્ણાંક av_channel_layout_describe_bprint(અચલ AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    પૂર્ણાંક i;

    પસંદગી (channel_layout->order) {
    સ્થિતિ AV_CHANNEL_ORDER_NATIVE:
        માટે (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            જો (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                પાછા 0;
            }
        av_fallthrough;
    સ્થિતિ AV_CHANNEL_ORDER_CUSTOM:
        જો (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            પૂર્ણાંક res = try_describe_ambisonic(bp, channel_layout);
            જો (res >= 0)
                પાછા 0;
            જો (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                પાછા av_channel_layout_describe_bprint(&native, bp);
            }
        }
        જો (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        માટે (i = 0; i < channel_layout->nb_channels; i++) {
            ગણના AVChannel ch = av_channel_layout_channel_from_index(channel_layout, i);

            જો (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            જો (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        જો (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            પાછા 0;
        }
        av_fallthrough;
    સ્થિતિ AV_CHANNEL_ORDER_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        પાછા 0;
    સ્થિતિ AV_CHANNEL_ORDER_AMBISONIC:
        પાછા try_describe_ambisonic(bp, channel_layout);
    મૂળભૂત:
        પાછા AVERROR(EINVAL);
    }
}

પૂર્ણાંક av_channel_layout_describe(અચલ AVChannelLayout *channel_layout,
                               અક્ષર *buf, size_t buf_size)
{
    AVBPrint bp;
    પૂર્ણાંક ret;

    જો (!buf && buf_size)
        પાછા AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    જો (ret < 0)
        પાછા ret;

    જો (bp.len >= INT_MAX)
        પાછા AVERROR(ERANGE);
    પાછા bp.len + 1;
}

ગણના AVChannel
av_channel_layout_channel_from_index(અચલ AVChannelLayout *channel_layout,
                                     unsigned પૂર્ણાંક idx)
{
    પૂર્ણાંક i;

    જો (idx >= channel_layout->nb_channels)
        પાછા AV_CHAN_NONE;

    પસંદગી (channel_layout->order) {
    સ્થિતિ AV_CHANNEL_ORDER_CUSTOM:
        પાછા channel_layout->u.map[idx].id;
    સ્થિતિ AV_CHANNEL_ORDER_AMBISONIC: {
        પૂર્ણાંક ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        જો (idx < ambi_channels)
            પાછા AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    સ્થિતિ AV_CHANNEL_ORDER_NATIVE:
        માટે (i = 0; i < 64; i++) {
            જો ((1ULL << i) & channel_layout->u.mask && !idx--)
                પાછા i;
        }
        av_fallthrough;
    મૂળભૂત:
        પાછા AV_CHAN_NONE;
    }
}

ગણના AVChannel
av_channel_layout_channel_from_string(અચલ AVChannelLayout *channel_layout,
                                      અચલ અક્ષર *str)
{
    પૂર્ણાંક index = av_channel_layout_index_from_string(channel_layout, str);

    જો (index < 0)
        પાછા AV_CHAN_NONE;

    પાછા av_channel_layout_channel_from_index(channel_layout, index);
}

પૂર્ણાંક av_channel_layout_index_from_channel(અચલ AVChannelLayout *channel_layout,
                                         ગણના AVChannel channel)
{
    પૂર્ણાંક i;

    જો (channel == AV_CHAN_NONE)
        પાછા AVERROR(EINVAL);

    પસંદગી (channel_layout->order) {
    સ્થિતિ AV_CHANNEL_ORDER_CUSTOM:
        માટે (i = 0; i < channel_layout->nb_channels; i++)
            જો (channel_layout->u.map[i].id == channel)
                પાછા i;
        પાછા AVERROR(EINVAL);
    સ્થિતિ AV_CHANNEL_ORDER_AMBISONIC:
    સ્થિતિ AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        પૂર્ણાંક ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        જો (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            જો (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                પાછા AVERROR(EINVAL);
            પાછા channel - AV_CHAN_AMBISONIC_BASE;
        }
        જો ((unsigned)channel > 63 || !(mask & (1ULL << channel)))
            પાછા AVERROR(EINVAL);
        mask &= (1ULL << channel) - 1;
        પાછા av_popcount64(mask) + ambi_channels;
        }
    મૂળભૂત:
        પાછા AVERROR(EINVAL);
    }
}

પૂર્ણાંક av_channel_layout_index_from_string(અચલ AVChannelLayout *channel_layout,
                                        અચલ અક્ષર *str)
{
    અચલ અક્ષર *chname;
    ગણના AVChannel ch = AV_CHAN_NONE;

    પસંદગી (channel_layout->order) {
    સ્થિતિ AV_CHANNEL_ORDER_CUSTOM:
        chname = strstr(str, "@");
        જો (chname) {
            અક્ષર buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(કદ(buf), chname - str));
            જો (!*chname)
                chname = ખાલી;
            ch = av_channel_from_string(buf);
            જો (ch == AV_CHAN_NONE && *buf)
                પાછા AVERROR(EINVAL);
        }
        માટે (પૂર્ણાંક i = 0; chname && i < channel_layout->nb_channels; i++) {
            જો (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                પાછા i;
        }
        av_fallthrough;
    સ્થિતિ AV_CHANNEL_ORDER_AMBISONIC:
    સ્થિતિ AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        જો (ch == AV_CHAN_NONE)
            પાછા AVERROR(EINVAL);
        પાછા av_channel_layout_index_from_channel(channel_layout, ch);
    }

    પાછા AVERROR(EINVAL);
}

પૂર્ણાંક av_channel_layout_check(અચલ AVChannelLayout *channel_layout)
{
    જો (channel_layout->nb_channels <= 0)
        પાછા 0;

    પસંદગી (channel_layout->order) {
    સ્થિતિ AV_CHANNEL_ORDER_NATIVE:
        પાછા av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    સ્થિતિ AV_CHANNEL_ORDER_CUSTOM:
        જો (!channel_layout->u.map)
            પાછા 0;
        માટે (પૂર્ણાંક i = 0; i < channel_layout->nb_channels; i++) {
            જો (channel_layout->u.map[i].id == AV_CHAN_NONE)
                પાછા 0;
        }
        પાછા 1;
    સ્થિતિ AV_CHANNEL_ORDER_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        પાછા av_popcount64(channel_layout->u.mask) < channel_layout->nb_channels;
    સ્થિતિ AV_CHANNEL_ORDER_UNSPEC:
        પાછા 1;
    મૂળભૂત:
        પાછા 0;
    }
}

પૂર્ણાંક av_channel_layout_compare(અચલ AVChannelLayout *chl, અચલ AVChannelLayout *chl1)
{
    પૂર્ણાંક i;

    /* different channel counts -> not equal */
    જો (chl->nb_channels != chl1->nb_channels)
        પાછા 1;

    /* if only one is unspecified -> not equal */
    જો ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        પાછા 1;
    /* both are unspecified -> equal */
    નહીંતર જો (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        પાછા 0;

    /* can compare masks directly */
    જો ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        પાછા chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    માટે (i = 0; i < chl->nb_channels; i++)
        જો (av_channel_layout_channel_from_index(chl,  i) !=
            av_channel_layout_channel_from_index(chl1, i))
            પાછા 1;
    પાછા 0;
}

શૂન્ય av_channel_layout_default(AVChannelLayout *ch_layout, પૂર્ણાંક nb_channels)
{
    પૂર્ણાંક i;
    માટે (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        જો (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            પાછા;
        }

    ch_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

અચલ AVChannelLayout *av_channel_layout_standard(શૂન્ય **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    અચલ AVChannelLayout *ch_layout = ખાલી;

    જો (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (શૂન્ય*)(i + 1);
    }

    પાછા ch_layout;
}

uint64_t av_channel_layout_subset(અચલ AVChannelLayout *channel_layout,
                                  uint64_t mask)
{
    uint64_t ret = 0;
    પૂર્ણાંક i;

    પસંદગી (channel_layout->order) {
    સ્થિતિ AV_CHANNEL_ORDER_NATIVE:
    સ્થિતિ AV_CHANNEL_ORDER_AMBISONIC:
        પાછા channel_layout->u.mask & mask;
    સ્થિતિ AV_CHANNEL_ORDER_CUSTOM:
        માટે (i = 0; i < 64; i++)
            જો (mask & (1ULL << i) && av_channel_layout_index_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        તોડો;
    }

    પાછા ret;
}

પૂર્ણાંક av_channel_layout_retype(AVChannelLayout *channel_layout, ગણના AVChannelOrder order, પૂર્ણાંક flags)
{
    પૂર્ણાંક allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    પૂર્ણાંક lossy;

    જો (!av_channel_layout_check(channel_layout))
        પાછા AVERROR(EINVAL);

    જો (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    જો (channel_layout->order == order)
        પાછા 0;

    પસંદગી (order) {
    સ્થિતિ AV_CHANNEL_ORDER_UNSPEC: {
        પૂર્ણાંક nb_channels = channel_layout->nb_channels;
        જો (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            માટે (પૂર્ણાંક i = 0; i < nb_channels; i++) {
                જો (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    તોડો;
                }
            }
        } નહીંતર {
            lossy = 1;
        }
        જો (!lossy || allow_lossy) {
            શૂન્ય *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            પાછા lossy;
        }
        પાછા AVERROR(ENOSYS);
        }
    સ્થિતિ AV_CHANNEL_ORDER_NATIVE:
        જો (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            જો (mask < 0)
                પાછા AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            જો (!lossy || allow_lossy) {
                શૂન્ય *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_mask(channel_layout, mask);
                channel_layout->opaque = opaque;
                પાછા lossy;
            }
        }
        પાછા AVERROR(ENOSYS);
    સ્થિતિ AV_CHANNEL_ORDER_CUSTOM: {
        AVChannelLayout custom = { 0 };
        પૂર્ણાંક ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        શૂન્ય *opaque = channel_layout->opaque;
        જો (ret < 0)
            પાછા ret;
        જો (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            માટે (પૂર્ણાંક i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_index(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        પાછા 0;
        }
    સ્થિતિ AV_CHANNEL_ORDER_AMBISONIC:
        જો (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            પૂર્ણાંક nb_channels = channel_layout->nb_channels;
            પૂર્ણાંક amb_order = av_channel_layout_ambisonic_order(channel_layout);
            જો (amb_order < 0)
                પાછા AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            જો (mask < 0)
                પાછા AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            જો (!lossy || allow_lossy) {
                શૂન્ય *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.mask      = mask;
                channel_layout->opaque      = opaque;
                પાછા lossy;
            }
        }
        પાછા AVERROR(ENOSYS);
    મૂળભૂત:
        પાછા AVERROR(EINVAL);
    }
}
