#ifndef __CONFIG_H
#define __CONFIG_H

#include <Arduino.h>

#define _STRINGIFY(x)      #x
#define STRINGIFY(x)      _STRINGIFY(x)

#define VERSION                BUILD_DATETIME
#define VERSIONSTR_LONG        STRINGIFY(GIT_BRANCH-VERSION)
#define VERSIONSTR_SHORT       STRINGIFY(VERSION)

#define LOOP_INTERVAL_MS       500

#ifdef DEBUG
	// Enable DBG(...) globally:
	// #define TOOLS_LOG_DEBUG

	// Or per file:
	#define DEBUG_MAIN_CPP

	// Specific parts:
#endif

#define BOOTSCREEN_TIMEOUT_MS   2000

#define PIN_SDA0                GPIO_NUM_21 // default
#define PIN_SCL0                GPIO_NUM_22 // default

#define PIN_SCL1                GPIO_NUM_13
#define PIN_SDA1                GPIO_NUM_15
// Wire0 = Wire, SDA = 21, SCL = 22


#define PIN_BTN_A				GPIO_NUM_39
#define PIN_BTN_B 				GPIO_NUM_38
#define PIN_BTN_C 				GPIO_NUM_37

#define PIN_SPEAKER             GPIO_NUM_25

#define PIN_MAX1_CS			    GPIO_NUM_16
#define PIN_MAX2_CS			    GPIO_NUM_17

#endif // __CONFIG_H

