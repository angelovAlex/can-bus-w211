#include <MCP2515.h>
#include "CAN_Stuff.h"

extern int len;
extern unsigned long filtered[];
extern MCP2515 canB;


unsigned int addr_list[100];
unsigned int addr_value[100];
unsigned int add_list_len = 0;
void analizePackage(CANMSG msg){

  //find package in packages history
  int found_adrs = -1;
  bool isNew = false;
  for (int i = 0; i < add_list_len; i++){
    if (addr_list[i] == msg.adrsValue) {
      found_adrs = i;
      break;
    }
  }
  if (found_adrs >= 0) {
    addr_value[found_adrs] = addr_value[found_adrs] + 1;
    //isNew = true;
  } else {
    if (add_list_len < 100) {
      addr_list[add_list_len] = msg.adrsValue;
      addr_value[add_list_len] = 1;
      add_list_len++;
      isNew = true;
    } else {
      Serial.println("skip");
    }
  }
  if (isNew) {
    //Serial.println(addr_list[add_list_len-1]);
    //Serial.println(" ");
    //for (int i = 0; i < add_list_len; i++) {
    //  Serial.print(addr_list[i]);
    //  Serial.print(' ');
    //  Serial.print(addr_value[i]);
    //  Serial.print('\t');
    //}
  }
  
}



bool isFiltered(CANMSG msg){
  for (int i = 0; i < len; i++){
    if (filtered[i] == msg.adrsValue) {
      return true;
    }
  }
  return false;
}


void printPackage(CANMSG msg, bool newline = true) {
  
    if (msg.isExtendedAdrs) {
      Serial.println("extended");
    }
    Serial.print(millis());
    Serial.print(" ");
    Serial.print(msg.adrsValue, HEX);
    Serial.print(" ");
    Serial.print(msg.dataLength);
    Serial.print(" ");
    for (int i = 0; i < msg.dataLength; i++){
      char bla[10];
      //
      //Serial.print(" ");
      sprintf(bla, "%02x", msg.data[i]);
      Serial.print(bla);
      Serial.print(" ");
    }
    if (newline) {
      Serial.println(" ");
    }   
}

void sendCanMsg(CANMSG msg, int del = 0, bool output = true) {
    canB.transmitCANMessage(msg, 100);
    if (output) {
      printPackage(msg);
    }
    if (del > 0) {
      delay(del);
    }
}
    

void sendCanMessages(int addrs, uint8_t *data, int count, bool output = false) {
  for (int i = 0; i < count; i++){
    CANMSG msg = createCANPackage(addrs, 8, data[0+i*8], data[1+i*8], data[2+i*8], data[3+i*8], data[4+i*8], data[5+i*8], data[6+i*8], data[7+i*8]);
    canB.transmitCANMessage(msg, 100);
    if (output) printPackage(msg);
    //delay(10);
  }
}

CANMSG createCANPackage(unsigned long addr, byte len, byte byte0, byte byte1 = 0, byte byte2 = 0, byte byte3 = 0, byte byte4 = 0, byte byte5 = 0, byte byte6 = 0, byte byte7 = 0) {
    CANMSG msg;
    msg.adrsValue = addr;
    msg.isExtendedAdrs = false;
    msg.rtr = false;
    msg.dataLength = len;
    msg.data[0] = byte0;
    msg.data[1] = byte1;
    msg.data[2] = byte2;
    msg.data[3] = byte3;
    msg.data[4] = byte4;
    msg.data[5] = byte5;
    msg.data[6] = byte6;
    msg.data[7] = byte7;
    return msg;
}

uint8_t fromHexString(String data) 
{
  uint8_t val = 0;
  if (data.length() == 0) return val;
  val = (data[0] >= 'a') ? ((data[0] - 'a' + 10) * 16) : ((data[0] - '0') * 16);
  if (data.length() == 1) return val/16;
  val += (data[1] >= 'a') ? ((data[1] - 'a' + 10)) : ((data[1] - '0'));
  return val;
}

uint8_t fromBinaryString(String data) 
{
  uint8_t val = ((data[0] == '1')?128:0) + ((data[1] == '1')?64:0) + ((data[2] == '1')?32:0) + ((data[3] == '1')?16:0) + ((data[4] == '1')?8:0) + ((data[5] == '1')?4:0) + ((data[6] == '1')?2:0) + ((data[7] == '1')?1:0);
  //b 68 4 00000000 00000000 00000000 00000000
  return val;
}

String getValue(String data, int index)
{
    int maxIndex = data.length() - 1;
    int j = 0;
    String chunkVal = "";

    for (int i = 0; i <= maxIndex && j <= index; i++)
    {
        chunkVal.concat(data[i]);

        if (data[i] == ' ')
        {
            j++;

            if (j > index)
            {
                chunkVal.trim();
                return chunkVal;
            }

            chunkVal = "";
        }
        else if ((i == maxIndex) && (j < index)) {
            chunkVal = "";
            return chunkVal;
        }
    }   
}


