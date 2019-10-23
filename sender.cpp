#include "util.hpp"

void write_bit(int b) {
  unsigned long long foo;
  unsigned int bar;
  int t;

  fprintf(stderr, "SENDER STARTING SYNC\n");

  while (1) {
    t = get_time(&bar);
    if (t / SYNC_TIME == 5) {
      break;
    }
  }

  fprintf(stderr, "SENDER STARTING SEND %d\n", b);

  while (1) {
    if (b) {
      read_rand(&foo);
    }

    t = get_time(&bar);
    if (t / SYNC_TIME == 4) {
      break;
    }
  }

  fprintf(stderr, "SENDER ENDING SEND\n");
}

int next_bit_one(unsigned char * cp) {
  int res = (*cp) & 1;
  *cp = (*cp) >> 1;
  return res;
}

int main(int argc, char **argv)
{
	// Put your covert channel setup code here

	printf("Please type a message.\n");

	bool sending = true;
	while (sending) {
		char text_buf[128];
    char * text_p = text_buf;
		fgets(text_buf, sizeof(text_buf), stdin);
		// Put your covert channel code here
    while (*text_p != 0) {
      unsigned char c = text_p[0];
      for (unsigned long i = 0; i < sizeof(unsigned char); i ++) {
        write_bit(next_bit_one(&c));
      }
      text_p++;
    }
	}

	printf("Sender finished.\n");

	return 0;
}


