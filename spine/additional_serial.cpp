#include <Arduino.h>
#include <SPI.h>
#include <wiring_private.h>
#include "additional_serial.h"


void serial_setup()
{
  //Serial.begin(57600);
  
  //Serial1.begin(2000000);           // Begin Serial1
  Serial1.begin(115200);  
  //Serial3.begin(2000000); // Begin Serial3
  Serial.setTimeout(1);//milliseconds to wait for serial data
}

void serial_motor_controls(int motor_tag,
                           float DIR_PACK,
                           int serial_val)
{
  serial_val = abs(serial_val);
//  Serial.println(serial_val);
  Serial1.write((byte)0xAA); // recognize baud rate 
  Serial1.write((byte)motor_tag); // identify which motor to send packet to 
  Serial1.write((byte)DIR_PACK); // forwards or backwards 
  Serial1.write(serial_val & 0x1F); // speed packet 1
  Serial1.write(serial_val >> 5); // speed packet 2 
}

// The below is taken from the pololu example code page: https://www.pololu.com/docs/0J77/8.4
// returns the specified variable as an int. -1 is reserved for errors. fuctions calling this must convert from signed int to unsigned int if needed.
// returns -1 if there was a serial read error. 
int getVariable(unsigned char variableID)
{
  Serial1.write(0xA1);
  Serial1.write(variableID);
  int LSB = readByte();
  int MSB = readByte();
  if (LSB <0 or MSB<0){
    return -1;
  }
  else{
    return LSB + MSB<<8;
  }
}

// read a serial byte (returns -2, avoiding other message -1 information, if nothing received after the timeout expires)
int readByte()
{
  char c;
  if(Serial1.readBytes(&c, 1) == 0){ return -2; }
  return (byte)c;
}

// returns true if the motor controller sees no erros and is thus able to move. 
// returns false if the motor has an error. An error will prevent the motor from moving.
// returns false if there was a serial read error.
bool isMotorOFF (){
  if (getVariable(ERROR_STATUS)==0){
    return false;
  }
  else{
    return true;
  }
}

// returns the voltage read on the VIN pin of the motor controller in mV as a 16bit number. 
// returns 4294967295 is there was a serial read error. thus this function assumes the voltage at VIN will not be max unsigned int. output is -1 when no voltage at VIN
unsigned int getVIN(){
  return (unsigned int)getVariable(VIN_STATUS);
}
