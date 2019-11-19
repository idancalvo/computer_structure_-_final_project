
# include "TFC.h"


//Change the power of motors: power(0-100) , side ( 0=Both , 1=left , 2=right ) 
 void MotorsSpeed (int power, int side){
	 int power1;
	 if (power>90){
		 power=90;
	 }
	 
	 if ( power<=0 ){
		 power1=0;
	 }
	 else{
		 power1 = (power * MUDULO_REGISTER)/100;
	 }
	 
	
	 switch (side) {
	 case 0 : 					//Both
		 TPM1_C0V = power1;
		 TPM2_C1V = power1-20;
		 EnginePower[0]=EnginePower[1]=power;
			break;
	 case 1 :					//left
		 TPM2_C1V = power1-20;
		 EnginePower[0] = power;
			break;
	 case 2 :					//right
		 TPM1_C0V = power1;
		 EnginePower[1] = power;
			break;
	 default:
	 		break;
	 }
 }
 
 void Motorsdir (int dir){
	 
	 switch (dir) {
	 	 	
	 	 case 0 :
	 		GPIOC_PDOR &= ~(PORT_LOC(5) +PORT_LOC(6)+ PORT_LOC(7)+PORT_LOC(10));
	 		break;
	 	 case 12 :					//strait
	 		GPIOC_PDOR &= ~(PORT_LOC(5) + PORT_LOC(7));
	 		GPIOC_PDOR |= PORT_LOC(6) + PORT_LOC(10);
	 		
	 			break;
	 	 case 3 :					//right
			GPIOC_PDOR |=  PORT_LOC(5) + PORT_LOC(10);
			GPIOC_PDOR &= ~(PORT_LOC(6) + PORT_LOC(7));
	 			break;
	 	 case 6 :					//left
	 		GPIOC_PDOR |= PORT_LOC(5) + PORT_LOC(7);
	 		GPIOC_PDOR &= ~(PORT_LOC(6) + PORT_LOC(10));
				break;
	 	 case 9 :					//reverse
	 		 GPIOC_PDOR |= PORT_LOC(6) + PORT_LOC(7);
	 		 GPIOC_PDOR &= ~(PORT_LOC(5) +  PORT_LOC(10));
				break;
	 	 default:
	 		// Default - Move forward [Right engine(1,0)],[Left engine(1,0)]
	 		 GPIOC_PDOR |= PORT_LOC(6) + PORT_LOC(10);
	 		 GPIOC_PDOR &= ~(PORT_LOC(5) + PORT_LOC(7));
	 	 		break;
	 }
 }
  
 void MotorsBalance (){
	 if (Enc1 > Enc2){
		 MotorsSpeed (EnginePower[0]-1,1);
	 }
	 else{
		 if (Enc1 < Enc2){
			 MotorsSpeed (EnginePower[0]+1,1);
		 }
	 }
	 indexBalance++;
 }
 
 void ChangeSpeed(int Speed,int dir){
 	 	Stop_TPM1;
 		Stop_TPM2;
 		MotorsSpeed (90,0);
 		Motorsdir (dir);
 	 	IR_En_TPM0_2;
 	 	IR_En_TPM0_3;
 		Start_TPM1;
 		Start_TPM2;
 		MotorsSpeed (Speed,0);
 }
 
 void distance2Driving (int distance, int speed){
		IR_Dis_TPM0_2;
		IR_Dis_TPM0_3;
		indexBalance = 1;
		Enc2=0;
		Enc1=0;
		cuntENC=0;
		int x=0;
		
	 	ChangeSpeed(speed,12);
		while (x==0){
			wait();
			if (cuntENC>(216*2)/10*distance){
				x=1;
			}
			if (cuntENC==3*indexBalance){
				MotorsBalance();
				Enc2=0;
				Enc1=0;
			}
		}
		
		MotorsSpeed (5,12);
		MotorsSpeed (0,0);
		Motorsdir (0);
		IR_Dis_TPM0_2;
		IR_Dis_TPM0_3;
		cuntENC=0;
	 }
 
 void distance2REVERS (int distance, int speed){
 		IR_Dis_TPM0_2;
 		IR_Dis_TPM0_3;
 		indexBalance = 1;
 		Enc2=0;
 		Enc1=0;
 		cuntENC=0;
 		int x=0;
 		
 	 	ChangeSpeed(speed,6);
 		while (x==0){
 			wait();
 			if (cuntENC>(216*2)/10*distance){
 				x=1;
 			}
 			if (cuntENC==3*indexBalance){
 				MotorsBalance();
 				Enc2=0;
 				Enc1=0;
 			}
 		}
 		
 		MotorsSpeed (5,6);
 		MotorsSpeed (0,0);
 		Motorsdir (0);
 		IR_Dis_TPM0_2;
 		IR_Dis_TPM0_3;
 		cuntENC=0;
 	 }
 
 void Turnright(){
	 	ChangeSpeed(40,3);
	 	int x=0;
	 	cuntENC=0;
	 	while(x==0){
	 		if (cuntENC>585)
	 			x=1;	
	 	}
	 	Motorsdir (0);
	 	MotorsSpeed (0,0);
		IR_Dis_TPM0_2;
		IR_Dis_TPM0_3;
 }
 
 void Turnleft(){
	 	ChangeSpeed(40,9);
	 	int x=0;
	 	cuntENC=0;
	 	while(x==0){
	 		if (cuntENC>585)
	 			x=1;	
	 	}
	 	Motorsdir (0);
	 	MotorsSpeed (0,0);
		IR_Dis_TPM0_2;
		IR_Dis_TPM0_3;
  }
 
 void RoundDahawin(){
 	ChangeSpeed(90,3);
  	int x=0;
  	while(x==0){
  		if (cuntENC>610*4)
  			x=1;	
  	}
  	Motorsdir (0);
  	IR_Dis_TPM0_2;
  	IR_Dis_TPM0_3;
  	cuntENC=0;
  }
