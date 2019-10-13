/*nerwerw*/

#include <wiringPi.h>
#include <stdio.h> //For printf functions
#include <stdlib.h> // For system functions
#include <signal.h>//for keyboard interrupt
#include <math.h>
#include "CurrentTime.h"
#include <wiringPiSPI.h>


void initPorts();


int main(void){
//intializations
initPorts();
for(;;){

int hours = getHours();
int mins = getMins();
int secs = getSecs();

printf("Hour: %02d:%02d:%02d\n",hours,mins,secs);

//SPI communication
unsigned char bufferADC[3];
bufferADC[0]=1;
bufferADC[1]=((8+0)<<4);
bufferADC[2]= 0;
wiringPiSPIDataRW(0,bufferADC,3);

int potRead = ((bufferADC[1] & 0b11) <<8 ) + bufferADC[2];

printf("Voltage: %d V\n",potRead);
delay(1000);
//read anaolg voltage of pot

}//end of for

}//end of main

void initPorts(void){
//analog in for voltage divider 0V-3.3V translates to 
//set port 4 to input analog
wiringPiSetup();
pinMode(7, INPUT) ;

int z =wiringPiSPISetup (0, 1350000);//sets up spi channel 0 and sets freq=500kHz
if(z==-1){printf("Something wrong");}
}
