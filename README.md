# GW eYacht Embedded Systems 🚤

Firmware and hardware architecture for the George Washington University eYacht team, competing in the Promoting Electric Propulsion (PEP) competition. 

As the Embedded Systems Subteam Lead, this repository contains the modular C++ telemetry architecture and the custom KiCad circuit designs required to interface a 3.3V STM32 microcontroller with a high-voltage electric hydroplane.

## Hardware Architecture
A core challenge of this project is safely bridging low-voltage logic with the boat's 12V peripheral and 48V drive systems. 
*   **Custom PCB Integration:** Designed schematics to drive 12V analog meters and OLED dashboard UI elements directly from the STM32 Nucleo using IRLZ44N logic-level MOSFETs.
*   **Telemetry Routing:** Hardware integration of SN65HVD230 CAN transceivers to read motor controller data, alongside I2C sensor arrays (IMU/GPS) for real-time spatial data. 

*(Include the image_077f95.png image here in the final markdown)*

## Software Architecture
The firmware is built with a modular, sensor-agnostic C++ architecture to allow the telemetry package to be easily transferred between different boat hulls.
*   **Object-Oriented Sensor Polling:** Core logic abstracted into `common/` modules, allowing seamless swapping of I2C/UART devices (GPS, IMU) without rewriting the main execution loop.
*   **Data-Oriented Dashboard:** Translating raw CAN bus metrics into human-readable data structures to drive the physical pilot UI.

<img width="872" height="620" alt="image" src="https://github.com/user-attachments/assets/80df8fb0-1e2e-4da9-b091-2bc68cd2767b" />
