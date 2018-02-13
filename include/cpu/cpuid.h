#ifndef CPUID_H
#define CPUID_H

#define CPUID_FEAT_EDX_FPU (1 << 0) // Floating-point Unit
#define CPUID_FEAT_EDX_VME (1 << 1) // Virtual Mode Extensioin
#define CPUID_FEAT_EDX_DE (1 << 2) // Debugging Extension
#define CPUID_FEAT_EDX_PSE (1 << 3) // Page Size Extension
#define CPUID_FEAT_EDX_TSC (1 << 4) // Time Stamp Counter
#define CPUID_FEAT_EDX_MSR (1 << 5) // Model Specific Registers
#define CPUID_FEAT_EDX_PAE (1 << 6) // Physical Address Extension
#define CPUID_FEAT_EDX_MCE (1 << 7) // Machine-Check Exception
#define CPUID_FEAT_EDX_CX8 (1 << 8) // CMPXCHG8 Instruction
#define CPUID_FEAT_EDX_APIC (1 << 9) // On-chip APIC Hardwawre
#define CPUID_FEAT_EDX_RESVD0 (1 << 10) // Reserved
#define CPUID_FEAT_EDX_SEP (1 << 11) // Fast System Call
#define CPUID_FEAT_EDX_MTRR (1 << 12) // Memory Type Range Registers
#define CPUID_FEAT_EDX_PGE (1 << 13) // Page Global Enable
#define CPUID_FEAT_EDX_MCA (1 << 14) // Machine-Check Architecture
#define CPUID_FEAT_EDX_CMOV (1 << 15) // Conditional Move Instruction
#define CPUID_FEAT_EDX_PAT (1 << 16) // Page Attribute Table
#define CPUID_FEAT_EDX_PSE36 (1 << 17) // 36-bit Page Size Extension
#define CPUID_FEAT_EDX_PSN (1 << 18) // Processor serial number is present and enabled
#define CPUID_FEAT_EDX_CLFLUSH (1 << 19) // CLFLUSH Instruction
#define CPUID_FEAT_EDX_RESVD1 (1 << 20) // Reserved
#define CPUID_FEAT_EDX_DS (1 << 21) // Debug Store
#define CPUID_FEAT_EDX_ACPI (1 << 22) // Thermal Monitor and Software Controlled Clock Facilities
#define CPUID_FEAT_EDX_MMX (1 << 23) // MMX Technology
#define CPUID_FEAT_EDX_FXSR (1 << 24) // FXSAVE and FXSTOR Instructions
#define CPUID_FEAT_EDX_SSE (1 << 25) // Streaming SIMD Extensions
#define CPUID_FEAT_EDX_SSE2 (1 << 26) // Streaming SIMD Extensions 2
#define CPUID_FEAT_EDX_SS (1 << 27) // Self-Snoop
#define CPUID_FEAT_EDX_HTT (1 << 28) // Multi-Threading
#define CPUID_FEAT_EDX_TM (1 << 29) // Thermal Monitor
#define CPUID_FEAT_EDX_RESVD2 (1 << 30) // Reserved
#define CPUID_FEAT_EDX_PBE (1 << 31) // Pending Break Enable

#define CPUID_FEAT_ECX_SSE3 (1 << 0) // Streaming SIMD Extensions 3
#define CPUID_FEAT_ECX_PCLMULDQ (1 << 1) // PCLMULDQ Instruction
#define CPUID_FEAT_ECX_DTES64 (1 << 2) // 64-Bit Debug Store
#define CPUID_FEAT_ECX_MONITOR (1 << 3) // MONITOR/MWAIT
#define CPUID_FEAT_ECX_DS_CPL (1 << 4) // CPL Qualified Debug Store
#define CPUID_FEAT_ECX_VMX (1 << 5) // Virtual Machine Extensions
#define CPUID_FEAT_ECX_SMX (1 << 6) // Safer MOde Extensions
#define CPUID_FEAT_ECX_EST (1 << 7) // Enhanced INtel SpeedStep(r) Technology
#define CPUID_FEAT_ECX_TM2 (1 << 8) // Thermal Monitor 2
#define CPUID_FEAT_ECX_SSSE3 (1 << 9) // Supplemental Streaming SIMD Extensions 3
#define CPUID_FEAT_ECX_CNXT_ID (1 << 10) // L1 Context ID
#define CPUID_FEAT_ECX_RESVD0 (1 << 11) // Reserved
#define CPUID_FEAT_ECX_RESVD1 (1 << 12) // Reserved 
#define CPUID_FEAT_ECX_CMPXCHG168 (1 << 13) // CMPXCHG168 Instruction
#define CPUID_FEAT_ECX_XTPR (1 << 14) // xTPR Update Control
#define CPUID_FEAT_ECX_PDCM (1 << 15) // Perfmon and Debug Capability
#define CPUID_FEAT_ECX_RESVD2 (1 << 16) // Reserved
#define CPUID_FEAT_ECX_RESVD3 (1 << 17) // Reserved
#define CPUID_FEAT_ECX_DCA (1 << 18) // Direct Cache Access
#define CPUID_FEAT_ECX_SSE4_1 (1 << 19) // Streaming SIMD Extensions 4.1
#define CPUID_FEAT_ECX_SSE4_2 (1 << 20) // Streaming SIMD Extensions 4.2
#define CPUID_FEAT_ECX_X2APIC (1 << 21) // Extended xAPIC Support
#define CPUID_FEAT_ECX_MOVBE (1 << 22) // MOVBE Instruction
#define CPUID_FEAT_ECX_POPCNT (1 << 23) // POPCNT Instruction
#define CPUID_FEAT_ECX_RESVD4 (1 << 24) // Reserved
#define CPUID_FEAT_ECX_AES (1 << 25) // AES Instruction
#define CPUID_FEAT_ECX_XSAVE (1 << 26) // XSAVE/XSTOR States
#define CPUID_FEAT_ECX_OSXSAVE (1 << 27) // OS-Enabled Extended State Management

typedef struct cpuid_info {
	char vendor[13];
	char name[44];
	unsigned long features_edx;
	unsigned long features_ecx;
} cpuid_info_t;

void cpuid_get(cpuid_info_t *info);

#endif
