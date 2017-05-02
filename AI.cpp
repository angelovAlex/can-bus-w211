#include <MCP2515.h>
#include "AI.h"
#include "CAN_Stuff.h"
#include "IC.h"

extern Car car;
extern MCP2515 canB;

void closeWindows(boolean closew = true) {
#define W_LF 0b00010000
#define W_RF 0b00100000
#define W_ALL 0b11110000
#define W_OPEN 0x0
#define W_CLOSE 0b00000100
#define W_AUTO 0b00000010
#define W_MAN 0b00000000
#define W_TEST 0b00001000

    sendCanMsg(createCANPackage(80, 1, W_ALL | W_MAN  | ((closew) ? W_CLOSE : W_OPEN)), 100);
    sendCanMsg(createCANPackage(80, 1, W_ALL | W_AUTO | ((closew) ? W_CLOSE : W_OPEN)));

    //sendCanMsg(createCANPackage(80, 1, W_LF | W_RF | W_AUTO | ((closew) ? W_CLOSE : W_OPEN)));
}


void closeWindowIfCarIsLocked(CANMSG msg) {
  if (msg.adrsValue == 0){
      if (msg.data[5] == 0xaa){
        

          closeWindows();
          Serial.println("LOCKED");
        
        
      }
    }
}


void testPackage(CANMSG msg)
{
  /*
  if (msg.adrsValue == -1) {
      if (msg.adrsValue == 2){
        uint16_t rpm = 0;
        rpm = msg.data[2] << 8;
        rpm = rpm | msg.data[3];
        //Serial.println(rpm);
      }
      printPackage(msg);
    }

    if (msg.adrsValue == 18) {
      //4a - right passager seat, 5a - nobody in the car
      //58 - driver seat
    }
    if (msg.adrsValue == 20){
      uint8_t val = msg.data[1];
      uint8_t val1 = val >> 2;
      uint8_t val2 = val & 0b00000011;
      Serial.print("temp: ");
      Serial.print(val1);
      Serial.print(".");
      Serial.println(val2 * 25);
    }
    */
}

//} else if (msg.adrsValue == 800) {
//car.consumption = (msg.data[0] << 8) | (msg.data[1]);
//Serial.println(car.consumption);

void ic_receive_consuption(CANMSG msg) 
{
  //petrol consumption
  if (msg.adrsValue == 800) {
    car.consumption = (msg.data[0] << 8) | (msg.data[1]);
    if (car.consumption < 0) {
      car.consumption = 0;
    }
    if (car.consumption > 0) {
      float diff = (micros() - car.consumption_total_last_time)*0.000001;
      car.consumption_total += car.consumption*diff;
    }
    car.consumption_total_last_time = micros();
    
    car.consumption = (car.consumption * 60.0 * 60.0)/1000000;

  //distance since start
  } else if (msg.adrsValue == 0x58) {
    unsigned long odometer = (msg.data[4] << 16) | (msg.data[5] << 8) | msg.data[6];
    if (car.start_odometer == 0) {
      car.start_odometer = odometer;
    }
    car.distance_after_start = (odometer - car.start_odometer)/10.0;

    if (car.ic_current_menu == 2) {
      
    }
  } else if (msg.adrsValue == 424) {
    //40 00
    Serial.println(msg.adrsValue);
    if (millis() - car.steering_button_pressed_last_time > 300){
      if (msg.data[0] == 0x40 && msg.data[1] == 0x00) {
        car.ic_current_menu++;
        car.ic_menu_last_update = 0;
        car.steering_button_pressed_last_time = millis();
      } else if (false) {
        car.ic_current_menu--;
        car.ic_menu_last_update = 0;
        car.steering_button_pressed_last_time = millis();
      }
      if (car.ic_current_menu > 2) car.ic_current_menu = 1;
      else if (car.ic_current_menu < 1) car.ic_current_menu = 2;
    }
  }
}

void ic_update_view()
{
  //Serial.println("tt"); 
  /*
  if (millis() - car.consumptionUpdate2 > 2000) {
    car.consumptionUpdate2 = millis();
    ic_music_top_line("Consumpt");
  }*/
  if (millis() - car.ic_menu_last_update > 200) {
    
    car.ic_menu_last_update = millis();
    if (car.ic_current_menu == 1) {
      String str = String(car.consumption, 2) + " " + String(car.consumption_total/1000.0, 1);
      char text[12];
      str.toCharArray(text, 12);
      ic_music_center_line(text);
      if (car.enable_ic_output_debug) {
        Serial.print(car.consumption);
        Serial.print(" ");
        Serial.println(car.consumption_total);       
      }

    } else if (car.ic_current_menu == 2) {
      float litters = car.consumption_total*0.000001;
      String str = String(car.distance_after_start, 1) + " " + String(litters*(100.0/car.distance_after_start));
      char text[12];
      str.toCharArray(text, 12);
      ic_music_center_line(text);
      if (car.enable_ic_output_debug) {
        Serial.print(litters);
        Serial.print(" ");
        Serial.print(car.distance_after_start);
        Serial.print(" ");
        Serial.println(litters*(100.0/car.distance_after_start));
      }
    }
  }
}

void doWork(CANMSG msg) 
{

  closeWindowIfCarIsLocked(msg);
  
    //checking if the engine is started
    if (msg.adrsValue == 10){
      //printPackage(msg);
      if (car.engineOn == false && msg.data[6] == 0x83) {
        car.engineOn = true;
        Serial.println("ignition on");
        /*
        CANMSG msg = createCANPackage(592, 1, 0xfa);
        MCP2515::transmitCANMessage(msg, 100);
        printPackage(msg);
        delay(100);
        msg = createCANPackage(592, 1, 0x00);
        MCP2515::transmitCANMessage(msg, 100);
        printPackage(msg);
        */
      } else if (car.engineOn == true && msg.data[6] == 0x82) {
        car.engineOn = false;
        Serial.println("ignition off");
        /*
        CANMSG msg = createCANPackage(592, 1, 0xfe);
        MCP2515::transmitCANMessage(msg, 100);
        printPackage(msg);
        delay(100);
        msg = createCANPackage(592, 1, 0x00);
        MCP2515::transmitCANMessage(msg, 100);
        printPackage(msg);
        */
      }

    } else if (msg.adrsValue == 12) {
      car.speeed = (msg.data[0] << 8) | (msg.data[1]);
      if (car.speeed == 255) {
        car.speeed = 0;
      }
      //Serial.print("speed ");
     // Serial.println(car.consumption*(100.0/car.speeed));
      //(100.0/car.speeed);
    } else if (msg.adrsValue == 800) {

      
    //checking battery voltage
    } else if (msg.adrsValue == 22){
      uint8_t val = msg.data[0];
      car.voltage = val/10.0;
    //checking in car temp
    } else if (msg.adrsValue == 20){
      uint8_t val = msg.data[1];
      car.temp = (val >> 2) + (val & 0x3) * 0.25;
       
    //checking if passager is on the seat, needs to enable passager's heater if it's too cold
    } else if (msg.adrsValue == 23){
      uint8_t val = msg.data[0];
      
      car.outsideTemp = (val >> 1) + (val & 0x1) * 0.5 - 40;
       
    //checking if passager is on the seat, needs to enable passager's heater if it's too cold
    } else if (msg.adrsValue == 18){
      car.seat2_status = msg.data[2];
    

    //enabling heaters if it's cold in car
    } else if (msg.adrsValue == 528) {
        //heater status
        //528 4 00 00 00 00(status)  18 - 3, 10 - 2, 8 - 1
        uint8_t heater1 = msg.data[0] >> 3;
        uint8_t heater2 = msg.data[1] >> 3;
        if (car.temp < 18) {
          if (heater1 == 0 && car.heater1_was_enabled_once == false){
            car.heater1_was_enabled_once = true;
            CANMSG msg = createCANPackage(44, 4, 0x00, 0x00, 0x08, 0x40);
            canB.transmitCANMessage(msg, 100);
            printPackage(msg);
            Serial.print("heater turned on ");
            Serial.println(car.temp);
          }
          if (heater2 == 0 && car.heater2_was_enabled_once == false && car.seat2_status == 0x4a){
            car.heater2_was_enabled_once = true;
            CANMSG msg = createCANPackage(44, 4, 0x00, 0x00, 0x80, 0x40);
            canB.transmitCANMessage(msg, 100);
            printPackage(msg);
            Serial.print("passager heater turned on ");
            Serial.println(car.temp);
          }
        }
    }
}

