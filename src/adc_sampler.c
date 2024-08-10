/*
 * adc_sampler.c
 *
 *  Created on: Aug 10, 2024
 *      Author: Duman
 */

#include <adc_sampler.h>

#ifdef XXX

static uint16_t adc_values[NUMBER_OF_ADC_CHANNELS];
static uint8_t adc_channels[NUMBER_OF_ADC_CHANNELS];
static uint8_t channel_id_counter = 0;

ChannelID adc_add_channel(uint8_t channel) {
	if (channel_id_counter >= NUMBER_OF_ADC_CHANNELS) {
		assert(0);
	}

	adc_channels[channel_id_counter++] = channel;
	return channel_id_counter - 1;
}

uint16_t adc_get_value(uint8_t channel) {
	return adc_values[channel];
}

__attribute__((weak)) void adc_set_channel(uint8_t channel) {

}

__attribute__((weak)) void adc_start() {

}

__attribute__((weak)) uint16_t adc_value()  {
	return 1;
}

__attribute__((weak)) uint8_t adc_ready() {
	return 1;
}

MAKE_FSM(adc_monitor) {
	if (fsm->step == 0) {
		for (uint8_t adc_counter = 0; adc_counter < NUMBER_OF_ADC_CHANNELS; adc_counter++) {
			adc_values[adc_counter] = 0;
		}
		fsm->block_template = 0;
		FSM_JUMP(FSM_NEXT_STEP);
	} else if (fsm->step == 1) {
		adc_set_channel(adc_channels[fsm->block_template]);
		adc_start();
		FSM_JUMP_AFTER_JOB(&adc_ready, 100, FSM_NEXT_STEP);
	} else if (fsm->step == 2) {
		adc_values[fsm->block_template] = adc_value();
		fsm->block_template++;
		if (fsm->block_template >= channel_id_counter) {
			fsm->block_template = 0;
		}
		FSM_JUMP(1);
	}
}
#endif
