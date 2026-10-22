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

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "macos_kperf.h"
#అన్తర్భావ "thread.h"

#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <dlfcn.h>

#నిర్వచించు KPERF_LIST                                             \
    F(పూర్ణాంకం, kpc_get_counting, శూన్య)                             \
    F(పూర్ణాంకం, kpc_force_all_ctrs_సమితి, పూర్ణాంకం)                        \
    F(పూర్ణాంకం, kpc_సమితి_counting, uint32_t)                         \
    F(పూర్ణాంకం, kpc_సమితి_thread_counting, uint32_t)                  \
    F(పూర్ణాంకం, kpc_సమితి_config, uint32_t, శూన్య *)                   \
    F(పూర్ణాంకం, kpc_get_config, uint32_t, శూన్య *)                   \
    F(పూర్ణాంకం, kpc_సమితి_period, uint32_t, శూన్య *)                   \
    F(పూర్ణాంకం, kpc_get_period, uint32_t, శూన్య *)                   \
    F(uint32_t, kpc_get_counter_లెక్క, uint32_t)               \
    F(uint32_t, kpc_get_config_లెక్క, uint32_t)                \
    F(పూర్ణాంకం, kperf_sample_get, పూర్ణాంకం *)                            \
    F(పూర్ణాంకం, kpc_get_thread_counters, పూర్ణాంకం, గుర్తులేని పూర్ణాంకం, శూన్య *)

#నిర్వచించు F(ret, name, ...)                                      \
    రకనిర్వచనం ret name##proc(__VA_ARGS__);                       \
    స్థిర name##proc *name = ఖాళీ;
KPERF_LIST
#నిర్వచనం_రద్దు F

#నిర్వచించు CFGWORD_EL0_A32_EN_ముసుగు (0x10000)
#నిర్వచించు CFGWORD_EL0_A64_EN_ముసుగు (0x20000)
#నిర్వచించు CFGWORD_EL1_EN_ముసుగు    (0x40000)
#నిర్వచించు CFGWORD_EL3_EN_ముసుగు    (0x80000)
#నిర్వచించు CFGWORD_ALLMODES_ముసుగు (0xf0000)

#నిర్వచించు CPMU_NONE 0
#నిర్వచించు CPMU_CORE_చక్రం 0x02
#నిర్వచించు CPMU_INST_A64 0x8c
#నిర్వచించు CPMU_INST_BRANCH 0x8d
#నిర్వచించు CPMU_SYNC_DC_ఎక్కించు_తప్పిపోవు 0xbf
#నిర్వచించు CPMU_SYNC_DC_STORE_తప్పిపోవు 0xc0
#నిర్వచించు CPMU_SYNC_DTLB_తప్పిపోవు 0xc1
#నిర్వచించు CPMU_SYNC_ST_తగిలింది_YNGR_LD 0xc4
#నిర్వచించు CPMU_SYNC_BR_ANY_MISP 0xcb
#నిర్వచించు CPMU_FED_IC_తప్పిపోవు_DEM 0xd3
#నిర్వచించు CPMU_FED_ITLB_తప్పిపోవు 0xd4

#నిర్వచించు KPC_CLASS_FIXED_ముసుగు        (1 << 0)
#నిర్వచించు KPC_CLASS_CONFIGURABLE_ముసుగు (1 << 1)
#నిర్వచించు KPC_CLASS_POWER_ముసుగు        (1 << 2)
#నిర్వచించు KPC_CLASS_RAWPMU_ముసుగు       (1 << 3)

#నిర్వచించు KPC_MAX_COUNTERS 32
#నిర్వచించు CONFIG_లెక్క 8
#నిర్వచించు KPC_ముసుగు (KPC_CLASS_CONFIGURABLE_ముసుగు | KPC_CLASS_FIXED_ముసుగు)

స్థిర శూన్య kperf_init(శూన్య)
{
    uint64_t config[CONFIG_లెక్క] = {0};
    శూన్య *kperf = ఖాళీ;
    uint32_t n;

    av_assert0(kperf = dlopen("/System/Library/PrivateFrameworks/kperf.framework/Versions/A/kperf", RTLD_LAZY));

#నిర్వచించు F(ret, name, ...) av_assert0(name = (name##proc *)(dlsym(kperf, #name)));
    KPERF_LIST
#నిర్వచనం_రద్దు F

    n = kpc_get_counter_లెక్క(KPC_ముసుగు);
    av_assert0(n <= KPC_MAX_COUNTERS);
    n = kpc_get_config_లెక్క(KPC_ముసుగు);
    av_assert0(n <= CONFIG_లెక్క);

    config[0] = CPMU_CORE_చక్రం | CFGWORD_EL0_A64_EN_ముసుగు;
    // config[3] = CPMU_INST_BRANCH | CFGWORD_EL0A64EN_MASK;
    // config[4] = CPMU_SYNC_BR_ANY_MISP | CFGWORD_EL0A64EN_MASK;
    // config[5] = CPMU_INST_A64 | CFGWORD_EL0A64EN_MASK;

    av_assert0(kpc_సమితి_config(KPC_ముసుగు, config) == 0 || !"the kperf API needs to be run as root");
    av_assert0(kpc_force_all_ctrs_సమితి(1) == 0);
    av_assert0(kpc_సమితి_counting(KPC_ముసుగు) == 0);
    av_assert0(kpc_సమితి_thread_counting(KPC_ముసుగు) == 0);
}

శూన్య ff_kperf_init(శూన్య)
{
    స్థిర AVOnce init_static_once = AV_ONCE_INIT;
    ff_thread_once(&init_static_once, kperf_init);
}

uint64_t ff_kperf_చక్రాలు(శూన్య)
{
    uint64_t counters[KPC_MAX_COUNTERS];

    ఒకవేళ (kpc_get_thread_counters(0, KPC_MAX_COUNTERS, counters)) {
        తిరిగి -1;
    }

    తిరిగి counters[0];
}
