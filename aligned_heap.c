
/*
	lib_ah : Aligned heap wrapper/library
	Author : Dimitris Vlachos (DimitrisV22@gmail.com @ github.com/DimitrisVlachos)
*/

#include "aligned_heap.h"
#include <malloc.h>

const ptrdiff_t k_heap_hdr_size = (const ptrdiff_t)(sizeof(void*) );

static inline void wr_addr(void* dst,const void* src) {
	register uint8_t* w = (uint8_t*)dst;
	register const uint8_t* r = (const uint8_t*)src;
	register const uint8_t* r2 = r + sizeof(void*);

	do {
		*(w++) = *(r++);
	} while (r < r2);
}


void* heap_new(uint64_t size) {
	const uint64_t msize = (k_heap_hdr_size + (k_heap_alignment << 1) + size) & (~k_heap_alignment_mask);
	void* ent;
	void* aligned;
	ptrdiff_t addr,saddr;

	ent = (void*)malloc(msize);
	if (!ent) {
		return 0;
	}
 
	addr = (ptrdiff_t)ent;
	saddr = addr;
	addr += k_heap_alignment - (addr % k_heap_alignment);
	aligned = (void*)addr;
	wr_addr(aligned,&saddr);

	return (void*)((uint8_t*)((uint8_t*)aligned + sizeof(void*)));
}
 
void heap_delete(void* ent) {
	ptrdiff_t addr;

	if (ent) {
		wr_addr(&addr,(uint8_t*)ent - sizeof(void*));
		free( (void*)addr);
	}
}


