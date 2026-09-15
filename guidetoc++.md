# Quick C++ Cheat Sheet for Embedded Firmware

This guide covers the essential C++ concepts we use for our sensor and microcontroller firmware. 

---

## 1. Standard Types (Always use these)
Because microcontrollers have specific hardware architectures, we never use standard `int`. We use fixed-width types from `<cstdint>` so we know exactly how many bytes we are using.

* `uint8_t` : 1 byte, unsigned (0 to 255) - **Use for raw bus buffers (I2C/SPI).**
* `int16_t` : 2 bytes, signed (-32,768 to 32,767) - **Use for raw sensor data.**
* `uint32_t`: 4 bytes, unsigned - **Use for timestamps (millis).**
* `float`   : 4 bytes, decimal - **Use for final engineering units (e.g., 25.4 °C).**

---

## 2. Standard Library Rules
Microcontrollers do not have operating systems. Therefore, many standard C++ libraries will crash our build.
* **Allowed:** `<cstdint>` (types), `<cmath>` (math functions), `<cstring>` (memory manipulation).
* **Forbidden:** `<iostream>` (no standard console exists), `<string>`, and `<vector>`.

---

## 3. Headers (`.hpp`) vs. Source (`.cpp`)

### The Header (`.hpp`) -> "The Menu"
Declares *what* exists. This is where you define classes, structs, and function signatures.
```cpp
#pragma once         // Always put this at the top to prevent double-inclusions
#include <cstdint>

class MySensor {
public:
    bool init();     // Just the signature
private:
    uint8_t id_;     // Naming convention: trailing underscore for private variables
};
```

### The Source (`.cpp`) -> "The Recipe"
Defines *how* it works. This is where you write the actual logic.
```cpp
#include "my_sensor.hpp"

// Use ClassName::FunctionName to implement it
bool MySensor::init() {
    id_ = 0x48;
    return true;
}
```

---

## 4. How the Code Actually Executes
To understand why we split files, here is exactly what happens when the microcontroller turns on:

1. **Bootup:** The microcontroller turns on and immediately looks for the `main()` function to start executing.
2. **The Function Call:** As the CPU reads through `main()`, it encounters a function call (e.g., `my_sensor.init();`).
3. **The Bookmark & Jump:** The CPU saves its current exact location in `main()` to memory (creating a bookmark) and jumps to the physical memory address that holds the instructions for the called function.
4. **How it Knows Where to Jump (Compile vs. Link):** This jump address was calculated before the code was ever flashed to the board:
   * **The Compiler** reads the `.hpp` file to know how much RAM the variables need, and translates the `.cpp` file into raw machine code.
   * **The Linker** sees the function call in `main()`, finds the compiled machine code from the `.cpp` file, and glues them together by hardcoding the exact jump address.
5. **Execution:** The CPU runs the instructions inside the function.
6. **The Return:** Once the function finishes, the CPU retrieves its saved bookmark and jumps back to exactly where it left off in `main()` to continue the loop.

### Flash Memory Bloat (Crucial for Microcontrollers)
You might wonder: *"If a function takes up 100 bytes of space, why does it matter if those 100 bytes are near `main` or somewhere else?"*

It doesn't matter *where* it lives—it matters **how many times it gets copied**. Microcontrollers have extremely limited Flash memory (the physical space that holds your written code). 

* **The `.cpp` way (Jumping):** The compiler translates your function into machine code exactly **once**. It takes up exactly 100 bytes of Flash memory. Every time you call that function in `main`, the CPU just uses a tiny 4-byte "jump" instruction to visit those 100 bytes.
* **The `.hpp` way (Copy-Pasting):** Because headers are copy-pasted into every file that `#includes` them, the compiler might build that same 100-byte function multiple times. Even worse, the compiler often "inlines" header functions. This means instead of using a 4-byte jump instruction, it physically copy-pastes the entire 100-byte function into `main` *every single time you call it*. If you call that function 10 times in your code, you just burned 1,000 bytes of memory instead of 140 bytes.
---

## 5. Structs vs. Classes

* **Struct:** Use these for grouping plain data together (everything is public by default). We use these to pass data out of our sensors.
  ```cpp
  struct SensorData {
      float temperature;
      uint32_t timestamp;
  };
  ```

* **Class:** Use these for the sensor drivers themselves. Classes can hide internal variables (private) and expose only what is safe to use (public).

---

## 6. The Golden Rule of Embedded Memory
**Never use `new`, `malloc()`, or `std::vector`.** 

Dynamic memory can cause fragmentation and crash a microcontroller after running for a few hours. 
* **Do this:** Allocate fixed-size arrays inside your class.
  ```cpp
  uint8_t rx_buffer[8]; // Good! Fixed size known at compile time.
  ```

---

## 7. Passing Data (Value vs. Reference)

When passing standard types (`float`, `uint8_t`), just pass them normally (by value). But when passing large structs, pass by **reference** (`&`) so the system doesn't waste time and memory copying it.

```cpp
// BAD: Makes a complete copy of the struct in memory
void printData(SensorData data) { ... }

// GOOD: Just points to the original struct in memory
void printData(const SensorData& data) { ... }
```
