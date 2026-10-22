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

#شامل <limits.h>
#شامل <stdint.h>
#شامل <stdio.h>

#شامل "libavutil/dovi_meta.h"
#شامل "libavutil/mem.h"

صحیح مین(خالی)
{
    AVDOVIDecoder_Configuration_ریکارڈ *cfg;
    AVDOVIMetadata *md;
    size_t سائز;

    /* av_dovi_alloc */
    لکھو("Testing av_dovi_alloc()\n");
    cfg = av_dovi_alloc(&سائز);
    اگر (cfg) {
        لکھو("alloc: OK, size>0=%s, dv_profile=%d\n",
               سائز > 0 ? "yes" : "no", cfg->dv_profile);
        av_free(cfg);
    } ورنہ {
        لکھو("alloc: FAIL\n");
    }

    cfg = av_dovi_alloc(تہی);
    لکھو("alloc (no size): %s\n", cfg ? "OK" : "FAIL");
    av_free(cfg);

    /* av_dovi_metadata_alloc */
    لکھو("\nTesting av_dovi_metadata_alloc()\n");
    md = av_dovi_metadata_alloc(&سائز);
    اگر (md) {
        AVDOVIRpu_ڈیٹا_سرخی *سرخی;
        AVDOVIDataMapping *mapping;
        AVDOVIColorMetadata *color;

        لکھو("alloc: OK, size>0=%s\n", سائز > 0 ? "yes" : "no");
        لکھو("num_ext_blocks=%d\n", md->عدد_ext_بلاکیں);

        /* pointer consistency checks for inline accessors */
        سرخی = av_dovi_get_سرخی(md);
        اگر ((uint8_t *)سرخی != (uint8_t *)md + md->سرخی_انحراف)
            لکھو("header: pointer inconsistent with header_offset\n");
        لکھو("header_offset>0=%s, rpu_type=%d\n",
               md->سرخی_انحراف > 0 ? "yes" : "no",
               سرخی->rpu_type);

        mapping = av_dovi_get_mapping(md);
        اگر ((uint8_t *)mapping != (uint8_t *)md + md->mapping_انحراف)
            لکھو("mapping: pointer inconsistent with mapping_offset\n");
        لکھو("mapping_offset>0=%s, nlq_method_idc=%d\n",
               md->mapping_انحراف > 0 ? "yes" : "no",
               mapping->nlq_طریقہ_idc);

        color = av_dovi_get_color(md);
        اگر ((uint8_t *)color != (uint8_t *)md + md->color_انحراف)
            لکھو("color: pointer inconsistent with color_offset\n");
        لکھو("color_offset>0=%s, dm_metadata_id=%d\n",
               md->color_انحراف > 0 ? "yes" : "no",
               color->dm_metadata_id);

        لکھو("ext_block_size>0=%s\n",
               md->ext_بلاک_سائز > 0 ? "yes" : "no");

        av_free(md);
    } ورنہ {
        لکھو("alloc: FAIL\n");
    }

    md = av_dovi_metadata_alloc(تہی);
    لکھو("alloc (no size): %s\n", md ? "OK" : "FAIL");
    av_free(md);

    /* av_dovi_find_level */
    لکھو("\nTesting av_dovi_find_level()\n");
    md = av_dovi_metadata_alloc(تہی);
    اگر (md) {
        AVDOVIDm_ڈیٹا *ext, *ملا;

        /* set up 3 ext blocks with different levels */
        md->عدد_ext_بلاکیں = 3;
        ext = av_dovi_get_ext(md, 0);
        اگر ((uint8_t *)ext != (uint8_t *)md + md->ext_بلاک_انحراف)
            لکھو("ext[0]: pointer inconsistent with ext_block_offset\n");
        ext->level = 1;
        ext = av_dovi_get_ext(md, 1);
        ext->level = 5;
        ext = av_dovi_get_ext(md, 2);
        ext->level = 1;

        ملا = av_dovi_ڈھونڈو_level(md, 1);
        لکھو("find level 1: %s\n", ملا && ملا->level == 1 ? "OK" : "FAIL");

        ملا = av_dovi_ڈھونڈو_level(md, 5);
        لکھو("find level 5: %s\n", ملا && ملا->level == 5 ? "OK" : "FAIL");

        /* first match -- should return ext[0], not ext[2] */
        ملا = av_dovi_ڈھونڈو_level(md, 1);
        لکھو("find level 1 first match: %s\n",
               ملا == av_dovi_get_ext(md, 0) ? "OK" : "FAIL");

        ملا = av_dovi_ڈھونڈو_level(md, 99);
        لکھو("find level 99 (missing): %s\n", ملا == تہی ? "OK" : "FAIL");

        av_free(md);
    }

    /* OOM paths via av_max_alloc */
    لکھو("\nTesting OOM paths\n");
    av_max_alloc(1);
    cfg = av_dovi_alloc(&سائز);
    لکھو("av_dovi_alloc OOM: %s\n", cfg ? "FAIL" : "OK");
    av_free(cfg);
    md = av_dovi_metadata_alloc(&سائز);
    لکھو("av_dovi_metadata_alloc OOM: %s\n", md ? "FAIL" : "OK");
    av_free(md);
    av_max_alloc(زیادہ_سے_زیادہ_عدد);

    واپس 0;
}
