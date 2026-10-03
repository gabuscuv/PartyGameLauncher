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
#include "pthread.h"                        // POSIX style threads management
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
static pthread_t threadId;
static libusb_context* libUSBContext = NULL;
static libusb_hotplug_callback_handle* callback_handle = NULL;
static void *USBPluginThread(void *arg);     // Loading data thread function declaration
#endif
static char* messageScreen = "Introduce un SingStar Dongle o un GamePad";


//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------/*
#if libUSB
void ExitLibUSB()
{
    if(callback_handle)
    {
        libusb_hotplug_deregister_callback(libUSBContext, *callback_handle);       
        TraceLog(LOG_INFO, "libUSB: Freeing Handle");
        free(callback_handle);
        callback_handle = NULL;
        TraceLog(LOG_INFO, "libUSB: deregistered libUSB events");
    }

    
    if(libUSBContext)
    {
        // It's seems it uses their own free
        libusb_exit(libUSBContext);
        libUSBContext=NULL;
        TraceLog(LOG_INFO, "libUSB: Freed libUSB Resources");
    }  
}
static void *USBPluginThread(void *arg)
{
    while ((finishScreen == 0 && !WindowShouldClose()))
    {
        TraceLog(LOG_INFO, "USBPluginThread: libusb_handle_events_completed Executed");
        libusb_handle_events_completed(libUSBContext, NULL);
    }

    ExitLibUSB();

    pthread_join(threadId, NULL);
    threadId = -1;
    return NULL;
}

int SingstarHotplugCallback(struct libusb_context *ctx, struct libusb_device *dev,
                     libusb_hotplug_event event, void *user_data) 
{
    struct libusb_device_descriptor desc; 
    (void)libusb_get_device_descriptor(dev, &desc);

    if (LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED == event) 
    {
        finishScreen = 2;
        TraceLog(LOG_INFO, "SingstarHotplugCallback: SingStar Dongle Connected");
    } 
    else if (LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT == event) 
    {
        TraceLog(LOG_INFO, "SingstarHotplugCallback: SingStar Dongle Disconnected");
        finishScreen = 0;
    }
    else 
    {
        TraceLog(LOG_INFO, "SingstarHotplugCallback: HandleEvent Not Detected");
    }

    return finishScreen;
}

#endif

// Title Screen Initialization logic
void InitTitleScreen(void)
{

    framesCounter = 0;
    finishScreen = 0;

#if libUSB
    libUSBContext = (libusb_context*)malloc(sizeof(libUSBContext));

#if LIBUSB_API_VERSION >= 0x0100010A
   libusb_init_context(&libUSBContext, NULL, 0);
#else
    libusb_init(&libUSBContext);
#endif

    if(callback_handle)
    {
            TraceLog(LOG_ERROR, "LibUSB: Houston, We have a Memory Leak");
    }

    callback_handle = (libusb_hotplug_callback_handle*)malloc(sizeof(libusb_hotplug_callback_handle));
    int rc = libusb_hotplug_register_callback(libUSBContext, LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED |
                                    LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT, 0, 0x1415, 0x0000,
                                    LIBUSB_HOTPLUG_MATCH_ANY, SingstarHotplugCallback, NULL,
                                    callback_handle);

    if (LIBUSB_SUCCESS != rc) 
    {
        TraceLog(LOG_ERROR, "LibUSB: Failed To Register SingstarHotplug Event");
        ExitLibUSB();
    }

    int threadResult = pthread_create(&threadId, NULL, &USBPluginThread, NULL);
    
  if (threadResult != 0) {
       TraceLog(LOG_INFO, "LibUSB: Error making thread for Checks");
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

    framesCounter++;
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
    TraceLog(LOG_INFO, "TitleScreen: called Unload");  
}

// Title Screen should finish?
int FinishTitleScreen(void)
{
    return finishScreen;
}