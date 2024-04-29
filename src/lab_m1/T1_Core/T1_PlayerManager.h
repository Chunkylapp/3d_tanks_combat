#pragma once

#include <vector>

#include "T1_Collectible.h"
#include "T1_GameScene.h"

#include "components/simple_scene.h"


class T1_PlayerManager {
public:
	static T1_PlayerManager* theManager;

	static T1_PlayerManager* GetManager();

	void Update(float myDeltaTimeSeconds);

	void Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix);

	void TryToCollect(float mouseX, float mouseY);

	void LoseLifePoint();

	bool GameOver() { return !leftHeart; };

	void AddStars(int stars);

	void DelStars(int stars);

	int GetStars() { return myStars; };

private:
	T1_PlayerManager();
	~T1_PlayerManager();

	int myStars;
	float myTimeToTrySpawn;

	T1_Object* leftHeart;
	T1_Object* middleHeart;
	T1_Object* rightHeart;

	std::vector<T1_Collectible*> mySpawnedStars;
	std::vector<T1_Object*> myStarsUI;

};