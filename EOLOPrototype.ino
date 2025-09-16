#include <U8g2lib.h>
#include <Wire.h>
#include "Logos.h"
#include "Input.h"
#include "GUI.h"
#include "Config.h"

DisplayModel u8g2(U8G2_R0, SCL_PIN, SDA_PIN);
Input input;

constexpr unsigned int hash(const char* s, int off = 0) {
  return !s[off] ? 5381 : (hash(s, off + 1) * 33) ^ s[off];
}

char* pantallaActual = "home";
int seleccionId = 0;

GUI gui(u8g2, input, pantallaActual, seleccionId);

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100);
  while (!Serial) delay(100);
  Serial.println("BOOT");
  input.begin();
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.drawXBM(32, 0, 128, 64, cmas);
  u8g2.sendBuffer();
  delay(3000);
  input.resetCounter();
}

void loop() {
  input.poll();
  gui.displayInicio();
  delay(10);
}
