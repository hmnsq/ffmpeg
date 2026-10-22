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

#ضمن <stdio.h>

#ضمن "libavutil/mem.h"
#ضمن "libavutil/spherical.h"

صحيح اصلی(فراغ)
{
    AVSphericalMapping *map;
    size_t اندازه;

    /* av_spherical_alloc with size output */
    چاپ_کن("Testing av_spherical_alloc()\n");
    map = av_spherical_alloc(&اندازه);
    إذا (map) {
        چاپ_کن("alloc: OK, size>0=%s, default projection=%d\n",
               اندازه > 0 ? "yes" : "no", map->projection);
        av_free(map);
    } وإلا {
        چاپ_کن("alloc: FAIL\n");
    }

    /* av_spherical_alloc without size */
    map = av_spherical_alloc(عدم);
    چاپ_کن("alloc (no size): %s\n", map ? "OK" : "FAIL");
    av_free(map);

    /* av_spherical_projection_name - all valid projections */
    چاپ_کن("\nTesting av_spherical_projection_name()\n");
    لكل (صحيح i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++)
        چاپ_کن("projection %d: %s\n", i, av_spherical_projection_name(i));
    چاپ_کن("out of range: %s\n", av_spherical_projection_name(100));

    /* av_spherical_from_name - all valid names */
    چاپ_کن("\nTesting av_spherical_from_name()\n");
    لكل (صحيح i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        ثابت حرف *name = av_spherical_projection_name(i);
        چاپ_کن("%s: %d\n", name, av_spherical_from_name(name));
    }
    چاپ_کن("nonexistent: %d\n", av_spherical_from_name("nonexistent"));

    /* projection name round-trip */
    چاپ_کن("\nTesting projection name round-trip\n");
    لكل (صحيح i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        ثابت حرف *name = av_spherical_projection_name(i);
        صحيح rt = av_spherical_from_name(name);
        چاپ_کن("roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_spherical_tile_bounds - no bounds (full frame) */
    چاپ_کن("\nTesting av_spherical_tile_bounds()\n");
    map = av_spherical_alloc(عدم);
    إذا (map) {
        size_t چپ, بالاترین, راست, bottom;

        map->projection = AV_SPHERICAL_EQUIRECTANGULAR_TILE;
        چاپ_کن("projection: %s\n",
               av_spherical_projection_name(map->projection));

        map->bound_چپ   = 0;
        map->bound_بالاترین    = 0;
        map->bound_راست  = 0;
        map->bound_bottom = 0;
        av_spherical_tile_bounds(map, 1920, 1080, &چپ, &بالاترین, &راست, &bottom);
        چاپ_کن("full frame: left=%zu top=%zu right=%zu bottom=%zu\n",
               چپ, بالاترین, راست, bottom);

        /* quarter tile at top-left (each bound is 0.32 fixed point) */
        map->bound_چپ   = 0;
        map->bound_بالاترین    = 0;
        map->bound_راست  = UINT32_MAX / 2;
        map->bound_bottom = UINT32_MAX / 2;
        av_spherical_tile_bounds(map, 960, 540, &چپ, &بالاترین, &راست, &bottom);
        چاپ_کن("quarter top-left: left=%zu top=%zu right=%zu bottom=%zu\n",
               چپ, بالاترین, راست, bottom);

        /* centered tile with equal margins */
        map->bound_چپ   = UINT32_MAX / 4;
        map->bound_بالاترین    = UINT32_MAX / 4;
        map->bound_راست  = UINT32_MAX / 4;
        map->bound_bottom = UINT32_MAX / 4;
        av_spherical_tile_bounds(map, 960, 540, &چپ, &بالاترین, &راست, &bottom);
        چاپ_کن("centered: left=%zu top=%zu right=%zu bottom=%zu\n",
               چپ, بالاترین, راست, bottom);

        av_free(map);
    }

    أرجع 0;
}
