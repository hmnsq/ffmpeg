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

AVSphericalMapping *av_spherical_alloc(size_t *اندازه)
{
    AVSphericalMapping *spherical = av_mallocz(حجم(AVSphericalMapping));

    إذا (اندازه)
        *اندازه = spherical ? حجم(*spherical) : 0;

    إذا (!spherical)
        أرجع عدم;

    spherical->projection = AV_SPHERICAL_RECTILINEAR;

    أرجع spherical;
}

فراغ av_spherical_tile_bounds(ثابت AVSphericalMapping *map,
                              size_t عرض, size_t ارتفاع,
                              size_t *چپ, size_t *بالاترین,
                              size_t *راست, size_t *bottom)
{
    /* conversion from 0.32 coordinates to pixels */
    uint64_t orig_عرض  = (uint64_t) عرض  * UINT32_MAX /
                           (UINT32_MAX - map->bound_راست  - map->bound_چپ);
    uint64_t orig_ارتفاع = (uint64_t) ارتفاع * UINT32_MAX /
                           (UINT32_MAX - map->bound_bottom - map->bound_بالاترین);

    /* add a (UINT32_MAX - 1) to round up integer division */
    *چپ   = (orig_عرض  * map->bound_چپ + UINT32_MAX - 1) / UINT32_MAX;
    *بالاترین    = (orig_ارتفاع * map->bound_بالاترین  + UINT32_MAX - 1) / UINT32_MAX;
    *راست  = orig_عرض  - عرض  - *چپ;
    *bottom = orig_ارتفاع - ارتفاع - *بالاترین;
}

ساكن ثابت حرف *ثابت spherical_projection_نامها[] = {
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
    إذا ((بیعلامت)projection >= FF_ARRAY_ELEMS(spherical_projection_نامها))
        أرجع "unknown";

    أرجع spherical_projection_نامها[projection];
}

صحيح av_spherical_from_name(ثابت حرف *name)
{
    صحيح i;

    لكل (i = 0; i < FF_ARRAY_ELEMS(spherical_projection_نامها); i++) {
        إذا (av_strstart(name, spherical_projection_نامها[i], عدم))
            أرجع i;
    }

    أرجع -1;
}
