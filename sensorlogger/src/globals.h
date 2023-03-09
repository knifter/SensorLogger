#ifndef __GLOBALS_H
#define __GLOBALS_H

#include "gui.h"
#include "settings.h"

#include <MAX31856.h>
#include <MPRLS.h>

extern settings_t settings;
extern SettingsManager setman;
extern GUI gui;

extern MAX31856 temp1;
// extern MPRLS pres1;

#endif //__GLOBALS_H
