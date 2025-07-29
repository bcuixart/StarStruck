#ifndef GAMEMANAGER_HH
#define GAMEMANAGER_HH

#include <iostream>
#include <random>

#include <raymob.h>
#include <raymath.h>

#include "Player.hh"
#include "Camera.hh"
#include "World.hh"

using namespace std;

class GameManager {
public:
	GameManager();

	enum GameState { MainMenu, Playing, PlayerDead };
	GameState GetGameState() const;

	void PrepareGame();

	void Update(const int width, const int height);
	void Render(const int width, const int height);

	bool GetIsKeyDown() const;
	bool GetIsKeyPressed() const;

	void CollectCoin();
	void KillPlayer();

	static GameManager* instance;

protected:

private:

	void Update_MainMenu(const float deltaTime);
	void Update_Playing(const float deltaTime);
	void Update_PlayerDead(const float deltaTime);

	Player* player;
	CameraManager* camera;
	World* world;

	GameState currentState = MainMenu;

	int coinsTotal = 0;
	int coinsCurrent = 0;
	int coinsHighscore = 0;

	float playerRadius;

	const float PLAYER_DEAD_RETRY_TIME = 1;
	float playerDeadTimeElapsed;

	const bool DEBUG_PRINT_SEED = false;
};

#endif