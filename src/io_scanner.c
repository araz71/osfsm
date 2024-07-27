/*
 * io_scanner.c
 *
 *  Created on: Jul 28, 2022
 *      Author: Duman
 */

#include <io_scanner.h>
#include <assert.h>

#ifdef IO_SCANNER_MAX_AVAL

#pragma pack(push)
#pragma pack(1)
typedef struct {
	uint8_t (*reader_callback)();
	uint8_t state;
	uint64_t ts;
	uint8_t mode;

	void (*trig_callback)();
	void (*untrig_callback)();
} io_scanner_st;
#pragma pack(pop)

static uint8_t io_cntr = 0;
static io_scanner_st ios[IO_SCANNER_MAX_AVAL];

void io_scanner_add(uint8_t (*reader_callback)(void), uint8_t trig_is_high,
		void (*trig_callback)(void), void (*untrig_callback)(void))
{
	assert(io_cntr < IO_SCANNER_MAX_AVAL);

	ios[io_cntr].mode = trig_is_high;
	ios[io_cntr].reader_callback = reader_callback;
	ios[io_cntr].trig_callback = trig_callback;
	ios[io_cntr].untrig_callback = untrig_callback;

	io_cntr++;
}

void io_scanner() {
	for (int i = 0; i < io_cntr; i++) {
		if (ios[i].state == 0) {
			if ((ios[i].mode && ios[i].reader_callback()) ||
					(!ios[i].mode && !ios[i].reader_callback()))
			{
				ios[i].ts = get_timestamp();
				ios[i].state = 1;
			}
		} else if (ios[i].state == 1) {
			if ((ios[i].mode && !ios[i].reader_callback()) ||
					(!ios[i].mode && ios[i].reader_callback()))
			{
				ios[i].state = 0;
			}

			if (delay_ms(ios[i].ts, 50)) {
				if (ios[i].trig_callback != NULL) ios[i].trig_callback();

				ios[i].state = 2;
			}

		} else if (ios[i].state == 2) {
			if ((ios[i].mode && !ios[i].reader_callback()) ||
					(!ios[i].mode && ios[i].reader_callback()))
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

			if ((ios[i].mode && ios[i].reader_callback()) ||
					(!ios[i].mode && !ios[i].reader_callback()))
			{
				ios[i].ts = get_timestamp();
			}
		}
	}
}

#endif
