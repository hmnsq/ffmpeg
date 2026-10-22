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

AVSphericalMapping *av_spherical_alloc(size_t *ಗಾತ್ರ_2)
{
    AVSphericalMapping *spherical = av_mallocz(ಗಾತ್ರ(AVSphericalMapping));

    ಆದರೆ (ಗಾತ್ರ_2)
        *ಗಾತ್ರ_2 = spherical ? ಗಾತ್ರ(*spherical) : 0;

    ಆದರೆ (!spherical)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    spherical->projection = AV_SPHERICAL_RECTILINEAR;

    ಹಿಂತಿರುಗಿ spherical;
}

ಶೂನ್ಯ av_spherical_tile_bounds(ಸ್ಥಿರಾಂಕ AVSphericalMapping *map,
                              size_t ಅಗಲ, size_t ಎತ್ತರ,
                              size_t *ಎಡ, size_t *ತುದಿ,
                              size_t *ಬಲ, size_t *bottom)
{
    /* conversion from 0.32 coordinates to pixels */
    uint64_t orig_ಅಗಲ  = (uint64_t) ಅಗಲ  * UINT32_MAX /
                           (UINT32_MAX - map->bound_ಬಲ  - map->bound_ಎಡ);
    uint64_t orig_ಎತ್ತರ = (uint64_t) ಎತ್ತರ * UINT32_MAX /
                           (UINT32_MAX - map->bound_bottom - map->bound_ತುದಿ);

    /* add a (UINT32_MAX - 1) to round up integer division */
    *ಎಡ   = (orig_ಅಗಲ  * map->bound_ಎಡ + UINT32_MAX - 1) / UINT32_MAX;
    *ತುದಿ    = (orig_ಎತ್ತರ * map->bound_ತುದಿ  + UINT32_MAX - 1) / UINT32_MAX;
    *ಬಲ  = orig_ಅಗಲ  - ಅಗಲ  - *ಎಡ;
    *bottom = orig_ಎತ್ತರ - ಎತ್ತರ - *ತುದಿ;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ spherical_projection_ಹೆಸರುಗಳು[] = {
    [AV_SPHERICAL_EQUIRECTANGULAR]      = "equirectangular",
    [AV_SPHERICAL_CUBEMAP]              = "cubemap",
    [AV_SPHERICAL_EQUIRECTANGULAR_TILE] = "tiled equirectangular",
    [AV_SPHERICAL_HALF_EQUIRECTANGULAR] = "half equirectangular",
    [AV_SPHERICAL_RECTILINEAR]          = "rectilinear",
    [AV_SPHERICAL_FISHEYE]              = "fisheye",
    [AV_SPHERICAL_PARAMETRIC_IMMERSIVE] = "parametric immersive",
};

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_spherical_projection_name(ಎಣಿಕೆ AVSphericalProjection projection)
{
    ಆದರೆ ((ಚಿಹ್ನೆರಹಿತ)projection >= FF_ARRAY_ELEMS(spherical_projection_ಹೆಸರುಗಳು))
        ಹಿಂತಿರುಗಿ "unknown";

    ಹಿಂತಿರುಗಿ spherical_projection_ಹೆಸರುಗಳು[projection];
}

ಪೂರ್ಣಾಂಕ av_spherical_from_name(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(spherical_projection_ಹೆಸರುಗಳು); i++) {
        ಆದರೆ (av_strstart(name, spherical_projection_ಹೆಸರುಗಳು[i], ಖಾಲಿ))
            ಹಿಂತಿರುಗಿ i;
    }

    ಹಿಂತಿರುಗಿ -1;
}
