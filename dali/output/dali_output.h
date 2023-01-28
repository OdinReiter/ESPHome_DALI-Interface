#pragma once

#include "esphome/core/component.h"
#include "esphome/components/output/float_output.h"
#include "../dali.h"


namespace esphome {
namespace Dali_Hub_ns {

class Dali_Output : public output::FloatOutput, public Component {
 public:
  void setup() override;
  void loop() override;
  void write_state(float state) override;
  void dump_config() override;

  void set_parent(Dali_Hub *parent) { parent_ = parent; }

  void set_Address(int address) { DALI_ADDRESS_ = (address << 1) + 1; }
  void set_Group(int group) { DALI_GROUP_ = (group * 2) + 1 + 0x80; }
  void set_FadeTime(int FadeTime) { DALI_FadeTime_ = FadeTime; }
  void set_FadeRate(int FadeRate) { DALI_FadeRate_ = FadeRate; }

  protected:
    //--- Parent
    Dali_Hub *parent_;

    //--- inputs
    int DALI_ADDRESS_ = 0xFF;
    int DALI_GROUP_ = 0x00;

    int DALI_FadeTime_ = 1;
    int DALI_FadeRate_ = 2;

    //--- internal stuff
    float state_ = 0;
    bool updateOutput_ = false;

    long lasttime_ms_ = 0;
    long updatetime_ms_ = 15;
};


} //namespace Dali_Hub_ns
} //namespace esphome