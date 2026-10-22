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

#അന്തര്ഭാവ "avstring.h"
#അന്തര്ഭാവ "macros.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "spherical.h"

AVSphericalMapping *av_spherical_alloc(size_t *size)
{
    AVSphericalMapping *spherical = av_mallocz(വലുപ്പം(AVSphericalMapping));

    എങ്കിൽ (size)
        *size = spherical ? വലുപ്പം(*spherical) : 0;

    എങ്കിൽ (!spherical)
        തിരികെ ശൂന്യ;

    spherical->projection = AV_SPHERICAL_RECTILINEAR;

    തിരികെ spherical;
}

ശൂന്യം av_spherical_tile_bounds(സ്ഥിരം AVSphericalMapping *map,
                              size_t width, size_t height,
                              size_t *ഇടത്, size_t *മുകൾ,
                              size_t *വലത്, size_t *bottom)
{
    /* conversion from 0.32 coordinates to pixels */
    uint64_t orig_width  = (uint64_t) width  * UINT32_MAX /
                           (UINT32_MAX - map->bound_വലത്  - map->bound_ഇടത്);
    uint64_t orig_height = (uint64_t) height * UINT32_MAX /
                           (UINT32_MAX - map->bound_bottom - map->bound_മുകൾ);

    /* add a (UINT32_MAX - 1) to round up integer division */
    *ഇടത്   = (orig_width  * map->bound_ഇടത് + UINT32_MAX - 1) / UINT32_MAX;
    *മുകൾ    = (orig_height * map->bound_മുകൾ  + UINT32_MAX - 1) / UINT32_MAX;
    *വലത്  = orig_width  - width  - *ഇടത്;
    *bottom = orig_height - height - *മുകൾ;
}

സ്ഥിതം സ്ഥിരം അക്ഷരം *സ്ഥിരം spherical_projection_names[] = {
    [AV_SPHERICAL_EQUIRECTANGULAR]      = "equirectangular",
    [AV_SPHERICAL_CUBEMAP]              = "cubemap",
    [AV_SPHERICAL_EQUIRECTANGULAR_TILE] = "tiled equirectangular",
    [AV_SPHERICAL_HALF_EQUIRECTANGULAR] = "half equirectangular",
    [AV_SPHERICAL_RECTILINEAR]          = "rectilinear",
    [AV_SPHERICAL_FISHEYE]              = "fisheye",
    [AV_SPHERICAL_PARAMETRIC_IMMERSIVE] = "parametric immersive",
};

സ്ഥിരം അക്ഷരം *av_spherical_projection_name(എണ്ണൽ AVSphericalProjection projection)
{
    എങ്കിൽ ((unsigned)projection >= FF_ARRAY_ELEMS(spherical_projection_names))
        തിരികെ "unknown";

    തിരികെ spherical_projection_names[projection];
}

പൂർണ്ണസംഖ്യ av_spherical_from_name(സ്ഥിരം അക്ഷരം *name)
{
    പൂർണ്ണസംഖ്യ i;

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(spherical_projection_names); i++) {
        എങ്കിൽ (av_strstart(name, spherical_projection_names[i], ശൂന്യ))
            തിരികെ i;
    }

    തിരികെ -1;
}
