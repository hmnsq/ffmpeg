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

/*
 * Test the stdatomic.h interface as used by FFmpeg, against whichever
 * implementation configure selected, the native one or the compat fallback.
 *
 * The output is architecture independent: integer results are converted to
 * long long before printing, and no pointer values are printed.
 */

#ضمن <limits.h>
#ضمن <stdint.h>
#ضمن <stdio.h>
#ضمن <stdatomic.h>

ساكن صحيح called;

ساكن فراغ callback(فراغ)
{
    called++;
}

#تعریف_کن TEST(A, T, name, V1, V2)                                             \
افعل {                                                                         \
    A object = 0;                                                            \
    T expected, r;                                                           \
    atomic_store(&object, (T)(V1));                                          \
    r = atomic_exchange(&object, (T)(V2));                                   \
    چاپ_کن(name " exchange  %lld\n", (دراز دراز)r);                          \
    r = atomic_fetch_add(&object, (T)1);                                     \
    چاپ_کن(name " add       %lld\n", (دراز دراز)r);                          \
    r = atomic_fetch_sub(&object, (T)((uint64_t)(V2) + 1));                  \
    چاپ_کن(name " sub       %lld\n", (دراز دراز)r);                          \
    r = atomic_fetch_or(&object, (T)0x10);                                   \
    چاپ_کن(name " or        %lld\n", (دراز دراز)r);                          \
    r = atomic_fetch_xor(&object, (T)0x10);                                  \
    چاپ_کن(name " xor       %lld\n", (دراز دراز)r);                          \
    r = atomic_fetch_and(&object, (T)1);                                     \
    چاپ_کن(name " and       %lld\n", (دراز دراز)r);                          \
    atomic_store(&object, (T)0x5a);                                          \
    expected = (T)(V1);                                                      \
    r = atomic_compare_exchange_strong(&object, &expected, (T)(V2));         \
    چاپ_کن(name " cas       %lld %lld\n",                                    \
           (دراز دراز)r, (دراز دراز)expected);                               \
    افعل {                                                                     \
        r = atomic_compare_exchange_weak(&object, &expected, (T)(V1));       \
    } طالما (!r);                                                            \
    چاپ_کن(name " cas weak  %lld %lld %lld\n",                               \
           (دراز دراز)r, (دراز دراز)expected,                                \
           (دراز دراز)atomic_load(&object));                                 \
} طالما (0)

صحيح اصلی(فراغ)
{
    _Bool _Atomic b = 0;
    _Bool be;
    atomic_uint u32 = 0;
    atomic_ullong u64 = 0;
    atomic_uchar u8 = 0;
    صحيح x = 42;
    صحيح *_Atomic p = عدم;
    صحيح *pe;
    فراغ (*_Atomic fp)(فراغ) = عدم;
    ثابت صحيح *ثابت arr[2] = { &x, عدم };
    ثابت صحيح *ثابت *_Atomic lst = عدم;
    atomic_flag f = ATOMIC_FLAG_INIT;
    دراز دراز old;
    صحيح r1, r2, r3;
    فراغ (*loaded_callback)(فراغ);

    TEST(atomic_char, حرف,         "char",         97, 122);
    TEST(atomic_schar, علامتدار حرف,        "schar",        -5, 42);
    TEST(atomic_uchar, بیعلامت حرف,        "uchar",        200, 42);
    TEST(atomic_short, کوتاه,        "short",        -30000, 42);
    TEST(atomic_ushort, بیعلامت کوتاه,       "ushort",       60000, 42);
    TEST(atomic_int, صحيح,          "int",          -2000000000, 2000000000);
    TEST(atomic_uint, بیعلامت صحيح,         "uint",         4000000000u, 7u);
    TEST(atomic_long, دراز,         "long",         -2000000000L, 2000000000L);
    TEST(atomic_ulong, بیعلامت دراز,        "ulong",        4000000000UL, 7UL);
    TEST(atomic_llong, دراز دراز,        "llong",        -9007199254740993LL, 9007199254740993LL);
    TEST(atomic_ullong, بیعلامت دراز دراز,       "ullong",       18446744073709551615ULL, 3ULL);
    TEST(atomic_int_least16_t, int_least16_t, "int_least16", -30000, 42);
    TEST(atomic_uint_least32_t, uint_least32_t, "uint_least32", 4000000000u, 7u);
    TEST(atomic_int_least64_t, int_least64_t, "int_least64", -9007199254740993LL, 9007199254740993LL);
    TEST(atomic_uint_least64_t, uint_least64_t, "uint_least64", 18446744073709551615ULL, 3ULL);
    TEST(atomic_int_fast16_t, int_fast16_t,  "int_fast16",  -30000, 42);
    TEST(atomic_uint_fast32_t, uint_fast32_t, "uint_fast32", 4000000000u, 7u);
    TEST(atomic_intptr_t, intptr_t,     "intptr",       -123456, 42);
    TEST(atomic_size_t, size_t,       "size",         4000000000u, 7u);
    TEST(atomic_intmax_t, intmax_t,     "intmax",       -9007199254740993LL, 9007199254740993LL);

    /* unsigned wraparound */
    atomic_store(&u32, UINT_MAX);
    old = atomic_fetch_add(&u32, 1u);
    چاپ_کن("uint wrap  %lld %lld\n",
           old, (دراز دراز)atomic_load(&u32));
    atomic_store(&u64, ULLONG_MAX);
    old = (دراز دراز)atomic_fetch_add(&u64, 1);
    چاپ_کن("ullong add %lld %lld\n",
           old, (دراز دراز)atomic_load(&u64));
    atomic_store(&u64, 5);
    old = (دراز دراز)atomic_fetch_sub(&u64, 10);
    چاپ_کن("ullong sub %lld %lld\n",
           old, (دراز دراز)atomic_load(&u64));
    atomic_store(&u8, 200);
    old = atomic_fetch_add(&u8, 100);
    چاپ_کن("uchar add  %lld %lld\n",
           old, (دراز دراز)atomic_load(&u8));

    /* bool, including the normalization of the desired value */
    atomic_store(&b, 1);
    be = 0;
    r1 = atomic_load(&b);
    r2 = atomic_exchange(&b, 0);
    r3 = atomic_compare_exchange_strong(&b, &be, 2);
    چاپ_کن("bool       %d %d %d %d %d\n", r1, r2, r3,
           (صحيح)be, (صحيح)atomic_load(&b));

    /* object pointers */
    atomic_store_explicit(&p, &x, memory_order_relaxed);
    pe = عدم;
    r1 = atomic_load_explicit(&p, memory_order_relaxed) == &x;
    r2 = atomic_compare_exchange_strong(&p, &pe, عدم);
    چاپ_کن("ptr        %d %d %d\n", r1, r2, pe == &x);
    چاپ_کن("ptr exch   %d\n", atomic_exchange(&p, عدم) == &x);

    /* function pointers, as in the log callback */
    atomic_store_explicit(&fp, callback, memory_order_relaxed);
    loaded_callback = atomic_load_explicit(&fp, memory_order_relaxed);
    loaded_callback();

    /* pointers to const, as in the device lists */
    ثابت صحيح *ثابت *l;
    atomic_store_explicit(&lst, arr, memory_order_relaxed);
    l = atomic_load_explicit(&lst, memory_order_relaxed);
    چاپ_کن("lst        %d %d\n", l == arr, **l == x);

    r1 = atomic_flag_test_and_set(&f);
    r2 = atomic_flag_test_and_set(&f);
    atomic_flag_clear(&f);
    r3 = atomic_flag_test_and_set(&f);
    چاپ_کن("flag       %d %d %d\n", r1, r2, r3);
    چاپ_کن("called     %d\n", called);

    {
        صحيح _Atomic i = 0;
        atomic_init(&i, 43);
        چاپ_کن("init       %d\n", (صحيح)atomic_load(&i));
    }
    atomic_thread_fence(memory_order_seq_cst);
    atomic_signal_fence(memory_order_acquire);
    چاپ_کن("kill_dep   %d\n", (صحيح)kill_dependency(1));

    أرجع 0;
}
