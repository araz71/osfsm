/*
 * io_scanner.c
 *
 *  Created on: Jul 28, 2022
 *      Author: Duman
 */

#include <io_scanner.h>
#include <assert.h>

typedef struct {
	GPIO_TypeDef *port;
	uint8_t pin;

	uint8_t state;
	uint64_t ts;
	uint8_t mode;

	void (*trig_callback)();
	void (*untrig_callback)();
} io_scanner_st;

static uint8_t io_cntr = 0;
static io_scanner_st ios[IO_SCANNER_MAX_AVAL];

void io_scanner_add(GPIO_TypeDef* port, uint8_t pin, uint8_t trig_is_high,
		void (*trig_callback)(void), void (*untrig_callback)(void))
{
	assert(io_cntr < IO_SCANNER_MAX_AVAL);

	ios[io_cntr].mode = trig_is_high;
	ios[io_cntr].pin = pin;
	ios[io_cntr].port = port;
	ios[io_cntr].trig_callback = trig_callback;
	ios[io_cntr].untrig_callback = untrig_callback;

	io_cntr++;
}

void io_scanner() {
	for (int i = 0; i < io_cntr; i++) {
		if (ios[i].state == 0) {
			if ((ios[i].mode && PIN_STATE(ios[i].port, ios[i].pin)) ||
					(!ios[i].mode && !PIN_STATE(ios[i].port, ios[i].pin)))
			{
				ios[i].ts = get_timestamp();
				ios[i].state = 1;
			}
		} else if (ios[i].state == 1) {
			if ((ios[i].mode && !PIN_STATE(ios[i].port, ios[i].pin)) ||
					(!ios[i].mode && PIN_STATE(ios[i].port, ios[i].pin)))
			{
				ios[i].state = 0;
			}

			if (delay_ms(ios[i].ts, 50)) {
				if (ios[i].trig_callback != NULL) ios[i].trig_callback();

				ios[i].state = 2;
			}

		} else if (ios[i].state == 2) {
			if ((ios[i].mode && !PIN_STATE(ios[i].port, ios[i].pin)) ||
					(!ios[i].mode && PIN_STATE(ios[i].port, ios[i].pin)))
			{
				ios[i].ts = get_timestamp();
				ios[i].state = 3;
			}

		} else if (ios[i].state == 3) {
			if (delay_ms(ios[i].ts, 50)) {
				if (ios[i].untrig_callback != NULL)
					ios[i].untrig_callback();

				ios[i].state = 0;
			}

			if ((ios[i].mode && PIN_STATE(ios[i].port, ios[i].pin)) ||
					(!ios[i].mode && !PIN_STATE(ios[i].port, ios[i].pin)))
			{
				ios[i].ts = get_timestamp();
			}
		}
	}
}
