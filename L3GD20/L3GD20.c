#include <L3GD20.h>

extern SPI_HandleTypeDef hspi1;

void L3GD20_CS_SET(void){
	HAL_GPIO_WritePin(L3GD20_CS_PORT, L3GD20_CS_PIN, 1);
}
void L3GD20_CS_RESET(void){
	HAL_GPIO_WritePin(L3GD20_CS_PORT, L3GD20_CS_PIN, 0);
}

void L3GD20_WriteReg(uint8_t reg, uint8_t data){
	uint8_t temp[2];
	temp[0]=reg;
	temp[1]=data;
	L3GD20_CS_RESET();
	HAL_SPI_Transmit(L3GD20_SPI, temp, 2, 100);
	L3GD20_CS_SET();
}

uint8_t L3GD20_ReadReg(uint8_t reg){
	uint8_t data;
	uint8_t temp = reg | (1 << 7);
	L3GD20_CS_RESET();
	HAL_SPI_Transmit(L3GD20_SPI, &temp, 1, 100);
	HAL_SPI_Receive(L3GD20_SPI, &data, 1, 100);
	L3GD20_CS_SET();
	return data;
}

void L3GD20_ReadMulti(uint8_t reg, uint8_t *buffer, uint8_t length){
	uint8_t temp = reg | (0b11 << 6);
	L3GD20_CS_RESET();
	HAL_SPI_Transmit(L3GD20_SPI, &temp, 1, 100);
	HAL_SPI_Receive(L3GD20_SPI, buffer, length, 1000);
	L3GD20_CS_SET();
}

void L3GD20_Init(void){
	L3GD20_WriteReg(L3GD20_CTRL_REG1, 0xFF);
	L3GD20_WriteReg(L3GD20_CTRL_REG2, 0x00);
	L3GD20_WriteReg(L3GD20_CTRL_REG3, 0x00);
	L3GD20_WriteReg(L3GD20_CTRL_REG4, 0x30);
	L3GD20_WriteReg(L3GD20_CTRL_REG5, 0x00);
}
void L3GD20_ReadRaw(int16_t *gx, int16_t *gy, int16_t *gz){
	uint8_t temp[2];
	L3GD20_ReadMulti(L3GD20_OUT_X_L, temp, 2);
	*gx = ((int16_t)temp[1] << 8) | temp[0];
	L3GD20_ReadMulti(L3GD20_OUT_Y_L, temp, 2);
	*gy = ((int16_t)temp[1] << 8) | temp[0];
	L3GD20_ReadMulti(L3GD20_OUT_Z_L, temp, 2);
	*gz = ((int16_t)temp[1] << 8) | temp[0];
}
void L3GD20_ReadGyro(int16_t *gx, int16_t *gy, int16_t *gz, float *Gx, float *Gy, float *Gz){
	*Gx = (*gx)*0.070f;
	*Gy = (*gy)*0.070f;
	*Gz = (*gz)*0.070f;
}