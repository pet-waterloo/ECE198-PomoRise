/*
 * Accelerometer.h
 *
 *  Created on: Nov 20, 2023
 *      Author: petthepotat
 */

#ifndef INC_ACCELEROMETER_H_
#define INC_ACCELEROMETER_H_


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



class Accelerometer {
private:
	bool active;
	I2C_HandleTypeDef* accel;

	int16_t RAW_AX, RAW_AY, RAW_AZ;
	float AX, AY, AZ;

	char buffer[10];

public:
	Accelerometer(I2C_HandleTypeDef*);
	virtual ~Accelerometer();

	void init();
	void read();

	double get_x();
	double get_y();
	double get_z();

	bool is_active();

};

#endif /* INC_ACCELEROMETER_H_ */
