/*
Main contributors to this file: Nolan Y.

Bug fixers: Gota7, bbomb64, SkilLP
*/

#include <raylib.h>
#include "scene.h"
#include "titleScreen.h"
#include "gameplay.h"
#include "screen.h"
#include "input.h"

// Main method.
int main(void) {

    // Initalize the game window
    InitWindow(Screen::GAME_WIDTH, Screen::GAME_HEIGHT, "Mario vs Luigi - Title Screen");
    Screen::Init();
    SetTargetFPS(60);
    InitAudioDevice();
    SetMasterVolume(100);

    // Some input.
    Input::AddControl("Left", KEY_LEFT, GAMEPAD_BUTTON_LEFT_FACE_LEFT, GAMEPAD_AXIS_LEFT_X, false, 0);
    Input::AddControl("Right", KEY_RIGHT, GAMEPAD_BUTTON_LEFT_FACE_RIGHT, GAMEPAD_AXIS_LEFT_X, true, 0);
    Input::gamePadIDs[0] = 0;

    // Scenes that exist.
    TitleScreen titleScreen;
    Gameplay gameplay;

    // Set the initial scene.
    Scene::LoadScene("TitleScreen", &titleScreen);
    Scene::LoadScene("Gameplay", &gameplay);
    Scene::ChangeScene("TitleScreen");

    // Main game loop
    while (!WindowShouldClose())
    {
        
        // Do update.
        UpdateCamera(&Scene::GetCamera());
        Scene::DoUpdate();

        // Fullscreen check.
        if (IsKeyPressed(KEY_F4))
        {
            Screen::DoToggleFullscreen();
        }

        // Draw everything.
        BeginDrawing();
            ClearBackground(BLACK);
            Scene::DoDrawBackground2D();
            BeginMode3D(Scene::GetCamera());
                Scene::DoDraw3D();
            EndMode3D();
            Scene::DoDrawForeground2D();
        EndDrawing();

    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseAudioDevice();   // Close the Audio Device
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}