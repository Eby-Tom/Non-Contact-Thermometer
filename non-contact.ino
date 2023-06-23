#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
uint8_t proximity_data = 0;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
int buzzer = 11;
int irPin = 7;  // This is our input pin (IR LED at pin 7)
int sensorOut = HIGH;  // HIGH at No Obstacle

void setup() 
{
  mlx.begin();
  pinMode(irPin, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
 Serial.begin(9600);
  pinMode (8, OUTPUT);
  pinMode (9, OUTPUT);
}

void loop() 
{
  String temperature = "";
  sensorOut = digitalRead(irPin);

  if (sensorOut == LOW && mlx.readObjectTempF() < 100) {

    temperature = String(mlx.readObjectTempC(), 1);
    Serial.print(" Body Temperature:");
    Serial.println(mlx.readObjectTempC());
    display.clearDisplay();
    display.invertDisplay(false);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(8, 0);
    display.clearDisplay();
    display.println("Body Temp:");
    display.setCursor(25, 18);
    display.print(mlx.readObjectTempF());
    display.setCursor(85, 8);
    display.print(".");
    display.setTextColor(WHITE);
    display.setCursor(85, 18);
    display.print(" F");
    display.display();
    digitalWrite (8, HIGH);
    tone(buzzer, 450);
    delay (300);
    noTone(buzzer);
    delay(2000);
    digitalWrite (8, LOW);
  }
 if (sensorOut == LOW) {
 if (mlx.readObjectTempF() > 102) {

      display.clearDisplay();
      display.invertDisplay(false);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");

      display.invertDisplay(true);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");

      display.invertDisplay(true);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");

      display.invertDisplay(false);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");

      display.invertDisplay(true);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");

      display.invertDisplay(true);

      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");
      
      display.invertDisplay(false);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(20, 0);
      display.clearDisplay();
      display.println("CRITICAL");
      display.setCursor(23, 18);
      display.print(mlx.readObjectTempF());
      display.setCursor(93, 8);
      display.print(".");
      display.setTextColor(WHITE);
      display.setCursor(93, 18);
      display.print(" F");
      display.display();

      digitalWrite (9, HIGH);

      tone(buzzer, 450);
       delay(1500);
      noTone(buzzer);
      delay(500);
      digitalWrite (9, LOW);
    }
  }

  if (sensorOut == LOW) {
    if (mlx.readObjectTempF() > 100) {

      display.setCursor(93, 8);
      display.print(".");
      display.setTextColor(WHITE);
      display.setCursor(93, 18);
      display.print(" F");
      display.display();
    }
  }
  else if (sensorOut == HIGH) {
    delay(1000);
    display.clearDisplay();
    display.invertDisplay(true);
    display.setTextSize(2.8);
    display.setTextColor(WHITE);
    display.setCursor(45, 1);
    display.clearDisplay();
    display.println("NOT");
    display.setCursor(17, 17);
    display.print("DETECTED");
    display.display();
  }
}
