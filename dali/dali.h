#pragma once
#include "esphome/core/component.h"
#include "esphome/core/gpio.h"
#include "esphome/core/hal.h"

#include "DALI_DAPC_VALUES.h"

namespace esphome {
namespace Dali_Hub_ns {

class Dali_Hub : public Component {

 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  //--- Setup functions
  void set_sending_pin(GPIOPin *sending_pin) { this->sending_pin_ = sending_pin; }
  void set_reading_pin(GPIOPin *reading_pin) { this->reading_pin_ = reading_pin; }

  void set_PosWaittime_us(int posWaittime) { this->waitTime_PosSlope_us_ = posWaittime; }
  void set_NegWaittime_us(int negWaittime) { this->waitTime_NegSlope_us_ = negWaittime; }
  //--- Interface function for the output class
  void testParent();
  void testParent(float brightness);
  void sendCommand(int address, int data);
  void sendFadingParam(int address, int faderate, int fadetime);
  void SendBrightness(int address, float brightness);

 protected:
  //--- Defined GPIO Pins
  GPIOPin *sending_pin_;
  GPIOPin *reading_pin_;


  bool sendBit = 0; // testing
  long last = 0;    // testing

  int waitTime_PosSlope_us_ = 416;
  int waitTime_NegSlope_us_ = 416;


  int calcDAPC_(double percent);
  double calcPercent_(int DAPC);

  // Sending Frame
  void sendForwardFrame_(int address, int data);
  bool bitRead_(int value, unsigned int i);

  // Sending functions
  void sendStartBit_();
  void sendStopBit_();
  void sendBit_(bool sendBit);
  void sendPosSlope_();
  void sendNegSlope_();
  
  void waitTime_us_(unsigned int waittime_us);
};


}  // namespace Dali_Hub
}  // namespace esphome