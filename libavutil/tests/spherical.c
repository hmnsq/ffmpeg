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

صحيح اصلي(فراغ)
{
    AVSphericalMapping *map;
    size_t اندازه;

    /* av_spherical_alloc with size output */
    چاپ_کړه("Testing av_spherical_alloc()\n");
    map = av_spherical_alloc(&اندازه);
    إذا (map) {
        چاپ_کړه("alloc: OK, size>0=%s, default projection=%d\n",
               اندازه > 0 ? "yes" : "no", map->projection);
        av_free(map);
    } وإلا {
        چاپ_کړه("alloc: FAIL\n");
    }

    /* av_spherical_alloc without size */
    map = av_spherical_alloc(عدم);
    چاپ_کړه("alloc (no size): %s\n", map ? "OK" : "FAIL");
    av_free(map);

    /* av_spherical_projection_name - all valid projections */
    چاپ_کړه("\nTesting av_spherical_projection_name()\n");
    لكل (صحيح i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++)
        چاپ_کړه("projection %d: %s\n", i, av_spherical_projection_name(i));
    چاپ_کړه("out of range: %s\n", av_spherical_projection_name(100));

    /* av_spherical_from_name - all valid names */
    چاپ_کړه("\nTesting av_spherical_from_name()\n");
    لكل (صحيح i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        ثابت حرف *name = av_spherical_projection_name(i);
        چاپ_کړه("%s: %d\n", name, av_spherical_from_name(name));
    }
    چاپ_کړه("nonexistent: %d\n", av_spherical_from_name("nonexistent"));

    /* projection name round-trip */
    چاپ_کړه("\nTesting projection name round-trip\n");
    لكل (صحيح i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        ثابت حرف *name = av_spherical_projection_name(i);
        صحيح rt = av_spherical_from_name(name);
        چاپ_کړه("roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_spherical_tile_bounds - no bounds (full frame) */
    چاپ_کړه("\nTesting av_spherical_tile_bounds()\n");
    map = av_spherical_alloc(عدم);
    إذا (map) {
        size_t کیڼ, سر, ښی, bottom;

        map->projection = AV_SPHERICAL_EQUIRECTANGULAR_TILE;
        چاپ_کړه("projection: %s\n",
               av_spherical_projection_name(map->projection));

        map->bound_کیڼ   = 0;
        map->bound_سر    = 0;
        map->bound_ښی  = 0;
        map->bound_bottom = 0;
        av_spherical_tile_bounds(map, 1920, 1080, &کیڼ, &سر, &ښی, &bottom);
        چاپ_کړه("full frame: left=%zu top=%zu right=%zu bottom=%zu\n",
               کیڼ, سر, ښی, bottom);

        /* quarter tile at top-left (each bound is 0.32 fixed point) */
        map->bound_کیڼ   = 0;
        map->bound_سر    = 0;
        map->bound_ښی  = UINT32_MAX / 2;
        map->bound_bottom = UINT32_MAX / 2;
        av_spherical_tile_bounds(map, 960, 540, &کیڼ, &سر, &ښی, &bottom);
        چاپ_کړه("quarter top-left: left=%zu top=%zu right=%zu bottom=%zu\n",
               کیڼ, سر, ښی, bottom);

        /* centered tile with equal margins */
        map->bound_کیڼ   = UINT32_MAX / 4;
        map->bound_سر    = UINT32_MAX / 4;
        map->bound_ښی  = UINT32_MAX / 4;
        map->bound_bottom = UINT32_MAX / 4;
        av_spherical_tile_bounds(map, 960, 540, &کیڼ, &سر, &ښی, &bottom);
        چاپ_کړه("centered: left=%zu top=%zu right=%zu bottom=%zu\n",
               کیڼ, سر, ښی, bottom);

        av_free(map);
    }

    أرجع 0;
}
