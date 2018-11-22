// This file defines offsets for the register map on the
// MPU-6050 Accelerometer/Gyroscope unit

#ifndef MPU6050_H
#define MPU6050_H

// Default MPU-6050 I2C address
#define MPU6050_ADDR 0x68

// Configuration register offsets
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C

// Power managements offsets
#define PWR_MGMT_1 0x6B
#define PWR_MGMT_2 0x6C

// Interrupt register offsets
#define INT_ENABLE 0x38
#define INT_STATUS 0x3A

// Accelerometer value offsets
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40

// Gyroscope value offsets
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48

// FIFO Value Queue offsets
#define FIFO_EN 0x23  // Controls which values are loaded into FIFO buffer
#define FIFO_COUNTH 0x72
#define FIFO_COUNTL 0x73
#define FIFO_R_W 0x74

// Motion detection status offset
#define MOT_DETECT_STATUS 0x61

// Motion detection threshold configuration offset
#define MOT_DETECT_THR 0x1F;

// I2C ID from MPU unit
#define WHO_AM_I 0x75

// Gyroscope configuration values (deg/s)
#define GYRO_FS_250_CFG 0x00
#define GYRO_FS_500_CFG 0x01
#define GYRO_FS_1000_CFG 0x02
#define GYRO_FS_2000_CFG 0x03

// Accelerometer configuration values (+-g)
#define ACCEL_FS_2_CFG 0x00
#define ACCEL_FS_4_CFG 0x01
#define ACCEL_FS_8_CFG 0x02
#define ACCEL_FS_16_CFG 0x03

// Temperature/external sensor disabled, Gyroscope/Accelerometer enabled
#define DISABLE_TEMP_FIFO_CFG 0x78

// Functions
void MPU6050_initialize(void);

#endif