/*
 * imu.h
 *
 *  Created on:    21 mar 2018
 *  Author:        Piotr Ziêbiñski
 * 	Description:   Header file containing definitions of IMU's functions and pins
*/

#ifndef IMU_H
#define IMU_H

/* gyroscope registers */
#define CTRL_REG1_G 	0x10
#define STATUS_REG_G	0x17
#define OUT_X_G_LSB 	0x18
#define OUT_X_G_MSB 	0x19
#define OUT_Y_G_LSB 	0x1A
#define OUT_Y_G_MSB 	0x1B
#define OUT_Z_G_LSB 	0x1C
#define OUT_Z_G_MSB 	0x1D

/* accelerometer registers */
#define OUT_X_XL_LSB 	0x28
#define OUT_X_XL_MSB 	0x29
#define OUT_Y_XL_LSB 	0x2A
#define OUT_Y_XL_MSB 	0x2B
#define OUT_Z_XL_LSB 	0x2C
#define OUT_Z_XL_MSB 	0x2D

/* magnetometer registers */
#define CTRL_REG3_M 	0x22
#define STATUS_REG_M	0x27
#define OUT_X_M_LSB 	0x28
#define OUT_X_M_MSB 	0x29
#define OUT_Y_M_LSB 	0x2A
#define OUT_Y_M_MSB 	0x2B
#define OUT_Z_M_LSB 	0x2C
#define OUT_Z_M_MSB 	0x2D

/* thermometer registers 0 */
#define OUT_TEMP_LSB	0x15
#define OUT_TEMP_MSB	0x16

/* devices */
#define GYRO_ACC_TEMP	0x6B
#define MAGNETOMETER 	0x1E

enum IMU_READ_STATUS{
	NO_NEW_DATA,
	READ_ERROR,
	READ_SUCCESS
};

uint16_t magX, magY, magZ;
uint16_t accX, accY, accZ;
uint16_t gyroPitch, gyroRoll, gyroYaw;
uint16_t temp;

/**
 * Initialize IMU's registers
 */
void IMU_Init(void);

/**
 * Read magnetic field's X-, Y- and Z-axis and store
 * them in variables magX, magY, magZ expressed as
 * two's complement. Function returns
 */
enum IMU_READ_STATUS IMU_GetMagneticField(void);

/**
 * Read linear acceleration's X-, Y- and Z-axis and store
 * them in variables magX, magY, magZ expressed as
 * two's complement
 */
enum IMU_READ_STATUS IMU_GetLinearAcceleration(void);

/**
 * Read linear acceleration's X-, Y- and Z-axis and store
 * them in variables magX, magY, magZ expressed as
 * two's complement
 */
enum IMU_READ_STATUS IMU_GetLinearAcceleration(void);

/**
 * Read temperature and store it in variable temp
 * expressed as two's complement
 */
enum IMU_READ_STATUS IMU_GetTemperature(void);


#endif
