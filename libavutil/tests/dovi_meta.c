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

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/dovi_meta.h"
#అన్తర్భావ "libavutil/mem.h"

పూర్ణాంకం ప్రధాన(శూన్య)
{
    AVDOVIDecoder_Configuration_రికార్డు *cfg;
    AVDOVIMetadata *md;
    size_t కొలత;

    /* av_dovi_alloc */
    రాయి("Testing av_dovi_alloc()\n");
    cfg = av_dovi_alloc(&కొలత);
    ఒకవేళ (cfg) {
        రాయి("alloc: OK, size>0=%s, dv_profile=%d\n",
               కొలత > 0 ? "yes" : "no", cfg->dv_profile);
        av_free(cfg);
    } లేకపోతే {
        రాయి("alloc: FAIL\n");
    }

    cfg = av_dovi_alloc(ఖాళీ);
    రాయి("alloc (no size): %s\n", cfg ? "OK" : "FAIL");
    av_free(cfg);

    /* av_dovi_metadata_alloc */
    రాయి("\nTesting av_dovi_metadata_alloc()\n");
    md = av_dovi_metadata_alloc(&కొలత);
    ఒకవేళ (md) {
        AVDOVIRpu_దత్తాంశం_శీర్షిక *శీర్షిక;
        AVDOVIDataMapping *mapping;
        AVDOVIColorMetadata *color;

        రాయి("alloc: OK, size>0=%s\n", కొలత > 0 ? "yes" : "no");
        రాయి("num_ext_blocks=%d\n", md->అంకె_ext_ఖండాలు);

        /* pointer consistency checks for inline accessors */
        శీర్షిక = av_dovi_get_శీర్షిక(md);
        ఒకవేళ ((uint8_t *)శీర్షిక != (uint8_t *)md + md->శీర్షిక_స్థానభ్రంశం)
            రాయి("header: pointer inconsistent with header_offset\n");
        రాయి("header_offset>0=%s, rpu_type=%d\n",
               md->శీర్షిక_స్థానభ్రంశం > 0 ? "yes" : "no",
               శీర్షిక->rpu_type);

        mapping = av_dovi_get_mapping(md);
        ఒకవేళ ((uint8_t *)mapping != (uint8_t *)md + md->mapping_స్థానభ్రంశం)
            రాయి("mapping: pointer inconsistent with mapping_offset\n");
        రాయి("mapping_offset>0=%s, nlq_method_idc=%d\n",
               md->mapping_స్థానభ్రంశం > 0 ? "yes" : "no",
               mapping->nlq_పద్ధతి_idc);

        color = av_dovi_get_color(md);
        ఒకవేళ ((uint8_t *)color != (uint8_t *)md + md->color_స్థానభ్రంశం)
            రాయి("color: pointer inconsistent with color_offset\n");
        రాయి("color_offset>0=%s, dm_metadata_id=%d\n",
               md->color_స్థానభ్రంశం > 0 ? "yes" : "no",
               color->dm_metadata_id);

        రాయి("ext_block_size>0=%s\n",
               md->ext_ఖండం_కొలత > 0 ? "yes" : "no");

        av_free(md);
    } లేకపోతే {
        రాయి("alloc: FAIL\n");
    }

    md = av_dovi_metadata_alloc(ఖాళీ);
    రాయి("alloc (no size): %s\n", md ? "OK" : "FAIL");
    av_free(md);

    /* av_dovi_find_level */
    రాయి("\nTesting av_dovi_find_level()\n");
    md = av_dovi_metadata_alloc(ఖాళీ);
    ఒకవేళ (md) {
        AVDOVIDm_దత్తాంశం *ext, *దొరికింది;

        /* set up 3 ext blocks with different levels */
        md->అంకె_ext_ఖండాలు = 3;
        ext = av_dovi_get_ext(md, 0);
        ఒకవేళ ((uint8_t *)ext != (uint8_t *)md + md->ext_ఖండం_స్థానభ్రంశం)
            రాయి("ext[0]: pointer inconsistent with ext_block_offset\n");
        ext->level = 1;
        ext = av_dovi_get_ext(md, 1);
        ext->level = 5;
        ext = av_dovi_get_ext(md, 2);
        ext->level = 1;

        దొరికింది = av_dovi_కనుగొను_level(md, 1);
        రాయి("find level 1: %s\n", దొరికింది && దొరికింది->level == 1 ? "OK" : "FAIL");

        దొరికింది = av_dovi_కనుగొను_level(md, 5);
        రాయి("find level 5: %s\n", దొరికింది && దొరికింది->level == 5 ? "OK" : "FAIL");

        /* first match -- should return ext[0], not ext[2] */
        దొరికింది = av_dovi_కనుగొను_level(md, 1);
        రాయి("find level 1 first match: %s\n",
               దొరికింది == av_dovi_get_ext(md, 0) ? "OK" : "FAIL");

        దొరికింది = av_dovi_కనుగొను_level(md, 99);
        రాయి("find level 99 (missing): %s\n", దొరికింది == ఖాళీ ? "OK" : "FAIL");

        av_free(md);
    }

    /* OOM paths via av_max_alloc */
    రాయి("\nTesting OOM paths\n");
    av_max_alloc(1);
    cfg = av_dovi_alloc(&కొలత);
    రాయి("av_dovi_alloc OOM: %s\n", cfg ? "FAIL" : "OK");
    av_free(cfg);
    md = av_dovi_metadata_alloc(&కొలత);
    రాయి("av_dovi_metadata_alloc OOM: %s\n", md ? "FAIL" : "OK");
    av_free(md);
    av_max_alloc(గరిష్ఠ_పూర్ణాంకం);

    తిరిగి 0;
}
