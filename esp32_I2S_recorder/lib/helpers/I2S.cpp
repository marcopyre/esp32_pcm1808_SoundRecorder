#include "I2S.h"
#include <esp_err.h>

void I2S_Init()
{
  i2s_config_t i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
      .sample_rate = SAMPLE_RATE,
      .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
      .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
      .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
      .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
      .dma_buf_count = 16,
      .dma_buf_len = 64,
      .use_apll = false,
      .tx_desc_auto_clear = false,
      .fixed_mclk = 0};

  i2s_pin_config_t pin_config = {
      .mck_io_num = 0,    // MASTER CLOCK(TO PIN 6 SCKI IN PCM1808)
      .bck_io_num = 2,    // BIT CLOCK(TO PIN 8 BCK IN PCM1808)
      .ws_io_num = 15,    // LR CLOCK(TO PIN 7 LRCK IN PCM1808)
      .data_out_num = -1, //(NOT USED)
      .data_in_num = 16   // DATA IN(FROM PIN 9 DOUT IN PCM1808)
  };

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
  i2s_zero_dma_buffer(I2S_NUM_0);
}

int I2S_Read(char *data, int numData)
{
  size_t bytes_read;
  return i2s_read(I2S_NUM_0, (char *)data, numData, &bytes_read, portMAX_DELAY);
}
