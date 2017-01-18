/*

   e-Gizmo 7 segmenet LED Display board Unit

   This code is for seven segment display board.
   It is a count up and down display.


   Codes by e-Gizmo Mechatronix Central
   January 18, 2017
   
*/

int latchPin = 6;
int clockPin = 5;
int dataPin = 7;


int numbers[10]={
 //hgfedcba
  B10111111, //0
  B00000110, //1
  B11011011, //2
  B01001111, //3
  B11100110, //4
  B01101101, //5
  B11111101, //6
  B00000111, //7
  B11111111, //8
  B01101111}; //9
  

void setup() {
  //set pins to output so you can control the shift register
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
 
}

void loop() {
   for (int i = 0; i< 10; i++) 
   {
      registerWrite(numbers[i]);
    }
}


void registerWrite(int numberToDisplay) {
    Serial.println(numberToDisplay);  
  
    if(numberToDisplay < 257){  //we check this to avoid getting noise from the board.
      digitalWrite(latchPin, LOW);
      // shift out the bits:
      shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);  
  
      //take the latch pin high so the LEDs will light up:
      digitalWrite(latchPin, HIGH);
    }
    
    delay(1000);
} 