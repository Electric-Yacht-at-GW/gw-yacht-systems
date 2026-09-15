# Sensor Firmware & Telemetry

Firmware repository for sensor acquisition, telemetry, and driver development.

## Current Objective: Phase 1 (Scaffolding & Interfaces)
We have not finalized our target microcontroller yet. Our immediate goal is **interface planning without hardware-specific code**:
* Define clean C++ header interfaces (`.hpp`).
* Outline low-level polling, initialization, and conversion steps using structured pseudocode (`.cpp`).
* **Memory constraint:** Fixed buffers and structs only. No dynamic allocation (`new` / `malloc`).
* **Team workflow rule:** Do NOT push directly to `main`. Always create a feature branch and submit a Pull Request (PR).

## Repository Structure
```text
├── common/
│   ├── include/       # Sensor header interfaces (.hpp)
│   └── src/           # Driver logic & pseudocode (.cpp)
├── docs/              # Guides and architecture notes
│   ├── git_guide.md   # How to branch, commit, and open PRs
│   └── pseudocode.md  # How to format sensor pseudocode
├── boat_1/            # Boat 1 specific configurations
├── boat_2/            # Boat 2 specific configurations
└── README.md
