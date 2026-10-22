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

#अन्तर्भाव <stdio.h>

#अन्तर्भाव "libavutil/mem.h"
#अन्तर्भाव "libavutil/spherical.h"

पूर्णांक main(शून्य)
{
    AVSphericalMapping *map;
    माप_प्रकार size;

    /* av_spherical_alloc with size output */
    म_लिखो("Testing av_spherical_alloc()\n");
    map = av_spherical_alloc(&size);
    जर (map) {
        म_लिखो("alloc: OK, size>0=%s, default projection=%d\n",
               size > 0 ? "yes" : "no", map->projection);
        av_free(map);
    } अन्यथा {
        म_लिखो("alloc: FAIL\n");
    }

    /* av_spherical_alloc without size */
    map = av_spherical_alloc(रिक्त);
    म_लिखो("alloc (no size): %s\n", map ? "OK" : "FAIL");
    av_free(map);

    /* av_spherical_projection_name - all valid projections */
    म_लिखो("\nTesting av_spherical_projection_name()\n");
    साठी (पूर्णांक i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++)
        म_लिखो("projection %d: %s\n", i, av_spherical_projection_name(i));
    म_लिखो("out of range: %s\n", av_spherical_projection_name(100));

    /* av_spherical_from_name - all valid names */
    म_लिखो("\nTesting av_spherical_from_name()\n");
    साठी (पूर्णांक i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        स्थिरांक अक्षर *name = av_spherical_projection_name(i);
        म_लिखो("%s: %d\n", name, av_spherical_from_name(name));
    }
    म_लिखो("nonexistent: %d\n", av_spherical_from_name("nonexistent"));

    /* projection name round-trip */
    म_लिखो("\nTesting projection name round-trip\n");
    साठी (पूर्णांक i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        स्थिरांक अक्षर *name = av_spherical_projection_name(i);
        पूर्णांक rt = av_spherical_from_name(name);
        म_लिखो("roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_spherical_tile_bounds - no bounds (full frame) */
    म_लिखो("\nTesting av_spherical_tile_bounds()\n");
    map = av_spherical_alloc(रिक्त);
    जर (map) {
        माप_प्रकार डावा, शीर्ष, उजवा, bottom;

        map->projection = AV_SPHERICAL_EQUIRECTANGULAR_TILE;
        म_लिखो("projection: %s\n",
               av_spherical_projection_name(map->projection));

        map->bound_डावा   = 0;
        map->bound_शीर्ष    = 0;
        map->bound_उजवा  = 0;
        map->bound_bottom = 0;
        av_spherical_tile_bounds(map, 1920, 1080, &डावा, &शीर्ष, &उजवा, &bottom);
        म_लिखो("full frame: left=%zu top=%zu right=%zu bottom=%zu\n",
               डावा, शीर्ष, उजवा, bottom);

        /* quarter tile at top-left (each bound is 0.32 fixed point) */
        map->bound_डावा   = 0;
        map->bound_शीर्ष    = 0;
        map->bound_उजवा  = UINT32_MAX / 2;
        map->bound_bottom = UINT32_MAX / 2;
        av_spherical_tile_bounds(map, 960, 540, &डावा, &शीर्ष, &उजवा, &bottom);
        म_लिखो("quarter top-left: left=%zu top=%zu right=%zu bottom=%zu\n",
               डावा, शीर्ष, उजवा, bottom);

        /* centered tile with equal margins */
        map->bound_डावा   = UINT32_MAX / 4;
        map->bound_शीर्ष    = UINT32_MAX / 4;
        map->bound_उजवा  = UINT32_MAX / 4;
        map->bound_bottom = UINT32_MAX / 4;
        av_spherical_tile_bounds(map, 960, 540, &डावा, &शीर्ष, &उजवा, &bottom);
        म_लिखो("centered: left=%zu top=%zu right=%zu bottom=%zu\n",
               डावा, शीर्ष, उजवा, bottom);

        av_free(map);
    }

    परत 0;
}
