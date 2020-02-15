#include <Servo.h>

Servo NoodleServo;
Servo EggServo;
Servo PowderServo;

int NoodlePin = 10;
int SoySaucePin = 2;
int EggPin = 12;
int PowderPin = 13;
int masterSwitchPin = 7;
int masterSwitch = HIGH;
String input = "";
bool is_ready = true;

void setup() {
  Serial.begin(9600);
  NoodleServo.attach(NoodlePin);
  NoodleServo.write(0);
  EggServo.attach(EggPin);
  EggServo.write(150);
  PowderServo.attach(PowderPin);
  PowderServo.write(0);
  pinMode(SoySaucePin, OUTPUT);
  digitalWrite(SoySaucePin, LOW);
  pinMode(masterSwitchPin, INPUT);
}

void releaseNoodles(){
  NoodleServo.write(120);
  Serial.println("noodles released");
  delay(3000);
  NoodleServo.write(0);
}

void crackEgg(){
  EggServo.write(70);
  Serial.println("egg cracked");
  delay(3000);
  EggServo.write(150);
}

void spraySoySauce(){
  digitalWrite(SoySaucePin, HIGH);
  Serial.println("soy released");
  delay(2000);  
  digitalWrite(SoySaucePin, LOW);
}

void releasePowder(){
  PowderServo.write(180);
  Serial.println("powder released");
  delay(3000);
  PowderServo.write(0);
}

void cookRamen(){
  releaseNoodles();
  delay(2000);
  spraySoySauce();
  delay(2000);
  releasePowder();
  delay(2000);
  crackEgg();
}


void loop() {
  masterSwitch = digitalRead(masterSwitchPin);
  if (masterSwitch == LOW && is_ready) {
    Serial.print("I read on switch: ");
    Serial.println(masterSwitch);
    Serial.println("yee haw -1");
    cookRamen();
    delay(5000);
    is_ready = false;
  }
  else {
    is_ready = true;
  }
  
  if (Serial.available() > 0) {
    // read the incoming byte:
    input = Serial.readString();
    Serial.print("I read: ");
    Serial.println(input);

    if (input == "reset\n") {
      Serial.println("yee haw 0");
      setup();
    }

    if (input == "noodle\n"){
      Serial.println("yee haw 1");
      releaseNoodles();
    }

    if (input == "soy\n"){
      Serial.println("yee haw 2");
      spraySoySauce();
    }

    if (input == "powder\n"){
      Serial.println("yee haw 3");
      releasePowder();
    }

    if (input == "egg\n"){
      Serial.println("yee haw 4");
      crackEgg();
    }

  }
}
