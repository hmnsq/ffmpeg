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

#అన్తర్భావ "libavutil/encryption_info.h"

#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "libavutil/avassert.h"
#అన్తర్భావ "libavutil/mem.h"

స్థిర స్థిరరాశి AVSubsampleEncryptionInfo test_subsamples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
స్థిర స్థిరరాశి size_t test_subsample_లెక్క = పరిమాణం(test_subsamples) / పరిమాణం(test_subsamples[0]);
స్థిర స్థిరరాశి uint8_t test_iv[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
స్థిర స్థిరరాశి uint8_t test_కీలకం_id[] = {0x21, 0x22, 0x23, 0x24};
స్థిర స్థిరరాశి uint8_t test_కీలకం_id_2[] = {0x31, 0x32, 0x33, 0x34};
స్థిర స్థిరరాశి uint8_t test_system_id[] = {0x41, 0x42, 0x43};
స్థిర స్థిరరాశి uint8_t test_దత్తాంశం[] = {0x51, 0x52};

స్థిర పూర్ణాంకం compare_encryption_info(స్థిరరాశి AVEncryptionInfo *a, స్థిరరాశి AVEncryptionInfo *b) {
    ఒకవేళ (!a || !b || a->scheme != b->scheme || a->crypt_byte_ఖండం != b->crypt_byte_ఖండం ||
        a->skip_byte_ఖండం != b->skip_byte_ఖండం || a->కీలకం_id_కొలత != b->కీలకం_id_కొలత ||
        a->iv_కొలత != b->iv_కొలత || a->subsample_లెక్క != b->subsample_లెక్క)
        తిరిగి 1;

    ఒకవేళ (memcmp(a->కీలకం_id, b->కీలకం_id, a->కీలకం_id_కొలత) != 0 ||
        memcmp(a->iv, b->iv, a->iv_కొలత) != 0 ||
        memcmp(a->subsamples, b->subsamples, a->subsample_లెక్క * పరిమాణం(a->subsamples[0])))
        తిరిగి 1;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం compare_encryption_init_info(స్థిరరాశి AVEncryptionInitInfo *a, స్థిరరాశి AVEncryptionInitInfo *b) {
    ఒకవేళ (!a || !b || a->system_id_కొలత != b->system_id_కొలత ||
        a->అంకె_కీలకం_ids != b->అంకె_కీలకం_ids || a->కీలకం_id_కొలత != b->కీలకం_id_కొలత ||
        a->దత్తాంశం_కొలత != b->దత్తాంశం_కొలత)
        తిరిగి 1;

    ఒకవేళ (memcmp(a->system_id, b->system_id, a->system_id_కొలత) != 0 ||
        memcmp(a->దత్తాంశం, b->దత్తాంశం, a->దత్తాంశం_కొలత) != 0)
        తిరిగి 1;

    కొరకు (uint32_t i = 0; i < a->అంకె_కీలకం_ids; i++) {
        ఒకవేళ (memcmp(a->కీలకం_ids[i], b->కీలకం_ids[i], a->కీలకం_id_కొలత) != 0)
            తిరిగి 1;
    }

    ఒకవేళ (a->తదుపరి || b->తదుపరి) {
        ఒకవేళ (!a->తదుపరి || !b->తదుపరి)
            తిరిగి 1;
        ఒకవేళ (compare_encryption_init_info(a->తదుపరి, b->తదుపరి) != 0)
            తిరిగి 1;
    }

    తిరిగి 0;
}

స్థిర శూన్య నిరంతరం_encryption_info_test(శూన్య)
{
    AVEncryptionInfo *info, *copy;
    uint8_t *side_దత్తాంశం;
    size_t side_దత్తాంశం_కొలత;

    info = av_encryption_info_alloc(test_subsample_లెక్క, పరిమాణం(test_కీలకం_id), పరిమాణం(test_iv));
    av_assert0(info);
    av_assert0(info->కీలకం_id);
    av_assert0(info->కీలకం_id_కొలత == పరిమాణం(test_కీలకం_id));
    av_assert0(info->iv);
    av_assert0(info->iv_కొలత == పరిమాణం(test_iv));
    av_assert0(info->subsamples);
    av_assert0(info->subsample_లెక్క == test_subsample_లెక్క);

    info->scheme = 1234;
    info->crypt_byte_ఖండం = 333;
    info->skip_byte_ఖండం = 444;
    జ్ఞాపకం_నకలు(info->కీలకం_id, test_కీలకం_id, పరిమాణం(test_కీలకం_id));
    జ్ఞాపకం_నకలు(info->iv, test_iv, పరిమాణం(test_iv));
    జ్ఞాపకం_నకలు(info->subsamples, test_subsamples, పరిమాణం(test_subsamples));

    copy = av_encryption_info_clone(info);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);

    side_దత్తాంశం = av_encryption_info_కూడు_side_దత్తాంశం(info, &side_దత్తాంశం_కొలత);
    av_assert0(side_దత్తాంశం);
    av_assert0(side_దత్తాంశం_కొలత > 0);

    copy = av_encryption_info_get_side_దత్తాంశం(side_దత్తాంశం, side_దత్తాంశం_కొలత);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);
    av_free(side_దత్తాంశం);

    av_encryption_info_free(info);
}

స్థిర AVEncryptionInitInfo *create_init_info(శూన్య)
{
    AVEncryptionInitInfo *info;

    info = av_encryption_init_info_alloc(పరిమాణం(test_system_id), 2, పరిమాణం(test_కీలకం_id), పరిమాణం(test_దత్తాంశం));
    av_assert0(info);
    av_assert0(info->system_id);
    av_assert0(info->system_id_కొలత == పరిమాణం(test_system_id));
    av_assert0(info->కీలకం_ids);
    av_assert0(info->అంకె_కీలకం_ids == 2);
    av_assert0(info->కీలకం_id_కొలత == పరిమాణం(test_కీలకం_id));
    av_assert0(info->కీలకం_ids[0]);
    av_assert0(info->కీలకం_ids[1]);
    av_assert0(info->దత్తాంశం);
    av_assert0(info->దత్తాంశం_కొలత == పరిమాణం(test_దత్తాంశం));
    av_assert0(!info->తదుపరి);

    జ్ఞాపకం_నకలు(info->system_id, test_system_id, పరిమాణం(test_system_id));
    జ్ఞాపకం_నకలు(info->కీలకం_ids[0], test_కీలకం_id, పరిమాణం(test_కీలకం_id));
    జ్ఞాపకం_నకలు(info->కీలకం_ids[1], test_కీలకం_id_2, పరిమాణం(test_కీలకం_id_2));
    జ్ఞాపకం_నకలు(info->దత్తాంశం, test_దత్తాంశం, పరిమాణం(test_దత్తాంశం));

    తిరిగి info;
}

స్థిర శూన్య నిరంతరం_encryption_init_info_test(శూన్య)
{
    AVEncryptionInitInfo *info, *copy;
    uint8_t *side_దత్తాంశం, *appended;
    size_t side_దత్తాంశం_కొలత, appended_కొలత;
    గుర్తులేని పూర్ణాంకం allocated_కొలత = 0;

    info = create_init_info();

    side_దత్తాంశం = av_encryption_init_info_కూడు_side_దత్తాంశం(info, &side_దత్తాంశం_కొలత);
    av_assert0(side_దత్తాంశం);
    av_assert0(side_దత్తాంశం_కొలత > 0);
    copy = av_encryption_init_info_get_side_దత్తాంశం(side_దత్తాంశం, side_దత్తాంశం_కొలత);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);
    av_free(side_దత్తాంశం);

    // Make the first init info different from the second to test the correct order.
    memset(info->system_id, 0, info->system_id_కొలత);
    appended = av_encryption_init_info_కూడు_side_దత్తాంశం(info, &appended_కొలత);
    av_assert0(appended);
    info->తదుపరి = create_init_info();
    side_దత్తాంశం = av_encryption_init_info_కూడు_side_దత్తాంశం(info, &side_దత్తాంశం_కొలత);
    av_assert0(side_దత్తాంశం);
    copy = av_encryption_init_info_get_side_దత్తాంశం(side_దత్తాంశం, side_దత్తాంశం_కొలత);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);

    av_assert0(av_encryption_init_info_append_side_దత్తాంశం(&appended, &appended_కొలత, &allocated_కొలత, info->తదుపరి) == 0);
    av_assert0(appended_కొలత == side_దత్తాంశం_కొలత);
    av_assert0(memcmp(appended, side_దత్తాంశం, side_దత్తాంశం_కొలత) == 0);
    av_free(appended);
    av_free(side_దత్తాంశం);

    av_encryption_init_info_free(info);
}

పూర్ణాంకం ప్రధాన(పూర్ణాంకం argc, అక్షరం **argv)
{
    నిరంతరం_encryption_info_test();
    నిరంతరం_encryption_init_info_test();
    తిరిగి 0;
}
