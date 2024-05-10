//
//    FILE: ADS_read.ino
//  AUTHOR: Rob.Tillaart
// PURPOSE: read analog inputs - straightforward.
//     URL: https://github.com/RobTillaart/ADS1X15

//  test
//  connect 1 potmeter per port.
//
//  GND ---[   x   ]------ 5V
//             |
//
//  measure at x (connect to AIN0).


#include "ADS1X15.h"
#include "BluetoothSerial.h"
#include <Wire.h> 
#include <SparkFunMLX90614.h>

//#define USE_PIN // Uncomment this to use PIN during pairing. The pin is specified on the line below
const char *pin = "1234"; // Change this to more secure PIN.

String device_name = "ESP32-BT-KAIZEN";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

ADS1115 ADS(0x48);
BluetoothSerial SerialBT;

void setup() 
{
  Serial.begin(115200);
  SerialBT.begin(device_name);
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  Wire.begin();
  ADS.begin();
}


void loop() 
{
  ADS.setGain(0);

  int16_t val_0 = ADS.readADC(0);  
  int16_t val_1 = ADS.readADC(1);  
  int16_t val_2 = ADS.readADC(2);  
  int16_t val_3 = ADS.readADC(3);  

  float f = ADS.toVoltage(1);  //  voltage factor

  //float current_read = ((val_0*f)-2.53)/0.125;
  float current_read = 0;
  float avg = 0;

  for(int i=0;i<100;i++){
    // take samples...11 times
    current_read = current_read + ((val_1*f)-2.527)/0.125;
    avg = current_read;
    delay(10);
  }

  float avg_current = avg/100;

  Serial.print("\tAnalog0: "); Serial.print(val_0); Serial.print('\t'); Serial.println(val_0 * f, 3);
  Serial.print("\tAnalog1: "); Serial.print(val_1); Serial.print('\t'); Serial.println(val_1 * f, 3);
  Serial.print("\tAnalog2: "); Serial.print(val_2); Serial.print('\t'); Serial.println(val_2 * f, 3);
  Serial.print("\tAnalog3: "); Serial.print(val_3); Serial.print('\t'); Serial.println(val_3 * f, 3);
  
  Serial.print("\tcurrent : "); Serial.print(avg_current); Serial.print('\t');

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }

  //delay(500);
}


//  -- END OF FILE --
