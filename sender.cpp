#include "util.hop"

unsigned int msg_num = 0;

unsigned int next_bit_one(unsigned char * cp) {
  unsigned int res = (*cp) & 1;
  *cp = (*cp) >> 1;
  return res;
}

void send_char(unsigned char * c) {
  for (unsigned long i = 0; i < sizeof(unsigned char) * 8; i++) {
    write_bit(next_bit_one(c));
  }
}

void send_message(char * buf) {
  for (int i = 0; i < 8; i++) {
    write_bit(1);
  }

  unsigned char c;
  unsigned int chk = 0;

  while (*buf != 0) {
    c = buf[0];
    send_char(&c);
    chk += c;
    buf++;
  }

  for (int i = 0; i < sizeof(unsigned int); i++) {
    c = ((unsigned char *)msg_num) + i;
    send_char(&c)
    chk += c;
  }

  chk &= 0xFF;
  chk ^= 0xFF;
  chk++;
  c = chk;
  send_char(&c);

  for (int i = 0; i < 8; i++) {
    write_bit(1);
  }
}

int main(int argc, char **argv)
{
	// Put your covert channel setup code here

	printf("Please type a message.\n");

	bool sending = true;
	while (sending) {
		char text_buf[128];
		fgets(text_buf, sizeof(text_buf), stdin);
    send_message(text_buf);
	}

	printf("Sender finished.\n");

	return 0;
}


