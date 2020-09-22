/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _ARCH_x86_64_CPU_CPUID_H_
# define _ARCH_x86_64_CPU_CPUID_H_

# include <cpuid.h>

/*
 * x86 CPUID feature list
 */
enum __cpuid_features
{
	CPUID_SIGN_SSE3         = 1 << 0, 
    CPUID_SIGN_PCLMUL       = 1 << 1,
    CPUID_SIGN_DTES64       = 1 << 2,
    CPUID_SIGN_MONITOR      = 1 << 3,  
    CPUID_SIGN_DS_CPL       = 1 << 4,  
    CPUID_SIGN_VMX          = 1 << 5,  
    CPUID_SIGN_SMX          = 1 << 6,  
    CPUID_SIGN_EST          = 1 << 7,  
    CPUID_SIGN_TM2          = 1 << 8,  
    CPUID_SIGN_SSSE3        = 1 << 9,  
    CPUID_SIGN_CID          = 1 << 10,
    CPUID_SIGN_FMA          = 1 << 12,
    CPUID_SIGN_CX16         = 1 << 13, 
    CPUID_SIGN_ETPRD        = 1 << 14, 
    CPUID_SIGN_PDCM         = 1 << 15, 
    CPUID_SIGN_PCIDE        = 1 << 17, 
    CPUID_SIGN_DCA          = 1 << 18, 
    CPUID_SIGN_SSE4_1       = 1 << 19, 
    CPUID_SIGN_SSE4_2       = 1 << 20, 
    CPUID_SIGN_x2APIC       = 1 << 21, 
    CPUID_SIGN_MOVBE        = 1 << 22, 
    CPUID_SIGN_POPCNT       = 1 << 23, 
    CPUID_SIGN_AES          = 1 << 25, 
    CPUID_SIGN_XSAVE        = 1 << 26, 
    CPUID_SIGN_OSXSAVE      = 1 << 27, 
    CPUID_SIGN_AVX          = 1 << 28,
 
    CPUID_FEAT_FPU          = 1 << 0,  
    CPUID_FEAT_VME          = 1 << 1,  
    CPUID_FEAT_DE           = 1 << 2,  
    CPUID_FEAT_PSE          = 1 << 3,  
    CPUID_FEAT_TSC          = 1 << 4,  
    CPUID_FEAT_MSR          = 1 << 5,  
    CPUID_FEAT_PAE          = 1 << 6,  
    CPUID_FEAT_MCE          = 1 << 7,  
    CPUID_FEAT_CX8          = 1 << 8,  
    CPUID_FEAT_APIC         = 1 << 9,  
    CPUID_FEAT_SEP          = 1 << 11, 
    CPUID_FEAT_MTRR         = 1 << 12, 
    CPUID_FEAT_PGE          = 1 << 13, 
    CPUID_FEAT_MCA          = 1 << 14, 
    CPUID_FEAT_CMOV         = 1 << 15, 
    CPUID_FEAT_PAT          = 1 << 16, 
    CPUID_FEAT_PSE36        = 1 << 17, 
    CPUID_FEAT_PSN          = 1 << 18, 
    CPUID_FEAT_CLF          = 1 << 19, 
    CPUID_FEAT_DTES         = 1 << 21, 
    CPUID_FEAT_ACPI         = 1 << 22, 
    CPUID_FEAT_MMX          = 1 << 23, 
    CPUID_FEAT_FXSR         = 1 << 24, 
    CPUID_FEAT_SSE          = 1 << 25, 
    CPUID_FEAT_SSE2         = 1 << 26, 
    CPUID_FEAT_SS           = 1 << 27, 
    CPUID_FEAT_HTT          = 1 << 28, 
    CPUID_FEAT_TM1          = 1 << 29, 
    CPUID_FEAT_IA64         = 1 << 30,
    CPUID_FEAT_PBE          = 1 << 31
};

static inline u32_t cpuid_get_features(void)
{
	u32_t eax, unused, edx;

	__get_cpuid(1, &eax, &unused, &unused, &edx);
	return (edx);
}

static inline bool cpuid_get_feature(enum __cpuid_features feature)
{
    return (cpuid_get_features() & feature);
}

static inline u32_t cpuid_get_signatures(void)
{
	u32_t eax, unused, ecx;

	__get_cpuid(1, &eax, &unused, &ecx, &unused);
	return (ecx);
}

static inline bool cpuid_get_signature(enum __cpuid_features signature)
{
	return (cpuid_get_signatures() & signature);
}

static inline void cpuid_get_cpu_vendor(char *vendor)
{
	u32_t eax;
	u8_t ebx[4], edx[4], ecx[4];

	__get_cpuid(0, &eax, &ebx, &ecx, &edx);
	vendor[0] = ebx[0];
	vendor[1] = ebx[1];
	vendor[2] = ebx[2];
	vendor[3] = ebx[3];
	vendor[4] = edx[0];
	vendor[5] = edx[1];
	vendor[6] = edx[2];
	vendor[7] = edx[3];
	vendor[8] = ecx[0];
	vendor[9] = ecx[1];
	vendor[10] = ecx[2];
	vendor[11] = ecx[3];
}

static inline u8_t cpuid_get_apic_id(void)
{
	u32_t eax, ebx, unused;

	__get_cpuid(1, &eax, &ebx, &unused, &unused);
	return ((u8_t)(ebx >> 24));
}

static inline u32_t cpuid_get_cpu_signature(void)
{
	u32_t eax,  unused;

	__get_cpuid(1, &eax, &unused, &unused, &unused);
	return (eax);
}

static inline u64_t cpuid_get_lower_cpu_serialnbr(void)
{
	u32_t eax, ecx, edx, unused;

	__get_cpuid(3, &eax, &unused, &ecx, &edx);
	return (((u64_t)ecx) + ((u64_t)edx << 32));
}

#endif /* !_ARCH_x86_64_CPU_CPUID_H_ */
