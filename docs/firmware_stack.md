Firmware Stack
Boot Chain
ROM → coreboot → U-Boot → Linux
Goals
Fully auditable boot process
No forced secure boot locks
User-controlled signing keys
Components
coreboot (primary firmware layer)
U-Boot (bootloader stage)
Minimal microcode blobs (if required)
