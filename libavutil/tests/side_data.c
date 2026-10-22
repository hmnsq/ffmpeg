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

#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "libavutil/avassert.h"
#అన్తర్భావ "libavutil/buffer.h"
#అన్తర్భావ "libavutil/dict.h"
#అన్తర్భావ "libavutil/display.h"
#అన్తర్భావ "libavutil/downmix_info.h"
#అన్తర్భావ "libavutil/error.h"
#అన్తర్భావ "libavutil/frame.h"
#అన్తర్భావ "libavutil/macros.h"
#అన్తర్భావ "libavutil/mem.h"
#అన్తర్భావ "libavutil/motion_vector.h"
#అన్తర్భావ "libavutil/spherical.h"
#అన్తర్భావ "libavutil/stereo3d.h"

రకనిర్వచనం నిర్మాణం సమితి_2 {
    AVFrame_Side_దత్తాంశం **sd;
    పూర్ణాంకం            nb_sd;
} సమితి_2;

/* Every entry below carries a payload laid out as AVFrameSideDataType
 * documents for its type: a producer owes that layout even when no consumer
 * reads the buffer back. The small number that identifies an entry in the
 * reference output therefore lives in the metadata dictionary, which
 * av_frame_side_data_clone() copies along with the buffer. */
స్థిర శూన్య సమితి_marker(AVFrame_Side_దత్తాంశం *sd, పూర్ణాంకం marker)
{
    అక్షరం విలువ[16];

    snprintf(విలువ, పరిమాణం(విలువ), "%d", marker);
    av_assert0(av_dict_సమితి(&sd->metadata, "marker", విలువ, 0) >= 0);
}

స్థిర AVFrame_Side_దత్తాంశం *new_నమోదు(సమితి_2 *s, గణన AVFrame_Side_దత్తాంశం_Type type,
                                  స్థిరరాశి శూన్య *payload, size_t కొలత, పూర్ణాంకం marker)
{
    AVFrame_Side_దత్తాంశం *sd = av_చట్రం_side_దత్తాంశం_new(&s->sd, &s->nb_sd, type,
                                                 కొలత, 0);

    av_assert0(sd && sd->కొలత == కొలత);
    జ్ఞాపకం_నకలు(sd->దత్తాంశం, payload, కొలత);
    సమితి_marker(sd, marker);
    తిరిగి sd;
}

స్థిర AVBufferRef *payload_బఫరు(స్థిరరాశి శూన్య *payload, size_t కొలత)
{
    AVBufferRef *buf = av_బఫరు_alloc(కొలత);

    av_assert0(buf);
    జ్ఞాపకం_నకలు(buf->దత్తాంశం, payload, కొలత);
    తిరిగి buf;
}

స్థిర స్థిరరాశి అక్షరం *నమోదు_marker(స్థిరరాశి AVFrame_Side_దత్తాంశం *sd)
{
    స్థిరరాశి AVDictionary_నమోదు *e = av_dict_get(sd->metadata, "marker", ఖాళీ, 0);

    తిరిగి e ? e->విలువ : "none";
}

స్థిర శూన్య print_సమితి(స్థిరరాశి అక్షరం *label, స్థిరరాశి సమితి_2 *s)
{
    రాయి("%s: n=%d\n", label, s->nb_sd);
    కొరకు (పూర్ణాంకం i = 0; i < s->nb_sd; i++)
        రాయి("  [%d] %s marker=%s\n", i,
               av_చట్రం_side_దత్తాంశం_name(s->sd[i]->type),
               నమోదు_marker(s->sd[i]));
}

/* Dumps a set by looking each type up instead of walking the array. Removal is
 * documented to drop the matching entries, not to keep the survivors where
 * they were, so printing by index would tie the reference to the current habit
 * of moving the last entry into the freed slot. */
స్థిర శూన్య print_lookup(స్థిరరాశి అక్షరం *label, స్థిరరాశి సమితి_2 *s,
                         స్థిరరాశి గణన AVFrame_Side_దత్తాంశం_Type *types, size_t nb_types)
{
    రాయి("%s: n=%d\n", label, s->nb_sd);
    కొరకు (size_t i = 0; i < nb_types; i++) {
        స్థిరరాశి AVFrame_Side_దత్తాంశం *sd =
            av_చట్రం_side_దత్తాంశం_get(s->sd, s->nb_sd, types[i]);
        స్థిరరాశి అక్షరం *name = av_చట్రం_side_దత్తాంశం_name(types[i]);

        ఒకవేళ (sd)
            రాయి("    %s: marker=%s\n", name, నమోదు_marker(sd));
        లేకపోతే
            రాయి("    %s: absent\n", name);
    }
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    /* desc / name accessors. */
    రాయి("Testing av_frame_side_data_desc() / av_frame_side_data_name()\n");
    స్థిర స్థిరరాశి గణన AVFrame_Side_దత్తాంశం_Type తెలిసిన[] = {
        AV_చట్రం_దత్తాంశం_STEREO3_D,                    /* PROP_GLOBAL */
        AV_చట్రం_దత్తాంశం_DYNAMIC_HDR_PLUS,            /* PROP_COLOR_DEPENDENT */
        AV_చట్రం_దత్తాంశం_SPHERICAL,                   /* PROP_GLOBAL|SIZE_DEPENDENT */
        AV_చట్రం_దత్తాంశం_DOWNMIX_INFO,                /* PROP_CHANNEL_DEPENDENT */
        AV_చట్రం_దత్తాంశం_SEI_UNREGISTERED,            /* PROP_MULTI */
    };
    కొరకు (size_t i = 0; i < FF_ARRAY_ELEMS(తెలిసిన); i++) {
        స్థిరరాశి AVSide_దత్తాంశం_Descriptor *d = av_చట్రం_side_దత్తాంశం_desc(తెలిసిన[i]);
        స్థిరరాశి అక్షరం *n = av_చట్రం_side_దత్తాంశం_name(తెలిసిన[i]);
        /* Compare content: the API only promises a string identifying the
         * type, not the descriptor's own pointer. */
        రాయి("  type=%d name_match=%s props=0x%x\n", తెలిసిన[i],
               d && n && !strcmp(d->name, n) ? "yes" : "no",
               d ? d->props : 0);
    }

    /* Invalid / unmapped types must return NULL (sd_props gap). */
    {
        గణన AVFrame_Side_దత్తాంశం_Type bad = (గణన AVFrame_Side_దత్తాంశం_Type)-1;
        రాయి("  invalid type desc=%s name=%s\n",
               av_చట్రం_side_దత్తాంశం_desc(bad) ? "non-null" : "null",
               av_చట్రం_side_దత్తాంశం_name(bad) ? "non-null" : "null");
    }

    /* Payloads. The two structs are allocated through their public
     * allocators because their sizes are not part of the public ABI. */
    size_t stereo3d_కొలత, spherical_కొలత;
    AVStereo3D         *stereo3d  = av_stereo3d_alloc_కొలత(&stereo3d_కొలత);
    AVSphericalMapping *spherical = av_spherical_alloc(&spherical_కొలత);
    /* 16 bytes of uuid_iso_iec_11578 followed by user_data_payload_byte. */
    uint8_t udu[16 + 8] = {
        0x9a, 0x21, 0xf3, 0x4d, 0x6b, 0x1c, 0x47, 0x8e,
        0xa5, 0x30, 0xc2, 0x7f, 0x11, 0x8d, 0x46, 0x02,
        'p',  'a',  'y',  'l',  'o',  'a',  'd',  '1',
    };
    int32_t displaymatrix[9];
    /* src_x = dst_x + motion_x / motion_scale, likewise for y. */
    AVMotion_సదిశ mvs[2] = {
        { .ఆధారం = -1, .w = 16, .h = 16, .src_x = 32, .src_y = 48,
          .dst_x = 40, .dst_y = 48, .motion_x = -8, .motion_y = 0,
          .motion_scale = 1 },
        { .ఆధారం =  1, .w =  8, .h =  8, .src_x = 64, .src_y = 64,
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
    stereo3d->primary_eye = AV_PRIMARY_EYE_ఎడమ;
    stereo3d->baseline    = 65000;

    spherical->projection = AV_SPHERICAL_EQUIRECTANGULAR;
    spherical->yaw        = 90 << 16;

    av_display_rotation_సమితి(displaymatrix, 90.0);

    /* Populate a set with several types, one of them MULTI. */
    సమితి_2 సమితి = { 0 };
    new_నమోదు(&సమితి, AV_చట్రం_దత్తాంశం_STEREO3_D, stereo3d, stereo3d_కొలత, 100);
    new_నమోదు(&సమితి, AV_చట్రం_దత్తాంశం_DOWNMIX_INFO, &downmix, పరిమాణం(downmix),
              200);
    new_నమోదు(&సమితి, AV_చట్రం_దత్తాంశం_SEI_UNREGISTERED, udu, పరిమాణం(udu), 1);
    udu[పరిమాణం(udu) - 1] = '2';
    new_నమోదు(&సమితి, AV_చట్రం_దత్తాంశం_SEI_UNREGISTERED, udu, పరిమాణం(udu), 2);
    new_నమోదు(&సమితి, AV_చట్రం_దత్తాంశం_SPHERICAL, spherical, spherical_కొలత, 300);
    /* Entries are appended, so this dump is the insertion order by
     * construction and shows both MULTI entries. */
    print_సమితి("\nInitial set", &సమితి);

    /* Types probed by every dump below. */
    స్థిర స్థిరరాశి గణన AVFrame_Side_దత్తాంశం_Type probed[] = {
        AV_చట్రం_దత్తాంశం_STEREO3_D,
        AV_చట్రం_దత్తాంశం_DOWNMIX_INFO,
        AV_చట్రం_దత్తాంశం_SEI_UNREGISTERED,
        AV_చట్రం_దత్తాంశం_SPHERICAL,
        AV_చట్రం_దత్తాంశం_DISPLAYMATRIX,
        AV_చట్రం_దత్తాంశం_MOTION_VECTORS,
    };

    /* get / get_c: present and missing types. */
    రాయి("\nTesting av_frame_side_data_get()\n");
    {
        స్థిరరాశి AVFrame_Side_దత్తాంశం *got =
            av_చట్రం_side_దత్తాంశం_get(సమితి.sd, సమితి.nb_sd, AV_చట్రం_దత్తాంశం_STEREO3_D);
        రాయి("  stereo3d: %s marker=%s payload_match=%s\n",
               got ? "found" : "missing", got ? నమోదు_marker(got) : "none",
               got && got->కొలత == stereo3d_కొలత &&
               !memcmp(got->దత్తాంశం, stereo3d, stereo3d_కొలత) ? "yes" : "no");
        got = av_చట్రం_side_దత్తాంశం_get(సమితి.sd, సమితి.nb_sd,
                                     AV_చట్రం_దత్తాంశం_MASTERING_DISPLAY_METADATA);
        రాయి("  mastering (absent): %s\n", got ? "FAIL" : "null");
    }

    /* remove by type clears all matching entries (including duplicates). */
    రాయి("\nTesting av_frame_side_data_remove()\n");
    av_చట్రం_side_దత్తాంశం_remove(&సమితి.sd, &సమితి.nb_sd,
                              AV_చట్రం_దత్తాంశం_SEI_UNREGISTERED);
    print_lookup("  after remove SEI_UNREGISTERED", &సమితి,
                 probed, FF_ARRAY_ELEMS(probed));

    /* remove_by_props: PROP_GLOBAL drops STEREO3D and SPHERICAL. */
    రాయి("\nTesting av_frame_side_data_remove_by_props()\n");
    av_చట్రం_side_దత్తాంశం_remove_by_props(&సమితి.sd, &సమితి.nb_sd,
                                       AV_SIDE_దత్తాంశం_PROP_GLOBAL);
    print_lookup("  after remove_by_props(GLOBAL)", &సమితి,
                 probed, FF_ARRAY_ELEMS(probed));

    /* Clone: copy remaining entry into a second set. */
    రాయి("\nTesting av_frame_side_data_clone()\n");
    సమితి_2 dst = { 0 };
    ఒకవేళ (సమితి.nb_sd > 0) {
        పూర్ణాంకం ret = av_చట్రం_side_దత్తాంశం_clone(&dst.sd, &dst.nb_sd,
                                           సమితి.sd[0], 0);
        రాయి("  clone into empty: ret=%d nb=%d marker=%s\n", ret, dst.nb_sd,
               dst.nb_sd ? నమోదు_marker(dst.sd[0]) : "none");

        /* Same type again without REPLACE must fail with EEXIST. */
        ret = av_చట్రం_side_దత్తాంశం_clone(&dst.sd, &dst.nb_sd, సమితి.sd[0], 0);
        రాయి("  clone duplicate no REPLACE: ret==AVERROR(EEXIST)=%s\n",
               ret == AVERROR(EEXIST) ? "yes" : "no");

        /* With REPLACE, clone replaces the existing entry in place. */
        ret = av_చట్రం_side_దత్తాంశం_clone(&dst.sd, &dst.nb_sd, సమితి.sd[0],
                                       AV_చట్రం_SIDE_దత్తాంశం_FLAG_REPLACE);
        రాయి("  clone REPLACE: ret=%d nb=%d\n", ret, dst.nb_sd);

        /* Invalid args. */
        ret = av_చట్రం_side_దత్తాంశం_clone(ఖాళీ, &dst.nb_sd, సమితి.sd[0], 0);
        రాయి("  clone NULL sd: ret==AVERROR(EINVAL)=%s\n",
               ret == AVERROR(EINVAL) ? "yes" : "no");
    }

    /* add: buffer ownership transfer and NEW_REF. */
    రాయి("\nTesting av_frame_side_data_add()\n");
    {
        AVBufferRef *buf = payload_బఫరు(displaymatrix, పరిమాణం(displaymatrix));

        AVFrame_Side_దత్తాంశం *sd_added =
            av_చట్రం_side_దత్తాంశం_కూడు(&dst.sd, &dst.nb_sd,
                                   AV_చట్రం_దత్తాంశం_DISPLAYMATRIX,
                                   &buf, AV_చట్రం_SIDE_దత్తాంశం_FLAG_UNIQUE);
        రాయి("  add (move): added=%s pbuf_nulled=%s\n",
               sd_added ? "yes" : "no", buf == ఖాళీ ? "yes" : "no");
        ఒకవేళ (sd_added)
            సమితి_marker(sd_added, 999);

        /* NEW_REF: the caller retains its reference. */
        AVBufferRef *keep = payload_బఫరు(mvs, పరిమాణం(mvs));
        sd_added = av_చట్రం_side_దత్తాంశం_కూడు(&dst.sd, &dst.nb_sd,
                                          AV_చట్రం_దత్తాంశం_MOTION_VECTORS, &keep,
                                          AV_చట్రం_SIDE_దత్తాంశం_FLAG_NEW_REF);
        రాయి("  add (NEW_REF): added=%s caller_ref_kept=%s nb_mvs=%d\n",
               sd_added ? "yes" : "no", keep ? "yes" : "no",
               sd_added ? (పూర్ణాంకం)(sd_added->కొలత / పరిమాణం(AVMotion_సదిశ)) : -1);
        ఒకవేళ (sd_added)
            సమితి_marker(sd_added, 42);
        av_బఫరు_unref(&keep);

        /* REPLACE on existing entry: same type, payload swaps in place. */
        int32_t replacement[9];
        av_display_rotation_సమితి(replacement, 180.0);
        AVBufferRef *repl = payload_బఫరు(replacement, పరిమాణం(replacement));
        sd_added = av_చట్రం_side_దత్తాంశం_కూడు(&dst.sd, &dst.nb_sd,
                                          AV_చట్రం_దత్తాంశం_DISPLAYMATRIX, &repl,
                                          AV_చట్రం_SIDE_దత్తాంశం_FLAG_REPLACE);
        ఒకవేళ (sd_added)
            సమితి_marker(sd_added, 1234);
        {
            స్థిరరాశి AVFrame_Side_దత్తాంశం *after =
                av_చట్రం_side_దత్తాంశం_get(dst.sd, dst.nb_sd,
                                       AV_చట్రం_దత్తాంశం_DISPLAYMATRIX);
            రాయి("  add (REPLACE existing): added=%s marker=%s"
                   " payload_match=%s\n",
                   sd_added ? "yes" : "no",
                   after ? నమోదు_marker(after) : "none",
                   after && after->కొలత == పరిమాణం(replacement) &&
                   !memcmp(after->దత్తాంశం, replacement, పరిమాణం(replacement)) ?
                   "yes" : "no");
        }
    }

    /* clone with UNIQUE: existing same-type entry is removed first. dst
     * already has a set.sd[0]->type entry from the REPLACE clone above. */
    రాయి("\nTesting av_frame_side_data_clone() UNIQUE\n");
    ఒకవేళ (సమితి.nb_sd > 0) {
        పూర్ణాంకం before = dst.nb_sd;
        పూర్ణాంకం ret = av_చట్రం_side_దత్తాంశం_clone(&dst.sd, &dst.nb_sd, సమితి.sd[0],
                                           AV_చట్రం_SIDE_దత్తాంశం_FLAG_UNIQUE);
        రాయి("  clone UNIQUE: ret=%d before=%d after=%d\n",
               ret, before, dst.nb_sd);
    }

    print_lookup("\nFinal dst", &dst, probed, FF_ARRAY_ELEMS(probed));

    av_చట్రం_side_దత్తాంశం_free(&dst.sd, &dst.nb_sd);
    av_చట్రం_side_దత్తాంశం_free(&సమితి.sd, &సమితి.nb_sd);
    రాయి("\nfree: set_nb=%d dst_nb=%d\n", సమితి.nb_sd, dst.nb_sd);

    av_free(stereo3d);
    av_free(spherical);

    తిరిగి 0;
}
