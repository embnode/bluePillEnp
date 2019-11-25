#include "flash_app.h"

static uint32_t flashAppGetSector(uint32_t Address);

/**
  * @brief  Стирание указанных страниц памяти.
  * @param  uint32_t startAddr, uint32_t stopAddr - используется только
  стартовый адрес. стоповый адрес оставлен для реализации адаптера к
  существующему коду.
  * @retval HAL status
  */
uint8_t FLASH_APP_Erase(uint32_t startAddr, uint32_t stopAddr) {
  HAL_StatusTypeDef status;
  FLASH_EraseInitTypeDef EraseInit;
  uint32_t PageError = 0, FirstSector, NbOfSectors;
  // Структура для ситрания страницы
  EraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
  EraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;
  FirstSector = flashAppGetSector(startAddr);
  EraseInit.Sector = FirstSector;
  NbOfSectors = flashAppGetSector(stopAddr) - FirstSector + 1;
  EraseInit.NbSectors = NbOfSectors;
  EraseInit.Banks = FLASH_BANK_1;
  // OBInit.OptionType = OPTIONBYTE_WRP;
  // OBInit.WRPState = OB_WRPSTATE_DISABLE;
  // OBInit.WRPSector = FirstSector;
  HAL_FLASH_Unlock();
  HAL_FLASH_OB_Unlock();
  // HAL_FLASHEx_OBProgram( &OBInit );
  status = HAL_FLASHEx_Erase(&EraseInit, &PageError);
  HAL_FLASH_Lock();
  return !status;
}

/**
  * @brief  Запись данных.
  * @param  * ptr - указатель на данные
                        * dst - адрес хранения данных
                         size - количество данных (в байтах)
  * @retval HAL status
  */
uint8_t FLASH_APP_Write(const void *ptr, void *dst, int size) {
  const uint8_t *src = ptr;
  uint32_t offset = 0;
  uint32_t addr = (uint32_t)dst;
  HAL_StatusTypeDef status = HAL_ERROR;

  // разблокировать
  HAL_FLASH_Unlock();
  HAL_FLASH_OB_Unlock();
  // запись
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
    // проверка ошибок записи
    if (status != HAL_OK)
      break;
  }
  // заблокировать
  HAL_FLASH_Lock();

  return !status;
}
/**
 * @brief  Gets the sector of a given address
 * @param  None
 * @retval The sector of a given address
 */
static uint32_t flashAppGetSector(uint32_t Address) {
  uint32_t sector = 0;

  if ((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0)) {
    sector = FLASH_SECTOR_0;
  } else if ((Address < ADDR_FLASH_SECTOR_2) &&
             (Address >= ADDR_FLASH_SECTOR_1)) {
    sector = FLASH_SECTOR_1;
  } else if ((Address < ADDR_FLASH_SECTOR_3) &&
             (Address >= ADDR_FLASH_SECTOR_2)) {
    sector = FLASH_SECTOR_2;
  } else if ((Address < ADDR_FLASH_SECTOR_4) &&
             (Address >= ADDR_FLASH_SECTOR_3)) {
    sector = FLASH_SECTOR_3;
  } else if ((Address < ADDR_FLASH_SECTOR_5) &&
             (Address >= ADDR_FLASH_SECTOR_4)) {
    sector = FLASH_SECTOR_4;
  } else if ((Address < ADDR_FLASH_SECTOR_6) &&
             (Address >= ADDR_FLASH_SECTOR_5)) {
    sector = FLASH_SECTOR_5;
  } else if ((Address < ADDR_FLASH_SECTOR_7) &&
             (Address >= ADDR_FLASH_SECTOR_6)) {
    sector = FLASH_SECTOR_6;
  } else if ((Address < ADDR_FLASH_SECTOR_8) &&
             (Address >= ADDR_FLASH_SECTOR_7)) {
    sector = FLASH_SECTOR_7;
  } else if ((Address < ADDR_FLASH_SECTOR_9) &&
             (Address >= ADDR_FLASH_SECTOR_8)) {
    sector = FLASH_SECTOR_8;
  } else if ((Address < ADDR_FLASH_SECTOR_10) &&
             (Address >= ADDR_FLASH_SECTOR_9)) {
    sector = FLASH_SECTOR_9;
  } else if ((Address < ADDR_FLASH_SECTOR_11) &&
             (Address >= ADDR_FLASH_SECTOR_10)) {
    sector = FLASH_SECTOR_10;
  } else {
    sector = FLASH_SECTOR_11;
  }
  return sector;
}
