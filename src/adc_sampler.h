/*
 * adc_sampler.h
 *
 *  Created on: Aug 10, 2024
 *      Author: Duman
 */
#ifdef XXX

#ifndef ADC_SAMPLER_H_
#define ADC_SAMPLER_H_

#include <fsm.h>

#ifndef NUMBER_OF_ADC_CHANNELS
#error "Please define number of adc channels"
#endif

typedef uint8_t ChannelID;

ChannelID adc_add_channel(uint8_t channel);
uint16_t adc_get_value(uint8_t channel);

MAKE_FSM(adc_monitor);

#endif /* ADC_SAMPLER_H_ */
#endif
