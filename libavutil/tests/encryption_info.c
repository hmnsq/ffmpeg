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

#ಅನ್ತರ್ಭಾವ "libavutil/encryption_info.h"

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/avassert.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVSubsampleEncryptionInfo test_subsamples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ size_t test_subsample_ಎಣಿಕೆ = ಗಾತ್ರ(test_subsamples) / ಗಾತ್ರ(test_subsamples[0]);
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t test_iv[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t test_ಕೀಲಿ_id[] = {0x21, 0x22, 0x23, 0x24};
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t test_ಕೀಲಿ_id_2[] = {0x31, 0x32, 0x33, 0x34};
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t test_system_id[] = {0x41, 0x42, 0x43};
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t test_ದತ್ತಾಂಶ[] = {0x51, 0x52};

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ compare_encryption_info(ಸ್ಥಿರಾಂಕ AVEncryptionInfo *a, ಸ್ಥಿರಾಂಕ AVEncryptionInfo *b) {
    ಆದರೆ (!a || !b || a->scheme != b->scheme || a->crypt_byte_ಖಂಡ != b->crypt_byte_ಖಂಡ ||
        a->skip_byte_ಖಂಡ != b->skip_byte_ಖಂಡ || a->ಕೀಲಿ_id_ಗಾತ್ರ != b->ಕೀಲಿ_id_ಗಾತ್ರ ||
        a->iv_ಗಾತ್ರ != b->iv_ಗಾತ್ರ || a->subsample_ಎಣಿಕೆ != b->subsample_ಎಣಿಕೆ)
        ಹಿಂತಿರುಗಿ 1;

    ಆದರೆ (memcmp(a->ಕೀಲಿ_id, b->ಕೀಲಿ_id, a->ಕೀಲಿ_id_ಗಾತ್ರ) != 0 ||
        memcmp(a->iv, b->iv, a->iv_ಗಾತ್ರ) != 0 ||
        memcmp(a->subsamples, b->subsamples, a->subsample_ಎಣಿಕೆ * ಗಾತ್ರ(a->subsamples[0])))
        ಹಿಂತಿರುಗಿ 1;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ compare_encryption_init_info(ಸ್ಥಿರಾಂಕ AVEncryptionInitInfo *a, ಸ್ಥಿರಾಂಕ AVEncryptionInitInfo *b) {
    ಆದರೆ (!a || !b || a->system_id_ಗಾತ್ರ != b->system_id_ಗಾತ್ರ ||
        a->ಅಂಕೆ_ಕೀಲಿ_ids != b->ಅಂಕೆ_ಕೀಲಿ_ids || a->ಕೀಲಿ_id_ಗಾತ್ರ != b->ಕೀಲಿ_id_ಗಾತ್ರ ||
        a->ದತ್ತಾಂಶ_ಗಾತ್ರ != b->ದತ್ತಾಂಶ_ಗಾತ್ರ)
        ಹಿಂತಿರುಗಿ 1;

    ಆದರೆ (memcmp(a->system_id, b->system_id, a->system_id_ಗಾತ್ರ) != 0 ||
        memcmp(a->ದತ್ತಾಂಶ, b->ದತ್ತಾಂಶ, a->ದತ್ತಾಂಶ_ಗಾತ್ರ) != 0)
        ಹಿಂತಿರುಗಿ 1;

    ಗಾಗಿ (uint32_t i = 0; i < a->ಅಂಕೆ_ಕೀಲಿ_ids; i++) {
        ಆದರೆ (memcmp(a->ಕೀಲಿ_ids[i], b->ಕೀಲಿ_ids[i], a->ಕೀಲಿ_id_ಗಾತ್ರ) != 0)
            ಹಿಂತಿರುಗಿ 1;
    }

    ಆದರೆ (a->ಮುಂದಿನ || b->ಮುಂದಿನ) {
        ಆದರೆ (!a->ಮುಂದಿನ || !b->ಮುಂದಿನ)
            ಹಿಂತಿರುಗಿ 1;
        ಆದರೆ (compare_encryption_init_info(a->ಮುಂದಿನ, b->ಮುಂದಿನ) != 0)
            ಹಿಂತಿರುಗಿ 1;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸತತ_encryption_info_test(ಶೂನ್ಯ)
{
    AVEncryptionInfo *info, *copy;
    uint8_t *side_ದತ್ತಾಂಶ;
    size_t side_ದತ್ತಾಂಶ_ಗಾತ್ರ;

    info = av_encryption_info_alloc(test_subsample_ಎಣಿಕೆ, ಗಾತ್ರ(test_ಕೀಲಿ_id), ಗಾತ್ರ(test_iv));
    av_assert0(info);
    av_assert0(info->ಕೀಲಿ_id);
    av_assert0(info->ಕೀಲಿ_id_ಗಾತ್ರ == ಗಾತ್ರ(test_ಕೀಲಿ_id));
    av_assert0(info->iv);
    av_assert0(info->iv_ಗಾತ್ರ == ಗಾತ್ರ(test_iv));
    av_assert0(info->subsamples);
    av_assert0(info->subsample_ಎಣಿಕೆ == test_subsample_ಎಣಿಕೆ);

    info->scheme = 1234;
    info->crypt_byte_ಖಂಡ = 333;
    info->skip_byte_ಖಂಡ = 444;
    ಸ್ಮರಣೆ_ನಕಲು(info->ಕೀಲಿ_id, test_ಕೀಲಿ_id, ಗಾತ್ರ(test_ಕೀಲಿ_id));
    ಸ್ಮರಣೆ_ನಕಲು(info->iv, test_iv, ಗಾತ್ರ(test_iv));
    ಸ್ಮರಣೆ_ನಕಲು(info->subsamples, test_subsamples, ಗಾತ್ರ(test_subsamples));

    copy = av_encryption_info_clone(info);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);

    side_ದತ್ತಾಂಶ = av_encryption_info_ಕೂಡಿಸು_side_ದತ್ತಾಂಶ(info, &side_ದತ್ತಾಂಶ_ಗಾತ್ರ);
    av_assert0(side_ದತ್ತಾಂಶ);
    av_assert0(side_ದತ್ತಾಂಶ_ಗಾತ್ರ > 0);

    copy = av_encryption_info_get_side_ದತ್ತಾಂಶ(side_ದತ್ತಾಂಶ, side_ದತ್ತಾಂಶ_ಗಾತ್ರ);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);
    av_free(side_ದತ್ತಾಂಶ);

    av_encryption_info_free(info);
}

ಸ್ಥಿರ AVEncryptionInitInfo *create_init_info(ಶೂನ್ಯ)
{
    AVEncryptionInitInfo *info;

    info = av_encryption_init_info_alloc(ಗಾತ್ರ(test_system_id), 2, ಗಾತ್ರ(test_ಕೀಲಿ_id), ಗಾತ್ರ(test_ದತ್ತಾಂಶ));
    av_assert0(info);
    av_assert0(info->system_id);
    av_assert0(info->system_id_ಗಾತ್ರ == ಗಾತ್ರ(test_system_id));
    av_assert0(info->ಕೀಲಿ_ids);
    av_assert0(info->ಅಂಕೆ_ಕೀಲಿ_ids == 2);
    av_assert0(info->ಕೀಲಿ_id_ಗಾತ್ರ == ಗಾತ್ರ(test_ಕೀಲಿ_id));
    av_assert0(info->ಕೀಲಿ_ids[0]);
    av_assert0(info->ಕೀಲಿ_ids[1]);
    av_assert0(info->ದತ್ತಾಂಶ);
    av_assert0(info->ದತ್ತಾಂಶ_ಗಾತ್ರ == ಗಾತ್ರ(test_ದತ್ತಾಂಶ));
    av_assert0(!info->ಮುಂದಿನ);

    ಸ್ಮರಣೆ_ನಕಲು(info->system_id, test_system_id, ಗಾತ್ರ(test_system_id));
    ಸ್ಮರಣೆ_ನಕಲು(info->ಕೀಲಿ_ids[0], test_ಕೀಲಿ_id, ಗಾತ್ರ(test_ಕೀಲಿ_id));
    ಸ್ಮರಣೆ_ನಕಲು(info->ಕೀಲಿ_ids[1], test_ಕೀಲಿ_id_2, ಗಾತ್ರ(test_ಕೀಲಿ_id_2));
    ಸ್ಮರಣೆ_ನಕಲು(info->ದತ್ತಾಂಶ, test_ದತ್ತಾಂಶ, ಗಾತ್ರ(test_ದತ್ತಾಂಶ));

    ಹಿಂತಿರುಗಿ info;
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸತತ_encryption_init_info_test(ಶೂನ್ಯ)
{
    AVEncryptionInitInfo *info, *copy;
    uint8_t *side_ದತ್ತಾಂಶ, *appended;
    size_t side_ದತ್ತಾಂಶ_ಗಾತ್ರ, appended_ಗಾತ್ರ;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ allocated_ಗಾತ್ರ = 0;

    info = create_init_info();

    side_ದತ್ತಾಂಶ = av_encryption_init_info_ಕೂಡಿಸು_side_ದತ್ತಾಂಶ(info, &side_ದತ್ತಾಂಶ_ಗಾತ್ರ);
    av_assert0(side_ದತ್ತಾಂಶ);
    av_assert0(side_ದತ್ತಾಂಶ_ಗಾತ್ರ > 0);
    copy = av_encryption_init_info_get_side_ದತ್ತಾಂಶ(side_ದತ್ತಾಂಶ, side_ದತ್ತಾಂಶ_ಗಾತ್ರ);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);
    av_free(side_ದತ್ತಾಂಶ);

    // Make the first init info different from the second to test the correct order.
    memset(info->system_id, 0, info->system_id_ಗಾತ್ರ);
    appended = av_encryption_init_info_ಕೂಡಿಸು_side_ದತ್ತಾಂಶ(info, &appended_ಗಾತ್ರ);
    av_assert0(appended);
    info->ಮುಂದಿನ = create_init_info();
    side_ದತ್ತಾಂಶ = av_encryption_init_info_ಕೂಡಿಸು_side_ದತ್ತಾಂಶ(info, &side_ದತ್ತಾಂಶ_ಗಾತ್ರ);
    av_assert0(side_ದತ್ತಾಂಶ);
    copy = av_encryption_init_info_get_side_ದತ್ತಾಂಶ(side_ದತ್ತಾಂಶ, side_ದತ್ತಾಂಶ_ಗಾತ್ರ);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);

    av_assert0(av_encryption_init_info_append_side_ದತ್ತಾಂಶ(&appended, &appended_ಗಾತ್ರ, &allocated_ಗಾತ್ರ, info->ಮುಂದಿನ) == 0);
    av_assert0(appended_ಗಾತ್ರ == side_ದತ್ತಾಂಶ_ಗಾತ್ರ);
    av_assert0(memcmp(appended, side_ದತ್ತಾಂಶ, side_ದತ್ತಾಂಶ_ಗಾತ್ರ) == 0);
    av_free(appended);
    av_free(side_ದತ್ತಾಂಶ);

    av_encryption_init_info_free(info);
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಪೂರ್ಣಾಂಕ argc, ಅಕ್ಷರ **argv)
{
    ಸತತ_encryption_info_test();
    ಸತತ_encryption_init_info_test();
    ಹಿಂತಿರುಗಿ 0;
}
