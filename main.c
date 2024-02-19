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

#define SHSTK_SIZE			(512 * PAGE_SIZE)

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

void* create_shstk(size_t size, int create_restore_token) {
	void *mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (mem == MAP_FAILED) {
		printf("map failed\n");
		return NULL;
	}

	// seems like the memory needs to actually be allocated (or there is some fucky wucky with the fault handling)
	for (int i = 0; i < size; i++) {
		((char*)mem)[i] = 0;
	}

	// create a restore token
	if (create_restore_token) {
		void *stack_start = ((char*)mem) + size - PAGE_SIZE;
		*(unsigned long long*)stack_start = (unsigned long long) stack_start;
	}

	// set the shadow stack page attributes
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

int init_isst() {
	unsigned long long* a = mmap(NULL, 8 * sizeof(unsigned long long), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (a == NULL) {
		printf("failed to init ISST\n");
		return -1;
	}
	for (int i = 1; i < 8; i++) {
		void* shstk = create_shstk(SHSTK_SIZE, 1);
		if (shstk == NULL) {
			printf("failed to init ISST shadow stack at index %d\n", i);
			return -2;
		}
		a[i] = (unsigned long long)(((char*)shstk) + SHSTK_SIZE - PAGE_SIZE);
		
		printf("ISST entry created at %d: %llx token:%llx\n", i, a[i], ((unsigned long long*)a[i])[0]);
	}
	wrmsrl(MSR_IA32_INT_SSP_TAB, (unsigned long long) a);
	return 0;
}

// the win function, shows the flag
void g() {
	printf("flag: ma-ta\n");
}

// has buffer overflow that could be used to call g
// currently fopen does not work for some reason
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
	a[i] = 0;
	printf("read: %s\n", a);
}

void h(int size) {
	char c[32];
	for (int i = 0; i < size; i++) {
		c[i] = 'A';
	}
	c[31] = 0;
	printf("Hello %s\n", c);
}

// c and fact are used to make sure
// the recursive calls are actually done as such and
// the compiler does not optimise them away.
// Checked with godbolt, SHOULD generate recursive calls.
int c() {
    int a = 5;
    for (int i = 0; i < 1000; i++) {
        a &= i;
    }
    return (a & 25);
}


int fact(int n) {
    if (n <= 1) {
        return 1;
    }
    return fact(n - 1) + fact(n - 2) + fact(n - 3);
}

int main()
{
	void *shstk;

	cr4_enable_cet();

	shstk = create_shstk(SHSTK_SIZE, 1);
	if (shstk == NULL) {
		printf("failed to create shstk\n");
		return 1;
	}

	if (init_isst() < 0) {
		printf("failed to initialize ISST\n");
		return 2;
	}

	wrmsrl(MSR_IA32_PL0_SSP, (unsigned long long)(((char*)shstk) + SHSTK_SIZE - PAGE_SIZE));
	wrmsrl(MSR_IA32_S_CET, CET_SHSTK_EN);
	asm volatile ("setssbsy" : : :); // apparently, for supervisor shadow stacks, this instruction needs to be called
					 // and a "restore token" set in the shadow stack

	void *ssp = 0x1;
	asm volatile ("rdsspq %0" : "=r"(ssp) : : );
	
	int n = fact(c() + 12);
	printf("SSP: %p recursive: %d\n", ssp, n);
//	h(128);
	FILE *f = fopen("payload.bin", "rb"); //- does not work, need to check why
	if (f == NULL) {
		printf("file ptr is null\n");
	}
	printf("REEEEEEEE\n");
	//g();
	//f();

	// asm volatile ("clrssbsy %0" : : "r"((unsigned long long)ssp) :); -- the opposite of setssbsy, looks like the code runs fine without it
									    // still, should try to get this working
	wrmsrl(MSR_IA32_S_CET, 0);
	wrmsrl(MSR_IA32_PL0_SSP, 0);

	munmap(shstk, SHSTK_SIZE);

	return 0;
}
