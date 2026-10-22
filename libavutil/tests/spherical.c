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

#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/mem.h"
#అన్తర్భావ "libavutil/spherical.h"

పూర్ణాంకం ప్రధాన(శూన్య)
{
    AVSphericalMapping *map;
    size_t కొలత;

    /* av_spherical_alloc with size output */
    రాయి("Testing av_spherical_alloc()\n");
    map = av_spherical_alloc(&కొలత);
    ఒకవేళ (map) {
        రాయి("alloc: OK, size>0=%s, default projection=%d\n",
               కొలత > 0 ? "yes" : "no", map->projection);
        av_free(map);
    } లేకపోతే {
        రాయి("alloc: FAIL\n");
    }

    /* av_spherical_alloc without size */
    map = av_spherical_alloc(ఖాళీ);
    రాయి("alloc (no size): %s\n", map ? "OK" : "FAIL");
    av_free(map);

    /* av_spherical_projection_name - all valid projections */
    రాయి("\nTesting av_spherical_projection_name()\n");
    కొరకు (పూర్ణాంకం i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++)
        రాయి("projection %d: %s\n", i, av_spherical_projection_name(i));
    రాయి("out of range: %s\n", av_spherical_projection_name(100));

    /* av_spherical_from_name - all valid names */
    రాయి("\nTesting av_spherical_from_name()\n");
    కొరకు (పూర్ణాంకం i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        స్థిరరాశి అక్షరం *name = av_spherical_projection_name(i);
        రాయి("%s: %d\n", name, av_spherical_from_name(name));
    }
    రాయి("nonexistent: %d\n", av_spherical_from_name("nonexistent"));

    /* projection name round-trip */
    రాయి("\nTesting projection name round-trip\n");
    కొరకు (పూర్ణాంకం i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        స్థిరరాశి అక్షరం *name = av_spherical_projection_name(i);
        పూర్ణాంకం rt = av_spherical_from_name(name);
        రాయి("roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_spherical_tile_bounds - no bounds (full frame) */
    రాయి("\nTesting av_spherical_tile_bounds()\n");
    map = av_spherical_alloc(ఖాళీ);
    ఒకవేళ (map) {
        size_t ఎడమ, శిఖరం, కుడి, bottom;

        map->projection = AV_SPHERICAL_EQUIRECTANGULAR_TILE;
        రాయి("projection: %s\n",
               av_spherical_projection_name(map->projection));

        map->bound_ఎడమ   = 0;
        map->bound_శిఖరం    = 0;
        map->bound_కుడి  = 0;
        map->bound_bottom = 0;
        av_spherical_tile_bounds(map, 1920, 1080, &ఎడమ, &శిఖరం, &కుడి, &bottom);
        రాయి("full frame: left=%zu top=%zu right=%zu bottom=%zu\n",
               ఎడమ, శిఖరం, కుడి, bottom);

        /* quarter tile at top-left (each bound is 0.32 fixed point) */
        map->bound_ఎడమ   = 0;
        map->bound_శిఖరం    = 0;
        map->bound_కుడి  = UINT32_MAX / 2;
        map->bound_bottom = UINT32_MAX / 2;
        av_spherical_tile_bounds(map, 960, 540, &ఎడమ, &శిఖరం, &కుడి, &bottom);
        రాయి("quarter top-left: left=%zu top=%zu right=%zu bottom=%zu\n",
               ఎడమ, శిఖరం, కుడి, bottom);

        /* centered tile with equal margins */
        map->bound_ఎడమ   = UINT32_MAX / 4;
        map->bound_శిఖరం    = UINT32_MAX / 4;
        map->bound_కుడి  = UINT32_MAX / 4;
        map->bound_bottom = UINT32_MAX / 4;
        av_spherical_tile_bounds(map, 960, 540, &ఎడమ, &శిఖరం, &కుడి, &bottom);
        రాయి("centered: left=%zu top=%zu right=%zu bottom=%zu\n",
               ఎడమ, శిఖరం, కుడి, bottom);

        av_free(map);
    }

    తిరిగి 0;
}
