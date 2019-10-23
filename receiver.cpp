
#include"util.hpp"

int read_bit() {
  unsigned long long foo;
  unsigned int bar;
  int t1, t2;

  fprintf(stderr, "RECEIVER STARTING SYNC\n");

  while (1) {
    t1 = get_time(&bar);
    if ((t1 % (10 * SYNC_TIME)) / SYNC_TIME == 5) {
      break;
    }
  }

  fprintf(stderr, "RECEIVER STARTING RECV\n");

  unsigned long iters = 0;
  float avg = 0.0;
  while (1) {
    iters++;
    t1 = get_time(&bar);
    read_rand(&foo);
    t2 = get_time(&bar);
    avg += t2 - t1;
    if ((t2 % (10 * SYNC_TIME)) / SYNC_TIME == 4) {
      break;
    }
  }
  avg /= iters;

  fprintf(stderr, "%d\n", (int) (avg < 320));
  // fprintf(stderr, "RECEIVER ENDING RECV %f avg\n", avg);

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
    for (unsigned long i = 0; i < sizeof(unsigned char); i ++) {
      c |= read_bit();
      c <<= 1;
    }
		// Put your covert channel code here
    // printf("%c", c);
	}

	printf("Receiver finished.\n");

	return 0;
}


