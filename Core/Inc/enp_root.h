#pragma once

#include "enpapi.h"

#define __usrdata __attribute__((section(".usr_const")))

#ifdef __cplusplus
extern "C" {
#endif

// Identificators for nodes
enum {
  NODE_ROOT,
  NODE_LED,
  ENP_NODENUM
};

// Identificators for variables
enum ENP_APP_VAR {
  ENP_ROOT_VAR_ERROR,  // error code
  ENP_ROOT_VAR_DEV_ID, // device id
  ENP_ROOT_VAR_TIME,   // up time
  ENP_ROOT_VAR_NUM
};

// Atttributes of variables
extern const ENP_Attr_t ICP_APP_VAR_ATTR[ENP_ROOT_VAR_NUM];
// Protocol init
void ENP_DevInit();

#ifdef __cplusplus
}
#endif
