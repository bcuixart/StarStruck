#ifndef CAMERA_HH
#define CAMERA_HH

#include <iostream>

#include <raymob.h>
#include <raymath.h>

using namespace std;

class CameraManager {
public:
	CameraManager();

	void Update(const Vector2 playerPosition, const int screenWidth, const int screenHeight, const float deltaTime);

	void Prepare();

	void MBeginMode2D();

	Vector2 getCameraPosition() const;

protected:

private:
	Camera2D camera = { 0 };

	Vector2 cameraPosition = { 0,0 };

	const float CAMERA_FAST_DISTANCE = 50;
	const float CAMERA_SPEED_SLOW = 150;
	const float CAMERA_SPEED_FAST = 300;

	float cameraSpeed;
};

#endif