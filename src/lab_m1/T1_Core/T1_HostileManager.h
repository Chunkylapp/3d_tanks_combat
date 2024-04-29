#pragma once

#include <vector>

#include "T1_Hostile.h"

#include "components/simple_scene.h"

class T1_HostileManager {
public:
	
	static T1_HostileManager* theManager;

	static T1_HostileManager* GetManager();

	void Update(float myDeltaTimeSeconds);

	void Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix);

	bool CollisionCheck(T1_Object* aStar, unsigned short grid, bool checkForColor); // grid is 0 for bottom -> 2 for top

	bool EnemyTypeOnLine(float aLineCoordinate, glm::vec3 aColor);

private:

	T1_HostileManager();
	~T1_HostileManager();

	std::vector<T1_Hostile*> myHostilesBottom;
	std::vector<T1_Hostile*> myHostilesMiddle;
	std::vector<T1_Hostile*> myHostilesTop;

	float timeToTrySpawn;

};