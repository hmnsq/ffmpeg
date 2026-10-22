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

#شامل "avstring.h"
#شامل "macros.h"
#شامل "mem.h"
#شامل "spherical.h"

AVSphericalMapping *av_spherical_alloc(size_t *size)
{
    AVSphericalMapping *spherical = av_mallocz(اندازه(AVSphericalMapping));

    اگر (size)
        *size = spherical ? اندازه(*spherical) : 0;

    اگر (!spherical)
        بازگشت پوچ;

    spherical->projection = AV_SPHERICAL_RECTILINEAR;

    بازگشت spherical;
}

تهی av_spherical_tile_bounds(ثابت AVSphericalMapping *map,
                              size_t width, size_t height,
                              size_t *چپ, size_t *بالاترین,
                              size_t *راست, size_t *bottom)
{
    /* conversion from 0.32 coordinates to pixels */
    uint64_t orig_width  = (uint64_t) width  * UINT32_MAX /
                           (UINT32_MAX - map->bound_راست  - map->bound_چپ);
    uint64_t orig_height = (uint64_t) height * UINT32_MAX /
                           (UINT32_MAX - map->bound_bottom - map->bound_بالاترین);

    /* add a (UINT32_MAX - 1) to round up integer division */
    *چپ   = (orig_width  * map->bound_چپ + UINT32_MAX - 1) / UINT32_MAX;
    *بالاترین    = (orig_height * map->bound_بالاترین  + UINT32_MAX - 1) / UINT32_MAX;
    *راست  = orig_width  - width  - *چپ;
    *bottom = orig_height - height - *بالاترین;
}

ایستا ثابت نویسه *ثابت spherical_projection_names[] = {
    [AV_SPHERICAL_EQUIRECTANGULAR]      = "equirectangular",
    [AV_SPHERICAL_CUBEMAP]              = "cubemap",
    [AV_SPHERICAL_EQUIRECTANGULAR_TILE] = "tiled equirectangular",
    [AV_SPHERICAL_HALF_EQUIRECTANGULAR] = "half equirectangular",
    [AV_SPHERICAL_RECTILINEAR]          = "rectilinear",
    [AV_SPHERICAL_FISHEYE]              = "fisheye",
    [AV_SPHERICAL_PARAMETRIC_IMMERSIVE] = "parametric immersive",
};

ثابت نویسه *av_spherical_projection_name(شمارش AVSphericalProjection projection)
{
    اگر ((unsigned)projection >= FF_ARRAY_ELEMS(spherical_projection_names))
        بازگشت "unknown";

    بازگشت spherical_projection_names[projection];
}

صحیح av_spherical_from_name(ثابت نویسه *name)
{
    صحیح i;

    برای (i = 0; i < FF_ARRAY_ELEMS(spherical_projection_names); i++) {
        اگر (av_strstart(name, spherical_projection_names[i], پوچ))
            بازگشت i;
    }

    بازگشت -1;
}
