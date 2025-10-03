#pragma once

#include <Arduino.h>
#include <Adafruit_I2CDevice.h>

#define MPRLS_DEFAULT_ADDR (0x18)
#define MPRLS_READ_TIMEOUT (20)
#define MPRLS_STATUS_POWERED (0x40)
#define MPRLS_STATUS_BUSY (0x20)
#define MPRLS_STATUS_FAILED (0x04)
#define MPRLS_STATUS_MATHSAT (0x01)
#define COUNTS_224 (16777216L)
#define PSI_to_HPA (68.947572932)
#define MPRLS_STATUS_MASK (0b01100101)

class Adafruit_MPRLS {
public:
  Adafruit_MPRLS(int8_t reset_pin = -1, int8_t EOC_pin = -1,
                 uint16_t PSI_min = 0, uint16_t PSI_max = 25,
                 float OUTPUT_min = 10, float OUTPUT_max = 90,
                 float K = PSI_to_HPA);

  bool begin(uint8_t i2c_addr = MPRLS_DEFAULT_ADDR, TwoWire *twoWire = &Wire);
  uint8_t readStatus(void);
  float readPressure(void);

  uint8_t lastStatus;

private:
  Adafruit_I2CDevice *i2c_dev = NULL;
  uint32_t readData(void);

  int8_t _reset, _eoc;
  uint16_t _PSI_min, _PSI_max;
  uint32_t _OUTPUT_min, _OUTPUT_max;
  float _K;
};
