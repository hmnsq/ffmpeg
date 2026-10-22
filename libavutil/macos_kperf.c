/*
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with FFmpeg; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ضمن "avassert.h"
#ضمن "macos_kperf.h"
#ضمن "thread.h"

#ضمن <stdio.h>
#ضمن <stdlib.h>
#ضمن <dlfcn.h>

#وصف_ڪريو KPERF_LIST                                             \
    F(صحيح, kpc_get_counting, فراغ)                             \
    F(صحيح, kpc_force_all_ctrs_سيٽ, صحيح)                        \
    F(صحيح, kpc_سيٽ_counting, uint32_t)                         \
    F(صحيح, kpc_سيٽ_thread_counting, uint32_t)                  \
    F(صحيح, kpc_سيٽ_config, uint32_t, فراغ *)                   \
    F(صحيح, kpc_get_config, uint32_t, فراغ *)                   \
    F(صحيح, kpc_سيٽ_period, uint32_t, فراغ *)                   \
    F(صحيح, kpc_get_period, uint32_t, فراغ *)                   \
    F(uint32_t, kpc_get_counter_ڳڻپ, uint32_t)               \
    F(uint32_t, kpc_get_config_ڳڻپ, uint32_t)                \
    F(صحيح, kperf_sample_get, صحيح *)                            \
    F(صحيح, kpc_get_thread_counters, صحيح, بنانشان صحيح, فراغ *)

#وصف_ڪريو F(ret, name, ...)                                      \
    تعريفنوع ret name##proc(__VA_ARGS__);                       \
    ساكن name##proc *name = عدم;
KPERF_LIST
#وصف_رد F

#وصف_ڪريو CFGWORD_EL0_A32_EN_نقاب (0x10000)
#وصف_ڪريو CFGWORD_EL0_A64_EN_نقاب (0x20000)
#وصف_ڪريو CFGWORD_EL1_EN_نقاب    (0x40000)
#وصف_ڪريو CFGWORD_EL3_EN_نقاب    (0x80000)
#وصف_ڪريو CFGWORD_ALLMODES_نقاب (0xf0000)

#وصف_ڪريو CPMU_NONE 0
#وصف_ڪريو CPMU_CORE_چڪر 0x02
#وصف_ڪريو CPMU_INST_A64 0x8c
#وصف_ڪريو CPMU_INST_BRANCH 0x8d
#وصف_ڪريو CPMU_SYNC_DC_ڀريو_ناڪامي 0xbf
#وصف_ڪريو CPMU_SYNC_DC_STORE_ناڪامي 0xc0
#وصف_ڪريو CPMU_SYNC_DTLB_ناڪامي 0xc1
#وصف_ڪريو CPMU_SYNC_ST_ڪاميابي_YNGR_LD 0xc4
#وصف_ڪريو CPMU_SYNC_BR_ANY_MISP 0xcb
#وصف_ڪريو CPMU_FED_IC_ناڪامي_DEM 0xd3
#وصف_ڪريو CPMU_FED_ITLB_ناڪامي 0xd4

#وصف_ڪريو KPC_CLASS_FIXED_نقاب        (1 << 0)
#وصف_ڪريو KPC_CLASS_CONFIGURABLE_نقاب (1 << 1)
#وصف_ڪريو KPC_CLASS_POWER_نقاب        (1 << 2)
#وصف_ڪريو KPC_CLASS_RAWPMU_نقاب       (1 << 3)

#وصف_ڪريو KPC_MAX_COUNTERS 32
#وصف_ڪريو CONFIG_ڳڻپ 8
#وصف_ڪريو KPC_نقاب (KPC_CLASS_CONFIGURABLE_نقاب | KPC_CLASS_FIXED_نقاب)

ساكن فراغ kperf_init(فراغ)
{
    uint64_t config[CONFIG_ڳڻپ] = {0};
    فراغ *kperf = عدم;
    uint32_t n;

    av_assert0(kperf = dlopen("/System/Library/PrivateFrameworks/kperf.framework/Versions/A/kperf", RTLD_LAZY));

#وصف_ڪريو F(ret, name, ...) av_assert0(name = (name##proc *)(dlsym(kperf, #name)));
    KPERF_LIST
#وصف_رد F

    n = kpc_get_counter_ڳڻپ(KPC_نقاب);
    av_assert0(n <= KPC_MAX_COUNTERS);
    n = kpc_get_config_ڳڻپ(KPC_نقاب);
    av_assert0(n <= CONFIG_ڳڻپ);

    config[0] = CPMU_CORE_چڪر | CFGWORD_EL0_A64_EN_نقاب;
    // config[3] = CPMU_INST_BRANCH | CFGWORD_EL0A64EN_MASK;
    // config[4] = CPMU_SYNC_BR_ANY_MISP | CFGWORD_EL0A64EN_MASK;
    // config[5] = CPMU_INST_A64 | CFGWORD_EL0A64EN_MASK;

    av_assert0(kpc_سيٽ_config(KPC_نقاب, config) == 0 || !"the kperf API needs to be run as root");
    av_assert0(kpc_force_all_ctrs_سيٽ(1) == 0);
    av_assert0(kpc_سيٽ_counting(KPC_نقاب) == 0);
    av_assert0(kpc_سيٽ_thread_counting(KPC_نقاب) == 0);
}

فراغ ff_kperf_init(فراغ)
{
    ساكن AVOnce init_static_once = AV_ONCE_INIT;
    ff_thread_once(&init_static_once, kperf_init);
}

uint64_t ff_kperf_چڪرن(فراغ)
{
    uint64_t counters[KPC_MAX_COUNTERS];

    إذا (kpc_get_thread_counters(0, KPC_MAX_COUNTERS, counters)) {
        أرجع -1;
    }

    أرجع counters[0];
}
