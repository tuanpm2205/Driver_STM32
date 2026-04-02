#ifndef __L3GD20
#define __L3GD20

#include <stm32f4xx.h>
#include <stdint.h>

//Config

#define L3GD20_SPI &hspi1

#define L3GD20_CS_PORT GPIOE
#define L3GD20_CS_PIN GPIO_PIN_3

/* L3GD20 Register Address Definitions */
#define L3GD20_WHO_AM_I      0x0F

#define L3GD20_CTRL_REG1     0x20
#define L3GD20_CTRL_REG2     0x21
#define L3GD20_CTRL_REG3     0x22
#define L3GD20_CTRL_REG4     0x23
#define L3GD20_CTRL_REG5     0x24

#define L3GD20_REFERENCE     0x25
#define L3GD20_OUT_TEMP      0x26
#define L3GD20_STATUS_REG    0x27

#define L3GD20_OUT_X_L       0x28
#define L3GD20_OUT_X_H       0x29
#define L3GD20_OUT_Y_L       0x2A
#define L3GD20_OUT_Y_H       0x2B
#define L3GD20_OUT_Z_L       0x2C
#define L3GD20_OUT_Z_H       0x2D

#define L3GD20_FIFO_CTRL_REG 0x2E
#define L3GD20_FIFO_SRC_REG  0x2F

#define L3GD20_INT1_CFG      0x30
#define L3GD20_INT1_SRC      0x31
#define L3GD20_INT1_THS_XH   0x32
#define L3GD20_INT1_THS_XL   0x33
#define L3GD20_INT1_THS_YH   0x34
#define L3GD20_INT1_THS_YL   0x35
#define L3GD20_INT1_THS_ZH   0x36
#define L3GD20_INT1_THS_ZL   0x37
#define L3GD20_INT1_DURATION 0x38


void L3GD20_CS_SET(void);
void L3GD20_CS_RESET(void);

void L3GD20_WriteReg(uint8_t reg, uint8_t data);
uint8_t L3GD20_ReadReg(uint8_t reg);
void L3GD20_ReadMulti(uint8_t reg, uint8_t *buffer, uint8_t length);	

// --- Prototypes cho Gyroscope ---
void L3GD20_Init(void);
void L3GD20_ReadRaw(int16_t *gx, int16_t *gy, int16_t *gz);
void L3GD20_ReadGyro(int16_t *gx, int16_t *gy, int16_t *gz, float *Gx, float *Gy, float *Gz);

#endif