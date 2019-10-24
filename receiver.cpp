#include"util.hpp"

/*int read_bit() {
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
  }*/

int main(int argc, char **argv)
{
	// Put your covert channel setup code here

	printf("Please press enter.\n");

	char text_buf[2];
	fgets(text_buf, sizeof(text_buf), stdin);

	printf("Receiver now listening.\n");

  while (1) {
    unsigned char num_ones = 0;
    while (num_ones != 0xFF) {
      num_ones = num_ones << 1;
      num_ones |= read_bit();
    }

    unsigned char c = 0;
    bool listening = true;
    while (listening) {
      for (unsigned long i = 0; i < sizeof(unsigned char) * 8; i++) {
        c |= (read_bit() << i);
      }

      if (c == 0xFF) {
        break;
      }

      if (c) {
        fprintf(stderr, "%c", c);
        c = 0;
      }
    }
  }

	printf("Receiver finished.\n");

	return 0;
}


