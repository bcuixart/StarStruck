#include "World.hh"
#include "GameManager.hh"

World::World() 
{
	worldObjects = map<pair<int, int>, vector<WorldObject*>>();
	loadedChunks = set<pair<int, int>>();
	collectedCoins = set<pair<int, int>>();
	obstacleTextures = vector<Texture>(OBSTACLE_TEXTURES + 1);

	for (int i = 0; i <= OBSTACLE_TEXTURES; ++i) {
		std::stringstream ss;
		ss << "Assets/Textures/Asteroid/Obstacle_Asteroid_"
			<< std::setfill('0') << std::setw(3) << (i)
			<< ".png";
		obstacleTextures[i] = LoadTexture(ss.str().c_str());

		std::cout << ss.str() << std::endl;
	}
}

void World::Prepare(int _seed) 
{
	seed = _seed;

	worldObjects = map<pair<int, int>, vector<WorldObject*>>();
	loadedChunks = set<pair<int, int>>();
	collectedCoins = set<pair<int, int>>();
}

void World::ClearWorld() 
{
	for (auto it = loadedChunks.begin(); it != loadedChunks.end(); )
	{
		pair<int, int> chunk = *it;
		UnloadChunk(chunk);

		it = loadedChunks.erase(it);
	}
}

float World::getRandomNumberFromSeed(int x, int y) const 
{
	unsigned int hash = seed;

	hash ^= (static_cast<unsigned int>(x) * 928371) ^ (static_cast<unsigned int>(y) * 982451);

	hash = (hash ^ (hash >> 16)) * 0x45d9f3b;
	hash = (hash ^ (hash >> 16)) * 0x45d9f3b;
	hash = hash ^ (hash >> 16);

	hash ^= hash >> 6;
	hash *= 0x6D2B79F5;
	hash ^= hash >> 16;

	return static_cast<float>(hash) / std::numeric_limits<unsigned int>::max();
}

float World::getRandomNumberBetween(float min, float max, int x, int y) const 
{
	float random = getRandomNumberFromSeed(x, y);

	return min + (max - min) * random;
}

void World::LoadUnloadNearbyChunks(const Vector2& playerPosition)
{
	int playerChunkX = int(playerPosition.x / CHUNK_SIZE);
	int playerChunkY = int(playerPosition.y / CHUNK_SIZE);

	int minX = playerChunkX - PLAYER_LOAD_CHUNK_RADIUS;
	int maxX = playerChunkX + PLAYER_LOAD_CHUNK_RADIUS;
	int minY = playerChunkY - PLAYER_LOAD_CHUNK_RADIUS;
	int maxY = playerChunkY + PLAYER_LOAD_CHUNK_RADIUS;

	LoadNearbyChunks(minX, maxX, minY, maxY);
	UnloadNearbyChunks(minX, maxX, minY, maxY);
}

void World::LoadNearbyChunks(const int minX, const int maxX, const int minY, const int maxY) 
{
	for (int x = minX; x <= maxX; ++x) {
		for (int y = minY; y <= maxY; ++y) {

			pair<int, int> chunk = { x, y };
			if (loadedChunks.find(chunk) == loadedChunks.end())
			{
				if (DEBUG_PRINT_CHUNKINFO) std::cout << "Must load a chunk: " << x << ' ' << y << std::endl;
				LoadChunk(chunk);
			}
		}
	}
}

void World::UnloadNearbyChunks(const int minX, const int maxX, const int minY, const int maxY) 
{
	for (auto it = loadedChunks.begin(); it != loadedChunks.end(); )
	{
		pair<int, int> chunk = *it;
		int x = chunk.first;
		int y = chunk.second;
		if (!(x >= minX && x <= maxX && y >= minY && y <= maxY))
		{
			if (DEBUG_PRINT_CHUNKINFO) std::cout << "Must delete a chunk: " << x << ' ' << y << std::endl;
			UnloadChunk(chunk);
			it = loadedChunks.erase(it);
		}
		else {
			++it;
		}
	}
}

void World::LoadChunk(const pair<int, int>& chunk)
{
	loadedChunks.insert(chunk);
	worldObjects[chunk] = vector<WorldObject*>();

	int minX = chunk.first * CHUNK_SIZE - CHUNK_SIZE / 2 + CHUNK_OBJECT_SIZE / 2;
	int maxX = chunk.first * CHUNK_SIZE + CHUNK_SIZE / 2 - CHUNK_OBJECT_SIZE / 2;
	int minY = chunk.second * CHUNK_SIZE - CHUNK_SIZE / 2 + CHUNK_OBJECT_SIZE / 2;
	int maxY = chunk.second * CHUNK_SIZE + CHUNK_SIZE / 2 - CHUNK_OBJECT_SIZE / 2;

	int chunkDistance = sqrt(chunk.first * chunk.first + chunk.second * chunk.second);

	float chanceToSpawnCoin = 0.1f;
	float chanceToSpawnObstacle = min(0.05f + 0.001f * chunkDistance, 0.3f);
	if (chunk.first == 0 && chunk.second == 0) chanceToSpawnObstacle = chanceToSpawnCoin = 0;

	for (int x = minX; x <= maxX; x += CHUNK_OBJECT_SIZE) {
		for (int y = minY; y <= maxY; y += CHUNK_OBJECT_SIZE) {
			float chanceToSpawnObject = getRandomNumberFromSeed(x, y);

			// BG Stars
			if (chanceToSpawnObject > 0.075f && chanceToSpawnObject < 0.5f)
			{
				worldObjects[chunk].push_back(
					new WorldObject({ float(x + chanceToSpawnObject*200),float(y + chanceToSpawnObject*200) },
						0,
						getRandomNumberBetween(1, 5, x, y),
						{ coinTexture })
				);
			}

			// Coins
			if (chanceToSpawnObject <= chanceToSpawnCoin && collectedCoins.find({ x,y }) == collectedCoins.end())
			{
				worldObjects[chunk].push_back(
					new Coin({ float(x),float(y) }, 
					getRandomNumberBetween(0, 360 * 1 / chanceToSpawnCoin, x, y),
					.65f * chanceToSpawnObject + 0.065f / 2, 
						{ coinTexture })
				);
			}

			// Obstacle
			if (chanceToSpawnObject >= 1 - chanceToSpawnObstacle)
			{
				worldObjects[chunk].push_back(
					new Obstacle({ float(x),float(y) },
						getRandomNumberBetween(0, 360 * 1 / chanceToSpawnObstacle, x, y),
						std::pow(chanceToSpawnObject, 7),
						obstacleTextures)
				);
			}
		}
	}
}

void World::UnloadChunk(const pair<int, int>& chunk)
{
	for (WorldObject* obj : worldObjects[chunk]) {
		delete obj;
	}

	worldObjects[chunk].clear();
}

void World::DeleteCoin(const WorldObject* coinToDelete)
{
	Vector2 coinPos = coinToDelete->getPosition();
	collectedCoins.insert({ coinPos.x, coinPos.y });

	for (auto& chunk : worldObjects) {
		auto& objects = chunk.second;

		for (auto it = objects.begin(); it != objects.end(); ++it) {
			if (*it == coinToDelete) {
				objects.erase(it);
				break;
			}
		}
	}

	delete coinToDelete;
}

void World::Update(const Vector2& playerPosition, const float playerRadius, const float deltaTime)
{
	LoadUnloadNearbyChunks(playerPosition);

	WorldObject* coinToDelete = nullptr;

	for (auto it = loadedChunks.begin(); it != loadedChunks.end(); ++it)
	{
		pair<int, int> chunk = *it;
		int s = worldObjects[chunk].size();
		for (int i = 0; i < s; ++i) {
			worldObjects[chunk][i]->Update(deltaTime);

			int colResult = worldObjects[chunk][i]->CheckPlayerCollision(playerPosition, playerRadius);
			if (colResult == 1) coinToDelete = worldObjects[chunk][i];
			if (colResult == 0) GameManager::instance->KillPlayer();
		}
	}

	if (coinToDelete != nullptr) {
		GameManager::instance->CollectCoin();
		DeleteCoin(coinToDelete);
	}
}

void World::Render() 
{
	for (auto it = loadedChunks.begin(); it != loadedChunks.end(); ++it)
	{
		pair<int, int> chunk = *it;
		int s = worldObjects[chunk].size();

		for (int i = 0; i < s; ++i) worldObjects[chunk][i]->Render();
	}
}