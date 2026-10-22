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

#समावेश <stdio.h>
#समावेश <string.h>

#समावेश "libavutil/avassert.h"
#समावेश "libavutil/buffer.h"
#समावेश "libavutil/dict.h"
#समावेश "libavutil/display.h"
#समावेश "libavutil/downmix_info.h"
#समावेश "libavutil/error.h"
#समावेश "libavutil/frame.h"
#समावेश "libavutil/macros.h"
#समावेश "libavutil/mem.h"
#समावेश "libavutil/motion_vector.h"
#समावेश "libavutil/spherical.h"
#समावेश "libavutil/stereo3d.h"

प्रकार काष्ठा Set {
    AVFrame_Side_तथ्य **sd;
    पूर्णांक            nb_sd;
} Set;

/* Every entry below carries a payload laid out as AVFrameSideDataType
 * documents for its type: a producer owes that layout even when no consumer
 * reads the buffer back. The small number that identifies an entry in the
 * reference output therefore lives in the metadata dictionary, which
 * av_frame_side_data_clone() copies along with the buffer. */
अटल व्योम set_marker(AVFrame_Side_तथ्य *sd, पूर्णांक marker)
{
    अक्षर मूल्य[16];

    snprintf(मूल्य, माप(मूल्य), "%d", marker);
    av_assert0(av_dict_set(&sd->metadata, "marker", मूल्य, 0) >= 0);
}

अटल AVFrame_Side_तथ्य *new_entry(Set *s, क्रमागत AVFrame_Side_तथ्य_Type type,
                                  स्थिर व्योम *payload, माप_प्रकार आकार, पूर्णांक marker)
{
    AVFrame_Side_तथ्य *sd = av_frame_side_तथ्य_new(&s->sd, &s->nb_sd, type,
                                                 आकार, 0);

    av_assert0(sd && sd->आकार == आकार);
    स_नकल(sd->तथ्य, payload, आकार);
    set_marker(sd, marker);
    वापस sd;
}

अटल AVBufferRef *payload_बफर(स्थिर व्योम *payload, माप_प्रकार आकार)
{
    AVBufferRef *buf = av_बफर_alloc(आकार);

    av_assert0(buf);
    स_नकल(buf->तथ्य, payload, आकार);
    वापस buf;
}

अटल स्थिर अक्षर *entry_marker(स्थिर AVFrame_Side_तथ्य *sd)
{
    स्थिर AVDictionaryEntry *e = av_dict_get(sd->metadata, "marker", शून्य, 0);

    वापस e ? e->मूल्य : "none";
}

अटल व्योम print_set(स्थिर अक्षर *label, स्थिर Set *s)
{
    म_लिखो("%s: n=%d\n", label, s->nb_sd);
    क्रम (पूर्णांक i = 0; i < s->nb_sd; i++)
        म_लिखो("  [%d] %s marker=%s\n", i,
               av_frame_side_तथ्य_name(s->sd[i]->type),
               entry_marker(s->sd[i]));
}

/* Dumps a set by looking each type up instead of walking the array. Removal is
 * documented to drop the matching entries, not to keep the survivors where
 * they were, so printing by index would tie the reference to the current habit
 * of moving the last entry into the freed slot. */
अटल व्योम print_lookup(स्थिर अक्षर *label, स्थिर Set *s,
                         स्थिर क्रमागत AVFrame_Side_तथ्य_Type *types, माप_प्रकार nb_types)
{
    म_लिखो("%s: n=%d\n", label, s->nb_sd);
    क्रम (माप_प्रकार i = 0; i < nb_types; i++) {
        स्थिर AVFrame_Side_तथ्य *sd =
            av_frame_side_तथ्य_get(s->sd, s->nb_sd, types[i]);
        स्थिर अक्षर *name = av_frame_side_तथ्य_name(types[i]);

        अगर (sd)
            म_लिखो("    %s: marker=%s\n", name, entry_marker(sd));
        अन्यथा
            म_लिखो("    %s: absent\n", name);
    }
}

पूर्णांक मुख्य(व्योम)
{
    /* desc / name accessors. */
    म_लिखो("Testing av_frame_side_data_desc() / av_frame_side_data_name()\n");
    अटल स्थिर क्रमागत AVFrame_Side_तथ्य_Type known[] = {
        AV_FRAME_तथ्य_STEREO3_D,                    /* PROP_GLOBAL */
        AV_FRAME_तथ्य_DYNAMIC_HDR_PLUS,            /* PROP_COLOR_DEPENDENT */
        AV_FRAME_तथ्य_SPHERICAL,                   /* PROP_GLOBAL|SIZE_DEPENDENT */
        AV_FRAME_तथ्य_DOWNMIX_INFO,                /* PROP_CHANNEL_DEPENDENT */
        AV_FRAME_तथ्य_SEI_UNREGISTERED,            /* PROP_MULTI */
    };
    क्रम (माप_प्रकार i = 0; i < FF_ARRAY_ELEMS(known); i++) {
        स्थिर AVSide_तथ्य_Descriptor *d = av_frame_side_तथ्य_desc(known[i]);
        स्थिर अक्षर *n = av_frame_side_तथ्य_name(known[i]);
        /* Compare content: the API only promises a string identifying the
         * type, not the descriptor's own pointer. */
        म_लिखो("  type=%d name_match=%s props=0x%x\n", known[i],
               d && n && !म_भेद(d->name, n) ? "yes" : "no",
               d ? d->props : 0);
    }

    /* Invalid / unmapped types must return NULL (sd_props gap). */
    {
        क्रमागत AVFrame_Side_तथ्य_Type bad = (क्रमागत AVFrame_Side_तथ्य_Type)-1;
        म_लिखो("  invalid type desc=%s name=%s\n",
               av_frame_side_तथ्य_desc(bad) ? "non-null" : "null",
               av_frame_side_तथ्य_name(bad) ? "non-null" : "null");
    }

    /* Payloads. The two structs are allocated through their public
     * allocators because their sizes are not part of the public ABI. */
    माप_प्रकार stereo3d_आकार, spherical_आकार;
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
    stereo3d->primary_eye = AV_PRIMARY_EYE_बायाँ;
    stereo3d->baseline    = 65000;

    spherical->projection = AV_SPHERICAL_EQUIRECTANGULAR;
    spherical->yaw        = 90 << 16;

    av_display_rotation_set(displaymatrix, 90.0);

    /* Populate a set with several types, one of them MULTI. */
    Set set = { 0 };
    new_entry(&set, AV_FRAME_तथ्य_STEREO3_D, stereo3d, stereo3d_आकार, 100);
    new_entry(&set, AV_FRAME_तथ्य_DOWNMIX_INFO, &downmix, माप(downmix),
              200);
    new_entry(&set, AV_FRAME_तथ्य_SEI_UNREGISTERED, udu, माप(udu), 1);
    udu[माप(udu) - 1] = '2';
    new_entry(&set, AV_FRAME_तथ्य_SEI_UNREGISTERED, udu, माप(udu), 2);
    new_entry(&set, AV_FRAME_तथ्य_SPHERICAL, spherical, spherical_आकार, 300);
    /* Entries are appended, so this dump is the insertion order by
     * construction and shows both MULTI entries. */
    print_set("\nInitial set", &set);

    /* Types probed by every dump below. */
    अटल स्थिर क्रमागत AVFrame_Side_तथ्य_Type probed[] = {
        AV_FRAME_तथ्य_STEREO3_D,
        AV_FRAME_तथ्य_DOWNMIX_INFO,
        AV_FRAME_तथ्य_SEI_UNREGISTERED,
        AV_FRAME_तथ्य_SPHERICAL,
        AV_FRAME_तथ्य_DISPLAYMATRIX,
        AV_FRAME_तथ्य_MOTION_VECTORS,
    };

    /* get / get_c: present and missing types. */
    म_लिखो("\nTesting av_frame_side_data_get()\n");
    {
        स्थिर AVFrame_Side_तथ्य *got =
            av_frame_side_तथ्य_get(set.sd, set.nb_sd, AV_FRAME_तथ्य_STEREO3_D);
        म_लिखो("  stereo3d: %s marker=%s payload_match=%s\n",
               got ? "found" : "missing", got ? entry_marker(got) : "none",
               got && got->आकार == stereo3d_आकार &&
               !स_भेद(got->तथ्य, stereo3d, stereo3d_आकार) ? "yes" : "no");
        got = av_frame_side_तथ्य_get(set.sd, set.nb_sd,
                                     AV_FRAME_तथ्य_MASTERING_DISPLAY_METADATA);
        म_लिखो("  mastering (absent): %s\n", got ? "FAIL" : "null");
    }

    /* remove by type clears all matching entries (including duplicates). */
    म_लिखो("\nTesting av_frame_side_data_remove()\n");
    av_frame_side_तथ्य_remove(&set.sd, &set.nb_sd,
                              AV_FRAME_तथ्य_SEI_UNREGISTERED);
    print_lookup("  after remove SEI_UNREGISTERED", &set,
                 probed, FF_ARRAY_ELEMS(probed));

    /* remove_by_props: PROP_GLOBAL drops STEREO3D and SPHERICAL. */
    म_लिखो("\nTesting av_frame_side_data_remove_by_props()\n");
    av_frame_side_तथ्य_remove_by_props(&set.sd, &set.nb_sd,
                                       AV_SIDE_तथ्य_PROP_GLOBAL);
    print_lookup("  after remove_by_props(GLOBAL)", &set,
                 probed, FF_ARRAY_ELEMS(probed));

    /* Clone: copy remaining entry into a second set. */
    म_लिखो("\nTesting av_frame_side_data_clone()\n");
    Set dst = { 0 };
    अगर (set.nb_sd > 0) {
        पूर्णांक ret = av_frame_side_तथ्य_clone(&dst.sd, &dst.nb_sd,
                                           set.sd[0], 0);
        म_लिखो("  clone into empty: ret=%d nb=%d marker=%s\n", ret, dst.nb_sd,
               dst.nb_sd ? entry_marker(dst.sd[0]) : "none");

        /* Same type again without REPLACE must fail with EEXIST. */
        ret = av_frame_side_तथ्य_clone(&dst.sd, &dst.nb_sd, set.sd[0], 0);
        म_लिखो("  clone duplicate no REPLACE: ret==AVERROR(EEXIST)=%s\n",
               ret == AVERROR(EEXIST) ? "yes" : "no");

        /* With REPLACE, clone replaces the existing entry in place. */
        ret = av_frame_side_तथ्य_clone(&dst.sd, &dst.nb_sd, set.sd[0],
                                       AV_FRAME_SIDE_तथ्य_FLAG_REPLACE);
        म_लिखो("  clone REPLACE: ret=%d nb=%d\n", ret, dst.nb_sd);

        /* Invalid args. */
        ret = av_frame_side_तथ्य_clone(शून्य, &dst.nb_sd, set.sd[0], 0);
        म_लिखो("  clone NULL sd: ret==AVERROR(EINVAL)=%s\n",
               ret == AVERROR(EINVAL) ? "yes" : "no");
    }

    /* add: buffer ownership transfer and NEW_REF. */
    म_लिखो("\nTesting av_frame_side_data_add()\n");
    {
        AVBufferRef *buf = payload_बफर(displaymatrix, माप(displaymatrix));

        AVFrame_Side_तथ्य *sd_added =
            av_frame_side_तथ्य_add(&dst.sd, &dst.nb_sd,
                                   AV_FRAME_तथ्य_DISPLAYMATRIX,
                                   &buf, AV_FRAME_SIDE_तथ्य_FLAG_UNIQUE);
        म_लिखो("  add (move): added=%s pbuf_nulled=%s\n",
               sd_added ? "yes" : "no", buf == शून्य ? "yes" : "no");
        अगर (sd_added)
            set_marker(sd_added, 999);

        /* NEW_REF: the caller retains its reference. */
        AVBufferRef *keep = payload_बफर(mvs, माप(mvs));
        sd_added = av_frame_side_तथ्य_add(&dst.sd, &dst.nb_sd,
                                          AV_FRAME_तथ्य_MOTION_VECTORS, &keep,
                                          AV_FRAME_SIDE_तथ्य_FLAG_NEW_REF);
        म_लिखो("  add (NEW_REF): added=%s caller_ref_kept=%s nb_mvs=%d\n",
               sd_added ? "yes" : "no", keep ? "yes" : "no",
               sd_added ? (पूर्णांक)(sd_added->आकार / माप(AVMotionVector)) : -1);
        अगर (sd_added)
            set_marker(sd_added, 42);
        av_बफर_unref(&keep);

        /* REPLACE on existing entry: same type, payload swaps in place. */
        int32_t replacement[9];
        av_display_rotation_set(replacement, 180.0);
        AVBufferRef *repl = payload_बफर(replacement, माप(replacement));
        sd_added = av_frame_side_तथ्य_add(&dst.sd, &dst.nb_sd,
                                          AV_FRAME_तथ्य_DISPLAYMATRIX, &repl,
                                          AV_FRAME_SIDE_तथ्य_FLAG_REPLACE);
        अगर (sd_added)
            set_marker(sd_added, 1234);
        {
            स्थिर AVFrame_Side_तथ्य *after =
                av_frame_side_तथ्य_get(dst.sd, dst.nb_sd,
                                       AV_FRAME_तथ्य_DISPLAYMATRIX);
            म_लिखो("  add (REPLACE existing): added=%s marker=%s"
                   " payload_match=%s\n",
                   sd_added ? "yes" : "no",
                   after ? entry_marker(after) : "none",
                   after && after->आकार == माप(replacement) &&
                   !स_भेद(after->तथ्य, replacement, माप(replacement)) ?
                   "yes" : "no");
        }
    }

    /* clone with UNIQUE: existing same-type entry is removed first. dst
     * already has a set.sd[0]->type entry from the REPLACE clone above. */
    म_लिखो("\nTesting av_frame_side_data_clone() UNIQUE\n");
    अगर (set.nb_sd > 0) {
        पूर्णांक before = dst.nb_sd;
        पूर्णांक ret = av_frame_side_तथ्य_clone(&dst.sd, &dst.nb_sd, set.sd[0],
                                           AV_FRAME_SIDE_तथ्य_FLAG_UNIQUE);
        म_लिखो("  clone UNIQUE: ret=%d before=%d after=%d\n",
               ret, before, dst.nb_sd);
    }

    print_lookup("\nFinal dst", &dst, probed, FF_ARRAY_ELEMS(probed));

    av_frame_side_तथ्य_free(&dst.sd, &dst.nb_sd);
    av_frame_side_तथ्य_free(&set.sd, &set.nb_sd);
    म_लिखो("\nfree: set_nb=%d dst_nb=%d\n", set.nb_sd, dst.nb_sd);

    av_free(stereo3d);
    av_free(spherical);

    वापस 0;
}
