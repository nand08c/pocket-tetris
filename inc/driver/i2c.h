#ifndef __I2C_H__
#define __I2C_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * initializes the i2c interface in the atmega328p
 * */
void i2c_setup(void);

/**
 * send a byte to a device using blocking transmition
 * @param addr address of the device in the i2c line
 * @param data byte to send
 *
 */
void i2c_sendbyte(uint8_t addr, uint8_t data);

/**
 * send an array of bytes using blocking transmition
 * @param addr addr address of the device in the i2c line
 * @param data pointer to an array of bytes
 * @param len size of the array, must be greater than 1
 *
 */
void i2c_sendbytes(uint8_t addr, uint8_t* data, size_t len);

/**
 * receive a byte from a device using blocking transmition
 * @param addr address of the device in the i2c line
 * @param data pointer to a byte to store the received data
 *
 */
void i2c_receivebyte(uint8_t addr, uint8_t* data);

/**
 * receive an array of bytes using blocking transmition
 * @param addr addr address of the device in the i2c line
 * @param data pointer to an array of bytes
 * @param len size of the array, must be greater than 1
 *
 */
void i2c_receivebytes(uint8_t addr, uint8_t* data, size_t len);

#endif /* __I2C_H__ */
