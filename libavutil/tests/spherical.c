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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/spherical.h"

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    AVSphericalMapping *map;
    size_t ਮਾਪ;

    /* av_spherical_alloc with size output */
    ਲਿਖੋ("Testing av_spherical_alloc()\n");
    map = av_spherical_alloc(&ਮਾਪ);
    ਜੇ (map) {
        ਲਿਖੋ("alloc: OK, size>0=%s, default projection=%d\n",
               ਮਾਪ > 0 ? "yes" : "no", map->projection);
        av_free(map);
    } ਨਹੀਂਤਾਂ {
        ਲਿਖੋ("alloc: FAIL\n");
    }

    /* av_spherical_alloc without size */
    map = av_spherical_alloc(ਨਿਰਾ);
    ਲਿਖੋ("alloc (no size): %s\n", map ? "OK" : "FAIL");
    av_free(map);

    /* av_spherical_projection_name - all valid projections */
    ਲਿਖੋ("\nTesting av_spherical_projection_name()\n");
    ਲਈ (ਪੂਰਨ i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++)
        ਲਿਖੋ("projection %d: %s\n", i, av_spherical_projection_name(i));
    ਲਿਖੋ("out of range: %s\n", av_spherical_projection_name(100));

    /* av_spherical_from_name - all valid names */
    ਲਿਖੋ("\nTesting av_spherical_from_name()\n");
    ਲਈ (ਪੂਰਨ i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        ਅਚਲ ਅੱਖਰ *name = av_spherical_projection_name(i);
        ਲਿਖੋ("%s: %d\n", name, av_spherical_from_name(name));
    }
    ਲਿਖੋ("nonexistent: %d\n", av_spherical_from_name("nonexistent"));

    /* projection name round-trip */
    ਲਿਖੋ("\nTesting projection name round-trip\n");
    ਲਈ (ਪੂਰਨ i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        ਅਚਲ ਅੱਖਰ *name = av_spherical_projection_name(i);
        ਪੂਰਨ rt = av_spherical_from_name(name);
        ਲਿਖੋ("roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_spherical_tile_bounds - no bounds (full frame) */
    ਲਿਖੋ("\nTesting av_spherical_tile_bounds()\n");
    map = av_spherical_alloc(ਨਿਰਾ);
    ਜੇ (map) {
        size_t ਖੱਬਾ, ਸਿਖਰ, ਸੱਜਾ, bottom;

        map->projection = AV_SPHERICAL_EQUIRECTANGULAR_TILE;
        ਲਿਖੋ("projection: %s\n",
               av_spherical_projection_name(map->projection));

        map->bound_ਖੱਬਾ   = 0;
        map->bound_ਸਿਖਰ    = 0;
        map->bound_ਸੱਜਾ  = 0;
        map->bound_bottom = 0;
        av_spherical_tile_bounds(map, 1920, 1080, &ਖੱਬਾ, &ਸਿਖਰ, &ਸੱਜਾ, &bottom);
        ਲਿਖੋ("full frame: left=%zu top=%zu right=%zu bottom=%zu\n",
               ਖੱਬਾ, ਸਿਖਰ, ਸੱਜਾ, bottom);

        /* quarter tile at top-left (each bound is 0.32 fixed point) */
        map->bound_ਖੱਬਾ   = 0;
        map->bound_ਸਿਖਰ    = 0;
        map->bound_ਸੱਜਾ  = UINT32_MAX / 2;
        map->bound_bottom = UINT32_MAX / 2;
        av_spherical_tile_bounds(map, 960, 540, &ਖੱਬਾ, &ਸਿਖਰ, &ਸੱਜਾ, &bottom);
        ਲਿਖੋ("quarter top-left: left=%zu top=%zu right=%zu bottom=%zu\n",
               ਖੱਬਾ, ਸਿਖਰ, ਸੱਜਾ, bottom);

        /* centered tile with equal margins */
        map->bound_ਖੱਬਾ   = UINT32_MAX / 4;
        map->bound_ਸਿਖਰ    = UINT32_MAX / 4;
        map->bound_ਸੱਜਾ  = UINT32_MAX / 4;
        map->bound_bottom = UINT32_MAX / 4;
        av_spherical_tile_bounds(map, 960, 540, &ਖੱਬਾ, &ਸਿਖਰ, &ਸੱਜਾ, &bottom);
        ਲਿਖੋ("centered: left=%zu top=%zu right=%zu bottom=%zu\n",
               ਖੱਬਾ, ਸਿਖਰ, ਸੱਜਾ, bottom);

        av_free(map);
    }

    ਵਾਪਸ 0;
}
