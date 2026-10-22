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

#ಅನ್ತರ್ಭಾವ "avstring.h"
#ಅನ್ತರ್ಭಾವ "macros.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "spherical.h"

AVSphericalMapping *av_spherical_alloc(size_t *size)
{
    AVSphericalMapping *spherical = av_mallocz(ಪರಿಮಾಣ(AVSphericalMapping));

    ಯದಿ (size)
        *size = spherical ? ಪರಿಮಾಣ(*spherical) : 0;

    ಯದಿ (!spherical)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    spherical->projection = AV_SPHERICAL_RECTILINEAR;

    ಪ್ರತ್ಯಾಗಮ spherical;
}

ಶೂನ್ಯ av_spherical_tile_bounds(ಧ್ರುವ AVSphericalMapping *map,
                              size_t width, size_t height,
                              size_t *ಎಡ, size_t *ತುದಿ,
                              size_t *ಬಲ, size_t *bottom)
{
    /* conversion from 0.32 coordinates to pixels */
    uint64_t orig_width  = (uint64_t) width  * UINT32_MAX /
                           (UINT32_MAX - map->bound_ಬಲ  - map->bound_ಎಡ);
    uint64_t orig_height = (uint64_t) height * UINT32_MAX /
                           (UINT32_MAX - map->bound_bottom - map->bound_ತುದಿ);

    /* add a (UINT32_MAX - 1) to round up integer division */
    *ಎಡ   = (orig_width  * map->bound_ಎಡ + UINT32_MAX - 1) / UINT32_MAX;
    *ತುದಿ    = (orig_height * map->bound_ತುದಿ  + UINT32_MAX - 1) / UINT32_MAX;
    *ಬಲ  = orig_width  - width  - *ಎಡ;
    *bottom = orig_height - height - *ತುದಿ;
}

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ spherical_projection_names[] = {
    [AV_SPHERICAL_EQUIRECTANGULAR]      = "equirectangular",
    [AV_SPHERICAL_CUBEMAP]              = "cubemap",
    [AV_SPHERICAL_EQUIRECTANGULAR_TILE] = "tiled equirectangular",
    [AV_SPHERICAL_HALF_EQUIRECTANGULAR] = "half equirectangular",
    [AV_SPHERICAL_RECTILINEAR]          = "rectilinear",
    [AV_SPHERICAL_FISHEYE]              = "fisheye",
    [AV_SPHERICAL_PARAMETRIC_IMMERSIVE] = "parametric immersive",
};

ಧ್ರುವ ವರ್ಣ *av_spherical_projection_name(ಗಣನಾ AVSphericalProjection projection)
{
    ಯದಿ ((unsigned)projection >= FF_ARRAY_ELEMS(spherical_projection_names))
        ಪ್ರತ್ಯಾಗಮ "unknown";

    ಪ್ರತ್ಯಾಗಮ spherical_projection_names[projection];
}

ಪೂರ್ಣಾಙ್ಕ av_spherical_from_name(ಧ್ರುವ ವರ್ಣ *name)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(spherical_projection_names); i++) {
        ಯದಿ (av_strstart(name, spherical_projection_names[i], ರಿಕ್ತ))
            ಪ್ರತ್ಯಾಗಮ i;
    }

    ಪ್ರತ್ಯಾಗಮ -1;
}
