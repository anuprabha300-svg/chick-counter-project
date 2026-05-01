
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

// Ultrasonic
int trig = 9;
int echo = 10;

// Motor A
int ENA = 3;
int IN1 = 8;
int IN2 = 12;

// Motor B
int ENB = 11;
int IN3 = 6;
int IN4 = 5;

long duration;
int distance;

int chickCount = 0;
bool objectDetected = false;

void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Chick Counter");
  delay(2000);
  lcd.clear();
}

void loop()
{
  // 🚗 ALWAYS MOVE FORWARD
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  // 📡 ULTRASONIC SENSOR
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  // 🐥 COUNTING LOGIC
  if(distance < 10 && objectDetected == false)
  {
    chickCount++;
    objectDetected = true;
  }

  if(distance > 10)
  {
    objectDetected = false;
  }

  // 📺 LCD DISPLAY
  lcd.setCursor(0,0);
  lcd.print("Chicks: ");
  lcd.print(chickCount);
  lcd.print("   "); // clear extra chars

  lcd.setCursor(0,1);
  lcd.print("Dist:");
  lcd.print(distance);
  lcd.print("cm   ");

  delay(150); // small delay (not too big)
}
