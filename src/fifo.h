#ifndef _FIFO_H_
#define _FIFO_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIFO_INIT_VALUE		0xFF

void fifo_init();

/*
 * Creates FIFO and returns it's id
 *
 * @param _ptr Pointer to FIFO container
 * @param _size Size of each element
 * @param _max_elem_aval Maximum size of FIFO
 * @return FIFO ID. you should keep this id.
 */
uint8_t fifo_req(uint8_t *_ptr, uint16_t _size, uint16_t _max_elem_aval);

/*
 * Pushs an object into FIFO
 *
 * @param _fifo_id FIFO ID which is returned in fifo_req
 * @param _data Pointer to object
 * @return 1 when pushes successfully. otherwise 0
 */
uint8_t fifo_push(uint8_t _fifo_id, uint8_t *_data);

/*
 * Checks if FIFO is full or not
 *
 * @param _fifo_id FIFO ID
 * @return 1 when FIFO is full otherwise 0.
 */
uint8_t fifo_full(uint8_t _fifo_id);

/*
 * Checks if FIFO is empty or not
 *
 * @param _fifo_id FIFO ID
 * @return 1 if FIFO is empty otherwise 0.
 */
uint8_t fifo_empty(uint8_t _fifo_id);

/*
 * Pops an object from FIFO
 *
 * @param _fifo_id FIFO ID
 * @return Pointer to an object. It should cast to your type.
 */
uint8_t *fifo_pop(uint8_t _fifo_id);

/*
 * Gets an object from FIFO
 *
 * @param _fifo_id FIFO ID
 * @return Pointer to an object. It should cast to your type.
 */
uint8_t *fifo_pop_stay(uint8_t _fifo_id);

/*
 * Removes an object from FIFO
 *
 * @param _fifo_id FIFO ID
 */
void fifo_free_elem(uint8_t _fifo_id);

/*
 * Clears a FIFO
 *
 * @param _fifo_id FIFO ID
 */
void fifo_clear(uint8_t _fifo_id);

/*
 * Returns size of FIFO
 *
 * @param _fifo_id FIFO ID
 * @return Size of FIFO
 */
uint16_t fifo_size(uint8_t _fifo_id);

#define BUILD_FIFO(NAME, TYPE, SIZE)			\
static TYPE fifo_##NAME[SIZE];					\
static uint8_t fifo_id_##NAME;					\
void init_##NAME() {							\
	fifo_id_##NAME = fifo_req((uint8_t*)fifo_##NAME, sizeof(TYPE), SIZE);	\
}												\
static void push_##NAME(TYPE* data) {					\
	fifo_push(fifo_id_##NAME, (uint8_t*)data);	\
}												\
static TYPE* pop_##NAME() {							\
	return (TYPE*)(fifo_pop(fifo_id_##NAME));	\
}                                               \
static uint8_t isempty_##NAME() {                      \
    return fifo_empty(fifo_id_##NAME);          \
}                                               \
__attribute__((unused)) static void clear_##NAME() {                          \
    fifo_clear(fifo_id_##NAME);                 \
}	\
__attribute__((unused)) static uint8_t size_##NAME() {	\
	return fifo_size(fifo_id_##NAME);	\
}

/* EXAMPLE :
    typedef struct {
        uint8_t code;
        uint8_t number;
    } event_st;
    PREPARE_FIFO(event, event_st, 20);)
    ...
    init_event();
    event_st ev{10, 20};
    push_event(&ev);
*/
#endif
