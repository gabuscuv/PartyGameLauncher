/**********************************************************************************************
*
*   Copyright (c) 2024 Gabriel Bustillo del Cuvillo (@gabuscuv)
*
*   raylib - Advance Game template
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"
#include <stdlib.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    
    // xdotoolweb is a highly security risk as it doesn't have auth and 
     // allows control Xorg environment and 
     // It doesn't have a appropriate security audition and the code has 4/5 year old
     // But It's useful in this context as a multimedia remote control due 
     // lack of native CEC support (https://wiki.archlinux.org/title/HDMI-CEC#Native_CEC)
     // This should be deprecated when CEC is enabled by Tunneling over DisplayPort 
     // (https://wiki.archlinux.org/title/HDMI-CEC#Tunneling_over_DisplayPort)

    // As a security measure, This should only run when It's necessary (on-demand)
    // rather being 24/7 active. (using systemctl enable --user xdotoolweb)
    // Also because there are some conditions when Xorg in not running in the machine.
    // Like When Video Display is not connected (This is a script behavior not a Xorg behaviour)

    // #1 Low effort implementation.
    // TODO: I should change this with dbus, libsystemd implementation
    // look about https://stackoverflow.com/a/14828105  
        // https://github.com/makercrew/dbus-sample
        // https://stackoverflow.com/questions/50780221/simple-c-or-c-api-for-controlling-systemd-services
    
    system("systemctl start --user xdotoolweb");
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        
        PlaySound(fxCoin);
        MinimizeWindow();
        system("ultrastar-worldparty");
        RestoreWindow();
        SetWindowFocused();
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "Waiting for Input", pos, font.baseSize*3.0f, 4, MAROON);
    DrawText("Connect a Mobile Device to the Input Web or connect a Keyboard a Press Enter", 130, 220, 20, MAROON);
    // TODO: Show a connected IP Address for access to the Web Interface
    DrawText("IP Address: ...", 120, GetScreenHeight()/1.1, 20, MAROON);

}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: See #1 (aprox line 48)
    system("systemctl stop --user xdotoolweb");

    // TODO: Unload GAMEPLAY screen variables here!
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}