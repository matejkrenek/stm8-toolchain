#ifndef __UI_H
#define __UI_H

#include "LCD_I2C_UI.h"
#include "LCD_I2C.h"

LCD_I2C_UI_Page_Content LCD_UI_Page_Home[] = {
    {
        .text = "Time: ",
        .onRender = UI_HomePage,
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "menu",
    },
};

LCD_I2C_UI_Page_Content LCD_UI_Page_Menu[] = {
    {
        .text = "Periferals",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "periferals",
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
        .text = "Actions",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "actions",
    },
    {
        .text = "Back",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "home",
    },
};

LCD_I2C_UI_Page_Content LCD_UI_Page_Periferals[] = {
    {
        .text = "Real Time Clock",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "periferal_rtc",
    },
    {
        .text = "RGB LED",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "periferal_rgb",
    },
    {
        .text = "LEDs (8b)",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "periferal_leds",
    },
    {
        .text = "Back",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "menu",
    },
};

LCD_I2C_UI_Page_Content LCD_UI_Page_Periferal_Leds[] = {
    {
        .text = "Val.: ",
        .onRender = UI_Periferal_LEDs,
        .onClick = UI_Periferal_LEDs_Action,
        .onLeft = UI_Periferal_LEDs_ActionLeft,
        .onRight = UI_Periferal_LEDs_ActionRight,
    },
    {
        .text = "Time: ",
        .onRender = UI_Periferal_LEDs_Period,
        .onClick = UI_Periferal_LEDs_Period_Action,
        .onLeft = UI_Periferal_LEDs_Period_ActionLeft,
        .onRight = UI_Periferal_LEDs_Period_ActionRight,
    },
    {
        .text = "Mode: ",
        .onRender = UI_Periferal_LEDs_Mode,
        .onClick = UI_Periferal_LEDs_Mode_Action,
        .onLeft = UI_Periferal_LEDs_Mode_ActionLeft,
        .onRight = UI_Periferal_LEDs_Mode_ActionRight,
    },
    {
        .text = "Back",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "periferals",
    },
};

LCD_I2C_UI_Page_Content LCD_UI_Page_Periferal_RTC[] = {
    {
        .text = "Time: ",
        .onRender = UI_Periferal_RTC_Time,
        .onClick = UI_Periferal_RTC_Time_Action,
        .onLeft = UI_Periferal_RTC_Time_ActionLeft,
        .onRight = UI_Periferal_RTC_Time_ActionRight,
    },
    {
        .text = "Date: ",
        .onRender = UI_Periferal_RTC_Date,
        .onClick = UI_Periferal_RTC_Date_Action,
        .onLeft = UI_Periferal_RTC_Date_ActionLeft,
        .onRight = UI_Periferal_RTC_Date_ActionRight,
    },
    {
        .text = "Back",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "periferals",
    },
};

LCD_I2C_UI_Page_Content LCD_UI_Page_Periferal_RGB[] = {
    {
        .text = "R: 255",
    },
    {
        .text = "G: 55",
    },
    {
        .text = "B: 80",
    },
    {
        .text = "Back",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "periferals",
    },
};

LCD_I2C_UI_Page_Content LCD_UI_Page_Settings[] = {
    {
        .text = "Light off: ",
        .onRender = UI_Periferal_Settings_Light,
        .onClick = UI_Periferal_Settings_Light_Action,
        .onLeft = UI_Periferal_Settings_Light_ActionLeft,
        .onRight = UI_Periferal_Settings_Light_ActionRight,
    },
    {
        .text = "Cursor: ",
        .onRender = UI_SettingsCursor,
        .onClick = UI_Action_SettingsCursor,
    },
    {
        .text = "Back",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "menu",
    },
};

LCD_I2C_UI_Page_Content LCD_UI_Page_MainPage[] = {
    {
        .text = "Time",
    },
    {
        .text = "Back",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "menu",
    },
};

LCD_I2C_UI_Page_Content LCD_UI_Page_Actions[] = {
    {
        .text = "Send Temp Chart",
        .onClick = UI_Actions_TempChart,
    },
    {
        .text = "Send Temp Table",
        .onClick = UI_Actions_TempTable,

    },
    {
        .text = "Send Temp Classic",
        .onClick = UI_Actions_TempClassic,

    },
    {
        .text = "Back",
        .onClick = LCD_I2C_UI_RedirectDynamically,
        .redirectName = "menu",
    },
};

LCD_I2C_UI_Page LCD_UI_Pages[] = {
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
        .name = "periferals",
        .content_length = len(LCD_UI_Page_Periferals),
        .content = LCD_UI_Page_Periferals,
        .hasScrollbar = TRUE,
    },
    {
        .name = "periferal_leds",
        .content_length = len(LCD_UI_Page_Periferal_Leds),
        .content = LCD_UI_Page_Periferal_Leds,
        .hasScrollbar = TRUE,
    },
    {
        .name = "periferal_rgb",
        .content_length = len(LCD_UI_Page_Periferal_RGB),
        .content = LCD_UI_Page_Periferal_RGB,
        .hasScrollbar = TRUE,
    },
    {
        .name = "periferal_rtc",
        .content_length = len(LCD_UI_Page_Periferal_RTC),
        .content = LCD_UI_Page_Periferal_RTC,
        .hasScrollbar = TRUE,
    },
    {
        .name = "settings",
        .content_length = len(LCD_UI_Page_Settings),
        .content = LCD_UI_Page_Settings,
        .hasScrollbar = TRUE,
    },
    {
        .name = "actions",
        .content_length = len(LCD_UI_Page_Actions),
        .content = LCD_UI_Page_Actions,
        .hasScrollbar = TRUE,
    },
    {
        .name = "main_page",
        .content_length = len(LCD_UI_Page_MainPage),
        .content = LCD_UI_Page_MainPage,
        .hasScrollbar = TRUE,
    },
};

LCD_I2C_UI_Config LCD_UI_CONFIG = {
    .page_length = len(LCD_UI_Pages),
    .pages = LCD_UI_Pages,
};

#endif /* __UI_H */