#ifndef PLAYER_HH
#define PLAYER_HH

#include <iostream>

#include <raymob.h>
#include <raymath.h>

#define DEG_TO_RAD  M_PI / 180

#define FIRE_TEXTURES 14
#define FIRE_ACCELERATE_TEXTURES 4
#define FIRE_MOVING_TEXTURES 10

using namespace std;

class Player {
public:
	Player();

	void Update(float deltaTime);
	void Render();

	void Prepare();

	void KillPlayer();

	Vector2 getPlayerPosition() const;
	float getPlayerRadius() const;

protected:

private:
	void DeadMoveDebris(float deltaTime);

	void Update_MainMenu(float deltaTime);
	void Update_Playing(float deltaTime);
	void Update_PlayerDead(float deltaTime);

	void RenderBodyPart(const Texture& bodyPartTexture, const Vector2& bodyPartPosition, const Rectangle& source, const Vector2& origin, const Color& color);

	Vector2 playerPosition = { 0, 0 };
	float playerRotation = 0;

	Vector2 playerVelocity = { 0, 0 };

	const float MAX_PLAYER_SPEED = 300.f;
	const float ACCELERATION = 350.f;
	const float DECELERATION = 100.f;
	const float DECELERATION_STOP_TOLERANCE = 0.01f;
	const float ROTATE_SPEED = -300;

	const float HITBOX_RADIUS = 12;

	Vector2 playerDeadPosition;
	const float PLAYER_DEAD_DECELERATION = 0.5f;
	const float PLAYER_DEAD_MIN_SPEED = 0.25f;
	float playerDeadDebrisSpeedMultiplier = 1.f;

	Vector2 playerPositionMain = { 0, 0 };
	Vector2 playerPositionWindow = { 0, 0 };
	Vector2 playerPositionPropeller000 = { 0, 0 };
	Vector2 playerPositionPropeller001 = { 0, 0 };
	Vector2 playerPositionPropeller002 = { 0, 0 };
	Vector2 playerPositionTop = { 0, 0 };

	const Texture playerBodyMainTexture = LoadTexture("Textures/Player_Body_Main.png");
	const Texture playerBodyWindowTexture = LoadTexture("Textures/Player_Body_Window.png");
	const Texture playerBodyPropeller000Texture = LoadTexture("Textures/Player_Body_Propeller_000.png");
	const Texture playerBodyPropeller001Texture = LoadTexture("Textures/Player_Body_Propeller_001.png");
	const Texture playerBodyPropeller002Texture = LoadTexture("Textures/Player_Body_Propeller_002.png");
	const Texture playerBodyTopTexture = LoadTexture("Textures/Player_Body_Top.png");

	const int textureWidth = playerBodyMainTexture.width;
	const int textureHeight = playerBodyMainTexture.height;

	const Texture fireTextures[FIRE_TEXTURES] = {
		LoadTexture("Textures/Player_Fire_Accelerate_000.png"),
		LoadTexture("Textures/Player_Fire_Accelerate_001.png"),
		LoadTexture("Textures/Player_Fire_Accelerate_002.png"),
		LoadTexture("Textures/Player_Fire_Accelerate_003.png"),
		LoadTexture("Textures/Player_Fire_Moving_000.png"),
		LoadTexture("Textures/Player_Fire_Moving_001.png"),
		LoadTexture("Textures/Player_Fire_Moving_002.png"),
		LoadTexture("Textures/Player_Fire_Moving_003.png"),
		LoadTexture("Textures/Player_Fire_Moving_004.png"),
		LoadTexture("Textures/Player_Fire_Moving_005.png"),
		LoadTexture("Textures/Player_Fire_Moving_006.png"),
		LoadTexture("Textures/Player_Fire_Moving_007.png"),
		LoadTexture("Textures/Player_Fire_Moving_008.png"),
		LoadTexture("Textures/Player_Fire_Moving_009.png"),
	};
	float currentFireTexture = -1;

	const float FIRE_TEXTURE_SPEED = 10;

	bool drawDirectionPoints = false;

	const bool DEBUG_PRINT_POS = false;
	const bool DEBUG_PRINT_ROT = false;
	const bool DEBUG_PRINT_VEL = false;

	const bool DEBUG_PRINT_FIRE_TEXTURE = false;
	
	const bool DEBUG_SHOW_HITBOX = false;
};

#endif