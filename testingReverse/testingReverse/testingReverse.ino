

void setup() {
  // put your setup code here, to run once:
  pinMode(9,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  analogWrite(9,60);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(12,LOW);//positive direction 
  digitalWrite(13,HIGH);
  delay(2000);
  digitalWrite(12,HIGH);//reverse
  digitalWrite(13,LOW);
  delay(2000);
}
