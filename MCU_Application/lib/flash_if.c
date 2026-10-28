/**
  ******************************************************************************
  * @file    flash_if.c
  * @brief   Flash layer functions - generic for all STM32F4 series
  *          Supports: 256KB(F401), 512KB(F411), 1MB(F405/407), 2MB dual-bank(F429/469)
  * @note    Robust against debug-mode stale flags: clears ALL error flags and
  *          waits for BSY before every erase/program, fixing the issue where
  *          ST-Link leaves stale OPERR/PGAERR/PGPERR flags that cause
  *          HAL_FLASHEx_Erase() to fail immediately when debugging.
  ******************************************************************************
  */
#include "flash_if.h"
#include "libcpu.h" /* for cpuGetFlashSize() */

/* Private typedef ----------------------------------------------------------- */
/* Private define ------------------------------------------------------------ */
#define FLASH_BASE_ADDR       0x08000000U
#define FLASH_BANK2_OFFSET    0x00100000U  /* 2MB devices: bank2 starts at 0x08100000 */
#define SECTOR_16KB           0x4000U
#define SECTOR_64KB           0x10000U
#define SECTOR_128KB          0x20000U

/* All flash error/status flags that can be left stale by a debug session:
 * EOP, OPERR, WRPERR, PGAERR, PGPERR, PGSERR.
 * Note: BSY is read-only and cannot be cleared by writing to SR. */
#define FLASH_ALL_CLEAR_FLAGS  (FLASH_FLAG_EOP   | FLASH_FLAG_OPERR | \
                                FLASH_FLAG_WRPERR| FLASH_FLAG_PGAERR| \
                                FLASH_FLAG_PGPERR| FLASH_FLAG_PGSERR)

#define FLASH_TIMEOUT_MS       5000U

/* Private variables --------------------------------------------------------- */
static uint32_t FirstSector = 0;
static uint32_t NbOfSectors = 0;
static uint32_t SectorError = 0;
static uint32_t OB_RDP_LEVEL;

/* Private function prototypes ----------------------------------------------- */
static uint32_t FLASH_If_GetSectorNumber(uint32_t Address);
static uint32_t FLASH_If_GetFlashEndAddr(void);
static void FLASH_If_Prepare(void);
static FLASH_OBProgramInitTypeDef FLASH_OBProgramInitStruct;
static FLASH_EraseInitTypeDef FLASH_EraseInitStruct;

/* Private functions --------------------------------------------------------- */

void FLASH_If_FlashUnlock(void)
{
  HAL_FLASH_Unlock();
}

FlagStatus FLASH_If_ReadOutProtectionStatus(void)
{
  FlagStatus readoutstatus = RESET;
  FLASH_OBProgramInitStruct.RDPLevel = OB_RDP_LEVEL;
  HAL_FLASHEx_OBGetConfig(&FLASH_OBProgramInitStruct);
  if (OB_RDP_LEVEL == SET)
    readoutstatus = SET;
  else
    readoutstatus = RESET;
  return readoutstatus;
}

/* Returns the last valid flash address for the current MCU, based on cpuGetFlashSize() */
static uint32_t FLASH_If_GetFlashEndAddr(void)
{
  uint16_t flashKb = cpuGetFlashSize();
  return FLASH_BASE_ADDR + ((uint32_t)flashKb << 10) - 1;
}

/*
 * Prepare flash for erase/program:
 * 1. Ensure FPEC is unlocked (tolerates already-unlocked state from debugger)
 * 2. Wait for BSY to clear with timeout
 * 3. Clear ALL stale error flags (OPERR/PGAERR/PGPERR/WRPERR/PGSERR/EOP)
 *
 * This fixes the classic "can't erase when debugging" issue:
 * when ST-Link aborts a flash operation mid-way, it leaves stale error flags
 * in FLASH_SR. HAL_FLASHEx_Erase() internally checks these flags and
 * immediately returns error without even starting the erase.
 * Standalone (power-on reset) clears all flags by hardware, so it works.
 */
static void FLASH_If_Prepare(void)
{
  uint32_t tickstart;

  /* 1. Ensure unlocked. If debugger already left it unlocked, ignore the error. */
  if ((FLASH->CR & FLASH_CR_LOCK) != 0U)
  {
    HAL_FLASH_Unlock();
  }

  /* 2. Wait for BSY to clear (with timeout). BSY is set by hardware during
   *    any flash operation. If a debug session halted the CPU mid-operation,
   *    BSY might still be set when we resume. */
  tickstart = HAL_GetTick();
  while ((FLASH->SR & FLASH_SR_BSY) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > FLASH_TIMEOUT_MS)
    {
      break; /* timeout: proceed anyway, the HAL will report the error */
    }
  }

  /* 3. Clear ALL error flags. Writing 1 to active bits clears them.
   *    This is the critical fix: without clearing OPERR/PGAERR/PGPERR,
   *    HAL_FLASHEx_Erase()'s internal WaitForLastOperation() sees stale
   *    flags and returns HAL_ERROR immediately. */
  __HAL_FLASH_CLEAR_FLAG(FLASH_ALL_CLEAR_FLAGS);
}

uint32_t FLASH_If_EraseApplication(void){
	FLASH_If_Prepare();
	FirstSector = FLASH_If_GetSectorNumber(APPLICATION_FLASH_START_ADDRESS);
	NbOfSectors = FLASH_If_GetSectorNumber((FLASH_If_GetFlashEndAddr() - 4)) - FirstSector + 1;
	FLASH_EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
	FLASH_EraseInitStruct.Sector = FirstSector;
	FLASH_EraseInitStruct.NbSectors = NbOfSectors;
	FLASH_EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	if(HAL_FLASHEx_Erase(&FLASH_EraseInitStruct, &SectorError) != HAL_OK){
		return (1);
	}
	return (0);
}

uint32_t FLASH_If_EraseBootload(void){
	FLASH_If_Prepare();
	FirstSector = FLASH_If_GetSectorNumber(BOOTLOADER_FLASH_START_ADDRESS);
	NbOfSectors = FLASH_If_GetSectorNumber((BOOTLOADER_FLASH_END_ADDRESS - 4)) - FirstSector + 1;
	FLASH_EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
	FLASH_EraseInitStruct.Sector = FirstSector;
	FLASH_EraseInitStruct.NbSectors = NbOfSectors;
	FLASH_EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
	if(HAL_FLASHEx_Erase(&FLASH_EraseInitStruct, &SectorError) != HAL_OK){
		return (1);
	}
	return (0);
}

uint32_t FLASH_If_WriteApplication(uint32_t Address, uint32_t Data)
{
  if (Address <= (FLASH_If_GetFlashEndAddr() - 4))
  {
    FLASH_If_Prepare();
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, Data) != HAL_OK)
      return (1);
  }
  else
  {
    return (1);
  }
  return (0);
}

uint32_t FLASH_If_Write(uint32_t Address, uint32_t Data)
{
  if (Address <= (FLASH_If_GetFlashEndAddr() - 4))
  {
    FLASH_If_Prepare();
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, Data) != HAL_OK)
      return (1);
  }
  else
  {
    return (1);
  }
  return (0);
}

uint32_t FLASH_lf_WriteBootload(uint32_t Address, uint32_t Data)
{
  if (Address <= (BOOTLOADER_FLASH_END_ADDRESS - 4))
  {
    FLASH_If_Prepare();
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Address, Data) != HAL_OK)
      return (1);
  }
  else
  {
    return (1);
  }
  return (0);
}

/*
 * Generic sector number computation for all STM32F4 devices:
 * Layout (per bank):
 *   offset 0x00000-0x0FFFF : sectors 0-3, 16KB each
 *   offset 0x10000-0x1FFFF : sector 4, 64KB
 *   offset 0x20000+        : sectors 5+, 128KB each
 * For 2MB dual-bank devices, addresses >= 0x08100000 map to bank 2 (sectors 12-23).
 */
static uint32_t FLASH_If_GetSectorNumber(uint32_t Address)
{
  uint32_t offset;
  uint32_t sector;
  uint16_t flashKb = cpuGetFlashSize();

  /* 2MB dual-bank: handle bank 2 */
  if (flashKb > 1024U && Address >= (FLASH_BASE_ADDR + FLASH_BANK2_OFFSET))
  {
    offset = Address - (FLASH_BASE_ADDR + FLASH_BANK2_OFFSET);
    if (offset < SECTOR_64KB) {
      sector = 12U + (offset / SECTOR_16KB);       /* sectors 12-15: 16KB each */
    } else if (offset < (SECTOR_64KB + SECTOR_64KB)) {
      sector = 16U;                                  /* sector 16: 64KB */
    } else {
      sector = 17U + ((offset - (SECTOR_64KB + SECTOR_64KB)) / SECTOR_128KB);
    }
    return sector;
  }

  /* Bank 1 (all devices) */
  offset = Address - FLASH_BASE_ADDR;
  if (offset < SECTOR_64KB) {
    sector = offset / SECTOR_16KB;          /* sectors 0-3: 16KB each */
  } else if (offset < (SECTOR_64KB + SECTOR_64KB)) {
    sector = 4U;                             /* sector 4: 64KB */
  } else {
    sector = 5U + ((offset - (SECTOR_64KB + SECTOR_64KB)) / SECTOR_128KB);
  }
  return sector;
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
