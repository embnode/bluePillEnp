#include "enpapi.h"
#include "usbd_cdc_if.h"
#include "staticBuffersTmpl.h"
#include "enp_usb.h"

// Object for enp protocol
ENP_Handle_t hEnpUSB;

staticBuffersTmpl::RingBuff<uint8_t, 256> usbBuff;

void ENPUSB_readUsbBuff(uint8_t *buf, uint16_t len) {
  int i = 0;
  while (len) {
    usbBuff.put(buf[i]);
    i++;
    len--;
  }
}

// Эта задача обслуживает обмен с конфигуратором
void ENPUSB_Proc(void) { ENP_Proc(&hEnpUSB); }
static int usb_getC(void) {
  int ret = -1;
  if (usbBuff.size()) {
    ret = usbBuff.get();
    usbBuff.pop();
  }
  return ret;
}

static int usb_putN(const char *s, int n) {
  CDC_Transmit_FS((uint8_t *)s, n);
  return n;
}

void ENPUSB_Init() {
  ENP_InitHandle(&hEnpUSB, 17000, 17000, usb_getC, usb_putN);
}
