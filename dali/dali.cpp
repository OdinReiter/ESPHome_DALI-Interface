#include "esphome/core/log.h"
#include "dali.h"

namespace esphome {
namespace Dali_Hub_ns {

static const char *TAG = "dali_hub.component";

void Dali_Hub::setup() {
    ESP_LOGD(TAG, "Hallooo");
}

void Dali_Hub::loop() {
    
}

void Dali_Hub::testParent(){
    ESP_LOGD(TAG, "Hallooo from output!");
}
void Dali_Hub::testParent(float brightness){
    ESP_LOGD(TAG, "Test! Brightness: %f", brightness);
}



void Dali_Hub::SendBrightness(int address, float brightness){
    int DAPC = calcDAPC_(brightness*100);
    sendForwardFrame_(address - 1, DAPC);
}

void Dali_Hub::dump_config(){
    ESP_LOGCONFIG(TAG, "Empty component");
    LOG_PIN("_sending_pin : ", this->sending_pin_);
}


// --- --- --- --- ---
// Sending functions
void Dali_Hub::sendForwardFrame_(int address, int data)
{
    bool iBit;
    //--- Startbit
    sendStartBit_();
    //--- Addresse
    for (int i = 7; i >= 0; i--)
    {
        iBit = bitRead_(address, i);
        sendBit_(iBit);
    }

    //--- Data
    for (int i = 7; i >= 0; i--)
    {
        iBit = bitRead_(data, i);
        sendBit_(iBit);
    }
    //--- Stopbits
    sendStopBit_();         // send stop bit
    waitTime_us_(10000);    // wait additional time
}

// implementation of bitRead (cause i dont find the arduino version)
bool Dali_Hub::bitRead_(int value, unsigned int i)
{

    int shift = value >> i;
    int erg = shift & 0x01;

    if(erg > 0)
        return true;
    return false;
}

// --- --- --- --- ---
// Sending functions
// --- --- --- --- ---

void Dali_Hub::sendStartBit_() {
    sendBit_(true);
}

void Dali_Hub::sendStopBit_() {
    sendNegSlope_();
    waitTime_us_(2000);
}

// Do Manchester Bit
void Dali_Hub::sendBit_(bool sendBit) {
    if (sendBit == true)
    {
        sendPosSlope_();
        sendNegSlope_();
    }
    else
    {
        sendNegSlope_();
        sendPosSlope_();
    }
}
// send positiv half Slope
void Dali_Hub::sendPosSlope_() {
    sending_pin_->digital_write(true);
    waitTime_us_(waitTime_PosSlope_us_);
}
// send negativ half Slope
void Dali_Hub::sendNegSlope_() {
    sending_pin_->digital_write(false);
    waitTime_us_(waitTime_NegSlope_us_);
}
// --- --- --- --- --- 
// Waittime for DALI Sending stuff (Blocking other tasks for timing)
void Dali_Hub::waitTime_us_(unsigned int waittime_us)
{
    int i = 0;
    unsigned long now_time = micros();
    while (micros() < now_time + waittime_us)
    {
        i++; // do dumb stuff
    }
}



//--- --------------------------------------------------------------------------------------------
//---
int Dali_Hub::calcDAPC_(double percent)
{
    //---
    double c = 0;
    for (int i = 0; i < 255; i++)
    {
        //--- calc differenz
        c = _DALI_DIMMINGCURVE_PERCENT[i] - percent;
        if (c >= 0)
        {
            return i;
        }
    }
    return 254;
}
//--- --------------------------------------------------------------------------------------------
//---
double Dali_Hub::calcPercent_(int DAPC)
{
    //---
    return _DALI_DIMMINGCURVE_PERCENT[DAPC];
}



}  // namespace dali_hub
}  // namespace esphome