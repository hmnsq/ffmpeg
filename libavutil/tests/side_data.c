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

تعريفنوع بنية سيٽ_2 {
    AVFrame_Side_معلومات **sd;
    صحيح            nb_sd;
} سيٽ_2;

/* Every entry below carries a payload laid out as AVFrameSideDataType
 * documents for its type: a producer owes that layout even when no consumer
 * reads the buffer back. The small number that identifies an entry in the
 * reference output therefore lives in the metadata dictionary, which
 * av_frame_side_data_clone() copies along with the buffer. */
ساكن فراغ سيٽ_marker(AVFrame_Side_معلومات *sd, صحيح marker)
{
    حرف قدر[16];

    snprintf(قدر, حجم(قدر), "%d", marker);
    av_assert0(av_dict_سيٽ(&sd->metadata, "marker", قدر, 0) >= 0);
}

ساكن AVFrame_Side_معلومات *new_داخلا(سيٽ_2 *s, تعداد AVFrame_Side_معلومات_Type type,
                                  ثابت فراغ *payload, size_t سائيز, صحيح marker)
{
    AVFrame_Side_معلومات *sd = av_چوکٺو_side_معلومات_new(&s->sd, &s->nb_sd, type,
                                                 سائيز, 0);

    av_assert0(sd && sd->سائيز == سائيز);
    يادگيري_نقل(sd->معلومات, payload, سائيز);
    سيٽ_marker(sd, marker);
    أرجع sd;
}

ساكن AVBufferRef *payload_بفر(ثابت فراغ *payload, size_t سائيز)
{
    AVBufferRef *buf = av_بفر_alloc(سائيز);

    av_assert0(buf);
    يادگيري_نقل(buf->معلومات, payload, سائيز);
    أرجع buf;
}

ساكن ثابت حرف *داخلا_marker(ثابت AVFrame_Side_معلومات *sd)
{
    ثابت AVDictionary_داخلا *e = av_dict_get(sd->metadata, "marker", عدم, 0);

    أرجع e ? e->قدر : "none";
}

ساكن فراغ print_سيٽ(ثابت حرف *label, ثابت سيٽ_2 *s)
{
    لکو("%s: n=%d\n", label, s->nb_sd);
    لكل (صحيح i = 0; i < s->nb_sd; i++)
        لکو("  [%d] %s marker=%s\n", i,
               av_چوکٺو_side_معلومات_name(s->sd[i]->type),
               داخلا_marker(s->sd[i]));
}

/* Dumps a set by looking each type up instead of walking the array. Removal is
 * documented to drop the matching entries, not to keep the survivors where
 * they were, so printing by index would tie the reference to the current habit
 * of moving the last entry into the freed slot. */
ساكن فراغ print_lookup(ثابت حرف *label, ثابت سيٽ_2 *s,
                         ثابت تعداد AVFrame_Side_معلومات_Type *types, size_t nb_types)
{
    لکو("%s: n=%d\n", label, s->nb_sd);
    لكل (size_t i = 0; i < nb_types; i++) {
        ثابت AVFrame_Side_معلومات *sd =
            av_چوکٺو_side_معلومات_get(s->sd, s->nb_sd, types[i]);
        ثابت حرف *name = av_چوکٺو_side_معلومات_name(types[i]);

        إذا (sd)
            لکو("    %s: marker=%s\n", name, داخلا_marker(sd));
        وإلا
            لکو("    %s: absent\n", name);
    }
}

صحيح مکيه(فراغ)
{
    /* desc / name accessors. */
    لکو("Testing av_frame_side_data_desc() / av_frame_side_data_name()\n");
    ساكن ثابت تعداد AVFrame_Side_معلومات_Type معلوم[] = {
        AV_چوکٺو_معلومات_STEREO3_D,                    /* PROP_GLOBAL */
        AV_چوکٺو_معلومات_DYNAMIC_HDR_PLUS,            /* PROP_COLOR_DEPENDENT */
        AV_چوکٺو_معلومات_SPHERICAL,                   /* PROP_GLOBAL|SIZE_DEPENDENT */
        AV_چوکٺو_معلومات_DOWNMIX_INFO,                /* PROP_CHANNEL_DEPENDENT */
        AV_چوکٺو_معلومات_SEI_UNREGISTERED,            /* PROP_MULTI */
    };
    لكل (size_t i = 0; i < FF_ARRAY_ELEMS(معلوم); i++) {
        ثابت AVSide_معلومات_Descriptor *d = av_چوکٺو_side_معلومات_desc(معلوم[i]);
        ثابت حرف *n = av_چوکٺو_side_معلومات_name(معلوم[i]);
        /* Compare content: the API only promises a string identifying the
         * type, not the descriptor's own pointer. */
        لکو("  type=%d name_match=%s props=0x%x\n", معلوم[i],
               d && n && !strcmp(d->name, n) ? "yes" : "no",
               d ? d->props : 0);
    }

    /* Invalid / unmapped types must return NULL (sd_props gap). */
    {
        تعداد AVFrame_Side_معلومات_Type bad = (تعداد AVFrame_Side_معلومات_Type)-1;
        لکو("  invalid type desc=%s name=%s\n",
               av_چوکٺو_side_معلومات_desc(bad) ? "non-null" : "null",
               av_چوکٺو_side_معلومات_name(bad) ? "non-null" : "null");
    }

    /* Payloads. The two structs are allocated through their public
     * allocators because their sizes are not part of the public ABI. */
    size_t stereo3d_سائيز, spherical_سائيز;
    AVStereo3D         *stereo3d  = av_stereo3d_alloc_سائيز(&stereo3d_سائيز);
    AVSphericalMapping *spherical = av_spherical_alloc(&spherical_سائيز);
    /* 16 bytes of uuid_iso_iec_11578 followed by user_data_payload_byte. */
    uint8_t udu[16 + 8] = {
        0x9a, 0x21, 0xf3, 0x4d, 0x6b, 0x1c, 0x47, 0x8e,
        0xa5, 0x30, 0xc2, 0x7f, 0x11, 0x8d, 0x46, 0x02,
        'p',  'a',  'y',  'l',  'o',  'a',  'd',  '1',
    };
    int32_t displaymatrix[9];
    /* src_x = dst_x + motion_x / motion_scale, likewise for y. */
    AVMotion_ويڪٽر mvs[2] = {
        { .ذريعو = -1, .w = 16, .h = 16, .src_x = 32, .src_y = 48,
          .dst_x = 40, .dst_y = 48, .motion_x = -8, .motion_y = 0,
          .motion_scale = 1 },
        { .ذريعو =  1, .w =  8, .h =  8, .src_x = 64, .src_y = 64,
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
    stereo3d->primary_eye = AV_PRIMARY_EYE_کاٻو;
    stereo3d->baseline    = 65000;

    spherical->projection = AV_SPHERICAL_EQUIRECTANGULAR;
    spherical->yaw        = 90 << 16;

    av_display_rotation_سيٽ(displaymatrix, 90.0);

    /* Populate a set with several types, one of them MULTI. */
    سيٽ_2 سيٽ = { 0 };
    new_داخلا(&سيٽ, AV_چوکٺو_معلومات_STEREO3_D, stereo3d, stereo3d_سائيز, 100);
    new_داخلا(&سيٽ, AV_چوکٺو_معلومات_DOWNMIX_INFO, &downmix, حجم(downmix),
              200);
    new_داخلا(&سيٽ, AV_چوکٺو_معلومات_SEI_UNREGISTERED, udu, حجم(udu), 1);
    udu[حجم(udu) - 1] = '2';
    new_داخلا(&سيٽ, AV_چوکٺو_معلومات_SEI_UNREGISTERED, udu, حجم(udu), 2);
    new_داخلا(&سيٽ, AV_چوکٺو_معلومات_SPHERICAL, spherical, spherical_سائيز, 300);
    /* Entries are appended, so this dump is the insertion order by
     * construction and shows both MULTI entries. */
    print_سيٽ("\nInitial set", &سيٽ);

    /* Types probed by every dump below. */
    ساكن ثابت تعداد AVFrame_Side_معلومات_Type probed[] = {
        AV_چوکٺو_معلومات_STEREO3_D,
        AV_چوکٺو_معلومات_DOWNMIX_INFO,
        AV_چوکٺو_معلومات_SEI_UNREGISTERED,
        AV_چوکٺو_معلومات_SPHERICAL,
        AV_چوکٺو_معلومات_DISPLAYMATRIX,
        AV_چوکٺو_معلومات_MOTION_VECTORS,
    };

    /* get / get_c: present and missing types. */
    لکو("\nTesting av_frame_side_data_get()\n");
    {
        ثابت AVFrame_Side_معلومات *got =
            av_چوکٺو_side_معلومات_get(سيٽ.sd, سيٽ.nb_sd, AV_چوکٺو_معلومات_STEREO3_D);
        لکو("  stereo3d: %s marker=%s payload_match=%s\n",
               got ? "found" : "missing", got ? داخلا_marker(got) : "none",
               got && got->سائيز == stereo3d_سائيز &&
               !memcmp(got->معلومات, stereo3d, stereo3d_سائيز) ? "yes" : "no");
        got = av_چوکٺو_side_معلومات_get(سيٽ.sd, سيٽ.nb_sd,
                                     AV_چوکٺو_معلومات_MASTERING_DISPLAY_METADATA);
        لکو("  mastering (absent): %s\n", got ? "FAIL" : "null");
    }

    /* remove by type clears all matching entries (including duplicates). */
    لکو("\nTesting av_frame_side_data_remove()\n");
    av_چوکٺو_side_معلومات_remove(&سيٽ.sd, &سيٽ.nb_sd,
                              AV_چوکٺو_معلومات_SEI_UNREGISTERED);
    print_lookup("  after remove SEI_UNREGISTERED", &سيٽ,
                 probed, FF_ARRAY_ELEMS(probed));

    /* remove_by_props: PROP_GLOBAL drops STEREO3D and SPHERICAL. */
    لکو("\nTesting av_frame_side_data_remove_by_props()\n");
    av_چوکٺو_side_معلومات_remove_by_props(&سيٽ.sd, &سيٽ.nb_sd,
                                       AV_SIDE_معلومات_PROP_GLOBAL);
    print_lookup("  after remove_by_props(GLOBAL)", &سيٽ,
                 probed, FF_ARRAY_ELEMS(probed));

    /* Clone: copy remaining entry into a second set. */
    لکو("\nTesting av_frame_side_data_clone()\n");
    سيٽ_2 dst = { 0 };
    إذا (سيٽ.nb_sd > 0) {
        صحيح ret = av_چوکٺو_side_معلومات_clone(&dst.sd, &dst.nb_sd,
                                           سيٽ.sd[0], 0);
        لکو("  clone into empty: ret=%d nb=%d marker=%s\n", ret, dst.nb_sd,
               dst.nb_sd ? داخلا_marker(dst.sd[0]) : "none");

        /* Same type again without REPLACE must fail with EEXIST. */
        ret = av_چوکٺو_side_معلومات_clone(&dst.sd, &dst.nb_sd, سيٽ.sd[0], 0);
        لکو("  clone duplicate no REPLACE: ret==AVERROR(EEXIST)=%s\n",
               ret == AVERROR(EEXIST) ? "yes" : "no");

        /* With REPLACE, clone replaces the existing entry in place. */
        ret = av_چوکٺو_side_معلومات_clone(&dst.sd, &dst.nb_sd, سيٽ.sd[0],
                                       AV_چوکٺو_SIDE_معلومات_FLAG_REPLACE);
        لکو("  clone REPLACE: ret=%d nb=%d\n", ret, dst.nb_sd);

        /* Invalid args. */
        ret = av_چوکٺو_side_معلومات_clone(عدم, &dst.nb_sd, سيٽ.sd[0], 0);
        لکو("  clone NULL sd: ret==AVERROR(EINVAL)=%s\n",
               ret == AVERROR(EINVAL) ? "yes" : "no");
    }

    /* add: buffer ownership transfer and NEW_REF. */
    لکو("\nTesting av_frame_side_data_add()\n");
    {
        AVBufferRef *buf = payload_بفر(displaymatrix, حجم(displaymatrix));

        AVFrame_Side_معلومات *sd_added =
            av_چوکٺو_side_معلومات_جوڙيو(&dst.sd, &dst.nb_sd,
                                   AV_چوکٺو_معلومات_DISPLAYMATRIX,
                                   &buf, AV_چوکٺو_SIDE_معلومات_FLAG_UNIQUE);
        لکو("  add (move): added=%s pbuf_nulled=%s\n",
               sd_added ? "yes" : "no", buf == عدم ? "yes" : "no");
        إذا (sd_added)
            سيٽ_marker(sd_added, 999);

        /* NEW_REF: the caller retains its reference. */
        AVBufferRef *keep = payload_بفر(mvs, حجم(mvs));
        sd_added = av_چوکٺو_side_معلومات_جوڙيو(&dst.sd, &dst.nb_sd,
                                          AV_چوکٺو_معلومات_MOTION_VECTORS, &keep,
                                          AV_چوکٺو_SIDE_معلومات_FLAG_NEW_REF);
        لکو("  add (NEW_REF): added=%s caller_ref_kept=%s nb_mvs=%d\n",
               sd_added ? "yes" : "no", keep ? "yes" : "no",
               sd_added ? (صحيح)(sd_added->سائيز / حجم(AVMotion_ويڪٽر)) : -1);
        إذا (sd_added)
            سيٽ_marker(sd_added, 42);
        av_بفر_unref(&keep);

        /* REPLACE on existing entry: same type, payload swaps in place. */
        int32_t replacement[9];
        av_display_rotation_سيٽ(replacement, 180.0);
        AVBufferRef *repl = payload_بفر(replacement, حجم(replacement));
        sd_added = av_چوکٺو_side_معلومات_جوڙيو(&dst.sd, &dst.nb_sd,
                                          AV_چوکٺو_معلومات_DISPLAYMATRIX, &repl,
                                          AV_چوکٺو_SIDE_معلومات_FLAG_REPLACE);
        إذا (sd_added)
            سيٽ_marker(sd_added, 1234);
        {
            ثابت AVFrame_Side_معلومات *after =
                av_چوکٺو_side_معلومات_get(dst.sd, dst.nb_sd,
                                       AV_چوکٺو_معلومات_DISPLAYMATRIX);
            لکو("  add (REPLACE existing): added=%s marker=%s"
                   " payload_match=%s\n",
                   sd_added ? "yes" : "no",
                   after ? داخلا_marker(after) : "none",
                   after && after->سائيز == حجم(replacement) &&
                   !memcmp(after->معلومات, replacement, حجم(replacement)) ?
                   "yes" : "no");
        }
    }

    /* clone with UNIQUE: existing same-type entry is removed first. dst
     * already has a set.sd[0]->type entry from the REPLACE clone above. */
    لکو("\nTesting av_frame_side_data_clone() UNIQUE\n");
    إذا (سيٽ.nb_sd > 0) {
        صحيح before = dst.nb_sd;
        صحيح ret = av_چوکٺو_side_معلومات_clone(&dst.sd, &dst.nb_sd, سيٽ.sd[0],
                                           AV_چوکٺو_SIDE_معلومات_FLAG_UNIQUE);
        لکو("  clone UNIQUE: ret=%d before=%d after=%d\n",
               ret, before, dst.nb_sd);
    }

    print_lookup("\nFinal dst", &dst, probed, FF_ARRAY_ELEMS(probed));

    av_چوکٺو_side_معلومات_free(&dst.sd, &dst.nb_sd);
    av_چوکٺو_side_معلومات_free(&سيٽ.sd, &سيٽ.nb_sd);
    لکو("\nfree: set_nb=%d dst_nb=%d\n", سيٽ.nb_sd, dst.nb_sd);

    av_free(stereo3d);
    av_free(spherical);

    أرجع 0;
}
