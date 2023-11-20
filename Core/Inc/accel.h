/*
 * accel.h
 *
 *  Created on: Nov 18, 2023
 *      Author: petthepotat
 */

#ifndef INC_ACCEL_H_
#define INC_ACCEL_H_


#include "stdlib.h"
#include "stdio.h"
#include "i2c.h"
#include "gpio.h"

#define MPU6050_ADDR 0xD0
#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_XOUT_H_REG 0x43
#define PWR_MGMT_1_REG 0x6B
#define WHO_AM_I_REG 0X75
#define DEVICE_ADDRESS 0x68


#define REG_CONFIG_GYRO 27
#define REG_CONFIG_ACC 28
#define REG_DATA 59

#define RS_GYRO_250 0
#define RS_GYRO_500 8
#define RS_ACC_2G 0
#define RS_ACC_4G 8




extern I2C_HandleTypeDef hi2c1;

int16_t RAW_AX, RAW_AY, RAW_AZ;
int16_t AX, AY, AZ;

char buffer[10];


// ---
void init_accel(I2C_HandleTypeDef*);



void init_accel(I2C_HandleTypeDef *hw){
	HAL_StatusTypeDef result;

	// -- check if ready
	// check if hal accelerometer is ready --> yeet to a specific address + wait 100ms
	result = HAL_I2C_IsDeviceReady(hw, (DEVICE_ADDRESS << 1), 1, 100);
	if(result == HAL_OK){
		printf("The device is ready \n");
	}else{
		printf("The device is not ready \n");
	}

	// configuring the accelerometer
	uint8_t td = RS_ACC_4G;
	result = HAL_I2C_Mem_Write(hw, (DEVICE_ADDRESS << 1), REG_CONFIG_ACC, 1, &td, 1, 100);
	if(result == HAL_OK){
		printf("Writing to register 28\n");
	}else{
		printf("Failed to configure accel \n");
	}

//	// configuring the gyro
//	td = FS_GYRO_500;
//	result = HAL_I2C_Mem_Write(hw, (DEVICE_ADDRESS << 1), REG_CONFIG_GYRO, 1, &td, 1, 100);
//	if(result == HAL_OK){
//		printf("Writing to register 28\n");
//	}else{
//		printf("Failed to write\n");
//	}

}

void read_accel(I2C_HandleTypeDef *hw){
	uint8_t data[2];
	int16_t x_acc;
	HAL_I2C_Mem_Read(hw, (DEVICE_ADDRESS << 1) + 1, REG_DATA, 1, data, 2, 100);
	x_acc = ((int16_t)data[0] << 8) + data[1];
	printf("x axis acceleration %d \n", x_acc);
}




#endif /* INC_ACCEL_H_ */
