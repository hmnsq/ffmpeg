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

#నిర్వచితం_కాకపోతే AVUTIL_HWCONTEXT_VIDEOTOOLBOX_H
#నిర్వచించు AVUTIL_HWCONTEXT_VIDEOTOOLBOX_H

#అన్తర్భావ <stdint.h>

#అన్తర్భావ <VideoToolbox/VideoToolbox.h>

#అన్తర్భావ "frame.h"
#అన్తర్భావ "pixfmt.h"

/**
 * @file
 * An API-specific header for AV_HWDEVICE_TYPE_VIDEOTOOLBOX.
 *
 * This API supports frame allocation using a native CVPixelBufferPool
 * instead of an AVBufferPool.
 *
 * If the API user sets a custom pool, AVHWFramesContext.pool must return
 * AVBufferRefs whose data pointer is a CVImageBufferRef or CVPixelBufferRef.
 * Note that the underlying CVPixelBuffer could be retained by OS frameworks
 * depending on application usage, so it is preferable to let CoreVideo manage
 * the pool using the default implementation.
 *
 * Currently AVHWDeviceContext.hwctx are always NULL.
 */

రకనిర్వచనం నిర్మాణం AVVTFramesContext {
    గణన AVColorRange color_range;
} AVVTFramesContext;

/**
 * Convert a VideoToolbox (actually CoreVideo) format to AVPixelFormat.
 * Returns AV_PIX_FMT_NONE if no known equivalent was found.
 */
గణన AVPixelFormat av_map_videotoolbox_format_గమ్యం_pixfmt(uint32_t cv_fmt);

/**
 * Convert an AVPixelFormat to a VideoToolbox (actually CoreVideo) format.
 * Returns 0 if no known equivalent was found.
 */
uint32_t av_map_videotoolbox_format_from_pixfmt(గణన AVPixelFormat pix_fmt);

/**
 * Same as av_map_videotoolbox_format_from_pixfmt function, but can map and
 * return full range pixel formats via a flag.
 */
uint32_t av_map_videotoolbox_format_from_pixfmt2(గణన AVPixelFormat pix_fmt, bool నిండిన_range);

/**
 * Convert an AVChromaLocation to a VideoToolbox/CoreVideo chroma location string.
 *
 * The returned string is a CoreVideo constant and must not be released.
 *
 * Returns NULL if no known equivalent was found.
 */
CFStringRef av_map_videotoolbox_chroma_loc_from_av(గణన AVChromaLocation loc);

/**
 * Convert an AVColorSpace to a VideoToolbox/CoreVideo color matrix string.
 *
 * The returned string is borrowed from CoreVideo and must not be released.
 * It is either a constant, or an entry of CoreVideo's internal codepoint
 * cache; releasing a cached entry makes later lookups of the same value
 * return a dangling pointer.
 *
 * Returns NULL if no known equivalent was found.
 */
CFStringRef av_map_videotoolbox_color_మాతృక_from_av(గణన AVColorSpace space);

/**
 * Convert an AVColorPrimaries to a VideoToolbox/CoreVideo color primaries string.
 *
 * The returned string is borrowed from CoreVideo and must not be released.
 * It is either a constant, or an entry of CoreVideo's internal codepoint
 * cache; releasing a cached entry makes later lookups of the same value
 * return a dangling pointer.
 *
 * Returns NULL if no known equivalent was found.
 */
CFStringRef av_map_videotoolbox_color_primaries_from_av(గణన AVColorPrimaries pri);

/**
 * Convert an AVColorTransferCharacteristic to a VideoToolbox/CoreVideo color transfer
 * function string.
 *
 * The returned string is borrowed from CoreVideo and must not be released.
 * It is either a constant, or an entry of CoreVideo's internal codepoint
 * cache; releasing a cached entry makes later lookups of the same value
 * return a dangling pointer.
 *
 * Returns NULL if no known equivalent was found.
 */
CFStringRef av_map_videotoolbox_color_trc_from_av(గణన AVColorTransferCharacteristic trc);

/**
 * Set CVPixelBufferRef's metadata based on an AVFrame.
 *
 * Sets/unsets the CVPixelBuffer attachments to match as closely as possible the
 * AVFrame metadata. To prevent inconsistent attachments, the attachments for properties
 * that could not be matched or are unspecified in the given AVFrame are unset. So if
 * any attachments already covered by AVFrame metadata need to be set to a specific
 * value, this should happen after calling this function.
 *
 * Returns < 0 in case of an error.
 */
పూర్ణాంకం av_vt_pixbuf_సమితి_attachments(శూన్య *log_ctx,
                                 CVPixel_బఫరు_Ref pixbuf, స్థిరరాశి నిర్మాణం AVFrame *src);

#అయితే_ముగింపు /* AVUTIL_HWCONTEXT_VIDEOTOOLBOX_H */
