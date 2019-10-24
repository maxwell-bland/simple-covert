
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

extern unsigned int msg_num;

unsigned int next_bit_one(unsigned char * cp) {
  unsigned int res = (*cp) & 1;
  *cp = (*cp) >> 1;
  return res;
}

void send_char(unsigned char c) {
  for (unsigned long i = 0; i < sizeof(unsigned char) * 8; i++) {
    write_bit(next_bit_one(&c));
  }
}

void send_message(char * buf) {
  for (int i = 0; i < 8; i++) {
    write_bit(1);
  }

  unsigned char c;
  unsigned char chk = 0;

  while ((*buf) != 0) {
    c = *buf;

    send_char(c);
    printf("SEND %d\n", c);

    chk += c;

    buf++;
  }

  for (int i = 0; i < sizeof(unsigned int); i++) {
    c = *(((unsigned char *) (&msg_num)) + i);

    send_char(c);
    printf("SEND %d\n", c);

    chk += c;
  }

  chk ^= 0xFF;
  chk++;
  c = chk;
  printf("SENDING %d\n", chk);
  send_char(c);


  for (int i = 0; i < 8; i++) {
    write_bit(1);
  }
}

void recv_char(unsigned char * c) {
  for (unsigned long i = 0; i < sizeof(unsigned char) * 8; i++) {
    *c |= (read_bit() << i);
  }
}

unsigned int recv_msg(unsigned char * buf, unsigned int buf_sz) {
  unsigned char * buf_i = buf;
  unsigned char c = 0;
  for (int i = 0; i < buf_sz; i++) {
    buf[i] = 0;
  }

  while (c != 0xFF) {
    c = c << 1;
    c |= read_bit();
  }

  int len = 0;
  while (1) {
    recv_char(buf);

    if ((*buf) == 0xFF) {
      printf("END SENT\n");
      break;
    }

    printf("RECV %d\n", *buf);
    buf++;
    len++;
  }
  buf = buf_i;

  unsigned char chk = 0;
  for (int i = 0; i < len - 1; i++) {
    chk += buf[i];
  }

  chk ^= 0xFF;
  chk++;

  printf("CHECKSUM %d\n", chk);

  if (len == 0 || chk != buf[len - 1]) {
    return -1;
  }

  unsigned int msg_num = -1;
  unsigned char * msg_num_p = (unsigned char *) &msg_num;
  for (int i = len - 1 - sizeof(unsigned int); i < len - 1; i++) {
    *msg_num_p = buf[i];
    buf[i] = 0;
    msg_num_p++;
  }

  for (int i = 0; i < len - 1 - sizeof(unsigned int); i++) {
    printf("%c", buf[i]);
  }

  return msg_num;
}
