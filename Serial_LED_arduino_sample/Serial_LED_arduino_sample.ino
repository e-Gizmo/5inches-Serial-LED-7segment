/*
        e-Gizmo Serial LED 7segment Display Board I/F
 
        This code is for Serial Seven Segment LED  Display
        Unit. It is designed to make integration of LED 
        display to your circuit as easy as possible. You
        just nedd to send simple serial commands to display
        some numbers.

        Codes by e-Gizmo Mechatronix Central
        January 18 ,2017
        www.e-gizmo.com
 
 */
// comment out if you do not wish to enable crc checking
#define CRC_ENABLE
/*
 * Send a packet to Serial Display unit
 * The packet is wrapped with STX and ETX markers as required by the
 * Serial Display Unit
 * txstring - message string to send
 */
#define  STX 0x02
#define  ETX 0x03

#define LEDADDR 5 // led controller device ID. Change according to your own           // setting

void setup(){
  Serial.begin(9600);
  
  //Initialize and test Serial Display
  init_display();

}

void loop(){


// Put your codes here//


}

/*
 * Initialize and 8test Serial Display unit
 */
void  init_display(void){

  /* setup serial LED for panels
      P - set number of installed display panels.
      example: Pn where n = 0 to F, n - number of panels
               P0, n=0=16 panels ; PF, n=F=15 panels ; P1, n=1=1 panel

      T - test Segments

  */
  send_to_display(LEDADDR,"P1");    // 1=1 panel
  delay(500);
  send_to_display(LEDADDR,"T");     // segment test, turns ON all segment for a second
  delay(1000);
 
 
  /* D - Display digits
     example: "D002" or "D012"
     where: D + start + size + todisplay
            start - start displaying in this position (0 to F)
            size - how many digits it will occupy (0 to F)
            to display - number string to display
  */
   //Display a "2" (1 digit display) starting in position 0
  send_to_display(LEDADDR,"D012");  
  delay(1000);
  
  //    #ifdef CRC_ENABLE
  //     //enable crc checking
  //    send_to_display(LEDADDR,"_CRC");
  //  
  //    #endif

}
//CRC-8 - based on the CRC8 formulas by
// Dallas/Maxim
//code released under the terms of the
// GNU GPL 3.0 license

uint8_t crc8_update(uint8_t crc, uint8_t data) {
  uint8_t updated = crc ^ data;
  for (uint8_t i = 0; i < 8; ++i) {
    if ((updated & 0x80 ) != 0) {
      updated <<= 1;
      updated ^= 0x07;
    }
    else {
      updated <<= 1;
    }
  }
  return updated;
}

uint8_t  cal_crc8(char *txstring){
  uint8_t  crc=0;
  char  *txptr=txstring;
  while(*txptr !=0){
    crc=crc8_update(crc,(uint8_t)*txptr);
    txptr++;
  }
  return(crc | 0x80); // see text
}
void  send_to_display(char addr, char *txstring){
  uint8_t  crc=0;
  char  *txptr=txstring;

#ifdef CRC_ENABLE

  //compute for crc8
  crc=crc8_update(crc,addr+0x30); // include device id in the calculation
  while(*txptr !=0){
    //Serial.print(*txptr,HEX);
    crc=crc8_update(crc,(uint8_t)*txptr);
    txptr++;
  }

  crc |= 0x80;
#endif

  Serial.write(STX);
  Serial.write(addr+0x30);
  Serial.print(txstring);

#ifdef CRC_ENABLE
  Serial.write(crc);
#endif

  Serial.write(ETX);

}








