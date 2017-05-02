#include <MCP2515.h>


void sendCanMsg(CANMSG msg, int del = 0, bool output = true);
bool isFiltered(CANMSG msg);
void printPackage(CANMSG msg, bool newline = true);
void sendCanMessages(int addrs, uint8_t *data, int count, bool output = false);
CANMSG createCANPackage(unsigned long addr, byte len, byte byte0, byte byte1 = 0, byte byte2 = 0, byte byte3 = 0, byte byte4 = 0, byte byte5 = 0, byte byte6 = 0, byte byte7 = 0);
uint8_t fromBinaryString(String data);
uint8_t fromHexString(String data);
String getValue(String data, int index);
