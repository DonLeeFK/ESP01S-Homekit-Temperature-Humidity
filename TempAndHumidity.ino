/*
 *
 *This is a implementation of Homekit Temperature and Humidity sensor on ESP-01S(ESP8266)
 *modified by DonLeeFK
 *
 * So, if you want use this HomeKit library and other Arduino Libraries together,
 * 1. define your HomeKit accessory/service/characteristic in a .c file
 * 2. in your .ino, include some Arduino Libraries and you can use them normally
 *                  write extern "C" homekit_characteristic_t xxxx; to access the characteristic defined in your .c file
 *                  write your logic code (eg. read sensors) and
 *                  report your data by writing your_characteristic.value.xxxx_value = some_data; homekit_characteristic_notify(..., ...)
 * done.
 */

#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "wifi_info.h"
#include <SimpleDHT.h>
//include the Arduino library for your real sensor here, e.g. <DHT.h>. I'm using DHT22 in this instance.

int pinDHT22 = 0;
SimpleDHT22 dht22(pinDHT22);

#define LOG_D(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);

void setup() {
	Serial.begin(115200);
	wifi_connect(); // in wifi_info.h
	my_homekit_setup();
}

void loop() {
	my_homekit_loop();
	delay(10);
}

//==============================
// Homekit setup and loop
//==============================

// access your homekit characteristics defined in my_accessory.c
extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_temperature;
extern "C" homekit_characteristic_t cha_humidity;

static uint32_t next_heap_millis = 0;
static uint32_t next_report_millis = 0;

void my_homekit_setup() {
	arduino_homekit_setup(&config);
}

void my_homekit_loop() {
	arduino_homekit_loop();
	const uint32_t t = millis();
	if (t > next_report_millis) {
		// report sensor values every 10 seconds
		next_report_millis = t + 10 * 1000;
		my_homekit_report();
	}
	if (t > next_heap_millis) {
		// show heap info every 5 seconds
		next_heap_millis = t + 5 * 1000;
		LOG_D("Free heap: %d, HomeKit clients: %d",
				ESP.getFreeHeap(), arduino_homekit_connected_clients_count());

	}
}


void my_homekit_report() {
	//float temperature_value = random_value(10, 30); // FIXME, read your real sensor here.
	float temperature_value = 0;
	float humidity_value = 0;
	byte data[40] = {0};
	int err = SimpleDHTErrSuccess;
	if ((err = dht22.read2(&temperature_value, &humidity_value, data)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT22 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(2000);
    return;
  	}
	cha_temperature.value.float_value = temperature_value;
	cha_humidity.value.float_value = humidity_value;
	LOG_D("Current temperature: %.1f", temperature_value);
	LOG_D("Current humidity: %.1f", humidity_value);
	homekit_characteristic_notify(&cha_temperature, cha_temperature.value);
	homekit_characteristic_notify(&cha_humidity, cha_humidity.value);
}

int random_value(int min, int max) {
	return min + random(max - min);
}
