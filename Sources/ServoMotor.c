
# include "TFC.h"

 //-----------------------------------------------------------------
 // Direction of motor Servo, left sensor
 //----------------------------------------------------------------- 
 void Servo1SetPos (int Servo1Position){
 	if (Servo1Position <= 180 && Servo1Position >= 0){
 		if (Servo1Position<=0){
 			TPM1_C1V = MinServoAngle1;
 			ServoAngle [0]= 0;
 			
 		}
 		else{
 			if (Servo1Position >= 100){
 				TPM1_C1V = MaxServoAngle1;
 				ServoAngle [0] = 100;
 			}
 			else {
 				TPM1_C1V = 426+68*Servo1Position/10;
 				ServoAngle [0] = Servo1Position;
 			}
 		}
 	}  
  }
  
 //-----------------------------------------------------------------
 // Direction of motor Servo, right sensor
 //----------------------------------------------------------------- 
 void Servo2SetPos (int Servo2Position){
 	if (Servo2Position <= 180 && Servo2Position >= 0){
 		if (Servo2Position <=70){
 			TPM0_C4V = MinServoAngle2;
 			ServoAngle [1] = 70;
 		}
 		else{
 			if (Servo2Position >= 170){
 				TPM0_C4V = MaxServoAngle2;
 				ServoAngle [1] = 170;
 			}
 			else {
 				TPM0_C4V = 426+68*(Servo2Position-10)/10;
 				ServoAngle [1] = Servo2Position;
 			}
 		}
 	}  
 }
 
 void ServoFront(int side){
	 switch (side) {
	 	 case 0 : 					//Both
	 		 Servo1SetPos (0);
	 		 Servo2SetPos (170);
	 			break;
	 	 case 1 :					//left
	 		 Servo1SetPos (0);
	 			break;
	 	 case 2 :					//right
	 		 Servo2SetPos (170);
	 			break;
	 	 default:
	 	 		break;
	 }
 }
 
 void Servoscan(int side){
	 if (side==1){
		 if (ServoAngle [0] >= 100){
			 ServoFront(1);
		 }
			else{		 
			Servo1SetPos (ServoAngle [0] + 6);
		 }
	 }
	 
	 if (side==2){
		 if (ServoAngle [1] <= 70){
			 ServoFront(2);
		 }
		 else{		 
			Servo2SetPos (ServoAngle[1] - 6);
		 }
	 }
 }
 
 

