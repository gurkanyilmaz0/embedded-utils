#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

#define RB_SIZE 64  // 2'nin kuvveti olmali (hizli modulo icin)

typedef struct {
    uint8_t buffer[RB_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
} RingBuffer_t;

void RB_Init(RingBuffer_t *rb);
bool RB_Push(RingBuffer_t *rb, uint8_t data);   // ISR-safe (tek yazici)
bool RB_Pop(RingBuffer_t *rb, uint8_t *data);   // ISR-safe (tek okuyucu)
bool RB_IsEmpty(RingBuffer_t *rb);
bool RB_IsFull(RingBuffer_t *rb);
uint16_t RB_Count(RingBuffer_t *rb);

#endif
