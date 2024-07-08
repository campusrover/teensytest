

/*
  #  CAT_Encoder_Distance_Rxx
  #
  #  Copyright 2022 Brandeis University
  #
  #
  #  You should have received a copy of the GNU General Public License
  #  along with this program; if not, write to the Free Software
  #  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
  #  MA 02110-1301, USA.
  #
  #   Rev05 made consistant with LAB software
*/




// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
  mpuInterrupt = true;
}




////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//Encoder pins definition

// Left encoder

#define Left_Encoder_PinA 14
#define Left_Encoder_PinB 15

volatile long Left_Encoder_Ticks = 0;
volatile bool LeftEncoderBSet;

//Right Encoder

#define Right_Encoder_PinA 12
#define Right_Encoder_PinB 11
volatile long Right_Encoder_Ticks = 0;
volatile bool RightEncoderBSet;

//Motor Pin definition
//Left Motor pins    1 20 22
#define Left_Motor_Pin_A 20  //was 20 
#define Left_Motor_Pin_B 1

//PWM 1 pin number
#define Left_Motor_PWM 22  // for Teensy 3.6  for Teensy 4.1


//Right Motor  //6 8 5
#define Right_Motor_Pin_A 6 //was 6
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
//Motor speed defined
//Motor left and right speed
float motor_left_speed = 6.25;       //************** set these to the speed you want in cm/sec
float motor_right_speed = 6.25;
float motor_left_ticks_act = 0;
float motor_right_ticks_act = 0;
float motor_left_ticks_set = 0;
float motor_right_ticks_set = 0;
float motor_left_total_ticks = 0;
float motor_right_total_ticks = 0;
int motor_ticks_cm = 16.5;     // ticks per cm xxx measured
int motor_right_pwm = 71;
int motor_left_pwm = 70;
float PRE_motor_right_pwm = 0;

// ticks per cm  = 52.6  50 gear ratio * 16 PPR /15.2 cm  wheel circumference
/////////////////////////////////////////////////////////////////


//Setup serial, encoders,  functions
void setup()
{

  //Init Serial port with 9600 baud rate  ************Note this is significantly slower than
  Serial.begin(9600);

  //Setup Encoders
  SetupEncoders();
  //Setup Motors
  SetupMotors();
  // motor_left_ticks_set = motor_ticks_cm * motor_left_speed;
  //  motor_right_ticks_set = motor_ticks_cm * motor_right_speed;
  motor_left_ticks_set = 270;
  motor_right_ticks_set = 270;


}

//SetupEncoders() Definition

void SetupEncoders()
{
  // Quadrature encoders  ************* note not used as quadrature encoder  we know what direction so we don't need the encoder to tell us
  // Left encoder
  pinMode(Left_Encoder_PinA, INPUT_PULLUP);      // sets pin A as input
  pinMode(Left_Encoder_PinB, INPUT_PULLUP);      // sets pin B as input
  //Attaching interrupt in Left_Enc_PinA.
  attachInterrupt(Left_Encoder_PinB, do_Left_Encoder, RISING);


  // Right encoder
  pinMode(Right_Encoder_PinA, INPUT_PULLUP);      // sets pin A as input
  pinMode(Right_Encoder_PinB, INPUT_PULLUP);      // sets pin B as input
  //Attaching interrupt in Right_Enc_PinA.
  attachInterrupt(Right_Encoder_PinB, do_Right_Encoder, RISING);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Setup Motors() function

void SetupMotors()    //these are the direction bits
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




  //Send time information through serial port
  // Update_Time();

  //Send encoders values through serial port
  Update_Encoders();


  //Update motor values with corresponding speed and send speed values through serial port
  Update_Motors();

  if (motor_left_total_ticks > 2000)
  { motor_left_pwm = 0;
    PRE_motor_right_pwm = 0;
    motor_right_pwm = 0;
  }

  delay(1000);



}





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//do_Left_Encoder() Definitions  interrupt handler
void do_Left_Encoder()
{
  // Test transition; since the interrupt will only fire on 'rising' we don't need to read pin A
  // LeftEncoderBSet = digitalRead(Left_Encoder_PinB);   // read the input pin
  motor_left_ticks_act += LeftEncoderBSet ? -1 : +1;
  //  motor_left_ticks_act = motor_left_ticks_act +1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//do_Right_Encoder() Definitions   interrupt handler

void do_Right_Encoder()
{

  // RightEncoderBSet = digitalRead(Right_Encoder_PinB);   // read the input pin
  motor_right_ticks_act += RightEncoderBSet ? -1 : +1;
  //motor_right_ticks_act = motor_right_ticks_act +1;
  //motor_right_ticks_act = motor_right_ticks_act ;

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Will update both motors
void Update_Motors()
{

  moveRightMotor(motor_right_pwm);
  moveLeftMotor(motor_left_pwm );

  if (motor_left_total_ticks - motor_right_total_ticks > 8 )
  {
    PRE_motor_right_pwm = PRE_motor_right_pwm + 0.1;
  //  motor_right_pwm = PRE_motor_right_pwm;
  }
  if (motor_left_total_ticks - motor_right_total_ticks < -8)
  {
    //   motor_right_pwm = motor_right_pwm -1;
    PRE_motor_right_pwm = PRE_motor_right_pwm - 0.1;
 //   motor_right_pwm = PRE_motor_right_pwm;
  }
  if (PRE_motor_right_pwm > 1)
  { motor_right_pwm = motor_right_pwm + 1;
    PRE_motor_right_pwm = 0;
  }

  if (PRE_motor_right_pwm < -1)
  { motor_right_pwm = motor_right_pwm - 1;
    PRE_motor_right_pwm = 0;
  }



  /*
    if (motor_right_ticks_act > motor_right_ticks_set)
    {
      motor_right_pwm = motor_right_pwm - 1;
    }
    else
    {
      motor_right_pwm = motor_right_pwm + 10;
    }

    if (motor_left_ticks_act > motor_left_ticks_set)
    {
      motor_left_pwm = motor_left_pwm - 1;
    }
    else
    {
      motor_left_pwm = motor_left_pwm + 10;   //was 10
    }
  */
  // Serial.print("motor_left_speed act");
  // Serial.print("\t");
  // Serial.print(motor_left_ticks_act /motor_ticks_cm ); // (ticks/sec) / (ticks/cm)
  //Serial.print("\t");
  Serial.print("Delta");
  Serial.print("\t");
  Serial.print(motor_left_total_ticks - motor_right_total_ticks  );
  Serial.print("\t");
  Serial.print("Right_PWM");
  Serial.print("\t");
  Serial.print(motor_right_pwm );
  Serial.print("\n");
  motor_right_total_ticks = motor_right_ticks_act + motor_right_total_ticks;
  motor_left_total_ticks = motor_left_ticks_act + motor_left_total_ticks;
  motor_right_ticks_act = 0;
  motor_left_ticks_act = 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Will update both encoder value through serial port
void Update_Encoders()
{

  Serial.print("left total ticks");
  Serial.print("\t");
  Serial.print(motor_left_total_ticks);
  Serial.print("\t");
  Serial.print("right_total ticks");
  Serial.print("\t");
  Serial.print(motor_right_total_ticks);
  Serial.print("\t");



}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Update time function
void Update_Time()
{


  CurrentMicrosecs = micros();
  LastUpdateMillisecs = millis();
  MicrosecsSinceLastUpdate = CurrentMicrosecs - LastUpdateMicrosecs;
  if (MicrosecsSinceLastUpdate < 0)
  {
    ///// MicrosecsSinceLastUpdate = INT_MIN - LastUpdateMicrosecs + CurrentMicrosecs;

  }
  LastUpdateMicrosecs = CurrentMicrosecs;
  SecondsSinceLastUpdate = MicrosecsSinceLastUpdate / 1000000.0;

  Serial.print("time");
  Serial.print("\t");
  Serial.print(LastUpdateMicrosecs);
  Serial.print("\t");
  Serial.print(SecondsSinceLastUpdate);
  Serial.print("\n");


}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Motor running function


void moveRightMotor(float rightServoValue)
{
  if (rightServoValue > 0)  //forward
  {

    digitalWrite(Right_Motor_Pin_A, HIGH);
    digitalWrite(Right_Motor_Pin_B, LOW);
    analogWrite(Right_Motor_PWM, rightServoValue);

  }
  else if (rightServoValue < 0) //backwards
  {
    digitalWrite(Right_Motor_Pin_A, LOW);
    digitalWrite(Right_Motor_Pin_B, HIGH);
    analogWrite(Right_Motor_PWM, abs(rightServoValue));

  }

  else if (rightServoValue == 0)  // stopped
  {
    digitalWrite(Right_Motor_Pin_A, HIGH);
    digitalWrite(Right_Motor_Pin_B, HIGH);


  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void moveLeftMotor(float leftServoValue)
{
  if (leftServoValue > 0)  //forward
  {
    digitalWrite(Left_Motor_Pin_A, HIGH);
    digitalWrite(Left_Motor_Pin_B, LOW);
    analogWrite(Left_Motor_PWM, leftServoValue);
  }
  else if (leftServoValue < 0) //backwards
  {
    digitalWrite(Left_Motor_Pin_A, LOW);
    digitalWrite(Left_Motor_Pin_B, HIGH);
    analogWrite(Left_Motor_PWM, abs(leftServoValue));

  }
  else if (leftServoValue == 0)  //stopped
  {

    digitalWrite(Left_Motor_Pin_A, HIGH);
    digitalWrite(Left_Motor_Pin_B, HIGH);

  }


}
