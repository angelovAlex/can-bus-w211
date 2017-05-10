#include <MCP2515.h>

void ic_music_center_line_test(char *str, uint8_t test_param,  uint8_t offset);
void ic_music_center_line(char *str);
void ic_music_top_line(char *str);
void ic_music_show_arrows(uint8_t up, uint8_t down);
void ic_package24(uint8_t val1, uint8_t val2, uint8_t val3, uint8_t val4, uint8_t val5, uint8_t val6);
void ic_package26(char *line1, char *line2, char *line3, char *line4);

class Decapsulator {
  unsigned long id;

  public:
  uint8_t response[72];
  uint8_t response_len = 0;
  
  Decapsulator(unsigned long id);
  bool receive(CANMSG msg);
};

class Diag {

  private:
  bool started = false;
  unsigned long last_keep_alive = 0;

  public:
  void start();
  void stop();
  void loop();
};

class IC_Screen {

  private:
  bool started = false;
  unsigned int current_menu = 0;
  unsigned long temp_screen_update = 0;
  uint8_t temp_x = 0;
  uint8_t temp_y = 0;

  public:
  Diag *diag;

  IC_Screen(Diag *diag);
  void start();
  void stop();
  void loop();
  void pixel();


  void next_menu();
  void priv_menu();
};


