#pragma once

#include "T1_Object.h"

#include "components/simple_scene.h"

class T1_Collectible : public T1_Object
{
public:

	T1_Collectible(std::string aName, glm::vec2 aCenterPosition, glm::vec3 aColo);
	~T1_Collectible();

	void Update(float myDeltaTimeSeconds) override;

	void Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix) override;

	bool IsDead() { return !myScale; };

	bool IsDying() { return isDying; };

	void SetDying();

private:
	
	bool isDying;

	float myLifeTimeSeconds;
	float myScale;

	float myAnimationY;
};