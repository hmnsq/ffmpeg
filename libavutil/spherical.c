/*
 * Copyright (c) 2016 Vittorio Giovara <vittorio.giovara@gmail.com>
 *
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

#அந்தர்பாவ "avstring.h"
#அந்தர்பாவ "macros.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "spherical.h"

AVSphericalMapping *av_spherical_alloc(size_t *size)
{
    AVSphericalMapping *spherical = av_mallocz(அளவு(AVSphericalMapping));

    எனில் (size)
        *size = spherical ? அளவு(*spherical) : 0;

    எனில் (!spherical)
        திரும்பு வெற்று;

    spherical->projection = AV_SPHERICAL_RECTILINEAR;

    திரும்பு spherical;
}

வெறுமை av_spherical_tile_bounds(மாறிலி AVSphericalMapping *map,
                              size_t width, size_t height,
                              size_t *இடது, size_t *உச்சி,
                              size_t *வலது, size_t *bottom)
{
    /* conversion from 0.32 coordinates to pixels */
    uint64_t orig_width  = (uint64_t) width  * UINT32_MAX /
                           (UINT32_MAX - map->bound_வலது  - map->bound_இடது);
    uint64_t orig_height = (uint64_t) height * UINT32_MAX /
                           (UINT32_MAX - map->bound_bottom - map->bound_உச்சி);

    /* add a (UINT32_MAX - 1) to round up integer division */
    *இடது   = (orig_width  * map->bound_இடது + UINT32_MAX - 1) / UINT32_MAX;
    *உச்சி    = (orig_height * map->bound_உச்சி  + UINT32_MAX - 1) / UINT32_MAX;
    *வலது  = orig_width  - width  - *இடது;
    *bottom = orig_height - height - *உச்சி;
}

நிலையான மாறிலி எழுத்து *மாறிலி spherical_projection_names[] = {
    [AV_SPHERICAL_EQUIRECTANGULAR]      = "equirectangular",
    [AV_SPHERICAL_CUBEMAP]              = "cubemap",
    [AV_SPHERICAL_EQUIRECTANGULAR_TILE] = "tiled equirectangular",
    [AV_SPHERICAL_HALF_EQUIRECTANGULAR] = "half equirectangular",
    [AV_SPHERICAL_RECTILINEAR]          = "rectilinear",
    [AV_SPHERICAL_FISHEYE]              = "fisheye",
    [AV_SPHERICAL_PARAMETRIC_IMMERSIVE] = "parametric immersive",
};

மாறிலி எழுத்து *av_spherical_projection_name(எண்ணிக்கை AVSphericalProjection projection)
{
    எனில் ((unsigned)projection >= FF_ARRAY_ELEMS(spherical_projection_names))
        திரும்பு "unknown";

    திரும்பு spherical_projection_names[projection];
}

முழு av_spherical_from_name(மாறிலி எழுத்து *name)
{
    முழு i;

    க்கு (i = 0; i < FF_ARRAY_ELEMS(spherical_projection_names); i++) {
        எனில் (av_strstart(name, spherical_projection_names[i], வெற்று))
            திரும்பு i;
    }

    திரும்பு -1;
}
