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


#यदि_अपरिभाषितम् AVUTIL_DOVI_META_H
#परिभाषय AVUTIL_DOVI_META_H

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stddef.h>

#अन्तर्भाव "rational.h"
#अन्तर्भाव "csp.h"

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
प्रकारनिर्देश संरचना AVDOVIDecoder_Configuration_लेखः {
    uint8_t dv_संस्करणम्_major;
    uint8_t dv_संस्करणम्_minor;
    uint8_t dv_profile;
    uint8_t dv_level;
    uint8_t rpu_present_flag;
    uint8_t el_present_flag;
    uint8_t bl_present_flag;
    uint8_t dv_bl_signal_compatibility_id;
    uint8_t dv_md_compression;
} AVDOVIDecoder_Configuration_लेखः;

गणना AVDOVICompression {
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
AVDOVIDecoder_Configuration_लेखः *av_dovi_alloc(size_t *आकार);

/**
 * Dolby Vision RPU data header.
 *
 * @note sizeof(AVDOVIRpuDataHeader) is not part of the public ABI.
 */
प्रकारनिर्देश संरचना AVDOVIRpu_दत्त_शीर्षकम् {
    uint8_t rpu_type;
    uint16_t rpu_format;
    uint8_t vdr_rpu_profile;
    uint8_t vdr_rpu_level;
    uint8_t chroma_resampling_explicit_filter_flag;
    uint8_t coef_दत्त_type; /* informative, lavc always converts to fixed */
    uint8_t coef_log2_denom;
    uint8_t vdr_rpu_normalized_idc;
    uint8_t bl_video_पूर्णम्_range_flag;
    uint8_t bl_bit_गभीरता; /* [8, 16] */
    uint8_t el_bit_गभीरता; /* [8, 16] */
    uint8_t vdr_bit_गभीरता; /* [8, 16] */
    uint8_t spatial_resampling_filter_flag;
    uint8_t el_spatial_resampling_filter_flag;
    uint8_t disable_residual_flag;
    uint8_t ext_mapping_idc_0_4; /* extended base layer inverse mapping indicator */
    uint8_t ext_mapping_idc_5_7; /* reserved */
} AVDOVIRpu_दत्त_शीर्षकम्;

गणना AVDOVIMapping_विधानम् {
    AV_DOVI_MAPPING_POLYNOMIAL = 0,
    AV_DOVI_MAPPING_MMR = 1,
};

/**
 * Coefficients of a piece-wise function. The pieces of the function span the
 * value ranges between two adjacent pivot values.
 */
#परिभाषय AV_DOVI_MAX_PIECES 8
प्रकारनिर्देश संरचना AVDOVIReshaping_वक्रम् {
    uint8_t अङ्कः_pivots;                         /* [2, 9] */
    uint16_t pivots[AV_DOVI_MAX_PIECES + 1];    /* sorted ascending */
    गणना AVDOVIMapping_विधानम् mapping_idc[AV_DOVI_MAX_PIECES];
    /* AV_DOVI_MAPPING_POLYNOMIAL */
    uint8_t poly_क्रमः[AV_DOVI_MAX_PIECES];     /* [1, 2] */
    int64_t poly_coef[AV_DOVI_MAX_PIECES][3];   /* x^0, x^1, x^2 */
    /* AV_DOVI_MAPPING_MMR */
    uint8_t mmr_क्रमः[AV_DOVI_MAX_PIECES];      /* [1, 3] */
    int64_t mmr_constant[AV_DOVI_MAX_PIECES];
    int64_t mmr_coef[AV_DOVI_MAX_PIECES][3/* order - 1 */][7];
} AVDOVIReshaping_वक्रम्;

गणना AVDOVINLQMethod {
    AV_DOVI_NLQ_NONE = -1,
    AV_DOVI_NLQ_रैखिकम्_DZ = 0,
};

/**
 * Coefficients of the non-linear inverse quantization. For the interpretation
 * of these, see ETSI GS CCM 001.
 */
प्रकारनिर्देश संरचना AVDOVINLQParams {
    uint16_t nlq_विस्थापनम्;
    uint64_t vdr_अन्तर्_max;
    /* AV_DOVI_NLQ_LINEAR_DZ */
    uint64_t रैखिकम्_deadzone_नतिः;
    uint64_t रैखिकम्_deadzone_देहली;
} AVDOVINLQParams;

/**
 * Dolby Vision RPU data mapping parameters.
 *
 * @note sizeof(AVDOVIDataMapping) is not part of the public ABI.
 */
प्रकारनिर्देश संरचना AVDOVIDataMapping {
    uint8_t vdr_rpu_id;
    uint8_t mapping_color_space;
    uint8_t mapping_chroma_format_idc;
    AVDOVIReshaping_वक्रम् curves[3]; /* per component */

    /* Non-linear inverse quantization */
    गणना AVDOVINLQMethod nlq_विधानम्_idc;
    uint32_t अङ्कः_x_partitions;
    uint32_t अङ्कः_y_partitions;
    AVDOVINLQParams nlq[3]; /* per component */
    uint16_t nlq_pivots[2];
} AVDOVIDataMapping;

/**
 * Dolby Vision RPU colorspace metadata parameters.
 *
 * @note sizeof(AVDOVIColorMetadata) is not part of the public ABI.
 */
प्रकारनिर्देश संरचना AVDOVIColorMetadata {
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
    AVRational ycc_गन्तव्यम्_rgb_matrix[9]; /* before PQ linearization */
    AVRational ycc_गन्तव्यम्_rgb_विस्थापनम्[3]; /* input offset of neutral value */
    AVRational rgb_गन्तव्यम्_lms_matrix[9]; /* after PQ linearization */

    /**
     * Extra signal metadata (see Dolby patents for more info).
     */
    uint16_t signal_eotf;
    uint16_t signal_eotf_param0;
    uint16_t signal_eotf_param1;
    uint32_t signal_eotf_param2;
    uint8_t signal_bit_गभीरता;
    uint8_t signal_color_space;
    uint8_t signal_chroma_format;
    uint8_t signal_पूर्णम्_range_flag; /* [0, 3] */
    uint16_t source_min_pq;
    uint16_t source_max_pq;
    uint16_t source_diagonal;
} AVDOVIColorMetadata;

प्रकारनिर्देश संरचना AVDOVIDmLevel1 {
    /* Per-frame brightness metadata */
    uint16_t min_pq;
    uint16_t max_pq;
    uint16_t avg_pq;
} AVDOVIDmLevel1;

प्रकारनिर्देश संरचना AVDOVIDmLevel2 {
    /* Usually derived from level 8 (at different levels) */
    uint16_t target_max_pq;
    uint16_t trim_नतिः;
    uint16_t trim_विस्थापनम्;
    uint16_t trim_power;
    uint16_t trim_chroma_weight;
    uint16_t trim_saturation_gain;
    int16_t ms_weight;
} AVDOVIDmLevel2;

प्रकारनिर्देश संरचना AVDOVIDmLevel3 {
    uint16_t min_pq_विस्थापनम्;
    uint16_t max_pq_विस्थापनम्;
    uint16_t avg_pq_विस्थापनम्;
} AVDOVIDmLevel3;

प्रकारनिर्देश संरचना AVDOVIDmLevel4 {
    uint16_t anchor_pq;
    uint16_t anchor_power;
} AVDOVIDmLevel4;

प्रकारनिर्देश संरचना AVDOVIDmLevel5 {
    /* Active area definition */
    uint16_t वामः_विस्थापनम्;
    uint16_t दक्षिणः_विस्थापनम्;
    uint16_t शिखरम्_विस्थापनम्;
    uint16_t bottom_विस्थापनम्;
} AVDOVIDmLevel5;

प्रकारनिर्देश संरचना AVDOVIDmLevel6 {
    /* Static HDR10 metadata */
    uint16_t max_luminance;
    uint16_t min_luminance;
    uint16_t max_cll;
    uint16_t max_fall;
} AVDOVIDmLevel6;

प्रकारनिर्देश संरचना AVDOVIDmLevel8 {
    /* Extended version of level 2 */
    uint8_t target_display_सूचकांक;
    uint16_t trim_नतिः;
    uint16_t trim_विस्थापनम्;
    uint16_t trim_power;
    uint16_t trim_chroma_weight;
    uint16_t trim_saturation_gain;
    uint16_t ms_weight;
    uint16_t target_mid_contrast;
    uint16_t clip_trim;
    uint8_t saturation_सदिशम्_क्षेत्रम्[6];
    uint8_t hue_सदिशम्_क्षेत्रम्[6];
} AVDOVIDmLevel8;

प्रकारनिर्देश संरचना AVDOVIDmLevel9 {
    /* Source display characteristics */
    uint8_t source_primary_सूचकांक;
    AVColorPrimariesDesc source_display_primaries;
} AVDOVIDmLevel9;

प्रकारनिर्देश संरचना AVDOVIDmLevel10 {
    /* Target display characteristics */
    uint8_t target_display_सूचकांक;
    uint16_t target_max_pq;
    uint16_t target_min_pq;
    uint8_t target_primary_सूचकांक;
    AVColorPrimariesDesc target_display_primaries;
} AVDOVIDmLevel10;

प्रकारनिर्देश संरचना AVDOVIDmLevel11 {
    uint8_t content_type;
    uint8_t whitepoint;
    uint8_t reference_बहुलकम्_flag;
#यदि FF_API_DOVI_L11_INVALID_PROPS
    attribute_deprecated
    uint8_t sharpness;
    attribute_deprecated
    uint8_t noise_reduction;
    attribute_deprecated
    uint8_t mpeg_noise_reduction;
    attribute_deprecated
    uint8_t frame_दरः_conversion;
    attribute_deprecated
    uint8_t brightness;
    attribute_deprecated
    uint8_t color;
#यदि_अन्तः
} AVDOVIDmLevel11;

प्रकारनिर्देश संरचना AVDOVIDmLevel254 {
    /* DMv2 info block, always present in samples with DMv2 metadata */
    uint8_t dm_बहुलकम्;
    uint8_t dm_संस्करणम्_सूचकांक;
} AVDOVIDmLevel254;

प्रकारनिर्देश संरचना AVDOVIDmLevel255 {
    /* Debug block, not really used in samples */
    uint8_t dm_सततम्_बहुलकम्;
    uint8_t dm_सततम्_संस्करणम्;
    uint8_t dm_debug[4];
} AVDOVIDmLevel255;

/**
 * Dolby Vision metadata extension block. Dynamic extension blocks may change
 * from frame to frame, while static blocks are constant throughout the entire
 * sequence.
 *
 * @note sizeof(AVDOVIDmData) is not part of the public API.
 */
प्रकारनिर्देश संरचना AVDOVIDm_दत्त {
    uint8_t level; /* [1, 255] */
    सङ्घ {
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
} AVDOVIDm_दत्त;

/**
 * Combined struct representing a combination of header, mapping and color
 * metadata, for attaching to frames as side data.
 *
 * @note The struct must be allocated with av_dovi_metadata_alloc() and
 *       its size is not a part of the public ABI.
 */

प्रकारनिर्देश संरचना AVDOVIMetadata {
    /**
     * Offset in bytes from the beginning of this structure at which the
     * respective structs start.
     */
    size_t शीर्षकम्_विस्थापनम्;   /* AVDOVIRpuDataHeader */
    size_t mapping_विस्थापनम्;  /* AVDOVIDataMapping */
    size_t color_विस्थापनम्;    /* AVDOVIColorMetadata */

    size_t ext_खण्डम्_विस्थापनम्; /* offset to start of ext blocks array */
    size_t ext_खण्डम्_आकार; /* size per element */
    पूर्णाङ्क अङ्कः_ext_खण्डानि; /* number of extension blocks */

    /* static limit on num_ext_blocks, derived from bitstream limitations */
#परिभाषय AV_DOVI_MAX_EXT_खण्डानि 32
} AVDOVIMetadata;

स्थिर av_always_inline AVDOVIRpu_दत्त_शीर्षकम् *
av_dovi_get_शीर्षकम्(ध्रुव AVDOVIMetadata *दत्त)
{
    प्रत्यागम (AVDOVIRpu_दत्त_शीर्षकम् *)((uint8_t *) दत्त + दत्त->शीर्षकम्_विस्थापनम्);
}

स्थिर av_always_inline AVDOVIDataMapping *
av_dovi_get_mapping(ध्रुव AVDOVIMetadata *दत्त)
{
    प्रत्यागम (AVDOVIDataMapping *)((uint8_t *) दत्त + दत्त->mapping_विस्थापनम्);
}

स्थिर av_always_inline AVDOVIColorMetadata *
av_dovi_get_color(ध्रुव AVDOVIMetadata *दत्त)
{
    प्रत्यागम (AVDOVIColorMetadata *)((uint8_t *) दत्त + दत्त->color_विस्थापनम्);
}

/**
 * Gets the specified Dolby Vision Display Management (DM) metadata
 * @param index must be non negative and below data->num_ext_blocks
 */
स्थिर av_always_inline AVDOVIDm_दत्त *
av_dovi_get_ext(ध्रुव AVDOVIMetadata *दत्त, पूर्णाङ्क सूचकांक)
{
    प्रत्यागम (AVDOVIDm_दत्त *)((uint8_t *) दत्त + दत्त->ext_खण्डम्_विस्थापनम् +
                            दत्त->ext_खण्डम्_आकार * सूचकांक);
}

/**
 * Find an extension block with a given level, or NULL. In the case of
 * multiple extension blocks, only the first is returned.
 */
AVDOVIDm_दत्त *av_dovi_find_level(ध्रुव AVDOVIMetadata *दत्त, uint8_t level);

/**
 * Allocate an AVDOVIMetadata structure and initialize its
 * fields to default values.
 *
 * @param size If this parameter is non-NULL, the size in bytes of the
 *             allocated struct will be written here on success
 *
 * @return the newly allocated struct or NULL on failure
 */
AVDOVIMetadata *av_dovi_metadata_alloc(size_t *आकार);

#यदि_अन्तः /* AVUTIL_DOVI_META_H */
