
// You may only use fgets() to pull input from stdin
// You may use any print function to stdout to print
// out chat messages
#include <stdio.h>

// You may use memory allocators and helper functions
// (e.g., rand()).  You may not use system().
#include <stdlib.h>

#include <inttypes.h>
#include <time.h>

#ifndef UTIL_H_
#define UTIL_H_

#define ADDR_PTR uint64_t
#define CYCLES uint32_t

#define SYNC_TIME 1000000
#define time_period(x) (x % (10 * SYNC_TIME)) / SYNC_TIME

int get_time(unsigned int * p);
int read_rand(unsigned long long * p);
CYCLES measure_one_block_access_time(ADDR_PTR addr);

#endif
