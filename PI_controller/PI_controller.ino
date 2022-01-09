//The sample code for driving one way motor encoder
const byte encoder0pinA = 2;//A pin -> the interrupt pin 0
const byte encoder0pinB = 3;//B pin -> the digital pin 3
byte encoder0PinALast;


float pos = 0;
float vel = 0;
float delayTime = 10;
int duration;//the number of the pulses
boolean Direction;//the rotation direction
float gearRatio = 2;

//theta2

float refPos = 1;
float refPosVal = 1;
int refIter = 0;
float KP;
float KI;
float KD;
float FC;
float RS;
float PO;
float controlVel;

float lastError = 0;
float error = 0;
float errorSum = 0;
float ctrl = 0;
float minPower = 0;
float epsilon = 0.01;
float maxPower = 255;
float lastPos = 0;


float startTime = 0;
float currentTime = 0;
int stepTime = 4000;
float lastRefPos;

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
  KP = 300;
  KI = 20;
  KD = 20;

//  KP = 400;
//  KI = 3;

  RS = 20;
  PO = -5.5;

  
  
  delay(200);
  startTime = millis();
}

void loop()
{

  lastRefPos = refPos;
  //generating fluctuating references
  //sinusoidal reference
  refPos = 1*sin(0.002*(millis()-210));

  //square wave reference
//  currentTime = millis();
//  if ((currentTime - startTime) > stepTime){
//    if (refPos == refPosVal){
//      refPos = -refPosVal;
//    }
//    else if (refPos == -refPosVal){
//      refPos = refPosVal;
//    }
////    stepTime += 4000;
//    startTime = millis();
//    errorSum = 0;
//  }

  //reference imported from matlab
//  refPos = refPosList[refIter];
//  refIter++;


  controlVel = (refPos-lastRefPos)/delayTime;


  //calculating variables
  vel = duration;
  vel = vel/(341.2*gearRatio*(delayTime/1000));//conversion to real units
  pos += duration;
  duration = 0;
  lastError = error;
  error = refPos - pos/(341.2*gearRatio);
  errorSum += error;

  //friction compensation, very large value for low speed but drops off exponentially once the motor starts moving | RS = Response Steepness | PO = Power Offset
  if (abs(refPos - lastRefPos) > epsilon){
    FC = exp(-(RS*abs(vel) + PO));
  } else {
    FC = 0;
  }

  if (abs(KI*errorSum) > 80){
    errorSum -= error;
  }

  //calculate control
  FC = 0;
  ctrl = KP*error + KI*errorSum + KD*(error-lastError)/(delayTime/1000) + FC;
  
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
  Serial.print(100*pos/(341.2*gearRatio) -300);
  Serial.print(",");
  Serial.println(100*refPos -300);
//  Serial.print(",");
//  Serial.print(vel*100);
//  Serial.print(",");
//  Serial.print(error);
//  Serial.print(",");
//  Serial.println(ctrl+300);
//  Serial.print(",");
//  Serial.println(vel/(341.2*GearRatio*(delayTime/1000)));

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
