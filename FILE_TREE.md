open-snapdragon/
├── README.md
├── ARCHITECTURE.md
├── FILE_TREE.md
├── docs/
│   ├── overview.md
│   ├── threat_model.md
│   ├── hardware_stack.md
│   ├── firmware_stack.md
│   ├── modem_strategy.md
│   └── gpu_strategy.md
│
├── hardware/
│   ├── cpu/
│   │   ├── risc_v_core_spec.md
│   │   ├── vector_extension.md
│   │   └── crypto_extensions.md
│   │
│   ├── gpu/
│   │   ├── vulkan_pipeline.md
│   │   ├── driver_architecture.md
│   │   └── tiling_engine_design.md
│   │
│   ├── npu/
│   │   ├── matrix_accelerator.md
│   │   ├── tensor_pipeline.md
│   │   └── ai_instruction_set.md
│   │
│   ├── isp/
│   │   ├── camera_pipeline.md
│   │   ├── libcamera_integration.md
│   │   └── calibration_system.md
│   │
│   ├── dsp/
│   │   ├── audio_pipeline.md
│   │   ├── sensor_fusion.md
│   │   └── realtime_processing.md
│   │
│   ├── modem/
│   │   ├── modular_radio_spec.md
│   │   ├── external_modem_interface.md
│   │   └── certification_strategy.md
│   │
│   ├── connectivity/
│   │   ├── wifi_bluetooth_stack.md
│   │   └── firmware_requirements.md
│   │
│   └── power/
│       ├── power_management.md
│       └── thermal_design.md
│
├── firmware/
│   ├── bootloader/
│   │   ├── coreboot_config.md
│   │   ├── u_boot_config.md
│   │   └── secure_boot_alternative.md
│   │
│   ├── microcode/
│   │   ├── cpu_microcode.md
│   │   └── gpu_firmware.md
│   │
│   └── runtime/
│       ├── device_init.md
│       └── hardware_abstraction.md
│
├── os/
│   ├── linux_kernel_config.md
│   ├── driver_model.md
│   └── system_integration.md
│
├── drivers/
│   ├── gpu_driver.md
│   ├── camera_driver.md
│   ├── audio_driver.md
│   ├── modem_driver_interface.md
│   └── sensor_drivers.md
│
├── security/
│   ├── threat_model.md
│   ├── secure_boot_chain.md
│   ├── hardware_root_of_trust.md
│   └── encryption_accelerators.md
│
├── tools/
│   ├── build_system.md
│   ├── simulation_env.md
│   ├── hardware_emulator.md
│   └── debug_tooling.md
│
└── research/
    ├── open_hardware_comparison.md
    ├── patent_landscape.md
    ├── modem_restrictions.md
    └── gpu_openness_report.md
