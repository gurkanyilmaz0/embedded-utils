#include "ring_buffer.h"

void RB_Init(RingBuffer_t *rb) {
    rb->head = 0;
    rb->tail = 0;
}

bool RB_IsEmpty(RingBuffer_t *rb) {
    return rb->head == rb->tail;
}

bool RB_IsFull(RingBuffer_t *rb) {
    return ((rb->head + 1) & (RB_SIZE - 1)) == rb->tail;
}

uint16_t RB_Count(RingBuffer_t *rb) {
    return (rb->head - rb->tail) & (RB_SIZE - 1);
}

bool RB_Push(RingBuffer_t *rb, uint8_t data) {
    uint16_t next_head = (rb->head + 1) & (RB_SIZE - 1);
    if (next_head == rb->tail) return false; // dolu
    rb->buffer[rb->head] = data;
    rb->head = next_head;
    return true;
}

bool RB_Pop(RingBuffer_t *rb, uint8_t *data) {
    if (rb->head == rb->tail) return false; // bos
    *data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) & (RB_SIZE - 1);
    return true;
}
