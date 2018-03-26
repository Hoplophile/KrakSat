/*
 * i2c3.h
 *
 *  Created on:    23 mar 2018
 *  Author:        Piotr Ziêbiñski
 * 	Description:   File contains constants and functions
 * 				   allowing to use I2C for communication.
*/
#include "i2c3.h"
#include "stm32l4xx_hal.h"

void I2C3_Init(){
	i2c3Error = 0;

	I2C_InitTypeDef I2C_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;

	__GPIOC_CLK_ENABLE();

	/* Initialize SCL (PC0) pin */
	GPIO_InitStruct.Pin = I2C3_SCL_PIN;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
	HAL_GPIO_Init(I2C3_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(I2C3_PORT, I2C3_SCL_PIN, GPIO_PIN_SET);

	/* Initialize SDA (PC1) pin */
	GPIO_InitStruct.Pin = I2C3_SDA_PIN;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
	HAL_GPIO_Init(I2C3_PORT, &GPIO_InitStruct);
	HAL_GPIO_WritePin(I2C3_PORT, I2C3_SDA_PIN, GPIO_PIN_SET);

	/* Initialize I2C3 */
	I2C_InitStruct.OwnAddress1 = I2C3_ADDRESS;
	I2C_InitStruct.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2C_InitStruct.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	I2C_InitStruct.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2C_InitStruct.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	I2C_HandleTypeDef I2C_HandleStruct;
	I2C_HandleStruct.Init = I2C_InitStruct;
	I2C_HandleStruct.Mode = HAL_I2C_MODE_MASTER;
	HAL_I2C_Init(&I2C_HandleStruct);
	HAL_I2C_MspInit(&I2C_HandleStruct);

	//TODO check if device is ready for communication

} /* I2C3_Init */

void I2C3_WriteMemory(uint16_t reg, uint16_t device, uint8_t data){
	i2c3Error = 0;

	I2C_InitTypeDef I2C_InitStruct;
	I2C_InitStruct.OwnAddress1 = I2C3_ADDRESS;
	I2C_InitStruct.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2C_InitStruct.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	I2C_InitStruct.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2C_InitStruct.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	I2C_HandleTypeDef I2C_HandleStruct;
	I2C_HandleStruct.Init = I2C_InitStruct;

	uint8_t dataSize = sizeof(data);

	HAL_StatusTypeDef HAL_Status = HAL_I2C_Mem_Write(&I2C_HandleStruct, device << 1, reg, 16, &data, dataSize, I2C3_TIMEOUT);

	if(HAL_Status == HAL_ERROR){
		i2c3Error = 1;
	}
}

uint8_t I2C3_ReadMemory(uint16_t reg, uint16_t device){
	i2c3Error = 0;

	I2C_InitTypeDef I2C_InitStruct;
	I2C_InitStruct.OwnAddress1 = I2C3_ADDRESS;
	I2C_InitStruct.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2C_InitStruct.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	I2C_InitStruct.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2C_InitStruct.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	I2C_HandleTypeDef I2C_HandleStruct;
	I2C_HandleStruct.Init = I2C_InitStruct;

	uint8_t data;

	HAL_StatusTypeDef HAL_Status = HAL_I2C_Mem_Read(&I2C_HandleStruct, device << 1, reg, 16, &data, 8, I2C3_TIMEOUT);

	if(HAL_Status == HAL_ERROR){
		i2c3Error = 1;
		return 0;
	} else {
		return data;
	}
}
