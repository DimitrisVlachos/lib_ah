
#include "aligned_heap.h"
#include <time.h>
#include <stdio.h>


int main() {
	const uint32_t max_iterations = 1U*10000U;
	uint32_t i;
	uint32_t passed;
	const uint32_t ptr_sz = sizeof(void*);
 
	srand(time(NULL));

	passed = 1U;

	for (i = 0U;i < max_iterations;++i) {
		const uint32_t len = 32U + (rand() & 0xffffffU);
		void* p = heap_new(len);
	 
		printf("Alloc %u(%u kb %u mb) @%p\n",len,len/1024,len/(1024*1024),p);
		if (!p) {
			printf("Out of memory!\n");
			passed = 0U;
			break;
		}
 
		if ( 0U != (((ptrdiff_t)p) & (ptr_sz-1U)) ) {
			printf("Address not aligned by at least %u bytes!\n",ptr_sz);
			passed = 0U;
			break;
		}

		printf("Free %p\n",p);
		heap_delete(p);
	 
	}

	printf("Test %s\n",passed ? "Passed" : "Failed");
	return 0;
}

