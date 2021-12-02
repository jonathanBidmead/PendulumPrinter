//The sample code for driving one way motor encoder
const byte encoder0pinA = 2;//A pin -> the interrupt pin 0
const byte encoder0pinB = 3;//B pin -> the digital pin 3
byte encoder0PinALast;


float pos = 0;
float vel = 0;
float delayTime = 10;
int duration;//the number of the pulses
boolean Direction;//the rotation direction

float refPos = 0.3;
float KP;
float KI;



float error = 0;
float errorSum = 0;
float ctrl = 0;
float minPower = 100;
float epsilon = 0.05;
float maxPower = 200;

float startTime = 0;
float currentTime = 0;
int stepTime = 4000;

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
  
  //good for 0.3 sqaure
  //KP = 120;
  //KI = 1;

  KP = 400;
  KI = 3;
  
  
  
  delay(2000);
  startTime = millis();
}

void loop()
{
  //generating fluctuating references
  //sinusoidal reference
  refPos = 0.3*sin(0.0005*(millis()-2100));

  //square wave reference
//  currentTime = millis();
//  if ((currentTime - startTime) > stepTime){
//    if (refPos == 0.3){
//      refPos = -0.3;
//    }
//    else if (refPos == -0.3){
//      refPos = 0.3;
//    }
//    stepTime += 4000;
//    errorSum = 0;
//  }



  //calculating variables
  vel = duration;
  pos += duration;
  duration = 0;
  error = refPos - pos/(341.2*2);
  errorSum += error;

//  //limiting effect of integral action
//  if (abs(error) > 0.05){
//    errorSum -= error;
//  }

  //calculate control
  ctrl = KP*error + KI*errorSum;
  
  //changing direction and applying deadzone offset
  if(ctrl < 0){
    digitalWrite(12,HIGH);//reversing
    digitalWrite(13,LOW);
    ctrl -= minPower;
  }
  else {
    digitalWrite(12,LOW);//forwards
    digitalWrite(13,HIGH);
    ctrl += minPower;
  }

  //saturating control
  if (abs(ctrl) > maxPower){
    Serial.println("Saturating");
    if (ctrl < 0){
      ctrl = -maxPower;
    }
    else{
      ctrl = maxPower;
    }
  }

  //sending working control to motor
  analogWrite(9,abs(ctrl));
//  analogWrite(9,100*sin(0.0005*(millis()-2100)));
  
  Serial.print("Position,Reference,Control,Velocity:");
  Serial.print(100*pos/(341.2*2) -300);
  Serial.print(",");
  Serial.print(100*refPos -300);
  Serial.print(",");
  Serial.print(minPower);
  Serial.print(",");
  Serial.print(-minPower);
  Serial.print(",");
  Serial.println(ctrl);
//  Serial.print(",");
//  Serial.println(vel/(341.2*2*(delayTime/1000)));

//  Serial.print("Control: ");
//  Serial.println(ctrl);



  
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
