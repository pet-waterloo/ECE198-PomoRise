/*
 * Accelerometer.cpp
 *
 *  Created on: Nov 20, 2023
 *      Author: petthepotat
 */

#pragma once
#include <Accelerometer.h>

Accelerometer::Accelerometer(I2C_HandleTypeDef* accel) : RAW_AX(0), RAW_AY(0), RAW_AZ(0), AX(0), AY(0), AZ(0), active(false){
	// TODO Auto-generated constructor stub
	this->accel = accel;
}

Accelerometer::~Accelerometer() {
	// TODO Auto-generated destructor stub
	for(int i = 0; i < 10; i++) this->buffer[i] = 0;
}


void Accelerometer::init(){
	// check if ready
	uint8_t check;
	HAL_I2C_Mem_Read(this->accel, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, 100);
	if(check == 0x68){
		// setting parameters for each section
		check = 0;
		HAL_I2C_Mem_Write(this->accel, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &check, 1, 100);

		check = 0x07;
		HAL_I2C_Mem_Write(this->accel, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &check, 1, 100);

		check = RS_ACC_4G;
		HAL_I2C_Mem_Write(this->accel, MPU6050_ADDR, REG_CONFIG_ACC, 1, &check, 1, 100);

		this->active = true;
	}
}

void Accelerometer::read(){
	// clear cache
	uint8_t recData[6];
	for(int i = 0; i < 6; i++) recData[i] = 0;

	HAL_I2C_Mem_Read(this->accel, MPU6050_ADDR, ACCEL_XOUT_H_REG, I2C_MEMADD_SIZE_8BIT, recData, 6, 100);
	HAL_Delay(10);

	RAW_AX = (int16_t)(recData[0] << 8 | recData[1]);
	RAW_AY = (int16_t)(recData[2] << 8 | recData[3]);
	RAW_AZ = (int16_t)(recData[4] << 8 | recData[5]);

	AX = (RAW_AX / 16384.0);
	AY = (RAW_AY / 16384.0);
	AZ = (RAW_AZ / 16384.0);
}

double Accelerometer::get_x(){
	return AX;
}

double Accelerometer::get_y(){
	return AY;
}

double Accelerometer::get_z(){
	return AZ;
}

bool Accelerometer::is_active(){
	return this->active;
}


