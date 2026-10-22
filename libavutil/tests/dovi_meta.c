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

صحيح اصلي(فراغ)
{
    AVDOVIDecoder_Configuration_ریکارډ *cfg;
    AVDOVIMetadata *md;
    size_t اندازه;

    /* av_dovi_alloc */
    چاپ_کړه("Testing av_dovi_alloc()\n");
    cfg = av_dovi_alloc(&اندازه);
    إذا (cfg) {
        چاپ_کړه("alloc: OK, size>0=%s, dv_profile=%d\n",
               اندازه > 0 ? "yes" : "no", cfg->dv_profile);
        av_free(cfg);
    } وإلا {
        چاپ_کړه("alloc: FAIL\n");
    }

    cfg = av_dovi_alloc(عدم);
    چاپ_کړه("alloc (no size): %s\n", cfg ? "OK" : "FAIL");
    av_free(cfg);

    /* av_dovi_metadata_alloc */
    چاپ_کړه("\nTesting av_dovi_metadata_alloc()\n");
    md = av_dovi_metadata_alloc(&اندازه);
    إذا (md) {
        AVDOVIRpu_معلومات_سرلیک *سرلیک;
        AVDOVIDataMapping *mapping;
        AVDOVIColorMetadata *color;

        چاپ_کړه("alloc: OK, size>0=%s\n", اندازه > 0 ? "yes" : "no");
        چاپ_کړه("num_ext_blocks=%d\n", md->عدد_ext_بلاکونه);

        /* pointer consistency checks for inline accessors */
        سرلیک = av_dovi_get_سرلیک(md);
        إذا ((uint8_t *)سرلیک != (uint8_t *)md + md->سرلیک_دننه_واټن)
            چاپ_کړه("header: pointer inconsistent with header_offset\n");
        چاپ_کړه("header_offset>0=%s, rpu_type=%d\n",
               md->سرلیک_دننه_واټن > 0 ? "yes" : "no",
               سرلیک->rpu_type);

        mapping = av_dovi_get_mapping(md);
        إذا ((uint8_t *)mapping != (uint8_t *)md + md->mapping_دننه_واټن)
            چاپ_کړه("mapping: pointer inconsistent with mapping_offset\n");
        چاپ_کړه("mapping_offset>0=%s, nlq_method_idc=%d\n",
               md->mapping_دننه_واټن > 0 ? "yes" : "no",
               mapping->nlq_لاره_idc);

        color = av_dovi_get_color(md);
        إذا ((uint8_t *)color != (uint8_t *)md + md->color_دننه_واټن)
            چاپ_کړه("color: pointer inconsistent with color_offset\n");
        چاپ_کړه("color_offset>0=%s, dm_metadata_id=%d\n",
               md->color_دننه_واټن > 0 ? "yes" : "no",
               color->dm_metadata_id);

        چاپ_کړه("ext_block_size>0=%s\n",
               md->ext_بلاک_اندازه > 0 ? "yes" : "no");

        av_free(md);
    } وإلا {
        چاپ_کړه("alloc: FAIL\n");
    }

    md = av_dovi_metadata_alloc(عدم);
    چاپ_کړه("alloc (no size): %s\n", md ? "OK" : "FAIL");
    av_free(md);

    /* av_dovi_find_level */
    چاپ_کړه("\nTesting av_dovi_find_level()\n");
    md = av_dovi_metadata_alloc(عدم);
    إذا (md) {
        AVDOVIDm_معلومات *ext, *وموندل;

        /* set up 3 ext blocks with different levels */
        md->عدد_ext_بلاکونه = 3;
        ext = av_dovi_get_ext(md, 0);
        إذا ((uint8_t *)ext != (uint8_t *)md + md->ext_بلاک_دننه_واټن)
            چاپ_کړه("ext[0]: pointer inconsistent with ext_block_offset\n");
        ext->level = 1;
        ext = av_dovi_get_ext(md, 1);
        ext->level = 5;
        ext = av_dovi_get_ext(md, 2);
        ext->level = 1;

        وموندل = av_dovi_پیدا_کړه_level(md, 1);
        چاپ_کړه("find level 1: %s\n", وموندل && وموندل->level == 1 ? "OK" : "FAIL");

        وموندل = av_dovi_پیدا_کړه_level(md, 5);
        چاپ_کړه("find level 5: %s\n", وموندل && وموندل->level == 5 ? "OK" : "FAIL");

        /* first match -- should return ext[0], not ext[2] */
        وموندل = av_dovi_پیدا_کړه_level(md, 1);
        چاپ_کړه("find level 1 first match: %s\n",
               وموندل == av_dovi_get_ext(md, 0) ? "OK" : "FAIL");

        وموندل = av_dovi_پیدا_کړه_level(md, 99);
        چاپ_کړه("find level 99 (missing): %s\n", وموندل == عدم ? "OK" : "FAIL");

        av_free(md);
    }

    /* OOM paths via av_max_alloc */
    چاپ_کړه("\nTesting OOM paths\n");
    av_max_alloc(1);
    cfg = av_dovi_alloc(&اندازه);
    چاپ_کړه("av_dovi_alloc OOM: %s\n", cfg ? "FAIL" : "OK");
    av_free(cfg);
    md = av_dovi_metadata_alloc(&اندازه);
    چاپ_کړه("av_dovi_metadata_alloc OOM: %s\n", md ? "FAIL" : "OK");
    av_free(md);
    av_max_alloc(لوی_عدد);

    أرجع 0;
}
