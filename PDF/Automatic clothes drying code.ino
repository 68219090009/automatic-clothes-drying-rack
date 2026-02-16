//https://app.cirkitdesigner.com/project/04591d30-a2a6-43f1-be1c-a3271f9bd8bb

#include <Servo.h>

const int rainSensorPin = A0; 
const int servoPin = 9;

Servo myservo;
int rainPercent = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin);
  
  // แก้ไข: เปลี่ยนจุดเริ่มต้นเป็น 180 (หรือตำแหน่งที่ผ้ากางออก)
  myservo.write(180); 
  Serial.println("System Start: Extended Position");
}

void loop() {
  int rawValue = analogRead(rainSensorPin);
  rainPercent = map(rawValue, 1023, 0, 0, 100);
  rainPercent = constrain(rainPercent, 0, 100);

  Serial.print("Rain: ");
  Serial.print(rainPercent);
  Serial.println("%");

  // --- ส่วนที่แก้ไขการสลับทิศทาง ---
  if (rainPercent >= 50) { 
    // ถ้าเจอฝน (เปียก) -> ให้หมุนไปที่ 0 องศา (เก็บผ้าเข้า)
    myservo.write(0);
    Serial.println(">> Raining: Retracting to 0");
  } 
  else if (rainPercent < 10) { 
    // ถ้าฝนหยุด (แห้ง) -> ให้หมุนกลับไปที่ 180 องศา (กางผ้าออก)
    myservo.write(180);
    Serial.println(">> Dry: Extending to 180");
  }

  delay(500); 
}
