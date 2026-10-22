/*
 * Copyright (c) 2020 Vacing Fang <vacingfang@tencent.com>
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

/**
 * @file
 * DOVI configuration
 */


#నిర్వచితం_కాకపోతే AVUTIL_DOVI_META_H
#నిర్వచించు AVUTIL_DOVI_META_H

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stddef.h>

#అన్తర్భావ "rational.h"
#అన్తర్భావ "csp.h"

/*
 * DOVI configuration
 * ref: dolby-vision-bitstreams-within-the-iso-base-media-file-format-v2.1.2
        dolby-vision-bitstreams-in-mpeg-2-transport-stream-multiplex-v1.2
 * @code
 * uint8_t  dv_version_major, the major version number that the stream complies with
 * uint8_t  dv_version_minor, the minor version number that the stream complies with
 * uint8_t  dv_profile, the Dolby Vision profile
 * uint8_t  dv_level, the Dolby Vision level
 * uint8_t  rpu_present_flag
 * uint8_t  el_present_flag
 * uint8_t  bl_present_flag
 * uint8_t  dv_bl_signal_compatibility_id
 * uint8_t  dv_md_compression, the compression method in use
 * @endcode
 *
 * @note The struct must be allocated with av_dovi_alloc() and
 *       its size is not a part of the public ABI.
 */
రకనిర్వచనం నిర్మాణం AVDOVIDecoder_Configuration_రికార్డు {
    uint8_t dv_సంస్కరణ_major;
    uint8_t dv_సంస్కరణ_minor;
    uint8_t dv_profile;
    uint8_t dv_level;
    uint8_t rpu_present_flag;
    uint8_t el_present_flag;
    uint8_t bl_present_flag;
    uint8_t dv_bl_signal_compatibility_id;
    uint8_t dv_md_compression;
} AVDOVIDecoder_Configuration_రికార్డు;

గణన AVDOVICompression {
    AV_DOVI_COMPRESSION_NONE     = 0,
    AV_DOVI_COMPRESSION_LIMITED  = 1,
    AV_DOVI_COMPRESSION_RESERVED = 2,
    AV_DOVI_COMPRESSION_EXTENDED = 3,
};

/**
 * Allocate a AVDOVIDecoderConfigurationRecord structure and initialize its
 * fields to default values.
 *
 * @return the newly allocated struct or NULL on failure
 */
AVDOVIDecoder_Configuration_రికార్డు *av_dovi_alloc(size_t *కొలత);

/**
 * Dolby Vision RPU data header.
 *
 * @note sizeof(AVDOVIRpuDataHeader) is not part of the public ABI.
 */
రకనిర్వచనం నిర్మాణం AVDOVIRpu_దత్తాంశం_శీర్షిక {
    uint8_t rpu_type;
    uint16_t rpu_format;
    uint8_t vdr_rpu_profile;
    uint8_t vdr_rpu_level;
    uint8_t chroma_resampling_explicit_filter_flag;
    uint8_t coef_దత్తాంశం_type; /* informative, lavc always converts to fixed */
    uint8_t coef_log2_denom;
    uint8_t vdr_rpu_normalized_idc;
    uint8_t bl_video_నిండిన_range_flag;
    uint8_t bl_బిట్టు_లోతు; /* [8, 16] */
    uint8_t el_బిట్టు_లోతు; /* [8, 16] */
    uint8_t vdr_బిట్టు_లోతు; /* [8, 16] */
    uint8_t spatial_resampling_filter_flag;
    uint8_t el_spatial_resampling_filter_flag;
    uint8_t disable_residual_flag;
    uint8_t ext_mapping_idc_0_4; /* extended base layer inverse mapping indicator */
    uint8_t ext_mapping_idc_5_7; /* reserved */
} AVDOVIRpu_దత్తాంశం_శీర్షిక;

గణన AVDOVIMapping_పద్ధతి {
    AV_DOVI_MAPPING_POLYNOMIAL = 0,
    AV_DOVI_MAPPING_MMR = 1,
};

/**
 * Coefficients of a piece-wise function. The pieces of the function span the
 * value ranges between two adjacent pivot values.
 */
#నిర్వచించు AV_DOVI_MAX_PIECES 8
రకనిర్వచనం నిర్మాణం AVDOVIReshaping_వక్రం {
    uint8_t అంకె_pivots;                         /* [2, 9] */
    uint16_t pivots[AV_DOVI_MAX_PIECES + 1];    /* sorted ascending */
    గణన AVDOVIMapping_పద్ధతి mapping_idc[AV_DOVI_MAX_PIECES];
    /* AV_DOVI_MAPPING_POLYNOMIAL */
    uint8_t poly_క్రమం[AV_DOVI_MAX_PIECES];     /* [1, 2] */
    int64_t poly_coef[AV_DOVI_MAX_PIECES][3];   /* x^0, x^1, x^2 */
    /* AV_DOVI_MAPPING_MMR */
    uint8_t mmr_క్రమం[AV_DOVI_MAX_PIECES];      /* [1, 3] */
    int64_t mmr_constant[AV_DOVI_MAX_PIECES];
    int64_t mmr_coef[AV_DOVI_MAX_PIECES][3/* order - 1 */][7];
} AVDOVIReshaping_వక్రం;

గణన AVDOVINLQMethod {
    AV_DOVI_NLQ_NONE = -1,
    AV_DOVI_NLQ_రేఖీయ_DZ = 0,
};

/**
 * Coefficients of the non-linear inverse quantization. For the interpretation
 * of these, see ETSI GS CCM 001.
 */
రకనిర్వచనం నిర్మాణం AVDOVINLQParams {
    uint16_t nlq_స్థానభ్రంశం;
    uint64_t vdr_లోపల_max;
    /* AV_DOVI_NLQ_LINEAR_DZ */
    uint64_t రేఖీయ_deadzone_వాలు;
    uint64_t రేఖీయ_deadzone_పరిమితి;
} AVDOVINLQParams;

/**
 * Dolby Vision RPU data mapping parameters.
 *
 * @note sizeof(AVDOVIDataMapping) is not part of the public ABI.
 */
రకనిర్వచనం నిర్మాణం AVDOVIDataMapping {
    uint8_t vdr_rpu_id;
    uint8_t mapping_color_space;
    uint8_t mapping_chroma_format_idc;
    AVDOVIReshaping_వక్రం curves[3]; /* per component */

    /* Non-linear inverse quantization */
    గణన AVDOVINLQMethod nlq_పద్ధతి_idc;
    uint32_t అంకె_x_partitions;
    uint32_t అంకె_y_partitions;
    AVDOVINLQParams nlq[3]; /* per component */
    uint16_t nlq_pivots[2];
} AVDOVIDataMapping;

/**
 * Dolby Vision RPU colorspace metadata parameters.
 *
 * @note sizeof(AVDOVIColorMetadata) is not part of the public ABI.
 */
రకనిర్వచనం నిర్మాణం AVDOVIColorMetadata {
    uint8_t dm_metadata_id;
    uint8_t scene_refresh_flag;

    /**
     * Coefficients of the custom Dolby Vision IPT-PQ matrices. These are to be
     * used instead of the matrices indicated by the frame's colorspace tags.
     * The output of rgb_to_lms_matrix is to be fed into a BT.2020 LMS->RGB
     * matrix based on a Hunt-Pointer-Estevez transform, but without any
     * crosstalk. (See the definition of the ICtCp colorspace for more
     * information.)
     */
    AVRational ycc_గమ్యం_rgb_మాతృక[9]; /* before PQ linearization */
    AVRational ycc_గమ్యం_rgb_స్థానభ్రంశం[3]; /* input offset of neutral value */
    AVRational rgb_గమ్యం_lms_మాతృక[9]; /* after PQ linearization */

    /**
     * Extra signal metadata (see Dolby patents for more info).
     */
    uint16_t signal_eotf;
    uint16_t signal_eotf_param0;
    uint16_t signal_eotf_param1;
    uint32_t signal_eotf_param2;
    uint8_t signal_బిట్టు_లోతు;
    uint8_t signal_color_space;
    uint8_t signal_chroma_format;
    uint8_t signal_నిండిన_range_flag; /* [0, 3] */
    uint16_t ఆధారం_min_pq;
    uint16_t ఆధారం_max_pq;
    uint16_t ఆధారం_diagonal;
} AVDOVIColorMetadata;

రకనిర్వచనం నిర్మాణం AVDOVIDmLevel1 {
    /* Per-frame brightness metadata */
    uint16_t min_pq;
    uint16_t max_pq;
    uint16_t avg_pq;
} AVDOVIDmLevel1;

రకనిర్వచనం నిర్మాణం AVDOVIDmLevel2 {
    /* Usually derived from level 8 (at different levels) */
    uint16_t లక్ష్యం_max_pq;
    uint16_t trim_వాలు;
    uint16_t trim_స్థానభ్రంశం;
    uint16_t trim_power;
    uint16_t trim_chroma_బరువు;
    uint16_t trim_saturation_gain;
    int16_t ms_బరువు;
} AVDOVIDmLevel2;

రకనిర్వచనం నిర్మాణం AVDOVIDmLevel3 {
    uint16_t min_pq_స్థానభ్రంశం;
    uint16_t max_pq_స్థానభ్రంశం;
    uint16_t avg_pq_స్థానభ్రంశం;
} AVDOVIDmLevel3;

రకనిర్వచనం నిర్మాణం AVDOVIDmLevel4 {
    uint16_t anchor_pq;
    uint16_t anchor_power;
} AVDOVIDmLevel4;

రకనిర్వచనం నిర్మాణం AVDOVIDmLevel5 {
    /* Active area definition */
    uint16_t ఎడమ_స్థానభ్రంశం;
    uint16_t కుడి_స్థానభ్రంశం;
    uint16_t శిఖరం_స్థానభ్రంశం;
    uint16_t bottom_స్థానభ్రంశం;
} AVDOVIDmLevel5;

రకనిర్వచనం నిర్మాణం AVDOVIDmLevel6 {
    /* Static HDR10 metadata */
    uint16_t max_luminance;
    uint16_t min_luminance;
    uint16_t max_cll;
    uint16_t max_fall;
} AVDOVIDmLevel6;

రకనిర్వచనం నిర్మాణం AVDOVIDmLevel8 {
    /* Extended version of level 2 */
    uint8_t లక్ష్యం_display_సూచీ;
    uint16_t trim_వాలు;
    uint16_t trim_స్థానభ్రంశం;
    uint16_t trim_power;
    uint16_t trim_chroma_బరువు;
    uint16_t trim_saturation_gain;
    uint16_t ms_బరువు;
    uint16_t లక్ష్యం_mid_contrast;
    uint16_t clip_trim;
    uint8_t saturation_సదిశ_క్షేత్రం[6];
    uint8_t hue_సదిశ_క్షేత్రం[6];
} AVDOVIDmLevel8;

రకనిర్వచనం నిర్మాణం AVDOVIDmLevel9 {
    /* Source display characteristics */
    uint8_t ఆధారం_primary_సూచీ;
    AVColorPrimariesDesc ఆధారం_display_primaries;
} AVDOVIDmLevel9;

రకనిర్వచనం నిర్మాణం AVDOVIDmLevel10 {
    /* Target display characteristics */
    uint8_t లక్ష్యం_display_సూచీ;
    uint16_t లక్ష్యం_max_pq;
    uint16_t లక్ష్యం_min_pq;
    uint8_t లక్ష్యం_primary_సూచీ;
    AVColorPrimariesDesc లక్ష్యం_display_primaries;
} AVDOVIDmLevel10;

రకనిర్వచనం నిర్మాణం AVDOVIDmLevel11 {
    uint8_t content_type;
    uint8_t whitepoint;
    uint8_t reference_బహుళకం_flag;
#ఒకవేళ FF_API_DOVI_L11_INVALID_PROPS
    attribute_deprecated
    uint8_t sharpness;
    attribute_deprecated
    uint8_t noise_reduction;
    attribute_deprecated
    uint8_t mpeg_noise_reduction;
    attribute_deprecated
    uint8_t చట్రం_రేటు_conversion;
    attribute_deprecated
    uint8_t brightness;
    attribute_deprecated
    uint8_t color;
#అయితే_ముగింపు
} AVDOVIDmLevel11;

రకనిర్వచనం నిర్మాణం AVDOVIDmLevel254 {
    /* DMv2 info block, always present in samples with DMv2 metadata */
    uint8_t dm_బహుళకం;
    uint8_t dm_సంస్కరణ_సూచీ;
} AVDOVIDmLevel254;

రకనిర్వచనం నిర్మాణం AVDOVIDmLevel255 {
    /* Debug block, not really used in samples */
    uint8_t dm_నిరంతరం_బహుళకం;
    uint8_t dm_నిరంతరం_సంస్కరణ;
    uint8_t dm_debug[4];
} AVDOVIDmLevel255;

/**
 * Dolby Vision metadata extension block. Dynamic extension blocks may change
 * from frame to frame, while static blocks are constant throughout the entire
 * sequence.
 *
 * @note sizeof(AVDOVIDmData) is not part of the public API.
 */
రకనిర్వచనం నిర్మాణం AVDOVIDm_దత్తాంశం {
    uint8_t level; /* [1, 255] */
    సంఘం {
        AVDOVIDmLevel1 l1; /* dynamic */
        AVDOVIDmLevel2 l2; /* dynamic, may appear multiple times */
        AVDOVIDmLevel3 l3; /* dynamic */
        AVDOVIDmLevel4 l4; /* dynamic */
        AVDOVIDmLevel5 l5; /* dynamic */
        AVDOVIDmLevel6 l6; /* static */
        /* level 7 is currently unused */
        AVDOVIDmLevel8 l8; /* dynamic, may appear multiple times */
        AVDOVIDmLevel9 l9; /* dynamic */
        AVDOVIDmLevel10 l10; /* static, may appear multiple times */
        AVDOVIDmLevel11 l11; /* dynamic */
        AVDOVIDmLevel254 l254; /* static */
        AVDOVIDmLevel255 l255; /* static */
    };
} AVDOVIDm_దత్తాంశం;

/**
 * Combined struct representing a combination of header, mapping and color
 * metadata, for attaching to frames as side data.
 *
 * @note The struct must be allocated with av_dovi_metadata_alloc() and
 *       its size is not a part of the public ABI.
 */

రకనిర్వచనం నిర్మాణం AVDOVIMetadata {
    /**
     * Offset in bytes from the beginning of this structure at which the
     * respective structs start.
     */
    size_t శీర్షిక_స్థానభ్రంశం;   /* AVDOVIRpuDataHeader */
    size_t mapping_స్థానభ్రంశం;  /* AVDOVIDataMapping */
    size_t color_స్థానభ్రంశం;    /* AVDOVIColorMetadata */

    size_t ext_ఖండం_స్థానభ్రంశం; /* offset to start of ext blocks array */
    size_t ext_ఖండం_కొలత; /* size per element */
    పూర్ణాంకం అంకె_ext_ఖండాలు; /* number of extension blocks */

    /* static limit on num_ext_blocks, derived from bitstream limitations */
#నిర్వచించు AV_DOVI_MAX_EXT_ఖండాలు 32
} AVDOVIMetadata;

స్థిర av_always_inline AVDOVIRpu_దత్తాంశం_శీర్షిక *
av_dovi_get_శీర్షిక(స్థిరరాశి AVDOVIMetadata *దత్తాంశం)
{
    తిరిగి (AVDOVIRpu_దత్తాంశం_శీర్షిక *)((uint8_t *) దత్తాంశం + దత్తాంశం->శీర్షిక_స్థానభ్రంశం);
}

స్థిర av_always_inline AVDOVIDataMapping *
av_dovi_get_mapping(స్థిరరాశి AVDOVIMetadata *దత్తాంశం)
{
    తిరిగి (AVDOVIDataMapping *)((uint8_t *) దత్తాంశం + దత్తాంశం->mapping_స్థానభ్రంశం);
}

స్థిర av_always_inline AVDOVIColorMetadata *
av_dovi_get_color(స్థిరరాశి AVDOVIMetadata *దత్తాంశం)
{
    తిరిగి (AVDOVIColorMetadata *)((uint8_t *) దత్తాంశం + దత్తాంశం->color_స్థానభ్రంశం);
}

/**
 * Gets the specified Dolby Vision Display Management (DM) metadata
 * @param index must be non negative and below data->num_ext_blocks
 */
స్థిర av_always_inline AVDOVIDm_దత్తాంశం *
av_dovi_get_ext(స్థిరరాశి AVDOVIMetadata *దత్తాంశం, పూర్ణాంకం సూచీ)
{
    తిరిగి (AVDOVIDm_దత్తాంశం *)((uint8_t *) దత్తాంశం + దత్తాంశం->ext_ఖండం_స్థానభ్రంశం +
                            దత్తాంశం->ext_ఖండం_కొలత * సూచీ);
}

/**
 * Find an extension block with a given level, or NULL. In the case of
 * multiple extension blocks, only the first is returned.
 */
AVDOVIDm_దత్తాంశం *av_dovi_కనుగొను_level(స్థిరరాశి AVDOVIMetadata *దత్తాంశం, uint8_t level);

/**
 * Allocate an AVDOVIMetadata structure and initialize its
 * fields to default values.
 *
 * @param size If this parameter is non-NULL, the size in bytes of the
 *             allocated struct will be written here on success
 *
 * @return the newly allocated struct or NULL on failure
 */
AVDOVIMetadata *av_dovi_metadata_alloc(size_t *కొలత);

#అయితే_ముగింపు /* AVUTIL_DOVI_META_H */
