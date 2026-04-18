Threat Model
Trust Boundaries
Firmware is a primary attack surface
Modem is isolated due to external network exposure
GPU drivers are considered semi-trusted
Key Risks
Baseband exploits (highest risk)
Closed firmware blobs
Supply chain hardware tampering
Mitigations
Verified boot (user-controlled keys)
Hardware isolation between modem and main SoC
Minimal privileged firmware
