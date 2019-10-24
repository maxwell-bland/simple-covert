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

    unsigned char c = 0;
    bool listening = true;
    while (listening) {
      unsigned char num_ones = 0;
      while (num_ones != 0xFF) {
        num_ones = num_ones << 1;
        num_ones |= read_bit();
      }

      for (int k = 0; k < 2; k++) {
        int boxes[4];
        int votes[4][4];
        for (int i = 0; i < 4; i++) {
          for (int j = 0; j < 4; j++) {
            votes[i][j] = read_bit();
          }
        }

        for (int i = 0; i < 4; i++) {
          boxes[i] = votes[i][i];
          for (int j = 0; j < 4; j++) {
            if (i != j) {
              boxes[i] += votes[i][j] ^ votes[j][j];
            }
          }
        }

        for (int i = 0; i < 4; i++) {
          if ((votes[i][i] == 0 && boxes[i] > 2) ||
              (votes[i][i] == 1 && boxes[i] < 2)) {
            votes[i][i] ^= 1;
            for (int j = 0; j < 4; j++) {
              if (j != i) {
                votes[j][i] ^= 1;
              }
            }
            i = -1;
          }
        }

        for (int i = 0; i < 4; i++) {
          c |= ((votes[i][i] << (4 * k)) << i);
        }
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


