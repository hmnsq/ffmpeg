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


#اگر_غیر_تعریف_شدہ AVUTIL_DOVI_META_H
#تعریف_کرو AVUTIL_DOVI_META_H

#شامل <stdint.h>
#شامل <stddef.h>

#شامل "rational.h"
#شامل "csp.h"

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
قسمتعریف ساخت AVDOVIDecoder_Configuration_ریکارڈ {
    uint8_t dv_نسخہ_major;
    uint8_t dv_نسخہ_minor;
    uint8_t dv_profile;
    uint8_t dv_level;
    uint8_t rpu_present_flag;
    uint8_t el_present_flag;
    uint8_t bl_present_flag;
    uint8_t dv_bl_signal_compatibility_id;
    uint8_t dv_md_compression;
} AVDOVIDecoder_Configuration_ریکارڈ;

شمار AVDOVICompression {
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
AVDOVIDecoder_Configuration_ریکارڈ *av_dovi_alloc(size_t *سائز);

/**
 * Dolby Vision RPU data header.
 *
 * @note sizeof(AVDOVIRpuDataHeader) is not part of the public ABI.
 */
قسمتعریف ساخت AVDOVIRpu_ڈیٹا_سرخی {
    uint8_t rpu_type;
    uint16_t rpu_format;
    uint8_t vdr_rpu_profile;
    uint8_t vdr_rpu_level;
    uint8_t chroma_resampling_explicit_filter_flag;
    uint8_t coef_ڈیٹا_type; /* informative, lavc always converts to fixed */
    uint8_t coef_log2_denom;
    uint8_t vdr_rpu_normalized_idc;
    uint8_t bl_video_بھرا_range_flag;
    uint8_t bl_ثنائی_ہندسہ_گہرائی; /* [8, 16] */
    uint8_t el_ثنائی_ہندسہ_گہرائی; /* [8, 16] */
    uint8_t vdr_ثنائی_ہندسہ_گہرائی; /* [8, 16] */
    uint8_t spatial_resampling_filter_flag;
    uint8_t el_spatial_resampling_filter_flag;
    uint8_t disable_residual_flag;
    uint8_t ext_mapping_idc_0_4; /* extended base layer inverse mapping indicator */
    uint8_t ext_mapping_idc_5_7; /* reserved */
} AVDOVIRpu_ڈیٹا_سرخی;

شمار AVDOVIMapping_طریقہ {
    AV_DOVI_MAPPING_POLYNOMIAL = 0,
    AV_DOVI_MAPPING_MMR = 1,
};

/**
 * Coefficients of a piece-wise function. The pieces of the function span the
 * value ranges between two adjacent pivot values.
 */
#تعریف_کرو AV_DOVI_MAX_PIECES 8
قسمتعریف ساخت AVDOVIReshaping_خم {
    uint8_t عدد_pivots;                         /* [2, 9] */
    uint16_t pivots[AV_DOVI_MAX_PIECES + 1];    /* sorted ascending */
    شمار AVDOVIMapping_طریقہ mapping_idc[AV_DOVI_MAX_PIECES];
    /* AV_DOVI_MAPPING_POLYNOMIAL */
    uint8_t poly_ترتیب[AV_DOVI_MAX_PIECES];     /* [1, 2] */
    int64_t poly_coef[AV_DOVI_MAX_PIECES][3];   /* x^0, x^1, x^2 */
    /* AV_DOVI_MAPPING_MMR */
    uint8_t mmr_ترتیب[AV_DOVI_MAX_PIECES];      /* [1, 3] */
    int64_t mmr_constant[AV_DOVI_MAX_PIECES];
    int64_t mmr_coef[AV_DOVI_MAX_PIECES][3/* order - 1 */][7];
} AVDOVIReshaping_خم;

شمار AVDOVINLQMethod {
    AV_DOVI_NLQ_NONE = -1,
    AV_DOVI_NLQ_خطی_DZ = 0,
};

/**
 * Coefficients of the non-linear inverse quantization. For the interpretation
 * of these, see ETSI GS CCM 001.
 */
قسمتعریف ساخت AVDOVINLQParams {
    uint16_t nlq_انحراف;
    uint64_t vdr_اندر_max;
    /* AV_DOVI_NLQ_LINEAR_DZ */
    uint64_t خطی_deadzone_ڈھلان;
    uint64_t خطی_deadzone_حد;
} AVDOVINLQParams;

/**
 * Dolby Vision RPU data mapping parameters.
 *
 * @note sizeof(AVDOVIDataMapping) is not part of the public ABI.
 */
قسمتعریف ساخت AVDOVIDataMapping {
    uint8_t vdr_rpu_id;
    uint8_t mapping_color_space;
    uint8_t mapping_chroma_format_idc;
    AVDOVIReshaping_خم curves[3]; /* per component */

    /* Non-linear inverse quantization */
    شمار AVDOVINLQMethod nlq_طریقہ_idc;
    uint32_t عدد_x_partitions;
    uint32_t عدد_y_partitions;
    AVDOVINLQParams nlq[3]; /* per component */
    uint16_t nlq_pivots[2];
} AVDOVIDataMapping;

/**
 * Dolby Vision RPU colorspace metadata parameters.
 *
 * @note sizeof(AVDOVIColorMetadata) is not part of the public ABI.
 */
قسمتعریف ساخت AVDOVIColorMetadata {
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
    AVRational ycc_مقصد_rgb_میٹرکس[9]; /* before PQ linearization */
    AVRational ycc_مقصد_rgb_انحراف[3]; /* input offset of neutral value */
    AVRational rgb_مقصد_lms_میٹرکس[9]; /* after PQ linearization */

    /**
     * Extra signal metadata (see Dolby patents for more info).
     */
    uint16_t signal_eotf;
    uint16_t signal_eotf_param0;
    uint16_t signal_eotf_param1;
    uint32_t signal_eotf_param2;
    uint8_t signal_ثنائی_ہندسہ_گہرائی;
    uint8_t signal_color_space;
    uint8_t signal_chroma_format;
    uint8_t signal_بھرا_range_flag; /* [0, 3] */
    uint16_t ماخذ_min_pq;
    uint16_t ماخذ_max_pq;
    uint16_t ماخذ_diagonal;
} AVDOVIColorMetadata;

قسمتعریف ساخت AVDOVIDmLevel1 {
    /* Per-frame brightness metadata */
    uint16_t min_pq;
    uint16_t max_pq;
    uint16_t avg_pq;
} AVDOVIDmLevel1;

قسمتعریف ساخت AVDOVIDmLevel2 {
    /* Usually derived from level 8 (at different levels) */
    uint16_t ہدف_max_pq;
    uint16_t trim_ڈھلان;
    uint16_t trim_انحراف;
    uint16_t trim_power;
    uint16_t trim_chroma_وزن;
    uint16_t trim_saturation_gain;
    int16_t ms_وزن;
} AVDOVIDmLevel2;

قسمتعریف ساخت AVDOVIDmLevel3 {
    uint16_t min_pq_انحراف;
    uint16_t max_pq_انحراف;
    uint16_t avg_pq_انحراف;
} AVDOVIDmLevel3;

قسمتعریف ساخت AVDOVIDmLevel4 {
    uint16_t anchor_pq;
    uint16_t anchor_power;
} AVDOVIDmLevel4;

قسمتعریف ساخت AVDOVIDmLevel5 {
    /* Active area definition */
    uint16_t بایاں_انحراف;
    uint16_t دایاں_انحراف;
    uint16_t چوٹی_انحراف;
    uint16_t bottom_انحراف;
} AVDOVIDmLevel5;

قسمتعریف ساخت AVDOVIDmLevel6 {
    /* Static HDR10 metadata */
    uint16_t max_luminance;
    uint16_t min_luminance;
    uint16_t max_cll;
    uint16_t max_fall;
} AVDOVIDmLevel6;

قسمتعریف ساخت AVDOVIDmLevel8 {
    /* Extended version of level 2 */
    uint8_t ہدف_display_اشاریہ;
    uint16_t trim_ڈھلان;
    uint16_t trim_انحراف;
    uint16_t trim_power;
    uint16_t trim_chroma_وزن;
    uint16_t trim_saturation_gain;
    uint16_t ms_وزن;
    uint16_t ہدف_mid_contrast;
    uint16_t clip_trim;
    uint8_t saturation_سمتیہ_میدان[6];
    uint8_t hue_سمتیہ_میدان[6];
} AVDOVIDmLevel8;

قسمتعریف ساخت AVDOVIDmLevel9 {
    /* Source display characteristics */
    uint8_t ماخذ_primary_اشاریہ;
    AVColorPrimariesDesc ماخذ_display_primaries;
} AVDOVIDmLevel9;

قسمتعریف ساخت AVDOVIDmLevel10 {
    /* Target display characteristics */
    uint8_t ہدف_display_اشاریہ;
    uint16_t ہدف_max_pq;
    uint16_t ہدف_min_pq;
    uint8_t ہدف_primary_اشاریہ;
    AVColorPrimariesDesc ہدف_display_primaries;
} AVDOVIDmLevel10;

قسمتعریف ساخت AVDOVIDmLevel11 {
    uint8_t content_type;
    uint8_t whitepoint;
    uint8_t reference_منوال_flag;
#اگر FF_API_DOVI_L11_INVALID_PROPS
    attribute_deprecated
    uint8_t sharpness;
    attribute_deprecated
    uint8_t noise_reduction;
    attribute_deprecated
    uint8_t mpeg_noise_reduction;
    attribute_deprecated
    uint8_t چوکھٹا_شرح_conversion;
    attribute_deprecated
    uint8_t brightness;
    attribute_deprecated
    uint8_t color;
#اگر_ختم
} AVDOVIDmLevel11;

قسمتعریف ساخت AVDOVIDmLevel254 {
    /* DMv2 info block, always present in samples with DMv2 metadata */
    uint8_t dm_منوال;
    uint8_t dm_نسخہ_اشاریہ;
} AVDOVIDmLevel254;

قسمتعریف ساخت AVDOVIDmLevel255 {
    /* Debug block, not really used in samples */
    uint8_t dm_تسلسل_منوال;
    uint8_t dm_تسلسل_نسخہ;
    uint8_t dm_debug[4];
} AVDOVIDmLevel255;

/**
 * Dolby Vision metadata extension block. Dynamic extension blocks may change
 * from frame to frame, while static blocks are constant throughout the entire
 * sequence.
 *
 * @note sizeof(AVDOVIDmData) is not part of the public API.
 */
قسمتعریف ساخت AVDOVIDm_ڈیٹا {
    uint8_t level; /* [1, 255] */
    اتحاد {
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
} AVDOVIDm_ڈیٹا;

/**
 * Combined struct representing a combination of header, mapping and color
 * metadata, for attaching to frames as side data.
 *
 * @note The struct must be allocated with av_dovi_metadata_alloc() and
 *       its size is not a part of the public ABI.
 */

قسمتعریف ساخت AVDOVIMetadata {
    /**
     * Offset in bytes from the beginning of this structure at which the
     * respective structs start.
     */
    size_t سرخی_انحراف;   /* AVDOVIRpuDataHeader */
    size_t mapping_انحراف;  /* AVDOVIDataMapping */
    size_t color_انحراف;    /* AVDOVIColorMetadata */

    size_t ext_بلاک_انحراف; /* offset to start of ext blocks array */
    size_t ext_بلاک_سائز; /* size per element */
    صحیح عدد_ext_بلاکیں; /* number of extension blocks */

    /* static limit on num_ext_blocks, derived from bitstream limitations */
#تعریف_کرو AV_DOVI_MAX_EXT_بلاکیں 32
} AVDOVIMetadata;

ساکن av_always_inline AVDOVIRpu_ڈیٹا_سرخی *
av_dovi_get_سرخی(ثابت AVDOVIMetadata *ڈیٹا)
{
    واپس (AVDOVIRpu_ڈیٹا_سرخی *)((uint8_t *) ڈیٹا + ڈیٹا->سرخی_انحراف);
}

ساکن av_always_inline AVDOVIDataMapping *
av_dovi_get_mapping(ثابت AVDOVIMetadata *ڈیٹا)
{
    واپس (AVDOVIDataMapping *)((uint8_t *) ڈیٹا + ڈیٹا->mapping_انحراف);
}

ساکن av_always_inline AVDOVIColorMetadata *
av_dovi_get_color(ثابت AVDOVIMetadata *ڈیٹا)
{
    واپس (AVDOVIColorMetadata *)((uint8_t *) ڈیٹا + ڈیٹا->color_انحراف);
}

/**
 * Gets the specified Dolby Vision Display Management (DM) metadata
 * @param index must be non negative and below data->num_ext_blocks
 */
ساکن av_always_inline AVDOVIDm_ڈیٹا *
av_dovi_get_ext(ثابت AVDOVIMetadata *ڈیٹا, صحیح اشاریہ)
{
    واپس (AVDOVIDm_ڈیٹا *)((uint8_t *) ڈیٹا + ڈیٹا->ext_بلاک_انحراف +
                            ڈیٹا->ext_بلاک_سائز * اشاریہ);
}

/**
 * Find an extension block with a given level, or NULL. In the case of
 * multiple extension blocks, only the first is returned.
 */
AVDOVIDm_ڈیٹا *av_dovi_ڈھونڈو_level(ثابت AVDOVIMetadata *ڈیٹا, uint8_t level);

/**
 * Allocate an AVDOVIMetadata structure and initialize its
 * fields to default values.
 *
 * @param size If this parameter is non-NULL, the size in bytes of the
 *             allocated struct will be written here on success
 *
 * @return the newly allocated struct or NULL on failure
 */
AVDOVIMetadata *av_dovi_metadata_alloc(size_t *سائز);

#اگر_ختم /* AVUTIL_DOVI_META_H */
