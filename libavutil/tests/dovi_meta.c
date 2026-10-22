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

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "libavutil/dovi_meta.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    AVDOVIDecoder_Configuration_ದಾಖಲೆ *cfg;
    AVDOVIMetadata *md;
    size_t ಗಾತ್ರ_2;

    /* av_dovi_alloc */
    ಬರೆ("Testing av_dovi_alloc()\n");
    cfg = av_dovi_alloc(&ಗಾತ್ರ_2);
    ಆದರೆ (cfg) {
        ಬರೆ("alloc: OK, size>0=%s, dv_profile=%d\n",
               ಗಾತ್ರ_2 > 0 ? "yes" : "no", cfg->dv_profile);
        av_free(cfg);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಬರೆ("alloc: FAIL\n");
    }

    cfg = av_dovi_alloc(ಖಾಲಿ);
    ಬರೆ("alloc (no size): %s\n", cfg ? "OK" : "FAIL");
    av_free(cfg);

    /* av_dovi_metadata_alloc */
    ಬರೆ("\nTesting av_dovi_metadata_alloc()\n");
    md = av_dovi_metadata_alloc(&ಗಾತ್ರ_2);
    ಆದರೆ (md) {
        AVDOVIRpu_ದತ್ತಾಂಶ_ಶೀರ್ಷಿಕೆ *ಶೀರ್ಷಿಕೆ;
        AVDOVIDataMapping *mapping;
        AVDOVIColorMetadata *color;

        ಬರೆ("alloc: OK, size>0=%s\n", ಗಾತ್ರ_2 > 0 ? "yes" : "no");
        ಬರೆ("num_ext_blocks=%d\n", md->ಅಂಕೆ_ext_ಖಂಡಗಳು);

        /* pointer consistency checks for inline accessors */
        ಶೀರ್ಷಿಕೆ = av_dovi_get_ಶೀರ್ಷಿಕೆ(md);
        ಆದರೆ ((uint8_t *)ಶೀರ್ಷಿಕೆ != (uint8_t *)md + md->ಶೀರ್ಷಿಕೆ_ಸ್ಥಾನಾಂತರ)
            ಬರೆ("header: pointer inconsistent with header_offset\n");
        ಬರೆ("header_offset>0=%s, rpu_type=%d\n",
               md->ಶೀರ್ಷಿಕೆ_ಸ್ಥಾನಾಂತರ > 0 ? "yes" : "no",
               ಶೀರ್ಷಿಕೆ->rpu_type);

        mapping = av_dovi_get_mapping(md);
        ಆದರೆ ((uint8_t *)mapping != (uint8_t *)md + md->mapping_ಸ್ಥಾನಾಂತರ)
            ಬರೆ("mapping: pointer inconsistent with mapping_offset\n");
        ಬರೆ("mapping_offset>0=%s, nlq_method_idc=%d\n",
               md->mapping_ಸ್ಥಾನಾಂತರ > 0 ? "yes" : "no",
               mapping->nlq_ವಿಧಾನ_idc);

        color = av_dovi_get_color(md);
        ಆದರೆ ((uint8_t *)color != (uint8_t *)md + md->color_ಸ್ಥಾನಾಂತರ)
            ಬರೆ("color: pointer inconsistent with color_offset\n");
        ಬರೆ("color_offset>0=%s, dm_metadata_id=%d\n",
               md->color_ಸ್ಥಾನಾಂತರ > 0 ? "yes" : "no",
               color->dm_metadata_id);

        ಬರೆ("ext_block_size>0=%s\n",
               md->ext_ಖಂಡ_ಗಾತ್ರ > 0 ? "yes" : "no");

        av_free(md);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಬರೆ("alloc: FAIL\n");
    }

    md = av_dovi_metadata_alloc(ಖಾಲಿ);
    ಬರೆ("alloc (no size): %s\n", md ? "OK" : "FAIL");
    av_free(md);

    /* av_dovi_find_level */
    ಬರೆ("\nTesting av_dovi_find_level()\n");
    md = av_dovi_metadata_alloc(ಖಾಲಿ);
    ಆದರೆ (md) {
        AVDOVIDm_ದತ್ತಾಂಶ *ext, *ಸಿಕ್ಕಿತು;

        /* set up 3 ext blocks with different levels */
        md->ಅಂಕೆ_ext_ಖಂಡಗಳು = 3;
        ext = av_dovi_get_ext(md, 0);
        ಆದರೆ ((uint8_t *)ext != (uint8_t *)md + md->ext_ಖಂಡ_ಸ್ಥಾನಾಂತರ)
            ಬರೆ("ext[0]: pointer inconsistent with ext_block_offset\n");
        ext->level = 1;
        ext = av_dovi_get_ext(md, 1);
        ext->level = 5;
        ext = av_dovi_get_ext(md, 2);
        ext->level = 1;

        ಸಿಕ್ಕಿತು = av_dovi_ಕಂಡುಹಿಡಿ_level(md, 1);
        ಬರೆ("find level 1: %s\n", ಸಿಕ್ಕಿತು && ಸಿಕ್ಕಿತು->level == 1 ? "OK" : "FAIL");

        ಸಿಕ್ಕಿತು = av_dovi_ಕಂಡುಹಿಡಿ_level(md, 5);
        ಬರೆ("find level 5: %s\n", ಸಿಕ್ಕಿತು && ಸಿಕ್ಕಿತು->level == 5 ? "OK" : "FAIL");

        /* first match -- should return ext[0], not ext[2] */
        ಸಿಕ್ಕಿತು = av_dovi_ಕಂಡುಹಿಡಿ_level(md, 1);
        ಬರೆ("find level 1 first match: %s\n",
               ಸಿಕ್ಕಿತು == av_dovi_get_ext(md, 0) ? "OK" : "FAIL");

        ಸಿಕ್ಕಿತು = av_dovi_ಕಂಡುಹಿಡಿ_level(md, 99);
        ಬರೆ("find level 99 (missing): %s\n", ಸಿಕ್ಕಿತು == ಖಾಲಿ ? "OK" : "FAIL");

        av_free(md);
    }

    /* OOM paths via av_max_alloc */
    ಬರೆ("\nTesting OOM paths\n");
    av_max_alloc(1);
    cfg = av_dovi_alloc(&ಗಾತ್ರ_2);
    ಬರೆ("av_dovi_alloc OOM: %s\n", cfg ? "FAIL" : "OK");
    av_free(cfg);
    md = av_dovi_metadata_alloc(&ಗಾತ್ರ_2);
    ಬರೆ("av_dovi_metadata_alloc OOM: %s\n", md ? "FAIL" : "OK");
    av_free(md);
    av_max_alloc(ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);

    ಹಿಂತಿರುಗಿ 0;
}
