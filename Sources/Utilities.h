/*
 
 */

// Start and Stop TPM
//			TPM0_SC |= TPM_SC_CMOD(1); 						//Start the TPM0 counter
//			TPM0_SC &= ~TPM_SC_CMOD(1); 					//Stop the TPM0 counter

//			TPM1_SC |= TPM_SC_CMOD(1); 						//Start the TPM1 counter
//			TPM1_SC &= ~TPM_SC_CMOD(1); 					//Stop the TPM1 counter

//			TPM2_SC |= TPM_SC_CMOD(1); 						//Start the TPM2 counter 
//			TPM2_SC &= ~TPM_SC_CMOD(1); 					//Stop the TPM2 counter


// Enables, Disables and Reset flags of Interrupt 

//			TPM0_SC |= TPM_SC_TOIE_MASK;					//Interrupt Enables TPM0
//			TPM0_SC &= ~TPM_SC_TOIE_MASK;					//Interrupt Disables TPM0
//			TPM1_SC |= TPM_SC_TOIE_MASK;					//Interrupt Enables TPM1
//			TPM1_SC &= ~TPM_SC_TOIE_MASK;					//Interrupt Disables TPM1
//			TPM2_SC |= TPM_SC_TOIE_MASK;					//Interrupt Enables TPM2
//			TPM2_SC &= ~TPM_SC_TOIE_MASK;					//Interrupt Disables TPM2

//			TPM0_C1SC |= TPM_CnSC_CHIE_MASK; 				//Interrupt Enables TPM0_CH1
//			TPM0_C1SC &= ~TPM_CnSC_CHIE_MASK;				//Interrupt Disables TPM0_CH1
//			TPM0_C2SC |= TPM_CnSC_CHIE_MASK; 				//Interrupt Enables TPM0_CH2
//			TPM0_C2SC &= ~TPM_CnSC_CHIE_MASK;				//Interrupt Disables TPM0_CH2
//			TPM0_C3SC |= TPM_CnSC_CHIE_MASK; 				//Interrupt Enables TPM0_CH3
//			TPM0_C3SC &= ~TPM_CnSC_CHIE_MASK; 				//Interrupt Disables TPM0_CH3
//			TPM0_C4SC |= TPM_CnSC_CHIE_MASK;				//Interrupt Enables TPM0_CH4
//			TPM0_C4SC &= ~TPM_CnSC_CHIE_MASK;				//Interrupt Disables TPM0_CH4

//			TPM1_C0SC |= TPM_CnSC_CHIE_MASK; 				//Interrupt Enables TPM1_CH0
//			TPM1_C0SC &= ~TPM_CnSC_CHIE_MASK; 				//Interrupt Disables TPM1_CH0
//			TPM1_C1SC |= TPM_CnSC_CHIE_MASK; 				//Interrupt Enables TPM1_CH1
//			TPM1_C1SC &= ~TPM_CnSC_CHIE_MASK; 				//Interrupt Disables TPM1_CH1

//			TPM2_C1SC |= TPM_CnSC_CHIE_MASK; 				//Interrupt Enables TPM2_CH1
//			TPM2_C1SC &= ~TPM_CnSC_CHIE_MASK; 				//Interrupt Disables TPM2_CH1

//			TPM0_STATUS |= 0x00001;							//Reset Interrupt flags TPM0
//			TPM1_STATUS |= 0x00001;							//Reset Interrupt flags TPM1
//			TPM2_STATUS |= 0x00001;							//Reset Interrupt flags TPM2


