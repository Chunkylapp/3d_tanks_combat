#pragma once

#include "T1_Object.h"
#include "T1_Projectile.h"

class T1_Turret : public T1_Object
{

public:

	enum TurretType {
		Orange,
		Blue,
		Yellow,
		Purple
	};

	T1_Turret(std::string aName, ObjectType aType, glm::vec2 aCenterPosition, glm::vec3 aColor, float anHp, float aDamage);
	~T1_Turret();

	void Update(float myDeltaTimeSeconds) override;

	void Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix) override;

	void Shoot(float myDeltaTimeSeconds);

	void SetActive();

	void SetDying();

	bool IsDead();

private:
	float myHp;
	float myDamage;

	float projectileCooldown;

	bool isActive;
	bool isDying;

	glm::vec2 myScale;

	TurretType myType;
};