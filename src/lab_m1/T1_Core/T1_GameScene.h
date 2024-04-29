#pragma once

#include <string>

#include "T1_Object.h"
#include "T1_Turret.h"

#include "components/simple_scene.h"

class T1_Cell : public T1_Object {
public:
	T1_Cell(std::string, ObjectType aType, glm::vec2 aCenterPosition, glm::vec3 aColor);
	~T1_Cell();

	void Update(float myDeltaTimeSeconds) override;

	void Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix) override;

	bool IsInCell(float mouseX, float mouseY);
};

class T1_RedLine : public T1_Object {
public:
	T1_RedLine(std::string, ObjectType aType, glm::vec2 aCenterPosition, glm::vec3 aColor);
	~T1_RedLine();

	void Update(float myDeltaTimeSeconds) override;

	void Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix) override;

	// bool IsInRedLine();
};

class T1_Spawner : public T1_Object {
public:

	T1_Spawner(std::string, ObjectType aType, glm::vec2 aCenterPosition, glm::vec3 aColor, T1_Turret::TurretType aSpawnType);
	~T1_Spawner();

	void Update(float myDeltaTimeSeconds) override;

	void Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix) override;

	bool IsInCell(float mouseX, float mouseY);

	bool IsDragging() { return isDragging; };

	void Drag() { isDragging = true; };

	void StopDrag();

	void MoveTurret(float mouseX, float mouseY);

	T1_Turret::TurretType GetSpawnerType() { return mySpawnerType; };

private:

	bool isDragging;

	glm::vec2 myDragMousePoz;

	T1_Turret::TurretType mySpawnerType;
	Mesh* myTurret;
};

class T1_HP : public T1_Object
{
public:
	T1_HP(std::string, ObjectType aType, glm::vec2 aCenterPosition, glm::vec3 aColor);
	~T1_HP();

	void Update(float myDeltaTimeSeconds) override;

	void Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix) override;
};