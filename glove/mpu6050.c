#include "mpu6050.h"

/**
 * Initializes the MPU6050 unit
 */
void MPU6050_initialize(void) {
  // Reset all internal registers to default values
  PWR_MGMT_1 = 0x80;

  // Disable sleep mode and temperature sensor and use X axis gyroscope as clock
  // source because it's more stable
  PWR_MGMT_1 = 0x09;

  // Set most precise accelerometer range (+- 2g)
  ACCEL_CONFIG = ACCEL_FS_2_CFG;

  // Set most precise gyroscope range (250 deg/s)
  GYRO_CONFIG = GYRO_FS_250_CFG;
}
