#include <MCP2515.h>

class Car {
  public:
  bool engineOn = false;
  float temp = 24.0;
  float outsideTemp = 24.0;
  float voltage = 0.0;
  float consumption = 0;
  float consumption_total = 0;
  unsigned long consumption_total_last_time = 0;
  int speeed = 0;
  
  unsigned long start_odometer = 0;
  float distance_after_start = 0;
  
  unsigned int consumptionBig = -1;
  unsigned int consumptionSmall = -1;
  
  unsigned long consumptionUpdate2 = 0;
  
  

  bool heater1_was_enabled_once = false;
  bool heater2_was_enabled_once = false;

  uint8_t seat2_status = 0;


  uint8_t ic_current_menu = 2;
  unsigned long ic_menu_last_update = 0;

  unsigned long steering_button_pressed_last_time = 0;

  bool enable_ic_output_debug = false;
};


void doWork(CANMSG msg);
void closeWindows(boolean closew = true);
void ic_receive_consuption(CANMSG msg);
void ic_update_view();


