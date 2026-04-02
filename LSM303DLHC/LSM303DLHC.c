#include <LSM303DLHC.h>

extern I2C_HandleTypeDef hi2c1;

void LSM303_WriteReg(uint8_t devAddr, uint8_t reg, uint8_t data){
	uint8_t temp[2];
	temp[0] = reg;
	temp[1] = data;
	HAL_I2C_Master_Transmit(LSM303DLHC_I2C, devAddr, temp, 2, 100);
}

uint8_t LSM303_ReadReg(uint8_t devAddr, uint8_t reg){
	uint8_t data;
	HAL_I2C_Master_Transmit(LSM303DLHC_I2C, devAddr, &reg, 1, 100);
	HAL_I2C_Master_Receive(LSM303DLHC_I2C, devAddr, &data, 1, 100);
	return data;
}

void LSM303_ReadMulti(uint8_t devAddr, uint8_t reg, uint8_t *buffer, uint8_t length){
	uint8_t temp = reg | (1 << 7);
	HAL_I2C_Master_Transmit(LSM303DLHC_I2C, devAddr, &temp, 1, 100);
	HAL_I2C_Master_Receive(LSM303DLHC_I2C, devAddr, buffer, length, 1000);
}

void LSM303_Accel_Init(void){
	LSM303_WriteReg(LSM303DLHC_SLAVE_ADDRESS, CTRL_REG1_A, 0x97);
	LSM303_WriteReg(LSM303DLHC_SLAVE_ADDRESS, CTRL_REG2_A, 0x00);
	LSM303_WriteReg(LSM303DLHC_SLAVE_ADDRESS, CTRL_REG3_A, 0x00);
	LSM303_WriteReg(LSM303DLHC_SLAVE_ADDRESS, CTRL_REG4_A, 0x88);
	LSM303_WriteReg(LSM303DLHC_SLAVE_ADDRESS, CTRL_REG5_A, 0x00);
	LSM303_WriteReg(LSM303DLHC_SLAVE_ADDRESS, CTRL_REG6_A, 0x00);
}

void LSM303_ReadAccelRaw(int16_t *ax, int16_t *ay, int16_t *az){
	uint8_t temp[2];
	LSM303_ReadMulti(LSM303DLHC_SLAVE_ADDRESS, OUT_X_L_A, temp, 2);
	*ax = ((uint16_t)temp[1] << 8) | temp[0];
	
	LSM303_ReadMulti(LSM303DLHC_SLAVE_ADDRESS, OUT_Y_L_A, temp, 2);
	*ay = ((uint16_t)temp[1] << 8) | temp[0];

	LSM303_ReadMulti(LSM303DLHC_SLAVE_ADDRESS, OUT_Z_L_A, temp, 2);
	*az = ((uint16_t)temp[1] << 8) | temp[0];
}

void LSM303_ReadAccel(int16_t *ax, int16_t *ay, int16_t *az, float *Ax, float *Ay, float *Az){
	*Ax = (float)(*ax >> 4)/1000.0;
	*Ay = (float)(*ay >> 4)/1000.0;
	*Az = (float)(*az >> 4)/1000.0;
}