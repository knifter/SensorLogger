#include "globals.h"

#include "gui.h"
#include "settings.h"

#include <MAX31856.h>
#include <MPRLS.h>

GUI gui;
settings_t settings;
SettingsManager setman(settings);

MAX31856 temp1(SPI, PIN_MAX1_CS);
// MPRLS mp(Wire1);
