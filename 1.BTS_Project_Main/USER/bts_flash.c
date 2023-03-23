#include "bts_flash.h"

	
void BTS_Flash_Erase_Pages(const uint32_t Flash_StartAddr, const uint32_t Flash_EndAddr)
{
	uint32_t EraseCounter;
	uint32_t PageNum = (Flash_EndAddr - Flash_StartAddr) / FMC_PAGE_SIZE;

	/* unlock the flash program/erase controller */
	fmc_unlock();
	/* clear all pending flags */
	fmc_flag_clear(FMC_FLAG_BANK0_END);
	fmc_flag_clear(FMC_FLAG_BANK0_WPERR);
	fmc_flag_clear(FMC_FLAG_BANK0_PGERR);

	/* erase the flash pages */
	for(EraseCounter = 0; EraseCounter < PageNum; EraseCounter++){
			fmc_page_erase(Flash_StartAddr + (FMC_PAGE_SIZE * EraseCounter));
			fmc_flag_clear(FMC_FLAG_BANK0_END);
			fmc_flag_clear(FMC_FLAG_BANK0_WPERR);
			fmc_flag_clear(FMC_FLAG_BANK0_PGERR);
	}

	/* lock the main FMC after the erase operation */
	fmc_lock();
}

void BTS_Flash_Write(const uint32_t FlashAddress,const uint32_t* Data ,const uint32_t DataLength)
{
	/* unlock the flash program/erase controller */
	uint32_t address = FlashAddress;
	uint32_t count_data = 0;
	fmc_unlock();
	for(count_data=0; count_data<DataLength; count_data++)
	{
		fmc_word_program(address, Data[count_data]);
		address += 4;
		fmc_flag_clear(FMC_FLAG_BANK0_END);
		fmc_flag_clear(FMC_FLAG_BANK0_WPERR);
		fmc_flag_clear(FMC_FLAG_BANK0_PGERR);
	}
}

uint32_t BTS_Flash_Read(const uint32_t FlashAddress)
{
	return FMC_READ(FlashAddress);
}
