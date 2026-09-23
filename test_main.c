#include <stdio.h>
#include <assert.h>
#include "ring_buffer.h"
#include "crc8.h"

int main(void) {
    // Ring buffer testi
    RingBuffer_t rb;
    RB_Init(&rb);

    assert(RB_IsEmpty(&rb));
    assert(RB_Push(&rb, 0xAA));
    assert(RB_Push(&rb, 0xBB));
    assert(RB_Count(&rb) == 2);

    uint8_t val;
    assert(RB_Pop(&rb, &val) && val == 0xAA);
    assert(RB_Pop(&rb, &val) && val == 0xBB);
    assert(RB_IsEmpty(&rb));

    printf("Ring buffer testleri gecti.\n");

    // CRC8 testi
    uint8_t test_data[] = {0x01, 0x02, 0x03, 0x04};
    uint8_t crc = CRC8_Calculate(test_data, sizeof(test_data));
    printf("CRC8 sonucu: 0x%02X\n", crc);

    printf("Tum testler basariyla tamamlandi.\n");
    return 0;
}
