/*
 * ProgMem.c
 *
 *  Created on: Oct 9, 2025
 *      Author: Dima
 *      В этом файле содержатся функции для записи данных в FLASH память.
 *


 */


#include "ProgMem.h"
#include "PalenishIT_Proc.h"
#include "stm32f1xx_hal.h"






// Функция для чтения настроек из Flash
void read_config_from_flash(ProgMemStruct* config) {
    // Просто копируем данные по указателю
    *config = *(ProgMemStruct*)EndPage;
}
/*
 * Функция записи данных в FLASH память.
 */

HAL_StatusTypeDef write_config_to_flash(ProgMemStruct* config) {
	HAL_StatusTypeDef status;

	    // 1. Разблокировать Flash
	status = HAL_FLASH_Unlock();
    if (status != HAL_OK) {
    	return status;
	}

    // 2. Стереть страницу
    FLASH_EraseInitTypeDef erase_init;
    erase_init.TypeErase = FLASH_TYPEERASE_PAGES;
    erase_init.PageAddress = EndPage;
    erase_init.NbPages = 1;

    uint32_t page_error = 0;
    status = HAL_FLASHEx_Erase(&erase_init, &page_error);
    if (status != HAL_OK) {
        HAL_FLASH_Lock();
        return status;
    }

    // 3. Запрограммировать данные
    // Записываем по 32 бита (4 байта) за раз
    uint32_t* data_ptr = (uint32_t*)config;
    for (uint32_t i = 0; i < sizeof(ProgMemStruct) / 4; i++) {
        status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, EndPage + (i * 4), data_ptr[i]);
        if (status != HAL_OK) {
            HAL_FLASH_Lock();
            return status;
        }
    }

    // 4. Заблокировать Flash
    HAL_FLASH_Lock();

    return HAL_OK;
}

/*
 * Function for initializing values ​​from memory.
 */
void StartInitCalValues(CalibrStruct *CalibrValues){

	ProgMemStruct config;
	uint32_t i = 0;
	InitADCStick(&hadc1);
	//read the structure and check the key.
	read_config_from_flash(&config);
	// if the key matches, then the memory structure is correct, I read from there.
	if(config.KeySt == Key){
		while(i<4){
			CalibrValues->CalibrValMax[i] = config.CalibrValues.CalibrValMax[i];
			CalibrValues->CalibrValMin[i] = config.CalibrValues.CalibrValMin[i];
			Adc1Null[i] = config.CalibrValues.Adc1NULL[i];
			i++;
		}
	}
	// If not, I write the default values.
	else{
		CalibrStartInit(CalibrValues);
	}
}

/*
 * Функция очистки памяти. Например посли неудачной калибровки.
 */
HAL_StatusTypeDef ClearProgMem(){
	ProgMemStruct config;
	HAL_StatusTypeDef status;

	read_config_from_flash(&config);


	 // 1. Разблокировать Flash
	status = HAL_FLASH_Unlock();
	if (status != HAL_OK) {
		return status;
	}
	  // 2. Стереть страницу
	FLASH_EraseInitTypeDef erase_init;
	erase_init.TypeErase = FLASH_TYPEERASE_PAGES;
	erase_init.PageAddress = EndPage;
	erase_init.NbPages = 1;

	uint32_t page_error = 0;
	status = HAL_FLASHEx_Erase(&erase_init, &page_error);
	if (status != HAL_OK) {
	   HAL_FLASH_Lock();
	   return status;
	}
	HAL_FLASH_Lock();
	return HAL_OK;
}




