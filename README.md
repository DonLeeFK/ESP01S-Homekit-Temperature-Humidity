# HomeKit Temperature & Humidity Sensor using ESP-01S (ESP8266)

A compact implementation of an Apple HomeKit-compatible temperature and humidity sensor using the ESP-01S module.

## Features
- Real-time temperature & humidity monitoring via HomeKit
- Compatible with ESP-01S (ESP8266)
- Low-power operation
- Easy setup through iOS Home app

## Hardware Requirements
- ESP-01S module
- DHT11/DHT22 sensor
- USB-to-Serial adapter (for programming)
- 3.3V power supply

## Dependencies
- [SimpleDHT Library](https://github.com/winlinvip/SimpleDHT)
- [HomeKit-ESP8266](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266)

## Setup

### 1. Configure WiFi Credentials
Create `wifi_info.h` file with:
```cpp
const char ssid "Your_WiFi_SSID"
const char "Your_WiFi_Password"
```

## Usage
First you need to fill in your wifi info in `wifi_info.h`.  
Build the project in Arduino/PlatformIO/Any IDE you fancy, upload it to your ESP01S in flash mode. Then you are ready to plugin and play.  
Or you can try to use the pre-built binary file, and upload it via 'esptool'(recommended).  

python3 -m pip install esptool
python3 -m esptool erase_flash
python3 -m esptool -b 115200 write_flash -fs 1MB -fm dout -ff 40m 0x0 firmware.bin

```

