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

#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"
#ಅನ್ತರ್ಭಾವ "libavutil/spherical.h"

ಪೂರ್ಣಾಙ್ಕ main(ಶೂನ್ಯ)
{
    AVSphericalMapping *map;
    size_t size;

    /* av_spherical_alloc with size output */
    printf("Testing av_spherical_alloc()\n");
    map = av_spherical_alloc(&size);
    ಯದಿ (map) {
        printf("alloc: OK, size>0=%s, default projection=%d\n",
               size > 0 ? "yes" : "no", map->projection);
        av_free(map);
    } ಅನ್ಯಥಾ {
        printf("alloc: FAIL\n");
    }

    /* av_spherical_alloc without size */
    map = av_spherical_alloc(ರಿಕ್ತ);
    printf("alloc (no size): %s\n", map ? "OK" : "FAIL");
    av_free(map);

    /* av_spherical_projection_name - all valid projections */
    printf("\nTesting av_spherical_projection_name()\n");
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++)
        printf("projection %d: %s\n", i, av_spherical_projection_name(i));
    printf("out of range: %s\n", av_spherical_projection_name(100));

    /* av_spherical_from_name - all valid names */
    printf("\nTesting av_spherical_from_name()\n");
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        ಧ್ರುವ ವರ್ಣ *name = av_spherical_projection_name(i);
        printf("%s: %d\n", name, av_spherical_from_name(name));
    }
    printf("nonexistent: %d\n", av_spherical_from_name("nonexistent"));

    /* projection name round-trip */
    printf("\nTesting projection name round-trip\n");
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        ಧ್ರುವ ವರ್ಣ *name = av_spherical_projection_name(i);
        ಪೂರ್ಣಾಙ್ಕ rt = av_spherical_from_name(name);
        printf("roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_spherical_tile_bounds - no bounds (full frame) */
    printf("\nTesting av_spherical_tile_bounds()\n");
    map = av_spherical_alloc(ರಿಕ್ತ);
    ಯದಿ (map) {
        size_t ಎಡ, ತುದಿ, ಬಲ, bottom;

        map->projection = AV_SPHERICAL_EQUIRECTANGULAR_TILE;
        printf("projection: %s\n",
               av_spherical_projection_name(map->projection));

        map->bound_ಎಡ   = 0;
        map->bound_ತುದಿ    = 0;
        map->bound_ಬಲ  = 0;
        map->bound_bottom = 0;
        av_spherical_tile_bounds(map, 1920, 1080, &ಎಡ, &ತುದಿ, &ಬಲ, &bottom);
        printf("full frame: left=%zu top=%zu right=%zu bottom=%zu\n",
               ಎಡ, ತುದಿ, ಬಲ, bottom);

        /* quarter tile at top-left (each bound is 0.32 fixed point) */
        map->bound_ಎಡ   = 0;
        map->bound_ತುದಿ    = 0;
        map->bound_ಬಲ  = UINT32_MAX / 2;
        map->bound_bottom = UINT32_MAX / 2;
        av_spherical_tile_bounds(map, 960, 540, &ಎಡ, &ತುದಿ, &ಬಲ, &bottom);
        printf("quarter top-left: left=%zu top=%zu right=%zu bottom=%zu\n",
               ಎಡ, ತುದಿ, ಬಲ, bottom);

        /* centered tile with equal margins */
        map->bound_ಎಡ   = UINT32_MAX / 4;
        map->bound_ತುದಿ    = UINT32_MAX / 4;
        map->bound_ಬಲ  = UINT32_MAX / 4;
        map->bound_bottom = UINT32_MAX / 4;
        av_spherical_tile_bounds(map, 960, 540, &ಎಡ, &ತುದಿ, &ಬಲ, &bottom);
        printf("centered: left=%zu top=%zu right=%zu bottom=%zu\n",
               ಎಡ, ತುದಿ, ಬಲ, bottom);

        av_free(map);
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}
