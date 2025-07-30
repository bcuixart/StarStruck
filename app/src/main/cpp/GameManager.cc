#include "GameManager.hh"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager() 
{
	GameManager::instance = this;

	player = new Player();
	camera = new CameraManager();
	world = new World();
    uiManager = new UIManager();
    colorManager = new ColorManager();

	playerRadius = player->getPlayerRadius();

	currentState = MainMenu;
	PrepareGame();
}

int GameManager::GetRandomNumber(int max) const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, max);

    return dis(gen);
}

int GameManager::GetRandomInRange(int min, int max) const
{
    return min + GetRandomNumber(max - min);
}

int GameManager::GetCoinsCurrent() const
{
    return coinsCurrent;
}

int GameManager::GetCoinsHighscore() const
{
    return coinsHighscore;
}

int GameManager::GetCoinsTotal() const
{
    return coinsTotal;
}

GameManager::GameState GameManager::GetGameState() const 
{
	return currentState;
}

bool GameManager::GetIsKeyDown() const
{
	return IsMouseButtonDown(0) or IsKeyDown(KEY_SPACE);
}

bool GameManager::GetIsKeyPressed() const
{
	return IsMouseButtonPressed(0) or IsKeyPressed(KEY_SPACE);
}

void GameManager::PrepareGame() 
{
	world->ClearWorld();

	int randomSeed = GetRandomNumber(1000000);
	if (DEBUG_PRINT_SEED) std::cout << "Seed:" << randomSeed << std::endl;

	world->Prepare(randomSeed);
	player->Prepare();
	camera->Prepare();

	coinsCurrent = 0;
}

void GameManager::CollectCoin() 
{
    SetSoundPitch(coinSounds[coinSoundIndex], (float) GetRandomInRange(13, 18) / 10.f);
    PlaySound(coinSounds[coinSoundIndex]);
    coinSoundIndex = (coinSoundIndex + 1) % COIN_SOUNDS;

	++coinsCurrent;
}

void GameManager::KillPlayer() 
{
	if (currentState == Playing) 
	{
		player->KillPlayer();

        StopMusicStream(music001);

        playerDeadTimeElapsed = 0;
		currentState = PlayerDead;

		coinsTotal += coinsCurrent;
		if (coinsCurrent > coinsHighscore) coinsHighscore = coinsCurrent;
	}
}

void GameManager::Update_MainMenu(const float deltaTime)
{
	if (GetIsKeyPressed())
    {
        PlayMusicStream(music001);
        currentState = Playing;
    }
}

void GameManager::Update_Playing(const float deltaTime)
{

}

void GameManager::Update_PlayerDead(const float deltaTime)
{
	playerDeadTimeElapsed += deltaTime;
	if (playerDeadTimeElapsed >= PLAYER_DEAD_RETRY_TIME && GetIsKeyPressed())
	{
		PrepareGame();
        colorManager->NextPalette();
		currentState = MainMenu;
	}
}

void GameManager::Update(const int width, const int height) 
{
	float deltaTime = GetFrameTime();

    UpdateMusicStream(music001);

	switch (currentState) 
	{
		case MainMenu: {
			Update_MainMenu(deltaTime);
			break;
		}
		case Playing: {
			Update_Playing(deltaTime);
			break;
		}
		case PlayerDead: {
			Update_PlayerDead(deltaTime);
			break;
		}
	}

	player->Update(deltaTime);
	world->Update(player->getPlayerPosition(), playerRadius, deltaTime);
	camera->Update(player->getPlayerPosition(), width, height, deltaTime);
}

void GameManager::Render(const int width, const int height) 
{
    float deltaTime = GetFrameTime();

    ClearBackground(colorManager->GetBackgroundColor());
	BeginDrawing();

	camera->MBeginMode2D();

	world->Render();
	player->Render();

	EndMode2D();

    uiManager->Render(GetScreenWidth(), GetScreenHeight(), deltaTime);

	EndDrawing();
}