#include "util.hpp"

unsigned int msg_num = 0;

int main(int argc, char **argv)
{

  while (1) {
    msg_num = 0;
    unsigned char recv_buf[256] = {0};
    char text_buf[128] = {0};
    fgets(text_buf, sizeof(text_buf) - 1, stdin);

    int i = 0;
    while (text_buf[i]) {
      i++;
    }

    size_t text_size = i;
    clock_t begin = clock();

    while (1) {
      send_message(text_buf, text_size);
      if (recv_msg(recv_buf, sizeof(recv_buf)) != -1) {
        if (msg_num == ((unsigned int *)recv_buf)[0]) {
          msg_num++;
          break;
        }
      }
    }

    clock_t end = clock();
    double time_spent = ((double)(end - begin)) / CLOCKS_PER_SEC;
    double bytes_per_sec = text_size / time_spent;
    fprintf(stderr, "B/sec %f\n", bytes_per_sec);

    char done[1] = {(char)0xF0};
    while (1) {
      send_message(done, 4);
      if (recv_msg(recv_buf, sizeof(recv_buf)) != -1) {
        if (msg_num == ((unsigned int *)recv_buf)[0]) {
          msg_num++;
          printf("Done recieved!\n");
          break;
        }
      }
    }

    unsigned int res = 0;
    while (1) {
      res = recv_msg(recv_buf, sizeof(recv_buf));
      if (res != -1) {
        if (recv_buf[0] != 0xF0) {
          int i = 0;
          while(recv_buf[i]) {
            printf("%c", recv_buf[i]);
            i++;
          }
        } else {
          char ack_buf[sizeof(unsigned int) + 1] = {0};
          *((unsigned int *)ack_buf) = res;
          send_message(ack_buf, sizeof(unsigned int));

          printf("Please type a message.\n");
          break;
        }
      }

      char ack_buf[sizeof(unsigned int) + 1] = {0};
      *((unsigned int *)ack_buf) = res;
      send_message(ack_buf, sizeof(unsigned int));
    }
  }









  /*
	// Put your covert channel setup code here

	printf("Please type a message.\n");

	bool sending = true;
	while (sending) {
    unsigned char recv_buf[256] = {0};
		char text_buf[128] = {0};
		fgets(text_buf, sizeof(text_buf) - 1, stdin);

    int i = 0;
    while (text_buf[i]) {
      i++;
    }

    size_t text_size = i;
    clock_t begin = clock();

    // Do send
    while (1) {
      send_message(text_buf, text_size);
      if (recv_msg(recv_buf, sizeof(recv_buf)) != -1) {
        if (msg_num == ((unsigned int *)recv_buf)[0]) {
          //printf("ACK SUCCESS!\n");
          msg_num++;
          break;
        }
      }
    }

    clock_t end = clock();
    double time_spent = ((double)(end - begin)) / CLOCKS_PER_SEC;
    double bytes_per_sec = text_size / time_spent;
    fprintf(stderr, "B/sec %f\n", bytes_per_sec);
	}
  */

	printf("Sender finished.\n");

	return 0;
}


