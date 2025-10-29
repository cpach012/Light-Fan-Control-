#include "fsl_device_registers.h"



int main(void){
	unsigned long i;


	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;	// Port B clock enable
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK; 	// Port C clock enable
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;	// Port D clock enable

	PORTB_GPCLR = 0x000C0100;	//Configure Port B Pin 2-3 for GPIO;
	PORTC_GPCLR = 0x01BF0100;	//configure PC[8:7, 5:0] for GPIO
	PORTD_GPCLR = 0x00FF0100;	//Configure Port D Pins 0-5 for GPIO;


	GPIOB_PDDR = 0x00000000;	//Configure Port B Pin 2-3 for Input;
	GPIOC_PDDR = 0x000001BF;	//Configure Port C Pins 0-5, 7-8 for Output;
	GPIOD_PDDR = 0x000000FF;	//Configure Port D Pins 0-5 for Output;

	PORTA_PCR1 = 0xA0100;			// Configure Port A  pin 1 for GPIO and interrupt on falling edge
//	PORTB_PCR10 = 0x100;			//Configure PORTB[10] for GPIO and to generate clock

	uint32_t ROT_DIR;// 1 for Clockwise- off
	// 0 for Counterclockwise  - on

	uint32_t ROT_SPD;// 0 for 22.5 degrees  - ON
	// 1 for 180 degrees  - OFF

	unsigned long speed_1 = 50000;
	unsigned long speed_2 = 20000;
	unsigned long speed_3 = 5000;

	uint32_t Input;

	uint32_t Photo; 	//photoresistor is C1
						//red is C2, green is C3, blue is C4


	uint32_t light_state;
	uint32_t motor_state;
	uint32_t user_light;
	uint32_t user_motor;
	uint32_t user_control;
	uint32_t light_bright;
	uint32_t light_color;
	uint32_t motor_speed;


	for(;;){
//		GPIOC_PDIR = 0x02; //photo
//		GPIOC_PDOR = 0x04; //red
//		GPIOC_PDOR = 0x08; //green
//		GPIOC_PDOR = 0x10; //blue



		Input = GPIOB_PDIR & 0x40C;                  //read Port B and bits 2-3 and 10;// Read PortB
		user_light = GPIOB_PDIR & 0x04;				 //switch 2
		user_motor = GPIOB_PDIR & 0x08;				//switch 3
		user_control = GPIOB_PDIR & 0x400;			//swtich 4


		//motor speed and state
		if(user_light == 0 && user_motor == 0){	// Clockwise and longDelay
			GPIOD_PDOR = 0x00;
			for (i=0; i<speed_1; i++);
			GPIOD_PDOR = 0x00;
			for (i=0; i<speed_1; i++);
			GPIOD_PDOR = 0x00;
			for (i=0; i<speed_1; i++);
			GPIOD_PDOR = 0x00;
			for (i=0; i<speed_1; i++);
		}
		else if(user_light == 0 && user_motor){	// Clockwise and speed_1
			GPIOD_PDOR = 0xD2;
			for (i=0; i<speed_1; i++);
			GPIOD_PDOR = 0xD1;
			for (i=0; i<speed_1; i++);
			GPIOD_PDOR = 0xE1;
			for (i=0; i<speed_1; i++);
			GPIOD_PDOR = 0xE2;
			for (i=0; i<speed_1; i++);
		}
		else if(user_light && user_motor == 0){	// clockwise and speed_2
			GPIOD_PDOR = 0xD2;
			for (i=0; i<speed_2; i++);
			GPIOD_PDOR = 0xD1;
			for (i=0; i<speed_2; i++);
			GPIOD_PDOR = 0xE1;
			for (i=0; i<speed_2; i++);
			GPIOD_PDOR = 0xE2;
			for (i=0; i<speed_2; i++);
		}
		else if(user_light && user_motor){	// Clockwise and speed_3
			GPIOD_PDOR = 0xD2;
			for (i=0; i<speed_3; i++);
			GPIOD_PDOR = 0xD1;
			for (i=0; i<speed_3; i++);
			GPIOD_PDOR = 0xE1;
			for (i=0; i<speed_3; i++);
			GPIOD_PDOR = 0xE2;
			for (i=0; i<speed_3; i++);
		}

	}

	return 0;
}
