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

प्रकारनिर्देश संरचना समुच्चयः_2 {
    AVFrame_Side_दत्त **sd;
    पूर्णाङ्क            nb_sd;
} समुच्चयः_2;

/* Every entry below carries a payload laid out as AVFrameSideDataType
 * documents for its type: a producer owes that layout even when no consumer
 * reads the buffer back. The small number that identifies an entry in the
 * reference output therefore lives in the metadata dictionary, which
 * av_frame_side_data_clone() copies along with the buffer. */
स्थिर शून्य समुच्चयः_marker(AVFrame_Side_दत्त *sd, पूर्णाङ्क marker)
{
    वर्ण मानम्[16];

    snprintf(मानम्, परिमाण(मानम्), "%d", marker);
    av_assert0(av_dict_समुच्चयः(&sd->metadata, "marker", मानम्, 0) >= 0);
}

स्थिर AVFrame_Side_दत्त *new_प्रविष्टिः(समुच्चयः_2 *s, गणना AVFrame_Side_दत्त_Type type,
                                  ध्रुव शून्य *payload, size_t आकार, पूर्णाङ्क marker)
{
    AVFrame_Side_दत्त *sd = av_frame_side_दत्त_new(&s->sd, &s->nb_sd, type,
                                                 आकार, 0);

    av_assert0(sd && sd->आकार == आकार);
    स्मृतिं_प्रतिलिख(sd->दत्त, payload, आकार);
    समुच्चयः_marker(sd, marker);
    प्रत्यागम sd;
}

स्थिर AVBufferRef *payload_बफर(ध्रुव शून्य *payload, size_t आकार)
{
    AVBufferRef *buf = av_बफर_alloc(आकार);

    av_assert0(buf);
    स्मृतिं_प्रतिलिख(buf->दत्त, payload, आकार);
    प्रत्यागम buf;
}

स्थिर ध्रुव वर्ण *प्रविष्टिः_marker(ध्रुव AVFrame_Side_दत्त *sd)
{
    ध्रुव AVDictionary_प्रविष्टिः *e = av_dict_get(sd->metadata, "marker", रिक्त, 0);

    प्रत्यागम e ? e->मानम् : "none";
}

स्थिर शून्य print_समुच्चयः(ध्रुव वर्ण *label, ध्रुव समुच्चयः_2 *s)
{
    प्रारूप_लिख("%s: n=%d\n", label, s->nb_sd);
    प्रति (पूर्णाङ्क i = 0; i < s->nb_sd; i++)
        प्रारूप_लिख("  [%d] %s marker=%s\n", i,
               av_frame_side_दत्त_name(s->sd[i]->type),
               प्रविष्टिः_marker(s->sd[i]));
}

/* Dumps a set by looking each type up instead of walking the array. Removal is
 * documented to drop the matching entries, not to keep the survivors where
 * they were, so printing by index would tie the reference to the current habit
 * of moving the last entry into the freed slot. */
स्थिर शून्य print_lookup(ध्रुव वर्ण *label, ध्रुव समुच्चयः_2 *s,
                         ध्रुव गणना AVFrame_Side_दत्त_Type *types, size_t nb_types)
{
    प्रारूप_लिख("%s: n=%d\n", label, s->nb_sd);
    प्रति (size_t i = 0; i < nb_types; i++) {
        ध्रुव AVFrame_Side_दत्त *sd =
            av_frame_side_दत्त_get(s->sd, s->nb_sd, types[i]);
        ध्रुव वर्ण *name = av_frame_side_दत्त_name(types[i]);

        यदि (sd)
            प्रारूप_लिख("    %s: marker=%s\n", name, प्रविष्टिः_marker(sd));
        अन्यथा
            प्रारूप_लिख("    %s: absent\n", name);
    }
}

पूर्णाङ्क मुख्यम्(शून्य)
{
    /* desc / name accessors. */
    प्रारूप_लिख("Testing av_frame_side_data_desc() / av_frame_side_data_name()\n");
    स्थिर ध्रुव गणना AVFrame_Side_दत्त_Type ज्ञातम्[] = {
        AV_FRAME_दत्त_STEREO3_D,                    /* PROP_GLOBAL */
        AV_FRAME_दत्त_DYNAMIC_HDR_PLUS,            /* PROP_COLOR_DEPENDENT */
        AV_FRAME_दत्त_SPHERICAL,                   /* PROP_GLOBAL|SIZE_DEPENDENT */
        AV_FRAME_दत्त_DOWNMIX_INFO,                /* PROP_CHANNEL_DEPENDENT */
        AV_FRAME_दत्त_SEI_UNREGISTERED,            /* PROP_MULTI */
    };
    प्रति (size_t i = 0; i < FF_ARRAY_ELEMS(ज्ञातम्); i++) {
        ध्रुव AVSide_दत्त_Descriptor *d = av_frame_side_दत्त_desc(ज्ञातम्[i]);
        ध्रुव वर्ण *n = av_frame_side_दत्त_name(ज्ञातम्[i]);
        /* Compare content: the API only promises a string identifying the
         * type, not the descriptor's own pointer. */
        प्रारूप_लिख("  type=%d name_match=%s props=0x%x\n", ज्ञातम्[i],
               d && n && !वाक्यं_तुलय(d->name, n) ? "yes" : "no",
               d ? d->props : 0);
    }

    /* Invalid / unmapped types must return NULL (sd_props gap). */
    {
        गणना AVFrame_Side_दत्त_Type bad = (गणना AVFrame_Side_दत्त_Type)-1;
        प्रारूप_लिख("  invalid type desc=%s name=%s\n",
               av_frame_side_दत्त_desc(bad) ? "non-null" : "null",
               av_frame_side_दत्त_name(bad) ? "non-null" : "null");
    }

    /* Payloads. The two structs are allocated through their public
     * allocators because their sizes are not part of the public ABI. */
    size_t stereo3d_आकार, spherical_आकार;
    AVStereo3D         *stereo3d  = av_stereo3d_alloc_आकार(&stereo3d_आकार);
    AVSphericalMapping *spherical = av_spherical_alloc(&spherical_आकार);
    /* 16 bytes of uuid_iso_iec_11578 followed by user_data_payload_byte. */
    uint8_t udu[16 + 8] = {
        0x9a, 0x21, 0xf3, 0x4d, 0x6b, 0x1c, 0x47, 0x8e,
        0xa5, 0x30, 0xc2, 0x7f, 0x11, 0x8d, 0x46, 0x02,
        'p',  'a',  'y',  'l',  'o',  'a',  'd',  '1',
    };
    int32_t displaymatrix[9];
    /* src_x = dst_x + motion_x / motion_scale, likewise for y. */
    AVMotion_सदिशम् mvs[2] = {
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
    stereo3d->primary_eye = AV_PRIMARY_EYE_वामः;
    stereo3d->baseline    = 65000;

    spherical->projection = AV_SPHERICAL_EQUIRECTANGULAR;
    spherical->yaw        = 90 << 16;

    av_display_rotation_समुच्चयः(displaymatrix, 90.0);

    /* Populate a set with several types, one of them MULTI. */
    समुच्चयः_2 समुच्चयः = { 0 };
    new_प्रविष्टिः(&समुच्चयः, AV_FRAME_दत्त_STEREO3_D, stereo3d, stereo3d_आकार, 100);
    new_प्रविष्टिः(&समुच्चयः, AV_FRAME_दत्त_DOWNMIX_INFO, &downmix, परिमाण(downmix),
              200);
    new_प्रविष्टिः(&समुच्चयः, AV_FRAME_दत्त_SEI_UNREGISTERED, udu, परिमाण(udu), 1);
    udu[परिमाण(udu) - 1] = '2';
    new_प्रविष्टिः(&समुच्चयः, AV_FRAME_दत्त_SEI_UNREGISTERED, udu, परिमाण(udu), 2);
    new_प्रविष्टिः(&समुच्चयः, AV_FRAME_दत्त_SPHERICAL, spherical, spherical_आकार, 300);
    /* Entries are appended, so this dump is the insertion order by
     * construction and shows both MULTI entries. */
    print_समुच्चयः("\nInitial set", &समुच्चयः);

    /* Types probed by every dump below. */
    स्थिर ध्रुव गणना AVFrame_Side_दत्त_Type probed[] = {
        AV_FRAME_दत्त_STEREO3_D,
        AV_FRAME_दत्त_DOWNMIX_INFO,
        AV_FRAME_दत्त_SEI_UNREGISTERED,
        AV_FRAME_दत्त_SPHERICAL,
        AV_FRAME_दत्त_DISPLAYMATRIX,
        AV_FRAME_दत्त_MOTION_VECTORS,
    };

    /* get / get_c: present and missing types. */
    प्रारूप_लिख("\nTesting av_frame_side_data_get()\n");
    {
        ध्रुव AVFrame_Side_दत्त *got =
            av_frame_side_दत्त_get(समुच्चयः.sd, समुच्चयः.nb_sd, AV_FRAME_दत्त_STEREO3_D);
        प्रारूप_लिख("  stereo3d: %s marker=%s payload_match=%s\n",
               got ? "found" : "missing", got ? प्रविष्टिः_marker(got) : "none",
               got && got->आकार == stereo3d_आकार &&
               !memcmp(got->दत्त, stereo3d, stereo3d_आकार) ? "yes" : "no");
        got = av_frame_side_दत्त_get(समुच्चयः.sd, समुच्चयः.nb_sd,
                                     AV_FRAME_दत्त_MASTERING_DISPLAY_METADATA);
        प्रारूप_लिख("  mastering (absent): %s\n", got ? "FAIL" : "null");
    }

    /* remove by type clears all matching entries (including duplicates). */
    प्रारूप_लिख("\nTesting av_frame_side_data_remove()\n");
    av_frame_side_दत्त_remove(&समुच्चयः.sd, &समुच्चयः.nb_sd,
                              AV_FRAME_दत्त_SEI_UNREGISTERED);
    print_lookup("  after remove SEI_UNREGISTERED", &समुच्चयः,
                 probed, FF_ARRAY_ELEMS(probed));

    /* remove_by_props: PROP_GLOBAL drops STEREO3D and SPHERICAL. */
    प्रारूप_लिख("\nTesting av_frame_side_data_remove_by_props()\n");
    av_frame_side_दत्त_remove_by_props(&समुच्चयः.sd, &समुच्चयः.nb_sd,
                                       AV_SIDE_दत्त_PROP_GLOBAL);
    print_lookup("  after remove_by_props(GLOBAL)", &समुच्चयः,
                 probed, FF_ARRAY_ELEMS(probed));

    /* Clone: copy remaining entry into a second set. */
    प्रारूप_लिख("\nTesting av_frame_side_data_clone()\n");
    समुच्चयः_2 dst = { 0 };
    यदि (समुच्चयः.nb_sd > 0) {
        पूर्णाङ्क ret = av_frame_side_दत्त_clone(&dst.sd, &dst.nb_sd,
                                           समुच्चयः.sd[0], 0);
        प्रारूप_लिख("  clone into empty: ret=%d nb=%d marker=%s\n", ret, dst.nb_sd,
               dst.nb_sd ? प्रविष्टिः_marker(dst.sd[0]) : "none");

        /* Same type again without REPLACE must fail with EEXIST. */
        ret = av_frame_side_दत्त_clone(&dst.sd, &dst.nb_sd, समुच्चयः.sd[0], 0);
        प्रारूप_लिख("  clone duplicate no REPLACE: ret==AVERROR(EEXIST)=%s\n",
               ret == AVERROR(EEXIST) ? "yes" : "no");

        /* With REPLACE, clone replaces the existing entry in place. */
        ret = av_frame_side_दत्त_clone(&dst.sd, &dst.nb_sd, समुच्चयः.sd[0],
                                       AV_FRAME_SIDE_दत्त_FLAG_REPLACE);
        प्रारूप_लिख("  clone REPLACE: ret=%d nb=%d\n", ret, dst.nb_sd);

        /* Invalid args. */
        ret = av_frame_side_दत्त_clone(रिक्त, &dst.nb_sd, समुच्चयः.sd[0], 0);
        प्रारूप_लिख("  clone NULL sd: ret==AVERROR(EINVAL)=%s\n",
               ret == AVERROR(EINVAL) ? "yes" : "no");
    }

    /* add: buffer ownership transfer and NEW_REF. */
    प्रारूप_लिख("\nTesting av_frame_side_data_add()\n");
    {
        AVBufferRef *buf = payload_बफर(displaymatrix, परिमाण(displaymatrix));

        AVFrame_Side_दत्त *sd_added =
            av_frame_side_दत्त_सङ्कलय(&dst.sd, &dst.nb_sd,
                                   AV_FRAME_दत्त_DISPLAYMATRIX,
                                   &buf, AV_FRAME_SIDE_दत्त_FLAG_UNIQUE);
        प्रारूप_लिख("  add (move): added=%s pbuf_nulled=%s\n",
               sd_added ? "yes" : "no", buf == रिक्त ? "yes" : "no");
        यदि (sd_added)
            समुच्चयः_marker(sd_added, 999);

        /* NEW_REF: the caller retains its reference. */
        AVBufferRef *keep = payload_बफर(mvs, परिमाण(mvs));
        sd_added = av_frame_side_दत्त_सङ्कलय(&dst.sd, &dst.nb_sd,
                                          AV_FRAME_दत्त_MOTION_VECTORS, &keep,
                                          AV_FRAME_SIDE_दत्त_FLAG_NEW_REF);
        प्रारूप_लिख("  add (NEW_REF): added=%s caller_ref_kept=%s nb_mvs=%d\n",
               sd_added ? "yes" : "no", keep ? "yes" : "no",
               sd_added ? (पूर्णाङ्क)(sd_added->आकार / परिमाण(AVMotion_सदिशम्)) : -1);
        यदि (sd_added)
            समुच्चयः_marker(sd_added, 42);
        av_बफर_unref(&keep);

        /* REPLACE on existing entry: same type, payload swaps in place. */
        int32_t replacement[9];
        av_display_rotation_समुच्चयः(replacement, 180.0);
        AVBufferRef *repl = payload_बफर(replacement, परिमाण(replacement));
        sd_added = av_frame_side_दत्त_सङ्कलय(&dst.sd, &dst.nb_sd,
                                          AV_FRAME_दत्त_DISPLAYMATRIX, &repl,
                                          AV_FRAME_SIDE_दत्त_FLAG_REPLACE);
        यदि (sd_added)
            समुच्चयः_marker(sd_added, 1234);
        {
            ध्रुव AVFrame_Side_दत्त *after =
                av_frame_side_दत्त_get(dst.sd, dst.nb_sd,
                                       AV_FRAME_दत्त_DISPLAYMATRIX);
            प्रारूप_लिख("  add (REPLACE existing): added=%s marker=%s"
                   " payload_match=%s\n",
                   sd_added ? "yes" : "no",
                   after ? प्रविष्टिः_marker(after) : "none",
                   after && after->आकार == परिमाण(replacement) &&
                   !memcmp(after->दत्त, replacement, परिमाण(replacement)) ?
                   "yes" : "no");
        }
    }

    /* clone with UNIQUE: existing same-type entry is removed first. dst
     * already has a set.sd[0]->type entry from the REPLACE clone above. */
    प्रारूप_लिख("\nTesting av_frame_side_data_clone() UNIQUE\n");
    यदि (समुच्चयः.nb_sd > 0) {
        पूर्णाङ्क before = dst.nb_sd;
        पूर्णाङ्क ret = av_frame_side_दत्त_clone(&dst.sd, &dst.nb_sd, समुच्चयः.sd[0],
                                           AV_FRAME_SIDE_दत्त_FLAG_UNIQUE);
        प्रारूप_लिख("  clone UNIQUE: ret=%d before=%d after=%d\n",
               ret, before, dst.nb_sd);
    }

    print_lookup("\nFinal dst", &dst, probed, FF_ARRAY_ELEMS(probed));

    av_frame_side_दत्त_free(&dst.sd, &dst.nb_sd);
    av_frame_side_दत्त_free(&समुच्चयः.sd, &समुच्चयः.nb_sd);
    प्रारूप_लिख("\nfree: set_nb=%d dst_nb=%d\n", समुच्चयः.nb_sd, dst.nb_sd);

    av_free(stereo3d);
    av_free(spherical);

    प्रत्यागम 0;
}
