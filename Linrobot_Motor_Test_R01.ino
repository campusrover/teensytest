


/*
  #  Linorobot_Motor_Test_Rxx.ino
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

// These are directly from lino_base_config.h
#define MOTOR1_IN_A 20
#define MOTOR1_IN_B 1
#define MOTOR1_PWM 22
#define MOTOR2_IN_A 6
#define MOTOR2_IN_B 8
#define MOTOR2_PWM 5

#define MOTOR1_ENCODER_A 14
#define MOTOR1_ENCODER_B 15
#define MOTOR2_ENCODER_A 12
#define MOTOR2_ENCODER_B 11



////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//Encoder pins definition

// Encoder variables

volatile long Left_Encoder_Ticks = 0;
volatile bool LeftEncoderBSet;
volatile long Right_Encoder_Ticks = 0;
volatile bool RightEncoderBSet;

/////////////////////////////////////////////////////////////////
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
  pinMode(MOTOR1_ENCODER_A, INPUT_PULLUP);      // sets pin A as input
  pinMode(MOTOR1_ENCODER_B, INPUT_PULLUP);      // sets pin B as input

  // Right encoder
  pinMode(MOTOR2_ENCODER_A, INPUT_PULLUP);      // sets pin A as input
  pinMode(MOTOR2_ENCODER_B, INPUT_PULLUP);      // sets pin B as input
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Setup Motors() function

void SetupMotors()
{
  //Left motor
  pinMode(MOTOR1_IN_A, OUTPUT);
  pinMode(MOTOR1_IN_B, OUTPUT);

  //Right Motor
  pinMode(MOTOR2_IN_A, OUTPUT);
  pinMode(MOTOR2_IN_A, OUTPUT);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MAIN LOOP

void loop()
{
  moveLeftMotor(128);
  moveRightMotor(0);
  delay(1000);

  moveLeftMotor(0);
  moveRightMotor(0);
  delay(1000);

  moveLeftMotor(0);
  moveRightMotor(128);
  delay(1000);

  moveLeftMotor(0);
  moveRightMotor(0);
  delay(1000);

  moveLeftMotor(-128);
  moveRightMotor(0);
  delay(1000);

  moveLeftMotor(0);
  moveRightMotor(0);
  delay(1000);

  moveLeftMotor(128);
  moveRightMotor(-128);
  delay(1000);
}

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

//////////////////////////////////////////
void moveLeftMotor(float leftServoValue)
{
  if (leftServoValue > 0)
  {
    digitalWrite(MOTOR1_IN_A, LOW);
    digitalWrite(MOTOR1_IN_B, HIGH);
    analogWrite(MOTOR1_PWM, leftServoValue);
  }
  else if (leftServoValue < 0)
  {
    digitalWrite(MOTOR2_IN_A, HIGH);
    digitalWrite(MOTOR2_IN_B, LOW);
    analogWrite(MOTOR2_PWM, abs(leftServoValue));
  }
  else if (leftServoValue == 0)
  {
    digitalWrite(MOTOR2_IN_A, HIGH);
    digitalWrite(MOTOR2_IN_B, HIGH);
  }
}
