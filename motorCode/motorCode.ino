  int startTime = millis();
  int lastTime = startTime;
  int dir = 0;
  int speed = 50;

  //The sample code for driving one way motor encoder
  const byte encoder0pinA = 2;//A pin -> the interrupt pin 0
  const byte encoder0pinB = 3;//B pin -> the digital pin 3
  byte encoder0PinALast;
  int encoderCounts;//the number of the pulses
  boolean Direction;//the rotation direction

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(9,OUTPUT);
  Serial.println("AT 0");
  // delay(3000);
  Serial.println("AT 0.5");
  analogWrite(9,0);
  
  digitalWrite(13,HIGH);
  digitalWrite(12,LOW);
  
  
  EncoderInit();//Initialize the module
//  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println("AT 1");
  if (millis() - lastTime > 5000){
    analogWrite(9,0);
    Serial.println("AT 2");
//    lastTime = millis();
  }
  else{
    analogWrite(9,150);
  }
  if (millis()%100 == 0){
//    Serial.println(encoderCounts/341.2);
  }
}

void EncoderInit()
{
  Direction = true;//default -> Forward
  pinMode(encoder0pinB,INPUT);
  attachInterrupt(0, wheelSpeed, CHANGE);
}

void wheelSpeed()
{
  int Lstate = digitalRead(encoder0pinA);
  if((encoder0PinALast == LOW) && Lstate==HIGH)
  {
    int val = digitalRead(encoder0pinB);
    if(val == LOW && Direction)
    {
      Direction = false; //Reverse
    }
    else if(val == HIGH && !Direction)
    {
      Direction = true;  //Forward
    }
  }
  encoder0PinALast = Lstate;

  if(!Direction)  encoderCounts++;
  else  encoderCounts--;
}
