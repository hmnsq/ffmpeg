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

#અન્તર્ભાવ "avstring.h"
#અન્તર્ભાવ "macros.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "spherical.h"

AVSphericalMapping *av_spherical_alloc(size_t *size)
{
    AVSphericalMapping *spherical = av_mallocz(કદ(AVSphericalMapping));

    જો (size)
        *size = spherical ? કદ(*spherical) : 0;

    જો (!spherical)
        પાછા ખાલી;

    spherical->projection = AV_SPHERICAL_RECTILINEAR;

    પાછા spherical;
}

શૂન્ય av_spherical_tile_bounds(અચલ AVSphericalMapping *map,
                              size_t width, size_t height,
                              size_t *ડાબું, size_t *ટોચ,
                              size_t *જમણું, size_t *bottom)
{
    /* conversion from 0.32 coordinates to pixels */
    uint64_t orig_width  = (uint64_t) width  * UINT32_MAX /
                           (UINT32_MAX - map->bound_જમણું  - map->bound_ડાબું);
    uint64_t orig_height = (uint64_t) height * UINT32_MAX /
                           (UINT32_MAX - map->bound_bottom - map->bound_ટોચ);

    /* add a (UINT32_MAX - 1) to round up integer division */
    *ડાબું   = (orig_width  * map->bound_ડાબું + UINT32_MAX - 1) / UINT32_MAX;
    *ટોચ    = (orig_height * map->bound_ટોચ  + UINT32_MAX - 1) / UINT32_MAX;
    *જમણું  = orig_width  - width  - *ડાબું;
    *bottom = orig_height - height - *ટોચ;
}

સ્થિર અચલ અક્ષર *અચલ spherical_projection_names[] = {
    [AV_SPHERICAL_EQUIRECTANGULAR]      = "equirectangular",
    [AV_SPHERICAL_CUBEMAP]              = "cubemap",
    [AV_SPHERICAL_EQUIRECTANGULAR_TILE] = "tiled equirectangular",
    [AV_SPHERICAL_HALF_EQUIRECTANGULAR] = "half equirectangular",
    [AV_SPHERICAL_RECTILINEAR]          = "rectilinear",
    [AV_SPHERICAL_FISHEYE]              = "fisheye",
    [AV_SPHERICAL_PARAMETRIC_IMMERSIVE] = "parametric immersive",
};

અચલ અક્ષર *av_spherical_projection_name(ગણના AVSphericalProjection projection)
{
    જો ((unsigned)projection >= FF_ARRAY_ELEMS(spherical_projection_names))
        પાછા "unknown";

    પાછા spherical_projection_names[projection];
}

પૂર્ણાંક av_spherical_from_name(અચલ અક્ષર *name)
{
    પૂર્ણાંક i;

    માટે (i = 0; i < FF_ARRAY_ELEMS(spherical_projection_names); i++) {
        જો (av_strstart(name, spherical_projection_names[i], ખાલી))
            પાછા i;
    }

    પાછા -1;
}
