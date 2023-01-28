import esphome.codegen as cg                    
import esphome.config_validation as cv                  
from esphome import pins                                # class Pins
from esphome.const import CONF_ID, CONF_PIN             # Const predefined names of esphome

# custom input in yaml
CONF_SENDING_PIN = 'sending_pin'
CONF_READING_PIN = 'reading_pin'
CONF_POS_WT = 'pos_waittime'
CONF_NEG_WT = 'neg_waittime'
# Config String for yaml for the output class
CONF_DALI_HUB = "DALI_Hub"

# define component namespace and class name for esphome
DALI_ns = cg.esphome_ns.namespace('Dali_Hub_ns')
DALI = DALI_ns.class_('Dali_Hub', cg.Component)

# Config schema for the usage in the device yaml
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(DALI),                       # Declare ID of this component
    cv.Required(CONF_SENDING_PIN): pins.gpio_output_pin_schema, # Get Pin (predefined as output)
    cv.Optional(CONF_READING_PIN): pins.gpio_input_pin_schema,  # Get Pin (predefined as output)
    cv.Optional(CONF_POS_WT): cv.int_range(min=0, max=1000),    # Config Sending Pin positive Waittime
    cv.Optional(CONF_NEG_WT): cv.int_range(min=0, max=1000),    # Config Sending Pin negative Waittime
}).extend(cv.COMPONENT_SCHEMA)

# code for connecting esphome to the cpp class
# has to be async 
async def to_code(config):
    # Registration of the component
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    # set sending pin
    pin = await cg.gpio_pin_expression(config[CONF_SENDING_PIN])    # get config of yaml
    cg.add(var.set_sending_pin(pin))                                # set pin in cpp (set_sending_pin is the function in cpp)
    # set reading pin
    if CONF_READING_PIN in config:
        pin2 = await cg.gpio_pin_expression(config[CONF_SENDING_PIN])
        cg.add(var.set_reading_pin(pin2))

    # set config for sending
    if CONF_POS_WT in config:
        cg.add(var.set_PosWaittime_us(config[CONF_POS_WT]))
    if CONF_NEG_WT in config:
        cg.add(var.set_NegWaittime_us(config[CONF_NEG_WT]))