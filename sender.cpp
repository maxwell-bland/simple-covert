#include "util.hpp"

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

		// Put your covert channel code here
    while (*text_p != 0) {
      for (int i = 0; i < 8; i++) {
        write_bit(1);
      }

      unsigned char c = text_p[0];
      for (int k = 0; k < 2; k++) {
        for (int i = 0; i < 4; i++) {
          for (int j = 0; j < 4; j++) {
            if (j == i) {
              write_bit(get_bit(c,i));
            } else {
              write_bit(get_bit(c,i) ^ get_bit(c,j));
            }
          }
        }
        c >>= 4;
      }

      text_p++;
      len++;
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


