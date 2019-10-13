/*nerwerw*/

#include <wiringPi.h>
#include <stdio.h> //For printf functions
#include <stdlib.h> // For system functions
#include <signal.h>//for keyboard interrupt
#include <math.h>
#include "CurrentTime.h"
#include <wiringPiSPI.h>



//FUNCTION DECLARATIONS
float readADC(int);
void initPorts();
float getTemp();
float getHumid();
float getLight();

//GLOBAL VARIABLES/CONSTANTS
float temp;
float humidity;
float light;

int main(void){
//intializations
initPorts();
for(;;){

int hours = getHours();
int mins = getMins();
int secs = getSecs();

printf("Time:%02d:%02d:%02d\t",hours,mins,secs);

temp = getTemp();
humidity = getHumid();
light = getLight();
printf("Temp:%.0fC\tHumid:%.1fV\tLight:%.0f\n",temp,humidity,light);
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
//The ADC takes 3, 8-bit values as an input
unsigned char bufferADC[3];

bufferADC[0]=1;//start bit with 7 leading 0s (0b00000001)
bufferADC[1]=((0b1000+channel)<<4);//config bits, 0b1000=single ended communication(not differential)
bufferADC[2]= 0;//ADC doesnt care what these vals are
wiringPiSPIDataRW(0,bufferADC,3);//chan=0 (SPI channel=/=ADC channel)

float reading = ((bufferADC[1] & 0b11) <<8 ) + bufferADC[2];
return reading;//returns a value of 0-1023 (10-bit value)
}



float getTemp(){
float temp = readADC(0);//0-1023
temp = (temp/1023)*3.3;//puts value into Volts
temp = (temp-0.5)/0.01;//equation for ambient temp, Ta = (Vout-V0*)/Tc
return temp;
}


float getHumid(){
float humid = readADC(1);//0-1023, channel 1
humid = (humid/1023)*3.3;//voltage
return humid;
}

float getLight(){//function could have been accomplished just by calling readADC(2) but for the same of congruenty it was added
float light = readADC(2);
return light;
}
