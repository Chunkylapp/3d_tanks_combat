#pragma once

#include <vector>

#include "components/simple_scene.h"

#include "T1_HostileManager.h"
#include "T1_Object.h"
#include "T1_Turret.h"

class T1_Core : public gfxc::SimpleScene {

public:

	struct ViewportSpace
	{
		ViewportSpace() : x(0), y(0), width(1), height(1) {}
		ViewportSpace(int x, int y, int width, int height)
			: x(x), y(y), width(width), height(height) {}
		int x;
		int y;
		int width;
		int height;
	};

	struct LogicSpace
	{
		LogicSpace() : x(0), y(0), width(1), height(1) {}
		LogicSpace(float x, float y, float width, float height)
			: x(x), y(y), width(width), height(height) {}
		float x;
		float y;
		float width;
		float height;
	};

	T1_Core();
	~T1_Core();

	void Init() override;

	void Core();

	void FrameStart();

	void Update(float myDeltaTimeSeconds) override;

	void OnKeyPress(int key, int mods) override;

	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;

	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;

	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;

	// Utils
	void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear);

	glm::mat3 VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);

private:

	ViewportSpace viewSpace;
	LogicSpace logicSpace;

	std::vector<T1_Object*>* myObjects;

	T1_Turret* myPlaceable;
};