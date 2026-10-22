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

#ଅନ୍ତର୍ଭାଵ "avstring.h"
#ଅନ୍ତର୍ଭାଵ "macros.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "spherical.h"

AVSphericalMapping *av_spherical_alloc(size_t *size)
{
    AVSphericalMapping *spherical = av_mallocz(ଆକାର(AVSphericalMapping));

    ଯଦି (size)
        *size = spherical ? ଆକାର(*spherical) : 0;

    ଯଦି (!spherical)
        ଫେରନ୍ତୁ ଖାଲି;

    spherical->projection = AV_SPHERICAL_RECTILINEAR;

    ଫେରନ୍ତୁ spherical;
}

ଶୂନ୍ୟ av_spherical_tile_bounds(ଅଚଳ AVSphericalMapping *map,
                              size_t width, size_t height,
                              size_t *ବାମ, size_t *ଶୀର୍ଷ,
                              size_t *ଡାହାଣ, size_t *bottom)
{
    /* conversion from 0.32 coordinates to pixels */
    uint64_t orig_width  = (uint64_t) width  * UINT32_MAX /
                           (UINT32_MAX - map->bound_ଡାହାଣ  - map->bound_ବାମ);
    uint64_t orig_height = (uint64_t) height * UINT32_MAX /
                           (UINT32_MAX - map->bound_bottom - map->bound_ଶୀର୍ଷ);

    /* add a (UINT32_MAX - 1) to round up integer division */
    *ବାମ   = (orig_width  * map->bound_ବାମ + UINT32_MAX - 1) / UINT32_MAX;
    *ଶୀର୍ଷ    = (orig_height * map->bound_ଶୀର୍ଷ  + UINT32_MAX - 1) / UINT32_MAX;
    *ଡାହାଣ  = orig_width  - width  - *ବାମ;
    *bottom = orig_height - height - *ଶୀର୍ଷ;
}

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *ଅଚଳ spherical_projection_names[] = {
    [AV_SPHERICAL_EQUIRECTANGULAR]      = "equirectangular",
    [AV_SPHERICAL_CUBEMAP]              = "cubemap",
    [AV_SPHERICAL_EQUIRECTANGULAR_TILE] = "tiled equirectangular",
    [AV_SPHERICAL_HALF_EQUIRECTANGULAR] = "half equirectangular",
    [AV_SPHERICAL_RECTILINEAR]          = "rectilinear",
    [AV_SPHERICAL_FISHEYE]              = "fisheye",
    [AV_SPHERICAL_PARAMETRIC_IMMERSIVE] = "parametric immersive",
};

ଅଚଳ ଅକ୍ଷର *av_spherical_projection_name(ଗଣନା AVSphericalProjection projection)
{
    ଯଦି ((unsigned)projection >= FF_ARRAY_ELEMS(spherical_projection_names))
        ଫେରନ୍ତୁ "unknown";

    ଫେରନ୍ତୁ spherical_projection_names[projection];
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_spherical_from_name(ଅଚଳ ଅକ୍ଷର *name)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(spherical_projection_names); i++) {
        ଯଦି (av_strstart(name, spherical_projection_names[i], ଖାଲି))
            ଫେରନ୍ତୁ i;
    }

    ଫେରନ୍ତୁ -1;
}
