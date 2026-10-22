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

#অন্তর্ভাব "avstring.h"
#অন্তর্ভাব "macros.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "spherical.h"

AVSphericalMapping *av_spherical_alloc(size_t *আকার_2)
{
    AVSphericalMapping *spherical = av_mallocz(আকার(AVSphericalMapping));

    যদি (আকার_2)
        *আকার_2 = spherical ? আকার(*spherical) : 0;

    যদি (!spherical)
        ফেরত ফাঁকা;

    spherical->projection = AV_SPHERICAL_RECTILINEAR;

    ফেরত spherical;
}

শূন্য av_spherical_tile_bounds(ধ্রুবক AVSphericalMapping *map,
                              size_t width, size_t height,
                              size_t *বাম, size_t *শীর্ষ,
                              size_t *ডান, size_t *bottom)
{
    /* conversion from 0.32 coordinates to pixels */
    uint64_t orig_width  = (uint64_t) width  * UINT32_MAX /
                           (UINT32_MAX - map->bound_ডান  - map->bound_বাম);
    uint64_t orig_height = (uint64_t) height * UINT32_MAX /
                           (UINT32_MAX - map->bound_bottom - map->bound_শীর্ষ);

    /* add a (UINT32_MAX - 1) to round up integer division */
    *বাম   = (orig_width  * map->bound_বাম + UINT32_MAX - 1) / UINT32_MAX;
    *শীর্ষ    = (orig_height * map->bound_শীর্ষ  + UINT32_MAX - 1) / UINT32_MAX;
    *ডান  = orig_width  - width  - *বাম;
    *bottom = orig_height - height - *শীর্ষ;
}

স্থির ধ্রুবক অক্ষর *ধ্রুবক spherical_projection_names[] = {
    [AV_SPHERICAL_EQUIRECTANGULAR]      = "equirectangular",
    [AV_SPHERICAL_CUBEMAP]              = "cubemap",
    [AV_SPHERICAL_EQUIRECTANGULAR_TILE] = "tiled equirectangular",
    [AV_SPHERICAL_HALF_EQUIRECTANGULAR] = "half equirectangular",
    [AV_SPHERICAL_RECTILINEAR]          = "rectilinear",
    [AV_SPHERICAL_FISHEYE]              = "fisheye",
    [AV_SPHERICAL_PARAMETRIC_IMMERSIVE] = "parametric immersive",
};

ধ্রুবক অক্ষর *av_spherical_projection_name(গণনা AVSphericalProjection projection)
{
    যদি ((unsigned)projection >= FF_ARRAY_ELEMS(spherical_projection_names))
        ফেরত "unknown";

    ফেরত spherical_projection_names[projection];
}

পূর্ণসংখ্যা av_spherical_from_name(ধ্রুবক অক্ষর *name)
{
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < FF_ARRAY_ELEMS(spherical_projection_names); i++) {
        যদি (av_strstart(name, spherical_projection_names[i], ফাঁকা))
            ফেরত i;
    }

    ফেরত -1;
}
