#include "esphome/core/log.h"
#include "dali_output.h"

namespace esphome {
namespace Dali_Hub_ns {

static const char *TAG = "dali_output.output";

void Dali_Output::setup(){

}

void Dali_Output::loop() {

    if(updateOutput_ == true){
        if(millis() > lasttime_ms_ + updatetime_ms_){
            ESP_LOGD(TAG, "Sending Brightness: %f", state_);
            updateOutput_ = false;
            this->parent_->SendBrightness(DALI_ADDRESS_, state_);
        }
    }
}


void Dali_Output::dump_config() {
    ESP_LOGCONFIG(TAG, "Empty custom float output");
}

//--- Handle for light component
void Dali_Output::write_state(float state){
    //ESP_LOGD(TAG, "state: %f", state);
    state_ = state;
    updateOutput_ = true;
    lasttime_ms_ = millis();
}




} //namespace Dali_Hub_ns
} //namespace esphome

