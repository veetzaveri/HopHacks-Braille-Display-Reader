
#include "LedControl.h"
#include "binary.h"
#include <basicMPU6050.h> 
basicMPU6050<> imu;

int DISPLAY_WIDTH = 10;
String SENTENCE_INPUT="Hi! how are you?";

int myBrailleDots[256];
char textMatrix[10][10];

int frameXPosition = 0;
int frameYPosition = 0;
LedControl lc=LedControl(12,11,10,1);

unsigned long delaytime=1000;

void setup() {
  imu.setup();
  String output = textPreprocessing(SENTENCE_INPUT);
  
  
  myBrailleDots[32] = 0;  // blank is 000000
  myBrailleDots[33] = 14;  // exlamation mark is 001110
  myBrailleDots[34] = 7;  // double quote is 000111
  myBrailleDots[34] = 2;  // single quote is 000010
  myBrailleDots[40] = 15;  // left parenthesis is 001111
  myBrailleDots[41] = 15;  // right parenthesis is 001111
  myBrailleDots[42] = 1;
  myBrailleDots[44] = 8;  // comma is 001000
  myBrailleDots[46] = 13;  // period is 001101
  myBrailleDots[48] = 28; // 0 is 011100
  myBrailleDots[49] = 32; // 1 is 100000
  myBrailleDots[50] = 40; // 2 is 101000
  myBrailleDots[51] = 48; // 3 is 110000
  myBrailleDots[52] = 52; // 4 is 110100
  myBrailleDots[53] = 36; // 5 is 100100
  myBrailleDots[54] = 56; // 6 is 111000
  myBrailleDots[55] = 60; // 7 is 111100
  myBrailleDots[56] = 44; // 8 is 101100
  myBrailleDots[57] = 24; // 9 is 011000
  myBrailleDots[58] = 12; // colon is 001100
  myBrailleDots[59] = 10; // semicolon is 001010
  myBrailleDots[63] = 11; // question mark is 001011
  myBrailleDots[65] = 32; // A is 100000
  myBrailleDots[66] = 40; // B is 101000
  myBrailleDots[67] = 48; // C is 110000
  myBrailleDots[68] = 52; // D is 110100
  myBrailleDots[69] = 36; // E is 100100
  myBrailleDots[70] = 56; // F is 111000
  myBrailleDots[71] = 60; // G is 111100
  myBrailleDots[72] = 44; // H is 101100
  myBrailleDots[73] = 24; // I is 011000
  myBrailleDots[74] = 28; // J is 011100
  myBrailleDots[75] = 34; // K is 100010
  myBrailleDots[76] = 42; // L is 101010
  myBrailleDots[77] = 50; // M is 110010
  myBrailleDots[78] = 54; // N is 110110
  myBrailleDots[79] = 38; // O is 100110
  myBrailleDots[80] = 58; // P is 111010
  myBrailleDots[81] = 62; // Q is 111110
  myBrailleDots[82] = 46; // R is 101110
  myBrailleDots[83] = 26; // S is 011010
  myBrailleDots[84] = 30; // T is 011110
  myBrailleDots[85] = 35; // U is 100011
  myBrailleDots[86] = 43; // V is 101011
  myBrailleDots[87] = 29; // W is 011101
  myBrailleDots[88] = 51; // X is 110011
  myBrailleDots[89] = 55; // Y is 110111
  myBrailleDots[90] = 39; // Z is 100111
  myBrailleDots[97] = 32; // A is 100000
  myBrailleDots[98] = 40; // B is 101000
  myBrailleDots[99] = 48; // C is 110000
  myBrailleDots[100] = 52; // D is 110100
  myBrailleDots[101] = 36; // E is 100100
  myBrailleDots[102] = 56; // F is 111000
  myBrailleDots[103] = 60; // G is 111100
  myBrailleDots[104] = 44; // H is 101100
  myBrailleDots[105] = 24; // I is 011000
  myBrailleDots[106] = 28; // J is 011100
  myBrailleDots[107] = 34; // K is 100010
  myBrailleDots[108] = 42; // L is 101010
  myBrailleDots[109] = 50; // M is 110010
  myBrailleDots[110] = 54; // N is 110110
  myBrailleDots[111] = 38; // O is 100110
  myBrailleDots[112] = 58; // P is 111010
  myBrailleDots[113] = 62; // Q is 111110
  myBrailleDots[114] = 46; // R is 101110
  myBrailleDots[115] = 26; // S is 011010
  myBrailleDots[116] = 30; // T is 011110
  myBrailleDots[117] = 35; // U is 100011
  myBrailleDots[118] = 43; // V is 101011
  myBrailleDots[119] = 29; // W is 011101
  myBrailleDots[120] = 51; // X is 110011
  myBrailleDots[121] = 55; // Y is 110111
  myBrailleDots[122] = 39; // Z is 100111

  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);  
  Serial.begin(38400);
  fillMatrix(output);
//  debugMatrix();
//  drawFaces();
//  animateText();
  drawFrame(frameXPosition,frameYPosition);
}

void updateDisplay()
{
    drawFrame(frameXPosition, frameYPosition);
}

void drawFrame(int row, int col)
{
 writeCharacter(myBrailleDots[int(textMatrix[row][col])], 0, 0);
 writeCharacter(myBrailleDots[int(textMatrix[row][col+1])], 0, 1);
 writeCharacter(myBrailleDots[int(textMatrix[row][col+2])], 0, 2);
 writeCharacter(myBrailleDots[int(textMatrix[row+1][col])], 1, 0);
 writeCharacter(myBrailleDots[int(textMatrix[row+1][col+1])], 1, 1);
 writeCharacter(myBrailleDots[int(textMatrix[row+1][col+2])], 1, 2);    
}

void animateText()
{
  for(int i=0; i<(DISPLAY_WIDTH-i); i++)
  {
     for(int j=0; j<(DISPLAY_WIDTH - 2); j++)
     {
        drawFrame(i,j);
        delay(delaytime);
      }
  }
 }

bool canMove(int x, int y)
{
  if (x<0 or y<0)
  {
    return false;
    }

   if(x>8 or y>7)
   {
    return false;
    }
   return true;
  }
 
void fillMatrix(String text)
{
  for(unsigned int i =0;i< text.length(); i++)
  {
    textMatrix[int(ceil(i/10))][i%10] = text.charAt(i);
  }
}

String textPreprocessing(String input)
{
  String output="";
  for(unsigned int i =0;i< input.length(); i++)
  {
    if(int((input.charAt(i))>=65) && (int(input.charAt(i))<=90))
    {
      output+="*";
      
      }
     output+=input.charAt(i);
  }
  return output;
  }

void debugMatrix()
{
  for(int i=0;i<DISPLAY_WIDTH; i++)
  {
    for(int j=0;j<DISPLAY_WIDTH; j++)
    { 
      Serial.print(textMatrix[i][j]);
      Serial.print("\t");
      }
      Serial.println();
   }
}

void writeCharacter(int x, int row, int col) {
    lc.setLed(0, 0+5*row, 0+3*col, bitRead(x,5));
    lc.setLed(0, 0+5*row, 1+3*col, bitRead(x,4));
    lc.setLed(0, 1+5*row, 0+3*col, bitRead(x,3));
    lc.setLed(0, 1+5*row, 1+3*col, bitRead(x,2));
    lc.setLed(0, 2+5*row, 0+3*col, bitRead(x,1));
    lc.setLed(0, 2+5*row, 1+3*col, bitRead(x,0));
}

void clearBrailleMatrix()
{
  for (int i = 0; i < 256; i = i + 1) {
     myBrailleDots[i] = 32;
  }
}


void loop() 
{
    if (Serial.available())
      {
        String input = String(char(Serial.read()));
        Serial.println(input);
        if(input == "r")
        {
          if(canMove(frameXPosition, frameYPosition+1))
              frameYPosition += 1;
           
          }
         else if(input == "l")
        {
           if(canMove(frameXPosition, frameYPosition-1))
              frameYPosition -= 1;
          }
         else if(input == "u")
        {
           if(canMove(frameXPosition - 1, frameYPosition))
              frameXPosition -= 1;
          }
          else if(input == "d")
        {
           if(canMove(frameXPosition + 1, frameYPosition+1))
              frameXPosition += 1;
          }
          updateDisplay();
          delay(10);
      }
}
