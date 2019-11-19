/*
 * BoardSupport.h
 *
 *  Created on: Jun 19, 2017
 *      Author: idan
 */
#include "TFC.h"

#ifndef BOARDSUPPORT_H_
#define BOARDSUPPORT_H_


#define TFC_HBRIDGE_EN_LOC			(uint32_t)(1<<21)
#define TFC_HBRIDGE_FAULT_LOC     	(uint32_t)(1<<20)

#define TFC_HBRIDGE_ENABLE			GPIOE_PSOR = TFC_HBRIDGE_EN_LOC	
#define TFC_HBRIDGE_DISABLE			GPIOE_PCOR = TFC_HBRIDGE_EN_LOC	

#define TFC_DIP_SWITCH0_LOC			((uint32_t)(1<<2))
#define TFC_DIP_SWITCH1_LOC			((uint32_t)(1<<3))
#define TFC_DIP_SWITCH2_LOC			((uint32_t)(1<<4))
#define TFC_DIP_SWITCH3_LOC			((uint32_t)(1<<5))

#define TFC_PUSH_BUTT0N0_LOC		((uint32_t)(1<<13))
#define TFC_PUSH_BUTT0N1_LOC		((uint32_t)(1<<17))	

#define TFC_BAT_LED0_LOC			((uint32_t)(1<<8))
#define TFC_BAT_LED1_LOC			((uint32_t)(1<<9))
#define TFC_BAT_LED2_LOC			((uint32_t)(1<<10))
#define TFC_BAT_LED3_LOC			((uint32_t)(1<<11))
//-------------  RGB LEDs ---------------------------------------------
#define RED_LED_LOC	         		((uint32_t)(1<<18))
#define GREEN_LED_LOC	         	((uint32_t)(1<<19))
#define BLUE_LED_LOC	         	((uint32_t)(1<<1))
#define PORT_LOC(x)        	        ((uint32_t)(1<<x))

#define RED_LED_OFF          		GPIOB_PSOR |= RED_LED_LOC
#define GREEN_LED_OFF	         	GPIOB_PSOR |= GREEN_LED_LOC
#define BLUE_LED_OFF	            GPIOD_PSOR |= BLUE_LED_LOC
#define RGB_LED_OFF	                RED_LED_OFF,GREEN_LED_OFF,BLUE_LED_OFF

#define RED_LED_TOGGLE          	GPIOB_PTOR |= RED_LED_LOC
#define GREEN_LED_TOGGLE	        GPIOB_PTOR |= GREEN_LED_LOC
#define BLUE_LED_TOGGLE	            GPIOD_PTOR |= BLUE_LED_LOC
#define RGB_LED_TOGGLE	            RED_LED_TOGGLE,GREEN_LED_TOGGLE,BLUE_LED_TOGGLE

#define RED_LED_ON          		GPIOB_PCOR |= RED_LED_LOC
#define GREEN_LED_ON	         	GPIOB_PCOR |= GREEN_LED_LOC
#define BLUE_LED_ON	                GPIOD_PCOR |= BLUE_LED_LOC
#define RGB_LED_ON	                RED_LED_ON,GREEN_LED_ON,BLUE_LED_ON

//------------- TPM ---------------------------------------------

//Start and Stop TPM
#define Start_TPM0					TPM0_SC |= TPM_SC_CMOD(1)
#define	Stop_TPM0					TPM0_SC &= ~TPM_SC_CMOD(1)
#define Start_TPM1					TPM1_SC |= TPM_SC_CMOD(1)
#define	Stop_TPM1					TPM1_SC &= ~TPM_SC_CMOD(1)
#define Start_TPM2					TPM2_SC |= TPM_SC_CMOD(1)
#define	Stop_TPM2					TPM2_SC &= ~TPM_SC_CMOD(1)

// Enables and Disables TPM Interrupt 
#define	IR_En_TPM0					TPM0_SC |= TPM_SC_TOIE_MASK
#define	IR_Dis_TPM0					TPM0_SC &= ~TPM_SC_TOIE_MASK
#define	IR_En_TPM1					TPM1_SC |= TPM_SC_TOIE_MASK
#define	IR_Dis_TPM1					TPM1_SC &= ~TPM_SC_TOIE_MASK
#define	IR_En_TPM2					TPM2_SC |= TPM_SC_TOIE_MASK
#define	IR_Dis_TPM2					TPM2_SC &= ~TPM_SC_TOIE_MASK

#define	IR_En_TPM0_0
#define	IR_Dis_TPM0_0

#define	IR_En_TPM0_1				TPM0_C1SC |= TPM_CnSC_CHIE_MASK
#define	IR_Dis_TPM0_1				TPM0_C1SC &= ~TPM_CnSC_CHIE_MASK
#define	IR_En_TPM0_2				TPM0_C2SC |= TPM_CnSC_CHIE_MASK
#define	IR_Dis_TPM0_2				TPM0_C2SC &= ~TPM_CnSC_CHIE_MASK
#define	IR_En_TPM0_3				TPM0_C3SC |= TPM_CnSC_CHIE_MASK
#define	IR_Dis_TPM0_3				TPM0_C3SC &= ~TPM_CnSC_CHIE_MASK
#define	IR_En_TPM0_4				TPM0_C4SC |= TPM_CnSC_CHIE_MASK
#define	IR_Dis_TPM0_4				TPM0_C4SC &= ~TPM_CnSC_CHIE_MASK

#define	IR_En_TPM1_0				TPM1_C0SC |= TPM_CnSC_CHIE_MASK
#define	IR_Dis_TPM1_0				TPM1_C0SC &= ~TPM_CnSC_CHIE_MASK
#define	IR_En_TPM1_1				TPM1_C1SC |= TPM_CnSC_CHIE_MASK
#define	IR_Dis_TPM1_1				TPM1_C1SC &= ~TPM_CnSC_CHIE_MASK

#define	IR_En_TPM2_1				TPM2_C1SC |= TPM_CnSC_CHIE_MASK
#define	IR_Dis_TPM2_1				TPM2_C1SC &= ~TPM_CnSC_CHIE_MASK

//Reset flags of Interrupt TPM
#define Reset_IR_flags_TPM0			TPM0_STATUS |= 0x00001
#define Reset_IR_flags_TPM1			TPM1_STATUS |= 0x00001
#define Reset_IR_flags_TPM2			TPM2_STATUS |= 0x00001

//------------- PIT ---------------------------------------------

//Start and Stop PIT
#define Start_PIT0 					PIT_TCTRL0 |= 0x01
#define Stop_PIT0 					PIT_TCTRL0 &= 0x06
#define Start_PIT1 					PIT_TCTRL1 = PIT_TCTRL_TEN_MASK
#define Stop_PIT1 					PIT_TCTRL1 &= 0x06
#define Start_PIT2 					PIT_TCTRL2 = PIT_TCTRL_TEN_MASK
#define Stop_PIT2 					PIT_TCTRL2 &= 0x06
// Enables and Disables PIT Interrupt
#define	IR_En_PIT0					PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK				
#define	IR_Dis_PIT0					PIT_TCTRL0 &= 0x05
#define	IR_En_PIT1					PIT_TCTRL1 |= PIT_TCTRL_TIE_MASK				
#define	IR_Dis_PIT1					PIT_TCTRL1 &= 0x05
//Reset flags of Interrupt PIT
#define Reset_IR_flags_PIT0			PIT_TFLG0 = PIT_TFLG_TIF_MASK
#define Reset_IR_flags_PIT1			PIT_TFLG1 = PIT_TFLG_TIF_MASK

//---------------------------------------------------------------------

//------------- ADC ---------------------------------------------

#define Connect_IRsensor2			ADC0_SC1B = ADC_SC1_ADCH(6) + ADC_SC1_AIEN_MASK //Connecting to the current sensor1
#define Connect_IRsensor1 			ADC0_SC1B = ADC_SC1_ADCH(7) + ADC_SC1_AIEN_MASK; //Connecting to the current sensor1
#define IRsampling					ADC0_RB
//---------------------------------------------------------------------



void ClockSetup();

void InitGPIO();
void InitLED();
void InitDirnEng();

void InitTPM();

void InitTPM0();
void InitTPM0_CH1_US();
void InitTPM0_CH2_Enc();
void InitTPM0_CH2_US();
void InitTPM0_CH3_Enc();
void InitTPM0_CH3_US();
void InitTPM0_CH4_SER();

void InitTPM1();
void InitTPM1_CH0_LEn();
void InitTPM1_CH1_SER();

void InitTPM2();
void InitTPM2_CH1_REn();

void InitPIT0();
void InitPIT1();	
	

#endif /* BOARDSUPPORT_H_ */
