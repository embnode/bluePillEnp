#include "flash.h"

/**
  * @brief  Erase memory.
  * @param  uint32_t startAddr, uint32_t stopAddr - start and stop addresses
  * @retval HAL status
  */
uint8_t FLASH_APP_Erase(uint32_t startAddr, uint32_t stopAddr) {
  HAL_StatusTypeDef status;
  FLASH_EraseInitTypeDef EraseInit;
  uint32_t NbOfPages, PageError;
  // Erase struct
  EraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
  EraseInit.Banks = FLASH_BANK_1;
  EraseInit.PageAddress = startAddr;
  NbOfPages = (stopAddr - startAddr) / 0x400;
  if(NbOfPages < 1) {
    NbOfPages = 1;
  }
  HAL_FLASH_Unlock();
  HAL_FLASH_OB_Unlock();
  status = HAL_FLASHEx_Erase(&EraseInit, &PageError);
  HAL_FLASH_Lock();
  return !status;
}

/**
  * @brief  Write data.
  * @param  * ptr - pointer to data in RAM
                        * dst - pointer to data in flash
                         size - number bytes
  * @retval HAL status
  */
uint8_t FLASH_APP_Write(const void *ptr, void *dst, int size) {
  const uint8_t *src = ptr;
  uint32_t offset = 0;
  uint32_t addr = (uint32_t)dst;
  HAL_StatusTypeDef status = HAL_ERROR;

  // unlock
  HAL_FLASH_Unlock();
  HAL_FLASH_OB_Unlock();
  // write
  while (size > 0) {
    if (size >= 4) {
      status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr,
                                 *(uint32_t *)(src + offset));
      addr += 4;
      size -= 4;
      offset += 4;
    } else {
      status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, addr,
                                 *(uint16_t *)(src + offset));
      addr += 2;
      size -= 2;
      offset += 2;
    }
    // error check
    if (status != HAL_OK)
      break;
  }
  HAL_FLASH_Lock();

  return !status;
}
