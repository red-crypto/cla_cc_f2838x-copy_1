

#ifndef COMMON_RINGBUFFER_H
#define COMMON_RINGBUFFER_H

#include "System_Header.h"

#define BUF_LEN 64 // Define the length of the ring buffer

typedef struct {
    uint8_t *buffer;
    uint16_t head;
    uint16_t tail;

} Ringbuffer_t;

extern Ringbuffer_t rb;

void ringbuffer_init(Ringbuffer_t *rb);
bool ringbuffer_write(Ringbuffer_t *rb, uint8_t data);
bool ringbuffer_read(Ringbuffer_t *rb, uint8_t *data);



#endif // COMMON_RINGBUFFER_H

