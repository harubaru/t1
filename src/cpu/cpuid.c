#include <cpu/cpuid.h>

static void cpuid(unsigned long function, unsigned long *eax, unsigned long *ebx, unsigned long *ecx, unsigned long *edx)
{
	asm volatile ("cpuid" : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx) : "0" (function));
}

void cpuid_get(cpuid_info_t *info)
{
	if (info) {
		unsigned long eax = 0, ebx = 0, ecx = 0, edx = 0;

		// function = 0: get vendor ID
		char *vendor = info->vendor;
		cpuid(0, &eax, (unsigned long *)(vendor + 0), (unsigned long *)(vendor + 8), (unsigned long *)(vendor + 4));
		vendor[12] = 0;

		// function = 1: get feature information
		if (eax >= 1) {
			cpuid(0x1, &eax, &ebx, &ecx, &edx);
			info->features_edx = edx;
			info->features_ecx = ecx;
		}

		// function = 0x80000000: get extended feature bits
		cpuid(0x80000000, &eax, &ebx, &ecx, &edx);

		// function = 0x80000002 -> 0x80000004: processor name
		if (eax >= 0x80000004) {
			char *name = info->name;
			cpuid(0x80000002, (unsigned long *)(name + 0),  (unsigned long *)(name + 4), (unsigned long *)(name + 8), (unsigned long *)(name + 12));
			cpuid(0x80000003, (unsigned long *)(name + 16),  (unsigned long *)(name + 20), (unsigned long *)(name + 24), (unsigned long *)(name + 28));
			cpuid(0x80000004, (unsigned long *)(name + 32),  (unsigned long *)(name + 36), (unsigned long *)(name + 40), (unsigned long *)(name + 44));
		}
	}
}
