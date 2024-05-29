#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "esp_system.h"
#define SAMPLE_RATE (44100)
#define PIN_I2S_BCLK 26
#define PIN_I2S_LRC 22
#define PIN_I2S_DIN 34
#define PIN_I2S_DOUT -1

void I2S_Init();

/// I2S_Read()
/// @parameter data: pointer to buffer
/// @parameter numData: buffer size
/// @return Number of bytes read
int I2S_Read(char *data, int numData);