
# include "TFC.h"

//Entering the arena
void Entering(){
	flag=0;
	InitPIT1(30);
	while (Mainflag==1){
		wait();
		switch (flag){
			case 0 :						//הכנות + בדיקה אם הפתח מולנו
				if(flagpit1==1){
					Connect_IRsensor1;
					RGB_LED_OFF;
					BLUE_LED_ON;
					ServoFront(0);
					flag=5;
					if (IRsampling<560){
						side = 0;
						flag=1; 
						InitPIT1(100);
					}
					else{
					InitPIT1(20);
					}
				}
				break;
				
			case 5 :							//סריקת סרבו שמאל
				if(flagpit1==1){
					if (IRsampling<560){
						side = 1;
						ServoFront(0);
						flag=1; 
						InitPIT1(100);
					}
					else{
						flag=6;
						Servoscan(1);
						Connect_IRsensor2;
						InitPIT1(8);
					}
				}
				break;
				
			 case 6 :							//סריקת סרבו ימין
				if(flagpit1==1){
					if (IRsampling<560){
						AngleExit =	ServoAngle [1];	
						side = 2;
						ServoFront(0);
						flag=1; 
						Connect_IRsensor1;
						InitPIT1(100);
					}
					else{
						flag=5;
						Servoscan(2);
						Connect_IRsensor1;
						InitPIT1(8);
						if(ServoAngle [1] >=165){
							flag=1; 
							Connect_IRsensor1;
							InitPIT1(100);
						}
					}
				}
				break;
				
			 case 1 :										//התקדמות לקיר עד 10 סמ ממנו
				if(flagpit1==1){
					RGB_LED_OFF;
					GREEN_LED_ON;
					if (side==0){
						int q;
						Servo1SetPos(45);
						for(q=0;q<1000000;q++);
						distance0(1);
						dist = 0.707106*dist;
						distance2Driving ((int)dist,70);
						Mainflag=2;
						RGB_LED_OFF;
						BLUE_LED_ON;
						InitPIT1(50);
					}
					else {
						Servo1SetPos(0);
						distance0 (1);
						distance2Driving ((int)dist-20,70);
					}
					flag=2;
					InitPIT1(50);
				}
					break;
					
			 case 2 :										//פניה לכיוון הפתח,סיבוב חישן לכיוון הפתח
				 if(flagpit1==1){
					 if (side==0){			//כניסה מלפנים
						 flag=7; 
					 }
					 else{
						if (side==2){		//כניסה מימין
							Turnright();
							Servo1SetPos(90);
							Connect_IRsensor1;
						}
						else{				//כניסה משמאל
							Turnleft();
							Servo2SetPos(90);
							Connect_IRsensor2;
						}
						flag=3;
					 }
					InitPIT1(50);
				 }
				 break;
					
			 case 3 :										//התקדמות עד הגעה לפתח
				 if(flagpit1==1){
					distance2Driving (5,70);
					if (IRsampling<560){
						distance2Driving (18,70);
						flag=4;
						InitPIT1(30);
					}
					else {
						flag=3;
						InitPIT1(1);
					}
				 }
					break;
					
			 case 4 :										//סיבוב לכיוון הפתח
				 if(flagpit1==1){
				 	 if (side==2){	
				 		 Turnleft();
					}
				 	 else{
						Turnright();
					}
				 	flag=7;
				 	InitPIT1(50);
				 }
				 break;
			
			 case 7 : 										//כניסה לרחבה
				 if(flagpit1==1){
					distance2Driving (20,60);
					Mainflag=2;
					RGB_LED_OFF;
					BLUE_LED_ON;
					InitPIT1(50);
				 }
				 break;
		}
	}
}

//Inside the arena
void Inside(){
	RGB_LED_ON;
	dist=0;
	flag=0;
	ServoFront(0);
	InitPIT1(80);
	while (Mainflag==2){
		wait();
		switch (flag) {
		
			case 0 :							//הכנה
				if(flagpit1==1){							
					Connect_IRsensor1;
					ServoFront(0);
					RGB_LED_OFF;
					GREEN_LED_ON;
					flag=1;
					InitPIT1(20);
				}
				break;
				
			case 1 :							//תנועה לכיוון מרכז הזירה
				if(flagpit1==1){		
					distance2Driving (80,50);
					updateMap (80,12);
					flag=2;
					InitPIT1(20);
				}
				break;
			
			case 2 :							// הזזת סרבו לצידי הרכב לשם סריקה
				if(flagpit1==1){
					Servo1SetPos(90);
					Servo2SetPos(90);
					RGB_LED_OFF;
					GREEN_LED_ON;
					ChangeSpeed(60,12);
					flag=3;
					InitPIT1(20);
				}
				
				break;
				
			case 3 :							// מחפש מימין
				if(flagpit1==1){
					if (IRsampling > 650 && map[xLocation][yLocation+1]==0) {//650
						Motorsdir (0);
						side=1;
						Turnleft();
						RGB_LED_OFF;
						BLUE_LED_ON;
						Connect_IRsensor1;
						flag=5;
						InitPIT1(20);
					}
					else{
						Connect_IRsensor2;
						updateMap (1,12);
						flag=4;
						InitPIT1(27);
					}
				}
				break;
		
			case 4 :							//מחפש משמאל
				if(flagpit1==1){		
					if (IRsampling>650 && map[xLocation][yLocation-1]==0) {//650
						Motorsdir (0);
						side=2;	
						Turnright();
						RGB_LED_OFF;
						BLUE_LED_ON;
						Connect_IRsensor1;
						flag=5;
						InitPIT1(20);
					}
					else{
						Connect_IRsensor1;
						updateMap (1,12);
						flag=3;
						InitPIT1(27);	
					}
				}
				break;
				
			case 5 :	
				if(flagpit1==1){
					ServoFront(0);
					flag=6;
					InitPIT1(70);
				}
				break;	
				
				
			case 6 :									//בדיקת מרחק מהמטרה				
				if(flagpit1==1){
					distance0 (1);
					flag=7;
					InitPIT1(20);
				}
				break;
				
				
				
			case 7 :									//תנועה לכיוון המטרה
				if(flagpit1==1){
					distance2Driving ((int)dist,60);
					if (side==2){
						updateMap ((int)dist,9);
					}
					else{
						updateMap ((int)dist,3);
					}
					map[xLocation][yLocation]=3;
					flag=10;
					InitPIT1(50);
				}
				break;
				
				
			case 8 :								//דקירה של המטרה
				if(flagpit1==1){
					distance2Driving (10,60);
					if (side==2){
						updateMap (10,9);
					}
					else{
						updateMap (10,3);
					}
					map[xLocation][yLocation]=3;
					flag=9;
					InitPIT1(100);
				}
				break;
			
				
			case 9 :								//חזרה מדקירה של המטרה
				if(flagpit1==1){
					distance2REVERS (10,60);
					if (side==2){
						updateMap (10,3);
					}
					else{
						updateMap (10,9);
					}
					flag=10;
					InitPIT1(30);
				}
				break;
				
			case 10 :								//חזרה למרכז הזירה
				if(flagpit1==1){
					distance2REVERS ((int)dist,60);
					if (side==2){
						updateMap ((int)dist,3);
					}
					else{
						updateMap ((int)dist,9);
					}
					flag=11;
					InitPIT1(15);
				}
				break;
				
			case 11 :									//סיבוב לכיוון היציאה
				if(flagpit1==1){
					if (side==2){
						Turnleft();
						map[xLocation][yLocation+1]=1;
						map[xLocation-1][yLocation+1]=1;
//						map[xLocation-2][yLocation+1]=1;
						map[xLocation+1][yLocation+1]=1;
//						map[xLocation+2][yLocation+1]=1;
						
					}	
					else{	
						Turnright();
						map[xLocation][yLocation-1]=1;
						map[xLocation-1][yLocation-1]=1;
//						map[xLocation-2][yLocation-1]=1;
						map[xLocation+1][yLocation-1]=1;
//						map[xLocation+2][yLocation-1]=1;
						
						
						
					}
					flag=2;
					InitPIT1(40);
				}
				break;
		}
		if (xLocation<10){
			distance2Driving (20,60);
			updateMap (20,12);
			Mainflag = 3;	
			InitPIT1(8);
		}
	}
}

//Exit the arena
void Exit(){
	
	side=0;
	flag=0;
	Connect_IRsensor1;
	InitPIT1(40);
	while (Mainflag==1){
		wait();
		switch (flag){
			case 0 :
				if(flagpit1==1){
					ServoFront(0);
					flag=1;
					InitPIT1(50);
				}
				break;
				
			case 1 :
				if(flagpit1==1){
					if (IRsampling>1600){
						Mainflag=0;
						InitPIT1(50);
					}
					else{
						distance2Driving (5,60);
						flag=1;
						InitPIT1(8);					
					}	
				}
				break;	
		}
		
	}
	side=0;
	Mainflag=1;
	Entering();
	Mainflag = 4;
}

 
 void updateMap (int distance, int dir){
	 while (distance>=0){
		 map[xLocation][yLocation]=1;
		 switch (dir) {
				 case 12 :					//strait
					xLocation--;
					break;
				 case 3 :					//right
					yLocation++;
					break;
				 case 6 :					//left
					xLocation++; 	
					break;
				 case 9 :					//reverse
					yLocation--;
					break;
			 }
		 map[xLocation][yLocation]=2;
		 distance=distance-10;
	 }
 }
 

 void disco(){
	 int x=0;
	 int y=0;
	 while(y<20){
		 InitPIT1(100);
		 wait();
		 x++;
		 switch (x) {			
			 case 1 :					//אדום
				 RGB_LED_OFF;
				 RED_LED_ON;
				 break;
			 case 2 :					
				 RGB_LED_OFF;
				 RED_LED_ON;
				 GREEN_LED_ON;
				break;
				
			 case 3 :					
				 RGB_LED_OFF;
				 RED_LED_ON;
				 BLUE_LED_ON;
				break;
				
			 case 4 : 					//ירוק
				 RGB_LED_OFF;
				 GREEN_LED_ON;
				break;
				
			 case 5 :	
				 RGB_LED_OFF;
				 GREEN_LED_ON;
				 BLUE_LED_ON;
				 break;
				
			 case 6 :					//כחול
				 RGB_LED_OFF;
				 BLUE_LED_ON;
				break;
				
			 case 7 :					//לבן
				 RGB_LED_OFF;
				 RED_LED_ON;
				 GREEN_LED_ON;
				 BLUE_LED_ON;
				 x=0;
				 y++;
				break;
		 }
	 }
 }
 
 
