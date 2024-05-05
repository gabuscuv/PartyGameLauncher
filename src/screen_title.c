/**********************************************************************************************
*
*   Copyright (c) 2024 Gabriel Bustillo del Cuvillo (@gabuscuv)
*
*   raylib - Advance Game template
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
**********************************************************************************************/
#define libUSB 1

#include "raylib.h"
#include "screens.h"
#if libUSB
#include <libusb-1.0/libusb.h>
#endif


//----------------------

// ------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
static int textStartX = 0;
static int textStartY = 0;
static int fontSize = 24;
#if libUSB
static libusb_hotplug_callback_handle callback_handle;
#endif
static char* messageScreen = "Introduce un SingStar Dongle o un GamePad";

//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------/*
#if libUSB
int SingstarHotplugCallback(struct libusb_context *ctx, struct libusb_device *dev,
                     libusb_hotplug_event event, void *user_data) 
{
  struct libusb_device_descriptor desc; 
  (void)libusb_get_device_descriptor(dev, &desc);
 
  if (LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED == event) {
    finishScreen = 2;
        TraceLog(LOG_INFO, "LibUSB: SingStar Dongle Connected");
        return 1;

  } else if (LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT == event) {
            TraceLog(LOG_INFO, "LibUSB: SingStar Dongle Disconnected");

    finishScreen = 0;
    }else {
            TraceLog(LOG_INFO, "LibUSB: HandleEvent Not Detected");
    }
  //count++;
 
  return 0;
}
#endif

// Title Screen Initialization logic
void InitTitleScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;

#if libUSB
    libusb_init(NULL);

        int rc = libusb_hotplug_register_callback(NULL, LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED |
                                        LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT, 0, 0x1415, 0x0000,
                                        LIBUSB_HOTPLUG_MATCH_ANY, SingstarHotplugCallback, NULL,
                                        &callback_handle);
  if (LIBUSB_SUCCESS != rc) {
    TraceLog(LOG_ERROR, "LibUSB: Failed To Register SingstarHotplug Event");
    libusb_exit(NULL);
  }
    TraceLog(LOG_INFO, "LibUSB: SingstarHotplug Event Registered Sucessfully");
#endif
  

    int textWidth = MeasureText(messageScreen, fontSize);
    textStartX = (GetScreenWidth() / 2) - (textWidth / 2);
    textStartY = (GetScreenHeight() / 2) - (fontSize / 2);

}



// Title Screen Update logic
void UpdateTitleScreen(void)
{
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        //finishScreen = 1;   // OPTIONS
        finishScreen = 2;   // GAMEPLAY
        PlaySound(fxCoin);
    }

    if (IsGamepadAvailable(0))
    {
        TraceLog(LOG_INFO, "Gamepad: GamePad Connected");
        finishScreen = 1;   // OPTIONS
        
        //finishScreen = 2;   // GAMEPLAY
        PlaySound(fxCoin);
    }

#if libUSB
    framesCounter++;

    if(callback_handle && framesCounter > 300)
    {
        TraceLog(LOG_INFO, "LibUSB: libusb_handle_events_completed Executed");
        libusb_handle_events_completed(NULL, NULL);
        framesCounter = 0;
    }

#endif
    // TODO: Update TITLE screen variables here!
    // Press enter or tap to change to GAMEPLAY screen

}

// Title Screen Draw logic
void DrawTitleScreen(void)
{
    // TODO: Draw TITLE screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), GREEN);
    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "PartyGameLaucher", pos, font.baseSize*3.0f, 4, DARKGREEN);
    DrawText(messageScreen, textStartX, textStartY, 20, DARKGREEN);
    DrawText("Desarrollado por: Gabriel Bustillo del Cuvillo (gabuscuv)", 120, GetScreenHeight()/1.1, 20, DARKGREEN);

}

// Title Screen Unload logic
void UnloadTitleScreen(void)
{
    framesCounter = 0;

    #if libUSB
    TraceLog(LOG_INFO, "libUSB: Freeing libUSB Resources");
    if (callback_handle)
    {
        libusb_hotplug_deregister_callback(NULL, callback_handle);
    }
    
    libusb_exit(NULL);
    #endif
    // TODO: Unload TITLE screen variables here!
}

// Title Screen should finish?
int FinishTitleScreen(void)
{
    return finishScreen;
}