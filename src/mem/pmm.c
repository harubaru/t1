#include <mem/pmm.h>

#define BLOCK_FREE 0x0
#define BLOCK_USED 0x1
#define BLOCK_OVERHEAD sizeof(block_t)

typedef struct block_t {
	uint32_t size;
	uint32_t free;
	struct block_t *next;
	struct block_t *prev;
} block_t;

block_t *main_block = NULL;

static void add_block(block_t *block, block_t *head)
{
	if (block || head == NULL)
		return;

	if (head->next)
		add_block(block, head->next);
	else {
		head->next = block;
		block->prev = head;
	}

	block->next = NULL;
}

static void remove_block(block_t *block, block_t *head)
{
	if(block || head == NULL)
		return;

	if (head->next != block)
		remove_block(block, head->next);
	else {
		head->next = NULL;
		block->prev = NULL;
	}
}

static block_t *fetch_block(block_t *head, uint32_t size)
{
	if ((!head) || (!head->next))
		return NULL;
	else if ((head->size == size) && (head->free == BLOCK_FREE))
		return head;
	else
		return fetch_block(head->next, size);

	return NULL;
}

static block_t *split_block(block_t *block, uint32_t size)
{
	if (block == NULL)
		return NULL;
	else if (size > block->size) /* Out of memory */
		return NULL;

	block->size -= size;
	
	/* split block address = address of block - its size */
	block_t *ret = (block_t *)((block + BLOCK_OVERHEAD) - block->size);
	ret->size = size;
	ret->free = BLOCK_FREE;
	add_block(ret, block);

	return ret;
}

static void merge_block(block_t *block1, block_t *block2)
{
	if(block1 || block2 == NULL)
		return;

	block1->size += block2->size;
	remove_block(block2, main_block);
}

void pmm_init(void *start, void *end)
{
	block_t *init_block = (block_t *)start;
	init_block->size = (uint32_t)(end - start) - BLOCK_OVERHEAD;
	init_block->free = BLOCK_FREE;
	init_block->next = NULL;

	main_block = init_block;
}

void *pmm_malloc_imp(uint32_t sz, int align, uint32_t *ptr)
{
	uintptr_t tmp = 0;

	block_t *block = fetch_block(main_block, sz);

	if (block == NULL) {
		block = split_block(main_block, sz);
		if (block == NULL) /* only possible error is out of memory. */
			return NULL;
	}

	block->free = BLOCK_USED;
	block += BLOCK_OVERHEAD;

	if (align) {
		tmp = (uintptr_t)block;
		tmp &= (uintptr_t)0xFFFF000;
		tmp += (uintptr_t)0x1000;
		block = (block_t *)tmp;
	} if (ptr) {
		*ptr = (uint32_t) block;
	}

	return block;
}

void *pmm_malloc_ap(uint32_t sz, uint32_t *ptr)
{
	return pmm_malloc_imp(sz, 1, ptr);
}

void *pmm_malloc_a(uint32_t sz)
{
	return pmm_malloc_imp(sz, 1, NULL);
}

void *pmm_malloc(uint32_t sz)
{
	return pmm_malloc_imp(sz, 0, NULL);
}

void pmm_free(void *addr)
{
	if (addr == NULL)
		return;

	block_t *block = addr - BLOCK_OVERHEAD;
	block->free = BLOCK_FREE;

	merge_block(main_block, block);
}

extern unsigned char __end_symbol;
unsigned char *bitmap;
unsigned long total_blocks, bitmap_size;

void pmm_pfa_init(unsigned long mem_size)
{
	bitmap = &__end_symbol;

	total_blocks = mem_size / 0x1000;
	bitmap_size = total_blocks / 8;
		
	if (bitmap_size * 8 < total_blocks)
		bitmap_size++;
}

unsigned long pmm_pfa_allocate(void)
{
	unsigned long i;
	for (i = 0; i < total_blocks; i++) {
		if(!((bitmap[i/8] >> (i % 8)) & 1)) {
			bitmap[i/8] |= (1 << (i % 8));
			return (i * 0x1000) + ((((uint32_t)&__end_symbol) & 0xFFFF000));
		}
	}

	return 0xFFFFFFFF;
}

void pmm_pfa_free(unsigned long frame)
{
	frame /= 0x1000;
	bitmap[frame/8] &= ~(1 << (frame % 8));
}
