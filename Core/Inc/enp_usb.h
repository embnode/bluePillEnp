#pragma once
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

void ENPUSB_Init(void);
void ENPUSB_Proc(void);
void ENPUSB_readUsbBuff(uint8_t* buf, uint16_t len);

#ifdef __cplusplus
}
#endif
