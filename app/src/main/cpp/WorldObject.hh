#ifndef WORLDOBJECT_HH
#define WORLDOBJECT_HH

#include <iostream>
#include <vector>

#include <raymob.h>
#include <raymath.h>

using namespace std;

class WorldObject {
public:
	WorldObject(Vector2 _position, float _rotation, float _scale, const vector<Texture>& _textures);
	virtual ~WorldObject() = default;

	virtual void Update(const float deltaTime);
	virtual void Render();

	virtual int CheckPlayerCollision(const Vector2& playerPos, const float playerRadius) const;

	Vector2 getPosition() const;
	float getRotation() const;
	float getScale() const;

protected:
	Vector2 position;
	float rotation;
	float scale;

	const bool DEBUG_SHOW_OBJECTS_HITBOX = false;

	vector<Texture> textures;
};

#endif