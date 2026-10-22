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

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/avassert.h"
#ಅನ್ತರ್ಭಾವ "libavutil/buffer.h"
#ಅನ್ತರ್ಭಾವ "libavutil/dict.h"
#ಅನ್ತರ್ಭಾವ "libavutil/display.h"
#ಅನ್ತರ್ಭಾವ "libavutil/downmix_info.h"
#ಅನ್ತರ್ಭಾವ "libavutil/error.h"
#ಅನ್ತರ್ಭಾವ "libavutil/frame.h"
#ಅನ್ತರ್ಭಾವ "libavutil/macros.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"
#ಅನ್ತರ್ಭಾವ "libavutil/motion_vector.h"
#ಅನ್ತರ್ಭಾವ "libavutil/spherical.h"
#ಅನ್ತರ್ಭಾವ "libavutil/stereo3d.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ಗಣ_2 {
    AVFrame_Side_ದತ್ತಾಂಶ **sd;
    ಪೂರ್ಣಾಂಕ            nb_sd;
} ಗಣ_2;

/* Every entry below carries a payload laid out as AVFrameSideDataType
 * documents for its type: a producer owes that layout even when no consumer
 * reads the buffer back. The small number that identifies an entry in the
 * reference output therefore lives in the metadata dictionary, which
 * av_frame_side_data_clone() copies along with the buffer. */
ಸ್ಥಿರ ಶೂನ್ಯ ಗಣ_marker(AVFrame_Side_ದತ್ತಾಂಶ *sd, ಪೂರ್ಣಾಂಕ marker)
{
    ಅಕ್ಷರ ಮೌಲ್ಯ[16];

    snprintf(ಮೌಲ್ಯ, ಗಾತ್ರ(ಮೌಲ್ಯ), "%d", marker);
    av_assert0(av_dict_ಗಣ(&sd->metadata, "marker", ಮೌಲ್ಯ, 0) >= 0);
}

ಸ್ಥಿರ AVFrame_Side_ದತ್ತಾಂಶ *new_ನಮೂದು(ಗಣ_2 *s, ಎಣಿಕೆ AVFrame_Side_ದತ್ತಾಂಶ_Type type,
                                  ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *payload, size_t ಗಾತ್ರ_2, ಪೂರ್ಣಾಂಕ marker)
{
    AVFrame_Side_ದತ್ತಾಂಶ *sd = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_new(&s->sd, &s->nb_sd, type,
                                                 ಗಾತ್ರ_2, 0);

    av_assert0(sd && sd->ಗಾತ್ರ_2 == ಗಾತ್ರ_2);
    ಸ್ಮರಣೆ_ನಕಲು(sd->ದತ್ತಾಂಶ, payload, ಗಾತ್ರ_2);
    ಗಣ_marker(sd, marker);
    ಹಿಂತಿರುಗಿ sd;
}

ಸ್ಥಿರ AVBufferRef *payload_ಬಫರ್(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *payload, size_t ಗಾತ್ರ_2)
{
    AVBufferRef *buf = av_ಬಫರ್_alloc(ಗಾತ್ರ_2);

    av_assert0(buf);
    ಸ್ಮರಣೆ_ನಕಲು(buf->ದತ್ತಾಂಶ, payload, ಗಾತ್ರ_2);
    ಹಿಂತಿರುಗಿ buf;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ನಮೂದು_marker(ಸ್ಥಿರಾಂಕ AVFrame_Side_ದತ್ತಾಂಶ *sd)
{
    ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *e = av_dict_get(sd->metadata, "marker", ಖಾಲಿ, 0);

    ಹಿಂತಿರುಗಿ e ? e->ಮೌಲ್ಯ : "none";
}

ಸ್ಥಿರ ಶೂನ್ಯ print_ಗಣ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *label, ಸ್ಥಿರಾಂಕ ಗಣ_2 *s)
{
    ಬರೆ("%s: n=%d\n", label, s->nb_sd);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < s->nb_sd; i++)
        ಬರೆ("  [%d] %s marker=%s\n", i,
               av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_name(s->sd[i]->type),
               ನಮೂದು_marker(s->sd[i]));
}

/* Dumps a set by looking each type up instead of walking the array. Removal is
 * documented to drop the matching entries, not to keep the survivors where
 * they were, so printing by index would tie the reference to the current habit
 * of moving the last entry into the freed slot. */
ಸ್ಥಿರ ಶೂನ್ಯ print_lookup(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *label, ಸ್ಥಿರಾಂಕ ಗಣ_2 *s,
                         ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVFrame_Side_ದತ್ತಾಂಶ_Type *types, size_t nb_types)
{
    ಬರೆ("%s: n=%d\n", label, s->nb_sd);
    ಗಾಗಿ (size_t i = 0; i < nb_types; i++) {
        ಸ್ಥಿರಾಂಕ AVFrame_Side_ದತ್ತಾಂಶ *sd =
            av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_get(s->sd, s->nb_sd, types[i]);
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_name(types[i]);

        ಆದರೆ (sd)
            ಬರೆ("    %s: marker=%s\n", name, ನಮೂದು_marker(sd));
        ಇಲ್ಲದಿದ್ದರೆ
            ಬರೆ("    %s: absent\n", name);
    }
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    /* desc / name accessors. */
    ಬರೆ("Testing av_frame_side_data_desc() / av_frame_side_data_name()\n");
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVFrame_Side_ದತ್ತಾಂಶ_Type ತಿಳಿದ[] = {
        AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_STEREO3_D,                    /* PROP_GLOBAL */
        AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DYNAMIC_HDR_PLUS,            /* PROP_COLOR_DEPENDENT */
        AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_SPHERICAL,                   /* PROP_GLOBAL|SIZE_DEPENDENT */
        AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DOWNMIX_INFO,                /* PROP_CHANNEL_DEPENDENT */
        AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_SEI_UNREGISTERED,            /* PROP_MULTI */
    };
    ಗಾಗಿ (size_t i = 0; i < FF_ARRAY_ELEMS(ತಿಳಿದ); i++) {
        ಸ್ಥಿರಾಂಕ AVSide_ದತ್ತಾಂಶ_Descriptor *d = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_desc(ತಿಳಿದ[i]);
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *n = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_name(ತಿಳಿದ[i]);
        /* Compare content: the API only promises a string identifying the
         * type, not the descriptor's own pointer. */
        ಬರೆ("  type=%d name_match=%s props=0x%x\n", ತಿಳಿದ[i],
               d && n && !strcmp(d->name, n) ? "yes" : "no",
               d ? d->props : 0);
    }

    /* Invalid / unmapped types must return NULL (sd_props gap). */
    {
        ಎಣಿಕೆ AVFrame_Side_ದತ್ತಾಂಶ_Type bad = (ಎಣಿಕೆ AVFrame_Side_ದತ್ತಾಂಶ_Type)-1;
        ಬರೆ("  invalid type desc=%s name=%s\n",
               av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_desc(bad) ? "non-null" : "null",
               av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_name(bad) ? "non-null" : "null");
    }

    /* Payloads. The two structs are allocated through their public
     * allocators because their sizes are not part of the public ABI. */
    size_t stereo3d_ಗಾತ್ರ, spherical_ಗಾತ್ರ;
    AVStereo3D         *stereo3d  = av_stereo3d_alloc_ಗಾತ್ರ(&stereo3d_ಗಾತ್ರ);
    AVSphericalMapping *spherical = av_spherical_alloc(&spherical_ಗಾತ್ರ);
    /* 16 bytes of uuid_iso_iec_11578 followed by user_data_payload_byte. */
    uint8_t udu[16 + 8] = {
        0x9a, 0x21, 0xf3, 0x4d, 0x6b, 0x1c, 0x47, 0x8e,
        0xa5, 0x30, 0xc2, 0x7f, 0x11, 0x8d, 0x46, 0x02,
        'p',  'a',  'y',  'l',  'o',  'a',  'd',  '1',
    };
    int32_t displaymatrix[9];
    /* src_x = dst_x + motion_x / motion_scale, likewise for y. */
    AVMotion_ಸದಿಶ mvs[2] = {
        { .ಮೂಲ = -1, .w = 16, .h = 16, .src_x = 32, .src_y = 48,
          .dst_x = 40, .dst_y = 48, .motion_x = -8, .motion_y = 0,
          .motion_scale = 1 },
        { .ಮೂಲ =  1, .w =  8, .h =  8, .src_x = 64, .src_y = 64,
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
    stereo3d->primary_eye = AV_PRIMARY_EYE_ಎಡ;
    stereo3d->baseline    = 65000;

    spherical->projection = AV_SPHERICAL_EQUIRECTANGULAR;
    spherical->yaw        = 90 << 16;

    av_display_rotation_ಗಣ(displaymatrix, 90.0);

    /* Populate a set with several types, one of them MULTI. */
    ಗಣ_2 ಗಣ = { 0 };
    new_ನಮೂದು(&ಗಣ, AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_STEREO3_D, stereo3d, stereo3d_ಗಾತ್ರ, 100);
    new_ನಮೂದು(&ಗಣ, AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DOWNMIX_INFO, &downmix, ಗಾತ್ರ(downmix),
              200);
    new_ನಮೂದು(&ಗಣ, AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_SEI_UNREGISTERED, udu, ಗಾತ್ರ(udu), 1);
    udu[ಗಾತ್ರ(udu) - 1] = '2';
    new_ನಮೂದು(&ಗಣ, AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_SEI_UNREGISTERED, udu, ಗಾತ್ರ(udu), 2);
    new_ನಮೂದು(&ಗಣ, AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_SPHERICAL, spherical, spherical_ಗಾತ್ರ, 300);
    /* Entries are appended, so this dump is the insertion order by
     * construction and shows both MULTI entries. */
    print_ಗಣ("\nInitial set", &ಗಣ);

    /* Types probed by every dump below. */
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVFrame_Side_ದತ್ತಾಂಶ_Type probed[] = {
        AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_STEREO3_D,
        AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DOWNMIX_INFO,
        AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_SEI_UNREGISTERED,
        AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_SPHERICAL,
        AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DISPLAYMATRIX,
        AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_MOTION_VECTORS,
    };

    /* get / get_c: present and missing types. */
    ಬರೆ("\nTesting av_frame_side_data_get()\n");
    {
        ಸ್ಥಿರಾಂಕ AVFrame_Side_ದತ್ತಾಂಶ *got =
            av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_get(ಗಣ.sd, ಗಣ.nb_sd, AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_STEREO3_D);
        ಬರೆ("  stereo3d: %s marker=%s payload_match=%s\n",
               got ? "found" : "missing", got ? ನಮೂದು_marker(got) : "none",
               got && got->ಗಾತ್ರ_2 == stereo3d_ಗಾತ್ರ &&
               !memcmp(got->ದತ್ತಾಂಶ, stereo3d, stereo3d_ಗಾತ್ರ) ? "yes" : "no");
        got = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_get(ಗಣ.sd, ಗಣ.nb_sd,
                                     AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_MASTERING_DISPLAY_METADATA);
        ಬರೆ("  mastering (absent): %s\n", got ? "FAIL" : "null");
    }

    /* remove by type clears all matching entries (including duplicates). */
    ಬರೆ("\nTesting av_frame_side_data_remove()\n");
    av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_remove(&ಗಣ.sd, &ಗಣ.nb_sd,
                              AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_SEI_UNREGISTERED);
    print_lookup("  after remove SEI_UNREGISTERED", &ಗಣ,
                 probed, FF_ARRAY_ELEMS(probed));

    /* remove_by_props: PROP_GLOBAL drops STEREO3D and SPHERICAL. */
    ಬರೆ("\nTesting av_frame_side_data_remove_by_props()\n");
    av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_remove_by_props(&ಗಣ.sd, &ಗಣ.nb_sd,
                                       AV_SIDE_ದತ್ತಾಂಶ_PROP_GLOBAL);
    print_lookup("  after remove_by_props(GLOBAL)", &ಗಣ,
                 probed, FF_ARRAY_ELEMS(probed));

    /* Clone: copy remaining entry into a second set. */
    ಬರೆ("\nTesting av_frame_side_data_clone()\n");
    ಗಣ_2 dst = { 0 };
    ಆದರೆ (ಗಣ.nb_sd > 0) {
        ಪೂರ್ಣಾಂಕ ret = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_clone(&dst.sd, &dst.nb_sd,
                                           ಗಣ.sd[0], 0);
        ಬರೆ("  clone into empty: ret=%d nb=%d marker=%s\n", ret, dst.nb_sd,
               dst.nb_sd ? ನಮೂದು_marker(dst.sd[0]) : "none");

        /* Same type again without REPLACE must fail with EEXIST. */
        ret = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_clone(&dst.sd, &dst.nb_sd, ಗಣ.sd[0], 0);
        ಬರೆ("  clone duplicate no REPLACE: ret==AVERROR(EEXIST)=%s\n",
               ret == AVERROR(EEXIST) ? "yes" : "no");

        /* With REPLACE, clone replaces the existing entry in place. */
        ret = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_clone(&dst.sd, &dst.nb_sd, ಗಣ.sd[0],
                                       AV_ಚೌಕಟ್ಟು_SIDE_ದತ್ತಾಂಶ_FLAG_REPLACE);
        ಬರೆ("  clone REPLACE: ret=%d nb=%d\n", ret, dst.nb_sd);

        /* Invalid args. */
        ret = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_clone(ಖಾಲಿ, &dst.nb_sd, ಗಣ.sd[0], 0);
        ಬರೆ("  clone NULL sd: ret==AVERROR(EINVAL)=%s\n",
               ret == AVERROR(EINVAL) ? "yes" : "no");
    }

    /* add: buffer ownership transfer and NEW_REF. */
    ಬರೆ("\nTesting av_frame_side_data_add()\n");
    {
        AVBufferRef *buf = payload_ಬಫರ್(displaymatrix, ಗಾತ್ರ(displaymatrix));

        AVFrame_Side_ದತ್ತಾಂಶ *sd_added =
            av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_ಕೂಡಿಸು(&dst.sd, &dst.nb_sd,
                                   AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DISPLAYMATRIX,
                                   &buf, AV_ಚೌಕಟ್ಟು_SIDE_ದತ್ತಾಂಶ_FLAG_UNIQUE);
        ಬರೆ("  add (move): added=%s pbuf_nulled=%s\n",
               sd_added ? "yes" : "no", buf == ಖಾಲಿ ? "yes" : "no");
        ಆದರೆ (sd_added)
            ಗಣ_marker(sd_added, 999);

        /* NEW_REF: the caller retains its reference. */
        AVBufferRef *keep = payload_ಬಫರ್(mvs, ಗಾತ್ರ(mvs));
        sd_added = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_ಕೂಡಿಸು(&dst.sd, &dst.nb_sd,
                                          AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_MOTION_VECTORS, &keep,
                                          AV_ಚೌಕಟ್ಟು_SIDE_ದತ್ತಾಂಶ_FLAG_NEW_REF);
        ಬರೆ("  add (NEW_REF): added=%s caller_ref_kept=%s nb_mvs=%d\n",
               sd_added ? "yes" : "no", keep ? "yes" : "no",
               sd_added ? (ಪೂರ್ಣಾಂಕ)(sd_added->ಗಾತ್ರ_2 / ಗಾತ್ರ(AVMotion_ಸದಿಶ)) : -1);
        ಆದರೆ (sd_added)
            ಗಣ_marker(sd_added, 42);
        av_ಬಫರ್_unref(&keep);

        /* REPLACE on existing entry: same type, payload swaps in place. */
        int32_t replacement[9];
        av_display_rotation_ಗಣ(replacement, 180.0);
        AVBufferRef *repl = payload_ಬಫರ್(replacement, ಗಾತ್ರ(replacement));
        sd_added = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_ಕೂಡಿಸು(&dst.sd, &dst.nb_sd,
                                          AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DISPLAYMATRIX, &repl,
                                          AV_ಚೌಕಟ್ಟು_SIDE_ದತ್ತಾಂಶ_FLAG_REPLACE);
        ಆದರೆ (sd_added)
            ಗಣ_marker(sd_added, 1234);
        {
            ಸ್ಥಿರಾಂಕ AVFrame_Side_ದತ್ತಾಂಶ *after =
                av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_get(dst.sd, dst.nb_sd,
                                       AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DISPLAYMATRIX);
            ಬರೆ("  add (REPLACE existing): added=%s marker=%s"
                   " payload_match=%s\n",
                   sd_added ? "yes" : "no",
                   after ? ನಮೂದು_marker(after) : "none",
                   after && after->ಗಾತ್ರ_2 == ಗಾತ್ರ(replacement) &&
                   !memcmp(after->ದತ್ತಾಂಶ, replacement, ಗಾತ್ರ(replacement)) ?
                   "yes" : "no");
        }
    }

    /* clone with UNIQUE: existing same-type entry is removed first. dst
     * already has a set.sd[0]->type entry from the REPLACE clone above. */
    ಬರೆ("\nTesting av_frame_side_data_clone() UNIQUE\n");
    ಆದರೆ (ಗಣ.nb_sd > 0) {
        ಪೂರ್ಣಾಂಕ before = dst.nb_sd;
        ಪೂರ್ಣಾಂಕ ret = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_clone(&dst.sd, &dst.nb_sd, ಗಣ.sd[0],
                                           AV_ಚೌಕಟ್ಟು_SIDE_ದತ್ತಾಂಶ_FLAG_UNIQUE);
        ಬರೆ("  clone UNIQUE: ret=%d before=%d after=%d\n",
               ret, before, dst.nb_sd);
    }

    print_lookup("\nFinal dst", &dst, probed, FF_ARRAY_ELEMS(probed));

    av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_free(&dst.sd, &dst.nb_sd);
    av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_free(&ಗಣ.sd, &ಗಣ.nb_sd);
    ಬರೆ("\nfree: set_nb=%d dst_nb=%d\n", ಗಣ.nb_sd, dst.nb_sd);

    av_free(stereo3d);
    av_free(spherical);

    ಹಿಂತಿರುಗಿ 0;
}
