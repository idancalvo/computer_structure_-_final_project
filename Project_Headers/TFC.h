/*
 * TFC.h
 *
 *  Created on: Apr 13, 2012
 *      Author: emh203
 */

#ifndef TFC_H_
#define TFC_H_

#define MUDULO_REGISTER 18750
//Servo Angle
#define MaxServoAngle1  1106   	//Angle 100 degrees
#define MinServoAngle1  426		//Angle 0 degrees
#define MaxServoAngle2  1582   	//Angle 170 degrees
#define MinServoAngle2  902		//Angle 70 degrees
#define OneServoAngle 68		//1 degrees

	int Mainflag;
	int flag;
	int flagpit1;
	int flagpit0;
	int EnginePower [2];  							//Engine power
	int ServoAngle [2];  							//Engine power
	
	int map [60][45];
	int xLocation,yLocation;
//	int targetsLOC [4][2];

		int indexBalance;

		int Enc1;
		int Enc2;
		int cuntENC;
		int side;
		
		//----IR----
		int AngleExit;
		double dist;

		
		

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
	
#include "Derivative.h"
#include "BoardSupport.h"
#include "arm_cm0.h"
#include "mcg.h"
#include "DCengine.h"
#include "ServoMotor.h"	
#include "func.h"	
#include "MKL25Z4.h"
#include "ADCandDAC.h"
#include "Distance.h"		
			


#endif /* TFC_H_ */
