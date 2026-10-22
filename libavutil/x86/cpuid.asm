;*****************************************************************************
;* Copyright (C) 2005-2010 x264 project
;*
;* Authors: Loren Merritt <lorenm@u.washington.edu>
;*          Fiona Glaser <fiona@x264.com>
;*
;* This file is part of FFmpeg.
;*
;* FFmpeg is free software; you can redistribute it and/or
;* modify it under the terms of the GNU Lesser General Public
;* License as published by the Free Software Foundation; either
;* version 2.1 of the License, or (at your option) any later version.
;*
;* FFmpeg is distributed in the hope that it will be useful,
;* but WITHOUT ANY WARRANTY; without even the implied warranty of
;* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
;* Lesser General Public License for more details.
;*
;* You should have received a copy of the GNU Lesser General Public
;* License along with FFmpeg; if not, write to the Free Software
;* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
;******************************************************************************

%include "libavutil/x86/x86util.asm"

SECTION .text

;-----------------------------------------------------------------------------
; void ff_cpu_cpuid(int index, int *eax, int *ebx, int *ecx, int *edx)
;-----------------------------------------------------------------------------
cglobal cpu_cpuid, 5,7
    निक्षिप rbx
    निक्षिप  r4
    निक्षिप  r3
    निक्षिप  r2
    निक्षिप  r1
    चालय  eax, r0d
    xor  ecx, ecx
    cpuid
    उद्धर   r4
    चालय [r4], eax
    उद्धर   r4
    चालय [r4], ebx
    उद्धर   r4
    चालय [r4], ecx
    उद्धर   r4
    चालय [r4], edx
    उद्धर  rbx
    RET

;-----------------------------------------------------------------------------
; void ff_cpu_xgetbv(int op, int *eax, int *edx)
;-----------------------------------------------------------------------------
cglobal cpu_xgetbv, 3,7
    निक्षिप  r2
    निक्षिप  r1
    चालय  ecx, r0d
    xgetbv
    उद्धर   r4
    चालय [r4], eax
    उद्धर   r4
    चालय [r4], edx
    RET

%if ARCH_X86_64 == 0
;-----------------------------------------------------------------------------
; int ff_cpu_cpuid_test(void)
; return 0 if unsupported
;-----------------------------------------------------------------------------
cglobal cpu_cpuid_test
    pushfd
    निक्षिप    ebx
    निक्षिप    ebp
    निक्षिप    esi
    निक्षिप    edi
    pushfd
    उद्धर     eax
    चालय     ebx, eax
    xor     eax, 0x200000
    निक्षिप    eax
    popfd
    pushfd
    उद्धर     eax
    xor     eax, ebx
    उद्धर     edi
    उद्धर     esi
    उद्धर     ebp
    उद्धर     ebx
    popfd
    प्रत्यागच्छ
%endif
