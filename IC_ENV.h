#include <MCP2515.h>

class IC_ENV {
  public:
  unsigned long last_every_second = 0;
  bool all_output = false;
  int stepp = 0;
  bool inited = false;

  uint8_t data24[30];
  uint8_t data24_len = 0;
  uint8_t data26[50];
  uint8_t data26_len = 0; 
};

void ic_env_loop();
void ic_env_w();
void ic_env_a();
void ic_env_s();
void ic_env_d();
void ic_env_receive(CANMSG msg);
