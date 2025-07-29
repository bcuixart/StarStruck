#include <iostream>
#include <cmath>
#include <vector>

#include <raymob.h>
#include <raymath.h>

#include "GameManager.hh"

#define SCREEN_WIDTH 0
#define SCREEN_HEIGHT 0

int main() 
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dorga");
    InitAudioDevice();

	SetTargetFPS(60);

    GameManager* gameManager = new GameManager();

	while (!WindowShouldClose()) 
	{
		int width = GetScreenWidth();
		int height = GetScreenHeight();

		gameManager->Update(width, height);
		gameManager->Render(width, height);
	}

    CloseAudioDevice();
	CloseWindow();
}