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

AVSphericalMapping *av_spherical_alloc(size_t *size)
{
    AVSphericalMapping *spherical = av_mallocz(حجم(AVSphericalMapping));

    إذا (size)
        *size = spherical ? حجم(*spherical) : 0;

    إذا (!spherical)
        أرجع عدم;

    spherical->projection = AV_SPHERICAL_RECTILINEAR;

    أرجع spherical;
}

فراغ av_spherical_tile_bounds(ثابت AVSphericalMapping *map,
                              size_t width, size_t height,
                              size_t *بایاں, size_t *چوٹی,
                              size_t *دایاں, size_t *bottom)
{
    /* conversion from 0.32 coordinates to pixels */
    uint64_t orig_width  = (uint64_t) width  * UINT32_MAX /
                           (UINT32_MAX - map->bound_دایاں  - map->bound_بایاں);
    uint64_t orig_height = (uint64_t) height * UINT32_MAX /
                           (UINT32_MAX - map->bound_bottom - map->bound_چوٹی);

    /* add a (UINT32_MAX - 1) to round up integer division */
    *بایاں   = (orig_width  * map->bound_بایاں + UINT32_MAX - 1) / UINT32_MAX;
    *چوٹی    = (orig_height * map->bound_چوٹی  + UINT32_MAX - 1) / UINT32_MAX;
    *دایاں  = orig_width  - width  - *بایاں;
    *bottom = orig_height - height - *چوٹی;
}

ساكن ثابت حرف *ثابت spherical_projection_names[] = {
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
    إذا ((unsigned)projection >= FF_ARRAY_ELEMS(spherical_projection_names))
        أرجع "unknown";

    أرجع spherical_projection_names[projection];
}

صحيح av_spherical_from_name(ثابت حرف *name)
{
    صحيح i;

    لكل (i = 0; i < FF_ARRAY_ELEMS(spherical_projection_names); i++) {
        إذا (av_strstart(name, spherical_projection_names[i], عدم))
            أرجع i;
    }

    أرجع -1;
}
