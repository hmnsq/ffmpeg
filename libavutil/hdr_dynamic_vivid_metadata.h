/*
 * Copyright (c) 2021 Limin Wang <lance.lmwang at gmail.com>
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

#నిర్వచితం_కాకపోతే AVUTIL_HDR_DYNAMIC_VIVID_METADATA_H
#నిర్వచించు AVUTIL_HDR_DYNAMIC_VIVID_METADATA_H

#అన్తర్భావ "frame.h"
#అన్తర్భావ "rational.h"

/**
 * HDR Vivid three spline params.
 */
రకనిర్వచనం నిర్మాణం AVHDRVivid3SplineParams {
    /**
     * The mode of three Spline. the value shall be in the range
     * of 0 to 3, inclusive.
     */
    పూర్ణాంకం th_బహుళకం;

    /**
     * three_Spline_TH_enable_MB is in the range of 0.0 to 1.0, inclusive
     * and in multiples of 1.0/255.
     *
     */
    AVRational th_enable_mb;

    /**
     * 3Spline_TH_enable of three Spline.
     * The value shall be in the range of 0.0 to 1.0, inclusive.
     * and in multiples of 1.0/4095.
     */
    AVRational th_enable;

    /**
     * 3Spline_TH_Delta1 of three Spline.
     * The value shall be in the range of 0.0 to 0.25, inclusive,
     * and in multiples of 0.25/1023.
     */
    AVRational th_delta1;

    /**
     * 3Spline_TH_Delta2 of three Spline.
     * The value shall be in the range of 0.0 to 0.25, inclusive,
     * and in multiples of 0.25/1023.
     */
    AVRational th_delta2;

    /**
     * 3Spline_enable_Strength of three Spline.
     * The value shall be in the range of 0.0 to 1.0, inclusive,
     * and in multiples of 1.0/255.
     */
    AVRational enable_strength;
} AVHDRVivid3SplineParams;

/**
 * Color tone mapping parameters at a processing window in a dynamic metadata for
 * CUVA 005.1:2021.
 */
రకనిర్వచనం నిర్మాణం AVHDRVividColorToneMappingParams {
    /**
     * The nominal maximum display luminance of the targeted system display,
     * in multiples of 1.0/4095 candelas per square metre. The value shall be in
     * the range of 0.0 to 1.0, inclusive.
     */
    AVRational targeted_system_display_గరిష్ఠ_luminance;

    /**
     * This flag indicates that transfer the base parameter(for value of 1)
     */
    పూర్ణాంకం పునాది_enable_flag;

    /**
     * base_param_m_p in the base parameter,
     * in multiples of 1.0/16383. The value shall be in
     * the range of 0.0 to 1.0, inclusive.
     */
    AVRational పునాది_param_m_p;

    /**
     * base_param_m_m in the base parameter,
     * in multiples of 1.0/10. The value shall be in
     * the range of 0.0 to 6.3, inclusive.
     */
    AVRational పునాది_param_m_m;

    /**
     * base_param_m_a in the base parameter,
     * in multiples of 1.0/1023. The value shall be in
     * the range of 0.0 to 1.0 inclusive.
     */
    AVRational పునాది_param_m_a;

    /**
     * base_param_m_b in the base parameter,
     * in multiples of 1/1023. The value shall be in
     * the range of 0.0 to 1.0, inclusive.
     */
    AVRational పునాది_param_m_b;

    /**
     * base_param_m_n in the base parameter,
     * in multiples of 1.0/10. The value shall be in
     * the range of 0.0 to 6.3, inclusive.
     */
    AVRational పునాది_param_m_n;

    /**
     * indicates k1_0 in the base parameter,
     * base_param_k1 <= 1: k1_0 = base_param_k1
     * base_param_k1 > 1: reserved
     */
    పూర్ణాంకం పునాది_param_k1;

    /**
     * indicates k2_0 in the base parameter,
     * base_param_k2 <= 1: k2_0 = base_param_k2
     * base_param_k2 > 1: reserved
     */
    పూర్ణాంకం పునాది_param_k2;

    /**
     * indicates k3_0 in the base parameter,
     * base_param_k3 == 1: k3_0 = base_param_k3
     * base_param_k3 == 2: k3_0 = maximum_maxrgb
     * base_param_k3 > 2: reserved
     */
    పూర్ణాంకం పునాది_param_k3;

    /**
     * This flag indicates that delta mode of base parameter(for value of 1)
     */
    పూర్ణాంకం పునాది_param_Delta_enable_బహుళకం;

    /**
     * base_param_Delta in the base parameter,
     * in multiples of 1.0/127. The value shall be in
     * the range of 0.0 to 1.0, inclusive.
     */
    AVRational పునాది_param_Delta;

    /**
     * indicates 3Spline_enable_flag in the base parameter,
     * This flag indicates that transfer three Spline of base parameter(for value of 1)
     */
    పూర్ణాంకం three_Spline_enable_flag;

    /**
     * The number of three Spline. The value shall be in the range
     * of 1 to 2, inclusive.
     */
    పూర్ణాంకం three_Spline_అంకె;

    AVHDRVivid3SplineParams three_spline[2];
} AVHDRVividColorToneMappingParams;


/**
 * Color transform parameters at a processing window in a dynamic metadata for
 * CUVA 005.1:2021.
 */
రకనిర్వచనం నిర్మాణం AVHDRVividColorTransformParams {
    /**
     * Indicates the minimum brightness of the displayed content.
     * The values should be in the range of 0.0 to 1.0,
     * inclusive and in multiples of 1/4095.
     */
    AVRational minimum_maxrgb;

    /**
     * Indicates the average brightness of the displayed content.
     * The values should be in the range of 0.0 to 1.0,
     * inclusive and in multiples of 1/4095.
     */
    AVRational సరాసరి_maxrgb;

    /**
     * Indicates the variance brightness of the displayed content.
     * The values should be in the range of 0.0 to 1.0,
     * inclusive and in multiples of 1/4095.
     */
    AVRational variance_maxrgb;

    /**
     * Indicates the maximum brightness of the displayed content.
     * The values should be in the range of 0.0 to 1.0, inclusive
     * and in multiples of 1/4095.
     */
    AVRational గరిష్ఠ_maxrgb;

    /**
     * This flag indicates that the metadata for the tone mapping function in
     * the processing window is present (for value of 1).
     */
    పూర్ణాంకం tone_mapping_బహుళకం_flag;

    /**
     * The number of tone mapping param. The value shall be in the range
     * of 1 to 2, inclusive.
     */
    పూర్ణాంకం tone_mapping_param_అంకె;

    /**
     * The color tone mapping parameters.
     */
    AVHDRVividColorToneMappingParams tm_params[2];

    /**
     * This flag indicates that the metadata for the color saturation mapping in
     * the processing window is present (for value of 1).
     */
    పూర్ణాంకం color_saturation_mapping_flag;

    /**
     * The number of color saturation param. The value shall be in the range
     * of 0 to 7, inclusive.
     */
    పూర్ణాంకం color_saturation_అంకె;

    /**
     * Indicates the color correction strength parameter.
     * The values should be in the range of 0.0 to 2.0, inclusive
     * and in multiples of 1/128.
     */
    AVRational color_saturation_gain[8];
} AVHDRVividColorTransformParams;

/**
 * This struct represents dynamic metadata for color volume transform -
 * CUVA 005.1:2021 standard
 *
 * To be used as payload of a AVFrameSideData or AVPacketSideData with the
 * appropriate type.
 *
 * @note The struct should be allocated with
 * av_dynamic_hdr_vivid_alloc() and its size is not a part of
 * the public ABI.
 */
రకనిర్వచనం నిర్మాణం AVDynamicHDRVivid {
    /**
     * The system start code. The value shall be set to 0x01.
     */
    uint8_t system_ప్రారంభం_సంకేతం;

    /**
     * The number of processing windows. The value shall be set to 0x01
     * if the system_start_code is 0x01.
     */
    uint8_t అంకె_windows;

    /**
     * The color transform parameters for every processing window.
     */
    AVHDRVividColorTransformParams params[3];
} AVDynamicHDRVivid;

/**
 * Allocate an AVDynamicHDRVivid structure and set its fields to
 * default values. The resulting struct can be freed using av_freep().
 *
 * @return An AVDynamicHDRVivid filled with default values or NULL
 *         on failure.
 */
AVDynamicHDRVivid *av_dynamic_hdr_vivid_alloc(size_t *కొలత);

/**
 * Allocate a complete AVDynamicHDRVivid and add it to the frame.
 * @param frame The frame which side data is added to.
 *
 * @return The AVDynamicHDRVivid structure to be filled by caller or NULL
 *         on failure.
 */
AVDynamicHDRVivid *av_dynamic_hdr_vivid_create_side_దత్తాంశం(AVFrame *చట్రం);

#అయితే_ముగింపు /* AVUTIL_HDR_DYNAMIC_VIVID_METADATA_H */
