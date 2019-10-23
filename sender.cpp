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
    }

    for (int i = 0; i < 8; i++) {
      write_bit(1);
    }

	}

	printf("Sender finished.\n");

	return 0;
}


