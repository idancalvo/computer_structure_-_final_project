/*
 * ADCandDAC.h
 *
 *  Created on: Jun 26, 2017
 *      Author: idan
 */

#ifndef ADCANDDAC_H_
#define ADCANDDAC_H_

void InitADCs();
void ADC0_IRQ();
void InitDAC();
void InitADCs();
void ADC_Init();

#define POT_ADC_CHANNEL		 0

#endif /* ADCANDDAC_H_ */
