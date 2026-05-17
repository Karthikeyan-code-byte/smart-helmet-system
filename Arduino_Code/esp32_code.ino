#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BluetoothSerial.h>
#include <MPU6050.h>

BluetoothSerial SerialBT;
LiquidCrystal_I2C lcd(0x27, 16, 2);
MPU6050 mpu;

#define MQ3_PIN 34
#define RELAY_PIN 26
#define BUZZER_PIN 27

int16_t ax, ay, az;

void setup()
{
  Serial.begin(115200);

  Wire.begin(21, 22);

  SerialBT.begin("AccidentDetector");   // Bluetooth device name

  lcd.init();
  lcd.backlight();

  pinMode(MQ3_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH);

  mpu.initialize();

  lcd.setCursor(0, 0);
  lcd.print("System Starting");

  delay(2000);

  lcd.clear();
}

void loop()
{

  // -------- ALCOHOL DETECTION --------

  int alcohol = analogRead(MQ3_PIN);

  Serial.print("Alcohol Value: ");
  Serial.println(alcohol);

  lcd.setCursor(0, 0);
  lcd.print("Alcohol:");
  lcd.print(alcohol);
  lcd.print("   ");

  if (alcohol > 2000)// if alcohol level is greater than threshold the engine will be locked
  {

    lcd.setCursor(0, 1);
    lcd.print("ENGINE LOCKED ");

    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    SerialBT.println("ALCOHOL");

    delay(2000);
  }
  else
  {

    lcd.setCursor(0, 1);
    lcd.print("System Normal ");

    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  // -------- ACCIDENT DETECTION --------

  mpu.getAcceleration(&ax, &ay, &az);

  int vibration = abs(ax) + abs(ay) + abs(az);

  Serial.print("Vibration: ");
  Serial.println(vibration);

  // Lower threshold for demo reliability
  if (vibration > 30000)
  {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ACCIDENT");

    lcd.setCursor(0, 1);
    lcd.print("DETECTED");

    digitalWrite(BUZZER_PIN, HIGH);

    Serial.println("CRASH DETECTED");
    if(SerialBT.hasClient()){
      SerialBT.println("CRASH");// Android app listens for this and sends alert through automation

    }else{
      Serial.println("Phone is not connected");
    }
       


    delay(5000);

    digitalWrite(BUZZER_PIN, LOW);

    lcd.clear();
  }

  delay(500);
}
