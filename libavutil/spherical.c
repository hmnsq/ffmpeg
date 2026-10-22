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

#अन्तर्भाव "avstring.h"
#अन्तर्भाव "macros.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "spherical.h"

AVSphericalMapping *av_spherical_alloc(size_t *आकार)
{
    AVSphericalMapping *spherical = av_mallocz(परिमाण(AVSphericalMapping));

    यदि (आकार)
        *आकार = spherical ? परिमाण(*spherical) : 0;

    यदि (!spherical)
        प्रत्यागम रिक्त;

    spherical->projection = AV_SPHERICAL_RECTILINEAR;

    प्रत्यागम spherical;
}

शून्य av_spherical_tile_bounds(ध्रुव AVSphericalMapping *map,
                              size_t विस्तारः, size_t height,
                              size_t *वामः, size_t *शिखरम्,
                              size_t *दक्षिणः, size_t *bottom)
{
    /* conversion from 0.32 coordinates to pixels */
    uint64_t orig_विस्तारः  = (uint64_t) विस्तारः  * UINT32_MAX /
                           (UINT32_MAX - map->bound_दक्षिणः  - map->bound_वामः);
    uint64_t orig_height = (uint64_t) height * UINT32_MAX /
                           (UINT32_MAX - map->bound_bottom - map->bound_शिखरम्);

    /* add a (UINT32_MAX - 1) to round up integer division */
    *वामः   = (orig_विस्तारः  * map->bound_वामः + UINT32_MAX - 1) / UINT32_MAX;
    *शिखरम्    = (orig_height * map->bound_शिखरम्  + UINT32_MAX - 1) / UINT32_MAX;
    *दक्षिणः  = orig_विस्तारः  - विस्तारः  - *वामः;
    *bottom = orig_height - height - *शिखरम्;
}

स्थिर ध्रुव वर्ण *ध्रुव spherical_projection_नामानि[] = {
    [AV_SPHERICAL_EQUIRECTANGULAR]      = "equirectangular",
    [AV_SPHERICAL_CUBEMAP]              = "cubemap",
    [AV_SPHERICAL_EQUIRECTANGULAR_TILE] = "tiled equirectangular",
    [AV_SPHERICAL_HALF_EQUIRECTANGULAR] = "half equirectangular",
    [AV_SPHERICAL_RECTILINEAR]          = "rectilinear",
    [AV_SPHERICAL_FISHEYE]              = "fisheye",
    [AV_SPHERICAL_PARAMETRIC_IMMERSIVE] = "parametric immersive",
};

ध्रुव वर्ण *av_spherical_projection_name(गणना AVSphericalProjection projection)
{
    यदि ((अचिह्नित)projection >= FF_ARRAY_ELEMS(spherical_projection_नामानि))
        प्रत्यागम "unknown";

    प्रत्यागम spherical_projection_नामानि[projection];
}

पूर्णाङ्क av_spherical_from_name(ध्रुव वर्ण *name)
{
    पूर्णाङ्क i;

    प्रति (i = 0; i < FF_ARRAY_ELEMS(spherical_projection_नामानि); i++) {
        यदि (av_strstart(name, spherical_projection_नामानि[i], रिक्त))
            प्रत्यागम i;
    }

    प्रत्यागम -1;
}
