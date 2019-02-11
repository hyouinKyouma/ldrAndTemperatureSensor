/*
 * ldr_and_temrature_sensor.c
 *
 * Created: 2/17/2018 2:01:16 PM
 *  Author: ADITYA
 */ 


#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#include <atmega/lcdheader.h>
#include <atmega/ADC.h>
#include <atmega/button.h>
#include <atmega/dcmotor.h>

int c=0,d=0;

void ASCII_conv_print(int c)
{
	unsigned char d[4];
	d[0]=c%10;
	d[1]=(c/10)%10;
	d[2]=(c/100)%10;
	d[3]=c/1000;
	for (int i=2;i>=0;i--)
	{
		ldta(d[i]+48);
	}
	
	
}
void street_light()
{
	ADC1;
	
	if (d!=ADC)
	{
		d=ADC;
		while(check_ADIF);
		if(c<512)
		PC3ON;
		else
		PC3OFF;
	}
	conv_start;
}

void thermometer()
{
	ADC2;
	lcmd(0x80);
	if (c!=ADC)
	{
		c=ADC;
		while(check_ADIF);
		int error=c/58;
		ASCII_conv_print(c/2-error);
		if((c/2-error)>=32)
			forward();
		else
			stop();
		
	}
	conv_start;
}

int main(void)
{
	DDRB=DDRC=DDRD=0xff;
	initialize_LCD(8,curon);
	ADCSRA=0XC3;
	
	
    while(1)
    {
		street_light();
		ADCSRA|=(1<<ADIF);
		thermometer();
		
        //TODO:: Please write your application code 
    }
}
