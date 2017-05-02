//TODO:
//try to send longer text
//try to send debug text
//в хеш функцию включить data[9] и попробовать менять

//known pids
//0 - EZS_A1, клемы
//2 - GW_C_B1, rpm, other values
//3 - GW_C_B2, gear, value maybe speed, break pedal, break pedal preasure
//4 - SAM_H_A1, if doors opened, brake pedal is pressed
//5 - GW_C_B7, value, simular to value in 3 but diferent, maybe speed
//6 - BLI_LI, unknown, 6 5 00 20 00 08 04/08/0c/10/14/1c/28/54/etc -
//9 - BSG_A1, always the same 9 3 00 00 01
//10 - SAM_V_A1, 10 7 80 00 00 08/0a 00 00 83 engine started, 82 engine stoped, //дальний, туманки, ручник, уровни, лампочки, лампочки, 0, //лампочки, подсветка, тормозная жидкость, уровень охл,омыватель,дальний,
//12(c) - KOMBI_A1, unknown 12 8 00 0e(diferent) 31 40 61 06 0a 00, rest are constant
//14 - SAM_H_A3, body status lights (in xls), 14 2 e0 22 - avarial signal
//18 - ARMADA_A1, SRS, if passeger is in the car 18 6 00 00 4a(41 - in car/58 - not in car) 06 ff 00  
//20 - DBE_A1, LIGHT SENSOR AS WELL? temperature sensor about byte[1] >> 2 - digital number, byte[1] & 0x3 - 0.25,0.50,0.75 = (byte[1] >> 2) + (byte[1] & 0x3) * 0.25, 20 8 00 56 00 00 01 00 00 00
//22 - EZS_A11, BATTERY VOLTAGE! outside temp, 90(+4.5 outside), 8f(5.0 outside)
//23 - SAM_V_A2, TEMPERATURE OUTSIDE! unknown, 23 6 46(rear) 00 14 01 72(sometimes) 00   
//24 - TVL_A3, left power window position
//25 - TVR_A3, right power window position
//26 - UBF_A1, something new - 4 00 00 00 00
//30 - ZGW_A6, unknown, 0d ff ff ff ff ff ff ff(fe - rear, once)
//31 - ZGW_A5, same 31 8 01 00 20 0d 88 78 14 92,31 8 01 00 20 0d 10 f0 29 24 , //такси электрика дефект, передачи, distronic
//44 - OBF_A1, panel over cdc, 4 00 00 00 40(control)
//48 - KLA_A1, ac power, something else
//52 - AGW_A1, unknown, interesting, 52 2 00 3f(different) -
//56 - KOMBI_A2, unknown, - 56 5 12 2b 02 02 11  the same, 56 5 12 3a 11 02 11  -
//68 - TVL CANMSG msg5 = createCANPackage(68, 4, 0x00, 0b11111111, 0x00, 0x00); 0b11111111- close all, 0b11110011 - open all
//88 - EZS ODOMETER!, unknown, 88 7 90 23 a7 27 27 ce b6   
//112 - SAM_V_A3, unknown, 112 1 01  -
//140(8c) - SAM_B_A1 - 140 4 40/00 when engine off 00 00 00, //лампочки ошибки  
//154 - TVL - left rear window position, 154 2 80 01  
//156 - TVR - right rear window position, 156 2 80 01  
//158 - KOMBI_A6, ODOMETER,  same as 88???? 158 7 90 23 a7 27 27 ce b6 -
//178 - VIN CODE, unknown, always 3 messages the same, 178 8 01 57 44 42 32 31 31 30, 178 8 02 38 32 31 58 31 31 38, 178 8 03 37 38 33 ff ff ff ff  
//204 - ic screen
//241(f1) - KLA_A5, 241 1 3d (sensor), потребность в обогреве, температура наружного воздуха 
//266(10a) - GW_C_B5, 2 values, 266 7 ff ff 43 06 43 0a 83, сокрости задних колес
//376 1 80 - heater left back
//380 1 80/00 - heater right back 
//384 - EZS_A12 - unknown, 384 2 e0 00, rear -
//404(194) - KOMBI_A7 - 404 2 fe 01, яркость дисплея, возможности
//408(198) - RDK_A1 - 408 7 00 00 ff ff ff ff fe, система контроля давления в шинах
//416(1a0) - TP_WR_KOMBI3, always 3 messages the same, 416 8 04 13 01 00 e8 6e 00 ab, 416 8 03 13 09 06 e8 6e 00 ab, 416 8 03 13 04 06 e8 6e 00 ab, комуникация ZGW с приборкой
//424 2 04 00 - buttons on steering wheel
//434(1b2) - KG_A1, 434 3 00 00 ff, keyless go, положение/опознание ключа
//444(1bc) - 8 01 45 02 45 04 00 28 84(decrementing), //сервисные сообщения(буква,0,0,0,активация,км,км,км)
//459(1cb) - KOMBI_A9, 459 1 02, IPS
//513(201) - GW_C_B8, 513 1 3f -, мощность генератора и клема
//528 - status of heaters and fans on seats 4 00 00 00 00, 18 - 3, 10 - 2, 8 - 1,
//546 - GW_C_B3, AKPP, 546 8 73 87 19 36 00 80 87 00 -
//592 - KLA closes all windows, opens all windows to its privious position
//608(260) - SAM_B_A2, 2 00 00 - when enabling command, звуковой сигнал???
//624(270) - DBE, same 2 00 00 - датчик дождя, стеклоочистители
//688(2b0) - same 1 00 - парктроник активен или нет
//728(2d8) - KLA_A3, температура точки росы :)), 1 40 sensor - 4d(+5 outside)
//800(320) - GW_C_B9,  8 0b 2e 38 00 00 00 00 00, расход ul/250ms и обьем 
//802(322) - pre safe сидения, окна регулировки unknown, same 2 1e 00, same -
//818 - EZS_ANZ, unknown, same 1 00, same -
//992(3e0) - 992 8 03 13 01 06 e0 04 b8 d5, 992 8 04 13 09 00 e0 04 b8 d5, 992 8 03 13 04 e7 e0 04 b8 d5 - , комуникация приборки с WR, коректором фар
//1987 - brake pedal
//1992 8 00 00 00 00 00 00 00 20 - sends when power windows are triggered but nothing happens when manually sent
//1993
//1994
//1995



//TVL - 1032
//1256
//1992
//1896
//652
//68
//24
//232

//THL - 1033
//1257
//1993 
//1897
//154 - 
//376

//PTS - 1043
//1267
//688 - Ersatzlicht park. vorne bei. seite aktiv
//526
//2003
//1907


//1985 6 00 00 00 00 00 00

//,2,3,4,5

//2 - 8 bytes, some pattern 

//14?
//52?
//88? - 
//158? - 7 bytes
//178? - seems to have 3 packages, but always the same - not interested
//241? - 1 byte, about 12 values
//266? - 7 bytes, always diferent
//546? - 8 bytes, always diferent
//724? - 4 values
//728? - 5 values
//800? - 8 bytes, 3 bytes always different, rest zeros
//1024 - 1053 - strange...

//TODO:
//record log when somebody go in and out of the car and pid 4 for open doors
//check pid 0, first byte sometimes is different
//check pid 5, last 3 bytes are different
//check pid 6, high beam

//1024 - EZS
//1025 - SAM_B
//1026 - SAM_V
//1027 - SAM_H
//1028 - ZGW
//1029 - OBF
//
//1032 - TVL
//
//1039 - LRK
//1040 - AAG
//1044 - KOMBI
//1045 - MRM
//

#define AGW_SIMULATION
//#define PRINT_IC_COMMUNICATION
//#define CONSUMPTION_MENU
#define DIAG_SIMULATION

#include <SPI.h>
#include <MCP2515.h>
#include "CAN_Stuff.h"
#include "AI.h"
#include "IC.h"
#include "KWP2000.h"
#include "IC_ENV.h"

extern KWP kwp;
extern IC_ENV ic;
Car car = Car();
CANMSG msg;

MCP2515 canB = MCP2515(10, 0x02, 0x9a, 0x07);
//MCP2515 canB = MCP2515(10, 0x00, 0x90, 0x82);

void setup()
{
  Serial.begin(115200);

  //Reset
  while (!canB.init()){
    Serial.println("init fail");
  }

  Serial.println("started");


}
//int len = 0;
//unsigned long filtered[0] = {};

int len = 73;
unsigned long filtered[73] = 
{0,2,3,4,5,6,9,10,12,18,20,22,23,24,25, 26, 30,31,44,48,52,56,88, 464, 420,
112,140,144,154,156,158,178,241,266,384,404,408,416,434,444,459,513,528,546,624,688,724,728,800,802,818,992,
1024,1025,1026,1027,1028,1029,1031,1032,1033,1034,1035,1041,1042,1043,1044,1045,1046,1048,1051,1052,1053};


int unfilteredPid = -1;
String inputString;
bool commandReady = false;
uint8_t t = 0;
void command_loop()
{
  bool stopp = false;
  if (Serial.available() > 0 && !stopp){
    char val = Serial.read();
    if (val != '\r') {
      if (val == '\n' || val == ';') {
        commandReady = true;
        stopp = true;
      } else {
        inputString += val;
      }
    }
  }
  if (commandReady) {
    Serial.println(inputString);
    String command = getValue(inputString, 0);
    if (command == "r") {
      int v1 = getValue(inputString, 1).toInt();
      int v2 = getValue(inputString, 2).toInt();
      uint8_t v3 = fromHexString(getValue(inputString, 3));
      uint8_t v4 = fromHexString(getValue(inputString, 4));
      uint8_t v5 = fromHexString(getValue(inputString, 5));
      uint8_t v6 = fromHexString(getValue(inputString, 6));
      uint8_t v7 = fromHexString(getValue(inputString, 7));
      uint8_t v8 = fromHexString(getValue(inputString, 8));
      uint8_t v9 = fromHexString(getValue(inputString, 9));
      uint8_t v10 = fromHexString(getValue(inputString, 10));
      if (v2 > 0 && v2 <= 8) {
        CANMSG msg = createCANPackage(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
        canB.transmitCANMessage(msg, 100);
        printPackage(msg);
      }
    } else if (command == "b") {
      int v1 = getValue(inputString, 1).toInt();
      int v2 = getValue(inputString, 2).toInt();
      uint8_t v3 = fromBinaryString(getValue(inputString, 3));
      uint8_t v4 = fromBinaryString(getValue(inputString, 4));
      uint8_t v5 = fromBinaryString(getValue(inputString, 5));
      uint8_t v6 = fromBinaryString(getValue(inputString, 6));
      uint8_t v7 = fromBinaryString(getValue(inputString, 7));
      uint8_t v8 = fromBinaryString(getValue(inputString, 8));
      uint8_t v9 = fromBinaryString(getValue(inputString, 9));
      uint8_t v10 = fromBinaryString(getValue(inputString, 10));
      CANMSG msg = createCANPackage(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
      canB.transmitCANMessage(msg, 100);
       printPackage(msg);
    } else if (command == "o") {
      closeWindows(false);
    } else if (command == "c") {
      closeWindows(true);
    } else if (command == "+") {
      unfilteredPid++;
      Serial.print("UNFILTERED PID: ");
      Serial.println(unfilteredPid);
    } else if (command == "-") {
      unfilteredPid--;
      Serial.print("UNFILTERED PID: ");
      Serial.println(unfilteredPid);
    } else if (command == "m") {
      String val = getValue(inputString, 1);
      uint8_t v2 = fromHexString(getValue(inputString, 2));
      uint8_t v3 = fromHexString(getValue(inputString, 3));
      char charBuf[50];
      val.toCharArray(charBuf, 50);
      ic_music_center_line_test(charBuf, v2, v3);
      
    } else if (command == "diag_start") {
      kwp.debug_output = true;
      uint8_t v1 = fromHexString(getValue(inputString, 1));
      diag_start();
      diag_read_ecu_id(DIAG_ID_KOMBO_KWP_REQ_ID);
      //canB.sendMsg(0x1c, 8, 0x02, 0x10, 0x92, 0xff, 0xff, 0xff, 0xff, 0xff);
      //canB.sendMsg(KOMBO_KWP_REQ_ID,8, 0x02, 0x1a, 0x86, 0xff, 0xff, 0xff, 0xff, 0xff);
      //diag_get_value(KOMBO_KWP_REQ_ID, v1);
      //diag_read_ecu_id(KOMBO_KWP_REQ_ID);
    } else if (command == "debug") {
      uint8_t v1 = fromHexString(getValue(inputString, 1));
      if (v1 == 0) {
        CANMSG msg = createCANPackage(DIAG_ID_KOMBO_KWP_RES_ID, 8, 0x03, 0x7f, 0x1a, 0x78, 0xff, 0xff, 0xff, 0xff); 
        diag_receive_response(msg);
      } else if (v1 == 1) {
        CANMSG msg = createCANPackage(DIAG_ID_KOMBO_KWP_RES_ID, 8, 0x10, 0x12+9, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6); 
        diag_receive_response(msg);
        CANMSG msg1 = createCANPackage(DIAG_ID_KOMBO_KWP_RES_ID, 8, 0x21, 0x7, 0x8, 0x9, 0x10, 0x11, 0x12, 0x13); 
        diag_receive_response(msg1);
        CANMSG msg2 = createCANPackage(DIAG_ID_KOMBO_KWP_RES_ID, 8, 0x22, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x20); 
        diag_receive_response(msg2);
        CANMSG msg3 = createCANPackage(DIAG_ID_KOMBO_KWP_RES_ID, 8, 0x23, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27); 
        diag_receive_response(msg3);
      }
    } else if (command == "diag_stop") {
      diag_stop();
    } else if (command == "w") {
      ic_env_w();
    } else if (command == "a") {
      ic_env_a();
    } else if (command == "s") {
      ic_env_s();
    } else if (command == "d") {
      ic_env_d();
    } else if (command == "ic_all") {
      ic.all_output = !ic.all_output;
    } else if (command == "diag_v") {
      int8_t v1 = fromHexString(getValue(inputString, 1));
      String val = getValue(inputString, 2);
      char charBuf[25];
      val.toCharArray(charBuf, 25);
      //ic_music_top_line(charBuf);
      //31 03 01 - draw pattern
      //31 03 02 10 10 01 ff - draws letter
      //31 03 03 - draw text
      //31 03 08 - clear

      //31 03 05 10 10 ff fa - draw dot
      //31 03 06 X1 Y1 X2 Y2 - draw line

      
      //31 03 01    FF FF FF FF    FF FF FF FF - 11
      //31 03 03    00 00 
      //31 0C 00 00 00
      //canB.sendMsg(1460, 8, 0x10, 0x0b, 0x31, 0x03, 0x01, 0xF0, 0xFF, 0xFF);
      //canB.sendMsg(1460, 8, 0x21, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);

      //uint8_t data[11] = {0x31, 0x03, 0x01, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF};
      //diag_send(1460, data, 11, false);

      uint8_t data[25] = {0x31, 0x03, 0x03, v1, 0x00};
      for (int i = 0; i < 20; i++) data[i+5] = charBuf[i];
      diag_send(1460, data, 25, false);
      
    } else if (command == "diag_read_value") {
      //r 1460 8 4 31 03 08 02 - clear red
      //r 1460 8 2 21 60 
      //r 1460 8 2 1a 86
      //r 1460 8 6 3B 04 00 00 00 00
      //r 1460 8 5 31 0c 01 00 00 - set trip odo
      //r 1460 8 5 3b 01 02 30 00 - time
      //r 1460 8 3 31 0a 01 - settings factory
      //r 1460 8 4 31 17 00 ff - set segment control
      
      uint8_t v1 = fromHexString(getValue(inputString, 1));
      diag_get_value(DIAG_ID_KOMBO_KWP_REQ_ID, v1);
    } else if (command == "audio_start") {
      //0x0416 - 1046
      ic.inited = false;

      ic.data24_len = 19;
      uint8_t data[19+1] = {0x05, 0x24, 0x02, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x12, 0x09, 0x01, 0x0a, 0x02, 0x00, 0x46, 0x4d, 0x31, 0x00};
      for (int i = 0; i < 19; i++) ic.data24[i] = data[i];

      ic.data26_len = 18;
      uint8_t data2[18+1] = {0x05, 0x26, 0x01, 0x00, 0x01, 0x0c, 0x10, 0x41, 0x55, 0x44, 0x49, 0x4f, 0x20, 0x6f, 0x66, 0x66, 0x00, 0x00};
      for (int i = 0; i < 18; i++) ic.data26[i] = data2[i];
      
      
      printPackage(canB.sendMsg(420, 8, 0x05, 0x05, 0x20, 0x02, 0x11, 0xc1, 0xff, 0xff));

        //canB.sendMsg(420, 8, 0x03, 0x05, 0x21, 0x06, 0xff, 0xff, 0xff, 0xff);
      
        //canB.sendMsg(420, 8, 0x10, 0x0f, 0x05, 0x24, 0x05, 0x40, 0x01, 0x01);
        //canB.sendMsg(420, 8, 0x21, 0x00, 0x00, 0x00, 0x11, 0x01, 0x00, 0x00);
        //canB.sendMsg(420, 8, 0x22, 0x00, 0x22, 0x66, 0x00, 0x00, 0x52, 0x00);
      
        //canB.sendMsg(420, 8, 0x03, 0x05, 0x25, 0x06, 0x40, 0x01, 0x01, 0x00);
      
        //canB.sendMsg(420, 8, 0x10, 0x13, 0x05, 0x26, 0x01, 0x00, 0x01, 0x0c);
        //canB.sendMsg(420, 8, 0x21, 0x10, 0x50, 0x68, 0x6f, 0x6e, 0x65, 0x20);
        //canB.sendMsg(420, 8, 0x22, 0x6f, 0x66, 0x66, 0x00, 0x00, 0xc8, 0x00);
    } else if (command == "top") {
      String val = getValue(inputString, 1);
      char charBuf[50];
      val.toCharArray(charBuf, 50);
      ic_music_top_line(charBuf);
      ic.stepp = 6;
    } else if (command == "ar") {
      uint8_t v1 = fromHexString(getValue(inputString, 1));
      uint8_t v2 = fromHexString(getValue(inputString, 2));
      ic_music_show_arrows(v1, v2);
      t++;
    } else if (command == "test") {
      canB.sendMsg(420, 8, 0x10, 0x08, 0x03, 0x29, 0x00, 0x46, 0x4d, 0x32  );
      canB.sendMsg(420, 8, 0x21, 0x00, 0xf9, 0x55, 0x58, 0x20, 0x46, 0x4d  );
    } else if (command == "test2") {
      //whole magic is here!
      //3 24 02 00 01 01 00 00 00 12 09 1 0a 02 00 46 4d 31 00 3d
      
    } else if (command == "test3") {
      
      canB.sendMsg(420, 8, 0x10, 0x13, 0x03, 0x26, 0x01, 0x00, 0x01, 0x0c);
      canB.sendMsg(420, 8, 0x21, 0x10, 0x31, 0x30, 0x30, 0x2e, 0x31, 0x20);
      canB.sendMsg(420, 8, 0x22, 0x4d, 0x48, 0x7a, 0x00, 0x00, 0x00, 0x3d);
    } else if (command == "test4") {
      //XX00 0000 - turns off audio (or crash it)
      //00X0 0000 - leaves only below and main text(after reopen)
      //000X 0000 - leaves only main text(after reopen)
      //0000 XXXX - nothin?

      
      
      
      uint8_t hash = (5 - 3) + 0x3b + 0x12 + 0x0a + 0x09 + 0x02 - 0x10 - 1 + 1;
      uint8_t val = 0x12;
      uint8_t upper = 0x09;
      uint8_t under = 0x0a;
      uint8_t val2 = fromHexString(getValue(inputString, 1));
      uint8_t val3 = fromHexString(getValue(inputString, 2));
      uint8_t val4 = fromHexString(getValue(inputString, 3));
      Serial.println(val2);
      hash -= val;
      hash -= upper;
      hash -= under;
      hash -= val2;
      hash -= val3;
      hash -= val4;
      printPackage(canB.sendMsg(420, 8, 0x10, 0x14, 3, 0x24, val2, val3, val4, 0x01));
      printPackage(canB.sendMsg(420, 8, 0x21, 0x00, 0x01, 0x00, val, upper, 0x01, under));
      printPackage(canB.sendMsg(420, 8, 0x22, 0x02, 0x10, 0x46, 0x4d, 0x31, 0x00, hash));
    } else if (command == "t26") {

     
      ic.data26_len = 17;
      uint8_t data[len+1] =  {0x05, 0x26, 0x01, 0x00, 0x02, 0x08, 0x00, 'i', 0x55, 0x44, 0x49, 0x4f, 0x00, 0x08, 0x00, 0x41, 0x55, 0x44, 0x49, 0x4f, 0x00};
      for (int i = 0; i < 25; i++) ic.data26[i] = data[i];
      diag_send_kwp(ic.data26, ic.data26_len, true);

      //printPackage(canB.sendMsg(420, 8, 0x03, 0x05, 0x04, 0x06, 0x00, 0x07, 0x38, 0x38));

      //printPackage(canB.sendMsg(420, 8, 0x03, 0x05, 0x25, 0x06, 0x00, 0x07, 0x38, 0x38));  
      //{0x05, 0x26, 0x01, 0x00, 0x04, 0x0e, 0x02, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x20, 0x64, 0x61, 0x74, 0x61, 0x07, 0x00, 0x49, 0x74, 0x65, 0x6d, 0x73, 0x0d,
      //0x00, 0x41, 0x64, 0x64, 0x69, 0x74, 0x2e, 0x20, 0x57, 0x6f, 0x72, 0x6b, 0x0e, 0x00, 0x43, 0x6f, 0x6e, 0x66, 0x69, 0x72, 0x6d, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x00, 0xb9};
      
      //printPackage(canB.sendMsg(420, 8, 0x10, 0x37, 0x05, 0x26, 0x01, 0x00, 0x04, 0x0e));  
      //printPackage(canB.sendMsg(420, 8, 0x21, 0x02, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63));  
      //printPackage(canB.sendMsg(420, 8, 0x22, 0x65, 0x20, 0x64, 0x61, 0x74, 0x61, 0x07));  
      //printPackage(canB.sendMsg(420, 8, 0x23, 0x00, 0x49, 0x74, 0x65, 0x6d, 0x73, 0x0d));  
      //printPackage(canB.sendMsg(420, 8, 0x24, 0x00, 0x41, 0x64, 0x64, 0x69, 0x74, 0x2e));  
      //printPackage(canB.sendMsg(420, 8, 0x25, 0x20, 0x57, 0x6f, 0x72, 0x6b, 0x0e, 0x00));  
      //printPackage(canB.sendMsg(420, 8, 0x26, 0x43, 0x6f, 0x6e, 0x66, 0x69, 0x72, 0x6d));  
      //printPackage(canB.sendMsg(420, 8, 0x27, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x00, 0xb9));  

      //printPackage(canB.sendMsg(420, 8, 0x04, 0x05, 0x01, 0x00, 0xe8, 0x6e, 0x00, 0xab));  
      //printPackage(canB.sendMsg(420, 8, 0x03, 0x05, 0x09, 0x06, 0xe8, 0x6e, 0x00, 0xab));  

      
    } else if (command == "tt1") {
      printPackage(canB.sendMsg(420, 8, 0x10, 0x19, 0x05, 0x24, 0x01, 0x90, 0x11, 0x04));  
      printPackage(canB.sendMsg(420, 8, 0x21, 0x00, 0x01, 0x00, 0x10, 0x50, 0x53, 0x65));  //Se 
      printPackage(canB.sendMsg(420, 8, 0x22, 0x72, 0x76, 0x69, 0x63, 0x65, 0x20, 0x6d));  //rvise m
      printPackage(canB.sendMsg(420, 8, 0x23, 0x65, 0x6e, 0x75, 0x00, 0x15, 0x38, 0x38));  //enu
    } else if (command == "tt2") {
      printPackage(canB.sendMsg(420, 8, 0x10, 0x19, 0x05, 0x24, 0x01, 0x82, 0x11, 0x03));
      printPackage(canB.sendMsg(420, 8, 0x21, 0x00, 0x01, 0x00, 0x10, 0x50, 0x53, 0x65));
      printPackage(canB.sendMsg(420, 8, 0x22, 0x72, 0x76, 0x69, 0x63, 0x65, 0x20, 0x64));
      printPackage(canB.sendMsg(420, 8, 0x23, 0x61, 0x74, 0x61, 0x00, 0x3f, 0x73, 0x0d));
    } else if (command == "t24") {
      uint8_t val2 = fromHexString(getValue(inputString, 1));
      uint8_t val3 = fromHexString(getValue(inputString, 2));
      uint8_t val4 = fromHexString(getValue(inputString, 3));
      uint8_t val5 = fromHexString(getValue(inputString, 4));
      uint8_t val6 = fromHexString(getValue(inputString, 5));
      uint8_t val7 = fromHexString(getValue(inputString, 6));
      ic_package24(val2, val3, val4, val5, val6, val7);
    } else if (command == "a_start") {
      ic.data24_len = 24;
      uint8_t data[len+1] = {0x05, 0x24, 0x02, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x10, 0x50, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x20, 0x64, 0x61, 0x74, 0x61, 0x00};
      for (int i = 0; i < 25; i++) ic.data24[i] = data[i];
      diag_send_kwp(ic.data24, ic.data24_len, true);
    } else if (command == "reinit") {
      while (!canB.init()){
        Serial.println("init fail");
      }
      Serial.println("asdf");
    } else if (command == "tt26") {
      String val = getValue(inputString, 1);
      String val2 = getValue(inputString, 2);
      String val3 = getValue(inputString, 3);
      String val4 = getValue(inputString, 4);
      char charBuf[50];
      val.toCharArray(charBuf, 50);
      char charBuf2[50];
      val2.toCharArray(charBuf2, 50);
      char charBuf3[50];
      val3.toCharArray(charBuf3, 50);
      char charBuf4[50];
      val4.toCharArray(charBuf4, 50);
      ic_package26(charBuf, charBuf2, charBuf3, charBuf4);
    }
    //6 00 00 02 a0 51 aa
    inputString = "";
    commandReady = false;
  }
}

bool sentDiagSession = false;
void loop()
{
  //Receives commands from serial
  command_loop();

#ifdef DIAG_SIMULATION
  diag_loop();
#endif
  
#ifdef AGW_SIMULATION
  //sends EZS, Battery Voltage, Odometer, AGW (for external IC)
  ic_env_loop();
#endif


#ifdef CONSUMPTION_MENU
  //updates ic views 
  ic_update_view();
#endif

  //receive next message
  if (!canB.receiveCANMessage(&msg, 100)) return;

  //prints all packages (for debugging)
  if (ic.all_output) printPackage(msg);

#ifdef DIAG_SIMULATION
  kwp.response_received = false;
  
  if (diag_receive_response(msg)) {
      if (kwp.response_received == true) {
        Serial.print("DIAG: ");
         for (int i = 0; i < kwp.response_len; i++) {
            Serial.print(kwp.response[i], HEX);
            Serial.print(" ");
         }
         Serial.println();
      }
  }
#endif

#ifdef PRINT_IC_COMMUNICATION
  //if we receive message from IC (KOMBO_KWP_REQ_ID or KOMBO_KWP_RES_ID)
  //check if it needs to be decapsulated
  if ((msg.adrsValue == ID_AGW_TO_KOMBO || msg.adrsValue == ID_KOMBO_TO_AGW) ||
      ((msg.adrsValue == 0x1A0 || msg.adrsValue == 0x3E0))) {
    if (msg.data[0] == 0x10) {
      if (msg.data[1] == 0x7f && msg.data[3] == 0x78){
        return;
      }
    }
    kwp.response_id = msg.adrsValue; 
    //printPackage(msg);
    kwp.response_received = false;
    if (diag_receive_response(msg, false)) {
      if (kwp.response_received == true) {

        Serial.print(kwp.response[0], HEX);

        if (msg.adrsValue == ID_AGW_TO_KOMBO || msg.adrsValue == 0x1A0) {
          Serial.print(" >>> ");
        } else {
          Serial.print(" <<< ");
        }
        
        for (int i = 1; i < kwp.response_len; i++) {
          Serial.print(kwp.response[i], HEX);
          
          Serial.print("(");
          Serial.print((char)kwp.response[i]);
          Serial.print(") ");
        }
        Serial.println();
        
        //For now do nothing as it's already printing package in diag_receive_response
      }
      //No need to continue as this package was analized by diag_receive_response
      //return;
    }
  }
#endif

#ifdef CONSUMPTION_MENU
  //analize packages 800(petrol consumption), 0x58(odometer distance), and 424(steering wheel buttons)
  ic_receive_consuption(msg);
#endif

#ifdef AGW_SIMULATION
  //communication of AGW with IC
  if (msg.adrsValue == 464) {
    //ic_env_receive(msg);
  }
#endif

  /*
  if (canB.receiveCANMessage(&msg, 100)) {
    if (msg.adrsValue == 0x1A0){
      printPackage(msg);
    } else if (msg.adrsValue == 0x1d0) {
      printPackage(msg);
    }
    printPackage(msg);
    
  } else {
    //Serial.println("fail");
  }
  */
  //return;

  //
  
  /*
  if (canB.receiveCANMessage(&msg, 100)) {
    if (ic.all_output) printPackage(msg);

    if (diag_receive_response(msg)) {
      if (kwp.response_received == true) {
        kwp.response_received = false;
      }
    }
  }
  return;
  */
  //return;


  
  

  

  //if (diag_receive_response(msg)) {
  //  if (kwp.response_received == true) {
  //    diag_stop();
  //  }
    //return;
  //}
 

  if (isFiltered(msg)){
    return;
  }
  printPackage(msg);
}

/*
  doWork(msg);

  //printPackage(msg);
  //return;
  
  if (msg.adrsValue == unfilteredPid){
    printPackage(msg);
  }
  
  
 // if ( msg.adrsValue == 420){
 //   printPackage(msg);
 // }

  if (isFiltered(msg)){
    //Serial.print("_");
    return;
  }
  //analizePackage(msg);
  printPackage(msg);
  */


/*
  if (Serial.available() > 0){
    int incomingByte = Serial.read();
    if (incomingByte == 'i'){
      Serial.print("temp: ");
      Serial.print(car.temp);
      Serial.print(", engine: ");
      Serial.print(car.engineOn);
      Serial.print(", voltage: ");
      Serial.print(car.voltage);
      Serial.print(", outside: ");
      Serial.println(car.outsideTemp);
    } else if (incomingByte == 'c'){
      //Serial.println("close");
      //CANMSG msg = closeWindowPackage(true);
      //printPackage(msg);
      //MCP2515::transmitCANMessage(msg, 100);
    } else if (incomingByte == 'o'){
      //Serial.println("open");
      //CANMSG msg = closeWindowPackage(false);
      //MCP2515::transmitCANMessage(msg, 100);
    } else if (incomingByte == 'l') {
      //Serial.println("clear");
      //add_list_len = 0;
    } else if (incomingByte == 't') {
      Serial.println("test sending");
      CANMSG msg = createCANPackage(592, 1, 0xfe);
      MCP2515::transmitCANMessage(msg, 100);
      printPackage(msg);
      delay(100);
      msg = createCANPackage(592, 1, 0x00);
      MCP2515::transmitCANMessage(msg, 100);
      printPackage(msg);
    } else if (incomingByte == 'r') {
      Serial.println("test sending");
      CANMSG msg = createCANPackage(592, 1, 0xfa);
      MCP2515::transmitCANMessage(msg, 100);
      printPackage(msg);
      delay(100);
      msg = createCANPackage(592, 1, 0x00);
      MCP2515::transmitCANMessage(msg, 100);
      printPackage(msg);
    } else if (incomingByte == '+') {
      unfilteredPid++;
      Serial.print("UNFILTERED PID: ");
      Serial.println(unfilteredPid);
    } else if (incomingByte == '-') {
      unfilteredPid--;
      Serial.print("UNFILTERED PID: ");
      Serial.println(unfilteredPid);
    } else if (incomingByte == '=') {
      unfilteredPid+=10;
      Serial.print("UNFILTERED PID: ");
      Serial.println(unfilteredPid);
    } else if (incomingByte == '_') {
      unfilteredPid-=10;
      Serial.print("UNFILTERED PID: ");
      Serial.println(unfilteredPid);
    } else if (incomingByte == 'm') {
      CANMSG msg = createCANPackage(44, 4, 0x00, 0x00, 0x08, 0x40);
      MCP2515::transmitCANMessage(msg, 100);
      printPackage(msg);
    } else if (incomingByte == 'k') {
      CANMSG msg = createCANPackage(44, 4, 0x00, 0x00, 0x80, 0x40);
      MCP2515::transmitCANMessage(msg, 100);
      printPackage(msg);
    } else if (incomingByte == '0') {
      //68 4 00 00 04 00
      CANMSG msg = createCANPackage(68, 4, 0x00, 0x00, 0x00, 0x20);
      MCP2515::transmitCANMessage(msg, 100);
      printPackage(msg);
    } else if (incomingByte == 'q') {
      
      ic_music_center_line("12345678901234");
      ic_music_top_line("12345678");

    } else if (incomingByte == 's') {

    }
  }
  */





