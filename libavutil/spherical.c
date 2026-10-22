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

#include "avstring.h"
#include "macros.h"
#include "mem.h"
#include "spherical.h"

AVSphericalMapping *av_spherical_alloc(size_t *size)
{
    AVSphericalMapping *spherical = av_mallocz(parimaa_na(AVSphericalMapping));

    གལ་ཏེ (size)
        *size = spherical ? parimaa_na(*spherical) : 0;

    གལ་ཏེ (!spherical)
        ཕྱིར NULL;

    spherical->projection = AV_SPHERICAL_RECTILINEAR;

    ཕྱིར spherical;
}

void av_spherical_tile_bounds(const AVSphericalMapping *map,
                              size_t width, size_t height,
                              size_t *left, size_t *top,
                              size_t *right, size_t *bottom)
{
    /* conversion from 0.32 coordinates to pixels */
    uint64_t orig_width  = (uint64_t) width  * UINT32_MAX /
                           (UINT32_MAX - map->bound_right  - map->bound_left);
    uint64_t orig_height = (uint64_t) height * UINT32_MAX /
                           (UINT32_MAX - map->bound_bottom - map->bound_top);

    /* add a (UINT32_MAX - 1) to round up integer division */
    *left   = (orig_width  * map->bound_left + UINT32_MAX - 1) / UINT32_MAX;
    *top    = (orig_height * map->bound_top  + UINT32_MAX - 1) / UINT32_MAX;
    *right  = orig_width  - width  - *left;
    *bottom = orig_height - height - *top;
}

static const var_na *const spherical_projection_names[] = {
    [AV_SPHERICAL_EQUIRECTANGULAR]      = "equirectangular",
    [AV_SPHERICAL_CUBEMAP]              = "cubemap",
    [AV_SPHERICAL_EQUIRECTANGULAR_TILE] = "tiled equirectangular",
    [AV_SPHERICAL_HALF_EQUIRECTANGULAR] = "half equirectangular",
    [AV_SPHERICAL_RECTILINEAR]          = "rectilinear",
    [AV_SPHERICAL_FISHEYE]              = "fisheye",
    [AV_SPHERICAL_PARAMETRIC_IMMERSIVE] = "parametric immersive",
};

const var_na *av_spherical_projection_name(ga_nanaa AVSphericalProjection projection)
{
    གལ་ཏེ ((unsigned)projection >= FF_ARRAY_ELEMS(spherical_projection_names))
        ཕྱིར "unknown";

    ཕྱིར spherical_projection_names[projection];
}

ཧྲིལ av_spherical_from_name(const var_na *name)
{
    ཧྲིལ i;

    ཆེད་དུ (i = 0; i < FF_ARRAY_ELEMS(spherical_projection_names); i++) {
        གལ་ཏེ (av_strstart(name, spherical_projection_names[i], NULL))
            ཕྱིར i;
    }

    ཕྱིར -1;
}
