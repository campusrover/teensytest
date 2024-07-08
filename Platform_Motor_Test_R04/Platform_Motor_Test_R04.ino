//////////////////////////////////////////////
//   Brandeis Platform   Motor Test         //
//                                          //
//           http://www.educ8s.tv           //
/////////////////////////////////////////////

//Revision  001  convert to motor controller
// Rev03 changed pins to conform to other tests and LAB software
// Rev 04  previous generation CAT_Motor_Test_R03


//Define all the connections maps to the  Motor Controller

int Left_Motor_Pin_A = 20;
int Left_Motor_Pin_B  = 1;   //forward and backwards switched on CAT kitty 1 20

int Motor_Left_Speed   =  22; // use 21 (3.6 )and  22 because of Teensy 4.1 compatibility

int Right_Motor_Pin_A  = 6;
int Right_Motor_Pin_B  =  8;   //forward and backwards switched on CAT kitty 8 6

int Motor_Right_Speed    =  5;



boolean goesForward = false;
int distance = 100;
int speedSet = 20;
int MAX_SPEED = 250;
int MAX_SPEED_OFFSET = 0;









void setup() 
{
 

  // Defines the function of the pin.  pinMode ( pin name, input or output);
  pinMode(Motor_Left_Speed,  OUTPUT);
  pinMode(Left_Motor_Pin_A, OUTPUT);
  pinMode(Left_Motor_Pin_B, OUTPUT);
  pinMode(Right_Motor_Pin_A, OUTPUT);
  pinMode(Right_Motor_Pin_B, OUTPUT);
  pinMode(Motor_Right_Speed,  OUTPUT);


  moveStop(1000);



}

void loop() {
  
 moveLeftMotorForward(1000);    // move left motor for 1 second
 moveStop(1000);    // move stop for 1 second
 moveRightMotorForward(1000);    // move left motor for 1 second
 moveStop(5000);    // move stop for 5 second
 /*moveLeft(1000);    // move left for 1 second
 moveStop(1000);    // stop for 1 seconds
 moveRight(1000);   // move right for 1 second
  moveStop(1000);    // move stop for 3 second
*/ moveForward(2000); // move forward for 1 second
  moveStop(1000);    // move stop for 1 second
  moveBackward(2000);// move backwards for 1 second
  moveStop(5000);    // move stop for 5 second


}



/**********************************************************

 *  *                  Subroutines


 ********************************************************/


void moveForward(int g)          //forward
{

  digitalWrite(Right_Motor_Pin_A, HIGH);
  digitalWrite(Right_Motor_Pin_B, LOW);
  analogWrite(Motor_Right_Speed, MAX_SPEED);
  digitalWrite(Left_Motor_Pin_A, HIGH);
  digitalWrite(Left_Motor_Pin_B, LOW);
  analogWrite(Motor_Left_Speed, MAX_SPEED);


  delay(g );
}

void moveLeftMotorForward(int m)          //forward
{

  digitalWrite(Right_Motor_Pin_A, HIGH);
  digitalWrite(Right_Motor_Pin_B, HIGH);
  analogWrite(Motor_Right_Speed, 0);
  digitalWrite(Left_Motor_Pin_A, HIGH);
  digitalWrite(Left_Motor_Pin_B, LOW);
  analogWrite(Motor_Left_Speed, MAX_SPEED);


  delay(m);
}

void moveRightMotorForward(int l)          //forward
{

  digitalWrite(Right_Motor_Pin_A, HIGH);
  digitalWrite(Right_Motor_Pin_B, LOW);
  analogWrite(Motor_Right_Speed, MAX_SPEED);
  digitalWrite(Left_Motor_Pin_A, HIGH);
  digitalWrite(Left_Motor_Pin_B, HIGH);
  analogWrite(Motor_Left_Speed, 0);


  delay(l);
}

void moveBackward(int n)          //back
{
  digitalWrite(Right_Motor_Pin_A, LOW);
  digitalWrite(Right_Motor_Pin_B, HIGH);
  analogWrite(Motor_Right_Speed, MAX_SPEED);
  digitalWrite(Left_Motor_Pin_A, LOW);
  digitalWrite(Left_Motor_Pin_B, HIGH);
  analogWrite(Motor_Left_Speed, MAX_SPEED);

  delay(n );

}


void moveStop(int f)         //stop
{
  digitalWrite(Right_Motor_Pin_A, HIGH);
  digitalWrite(Right_Motor_Pin_B, HIGH);
  analogWrite(Motor_Right_Speed, 0);
  digitalWrite(Left_Motor_Pin_A, HIGH);
  digitalWrite(Left_Motor_Pin_B, HIGH);
  analogWrite(Motor_Left_Speed, 0);
  delay(f);
}


void moveRight(int d)        //right
{
  digitalWrite(Right_Motor_Pin_A, LOW);
  digitalWrite(Right_Motor_Pin_B, HIGH);
  analogWrite(Motor_Right_Speed, 0);
  digitalWrite(Left_Motor_Pin_A, LOW);
  digitalWrite(Left_Motor_Pin_B, HIGH);
  analogWrite(Motor_Left_Speed, MAX_SPEED);
  delay(d );
}


void moveLeft(int d)        //right
{
  digitalWrite(Right_Motor_Pin_A,LOW);
  digitalWrite(Right_Motor_Pin_B, HIGH);
  analogWrite(Motor_Right_Speed, MAX_SPEED);
  digitalWrite(Left_Motor_Pin_A, LOW);
  digitalWrite(Left_Motor_Pin_B, HIGH);
  analogWrite(Motor_Left_Speed, 0);
  delay(d );
}
