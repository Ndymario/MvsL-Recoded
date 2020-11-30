/*
Contributors to this file: Nolan Y.
*/
#include <stdio.h>
#include <raylib.h>

// Some constants.
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;
const Vector2 ZERO = { 0, 0 };

int main(void) {

    // Initialization
    //--------------------------------------------------------------------------------------

    // Declare constants for the dimentions of assets
        // Titlescreen:
    const int highlightedPipeWidth = 228;
    const int highlightedPipeHeight = 35;
    const int unhighlightedPipeWidth = 217;
    const int unhighlightedPipeHeight = 35;

    // Initalize the game window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mario vs Luigi - Title Screen");

    // Load the Title Screen assets (NOTE: This path needs to be hard coded for macOS, will find a fix later)
    Image asset = LoadImage("/Users/ndymario/Desktop/Programming/C/MvsL-Recoded/assets/title/title_screen_assets.png");

    // Define the rectangles for the bounding boxes of the buttons. (Also used for cropping)
    // Y pos of first buttton in the .png is 68
    Rectangle mvslHighlightedBox = { 0, 68, highlightedPipeWidth, highlightedPipeHeight };
    Rectangle mvslUnhighlightedBox = { 0, 68 + highlightedPipeHeight, unhighlightedPipeWidth, unhighlightedPipeHeight };
    Rectangle minigameHighlightedBox = { 0, 68 + (highlightedPipeHeight * 2), highlightedPipeWidth, highlightedPipeHeight };
    Rectangle minigameUnhighlightedBox = { 0, 68 + (highlightedPipeHeight * 3), unhighlightedPipeWidth, unhighlightedPipeHeight };
    Rectangle optionsHighlightedBox = { 0, 68 + (highlightedPipeHeight * 4), highlightedPipeWidth, highlightedPipeHeight };
    Rectangle optionsUnhighlightedBox = { 0, 68 + (highlightedPipeHeight * 5), unhighlightedPipeWidth, unhighlightedPipeHeight };

    // Create Textures for drawing to the screen
    Texture2D titleAsset = LoadTextureFromImage(asset);

    // Declare bools to keep track of what game state we are in
    bool titleScreen = true;
    bool inGame = false;
    bool inMinigame = false;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Declare some ints for determining if the mouse is hovering over a button
        int mvslHover = 0;
        int minigameHover = 0;
        int optionsHover = 0;

        // Declare some bounding boxes for the title screen buttons
        Rectangle mvslButton = { SCREEN_WIDTH/4, 0, highlightedPipeWidth, highlightedPipeHeight };
        Rectangle minigameButton = { SCREEN_WIDTH/4, highlightedPipeHeight, highlightedPipeWidth, highlightedPipeHeight };
        Rectangle optionsButton = { SCREEN_WIDTH/4, highlightedPipeHeight * 2, highlightedPipeWidth, highlightedPipeHeight };

        Vector2 mvslButtonCoords = { mvslButton.x, mvslButton.y };
        Vector2 minigameButtonCoords = { minigameButton.x, minigameButton.y };
        Vector2 optionsButtonCoords = { optionsButton.x, optionsButton.y };

        while (titleScreen) {

            // Swap the Texture for if the buttons are highlightted are not

            if (GetMouseX() > mvslButton.x & GetMouseX() < (mvslButton.x + highlightedPipeWidth)){
                if (GetMouseY() > mvslButton.y & GetMouseY() < (mvslButton.y + highlightedPipeHeight)){
                    mvslHover = 1;
                } else {
                    mvslHover = 0;
                }
            } else {
                mvslHover = 0;
            }

            if (GetMouseX() > minigameButton.x & GetMouseX() < (minigameButton.x + highlightedPipeWidth)){
                if ((GetMouseY() > minigameButton.y) & (GetMouseY() < (minigameButton.y + highlightedPipeHeight))){
                    minigameHover = 1;
                } else {
                    minigameHover = 0;
                }
            } else {
                minigameHover = 0;
            }

            if (GetMouseX() > optionsButton.x & GetMouseX() < (optionsButton.x + highlightedPipeWidth)){
                if ((GetMouseY() > optionsButton.y) & (GetMouseY() < (optionsButton.y + highlightedPipeHeight))){
                    optionsHover = 1;
                } else {
                    optionsHover = 0;
                }
            } else {
                optionsHover = 0;
            }
            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();
            ClearBackground(BLACK);
            DrawTextureRec(titleAsset, mvslHover ? mvslHighlightedBox : mvslUnhighlightedBox, mvslButtonCoords, WHITE);
            DrawTextureRec(titleAsset, minigameHover ? minigameHighlightedBox : minigameUnhighlightedBox, minigameButtonCoords, WHITE);
            DrawTextureRec(titleAsset, optionsHover ? optionsHighlightedBox : optionsUnhighlightedBox, optionsButtonCoords, WHITE);

            EndDrawing();
            //----------------------------------------------------------------------------------
        }
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}