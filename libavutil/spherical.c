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

#అన్తర్భావ "avstring.h"
#అన్తర్భావ "macros.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "spherical.h"

AVSphericalMapping *av_spherical_alloc(size_t *కొలత)
{
    AVSphericalMapping *spherical = av_mallocz(పరిమాణం(AVSphericalMapping));

    ఒకవేళ (కొలత)
        *కొలత = spherical ? పరిమాణం(*spherical) : 0;

    ఒకవేళ (!spherical)
        తిరిగి ఖాళీ;

    spherical->projection = AV_SPHERICAL_RECTILINEAR;

    తిరిగి spherical;
}

శూన్య av_spherical_tile_bounds(స్థిరరాశి AVSphericalMapping *map,
                              size_t వెడల్పు, size_t ఎత్తు,
                              size_t *ఎడమ, size_t *శిఖరం,
                              size_t *కుడి, size_t *bottom)
{
    /* conversion from 0.32 coordinates to pixels */
    uint64_t orig_వెడల్పు  = (uint64_t) వెడల్పు  * UINT32_MAX /
                           (UINT32_MAX - map->bound_కుడి  - map->bound_ఎడమ);
    uint64_t orig_ఎత్తు = (uint64_t) ఎత్తు * UINT32_MAX /
                           (UINT32_MAX - map->bound_bottom - map->bound_శిఖరం);

    /* add a (UINT32_MAX - 1) to round up integer division */
    *ఎడమ   = (orig_వెడల్పు  * map->bound_ఎడమ + UINT32_MAX - 1) / UINT32_MAX;
    *శిఖరం    = (orig_ఎత్తు * map->bound_శిఖరం  + UINT32_MAX - 1) / UINT32_MAX;
    *కుడి  = orig_వెడల్పు  - వెడల్పు  - *ఎడమ;
    *bottom = orig_ఎత్తు - ఎత్తు - *శిఖరం;
}

స్థిర స్థిరరాశి అక్షరం *స్థిరరాశి spherical_projection_పేర్లు[] = {
    [AV_SPHERICAL_EQUIRECTANGULAR]      = "equirectangular",
    [AV_SPHERICAL_CUBEMAP]              = "cubemap",
    [AV_SPHERICAL_EQUIRECTANGULAR_TILE] = "tiled equirectangular",
    [AV_SPHERICAL_HALF_EQUIRECTANGULAR] = "half equirectangular",
    [AV_SPHERICAL_RECTILINEAR]          = "rectilinear",
    [AV_SPHERICAL_FISHEYE]              = "fisheye",
    [AV_SPHERICAL_PARAMETRIC_IMMERSIVE] = "parametric immersive",
};

స్థిరరాశి అక్షరం *av_spherical_projection_name(గణన AVSphericalProjection projection)
{
    ఒకవేళ ((గుర్తులేని)projection >= FF_ARRAY_ELEMS(spherical_projection_పేర్లు))
        తిరిగి "unknown";

    తిరిగి spherical_projection_పేర్లు[projection];
}

పూర్ణాంకం av_spherical_from_name(స్థిరరాశి అక్షరం *name)
{
    పూర్ణాంకం i;

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(spherical_projection_పేర్లు); i++) {
        ఒకవేళ (av_strstart(name, spherical_projection_పేర్లు[i], ఖాళీ))
            తిరిగి i;
    }

    తిరిగి -1;
}
