/***************************************************
3 mlx and 1 current sensor code using DFRobot library.
showing output in bluetooth terminal
 ****************************************************/

#include <DFRobot_MLX90614.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT; 
DFRobot_MLX90614_I2C sensorA(0x5A);   // instantiate an object to drive our sensor
DFRobot_MLX90614_I2C sensorB(0x5B);   // instantiate an object to drive our sensor
DFRobot_MLX90614_I2C sensorC(0x5C);   // instantiate an object to drive our sensor
int currentpin = 13;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  SerialBT.begin("ESP32_BT_Server"); // Set a name for Bluetooth server
  pinMode(currentpin, INPUT);

  // initialize the sensor
  while( NO_ERR != sensorA.begin() ){
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
}

void loop() {
  //ACS721
  int adc = analogRead(currentpin);
  float adc_voltage = adc * (2.28 / 4096.0);
  float current_voltage = adc_voltage;
  float current = (current_voltage-1.14)/0.100;
  SerialBT.print("Current Value: ");
  //Serial.println(adc);
  //SerialBT.println(current_voltage);
  //SerialBT.println(adc_voltage);
  SerialBT.println(current);

  //MLX90614
  float objectATemp = sensorA.getObjectTempCelsius();
  float objectBTemp = sensorB.getObjectTempCelsius();
  float objectCTemp = sensorC.getObjectTempCelsius();

  // print measured data in Celsius
  SerialBT.print("ObjectA celsius : ");  SerialBT.print(objectATemp);  SerialBT.println(" °C");
  SerialBT.print("ObjectB celsius : ");  SerialBT.print(objectBTemp);  SerialBT.println(" °C");
  SerialBT.print("ObjectC celsius : ");  SerialBT.print(objectCTemp);  SerialBT.println(" °C");

  SerialBT.println();
  delay(500);
}