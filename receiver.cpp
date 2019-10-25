#include"util.hpp"

unsigned int my_msg_num = 0;
unsigned int msg_num = 0;

int main(int argc, char **argv)
{
	// Put your covert channel setup code here

	printf("Please press enter.\n");

  unsigned char recv_buf[256] = {0};
	char text_buf[2];
	fgets(text_buf, sizeof(text_buf), stdin);

	printf("Receiver now listening.\n");

  while (1) {
    unsigned int res = recv_msg(recv_buf, sizeof(recv_buf));
    if (res != -1) {
      msg_num = res;
      if (msg_num == my_msg_num) {

	int i = 0;
	while(recv_buf[i]) {
	  printf("%c", recv_buf[i]);
	  i++;
	}
	my_msg_num++;
      }
    }

    char ack_buf[sizeof(unsigned int) + 1] = {0};
    *((unsigned int *)ack_buf) = msg_num;
    send_message(ack_buf, sizeof(unsigned int));
  }

	printf("Receiver finished.\n");

	return 0;
}


