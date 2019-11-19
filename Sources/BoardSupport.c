
# include "TFC.h"

void ClockSetup(){
	  
	pll_init(8000000, LOW_POWER, CRYSTAL,4,24,MCGOUT); //Core Clock is now at 48MHz using the 8MHZ Crystal
	
	//Clock Setup for the TPM requires a couple steps.
	//1st,  set the clock mux
	//See Page 124 of f the KL25 Sub-Family Reference Manual
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;// We Want MCGPLLCLK/2=24MHz (See Page 196 of the KL25 Sub-Family Reference Manual
	SIM_SOPT2 &= ~(SIM_SOPT2_TPMSRC_MASK);
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); //We want the MCGPLLCLK/2 (See Page 196 of the KL25 Sub-Family Reference Manual
	
	//Enable the Clock to the TPM0 and PIT Modules
	//See Page 207 of f the KL25 Sub-Family Reference Manual
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK + SIM_SCGC6_TPM2_MASK + SIM_SCGC6_TPM1_MASK + SIM_SCGC6_PIT_MASK;
	// TPM_clock = 24MHz , PIT_clock = 48MHz - its actually 100MHz!
}


// set I/O for switches and LEDs
void InitGPIO() {
	
	//enable Clocks to all ports
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK 
				| SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
	
	InitLED();
	InitDirnEng();
	
}

//GPIO Configuration - LEDs - Output
void InitLED() {	
		PORTD_PCR1 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;  			//Blue
		GPIOD_PDDR |= BLUE_LED_LOC; 								//Setup as output pin
		PORTB_PCR18 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; 			//Red  
	    PORTB_PCR19 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; 			//Green
	    GPIOB_PDDR |= RED_LED_LOC + GREEN_LED_LOC; 					//Setup as output pins
}

// configuration port Output for engine - Controls the direction of the engines
void InitDirnEng() {
	
		//   >>>>(Right engine)<<<< 
		PORTC_PCR5 = PORT_PCR_MUX(1); 	// assign PTC5 as GPIO - M1_IN1
		GPIOC_PDDR |= PORT_LOC(5); 		// PTC5 is Output
		
		PORTC_PCR6 = PORT_PCR_MUX(1); 	// assign PTC6 as GPIO - M1_IN2
		GPIOC_PDDR |= PORT_LOC(6);  	// PTC6 is Output

		//   >>>>(Left engine)<<<<
		PORTC_PCR7 = PORT_PCR_MUX(1); 	// assign PTC7 as GPIO - M2_IN1
		GPIOC_PDDR |= PORT_LOC(7); 		// PTC7 is Output
		
		PORTC_PCR10 = PORT_PCR_MUX(1); 	// assign PTC10 as GPIO - M2_IN2
		GPIOC_PDDR |= PORT_LOC(10); 	// PTC10 is Output

		
}

//all TPM Configuration
void InitTPM(){
	
	SIM_SCGC5 |= SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM1_MASK | SIM_SCGC6_TPM2_MASK;
	
	InitTPM0();
	InitTPM1();
	InitTPM2();
	
}
	
//TPM0	
void InitTPM0(){
	
	TPM0_SC = 0; 							//to ensure that the counter is not running At configuration
	TPM0_SC |= TPM_SC_PS(5);				//Prescaler Divide by 32, up-mode, counter-disable
	TPM0_MOD = MUDULO_REGISTER;				//PWM frequency of 40Hz = 24MHz/(32x18,750)
	TPM1_CONF = 0;							//behavior in debug and wait modes
	 
//	InitTPM0_CH1_US();						//TPM0_CH1 - PTD1 - UltraSonic_triger
	InitTPM0_CH2_Enc();						//TPM0_CH2 - PTC3 - Encoder Right engine 
//	InitTPM0_CH2_US();						//TPM0_CH2 - PTD2 - UltraSonic Echo
	InitTPM0_CH3_Enc();						//TPM0_CH3 - PTC4 - Encoder Left engine
//	InitTPM0_CH3_US();						//TPM0_CH3 - PTD3 - UltraSonic Echo
	InitTPM0_CH4_SER();						//TPM0_CH4 - PTE31 - Servo2 Right
	
	enable_irq(INT_TPM0-16); 				// Enable Interrupts 
	set_irq_priority (INT_TPM0-16,1);  		// Interrupt priority = 0 = max 
		
}
	
//TPM0_CH1 - PTD1 - UltraSonic_triger
void InitTPM0_CH1_US(){	
	TPM0_C1SC |= TPM_CnSC_MSB_MASK + TPM_CnSC_ELSB_MASK;  		// Mod: Edge-aligned PWM 
	PORTD_PCR1 = PORT_PCR_MUX(4); 								// PTD1 pin TPM0_CH1	
}
	
//TPM0_CH2 - PTC3 - Encoder Right engine 
void InitTPM0_CH2_Enc(){
	TPM0_C2SC |= TPM_CnSC_ELSA_MASK;  							// Mod : Input capture
	PORTC_PCR3 = PORT_PCR_MUX(4); 								// PTC3 pin TPM0_CH2 
}

//TPM0_CH2 - PTD2 - UltraSonic Echo
void InitTPM0_CH2_US(){
	TPM0_C2SC |= TPM_CnSC_ELSA_MASK;  							// Mod : Input capture
	PORTD_PCR2 = PORT_PCR_MUX(4); 								// PTD2 pin TPM0_CH2 
}
	
//TPM0_CH3 - PTC4 - Encoder Left engine 
void InitTPM0_CH3_Enc(){
	TPM0_C3SC |= TPM_CnSC_ELSA_MASK;  							// Mod : Input capture
	PORTC_PCR4 = PORT_PCR_MUX(4); 								// PTC4 pin TPM0_CH3		 	
}

//TPM0_CH3 - PTD3 - UltraSonic Echo
void InitTPM0_CH3_US(){
	TPM0_C3SC |= TPM_CnSC_ELSA_MASK;  							// Mod : Input capture
	PORTD_PCR3 = PORT_PCR_MUX(4); 								// PTD3 pin TPM0_CH3 
}

//TPM0_CH4 - PTE31 - Servo2 Right
void InitTPM0_CH4_SER(){
	TPM0_C4SC |= TPM_CnSC_MSB_MASK + TPM_CnSC_ELSB_MASK ;  		//Mod: Edge-aligned PWM
	PORTE_PCR31 = PORT_PCR_MUX(3); 								//PTE31 pin TPM0_CH4 
}	
		 		
//TPM1		
void InitTPM1(){ 
	
	TPM1_SC = 0; 							//to ensure that the counter is not running At configuration
	TPM1_SC |= TPM_SC_PS(5);				//Prescaler Divide by 1, up-mode, counter-disable
	TPM1_MOD = MUDULO_REGISTER;				//PWM frequency of 40Hz = 24MHz/(32x18,750)
	TPM1_CONF = 0;							//behavior in debug and wait modes
	
	InitTPM1_CH0_LEn();						//TPM1_CH0 - PTE20 - Left engine
	InitTPM1_CH1_SER();						//TPM1_CH1 - PT - Servo1 Left
	
	set_irq_priority (INT_TPM1-16,1);  		// Interrupt priority = 0 = max
}

//TPM1_CH0 - PTE20 - Left engine
void InitTPM1_CH0_LEn(){	
	TPM1_C0SC |= TPM_CnSC_MSB_MASK + TPM_CnSC_ELSB_MASK;  		//Mod: Edge-aligned PWM 
	PORTE_PCR20 = PORT_PCR_MUX(3); 								//PTE20 pin TPM1_CH0
}

//TPM1_CH1 - PTE21 - Servo1 Left
void InitTPM1_CH1_SER(){	
	TPM1_C1SC |= TPM_CnSC_MSB_MASK + TPM_CnSC_ELSB_MASK;  		//Mod: Edge-aligned PWM
	PORTE_PCR21 = PORT_PCR_MUX(3); 								// PTE21 pin TPM1_CH1
}

//TPM2
void InitTPM2(){
	
	TPM2_SC = 0; 									//to ensure that the counter is not running At configuration
	TPM2_SC |= TPM_SC_PS(5);						//Prescaler Divide by 1, up-mode, counter-disable
	TPM2_MOD = MUDULO_REGISTER;						//PWM frequency of 40Hz = 24MHz/(32x18,750)
	TPM2_CONF = 0; 									//behavior in debug and wait modes

	InitTPM2_CH1_REn();								//TPM2_CH1  - PTE23 - Right engine 
	
	set_irq_priority (INT_TPM2-16,1);  		// Interrupt priority = 0 = max	
}

//TPM2_CH1  - PTE23 - Right engine 
void InitTPM2_CH1_REn(){
	TPM2_C1SC |= TPM_CnSC_MSB_MASK + TPM_CnSC_ELSB_MASK;  		// Mod: Edge-aligned PWM
	PORTE_PCR23 = PORT_PCR_MUX(3); 								// PTE23 pin TPM2_CH1 	
}

//PIT0
void InitPIT0 (void){
	
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK; //Enable the Clock to the PIT Modules
	
	PIT_MCR = 0;
	// Timer 0
	PIT_LDVAL0 = 0xFFFF; // setup timer 0 for maximum counting period [(0xFFFF = 65535)/24MHz =  sec]
	PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;

	
}
//PIT1
void InitPIT1(int x){
	flagpit1=0;
	
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK; //Enable the Clock to the PIT Modules
	x = x * 0x3A980;
	PIT_MCR = 0;
	PIT_LDVAL1 = x; //[(0x16E3600 = 24M)/24MHz = 1sec]
	PIT_TCTRL1 |= PIT_TCTRL_TIE_MASK; // its interrupt
	PIT_TCTRL1 |= PIT_TCTRL_TEN_MASK;
	flagpit1=0;
	enable_irq(INT_PIT-16); //  //Enable PIT IRQ on the NVIC
	set_irq_priority(INT_PIT-16,1);  // Interrupt priority = 0 = max
	
	SIM_SOPT7 |= SIM_SOPT7_ADC0ALTTRGEN_MASK | SIM_SOPT7_ADC0PRETRGSEL_MASK | SIM_SOPT7_ADC0TRGSEL(4);//set up the adc-b and connect to pit0
}

	
