#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

////////////////Water Sensor////////////
int WaterSensorPin = 5;
int ValueForWaterSensor = 0;

/////////////////OLED//////////////////
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/////////////////RGB////////////////////
int RGBPin[] = {9, 10, 11};

//////////////TEMP////////////////////
int TemperatureSensorPin = 0;
int ValueForTemperatureSensor = 0;
float R1 = 10000;
float logR2, R2, T;
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741;

///////////////////////////////////////////////////////////
void setup(){
    Serial.begin(9600);
    pinMode(RGBPin[0], OUTPUT);
    pinMode(RGBPin[1], OUTPUT);
    pinMode(RGBPin[2], OUTPUT);
}

void loop(){
/////กรี๊ดดดดดดดดดดดด/////
}

void WaterSensor(){
    ValueForWaterSensor = analogRead(WaterSensorPin);
    if (ValueForWaterSensor > 271) {
    Serial.println("Enough");
  } else {
    Serial.println("Fill it");
  }
  delay(1000);
}

void OLEDdisplay( int PositionX, int PositionY, int TextSize, String Text ){
    OLED.clearDisplay();
    OLED.setTextColor(WHITE, BLACK);
    OLED.setCursor(PositionX,PositionY);
    OLED.setTextSize(TextSize);
    OLED.println(Text);
    OLED.display(); 
    delay(1000);
}

void RGB(int r, int g, int b){
  analogWrite(RGBPin[0], r);
  analogWrite(RGBPin[1], g);
  analogWrite(RGBPin[2], b);
}

void TemperatureSensor(){
  ValueForTemperatureSensor = analogRead(TemperatureSensorPin);
  R2 = R1 * (1023.0 / (float)ValueForTemperatureSensor - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  T = T - 273.15;
  Serial.print("Temperature: ");
  Serial.print(T);
  Serial.println(" C");
  if (T > 32) {
    Serial.println("Too warm");
  } else if (T >= 27 && T < 32) {
    Serial.println("Chill");
  } else {
    Serial.println("Too cool");
  }
  delay(1000);
}
