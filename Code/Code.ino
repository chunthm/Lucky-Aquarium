#include <SPI.h>
#include <Wire.h>
#include <Servo.h>
////////////////Water Sensor////////////
int WaterSensorPin = 5;
int ValueForWaterSensor = 0;

/////////////////RGB////////////////////
int RGBPin[] = {9, 10, 11};

///////////////Servo///////////////////
Servo myservo;

//////////////TEMP////////////////////
int TemperatureSensorPin = 0;
int ValueForTemperatureSensor = 0;
float R1 = 10000;
float logR2, R2, T;
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741;
///////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  pinMode(RGBPin[0], OUTPUT);
  pinMode(RGBPin[1], OUTPUT);
  pinMode(RGBPin[2], OUTPUT);
  myservo.attach(6);

}
void loop() {
  WaterSensor();
  TemperatureSensor();
}
void WaterSensor() {
  ValueForWaterSensor = analogRead(WaterSensorPin);
  if (ValueForWaterSensor > 271) {
    ServoSensor(135);
  }
  else {
    ServoSensor(45);
    RGB(255, 0, 0);
  }
  delay(1000);
}

void RGB(int r, int g, int b) {
  analogWrite(RGBPin[0], r);
  analogWrite(RGBPin[1], g);
  analogWrite(RGBPin[2], b);
}

void ServoSensor(int angle){
  myservo.write(angle);

}

void TemperatureSensor() {
  ValueForTemperatureSensor = analogRead(TemperatureSensorPin);
  R2 = R1 * (1023.0 / (float)ValueForTemperatureSensor - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  T = T - 273.15;
  Serial.print("Temperature: ");
  Serial.print(T);
  Serial.println(" C");
  if (T > 32) {
    ServoSensor(180);
    RGB(255, 0, 255);
  }
  else if (T >= 27 && T < 32) {
    ServoSensor(90);
    RGB(0, 255, 0);
  }
  else {
    ServoSensor(0);
    RGB(0, 255, 255);
  }
  delay(1000);
}
