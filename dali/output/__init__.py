import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output
from esphome.const import CONF_ID

# --- import namespace from dali_hub (doesnt work)
from .. import DALI_ns, DALI, CONF_DALI_HUB

#DEPENDENCIES = ["dali_hub"]

# Names for inputs
CONF_ADDRESS = 'address'
CONF_GROUP = 'group'
CONF_FADERATE = 'faderate'
CONF_FADETIME = 'faderate'

# Setup namesspace for class
#dali_output_ns = cg.esphome_ns.namespace('Dali_Output_ns')
DALI_Output = DALI_ns.class_('Dali_Output', output.FloatOutput, cg.Component)

# Setup Config Schema for yaml 
CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend({
    cv.Required(CONF_ID): cv.declare_id(DALI_Output),
    cv.GenerateID(CONF_DALI_HUB): cv.use_id(DALI),
    cv.Optional(CONF_ADDRESS): cv.int_range(min=0, max=63),
    cv.Optional(CONF_GROUP): cv.int_range(min=0, max=15),
    cv.Optional(CONF_FADERATE): cv.int_range(min=0, max=15),
    cv.Optional(CONF_FADETIME): cv.int_range(min=0, max=15),
}).extend(cv.COMPONENT_SCHEMA)



async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await output.register_output(var, config)
    await cg.register_component(var, config)

    # Set Parent
    parent = await cg.get_variable(config[CONF_DALI_HUB])
    cg.add(var.set_parent(parent))

    # Address & group
    if CONF_ADDRESS in config:
        cg.add(var.set_Address(config[CONF_ADDRESS]))
    if CONF_GROUP in config:
        cg.add(var.set_Group(config[CONF_GROUP]))
    # Faderate & fadetime
    if CONF_FADERATE in config:
        cg.add(var.set_FadeRate(config[CONF_FADERATE]))
    if CONF_FADETIME in config:
        cg.add(var.set_FadeTime(config[CONF_FADETIME]))
    