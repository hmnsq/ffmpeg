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

#شامل <stdio.h>

#شامل "libavutil/mem.h"
#شامل "libavutil/spherical.h"

صحیح مین(خالی)
{
    AVSphericalMapping *map;
    size_t سائز;

    /* av_spherical_alloc with size output */
    لکھو("Testing av_spherical_alloc()\n");
    map = av_spherical_alloc(&سائز);
    اگر (map) {
        لکھو("alloc: OK, size>0=%s, default projection=%d\n",
               سائز > 0 ? "yes" : "no", map->projection);
        av_free(map);
    } ورنہ {
        لکھو("alloc: FAIL\n");
    }

    /* av_spherical_alloc without size */
    map = av_spherical_alloc(تہی);
    لکھو("alloc (no size): %s\n", map ? "OK" : "FAIL");
    av_free(map);

    /* av_spherical_projection_name - all valid projections */
    لکھو("\nTesting av_spherical_projection_name()\n");
    برائے (صحیح i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++)
        لکھو("projection %d: %s\n", i, av_spherical_projection_name(i));
    لکھو("out of range: %s\n", av_spherical_projection_name(100));

    /* av_spherical_from_name - all valid names */
    لکھو("\nTesting av_spherical_from_name()\n");
    برائے (صحیح i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        ثابت حرف *name = av_spherical_projection_name(i);
        لکھو("%s: %d\n", name, av_spherical_from_name(name));
    }
    لکھو("nonexistent: %d\n", av_spherical_from_name("nonexistent"));

    /* projection name round-trip */
    لکھو("\nTesting projection name round-trip\n");
    برائے (صحیح i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        ثابت حرف *name = av_spherical_projection_name(i);
        صحیح rt = av_spherical_from_name(name);
        لکھو("roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_spherical_tile_bounds - no bounds (full frame) */
    لکھو("\nTesting av_spherical_tile_bounds()\n");
    map = av_spherical_alloc(تہی);
    اگر (map) {
        size_t بایاں, چوٹی, دایاں, bottom;

        map->projection = AV_SPHERICAL_EQUIRECTANGULAR_TILE;
        لکھو("projection: %s\n",
               av_spherical_projection_name(map->projection));

        map->bound_بایاں   = 0;
        map->bound_چوٹی    = 0;
        map->bound_دایاں  = 0;
        map->bound_bottom = 0;
        av_spherical_tile_bounds(map, 1920, 1080, &بایاں, &چوٹی, &دایاں, &bottom);
        لکھو("full frame: left=%zu top=%zu right=%zu bottom=%zu\n",
               بایاں, چوٹی, دایاں, bottom);

        /* quarter tile at top-left (each bound is 0.32 fixed point) */
        map->bound_بایاں   = 0;
        map->bound_چوٹی    = 0;
        map->bound_دایاں  = UINT32_MAX / 2;
        map->bound_bottom = UINT32_MAX / 2;
        av_spherical_tile_bounds(map, 960, 540, &بایاں, &چوٹی, &دایاں, &bottom);
        لکھو("quarter top-left: left=%zu top=%zu right=%zu bottom=%zu\n",
               بایاں, چوٹی, دایاں, bottom);

        /* centered tile with equal margins */
        map->bound_بایاں   = UINT32_MAX / 4;
        map->bound_چوٹی    = UINT32_MAX / 4;
        map->bound_دایاں  = UINT32_MAX / 4;
        map->bound_bottom = UINT32_MAX / 4;
        av_spherical_tile_bounds(map, 960, 540, &بایاں, &چوٹی, &دایاں, &bottom);
        لکھو("centered: left=%zu top=%zu right=%zu bottom=%zu\n",
               بایاں, چوٹی, دایاں, bottom);

        av_free(map);
    }

    واپس 0;
}
