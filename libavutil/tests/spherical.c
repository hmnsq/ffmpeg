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

صحيح مکيه(فراغ)
{
    AVSphericalMapping *map;
    size_t سائيز;

    /* av_spherical_alloc with size output */
    لکو("Testing av_spherical_alloc()\n");
    map = av_spherical_alloc(&سائيز);
    إذا (map) {
        لکو("alloc: OK, size>0=%s, default projection=%d\n",
               سائيز > 0 ? "yes" : "no", map->projection);
        av_free(map);
    } وإلا {
        لکو("alloc: FAIL\n");
    }

    /* av_spherical_alloc without size */
    map = av_spherical_alloc(عدم);
    لکو("alloc (no size): %s\n", map ? "OK" : "FAIL");
    av_free(map);

    /* av_spherical_projection_name - all valid projections */
    لکو("\nTesting av_spherical_projection_name()\n");
    لكل (صحيح i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++)
        لکو("projection %d: %s\n", i, av_spherical_projection_name(i));
    لکو("out of range: %s\n", av_spherical_projection_name(100));

    /* av_spherical_from_name - all valid names */
    لکو("\nTesting av_spherical_from_name()\n");
    لكل (صحيح i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        ثابت حرف *name = av_spherical_projection_name(i);
        لکو("%s: %d\n", name, av_spherical_from_name(name));
    }
    لکو("nonexistent: %d\n", av_spherical_from_name("nonexistent"));

    /* projection name round-trip */
    لکو("\nTesting projection name round-trip\n");
    لكل (صحيح i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        ثابت حرف *name = av_spherical_projection_name(i);
        صحيح rt = av_spherical_from_name(name);
        لکو("roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_spherical_tile_bounds - no bounds (full frame) */
    لکو("\nTesting av_spherical_tile_bounds()\n");
    map = av_spherical_alloc(عدم);
    إذا (map) {
        size_t کاٻو, چوٽي, ساڄو, bottom;

        map->projection = AV_SPHERICAL_EQUIRECTANGULAR_TILE;
        لکو("projection: %s\n",
               av_spherical_projection_name(map->projection));

        map->bound_کاٻو   = 0;
        map->bound_چوٽي    = 0;
        map->bound_ساڄو  = 0;
        map->bound_bottom = 0;
        av_spherical_tile_bounds(map, 1920, 1080, &کاٻو, &چوٽي, &ساڄو, &bottom);
        لکو("full frame: left=%zu top=%zu right=%zu bottom=%zu\n",
               کاٻو, چوٽي, ساڄو, bottom);

        /* quarter tile at top-left (each bound is 0.32 fixed point) */
        map->bound_کاٻو   = 0;
        map->bound_چوٽي    = 0;
        map->bound_ساڄو  = UINT32_MAX / 2;
        map->bound_bottom = UINT32_MAX / 2;
        av_spherical_tile_bounds(map, 960, 540, &کاٻو, &چوٽي, &ساڄو, &bottom);
        لکو("quarter top-left: left=%zu top=%zu right=%zu bottom=%zu\n",
               کاٻو, چوٽي, ساڄو, bottom);

        /* centered tile with equal margins */
        map->bound_کاٻو   = UINT32_MAX / 4;
        map->bound_چوٽي    = UINT32_MAX / 4;
        map->bound_ساڄو  = UINT32_MAX / 4;
        map->bound_bottom = UINT32_MAX / 4;
        av_spherical_tile_bounds(map, 960, 540, &کاٻو, &چوٽي, &ساڄو, &bottom);
        لکو("centered: left=%zu top=%zu right=%zu bottom=%zu\n",
               کاٻو, چوٽي, ساڄو, bottom);

        av_free(map);
    }

    أرجع 0;
}
