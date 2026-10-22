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

#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "libavutil/avassert.h"
#अन्तर्भाव "libavutil/buffer.h"
#अन्तर्भाव "libavutil/dict.h"
#अन्तर्भाव "libavutil/display.h"
#अन्तर्भाव "libavutil/downmix_info.h"
#अन्तर्भाव "libavutil/error.h"
#अन्तर्भाव "libavutil/frame.h"
#अन्तर्भाव "libavutil/macros.h"
#अन्तर्भाव "libavutil/mem.h"
#अन्तर्भाव "libavutil/motion_vector.h"
#अन्तर्भाव "libavutil/spherical.h"
#अन्तर्भाव "libavutil/stereo3d.h"

प्रकारनिर्देश संरचना Set {
    AVFrameSideData **sd;
    पूर्णाङ्क            nb_sd;
} Set;

/* Every entry below carries a payload laid out as AVFrameSideDataType
 * documents for its type: a producer owes that layout even when no consumer
 * reads the buffer back. The small number that identifies an entry in the
 * reference output therefore lives in the metadata dictionary, which
 * av_frame_side_data_clone() copies along with the buffer. */
स्थिर शून्य set_marker(AVFrameSideData *sd, पूर्णाङ्क marker)
{
    वर्ण मूल्य[16];

    snprintf(मूल्य, परिमाण(मूल्य), "%d", marker);
    av_assert0(av_dict_set(&sd->metadata, "marker", मूल्य, 0) >= 0);
}

स्थिर AVFrameSideData *new_entry(Set *s, गणना AVFrameSideDataType type,
                                  ध्रुव शून्य *payload, size_t size, पूर्णाङ्क marker)
{
    AVFrameSideData *sd = av_frame_side_data_new(&s->sd, &s->nb_sd, type,
                                                 size, 0);

    av_assert0(sd && sd->size == size);
    memcpy(sd->data, payload, size);
    set_marker(sd, marker);
    प्रत्यागम sd;
}

स्थिर AVBufferRef *payload_buffer(ध्रुव शून्य *payload, size_t size)
{
    AVBufferRef *buf = av_buffer_alloc(size);

    av_assert0(buf);
    memcpy(buf->data, payload, size);
    प्रत्यागम buf;
}

स्थिर ध्रुव वर्ण *entry_marker(ध्रुव AVFrameSideData *sd)
{
    ध्रुव AVDictionaryEntry *e = av_dict_get(sd->metadata, "marker", रिक्त, 0);

    प्रत्यागम e ? e->मूल्य : "none";
}

स्थिर शून्य print_set(ध्रुव वर्ण *label, ध्रुव Set *s)
{
    printf("%s: n=%d\n", label, s->nb_sd);
    प्रति (पूर्णाङ्क i = 0; i < s->nb_sd; i++)
        printf("  [%d] %s marker=%s\n", i,
               av_frame_side_data_name(s->sd[i]->type),
               entry_marker(s->sd[i]));
}

/* Dumps a set by looking each type up instead of walking the array. Removal is
 * documented to drop the matching entries, not to keep the survivors where
 * they were, so printing by index would tie the reference to the current habit
 * of moving the last entry into the freed slot. */
स्थिर शून्य print_lookup(ध्रुव वर्ण *label, ध्रुव Set *s,
                         ध्रुव गणना AVFrameSideDataType *types, size_t nb_types)
{
    printf("%s: n=%d\n", label, s->nb_sd);
    प्रति (size_t i = 0; i < nb_types; i++) {
        ध्रुव AVFrameSideData *sd =
            av_frame_side_data_get(s->sd, s->nb_sd, types[i]);
        ध्रुव वर्ण *name = av_frame_side_data_name(types[i]);

        यदि (sd)
            printf("    %s: marker=%s\n", name, entry_marker(sd));
        अन्यथा
            printf("    %s: absent\n", name);
    }
}

पूर्णाङ्क main(शून्य)
{
    /* desc / name accessors. */
    printf("Testing av_frame_side_data_desc() / av_frame_side_data_name()\n");
    स्थिर ध्रुव गणना AVFrameSideDataType known[] = {
        AV_FRAME_DATA_STEREO3D,                    /* PROP_GLOBAL */
        AV_FRAME_DATA_DYNAMIC_HDR_PLUS,            /* PROP_COLOR_DEPENDENT */
        AV_FRAME_DATA_SPHERICAL,                   /* PROP_GLOBAL|SIZE_DEPENDENT */
        AV_FRAME_DATA_DOWNMIX_INFO,                /* PROP_CHANNEL_DEPENDENT */
        AV_FRAME_DATA_SEI_UNREGISTERED,            /* PROP_MULTI */
    };
    प्रति (size_t i = 0; i < FF_ARRAY_ELEMS(known); i++) {
        ध्रुव AVSideDataDescriptor *d = av_frame_side_data_desc(known[i]);
        ध्रुव वर्ण *n = av_frame_side_data_name(known[i]);
        /* Compare content: the API only promises a string identifying the
         * type, not the descriptor's own pointer. */
        printf("  type=%d name_match=%s props=0x%x\n", known[i],
               d && n && !strcmp(d->name, n) ? "yes" : "no",
               d ? d->props : 0);
    }

    /* Invalid / unmapped types must return NULL (sd_props gap). */
    {
        गणना AVFrameSideDataType bad = (गणना AVFrameSideDataType)-1;
        printf("  invalid type desc=%s name=%s\n",
               av_frame_side_data_desc(bad) ? "non-null" : "null",
               av_frame_side_data_name(bad) ? "non-null" : "null");
    }

    /* Payloads. The two structs are allocated through their public
     * allocators because their sizes are not part of the public ABI. */
    size_t stereo3d_size, spherical_size;
    AVStereo3D         *stereo3d  = av_stereo3d_alloc_size(&stereo3d_size);
    AVSphericalMapping *spherical = av_spherical_alloc(&spherical_size);
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
    stereo3d->primary_eye = AV_PRIMARY_EYE_डावा;
    stereo3d->baseline    = 65000;

    spherical->projection = AV_SPHERICAL_EQUIRECTANGULAR;
    spherical->yaw        = 90 << 16;

    av_display_rotation_set(displaymatrix, 90.0);

    /* Populate a set with several types, one of them MULTI. */
    Set set = { 0 };
    new_entry(&set, AV_FRAME_DATA_STEREO3D, stereo3d, stereo3d_size, 100);
    new_entry(&set, AV_FRAME_DATA_DOWNMIX_INFO, &downmix, परिमाण(downmix),
              200);
    new_entry(&set, AV_FRAME_DATA_SEI_UNREGISTERED, udu, परिमाण(udu), 1);
    udu[परिमाण(udu) - 1] = '2';
    new_entry(&set, AV_FRAME_DATA_SEI_UNREGISTERED, udu, परिमाण(udu), 2);
    new_entry(&set, AV_FRAME_DATA_SPHERICAL, spherical, spherical_size, 300);
    /* Entries are appended, so this dump is the insertion order by
     * construction and shows both MULTI entries. */
    print_set("\nInitial set", &set);

    /* Types probed by every dump below. */
    स्थिर ध्रुव गणना AVFrameSideDataType probed[] = {
        AV_FRAME_DATA_STEREO3D,
        AV_FRAME_DATA_DOWNMIX_INFO,
        AV_FRAME_DATA_SEI_UNREGISTERED,
        AV_FRAME_DATA_SPHERICAL,
        AV_FRAME_DATA_DISPLAYMATRIX,
        AV_FRAME_DATA_MOTION_VECTORS,
    };

    /* get / get_c: present and missing types. */
    printf("\nTesting av_frame_side_data_get()\n");
    {
        ध्रुव AVFrameSideData *got =
            av_frame_side_data_get(set.sd, set.nb_sd, AV_FRAME_DATA_STEREO3D);
        printf("  stereo3d: %s marker=%s payload_match=%s\n",
               got ? "found" : "missing", got ? entry_marker(got) : "none",
               got && got->size == stereo3d_size &&
               !memcmp(got->data, stereo3d, stereo3d_size) ? "yes" : "no");
        got = av_frame_side_data_get(set.sd, set.nb_sd,
                                     AV_FRAME_DATA_MASTERING_DISPLAY_METADATA);
        printf("  mastering (absent): %s\n", got ? "FAIL" : "null");
    }

    /* remove by type clears all matching entries (including duplicates). */
    printf("\nTesting av_frame_side_data_remove()\n");
    av_frame_side_data_remove(&set.sd, &set.nb_sd,
                              AV_FRAME_DATA_SEI_UNREGISTERED);
    print_lookup("  after remove SEI_UNREGISTERED", &set,
                 probed, FF_ARRAY_ELEMS(probed));

    /* remove_by_props: PROP_GLOBAL drops STEREO3D and SPHERICAL. */
    printf("\nTesting av_frame_side_data_remove_by_props()\n");
    av_frame_side_data_remove_by_props(&set.sd, &set.nb_sd,
                                       AV_SIDE_DATA_PROP_GLOBAL);
    print_lookup("  after remove_by_props(GLOBAL)", &set,
                 probed, FF_ARRAY_ELEMS(probed));

    /* Clone: copy remaining entry into a second set. */
    printf("\nTesting av_frame_side_data_clone()\n");
    Set dst = { 0 };
    यदि (set.nb_sd > 0) {
        पूर्णाङ्क ret = av_frame_side_data_clone(&dst.sd, &dst.nb_sd,
                                           set.sd[0], 0);
        printf("  clone into empty: ret=%d nb=%d marker=%s\n", ret, dst.nb_sd,
               dst.nb_sd ? entry_marker(dst.sd[0]) : "none");

        /* Same type again without REPLACE must fail with EEXIST. */
        ret = av_frame_side_data_clone(&dst.sd, &dst.nb_sd, set.sd[0], 0);
        printf("  clone duplicate no REPLACE: ret==AVERROR(EEXIST)=%s\n",
               ret == AVERROR(EEXIST) ? "yes" : "no");

        /* With REPLACE, clone replaces the existing entry in place. */
        ret = av_frame_side_data_clone(&dst.sd, &dst.nb_sd, set.sd[0],
                                       AV_FRAME_SIDE_DATA_FLAG_REPLACE);
        printf("  clone REPLACE: ret=%d nb=%d\n", ret, dst.nb_sd);

        /* Invalid args. */
        ret = av_frame_side_data_clone(रिक्त, &dst.nb_sd, set.sd[0], 0);
        printf("  clone NULL sd: ret==AVERROR(EINVAL)=%s\n",
               ret == AVERROR(EINVAL) ? "yes" : "no");
    }

    /* add: buffer ownership transfer and NEW_REF. */
    printf("\nTesting av_frame_side_data_add()\n");
    {
        AVBufferRef *buf = payload_buffer(displaymatrix, परिमाण(displaymatrix));

        AVFrameSideData *sd_added =
            av_frame_side_data_add(&dst.sd, &dst.nb_sd,
                                   AV_FRAME_DATA_DISPLAYMATRIX,
                                   &buf, AV_FRAME_SIDE_DATA_FLAG_UNIQUE);
        printf("  add (move): added=%s pbuf_nulled=%s\n",
               sd_added ? "yes" : "no", buf == रिक्त ? "yes" : "no");
        यदि (sd_added)
            set_marker(sd_added, 999);

        /* NEW_REF: the caller retains its reference. */
        AVBufferRef *keep = payload_buffer(mvs, परिमाण(mvs));
        sd_added = av_frame_side_data_add(&dst.sd, &dst.nb_sd,
                                          AV_FRAME_DATA_MOTION_VECTORS, &keep,
                                          AV_FRAME_SIDE_DATA_FLAG_NEW_REF);
        printf("  add (NEW_REF): added=%s caller_ref_kept=%s nb_mvs=%d\n",
               sd_added ? "yes" : "no", keep ? "yes" : "no",
               sd_added ? (पूर्णाङ्क)(sd_added->size / परिमाण(AVMotionVector)) : -1);
        यदि (sd_added)
            set_marker(sd_added, 42);
        av_buffer_unref(&keep);

        /* REPLACE on existing entry: same type, payload swaps in place. */
        int32_t replacement[9];
        av_display_rotation_set(replacement, 180.0);
        AVBufferRef *repl = payload_buffer(replacement, परिमाण(replacement));
        sd_added = av_frame_side_data_add(&dst.sd, &dst.nb_sd,
                                          AV_FRAME_DATA_DISPLAYMATRIX, &repl,
                                          AV_FRAME_SIDE_DATA_FLAG_REPLACE);
        यदि (sd_added)
            set_marker(sd_added, 1234);
        {
            ध्रुव AVFrameSideData *after =
                av_frame_side_data_get(dst.sd, dst.nb_sd,
                                       AV_FRAME_DATA_DISPLAYMATRIX);
            printf("  add (REPLACE existing): added=%s marker=%s"
                   " payload_match=%s\n",
                   sd_added ? "yes" : "no",
                   after ? entry_marker(after) : "none",
                   after && after->size == परिमाण(replacement) &&
                   !memcmp(after->data, replacement, परिमाण(replacement)) ?
                   "yes" : "no");
        }
    }

    /* clone with UNIQUE: existing same-type entry is removed first. dst
     * already has a set.sd[0]->type entry from the REPLACE clone above. */
    printf("\nTesting av_frame_side_data_clone() UNIQUE\n");
    यदि (set.nb_sd > 0) {
        पूर्णाङ्क before = dst.nb_sd;
        पूर्णाङ्क ret = av_frame_side_data_clone(&dst.sd, &dst.nb_sd, set.sd[0],
                                           AV_FRAME_SIDE_DATA_FLAG_UNIQUE);
        printf("  clone UNIQUE: ret=%d before=%d after=%d\n",
               ret, before, dst.nb_sd);
    }

    print_lookup("\nFinal dst", &dst, probed, FF_ARRAY_ELEMS(probed));

    av_frame_side_data_free(&dst.sd, &dst.nb_sd);
    av_frame_side_data_free(&set.sd, &set.nb_sd);
    printf("\nfree: set_nb=%d dst_nb=%d\n", set.nb_sd, dst.nb_sd);

    av_free(stereo3d);
    av_free(spherical);

    प्रत्यागम 0;
}
