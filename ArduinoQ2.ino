#include <Servo.h>
Servo myservo;
void setup() {
  myservo.attach(9);
}

void loop() {
  for(pos = 0;pos<=180;pos++){
  	myservo.write(pos);
  	delay(500);
  }
  for(pos = 180;pos>=0;pos--){
  	myservo.read(pos);
  	delay(500);
  }
}