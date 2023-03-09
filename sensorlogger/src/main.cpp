#include <Arduino.h>

#include "config.h"
#include "globals.h"
#include "settings.h"
#include "screens.h"

#include <MAX31856.h>
#include <MPRLS.h>

//#include "tools-log.h"

void halt(const char*);
uint32_t scan_keys();

void setup()
{
	Serial.begin(115200);

    // Init IO
	digitalWrite(PIN_SPEAKER, LOW);
	pinMode(PIN_SPEAKER, OUTPUT);
	pinMode(PIN_BTN_A, INPUT);
	pinMode(PIN_BTN_B, INPUT);
	pinMode(PIN_BTN_C, INPUT);

    // Start up GUI
	gui.begin();

    // Initialize sensors etc
    temp1.begin();

    // Bootstrap
    ScreenPtr scr = std::make_shared<BootScreen>(gui);
    gui.pushScreen(scr);
    DBG("setup() done.");
};

void loop()
{
    soogh_event_t e = static_cast<soogh_event_t>(key2event(scan_keys()));

    time_t now = millis();
    static time_t last = now;
    if((now - last) > 500)
    {
        float T = temp1.readThermocoupleTemperature();
        float C = temp1.readCJTemperature();
        uint8_t f = temp1.getFault();

        INFO("status = %d, JC = %f, Temp = %f", f, C, T);
        last = now;
    };
	gui.handle(e);

	setman.loop();
};

void halt(const char* error)
{
	gui.showMessage("HALT:", error);
	// DBG("HALT: %s", error);
	while(true)
	{
		// gui.loop();
	};
};

uint32_t scan_keys()
{
	// Read current states
	uint32_t pressed = KEY_NONE;
	if(digitalRead(PIN_BTN_A) == LOW)
		pressed |= KEY_A;
	if(digitalRead(PIN_BTN_B) == LOW)
		pressed |= KEY_B;
	if(digitalRead(PIN_BTN_C) == LOW)
		pressed |= KEY_C;
	// if(digitalRead(PIN_POWERINT) == LOW)
	// 	pressed |= KEY_P;
	return pressed;
};
