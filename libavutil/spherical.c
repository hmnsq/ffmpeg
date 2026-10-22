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

#অন্তর্ভাৱ "avstring.h"
#অন্তর্ভাৱ "macros.h"
#অন্তর্ভাৱ "mem.h"
#অন্তর্ভাৱ "spherical.h"

AVSphericalMapping *av_spherical_alloc(size_t *size)
{
    AVSphericalMapping *spherical = av_mallocz(পরিমাণ(AVSphericalMapping));

    যদি (size)
        *size = spherical ? পরিমাণ(*spherical) : 0;

    যদি (!spherical)
        ঘূৰাই রিক্ত;

    spherical->projection = AV_SPHERICAL_RECTILINEAR;

    ঘূৰাই spherical;
}

শূন্য av_spherical_tile_bounds(ধ্রুৱ AVSphericalMapping *map,
                              size_t width, size_t height,
                              size_t *বাম, size_t *শীৰ্ষ,
                              size_t *ডান, size_t *bottom)
{
    /* conversion from 0.32 coordinates to pixels */
    uint64_t orig_width  = (uint64_t) width  * UINT32_MAX /
                           (UINT32_MAX - map->bound_ডান  - map->bound_বাম);
    uint64_t orig_height = (uint64_t) height * UINT32_MAX /
                           (UINT32_MAX - map->bound_bottom - map->bound_শীৰ্ষ);

    /* add a (UINT32_MAX - 1) to round up integer division */
    *বাম   = (orig_width  * map->bound_বাম + UINT32_MAX - 1) / UINT32_MAX;
    *শীৰ্ষ    = (orig_height * map->bound_শীৰ্ষ  + UINT32_MAX - 1) / UINT32_MAX;
    *ডান  = orig_width  - width  - *বাম;
    *bottom = orig_height - height - *শীৰ্ষ;
}

স্থির ধ্রুৱ ৱর্ণ *ধ্রুৱ spherical_projection_names[] = {
    [AV_SPHERICAL_EQUIRECTANGULAR]      = "equirectangular",
    [AV_SPHERICAL_CUBEMAP]              = "cubemap",
    [AV_SPHERICAL_EQUIRECTANGULAR_TILE] = "tiled equirectangular",
    [AV_SPHERICAL_HALF_EQUIRECTANGULAR] = "half equirectangular",
    [AV_SPHERICAL_RECTILINEAR]          = "rectilinear",
    [AV_SPHERICAL_FISHEYE]              = "fisheye",
    [AV_SPHERICAL_PARAMETRIC_IMMERSIVE] = "parametric immersive",
};

ধ্রুৱ ৱর্ণ *av_spherical_projection_name(গণনা AVSphericalProjection projection)
{
    যদি ((unsigned)projection >= FF_ARRAY_ELEMS(spherical_projection_names))
        ঘূৰাই "unknown";

    ঘূৰাই spherical_projection_names[projection];
}

পূর্ণাঙ্ক av_spherical_from_name(ধ্রুৱ ৱর্ণ *name)
{
    পূর্ণাঙ্ক i;

    বাবে (i = 0; i < FF_ARRAY_ELEMS(spherical_projection_names); i++) {
        যদি (av_strstart(name, spherical_projection_names[i], রিক্ত))
            ঘূৰাই i;
    }

    ঘূৰাই -1;
}
