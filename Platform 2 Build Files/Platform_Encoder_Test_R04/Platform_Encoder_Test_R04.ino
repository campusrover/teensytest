
/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * Brandeis University
 * 
 * Used with serial monitor
 * 
 * Forward movment results in positive numbers
 * 1 rev should equal around 3.2K counts
 * 
 * Rev 02 print out both left and right encoders on either change
 * Rev 04 updated for Platform encoder pins
 */

#include <Encoder.h>


///////////////////////////////////////////////////////////////
//Encoder pins definition  11 06 22

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

//   Low Performance:  neither pin has interrupt capability
Encoder LeftEnc(Left_Encoder_PinA, Left_Encoder_PinB);    // other encoder is pins    14,15 

Encoder RightEnc(Right_Encoder_PinA, Right_Encoder_PinB);    // other encoder is pins 11,12




long LeftoldPosition  = -999;
long RightoldPosition  = -999;


void setup() 
{
  // put your setup code here, to run once:
 // SetupEncoders()
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");


}

//////////////////////////////////////////////////////
void loop() 
{
 long LeftnewPosition = LeftEnc.read();
  long RightnewPosition = RightEnc.read();
  if ((LeftnewPosition != LeftoldPosition) || (RightnewPosition != RightoldPosition)) 
//   if (LeftnewPosition != LeftoldPosition) 
      {
    LeftoldPosition = LeftnewPosition;
    Serial.print("Left");
    Serial.print("\t");
    Serial.print( LeftnewPosition);
    Serial.print("\t");
 //     }

 
// long RightnewPosition = RightEnc.read();
//  if (RightnewPosition != RightoldPosition) 
 //     {
    RightoldPosition = RightnewPosition;
    Serial.print("Right");
    Serial.print("\t");
    Serial.print( RightnewPosition);
    Serial.print("\n");
   }


}


//SetupEncoders() Definition

void SetupEncoders()
{
  // Quadrature encoders  ************* note not used as quadrature encoder  we know what direction so we don't need the encoder to tell us
  // Left encoder
  pinMode(Left_Encoder_PinA, INPUT_PULLUP);      // sets pin A as input
  pinMode(Left_Encoder_PinB, INPUT_PULLUP);      // sets pin B as input
  //Attaching interrupt in Left_Enc_PinA.
  //attachInterrupt(Left_Encoder_PinA, do_Left_Encoder, RISING);


  // Right encoder
  pinMode(Right_Encoder_PinA, INPUT_PULLUP);      // sets pin A as input
  pinMode(Right_Encoder_PinB, INPUT_PULLUP);      // sets pin B as input
  //Attaching interrupt in Right_Enc_PinA.
 // attachInterrupt(Right_Encoder_PinA, do_Right_Encoder, RISING);

}
