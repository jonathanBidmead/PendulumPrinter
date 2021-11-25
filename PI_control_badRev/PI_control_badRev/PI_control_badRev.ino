//The sample code for driving one way motor encoder
const byte encoder0pinA = 2;//A pin -> the interrupt pin 0
const byte encoder0pinB = 3;//B pin -> the digital pin 3
byte encoder0PinALast;
float pos = 0;
float vel = 0;
float delayTime = 100;
int duration;//the number of the pulses
boolean Direction;//the rotation direction

float refPos = 3;
float KP = 10;
float KI = 1;
float error = 0;
float errorSum = 0;
float ctrl = 0;
float minPower = 0;
float epsilon = 0.02;
void setup()
{
  Serial.begin(57600);//Initialize the serial port
  EncoderInit();//Initialize the module
  pinMode(9,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  analogWrite(9,0);
  digitalWrite(12,LOW);//positive direction by default
  digitalWrite(13,HIGH);
  delay(2000);
}

void loop()
{
  //generating fluctuating reference
//  refPos = 8 + 5*sin(0.0001*(millis()-2100));
  if (abs(error) < epsilon){
    refPos = 3-refPos;
  }
//  refPos = 3;
  vel = duration;
  pos += duration;
  error = refPos - pos/(341.2*2);
  errorSum += error;

  //saturating integral action (only increase if below threshold)
//  if (abs(KI*errorSum) < 40){
//    errorSum += error;
//  }

  //calculate control
  ctrl = KP*error + KI*errorSum;
  
  //changing direction
  if(ctrl < 0){
//    analogWrite(9,0);
    
    digitalWrite(12,HIGH);//reversing
    digitalWrite(13,LOW);
//    delay(1);
  }
  else {
//    analogWrite(9,0);
    
    digitalWrite(12,LOW);//forwards
    digitalWrite(13,HIGH);
//    delay(1);
  }

  //saturating control
  if (abs(ctrl) > 255){
    Serial.println("Saturating");
    if (ctrl < 0){
      ctrl = -255;
    }
    else{
      ctrl = 255;
    }
  }
//  if (abs(ctrl) < minPower){
//    if (ctrl < 0){
//      ctrl = -minPower;
//    }
//    else {
//      ctrl = minPower;
//    }
//  }

  //turning off control if setpoint within acceptable limits
//  if (abs(error) < epsilon){
//    ctrl = 0;
//    error = refPos - pos/(341.2*2);
//  }
  
  analogWrite(9,ctrl);
  
  Serial.print("Position & Velocity:");
  Serial.print(pos/(341.2*2));
  Serial.print(",");
  Serial.print(refPos);
  Serial.print(",");
  Serial.print(ctrl/20);
  Serial.print(",");
  Serial.println(vel/(341.2*2*(delayTime/1000)));

//  Serial.print("Control: ");
//  Serial.println(ctrl);
  duration = 0;
  delay(delayTime);
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

  if(!Direction)  duration++;
  else  duration--;
}
