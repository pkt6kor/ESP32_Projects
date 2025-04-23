
# ESP32 OTA Ethernet Update Project (Olimex ESP32-EVB)

## Overview

This project enables over-the-air (OTA) firmware updates via Ethernet on the Olimex ESP32-EVB board using LAN8720 PHY.

## How It Works

- The device connects to your LAN using Ethernet.
- OTA server is initialized using the ArduinoOTA library.
- Upload firmware remotely using `espota.py` or Arduino IDE.

## Configuration

### platformio.ini
```ini
[env:ota_board]
platform = espressif32
board = esp32dev
framework = arduino
lib_deps = 
upload_protocol = espota
upload_port = 192.168.1.150
build_flags =
  -DARDUINO_RUNNING_CORE=1
```

## Uploading Firmware

### Step 1: Flash OTA Firmware (via USB)
Use PlatformIO or Arduino IDE to flash the first OTA firmware via USB.

### Step 2: OTA Update Over Network

Once device is running with Ethernet and OTA ready, use:
```bash
platformio run -e ota_board --target upload
```
Or use Arduino IDE -> Select Port with IP and upload.

## Note
Ensure the board is connected to the same subnet as your PC.
Use static IP or assign via DHCP reservation for reliability.

