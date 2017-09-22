/*
 * Browser-side program for off grid communication.  Bytes arriving on serial port
 * are sent out via RF.  Bytes arriving on RF are sent to browser on serial port.
 * 
 * 
 * in terminal 
 *              cd Documents/off-grid
 *              node index.js [port name]
 * 
 * in browser:  http://localhost:3000/
 */

#include <SoftwareSerial.h>


SoftwareSerial mySerial(2, 3);

const int EOT = '~';          // end of transmission character
const int BUFFER_SIZE = 150;  
char buffer[BUFFER_SIZE+1];   // buffer for incomming messages
int buffIdx=0;                // index into buffer

void setup()
{
  Serial.begin(9600);     // hw serial for node
  mySerial.begin(9600);   // sw serial for HC-12
  
  Serial.println("Starting Arduino");

}

// checkRF
//
// Bytes coming from RF are written to the serial port
// once the EOT character is recieved.
//
void checkRF()
{

  // if data from RF available
  if ( mySerial.available() )
  {

    int inCnt;

    // read it
    inCnt = mySerial.readBytesUntil(EOT,buffer,BUFFER_SIZE-1);

    // terminate buffer
    *(buffer + inCnt) = '\0';

    // send to serial port
    Serial.println(buffer);

  } // if


}

// checkSerial
//
// Bytes on the serial port are sent out via RF
//
void checkSerial()
{

  // if bytes on serial port
  if ( Serial.available() )
  {

    int inCnt;

    // read until end of transmission char
    inCnt = Serial.readBytesUntil(EOT,buffer, BUFFER_SIZE);

    // need to send EOT character
    buffer[inCnt++] = EOT;
    
    // terminate string
    buffer[inCnt] = '\0';

    // send bytes out RF
    mySerial.print(buffer);

  } // if

}

void loop()
{

  // look for incoming bytes from radio
  checkRF();

  // look for outgoing bytes from browser
  checkSerial();

}






