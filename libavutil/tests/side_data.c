/*
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
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/buffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/dict.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/display.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/downmix_info.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/frame.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/motion_vector.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/spherical.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/stereo3d.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ਸੈੱਟ_2 {
    AVFrame_Side_ਅੰਕੜੇ **sd;
    ਪੂਰਨ            nb_sd;
} ਸੈੱਟ_2;

/* Every entry below carries a payload laid out as AVFrameSideDataType
 * documents for its type: a producer owes that layout even when no consumer
 * reads the buffer back. The small number that identifies an entry in the
 * reference output therefore lives in the metadata dictionary, which
 * av_frame_side_data_clone() copies along with the buffer. */
ਸਥਿਰ ਖਾਲੀ ਸੈੱਟ_marker(AVFrame_Side_ਅੰਕੜੇ *sd, ਪੂਰਨ marker)
{
    ਅੱਖਰ ਮੁੱਲ[16];

    snprintf(ਮੁੱਲ, ਆਕਾਰ(ਮੁੱਲ), "%d", marker);
    av_assert0(av_dict_ਸੈੱਟ(&sd->metadata, "marker", ਮੁੱਲ, 0) >= 0);
}

ਸਥਿਰ AVFrame_Side_ਅੰਕੜੇ *new_ਇੰਦਰਾਜ(ਸੈੱਟ_2 *s, ਗਿਣਤੀ AVFrame_Side_ਅੰਕੜੇ_Type type,
                                  ਅਚਲ ਖਾਲੀ *payload, size_t ਮਾਪ, ਪੂਰਨ marker)
{
    AVFrame_Side_ਅੰਕੜੇ *sd = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_new(&s->sd, &s->nb_sd, type,
                                                 ਮਾਪ, 0);

    av_assert0(sd && sd->ਮਾਪ == ਮਾਪ);
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(sd->ਅੰਕੜੇ, payload, ਮਾਪ);
    ਸੈੱਟ_marker(sd, marker);
    ਵਾਪਸ sd;
}

ਸਥਿਰ AVBufferRef *payload_ਬਫਰ(ਅਚਲ ਖਾਲੀ *payload, size_t ਮਾਪ)
{
    AVBufferRef *buf = av_ਬਫਰ_alloc(ਮਾਪ);

    av_assert0(buf);
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(buf->ਅੰਕੜੇ, payload, ਮਾਪ);
    ਵਾਪਸ buf;
}

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਇੰਦਰਾਜ_marker(ਅਚਲ AVFrame_Side_ਅੰਕੜੇ *sd)
{
    ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *e = av_dict_get(sd->metadata, "marker", ਨਿਰਾ, 0);

    ਵਾਪਸ e ? e->ਮੁੱਲ : "none";
}

ਸਥਿਰ ਖਾਲੀ print_ਸੈੱਟ(ਅਚਲ ਅੱਖਰ *label, ਅਚਲ ਸੈੱਟ_2 *s)
{
    ਲਿਖੋ("%s: n=%d\n", label, s->nb_sd);
    ਲਈ (ਪੂਰਨ i = 0; i < s->nb_sd; i++)
        ਲਿਖੋ("  [%d] %s marker=%s\n", i,
               av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_name(s->sd[i]->type),
               ਇੰਦਰਾਜ_marker(s->sd[i]));
}

/* Dumps a set by looking each type up instead of walking the array. Removal is
 * documented to drop the matching entries, not to keep the survivors where
 * they were, so printing by index would tie the reference to the current habit
 * of moving the last entry into the freed slot. */
ਸਥਿਰ ਖਾਲੀ print_lookup(ਅਚਲ ਅੱਖਰ *label, ਅਚਲ ਸੈੱਟ_2 *s,
                         ਅਚਲ ਗਿਣਤੀ AVFrame_Side_ਅੰਕੜੇ_Type *types, size_t nb_types)
{
    ਲਿਖੋ("%s: n=%d\n", label, s->nb_sd);
    ਲਈ (size_t i = 0; i < nb_types; i++) {
        ਅਚਲ AVFrame_Side_ਅੰਕੜੇ *sd =
            av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_get(s->sd, s->nb_sd, types[i]);
        ਅਚਲ ਅੱਖਰ *name = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_name(types[i]);

        ਜੇ (sd)
            ਲਿਖੋ("    %s: marker=%s\n", name, ਇੰਦਰਾਜ_marker(sd));
        ਨਹੀਂਤਾਂ
            ਲਿਖੋ("    %s: absent\n", name);
    }
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    /* desc / name accessors. */
    ਲਿਖੋ("Testing av_frame_side_data_desc() / av_frame_side_data_name()\n");
    ਸਥਿਰ ਅਚਲ ਗਿਣਤੀ AVFrame_Side_ਅੰਕੜੇ_Type ਗਿਆਤ[] = {
        AV_ਚੌਖਟਾ_ਅੰਕੜੇ_STEREO3_D,                    /* PROP_GLOBAL */
        AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DYNAMIC_HDR_PLUS,            /* PROP_COLOR_DEPENDENT */
        AV_ਚੌਖਟਾ_ਅੰਕੜੇ_SPHERICAL,                   /* PROP_GLOBAL|SIZE_DEPENDENT */
        AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DOWNMIX_INFO,                /* PROP_CHANNEL_DEPENDENT */
        AV_ਚੌਖਟਾ_ਅੰਕੜੇ_SEI_UNREGISTERED,            /* PROP_MULTI */
    };
    ਲਈ (size_t i = 0; i < FF_ARRAY_ELEMS(ਗਿਆਤ); i++) {
        ਅਚਲ AVSide_ਅੰਕੜੇ_Descriptor *d = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_desc(ਗਿਆਤ[i]);
        ਅਚਲ ਅੱਖਰ *n = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_name(ਗਿਆਤ[i]);
        /* Compare content: the API only promises a string identifying the
         * type, not the descriptor's own pointer. */
        ਲਿਖੋ("  type=%d name_match=%s props=0x%x\n", ਗਿਆਤ[i],
               d && n && !strcmp(d->name, n) ? "yes" : "no",
               d ? d->props : 0);
    }

    /* Invalid / unmapped types must return NULL (sd_props gap). */
    {
        ਗਿਣਤੀ AVFrame_Side_ਅੰਕੜੇ_Type bad = (ਗਿਣਤੀ AVFrame_Side_ਅੰਕੜੇ_Type)-1;
        ਲਿਖੋ("  invalid type desc=%s name=%s\n",
               av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_desc(bad) ? "non-null" : "null",
               av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_name(bad) ? "non-null" : "null");
    }

    /* Payloads. The two structs are allocated through their public
     * allocators because their sizes are not part of the public ABI. */
    size_t stereo3d_ਮਾਪ, spherical_ਮਾਪ;
    AVStereo3D         *stereo3d  = av_stereo3d_alloc_ਮਾਪ(&stereo3d_ਮਾਪ);
    AVSphericalMapping *spherical = av_spherical_alloc(&spherical_ਮਾਪ);
    /* 16 bytes of uuid_iso_iec_11578 followed by user_data_payload_byte. */
    uint8_t udu[16 + 8] = {
        0x9a, 0x21, 0xf3, 0x4d, 0x6b, 0x1c, 0x47, 0x8e,
        0xa5, 0x30, 0xc2, 0x7f, 0x11, 0x8d, 0x46, 0x02,
        'p',  'a',  'y',  'l',  'o',  'a',  'd',  '1',
    };
    int32_t displaymatrix[9];
    /* src_x = dst_x + motion_x / motion_scale, likewise for y. */
    AVMotion_ਸਦਿਸ਼ mvs[2] = {
        { .ਸਰੋਤ = -1, .w = 16, .h = 16, .src_x = 32, .src_y = 48,
          .dst_x = 40, .dst_y = 48, .motion_x = -8, .motion_y = 0,
          .motion_scale = 1 },
        { .ਸਰੋਤ =  1, .w =  8, .h =  8, .src_x = 64, .src_y = 64,
          .dst_x = 64, .dst_y = 72, .motion_x = 0, .motion_y = -8,
          .motion_scale = 1 },
    };
    /* The mix levels are absolute linear scale factors, not dB. */
    AVDownmixInfo downmix = {
        .preferred_downmix_type  = AV_DOWNMIX_TYPE_LTRT,
        .center_mix_level        = 0.5,
        .center_mix_level_ltrt   = 0.625,
        .surround_mix_level      = 0.25,
        .surround_mix_level_ltrt = 0.375,
        .lfe_mix_level           = 0.125,
    };

    av_assert0(stereo3d && spherical);

    stereo3d->type        = AV_STEREO3D_SIDEBYSIDE;
    stereo3d->view        = AV_STEREO3D_VIEW_PACKED;
    stereo3d->primary_eye = AV_PRIMARY_EYE_ਖੱਬਾ;
    stereo3d->baseline    = 65000;

    spherical->projection = AV_SPHERICAL_EQUIRECTANGULAR;
    spherical->yaw        = 90 << 16;

    av_display_rotation_ਸੈੱਟ(displaymatrix, 90.0);

    /* Populate a set with several types, one of them MULTI. */
    ਸੈੱਟ_2 ਸੈੱਟ = { 0 };
    new_ਇੰਦਰਾਜ(&ਸੈੱਟ, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_STEREO3_D, stereo3d, stereo3d_ਮਾਪ, 100);
    new_ਇੰਦਰਾਜ(&ਸੈੱਟ, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DOWNMIX_INFO, &downmix, ਆਕਾਰ(downmix),
              200);
    new_ਇੰਦਰਾਜ(&ਸੈੱਟ, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_SEI_UNREGISTERED, udu, ਆਕਾਰ(udu), 1);
    udu[ਆਕਾਰ(udu) - 1] = '2';
    new_ਇੰਦਰਾਜ(&ਸੈੱਟ, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_SEI_UNREGISTERED, udu, ਆਕਾਰ(udu), 2);
    new_ਇੰਦਰਾਜ(&ਸੈੱਟ, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_SPHERICAL, spherical, spherical_ਮਾਪ, 300);
    /* Entries are appended, so this dump is the insertion order by
     * construction and shows both MULTI entries. */
    print_ਸੈੱਟ("\nInitial set", &ਸੈੱਟ);

    /* Types probed by every dump below. */
    ਸਥਿਰ ਅਚਲ ਗਿਣਤੀ AVFrame_Side_ਅੰਕੜੇ_Type probed[] = {
        AV_ਚੌਖਟਾ_ਅੰਕੜੇ_STEREO3_D,
        AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DOWNMIX_INFO,
        AV_ਚੌਖਟਾ_ਅੰਕੜੇ_SEI_UNREGISTERED,
        AV_ਚੌਖਟਾ_ਅੰਕੜੇ_SPHERICAL,
        AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DISPLAYMATRIX,
        AV_ਚੌਖਟਾ_ਅੰਕੜੇ_MOTION_VECTORS,
    };

    /* get / get_c: present and missing types. */
    ਲਿਖੋ("\nTesting av_frame_side_data_get()\n");
    {
        ਅਚਲ AVFrame_Side_ਅੰਕੜੇ *got =
            av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_get(ਸੈੱਟ.sd, ਸੈੱਟ.nb_sd, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_STEREO3_D);
        ਲਿਖੋ("  stereo3d: %s marker=%s payload_match=%s\n",
               got ? "found" : "missing", got ? ਇੰਦਰਾਜ_marker(got) : "none",
               got && got->ਮਾਪ == stereo3d_ਮਾਪ &&
               !memcmp(got->ਅੰਕੜੇ, stereo3d, stereo3d_ਮਾਪ) ? "yes" : "no");
        got = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_get(ਸੈੱਟ.sd, ਸੈੱਟ.nb_sd,
                                     AV_ਚੌਖਟਾ_ਅੰਕੜੇ_MASTERING_DISPLAY_METADATA);
        ਲਿਖੋ("  mastering (absent): %s\n", got ? "FAIL" : "null");
    }

    /* remove by type clears all matching entries (including duplicates). */
    ਲਿਖੋ("\nTesting av_frame_side_data_remove()\n");
    av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_remove(&ਸੈੱਟ.sd, &ਸੈੱਟ.nb_sd,
                              AV_ਚੌਖਟਾ_ਅੰਕੜੇ_SEI_UNREGISTERED);
    print_lookup("  after remove SEI_UNREGISTERED", &ਸੈੱਟ,
                 probed, FF_ARRAY_ELEMS(probed));

    /* remove_by_props: PROP_GLOBAL drops STEREO3D and SPHERICAL. */
    ਲਿਖੋ("\nTesting av_frame_side_data_remove_by_props()\n");
    av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_remove_by_props(&ਸੈੱਟ.sd, &ਸੈੱਟ.nb_sd,
                                       AV_SIDE_ਅੰਕੜੇ_PROP_GLOBAL);
    print_lookup("  after remove_by_props(GLOBAL)", &ਸੈੱਟ,
                 probed, FF_ARRAY_ELEMS(probed));

    /* Clone: copy remaining entry into a second set. */
    ਲਿਖੋ("\nTesting av_frame_side_data_clone()\n");
    ਸੈੱਟ_2 dst = { 0 };
    ਜੇ (ਸੈੱਟ.nb_sd > 0) {
        ਪੂਰਨ ret = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_clone(&dst.sd, &dst.nb_sd,
                                           ਸੈੱਟ.sd[0], 0);
        ਲਿਖੋ("  clone into empty: ret=%d nb=%d marker=%s\n", ret, dst.nb_sd,
               dst.nb_sd ? ਇੰਦਰਾਜ_marker(dst.sd[0]) : "none");

        /* Same type again without REPLACE must fail with EEXIST. */
        ret = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_clone(&dst.sd, &dst.nb_sd, ਸੈੱਟ.sd[0], 0);
        ਲਿਖੋ("  clone duplicate no REPLACE: ret==AVERROR(EEXIST)=%s\n",
               ret == AVERROR(EEXIST) ? "yes" : "no");

        /* With REPLACE, clone replaces the existing entry in place. */
        ret = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_clone(&dst.sd, &dst.nb_sd, ਸੈੱਟ.sd[0],
                                       AV_ਚੌਖਟਾ_SIDE_ਅੰਕੜੇ_FLAG_REPLACE);
        ਲਿਖੋ("  clone REPLACE: ret=%d nb=%d\n", ret, dst.nb_sd);

        /* Invalid args. */
        ret = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_clone(ਨਿਰਾ, &dst.nb_sd, ਸੈੱਟ.sd[0], 0);
        ਲਿਖੋ("  clone NULL sd: ret==AVERROR(EINVAL)=%s\n",
               ret == AVERROR(EINVAL) ? "yes" : "no");
    }

    /* add: buffer ownership transfer and NEW_REF. */
    ਲਿਖੋ("\nTesting av_frame_side_data_add()\n");
    {
        AVBufferRef *buf = payload_ਬਫਰ(displaymatrix, ਆਕਾਰ(displaymatrix));

        AVFrame_Side_ਅੰਕੜੇ *sd_added =
            av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_ਜੋੜੋ(&dst.sd, &dst.nb_sd,
                                   AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DISPLAYMATRIX,
                                   &buf, AV_ਚੌਖਟਾ_SIDE_ਅੰਕੜੇ_FLAG_UNIQUE);
        ਲਿਖੋ("  add (move): added=%s pbuf_nulled=%s\n",
               sd_added ? "yes" : "no", buf == ਨਿਰਾ ? "yes" : "no");
        ਜੇ (sd_added)
            ਸੈੱਟ_marker(sd_added, 999);

        /* NEW_REF: the caller retains its reference. */
        AVBufferRef *keep = payload_ਬਫਰ(mvs, ਆਕਾਰ(mvs));
        sd_added = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_ਜੋੜੋ(&dst.sd, &dst.nb_sd,
                                          AV_ਚੌਖਟਾ_ਅੰਕੜੇ_MOTION_VECTORS, &keep,
                                          AV_ਚੌਖਟਾ_SIDE_ਅੰਕੜੇ_FLAG_NEW_REF);
        ਲਿਖੋ("  add (NEW_REF): added=%s caller_ref_kept=%s nb_mvs=%d\n",
               sd_added ? "yes" : "no", keep ? "yes" : "no",
               sd_added ? (ਪੂਰਨ)(sd_added->ਮਾਪ / ਆਕਾਰ(AVMotion_ਸਦਿਸ਼)) : -1);
        ਜੇ (sd_added)
            ਸੈੱਟ_marker(sd_added, 42);
        av_ਬਫਰ_unref(&keep);

        /* REPLACE on existing entry: same type, payload swaps in place. */
        int32_t replacement[9];
        av_display_rotation_ਸੈੱਟ(replacement, 180.0);
        AVBufferRef *repl = payload_ਬਫਰ(replacement, ਆਕਾਰ(replacement));
        sd_added = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_ਜੋੜੋ(&dst.sd, &dst.nb_sd,
                                          AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DISPLAYMATRIX, &repl,
                                          AV_ਚੌਖਟਾ_SIDE_ਅੰਕੜੇ_FLAG_REPLACE);
        ਜੇ (sd_added)
            ਸੈੱਟ_marker(sd_added, 1234);
        {
            ਅਚਲ AVFrame_Side_ਅੰਕੜੇ *after =
                av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_get(dst.sd, dst.nb_sd,
                                       AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DISPLAYMATRIX);
            ਲਿਖੋ("  add (REPLACE existing): added=%s marker=%s"
                   " payload_match=%s\n",
                   sd_added ? "yes" : "no",
                   after ? ਇੰਦਰਾਜ_marker(after) : "none",
                   after && after->ਮਾਪ == ਆਕਾਰ(replacement) &&
                   !memcmp(after->ਅੰਕੜੇ, replacement, ਆਕਾਰ(replacement)) ?
                   "yes" : "no");
        }
    }

    /* clone with UNIQUE: existing same-type entry is removed first. dst
     * already has a set.sd[0]->type entry from the REPLACE clone above. */
    ਲਿਖੋ("\nTesting av_frame_side_data_clone() UNIQUE\n");
    ਜੇ (ਸੈੱਟ.nb_sd > 0) {
        ਪੂਰਨ before = dst.nb_sd;
        ਪੂਰਨ ret = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_clone(&dst.sd, &dst.nb_sd, ਸੈੱਟ.sd[0],
                                           AV_ਚੌਖਟਾ_SIDE_ਅੰਕੜੇ_FLAG_UNIQUE);
        ਲਿਖੋ("  clone UNIQUE: ret=%d before=%d after=%d\n",
               ret, before, dst.nb_sd);
    }

    print_lookup("\nFinal dst", &dst, probed, FF_ARRAY_ELEMS(probed));

    av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_free(&dst.sd, &dst.nb_sd);
    av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_free(&ਸੈੱਟ.sd, &ਸੈੱਟ.nb_sd);
    ਲਿਖੋ("\nfree: set_nb=%d dst_nb=%d\n", ਸੈੱਟ.nb_sd, dst.nb_sd);

    av_free(stereo3d);
    av_free(spherical);

    ਵਾਪਸ 0;
}
