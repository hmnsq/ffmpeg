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

पूर्णाङ्क मुख्यम्(शून्य)
{
    AVDOVIDecoder_Configuration_लेखः *cfg;
    AVDOVIMetadata *md;
    size_t आकार;

    /* av_dovi_alloc */
    प्रारूप_लिख("Testing av_dovi_alloc()\n");
    cfg = av_dovi_alloc(&आकार);
    यदि (cfg) {
        प्रारूप_लिख("alloc: OK, size>0=%s, dv_profile=%d\n",
               आकार > 0 ? "yes" : "no", cfg->dv_profile);
        av_free(cfg);
    } अन्यथा {
        प्रारूप_लिख("alloc: FAIL\n");
    }

    cfg = av_dovi_alloc(रिक्त);
    प्रारूप_लिख("alloc (no size): %s\n", cfg ? "OK" : "FAIL");
    av_free(cfg);

    /* av_dovi_metadata_alloc */
    प्रारूप_लिख("\nTesting av_dovi_metadata_alloc()\n");
    md = av_dovi_metadata_alloc(&आकार);
    यदि (md) {
        AVDOVIRpu_दत्त_शीर्षकम् *शीर्षकम्;
        AVDOVIDataMapping *mapping;
        AVDOVIColorMetadata *color;

        प्रारूप_लिख("alloc: OK, size>0=%s\n", आकार > 0 ? "yes" : "no");
        प्रारूप_लिख("num_ext_blocks=%d\n", md->अङ्कः_ext_खण्डानि);

        /* pointer consistency checks for inline accessors */
        शीर्षकम् = av_dovi_get_शीर्षकम्(md);
        यदि ((uint8_t *)शीर्षकम् != (uint8_t *)md + md->शीर्षकम्_विस्थापनम्)
            प्रारूप_लिख("header: pointer inconsistent with header_offset\n");
        प्रारूप_लिख("header_offset>0=%s, rpu_type=%d\n",
               md->शीर्षकम्_विस्थापनम् > 0 ? "yes" : "no",
               शीर्षकम्->rpu_type);

        mapping = av_dovi_get_mapping(md);
        यदि ((uint8_t *)mapping != (uint8_t *)md + md->mapping_विस्थापनम्)
            प्रारूप_लिख("mapping: pointer inconsistent with mapping_offset\n");
        प्रारूप_लिख("mapping_offset>0=%s, nlq_method_idc=%d\n",
               md->mapping_विस्थापनम् > 0 ? "yes" : "no",
               mapping->nlq_विधानम्_idc);

        color = av_dovi_get_color(md);
        यदि ((uint8_t *)color != (uint8_t *)md + md->color_विस्थापनम्)
            प्रारूप_लिख("color: pointer inconsistent with color_offset\n");
        प्रारूप_लिख("color_offset>0=%s, dm_metadata_id=%d\n",
               md->color_विस्थापनम् > 0 ? "yes" : "no",
               color->dm_metadata_id);

        प्रारूप_लिख("ext_block_size>0=%s\n",
               md->ext_खण्डम्_आकार > 0 ? "yes" : "no");

        av_free(md);
    } अन्यथा {
        प्रारूप_लिख("alloc: FAIL\n");
    }

    md = av_dovi_metadata_alloc(रिक्त);
    प्रारूप_लिख("alloc (no size): %s\n", md ? "OK" : "FAIL");
    av_free(md);

    /* av_dovi_find_level */
    प्रारूप_लिख("\nTesting av_dovi_find_level()\n");
    md = av_dovi_metadata_alloc(रिक्त);
    यदि (md) {
        AVDOVIDm_दत्त *ext, *प्राप्तम्;

        /* set up 3 ext blocks with different levels */
        md->अङ्कः_ext_खण्डानि = 3;
        ext = av_dovi_get_ext(md, 0);
        यदि ((uint8_t *)ext != (uint8_t *)md + md->ext_खण्डम्_विस्थापनम्)
            प्रारूप_लिख("ext[0]: pointer inconsistent with ext_block_offset\n");
        ext->level = 1;
        ext = av_dovi_get_ext(md, 1);
        ext->level = 5;
        ext = av_dovi_get_ext(md, 2);
        ext->level = 1;

        प्राप्तम् = av_dovi_find_level(md, 1);
        प्रारूप_लिख("find level 1: %s\n", प्राप्तम् && प्राप्तम्->level == 1 ? "OK" : "FAIL");

        प्राप्तम् = av_dovi_find_level(md, 5);
        प्रारूप_लिख("find level 5: %s\n", प्राप्तम् && प्राप्तम्->level == 5 ? "OK" : "FAIL");

        /* first match -- should return ext[0], not ext[2] */
        प्राप्तम् = av_dovi_find_level(md, 1);
        प्रारूप_लिख("find level 1 first match: %s\n",
               प्राप्तम् == av_dovi_get_ext(md, 0) ? "OK" : "FAIL");

        प्राप्तम् = av_dovi_find_level(md, 99);
        प्रारूप_लिख("find level 99 (missing): %s\n", प्राप्तम् == रिक्त ? "OK" : "FAIL");

        av_free(md);
    }

    /* OOM paths via av_max_alloc */
    प्रारूप_लिख("\nTesting OOM paths\n");
    av_max_alloc(1);
    cfg = av_dovi_alloc(&आकार);
    प्रारूप_लिख("av_dovi_alloc OOM: %s\n", cfg ? "FAIL" : "OK");
    av_free(cfg);
    md = av_dovi_metadata_alloc(&आकार);
    प्रारूप_लिख("av_dovi_metadata_alloc OOM: %s\n", md ? "FAIL" : "OK");
    av_free(md);
    av_max_alloc(अधिकतम_पूर्णाङ्कः);

    प्रत्यागम 0;
}
