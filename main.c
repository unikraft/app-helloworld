#include <stdio.h>
#include <sys/mman.h>

#define PAGE_ATTR_PROT_READ		0x01 /* Page is readable */
#define X86_PTE_DIRTY			0x040UL
#define PAGE_SIZE 4096

#define X86_CR4_CET			(1 << 23)

#define MSR_IA32_U_CET			0x000006a0 /* user mode cet */
#define MSR_IA32_S_CET			0x000006a2 /* kernel mode cet */

#define MSR_IA32_PL0_SSP		0x000006a4 /* ring-0 shadow stack pointer */
#define MSR_IA32_PL1_SSP		0x000006a5 /* ring-1 shadow stack pointer */
#define MSR_IA32_PL2_SSP		0x000006a6 /* ring-2 shadow stack pointer */
#define MSR_IA32_PL3_SSP		0x000006a7 /* ring-3 shadow stack pointer */
#define MSR_IA32_INT_SSP_TAB		0x000006a8 /* exception shadow stack table */

#define CET_SHSTK_EN			(1 << 0)

static inline void wrmsr(unsigned int msr, __u32 lo, __u32 hi)
{
	asm volatile("wrmsr"
			     : /* no outputs */
			     : "c"(msr), "a"(lo), "d"(hi));
}

static inline void wrmsrl(unsigned int msr, __u64 val)
{
	wrmsr(msr, (__u32) (val & 0xffffffffULL), (__u32) (val >> 32));
}

void cr4_enable_cet() {
	unsigned long cr4_val;
	asm volatile ("mov %%cr4, %0\n\t" : "=r" (cr4_val) : :);
	cr4_val |= X86_CR4_CET;
	asm volatile ("mov %0, %%cr4\n\t" : : "r" (cr4_val) :);
}

void* create_shstk(size_t size) {
	void *mem = mmap(NULL, size, PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (mem == MAP_FAILED) {
		printf("map failed\n");
		return NULL;
	}
	struct uk_vas* vas = uk_vas_get_active();
	if (vas == NULL) {
		printf("failed to get vas\n");
		return NULL;
	}
	int rc = uk_vma_set_attr(vas, mem, size, PAGE_ATTR_PROT_READ | X86_PTE_DIRTY, 0);
	if (rc != 0) {
		printf("failed to set attributes rc=%d\n", rc);
		return NULL;
	}
	return mem;
}

void g() {
	printf("flag: ma-ta\n");
}

void f() {
	char a[32];
	FILE *fd = fopen("payload.bin", "rb");
	if (fd == NULL) {
		printf("failed to open payload file\n");
		return;
	}
	int i;
	for (i = 0; i < 128; i++) {
		char c;
		if(fread(&c, 1, 1, fd) == 0) {
		//	printf("done after %d bytes\n", i);
			break;
		}
		//printf("read one: %c\n", c);
		a[i] = c;
	}
	a[i + 5] = 0;
	printf("read: %s\n", a);
}

int main()
{
	void *shstk;

	size_t shstk_len = 12 * PAGE_SIZE;

	cr4_enable_cet();

	shstk = create_shstk(shstk_len);
	if (shstk == NULL) {
		printf("failed to create shstk\n");
		return 1;
	}

	wrmsrl(MSR_IA32_PL0_SSP, shstk + shstk_len - PAGE_SIZE);
	wrmsrl(MSR_IA32_S_CET, CET_SHSTK_EN);

	printf("Hello world!\n");

//	f();

	wrmsrl(MSR_IA32_S_CET, 0);
	wrmsrl(MSR_IA32_PL0_SSP, 0);

	munmap(shstk, shstk_len);

	return 0;
}
