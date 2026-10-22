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

صحيح مکيه(فراغ)
{
    AVDOVIDecoder_Configuration_رڪارڊ *cfg;
    AVDOVIMetadata *md;
    size_t سائيز;

    /* av_dovi_alloc */
    لکو("Testing av_dovi_alloc()\n");
    cfg = av_dovi_alloc(&سائيز);
    إذا (cfg) {
        لکو("alloc: OK, size>0=%s, dv_profile=%d\n",
               سائيز > 0 ? "yes" : "no", cfg->dv_profile);
        av_free(cfg);
    } وإلا {
        لکو("alloc: FAIL\n");
    }

    cfg = av_dovi_alloc(عدم);
    لکو("alloc (no size): %s\n", cfg ? "OK" : "FAIL");
    av_free(cfg);

    /* av_dovi_metadata_alloc */
    لکو("\nTesting av_dovi_metadata_alloc()\n");
    md = av_dovi_metadata_alloc(&سائيز);
    إذا (md) {
        AVDOVIRpu_معلومات_سرو *سرو;
        AVDOVIDataMapping *mapping;
        AVDOVIColorMetadata *color;

        لکو("alloc: OK, size>0=%s\n", سائيز > 0 ? "yes" : "no");
        لکو("num_ext_blocks=%d\n", md->انگ_ext_بلاڪون);

        /* pointer consistency checks for inline accessors */
        سرو = av_dovi_get_سرو(md);
        إذا ((uint8_t *)سرو != (uint8_t *)md + md->سرو_وٿي)
            لکو("header: pointer inconsistent with header_offset\n");
        لکو("header_offset>0=%s, rpu_type=%d\n",
               md->سرو_وٿي > 0 ? "yes" : "no",
               سرو->rpu_type);

        mapping = av_dovi_get_mapping(md);
        إذا ((uint8_t *)mapping != (uint8_t *)md + md->mapping_وٿي)
            لکو("mapping: pointer inconsistent with mapping_offset\n");
        لکو("mapping_offset>0=%s, nlq_method_idc=%d\n",
               md->mapping_وٿي > 0 ? "yes" : "no",
               mapping->nlq_طريقو_idc);

        color = av_dovi_get_color(md);
        إذا ((uint8_t *)color != (uint8_t *)md + md->color_وٿي)
            لکو("color: pointer inconsistent with color_offset\n");
        لکو("color_offset>0=%s, dm_metadata_id=%d\n",
               md->color_وٿي > 0 ? "yes" : "no",
               color->dm_metadata_id);

        لکو("ext_block_size>0=%s\n",
               md->ext_بلاڪ_سائيز > 0 ? "yes" : "no");

        av_free(md);
    } وإلا {
        لکو("alloc: FAIL\n");
    }

    md = av_dovi_metadata_alloc(عدم);
    لکو("alloc (no size): %s\n", md ? "OK" : "FAIL");
    av_free(md);

    /* av_dovi_find_level */
    لکو("\nTesting av_dovi_find_level()\n");
    md = av_dovi_metadata_alloc(عدم);
    إذا (md) {
        AVDOVIDm_معلومات *ext, *مليو;

        /* set up 3 ext blocks with different levels */
        md->انگ_ext_بلاڪون = 3;
        ext = av_dovi_get_ext(md, 0);
        إذا ((uint8_t *)ext != (uint8_t *)md + md->ext_بلاڪ_وٿي)
            لکو("ext[0]: pointer inconsistent with ext_block_offset\n");
        ext->level = 1;
        ext = av_dovi_get_ext(md, 1);
        ext->level = 5;
        ext = av_dovi_get_ext(md, 2);
        ext->level = 1;

        مليو = av_dovi_ڳوليو_level(md, 1);
        لکو("find level 1: %s\n", مليو && مليو->level == 1 ? "OK" : "FAIL");

        مليو = av_dovi_ڳوليو_level(md, 5);
        لکو("find level 5: %s\n", مليو && مليو->level == 5 ? "OK" : "FAIL");

        /* first match -- should return ext[0], not ext[2] */
        مليو = av_dovi_ڳوليو_level(md, 1);
        لکو("find level 1 first match: %s\n",
               مليو == av_dovi_get_ext(md, 0) ? "OK" : "FAIL");

        مليو = av_dovi_ڳوليو_level(md, 99);
        لکو("find level 99 (missing): %s\n", مليو == عدم ? "OK" : "FAIL");

        av_free(md);
    }

    /* OOM paths via av_max_alloc */
    لکو("\nTesting OOM paths\n");
    av_max_alloc(1);
    cfg = av_dovi_alloc(&سائيز);
    لکو("av_dovi_alloc OOM: %s\n", cfg ? "FAIL" : "OK");
    av_free(cfg);
    md = av_dovi_metadata_alloc(&سائيز);
    لکو("av_dovi_metadata_alloc OOM: %s\n", md ? "FAIL" : "OK");
    av_free(md);
    av_max_alloc(وڌ_کان_وڌ_عدد);

    أرجع 0;
}
