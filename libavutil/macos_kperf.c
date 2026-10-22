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

#تعریف_کړه KPERF_LIST                                             \
    F(صحيح, kpc_get_counting, فراغ)                             \
    F(صحيح, kpc_force_all_ctrs_سېټ, صحيح)                        \
    F(صحيح, kpc_سېټ_counting, uint32_t)                         \
    F(صحيح, kpc_سېټ_thread_counting, uint32_t)                  \
    F(صحيح, kpc_سېټ_config, uint32_t, فراغ *)                   \
    F(صحيح, kpc_get_config, uint32_t, فراغ *)                   \
    F(صحيح, kpc_سېټ_period, uint32_t, فراغ *)                   \
    F(صحيح, kpc_get_period, uint32_t, فراغ *)                   \
    F(uint32_t, kpc_get_counter_شمېر, uint32_t)               \
    F(uint32_t, kpc_get_config_شمېر, uint32_t)                \
    F(صحيح, kperf_sample_get, صحيح *)                            \
    F(صحيح, kpc_get_thread_counters, صحيح, بینښه صحيح, فراغ *)

#تعریف_کړه F(ret, name, ...)                                      \
    تعريفنوع ret name##proc(__VA_ARGS__);                       \
    ساكن name##proc *name = عدم;
KPERF_LIST
#تعریف_لغوه F

#تعریف_کړه CFGWORD_EL0_A32_EN_ماسک (0x10000)
#تعریف_کړه CFGWORD_EL0_A64_EN_ماسک (0x20000)
#تعریف_کړه CFGWORD_EL1_EN_ماسک    (0x40000)
#تعریف_کړه CFGWORD_EL3_EN_ماسک    (0x80000)
#تعریف_کړه CFGWORD_ALLMODES_ماسک (0xf0000)

#تعریف_کړه CPMU_NONE 0
#تعریف_کړه CPMU_CORE_دوره 0x02
#تعریف_کړه CPMU_INST_A64 0x8c
#تعریف_کړه CPMU_INST_BRANCH 0x8d
#تعریف_کړه CPMU_SYNC_DC_بارول_نه_موندنه 0xbf
#تعریف_کړه CPMU_SYNC_DC_STORE_نه_موندنه 0xc0
#تعریف_کړه CPMU_SYNC_DTLB_نه_موندنه 0xc1
#تعریف_کړه CPMU_SYNC_ST_موندنه_YNGR_LD 0xc4
#تعریف_کړه CPMU_SYNC_BR_ANY_MISP 0xcb
#تعریف_کړه CPMU_FED_IC_نه_موندنه_DEM 0xd3
#تعریف_کړه CPMU_FED_ITLB_نه_موندنه 0xd4

#تعریف_کړه KPC_CLASS_FIXED_ماسک        (1 << 0)
#تعریف_کړه KPC_CLASS_CONFIGURABLE_ماسک (1 << 1)
#تعریف_کړه KPC_CLASS_POWER_ماسک        (1 << 2)
#تعریف_کړه KPC_CLASS_RAWPMU_ماسک       (1 << 3)

#تعریف_کړه KPC_MAX_COUNTERS 32
#تعریف_کړه CONFIG_شمېر 8
#تعریف_کړه KPC_ماسک (KPC_CLASS_CONFIGURABLE_ماسک | KPC_CLASS_FIXED_ماسک)

ساكن فراغ kperf_init(فراغ)
{
    uint64_t config[CONFIG_شمېر] = {0};
    فراغ *kperf = عدم;
    uint32_t n;

    av_assert0(kperf = dlopen("/System/Library/PrivateFrameworks/kperf.framework/Versions/A/kperf", RTLD_LAZY));

#تعریف_کړه F(ret, name, ...) av_assert0(name = (name##proc *)(dlsym(kperf, #name)));
    KPERF_LIST
#تعریف_لغوه F

    n = kpc_get_counter_شمېر(KPC_ماسک);
    av_assert0(n <= KPC_MAX_COUNTERS);
    n = kpc_get_config_شمېر(KPC_ماسک);
    av_assert0(n <= CONFIG_شمېر);

    config[0] = CPMU_CORE_دوره | CFGWORD_EL0_A64_EN_ماسک;
    // config[3] = CPMU_INST_BRANCH | CFGWORD_EL0A64EN_MASK;
    // config[4] = CPMU_SYNC_BR_ANY_MISP | CFGWORD_EL0A64EN_MASK;
    // config[5] = CPMU_INST_A64 | CFGWORD_EL0A64EN_MASK;

    av_assert0(kpc_سېټ_config(KPC_ماسک, config) == 0 || !"the kperf API needs to be run as root");
    av_assert0(kpc_force_all_ctrs_سېټ(1) == 0);
    av_assert0(kpc_سېټ_counting(KPC_ماسک) == 0);
    av_assert0(kpc_سېټ_thread_counting(KPC_ماسک) == 0);
}

فراغ ff_kperf_init(فراغ)
{
    ساكن AVOnce init_static_once = AV_ONCE_INIT;
    ff_thread_once(&init_static_once, kperf_init);
}

uint64_t ff_kperf_دورې(فراغ)
{
    uint64_t counters[KPC_MAX_COUNTERS];

    إذا (kpc_get_thread_counters(0, KPC_MAX_COUNTERS, counters)) {
        أرجع -1;
    }

    أرجع counters[0];
}
