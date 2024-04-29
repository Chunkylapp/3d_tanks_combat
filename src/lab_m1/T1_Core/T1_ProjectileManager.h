#pragma once

#include <vector>

#include "T1_Object.h"
#include "T1_Projectile.h"

class T1_ProjectileManager
{
public:

	static T1_ProjectileManager* theManager;

	static T1_ProjectileManager* GetManager();


	void Update(float myDeltaTimeSeconds);

	void Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix);

	void AddProjectile(std::string aName, T1_Object::ObjectType aType, glm::vec2 aCenterPosition, glm::vec3 aColor, float aDamage);

private:
	T1_ProjectileManager();
	~T1_ProjectileManager();

	std::vector<T1_Projectile*> myProjectilesBottom;
	std::vector<T1_Projectile*> myProjectilesMiddle;
	std::vector<T1_Projectile*> myProjectilesTop;
};