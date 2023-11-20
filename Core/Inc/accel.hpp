/*
 * accel.h
 *
 *  Created on: Nov 18, 2023
 *      Author: petthepotat
 */

#ifndef INC_ACCEL_HPP_
#define INC_ACCEL_HPP_



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
float AX, AY, AZ;

char buffer[10];

bool ACCEL_ACTIVATED = false;


// ---
void init_accel(I2C_HandleTypeDef*);



void init_accel(I2C_HandleTypeDef *hw){
	uint8_t check;

	// -- check if ready
	// check if hal accelerometer is ready --> yeet to a specific address + wait 100ms
//	result = HAL_I2C_IsDeviceReady(hw, MPUWHO_AM_I_REG, 1, 100);
	HAL_I2C_Mem_Read(hw, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, 100);
	if(check == 0x68){
//		set_speaker_state(true);
		HAL_Delay(100);
//		set_speaker_state(false);

		// idk what this is for but its important
		check = 0;
		HAL_I2C_Mem_Write(hw, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &check, 1, 100);

		check = 0x07;
		HAL_I2C_Mem_Write(hw, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &check, 1, 100);

		check = RS_ACC_4G;
		HAL_I2C_Mem_Write(hw, MPU6050_ADDR, REG_CONFIG_ACC, 1, &check, 1, 100);

//		check = 0x00;
//		HAL_I2C_Mem_Write(hw, MPU6050_ADDR, REG_GYRO_CONFIG, 1, &check, 1, 1000);


//		// configuring the accelerometer
//		uint8_t td = RS_ACC_4G;
////		result = HAL_I2C_Mem_Write(hw, (DEVICE_ADDRESS << 1), REG_CONFIG_ACC, 1, &td, 1, 100);
//        HAL_I2C_Mem_Write(hw, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &td, 1, 50);

        ACCEL_ACTIVATED = true;
	}else{
		// scam

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
//	uint8_t data[2];
//	int16_t x_acc;
//	HAL_I2C_Mem_Read(hw, (DEVICE_ADDRESS << 1) + 1, REG_DATA, 1, data, 2, 100);
//	x_acc = ((int16_t)data[0] << 8) + data[1];
//	printf("x axis acceleration %d \n", x_acc);


	uint8_t recData[6];
	for(int i = 0; i < 6; i++) recData[i] = 0;

	HAL_I2C_Mem_Read(hw, MPU6050_ADDR, ACCEL_XOUT_H_REG, I2C_MEMADD_SIZE_8BIT, recData, 6, 100);
	HAL_Delay(50);

	RAW_AX = (int16_t)(recData[0] << 8 | recData[1]);
	RAW_AY = (int16_t)(recData[2] << 8 | recData[3]);
	RAW_AZ = (int16_t)(recData[4] << 8 | recData[5]);

	AX = (RAW_AX / 16384.0);
	AY = (RAW_AY / 16384.0);
	AZ = (RAW_AZ / 16384.0);
}


#endif /* INC_ACCEL_HPP_ */
