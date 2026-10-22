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

#समावेश "avassert.h"
#समावेश "macos_kperf.h"
#समावेश "thread.h"

#समावेश <stdio.h>
#समावेश <stdlib.h>
#समावेश <dlfcn.h>

#घोषणा KPERF_LIST                                             \
    F(पूर्णांक, kpc_get_counting, व्योम)                             \
    F(पूर्णांक, kpc_force_all_ctrs_set, पूर्णांक)                        \
    F(पूर्णांक, kpc_set_counting, uint32_t)                         \
    F(पूर्णांक, kpc_set_thread_counting, uint32_t)                  \
    F(पूर्णांक, kpc_set_config, uint32_t, व्योम *)                   \
    F(पूर्णांक, kpc_get_config, uint32_t, व्योम *)                   \
    F(पूर्णांक, kpc_set_period, uint32_t, व्योम *)                   \
    F(पूर्णांक, kpc_get_period, uint32_t, व्योम *)                   \
    F(uint32_t, kpc_get_गणक_गिनती, uint32_t)               \
    F(uint32_t, kpc_get_config_गिनती, uint32_t)                \
    F(पूर्णांक, kperf_sample_get, पूर्णांक *)                            \
    F(पूर्णांक, kpc_get_thread_counters, पूर्णांक, अचिन्हित पूर्णांक, व्योम *)

#घोषणा F(ret, name, ...)                                      \
    प्रकार ret name##proc(__VA_ARGS__);                       \
    अटल name##proc *name = शून्य;
KPERF_LIST
#अघोषित F

#घोषणा CFGWORD_EL0A32EN_MASK (0x10000)
#घोषणा CFGWORD_EL0A64EN_MASK (0x20000)
#घोषणा CFGWORD_EL1EN_MASK    (0x40000)
#घोषणा CFGWORD_EL3EN_MASK    (0x80000)
#घोषणा CFGWORD_ALLMODES_MASK (0xf0000)

#घोषणा CPMU_NONE 0
#घोषणा CPMU_CORE_CYCLE 0x02
#घोषणा CPMU_INST_A64 0x8c
#घोषणा CPMU_INST_BRANCH 0x8d
#घोषणा CPMU_SYNC_DC_LOAD_MISS 0xbf
#घोषणा CPMU_SYNC_DC_STORE_MISS 0xc0
#घोषणा CPMU_SYNC_DTLB_MISS 0xc1
#घोषणा CPMU_SYNC_ST_HIT_YNGR_LD 0xc4
#घोषणा CPMU_SYNC_BR_ANY_MISP 0xcb
#घोषणा CPMU_FED_IC_MISS_DEM 0xd3
#घोषणा CPMU_FED_ITLB_MISS 0xd4

#घोषणा KPC_CLASS_FIXED_MASK        (1 << 0)
#घोषणा KPC_CLASS_CONFIGURABLE_MASK (1 << 1)
#घोषणा KPC_CLASS_POWER_MASK        (1 << 2)
#घोषणा KPC_CLASS_RAWPMU_MASK       (1 << 3)

#घोषणा KPC_MAX_COUNTERS 32
#घोषणा CONFIG_गिनती 8
#घोषणा KPC_MASK (KPC_CLASS_CONFIGURABLE_MASK | KPC_CLASS_FIXED_MASK)

अटल व्योम kperf_init(व्योम)
{
    uint64_t config[CONFIG_गिनती] = {0};
    व्योम *kperf = शून्य;
    uint32_t n;

    av_assert0(kperf = dlopen("/System/Library/PrivateFrameworks/kperf.framework/Versions/A/kperf", RTLD_LAZY));

#घोषणा F(ret, name, ...) av_assert0(name = (name##proc *)(dlsym(kperf, #name)));
    KPERF_LIST
#अघोषित F

    n = kpc_get_गणक_गिनती(KPC_MASK);
    av_assert0(n <= KPC_MAX_COUNTERS);
    n = kpc_get_config_गिनती(KPC_MASK);
    av_assert0(n <= CONFIG_गिनती);

    config[0] = CPMU_CORE_CYCLE | CFGWORD_EL0A64EN_MASK;
    // config[3] = CPMU_INST_BRANCH | CFGWORD_EL0A64EN_MASK;
    // config[4] = CPMU_SYNC_BR_ANY_MISP | CFGWORD_EL0A64EN_MASK;
    // config[5] = CPMU_INST_A64 | CFGWORD_EL0A64EN_MASK;

    av_assert0(kpc_set_config(KPC_MASK, config) == 0 || !"the kperf API needs to be run as root");
    av_assert0(kpc_force_all_ctrs_set(1) == 0);
    av_assert0(kpc_set_counting(KPC_MASK) == 0);
    av_assert0(kpc_set_thread_counting(KPC_MASK) == 0);
}

व्योम ff_kperf_init(व्योम)
{
    अटल AVOnce init_static_once = AV_ONCE_INIT;
    ff_thread_once(&init_static_once, kperf_init);
}

uint64_t ff_kperf_cycles(व्योम)
{
    uint64_t counters[KPC_MAX_COUNTERS];

    अगर (kpc_get_thread_counters(0, KPC_MAX_COUNTERS, counters)) {
        वापस -1;
    }

    वापस counters[0];
}
