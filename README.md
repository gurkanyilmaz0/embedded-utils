# Embedded Utils — Hardware-Agnostic C Utilities 🔧

Reusable, portable embedded C utilities designed to be hardware-independent and unit-testable on a host PC before deployment to any microcontroller (tested against STM32F407, no HAL dependency).

The goal: write and verify core data-structure/algorithm logic on a host machine with fast iteration, then drop the same `.c`/`.h` files directly into firmware — no changes required.

---

## ✅ Included Modules

| Module | Status | Description |
|---|---|---|
| **Ring Buffer** | ✅ Done | Fixed-size circular buffer, single-producer/single-consumer, ISR-safe (no locks needed for 1 writer + 1 reader) |
| **CRC-8** | ✅ Done | Table-free CRC-8 (polynomial 0x07), byte-wise calculation for packet integrity checks |
| **Host Unit Tests** | ✅ Done | Standalone `gcc`-buildable test harness, no MCU/hardware required |

---

## 📁 File Structure

```
embedded-utils/
├── ring_buffer.h
├── ring_buffer.c
├── crc8.h
├── crc8.c
├── test_main.c
└── README.md
```

---

## 🧪 Why Host-Testable Matters

Embedded bugs are expensive to debug on real hardware (JTAG sessions, flashing cycles, no `printf` debugging in some setups). By keeping core logic hardware-agnostic (no register access, no `HAL_Delay`, no platform headers), these modules can be:

- Compiled and tested in seconds on a PC (`gcc`)
- Verified with `assert()`-based unit tests before ever touching a microcontroller
- Dropped into any MCU project (STM32, ESP32, AVR) without modification

---

## 🛠️ Build & Run (Host PC)

```bash
gcc -Wall -o test test_main.c ring_buffer.c crc8.c
./test
```

Expected output:
```
Ring buffer testleri gecti.
CRC8 sonucu: 0x??
Tum testler basariyla tamamlandi.
```

---

## 🔌 Usage on STM32 (or any MCU)

```c
#include "ring_buffer.h"
#include "crc8.h"

RingBuffer_t uart_rx_buf;

void USART_IRQHandler(void) {
    uint8_t byte = (uint8_t)USART_DR; // read from your UART data register
    RB_Push(&uart_rx_buf, byte);
}

int main(void) {
    RB_Init(&uart_rx_buf);
    uint8_t data[4] = {0x01, 0x02, 0x03, 0x04};
    uint8_t crc = CRC8_Calculate(data, sizeof(data));
    // ... attach crc to your telemetry frame
}
```

---

## 🚀 Roadmap

- [ ] Add CRC-16/CRC-32 variants
- [ ] Add fixed-size memory pool allocator (no dynamic heap)
- [ ] Add multi-producer/multi-consumer ring buffer variant with mutex support
- [ ] Port and validate on STM32F407 hardware (UART RX buffering use case)
