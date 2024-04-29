#pragma once

#include "T1_Object.h"

class T1_Projectile : public T1_Object
{
public:

	T1_Projectile(std::string aName, ObjectType aType, glm::vec2 aCenterPosition, glm::vec3 aColor, float aDamage);
	~T1_Projectile();

	void Update(float myDeltaTimeSeconds) override;

	void Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix) override;

	bool IsDead() { return !myScale; };

	void SetDying();

private:
	
	bool isDying;

	float myDamage;
	float myRotation;

	float myScale;

};