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

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/encryption_info.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"

ਸਥਿਰ ਅਚਲ AVSubsampleEncryptionInfo test_subsamples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
ਸਥਿਰ ਅਚਲ size_t test_subsample_ਗਿਣਤੀ = ਆਕਾਰ(test_subsamples) / ਆਕਾਰ(test_subsamples[0]);
ਸਥਿਰ ਅਚਲ uint8_t test_iv[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
ਸਥਿਰ ਅਚਲ uint8_t test_ਕੁੰਜੀ_id[] = {0x21, 0x22, 0x23, 0x24};
ਸਥਿਰ ਅਚਲ uint8_t test_ਕੁੰਜੀ_id_2[] = {0x31, 0x32, 0x33, 0x34};
ਸਥਿਰ ਅਚਲ uint8_t test_system_id[] = {0x41, 0x42, 0x43};
ਸਥਿਰ ਅਚਲ uint8_t test_ਅੰਕੜੇ[] = {0x51, 0x52};

ਸਥਿਰ ਪੂਰਨ compare_encryption_info(ਅਚਲ AVEncryptionInfo *a, ਅਚਲ AVEncryptionInfo *b) {
    ਜੇ (!a || !b || a->scheme != b->scheme || a->crypt_byte_ਖੰਡ != b->crypt_byte_ਖੰਡ ||
        a->skip_byte_ਖੰਡ != b->skip_byte_ਖੰਡ || a->ਕੁੰਜੀ_id_ਮਾਪ != b->ਕੁੰਜੀ_id_ਮਾਪ ||
        a->iv_ਮਾਪ != b->iv_ਮਾਪ || a->subsample_ਗਿਣਤੀ != b->subsample_ਗਿਣਤੀ)
        ਵਾਪਸ 1;

    ਜੇ (memcmp(a->ਕੁੰਜੀ_id, b->ਕੁੰਜੀ_id, a->ਕੁੰਜੀ_id_ਮਾਪ) != 0 ||
        memcmp(a->iv, b->iv, a->iv_ਮਾਪ) != 0 ||
        memcmp(a->subsamples, b->subsamples, a->subsample_ਗਿਣਤੀ * ਆਕਾਰ(a->subsamples[0])))
        ਵਾਪਸ 1;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ compare_encryption_init_info(ਅਚਲ AVEncryptionInitInfo *a, ਅਚਲ AVEncryptionInitInfo *b) {
    ਜੇ (!a || !b || a->system_id_ਮਾਪ != b->system_id_ਮਾਪ ||
        a->ਅੰਕ_ਕੁੰਜੀ_ids != b->ਅੰਕ_ਕੁੰਜੀ_ids || a->ਕੁੰਜੀ_id_ਮਾਪ != b->ਕੁੰਜੀ_id_ਮਾਪ ||
        a->ਅੰਕੜੇ_ਮਾਪ != b->ਅੰਕੜੇ_ਮਾਪ)
        ਵਾਪਸ 1;

    ਜੇ (memcmp(a->system_id, b->system_id, a->system_id_ਮਾਪ) != 0 ||
        memcmp(a->ਅੰਕੜੇ, b->ਅੰਕੜੇ, a->ਅੰਕੜੇ_ਮਾਪ) != 0)
        ਵਾਪਸ 1;

    ਲਈ (uint32_t i = 0; i < a->ਅੰਕ_ਕੁੰਜੀ_ids; i++) {
        ਜੇ (memcmp(a->ਕੁੰਜੀ_ids[i], b->ਕੁੰਜੀ_ids[i], a->ਕੁੰਜੀ_id_ਮਾਪ) != 0)
            ਵਾਪਸ 1;
    }

    ਜੇ (a->ਅਗਲਾ || b->ਅਗਲਾ) {
        ਜੇ (!a->ਅਗਲਾ || !b->ਅਗਲਾ)
            ਵਾਪਸ 1;
        ਜੇ (compare_encryption_init_info(a->ਅਗਲਾ, b->ਅਗਲਾ) != 0)
            ਵਾਪਸ 1;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ ਲੜੀਵਾਰ_encryption_info_test(ਖਾਲੀ)
{
    AVEncryptionInfo *info, *copy;
    uint8_t *side_ਅੰਕੜੇ;
    size_t side_ਅੰਕੜੇ_ਮਾਪ;

    info = av_encryption_info_alloc(test_subsample_ਗਿਣਤੀ, ਆਕਾਰ(test_ਕੁੰਜੀ_id), ਆਕਾਰ(test_iv));
    av_assert0(info);
    av_assert0(info->ਕੁੰਜੀ_id);
    av_assert0(info->ਕੁੰਜੀ_id_ਮਾਪ == ਆਕਾਰ(test_ਕੁੰਜੀ_id));
    av_assert0(info->iv);
    av_assert0(info->iv_ਮਾਪ == ਆਕਾਰ(test_iv));
    av_assert0(info->subsamples);
    av_assert0(info->subsample_ਗਿਣਤੀ == test_subsample_ਗਿਣਤੀ);

    info->scheme = 1234;
    info->crypt_byte_ਖੰਡ = 333;
    info->skip_byte_ਖੰਡ = 444;
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(info->ਕੁੰਜੀ_id, test_ਕੁੰਜੀ_id, ਆਕਾਰ(test_ਕੁੰਜੀ_id));
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(info->iv, test_iv, ਆਕਾਰ(test_iv));
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(info->subsamples, test_subsamples, ਆਕਾਰ(test_subsamples));

    copy = av_encryption_info_clone(info);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);

    side_ਅੰਕੜੇ = av_encryption_info_ਜੋੜੋ_side_ਅੰਕੜੇ(info, &side_ਅੰਕੜੇ_ਮਾਪ);
    av_assert0(side_ਅੰਕੜੇ);
    av_assert0(side_ਅੰਕੜੇ_ਮਾਪ > 0);

    copy = av_encryption_info_get_side_ਅੰਕੜੇ(side_ਅੰਕੜੇ, side_ਅੰਕੜੇ_ਮਾਪ);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);
    av_free(side_ਅੰਕੜੇ);

    av_encryption_info_free(info);
}

ਸਥਿਰ AVEncryptionInitInfo *create_init_info(ਖਾਲੀ)
{
    AVEncryptionInitInfo *info;

    info = av_encryption_init_info_alloc(ਆਕਾਰ(test_system_id), 2, ਆਕਾਰ(test_ਕੁੰਜੀ_id), ਆਕਾਰ(test_ਅੰਕੜੇ));
    av_assert0(info);
    av_assert0(info->system_id);
    av_assert0(info->system_id_ਮਾਪ == ਆਕਾਰ(test_system_id));
    av_assert0(info->ਕੁੰਜੀ_ids);
    av_assert0(info->ਅੰਕ_ਕੁੰਜੀ_ids == 2);
    av_assert0(info->ਕੁੰਜੀ_id_ਮਾਪ == ਆਕਾਰ(test_ਕੁੰਜੀ_id));
    av_assert0(info->ਕੁੰਜੀ_ids[0]);
    av_assert0(info->ਕੁੰਜੀ_ids[1]);
    av_assert0(info->ਅੰਕੜੇ);
    av_assert0(info->ਅੰਕੜੇ_ਮਾਪ == ਆਕਾਰ(test_ਅੰਕੜੇ));
    av_assert0(!info->ਅਗਲਾ);

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(info->system_id, test_system_id, ਆਕਾਰ(test_system_id));
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(info->ਕੁੰਜੀ_ids[0], test_ਕੁੰਜੀ_id, ਆਕਾਰ(test_ਕੁੰਜੀ_id));
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(info->ਕੁੰਜੀ_ids[1], test_ਕੁੰਜੀ_id_2, ਆਕਾਰ(test_ਕੁੰਜੀ_id_2));
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(info->ਅੰਕੜੇ, test_ਅੰਕੜੇ, ਆਕਾਰ(test_ਅੰਕੜੇ));

    ਵਾਪਸ info;
}

ਸਥਿਰ ਖਾਲੀ ਲੜੀਵਾਰ_encryption_init_info_test(ਖਾਲੀ)
{
    AVEncryptionInitInfo *info, *copy;
    uint8_t *side_ਅੰਕੜੇ, *appended;
    size_t side_ਅੰਕੜੇ_ਮਾਪ, appended_ਮਾਪ;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ allocated_ਮਾਪ = 0;

    info = create_init_info();

    side_ਅੰਕੜੇ = av_encryption_init_info_ਜੋੜੋ_side_ਅੰਕੜੇ(info, &side_ਅੰਕੜੇ_ਮਾਪ);
    av_assert0(side_ਅੰਕੜੇ);
    av_assert0(side_ਅੰਕੜੇ_ਮਾਪ > 0);
    copy = av_encryption_init_info_get_side_ਅੰਕੜੇ(side_ਅੰਕੜੇ, side_ਅੰਕੜੇ_ਮਾਪ);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);
    av_free(side_ਅੰਕੜੇ);

    // Make the first init info different from the second to test the correct order.
    memset(info->system_id, 0, info->system_id_ਮਾਪ);
    appended = av_encryption_init_info_ਜੋੜੋ_side_ਅੰਕੜੇ(info, &appended_ਮਾਪ);
    av_assert0(appended);
    info->ਅਗਲਾ = create_init_info();
    side_ਅੰਕੜੇ = av_encryption_init_info_ਜੋੜੋ_side_ਅੰਕੜੇ(info, &side_ਅੰਕੜੇ_ਮਾਪ);
    av_assert0(side_ਅੰਕੜੇ);
    copy = av_encryption_init_info_get_side_ਅੰਕੜੇ(side_ਅੰਕੜੇ, side_ਅੰਕੜੇ_ਮਾਪ);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);

    av_assert0(av_encryption_init_info_append_side_ਅੰਕੜੇ(&appended, &appended_ਮਾਪ, &allocated_ਮਾਪ, info->ਅਗਲਾ) == 0);
    av_assert0(appended_ਮਾਪ == side_ਅੰਕੜੇ_ਮਾਪ);
    av_assert0(memcmp(appended, side_ਅੰਕੜੇ, side_ਅੰਕੜੇ_ਮਾਪ) == 0);
    av_free(appended);
    av_free(side_ਅੰਕੜੇ);

    av_encryption_init_info_free(info);
}

ਪੂਰਨ ਮੁੱਖ(ਪੂਰਨ argc, ਅੱਖਰ **argv)
{
    ਲੜੀਵਾਰ_encryption_info_test();
    ਲੜੀਵਾਰ_encryption_init_info_test();
    ਵਾਪਸ 0;
}
