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

#अन्तर्भाव <limits.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdio.h>

#अन्तर्भाव "libavutil/dovi_meta.h"
#अन्तर्भाव "libavutil/mem.h"

पूर्णाङ्क main(शून्य)
{
    AVDOVIDecoderConfigurationRecord *cfg;
    AVDOVIMetadata *md;
    माप_प्रकार size;

    /* av_dovi_alloc */
    म_लिखो("Testing av_dovi_alloc()\n");
    cfg = av_dovi_alloc(&size);
    यदि (cfg) {
        म_लिखो("alloc: OK, size>0=%s, dv_profile=%d\n",
               size > 0 ? "yes" : "no", cfg->dv_profile);
        av_free(cfg);
    } अन्यथा {
        म_लिखो("alloc: FAIL\n");
    }

    cfg = av_dovi_alloc(रिक्त);
    म_लिखो("alloc (no size): %s\n", cfg ? "OK" : "FAIL");
    av_free(cfg);

    /* av_dovi_metadata_alloc */
    म_लिखो("\nTesting av_dovi_metadata_alloc()\n");
    md = av_dovi_metadata_alloc(&size);
    यदि (md) {
        AVDOVIRpuDataHeader *header;
        AVDOVIDataMapping *mapping;
        AVDOVIColorMetadata *color;

        म_लिखो("alloc: OK, size>0=%s\n", size > 0 ? "yes" : "no");
        म_लिखो("num_ext_blocks=%d\n", md->अङ्क_ext_blocks);

        /* pointer consistency checks for inline accessors */
        header = av_dovi_get_header(md);
        यदि ((uint8_t *)header != (uint8_t *)md + md->header_offset)
            म_लिखो("header: pointer inconsistent with header_offset\n");
        म_लिखो("header_offset>0=%s, rpu_type=%d\n",
               md->header_offset > 0 ? "yes" : "no",
               header->rpu_type);

        mapping = av_dovi_get_mapping(md);
        यदि ((uint8_t *)mapping != (uint8_t *)md + md->mapping_offset)
            म_लिखो("mapping: pointer inconsistent with mapping_offset\n");
        म_लिखो("mapping_offset>0=%s, nlq_method_idc=%d\n",
               md->mapping_offset > 0 ? "yes" : "no",
               mapping->nlq_method_idc);

        color = av_dovi_get_color(md);
        यदि ((uint8_t *)color != (uint8_t *)md + md->color_offset)
            म_लिखो("color: pointer inconsistent with color_offset\n");
        म_लिखो("color_offset>0=%s, dm_metadata_id=%d\n",
               md->color_offset > 0 ? "yes" : "no",
               color->dm_metadata_id);

        म_लिखो("ext_block_size>0=%s\n",
               md->ext_block_size > 0 ? "yes" : "no");

        av_free(md);
    } अन्यथा {
        म_लिखो("alloc: FAIL\n");
    }

    md = av_dovi_metadata_alloc(रिक्त);
    म_लिखो("alloc (no size): %s\n", md ? "OK" : "FAIL");
    av_free(md);

    /* av_dovi_find_level */
    म_लिखो("\nTesting av_dovi_find_level()\n");
    md = av_dovi_metadata_alloc(रिक्त);
    यदि (md) {
        AVDOVIDmData *ext, *found;

        /* set up 3 ext blocks with different levels */
        md->अङ्क_ext_blocks = 3;
        ext = av_dovi_get_ext(md, 0);
        यदि ((uint8_t *)ext != (uint8_t *)md + md->ext_block_offset)
            म_लिखो("ext[0]: pointer inconsistent with ext_block_offset\n");
        ext->level = 1;
        ext = av_dovi_get_ext(md, 1);
        ext->level = 5;
        ext = av_dovi_get_ext(md, 2);
        ext->level = 1;

        found = av_dovi_find_level(md, 1);
        म_लिखो("find level 1: %s\n", found && found->level == 1 ? "OK" : "FAIL");

        found = av_dovi_find_level(md, 5);
        म_लिखो("find level 5: %s\n", found && found->level == 5 ? "OK" : "FAIL");

        /* first match -- should return ext[0], not ext[2] */
        found = av_dovi_find_level(md, 1);
        म_लिखो("find level 1 first match: %s\n",
               found == av_dovi_get_ext(md, 0) ? "OK" : "FAIL");

        found = av_dovi_find_level(md, 99);
        म_लिखो("find level 99 (missing): %s\n", found == रिक्त ? "OK" : "FAIL");

        av_free(md);
    }

    /* OOM paths via av_max_alloc */
    म_लिखो("\nTesting OOM paths\n");
    av_max_alloc(1);
    cfg = av_dovi_alloc(&size);
    म_लिखो("av_dovi_alloc OOM: %s\n", cfg ? "FAIL" : "OK");
    av_free(cfg);
    md = av_dovi_metadata_alloc(&size);
    म_लिखो("av_dovi_metadata_alloc OOM: %s\n", md ? "FAIL" : "OK");
    av_free(md);
    av_max_alloc(पूर्णांक_उच्च);

    फर्काऊ 0;
}
