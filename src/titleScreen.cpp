#include "titleScreen.h"
#include "assetManager.h"
#include "screen.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

// Declare constants for the dimentions of assets
// Titlescreen:
const int highlightedPipeWidth = 228;
const int highlightedPipeHeight = 35;
const int unhighlightedPipeWidth = 228;
const int unhighlightedPipeHeight = 35;
const int backgroundWidth = 256;
const int backgroundHeight = 160;

// Declare bools to keep track of what game state we are in
bool titleScreen = true;
bool inGame = false;
bool inMinigame = false;

// Declare some bools for determining if the mouse is hovering over a button
bool mvslHover = false;
bool minigameHover = false;
bool optionsHover = false;

// Define the rectangles for the bounding boxes of the buttons. (Also used for cropping)
// Y pos of first buttton in the .png is 68
// BG Coords (270, 195)
Rectangle mvslHighlightedBox = {0, 68, highlightedPipeWidth, highlightedPipeHeight};
Rectangle mvslUnhighlightedBox = {0, 68 + highlightedPipeHeight, unhighlightedPipeWidth, unhighlightedPipeHeight};
Rectangle minigameHighlightedBox = {0, 68 + (highlightedPipeHeight * 2), highlightedPipeWidth, highlightedPipeHeight};
Rectangle minigameUnhighlightedBox = {0, 68 + (highlightedPipeHeight * 3), unhighlightedPipeWidth, unhighlightedPipeHeight};
Rectangle optionsHighlightedBox = {0, 68 + (highlightedPipeHeight * 4), highlightedPipeWidth, highlightedPipeHeight};
Rectangle optionsUnhighlightedBox = {0, 68 + (highlightedPipeHeight * 5), unhighlightedPipeWidth, unhighlightedPipeHeight};
Rectangle backgroundBox = {270, 195, backgroundWidth, backgroundHeight};

// Declare some bounding boxes for the title screen buttons
Rectangle mvslButton = {SCREEN_WIDTH / 4 + 20, backgroundHeight, highlightedPipeWidth * 3, highlightedPipeHeight * 3};
Rectangle minigameButton = {mvslButton.x, mvslButton.y + highlightedPipeHeight * 3, highlightedPipeWidth * 3, highlightedPipeHeight * 3};
Rectangle optionsButton = {mvslButton.x, minigameButton.y + highlightedPipeHeight * 3, highlightedPipeWidth * 3, highlightedPipeHeight * 3};

Rectangle mvslButtonCoords = {mvslButton.x, mvslButton.y, highlightedPipeWidth * 3, highlightedPipeHeight * 3};
Rectangle minigameButtonCoords = {minigameButton.x, minigameButton.y, highlightedPipeWidth * 3, highlightedPipeHeight * 3};
Rectangle optionsButtonCoords = {optionsButton.x, optionsButton.y, highlightedPipeWidth * 3, highlightedPipeHeight * 3};

// Make a position vector for the background
Rectangle backgroundCoords = {SCREEN_WIDTH / 4, backgroundHeight, backgroundWidth * 3, backgroundHeight * 3};

// Declare and Initalized the status of the buttons
bool mvslButtonPressed = false;
bool miniGameButtonPressed = false;
bool optionsButtonPressed = false;

// Misc. assets.
Texture2D titleAsset;
Sound buttonSound;

void TitleScreen::Initialize()
{
	AssetManager::LoadTextureAsset("title/title_screen_assets.png", "TitleAsset");
	titleAsset = AssetManager::GetTexture("TitleAsset");
	AssetManager::LoadSoundAsset("sounds/Mario/whoohoo.wav", "TitleButtonSound");
	buttonSound = AssetManager::GetSound("TitleButtonSound");
}

void TitleScreen::DrawBackground2D()
{
}

void TitleScreen::DrawForeground2D()
{

	if (!optionsButtonPressed)
	{
		DrawTexturePro(titleAsset, backgroundBox, Screen::ScaleRectangle(&backgroundCoords), {0, 0}, 0, WHITE);
		DrawTexturePro(titleAsset, mvslHover ? mvslHighlightedBox : mvslUnhighlightedBox, Screen::ScaleRectangle(&mvslButtonCoords), {0, 0}, 0, WHITE);
		DrawTexturePro(titleAsset, minigameHover ? minigameHighlightedBox : minigameUnhighlightedBox, Screen::ScaleRectangle(&minigameButtonCoords), {0, 0}, 0, WHITE);
		DrawTexturePro(titleAsset, optionsHover ? optionsHighlightedBox : optionsUnhighlightedBox, Screen::ScaleRectangle(&optionsButtonCoords), {0, 0}, 0, WHITE);
	}

	if (optionsButtonPressed)
	{
		DrawRectangle(10, 10, 10, 10, RED);
	}
}

void TitleScreen::Draw3D()
{
}

void TitleScreen::Update()
{

	// Swap the Texture for if the buttons are highlightted are not
	mvslHover = CheckCollisionPointRec(GetMousePosition(), Screen::ScaleRectangle(&mvslButton));
	minigameHover = CheckCollisionPointRec(GetMousePosition(), Screen::ScaleRectangle(&minigameButton));
	optionsHover = CheckCollisionPointRec(GetMousePosition(), Screen::ScaleRectangle(&optionsButton));

	// Check to see if the mouse is being clicked inside of a button, and do something based
	// on what button is pressed

	if (IsMouseButtonPressed(0))
	{
		if (mvslHover)
		{
			// If the mouse clicks on the MvsL Button
			//PlaySound(buttonSound);
			mvslButtonPressed = true;
		}
		else if (minigameHover)
		{
			// If the mouse clicks on the Minigame Button
			//PlaySound(buttonSound);
			miniGameButtonPressed = true;
		}
		else if (optionsHover)
		{
			// If the mouse clicks on the Options Button
			//PlaySound(buttonSound);
			optionsButtonPressed = true;
		}
	}

	if (mvslButtonPressed || miniGameButtonPressed)
	{
		// Transition to the other scene
		titleScreen = false;

		if (mvslButtonPressed)
		{
			// Load the MvsL game scene
			Scene::ChangeScene("Gameplay");
		}

		if (miniGameButtonPressed)
		{
			// Load the minigame game scene
			// [TODO]
		}
	}
}

void TitleScreen::Cleanup()
{

	AssetManager::UnloadTextureAsset("TitleAsset");
	//AssetManager::UnloadSoundAsset("TitleButtonSound");
}