#ifndef COIN_HH
#define COIN_HH

#include <iostream>

#include <raymob.h>
#include <raymath.h>

#include "WorldObject.hh"

using namespace std;

class Coin : public WorldObject {
public:
	Coin(Vector2 _position, float _rotation, float _scale, const vector<Texture>& _textures);

	virtual void Update(const float deltaTime);
	virtual void Render();

	virtual int CheckPlayerCollision(const Vector2& playerPos, const float playerRadius) const;

protected:

private:
	const float COIN_ROTATE_SPEED = 10;

	const float COIN_RADIUS_SCALE_MULTIPLIER = 250;
};

#endif