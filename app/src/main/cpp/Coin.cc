#include "Coin.hh"

Coin::Coin(Vector2 _position, float _rotation, float _scale, const vector<Texture>& _textures)
	: WorldObject(_position, _rotation, _scale, _textures)
{

}

int Coin::CheckPlayerCollision(const Vector2& playerPos, const float playerRadius) const
{
	if (CheckCollisionCircles(position, scale * COIN_RADIUS_SCALE_MULTIPLIER, playerPos, playerRadius)) return 1;
	return -1;
}

void Coin::Update(float deltaTime)
{
	rotation = std::fmod(rotation + COIN_ROTATE_SPEED * deltaTime, 360.f);
}

void Coin::Render() 
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

	DrawTexturePro(textures[0], sourceRec, destRec, origin, rotation, COIN_COLOR);

    if (DEBUG_SHOW_OBJECTS_HITBOX) DrawCircleLines(position.x, position.y, scale * COIN_RADIUS_SCALE_MULTIPLIER, GREEN);
}