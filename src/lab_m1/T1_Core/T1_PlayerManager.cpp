
#include "T1_Collectible.h"
#include "T1_PlayerManager.h"

T1_PlayerManager::T1_PlayerManager()
{
	leftHeart = new T1_HP(T1_Object::GetRandomString(20), T1_Object::HP, glm::vec2(120, 97.5), glm::vec3(1.0f, 0.0f, 0.0f));
	middleHeart = new T1_HP(T1_Object::GetRandomString(20), T1_Object::HP, glm::vec2(140, 97.5), glm::vec3(1.0f, 0.0f, 0.0f));
    rightHeart = new T1_HP(T1_Object::GetRandomString(20), T1_Object::HP, glm::vec2(160, 97.5), glm::vec3(1.0f, 0.0f, 0.0f));
	myTimeToTrySpawn = 1.f;
	myStars = 0;
}

T1_PlayerManager::~T1_PlayerManager() {

}

T1_PlayerManager* T1_PlayerManager::theManager = nullptr;

T1_PlayerManager* T1_PlayerManager::GetManager()
{
	if (theManager == nullptr) {
		T1_PlayerManager::theManager = new T1_PlayerManager();
	}
	return T1_PlayerManager::theManager;
}

void T1_PlayerManager::Update(float myDeltaTimeSeconds) {
	if (myStarsUI.size() < myStars) {
		float starX = 97.5;
		float starY = 87;
		if (myStarsUI.size() > 0) {
			starX = myStarsUI[myStarsUI.size() - 1]->GetCenterPosition().x + 5.f;
			starY = myStarsUI[myStarsUI.size() - 1]->GetCenterPosition().y;
		}
		if (starX > 185) {
			starX = 97.5;
			starY = starY - 5.f;
		}
		myStarsUI.push_back(new T1_Object(T1_Object::GetRandomString(20),
							T1_Object::ObjectType::StarUI,
							glm::vec2(starX, starY),
							glm::vec3(1.0f, 1.0f, 1.0f)));
	}
	if (myStarsUI.size() > myStars) {
		int size = myStarsUI.size() - myStars;
		for (int i = 0; i < size; i++) {
			T1_Object* toDelete = myStarsUI[myStarsUI.size() - 1];
			myStarsUI.pop_back();
			delete toDelete;
		}
	}

	for (int i = 0; i < mySpawnedStars.size(); i++) {
		mySpawnedStars[i]->Update(myDeltaTimeSeconds);
		if (mySpawnedStars[i]->IsDead()) {
			T1_Collectible* toDelete = mySpawnedStars[i];
			mySpawnedStars.erase(mySpawnedStars.begin() + i, mySpawnedStars.begin() + i + 1);
			i--;
			delete toDelete;
		}
	}


	myTimeToTrySpawn -= myDeltaTimeSeconds * 7.5f;

	if (myTimeToTrySpawn <= 0.f) {
		int rand_no = rand() * myDeltaTimeSeconds;
		int starX = rand_no % 192;
		int starY = rand_no % 80; // to not spawn over ui :3
		if (starX < 10.f)
			starX = 10.f;
		if (starY < 10.f)
			starY = 10.f;

		mySpawnedStars.push_back(new T1_Collectible(T1_Object::GetRandomString(20),
								 glm::vec2(starX, starY),
								 glm::vec3(1.0f, 1.0f, 1.0f)));

		myTimeToTrySpawn = 25.f;
	}

}

void T1_PlayerManager::Draw(gfxc::SimpleScene* aScene, glm::mat3 visMatrix)
{
	for (int i = 0; i < mySpawnedStars.size(); i++) {
		mySpawnedStars[i]->Draw(aScene, visMatrix);
	}
	for (int i = 0; i < myStarsUI.size(); i++) {
		myStarsUI[i]->Draw(aScene, visMatrix);
	}

	if (leftHeart)
		leftHeart->Draw(aScene, visMatrix);
	if (middleHeart)
		middleHeart->Draw(aScene, visMatrix);
	if (rightHeart)
		rightHeart->Draw(aScene, visMatrix);
}

void T1_PlayerManager::TryToCollect(float mouseX, float mouseY) {
	for (int i = 0; i < mySpawnedStars.size(); i++) {
		if (glm::distance(mySpawnedStars[i]->GetCenterPosition(), glm::vec2(mouseX, mouseY)) < mySpawnedStars[i]->GetRadius() &&
			!mySpawnedStars[i]->IsDying()) {
			myStars++;
			mySpawnedStars[i]->SetDying();
			return;
		}
	}
}

void T1_PlayerManager::LoseLifePoint() {
	if (rightHeart) {
		delete rightHeart;
		rightHeart = nullptr;
		return;
	}
	if (middleHeart) {
		delete middleHeart;
		middleHeart = nullptr;
		return;
	}
	if (leftHeart) {
		delete leftHeart;
		leftHeart = nullptr;
		return;
	}
}

void T1_PlayerManager::AddStars(int stars) {
	myStars += stars;
}

void T1_PlayerManager::DelStars(int stars) {
	myStars -= stars;
}