#include <MCP2515.h>
#include "AI.h"
#include "CAN_Stuff.h"
#include "IC.h"
#include "KWP2000.h"
#include "IC_ENV.h"

extern MCP2515 canB;

IC_ENV ic;

bool sentAudioStart = 0;

void ic_env_loop() {
  if (millis() - ic.last_every_second > 1000) {
    ic.last_every_second = millis();
    canB.sendMsg(0x0, 8, 0x04, 0, 0, 0, 0, 0, 0, 0); //EZS
    canB.sendMsg(0x16, 1, 0x7f); //battery voltage
    canB.sendMsg(0x58, 7, 0x78, 0x74, 0xb2, 0x92, 0x27, 0xd3, 0x50 );
    canB.sendMsg(1046, 8, 0xfe, 0x16, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00); 
  }
}

#define IC_REQ_INIT 0x04
#define IC_GET_LINES 0x25
#define IC_RES_SUCCESS 0x06

#define IC_SCREEN_MUSIC 0x03
#define IC_SCREEN_PHONE 0x05


//я - 20
//o - 20 - 06
//o - 21
//я - 21 - 06
//я - 24
//o - 24 - 06
//o - 25
//я - 25 - 06
//я - 26
//о - 26 - 06



void tel_receive(CANMSG msg) {
  
}


void ic_env_receive(CANMSG msg) {
  if (msg.data[0] == 0x30 && msg.data[2] == 0x28) {
    
  } else {
    printPackage(msg);
  }
  
  if (msg.data[2] == 0x21) {
    canB.sendMsg(420, 8, 0x03, msg.data[1], msg.data[2], IC_RES_SUCCESS);
    Serial.println("21 - ok");
    if (ic.data24_len > 0) {
      Serial.println(ic.data24_len);
      diag_send_kwp(ic.data24, ic.data24_len, true);
    }
  } else if (msg.data[2] == IC_GET_LINES) {
    canB.sendMsg(420, 8, 0x03, msg.data[1], msg.data[2], IC_RES_SUCCESS);
    Serial.println("25 - ok");
    if (ic.data26_len > 0) {
      ic.data26[2] = msg.data[3];
      diag_send_kwp(ic.data26, ic.data26_len, true); 
    }
  } else if (msg.data[2] == 9) {
    canB.sendMsg(420, 8, 0x03, msg.data[1], msg.data[2], IC_RES_SUCCESS);
    Serial.println("9 - ok");
  } else if (msg.data[2] == 0x22) {
    canB.sendMsg(420, 8, 0x03, msg.data[1], msg.data[2], IC_RES_SUCCESS);
    Serial.println("22 - ok");
  } else if (msg.data[2] == 0x27) {
    canB.sendMsg(420, 8, 0x03, msg.data[1], msg.data[2], IC_RES_SUCCESS);
    Serial.println("27 - ok");
  }

  return;
  if (ic.inited) return;
  
  if (msg.data[2] == IC_REQ_INIT) {
  
    Serial.println("1");
    printPackage(canB.sendMsg(420, 8, 0x03, 0x05, msg.data[2], IC_RES_SUCCESS));
    uint8_t hash = (5 - msg.data[1]) + 0xc1;
    printPackage(canB.sendMsg(420, 8, 0x05, msg.data[1], 0x20, 0x02, 0x11, hash, 0xff, 0xff));

  } else if (msg.data[2] == 0x21) {
    //Serial.println("3");
    //uint8_t hash = (5 - msg.data[1]) + 0x3b;
    //printPackage(canB.sendMsg(420, 8, 0x03, msg.data[1], msg.data[2], IC_RES_SUCCESS));
    //printPackage(canB.sendMsg(420, 8, 0x10, 0x0f, msg.data[1], 0x24, 0x05, 0x40, 0x01, 0x01));   //24
    //printPackage(canB.sendMsg(420, 8, 0x21, 0x00, 0x00, 0x00, 0x11, 0x01, 0x00, 0x00));
    //printPackage(canB.sendMsg(420, 8, 0x22, 0x00, hash));

    //03 24 05 40 01 01 00 00 00 11 01 00 00 00 hash
    //03 24 02 00 01 01 00 00 00 12 09 01 0a 02 00 46 4d 31 00 hash
    //printPackage(canB.sendMsg(420, 8, 0x10, 0x19, 0x05, 0x24, 0x01, 0x90, 0x11, 0x04));
    //printPackage(canB.sendMsg(420, 8, 0x21, 0x00, 0x01, 0x00, 0x10, 0x50, 0x53, 0x65)); 
    //printPackage(canB.sendMsg(420, 8, 0x22, 0x72, 0x76, 0x69, 0x63, 0x65, 0x20, 0x6d)); 
    //printPackage(canB.sendMsg(420, 8, 0x23, 0x65, 0x6e, 0x75, 0x00, 0x15, 0x73, 0x0d));

    

    

    //printPackage(canB.sendMsg(420, 8, 0x10, 0x14, msg.data[1], 0x24, 0x02, 0x00, 0x01, 0x01));
    //printPackage(canB.sendMsg(420, 8, 0x21, 0x00, 0x00, 0x00, 0x12, 0x09, 0x01, 0x0a));
    //printPackage(canB.sendMsg(420, 8, 0x22, 0x02, 0x00, 0x46, 0x4d, 0x31, 0x00, hash));
  } else if (msg.data[2] == 0x25) {

      uint8_t hash = (5 - msg.data[1]) + 0x50;
      
      printPackage(canB.sendMsg(420, 8, 0x10, 0x13, msg.data[1], 0x26, 0x01, 0x00, 0x01, 0x0c));   //26
      printPackage(canB.sendMsg(420, 8, 0x21, 0x10, 0x41, 0x55, 0x44, 0x49, 0x4f, 0x20));
      printPackage(canB.sendMsg(420, 8, 0x22, 0x6f, 0x66, 0x66, 0x00, 0x00, hash, 0x00));

      /*
  
    
    Serial.println("4");
    if (msg.data[1] == 0x05) {
      printPackage(canB.sendMsg(420, 8, 0x10, 0x37, 0x05, 0x26, 0x01, 0x00, 0x04, 0x0e));  
      printPackage(canB.sendMsg(420, 8, 0x21, 0x02, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63));  
      printPackage(canB.sendMsg(420, 8, 0x22, 0x65, 0x20, 0x64, 0x61, 0x74, 0x61, 0x07));  
      printPackage(canB.sendMsg(420, 8, 0x23, 0x00, 0x49, 0x74, 0x65, 0x6d, 0x73, 0x0d));  
      printPackage(canB.sendMsg(420, 8, 0x24, 0x00, 0x41, 0x64, 0x64, 0x69, 0x74, 0x2e));  
      printPackage(canB.sendMsg(420, 8, 0x25, 0x20, 0x57, 0x6f, 0x72, 0x6b, 0x0e, 0x00));  
      printPackage(canB.sendMsg(420, 8, 0x26, 0x43, 0x6f, 0x6e, 0x66, 0x69, 0x72, 0x6d));  
      printPackage(canB.sendMsg(420, 8, 0x27, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x00, 0xb9)); 
    } else {
      uint8_t hash = (5 - msg.data[1]) + 0x50;
      
      
      Serial.println("CHECK");
      ic.inited = true;
      if (msg.data[1] != 0x05) {
        printPackage(canB.sendMsg(420, 8, 0x05, 0x05, 0x20, 0x02, 0x11, 0xc1, 0xff, 0xff));         //start initing of phone screen
      }
    }
*/
  //} else if (msg.data[2] == 0x27) {
  //  ic_music_center_line_test("test27", 0, 0);
  //SUCCESS REPLY
  } else if (msg.data[0] == 0x03 && msg.data[3] == 0x06) {
    if (msg.data[2] == 0x20) {
      Serial.println("2");
    }
  //ERROR REPLY
  } else if (msg.data[0] == 0x03 && msg.data[3] != 0x06) {
    Serial.print("Error: ");
    Serial.println(msg.data[3], HEX);
  }


      
  
  //

  /*
  if (msg.data[0] == 0x03 && msg.data[2] == 0x04) {
    Serial.println("1");
    printPackage(canB.sendMsg(420, 8, 0x03, msg.data[1], 0x04, 0x06));
  } else if (msg.data[0] == 0x05 && msg.data[2] == 0x21) {
    Serial.println("2");
    ic.stepp = 1;
    printPackage(canB.sendMsg(420, 8, 0x03, msg.data[1], 0x21, 0x06));
    printPackage(canB.sendMsg(420, 8, 0x10, 0x0f, 0x03, 0x24, 0x05, 0x40, 0x01, 0x01));
  } else if (msg.data[0] == 0x30 && msg.data[2] == 0x28) {
    if (ic.stepp == 1) {
      printPackage(canB.sendMsg(420, 8, 0x21, 0x00, 0x00, 0x00, 0x11, 0x01, 0x00, 0x00));
      printPackage(canB.sendMsg(420, 8, 0x22, 0x00, 0x24));
    } else if (ic.stepp == 2) {
      printPackage(canB.sendMsg(420, 8, 0x21, 0x10, 0x00, 0x00, 0x9d, 0x01, 0x00, 0x00));
    } else if (ic.stepp == 3) {
      ic.stepp = 5;
      printPackage(canB.sendMsg(420, 8, 0x21, 0x00, 0x00, 0x00, 0x11, 0x01, 0x00, 0x00 ));
      printPackage(canB.sendMsg(420, 8, 0x22, 0x00, 0x24));
    } else if (ic.stepp == 5) {
      printPackage(canB.sendMsg(420, 8, 0x21, 0x10, 0x41, 0x55, 0x44, 0x49, 0x4f, 0x20));
      printPackage(canB.sendMsg(420, 8, 0x22, 0x6f, 0x66, 0x66, 0x00, 0x00, 0x52, 0x00));
    }
  } else if (msg.data[0] == 0x06 && msg.data[2] == 0x25) {
    if (ic.stepp = 5) {
      Serial.println("5");
      printPackage(canB.sendMsg(420, 8, 0x03, 0x03, 0x25, 0x06));
      printPackage(canB.sendMsg(420, 8, 0x10, 0x13, 0x03, 0x26, 0x01, 0x00, 0x01, 0x0c));  
    } else {
      Serial.println("3");
      ic.stepp = 2;
      printPackage(canB.sendMsg(420, 8, 0x03, msg.data[1], 0x25, 0x06)); 
      printPackage(canB.sendMsg(420, 8, 0x10, 0x0a, 0x03, 0x26, 0x01, 0x00, 0x01, 0x03)); 
    } 
  //13433 1D0 8 03 03 26 06 00 01 cb 00 
  } else if (msg.data[0] == 0x03 && msg.data[2] == 0x26) {
    if (msg.data[3] != 0x06) {
      Serial.print("Unknown response: ");
      Serial.println(msg.data[3], HEX);
    }
    if (ic.stepp == 5) {
      Serial.println("end");
      return;
    }
    Serial.println("4");
    ic.stepp = 3;
    printPackage(canB.sendMsg(420, 8, 0x10, 0x0f, 0x03, 0x24, 0x05, 0x40, 0x01, 0x01));
  }
  */
}

void ic_env_w() {
  canB.sendMsg(424, 2, 0x02, 0x00);
}

void ic_env_a() {
  canB.sendMsg(424, 2, 0x04, 0x00);
}

void ic_env_s() {
  canB.sendMsg(424, 2, 0x08, 0x00);
}

void ic_env_d() {
  
}

