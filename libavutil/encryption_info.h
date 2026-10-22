/**
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

#यदि_अपरिभाषितम् AVUTIL_ENCRYPTION_INFO_H
#परिभाषय AVUTIL_ENCRYPTION_INFO_H

#अन्तर्भाव <stddef.h>
#अन्तर्भाव <stdint.h>

प्रकारनिर्देश संरचना AVSubsampleEncryptionInfo {
    /** The number of bytes that are clear. */
    अचिह्नित पूर्णाङ्क अष्टकानि_सम्बन्धि_clear_दत्त;

    /**
     * The number of bytes that are protected.  If using pattern encryption,
     * the pattern applies to only the protected bytes; if not using pattern
     * encryption, all these bytes are encrypted.
     */
    अचिह्नित पूर्णाङ्क अष्टकानि_सम्बन्धि_protected_दत्त;
} AVSubsampleEncryptionInfo;

/**
 * This describes encryption info for a packet.  This contains frame-specific
 * info for how to decrypt the packet before passing it to the decoder.
 *
 * The size of this struct is not part of the public ABI.
 */
प्रकारनिर्देश संरचना AVEncryptionInfo {
    /** The fourcc encryption scheme, in big-endian byte order. */
    uint32_t scheme;

    /**
     * Only used for pattern encryption.  This is the number of 16-byte blocks
     * that are encrypted.
     */
    uint32_t crypt_byte_खण्डम्;

    /**
     * Only used for pattern encryption.  This is the number of 16-byte blocks
     * that are clear.
     */
    uint32_t skip_byte_खण्डम्;

    /**
     * The ID of the key used to encrypt the packet.  This should always be
     * 16 bytes long, but may be changed in the future.
     */
    uint8_t *कुञ्चिका_id;
    uint32_t कुञ्चिका_id_आकार;

    /**
     * The initialization vector.  This may have been zero-filled to be the
     * correct block size.  This should always be 16 bytes long, but may be
     * changed in the future.
     */
    uint8_t *iv;
    uint32_t iv_आकार;

    /**
     * An array of subsample encryption info specifying how parts of the sample
     * are encrypted.  If there are no subsamples, then the whole sample is
     * encrypted.
     */
    AVSubsampleEncryptionInfo *subsamples;
    uint32_t subsample_गणनम्;
} AVEncryptionInfo;

/**
 * This describes info used to initialize an encryption key system.
 *
 * The size of this struct is not part of the public ABI.
 */
प्रकारनिर्देश संरचना AVEncryptionInitInfo {
    /**
     * A unique identifier for the key system this is for, can be NULL if it
     * is not known.  This should always be 16 bytes, but may change in the
     * future.
     */
    uint8_t* system_id;
    uint32_t system_id_आकार;

    /**
     * An array of key IDs this initialization data is for.  All IDs are the
     * same length.  Can be NULL if there are no known key IDs.
     */
    uint8_t** कुञ्चिका_ids;
    /** The number of key IDs. */
    uint32_t अङ्कः_कुञ्चिका_ids;
    /**
     * The number of bytes in each key ID.  This should always be 16, but may
     * change in the future.
     */
    uint32_t कुञ्चिका_id_आकार;

    /**
     * Key-system specific initialization data.  This data is copied directly
     * from the file and the format depends on the specific key system.  This
     * can be NULL if there is no initialization data; in that case, there
     * will be at least one key ID.
     */
    uint8_t* दत्त;
    uint32_t दत्त_आकार;

    /**
     * An optional pointer to the next initialization info in the list.
     */
    संरचना AVEncryptionInitInfo *अग्र;
} AVEncryptionInitInfo;

/**
 * Allocates an AVEncryptionInfo structure and sub-pointers to hold the given
 * number of subsamples.  This will allocate pointers for the key ID, IV,
 * and subsample entries, set the size members, and zero-initialize the rest.
 *
 * @param subsample_count The number of subsamples.
 * @param key_id_size The number of bytes in the key ID, should be 16.
 * @param iv_size The number of bytes in the IV, should be 16.
 *
 * @return The new AVEncryptionInfo structure, or NULL on error.
 */
AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_गणनम्, uint32_t कुञ्चिका_id_आकार, uint32_t iv_आकार);

/**
 * Allocates an AVEncryptionInfo structure with a copy of the given data.
 * @return The new AVEncryptionInfo structure, or NULL on error.
 */
AVEncryptionInfo *av_encryption_info_clone(ध्रुव AVEncryptionInfo *info);

/**
 * Frees the given encryption info object.  This MUST NOT be used to free the
 * side-data data pointer, that should use normal side-data methods.
 */
शून्य av_encryption_info_free(AVEncryptionInfo *info);

/**
 * Creates a copy of the AVEncryptionInfo that is contained in the given side
 * data.  The resulting object should be passed to av_encryption_info_free()
 * when done.
 *
 * @return The new AVEncryptionInfo structure, or NULL on error.
 */
AVEncryptionInfo *av_encryption_info_get_side_दत्त(ध्रुव uint8_t *side_दत्त, size_t side_दत्त_आकार);

/**
 * Allocates and initializes side data that holds a copy of the given encryption
 * info.  The resulting pointer should be either freed using av_free or given
 * to av_packet_add_side_data().
 *
 * @return The new side-data pointer, or NULL.
 */
uint8_t *av_encryption_info_सङ्कलय_side_दत्त(
      ध्रुव AVEncryptionInfo *info, size_t *side_दत्त_आकार);


/**
 * Allocates an AVEncryptionInitInfo structure and sub-pointers to hold the
 * given sizes.  This will allocate pointers and set all the fields.
 *
 * @return The new AVEncryptionInitInfo structure, or NULL on error.
 */
AVEncryptionInitInfo *av_encryption_init_info_alloc(
    uint32_t system_id_आकार, uint32_t अङ्कः_कुञ्चिका_ids, uint32_t कुञ्चिका_id_आकार, uint32_t दत्त_आकार);

/**
 * Frees the given encryption init info object.  This MUST NOT be used to free
 * the side-data data pointer, that should use normal side-data methods.
 */
शून्य av_encryption_init_info_free(AVEncryptionInitInfo* info);

/**
 * Creates a copy of the AVEncryptionInitInfo that is contained in the given
 * side data.  The resulting object should be passed to
 * av_encryption_init_info_free() when done.
 *
 * @return The new AVEncryptionInitInfo structure, or NULL on error.
 */
AVEncryptionInitInfo *av_encryption_init_info_get_side_दत्त(
    ध्रुव uint8_t* side_दत्त, size_t side_दत्त_आकार);

/**
 * Allocates and initializes side data that holds a copy of the given encryption
 * init info.  The resulting pointer should be either freed using av_free or
 * given to av_packet_add_side_data().
 *
 * @return The new side-data pointer, or NULL.
 */
uint8_t *av_encryption_init_info_सङ्कलय_side_दत्त(
    ध्रुव AVEncryptionInitInfo *info, size_t *side_दत्त_आकार);

/**
 * Appends a copy of the given encryption init info list to encryption init
 * info side data, growing the side data with av_fast_realloc().
 *
 * @param side_data      Side data created by this function or
 *                       av_encryption_init_info_add_side_data(), *side_data
 *                       may be NULL to create new side data.
 * @param side_data_size Size of *side_data.
 * @param allocated_size Allocated size of *side_data, as for av_fast_realloc().
 * @param info           The list to append.
 * @return 0 on success, a negative AVERROR code on failure, in which case
 *         *side_data and *side_data_size are unchanged.
 */
पूर्णाङ्क av_encryption_init_info_append_side_दत्त(
    uint8_t **side_दत्त, size_t *side_दत्त_आकार, अचिह्नित पूर्णाङ्क *allocated_आकार,
    ध्रुव AVEncryptionInitInfo *info);

#यदि_अन्तः /* AVUTIL_ENCRYPTION_INFO_H */
