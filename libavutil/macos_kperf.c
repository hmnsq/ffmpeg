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

#شامل "avassert.h"
#شامل "macos_kperf.h"
#شامل "thread.h"

#شامل <stdio.h>
#شامل <stdlib.h>
#شامل <dlfcn.h>

#define KPERF_LIST                                             \
    F(صحیح, kpc_get_counting, تهی)                             \
    F(صحیح, kpc_force_all_ctrs_set, صحیح)                        \
    F(صحیح, kpc_set_counting, uint32_t)                         \
    F(صحیح, kpc_set_thread_counting, uint32_t)                  \
    F(صحیح, kpc_set_config, uint32_t, تهی *)                   \
    F(صحیح, kpc_get_config, uint32_t, تهی *)                   \
    F(صحیح, kpc_set_period, uint32_t, تهی *)                   \
    F(صحیح, kpc_get_period, uint32_t, تهی *)                   \
    F(uint32_t, kpc_get_counter_شمار, uint32_t)               \
    F(uint32_t, kpc_get_config_شمار, uint32_t)                \
    F(صحیح, kperf_sample_get, صحیح *)                            \
    F(صحیح, kpc_get_thread_counters, صحیح, unsigned صحیح, تهی *)

#define F(ret, name, ...)                                      \
    تعریفنوع ret name##proc(__VA_ARGS__);                       \
    ایستا name##proc *name = پوچ;
KPERF_LIST
#undef F

#define CFGWORD_EL0A32EN_MASK (0x10000)
#define CFGWORD_EL0A64EN_MASK (0x20000)
#define CFGWORD_EL1EN_MASK    (0x40000)
#define CFGWORD_EL3EN_MASK    (0x80000)
#define CFGWORD_ALLMODES_MASK (0xf0000)

#define CPMU_NONE 0
#define CPMU_CORE_CYCLE 0x02
#define CPMU_INST_A64 0x8c
#define CPMU_INST_BRANCH 0x8d
#define CPMU_SYNC_DC_LOAD_MISS 0xbf
#define CPMU_SYNC_DC_STORE_MISS 0xc0
#define CPMU_SYNC_DTLB_MISS 0xc1
#define CPMU_SYNC_ST_HIT_YNGR_LD 0xc4
#define CPMU_SYNC_BR_ANY_MISP 0xcb
#define CPMU_FED_IC_MISS_DEM 0xd3
#define CPMU_FED_ITLB_MISS 0xd4

#define KPC_CLASS_FIXED_MASK        (1 << 0)
#define KPC_CLASS_CONFIGURABLE_MASK (1 << 1)
#define KPC_CLASS_POWER_MASK        (1 << 2)
#define KPC_CLASS_RAWPMU_MASK       (1 << 3)

#define KPC_MAX_COUNTERS 32
#define CONFIG_شمار 8
#define KPC_MASK (KPC_CLASS_CONFIGURABLE_MASK | KPC_CLASS_FIXED_MASK)

ایستا تهی kperf_init(تهی)
{
    uint64_t config[CONFIG_شمار] = {0};
    تهی *kperf = پوچ;
    uint32_t n;

    av_assert0(kperf = dlopen("/System/Library/PrivateFrameworks/kperf.framework/Versions/A/kperf", RTLD_LAZY));

#define F(ret, name, ...) av_assert0(name = (name##proc *)(dlsym(kperf, #name)));
    KPERF_LIST
#undef F

    n = kpc_get_counter_شمار(KPC_MASK);
    av_assert0(n <= KPC_MAX_COUNTERS);
    n = kpc_get_config_شمار(KPC_MASK);
    av_assert0(n <= CONFIG_شمار);

    config[0] = CPMU_CORE_CYCLE | CFGWORD_EL0A64EN_MASK;
    // config[3] = CPMU_INST_BRANCH | CFGWORD_EL0A64EN_MASK;
    // config[4] = CPMU_SYNC_BR_ANY_MISP | CFGWORD_EL0A64EN_MASK;
    // config[5] = CPMU_INST_A64 | CFGWORD_EL0A64EN_MASK;

    av_assert0(kpc_set_config(KPC_MASK, config) == 0 || !"the kperf API needs to be run as root");
    av_assert0(kpc_force_all_ctrs_set(1) == 0);
    av_assert0(kpc_set_counting(KPC_MASK) == 0);
    av_assert0(kpc_set_thread_counting(KPC_MASK) == 0);
}

تهی ff_kperf_init(تهی)
{
    ایستا AVOnce init_static_once = AV_ONCE_INIT;
    ff_thread_once(&init_static_once, kperf_init);
}

uint64_t ff_kperf_cycles(تهی)
{
    uint64_t counters[KPC_MAX_COUNTERS];

    اگر (kpc_get_thread_counters(0, KPC_MAX_COUNTERS, counters)) {
        بازگشت -1;
    }

    بازگشت counters[0];
}
