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


#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_DOVI_META_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_DOVI_META_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stddef.h>

#ಅನ್ತರ್ಭಾವ "rational.h"
#ಅನ್ತರ್ಭಾವ "csp.h"

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
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIDecoder_Configuration_ದಾಖಲೆ {
    uint8_t dv_ಆವೃತ್ತಿ_major;
    uint8_t dv_ಆವೃತ್ತಿ_minor;
    uint8_t dv_profile;
    uint8_t dv_level;
    uint8_t rpu_present_flag;
    uint8_t el_present_flag;
    uint8_t bl_present_flag;
    uint8_t dv_bl_signal_compatibility_id;
    uint8_t dv_md_compression;
} AVDOVIDecoder_Configuration_ದಾಖಲೆ;

ಎಣಿಕೆ AVDOVICompression {
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
AVDOVIDecoder_Configuration_ದಾಖಲೆ *av_dovi_alloc(size_t *ಗಾತ್ರ_2);

/**
 * Dolby Vision RPU data header.
 *
 * @note sizeof(AVDOVIRpuDataHeader) is not part of the public ABI.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIRpu_ದತ್ತಾಂಶ_ಶೀರ್ಷಿಕೆ {
    uint8_t rpu_type;
    uint16_t rpu_format;
    uint8_t vdr_rpu_profile;
    uint8_t vdr_rpu_level;
    uint8_t chroma_resampling_explicit_filter_flag;
    uint8_t coef_ದತ್ತಾಂಶ_type; /* informative, lavc always converts to fixed */
    uint8_t coef_log2_denom;
    uint8_t vdr_rpu_normalized_idc;
    uint8_t bl_video_ತುಂಬಿದ_range_flag;
    uint8_t bl_ಬಿಟ್_ಆಳ; /* [8, 16] */
    uint8_t el_ಬಿಟ್_ಆಳ; /* [8, 16] */
    uint8_t vdr_ಬಿಟ್_ಆಳ; /* [8, 16] */
    uint8_t spatial_resampling_filter_flag;
    uint8_t el_spatial_resampling_filter_flag;
    uint8_t disable_residual_flag;
    uint8_t ext_mapping_idc_0_4; /* extended base layer inverse mapping indicator */
    uint8_t ext_mapping_idc_5_7; /* reserved */
} AVDOVIRpu_ದತ್ತಾಂಶ_ಶೀರ್ಷಿಕೆ;

ಎಣಿಕೆ AVDOVIMapping_ವಿಧಾನ {
    AV_DOVI_MAPPING_POLYNOMIAL = 0,
    AV_DOVI_MAPPING_MMR = 1,
};

/**
 * Coefficients of a piece-wise function. The pieces of the function span the
 * value ranges between two adjacent pivot values.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_DOVI_MAX_PIECES 8
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIReshaping_ವಕ್ರ {
    uint8_t ಅಂಕೆ_pivots;                         /* [2, 9] */
    uint16_t pivots[AV_DOVI_MAX_PIECES + 1];    /* sorted ascending */
    ಎಣಿಕೆ AVDOVIMapping_ವಿಧಾನ mapping_idc[AV_DOVI_MAX_PIECES];
    /* AV_DOVI_MAPPING_POLYNOMIAL */
    uint8_t poly_ಕ್ರಮ[AV_DOVI_MAX_PIECES];     /* [1, 2] */
    int64_t poly_coef[AV_DOVI_MAX_PIECES][3];   /* x^0, x^1, x^2 */
    /* AV_DOVI_MAPPING_MMR */
    uint8_t mmr_ಕ್ರಮ[AV_DOVI_MAX_PIECES];      /* [1, 3] */
    int64_t mmr_constant[AV_DOVI_MAX_PIECES];
    int64_t mmr_coef[AV_DOVI_MAX_PIECES][3/* order - 1 */][7];
} AVDOVIReshaping_ವಕ್ರ;

ಎಣಿಕೆ AVDOVINLQMethod {
    AV_DOVI_NLQ_NONE = -1,
    AV_DOVI_NLQ_ರೇಖೀಯ_DZ = 0,
};

/**
 * Coefficients of the non-linear inverse quantization. For the interpretation
 * of these, see ETSI GS CCM 001.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVINLQParams {
    uint16_t nlq_ಸ್ಥಾನಾಂತರ;
    uint64_t vdr_ಒಳ_max;
    /* AV_DOVI_NLQ_LINEAR_DZ */
    uint64_t ರೇಖೀಯ_deadzone_ಇಳಿಜಾರು;
    uint64_t ರೇಖೀಯ_deadzone_ಮಿತಿ;
} AVDOVINLQParams;

/**
 * Dolby Vision RPU data mapping parameters.
 *
 * @note sizeof(AVDOVIDataMapping) is not part of the public ABI.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIDataMapping {
    uint8_t vdr_rpu_id;
    uint8_t mapping_color_space;
    uint8_t mapping_chroma_format_idc;
    AVDOVIReshaping_ವಕ್ರ curves[3]; /* per component */

    /* Non-linear inverse quantization */
    ಎಣಿಕೆ AVDOVINLQMethod nlq_ವಿಧಾನ_idc;
    uint32_t ಅಂಕೆ_x_partitions;
    uint32_t ಅಂಕೆ_y_partitions;
    AVDOVINLQParams nlq[3]; /* per component */
    uint16_t nlq_pivots[2];
} AVDOVIDataMapping;

/**
 * Dolby Vision RPU colorspace metadata parameters.
 *
 * @note sizeof(AVDOVIColorMetadata) is not part of the public ABI.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIColorMetadata {
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
    AVRational ycc_ಗಮ್ಯ_rgb_ಮಾತೃಕೆ[9]; /* before PQ linearization */
    AVRational ycc_ಗಮ್ಯ_rgb_ಸ್ಥಾನಾಂತರ[3]; /* input offset of neutral value */
    AVRational rgb_ಗಮ್ಯ_lms_ಮಾತೃಕೆ[9]; /* after PQ linearization */

    /**
     * Extra signal metadata (see Dolby patents for more info).
     */
    uint16_t signal_eotf;
    uint16_t signal_eotf_param0;
    uint16_t signal_eotf_param1;
    uint32_t signal_eotf_param2;
    uint8_t signal_ಬಿಟ್_ಆಳ;
    uint8_t signal_color_space;
    uint8_t signal_chroma_format;
    uint8_t signal_ತುಂಬಿದ_range_flag; /* [0, 3] */
    uint16_t ಮೂಲ_min_pq;
    uint16_t ಮೂಲ_max_pq;
    uint16_t ಮೂಲ_diagonal;
} AVDOVIColorMetadata;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIDmLevel1 {
    /* Per-frame brightness metadata */
    uint16_t min_pq;
    uint16_t max_pq;
    uint16_t avg_pq;
} AVDOVIDmLevel1;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIDmLevel2 {
    /* Usually derived from level 8 (at different levels) */
    uint16_t ಗುರಿ_max_pq;
    uint16_t trim_ಇಳಿಜಾರು;
    uint16_t trim_ಸ್ಥಾನಾಂತರ;
    uint16_t trim_power;
    uint16_t trim_chroma_ತೂಕ;
    uint16_t trim_saturation_gain;
    int16_t ms_ತೂಕ;
} AVDOVIDmLevel2;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIDmLevel3 {
    uint16_t min_pq_ಸ್ಥಾನಾಂತರ;
    uint16_t max_pq_ಸ್ಥಾನಾಂತರ;
    uint16_t avg_pq_ಸ್ಥಾನಾಂತರ;
} AVDOVIDmLevel3;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIDmLevel4 {
    uint16_t anchor_pq;
    uint16_t anchor_power;
} AVDOVIDmLevel4;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIDmLevel5 {
    /* Active area definition */
    uint16_t ಎಡ_ಸ್ಥಾನಾಂತರ;
    uint16_t ಬಲ_ಸ್ಥಾನಾಂತರ;
    uint16_t ತುದಿ_ಸ್ಥಾನಾಂತರ;
    uint16_t bottom_ಸ್ಥಾನಾಂತರ;
} AVDOVIDmLevel5;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIDmLevel6 {
    /* Static HDR10 metadata */
    uint16_t max_luminance;
    uint16_t min_luminance;
    uint16_t max_cll;
    uint16_t max_fall;
} AVDOVIDmLevel6;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIDmLevel8 {
    /* Extended version of level 2 */
    uint8_t ಗುರಿ_display_ಸೂಚ್ಯಂಕ;
    uint16_t trim_ಇಳಿಜಾರು;
    uint16_t trim_ಸ್ಥಾನಾಂತರ;
    uint16_t trim_power;
    uint16_t trim_chroma_ತೂಕ;
    uint16_t trim_saturation_gain;
    uint16_t ms_ತೂಕ;
    uint16_t ಗುರಿ_mid_contrast;
    uint16_t clip_trim;
    uint8_t saturation_ಸದಿಶ_ಕ್ಷೇತ್ರ[6];
    uint8_t hue_ಸದಿಶ_ಕ್ಷೇತ್ರ[6];
} AVDOVIDmLevel8;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIDmLevel9 {
    /* Source display characteristics */
    uint8_t ಮೂಲ_primary_ಸೂಚ್ಯಂಕ;
    AVColorPrimariesDesc ಮೂಲ_display_primaries;
} AVDOVIDmLevel9;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIDmLevel10 {
    /* Target display characteristics */
    uint8_t ಗುರಿ_display_ಸೂಚ್ಯಂಕ;
    uint16_t ಗುರಿ_max_pq;
    uint16_t ಗುರಿ_min_pq;
    uint8_t ಗುರಿ_primary_ಸೂಚ್ಯಂಕ;
    AVColorPrimariesDesc ಗುರಿ_display_primaries;
} AVDOVIDmLevel10;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIDmLevel11 {
    uint8_t content_type;
    uint8_t whitepoint;
    uint8_t reference_ಬಹುಲಕ_flag;
#ಆದರೆ FF_API_DOVI_L11_INVALID_PROPS
    attribute_deprecated
    uint8_t sharpness;
    attribute_deprecated
    uint8_t noise_reduction;
    attribute_deprecated
    uint8_t mpeg_noise_reduction;
    attribute_deprecated
    uint8_t ಚೌಕಟ್ಟು_ದರ_conversion;
    attribute_deprecated
    uint8_t brightness;
    attribute_deprecated
    uint8_t color;
#ಆದರೆ_ಅಂತ್ಯ
} AVDOVIDmLevel11;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIDmLevel254 {
    /* DMv2 info block, always present in samples with DMv2 metadata */
    uint8_t dm_ಬಹುಲಕ;
    uint8_t dm_ಆವೃತ್ತಿ_ಸೂಚ್ಯಂಕ;
} AVDOVIDmLevel254;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIDmLevel255 {
    /* Debug block, not really used in samples */
    uint8_t dm_ಸತತ_ಬಹುಲಕ;
    uint8_t dm_ಸತತ_ಆವೃತ್ತಿ;
    uint8_t dm_debug[4];
} AVDOVIDmLevel255;

/**
 * Dolby Vision metadata extension block. Dynamic extension blocks may change
 * from frame to frame, while static blocks are constant throughout the entire
 * sequence.
 *
 * @note sizeof(AVDOVIDmData) is not part of the public API.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIDm_ದತ್ತಾಂಶ {
    uint8_t level; /* [1, 255] */
    ಒಕ್ಕೂಟ {
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
} AVDOVIDm_ದತ್ತಾಂಶ;

/**
 * Combined struct representing a combination of header, mapping and color
 * metadata, for attaching to frames as side data.
 *
 * @note The struct must be allocated with av_dovi_metadata_alloc() and
 *       its size is not a part of the public ABI.
 */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIMetadata {
    /**
     * Offset in bytes from the beginning of this structure at which the
     * respective structs start.
     */
    size_t ಶೀರ್ಷಿಕೆ_ಸ್ಥಾನಾಂತರ;   /* AVDOVIRpuDataHeader */
    size_t mapping_ಸ್ಥಾನಾಂತರ;  /* AVDOVIDataMapping */
    size_t color_ಸ್ಥಾನಾಂತರ;    /* AVDOVIColorMetadata */

    size_t ext_ಖಂಡ_ಸ್ಥಾನಾಂತರ; /* offset to start of ext blocks array */
    size_t ext_ಖಂಡ_ಗಾತ್ರ; /* size per element */
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_ext_ಖಂಡಗಳು; /* number of extension blocks */

    /* static limit on num_ext_blocks, derived from bitstream limitations */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_DOVI_MAX_EXT_ಖಂಡಗಳು 32
} AVDOVIMetadata;

ಸ್ಥಿರ av_always_inline AVDOVIRpu_ದತ್ತಾಂಶ_ಶೀರ್ಷಿಕೆ *
av_dovi_get_ಶೀರ್ಷಿಕೆ(ಸ್ಥಿರಾಂಕ AVDOVIMetadata *ದತ್ತಾಂಶ)
{
    ಹಿಂತಿರುಗಿ (AVDOVIRpu_ದತ್ತಾಂಶ_ಶೀರ್ಷಿಕೆ *)((uint8_t *) ದತ್ತಾಂಶ + ದತ್ತಾಂಶ->ಶೀರ್ಷಿಕೆ_ಸ್ಥಾನಾಂತರ);
}

ಸ್ಥಿರ av_always_inline AVDOVIDataMapping *
av_dovi_get_mapping(ಸ್ಥಿರಾಂಕ AVDOVIMetadata *ದತ್ತಾಂಶ)
{
    ಹಿಂತಿರುಗಿ (AVDOVIDataMapping *)((uint8_t *) ದತ್ತಾಂಶ + ದತ್ತಾಂಶ->mapping_ಸ್ಥಾನಾಂತರ);
}

ಸ್ಥಿರ av_always_inline AVDOVIColorMetadata *
av_dovi_get_color(ಸ್ಥಿರಾಂಕ AVDOVIMetadata *ದತ್ತಾಂಶ)
{
    ಹಿಂತಿರುಗಿ (AVDOVIColorMetadata *)((uint8_t *) ದತ್ತಾಂಶ + ದತ್ತಾಂಶ->color_ಸ್ಥಾನಾಂತರ);
}

/**
 * Gets the specified Dolby Vision Display Management (DM) metadata
 * @param index must be non negative and below data->num_ext_blocks
 */
ಸ್ಥಿರ av_always_inline AVDOVIDm_ದತ್ತಾಂಶ *
av_dovi_get_ext(ಸ್ಥಿರಾಂಕ AVDOVIMetadata *ದತ್ತಾಂಶ, ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ)
{
    ಹಿಂತಿರುಗಿ (AVDOVIDm_ದತ್ತಾಂಶ *)((uint8_t *) ದತ್ತಾಂಶ + ದತ್ತಾಂಶ->ext_ಖಂಡ_ಸ್ಥಾನಾಂತರ +
                            ದತ್ತಾಂಶ->ext_ಖಂಡ_ಗಾತ್ರ * ಸೂಚ್ಯಂಕ);
}

/**
 * Find an extension block with a given level, or NULL. In the case of
 * multiple extension blocks, only the first is returned.
 */
AVDOVIDm_ದತ್ತಾಂಶ *av_dovi_ಕಂಡುಹಿಡಿ_level(ಸ್ಥಿರಾಂಕ AVDOVIMetadata *ದತ್ತಾಂಶ, uint8_t level);

/**
 * Allocate an AVDOVIMetadata structure and initialize its
 * fields to default values.
 *
 * @param size If this parameter is non-NULL, the size in bytes of the
 *             allocated struct will be written here on success
 *
 * @return the newly allocated struct or NULL on failure
 */
AVDOVIMetadata *av_dovi_metadata_alloc(size_t *ಗಾತ್ರ_2);

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_DOVI_META_H */
