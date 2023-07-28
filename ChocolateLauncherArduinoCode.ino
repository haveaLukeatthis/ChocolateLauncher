#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 9 through 12:
Stepper xStepper(stepsPerRevolution, 10, 12, 11, 13);
// initialize the stepper library on pins 5 through 8:
Stepper yStepper(stepsPerRevolution, 6, 8, 7, 9);
// initialize the stepper library on pins 1 through 4:
Stepper fireStepper(stepsPerRevolution, 2, 4, 3, 5);

String inputString = "";         // a string to hold incoming data
unsigned int cont=0;
unsigned long delayStart=0;


void setup() 
{
  // set the speed at 60 rpm:
  xStepper.setSpeed(30);
  yStepper.setSpeed(30);
  fireStepper.setSpeed(50);
  // initialize the serial port:
  Serial.begin(9600);
  Serial.println("Ready");
  delayStart = millis();   // start delay
}


void loop() 
{
  
  signed int vel;
  signed int velLimx;
  velLimx = 20;
  signed int velLimy;
  velLimy = 40;
  signed int stepSize;
  stepSize = 1;
  signed int fireCountdown;
  unsigned int pos;
  
  if (Serial.available()) 
  {
    inputString = Serial.readStringUntil('!');
    vel = inputString.toInt();   

    if(inputString.endsWith("x"))
    {
      if (vel > velLimx)
        xStepper.step(stepSize);  
      else if (vel < -velLimx)
        xStepper.step(-stepSize);     
    }

    if(inputString.endsWith("y"))
    {
      if (vel > velLimy)
        yStepper.step(stepSize);  
      else if (vel < -velLimy)
        yStepper.step(-stepSize);     
    }

    if(inputString.endsWith("f"))
    {
      if ((millis() - delayStart) >= 5000) {
        fireStepper.step(-20);
        fireStepper.step(20);
        delayStart = millis();
      }
      
    }

    
    inputString = "";
    }
    inputString = "";
}
