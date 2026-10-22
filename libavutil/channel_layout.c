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

#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "channel_layout.h"
#அந்தர்பாவ "bprint.h"
#அந்தர்பாவ "common.h"
#அந்தர்பாவ "error.h"
#அந்தர்பாவ "attributes.h"
#அந்தர்பாவ "macros.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "opt.h"

#define CHAN_IS_AMBI(x) ((x) >= AV_CHAN_AMBISONIC_BASE &&\
                         (x) <= AV_CHAN_AMBISONIC_END)

கட்டமைப்பு channel_name {
    மாறிலி எழுத்து *name;
    மாறிலி எழுத்து *description;
};

நிலையான மாறிலி கட்டமைப்பு channel_name channel_names[] = {
    [AV_CHAN_FRONT_இடது           ] = { "FL",        "front left"            },
    [AV_CHAN_FRONT_வலது          ] = { "FR",        "front right"           },
    [AV_CHAN_FRONT_CENTER         ] = { "FC",        "front center"          },
    [AV_CHAN_கீழ்_FREQUENCY        ] = { "LFE",       "low frequency"         },
    [AV_CHAN_BACK_இடது            ] = { "BL",        "back left"             },
    [AV_CHAN_BACK_வலது           ] = { "BR",        "back right"            },
    [AV_CHAN_FRONT_இடது_OF_CENTER ] = { "FLC",       "front left-of-center"  },
    [AV_CHAN_FRONT_வலது_OF_CENTER] = { "FRC",       "front right-of-center" },
    [AV_CHAN_BACK_CENTER          ] = { "BC",        "back center"           },
    [AV_CHAN_SIDE_இடது            ] = { "SL",        "side left"             },
    [AV_CHAN_SIDE_வலது           ] = { "SR",        "side right"            },
    [AV_CHAN_உச்சி_CENTER           ] = { "TC",        "top center"            },
    [AV_CHAN_உச்சி_FRONT_இடது       ] = { "TFL",       "top front left"        },
    [AV_CHAN_உச்சி_FRONT_CENTER     ] = { "TFC",       "top front center"      },
    [AV_CHAN_உச்சி_FRONT_வலது      ] = { "TFR",       "top front right"       },
    [AV_CHAN_உச்சி_BACK_இடது        ] = { "TBL",       "top back left"         },
    [AV_CHAN_உச்சி_BACK_CENTER      ] = { "TBC",       "top back center"       },
    [AV_CHAN_உச்சி_BACK_வலது       ] = { "TBR",       "top back right"        },
    [AV_CHAN_STEREO_இடது          ] = { "DL",        "downmix left"          },
    [AV_CHAN_STEREO_வலது         ] = { "DR",        "downmix right"         },
    [AV_CHAN_WIDE_இடது            ] = { "WL",        "wide left"             },
    [AV_CHAN_WIDE_வலது           ] = { "WR",        "wide right"            },
    [AV_CHAN_SURROUND_DIRECT_இடது ] = { "SDL",       "surround direct left"  },
    [AV_CHAN_SURROUND_DIRECT_வலது] = { "SDR",       "surround direct right" },
    [AV_CHAN_கீழ்_FREQUENCY_2      ] = { "LFE2",      "low frequency 2"       },
    [AV_CHAN_உச்சி_SIDE_இடது        ] = { "TSL",       "top side left"         },
    [AV_CHAN_உச்சி_SIDE_வலது       ] = { "TSR",       "top side right"        },
    [AV_CHAN_BOTTOM_FRONT_CENTER  ] = { "BFC",       "bottom front center"   },
    [AV_CHAN_BOTTOM_FRONT_இடது    ] = { "BFL",       "bottom front left"     },
    [AV_CHAN_BOTTOM_FRONT_வலது   ] = { "BFR",       "bottom front right"    },
    [AV_CHAN_SIDE_SURROUND_இடது   ] = { "SSL",       "side surround left"    },
    [AV_CHAN_SIDE_SURROUND_வலது  ] = { "SSR",       "side surround right"   },
    [AV_CHAN_உச்சி_SURROUND_இடது    ] = { "TTL",       "top surround left"     },
    [AV_CHAN_உச்சி_SURROUND_வலது   ] = { "TTR",       "top surround right"    },
    [AV_CHAN_BINAURAL_இடது        ] = { "BIL",       "binaural left"         },
    [AV_CHAN_BINAURAL_வலது       ] = { "BIR",       "binaural right"        },
};

வெறுமை av_channel_name_bprint(AVBPrint *bp, எண்ணிக்கை AVChannel channel_id)
{
    எனில் (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "AMBI%d", channel_id - AV_CHAN_AMBISONIC_BASE);
    இல்லையெனில் எனில் ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].name)
        av_bprintf(bp, "%s", channel_names[channel_id].name);
    இல்லையெனில் எனில் (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "NONE");
    இல்லையெனில் எனில் (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "UNK");
    இல்லையெனில் எனில் (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "UNSD");
    இல்லையெனில்
        av_bprintf(bp, "USR%d", channel_id);
}

முழு av_channel_name(எழுத்து *buf, size_t buf_size, எண்ணிக்கை AVChannel channel_id)
{
    AVBPrint bp;

    எனில் (!buf && buf_size)
        திரும்பு AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_name_bprint(&bp, channel_id);

    எனில் (bp.len >= INT_MAX)
        திரும்பு AVERROR(ERANGE);
    திரும்பு bp.len + 1;
}

வெறுமை av_channel_description_bprint(AVBPrint *bp, எண்ணிக்கை AVChannel channel_id)
{
    எனில் (channel_id >= AV_CHAN_AMBISONIC_BASE &&
        channel_id <= AV_CHAN_AMBISONIC_END)
        av_bprintf(bp, "ambisonic ACN %d", channel_id - AV_CHAN_AMBISONIC_BASE);
    இல்லையெனில் எனில் ((unsigned)channel_id < FF_ARRAY_ELEMS(channel_names) &&
             channel_names[channel_id].description)
        av_bprintf(bp, "%s", channel_names[channel_id].description);
    இல்லையெனில் எனில் (channel_id == AV_CHAN_NONE)
        av_bprintf(bp, "none");
    இல்லையெனில் எனில் (channel_id == AV_CHAN_UNKNOWN)
        av_bprintf(bp, "unknown");
    இல்லையெனில் எனில் (channel_id == AV_CHAN_UNUSED)
        av_bprintf(bp, "unused");
    இல்லையெனில்
        av_bprintf(bp, "user %d", channel_id);
}

முழு av_channel_description(எழுத்து *buf, size_t buf_size, எண்ணிக்கை AVChannel channel_id)
{
    AVBPrint bp;

    எனில் (!buf && buf_size)
        திரும்பு AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    av_channel_description_bprint(&bp, channel_id);

    எனில் (bp.len >= INT_MAX)
        திரும்பு AVERROR(ERANGE);
    திரும்பு bp.len + 1;
}

எண்ணிக்கை AVChannel av_channel_from_string(மாறிலி எழுத்து *str)
{
    முழு i;
    எழுத்து *endptr = (எழுத்து *)str;
    எண்ணிக்கை AVChannel id = AV_CHAN_NONE;

    எனில் (!strncmp(str, "AMBI", 4)) {
        i = strtol(str + 4, வெற்று, 0);
        எனில் (i < 0 || i > AV_CHAN_AMBISONIC_END - AV_CHAN_AMBISONIC_BASE)
            திரும்பு AV_CHAN_NONE;
        திரும்பு AV_CHAN_AMBISONIC_BASE + i;
    }

    க்கு (i = 0; i < FF_ARRAY_ELEMS(channel_names); i++) {
        எனில் (channel_names[i].name && !strcmp(str, channel_names[i].name))
            திரும்பு i;
    }
    எனில் (!strcmp(str, "UNK"))
        திரும்பு AV_CHAN_UNKNOWN;
    எனில் (!strcmp(str, "UNSD"))
        திரும்பு AV_CHAN_UNUSED;

    எனில் (!strncmp(str, "USR", 3)) {
        மாறிலி எழுத்து *p = str + 3;
        id = strtol(p, &endptr, 0);
    }
    எனில் (id >= 0 && !*endptr)
        திரும்பு id;

    திரும்பு AV_CHAN_NONE;
}

கட்டமைப்பு channel_layout_name {
    மாறிலி எழுத்து *name;
    AVChannelLayout layout;
};

நிலையான மாறிலி கட்டமைப்பு channel_layout_name channel_layout_map[] = {
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

முழு av_channel_layout_custom_init(AVChannelLayout *channel_layout, முழு nb_channels)
{
    AVChannelCustom *map;

    எனில் (nb_channels <= 0)
        திரும்பு AVERROR(EINVAL);

    map = av_calloc(nb_channels, அளவு(*channel_layout->u.map));
    எனில் (!map)
        திரும்பு AVERROR(ENOMEM);
    க்கு (முழு i = 0; i < nb_channels; i++)
        map[i].id = AV_CHAN_UNKNOWN;

    channel_layout->order       = AV_CHANNEL_ORDER_CUSTOM;
    channel_layout->nb_channels = nb_channels;
    channel_layout->u.map       = map;

    திரும்பு 0;
}

முழு av_channel_layout_from_mask(AVChannelLayout *channel_layout,
                                uint64_t mask)
{
    எனில் (!mask)
        திரும்பு AVERROR(EINVAL);

    channel_layout->order       = AV_CHANNEL_ORDER_NATIVE;
    channel_layout->nb_channels = av_popcount64(mask);
    channel_layout->u.mask      = mask;

    திரும்பு 0;
}

நிலையான முழு parse_channel_list(AVChannelLayout *ch_layout, மாறிலி எழுத்து *str)
{
    முழு ret;
    முழு nb_channels = 0;
    AVChannelCustom *map = வெற்று;
    AVChannelCustom custom = {0};

    போது (*str) {
        எழுத்து *channel, *chname;
        ret = av_opt_get_சாவி_மதிப்பு(&str, "@", "+", AV_OPT_FLAG_IMPLICIT_சாவி, &channel, &chname);
        எனில் (ret < 0) {
            av_freep(&map);
            திரும்பு ret;
        }
        எனில் (*str)
            str++; // skip separator
        எனில் (!channel) {
            channel = chname;
            chname = வெற்று;
        }
        av_strlcpy(custom.name, chname ? chname : "", அளவு(custom.name));
        custom.id = av_channel_from_string(channel);
        av_free(channel);
        av_free(chname);
        எனில் (custom.id == AV_CHAN_NONE) {
            av_freep(&map);
            திரும்பு AVERROR(EINVAL);
        }

        av_dynarray2_add((வெறுமை **)&map, &nb_channels, அளவு(custom), (வெறுமை *)&custom);
        எனில் (!map)
            திரும்பு AVERROR(ENOMEM);
    }

    எனில் (!nb_channels)
        திரும்பு AVERROR(EINVAL);

    ch_layout->order = AV_CHANNEL_ORDER_CUSTOM;
    ch_layout->u.map = map;
    ch_layout->nb_channels = nb_channels;

    ret = av_channel_layout_retype(ch_layout, 0, AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL);
    av_assert0(ret == 0);

    திரும்பு 0;
}

முழு av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  மாறிலி எழுத்து *str)
{
    முழு i, matches, ret;
    முழு channels = 0, nb_channels = 0;
    எழுத்து *chlist, *end;
    uint64_t mask = 0;

    /* channel layout names */
    க்கு (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++) {
        எனில் (channel_layout_map[i].name && !strcmp(str, channel_layout_map[i].name)) {
            *channel_layout = channel_layout_map[i].layout;
            திரும்பு 0;
        }
    }

    /* This function is a channel layout initializer, so we have to
     * zero-initialize before we start setting fields individually. */
    memset(channel_layout, 0, அளவு(*channel_layout));

    /* ambisonic */
    எனில் (!strncmp(str, "ambisonic ", 10)) {
        மாறிலி எழுத்து *p = str + 10;
        எழுத்து *endptr;
        AVChannelLayout extra = {0};
        முழு order;

        order = strtol(p, &endptr, 0);
        எனில் (order < 0 || order + 1  > INT_MAX / (order + 1) ||
            (*endptr && *endptr != '+'))
            திரும்பு AVERROR(EINVAL);

        channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
        channel_layout->nb_channels = (order + 1) * (order + 1);

        எனில் (*endptr) {
            ret = av_channel_layout_from_string(&extra, endptr + 1);
            எனில் (ret < 0)
                திரும்பு ret;
            எனில் (extra.nb_channels >= INT_MAX - channel_layout->nb_channels) {
                av_channel_layout_uninit(&extra);
                திரும்பு AVERROR(EINVAL);
            }

            எனில் (extra.order == AV_CHANNEL_ORDER_NATIVE) {
                channel_layout->u.mask = extra.u.mask;
            } இல்லையெனில் {
                channel_layout->order = AV_CHANNEL_ORDER_CUSTOM;
                channel_layout->u.map =
                    av_calloc(channel_layout->nb_channels + extra.nb_channels,
                              அளவு(*channel_layout->u.map));
                எனில் (!channel_layout->u.map) {
                    av_channel_layout_uninit(&extra);
                    திரும்பு AVERROR(ENOMEM);
                }

                க்கு (i = 0; i < channel_layout->nb_channels; i++)
                    channel_layout->u.map[i].id = AV_CHAN_AMBISONIC_BASE + i;
                க்கு (i = 0; i < extra.nb_channels; i++) {
                    எண்ணிக்கை AVChannel ch = av_channel_layout_channel_from_index(&extra, i);
                    எனில் (CHAN_IS_AMBI(ch)) {
                        av_channel_layout_uninit(channel_layout);
                        av_channel_layout_uninit(&extra);
                        திரும்பு AVERROR(EINVAL);
                    }
                    channel_layout->u.map[channel_layout->nb_channels + i].id = ch;
                    எனில் (extra.order == AV_CHANNEL_ORDER_CUSTOM &&
                        extra.u.map[i].name[0])
                        av_strlcpy(channel_layout->u.map[channel_layout->nb_channels + i].name,
                                   extra.u.map[i].name,
                                   அளவு(channel_layout->u.map[channel_layout->nb_channels + i].name));
                }
            }
            channel_layout->nb_channels += extra.nb_channels;
            av_channel_layout_uninit(&extra);
        }

        திரும்பு 0;
    }

    chlist = av_strdup(str);
    எனில் (!chlist)
        திரும்பு AVERROR(ENOMEM);

    /* channel names */
    matches = av_sscanf(str, "%d channels (%[^)]", &nb_channels, chlist);
    ret = parse_channel_list(channel_layout, chlist);
    av_freep(&chlist);
    எனில் (ret < 0 && ret != AVERROR(EINVAL))
        திரும்பு ret;

    எனில் (ret >= 0) {
        மாறிலி எழுத்து *end_par = strchr(str, ')');
        எனில் (matches == 2 && (nb_channels != channel_layout->nb_channels || !end_par || *++end_par)) {
            av_channel_layout_uninit(channel_layout);
            திரும்பு AVERROR(EINVAL);
        }
        திரும்பு 0;
    }

    errno = 0;
    mask = strtoull(str, &end, 0);

    /* channel layout mask */
    எனில் (!errno && !*end && !strchr(str, '-') && mask) {
        av_channel_layout_from_mask(channel_layout, mask);
        திரும்பு 0;
    }

    errno = 0;
    channels = strtol(str, &end, 10);

    /* number of channels */
    எனில் (!errno && !strcmp(end, "c") && channels > 0) {
        av_channel_layout_default(channel_layout, channels);
        எனில் (channel_layout->order == AV_CHANNEL_ORDER_NATIVE)
            திரும்பு 0;
    }

    /* number of unordered channels */
    எனில் (!errno && (!strcmp(end, "C") || !strcmp(end, " channels"))
        && channels > 0) {
        channel_layout->order = AV_CHANNEL_ORDER_UNSPEC;
        channel_layout->nb_channels = channels;
        திரும்பு 0;
    }

    திரும்பு AVERROR(EINVAL);
}

வெறுமை av_channel_layout_uninit(AVChannelLayout *channel_layout)
{
    எனில் (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM)
        av_freep(&channel_layout->u.map);
    memset(channel_layout, 0, அளவு(*channel_layout));
}

முழு av_channel_layout_copy(AVChannelLayout *dst, மாறிலி AVChannelLayout *src)
{
    av_channel_layout_uninit(dst);
    *dst = *src;
    எனில் (src->order == AV_CHANNEL_ORDER_CUSTOM) {
        dst->u.map = av_malloc_array(src->nb_channels, அளவு(*dst->u.map));
        எனில் (!dst->u.map)
            திரும்பு AVERROR(ENOMEM);
        memcpy(dst->u.map, src->u.map, src->nb_channels * அளவு(*src->u.map));
    }
    திரும்பு 0;
}

நிலையான int64_t masked_description(மாறிலி AVChannelLayout *channel_layout, முழு start_channel)
{
    uint64_t mask = 0;
    க்கு (முழு i = start_channel; i < channel_layout->nb_channels; i++) {
        எண்ணிக்கை AVChannel ch = channel_layout->u.map[i].id;
        எனில் (ch >= 0 && ch < 63 && mask < (1ULL << ch))
            mask |= (1ULL << ch);
        இல்லையெனில்
            திரும்பு AVERROR(EINVAL);
    }
    திரும்பு mask;
}

நிலையான முழு has_channel_names(மாறிலி AVChannelLayout *channel_layout)
{
    எனில் (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        திரும்பு 0;
    க்கு (முழு i = 0; i < channel_layout->nb_channels; i++)
        எனில் (channel_layout->u.map[i].name[0])
            திரும்பு 1;
    திரும்பு 0;
}

முழு av_channel_layout_ambisonic_order(மாறிலி AVChannelLayout *channel_layout)
{
    முழு i, highest_ambi, order;

    எனில் (channel_layout->order != AV_CHANNEL_ORDER_AMBISONIC &&
        channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        திரும்பு AVERROR(EINVAL);

    highest_ambi = -1;
    எனில் (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC)
        highest_ambi = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask) - 1;
    இல்லையெனில் {
        மாறிலி AVChannelCustom *map = channel_layout->u.map;
        av_assert0(channel_layout->order == AV_CHANNEL_ORDER_CUSTOM);

        க்கு (i = 0; i < channel_layout->nb_channels; i++) {
            முழு is_ambi = CHAN_IS_AMBI(map[i].id);

            /* ambisonic following non-ambisonic */
            எனில் (i > 0 && is_ambi && !CHAN_IS_AMBI(map[i - 1].id))
                திரும்பு AVERROR(EINVAL);

            /* non-default ordering */
            எனில் (is_ambi && map[i].id - AV_CHAN_AMBISONIC_BASE != i)
                திரும்பு AVERROR(EINVAL);

            எனில் (CHAN_IS_AMBI(map[i].id))
                highest_ambi = i;
        }
    }
    /* no ambisonic channels*/
    எனில் (highest_ambi < 0)
        திரும்பு AVERROR(EINVAL);

    order = floor(sqrt(highest_ambi));
    /* incomplete order - some harmonics are missing */
    எனில் ((order + 1) * (order + 1) != highest_ambi + 1)
        திரும்பு AVERROR(EINVAL);

    திரும்பு order;
}

நிலையான எண்ணிக்கை AVChannelOrder canonical_order(AVChannelLayout *channel_layout)
{
    முழு has_known_channel = 0;
    முழு order;

    எனில் (channel_layout->order != AV_CHANNEL_ORDER_CUSTOM)
        திரும்பு channel_layout->order;

    எனில் (has_channel_names(channel_layout))
        திரும்பு AV_CHANNEL_ORDER_CUSTOM;

    க்கு (முழு i = 0; i < channel_layout->nb_channels && !has_known_channel; i++)
        எனில் (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN)
            has_known_channel = 1;
    எனில் (!has_known_channel)
        திரும்பு AV_CHANNEL_ORDER_UNSPEC;

    எனில் (masked_description(channel_layout, 0) > 0)
        திரும்பு AV_CHANNEL_ORDER_NATIVE;

    order = av_channel_layout_ambisonic_order(channel_layout);
    எனில் (order >= 0 && masked_description(channel_layout, (order + 1) * (order + 1)) >= 0)
        திரும்பு AV_CHANNEL_ORDER_AMBISONIC;

    திரும்பு AV_CHANNEL_ORDER_CUSTOM;
}

/**
 * If the custom layout is n-th order standard-order ambisonic, with optional
 * extra non-diegetic channels at the end, write its string description in bp.
 * Return a negative error code otherwise.
 */
நிலையான முழு try_describe_ambisonic(AVBPrint *bp, மாறிலி AVChannelLayout *channel_layout)
{
    முழு nb_ambi_channels;
    முழு order = av_channel_layout_ambisonic_order(channel_layout);
    எனில் (order < 0)
        திரும்பு order;

    av_bprintf(bp, "ambisonic %d", order);

    /* extra channels present */
    nb_ambi_channels = (order + 1) * (order + 1);
    எனில் (nb_ambi_channels < channel_layout->nb_channels) {
        AVChannelLayout extra = { 0 };

        எனில் (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC) {
            extra.order       = AV_CHANNEL_ORDER_NATIVE;
            extra.nb_channels = av_popcount64(channel_layout->u.mask);
            extra.u.mask      = channel_layout->u.mask;
        } இல்லையெனில் {
            int64_t mask;
            எனில் (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, nb_ambi_channels)) > 0) {
                extra.order       = AV_CHANNEL_ORDER_NATIVE;
                extra.nb_channels = av_popcount64(mask);
                extra.u.mask      = mask;
            } இல்லையெனில் {
                extra.order       = AV_CHANNEL_ORDER_CUSTOM;
                extra.nb_channels = channel_layout->nb_channels - nb_ambi_channels;
                extra.u.map       = channel_layout->u.map + nb_ambi_channels;
            }
        }

        av_bprint_chars(bp, '+', 1);
        av_channel_layout_describe_bprint(&extra, bp);
        /* Not calling uninit here on extra because we don't own the u.map pointer */
    }

    திரும்பு 0;
}

முழு av_channel_layout_describe_bprint(மாறிலி AVChannelLayout *channel_layout,
                                      AVBPrint *bp)
{
    முழு i;

    தேர்வு (channel_layout->order) {
    நிலை AV_CHANNEL_ORDER_NATIVE:
        க்கு (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
            எனில் (channel_layout->u.mask == channel_layout_map[i].layout.u.mask) {
                av_bprintf(bp, "%s", channel_layout_map[i].name);
                திரும்பு 0;
            }
        av_fallthrough;
    நிலை AV_CHANNEL_ORDER_CUSTOM:
        எனில் (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            முழு res = try_describe_ambisonic(bp, channel_layout);
            எனில் (res >= 0)
                திரும்பு 0;
            எனில் (!has_channel_names(channel_layout) &&
                (mask = masked_description(channel_layout, 0)) > 0) {
                AVChannelLayout native = { .order       = AV_CHANNEL_ORDER_NATIVE,
                                           .nb_channels = av_popcount64(mask),
                                           .u.mask      = mask };
                திரும்பு av_channel_layout_describe_bprint(&native, bp);
            }
        }
        எனில் (channel_layout->nb_channels)
            av_bprintf(bp, "%d channels (", channel_layout->nb_channels);
        க்கு (i = 0; i < channel_layout->nb_channels; i++) {
            எண்ணிக்கை AVChannel ch = av_channel_layout_channel_from_index(channel_layout, i);

            எனில் (i)
                av_bprintf(bp, "+");
            av_channel_name_bprint(bp, ch);
            எனில் (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM &&
                channel_layout->u.map[i].name[0])
                av_bprintf(bp, "@%s", channel_layout->u.map[i].name);
        }
        எனில் (channel_layout->nb_channels) {
            av_bprintf(bp, ")");
            திரும்பு 0;
        }
        av_fallthrough;
    நிலை AV_CHANNEL_ORDER_UNSPEC:
        av_bprintf(bp, "%d channels", channel_layout->nb_channels);
        திரும்பு 0;
    நிலை AV_CHANNEL_ORDER_AMBISONIC:
        திரும்பு try_describe_ambisonic(bp, channel_layout);
    இயல்பு:
        திரும்பு AVERROR(EINVAL);
    }
}

முழு av_channel_layout_describe(மாறிலி AVChannelLayout *channel_layout,
                               எழுத்து *buf, size_t buf_size)
{
    AVBPrint bp;
    முழு ret;

    எனில் (!buf && buf_size)
        திரும்பு AVERROR(EINVAL);

    av_bprint_init_for_buffer(&bp, buf, buf_size);
    ret = av_channel_layout_describe_bprint(channel_layout, &bp);
    எனில் (ret < 0)
        திரும்பு ret;

    எனில் (bp.len >= INT_MAX)
        திரும்பு AVERROR(ERANGE);
    திரும்பு bp.len + 1;
}

எண்ணிக்கை AVChannel
av_channel_layout_channel_from_index(மாறிலி AVChannelLayout *channel_layout,
                                     unsigned முழு idx)
{
    முழு i;

    எனில் (idx >= channel_layout->nb_channels)
        திரும்பு AV_CHAN_NONE;

    தேர்வு (channel_layout->order) {
    நிலை AV_CHANNEL_ORDER_CUSTOM:
        திரும்பு channel_layout->u.map[idx].id;
    நிலை AV_CHANNEL_ORDER_AMBISONIC: {
        முழு ambi_channels = channel_layout->nb_channels - av_popcount64(channel_layout->u.mask);
        எனில் (idx < ambi_channels)
            திரும்பு AV_CHAN_AMBISONIC_BASE + idx;
        idx -= ambi_channels;
        }
        av_fallthrough;
    நிலை AV_CHANNEL_ORDER_NATIVE:
        க்கு (i = 0; i < 64; i++) {
            எனில் ((1ULL << i) & channel_layout->u.mask && !idx--)
                திரும்பு i;
        }
        av_fallthrough;
    இயல்பு:
        திரும்பு AV_CHAN_NONE;
    }
}

எண்ணிக்கை AVChannel
av_channel_layout_channel_from_string(மாறிலி AVChannelLayout *channel_layout,
                                      மாறிலி எழுத்து *str)
{
    முழு index = av_channel_layout_index_from_string(channel_layout, str);

    எனில் (index < 0)
        திரும்பு AV_CHAN_NONE;

    திரும்பு av_channel_layout_channel_from_index(channel_layout, index);
}

முழு av_channel_layout_index_from_channel(மாறிலி AVChannelLayout *channel_layout,
                                         எண்ணிக்கை AVChannel channel)
{
    முழு i;

    எனில் (channel == AV_CHAN_NONE)
        திரும்பு AVERROR(EINVAL);

    தேர்வு (channel_layout->order) {
    நிலை AV_CHANNEL_ORDER_CUSTOM:
        க்கு (i = 0; i < channel_layout->nb_channels; i++)
            எனில் (channel_layout->u.map[i].id == channel)
                திரும்பு i;
        திரும்பு AVERROR(EINVAL);
    நிலை AV_CHANNEL_ORDER_AMBISONIC:
    நிலை AV_CHANNEL_ORDER_NATIVE: {
        uint64_t mask = channel_layout->u.mask;
        முழு ambi_channels = channel_layout->nb_channels - av_popcount64(mask);
        எனில் (channel_layout->order == AV_CHANNEL_ORDER_AMBISONIC &&
            channel >= AV_CHAN_AMBISONIC_BASE) {
            எனில் (channel - AV_CHAN_AMBISONIC_BASE >= ambi_channels)
                திரும்பு AVERROR(EINVAL);
            திரும்பு channel - AV_CHAN_AMBISONIC_BASE;
        }
        எனில் ((unsigned)channel > 63 || !(mask & (1ULL << channel)))
            திரும்பு AVERROR(EINVAL);
        mask &= (1ULL << channel) - 1;
        திரும்பு av_popcount64(mask) + ambi_channels;
        }
    இயல்பு:
        திரும்பு AVERROR(EINVAL);
    }
}

முழு av_channel_layout_index_from_string(மாறிலி AVChannelLayout *channel_layout,
                                        மாறிலி எழுத்து *str)
{
    மாறிலி எழுத்து *chname;
    எண்ணிக்கை AVChannel ch = AV_CHAN_NONE;

    தேர்வு (channel_layout->order) {
    நிலை AV_CHANNEL_ORDER_CUSTOM:
        chname = strstr(str, "@");
        எனில் (chname) {
            எழுத்து buf[16];
            chname++;
            av_strlcpy(buf, str, FFMIN(அளவு(buf), chname - str));
            எனில் (!*chname)
                chname = வெற்று;
            ch = av_channel_from_string(buf);
            எனில் (ch == AV_CHAN_NONE && *buf)
                திரும்பு AVERROR(EINVAL);
        }
        க்கு (முழு i = 0; chname && i < channel_layout->nb_channels; i++) {
            எனில் (!strcmp(chname, channel_layout->u.map[i].name) &&
                (ch == AV_CHAN_NONE || ch == channel_layout->u.map[i].id))
                திரும்பு i;
        }
        av_fallthrough;
    நிலை AV_CHANNEL_ORDER_AMBISONIC:
    நிலை AV_CHANNEL_ORDER_NATIVE:
        ch = av_channel_from_string(str);
        எனில் (ch == AV_CHAN_NONE)
            திரும்பு AVERROR(EINVAL);
        திரும்பு av_channel_layout_index_from_channel(channel_layout, ch);
    }

    திரும்பு AVERROR(EINVAL);
}

முழு av_channel_layout_check(மாறிலி AVChannelLayout *channel_layout)
{
    எனில் (channel_layout->nb_channels <= 0)
        திரும்பு 0;

    தேர்வு (channel_layout->order) {
    நிலை AV_CHANNEL_ORDER_NATIVE:
        திரும்பு av_popcount64(channel_layout->u.mask) == channel_layout->nb_channels;
    நிலை AV_CHANNEL_ORDER_CUSTOM:
        எனில் (!channel_layout->u.map)
            திரும்பு 0;
        க்கு (முழு i = 0; i < channel_layout->nb_channels; i++) {
            எனில் (channel_layout->u.map[i].id == AV_CHAN_NONE)
                திரும்பு 0;
        }
        திரும்பு 1;
    நிலை AV_CHANNEL_ORDER_AMBISONIC:
        /* If non-diegetic channels are present, ensure they are taken into account */
        திரும்பு av_popcount64(channel_layout->u.mask) < channel_layout->nb_channels;
    நிலை AV_CHANNEL_ORDER_UNSPEC:
        திரும்பு 1;
    இயல்பு:
        திரும்பு 0;
    }
}

முழு av_channel_layout_compare(மாறிலி AVChannelLayout *chl, மாறிலி AVChannelLayout *chl1)
{
    முழு i;

    /* different channel counts -> not equal */
    எனில் (chl->nb_channels != chl1->nb_channels)
        திரும்பு 1;

    /* if only one is unspecified -> not equal */
    எனில் ((chl->order  == AV_CHANNEL_ORDER_UNSPEC) !=
        (chl1->order == AV_CHANNEL_ORDER_UNSPEC))
        திரும்பு 1;
    /* both are unspecified -> equal */
    இல்லையெனில் எனில் (chl->order == AV_CHANNEL_ORDER_UNSPEC)
        திரும்பு 0;

    /* can compare masks directly */
    எனில் ((chl->order == AV_CHANNEL_ORDER_NATIVE ||
         chl->order == AV_CHANNEL_ORDER_AMBISONIC) &&
        chl->order == chl1->order)
        திரும்பு chl->u.mask != chl1->u.mask;

    /* compare channel by channel */
    க்கு (i = 0; i < chl->nb_channels; i++)
        எனில் (av_channel_layout_channel_from_index(chl,  i) !=
            av_channel_layout_channel_from_index(chl1, i))
            திரும்பு 1;
    திரும்பு 0;
}

வெறுமை av_channel_layout_default(AVChannelLayout *ch_layout, முழு nb_channels)
{
    முழு i;
    க்கு (i = 0; i < FF_ARRAY_ELEMS(channel_layout_map); i++)
        எனில் (nb_channels == channel_layout_map[i].layout.nb_channels) {
            *ch_layout = channel_layout_map[i].layout;
            திரும்பு;
        }

    ch_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
    ch_layout->nb_channels = nb_channels;
}

மாறிலி AVChannelLayout *av_channel_layout_standard(வெறுமை **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    மாறிலி AVChannelLayout *ch_layout = வெற்று;

    எனில் (i < FF_ARRAY_ELEMS(channel_layout_map)) {
        ch_layout = &channel_layout_map[i].layout;
        *opaque = (வெறுமை*)(i + 1);
    }

    திரும்பு ch_layout;
}

uint64_t av_channel_layout_subset(மாறிலி AVChannelLayout *channel_layout,
                                  uint64_t mask)
{
    uint64_t ret = 0;
    முழு i;

    தேர்வு (channel_layout->order) {
    நிலை AV_CHANNEL_ORDER_NATIVE:
    நிலை AV_CHANNEL_ORDER_AMBISONIC:
        திரும்பு channel_layout->u.mask & mask;
    நிலை AV_CHANNEL_ORDER_CUSTOM:
        க்கு (i = 0; i < 64; i++)
            எனில் (mask & (1ULL << i) && av_channel_layout_index_from_channel(channel_layout, i) >= 0)
                ret |= (1ULL << i);
        நிறுத்து;
    }

    திரும்பு ret;
}

முழு av_channel_layout_retype(AVChannelLayout *channel_layout, எண்ணிக்கை AVChannelOrder order, முழு flags)
{
    முழு allow_lossy = !(flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS);
    முழு lossy;

    எனில் (!av_channel_layout_check(channel_layout))
        திரும்பு AVERROR(EINVAL);

    எனில் (flags & AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL)
        order = canonical_order(channel_layout);

    எனில் (channel_layout->order == order)
        திரும்பு 0;

    தேர்வு (order) {
    நிலை AV_CHANNEL_ORDER_UNSPEC: {
        முழு nb_channels = channel_layout->nb_channels;
        எனில் (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            lossy = 0;
            க்கு (முழு i = 0; i < nb_channels; i++) {
                எனில் (channel_layout->u.map[i].id != AV_CHAN_UNKNOWN || channel_layout->u.map[i].name[0]) {
                    lossy = 1;
                    நிறுத்து;
                }
            }
        } இல்லையெனில் {
            lossy = 1;
        }
        எனில் (!lossy || allow_lossy) {
            வெறுமை *opaque = channel_layout->opaque;
            av_channel_layout_uninit(channel_layout);
            channel_layout->order       = AV_CHANNEL_ORDER_UNSPEC;
            channel_layout->nb_channels = nb_channels;
            channel_layout->opaque      = opaque;
            திரும்பு lossy;
        }
        திரும்பு AVERROR(ENOSYS);
        }
    நிலை AV_CHANNEL_ORDER_NATIVE:
        எனில் (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask = masked_description(channel_layout, 0);
            எனில் (mask < 0)
                திரும்பு AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            எனில் (!lossy || allow_lossy) {
                வெறுமை *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                av_channel_layout_from_mask(channel_layout, mask);
                channel_layout->opaque = opaque;
                திரும்பு lossy;
            }
        }
        திரும்பு AVERROR(ENOSYS);
    நிலை AV_CHANNEL_ORDER_CUSTOM: {
        AVChannelLayout custom = { 0 };
        முழு ret = av_channel_layout_custom_init(&custom, channel_layout->nb_channels);
        வெறுமை *opaque = channel_layout->opaque;
        எனில் (ret < 0)
            திரும்பு ret;
        எனில் (channel_layout->order != AV_CHANNEL_ORDER_UNSPEC)
            க்கு (முழு i = 0; i < channel_layout->nb_channels; i++)
                custom.u.map[i].id = av_channel_layout_channel_from_index(channel_layout, i);
        av_channel_layout_uninit(channel_layout);
        *channel_layout = custom;
        channel_layout->opaque = opaque;
        திரும்பு 0;
        }
    நிலை AV_CHANNEL_ORDER_AMBISONIC:
        எனில் (channel_layout->order == AV_CHANNEL_ORDER_CUSTOM) {
            int64_t mask;
            முழு nb_channels = channel_layout->nb_channels;
            முழு amb_order = av_channel_layout_ambisonic_order(channel_layout);
            எனில் (amb_order < 0)
                திரும்பு AVERROR(ENOSYS);
            mask = masked_description(channel_layout, (amb_order + 1) * (amb_order + 1));
            எனில் (mask < 0)
                திரும்பு AVERROR(ENOSYS);
            lossy = has_channel_names(channel_layout);
            எனில் (!lossy || allow_lossy) {
                வெறுமை *opaque = channel_layout->opaque;
                av_channel_layout_uninit(channel_layout);
                channel_layout->order       = AV_CHANNEL_ORDER_AMBISONIC;
                channel_layout->nb_channels = nb_channels;
                channel_layout->u.mask      = mask;
                channel_layout->opaque      = opaque;
                திரும்பு lossy;
            }
        }
        திரும்பு AVERROR(ENOSYS);
    இயல்பு:
        திரும்பு AVERROR(EINVAL);
    }
}
