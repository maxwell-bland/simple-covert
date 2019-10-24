#include "util.hpp"

unsigned int msg_num = 0;

int main(int argc, char **argv)
{
	// Put your covert channel setup code here

	printf("Please type a message.\n");

	bool sending = true;
	while (sending) {
    unsigned char recv_buf[129] = {0};
		char text_buf[128] = {0};
		fgets(text_buf, sizeof(text_buf) - 1, stdin);

    int i = 0;
    while (text_buf[i]) {
      i++;
    }

    size_t text_size = i - 1;
    clock_t begin = clock();

    // Do send
    while (1) {
      send_message(text_buf, text_size);
      if (recv_msg(recv_buf, sizeof(recv_buf)) != -1) {
        if (msg_num == ((unsigned int *)recv_buf)[0]) {
          printf("ACK SUCCESS!\n");
          msg_num++;
          break;
        }
      }
    }

    clock_t end = clock();
    double time_spent = (end - begin) / CLOCKS_PER_SEC;
    double bytes_per_sec = text_size / time_spent;
    printf("B/sec %f\n", bytes_per_sec);
	}

	printf("Sender finished.\n");

	return 0;
}


