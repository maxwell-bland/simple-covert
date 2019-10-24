#include"util.hpp"

int recv_msg(unsigned char * buf) {
  unsigned char buf_i = buf;
  unsigned char c = 0;
  while (c != 0xFF) {
    c = c << 1;
    c |= read_bit();
  }

  int len = 0
  while (1) {
    for (unsigned long i = 0; i < sizeof(unsigned char) * 8; i++) {
      *buf |= (read_bit() << i);
    }

    if ((*buf) == 0xFF) {
      break;
    }

    if (*buf) {
      buf++;
      len++;
    }
  }
  buf = buf_i;

  unsigned int chk = 0;
  for (int i = 0; i < len - 1; i++) {
    chk += buf[i];
  }

  chk &= 0xFF;
  chk ^= 0xFF;
  chk++;

  if (chk != buf[len - 1]) {
    return -1;
  }

  for (int i = 0; i < len - 1 - sizeof(unsigned int); i++) {
    printf("%c", buf[i]);
  }

  unsigned int msg_num = -1;
  unsigned char * msg_num_p = (unsigned char *) &msg_num;
  for (int i = len - 1 - sizeof(unsigned int); i < len - 1; i++) {
    *msg_num_p = buf[i];
    msg_num_p++;
  }

  return msg_num;
}

int main(int argc, char **argv)
{
	// Put your covert channel setup code here

	printf("Please press enter.\n");

  unsigned char recv_buf[128] = {0};
	char text_buf[2];
	fgets(text_buf, sizeof(text_buf), stdin);

	printf("Receiver now listening.\n");

  while (1) {
    recv_msg(recv_buf);
  }

	printf("Receiver finished.\n");

	return 0;
}


