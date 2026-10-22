/*
 * Copyright (c) 2023 Jan Ekström <jeebjp@gmail.com>
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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/frame.c"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/internal.h"

ਸਥਿਰ ਖਾਲੀ print_entries(ਅਚਲ AVFrame_Side_ਅੰਕੜੇ **sd, ਅਚਲ ਪੂਰਨ nb_sd)
{
    ਲਈ (ਪੂਰਨ i = 0; i < nb_sd; i++) {
        ਅਚਲ AVFrame_Side_ਅੰਕੜੇ *ਇੰਦਰਾਜ = sd[i];

        ਲਿਖੋ("sd %d (size %zu), %s",
               i, ਇੰਦਰਾਜ->ਮਾਪ, av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_name(ਇੰਦਰਾਜ->type));

        ਜੇ (ਇੰਦਰਾਜ->type != AV_ਚੌਖਟਾ_ਅੰਕੜੇ_SEI_UNREGISTERED) {
            ਅੱਖਰ_ਲਿਖੋ('\n');
            ਜਾਰੀ;
        }

        ਲਿਖੋ(": %d\n", *(int32_t *)ਇੰਦਰਾਜ->ਅੰਕੜੇ);
    }
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ਚੌਖਟਾ_Side_ਅੰਕੜੇ_ਸੈੱਟ {
    AVFrame_Side_ਅੰਕੜੇ **sd;
    ਪੂਰਨ            nb_sd;
} ਚੌਖਟਾ_Side_ਅੰਕੜੇ_ਸੈੱਟ;

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    ਚੌਖਟਾ_Side_ਅੰਕੜੇ_ਸੈੱਟ ਸੈੱਟ = { 0 };

    av_assert0(
        av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_new(&ਸੈੱਟ.sd, &ਸੈੱਟ.nb_sd,
                               AV_ਚੌਖਟਾ_ਅੰਕੜੇ_CONTENT_LIGHT_LEVEL,
                               ਆਕਾਰ(int64_t), 0));
    av_assert0(
        av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_new(&ਸੈੱਟ.sd, &ਸੈੱਟ.nb_sd,
                               AV_ਚੌਖਟਾ_ਅੰਕੜੇ_CONTENT_LIGHT_LEVEL,
                               ਆਕਾਰ(int32_t), AV_ਚੌਖਟਾ_SIDE_ਅੰਕੜੇ_FLAG_REPLACE));

    // test entries in the middle
    ਲਈ (ਪੂਰਨ ਮੁੱਲ = 1; ਮੁੱਲ < 4; ਮੁੱਲ++) {
        AVFrame_Side_ਅੰਕੜੇ *sd = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_new(
            &ਸੈੱਟ.sd, &ਸੈੱਟ.nb_sd, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_SEI_UNREGISTERED,
            ਆਕਾਰ(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->ਅੰਕੜੇ = ਮੁੱਲ;
    }

    av_assert0(
        av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_new(
            &ਸੈੱਟ.sd, &ਸੈੱਟ.nb_sd, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_SPHERICAL,
           ਆਕਾਰ(int64_t), 0));

    av_assert0(
        av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_new(
            &ਸੈੱਟ.sd, &ਸੈੱਟ.nb_sd, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_SPHERICAL,
            ਆਕਾਰ(int32_t), AV_ਚੌਖਟਾ_SIDE_ਅੰਕੜੇ_FLAG_REPLACE));

    // test entries at the end
    ਲਈ (ਪੂਰਨ ਮੁੱਲ = 1; ਮੁੱਲ < 4; ਮੁੱਲ++) {
        AVFrame_Side_ਅੰਕੜੇ *sd = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_new(
            &ਸੈੱਟ.sd, &ਸੈੱਟ.nb_sd, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_SEI_UNREGISTERED,
            ਆਕਾਰ(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->ਅੰਕੜੇ = ਮੁੱਲ + 3;
    }

    puts("Initial addition results with duplicates:");
    print_entries((ਅਚਲ AVFrame_Side_ਅੰਕੜੇ **)ਸੈੱਟ.sd, ਸੈੱਟ.nb_sd);

    {
        AVFrame_Side_ਅੰਕੜੇ *sd = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_new(
            &ਸੈੱਟ.sd, &ਸੈੱਟ.nb_sd, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_SEI_UNREGISTERED,
            ਆਕਾਰ(int32_t), AV_ਚੌਖਟਾ_SIDE_ਅੰਕੜੇ_FLAG_UNIQUE);

        av_assert0(sd);

        *(int32_t *)sd->ਅੰਕੜੇ = 1337;
    }

    puts("\nFinal state after a single 'no-duplicates' addition:");
    print_entries((ਅਚਲ AVFrame_Side_ਅੰਕੜੇ **)ਸੈੱਟ.sd, ਸੈੱਟ.nb_sd);

    av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_free(&ਸੈੱਟ.sd, &ਸੈੱਟ.nb_sd);

    ਵਾਪਸ 0;
}
