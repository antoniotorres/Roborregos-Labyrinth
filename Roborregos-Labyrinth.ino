/* vexMotorLibraryExample.ino

 Upload this program to your Arduino and open up the Serial Monitor
 to manually control / specify the speed of your servo motor.

 This example exercises all of the methods and properties that are
 used in the vexMotor class. vexMotor uses the Servo library. You must
 include both vexMotor.h and Servo.h.

 Hardware connections:
 =====================
 To connect the standard 2-wire VEX motor 393 to an Arduino requires
 a Motor Controller 29 module. Connect the wires on the Motor Controller
 to the Arduino with the following pins:

 MOTOR CONTROLLER 29  <-------->  ARDUINO
 =============================================
 WHITE (signal)           Digital pin 9
 RED (power)              VIN (Battery Power -- 5V works too, but won't be as strong or fast)
 BLACK (ground)           Ground (GND)

 This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
 This code is completely free for any use.
 */

#include <vexMotor.h> // includes the vexMotor library (must also include Servo.h)
#include <Servo.h>    // servo library -- vexMotor relies on the Servo library

vexMotor vexMotorFR;  // creates an instance of the vexMotor class
vexMotor vexMotorFL;  // creates an instance of the vexMotor class
vexMotor vexMotorBR;  // creates an instance of the vexMotor class
vexMotor vexMotorBL;  // creates an instance of the vexMotor class

float yDir = 0; //This is the forward or backwards movment
float xDir = 0; //This is the stride or lateral movement
float rDir = 0; //This is the rotation movement

float speedChangePerLoop = 0.03; 
float frPower = 0;
float flPower = 0;
float brPower = 0;
float blPower = 0;


void setup()
{
   vexMotorFR.attach(6); // setup / attach the vexMotor
   vexMotorFL.attach(9); // setup / attach the vexMotor
   vexMotorBR.attach(10); // setup / attach the vexMotor
   vexMotorBL.attach(11); // setup / attach the vexMotor
  Serial.begin(9600);    // starts the Serial communication on Arduino
}

void loop()
{
  int inputValue;
  // Holding loop until an input is read.
  if(Serial.available() != 0)
  {
    // Read in value from Serial Monitor
    Serial.println("x");
    inputValue = Serial.parseInt();
    yDir = inputValue;
    while(Serial.available() == 0){
    }
    Serial.println("y");
    inputValue = Serial.parseInt();
    xDir = inputValue;
    while(Serial.available() == 0){
    }
    Serial.println("z");
    inputValue = Serial.parseInt();
    rDir = inputValue;
    Serial.println("--------------------------------------");
    Serial.println(yDir);
    Serial.println(xDir);
    Serial.println(rDir);
    Serial.println();
    Serial.println();
  }
  drive();
}

void drive()
{
  int targetFL = yDir + xDir + rDir;
  int targetBL = yDir - xDir + rDir;
  
  int targetFR = yDir - xDir - rDir;
  int targetBR = yDir + xDir - rDir;
  if(targetFL < flPower)
  {
    flPower -= speedChangePerLoop;
  }
  else if(targetFL > flPower)
  {
    flPower += speedChangePerLoop;
  }
  else{}

  if(targetFR < frPower)
  {
    frPower -= speedChangePerLoop;
  }
  else if(targetFR > frPower)
  {
    frPower += speedChangePerLoop;
  }
  else{}

  if(targetBL < blPower)
  {
    blPower -= speedChangePerLoop;
  }
  else if(targetBL > blPower)
  {
    blPower += speedChangePerLoop;
  }
  else{}

  if(targetBR < brPower)
  {
    brPower -= speedChangePerLoop;
  }
  else if(targetBR > brPower)
  {
    brPower += speedChangePerLoop;
  }
  else{}
  
  //Write the value onto the motors
  //Right
  vexMotorFR.write(frPower);
  vexMotorBR.write(brPower);
  //Left
  vexMotorFL.write(flPower);
  vexMotorBL.write(blPower);
}






