#pragma once

#include "enpapi.h"

#define __usrdata __attribute__((section(".usr_const")))
extern __usrdata ENP_Data_t DEVICE_UsrData;

// Identificators for nodes
enum {
  NODE_ROOT = 100, // ROOT
  ENP_APP_NODENUM = 5
};

// Identificators for variables
enum ENP_APP_VAR {
  ENP_APP_VAR_ERROR,  // error code
  ENP_APP_VAR_DEV_ID, // device id
  ENP_APP_VAR_TIME,   // up time
  ENP_APP_VAR_NUM
};

// Atttributes of variables
extern const ENP_Attr_t ICP_APP_VAR_ATTR[ENP_APP_VAR_NUM];
// Protocol init
void ENP_DevInit();
