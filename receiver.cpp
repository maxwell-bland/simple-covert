
#include"util.hpp"

int read_bit() {
  unsigned long long foo;
  unsigned int bar;

  fprintf(stderr, "RECEIVER STARTING SYNC\n");

  while (1) {if (time_period(get_time(&bar)) == 5) break;}

  fprintf(stderr, "RECEIVER STARTING RECV\n");

  unsigned long iters = 0;
  float avg = 0.0;
  while (1) {
    iters++;
    avg += read_rand(&foo);
    if (time_period(get_time(&bar)) == 4) break;
  }
  avg /= iters;

  fprintf(stderr, "RECEIVER ENDING RECV %f avg\n", avg);

  return 1;
}

int main(int argc, char **argv)
{
	// Put your covert channel setup code here

	printf("Please press enter.\n");

	char text_buf[2];
	fgets(text_buf, sizeof(text_buf), stdin);

	printf("Receiver now listening.\n");

  unsigned char c = 0;
	bool listening = true;
	while (listening) {
    for (unsigned long i = 0; i < sizeof(unsigned char) * 8; i ++) {
      c |= read_bit();
      c <<= 1;
    }
	}

	printf("Receiver finished.\n");

	return 0;
}


