#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int trig = 9;
int echo = 10;

long duration;
int distance;

int chickCount = 0;
bool objectDetected = false;

void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Chick Counter");
  delay(2000);
  lcd.clear();
}

void loop()
{
  // Ultrasonic
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  // Limit display range
  int displayDistance = distance;
  if(displayDistance > 45) displayDistance = 45;
  if(displayDistance < 1) displayDistance = 1;

  // Counting
  if(displayDistance < 10 && objectDetected == false)
  {
    chickCount++;
    objectDetected = true;
    delay(300);
  }

  if(displayDistance >15)
  {
    objectDetected = false;
  }

  // LCD
  lcd.setCursor(0,0);
  lcd.print("Chicks: ");
  lcd.print(chickCount);
  lcd.print("   ");

  lcd.setCursor(0,1);
  lcd.print("Dist:");
  lcd.print(displayDistance);
  lcd.print("cm   ");

  delay(150);
}