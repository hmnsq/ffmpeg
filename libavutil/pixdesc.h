/*
 * pixel format descriptor
 * Copyright (c) 2009 Michael Niedermayer <michaelni@gmx.at>
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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_PIXDESC_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_PIXDESC_H

#ਅਨ੍ਤਰ੍ਭਾਵ <inttypes.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixfmt.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVComponentDescriptor {
    /**
     * Which of the 4 planes contains the component.
     */
    ਪੂਰਨ plane;

    /**
     * Number of elements between 2 horizontally consecutive pixels.
     * Elements are bits for bitstream formats, bytes otherwise.
     */
    ਪੂਰਨ ਕਦਮ;

    /**
     * Number of elements before the component of the first pixel.
     * Elements are bits for bitstream formats, bytes otherwise.
     */
    ਪੂਰਨ ਵਿੱਥ;

    /**
     * Number of least significant bits that must be shifted away
     * to get the value.
     */
    ਪੂਰਨ ਖਿਸਕਾਓ;

    /**
     * Number of bits in the component.
     */
    ਪੂਰਨ ਡੂੰਘਾਈ;
} AVComponentDescriptor;

/**
 * Descriptor that unambiguously describes how the bits of a pixel are
 * stored in the up to 4 data planes of an image. It also stores the
 * subsampling factors and number of components.
 *
 * @note This is separate of the colorspace (RGB, YCbCr, YPbPr, JPEG-style YUV
 *       and all the YUV variants) AVPixFmtDescriptor just stores how values
 *       are stored not what these values represent.
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVPixFmtDescriptor {
    ਅਚਲ ਅੱਖਰ *name;
    uint8_t nb_components;  ///< The number of components each pixel has, (1-4)

    /**
     * Amount to shift the luma width right to find the chroma width.
     * For YV12 this is 1 for example.
     * chroma_width = AV_CEIL_RSHIFT(luma_width, log2_chroma_w)
     * The note above is needed to ensure rounding up.
     * This value only refers to the chroma components.
     */
    uint8_t log2_chroma_w;

    /**
     * Amount to shift the luma height right to find the chroma height.
     * For YV12 this is 1 for example.
     * chroma_height= AV_CEIL_RSHIFT(luma_height, log2_chroma_h)
     * The note above is needed to ensure rounding up.
     * This value only refers to the chroma components.
     */
    uint8_t log2_chroma_h;

    /**
     * Combination of AV_PIX_FMT_FLAG_... flags.
     */
    uint64_t flags;

    /**
     * Parameters that describe how pixels are packed.
     * If the format has 1 or 2 components, then luma is 0.
     * If the format has 3 or 4 components:
     *   if the RGB flag is set then 0 is red, 1 is green and 2 is blue;
     *   otherwise 0 is luma, 1 is chroma-U and 2 is chroma-V.
     *
     * If present, the Alpha channel is always the last component.
     */
    AVComponentDescriptor comp[4];

    /**
     * Alternative comma-separated names.
     */
    ਅਚਲ ਅੱਖਰ *alias;
} AVPixFmtDescriptor;

/**
 * Pixel format is big-endian.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_PIX_FMT_FLAG_BE           (1 << 0)
/**
 * Pixel format has a palette in data[1], values are indexes in this palette.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_PIX_FMT_FLAG_PAL          (1 << 1)
/**
 * All values of a component are bit-wise packed end to end.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_PIX_FMT_FLAG_BITSTREAM    (1 << 2)
/**
 * Pixel format is an HW accelerated format.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_PIX_FMT_FLAG_HWACCEL      (1 << 3)
/**
 * At least one pixel component is not in the first data plane.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_PIX_FMT_FLAG_PLANAR       (1 << 4)
/**
 * The pixel format contains RGB-like data (as opposed to YUV/grayscale).
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_PIX_FMT_FLAG_RGB          (1 << 5)

/**
 * The pixel format has an alpha channel. This is set on all formats that
 * support alpha in some way, including AV_PIX_FMT_PAL8. The alpha is always
 * straight, never pre-multiplied.
 *
 * If a codec or a filter does not support alpha, it should set all alpha to
 * opaque, or use the equivalent pixel formats without alpha component, e.g.
 * AV_PIX_FMT_RGB0 (or AV_PIX_FMT_RGB24 etc.) instead of AV_PIX_FMT_RGBA.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_PIX_FMT_FLAG_ALPHA        (1 << 7)

/**
 * The pixel format is following a Bayer pattern
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_PIX_FMT_FLAG_BAYER        (1 << 8)

/**
 * The pixel format contains IEEE-754 floating point values. Precision (double,
 * single, or half) should be determined by the pixel size (64, 32, or 16 bits).
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_PIX_FMT_FLAG_FLOAT        (1 << 9)

/**
 * The pixel format contains XYZ-like data (as opposed to YUV/RGB/grayscale).
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_PIX_FMT_FLAG_XYZ          (1 << 10)

/**
 * Return the number of bits per pixel used by the pixel format
 * described by pixdesc. Note that this is not the same as the number
 * of bits per sample.
 *
 * The returned number of bits refers to the number of bits actually
 * used for storing the pixel information, that is padding bits are
 * not counted.
 */
ਪੂਰਨ av_get_ਬਿੱਟ_ਪ੍ਰਤੀ_pixel(ਅਚਲ AVPixFmtDescriptor *pixdesc);

/**
 * Return the number of bits per pixel for the pixel format
 * described by pixdesc, including any padding or unused bits.
 */
ਪੂਰਨ av_get_padded_ਬਿੱਟ_ਪ੍ਰਤੀ_pixel(ਅਚਲ AVPixFmtDescriptor *pixdesc);

/**
 * @return a pixel format descriptor for provided pixel format or NULL if
 * this pixel format is unknown.
 */
ਅਚਲ AVPixFmtDescriptor *av_pix_fmt_desc_get(ਗਿਣਤੀ AVPixelFormat pix_fmt);

/**
 * Iterate over all pixel format descriptors known to libavutil.
 *
 * @param prev previous descriptor. NULL to get the first descriptor.
 *
 * @return next descriptor or NULL after the last descriptor
 */
ਅਚਲ AVPixFmtDescriptor *av_pix_fmt_desc_ਅਗਲਾ(ਅਚਲ AVPixFmtDescriptor *prev);

/**
 * @return an AVPixelFormat id described by desc, or AV_PIX_FMT_NONE if desc
 * is not a valid pointer to a pixel format descriptor.
 */
ਗਿਣਤੀ AVPixelFormat av_pix_fmt_desc_get_id(ਅਚਲ AVPixFmtDescriptor *desc);

/**
 * Utility function to access log2_chroma_w log2_chroma_h from
 * the pixel format AVPixFmtDescriptor.
 *
 * @param[in]  pix_fmt the pixel format
 * @param[out] h_shift store log2_chroma_w (horizontal/width shift)
 * @param[out] v_shift store log2_chroma_h (vertical/height shift)
 *
 * @return 0 on success, AVERROR(ENOSYS) on invalid or unknown pixel format
 */
ਪੂਰਨ av_pix_fmt_get_chroma_sub_sample(ਗਿਣਤੀ AVPixelFormat pix_fmt,
                                     ਪੂਰਨ *h_ਖਿਸਕਾਓ, ਪੂਰਨ *v_ਖਿਸਕਾਓ);

/**
 * @return number of planes in pix_fmt, a negative AVERROR if pix_fmt is not a
 * valid pixel format.
 */
ਪੂਰਨ av_pix_fmt_ਗਿਣਤੀ_planes(ਗਿਣਤੀ AVPixelFormat pix_fmt);

/**
 * @return the name for provided color range or NULL if unknown.
 */
ਅਚਲ ਅੱਖਰ *av_color_range_name(ਗਿਣਤੀ AVColorRange range);

/**
 * @return the AVColorRange value for name or an AVError if not found.
 */
ਪੂਰਨ av_color_range_from_name(ਅਚਲ ਅੱਖਰ *name);

/**
 * @return the name for provided color primaries or NULL if unknown.
 */
ਅਚਲ ਅੱਖਰ *av_color_primaries_name(ਗਿਣਤੀ AVColorPrimaries primaries);

/**
 * @return the AVColorPrimaries value for name or an AVError if not found.
 */
ਪੂਰਨ av_color_primaries_from_name(ਅਚਲ ਅੱਖਰ *name);

/**
 * @return the name for provided color transfer or NULL if unknown.
 */
ਅਚਲ ਅੱਖਰ *av_color_transfer_name(ਗਿਣਤੀ AVColorTransferCharacteristic transfer);

/**
 * @return the AVColorTransferCharacteristic value for name or an AVError if not found.
 */
ਪੂਰਨ av_color_transfer_from_name(ਅਚਲ ਅੱਖਰ *name);

/**
 * @return the name for provided color space or NULL if unknown.
 */
ਅਚਲ ਅੱਖਰ *av_color_space_name(ਗਿਣਤੀ AVColorSpace space);

/**
 * @return the AVColorSpace value for name or an AVError if not found.
 */
ਪੂਰਨ av_color_space_from_name(ਅਚਲ ਅੱਖਰ *name);

/**
 * @return the name for provided chroma location or NULL if unknown.
 */
ਅਚਲ ਅੱਖਰ *av_chroma_location_name(ਗਿਣਤੀ AVChromaLocation location);

/**
 * @return the AVChromaLocation value for name or an AVError if not found.
 */
ਪੂਰਨ av_chroma_location_from_name(ਅਚਲ ਅੱਖਰ *name);

/**
 * Converts AVChromaLocation to swscale x/y chroma position.
 *
 * The positions represent the chroma (0,0) position in a coordinates system
 * with luma (0,0) representing the origin and luma(1,1) representing 256,256
 *
 * @param xpos  horizontal chroma sample position
 * @param ypos  vertical   chroma sample position
 */
ਪੂਰਨ av_chroma_location_enum_ਮੰਜ਼ਿਲ_pos(ਪੂਰਨ *xpos, ਪੂਰਨ *ypos, ਗਿਣਤੀ AVChromaLocation pos);

/**
 * Converts swscale x/y chroma position to AVChromaLocation.
 *
 * The positions represent the chroma (0,0) position in a coordinates system
 * with luma (0,0) representing the origin and luma(1,1) representing 256,256
 *
 * @param xpos  horizontal chroma sample position
 * @param ypos  vertical   chroma sample position
 */
ਗਿਣਤੀ AVChromaLocation av_chroma_location_pos_ਮੰਜ਼ਿਲ_enum(ਪੂਰਨ xpos, ਪੂਰਨ ypos);

/**
 * @return the name for provided alpha mode or NULL if unknown.
 */
ਅਚਲ ਅੱਖਰ *av_alpha_ਬਹੁਲਕ_name(ਗਿਣਤੀ AVAlpha_ਬਹੁਲਕ ਬਹੁਲਕ);

/**
 * @return the AVAlphaMode value for name or an AVError if not found.
 */
ਗਿਣਤੀ AVAlpha_ਬਹੁਲਕ av_alpha_ਬਹੁਲਕ_from_name(ਅਚਲ ਅੱਖਰ *name);

/**
 * Return the pixel format corresponding to name.
 *
 * If there is no pixel format with name name, then looks for a
 * pixel format with the name corresponding to the native endian
 * format of name.
 * For example in a little-endian system, first looks for "gray16",
 * then for "gray16le".
 *
 * Finally if no pixel format has been found, returns AV_PIX_FMT_NONE.
 */
ਗਿਣਤੀ AVPixelFormat av_get_pix_fmt(ਅਚਲ ਅੱਖਰ *name);

/**
 * Return the short name for a pixel format, NULL in case pix_fmt is
 * unknown.
 *
 * @see av_get_pix_fmt(), av_get_pix_fmt_string()
 */
ਅਚਲ ਅੱਖਰ *av_get_pix_fmt_name(ਗਿਣਤੀ AVPixelFormat pix_fmt);

/**
 * Print in buf the string corresponding to the pixel format with
 * number pix_fmt, or a header if pix_fmt is negative.
 *
 * @param buf the buffer where to write the string
 * @param buf_size the size of buf
 * @param pix_fmt the number of the pixel format to print the
 * corresponding info string, or a negative value to print the
 * corresponding header.
 */
ਅੱਖਰ *av_get_pix_fmt_string(ਅੱਖਰ *buf, ਪੂਰਨ buf_ਮਾਪ,
                            ਗਿਣਤੀ AVPixelFormat pix_fmt);

/**
 * Read a line from an image, and write the values of the
 * pixel format component c to dst.
 *
 * @param data the array containing the pointers to the planes of the image
 * @param linesize the array containing the linesizes of the image
 * @param desc the pixel format descriptor for the image
 * @param x the horizontal coordinate of the first pixel to read
 * @param y the vertical coordinate of the first pixel to read
 * @param w the width of the line to read, that is the number of
 * values to write to dst
 * @param read_pal_component if not zero and the format is a paletted
 * format writes the values corresponding to the palette
 * component c in data[1] to dst, rather than the palette indexes in
 * data[0]. The behavior is undefined if the format is not paletted.
 * @param dst_element_size size of elements in dst array (2 or 4 byte)
 */
ਖਾਲੀ av_read_image_line2(ਖਾਲੀ *dst, ਅਚਲ uint8_t *ਅੰਕੜੇ[4],
                        ਅਚਲ ਪੂਰਨ linesize[4], ਅਚਲ AVPixFmtDescriptor *desc,
                        ਪੂਰਨ x, ਪੂਰਨ y, ਪੂਰਨ c, ਪੂਰਨ w, ਪੂਰਨ read_pal_component,
                        ਪੂਰਨ dst_element_ਮਾਪ);

ਖਾਲੀ av_read_image_ਸਤਰ(uint16_t *dst, ਅਚਲ uint8_t *ਅੰਕੜੇ[4],
                        ਅਚਲ ਪੂਰਨ linesize[4], ਅਚਲ AVPixFmtDescriptor *desc,
                        ਪੂਰਨ x, ਪੂਰਨ y, ਪੂਰਨ c, ਪੂਰਨ w, ਪੂਰਨ read_pal_component);

/**
 * Write the values from src to the pixel format component c of an
 * image line.
 *
 * @param src array containing the values to write
 * @param data the array containing the pointers to the planes of the
 * image to write into. It is supposed to be zeroed.
 * @param linesize the array containing the linesizes of the image
 * @param desc the pixel format descriptor for the image
 * @param x the horizontal coordinate of the first pixel to write
 * @param y the vertical coordinate of the first pixel to write
 * @param w the width of the line to write, that is the number of
 * values to write to the image line
 * @param src_element_size size of elements in src array (2 or 4 byte)
 */
ਖਾਲੀ av_write_image_line2(ਅਚਲ ਖਾਲੀ *src, uint8_t *ਅੰਕੜੇ[4],
                         ਅਚਲ ਪੂਰਨ linesize[4], ਅਚਲ AVPixFmtDescriptor *desc,
                         ਪੂਰਨ x, ਪੂਰਨ y, ਪੂਰਨ c, ਪੂਰਨ w, ਪੂਰਨ src_element_ਮਾਪ);

ਖਾਲੀ av_write_image_ਸਤਰ(ਅਚਲ uint16_t *src, uint8_t *ਅੰਕੜੇ[4],
                         ਅਚਲ ਪੂਰਨ linesize[4], ਅਚਲ AVPixFmtDescriptor *desc,
                         ਪੂਰਨ x, ਪੂਰਨ y, ਪੂਰਨ c, ਪੂਰਨ w);

/**
 * Utility function to swap the endianness of a pixel format.
 *
 * @param[in]  pix_fmt the pixel format
 *
 * @return pixel format with swapped endianness if it exists,
 * otherwise AV_PIX_FMT_NONE
 */
ਗਿਣਤੀ AVPixelFormat av_pix_fmt_ਅਦਲਾ_ਬਦਲੀ_endianness(ਗਿਣਤੀ AVPixelFormat pix_fmt);

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_LOSS_RESOLUTION        0x0001 /**< loss due to resolution change */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_LOSS_ਡੂੰਘਾਈ             0x0002 /**< loss due to color depth change */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_LOSS_COLORSPACE        0x0004 /**< loss due to color space conversion */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_LOSS_ALPHA             0x0008 /**< loss of alpha bits */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_LOSS_COLORQUANT        0x0010 /**< loss due to color quantization */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_LOSS_CHROMA            0x0020 /**< loss of chroma (e.g. RGB to gray conversion) */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_LOSS_EXCESS_RESOLUTION 0x0040 /**< loss due to unneeded extra resolution */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_LOSS_EXCESS_ਡੂੰਘਾਈ      0x0080 /**< loss due to unneeded extra color depth */


/**
 * Compute what kind of losses will occur when converting from one specific
 * pixel format to another.
 * When converting from one pixel format to another, information loss may occur.
 * For example, when converting from RGB24 to GRAY, the color information will
 * be lost. Similarly, other losses occur when converting from some formats to
 * other formats. These losses can involve loss of chroma, but also loss of
 * resolution, loss of color depth, loss due to the color space conversion, loss
 * of the alpha bits or loss due to color quantization.
 * av_get_fix_fmt_loss() informs you about the various types of losses
 * which will occur when converting from one pixel format to another.
 *
 * @param[in] dst_pix_fmt destination pixel format
 * @param[in] src_pix_fmt source pixel format
 * @param[in] has_alpha Whether the source pixel format alpha channel is used.
 * @return Combination of flags informing you what kind of losses will occur
 * (maximum loss for an invalid dst_pix_fmt).
 */
ਪੂਰਨ av_get_pix_fmt_loss(ਗਿਣਤੀ AVPixelFormat dst_pix_fmt,
                        ਗਿਣਤੀ AVPixelFormat src_pix_fmt,
                        ਪੂਰਨ has_alpha);

/**
 * Compute what kind of losses will occur when converting from one specific
 * pixel format to another.
 * When converting from one pixel format to another, information loss may occur.
 * For example, when converting from RGB24 to GRAY, the color information will
 * be lost. Similarly, other losses occur when converting from some formats to
 * other formats. These losses can involve loss of chroma, but also loss of
 * resolution, loss of color depth, loss due to the color space conversion, loss
 * of the alpha bits or loss due to color quantization.
 * av_get_fix_fmt_loss() informs you about the various types of losses
 * which will occur when converting from one pixel format to another.
 *
 * @param[in] dst_pix_fmt destination pixel format
 * @param[in] src_pix_fmt source pixel format
 * @param[in] has_alpha Whether the source pixel format alpha channel is used.
 * @return Combination of flags informing you what kind of losses will occur
 * (maximum loss for an invalid dst_pix_fmt).
 */
ਗਿਣਤੀ AVPixelFormat av_ਲੱਭੋ_ਉੱਤਮ_pix_fmt_ਦਾ_2(ਗਿਣਤੀ AVPixelFormat dst_pix_fmt1, ਗਿਣਤੀ AVPixelFormat dst_pix_fmt2,
                                             ਗਿਣਤੀ AVPixelFormat src_pix_fmt, ਪੂਰਨ has_alpha, ਪੂਰਨ *loss_ptr);

#ਜੇ_ਅੰਤ /* AVUTIL_PIXDESC_H */
