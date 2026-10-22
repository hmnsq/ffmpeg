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

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/dovi_meta.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    AVDOVIDecoder_Configuration_ਰਿਕਾਰਡ *cfg;
    AVDOVIMetadata *md;
    size_t ਮਾਪ;

    /* av_dovi_alloc */
    ਲਿਖੋ("Testing av_dovi_alloc()\n");
    cfg = av_dovi_alloc(&ਮਾਪ);
    ਜੇ (cfg) {
        ਲਿਖੋ("alloc: OK, size>0=%s, dv_profile=%d\n",
               ਮਾਪ > 0 ? "yes" : "no", cfg->dv_profile);
        av_free(cfg);
    } ਨਹੀਂਤਾਂ {
        ਲਿਖੋ("alloc: FAIL\n");
    }

    cfg = av_dovi_alloc(ਨਿਰਾ);
    ਲਿਖੋ("alloc (no size): %s\n", cfg ? "OK" : "FAIL");
    av_free(cfg);

    /* av_dovi_metadata_alloc */
    ਲਿਖੋ("\nTesting av_dovi_metadata_alloc()\n");
    md = av_dovi_metadata_alloc(&ਮਾਪ);
    ਜੇ (md) {
        AVDOVIRpu_ਅੰਕੜੇ_ਸਿਰਲੇਖ *ਸਿਰਲੇਖ;
        AVDOVIDataMapping *mapping;
        AVDOVIColorMetadata *color;

        ਲਿਖੋ("alloc: OK, size>0=%s\n", ਮਾਪ > 0 ? "yes" : "no");
        ਲਿਖੋ("num_ext_blocks=%d\n", md->ਅੰਕ_ext_ਖੰਡਾਂ);

        /* pointer consistency checks for inline accessors */
        ਸਿਰਲੇਖ = av_dovi_get_ਸਿਰਲੇਖ(md);
        ਜੇ ((uint8_t *)ਸਿਰਲੇਖ != (uint8_t *)md + md->ਸਿਰਲੇਖ_ਵਿੱਥ)
            ਲਿਖੋ("header: pointer inconsistent with header_offset\n");
        ਲਿਖੋ("header_offset>0=%s, rpu_type=%d\n",
               md->ਸਿਰਲੇਖ_ਵਿੱਥ > 0 ? "yes" : "no",
               ਸਿਰਲੇਖ->rpu_type);

        mapping = av_dovi_get_mapping(md);
        ਜੇ ((uint8_t *)mapping != (uint8_t *)md + md->mapping_ਵਿੱਥ)
            ਲਿਖੋ("mapping: pointer inconsistent with mapping_offset\n");
        ਲਿਖੋ("mapping_offset>0=%s, nlq_method_idc=%d\n",
               md->mapping_ਵਿੱਥ > 0 ? "yes" : "no",
               mapping->nlq_ਵਿਧੀ_idc);

        color = av_dovi_get_color(md);
        ਜੇ ((uint8_t *)color != (uint8_t *)md + md->color_ਵਿੱਥ)
            ਲਿਖੋ("color: pointer inconsistent with color_offset\n");
        ਲਿਖੋ("color_offset>0=%s, dm_metadata_id=%d\n",
               md->color_ਵਿੱਥ > 0 ? "yes" : "no",
               color->dm_metadata_id);

        ਲਿਖੋ("ext_block_size>0=%s\n",
               md->ext_ਖੰਡ_ਮਾਪ > 0 ? "yes" : "no");

        av_free(md);
    } ਨਹੀਂਤਾਂ {
        ਲਿਖੋ("alloc: FAIL\n");
    }

    md = av_dovi_metadata_alloc(ਨਿਰਾ);
    ਲਿਖੋ("alloc (no size): %s\n", md ? "OK" : "FAIL");
    av_free(md);

    /* av_dovi_find_level */
    ਲਿਖੋ("\nTesting av_dovi_find_level()\n");
    md = av_dovi_metadata_alloc(ਨਿਰਾ);
    ਜੇ (md) {
        AVDOVIDm_ਅੰਕੜੇ *ext, *ਮਿਲਿਆ;

        /* set up 3 ext blocks with different levels */
        md->ਅੰਕ_ext_ਖੰਡਾਂ = 3;
        ext = av_dovi_get_ext(md, 0);
        ਜੇ ((uint8_t *)ext != (uint8_t *)md + md->ext_ਖੰਡ_ਵਿੱਥ)
            ਲਿਖੋ("ext[0]: pointer inconsistent with ext_block_offset\n");
        ext->level = 1;
        ext = av_dovi_get_ext(md, 1);
        ext->level = 5;
        ext = av_dovi_get_ext(md, 2);
        ext->level = 1;

        ਮਿਲਿਆ = av_dovi_ਲੱਭੋ_level(md, 1);
        ਲਿਖੋ("find level 1: %s\n", ਮਿਲਿਆ && ਮਿਲਿਆ->level == 1 ? "OK" : "FAIL");

        ਮਿਲਿਆ = av_dovi_ਲੱਭੋ_level(md, 5);
        ਲਿਖੋ("find level 5: %s\n", ਮਿਲਿਆ && ਮਿਲਿਆ->level == 5 ? "OK" : "FAIL");

        /* first match -- should return ext[0], not ext[2] */
        ਮਿਲਿਆ = av_dovi_ਲੱਭੋ_level(md, 1);
        ਲਿਖੋ("find level 1 first match: %s\n",
               ਮਿਲਿਆ == av_dovi_get_ext(md, 0) ? "OK" : "FAIL");

        ਮਿਲਿਆ = av_dovi_ਲੱਭੋ_level(md, 99);
        ਲਿਖੋ("find level 99 (missing): %s\n", ਮਿਲਿਆ == ਨਿਰਾ ? "OK" : "FAIL");

        av_free(md);
    }

    /* OOM paths via av_max_alloc */
    ਲਿਖੋ("\nTesting OOM paths\n");
    av_max_alloc(1);
    cfg = av_dovi_alloc(&ਮਾਪ);
    ਲਿਖੋ("av_dovi_alloc OOM: %s\n", cfg ? "FAIL" : "OK");
    av_free(cfg);
    md = av_dovi_metadata_alloc(&ਮਾਪ);
    ਲਿਖੋ("av_dovi_metadata_alloc OOM: %s\n", md ? "FAIL" : "OK");
    av_free(md);
    av_max_alloc(ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);

    ਵਾਪਸ 0;
}
