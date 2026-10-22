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

#ضمن <limits.h>
#ضمن <stdint.h>
#ضمن <stdio.h>

#ضمن "libavutil/dovi_meta.h"
#ضمن "libavutil/mem.h"

صحيح مکھ(فراغ)
{
    AVDOVIDecoder_Configuration_ریکارڈ *cfg;
    AVDOVIMetadata *md;
    size_t ناپ;

    /* av_dovi_alloc */
    لکھو("Testing av_dovi_alloc()\n");
    cfg = av_dovi_alloc(&ناپ);
    إذا (cfg) {
        لکھو("alloc: OK, size>0=%s, dv_profile=%d\n",
               ناپ > 0 ? "yes" : "no", cfg->dv_profile);
        av_free(cfg);
    } وإلا {
        لکھو("alloc: FAIL\n");
    }

    cfg = av_dovi_alloc(عدم);
    لکھو("alloc (no size): %s\n", cfg ? "OK" : "FAIL");
    av_free(cfg);

    /* av_dovi_metadata_alloc */
    لکھو("\nTesting av_dovi_metadata_alloc()\n");
    md = av_dovi_metadata_alloc(&ناپ);
    إذا (md) {
        AVDOVIRpu_انکڑے_سرخی *سرخی;
        AVDOVIDataMapping *mapping;
        AVDOVIColorMetadata *color;

        لکھو("alloc: OK, size>0=%s\n", ناپ > 0 ? "yes" : "no");
        لکھو("num_ext_blocks=%d\n", md->عدد_ext_بلاکاں);

        /* pointer consistency checks for inline accessors */
        سرخی = av_dovi_get_سرخی(md);
        إذا ((uint8_t *)سرخی != (uint8_t *)md + md->سرخی_وتھ)
            لکھو("header: pointer inconsistent with header_offset\n");
        لکھو("header_offset>0=%s, rpu_type=%d\n",
               md->سرخی_وتھ > 0 ? "yes" : "no",
               سرخی->rpu_type);

        mapping = av_dovi_get_mapping(md);
        إذا ((uint8_t *)mapping != (uint8_t *)md + md->mapping_وتھ)
            لکھو("mapping: pointer inconsistent with mapping_offset\n");
        لکھو("mapping_offset>0=%s, nlq_method_idc=%d\n",
               md->mapping_وتھ > 0 ? "yes" : "no",
               mapping->nlq_طریقہ_idc);

        color = av_dovi_get_color(md);
        إذا ((uint8_t *)color != (uint8_t *)md + md->color_وتھ)
            لکھو("color: pointer inconsistent with color_offset\n");
        لکھو("color_offset>0=%s, dm_metadata_id=%d\n",
               md->color_وتھ > 0 ? "yes" : "no",
               color->dm_metadata_id);

        لکھو("ext_block_size>0=%s\n",
               md->ext_بلاک_ناپ > 0 ? "yes" : "no");

        av_free(md);
    } وإلا {
        لکھو("alloc: FAIL\n");
    }

    md = av_dovi_metadata_alloc(عدم);
    لکھو("alloc (no size): %s\n", md ? "OK" : "FAIL");
    av_free(md);

    /* av_dovi_find_level */
    لکھو("\nTesting av_dovi_find_level()\n");
    md = av_dovi_metadata_alloc(عدم);
    إذا (md) {
        AVDOVIDm_انکڑے *ext, *لبھیا;

        /* set up 3 ext blocks with different levels */
        md->عدد_ext_بلاکاں = 3;
        ext = av_dovi_get_ext(md, 0);
        إذا ((uint8_t *)ext != (uint8_t *)md + md->ext_بلاک_وتھ)
            لکھو("ext[0]: pointer inconsistent with ext_block_offset\n");
        ext->level = 1;
        ext = av_dovi_get_ext(md, 1);
        ext->level = 5;
        ext = av_dovi_get_ext(md, 2);
        ext->level = 1;

        لبھیا = av_dovi_لبھو_level(md, 1);
        لکھو("find level 1: %s\n", لبھیا && لبھیا->level == 1 ? "OK" : "FAIL");

        لبھیا = av_dovi_لبھو_level(md, 5);
        لکھو("find level 5: %s\n", لبھیا && لبھیا->level == 5 ? "OK" : "FAIL");

        /* first match -- should return ext[0], not ext[2] */
        لبھیا = av_dovi_لبھو_level(md, 1);
        لکھو("find level 1 first match: %s\n",
               لبھیا == av_dovi_get_ext(md, 0) ? "OK" : "FAIL");

        لبھیا = av_dovi_لبھو_level(md, 99);
        لکھو("find level 99 (missing): %s\n", لبھیا == عدم ? "OK" : "FAIL");

        av_free(md);
    }

    /* OOM paths via av_max_alloc */
    لکھو("\nTesting OOM paths\n");
    av_max_alloc(1);
    cfg = av_dovi_alloc(&ناپ);
    لکھو("av_dovi_alloc OOM: %s\n", cfg ? "FAIL" : "OK");
    av_free(cfg);
    md = av_dovi_metadata_alloc(&ناپ);
    لکھو("av_dovi_metadata_alloc OOM: %s\n", md ? "FAIL" : "OK");
    av_free(md);
    av_max_alloc(ودھ_توں_ودھ_عدد);

    أرجع 0;
}
