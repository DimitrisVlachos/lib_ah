#include "aligned_heap.h"
#include <stdio.h>
 
#include <emmintrin.h>
#include <mmintrin.h>


int main() {
	const uint32_t len = 16 * 1024 * 1024;
	uint32_t i;

	uint8_t* p = (uint8_t*)heap_new(len);
	if (!p) {
		printf("out of memory!\n");
		return 1;
	}

	printf("Test 16bit stores\n");
	for (i = 0;i < len;i += 2)	
		*(uint16_t*)&p[i] = i & 0xffff;

	printf("Test 32bit stores\n");
	for (i = 0;i < len;i += 4)	
		*(uint32_t*)&p[i] = i;

	printf("Test 64bit stores\n");
	for (i = 0;i < len;i += 8)	
		*(uint64_t*)&p[i] = i;
		

	printf("Test 128bit loads/stores\n");

	__m128 v ;
	
 	for (i = 0;i < len;i += 16)	{
		v = _mm_load_ps((float*)(p + i));
		_mm_store_ps((float*)(p + i),v);
	}

	heap_delete(p);

	printf("Got no unaligned addr exception!\n");
	return 0;
}

