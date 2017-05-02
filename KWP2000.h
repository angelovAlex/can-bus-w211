#include <MCP2515.h>

#define ID_AGW_TO_KOMBO 420
#define ID_KOMBO_TO_AGW 464
#define DIAG_ID_KOMBO_KWP_REQ_ID 0x5b4
#define DIAG_ID_KOMBO_KWP_RES_ID 0x4f4

class KWP {

  public:
  bool diag_running = false;

  unsigned long last_keep_alive = 0;

  unsigned long request_id = 99999;
  unsigned long response_id = 99999;
  uint8_t response[72];
  uint8_t response_len = 0;
  bool response_received = false;

  bool debug_output = false;
  
};

void diag_start();
void diag_stop();
void diag_loop();
bool diag_receive_response(CANMSG msg, bool should_answer = true);
void diag_get_value(unsigned long addr, uint8_t value);
void diag_read_ecu_id(unsigned long addr);
void diag_incapsulate(uint8_t *input, uint8_t input_len, uint8_t *output, uint8_t *output_len);
void diag_send_kwp(uint8_t *data, uint8_t len, bool hash);
void diag_send(unsigned long adrs, uint8_t *data, uint8_t len, bool hash);
