#ifndef GAMEMANAGER_HH
#define GAMEMANAGER_HH

#include <iostream>
#include <random>

#include <raymob.h>
#include <raymath.h>

#include "Player.hh"
#include "Camera.hh"
#include "World.hh"
#include "UIManager.hh"

using namespace std;

class GameManager {
public:
	GameManager();

	enum GameState { MainMenu, Playing, PlayerDead };
	GameState GetGameState() const;

	void PrepareGame();

	void Update(const int width, const int height);
	void Render(const int width, const int height);

    int GetRandomNumber(int max) const;
    int GetRandomInRange(int min, int max) const;

    int GetCoinsCurrent() const;
    int GetCoinsHighscore() const;
    int GetCoinsTotal() const;

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
    UIManager* uiManager;

    const int COIN_SOUNDS = 3;
    int coinSoundIndex = 0;
    vector<Sound> coinSounds = {
        LoadSound("Sounds/Coin_000.mp3"),
        LoadSound("Sounds/Coin_001.mp3"),
        LoadSound("Sounds/Coin_002.mp3"),
    };

    Music music001 = LoadMusicStream("Sounds/Music_001.mp3");

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