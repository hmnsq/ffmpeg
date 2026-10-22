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

#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "libavutil/avassert.h"
#অন্তর্ভাব "libavutil/buffer.h"
#অন্তর্ভাব "libavutil/dict.h"
#অন্তর্ভাব "libavutil/display.h"
#অন্তর্ভাব "libavutil/downmix_info.h"
#অন্তর্ভাব "libavutil/error.h"
#অন্তর্ভাব "libavutil/frame.h"
#অন্তর্ভাব "libavutil/macros.h"
#অন্তর্ভাব "libavutil/mem.h"
#অন্তর্ভাব "libavutil/motion_vector.h"
#অন্তর্ভাব "libavutil/spherical.h"
#অন্তর্ভাব "libavutil/stereo3d.h"

প্রকারলেখ কাঠামো Set {
    AVFrame_Side_তথ্য **sd;
    পূর্ণসংখ্যা            nb_sd;
} Set;

/* Every entry below carries a payload laid out as AVFrameSideDataType
 * documents for its type: a producer owes that layout even when no consumer
 * reads the buffer back. The small number that identifies an entry in the
 * reference output therefore lives in the metadata dictionary, which
 * av_frame_side_data_clone() copies along with the buffer. */
স্থির শূন্য set_marker(AVFrame_Side_তথ্য *sd, পূর্ণসংখ্যা marker)
{
    অক্ষর মান[16];

    snprintf(মান, আকার(মান), "%d", marker);
    av_assert0(av_dict_set(&sd->metadata, "marker", মান, 0) >= 0);
}

স্থির AVFrame_Side_তথ্য *new_entry(Set *s, গণনা AVFrame_Side_তথ্য_Type type,
                                  ধ্রুবক শূন্য *payload, size_t আকার_2, পূর্ণসংখ্যা marker)
{
    AVFrame_Side_তথ্য *sd = av_frame_side_তথ্য_new(&s->sd, &s->nb_sd, type,
                                                 আকার_2, 0);

    av_assert0(sd && sd->আকার_2 == আকার_2);
    memcpy(sd->তথ্য, payload, আকার_2);
    set_marker(sd, marker);
    ফেরত sd;
}

স্থির AVBufferRef *payload_বাফার(ধ্রুবক শূন্য *payload, size_t আকার_2)
{
    AVBufferRef *buf = av_বাফার_alloc(আকার_2);

    av_assert0(buf);
    memcpy(buf->তথ্য, payload, আকার_2);
    ফেরত buf;
}

স্থির ধ্রুবক অক্ষর *entry_marker(ধ্রুবক AVFrame_Side_তথ্য *sd)
{
    ধ্রুবক AVDictionaryEntry *e = av_dict_get(sd->metadata, "marker", ফাঁকা, 0);

    ফেরত e ? e->মান : "none";
}

স্থির শূন্য print_set(ধ্রুবক অক্ষর *label, ধ্রুবক Set *s)
{
    printf("%s: n=%d\n", label, s->nb_sd);
    জন্য (পূর্ণসংখ্যা i = 0; i < s->nb_sd; i++)
        printf("  [%d] %s marker=%s\n", i,
               av_frame_side_তথ্য_name(s->sd[i]->type),
               entry_marker(s->sd[i]));
}

/* Dumps a set by looking each type up instead of walking the array. Removal is
 * documented to drop the matching entries, not to keep the survivors where
 * they were, so printing by index would tie the reference to the current habit
 * of moving the last entry into the freed slot. */
স্থির শূন্য print_lookup(ধ্রুবক অক্ষর *label, ধ্রুবক Set *s,
                         ধ্রুবক গণনা AVFrame_Side_তথ্য_Type *types, size_t nb_types)
{
    printf("%s: n=%d\n", label, s->nb_sd);
    জন্য (size_t i = 0; i < nb_types; i++) {
        ধ্রুবক AVFrame_Side_তথ্য *sd =
            av_frame_side_তথ্য_get(s->sd, s->nb_sd, types[i]);
        ধ্রুবক অক্ষর *name = av_frame_side_তথ্য_name(types[i]);

        যদি (sd)
            printf("    %s: marker=%s\n", name, entry_marker(sd));
        অন্যথা
            printf("    %s: absent\n", name);
    }
}

পূর্ণসংখ্যা প্রধান(শূন্য)
{
    /* desc / name accessors. */
    printf("Testing av_frame_side_data_desc() / av_frame_side_data_name()\n");
    স্থির ধ্রুবক গণনা AVFrame_Side_তথ্য_Type known[] = {
        AV_FRAME_তথ্য_STEREO3_D,                    /* PROP_GLOBAL */
        AV_FRAME_তথ্য_DYNAMIC_HDR_PLUS,            /* PROP_COLOR_DEPENDENT */
        AV_FRAME_তথ্য_SPHERICAL,                   /* PROP_GLOBAL|SIZE_DEPENDENT */
        AV_FRAME_তথ্য_DOWNMIX_INFO,                /* PROP_CHANNEL_DEPENDENT */
        AV_FRAME_তথ্য_SEI_UNREGISTERED,            /* PROP_MULTI */
    };
    জন্য (size_t i = 0; i < FF_ARRAY_ELEMS(known); i++) {
        ধ্রুবক AVSide_তথ্য_Descriptor *d = av_frame_side_তথ্য_desc(known[i]);
        ধ্রুবক অক্ষর *n = av_frame_side_তথ্য_name(known[i]);
        /* Compare content: the API only promises a string identifying the
         * type, not the descriptor's own pointer. */
        printf("  type=%d name_match=%s props=0x%x\n", known[i],
               d && n && !strcmp(d->name, n) ? "yes" : "no",
               d ? d->props : 0);
    }

    /* Invalid / unmapped types must return NULL (sd_props gap). */
    {
        গণনা AVFrame_Side_তথ্য_Type bad = (গণনা AVFrame_Side_তথ্য_Type)-1;
        printf("  invalid type desc=%s name=%s\n",
               av_frame_side_তথ্য_desc(bad) ? "non-null" : "null",
               av_frame_side_তথ্য_name(bad) ? "non-null" : "null");
    }

    /* Payloads. The two structs are allocated through their public
     * allocators because their sizes are not part of the public ABI. */
    size_t stereo3d_আকার, spherical_আকার;
    AVStereo3D         *stereo3d  = av_stereo3d_alloc_আকার(&stereo3d_আকার);
    AVSphericalMapping *spherical = av_spherical_alloc(&spherical_আকার);
    /* 16 bytes of uuid_iso_iec_11578 followed by user_data_payload_byte. */
    uint8_t udu[16 + 8] = {
        0x9a, 0x21, 0xf3, 0x4d, 0x6b, 0x1c, 0x47, 0x8e,
        0xa5, 0x30, 0xc2, 0x7f, 0x11, 0x8d, 0x46, 0x02,
        'p',  'a',  'y',  'l',  'o',  'a',  'd',  '1',
    };
    int32_t displaymatrix[9];
    /* src_x = dst_x + motion_x / motion_scale, likewise for y. */
    AVMotionVector mvs[2] = {
        { .source = -1, .w = 16, .h = 16, .src_x = 32, .src_y = 48,
          .dst_x = 40, .dst_y = 48, .motion_x = -8, .motion_y = 0,
          .motion_scale = 1 },
        { .source =  1, .w =  8, .h =  8, .src_x = 64, .src_y = 64,
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
    stereo3d->primary_eye = AV_PRIMARY_EYE_বাম;
    stereo3d->baseline    = 65000;

    spherical->projection = AV_SPHERICAL_EQUIRECTANGULAR;
    spherical->yaw        = 90 << 16;

    av_display_rotation_set(displaymatrix, 90.0);

    /* Populate a set with several types, one of them MULTI. */
    Set set = { 0 };
    new_entry(&set, AV_FRAME_তথ্য_STEREO3_D, stereo3d, stereo3d_আকার, 100);
    new_entry(&set, AV_FRAME_তথ্য_DOWNMIX_INFO, &downmix, আকার(downmix),
              200);
    new_entry(&set, AV_FRAME_তথ্য_SEI_UNREGISTERED, udu, আকার(udu), 1);
    udu[আকার(udu) - 1] = '2';
    new_entry(&set, AV_FRAME_তথ্য_SEI_UNREGISTERED, udu, আকার(udu), 2);
    new_entry(&set, AV_FRAME_তথ্য_SPHERICAL, spherical, spherical_আকার, 300);
    /* Entries are appended, so this dump is the insertion order by
     * construction and shows both MULTI entries. */
    print_set("\nInitial set", &set);

    /* Types probed by every dump below. */
    স্থির ধ্রুবক গণনা AVFrame_Side_তথ্য_Type probed[] = {
        AV_FRAME_তথ্য_STEREO3_D,
        AV_FRAME_তথ্য_DOWNMIX_INFO,
        AV_FRAME_তথ্য_SEI_UNREGISTERED,
        AV_FRAME_তথ্য_SPHERICAL,
        AV_FRAME_তথ্য_DISPLAYMATRIX,
        AV_FRAME_তথ্য_MOTION_VECTORS,
    };

    /* get / get_c: present and missing types. */
    printf("\nTesting av_frame_side_data_get()\n");
    {
        ধ্রুবক AVFrame_Side_তথ্য *got =
            av_frame_side_তথ্য_get(set.sd, set.nb_sd, AV_FRAME_তথ্য_STEREO3_D);
        printf("  stereo3d: %s marker=%s payload_match=%s\n",
               got ? "found" : "missing", got ? entry_marker(got) : "none",
               got && got->আকার_2 == stereo3d_আকার &&
               !memcmp(got->তথ্য, stereo3d, stereo3d_আকার) ? "yes" : "no");
        got = av_frame_side_তথ্য_get(set.sd, set.nb_sd,
                                     AV_FRAME_তথ্য_MASTERING_DISPLAY_METADATA);
        printf("  mastering (absent): %s\n", got ? "FAIL" : "null");
    }

    /* remove by type clears all matching entries (including duplicates). */
    printf("\nTesting av_frame_side_data_remove()\n");
    av_frame_side_তথ্য_remove(&set.sd, &set.nb_sd,
                              AV_FRAME_তথ্য_SEI_UNREGISTERED);
    print_lookup("  after remove SEI_UNREGISTERED", &set,
                 probed, FF_ARRAY_ELEMS(probed));

    /* remove_by_props: PROP_GLOBAL drops STEREO3D and SPHERICAL. */
    printf("\nTesting av_frame_side_data_remove_by_props()\n");
    av_frame_side_তথ্য_remove_by_props(&set.sd, &set.nb_sd,
                                       AV_SIDE_তথ্য_PROP_GLOBAL);
    print_lookup("  after remove_by_props(GLOBAL)", &set,
                 probed, FF_ARRAY_ELEMS(probed));

    /* Clone: copy remaining entry into a second set. */
    printf("\nTesting av_frame_side_data_clone()\n");
    Set dst = { 0 };
    যদি (set.nb_sd > 0) {
        পূর্ণসংখ্যা ret = av_frame_side_তথ্য_clone(&dst.sd, &dst.nb_sd,
                                           set.sd[0], 0);
        printf("  clone into empty: ret=%d nb=%d marker=%s\n", ret, dst.nb_sd,
               dst.nb_sd ? entry_marker(dst.sd[0]) : "none");

        /* Same type again without REPLACE must fail with EEXIST. */
        ret = av_frame_side_তথ্য_clone(&dst.sd, &dst.nb_sd, set.sd[0], 0);
        printf("  clone duplicate no REPLACE: ret==AVERROR(EEXIST)=%s\n",
               ret == AVERROR(EEXIST) ? "yes" : "no");

        /* With REPLACE, clone replaces the existing entry in place. */
        ret = av_frame_side_তথ্য_clone(&dst.sd, &dst.nb_sd, set.sd[0],
                                       AV_FRAME_SIDE_তথ্য_FLAG_REPLACE);
        printf("  clone REPLACE: ret=%d nb=%d\n", ret, dst.nb_sd);

        /* Invalid args. */
        ret = av_frame_side_তথ্য_clone(ফাঁকা, &dst.nb_sd, set.sd[0], 0);
        printf("  clone NULL sd: ret==AVERROR(EINVAL)=%s\n",
               ret == AVERROR(EINVAL) ? "yes" : "no");
    }

    /* add: buffer ownership transfer and NEW_REF. */
    printf("\nTesting av_frame_side_data_add()\n");
    {
        AVBufferRef *buf = payload_বাফার(displaymatrix, আকার(displaymatrix));

        AVFrame_Side_তথ্য *sd_added =
            av_frame_side_তথ্য_add(&dst.sd, &dst.nb_sd,
                                   AV_FRAME_তথ্য_DISPLAYMATRIX,
                                   &buf, AV_FRAME_SIDE_তথ্য_FLAG_UNIQUE);
        printf("  add (move): added=%s pbuf_nulled=%s\n",
               sd_added ? "yes" : "no", buf == ফাঁকা ? "yes" : "no");
        যদি (sd_added)
            set_marker(sd_added, 999);

        /* NEW_REF: the caller retains its reference. */
        AVBufferRef *keep = payload_বাফার(mvs, আকার(mvs));
        sd_added = av_frame_side_তথ্য_add(&dst.sd, &dst.nb_sd,
                                          AV_FRAME_তথ্য_MOTION_VECTORS, &keep,
                                          AV_FRAME_SIDE_তথ্য_FLAG_NEW_REF);
        printf("  add (NEW_REF): added=%s caller_ref_kept=%s nb_mvs=%d\n",
               sd_added ? "yes" : "no", keep ? "yes" : "no",
               sd_added ? (পূর্ণসংখ্যা)(sd_added->আকার_2 / আকার(AVMotionVector)) : -1);
        যদি (sd_added)
            set_marker(sd_added, 42);
        av_বাফার_unref(&keep);

        /* REPLACE on existing entry: same type, payload swaps in place. */
        int32_t replacement[9];
        av_display_rotation_set(replacement, 180.0);
        AVBufferRef *repl = payload_বাফার(replacement, আকার(replacement));
        sd_added = av_frame_side_তথ্য_add(&dst.sd, &dst.nb_sd,
                                          AV_FRAME_তথ্য_DISPLAYMATRIX, &repl,
                                          AV_FRAME_SIDE_তথ্য_FLAG_REPLACE);
        যদি (sd_added)
            set_marker(sd_added, 1234);
        {
            ধ্রুবক AVFrame_Side_তথ্য *after =
                av_frame_side_তথ্য_get(dst.sd, dst.nb_sd,
                                       AV_FRAME_তথ্য_DISPLAYMATRIX);
            printf("  add (REPLACE existing): added=%s marker=%s"
                   " payload_match=%s\n",
                   sd_added ? "yes" : "no",
                   after ? entry_marker(after) : "none",
                   after && after->আকার_2 == আকার(replacement) &&
                   !memcmp(after->তথ্য, replacement, আকার(replacement)) ?
                   "yes" : "no");
        }
    }

    /* clone with UNIQUE: existing same-type entry is removed first. dst
     * already has a set.sd[0]->type entry from the REPLACE clone above. */
    printf("\nTesting av_frame_side_data_clone() UNIQUE\n");
    যদি (set.nb_sd > 0) {
        পূর্ণসংখ্যা before = dst.nb_sd;
        পূর্ণসংখ্যা ret = av_frame_side_তথ্য_clone(&dst.sd, &dst.nb_sd, set.sd[0],
                                           AV_FRAME_SIDE_তথ্য_FLAG_UNIQUE);
        printf("  clone UNIQUE: ret=%d before=%d after=%d\n",
               ret, before, dst.nb_sd);
    }

    print_lookup("\nFinal dst", &dst, probed, FF_ARRAY_ELEMS(probed));

    av_frame_side_তথ্য_free(&dst.sd, &dst.nb_sd);
    av_frame_side_তথ্য_free(&set.sd, &set.nb_sd);
    printf("\nfree: set_nb=%d dst_nb=%d\n", set.nb_sd, dst.nb_sd);

    av_free(stereo3d);
    av_free(spherical);

    ফেরত 0;
}
