/*
 * i2c3.h
 *
 *  Created on:    23 mar 2018
 *  Author:        Piotr Ziêbiñski
 * 	Description:   Header file containing definitions of functions
 * 				   and constants for I2C.
*/
#ifndef I2C_H
#define I2C_H

#include "stm32l4xx_hal.h"

#define I2C3_PORT GPIOC
#define I2C3_SCL_PIN GPIO_PIN_0
#define I2C3_SDA_PIN GPIO_PIN_1
#define I2C3_TIMEOUT 1000
#define I2C3_ADDRESS 0x33		//might be wrong TODO

uint8_t i2c3Error;	//i2c error flag

/**
 * Set up I2C3 and GPIOs for communication with IMU
 */
void I2C3_Init(void);

/**
 * Write data to specified register of a device using I2C3
 */
void I2C3_WriteMemory(uint16_t reg, uint16_t device, uint8_t data);

/**
 * Read data from register of a device using I2C3
 */
uint8_t I2C3_ReadMemory(uint16_t reg, uint16_t device);


#endif
