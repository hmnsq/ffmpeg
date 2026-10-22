/*
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

/**
 * @file
 * @ingroup lavu_video_3d_reference_displays_info
 * Spherical video
 */

#నిర్వచితం_కాకపోతే AVUTIL_TDRDI_H
#నిర్వచించు AVUTIL_TDRDI_H

#అన్తర్భావ <stddef.h>
#అన్తర్భావ <stdint.h>

#అన్తర్భావ "libavutil/avassert.h"

/**
 * @defgroup lavu_video_3d_reference_displays_info 3D Reference Displays Information
 * @ingroup lavu_video
 *
 * The 3D Reference Displays Information describes information about the reference display
 * width(s) and reference viewing distance(s) as well as information about the corresponding
 * reference stereo pair(s).
 * @{
 */

#నిర్వచించు AV_TDRDI_MAX_అంకె_REF_DISPLAY 32

/**
 * This structure describes information about the reference display width(s) and reference
 * viewing distance(s) as well as information about the corresponding reference stereo pair(s).
 * See section G.14.3.2.3 of ITU-T H.265 for more information.
 *
 * @note The struct must be allocated with av_tdrdi_alloc() and
 *       its size is not a part of the public ABI.
 */
రకనిర్వచనం నిర్మాణం AV3DReferenceDisplaysInfo {
    /**
     * The exponent of the maximum allowable truncation error for
     * {exponent,mantissa}_ref_display_width as given by 2<sup>(-prec_ref_display_width)</sup>.
     */
    uint8_t prec_ref_display_వెడల్పు;

    /**
     * A flag to indicate the presence of reference viewing distance.
     * If false, the values of prec_ref_viewing_dist, exponent_ref_viewing_distance,
     * and mantissa_ref_viewing_distance are undefined.
     */
    uint8_t ref_viewing_దూరం_flag;

    /**
     * The exponent of the maximum allowable truncation error for
     * {exponent,mantissa}_ref_viewing_distance as given by 2<sup>^(-prec_ref_viewing_dist)</sup>.
     * The value of prec_ref_viewing_dist shall be in the range of 0 to 31, inclusive.
     */
    uint8_t prec_ref_viewing_dist;

    /**
     * The number of reference displays that are signalled in this struct.
     * Allowed range is 1 to 32, inclusive.
     */
    uint8_t అంకె_ref_displays;

    /**
     * Offset in bytes from the beginning of this structure at which the array
     * of reference displays starts.
     */
    size_t entries_స్థానభ్రంశం;

    /**
     * Size of each entry in bytes. May not match sizeof(AV3DReferenceDisplay).
     */
    size_t నమోదు_కొలత;
} AV3DReferenceDisplaysInfo;

/**
 * Data structure for single deference display information.
 * It is allocated as a part of AV3DReferenceDisplaysInfo and should be retrieved with
 * av_tdrdi_get_display().
 *
 * sizeof(AV3DReferenceDisplay) is not a part of the ABI and new fields may be
 * added to it.
*/
రకనిర్వచనం నిర్మాణం AV3DReferenceDisplay {
    /**
     * The ViewId of the left view of a stereo pair corresponding to the n-th reference display.
     */
    uint16_t ఎడమ_view_id;

    /**
     * The ViewId of the left view of a stereo pair corresponding to the n-th reference display.
     */
    uint16_t కుడి_view_id;

    /**
     * The exponent part of the reference display width of the n-th reference display.
     */
    uint8_t exponent_ref_display_వెడల్పు;

    /**
     * The mantissa part of the reference display width of the n-th reference display.
     */
    uint8_t mantissa_ref_display_వెడల్పు;

    /**
     * The exponent part of the reference viewing distance of the n-th reference display.
     */
    uint8_t exponent_ref_viewing_దూరం;

    /**
     * The mantissa part of the reference viewing distance of the n-th reference display.
     */
    uint8_t mantissa_ref_viewing_దూరం;

    /**
     * An array of flags to indicates that the information about additional horizontal shift of
     * the left and right views for the n-th reference display is present.
     */
    uint8_t additional_జరుపు_present_flag;

    /**
     * The recommended additional horizontal shift for a stereo pair corresponding to the n-th
     * reference baseline and the n-th reference display.
     */
    int16_t అంకె_sample_జరుపు;
} AV3DReferenceDisplay;

స్థిర av_always_inline AV3DReferenceDisplay*
av_tdrdi_get_display(AV3DReferenceDisplaysInfo *tdrdi, గుర్తులేని పూర్ణాంకం idx)
{
    av_assert0(idx < tdrdi->అంకె_ref_displays);
    తిరిగి (AV3DReferenceDisplay *)((uint8_t *)tdrdi + tdrdi->entries_స్థానభ్రంశం +
                                    idx * tdrdi->నమోదు_కొలత);
}

/**
 * Allocate a AV3DReferenceDisplaysInfo structure and initialize its fields to default
 * values.
 *
 * @return the newly allocated struct or NULL on failure
 */
AV3DReferenceDisplaysInfo *av_tdrdi_alloc(గుర్తులేని పూర్ణాంకం nb_displays, size_t *కొలత);

/**
 * @}
 */

#అయితే_ముగింపు /* AVUTIL_TDRDI_H */
