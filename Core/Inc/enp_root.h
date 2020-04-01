#pragma once

#include "enpHelper.h"

#define __usrdata __attribute__((section(".usr_pars")))

#ifdef __cplusplus
extern "C" {
#endif

// Identificators for nodes
enum {
    NODE_ROOT,
    NODE_LED,
    ENP_NODENUM
};

// Protocol init
void ENP_DevInit();

#ifdef __cplusplus
}
#endif
