#ifndef VMM_H
#define VMM_H

#include <mem/pmm.h>
#include <stdint.h>

typedef struct page_directory {
	uint32_t *pd;
	uint32_t *pt[1024];
} page_directory_t;

extern page_directory_t *kern_pd;
extern page_directory_t *curr_pd;

void vmm_init(void *end);
page_directory_t *vmm_init_pd(void);
void vmm_free_pd(page_directory_t *pd);
void vmm_switch_pd(void *pd);
void vmm_copy_pd(page_directory_t *dst, page_directory_t *src);
void vmm_pd_free(page_directory_t *pd);
void *vmm_map(void *addr);
void *vmm_malloc(uint32_t size);
void vmm_free(uint32_t *addr);

#endif
