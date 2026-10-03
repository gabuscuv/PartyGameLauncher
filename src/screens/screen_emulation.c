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

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
static int textStartX = 0;
static int textStartY = 0;
static int fontSize = 24;
static bool changeToMainMenu = false;
static char * messageScreen = "Switch off all controls to return to the main menu.";
static Vector2 pos = { 20, 10 };

//----------------------------------------------------------------------------------
// Options Screen Functions Definition
//----------------------------------------------------------------------------------

// Options Screen Initialization logic
void InitOptionsScreen(void)
{
    // TODO: Initialize OPTIONS screen variables here!
    framesCounter = 0;
    finishScreen = 0;

    int textWidth = MeasureText(messageScreen, fontSize);
    textStartX = (GetScreenWidth() / 2) - (textWidth / 2);
    textStartY = (GetScreenHeight() / 2) - (fontSize / 2);
}

// Options Screen Update logic
void UpdateOptionsScreen(void)
{
    framesCounter++;
    if ( framesCounter > 10 && ! changeToMainMenu)
    {
        MinimizeWindow();
        system("ES-DE");
        RestoreWindow();
        SetWindowFocused();
        changeToMainMenu = true;
        // This is just a way of disconnect all devices connected
        // #2 Low effort implementation.
        system("bluetoothctl power off");
        system("bluetoothctl power on");
    }

    if (changeToMainMenu && ! IsGamepadAvailable(0))
    {
        finishScreen = 1;
    }
    // TODO: Update OPTIONS screen variables here!
}

// Options Screen Draw logic
void DrawOptionsScreen(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);
    DrawTextEx(font, "Playing", pos, font.baseSize*3.0f, 4, DARKBLUE);

    if (changeToMainMenu)
    {
        DrawText(messageScreen, textStartX, textStartY, fontSize, DARKBLUE);
    }
    // TODO: Draw OPTIONS screen here!
}

// Options Screen Unload logic
void UnloadOptionsScreen(void)
{
    framesCounter = 0;
    changeToMainMenu = false;
    // TODO: Unload OPTIONS screen variables here!
}

// Options Screen should finish?
int FinishOptionsScreen(void)
{
    return finishScreen;
}