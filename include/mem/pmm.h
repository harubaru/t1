#ifndef MEM_PMM_H
#define MEM_PMM_H

#include <stdint.h>
#include <stddef.h>

void pmm_init(void *start, void *end);
void *pmm_malloc_imp(uint32_t sz, int align, void *ptr);
void *pmm_malloc_ap(uint32_t sz, void *ptr);
void *pmm_malloc_a(uint32_t sz);
void *pmm_malloc(uint32_t sz);
void pmm_free(void *addr);

#endif
