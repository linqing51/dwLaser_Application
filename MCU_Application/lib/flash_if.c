/**
  ******************************************************************************
  * @file    flash_if.c
  * @brief   Flash layer functions - generic for STM32F1 and STM32F4 series
  *          F4: 256KB(F401), 512KB(F411/446), 1MB(F405/407/412/413/423),
  *              2MB dual-bank(F439/469/479)
  *          F1: 64KB~1MB (F101/F102/F103/F105/F107, 1KB/2KB page erase)
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
#define FLASH_BANK2_OFFSET    0x00100000U  /* 2MB devices (F439/469/479): bank2 starts at 0x08100000 */
#define FLASH_BANK2_OFFSET_1MB 0x00080000U /* 1MB dual-bank (F413/F423): bank2 starts at 0x08080000 */
#define SECTOR_16KB           0x4000U
#define SECTOR_64KB           0x10000U
#define SECTOR_128KB          0x20000U

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
  __HAL_FLASH_CLEAR_FLAG(FLASH_IF_ALL_CLEAR_FLAGS);
}

uint32_t FLASH_If_EraseApplication(void){
	FLASH_If_Prepare();
	FirstSector = FLASH_If_GetSectorNumber(APPLICATION_FLASH_START_ADDRESS);
	NbOfSectors = FLASH_If_GetSectorNumber((FLASH_If_GetFlashEndAddr() - 4)) - FirstSector + 1;
#if defined(STM32F1xx)
	/* F1: 按页擦除, PageAddress为起始地址(页对齐), NbPages为页数 */
	FLASH_EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	FLASH_EraseInitStruct.PageAddress = APPLICATION_FLASH_START_ADDRESS;
	FLASH_EraseInitStruct.NbPages = NbOfSectors;
#else
	FLASH_EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
	FLASH_EraseInitStruct.Sector = FirstSector;
	FLASH_EraseInitStruct.NbSectors = NbOfSectors;
	FLASH_EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
#endif
	if(HAL_FLASHEx_Erase(&FLASH_EraseInitStruct, &SectorError) != HAL_OK){
		return (1);
	}
	return (0);
}

uint32_t FLASH_If_EraseBootload(void){
	FLASH_If_Prepare();
	FirstSector = FLASH_If_GetSectorNumber(BOOTLOADER_FLASH_START_ADDRESS);
	NbOfSectors = FLASH_If_GetSectorNumber((BOOTLOADER_FLASH_END_ADDRESS - 4)) - FirstSector + 1;
#if defined(STM32F1xx)
	/* F1: 按页擦除, PageAddress为起始地址(页对齐), NbPages为页数 */
	FLASH_EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	FLASH_EraseInitStruct.PageAddress = BOOTLOADER_FLASH_START_ADDRESS;
	FLASH_EraseInitStruct.NbPages = NbOfSectors;
#else
	FLASH_EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
	FLASH_EraseInitStruct.Sector = FirstSector;
	FLASH_EraseInitStruct.NbSectors = NbOfSectors;
	FLASH_EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
#endif
	if(HAL_FLASHEx_Erase(&FLASH_EraseInitStruct, &SectorError) != HAL_OK){
		return (1);
	}
	return (0);
}

uint32_t FLASH_If_Read(uint32_t Address)
{
  /* Flash可像内存一样直接读取(F1/F4全系列); 调用方需保证地址在有效Flash范围内 */
  return (*(__IO uint32_t *)Address);
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
 * Returns the erase-unit index of an address:
 *   F1: page number  (page size = FLASH_PAGE_SIZE, 1KB or 2KB per chip density)
 *   F4: sector number, per-device layout:
 *     单bank(0-11): F405/407/415/417/412 (16KB*4 + 64KB + 128KB*7)
 *     1MB双bank(0-15): F413/F423 - bank1 0x08000000-0x0807FFFF (0-7),
 *                        bank2 0x08080000-0x080FFFFF (8-15); 每bank 16KB*4+64KB+128KB*3
 *     2MB双bank(0-23): F439/469/479 - bank1 0x08000000-0x080FFFFF (0-11),
 *                        bank2 0x08100000-0x081FFFFF (12-23)
 */
static uint32_t FLASH_If_GetSectorNumber(uint32_t Address)
{
#if defined(STM32F1xx)
  /* F1: 页号 = 偏移 / 页大小(1KB小容量/2KB大容量, 由HAL按器件定义) */
  return (Address - FLASH_BASE_ADDR) / FLASH_PAGE_SIZE;
#elif defined(STM32F413xx) || defined(STM32F423xx)
  /* 1MB双bank(F413/F423): bank2起始0x08080000, 每bank 8扇区(扇区号连续0-15) */
  uint32_t offset;
  uint32_t sector;

  if (Address >= (FLASH_BASE_ADDR + FLASH_BANK2_OFFSET_1MB))
  {
    offset = Address - (FLASH_BASE_ADDR + FLASH_BANK2_OFFSET_1MB);
    if (offset < SECTOR_64KB) {
      sector = 8U + (offset / SECTOR_16KB);        /* sectors 8-11: 16KB each */
    } else if (offset < (SECTOR_64KB + SECTOR_64KB)) {
      sector = 12U;                                 /* sector 12: 64KB */
    } else {
      sector = 13U + ((offset - (SECTOR_64KB + SECTOR_64KB)) / SECTOR_128KB);
    }
    return sector;
  }
  /* F413/F423 bank1: sectors 0-7 */
  offset = Address - FLASH_BASE_ADDR;
  if (offset < SECTOR_64KB) {
    sector = offset / SECTOR_16KB;                  /* sectors 0-3: 16KB each */
  } else if (offset < (SECTOR_64KB + SECTOR_64KB)) {
    sector = 4U;                                     /* sector 4: 64KB */
  } else {
    sector = 5U + ((offset - (SECTOR_64KB + SECTOR_64KB)) / SECTOR_128KB);
  }
  return sector;
#else
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
#endif
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
