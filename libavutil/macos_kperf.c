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

#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "macos_kperf.h"
#અન્તર્ભાવ "thread.h"

#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <dlfcn.h>

#define KPERF_LIST                                             \
    F(પૂર્ણાંક, kpc_get_counting, શૂન્ય)                             \
    F(પૂર્ણાંક, kpc_force_all_ctrs_set, પૂર્ણાંક)                        \
    F(પૂર્ણાંક, kpc_set_counting, uint32_t)                         \
    F(પૂર્ણાંક, kpc_set_thread_counting, uint32_t)                  \
    F(પૂર્ણાંક, kpc_set_config, uint32_t, શૂન્ય *)                   \
    F(પૂર્ણાંક, kpc_get_config, uint32_t, શૂન્ય *)                   \
    F(પૂર્ણાંક, kpc_set_period, uint32_t, શૂન્ય *)                   \
    F(પૂર્ણાંક, kpc_get_period, uint32_t, શૂન્ય *)                   \
    F(uint32_t, kpc_get_counter_ગણતરી, uint32_t)               \
    F(uint32_t, kpc_get_config_ગણતરી, uint32_t)                \
    F(પૂર્ણાંક, kperf_sample_get, પૂર્ણાંક *)                            \
    F(પૂર્ણાંક, kpc_get_thread_counters, પૂર્ણાંક, unsigned પૂર્ણાંક, શૂન્ય *)

#define F(ret, name, ...)                                      \
    પ્રકારવ્યાખ્યા ret name##proc(__VA_ARGS__);                       \
    સ્થિર name##proc *name = ખાલી;
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
#define CONFIG_ગણતરી 8
#define KPC_MASK (KPC_CLASS_CONFIGURABLE_MASK | KPC_CLASS_FIXED_MASK)

સ્થિર શૂન્ય kperf_init(શૂન્ય)
{
    uint64_t config[CONFIG_ગણતરી] = {0};
    શૂન્ય *kperf = ખાલી;
    uint32_t n;

    av_assert0(kperf = dlopen("/System/Library/PrivateFrameworks/kperf.framework/Versions/A/kperf", RTLD_LAZY));

#define F(ret, name, ...) av_assert0(name = (name##proc *)(dlsym(kperf, #name)));
    KPERF_LIST
#undef F

    n = kpc_get_counter_ગણતરી(KPC_MASK);
    av_assert0(n <= KPC_MAX_COUNTERS);
    n = kpc_get_config_ગણતરી(KPC_MASK);
    av_assert0(n <= CONFIG_ગણતરી);

    config[0] = CPMU_CORE_CYCLE | CFGWORD_EL0A64EN_MASK;
    // config[3] = CPMU_INST_BRANCH | CFGWORD_EL0A64EN_MASK;
    // config[4] = CPMU_SYNC_BR_ANY_MISP | CFGWORD_EL0A64EN_MASK;
    // config[5] = CPMU_INST_A64 | CFGWORD_EL0A64EN_MASK;

    av_assert0(kpc_set_config(KPC_MASK, config) == 0 || !"the kperf API needs to be run as root");
    av_assert0(kpc_force_all_ctrs_set(1) == 0);
    av_assert0(kpc_set_counting(KPC_MASK) == 0);
    av_assert0(kpc_set_thread_counting(KPC_MASK) == 0);
}

શૂન્ય ff_kperf_init(શૂન્ય)
{
    સ્થિર AVOnce init_static_once = AV_ONCE_INIT;
    ff_thread_once(&init_static_once, kperf_init);
}

uint64_t ff_kperf_cycles(શૂન્ય)
{
    uint64_t counters[KPC_MAX_COUNTERS];

    જો (kpc_get_thread_counters(0, KPC_MAX_COUNTERS, counters)) {
        પાછા -1;
    }

    પાછા counters[0];
}
