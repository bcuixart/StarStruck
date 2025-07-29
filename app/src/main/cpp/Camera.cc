#include "Camera.hh"

CameraManager::CameraManager()
{

}

void CameraManager::Prepare() 
{
	cameraPosition.x = 0;
	cameraPosition.y = 0;
}

Vector2 CameraManager::getCameraPosition() const
{
	return cameraPosition;
}

void CameraManager::Update(const Vector2 playerPosition, const int screenWidth, const int screenHeight, const float deltaTime)
{
	camera = { 0 };

	float distance = Vector2Distance(playerPosition, cameraPosition);
	Vector2 direction = Vector2Normalize(playerPosition - cameraPosition);

	cameraSpeed = min(distance / CAMERA_FAST_DISTANCE * CAMERA_SPEED_SLOW, CAMERA_SPEED_FAST);

	cameraPosition.x += direction.x * cameraSpeed * deltaTime;
	cameraPosition.y += direction.y * cameraSpeed * deltaTime;

	camera.target = cameraPosition;
	camera.offset = (Vector2){ float(screenWidth / 2), float(screenHeight / 2) };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
}

void CameraManager::MBeginMode2D()
{
	BeginMode2D(camera);
}