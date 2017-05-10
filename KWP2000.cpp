#include <MCP2515.h>
#include "AI.h"
#include "CAN_Stuff.h"
#include "IC.h"
#include "KWP2000.h"

extern MCP2515 canB;

KWP kwp = KWP();
void diag_start()
{
  Serial.println("Diag: Started");
  kwp.diag_running = true;
  kwp.last_keep_alive = millis();
  canB.sendMsg(0x1c, 8, 0x02, 0x10, 0x92 /*0x85*/, 0xff, 0xff, 0xff, 0xff, 0xff);
  //CANMSG msg1 = createCANPackage(0x1c, 8, 0x02, 0x10, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff); 
  //canB.transmitCANMessage(msg1, 100);
  //if (kwp.debug_output) printPackage(msg1);
}

void diag_stop()
{
  kwp.diag_running = false;
  Serial.println("Diag: Stopped");
}

void diag_loop()
{
  if (!kwp.diag_running) return;
  if (millis() - kwp.last_keep_alive > 1000) {
    kwp.last_keep_alive = millis();
    canB.sendMsg(0x1c, 8, 0x02, 0x3e, 0x02, 0xff, 0xff, 0xff, 0xff, 0xff);
    //CANMSG msg1 = createCANPackage(0x1c, 8, 0x02, 0x3e, 0x02, 0xff, 0xff, 0xff, 0xff, 0xff); 
    //canB.transmitCANMessage(msg1, 100);
    //if (kwp.debug_output) printPackage(msg1);
  }
}

void diag_read_ecu_id(unsigned long addr)
{
  if (addr == DIAG_ID_KOMBO_KWP_REQ_ID) {
    kwp.response_id = DIAG_ID_KOMBO_KWP_RES_ID;
  } else {
    Serial.println("Diag: Unknown id");
  }
  kwp.request_id = addr;
  canB.sendMsg(addr,8, 0x02, 0x1a, 0x86, 0xff, 0xff, 0xff, 0xff, 0xff);
  //CANMSG msg1 = createCANPackage(addr, 8, 0x02, 0x1a, 0x86, 0xff, 0xff, 0xff, 0xff, 0xff); 
  //canB.transmitCANMessage(msg1, 100);
  //if (kwp.debug_output) printPackage(msg1);
}

void diag_get_value(unsigned long addr, uint8_t value)
{
  canB.sendMsg(addr,8, 0x02, 0x21, value, 0xff, 0xff, 0xff, 0xff, 0xff);
}

bool diag_receive_response(CANMSG msg, bool should_answer = true)
{
  
  if (msg.adrsValue != kwp.response_id) return false;
  //Serial.print("res ");
  //printPackage(msg);
  if (msg.data[0] < 0x10){
    if (msg.data[1] == 0x7f && msg.data[3] == 0x78){
      //Serial.println("Diag: processing...");
      return true;
    }
    //printPackage(msg);
    kwp.response_len = msg.data[0];
    kwp.response_received = true;
    for (int i = 0; i < 7; i++) kwp.response[i] = msg.data[i+1];
    //Serial.print("Diag: Full response: ");
    for (int i = 0; i < kwp.response_len; i++) {
      //Serial.print(kwp.response[i], HEX);
      //Serial.print(" ");
    }
    //Serial.println();
  } else if (msg.data[0] == 0x10){
    //

    kwp.response_received = false;
    kwp.response_len = msg.data[1];
    for (int i = 0; i < 6; i++) kwp.response[i] = msg.data[i+2];
    //Serial.println("Diag: response");
    //printPackage(msg);
    if (should_answer) {
      canB.sendMsg(kwp.request_id,8, 0x30, 0x08, 0x14, 0xff, 0xff, 0xff, 0xff, 0xff);
      //CANMSG msg1 = createCANPackage(kwp.request_id, 8, 0x30, 0x08, 0x14, 0xff, 0xff, 0xff, 0xff, 0xff); 
      //canB.transmitCANMessage(msg, 100);
      //if (kwp.debug_output) printPackage(msg1);
    }
  } else if (msg.data[0] == 0x30) {
      return true; 
  } else if (msg.data[0] > 0x20){
    uint8_t p_number = msg.data[0] - 0x20;
    uint8_t offset = 6 + (p_number-1)*7;
    //Serial.println(offset);
    //Serial.println(kwp.response_len);
    for (int i = 0; i < 7; i++) kwp.response[i+offset] = msg.data[i+1];
    //Serial.println("Diag: response");
    //printPackage(msg);
    if (offset + 7 >= kwp.response_len) {
      //Serial.print("Diag: Full response: ");
      kwp.response_received = true;
      for (int i = 0; i < kwp.response_len; i++) {
        //Serial.print(kwp.response[i], HEX);
        //Serial.print(" ");
      }
      //Serial.println();
    }
  }
  return true;
}

void diag_incapsulate(uint8_t *input, uint8_t input_len, uint8_t *output, uint8_t *output_len)
{
    if (input_len < 7) {
        output[0] = input_len;
        for (int i = 0; i < input_len; i++) {
            output[i+1] = input[i];
        }
        *output_len = 8;
    } else {
        output[0] = 0x10;
        output[1] = input_len;
        for (int i = 0; i < 6; i++) output[i+2] = input[i];
        output[8] = 0x21;
        int val = min(7, input_len - 6);
        for (int i = 0; i < val; i++) output[i+9] = input[i+6];
        *output_len = 16;
        if (input_len > 13) {
            output[16] = 0x22;
            int val = min(7, input_len - 13);
            for (int i = 0; i < val; i++) output[i+17] = input[i+13];
            *output_len = 24;
        }
        if (input_len > 20) {
            output[24] = 0x23;
            int val = min(7, input_len - 20);
            for (int i = 0; i < val; i++) output[i+25] = input[i+20];
            *output_len = 32;
        }
        if (input_len > 27) {
            //error
            printf("too big!");
        }
    }
}

void diag_send(unsigned long adrs, uint8_t *data, uint8_t len, bool hash)
{
  if (hash) {
    uint8_t hash2 = 0xff;
    for (int i = 0; i < len; i++) hash2 -= (i + data[i]);
    data[len] = hash2;
  }
  
  uint8_t output2[48];
  uint8_t output_len;
  diag_incapsulate(data, (hash)?len+1:len, output2, &output_len);
  sendCanMessages(adrs, output2, output_len/8, true);
}

void diag_send_kwp(uint8_t *data, uint8_t len, bool hash)
{

    uint8_t hash2 = 0xff;
    for (int i = 0; i < len; i++) hash2 -= (i + data[i]);
    data[len] = hash2;

    uint8_t output2[48];
    uint8_t output_len;
    diag_incapsulate(data, len+1, output2, &output_len);
    sendCanMessages(420, output2, output_len/8, true);
}


