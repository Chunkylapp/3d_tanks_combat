

#include "T1_ProjectileManager.h"
#include "T1_HostileManager.h"

T1_ProjectileManager::T1_ProjectileManager() {

}

T1_ProjectileManager::~T1_ProjectileManager() {

}

T1_ProjectileManager* T1_ProjectileManager::theManager = nullptr;

T1_ProjectileManager* T1_ProjectileManager::GetManager()
{
	if (theManager == nullptr) {
		T1_ProjectileManager::theManager = new T1_ProjectileManager();
	}
	return T1_ProjectileManager::theManager;
}

void T1_ProjectileManager::Update(float myDeltaTimeSeconds)
{
	T1_HostileManager* hostileManager = T1_HostileManager::GetManager();
	// bottom
	for (int i = 0; i < myProjectilesBottom.size(); i++)
	{
		myProjectilesBottom[i]->Update(myDeltaTimeSeconds);
		// check for OOB despawn and collision based despawn
		if (myProjectilesBottom[i]->GetCenterPosition().x > 200 || myProjectilesBottom[i]->IsDead()) {
			T1_Projectile* ToDelete = myProjectilesBottom[i];
			myProjectilesBottom.erase(myProjectilesBottom.begin() + i, myProjectilesBottom.begin() + i + 1);
			delete ToDelete;
			i--;
		}
		else {
			if (hostileManager->CollisionCheck(myProjectilesBottom[i], 0, true)) {
				myProjectilesBottom[i]->SetDying();
			}
		}
	}
	// middle
	for (int i = 0; i < myProjectilesMiddle.size(); i++)
	{
		myProjectilesMiddle[i]->Update(myDeltaTimeSeconds);
		// check for OOB despawn and collision based despawn
		if (myProjectilesMiddle[i]->GetCenterPosition().x > 200 || myProjectilesMiddle[i]->IsDead()) {
			T1_Projectile* ToDelete = myProjectilesMiddle[i];
			myProjectilesMiddle.erase(myProjectilesMiddle.begin() + i, myProjectilesMiddle.begin() + i + 1);
			delete ToDelete;
			i--;
		}
		else {
			if (hostileManager->CollisionCheck(myProjectilesMiddle[i], 1, true)) {
				myProjectilesMiddle[i]->SetDying();
			}
		}
	}
	// top
	for (int i = 0; i < myProjectilesTop.size(); i++)
	{
		myProjectilesTop[i]->Update(myDeltaTimeSeconds);
		// check for OOB despawn and collision based despawn
		if (myProjectilesTop[i]->GetCenterPosition().x > 200 || myProjectilesTop[i]->IsDead()) {
			T1_Projectile* ToDelete = myProjectilesTop[i];
			myProjectilesTop.erase(myProjectilesTop.begin() + i, myProjectilesTop.begin() + i + 1);
			delete ToDelete;
			i--;
		}
		else {
			if (hostileManager->CollisionCheck(myProjectilesTop[i], 2, true)) {
				myProjectilesTop[i]->SetDying();
			}
		}
	}
}

void T1_ProjectileManager::Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix)
{
	for (int i = 0; i < myProjectilesBottom.size(); i++)
		myProjectilesBottom[i]->Draw(aScene, visMatrix);

	for (int i = 0; i < myProjectilesMiddle.size(); i++)
		myProjectilesMiddle[i]->Draw(aScene, visMatrix);

	for (int i = 0; i < myProjectilesTop.size(); i++)
		myProjectilesTop[i]->Draw(aScene, visMatrix);
}

void T1_ProjectileManager::AddProjectile(std::string aName, T1_Object::ObjectType aType, glm::vec2 aCenterPosition, glm::vec3 aColor,float aDamage)
{
	if (aCenterPosition.y == 20.f)
		myProjectilesBottom.push_back(new T1_Projectile(aName, aType, aCenterPosition, aColor, aDamage));
	else
		if (aCenterPosition.y == 40.f)
			myProjectilesMiddle.push_back(new T1_Projectile(aName, aType, aCenterPosition, aColor, aDamage));
		else
			myProjectilesTop.push_back(new T1_Projectile(aName, aType, aCenterPosition, aColor, aDamage));
}