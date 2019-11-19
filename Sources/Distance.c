/*
 * Distance.c
 *
 *  Created on: Jun 26, 2017
 *      Author: idan
 */

# include "TFC.h"

int CardRangesR [28] = {3170,2977,2700,2432,2105,1838,1645,1461,1351,1251
						,1105,989,923,868,837,811,753,724,689,676
						,649,637,601,602,634,582,569,552};
int CardRangesL [28] = {3246,2983,2611,2383,2103,1885,1626,1530,1375,1290
						,1175,1102,1028,997,972,864,822,789,758,709
						,688,659,604,577,588,570,503,501};



void distance0 (int dir){
	 if (dir==2){
		 distance2(); 
	 }
	 else {
		 distance1();
	 }
	 dir +=10;
 }
 
 
void distance1 (){
	dist = IRsampling;
	int k;
	for (k=0;k<29&&dist<CardRangesL[k];k++);
	if (k==29){
		dist = 150;
	}
	else{
		int delta = CardRangesL[k]- CardRangesL[k-1];
		dist = dist-CardRangesL[k-1];
		dist = 15+(5*k)+(dist/delta);
	}
}
	 
void distance2 (){	
	dist = IRsampling;
	int k;
	for (k=0;k<29&&dist<CardRangesR[k];k++);
	if (k==29){
		dist = 150;
	}
	else{
		int delta = CardRangesR[k]- CardRangesR[k-1];
		dist = dist-CardRangesR[k-1];
		dist = 15+(5*k)+(dist/delta);
	}
}

void set_CardRanges(){
	Connect_IRsensor1;//
	int index =0;
	InitPIT1(300);	
	while (index < 30){
		RGB_LED_OFF;
		GREEN_LED_ON;
		wait();
		if (flagpit1==1){
		RGB_LED_OFF;
		RED_LED_ON;
		CardRangesL[index]=IRsampling;
		index++;
		InitPIT1(100);
		wait();
		InitPIT1(300);
		}
	}
	
	Connect_IRsensor2;//
	index =0;
	InitPIT1(300);
	while (index <30){
			RGB_LED_OFF;
			GREEN_LED_ON;
			wait();
			if (flagpit1==1){
			RGB_LED_OFF;
			RED_LED_ON;
			CardRangesR[index]=IRsampling;
			index++;
			InitPIT1(100);
			wait();
			InitPIT1(300);
			}
		}
}


