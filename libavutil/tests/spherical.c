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

#அந்தர்பாவ <stdio.h>

#அந்தர்பாவ "libavutil/mem.h"
#அந்தர்பாவ "libavutil/spherical.h"

முழு முதன்மை(வெறுமை)
{
    AVSphericalMapping *map;
    size_t size;

    /* av_spherical_alloc with size output */
    printf("Testing av_spherical_alloc()\n");
    map = av_spherical_alloc(&size);
    எனில் (map) {
        printf("alloc: OK, size>0=%s, default projection=%d\n",
               size > 0 ? "yes" : "no", map->projection);
        av_free(map);
    } இல்லையெனில் {
        printf("alloc: FAIL\n");
    }

    /* av_spherical_alloc without size */
    map = av_spherical_alloc(வெற்று);
    printf("alloc (no size): %s\n", map ? "OK" : "FAIL");
    av_free(map);

    /* av_spherical_projection_name - all valid projections */
    printf("\nTesting av_spherical_projection_name()\n");
    க்கு (முழு i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++)
        printf("projection %d: %s\n", i, av_spherical_projection_name(i));
    printf("out of range: %s\n", av_spherical_projection_name(100));

    /* av_spherical_from_name - all valid names */
    printf("\nTesting av_spherical_from_name()\n");
    க்கு (முழு i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        மாறிலி எழுத்து *name = av_spherical_projection_name(i);
        printf("%s: %d\n", name, av_spherical_from_name(name));
    }
    printf("nonexistent: %d\n", av_spherical_from_name("nonexistent"));

    /* projection name round-trip */
    printf("\nTesting projection name round-trip\n");
    க்கு (முழு i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        மாறிலி எழுத்து *name = av_spherical_projection_name(i);
        முழு rt = av_spherical_from_name(name);
        printf("roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_spherical_tile_bounds - no bounds (full frame) */
    printf("\nTesting av_spherical_tile_bounds()\n");
    map = av_spherical_alloc(வெற்று);
    எனில் (map) {
        size_t இடது, உச்சி, வலது, bottom;

        map->projection = AV_SPHERICAL_EQUIRECTANGULAR_TILE;
        printf("projection: %s\n",
               av_spherical_projection_name(map->projection));

        map->bound_இடது   = 0;
        map->bound_உச்சி    = 0;
        map->bound_வலது  = 0;
        map->bound_bottom = 0;
        av_spherical_tile_bounds(map, 1920, 1080, &இடது, &உச்சி, &வலது, &bottom);
        printf("full frame: left=%zu top=%zu right=%zu bottom=%zu\n",
               இடது, உச்சி, வலது, bottom);

        /* quarter tile at top-left (each bound is 0.32 fixed point) */
        map->bound_இடது   = 0;
        map->bound_உச்சி    = 0;
        map->bound_வலது  = UINT32_MAX / 2;
        map->bound_bottom = UINT32_MAX / 2;
        av_spherical_tile_bounds(map, 960, 540, &இடது, &உச்சி, &வலது, &bottom);
        printf("quarter top-left: left=%zu top=%zu right=%zu bottom=%zu\n",
               இடது, உச்சி, வலது, bottom);

        /* centered tile with equal margins */
        map->bound_இடது   = UINT32_MAX / 4;
        map->bound_உச்சி    = UINT32_MAX / 4;
        map->bound_வலது  = UINT32_MAX / 4;
        map->bound_bottom = UINT32_MAX / 4;
        av_spherical_tile_bounds(map, 960, 540, &இடது, &உச்சி, &வலது, &bottom);
        printf("centered: left=%zu top=%zu right=%zu bottom=%zu\n",
               இடது, உச்சி, வலது, bottom);

        av_free(map);
    }

    திரும்பு 0;
}
