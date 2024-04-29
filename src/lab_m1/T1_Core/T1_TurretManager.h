#pragma once

#include <vector>

#include "T1_Object.h"
#include "T1_Turret.h"

class T1_TurretManager
{
public:

	static T1_TurretManager* theManager;

	static T1_TurretManager* GetManager();


	void Update(float myDeltaTimeSeconds);

	void Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix);

	void AddTurret(glm::vec2 aCenterPosition, T1_Turret::TurretType aType);

	void Kill(glm::vec2 aCenterPosition);

	bool TurretAtPosition(glm::vec2 aCenterPosition);

private:
	T1_TurretManager();
	~T1_TurretManager();

	std::vector<T1_Turret*> myTurretsBottom;
	std::vector<T1_Turret*> myTurretsMiddle;
	std::vector<T1_Turret*> myTurretsTop;
};