# 🚀 Embedded C++ Driver for STM32F401CC

## 📌 Overview
This project implements an **embedded C++ driver** for the STM32F401CC microcontroller using **Object-Oriented Programming (OOP)**. It provides driver support for:
- **RCC (Reset and Clock Control) for enabling GPIO peripherals**
- **GPIO (General-Purpose Input/Output) abstraction**
- **LED Driver** built on top of GPIO

The project is designed to demonstrate **hardware abstraction and modular driver development** in **Embedded C++**, avoiding the use of the standard C++ library for portability.

---

## 🛠 Features
- **RCC Configuration:** Enables required GPIO peripherals.
- **GPIO Driver:** Provides abstraction for configuring and controlling GPIO pins.
- **LED Driver:** Encapsulates LED control with OOP principles.
- **Default Constructor Handling:**
  - Default constructors set **invalid values** to prevent unintended behavior.
  - No use of `std` library functions.

---

## 📂 Project Structure
```
├── include
│   ├── GPIO_Private.h   # GPIO register definitions
│   ├── GPIO.hpp         # GPIO driver header
│   ├── LED.hpp          # LED driver header
│   ├── STD_TYPES.h      # Standard type definitions (without stdlib)
│
├── src
│   ├── GPIO.cpp        # GPIO implementation
│   ├── LED.cpp         # LED implementation
│   ├── main.cpp        # Main application logic (Traffic Light Simulation)
│
├── README.md           # Project documentation
```

---

## 🔧 Hardware Used
- **Microcontroller:** STM32F401CC (ARM Cortex-M4)
- **Development Tools:**
  - VS Code with PlatformIO
  - STM32CubeIDE (Optional for debugging)

---

## 📜 Implementation Details

### 🏗 GPIO Driver
Provides functions to configure, read, and write GPIO pins.
- **Default Constructor:** Initializes invalid ports and pins.
- **Parameterized Constructor:** Initializes a valid GPIO pin.
- **Functions:**
  - `setMode(Mode mode)`: Configures the GPIO pin as input/output.
  - `write(Value value)`: Sets the pin high or low.

### 🏗 LED Driver
Encapsulates GPIO functionality for LED control.
- **Functions:**
  - `turnOn()`: Turns the LED on.
  - `turnOff()`: Turns the LED off.
  - `toggle()`: Toggles the LED state.
  - `enableRCC()`: Enables the RCC for the selected port.

---

## 🚀 How to Build and Flash
### **Using PlatformIO**
1. Open the project in **VS Code with PlatformIO**.
2. Click **Build** (✔️) to compile the code.
3. Locate the **firmware.elf** file in:
   ```
   .pio/build/genericSTM32F401CC/firmware.elf
   ```
4. Flash the **firmware.elf** using ST-Link or any flashing tool.
5. if you want hex file 

    ```
    arm-none-eabi-objcopy -O ihex .pio/build/genericSTM32F401CC/firmware.elf firmware.hex

    ```
---

## 🏎 Example Application (Traffic Light Simulation)
This application simulates a basic traffic light system using **three LEDs**:
- **Red** (Stop)
- **Yellow** (Get Ready)
- **Green** (Go)

```cpp
#include "LED.hpp"

void delay() {
    for (volatile int i = 0; i < 1000000; i++); // Simple delay for 1 second
}

int main()
{
    LED red(GPIO::GPIO_A, GPIO::PIN5);   // Red LED on PA5
    LED yellow(GPIO::GPIO_A, GPIO::PIN6); // Yellow LED on PA6
    LED green(GPIO::GPIO_A, GPIO::PIN7);  // Green LED on PA7
    
    while (1)
    {
        // Red Light (Stop)
        red.turnOn();
        yellow.turnOff();
        green.turnOff();
        delay();

        // Yellow Light (Get Ready)
        red.turnOff();
        yellow.turnOn();
        green.turnOff();
        delay();

        // Green Light (Go)
        red.turnOff();
        yellow.turnOff();
        green.turnOn();
        delay();
    }
    return 0;
}
```

---

## 📌 Notes
- **No Standard Library Usage:** This project avoids `std::` functions to keep it lightweight.
- **Hardware Registers Used Directly:** The drivers interact with hardware registers without HAL or third-party abstraction layers.
- **Extendable Architecture:** Additional GPIO-based peripherals can be added easily.

---

## 🏁 Future Enhancements
- Implement **button input handling**.
- Create a **PWM-based LED fading effect**.
- Add **UART debugging support**.

---


