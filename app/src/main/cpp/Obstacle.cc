#include "Obstacle.hh"

Obstacle::Obstacle(Vector2 _position, float _rotation, float _scale, const vector<Texture>& _textures)
	: WorldObject(_position, _rotation, _scale, _textures)
{

}

int Obstacle::CheckPlayerCollision(const Vector2& playerPos, const float playerRadius) const
{
	if (DEBUG_PLAYER_INVINCIBLE) return -1;

	if (CheckCollisionCircles(position, scale * OBSTACLE_RADIUS_SCALE_MULTIPLIER, playerPos, playerRadius)) return 0;
	return -1;
}

void Obstacle::Update(const float deltaTime) 
{
	currentTexture = currentTexture + ANIMATION_SPEED * deltaTime;
	if (currentTexture >= textures.size()) currentTexture = 1;
}

void Obstacle::Render()
{
	Rectangle sourceRec = { 0.0f, 0.0f, (float)textures[0].width, (float)textures[0].height };
	Rectangle destRec = {
		position.x,
		position.y,
		(float)textures[0].width * scale,
		(float)textures[0].height * scale
	};
	Vector2 origin = {
		(float)textures[0].width * scale / 2,
		(float)textures[0].height * scale / 2
	};

	DrawTexturePro(textures[0], sourceRec, destRec, origin, rotation, COLOR_BASE);
	DrawTexturePro(textures[(int)currentTexture], sourceRec, destRec, origin, rotation, COLOR_CRATERS);

	if (DEBUG_SHOW_OBJECTS_HITBOX) DrawCircleLines(position.x, position.y, scale * OBSTACLE_RADIUS_SCALE_MULTIPLIER, RED);
}