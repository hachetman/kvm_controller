#ifndef __I2C_DDC_H_
#define __I2C_DDC_H_

#include <Arduino.h>
#include <Wire.h>

class ddc {
  // user-accessible "public" interface
public:
  ddc(void);
  int get_display_channel(void);
  void set_display_channel(int channel);

private:
  const byte read_cmd[5] = {0x51, 0x82, 0x01, 0x60, 0xdc};
  const byte dp_cmd[7] = {0x51, 0x84, 0x03, 0x60, 0x00, 0x0f, 0xd7};
  const byte mdp_cmd[7] = {0x51, 0x84, 0x03, 0x60, 0x00, 0x10, 0xc8};
  byte buffer[20];
};
#endif // __I2C_DDC_H_
