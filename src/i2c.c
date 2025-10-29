#include "driver/i2c.h"

#include <avr/io.h>
#include <util/twi.h>

#define F_SCL 100000UL  // SCL frequency of 100kHz
#define TWBR_VAL ((((F_CPU / F_SCL) / 1) - 16) / 2)

// Helper function to wait for TWI operation completion
static void i2c_wait(void) { while (!(TWCR & (1 << TWINT))); }

// Helper function to send a start condition
static void i2c_start(void) {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    i2c_wait();
}

// Helper function to send a stop condition
static void i2c_stop(void) { TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN); }

// Helper function to write a byte to the I2C bus
static void i2c_write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    i2c_wait();
}

// Helper function to read a byte from the I2C bus
static uint8_t i2c_read(bool ack) {
    if (ack) {
        TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    } else {
        TWCR = (1 << TWINT) | (1 << TWEN);
    }
    i2c_wait();
    return TWDR;
}

void i2c_setup(void) {
    // Set SCL frequency
    TWSR = 0;  // Prescaler = 1
    TWBR = (uint8_t)TWBR_VAL;
    // Enable TWI
    TWCR = (1 << TWEN);
}

void i2c_sendbyte(uint8_t addr, uint8_t data) {
    i2c_start();
    // Send slave address with write bit
    i2c_write((addr << 1) | TW_WRITE);
    // Send data
    i2c_write(data);
    i2c_stop();
}

void i2c_sendbytes(uint8_t addr, uint8_t* data, size_t len) {
    i2c_start();
    // Send slave address with write bit
    i2c_write((addr << 1) | TW_WRITE);
    // Send data bytes
    for (size_t i = 0; i < len; i++) {
        i2c_write(data[i]);
    }
    i2c_stop();
}

void i2c_receivebyte(uint8_t addr, uint8_t* data) {
    i2c_start();
    // Send slave address with read bit
    i2c_write((addr << 1) | TW_READ);
    // Read data with NACK
    *data = i2c_read(false);
    i2c_stop();
}

void i2c_receivebytes(uint8_t addr, uint8_t* data, size_t len) {
    i2c_start();
    // Send slave address with read bit
    i2c_write((addr << 1) | TW_READ);
    // Read data bytes
    for (size_t i = 0; i < len - 1; i++) {
        data[i] = i2c_read(true);
    }
    // Read last byte with NACK
    data[len - 1] = i2c_read(false);
    i2c_stop();
}
