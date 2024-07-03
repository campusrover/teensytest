


/*
  #  Linorobot_Motor_Test_Rxx.ino - Pito
  #

  # This program tests the motors for simple operation.  L298N motor drivers are needed
  #  This program is distributed in the hope that it will be useful,
  #  but WITHOUT ANY WARRANTY; without even the implied warranty of
  #  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  #  GNU General Public License for more details.
  #

*/


//Contain definition of maximum limits of various data type
#include <limits.h>





////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//Encoder pins definition

// Left encoder

#define Left_Encoder_PinA 15
#define Left_Encoder_PinB 14

volatile long Left_Encoder_Ticks = 0;
volatile bool LeftEncoderBSet;

//Right Encoder

#define Right_Encoder_PinA 11
#define Right_Encoder_PinB 12
volatile long Right_Encoder_Ticks = 0;
volatile bool RightEncoderBSet;

/////////////////////////////////////////////////////////////////
//Motor Pin definition
//Left Motor pins

#define Left_Motor_Pin_A 20
#define Left_Motor_Pin_B 1

//PWM 1 pin number
#define Left_Motor_PWM 21


//Right Motor
#define Right_Motor_Pin_A 6       // switch to also rotate in clockwise direction
#define Right_Motor_Pin_B 8

//PWM 2 pin number
#define Right_Motor_PWM 5

/////////////////////////////////////////////////////////////////////////////////////////
//Time  update variables

unsigned long LastUpdateMicrosecs = 0;
unsigned long LastUpdateMillisecs = 0;
unsigned long CurrentMicrosecs = 0;
unsigned long MicrosecsSinceLastUpdate = 0;
float SecondsSinceLastUpdate = 0;

///////////////////////////////////////////////////////////////////////////////////////
//Motor speed from PC
//Motor left and right speed
float motor_left_speed = 0;
float motor_right_speed = 0;
/////////////////////////////////////////////////////////////////


//Setup serial, encoders functions
void setup()
{


  //Setup Encoders
  SetupEncoders();
  //Setup Motors
  SetupMotors();


}

//SetupEncoders() Definition

void SetupEncoders()
{
  // Quadrature encoders
  // Left encoder
  pinMode(Left_Encoder_PinA, INPUT_PULLUP);      // sets pin A as input
  pinMode(Left_Encoder_PinB, INPUT_PULLUP);      // sets pin B as input



  // Right encoder
  pinMode(Right_Encoder_PinA, INPUT_PULLUP);      // sets pin A as input
  pinMode(Right_Encoder_PinB, INPUT_PULLUP);      // sets pin B as input


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Setup Motors() function

void SetupMotors()
{

  //Left motor
  pinMode(Left_Motor_Pin_A, OUTPUT);
  pinMode(Left_Motor_Pin_B, OUTPUT);


  //Right Motor
  pinMode(Right_Motor_Pin_A, OUTPUT);
  pinMode(Right_Motor_Pin_B, OUTPUT);

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MAIN LOOP

void loop()
{


  moveLeftMotor(128);     //motor speed goes from -255 (full reverse) to  0 (stopped) to 255 full on
  moveRightMotor(0);
  delay(1000);

  moveLeftMotor(0);     //motor speed goes from -255 (full reverse) to  0 (stopped) to 255 full on
  moveRightMotor(0);
  delay(1000);

  moveLeftMotor(0);     //motor speed goes from -255 (full reverse) to  0 (stopped) to 255 full on
  moveRightMotor(128);
  delay(1000);

  moveLeftMotor(0);     //motor speed goes from -255 (full reverse) to  0 (stopped) to 255 full on
  moveRightMotor(0);
  delay(1000);

  moveLeftMotor(-128);     //motor speed goes from -255 (full reverse) to  0 (stopped) to 255 full on
  moveRightMotor(0);
  delay(1000);

  moveLeftMotor(0);     //motor speed goes from -255 (full reverse) to  0 (stopped) to 255 full on
  moveRightMotor(0);
  delay(1000);

  moveLeftMotor(128);     //motor speed goes from -255 (full reverse) to  0 (stopped) to 255 full on
  moveRightMotor(-128);
  delay(1000);

 


}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Set speed
void Set_Speed()
{

  /////  motor_left_speed = Messenger_Handler.readLong();
  /////  motor_right_speed = Messenger_Handler.readLong();



}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Will update both motors
void Update_Motors()
{

  moveRightMotor(motor_right_speed);
  moveLeftMotor(motor_left_speed);


}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Motor running function


void moveRightMotor(float rightServoValue)
{
  if (rightServoValue > 0)
  {

    digitalWrite(Right_Motor_Pin_A, HIGH);
    digitalWrite(Right_Motor_Pin_B, LOW);
    analogWrite(Right_Motor_PWM, rightServoValue);

  }
  else if (rightServoValue < 0)
  {
    digitalWrite(Right_Motor_Pin_A, LOW);
    digitalWrite(Right_Motor_Pin_B, HIGH);
    analogWrite(Right_Motor_PWM, abs(rightServoValue));

  }

  else if (rightServoValue == 0)
  {
    digitalWrite(Right_Motor_Pin_A, HIGH);
    digitalWrite(Right_Motor_Pin_B, HIGH);


  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void moveLeftMotor(float leftServoValue)
{
  if (leftServoValue > 0)
  {
    digitalWrite(Left_Motor_Pin_A, LOW);
    digitalWrite(Left_Motor_Pin_B, HIGH);
    analogWrite(Left_Motor_PWM, leftServoValue);
  }
  else if (leftServoValue < 0)
  {
    digitalWrite(Left_Motor_Pin_A, HIGH);
    digitalWrite(Left_Motor_Pin_B, LOW);
    analogWrite(Left_Motor_PWM, abs(leftServoValue));

  }
  else if (leftServoValue == 0)
  {

    digitalWrite(Left_Motor_Pin_A, HIGH);
    digitalWrite(Left_Motor_Pin_B, HIGH);

  }
}
