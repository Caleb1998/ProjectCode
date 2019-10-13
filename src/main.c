/*nerwerw*/

#include <wiringPi.h>
#include <stdio.h> //For printf functions
#include <stdlib.h> // For system functions
#include <signal.h>//for keyboard interrupt
#include <math.h>
#include "CurrentTime.h"
#include <wiringPiSPI.h>

float readADC(int);
void initPorts();


int main(void){
//intializations
initPorts();
for(;;){

int hours = getHours();
int mins = getMins();
int secs = getSecs();

printf("Hour: %02d:%02d:%02d\n",hours,mins,secs);


float ch0_ADC =  readADC(0);
ch0_ADC = (ch0_ADC/1023)*3.3;
ch0_ADC = (ch0_ADC-0.5)/0.01;
printf("Voltage: %.0f C\n",ch0_ADC);
delay(1000);
//read anaolg voltage of pot

}//end of for

}//end of main

void initPorts(void){
//analog in for voltage divider 0V-3.3V translates to 
//set port 4 to input analog
wiringPiSetup();
pinMode(7, INPUT) ;

int z =wiringPiSPISetup (0, 1350000);//sets up spi channel 0 and sets freq=1.35MHz
if(z==-1){printf("Something wrong");}
}


float readADC(int channel){//channel specifies the analogue input

//SPI communication
//The ADC takes 3 8bit values as an input
unsigned char bufferADC[3];

bufferADC[0]=1;//start bit with 7 leading 0s (0b00000001)
bufferADC[1]=((0b1000+channel)<<4);//config bits, 0b1000=single ended communication(not differential)
bufferADC[2]= 0;//ADC doesnt care what these vals are
wiringPiSPIDataRW(0,bufferADC,3);//chan=0 (SPI channel=/=ADC channel)

float reading = ((bufferADC[1] & 0b11) <<8 ) + bufferADC[2];
return reading;//returns a value of 0-1023 (10-bit value)
}

