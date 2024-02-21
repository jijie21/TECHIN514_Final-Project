#include "BluetoothSerial.h"
#include "driver/adc.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

const int micPin = 34; // SPW2430 Audio output connected to GPIO34 (Analog ADC1_CH6)
const int samplingFrequency = 10000; // Sample rate in Hz

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32SoundSensor"); // Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  adc1_config_width(ADC_WIDTH_BIT_12); //Configure ADC
  adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
}

void loop() {
  int micValue = adc1_get_raw(ADC1_CHANNEL_6); // Read the microphone value
  SerialBT.println(micValue); // Send the value over Bluetooth
  delay(1000/samplingFrequency); // Delay for the sampling rate
}
