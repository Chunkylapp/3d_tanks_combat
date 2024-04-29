#pragma once

#include <string>

#include "components/simple_scene.h"

class T1_Object {
public:

	enum ObjectType {
		Turret,
		Hostile,
		Projectile,
		Cell,
		RedLine,
		Spawner,
		HP,
		Collectible,
		StarUI,
		UIContainer
	};

	T1_Object(std::string aName, ObjectType aType, glm::vec2 aCenterPosition, glm::vec3 aColor);
	~T1_Object();

	void Move(float x, float y);

	void virtual Update(float myDeltaTimeSeconds);

	void virtual Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix);
	
	static std::string GetRandomString(int length);

	inline glm::mat3 Translate(float translateX, float translateY)
	{
		return glm::transpose(
			glm::mat3(1, 0, translateX,
				0, 1, translateY,
				0, 0, 1)
		);
	}

	inline glm::mat3 Scale(float scaleX, float scaleY)
	{
		return glm::mat3(scaleX, 0, 0,
			0, scaleY, 0,
			0, 0, 1);
	}

	inline glm::mat3 Rotate(float radians)
	{
		return glm::mat3(cos(radians), -sin(radians), 0,
			sin(radians), cos(radians), 0,
			0, 0, 1);
	}

	glm::vec2 GetCenterPosition() { return myCenterPosition; };

	glm::vec3 GetColor() { return myColor; };

	glm::vec2 GetSizes() { return mySizes; };

	ObjectType GetType() { return myType; };

	bool IsColliding(T1_Object* anObjcet, bool checkForColor);

	float GetRadius() { return myRadius; };

protected:

	glm::vec2 myCenterPosition;
	glm::vec3 myColor;
	glm::vec2 mySizes;
	
	float myRadius;

	Mesh* myMesh;

	ObjectType myType;
};