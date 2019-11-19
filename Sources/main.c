/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


# include "TFC.h"

int main(void){

	ClockSetup();
	InitGPIO();
	InitTPM();
	ADC_Init();
	InitPIT0 ();
	
	
	Start_TPM0;
	Start_TPM1;
	Start_TPM2;
	
	RGB_LED_OFF;
	RED_LED_ON;
	Connect_IRsensor1;
	ServoFront(0);
	
	xLocation=59;
	yLocation=22;
	map[xLocation][yLocation]=2;
	
	Mainflag=0;
	indexBalance=1;
	side=1;
	
	InitPIT1(10);
	Connect_IRsensor1;
	wait();
	Mainflag=1;
	
	InitPIT1(400);
	
//	wait();
//	Turnleft();
//	Turnright();
//	distance2REVERS (100,60);
//	distance2Driving (100,60);
//	while(1);
	
	
	while(1){	
		wait();
		switch (Mainflag) {
				 case 1 : //כניסה לזירה	
					 Entering();
					 InitPIT1(80);
					 break;
				 case 2 ://בתוך הזירה
					 Inside();
					 InitPIT1(80);
					 break;
				 case 3 ://יציאה מהזירה
					 Exit();
					 InitPIT1(80);
					 break;
				 case 4 ://סיבוב ניצחון וכיבוי
					RoundDahawin();
					InitPIT1(30);
					wait();
					RoundDahawin();
					InitPIT1(30);
					wait();
					RoundDahawin();
					IR_Dis_TPM0_2;
					IR_Dis_TPM0_3;
					disco();
					Stop_TPM0;
					Stop_TPM1;
					Stop_TPM2;
					Mainflag=0;
					break;
			}
	}
	return 0;
}


//-----------------------------------------------------------------
//  TPM0 - ISR
//-----------------------------------------------------------------
void FTM0_IRQHandler(){
 	if(TPM0_STATUS & TPM_STATUS_CH2F_MASK && (TPM0_C2SC & TPM_CnSC_CHIE_MASK)){   							//Clock Rise Right Engine
 		Enc1++;
 	}
 	if(TPM0_STATUS & TPM_STATUS_CH3F_MASK && (TPM0_C3SC & TPM_CnSC_CHIE_MASK)){   							//Clock Rise Left Engine
 		Enc2++;
 	}
 	cuntENC++;
 	Reset_IR_flags_TPM0;
}

//-----------------------------------------------------------------
// PIT - ISR = Interrupt Service Routine
//-----------------------------------------------------------------
void PIT_IRQHandler(){
//	if(PIT_TFLG0 & 1){
//		Reset_IR_flags_PIT0;					//Turn off the Pit 0 Irq flag
//	}
	
	if(PIT_TFLG1 & 1){
		Stop_PIT1; 								//stop the PIT1
		flagpit1=1;
		
		Reset_IR_flags_PIT1;					//Turn off the Pit 1 Irq flag
		IR_Dis_PIT1;							//Disables Interrupt PIT1
	}
}




