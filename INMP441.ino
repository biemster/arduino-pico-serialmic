#include <I2S.h>

I2S i2s(INPUT);
int32_t l, r, sample;
unsigned long previousMillis, currentMillis;
bool use_SerialMonitor = false;

void setup() {
  currentMillis = 0;
  pinMode(1, OUTPUT); // L/R
  digitalWrite(1, LOW); // LOW=LEFT, HIGH=RIGHT
  
  i2s.setDATA(29);
  i2s.setBCLK(3); // LRCLK = +1
  i2s.setBitsPerSample(24);
  i2s.begin(16000);
}

void loop() {
  i2s.read32(&l, &r);
  sample = l ? l : r;

  if(!use_SerialMonitor) {
    Serial.printf("%.6x\n", sample);
    // play using $ cat /dev/ttyACM0 | xxd -r -p | aplay -r16000 -c1 -fS24_3BE
  }
  else {
    currentMillis = millis();
    if (currentMillis - previousMillis >= 10) {
      previousMillis = currentMillis;    
      sample += (sample & (1<<23)) ? 0xff000000 : 0; // this is actually 24 bits
      Serial.print("-10000 ");
      Serial.print(sample);
      Serial.println(" 10000");
    }
  }
}
