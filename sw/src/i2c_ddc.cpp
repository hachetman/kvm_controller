#include "../include/i2c_ddc.h"

ddc::ddc() { Wire.begin(); };

int ddc::get_display_channel(void) {
  int nDevices = 0;

  Wire.beginTransmission(0x37);
  for (int i = 0; i < 5; i++) {
    Wire.write(read_cmd[i]);
  }
  Wire.endTransmission();
  delay(100);

  int n = Wire.requestFrom(0x37, 20);
  Wire.readBytes(buffer, n);
  return buffer[9];

  // byte buf[7] = {0x51, 0x84, 0x03, 0x60, 0x00, 0x0f, 0xd7};
  // Wire.beginTransmission(0x37);
  // Serial.println("writing: ");
  // for (int i = 0; i < 7; i++) {
  //  Wire.write(buf[i]);
  //  Serial.print(buf[i], HEX);
  //}
  // Wire.endTransmission();
  return 0;
}

void ddc::set_display_channel(int channel) {
  Wire.beginTransmission(0x37);
  if (channel == 0xf) {
    for (int i = 0; i < 7; i++) {
      Wire.write(dp_cmd[i]);
      Serial.print(dp_cmd[i], HEX);
    }
  } else {
    for (int i = 0; i < 7; i++) {
      Wire.write(mdp_cmd[i]);
      Serial.print(mdp_cmd[i], HEX);
    }
  }
  Wire.endTransmission();
}
