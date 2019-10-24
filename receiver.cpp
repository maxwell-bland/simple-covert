#include"util.hpp"

unsigned int msg_num = 0;

int main(int argc, char **argv)
{
	// Put your covert channel setup code here

	printf("Please press enter.\n");

  unsigned char recv_buf[129] = {0};
	char text_buf[2];
	fgets(text_buf, sizeof(text_buf), stdin);

	printf("Receiver now listening.\n");

  while (1) {
    unsigned int res = recv_msg(recv_buf, sizeof(recv_buf));
    if (res != -1) {
      printf("MSG NUM RECV %d\n", res);
      msg_num = res;
    }

    char ack_buf[sizeof(unsigned int) + 1] = {0};
    *((unsigned int *)ack_buf) = msg_num;
    send_message(ack_buf, sizeof(unsigned int));
  }

	printf("Receiver finished.\n");

	return 0;
}


