#pragma once

#include "T1_Object.h"

class T1_Hostile : public T1_Object
{
public:

	enum HostileType {
		Orange,
		Blue,
		Yellow,
		Purple
	};

	T1_Hostile(std::string aName, ObjectType aType, glm::vec2 aCenterPosition, glm::vec3 aColor, HostileType aHostileType);
	~T1_Hostile();


	void Update(float myDeltaTimeSeconds) override;

	void Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix) override;

	bool IsDead() { return !myScale; };

	void SetDying();

private:
	bool isDying;

	float myHP;
	float myRotation;
	float myScale;

};