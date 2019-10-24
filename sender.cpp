#include "util.hpp"

unsigned int next_bit_one(unsigned char * cp) {
  unsigned int res = (*cp) & 1;
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

    int len = 0;
    clock_t begin = clock();
    
    for (int i = 0; i < 8; i++) {
      write_bit(1);
    }

		// Put your covert channel code here
    while (*text_p != 0) {

      unsigned char c = text_p[0];
      for (unsigned long i = 0; i < sizeof(unsigned char) * 8; i++) {
        write_bit(next_bit_one(&c));
      }
      text_p++;
      len++;
    }

    for (int i = 0; i < 8; i++) {
      write_bit(1);
    }

    clock_t end = clock();
   
    double time_spent = (long double)(end-begin) / CLOCKS_PER_SEC;
    printf("totalTime: %f\n", time_spent);
    double bytes_per_sec = len / time_spent;
    printf("B/sec: %f\n", bytes_per_sec);

	}

	printf("Sender finished.\n");

	return 0;
}


