#include "WorldObject.hh"

WorldObject::WorldObject(Vector2 _position, float _rotation, float _scale, const vector<Texture>& _textures)
{
	position = _position;
	rotation = _rotation;
	scale = _scale;

	textures = _textures;
}

Vector2 WorldObject::getPosition() const
{
	return position;
}

float WorldObject::getRotation() const
{
	return rotation;
}

float WorldObject::getScale() const
{
	return scale;
}

void WorldObject::Update(const float deltaTime)
{

}

int WorldObject::CheckPlayerCollision(const Vector2& playerPos, const float playerRadius) const 
{
	return -1;
}

void WorldObject::Render() 
{
	DrawCircle(position.x, position.y, scale, { 229, 197, 247, 255 });
}