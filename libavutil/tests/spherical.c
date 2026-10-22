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

पूर्णाङ्क मुख्यम्(शून्य)
{
    AVSphericalMapping *map;
    size_t आकार;

    /* av_spherical_alloc with size output */
    प्रारूप_लिख("Testing av_spherical_alloc()\n");
    map = av_spherical_alloc(&आकार);
    यदि (map) {
        प्रारूप_लिख("alloc: OK, size>0=%s, default projection=%d\n",
               आकार > 0 ? "yes" : "no", map->projection);
        av_free(map);
    } अन्यथा {
        प्रारूप_लिख("alloc: FAIL\n");
    }

    /* av_spherical_alloc without size */
    map = av_spherical_alloc(रिक्त);
    प्रारूप_लिख("alloc (no size): %s\n", map ? "OK" : "FAIL");
    av_free(map);

    /* av_spherical_projection_name - all valid projections */
    प्रारूप_लिख("\nTesting av_spherical_projection_name()\n");
    प्रति (पूर्णाङ्क i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++)
        प्रारूप_लिख("projection %d: %s\n", i, av_spherical_projection_name(i));
    प्रारूप_लिख("out of range: %s\n", av_spherical_projection_name(100));

    /* av_spherical_from_name - all valid names */
    प्रारूप_लिख("\nTesting av_spherical_from_name()\n");
    प्रति (पूर्णाङ्क i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        ध्रुव वर्ण *name = av_spherical_projection_name(i);
        प्रारूप_लिख("%s: %d\n", name, av_spherical_from_name(name));
    }
    प्रारूप_लिख("nonexistent: %d\n", av_spherical_from_name("nonexistent"));

    /* projection name round-trip */
    प्रारूप_लिख("\nTesting projection name round-trip\n");
    प्रति (पूर्णाङ्क i = 0; i <= AV_SPHERICAL_PARAMETRIC_IMMERSIVE; i++) {
        ध्रुव वर्ण *name = av_spherical_projection_name(i);
        पूर्णाङ्क rt = av_spherical_from_name(name);
        प्रारूप_लिख("roundtrip %d (%s): %s\n", i, name, rt == i ? "OK" : "FAIL");
    }

    /* av_spherical_tile_bounds - no bounds (full frame) */
    प्रारूप_लिख("\nTesting av_spherical_tile_bounds()\n");
    map = av_spherical_alloc(रिक्त);
    यदि (map) {
        size_t वामः, शिखरम्, दक्षिणः, bottom;

        map->projection = AV_SPHERICAL_EQUIRECTANGULAR_TILE;
        प्रारूप_लिख("projection: %s\n",
               av_spherical_projection_name(map->projection));

        map->bound_वामः   = 0;
        map->bound_शिखरम्    = 0;
        map->bound_दक्षिणः  = 0;
        map->bound_bottom = 0;
        av_spherical_tile_bounds(map, 1920, 1080, &वामः, &शिखरम्, &दक्षिणः, &bottom);
        प्रारूप_लिख("full frame: left=%zu top=%zu right=%zu bottom=%zu\n",
               वामः, शिखरम्, दक्षिणः, bottom);

        /* quarter tile at top-left (each bound is 0.32 fixed point) */
        map->bound_वामः   = 0;
        map->bound_शिखरम्    = 0;
        map->bound_दक्षिणः  = UINT32_MAX / 2;
        map->bound_bottom = UINT32_MAX / 2;
        av_spherical_tile_bounds(map, 960, 540, &वामः, &शिखरम्, &दक्षिणः, &bottom);
        प्रारूप_लिख("quarter top-left: left=%zu top=%zu right=%zu bottom=%zu\n",
               वामः, शिखरम्, दक्षिणः, bottom);

        /* centered tile with equal margins */
        map->bound_वामः   = UINT32_MAX / 4;
        map->bound_शिखरम्    = UINT32_MAX / 4;
        map->bound_दक्षिणः  = UINT32_MAX / 4;
        map->bound_bottom = UINT32_MAX / 4;
        av_spherical_tile_bounds(map, 960, 540, &वामः, &शिखरम्, &दक्षिणः, &bottom);
        प्रारूप_लिख("centered: left=%zu top=%zu right=%zu bottom=%zu\n",
               वामः, शिखरम्, दक्षिणः, bottom);

        av_free(map);
    }

    प्रत्यागम 0;
}
