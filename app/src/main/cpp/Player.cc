#include "Player.hh"
#include "GameManager.hh"

Player::Player() 
{
	Prepare();
}

Vector2 Player::getPlayerPosition() const {
	return playerPosition;
}

float Player::getPlayerRadius() const {
	return HITBOX_RADIUS;
}

void Player::Prepare() 
{
	playerVelocity.x = 0;
	playerVelocity.y = 0;

	playerPosition.x = 0;
	playerPosition.y = 0;
	playerRotation = 90;

	playerPositionMain = playerPositionWindow = playerPositionPropeller000 = playerPositionPropeller001 = playerPositionPropeller002 = playerPositionTop = playerPosition;

	playerDeadDebrisSpeedMultiplier = 1;
}

void Player::KillPlayer() 
{
	playerDeadPosition = playerPosition;
}

void Player::DeadMoveDebris(float deltaTime)
{
	float x = playerVelocity.x * deltaTime;
	float y = playerVelocity.y * deltaTime;

	playerPositionMain = Vector2Add(playerPositionMain, { x, -y } );
	playerPositionWindow = Vector2Add(playerPositionWindow, { x, -y } );
	playerPositionTop = Vector2Add(playerPositionTop, { x*1.25f, -y*1.25f } );
	playerPositionPropeller000 = Vector2Add(playerPositionPropeller000, { -y, -x } );
	playerPositionPropeller001 = Vector2Add(playerPositionPropeller001, { -x, y } );
	playerPositionPropeller002 = Vector2Add(playerPositionPropeller002, { y, x } );
}

void Player::Update_MainMenu(float deltaTime)
{
	currentFireTexture = -1;
}

void Player::Update_Playing(float deltaTime)
{
	float rotationSin = std::sin(playerRotation * DEG_TO_RAD);
	float rotationCos = std::cos(playerRotation * DEG_TO_RAD);

	if (GameManager::instance->GetIsKeyDown())
	{
		playerVelocity.x += ACCELERATION * rotationCos * deltaTime;
		playerVelocity.y += ACCELERATION * rotationSin * deltaTime;

		if (currentFireTexture == -1) currentFireTexture = 0;
		currentFireTexture = currentFireTexture + FIRE_TEXTURE_SPEED * deltaTime;
		if (currentFireTexture > (float)FIRE_TEXTURES) currentFireTexture = (float)FIRE_ACCELERATE_TEXTURES;
	}
	else
	{
		playerRotation = std::fmod(playerRotation + ROTATE_SPEED * deltaTime, 360.f);

		if (currentFireTexture > (float)FIRE_ACCELERATE_TEXTURES) currentFireTexture = FIRE_ACCELERATE_TEXTURES;
		currentFireTexture = currentFireTexture - FIRE_TEXTURE_SPEED * deltaTime;
		if (currentFireTexture <= 0) currentFireTexture = -1;
	}

	if (DEBUG_PRINT_FIRE_TEXTURE) std::cout << currentFireTexture << std::endl;

	float speed = std::sqrt(playerVelocity.x * playerVelocity.x + playerVelocity.y * playerVelocity.y);
	if (speed > 0)
	{
		playerVelocity.x += -playerVelocity.x / speed * DECELERATION * deltaTime;
		playerVelocity.y += -playerVelocity.y / speed * DECELERATION * deltaTime;

		float newSpeed = std::sqrt(playerVelocity.x * playerVelocity.x + playerVelocity.y * playerVelocity.y);
		speed = newSpeed;
		if (newSpeed < DECELERATION_STOP_TOLERANCE)
		{
			playerVelocity = { 0.0f, 0.0f };
		}
	}

	if (speed > MAX_PLAYER_SPEED)
	{
		playerVelocity.x = (playerVelocity.x / speed) * MAX_PLAYER_SPEED;
		playerVelocity.y = (playerVelocity.y / speed) * MAX_PLAYER_SPEED;
	}

	playerPosition.x += playerVelocity.x * deltaTime;
	playerPosition.y -= playerVelocity.y * deltaTime;

	playerPositionMain = playerPositionWindow = playerPositionPropeller000 = playerPositionPropeller001 = playerPositionPropeller002 = playerPositionTop = playerPosition;

	if (DEBUG_PRINT_ROT) std::cout << playerRotation << std::endl;
	if (DEBUG_PRINT_POS) std::cout << playerPosition.x << ' ' << playerPosition.y << std::endl;
	if (DEBUG_PRINT_VEL) std::cout << playerVelocity.x << ' ' << playerVelocity.y << std::endl;
}

void Player::Update_PlayerDead(float deltaTime)
{
	currentFireTexture = -1;

	DeadMoveDebris(deltaTime * playerDeadDebrisSpeedMultiplier);
	playerDeadDebrisSpeedMultiplier = max(playerDeadDebrisSpeedMultiplier - PLAYER_DEAD_DECELERATION * deltaTime, PLAYER_DEAD_MIN_SPEED);
}

void Player::Update(float deltaTime)
{
	switch (GameManager::instance->GetGameState()) 
	{
		case GameManager::GameState::MainMenu: {
			Update_MainMenu(deltaTime);
			break;
		}
		case GameManager::GameState::Playing: {
			Update_Playing(deltaTime);
			break;
		}
		case GameManager::GameState::PlayerDead: {
			Update_PlayerDead(deltaTime);
			break;
		}
	}
}

void Player::RenderBodyPart(const Texture& bodyPartTexture, const Vector2& bodyPartPosition, const Rectangle& source, const Vector2& origin, const Color& color)
{
	Rectangle dest = { bodyPartPosition.x, bodyPartPosition.y, (float)textureWidth / 8, (float)textureHeight / 8 };
	DrawTexturePro(bodyPartTexture, source, dest, origin, -playerRotation + 90, color);
}

void Player::Render() 
{
	Rectangle source = { 0.0f, 0.0f, (float)textureWidth, (float)textureHeight };
	Rectangle destFire = { playerPositionMain.x, playerPositionMain.y, (float)textureWidth / 8, (float)textureHeight / 8 };
	Vector2 origin = { (float)textureWidth * 1 / 16, (float)textureHeight * 1 / 16 };

	RenderBodyPart(playerBodyMainTexture, playerPositionMain, source, origin, GameManager::instance->colorManager->GetRocketBaseColor());
	RenderBodyPart(playerBodyWindowTexture, playerPositionMain, source, origin, GameManager::instance->colorManager->GetRocketWindowColor());
	RenderBodyPart(playerBodyPropeller000Texture, playerPositionPropeller000, source, origin, GameManager::instance->colorManager->GetRocketPropeller000Color());
	RenderBodyPart(playerBodyPropeller001Texture, playerPositionPropeller001, source, origin, GameManager::instance->colorManager->GetRocketPropeller001Color());
	RenderBodyPart(playerBodyPropeller002Texture, playerPositionPropeller002, source, origin, GameManager::instance->colorManager->GetRocketPropeller002Color());
	RenderBodyPart(playerBodyTopTexture, playerPositionTop, source, origin, GameManager::instance->colorManager->GetRocketTopColor());
	if (currentFireTexture != -1) DrawTexturePro(fireTextures[(int)currentFireTexture], source, destFire, origin, -playerRotation + 90, GameManager::instance->colorManager->GetRocketFireColor());

	if (drawDirectionPoints) 
	{
		float rotationSin = std::sin((-playerRotation) * DEG_TO_RAD);
		float rotationCos = std::cos((-playerRotation) * DEG_TO_RAD);

		Vector2 directionPoint1 = {
			playerPosition.x + 20 * rotationCos,
			playerPosition.y + 20 * rotationSin
		};

		Vector2 directionPoint2 = {
			playerPosition.x + 30 * rotationCos,
			playerPosition.y + 30 * rotationSin
		};

		Vector2 directionPoint3 = {
			playerPosition.x + 40 * rotationCos,
			playerPosition.y + 40 * rotationSin
		};

		DrawCircle(directionPoint1.x, directionPoint1.y, 1.5f, WHITE);
		DrawCircle(directionPoint2.x, directionPoint2.y, 1.5f, WHITE);
		DrawCircle(directionPoint3.x, directionPoint3.y, 1.25f, GRAY);
	}

	if (DEBUG_SHOW_HITBOX) DrawCircleLines(playerPosition.x, playerPosition.y, HITBOX_RADIUS, BLUE);
}