🧠 Vision

An open, modular replacement for Snapdragon-class SoCs built on:

RISC-V compute
Open graphics pipeline
Modular AI + DSP
External or isolated modem system
Fully auditable firmware stack
🧩 System Stack
Apps
 ↓
Linux (mainline)
 ↓
Open drivers (Vulkan, libcamera, ALSA)
 ↓
HAL (hardware abstraction layer)
 ↓
RISC-V CPU + GPU + NPU + DSP
 ↓
coreboot / U-Boot
 ↓
Hardware
🔐 Design Principles
No vendor lock-in
Minimal proprietary firmware
Modular subsystems
User-controlled trust boundaries
⚠️ Core Constraints
Cellular modem: regulatory + patents
GPU: performance gap vs proprietary stacks
ISP: calibration data dependency
