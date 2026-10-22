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

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macos_kperf.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "thread.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <dlfcn.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ KPERF_LIST                                             \
    F(ਪੂਰਨ, kpc_get_counting, ਖਾਲੀ)                             \
    F(ਪੂਰਨ, kpc_force_all_ctrs_ਸੈੱਟ, ਪੂਰਨ)                        \
    F(ਪੂਰਨ, kpc_ਸੈੱਟ_counting, uint32_t)                         \
    F(ਪੂਰਨ, kpc_ਸੈੱਟ_thread_counting, uint32_t)                  \
    F(ਪੂਰਨ, kpc_ਸੈੱਟ_config, uint32_t, ਖਾਲੀ *)                   \
    F(ਪੂਰਨ, kpc_get_config, uint32_t, ਖਾਲੀ *)                   \
    F(ਪੂਰਨ, kpc_ਸੈੱਟ_period, uint32_t, ਖਾਲੀ *)                   \
    F(ਪੂਰਨ, kpc_get_period, uint32_t, ਖਾਲੀ *)                   \
    F(uint32_t, kpc_get_counter_ਗਿਣਤੀ, uint32_t)               \
    F(uint32_t, kpc_get_config_ਗਿਣਤੀ, uint32_t)                \
    F(ਪੂਰਨ, kperf_sample_get, ਪੂਰਨ *)                            \
    F(ਪੂਰਨ, kpc_get_thread_counters, ਪੂਰਨ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ, ਖਾਲੀ *)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ F(ret, name, ...)                                      \
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ret name##proc(__VA_ARGS__);                       \
    ਸਥਿਰ name##proc *name = ਨਿਰਾ;
KPERF_LIST
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ F

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CFGWORD_EL0_A32_EN_ਨਕਾਬ (0x10000)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CFGWORD_EL0_A64_EN_ਨਕਾਬ (0x20000)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CFGWORD_EL1_EN_ਨਕਾਬ    (0x40000)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CFGWORD_EL3_EN_ਨਕਾਬ    (0x80000)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CFGWORD_ALLMODES_ਨਕਾਬ (0xf0000)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPMU_NONE 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPMU_CORE_ਚੱਕਰ 0x02
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPMU_INST_A64 0x8c
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPMU_INST_BRANCH 0x8d
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPMU_SYNC_DC_ਲੱਦੋ_ਖੁੰਝ 0xbf
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPMU_SYNC_DC_STORE_ਖੁੰਝ 0xc0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPMU_SYNC_DTLB_ਖੁੰਝ 0xc1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPMU_SYNC_ST_ਪ੍ਰਾਪਤੀ_YNGR_LD 0xc4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPMU_SYNC_BR_ANY_MISP 0xcb
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPMU_FED_IC_ਖੁੰਝ_DEM 0xd3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPMU_FED_ITLB_ਖੁੰਝ 0xd4

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ KPC_CLASS_FIXED_ਨਕਾਬ        (1 << 0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ KPC_CLASS_CONFIGURABLE_ਨਕਾਬ (1 << 1)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ KPC_CLASS_POWER_ਨਕਾਬ        (1 << 2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ KPC_CLASS_RAWPMU_ਨਕਾਬ       (1 << 3)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ KPC_MAX_COUNTERS 32
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CONFIG_ਗਿਣਤੀ 8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ KPC_ਨਕਾਬ (KPC_CLASS_CONFIGURABLE_ਨਕਾਬ | KPC_CLASS_FIXED_ਨਕਾਬ)

ਸਥਿਰ ਖਾਲੀ kperf_init(ਖਾਲੀ)
{
    uint64_t config[CONFIG_ਗਿਣਤੀ] = {0};
    ਖਾਲੀ *kperf = ਨਿਰਾ;
    uint32_t n;

    av_assert0(kperf = dlopen("/System/Library/PrivateFrameworks/kperf.framework/Versions/A/kperf", RTLD_LAZY));

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ F(ret, name, ...) av_assert0(name = (name##proc *)(dlsym(kperf, #name)));
    KPERF_LIST
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ F

    n = kpc_get_counter_ਗਿਣਤੀ(KPC_ਨਕਾਬ);
    av_assert0(n <= KPC_MAX_COUNTERS);
    n = kpc_get_config_ਗਿਣਤੀ(KPC_ਨਕਾਬ);
    av_assert0(n <= CONFIG_ਗਿਣਤੀ);

    config[0] = CPMU_CORE_ਚੱਕਰ | CFGWORD_EL0_A64_EN_ਨਕਾਬ;
    // config[3] = CPMU_INST_BRANCH | CFGWORD_EL0A64EN_MASK;
    // config[4] = CPMU_SYNC_BR_ANY_MISP | CFGWORD_EL0A64EN_MASK;
    // config[5] = CPMU_INST_A64 | CFGWORD_EL0A64EN_MASK;

    av_assert0(kpc_ਸੈੱਟ_config(KPC_ਨਕਾਬ, config) == 0 || !"the kperf API needs to be run as root");
    av_assert0(kpc_force_all_ctrs_ਸੈੱਟ(1) == 0);
    av_assert0(kpc_ਸੈੱਟ_counting(KPC_ਨਕਾਬ) == 0);
    av_assert0(kpc_ਸੈੱਟ_thread_counting(KPC_ਨਕਾਬ) == 0);
}

ਖਾਲੀ ff_kperf_init(ਖਾਲੀ)
{
    ਸਥਿਰ AVOnce init_static_once = AV_ONCE_INIT;
    ff_thread_once(&init_static_once, kperf_init);
}

uint64_t ff_kperf_ਚੱਕਰਾਂ(ਖਾਲੀ)
{
    uint64_t counters[KPC_MAX_COUNTERS];

    ਜੇ (kpc_get_thread_counters(0, KPC_MAX_COUNTERS, counters)) {
        ਵਾਪਸ -1;
    }

    ਵਾਪਸ counters[0];
}
