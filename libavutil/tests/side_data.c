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

#ضمن <stdio.h>
#ضمن <string.h>

#ضمن "libavutil/avassert.h"
#ضمن "libavutil/buffer.h"
#ضمن "libavutil/dict.h"
#ضمن "libavutil/display.h"
#ضمن "libavutil/downmix_info.h"
#ضمن "libavutil/error.h"
#ضمن "libavutil/frame.h"
#ضمن "libavutil/macros.h"
#ضمن "libavutil/mem.h"
#ضمن "libavutil/motion_vector.h"
#ضمن "libavutil/spherical.h"
#ضمن "libavutil/stereo3d.h"

تعريفنوع بنية مجموعه_2 {
    AVFrame_Side_داده **sd;
    صحيح            nb_sd;
} مجموعه_2;

/* Every entry below carries a payload laid out as AVFrameSideDataType
 * documents for its type: a producer owes that layout even when no consumer
 * reads the buffer back. The small number that identifies an entry in the
 * reference output therefore lives in the metadata dictionary, which
 * av_frame_side_data_clone() copies along with the buffer. */
ساكن فراغ مجموعه_marker(AVFrame_Side_داده *sd, صحيح marker)
{
    حرف مقدار[16];

    snprintf(مقدار, حجم(مقدار), "%d", marker);
    av_assert0(av_dict_مجموعه(&sd->metadata, "marker", مقدار, 0) >= 0);
}

ساكن AVFrame_Side_داده *new_مدخل(مجموعه_2 *s, تعداد AVFrame_Side_داده_Type type,
                                  ثابت فراغ *payload, size_t اندازه, صحيح marker)
{
    AVFrame_Side_داده *sd = av_قاب_side_داده_new(&s->sd, &s->nb_sd, type,
                                                 اندازه, 0);

    av_assert0(sd && sd->اندازه == اندازه);
    کپی_حافظه(sd->داده, payload, اندازه);
    مجموعه_marker(sd, marker);
    أرجع sd;
}

ساكن AVBufferRef *payload_میانگیر(ثابت فراغ *payload, size_t اندازه)
{
    AVBufferRef *buf = av_میانگیر_alloc(اندازه);

    av_assert0(buf);
    کپی_حافظه(buf->داده, payload, اندازه);
    أرجع buf;
}

ساكن ثابت حرف *مدخل_marker(ثابت AVFrame_Side_داده *sd)
{
    ثابت AVDictionary_مدخل *e = av_dict_get(sd->metadata, "marker", عدم, 0);

    أرجع e ? e->مقدار : "none";
}

ساكن فراغ print_مجموعه(ثابت حرف *label, ثابت مجموعه_2 *s)
{
    چاپ_کن("%s: n=%d\n", label, s->nb_sd);
    لكل (صحيح i = 0; i < s->nb_sd; i++)
        چاپ_کن("  [%d] %s marker=%s\n", i,
               av_قاب_side_داده_name(s->sd[i]->type),
               مدخل_marker(s->sd[i]));
}

/* Dumps a set by looking each type up instead of walking the array. Removal is
 * documented to drop the matching entries, not to keep the survivors where
 * they were, so printing by index would tie the reference to the current habit
 * of moving the last entry into the freed slot. */
ساكن فراغ print_lookup(ثابت حرف *label, ثابت مجموعه_2 *s,
                         ثابت تعداد AVFrame_Side_داده_Type *types, size_t nb_types)
{
    چاپ_کن("%s: n=%d\n", label, s->nb_sd);
    لكل (size_t i = 0; i < nb_types; i++) {
        ثابت AVFrame_Side_داده *sd =
            av_قاب_side_داده_get(s->sd, s->nb_sd, types[i]);
        ثابت حرف *name = av_قاب_side_داده_name(types[i]);

        إذا (sd)
            چاپ_کن("    %s: marker=%s\n", name, مدخل_marker(sd));
        وإلا
            چاپ_کن("    %s: absent\n", name);
    }
}

صحيح اصلی(فراغ)
{
    /* desc / name accessors. */
    چاپ_کن("Testing av_frame_side_data_desc() / av_frame_side_data_name()\n");
    ساكن ثابت تعداد AVFrame_Side_داده_Type معلوم[] = {
        AV_قاب_داده_STEREO3_D,                    /* PROP_GLOBAL */
        AV_قاب_داده_DYNAMIC_HDR_PLUS,            /* PROP_COLOR_DEPENDENT */
        AV_قاب_داده_SPHERICAL,                   /* PROP_GLOBAL|SIZE_DEPENDENT */
        AV_قاب_داده_DOWNMIX_INFO,                /* PROP_CHANNEL_DEPENDENT */
        AV_قاب_داده_SEI_UNREGISTERED,            /* PROP_MULTI */
    };
    لكل (size_t i = 0; i < FF_ARRAY_ELEMS(معلوم); i++) {
        ثابت AVSide_داده_Descriptor *d = av_قاب_side_داده_desc(معلوم[i]);
        ثابت حرف *n = av_قاب_side_داده_name(معلوم[i]);
        /* Compare content: the API only promises a string identifying the
         * type, not the descriptor's own pointer. */
        چاپ_کن("  type=%d name_match=%s props=0x%x\n", معلوم[i],
               d && n && !strcmp(d->name, n) ? "yes" : "no",
               d ? d->props : 0);
    }

    /* Invalid / unmapped types must return NULL (sd_props gap). */
    {
        تعداد AVFrame_Side_داده_Type bad = (تعداد AVFrame_Side_داده_Type)-1;
        چاپ_کن("  invalid type desc=%s name=%s\n",
               av_قاب_side_داده_desc(bad) ? "non-null" : "null",
               av_قاب_side_داده_name(bad) ? "non-null" : "null");
    }

    /* Payloads. The two structs are allocated through their public
     * allocators because their sizes are not part of the public ABI. */
    size_t stereo3d_اندازه, spherical_اندازه;
    AVStereo3D         *stereo3d  = av_stereo3d_alloc_اندازه(&stereo3d_اندازه);
    AVSphericalMapping *spherical = av_spherical_alloc(&spherical_اندازه);
    /* 16 bytes of uuid_iso_iec_11578 followed by user_data_payload_byte. */
    uint8_t udu[16 + 8] = {
        0x9a, 0x21, 0xf3, 0x4d, 0x6b, 0x1c, 0x47, 0x8e,
        0xa5, 0x30, 0xc2, 0x7f, 0x11, 0x8d, 0x46, 0x02,
        'p',  'a',  'y',  'l',  'o',  'a',  'd',  '1',
    };
    int32_t displaymatrix[9];
    /* src_x = dst_x + motion_x / motion_scale, likewise for y. */
    AVMotion_وکتور mvs[2] = {
        { .منبع = -1, .w = 16, .h = 16, .src_x = 32, .src_y = 48,
          .dst_x = 40, .dst_y = 48, .motion_x = -8, .motion_y = 0,
          .motion_scale = 1 },
        { .منبع =  1, .w =  8, .h =  8, .src_x = 64, .src_y = 64,
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
    stereo3d->primary_eye = AV_PRIMARY_EYE_چپ;
    stereo3d->baseline    = 65000;

    spherical->projection = AV_SPHERICAL_EQUIRECTANGULAR;
    spherical->yaw        = 90 << 16;

    av_display_rotation_مجموعه(displaymatrix, 90.0);

    /* Populate a set with several types, one of them MULTI. */
    مجموعه_2 مجموعه = { 0 };
    new_مدخل(&مجموعه, AV_قاب_داده_STEREO3_D, stereo3d, stereo3d_اندازه, 100);
    new_مدخل(&مجموعه, AV_قاب_داده_DOWNMIX_INFO, &downmix, حجم(downmix),
              200);
    new_مدخل(&مجموعه, AV_قاب_داده_SEI_UNREGISTERED, udu, حجم(udu), 1);
    udu[حجم(udu) - 1] = '2';
    new_مدخل(&مجموعه, AV_قاب_داده_SEI_UNREGISTERED, udu, حجم(udu), 2);
    new_مدخل(&مجموعه, AV_قاب_داده_SPHERICAL, spherical, spherical_اندازه, 300);
    /* Entries are appended, so this dump is the insertion order by
     * construction and shows both MULTI entries. */
    print_مجموعه("\nInitial set", &مجموعه);

    /* Types probed by every dump below. */
    ساكن ثابت تعداد AVFrame_Side_داده_Type probed[] = {
        AV_قاب_داده_STEREO3_D,
        AV_قاب_داده_DOWNMIX_INFO,
        AV_قاب_داده_SEI_UNREGISTERED,
        AV_قاب_داده_SPHERICAL,
        AV_قاب_داده_DISPLAYMATRIX,
        AV_قاب_داده_MOTION_VECTORS,
    };

    /* get / get_c: present and missing types. */
    چاپ_کن("\nTesting av_frame_side_data_get()\n");
    {
        ثابت AVFrame_Side_داده *got =
            av_قاب_side_داده_get(مجموعه.sd, مجموعه.nb_sd, AV_قاب_داده_STEREO3_D);
        چاپ_کن("  stereo3d: %s marker=%s payload_match=%s\n",
               got ? "found" : "missing", got ? مدخل_marker(got) : "none",
               got && got->اندازه == stereo3d_اندازه &&
               !memcmp(got->داده, stereo3d, stereo3d_اندازه) ? "yes" : "no");
        got = av_قاب_side_داده_get(مجموعه.sd, مجموعه.nb_sd,
                                     AV_قاب_داده_MASTERING_DISPLAY_METADATA);
        چاپ_کن("  mastering (absent): %s\n", got ? "FAIL" : "null");
    }

    /* remove by type clears all matching entries (including duplicates). */
    چاپ_کن("\nTesting av_frame_side_data_remove()\n");
    av_قاب_side_داده_remove(&مجموعه.sd, &مجموعه.nb_sd,
                              AV_قاب_داده_SEI_UNREGISTERED);
    print_lookup("  after remove SEI_UNREGISTERED", &مجموعه,
                 probed, FF_ARRAY_ELEMS(probed));

    /* remove_by_props: PROP_GLOBAL drops STEREO3D and SPHERICAL. */
    چاپ_کن("\nTesting av_frame_side_data_remove_by_props()\n");
    av_قاب_side_داده_remove_by_props(&مجموعه.sd, &مجموعه.nb_sd,
                                       AV_SIDE_داده_PROP_GLOBAL);
    print_lookup("  after remove_by_props(GLOBAL)", &مجموعه,
                 probed, FF_ARRAY_ELEMS(probed));

    /* Clone: copy remaining entry into a second set. */
    چاپ_کن("\nTesting av_frame_side_data_clone()\n");
    مجموعه_2 dst = { 0 };
    إذا (مجموعه.nb_sd > 0) {
        صحيح ret = av_قاب_side_داده_clone(&dst.sd, &dst.nb_sd,
                                           مجموعه.sd[0], 0);
        چاپ_کن("  clone into empty: ret=%d nb=%d marker=%s\n", ret, dst.nb_sd,
               dst.nb_sd ? مدخل_marker(dst.sd[0]) : "none");

        /* Same type again without REPLACE must fail with EEXIST. */
        ret = av_قاب_side_داده_clone(&dst.sd, &dst.nb_sd, مجموعه.sd[0], 0);
        چاپ_کن("  clone duplicate no REPLACE: ret==AVERROR(EEXIST)=%s\n",
               ret == AVERROR(EEXIST) ? "yes" : "no");

        /* With REPLACE, clone replaces the existing entry in place. */
        ret = av_قاب_side_داده_clone(&dst.sd, &dst.nb_sd, مجموعه.sd[0],
                                       AV_قاب_SIDE_داده_FLAG_REPLACE);
        چاپ_کن("  clone REPLACE: ret=%d nb=%d\n", ret, dst.nb_sd);

        /* Invalid args. */
        ret = av_قاب_side_داده_clone(عدم, &dst.nb_sd, مجموعه.sd[0], 0);
        چاپ_کن("  clone NULL sd: ret==AVERROR(EINVAL)=%s\n",
               ret == AVERROR(EINVAL) ? "yes" : "no");
    }

    /* add: buffer ownership transfer and NEW_REF. */
    چاپ_کن("\nTesting av_frame_side_data_add()\n");
    {
        AVBufferRef *buf = payload_میانگیر(displaymatrix, حجم(displaymatrix));

        AVFrame_Side_داده *sd_added =
            av_قاب_side_داده_جمع_کن(&dst.sd, &dst.nb_sd,
                                   AV_قاب_داده_DISPLAYMATRIX,
                                   &buf, AV_قاب_SIDE_داده_FLAG_UNIQUE);
        چاپ_کن("  add (move): added=%s pbuf_nulled=%s\n",
               sd_added ? "yes" : "no", buf == عدم ? "yes" : "no");
        إذا (sd_added)
            مجموعه_marker(sd_added, 999);

        /* NEW_REF: the caller retains its reference. */
        AVBufferRef *keep = payload_میانگیر(mvs, حجم(mvs));
        sd_added = av_قاب_side_داده_جمع_کن(&dst.sd, &dst.nb_sd,
                                          AV_قاب_داده_MOTION_VECTORS, &keep,
                                          AV_قاب_SIDE_داده_FLAG_NEW_REF);
        چاپ_کن("  add (NEW_REF): added=%s caller_ref_kept=%s nb_mvs=%d\n",
               sd_added ? "yes" : "no", keep ? "yes" : "no",
               sd_added ? (صحيح)(sd_added->اندازه / حجم(AVMotion_وکتور)) : -1);
        إذا (sd_added)
            مجموعه_marker(sd_added, 42);
        av_میانگیر_unref(&keep);

        /* REPLACE on existing entry: same type, payload swaps in place. */
        int32_t replacement[9];
        av_display_rotation_مجموعه(replacement, 180.0);
        AVBufferRef *repl = payload_میانگیر(replacement, حجم(replacement));
        sd_added = av_قاب_side_داده_جمع_کن(&dst.sd, &dst.nb_sd,
                                          AV_قاب_داده_DISPLAYMATRIX, &repl,
                                          AV_قاب_SIDE_داده_FLAG_REPLACE);
        إذا (sd_added)
            مجموعه_marker(sd_added, 1234);
        {
            ثابت AVFrame_Side_داده *after =
                av_قاب_side_داده_get(dst.sd, dst.nb_sd,
                                       AV_قاب_داده_DISPLAYMATRIX);
            چاپ_کن("  add (REPLACE existing): added=%s marker=%s"
                   " payload_match=%s\n",
                   sd_added ? "yes" : "no",
                   after ? مدخل_marker(after) : "none",
                   after && after->اندازه == حجم(replacement) &&
                   !memcmp(after->داده, replacement, حجم(replacement)) ?
                   "yes" : "no");
        }
    }

    /* clone with UNIQUE: existing same-type entry is removed first. dst
     * already has a set.sd[0]->type entry from the REPLACE clone above. */
    چاپ_کن("\nTesting av_frame_side_data_clone() UNIQUE\n");
    إذا (مجموعه.nb_sd > 0) {
        صحيح before = dst.nb_sd;
        صحيح ret = av_قاب_side_داده_clone(&dst.sd, &dst.nb_sd, مجموعه.sd[0],
                                           AV_قاب_SIDE_داده_FLAG_UNIQUE);
        چاپ_کن("  clone UNIQUE: ret=%d before=%d after=%d\n",
               ret, before, dst.nb_sd);
    }

    print_lookup("\nFinal dst", &dst, probed, FF_ARRAY_ELEMS(probed));

    av_قاب_side_داده_free(&dst.sd, &dst.nb_sd);
    av_قاب_side_داده_free(&مجموعه.sd, &مجموعه.nb_sd);
    چاپ_کن("\nfree: set_nb=%d dst_nb=%d\n", مجموعه.nb_sd, dst.nb_sd);

    av_free(stereo3d);
    av_free(spherical);

    أرجع 0;
}
