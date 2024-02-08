#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Scene.h"
#include "Sprite.h"

class TitleScene {
public:

	TitleScene();

	~TitleScene();

	void Initialize();

	void Update();

	void Draw();

	bool IsSceneEnd() { return isSceneEnd; }
	SceneType NextScene() { return SceneType::kGamePlay; }

private:

	bool isSceneEnd = false;

};
