#ifndef __UI_H
#define __UI_H

#include "stm8s.h"
#include "LCD_I2C_UI.h"
#include "LCD_I2C.h"
#include "peripherals.h"
#include "eeprom.h"
#include "rgb.h"
#include "tone.h"
#include "dsrtc.h"
#include "string.h"
#include "milis.h"
#include "delay.h"
#include "stdio.h"

static LCD_I2C_UI_Page_Content LCD_UI_Page_Home[] = {
    {
        .text = "",
        .onRender = UI_HomePage,
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "menu",
    },
};

static LCD_I2C_UI_Page_Content LCD_UI_Page_Menu[] = {
    {
        .text = "Peripherals",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "peripherals",
    },
    {
        .text = "Settings",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "settings",
    },
    {
        .text = "Main Page",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "main_page",
    },
    {
        .text = "Back",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "home",
    },
};

static LCD_I2C_UI_Page_Content LCD_UI_Page_Peripherals[] = {
    {
        .text = "Real Time Clock",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "peripheral_rtc",
    },
    {
        .text = "RGB LED",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "peripheral_rgb",
    },
    {
        .text = "LEDs (8b)",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "peripheral_leds",
    },
    {
        .text = "Back",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "menu",
    },
};

static LCD_I2C_UI_Page_Content LCD_UI_Page_Peripheral_Leds[] = {
    {
        .text = "Val.: ",
        .onRender = UI_Peripheral_LEDs,
        .onClick = UI_Peripheral_LEDs_Action,
        .onLeft = UI_Peripheral_LEDs_ActionLeft,
        .onRight = UI_Peripheral_LEDs_ActionRight,
    },
    {
        .text = "Time: ",
        .onRender = UI_Peripheral_LEDs_Period,
        .onClick = UI_Peripheral_LEDs_Period_Action,
        .onLeft = UI_Peripheral_LEDs_Period_ActionLeft,
        .onRight = UI_Peripheral_LEDs_Period_ActionRight,
    },
    {
        .text = "Mode: ",
        .onRender = UI_Peripheral_LEDs_Mode,
        .onClick = UI_Peripheral_LEDs_Mode_Action,
        .onLeft = UI_Peripheral_LEDs_Mode_ActionLeft,
        .onRight = UI_Peripheral_LEDs_Mode_ActionRight,
    },
    {
        .text = "Back",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "peripherals",
    },
};

static LCD_I2C_UI_Page_Content LCD_UI_Page_Peripheral_RTC[] = {
    {
        .text = "Time: ",
        .onRender = UI_Peripheral_RTC_Time,
        .onClick = UI_Peripheral_RTC_Time_Action,
        .onLeft = UI_Peripheral_RTC_Time_ActionLeft,
        .onRight = UI_Peripheral_RTC_Time_ActionRight,
    },
    {
        .text = "Date: ",
        .onRender = UI_Peripheral_RTC_Date,
        .onClick = UI_Peripheral_RTC_Date_Action,
        .onLeft = UI_Peripheral_RTC_Date_ActionLeft,
        .onRight = UI_Peripheral_RTC_Date_ActionRight,
    },
    {
        .text = "Back",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "peripherals",
    },
};

static LCD_I2C_UI_Page_Content LCD_UI_Page_Peripheral_RGB[] = {
    {
        .text = "R: ",
        .onRender = UI_Peripheral_RGB_Red,
        .onClick = UI_Peripheral_RGB_Red_Action,
        .onLeft = UI_Peripheral_RGB_Red_ActionLeft,
        .onRight = UI_Peripheral_RGB_Red_ActionRight,
    },
    {
        .text = "G: ",
        .onRender = UI_Peripheral_RGB_Green,
        .onClick = UI_Peripheral_RGB_Green_Action,
        .onLeft = UI_Peripheral_RGB_Green_ActionLeft,
        .onRight = UI_Peripheral_RGB_Green_ActionRight,
    },
    {
        .text = "B: ",
        .onRender = UI_Peripheral_RGB_Blue,
        .onClick = UI_Peripheral_RGB_Blue_Action,
        .onLeft = UI_Peripheral_RGB_Blue_ActionLeft,
        .onRight = UI_Peripheral_RGB_Blue_ActionRight,
    },
    {
        .text = "Alpha: ",
        .onRender = UI_Peripheral_RGB_Alpha,
        .onClick = UI_Peripheral_RGB_Alpha_Action,
        .onLeft = UI_Peripheral_RGB_Alpha_ActionLeft,
        .onRight = UI_Peripheral_RGB_Alpha_ActionRight,
    },
    {
        .text = "Back",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "peripherals",
    },
};

static LCD_I2C_UI_Page_Content LCD_UI_Page_Settings[] = {
    {
        .text = "Light off: ",
        .onRender = UI_Peripheral_Settings_Light,
        .onClick = UI_Peripheral_Settings_Light_Action,
        .onLeft = UI_Peripheral_Settings_Light_ActionLeft,
        .onRight = UI_Peripheral_Settings_Light_ActionRight,
    },
    {
        .text = "Cursor: ",
        .onRender = UI_SettingsCursor,
        .onClick = UI_Action_SettingsCursor,
    },
    {
        .text = "Volume: ",
        .onRender = UI_Settings_Sound_Volume,
        .onClick = UI_Settings_Sound_Volume_Action,
        .onLeft = UI_Settings_Sound_Volume_ActionLeft,
        .onRight = UI_Settings_Sound_Volume_ActionRight,
    },
    {
        .text = "Freq.: ",
        .onRender = UI_Settings_Sound_Freq,
        .onClick = UI_Settings_Sound_Freq_Action,
        .onLeft = UI_Settings_Sound_Freq_ActionLeft,
        .onRight = UI_Settings_Sound_Freq_ActionRight,
    },
    {
        .text = "Back",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "menu",
    },
};

static LCD_I2C_UI_Page_Content LCD_UI_Page_MainPage[] = {
    {
        .text = "Periph.: ",
        .onRender = UI_MainPage_Peripheral,
        .onClick = UI_MainPage_Peripheral_Action,
        .onLeft = UI_MainPage_Peripheral_ActionLeft,
        .onRight = UI_MainPage_Peripheral_ActionRight,
    },
    {
        .text = "Back",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "menu",
    },
};

static LCD_I2C_UI_Page LCD_UI_Pages[] = {
    {
        .name = "home",
        .content_length = len(LCD_UI_Page_Home),
        .content = LCD_UI_Page_Home,
        .hasScrollbar = FALSE,
    },
    {
        .name = "menu",
        .content_length = len(LCD_UI_Page_Menu),
        .content = LCD_UI_Page_Menu,
        .hasScrollbar = TRUE,
    },
    {
        .name = "peripherals",
        .content_length = len(LCD_UI_Page_Peripherals),
        .content = LCD_UI_Page_Peripherals,
        .hasScrollbar = TRUE,
    },
    {
        .name = "peripheral_leds",
        .content_length = len(LCD_UI_Page_Peripheral_Leds),
        .content = LCD_UI_Page_Peripheral_Leds,
        .hasScrollbar = TRUE,
    },
    {
        .name = "peripheral_rgb",
        .content_length = len(LCD_UI_Page_Peripheral_RGB),
        .content = LCD_UI_Page_Peripheral_RGB,
        .hasScrollbar = TRUE,
    },
    {
        .name = "peripheral_rtc",
        .content_length = len(LCD_UI_Page_Peripheral_RTC),
        .content = LCD_UI_Page_Peripheral_RTC,
        .hasScrollbar = TRUE,
    },
    {
        .name = "settings",
        .content_length = len(LCD_UI_Page_Settings),
        .content = LCD_UI_Page_Settings,
        .hasScrollbar = TRUE,
    },
    {
        .name = "main_page",
        .content_length = len(LCD_UI_Page_MainPage),
        .content = LCD_UI_Page_MainPage,
        .hasScrollbar = TRUE,
    },
};

static LCD_I2C_UI_Config LCD_UI_CONFIG = {
    .page_length = len(LCD_UI_Pages),
    .pages = LCD_UI_Pages,
};

void UI_HomePage();
void UI_Peripheral_LEDs();
void UI_Peripheral_LEDs_Mode();
void UI_Peripheral_LEDs_Mode_Action();
void UI_Peripheral_LEDs_Mode_ActionLeft();
void UI_Peripheral_LEDs_Mode_ActionRight();
void UI_Peripheral_LEDs_Period();
void UI_Peripheral_LEDs_Period_Action();
void UI_Peripheral_LEDs_Period_ActionLeft();
void UI_Peripheral_LEDs_Period_ActionRight();
void UI_Peripheral_LEDs_Action();
void UI_Peripheral_LEDs_ActionLeft();
void UI_Peripheral_LEDs_ActionRight();
void UI_SettingsCursor();
void UI_Action_SettingsCursor();
void UI_Peripheral_RTC_Time();
void UI_Peripheral_RTC_Time_Action();
void UI_Peripheral_RTC_Time_ActionLeft();
void UI_Peripheral_RTC_Time_ActionRight();
void UI_Peripheral_RTC_Date();
void UI_Peripheral_RTC_Date_Action();
void UI_Peripheral_RTC_Date_ActionLeft();
void UI_Peripheral_RTC_Date_ActionRight();
void UI_Peripheral_Settings_Light();
void UI_Peripheral_Settings_Light_Action();
void UI_Peripheral_Settings_Light_ActionLeft();
void UI_Peripheral_Settings_Light_ActionRight();
void UI_Settings_Sound_Volume();
void UI_Settings_Sound_Volume_Action();
void UI_Settings_Sound_Volume_ActionLeft();
void UI_Settings_Sound_Volume_ActionRight();
void UI_Settings_Sound_Freq();
void UI_Settings_Sound_Freq_Action();
void UI_Settings_Sound_Freq_ActionLeft();
void UI_Settings_Sound_Freq_ActionRight();
void UI_Peripheral_RGB_Red();
void UI_Peripheral_RGB_Red_Action();
void UI_Peripheral_RGB_Red_ActionLeft();
void UI_Peripheral_RGB_Red_ActionRight();
void UI_Peripheral_RGB_Green();
void UI_Peripheral_RGB_Green_Action();
void UI_Peripheral_RGB_Green_ActionLeft();
void UI_Peripheral_RGB_Green_ActionRight();
void UI_Peripheral_RGB_Blue();
void UI_Peripheral_RGB_Blue_Action();
void UI_Peripheral_RGB_Blue_ActionLeft();
void UI_Peripheral_RGB_Blue_ActionRight();
void UI_Peripheral_RGB_Alpha();
void UI_Peripheral_RGB_Alpha_Action();
void UI_Peripheral_RGB_Alpha_ActionLeft();
void UI_Peripheral_RGB_Alpha_ActionRight();
void UI_MainPage_Peripheral();
void UI_MainPage_Peripheral_Action();
void UI_MainPage_Peripheral_ActionLeft();
void UI_MainPage_Peripheral_ActionRight();

#endif /* __UI_H */