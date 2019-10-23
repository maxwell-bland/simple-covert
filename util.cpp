
#include "util.hpp"

int read_bit() {
  unsigned long long foo;
  unsigned int bar;

  while (1) {if (time_period(get_time(&bar)) == 5) break;}

  unsigned long iters = 0;
  float avg = 0.0;
  while (1) {
    iters++;
    avg += read_rand(&foo);
    if (time_period(get_time(&bar)) == 4) break;
  }

  avg /= iters;

  return avg < THRESH;
}

void write_bit(unsigned int b) {
  unsigned long long foo;
  unsigned int bar;

  while (1) {if (time_period(get_time(&bar)) == 5) break;}

  while (1) {
    if (b) read_rand(&foo);
    if (time_period(get_time(&bar)) == 4) break;
  }
}

int get_time(unsigned int * p) {
  return __builtin_ia32_rdtscp(p);
}

int read_rand(unsigned long long * p) {
  return __builtin_ia32_rdseed_di_step(p);
}

/* Measure the time it takes to access a block with virtual address addr. */
CYCLES measure_one_block_access_time(ADDR_PTR addr)
{
	CYCLES cycles;

	asm volatile("mov %1, %%r8\n\t"
	"lfence\n\t"
	"rdtsc\n\t"
	"mov %%eax, %%edi\n\t"
	"mov (%%r8), %%r8\n\t"
	"lfence\n\t"
	"rdtsc\n\t"
	"sub %%edi, %%eax\n\t"
	: "=a"(cycles) /*output*/
	: "r"(addr)
	: "r8", "edi");	

	return cycles;
}


