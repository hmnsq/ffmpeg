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

#ਅਨ੍ਤਰ੍ਭਾਵ "avstring.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "spherical.h"

AVSphericalMapping *av_spherical_alloc(size_t *ਮਾਪ)
{
    AVSphericalMapping *spherical = av_mallocz(ਆਕਾਰ(AVSphericalMapping));

    ਜੇ (ਮਾਪ)
        *ਮਾਪ = spherical ? ਆਕਾਰ(*spherical) : 0;

    ਜੇ (!spherical)
        ਵਾਪਸ ਨਿਰਾ;

    spherical->projection = AV_SPHERICAL_RECTILINEAR;

    ਵਾਪਸ spherical;
}

ਖਾਲੀ av_spherical_tile_bounds(ਅਚਲ AVSphericalMapping *map,
                              size_t ਚੌੜਾਈ, size_t ਉਚਾਈ,
                              size_t *ਖੱਬਾ, size_t *ਸਿਖਰ,
                              size_t *ਸੱਜਾ, size_t *bottom)
{
    /* conversion from 0.32 coordinates to pixels */
    uint64_t orig_ਚੌੜਾਈ  = (uint64_t) ਚੌੜਾਈ  * UINT32_MAX /
                           (UINT32_MAX - map->bound_ਸੱਜਾ  - map->bound_ਖੱਬਾ);
    uint64_t orig_ਉਚਾਈ = (uint64_t) ਉਚਾਈ * UINT32_MAX /
                           (UINT32_MAX - map->bound_bottom - map->bound_ਸਿਖਰ);

    /* add a (UINT32_MAX - 1) to round up integer division */
    *ਖੱਬਾ   = (orig_ਚੌੜਾਈ  * map->bound_ਖੱਬਾ + UINT32_MAX - 1) / UINT32_MAX;
    *ਸਿਖਰ    = (orig_ਉਚਾਈ * map->bound_ਸਿਖਰ  + UINT32_MAX - 1) / UINT32_MAX;
    *ਸੱਜਾ  = orig_ਚੌੜਾਈ  - ਚੌੜਾਈ  - *ਖੱਬਾ;
    *bottom = orig_ਉਚਾਈ - ਉਚਾਈ - *ਸਿਖਰ;
}

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਅਚਲ spherical_projection_ਨਾਂ[] = {
    [AV_SPHERICAL_EQUIRECTANGULAR]      = "equirectangular",
    [AV_SPHERICAL_CUBEMAP]              = "cubemap",
    [AV_SPHERICAL_EQUIRECTANGULAR_TILE] = "tiled equirectangular",
    [AV_SPHERICAL_HALF_EQUIRECTANGULAR] = "half equirectangular",
    [AV_SPHERICAL_RECTILINEAR]          = "rectilinear",
    [AV_SPHERICAL_FISHEYE]              = "fisheye",
    [AV_SPHERICAL_PARAMETRIC_IMMERSIVE] = "parametric immersive",
};

ਅਚਲ ਅੱਖਰ *av_spherical_projection_name(ਗਿਣਤੀ AVSphericalProjection projection)
{
    ਜੇ ((ਬਿਨਾਨਿਸ਼ਾਨੀ)projection >= FF_ARRAY_ELEMS(spherical_projection_ਨਾਂ))
        ਵਾਪਸ "unknown";

    ਵਾਪਸ spherical_projection_ਨਾਂ[projection];
}

ਪੂਰਨ av_spherical_from_name(ਅਚਲ ਅੱਖਰ *name)
{
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(spherical_projection_ਨਾਂ); i++) {
        ਜੇ (av_strstart(name, spherical_projection_ਨਾਂ[i], ਨਿਰਾ))
            ਵਾਪਸ i;
    }

    ਵਾਪਸ -1;
}
