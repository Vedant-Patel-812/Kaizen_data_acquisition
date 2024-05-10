#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "ADS1X15.h"
//#include "BluetoothSerial.h"

//String device_name = "maybe..";

ADS1115 ADS(0x48);
//BluetoothSerial SerialBT;

Adafruit_MLX90614 mlx_1 = Adafruit_MLX90614(0x5A);
Adafruit_MLX90614 mlx_2 = Adafruit_MLX90614(0x5B);
Adafruit_MLX90614 mlx_3 = Adafruit_MLX90614(0x5C);
Adafruit_MLX90614 mlx_4 = Adafruit_MLX90614(0x5D);
Adafruit_MLX90614 mlx_5 = Adafruit_MLX90614(0x5E);

unsigned int startMil;
unsigned int currentMil;
unsigned int period = 200;

void setup() {

  //for wires/I2C
  Wire.begin();
  ADS.begin();

  //settings for bluetooth
  Serial.begin(115200);
  Serial.print("Start-up");
  //SerialBT.begin(device_name);

  //for MLX
  mlx_1.begin();
  mlx_2.begin();
  mlx_3.begin();
  mlx_4.begin();
  mlx_5.begin(); 

  startMil = millis();
}

void loop() {

  //currentMil = millis();

  //Current Reading
  ADS.setGain(0);

  int16_t val_1 = ADS.readADC(1);
  float f = ADS.toVoltage(1);
  float current_read = 0;
  float avg = 0;
  
  for(int i=0;i<50;i++){
    // take samples...100 times
    current_read = current_read + ((val_1*f)-2.527)/0.125;
    avg = current_read;
    delay(10);
  }
  float avg_current = avg/50;
  Serial.print("Current : "); Serial.print(avg_current);
  Serial.println();

  //For temperature
  Serial.print("M1="); Serial.print(mlx_1.readObjectTempC());
  Serial.print(" M2="); Serial.print(mlx_2.readObjectTempC());
  Serial.print(" M3="); Serial.print(mlx_3.readObjectTempC());
  Serial.print(" M4="); Serial.print(mlx_4.readObjectTempC());
  Serial.print(" M5="); Serial.print(mlx_5.readObjectTempC());
  Serial.println();
  Serial.println();

  //String Send = "M1 :"+ String(mlx_1.readObjectTempC());

  //For Bluetooth comm..
  //if (Serial.available()) {
    //SerialBT.println();
  //}
  //if (SerialBT.available()) {
    //Serial.write(SerialBT.read());
  //}
  
}
