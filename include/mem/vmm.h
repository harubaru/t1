#ifndef VMM_H
#define VMM_H

#include <tty.h>
#include <mem/pmm.h>
#include <stdint.h>

void vmm_init(void *end);
void vmm_switch_pd(void *pd);
void *vmm_map(void *addr);
void vmm_free(uint32_t *addr);

#endif
