

#include "T1_HostileManager.h"
#include "T1_ProjectileManager.h"
#include "T1_Turret.h"


T1_Turret::T1_Turret(std::string aName, ObjectType aType, glm::vec2 aCenterPosition, glm::vec3 aColor, float anHp, float aDamage) :
	T1_Object(aName, aType, aCenterPosition, aColor),
	projectileCooldown(0.f)
{
	myHp = anHp;
	myDamage = aDamage;

	isActive = true;
	isDying = false;

	myScale = glm::vec2(1.f, 1.f);
}

T1_Turret::~T1_Turret()
{

}

void T1_Turret::Update(float myDeltaTimeSeconds) {
	Shoot(myDeltaTimeSeconds);
	if (isDying) {
		myScale.x -= myDeltaTimeSeconds;
		myScale.y -= myDeltaTimeSeconds;
		if (myScale.x <= 0.f && myScale.y <= 0.f) {
			isDying = false;
			myScale.x = myScale.y = 0;
		}
	}
}

void T1_Turret::Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix)
{
	glm::mat3 modelMatrix = visMatrix * Translate(myCenterPosition.x, myCenterPosition.y) * Scale(myScale.x, myScale.y);
	aScene->RenderMesh2D(myMesh, aScene->shaders["VertexColor"], modelMatrix);
}

void T1_Turret::Shoot(float myDeltaTimeSeconds)
{
	T1_HostileManager* hostileManager = T1_HostileManager::GetManager();
	if (isActive) {
		projectileCooldown -= myDeltaTimeSeconds * 2;

		if (hostileManager->EnemyTypeOnLine(myCenterPosition.y, myColor) && projectileCooldown < 0.f)
		{
			T1_ProjectileManager* projectileManager = T1_ProjectileManager::GetManager();
			projectileManager->AddProjectile(T1_Object::GetRandomString(20), T1_Object::Projectile, myCenterPosition, myColor, myDamage);

			projectileCooldown = 20.f;
		}

	}
}

void T1_Turret::SetActive()
{
	isActive = true;
}

void T1_Turret::SetDying() {
	isActive = false;
	isDying = true;
}

bool T1_Turret::IsDead() {
	return myScale.x == 0.f && myScale.y == 0.f;
}