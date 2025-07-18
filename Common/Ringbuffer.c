

#include "Ringbuffer.h"

Ringbuffer_t rb;


void ringbuffer_init(Ringbuffer_t *rb)
{
    rb->head =0;
    rb->tail =0;
    rb->buffer = (uint8_t *)malloc(BUF_LEN * sizeof(uint8_t));
    if (rb->buffer == NULL) {
        // Handle memory allocation failure
        // For example, you could set an error flag or return an error code
        return;
    }
}
bool ringbuffer_write(Ringbuffer_t *rb, uint8_t data)
{
    uint16_t next_head = (rb->head + 1) % BUF_LEN;
    if (next_head == rb->tail) {
        // Buffer is full, cannot write
        return false;
    }
    rb->buffer[rb->head] = data;
    rb->head = next_head;
    return true; // Write successful
}
bool ringbuffer_read(Ringbuffer_t *rb, uint8_t *data)
{
    if (rb->head == rb->tail) {
        // Buffer is empty, cannot read
        return false;
    }
    *data = rb->buffer[rb->tail];
    rb->tail = (rb->tail +1) % BUF_LEN;
    return true; // Read successful
}




