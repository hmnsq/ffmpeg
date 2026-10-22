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

#ضمن "avstring.h"
#ضمن "macros.h"
#ضمن "mem.h"
#ضمن "spherical.h"

AVSphericalMapping *av_spherical_alloc(size_t *سائيز)
{
    AVSphericalMapping *spherical = av_mallocz(حجم(AVSphericalMapping));

    إذا (سائيز)
        *سائيز = spherical ? حجم(*spherical) : 0;

    إذا (!spherical)
        أرجع عدم;

    spherical->projection = AV_SPHERICAL_RECTILINEAR;

    أرجع spherical;
}

فراغ av_spherical_tile_bounds(ثابت AVSphericalMapping *map,
                              size_t ويڪر, size_t اوچائي,
                              size_t *کاٻو, size_t *چوٽي,
                              size_t *ساڄو, size_t *bottom)
{
    /* conversion from 0.32 coordinates to pixels */
    uint64_t orig_ويڪر  = (uint64_t) ويڪر  * UINT32_MAX /
                           (UINT32_MAX - map->bound_ساڄو  - map->bound_کاٻو);
    uint64_t orig_اوچائي = (uint64_t) اوچائي * UINT32_MAX /
                           (UINT32_MAX - map->bound_bottom - map->bound_چوٽي);

    /* add a (UINT32_MAX - 1) to round up integer division */
    *کاٻو   = (orig_ويڪر  * map->bound_کاٻو + UINT32_MAX - 1) / UINT32_MAX;
    *چوٽي    = (orig_اوچائي * map->bound_چوٽي  + UINT32_MAX - 1) / UINT32_MAX;
    *ساڄو  = orig_ويڪر  - ويڪر  - *کاٻو;
    *bottom = orig_اوچائي - اوچائي - *چوٽي;
}

ساكن ثابت حرف *ثابت spherical_projection_نالا[] = {
    [AV_SPHERICAL_EQUIRECTANGULAR]      = "equirectangular",
    [AV_SPHERICAL_CUBEMAP]              = "cubemap",
    [AV_SPHERICAL_EQUIRECTANGULAR_TILE] = "tiled equirectangular",
    [AV_SPHERICAL_HALF_EQUIRECTANGULAR] = "half equirectangular",
    [AV_SPHERICAL_RECTILINEAR]          = "rectilinear",
    [AV_SPHERICAL_FISHEYE]              = "fisheye",
    [AV_SPHERICAL_PARAMETRIC_IMMERSIVE] = "parametric immersive",
};

ثابت حرف *av_spherical_projection_name(تعداد AVSphericalProjection projection)
{
    إذا ((بنانشان)projection >= FF_ARRAY_ELEMS(spherical_projection_نالا))
        أرجع "unknown";

    أرجع spherical_projection_نالا[projection];
}

صحيح av_spherical_from_name(ثابت حرف *name)
{
    صحيح i;

    لكل (i = 0; i < FF_ARRAY_ELEMS(spherical_projection_نالا); i++) {
        إذا (av_strstart(name, spherical_projection_نالا[i], عدم))
            أرجع i;
    }

    أرجع -1;
}
