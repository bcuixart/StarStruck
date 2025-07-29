#include "GameManager.hh"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager() 
{
	GameManager::instance = this;

	player = new Player();
	camera = new CameraManager();
	world = new World();

	playerRadius = player->getPlayerRadius();

	currentState = MainMenu;
	PrepareGame();
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

	std::random_device rd;
	std::mt19937 gen(rd());

	unsigned int randomSeed = static_cast<unsigned int>(gen());
	if (DEBUG_PRINT_SEED) std::cout << "Seed:" << randomSeed << std::endl;

	world->Prepare(randomSeed);
	player->Prepare();
	camera->Prepare();

	coinsCurrent = 0;
}

void GameManager::CollectCoin() 
{
	++coinsCurrent;
}

void GameManager::KillPlayer() 
{
	if (currentState == Playing) 
	{
		player->KillPlayer();

		playerDeadTimeElapsed = 0;
		currentState = PlayerDead;

		coinsTotal += coinsCurrent;
		if (coinsCurrent > coinsHighscore) coinsHighscore = coinsCurrent;
	}
}

void GameManager::Update_MainMenu(const float deltaTime)
{
	if (GetIsKeyPressed()) currentState = Playing;
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
		currentState = MainMenu;
	}
}

void GameManager::Update(const int width, const int height) 
{
	float deltaTime = GetFrameTime();

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
	ClearBackground({ 133, 60, 217, 255 });
	BeginDrawing();

	camera->MBeginMode2D();

	world->Render();
	player->Render();

	EndMode2D();

	char buff[100];
	sprintf(buff, "Coins: %d", coinsCurrent);
	DrawText(buff, width / 2, 0, 25, WHITE);

	DrawFPS(0, 0);

	EndDrawing();
}