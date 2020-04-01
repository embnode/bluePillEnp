#include "led.h"
#include "stdint.h"
#include "enProt.h"
#include "stm32f1xx_hal.h"
#include "enp_root.h"

static uint32_t tick = 0;
static uint32_t toggleTick = 0;
static uint32_t mode = 0;
static uint32_t toggleDelay = 1000;

// prototypes functions support configuration
static uint16_t _varGet(uint16_t, uint16_t, void *);
static uint16_t _varSet(uint16_t, uint16_t, void *);

// Identificators for variables
enum {
  LED_VAR_MODE, 
  LED_VAR_DELAY, 
  LED_VAR_NUM
};

static const ENP_Attr_t attr[LED_VAR_NUM] = {
    {"Mode", ENP_TYPE_UINT | ENP_PROP_CONST},
    {"Delay", ENP_TYPE_UINT | ENP_PROP_CONST},
};

// Nodelist for led configuration
const ENP_Node_t LED_NodeList[] = {
    {"LED", NODE_LED, NODE_ROOT, LED_VAR_NUM, attr,
     _varGet, _varSet}
};

void LED_Init() {
  uint16_t nodeNum = GET_NODES_NUM(LED_NodeList);
  ENP_InsertNodes(LED_NodeList, nodeNum); // Добавляем узел
}

void LED_Proc() {
  if(mode == 0){
    tick = HAL_GetTick();
    if (tick > toggleTick) {
      HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
      toggleTick = tick + toggleDelay;
    }
  } else {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
  }
}

// Get variable
static uint16_t _varGet(uint16_t nodeid, uint16_t varid, void *value) {
  switch (nodeid) {
  case NODE_LED:
    switch (varid) {
      case   LED_VAR_MODE:
        *(uint32_t *)value = mode;
        break;
      case   LED_VAR_DELAY:
        *(uint32_t *)value = toggleDelay;
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
static uint16_t _varSet(uint16_t nodeid, uint16_t varid, void *value) {
  switch (nodeid) {
  case NODE_LED:
    switch (varid) {
      case   LED_VAR_MODE:
        mode = *(uint32_t *)value;
        break;
      case   LED_VAR_DELAY:
        toggleDelay = *(uint32_t *)value;
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
