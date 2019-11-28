#include "led.h"
//#include "stdint.h"
#include "enpprot.h"
#include "stm32f1xx_hal.h"
#include "enp_app.h"

static uint32_t tick = 0;
static uint32_t toggleTick = 0;

// prototypes functions of configuration
static uint16_t LED_VarGetAttr(uint16_t, uint16_t, char *, uint16_t *);
static uint16_t LED_NodeName(uint16_t, char *);
static uint16_t LED_VarGet(uint16_t, uint16_t, void *);
static uint16_t LED_VarSet(uint16_t, uint16_t, void *);

// Identificators for variables
enum {
  LED_VAR_MODE, 
  LED_VAR_DELAY, 
  LED_VAR_NUM
};

static const ENP_Attr_t attr[] = {
    {"Mode", ENP_TYPE_HEX},
    {"Delay", ENP_TYPE_UINT},
};

// Nodelist for led configuration
const ENP_Node_t LED_NodeList[] = {
    {"I2C_IO", NODE_LED, NODE_ROOT, sizeof(attr) / sizeof(attr[0]), 0,
     LED_VarGet, LED_VarSet, LED_VarGetAttr, LED_NodeName},
};

void LED_Init() {
  uint16_t nodeNum = API_GET_NODE_NUM(LED_NodeList);
  ENP_InsertNode(LED_NodeList, nodeNum); // Добавляем узел
}

void LED_Proc() {
  tick = HAL_GetTick();
  if (tick > toggleTick) {
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    toggleTick = tick + 1000;
  }
}

// Get variable
uint16_t LED_VarGet(uint16_t nodeid, uint16_t varid, void *value) {
  switch (nodeid) {
  case NODE_LED:
    switch (varid) {
      case   LED_VAR_MODE:
        *(uint32_t *)value = 0;
        break;
      case   LED_VAR_DELAY:
        *(uint32_t *)value = 0;
        break;
      default:
        return ENP_ERROR_VARID;
      }
    break;
  default:
    return ENP_ERROR_NODEID;
  }
  return ENP_ERROR_NONE;
}

// set variable
uint16_t LED_VarSet(uint16_t nodeid, uint16_t varid, void *value) {
  switch (nodeid) {
  case NODE_LED:
    switch (varid) {
      case   LED_VAR_MODE:
        //*(uint32_t *)value = 0;
        break;
      case   LED_VAR_DELAY:
        //*(uint32_t *)value = 0;
        break;
      default:
        return ENP_ERROR_VARID;
      }
    break;
  default:
    return ENP_ERROR_NODEID;
  }
  return ENP_ERROR_NONE;
}

// get attributes
uint16_t LED_VarGetAttr(uint16_t nodeid, uint16_t varid, char *name,
                        uint16_t *prop) {
  switch (nodeid) {
  case NODE_LED:
    // uint32_t ret = ENP_ERROR_NONE;
    // if ((varid < this->varNum) && (this->attr != nullptr))
    // {
    //     if (name != nullptr)
    //     {
    //         strcpy(name, this->attr[varid].name);
    //     }
    //     if (prop != nullptr)
    //     {
    //         *prop = this->attr[varid].prop;
    //     }
    // }
    // else
    // {
    //     ret = ENP_ERROR_VARID;
    // }
    //return ret;
    break;
  default:
    return ENP_ERROR_NODEID;
  }
  return ENP_ERROR_NONE;
}

uint16_t LED_NodeName(uint16_t nodeid, char *name) {
  switch (nodeid) {
  case NODE_LED:
    //node.getName(name);
    break;
  default:
    return ENP_ERROR_NODEID;
  }
  return ENP_ERROR_NONE;
}
