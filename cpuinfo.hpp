/*\
 *
 * File: cpuinfo.hpp
 * Language: C++
 *
 * Author: culb ( nightfrog )
 *
\*/

#ifndef __CPUINFO__
#define __CPUINFO__

#include <string>
#include <stdint.h>




namespace cpu
{
	void cpuid(uint32_t op, uint32_t& eax, uint32_t& ebx, uint32_t& ecx, uint32_t& edx);

	bool bits(void);
	bool supported(void);

	uint32_t maxcalls(void);
	uint32_t family(void);
	uint32_t model(void);
	uint32_t stepping(void);

	std::string vendor(void);
	std::string brand(void);

namespace features
{
	uint32_t ecx(void);
	uint32_t edx(void);
}/* features*/
}/* cpu */


/* Flags for features */
namespace flags
{
	enum ecx
	{
		SSE3        = 0x00000001,
		PCLMULQDQ   = 0x00000002,
		DTES64      = 0x00000004,
		MONITOR     = 0x00000008,
		DSCPL       = 0x00000010,
		VMX         = 0x00000020,
		SMX         = 0x00000040,
		EIST        = 0x00000080,
		TM2         = 0x00000100,
		SSSE3       = 0x00000200,
		CNXTID      = 0x00000400,
		FMA         = 0x00001000,
		CMPXCHG16B  = 0x00002000,
		xTPR        = 0x00004000,
		PDCM        = 0x00008000,
		PCID        = 0x00020000,
		DCA         = 0x00040000,
		SSE41       = 0x00080000,
		SSE42       = 0x00100000,
		x2APIC      = 0x00200000,
		MOVBE       = 0x00400000,
		POPCNT      = 0x00800000,
		TSCDEADLINE = 0x01000000,
		AESNI       = 0x02000000,
		XSAVE       = 0x04000000,
		OSXSAVE     = 0x08000000,
		AVX         = 0x10000000,
		RDRND       = 0x40000000
	};

	enum edx
	{
		FPU    = 0x00000001,
		VME    = 0x00000002,
		DE     = 0x00000004,
		PSE    = 0x00000008,
		TSC    = 0x00000010,
		MSR    = 0x00000020,
		PAE    = 0x00000040,
		MCE    = 0x00000080,
		CX8    = 0x00000100,
		APIC   = 0x00000200,
		SEP    = 0x00000800,
		MTRR   = 0x00001000,
		PGE    = 0x00002000,
		MCA    = 0x00004000,
		CMOV   = 0x00008000,
		PAT    = 0x00010000,
		PSE36  = 0x00020000,
		PSN    = 0x00040000,
		CLFSH  = 0x00080000,
		DS     = 0x00200000,
		ACPI   = 0x00400000,
		MMX    = 0x00800000,
		FXSR   = 0x01000000,
		FXSAVE = 0x01000000,
		SSE    = 0x02000000,
		SSE2   = 0x04000000,
		SS     = 0x08000000,
		HTT    = 0x10000000,
		TM     = 0x20000000,
		PBE    = 0x80000000
	};
}


/* TODO: Change these to something more meaningful */
#if defined ( _MSC_VER )
/* Responses identification request with %eax 0 */
/* AMD:     "AuthenticAMD" */
#define signature_AMD_ebx 0x68747541
#define signature_AMD_edx 0x69746e65
#define signature_AMD_ecx 0x444d4163
/* CENTAUR: "CentaurHauls" */
#define signature_CENTAUR_ebx 0x746e6543
#define signature_CENTAUR_edx 0x48727561
#define signature_CENTAUR_ecx 0x736c7561
/* CYRIX:   "CyrixInstead" */
#define signature_CYRIX_ebx 0x69727943
#define signature_CYRIX_edx 0x736e4978
#define signature_CYRIX_ecx 0x64616574
/* INTEL:   "GenuineIntel" */
#define signature_INTEL_ebx 0x756e6547
#define signature_INTEL_edx 0x49656e69
#define signature_INTEL_ecx 0x6c65746e
/* TM1:     "TransmetaCPU" */
#define signature_TM1_ebx 0x6e617254
#define signature_TM1_edx 0x74656d73
#define signature_TM1_ecx 0x55504361
/* TM2:     "GenuineTMx86" */
#define signature_TM2_ebx 0x756e6547
#define signature_TM2_edx 0x54656e69
#define signature_TM2_ecx 0x3638784d
/* NSC:     "Geode by NSC" */
#define signature_NSC_ebx 0x646f6547
#define signature_NSC_edx 0x43534e20
#define signature_NSC_ecx 0x79622065
/* NEXGEN:  "NexGenDriven" */
#define signature_NEXGEN_ebx 0x4778654e
#define signature_NEXGEN_edx 0x72446e65
#define signature_NEXGEN_ecx 0x6e657669
/* RISE:    "RiseRiseRise" */
#define signature_RISE_ebx 0x65736952
#define signature_RISE_edx 0x65736952
#define signature_RISE_ecx 0x65736952
/* SIS:     "SiS SiS SiS " */
#define signature_SIS_ebx 0x20536953
#define signature_SIS_edx 0x20536953
#define signature_SIS_ecx 0x20536953
/* UMC:     "UMC UMC UMC " */
#define signature_UMC_ebx 0x20434d55
#define signature_UMC_edx 0x20434d55
#define signature_UMC_ecx 0x20434d55
/* VIA:     "VIA VIA VIA " */
#define signature_VIA_ebx 0x20414956
#define signature_VIA_edx 0x20414956
#define signature_VIA_ecx 0x20414956
/* VORTEX:  "Vortex86 SoC" */
#define signature_VORTEX_ebx 0x74726f56
#define signature_VORTEX_edx 0x36387865
#define signature_VORTEX_ecx 0x436f5320

/* Features in %ebx for level 7 sub-leaf 0 */
#define bit_FSGSBASE    0x00000001
#define bit_SMEP        0x00000080
#define bit_ENH_MOVSB   0x00000200
#endif /* _MSC_VER */

#endif /* __CPUINFO__ */
