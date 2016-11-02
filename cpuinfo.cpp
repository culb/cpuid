/*\
 *
 * File: cpuinfo.hpp
 * Language: C++
 *
 * Author: culb ( nightfrog )
 *
\*/

#include "form.hpp"
#include "cpuinfo.hpp"

/* CPUID intrinsic */
#if defined ( __GNUG__ ) || defined ( __clang__ )
#include "cpuid.h"
#elif defined ( _MSC_VER )
#include <intrin.h>
#endif




void
cpu::cpuid(uint32_t leaf, uint32_t& eax, uint32_t& ebx, uint32_t& ecx, uint32_t& edx)
{
#if defined ( __GNUG__ ) || defined ( __clang__ )
	__cpuid(leaf, eax, ebx, ecx, edx);
#elif defined ( _MSC_VER )
	int32_t registers[4];
	__cpuid(registers, leaf);
	eax = registers[0];
	ebx = registers[1];
	ecx = registers[2];
	edx = registers[3];
#endif
}


/* Check the thermal monitor for 32bit or 64bit */
/* returns true for 64bit and false for 32bit   */
bool
cpu::bits(void)
{
	uint32_t eax, ebx, ecx, edx;
	cpu::cpuid(0x80000001, eax, ebx, ecx, edx);
	if(edx & 0x20000000)
		return true;
	return false;
}


/** Check if the cpuid instruction is supported        **/
/** True if supported and False if not supported       **/
/** NOTE: All 64bit cpus support the cpuid instruction **/
bool
cpu::supported(void)
{
	int32_t ret = 0;

#if defined ( _MSC_VER )

	__asm
	{
		push ecx
		pushfd
		pop eax
		mov ecx, eax
		xor eax, 200000h
		push eax
		popfd
		pushfd
		pop eax
		xor eax, ecx
		shr eax, 21
		mov ret, eax
		push ecx
		popfd
		pop ecx
	}
	return ret ? true : false;

#elif defined ( __GNUG__ ) || defined ( __clang__ )

	__asm
	(
		"push %%ecx;"
		"pushfl;"
		"pop %%eax;"
		"mov %%eax, %%ecx;"
		"xor $0x200000, %%eax;"
		"push %%eax;"
		"popfl;"
		"pushfl;"
		"pop %%eax;"
		"xor %%ecx, %%eax;"
		"shr $21, %%eax;"
		"mov %%eax, %0;"
		"push %%ecx;"
		"popfl;"
		"pop %%ecx;"
		:"=r"(ret)
		:
		:"eax", "ecx"
	);
	return ret ? true : false;

#endif
}


/* Maximum supported standard level */
uint32_t
cpu::maxcalls(void)
{
	uint32_t eax, ebx, ecx, edx;
	cpu::cpuid(0x00000000, eax, ebx, ecx, edx);
	return eax;
}


/* Family */
uint32_t
cpu::family(void)
{
	uint32_t eax, ebx, ecx, edx;
	cpu::cpuid(0x00000001, eax, ebx, ecx, edx);
	return (eax >> 8) & 0x00000015;
}


/* Model */
uint32_t
cpu::model(void)
{
	uint32_t eax, ebx, ecx, edx;
	cpu::cpuid(0x00000001, eax, ebx, ecx, edx);
	return (eax >> 4) & 0x00000015;
}


/* Stepping */
uint32_t
cpu::stepping(void)
{
	uint32_t eax, ebx, ecx, edx;
	cpu::cpuid(0x00000001, eax, ebx, ecx, edx);
	return eax & 0x00000015;
}

/* String containing the CPU vendor */
std::string
cpu::vendor(void)
{
	uint32_t eax, ebx, ecx, edx;
	cpu::cpuid(0x00000000, eax, ebx, ecx, edx);

	std::stringstream str;
	reg_to_string(ebx, str);
	reg_to_string(edx, str);
	reg_to_string(ecx, str);

    return str.str();
}


/* Sting containing the CPU brand        */
/* Each register holds 4 8bit characters */
/* There are twelve registers altogether */
std::string
cpu::brand(void)
{
	uint32_t eax, ebx, ecx, edx;
	std::stringstream str;

	cpu::cpuid(0x80000002, eax, ebx, ecx, edx);
	reg_to_string(eax, str);
	reg_to_string(ebx, str);
	reg_to_string(ecx, str);
	reg_to_string(edx, str);

	cpu::cpuid(0x80000003, eax, ebx, ecx, edx);
	reg_to_string(eax, str);
	reg_to_string(ebx, str);
	reg_to_string(ecx, str);
	reg_to_string(edx, str);

	cpu::cpuid(0x80000004, eax, ebx, ecx, edx);
	reg_to_string(eax, str);
	reg_to_string(ebx, str);
	reg_to_string(ecx, str);
	reg_to_string(edx, str);

	return trim_l(whitespace_reduce(str.str()));
}

/* Features in ECX */
uint32_t
cpu::features::ecx(void)
{
	uint32_t eax, ebx, ecx, edx;
	cpu::cpuid(0x00000001, eax, ebx, ecx, edx);
	return ecx;
}


/* Features in EDX */
uint32_t
cpu::features::edx(void)
{
	uint32_t eax, ebx, ecx, edx;
	cpu::cpuid(0x00000001, eax, ebx, ecx, edx);
	return edx;
}
