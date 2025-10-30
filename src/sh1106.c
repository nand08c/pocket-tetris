
#include "driver/sh1106.h"

#include "driver/i2c.h"

#define SH1106_I2C_ADDR 0x3C

static uint64_t canvas[CANVAS_LEN];

void sh1106_setup(void) {
    const uint8_t init_commands[] = {
        0x00,        // Control byte for commands
        0xAE,        // Set Display OFF
        0xD5, 0x80,  // Set Display Clock Divide Ratio/Oscillator Frequency
        0xA8, 0x3F,  // Set Multiplex Ratio
        0xD3, 0x00,  // Set Display Offset
        0x40,        // Set Display Start Line
        0x8D, 0x14,  // Set Charge Pump Setting
        0x20, 0x02,  // Set Memory Addressing Mode
        0xA1,        // Set Segment Re-map
        0xC8,        // Set COM Output Scan Direction
        0xDA, 0x12,  // Set COM Pins Hardware Configuration
        0x81, 0xCF,  // Set Contrast Control
        0xD9, 0xF1,  // Set Pre-charge Period
        0xDB, 0x40,  // Set VCOM Deselect Level
        0xA4,        // Entire Display ON/OFF
        0xA6,        // Set Normal/Inverse Display
        0xAF         // Set Display ON
    };
    i2c_sendbytes(SH1106_I2C_ADDR, init_commands, sizeof(init_commands));
}

void sh1106_canvas_clear(void) {
    for (int i = 0; i < CANVAS_LEN; i++) {
        canvas[i] = 0;
    }
}

void sh1106_canvas_update(void) {
    uint8_t command_buffer[2];
    uint8_t data_buffer[CANVAS_LEN + 1];  // +1 for the control byte

    for (uint8_t page = 0; page < 8; page++) {
        // Set page address
        command_buffer[0] = 0x00;  // Control byte for command
        command_buffer[1] = 0xB0 | page;
        i2c_sendbytes(SH1106_I2C_ADDR, command_buffer, sizeof(command_buffer));

        // Set lower column start address (0x00)
        command_buffer[0] = 0x00;
        command_buffer[1] = 0x00;
        i2c_sendbytes(SH1106_I2C_ADDR, command_buffer, sizeof(command_buffer));

        // Set higher column start address (0x10)
        command_buffer[0] = 0x00;
        command_buffer[1] = 0x10;
        i2c_sendbytes(SH1106_I2C_ADDR, command_buffer, sizeof(command_buffer));

        // Prepare data buffer
        data_buffer[0] = 0x40;  // Control byte for data
        for (uint8_t col = 0; col < CANVAS_LEN; col++) {
            data_buffer[col + 1] =
                (uint8_t)((canvas[col] >> (page * 8)) & 0xFF);
        }
        i2c_sendbytes(SH1106_I2C_ADDR, data_buffer, sizeof(data_buffer));
    }
}

uint64_t* sh1106_get_canvas(void) { return canvas; }
