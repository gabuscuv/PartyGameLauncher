/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Options Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
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
        system("ES-DE");
        changeToMainMenu = true;
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