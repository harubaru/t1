#include <mem/vmm.h>

extern uint32_t __end_symbol;
uint32_t end_symbol = (uint32_t)&__end_symbol;

page_directory_t *kern_pd = NULL;
page_directory_t *curr_pd = NULL;

static void __load_tlb(uint32_t pdaddr)
{
	asm volatile("mov %0, %%cr3" :: "r"(pdaddr));
}

static void __flush_tlb(void)
{
	asm volatile("movl %%cr3, %%eax; movl %%eax, %%cr3" ::: "eax", "memory");
}

static void __enable_paging(void)
{
	asm volatile("mov %cr0, %eax");
	asm volatile("orl $0x80000000, %eax");
	asm volatile("mov %eax, %cr0");	
}

page_directory_t *vmm_init_pd(void)
{
	uint32_t i;
	page_directory_t *pd = pmm_malloc(sizeof(page_directory_t));
	pd->pd = pmm_malloc_a(1024 * sizeof(uint32_t));

	for (i = 0; i < 1024; i++)
		pd->pd[i] = 0x2;

	for (i = 0; i < 1024; i++)
		pd->pt[i] = NULL;

	return pd;
}

void vmm_free_pd(page_directory_t *pd)
{
	uint32_t i;

	if (pd != curr_pd) {
		// free page tables
		for (i = 0; i < 1024; i++)
			pmm_free(pd->pt[i]);
		
		// free page directory entries, then finally free the page directory structure.
		pmm_free(pd->pd);
		pmm_free(pd);
	}
}

static void init_pt(uint32_t idx, page_directory_t *pd)
{
	uint32_t i;
	uint32_t *pt;

	if(!pd->pt[idx]) {
		pd->pt[idx] = pmm_malloc_a(1024 * sizeof(uint32_t));
		pt = pd->pt[idx];

		for (i = 0; i < 1024; i++)
			pt[i] = (i * 0x1000) | 3;
	} else {
		return;
	}
}

void vmm_init(void *end)
{
	pmm_pfa_init((uint32_t)end - (uint32_t)&__end_symbol);
	pmm_init(&__end_symbol, end);

	kern_pd = vmm_init_pd();
	curr_pd = kern_pd;

	// map 20 megs of memory
	vmm_identity_map((void *)0x000000, (void *)0x1400000);

	__load_tlb((uint32_t)kern_pd->pd);
	__enable_paging();
}

void vmm_switch_pd(void *pd)
{
	curr_pd = pd;
	__load_tlb((uint32_t)pd);
}

void vmm_copy_pd(page_directory_t *dst, page_directory_t *src)
{
	uint32_t i;
	for (i = 0; i < 1024; i++) {
		dst->pd[i] = src->pd[i];
		dst->pt[i] = src->pt[i];
	}
}

void vmm_pd_free(page_directory_t *pd)
{
	if ((pd) && (pd != kern_pd)) {
		pmm_free(pd);
	}
}

void *vmm_map(void *addr)
{
	uint32_t pd_idx = (uint32_t)addr >> 22;
	uint32_t pt_idx = (uint32_t)addr >> 12 & 0x03FF;

	uint32_t tmp;
	uint32_t *pt = curr_pd->pt[pd_idx];

	if (!pt) // if pt is null
		init_pt(pt_idx, curr_pd);
	else if (pt[pt_idx]) // else if, page table exists and page does too.
		return (void *)pt[pt_idx];

	pt = curr_pd->pt[pt_idx];
	tmp = pmm_pfa_allocate();
	pt[pt_idx] = tmp | 3;

	curr_pd->pd[pd_idx] = ((uint32_t)&pt[pt_idx]) | 3; // set page directory entry

	__flush_tlb();

	return (void *)tmp;
}

void vmm_identity_map(void *from, void *to)
{
	uint32_t i = (uint32_t)from;
	while (i < (uint32_t)to) {
		(void)vmm_map(i);
		i += 0x1000;
	}
}

void *vmm_malloc(uint32_t size)
{
	void *ret = (void *)((uint32_t)pmm_malloc_a(size) >> 12);
	ret = vmm_map(ret);

	return ret;
}

void vmm_free(uint32_t *addr)
{
	uint32_t *page = vmm_map(addr);

	if (page) {
		*page = 3; // set Frame to NULL
		pmm_free(page);
	}
}
