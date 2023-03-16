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
    if(!Wire.begin(PIN_SDA0, PIN_SCL0))
        ERROR("Wire.begin() Failed.");
    if(!Wire1.begin(PIN_SDA1, PIN_SCL1))
        ERROR("Wire1.begin() Failed with pins sda:%d scl:%d", PIN_SDA1, PIN_SCL1);
    
    // Init IO
	digitalWrite(PIN_SPEAKER, LOW);
	pinMode(PIN_SPEAKER, OUTPUT);
	pinMode(PIN_BTN_A, INPUT);
	pinMode(PIN_BTN_B, INPUT);
	pinMode(PIN_BTN_C, INPUT);

    // Initialize sensors etc
    if(!pres1.begin())
        ERROR("pres1.begin() Failed! Not present?");
    if(!pres2.begin())
        ERROR("pres2.begin() Failed! Not present?");
    if(!temp1.begin())
        ERROR("temp1.begin() Failed! Not present?");
    if(!temp2.begin())
        ERROR("temp2.begin() Failed! Not present?");

    // // Start up GUI
	// gui.begin();

    // // Bootstrap
    // ScreenPtr scr = std::make_shared<BootScreen>(gui);
    // gui.pushScreen(scr);

    DBG("setup() done.");

    return;
};

void loop()
{
    soogh_event_t e = static_cast<soogh_event_t>(key2event(scan_keys()));

    time_t now = millis();
    static time_t start = now;
    static time_t next = now;
    if(next < now)
    {
        float T1 = temp1.readThermocoupleTemperature();
        float C1 = temp1.readCJTemperature();
        uint8_t f1 = temp1.getFault();
        if(f1)
            T1 = NAN;
        // INFO("Temp1: status = %d, JC = %f, Temp = %f", f1, C1, T1);

        float T2 = temp2.readThermocoupleTemperature();
        float C2 = temp2.readCJTemperature();
        uint8_t f2 = temp2.getFault();
        // INFO("Temp2: status = %d, JC = %f, Temp = %f", f2, C2, T2);
        if(f2)
            T2 = NAN;

        float P1 = pres1.readPressureHPA();
        float P2 = pres2.readPressureHPA();
        // INFO("P1 = %f hPa", P1);
        // INFO("P2 = %f hPa delta: %f", P2, P2-P1);

        // Print CSV
        Serial.printf("%d, %0.3f, %0.3f, %0.3f, %0.3f\n", now - start, T1, T2, P1, P2-P1);

        next += LOOP_INTERVAL_MS;
    };
	// gui.handle(e);

	// setman.loop();
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
