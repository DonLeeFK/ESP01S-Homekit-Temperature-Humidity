# ESP01S-Homekit-Temperature-Humidity
This is a implamentation of HomeKit Temperature and Humidity sensor on ESP-01S(ESP8266)

## Dependencies
SimpleDHT  
HomeKit-ESP8266

## Usage
First you need to fill in your wifi info in `wifi_info.h`.  
Build the project in Arduino/PlatformIO/Any IDE you fancy, upload it to your ESP01S in flash mode. Then you are ready to plugin and play.  
Or you can try to use the pre-built binary file, and upload it via 'esptool'(recommended).  
```
python3 -m pip install esptool
python3 -m esptool erase_flash
python3 -m esptool -b 115200 write_flash -fs 1MB -fm dout -ff 40m 0x0 firmware.bin

```

