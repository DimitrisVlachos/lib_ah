
/*
	lib_ah : Aligned heap wrapper/library
	Author : Dimitris Vlachos (DimitrisV22@gmail.com @ github.com/DimitrisVlachos)
*/

#ifndef __aligned_heap__h__
#define __aligned_heap__h__
#include <stdint.h>
#include <malloc.h>

#define k_heap_alignment (64U)
#define k_heap_alignment_mask (k_heap_alignment - 1U)

#define heap_align_attr __attribute__ ((aligned (k_heap_alignment)))
#define heap_align_attr_imm(_imm_) __attribute__ ((aligned (_imm_)))

 
void* heap_new(uint64_t size);
void heap_delete(void* ent);
void heap_leak_stats();
void heap_init();
void heap_shutdown();
#endif

