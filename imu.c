/*
 * imu.c
 *
 *  Created on:    21 mar 2018
 *  Author:        Piotr Ziêbiñski
 * 	Description:   File contains constants and functions
 * 				   correlated with IMU's setup and actions
*/

#include "stm32l4xx_hal.h"
#include "i2c3.h"
#include "imu.h"

void IMU_Init(void){
	magX = magY = magZ = 0;

	I2C3_WriteMemory(CTRL_REG1_G, GYRO_ACC_TEMP, (1<<5));
	I2C3_WriteMemory(CTRL_REG3_M, MAGNETOMETER, 0);
}

enum IMU_READ_STATUS IMU_GetMagneticField(){

	uint8_t dataStatus = I2C3_ReadMemory(STATUS_REG_M, MAGNETOMETER);

	if (i2c3Error == 1) {
		i2c3Error = 0;
		return READ_ERROR;
	}
	else if((dataStatus & (1 << 1)) == 0) {
		return NO_NEW_DATA;
	}
	else {
		magX = I2C3_ReadMemory(OUT_X_M_MSB, MAGNETOMETER) << 8;
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}
		magX = magX | I2C3_ReadMemory(OUT_X_M_LSB, MAGNETOMETER);
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}

		magY = I2C3_ReadMemory(OUT_Y_M_MSB, MAGNETOMETER) << 8;
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}
		magY = magY | I2C3_ReadMemory(OUT_Y_M_LSB, MAGNETOMETER);
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}

		magZ = I2C3_ReadMemory(OUT_Z_M_MSB, MAGNETOMETER) << 8;
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}
		magZ = magZ | I2C3_ReadMemory(OUT_Z_M_LSB, MAGNETOMETER);
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}

		return READ_SUCCESS;
	}
}

enum IMU_READ_STATUS IMU_GetLinearAcceleration(){

	uint8_t dataStatus = I2C3_ReadMemory(STATUS_REG_G, GYRO_ACC_TEMP);

	if (i2c3Error == 1) {
		i2c3Error = 0;
		return READ_ERROR;
	}
	else if((dataStatus & (1 << 1)) == 0) {
		return NO_NEW_DATA;
	}
	else {
		accX = I2C3_ReadMemory(OUT_X_XL_MSB, GYRO_ACC_TEMP) << 8;
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}
		accX = accX | I2C3_ReadMemory(OUT_X_XL_LSB, GYRO_ACC_TEMP);
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}

		accY = I2C3_ReadMemory(OUT_Y_XL_MSB, GYRO_ACC_TEMP) << 8;
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}
		accY = accY | I2C3_ReadMemory(OUT_Y_XL_LSB, GYRO_ACC_TEMP);
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}

		accZ = I2C3_ReadMemory(OUT_Z_XL_MSB, GYRO_ACC_TEMP) << 8;
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}
		accZ = accZ | I2C3_ReadMemory(OUT_Z_XL_LSB, GYRO_ACC_TEMP);
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}

		return READ_SUCCESS;
	}
}

enum IMU_READ_STATUS IMU_GetAngularAcceleration(){

	uint8_t dataStatus = I2C3_ReadMemory(STATUS_REG_G, GYRO_ACC_TEMP);

	if (i2c3Error == 1) {
		i2c3Error = 0;
		return READ_ERROR;
	}
	else if((dataStatus & (1 << 1)) == 0) {
		return NO_NEW_DATA;
	}
	else {
		gyroPitch = I2C3_ReadMemory(OUT_X_G_MSB, GYRO_ACC_TEMP) << 8;
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}
		gyroPitch = gyroPitch | I2C3_ReadMemory(OUT_X_G_LSB, GYRO_ACC_TEMP);
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}

		gyroRoll = I2C3_ReadMemory(OUT_Y_G_MSB, GYRO_ACC_TEMP) << 8;
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}
		gyroRoll = gyroRoll | I2C3_ReadMemory(OUT_Y_G_LSB, GYRO_ACC_TEMP);
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}

		gyroYaw = I2C3_ReadMemory(OUT_Z_G_MSB, GYRO_ACC_TEMP) << 8;
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}
		gyroYaw = gyroYaw | I2C3_ReadMemory(OUT_Z_G_LSB, GYRO_ACC_TEMP);
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}

		return READ_SUCCESS;
	}
}

enum IMU_READ_STATUS IMU_GetTemperature(){

	uint8_t dataStatus = I2C3_ReadMemory(STATUS_REG_G, GYRO_ACC_TEMP);

	if (i2c3Error == 1) {
		i2c3Error = 0;
		return READ_ERROR;
	}
	else if((dataStatus & (1 << 2)) == 0) {
		return NO_NEW_DATA;
	}
	else {
		temp = I2C3_ReadMemory(OUT_TEMP_MSB, GYRO_ACC_TEMP) << 8;
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}
		temp = temp | I2C3_ReadMemory(OUT_TEMP_LSB, GYRO_ACC_TEMP);
		if(i2c3Error == 1){
			i2c3Error = 0;
			return READ_ERROR;
		}
		return READ_SUCCESS;
	}
}
