//The sample code for driving one way motor encoder
const byte encoder0pinA = 2;//A pin -> the interrupt pin 0
const byte encoder0pinB = 3;//B pin -> the digital pin 3
byte encoder0PinALast;

float pos = 0;
float vel = 0;
float delayTime = 10;
int duration;//the number of the pulses
boolean Direction;//the rotation direction

float startTime = 0;
float currentTime = 0;
float error = 0;
float refPos = 255;
float ctrl;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);//Initialize the serial port
  EncoderInit();//Initialize the module
  pinMode(9,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  analogWrite(9,0);
  digitalWrite(12,LOW);//positive direction by default
  digitalWrite(13,HIGH);
  delay(500);
  startTime = millis();
}

void loop() {

  currentTime = millis();
  
  
  pos += duration;
  vel = duration;
  duration = 0;

  error = refPos - pos;

  ctrl = error;
  
  //changing direction and applying deadzone offset
  if(ctrl < 0){
    digitalWrite(12,HIGH);//reversing
    digitalWrite(13,LOW);
    ctrl -= 0;
  }
  else {
    digitalWrite(12,LOW);//forwards
    digitalWrite(13,HIGH);
    ctrl += 0;
  }

  analogWrite(9,error);
  
  Serial.print(pos);
  Serial.print(",");
  delay(10);
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
