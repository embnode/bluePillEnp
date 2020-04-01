#include "enp_usb.h"
#include "enpHelper.h"
#include "usbd_cdc_if.h"

// Object for enp protocol
ENP_Handle_t hEnpUSB;

bool isFrameParsed = false;

void ENPUSB_readUsbBuff(uint8_t* buf, uint16_t len)
{
    // Parse enp
    isFrameParsed = ENP_ParseFrame(&hEnpUSB, buf, len);
}

// ENP protocol task
void ENPUSB_Proc(void)
{
    if(isFrameParsed){
        ENP_AnswerProc(&hEnpUSB);
        isFrameParsed = false;
    }
}

static int TxFunc(const void* s, int n)
{
    uint8_t* buff = (uint8_t*)s;
    CDC_Transmit_FS(buff, n);
    return n;
}

void ENPUSB_Init()
{
    ENP_InitHandle(&hEnpUSB, 1, 2, TxFunc);
}
